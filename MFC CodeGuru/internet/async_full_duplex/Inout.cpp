#include "stdafx.h"
#include "inout.h"
#include <process.h>

//****************default threads implementation*************************
void ServiceThreadFunc(void* param)
{
	CInOutConnection* MainThread = (CInOutConnection*)param;
	MainThread->AddThread();
	while (!MainThread->Terminate())
	{
		Sleep(1000);
#ifndef _DEBUG
	try{
#endif
		MainThread->OnServiceTimer();
#ifndef _DEBUG
	}catch(...){};
#endif
	};
	MainThread->RemoveThread();
}
 
void InThreadFunc(void* param)
{
	CInOutConnection* MainThread = (CInOutConnection*)param;
#ifndef _DEBUG
	try{
#endif
#ifndef _DEBUG
	try{
#endif
	if (!MainThread->InitInThread())
	{
		MainThread->SetTerminate();
		return;
	};
	while (!MainThread->Terminate())
	{
		int error;
		int length;
		void* msg;
#ifndef _DEBUG
	try{
#endif
//		msg = MainThread->cioReceiveMessage(&error, &length);
		msg = MainThread->InternalReceiveMessage(&error, &length);
#ifndef _DEBUG
	}catch(...){msg = NULL;};
#endif
		if (error!=0) 
		{
			MainThread->OnInThreadError();
			break;
		};
		EnterCriticalSection(&MainThread->timeoutGuard);
		MainThread->TimeOutCounter = MainThread->TimeOutInit;
		LeaveCriticalSection(&MainThread->timeoutGuard);
		if (msg!=NULL) 
		{
#ifndef _DEBUG
	try{
#endif
			MainThread->PreprocessIncomingMessage(msg, length);
#ifndef _DEBUG
	}catch(...){};
#endif
		} else
		{//perform idle action
#ifndef _DEBUG
	try{
#endif
			MainThread->OnInThreadIdle();
#ifndef _DEBUG
	}catch(...){};
#endif
		};
	};
	MainThread->SetTerminate();
	MainThread->InThreadTerminated();
#ifndef _DEBUG
	}catch(...)
	{
		MainThread->SetTerminate();
		MainThread->InThreadTerminated();
	};
#endif
#ifndef _DEBUG
	}catch(...){}; //catch exceptions in previous catch block
#endif
}

void OutThreadFunc(void* param)
{
	CInOutConnection* MainThread = (CInOutConnection*)param;
#ifndef _DEBUG
	try{
#endif
#ifndef _DEBUG
	try{
#endif
	if (!MainThread->InitOutThread())
	{
		MainThread->SetTerminate();
		return;
	};
	while (!MainThread->Terminate())
	{
		if (MainThread->GetOutQueue()->IsQueueFull())
		{
			DWORD length, len;
			void* msg = MainThread->GetOutQueue()->GetFirstMessage(length);
			if (msg!=NULL) 
			{
				void* lp= NULL;
				BOOL res = FALSE;
#ifndef _DEBUG
	try{
#endif
				MainThread->PreprocessOutgoingMessage(msg);
				lp = MainThread->PrepareMessageToSend(msg, length, len);
				res = MainThread->cioSendMessage(lp, len);
#ifndef _DEBUG
	}catch(...){}; 
#endif
				if (lp!=NULL) delete lp;
//				delete msg;  // - the responsibility to delete msg is on PrepareMessageToSend
				if (!res)
				{
					MainThread->OnOutThreadError();
					break;
				};
			};
		} else
		{//perform idle action
#ifndef _DEBUG
	try{
#endif
			MainThread->OnOutThreadIdle();
#ifndef _DEBUG
	}catch(...){}; 
#endif
		};
	};
	MainThread->SetTerminate();
	MainThread->OutThreadTerminated();
#ifndef _DEBUG
	}catch(...)
	{
		MainThread->SetTerminate();
		MainThread->OutThreadTerminated();
	};
#endif
#ifndef _DEBUG
	}catch(...){}; 
#endif
}

void SyncThreadFunc(void* param)
{
	CInOutConnection* MainThread = (CInOutConnection*)param;
#ifndef _DEBUG
	try{
#endif
#ifndef _DEBUG
	try{
#endif
	if (!MainThread->InitSyncThread())
	{
		MainThread->SetTerminate();
		return;
	};
	while (!MainThread->Terminate())
	{
		if (MainThread->GetInQueue()->IsQueueFull())
		{
#ifndef _DEBUG
	try{
#endif
			MainThread->ProcessMessage();
#ifndef _DEBUG
	}catch(...){}; 
#endif
		} else
		{//perform idle action
			MainThread->OnSyncThreadIdle();
		};
	};
	MainThread->SetTerminate();
	MainThread->SyncThreadTerminated();
#ifndef _DEBUG
	}catch(...)
	{
		MainThread->SetTerminate();
		MainThread->SyncThreadTerminated();
	};
#endif
#ifndef _DEBUG
	}catch(...){}; 
#endif
}

//*************************CInOutConnection*************************
CInOutConnection::CInOutConnection()
{
	CurrentThreadCount = 0;
	TimeOutInit = NO_TIMEOUT;
	TimeOutCounter = TimeOutInit ;
	SECURITY_ATTRIBUTES sat;
	sat.nLength = sizeof(SECURITY_ATTRIBUTES);
	sat.lpSecurityDescriptor = NULL;
	sat.bInheritHandle = TRUE;
	InitializeCriticalSection(&timeoutGuard);
	m_IsTerminated = CreateEvent(&sat, TRUE, FALSE, NULL);
	ResetConnection();
}

CInOutConnection::~CInOutConnection()
{
	CloseHandle(m_IsTerminated);
	DeleteCriticalSection(&timeoutGuard);
}

void CInOutConnection::SetCallbackWindow(HWND window, int MessageId)
{
	callbackWindow = window;
	MsgId = MessageId;
}

void CInOutConnection::ClearCallbackWindow()
{
	callbackWindow = 0;
}

void CInOutConnection::SetCallbackFunction(void* newFunc)
{
	CallbackFunc = newFunc;
}

void CInOutConnection::ClearCallBackFunction()
{
	CallbackFunc = 0;
}

BOOL CInOutConnection::CreateThreads()
{
	CurrentThreadCount = 0;
	::_beginthread(InThreadFunc, 0, (void*)this );
	::_beginthread(OutThreadFunc, 0, (void*)this );
	::_beginthread(SyncThreadFunc, 0, (void*)this );
	::_beginthread(ServiceThreadFunc, 0, (void*)this );
	BOOL ret = CreateThreadsEx();
	if (!ret) return FALSE;
	return WaitThreadsToStart();
}

void CInOutConnection::WaitForTermination()
{
	int Count = 0;
	while(CurrentThreadCount>0 && Count<30000)
	{
		Sleep(1);
		Count+=1;
	};
}

BOOL CInOutConnection::Terminate()
{
	return (WaitForSingleObject(m_IsTerminated, 1) == WAIT_OBJECT_0);
}

void CInOutConnection::SetTerminate()
{
	SetEvent(m_IsTerminated);
}

BOOL CInOutConnection::InitInThread()
{
	AddThread();
	return TRUE;
}

BOOL CInOutConnection::InitOutThread()
{
	AddThread();
	return TRUE;
}

BOOL CInOutConnection::InitSyncThread()
{
	AddThread();
	return TRUE;
}

BOOL CInOutConnection::WaitThreadsToStart()
{
	int Count = 0;
	while(CurrentThreadCount<GetAllThreadsCount() && Count<200)
	{
		Sleep(50);
		Count+=1;
	};
	if (CurrentThreadCount<GetAllThreadsCount()) return FALSE;
	return TRUE;
}

void CInOutConnection::InThreadTerminated()
{
	RemoveThread();
}

void CInOutConnection::OutThreadTerminated()
{
	RemoveThread();
}

void CInOutConnection::SyncThreadTerminated()
{
	RemoveThread();
}

void* CInOutConnection::InternalReceiveMessage(int* Error, int* length)
{
#ifndef _DEBUG
	try{
#endif
	*Error = 0;
	int l = GetHeaderLength();
	void* buf = cioReceiveMessage(Error, &l);
	if (*Error!=0 || l!=GetHeaderLength()) 
	{
		if (buf!=NULL) delete buf;
		return NULL;
	};
	if (!IsCorrectHeader((char*)buf))
	{
		delete buf;
		return NULL;
	};	
	int size = GetMessageSizeFromHeader((char*)buf);
	l = size;
	delete buf;
	buf = cioReceiveMessage(Error, &l);
	if (*Error!=0 || l!=size) 
	{
		if (buf!=NULL) delete buf;
		return NULL;
	};

	*length = size;
	return buf;
#ifndef _DEBUG
	}catch(...){ASSERT(FALSE);return NULL;};
#endif
}

void* CInOutConnection::cioReceiveMessage(int* Error, int* length)
{
	*Error = 1;
	return NULL;
}

BOOL CInOutConnection::cioSendMessage(void* msg, int msg_size)
{
	return FALSE;
}

int CInOutConnection::GetHeaderLength()
{
	return CInOutConnection::DEFAULT_HEADER_SIZE;
}

BOOL CInOutConnection::IsCorrectHeader(char* header)
{
	if (((DWORD*)header)[0] == CInOutConnection::DEFAULT_FRAME) return TRUE;
	return FALSE;
}

int CInOutConnection::GetMessageSizeFromHeader(char* header)
{
	return ((DWORD*)header)[1];
}

void* CInOutConnection::PrepareMessageToSend(void* msg, DWORD length, DWORD& len)
{
	if (length == 0) return NULL;
	len = length+CInOutConnection::DEFAULT_HEADER_SIZE;
	LPVOID lp = (void*) new char[len];
	memcpy((char*)lp+CInOutConnection::DEFAULT_HEADER_SIZE, msg, length);
	DWORD* dw = (DWORD*)lp;
	dw[0] = CInOutConnection::DEFAULT_FRAME;
	dw[1] = length;
	delete msg;
	return lp;
}

void CInOutConnection::ProcessCurrentMessage(void* msg, DWORD length)
{

}

void CInOutConnection::ProcessMessage()
{
	if (callbackWindow!=0)
	{
		SendMessage(callbackWindow, WM_COMMAND, MsgId, (DWORD)this);
	} else
	{
		if (CallbackFunc!=NULL)
		{
			((InOutCallbackFunc*)CallbackFunc)((void*) this);
		} else 
		{
			DWORD length;
			void* msg = GetInQueue()->GetFirstMessage(length);
			if (msg!=NULL) 
			{
				ProcessCurrentMessage(msg, length);
			};
		};
	};
}

BOOL CInOutConnection::IsConnectionValid()
{
	return (CurrentThreadCount == GetAllThreadsCount());
}

void CInOutConnection::ResetConnection()
{
	ResetEvent(m_IsTerminated);
	callbackWindow = 0;
	CallbackFunc = 0;
}

void CInOutConnection::OnInThreadError()
{
}

void CInOutConnection::OnOutThreadError()
{
}

void CInOutConnection::OnSyncThreadIdle()
{	
} 

void CInOutConnection::OnInThreadIdle()
{	
}

void CInOutConnection::OnOutThreadIdle()
{	
}

void CInOutConnection::OnServiceTimer()
{
	BOOL ExitFlag = FALSE;
	EnterCriticalSection(&timeoutGuard);
	if (TimeOutCounter!= CInOutConnection::NO_TIMEOUT)
	{
		TimeOutCounter-=1;
		if (TimeOutCounter == 0)
		{
			ExitFlag = TRUE;
		};
	};
	LeaveCriticalSection(&timeoutGuard);
	if (ExitFlag) 
	{
		SetTerminate();
	};
}

void CInOutConnection::PreprocessIncomingMessage(void* message, int length)
{
	GetInQueue()->AddSingleMessage(message, length);
}

void CInOutConnection::PreprocessOutgoingMessage(void* message)
{
	
}

