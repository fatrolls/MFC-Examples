// ==========================================================================
// 							Class Implementation : COXThreadEngine
// ==========================================================================

// Source file : OXThreadEngine.cpp

// This software along with its related components, documentation and files ("The Libraries")
// is © 1994-2007 The Code Project (1612916 Ontario Limited) and use of The Libraries is
// governed by a software license agreement ("Agreement").  Copies of the Agreement are
// available at The Code Project (www.codeproject.com), as part of the package you downloaded
// to obtain this file, or directly from our office.  For a copy of the license governing
// this software, you may contact us at legalaffairs@codeproject.com, or by calling 416-849-8900.                      
                          
// //////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OXThreadEngine.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// timeout value (in msec) for the thread termination (see 'COXThreadEngine::Terminate()')
#define OXTE_TERMINATION_TIMEOUT 10000

/////////////////////////////////////////////////////////////////////////////
// COXEngineCmd
//

// Definition of static members ---------------------------------------------

DWORD COXEngineCmd::m_dwGlobalIndex = 0;


// Data members -------------------------------------------------------------
// protected:

	// COXDoneNotifier*	m_pDoneNotifier;
	// --- For optional notification after execution

	// HANDLE m_hFinishedEvent;
	// --- Used for synchronisation of synchrone commands

	// LONG	m_nRef;
	// --- Used for reference counting

// private:

	// static DWORD	m_dwGlobalIndex;
	// --- Internal cyclic counter

// Implementation of macros -------------------------------------------------
IMPLEMENT_DYNAMIC(COXEngineCmd, CObject)

// Member functions ---------------------------------------------------------

// public:

COXEngineCmd::COXEngineCmd(BOOL bSynchrone /*= TRUE*/, COXDoneNotifier* pDoneNotifier /*= NULL*/) : 
	m_hFinishedEvent(NULL),
	m_dwIndex(++m_dwGlobalIndex),
	m_pDoneNotifier(pDoneNotifier),
	m_nRef(2+(pDoneNotifier!=NULL?1:0))	// One release has to be done after PostCommand();
										// Another one will be done by the engine after the 
										// execution
										// In case of notification a release has 
{										// to be done after notification
	if (bSynchrone)	// 
		m_hFinishedEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
}

COXEngineCmd::~COXEngineCmd()
{
	if (m_hFinishedEvent)
		CloseHandle(m_hFinishedEvent);
}

void COXEngineCmd::Release()
{
	if (InterlockedDecrement(&m_nRef) == 0)
		delete this;
}

BOOL COXEngineCmd::IsSynchrone() const
{
	return (m_hFinishedEvent!=NULL);
}


/////////////////////////////////////////////////////////////////////////////
// COXThreadEngine::COXEngineCmdList

// Data members -------------------------------------------------------------

// protected:

	// HANDLE m_hMutex;
	// --- mutex for lock functionality

// Member functions ---------------------------------------------------------

// public:

COXThreadEngine::COXEngineCmdList::COXEngineCmdList() :
	m_hMutex(NULL)
// --- In : none
// --- Out : none
// --- Returns : none
// --- Effect : constructs the command list and creates the internal mutex
{
	m_hMutex = CreateMutex(NULL, FALSE, NULL);
}

COXThreadEngine::COXEngineCmdList::~COXEngineCmdList()
// --- In : none
// --- Out : none
// --- Returns : none
// --- Effect : destructs the command list and closes the mutex handle
{
	if (m_hMutex)
		CloseHandle(m_hMutex);
}

void COXThreadEngine::COXEngineCmdList::Lock()
// --- In : none
// --- Out : none
// --- Returns : none
// --- Effect : locks the list exclusively
{
	WaitForSingleObject(m_hMutex, INFINITE);
}

void COXThreadEngine::COXEngineCmdList::Unlock()
// --- In : none
// --- Out : none
// --- Returns : none
// --- Effect : unlocks the list
{
	VERIFY(ReleaseMutex(m_hMutex));
}


/////////////////////////////////////////////////////////////////////////////
// COXThreadEngineBase

// Data members -------------------------------------------------------------

// protected:

	// BOOL m_bEndThread;
	// --- Thread shall terminate during next thread event
	
	// BOOL	m_bInitialized;
	// --- If successfully initialised

	// CWinThread* m_pThread;
	// --- Thread pointer of the engines thread

	// HANDLE m_hCreatedEvent;
	// --- Event for initialisation synchronisation

	// HANDLE m_hEndEvent;
	// --- Event for termination synchronisation

	// HANDLE m_hThreadEvent;
	// --- event when a new command is posted
	
	// COXEngineCmdList m_cmdList;
	// --- the command queue of the engine



// Member functions ---------------------------------------------------------

// public:



COXThreadEngine::COXThreadEngine() :
	m_hCreatedEvent(NULL),
	m_bInitialized(FALSE),
	m_bEndThread(FALSE),
	m_hEndEvent(NULL),
	m_hThreadEvent(NULL),
	m_pThread(NULL),
	m_nTerinationTimeout(OXTE_TERMINATION_TIMEOUT)
{
	m_hCreatedEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	m_hEndEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	m_hThreadEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
}

COXThreadEngine::~COXThreadEngine()
{
	if (m_hEndEvent)
		CloseHandle(m_hEndEvent);
	if (m_hCreatedEvent)
		CloseHandle(m_hCreatedEvent);
	if (m_hThreadEvent)
		CloseHandle(m_hThreadEvent);
}

BOOL COXThreadEngine::Initialize()
{
	DWORD	dwWaitResult;

	if (IsInitialized())
	{
		TRACE0("COXThreadEngine::Initialize() -> Already initialized !!");
		ASSERT(FALSE);
		return FALSE;
	}
	m_pThread = AfxBeginThread((AFX_THREADPROC)StartThread, this);
	if (m_pThread)
	{
		while (TRUE)
		{
			dwWaitResult = ::WaitForSingleObject(&m_hCreatedEvent,INFINITE);
			//dwWaitResult = MsgWaitForMultipleObjects(1, &m_hCreatedEvent, FALSE, INFINITE, QS_ALLINPUT);
			if (dwWaitResult == (WAIT_OBJECT_0 + 1))
				// You must avoid a WM_QUIT to be send during initialization
				VERIFY(AfxGetThread()->PumpMessage());
			else
				return TRUE;
		}
	}
	return FALSE;
}

BOOL COXThreadEngine::IsInitialized()
{
	return m_bInitialized;
}

void COXThreadEngine::Terminate()
{
	DWORD	dwWaitResult;
	BOOL	bEnd = FALSE;
	BOOL	bPostQuit = FALSE;

	if (m_pThread==NULL)
		return;

	m_bEndThread = TRUE;
	SetEvent(m_hThreadEvent);

	while (!bEnd)
	{
		dwWaitResult = MsgWaitForMultipleObjects(1, &m_hEndEvent, FALSE, m_nTerinationTimeout, QS_ALLINPUT);

		if (dwWaitResult == (WAIT_OBJECT_0 + 1))
		{
			MSG msg;
			// making sure there is a msg in the queue
			// we don't want PumpMessage() to hang
			if (PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE))
				bPostQuit = (!AfxGetThread()->PumpMessage()) || bPostQuit;
		}
		else
		{
			if (m_pThread && (dwWaitResult != WAIT_OBJECT_0))
				TerminateThread(m_pThread->m_hThread, 0);
			bEnd = TRUE;
		}
    }
	if (bPostQuit)
	{
		AfxPostQuitMessage(0);
		Sleep(200); // Give the terminating thread the time to terminate
	}
	m_bEndThread = FALSE;
	m_bInitialized = FALSE;
}

void COXThreadEngine::PostCommand(COXEngineCmd* pCmd, BOOL bASAP /*= FALSE*/)
{
	m_cmdList.Lock();
	if (bASAP)
		m_cmdList.AddHead(pCmd);
	else
		m_cmdList.AddTail(pCmd);
	m_cmdList.Unlock();
	SetEvent(m_hThreadEvent);
	if (pCmd->m_hFinishedEvent)
		WaitForSingleObject(pCmd->m_hFinishedEvent, INFINITE);
}

// protected:

UINT COXThreadEngine::StartThread( LPVOID pParam )
// --- In : pParam: the engine itself (it needs to be past on as a parameter
//					because this is a static functions)
// --- Out : none
// --- Returns : always zero (indicates that the thread terminated normally)
// --- Effect : calls the Run() functions which implements a message loop
{
	((COXThreadEngine*) pParam)->Run();
	return 0;
}

void COXThreadEngine::Run()
// --- In : none
// --- Out : none
// --- Returns : none
// --- Effect : implements a loop which ends if Terminate() is called;
//				this loop reacts on every command that is added to the engines queue
{
    MSG     msg;
	HRESULT	hr;

    hr = CoInitialize(NULL);
	if (hr==S_OK)
		m_bInitialized = OnThreadCreation();
	SetEvent(m_hCreatedEvent);
    if (m_bInitialized)
    {
		DWORD dwWaitResult;

		while (!m_bEndThread)
		{
			dwWaitResult = MsgWaitForMultipleObjects(1, &m_hThreadEvent, FALSE, INFINITE, QS_ALLINPUT);
			if (dwWaitResult == (WAIT_OBJECT_0 + 1))
			{
				while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
					DispatchMessage(&msg);
			}
			else if (!m_bEndThread)
				OnThreadEvent();
    	}
		OnThreadDestruction();
		m_pThread = NULL;
		CoUninitialize();
		SetEvent(m_hEndEvent);
	}
	m_pThread = NULL;
}

BOOL COXThreadEngine::OnThreadCreation()
// --- In : none
// --- Out : none
// --- Returns : if initialisation of the engine will be successful or not
// --- Effect : is called by the engine when the thread is started 
//				overload this function if you need to do some specific
//				initialisation
{
	return TRUE;
}

void COXThreadEngine::OnThreadDestruction()
// --- In : none
// --- Out : none
// --- Returns : none
// --- Effect : is called by the engine when the thread is terminated;
//				overload this function if you need to do some specific
//				uninitialisation;
//				dont forget to call this base function on the
//				end of your overloaded version
{
	COXEngineCmd* pCmd;
	while (m_cmdList.GetCount())
	{
		pCmd = m_cmdList.RemoveHead();
		pCmd->Release(); // the one that will not be done by OnThreadEvent()
		if (pCmd->m_pDoneNotifier)
			pCmd->Release(); // the one that will not be done by the notifier
	}
}

void COXThreadEngine::OnThreadEvent()
// --- In : none
// --- Out : none
// --- Returns : none
// --- Effect : if a thread event occurs, this function is called to execute all
//				the commands in the engine queue (from head to tail)
{
	COXEngineCmd*		pCmd;
	COXDoneNotifier*	pDoneNotifier;
	HANDLE				hFinishedEvent;

	m_cmdList.Lock();
	while (!m_bEndThread && m_cmdList.GetCount())
	{
		pCmd = m_cmdList.RemoveHead();
		m_cmdList.Unlock();
		hFinishedEvent = pCmd->m_hFinishedEvent;
		pDoneNotifier = pCmd->m_pDoneNotifier;
		OnExecuteCmd(pCmd);

		if (pDoneNotifier)
			pDoneNotifier->DoneCommand(pCmd);
		if (hFinishedEvent)
			SetEvent(hFinishedEvent);
		pCmd->Release();
		m_cmdList.Lock();
	}
	m_cmdList.Unlock();
}
