/////////////////////////////////////////////////////////////////////
// Class Creator Version 2.0.000 Copyrigth (C) Poul A. Costinsky 1994
///////////////////////////////////////////////////////////////////
// Implementation File RawSocketServerWorker.cpp
// class CWizRawSocketServerWorker
//
// 16/07/1996 17:53                             Author: Poul
///////////////////////////////////////////////////////////////////
 

#include "stdafx.h"

#include "RawSocketServerWorker.h"


#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif

// Events to interrupt blocking socket functions.
__declspec( thread ) static const int HOOK_CANCEL_EVENTS = 2;
__declspec( thread ) static HANDLE sh_HookCanselEvents[HOOK_CANCEL_EVENTS] 
	= { NULL, NULL };
__declspec( thread ) static int nHookEventsInstalled = 0;

///////////////////////////////////////////////////////////////////
//*****************************************************************
inline void ThrowIfNull(void* p)
{
	if (p == NULL)
		AfxThrowMemoryException();
}
//*****************************************************************
// Function called from Windows Sockets blocking hook function
inline BOOL TestCancelEvents (DWORD TimeOut = 0)
{
#ifdef _DEBUG
	ASSERT(nHookEventsInstalled <= HOOK_CANCEL_EVENTS);
	for(INDEX i = 0; i < nHookEventsInstalled; i++)
		ASSERT(sh_HookCanselEvents[i] != NULL);
#endif
	// Tests events - if one signaled, should cancel blocking function.
	return (::WaitForMultipleObjects (nHookEventsInstalled, sh_HookCanselEvents, FALSE, TimeOut) != WAIT_TIMEOUT);
}
//*****************************************************************
// Windows Sockets blocking hook function
BOOL WINAPI BlockingHook(void) 
{
	// As simple as...
	if (::TestCancelEvents(0))
		WSACancelBlockingCall();
	return 0;
}
//*****************************************************************
// Function installes blocking hook handler
inline BOOL SetHook()
{
	static BOOL bInstalled = FALSE;
	// If not installed yet
	if (!bInstalled)
		{
		// Try to install hook even if some
		// blocking Windows Sockets operation is in progress.
		while (::WSASetBlockingHook(BlockingHook) == NULL)
			{
			if (::WSAGetLastError() != WSAEINPROGRESS)
				{
				return FALSE;
				}
			if(::TestCancelEvents(100))
				return FALSE;
			}
		bInstalled = TRUE;
		}
	return TRUE;
}

///////////////////////////////////////////////////////////////////
// class CWizRawSocketListener
///////////////////////////////////////////////////////////////////
//**********************************************************//
// Default Constructor										//
CWizRawSocketListener::CWizRawSocketListener(int nPort)     //
	: m_pListenSocket (NULL),								//
	  m_nPort         (nPort)								//
{															//
}															//
//**********************************************************//
// Destructor												//
CWizRawSocketListener::~CWizRawSocketListener()				//
{															//
	if (m_pListenSocket != NULL)							//
		{													//
		ASSERT(0);											//
		delete m_pListenSocket;								//
		}													//
}															//
//**********************************************************//
// Method called from dispath thread.
void CWizRawSocketListener::Prepare ()
{
	// Maybe install hook
	if(!SetHook())
		throw CWizRawSocketListener::XCannotSetHook();
	ASSERT(nHookEventsInstalled == 0);
	// Create listening socket
	if (m_pListenSocket != NULL)
		{
		ASSERT(0);
		delete m_pListenSocket;
		}
	m_pListenSocket = new CWizSyncSocket (m_nPort);
	ThrowIfNull (m_pListenSocket);
	ASSERT(nHookEventsInstalled == 0);
#ifdef _DEBUG
	TCHAR buff[100];
	unsigned int nP;
	VERIFY(m_pListenSocket->GetHostName (buff,100,nP));
	TRACE(_T("Listening at %s:%d\n"), buff, nP);
#endif
}
//*****************************************************************
// Method called from dispath thread.
void CWizRawSocketListener::CleanUp()
{
	// close and destroy listening socket
	delete m_pListenSocket;
	m_pListenSocket = NULL;
}

//*****************************************************************
struct EventInstall
	{
	EventInstall (HANDLE h, int &n)
		: m_n (n)
		{
		ASSERT(nHookEventsInstalled <= m_n);
		if (nHookEventsInstalled > m_n)
			throw CWizRawSocketListener::XCannotSetHookEvent();
		sh_HookCanselEvents [m_n] = h;
		nHookEventsInstalled = m_n + 1;
		n++;
		}
	~EventInstall ()
		{
		ASSERT(nHookEventsInstalled == m_n + 1);
		sh_HookCanselEvents [m_n] = NULL;
		nHookEventsInstalled = m_n;
		}
	int m_n;
	};
//*****************************************************************
// Method called from dispath thread.
BOOL CWizRawSocketListener::WaitForData (HANDLE hShutDownEvent)
{
TRACE(_T("Wait for data thread %d\n"),AfxGetThread()->m_hThread);

	m_hAcceptedSocket = INVALID_SOCKET;
	// Install shutdown event.
	int n = 0;
	EventInstall ei (hShutDownEvent, n);
	// Maybe set hook.
	if(!SetHook())
		throw CWizRawSocketListener::XCannotSetHook();
	// Accept pending connections or wait.
	while (1)
		{
		// Get accepted socket.
		SOCKET h = m_pListenSocket->Accept();
		// Shutdown?
		if (::WaitForSingleObject(hShutDownEvent,0) != WAIT_TIMEOUT)
			return FALSE;
		// If it's connected client, go to serve it.
		if (h != INVALID_SOCKET)
			{
			m_hAcceptedSocket = h;
			return TRUE;
			}
		} // while 1
	return TRUE;
}
//*****************************************************************
// Method called from dispath thread.
BOOL CWizRawSocketListener::TreatData   (HANDLE hShutDownEvent, HANDLE hDataTakenEvent)
{
TRACE(_T("Treat data thread %d\n"),AfxGetThread()->m_hThread);

	int n = 0;
	// Install shutdown event.
	EventInstall ei (hShutDownEvent,n);
	// Create client side socket to communicate with client.
	CWizReadWriteSocket clientSide (m_hAcceptedSocket);
	// Signal dispather to continue waiting.
	::SetEvent(hDataTakenEvent);
	// Maybe set hook.
	if(!SetHook())
		throw CWizRawSocketListener::XCannotSetHook();

#ifdef _DEBUG
	TCHAR buff[100];
	unsigned int nP = 0;
	clientSide.GetPeerName (buff,100,nP);
	TRACE(_T("Connected to %s:%d\n"), buff, nP);
#endif

	while(1)
		{
		// Shutdown?
		if (::WaitForSingleObject(hShutDownEvent, 0) == WAIT_OBJECT_0)
			return FALSE;
		// Exchange with client. 
		if (!ReadWrite(clientSide))
			break;
		}
	return TRUE;
}
//*****************************************************************
