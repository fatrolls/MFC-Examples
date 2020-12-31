#include "stdafx.h"
#include "messageq.h"

// CMessageQueue class implementation ********************************

CMessageQueue::CMessageQueue()
{
	InitializeCriticalSection(&UsageFlag);
	//create event indicator event
	 SECURITY_ATTRIBUTES sat;
	 sat.nLength = sizeof(SECURITY_ATTRIBUTES);
	 sat.lpSecurityDescriptor = NULL;
	 sat.bInheritHandle = TRUE;
	 QueueFull = CreateEvent(&sat, TRUE, FALSE, NULL);
}

CMessageQueue::~CMessageQueue()
{
	if (MsgQueue.size()!=0)
		RemoveAllMessages();
	DeleteCriticalSection(&UsageFlag);
	CloseHandle(QueueFull);
}

void CMessageQueue::BlockQueue()
{
	EnterCriticalSection(&UsageFlag);
}

void CMessageQueue::UnBlockQueue()
{
	LeaveCriticalSection(&UsageFlag);
}

unsigned long CMessageQueue::AddMessage(void* Msg, DWORD length)
{
	SSingleMessage ssm;
	ssm.message = Msg;
	ssm.length = length;
	unsigned long l = GetMsgCount();
	MsgQueue.push_back(ssm);
	SetQueueFlag();
	return l;
}

unsigned long CMessageQueue::InsertMessage(void* Msg, DWORD length, unsigned long pos)
{
	SSingleMessage ssm;
	ssm.message = Msg;
	ssm.length = length;
	MsgQueue.insert(MsgQueue.begin()+pos, ssm);
	SetQueueFlag();
	return pos;
}

unsigned long CMessageQueue::AddSingleMessage(void* Msg, DWORD length)
{
	BlockQueue();
	SSingleMessage ssm;
	ssm.message = Msg;
	ssm.length = length;
	unsigned long l = GetMsgCount();
	MsgQueue.push_back(ssm);
	SetQueueFlag();
	UnBlockQueue();
	return l;
}

void* CMessageQueue::GetMessage(unsigned long Num, DWORD& length)
{
	LPVOID lp;
	lp = PeekMessage(Num, length);
	if (lp!=NULL) MsgQueue.erase(MsgQueue.begin()+Num);
	SetQueueFlag();
	return lp;
}

void* CMessageQueue::PeekMessage(unsigned long Num, DWORD& length)
{
	LPVOID lp;
	if (!IsMsgValid(Num)) return NULL;
	SSingleMessage ssm = MsgQueue.at(Num);
	lp = ssm.message;
	length = ssm.length;
	return lp;
}

unsigned long CMessageQueue::GetMsgCount()
{
	int l = MsgQueue.size();
	return l;
}

void CMessageQueue::DeleteAllMessages()
{
	MsgQueue.clear();
	SetQueueFlag();
}

void CMessageQueue::RemoveAllMessages()
{
	DWORD length;
	for (unsigned long i=0; i<GetMsgCount(); i++)
	{
		LPVOID lp = PeekMessage(i, length);
		if (lp!=NULL) delete lp;
	};
	MsgQueue.clear();
	SetQueueFlag();
}

void CMessageQueue::DeleteMessage(unsigned long Num)
{
	if (!IsMsgValid(Num)) return;
	MsgQueue.erase(MsgQueue.begin() + Num);
	SetQueueFlag();
}

void CMessageQueue::RemoveMessage(unsigned long Num)
{
	DWORD length;
	if (!IsMsgValid(Num)) return;
	delete GetMessage(Num, length);
	SetQueueFlag();
}

BOOL CMessageQueue::IsMsgValid(unsigned long Num)
{
	if (Num<0 || Num>=GetMsgCount()) return FALSE;
	return TRUE;
}

void CMessageQueue::SetQueueFlag()
{
	if (GetMsgCount()!=0) SetEvent(QueueFull);
	 else ResetEvent(QueueFull);
}

void* CMessageQueue::GetFirstMessage(DWORD& length)
{
	BlockQueue();
	void* msg = GetMessage(0, length);
	UnBlockQueue();
	return msg;
}

