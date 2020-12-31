#include "StdAfx.h"
#include "HooksClient.h"
#include <string.h>

/* 
** ****************
** * CHooksClient *
** ****************
*/

/*
** Construction & Destruction
*/

CHooksClient::CHooksClient(BOOL AutoInstall)
{
	// Initialize syncronization events
	CHooksClientThread::m_hEventHooksClientWindowCreated  = CreateEvent(NULL, TRUE, FALSE, "ClientWindowCreated");
	CHooksClientThread::m_hEventHooksClientThreadKilled  = CreateEvent(NULL, FALSE, FALSE, "ClientThreadKilled");

	// Create client thread and wait for acknowlegement
	CreateClientThread();
	// Load hooks server
	LoadHooksServer();
}

CHooksClient::~CHooksClient()
{
	// Remove all hooks
	UninstallAllHooks();
	// Destroy client thread
	DestroyClientThread();
	// Unload hooks server
	FreeHooksServer();
}

/*
** Information retrival
*/

BOOL CHooksClient::IsServerLoaded()
{
	return (m_hHooksServer != NULL);
}

/*
** Client initialization
*/

void CHooksClient::InstallWindowHook(HWND hWnd)
{
	if( (hWnd) && (::IsWindow(hWnd)) )
	{
		DWORD dwThreadID = ::GetWindowThreadProcessId(hWnd, NULL);

		if(dwThreadID)
		{
			DWORD dwGlobalHook, dwInstalledHook;

			// Check for a system hook
			if(GetGlobalHook(dwGlobalHook))
			{
				TRACE1("Global tracing is enabled. Hook was not installed for window %8.8x\n",
					hWnd);
			}
			// Check for hook installed for the thread id
			else if(m_oHandles.Lookup(dwThreadID, dwInstalledHook))
			{
				TRACE2("Hook for window %8.8x (thread %8.8x) is already installed\n", 
					hWnd, dwThreadID);
			}
			// Everything is ok, install hook
			else
			{
				InstallHookEx(dwThreadID);
			}
		}
	}
}

void CHooksClient::InstallSystemHook()
{
	int nCount = m_oHandles.GetCount();

	if(m_oHandles.IsEmpty())
	{
		// No hooks, install
		InstallHookEx(0);
	}
	else
	{
		DWORD dwGlobalHook;

		if(GetGlobalHook(dwGlobalHook))
		{
			TRACE0("Global tracing is already enabled, ignoring request\n");
		}
		else
		{
			TRACE0("Other hooks are installed, removing all hooks\n");
			UninstallAllHooks();
			InstallHookEx(0);
		}
	}
}

/*
** Client un-initialization
*/

void CHooksClient::UninstallWindowHook(HWND hWnd)
{
	if( (hWnd) && (::IsWindow(hWnd)) )
	{
		DWORD dwThreadID = ::GetWindowThreadProcessId(hWnd, NULL);

		if(dwThreadID)
		{
			UninstallHookEx(dwThreadID);
		}
		else
		{
			TRACE2("Hook for window %8.8x (thread %8.8x) is NOT installed\n", 
				hWnd, dwThreadID);
		}
	}
}

void CHooksClient::UninstallSystemHook()
{
	DWORD dwGlobalHook;

	if( (m_oHandles.GetCount() == 1) && (GetGlobalHook(dwGlobalHook)) )
	{
		// When a system hook is installed - it's the one and only
		// hook - so the count must be one and an item in the map
		// with a key 0 must exist
		UninstallHookEx(dwGlobalHook);
	}
	else
	{
		TRACE0("Global tracing is not installed, ignoring request\n");
	}
}

/*
** Client clean-up
*/

void CHooksClient::UninstallAllHooks()
{
	DWORD dwThread, dwHooks;

	for(POSITION pthrd = m_oHandles.GetStartPosition() ; pthrd != NULL ; )
	{
		m_oHandles.GetNextAssoc(pthrd, dwThread, dwHooks);

		UninstallHookEx(dwThread);
	}
}

/*
** Thread creation
*/

void CHooksClient::CreateClientThread()
{
	m_pClientThread = new CHooksClientThread(this);

	if(!m_pClientThread->CreateThread())
	{
		delete m_pClientThread;
		m_pClientThread = NULL;
		TRACE0("Unable to create client thread\n");
	}
}

/*
** Thread destruction
*/

void CHooksClient::DestroyClientThread()
{
	if(m_pClientThread)
	{
		m_pClientThread->PrepareToClose();
		delete m_pClientThread;
		WaitForSingleObject(CHooksClientThread::m_hEventHooksClientThreadKilled, INFINITE);
		m_pClientThread = NULL;
	}
}

/*
** Hook server DLL management
*/

void CHooksClient::LoadHooksServer()
{
	const char szHooksServer[] = "App8Hook.DLL";

	// Attempt to load the server
	if(m_hHooksServer = ::LoadLibrary(szHooksServer))
	{
		TRACE1("Hooks server DLL (%s) loaded\n", szHooksServer);
	}
	else
	{
		TRACE1("Unable to load hooks server %s\n", szHooksServer);
	}
}

void CHooksClient::FreeHooksServer()
{
	if(m_hHooksServer)
	{
		UninstallAllHooks();
		::FreeLibrary(m_hHooksServer);
		TRACE0("Hooks server unloaded\n");
	}
}

/*
** Hook installation helpers
*/

BOOL CHooksClient::GetGlobalHook(DWORD &dwGlobalHook)
{
	DWORD dwIndex = 0;

	return m_oHandles.Lookup(dwIndex, dwGlobalHook);
}

void CHooksClient::InstallHookEx(DWORD dwThreadID)
{
	const char szGetMsgProc[] = "ClientGetMsgProc",
			   szCallWndProc[] = "ClientCallWndProc";
	
	// Wait for acknowlegement from thread
	#ifdef _DEBUG
		// Wait for window to be created - debug version
		DWORD dwEvent = WaitForSingleObject(CHooksClientThread::m_hEventHooksClientWindowCreated, 10000);
	#else
		// Wait 10 seconds for window to be created
		DWORD dwEvent = WaitForSingleObject(CHooksClientThread::m_hEventHooksClientWindowCreated, INFINITE);
	#endif

	if( (m_hHooksServer) && (dwEvent == WAIT_OBJECT_0) )
	{
		FARPROC lpGetMsgProc, lpCallWndProc;
		HHOOK hGetMsgHook = NULL, hCallWndHook = NULL;
		
		// Load GetMessage hook function address 
		lpGetMsgProc = ::GetProcAddress(m_hHooksServer, szGetMsgProc);
		// Load CallWnd hook function address 
		lpCallWndProc = ::GetProcAddress(m_hHooksServer, szCallWndProc);
		// Install the hooks
		if(lpGetMsgProc)  // WH_GETMESSAGE
			hGetMsgHook = ::SetWindowsHookEx(WH_GETMESSAGE, (HOOKPROC) lpGetMsgProc, m_hHooksServer, dwThreadID);
		if(lpCallWndProc) // (WH_CALLWNDPROC)
			hCallWndHook = ::SetWindowsHookEx(WH_CALLWNDPROC, (HOOKPROC) lpCallWndProc, m_hHooksServer, dwThreadID);

		if( (!hGetMsgHook) || (!hCallWndHook) )
		{
			if(hGetMsgHook)
				::UnhookWindowsHookEx(hGetMsgHook);
			if(hCallWndHook)
				::UnhookWindowsHookEx(hCallWndHook);
			if(dwThreadID)
				TRACE1("Unable to install hook for thread %8.8x\n", dwThreadID);
			else
				TRACE0("Unable to install system hook\n");
		}
		else
		{
			// Add the hook into map
			m_oHandles[dwThreadID] = MAKELONG(hGetMsgHook, hCallWndHook);
			if(dwThreadID)
				TRACE1("Hook for thread %8.8x has been installed\n", dwThreadID);
			else
				TRACE0("System-wide hook has been installed\n");
		}
	}
}

void CHooksClient::UninstallHookEx(DWORD dwThreadID)
{
	DWORD dwHooks;

	if(m_oHandles.Lookup(dwThreadID, dwHooks))
	{
		// Hooks found, unhook !
		::UnhookWindowsHookEx((HHOOK) LOWORD(dwHooks)); // GetMessage
		::UnhookWindowsHookEx((HHOOK) HIWORD(dwHooks)); // CallWnd
		m_oHandles.RemoveKey(dwThreadID);
		if(dwThreadID)
			TRACE1("Hook for thread %8.8x has been removed\n", dwThreadID);
		else
			TRACE0("System-wide hook has been removed\n");
	}
}

/*
** **********************
** * CHooksClientThread *
** **********************
*/

/*
** Static members
*/

HANDLE CHooksClientThread::m_hEventHooksClientThreadKilled;
HANDLE CHooksClientThread::m_hEventHooksClientWindowCreated;

/*
** MFC Stuff
*/

IMPLEMENT_DYNCREATE(CHooksClientThread, CWinThread)

BEGIN_MESSAGE_MAP(CHooksClientThread, CWinThread)
	//{{AFX_MSG_MAP(CHooksClientThread)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/*
** Construction and Destruction
*/

CHooksClientThread::CHooksClientThread(CHooksClient *pClient)
{
	m_pClientWnd = NULL;
	SetClient(pClient);
}

CHooksClientThread::~CHooksClientThread()
{
}

/*
** Save client
*/

void CHooksClientThread::SetClient(CHooksClient *pClient)
{
	m_pClient = pClient;
	if(m_pClientWnd)
		m_pClientWnd->SetClient(pClient);
}

/*
** Prepare to close - delete client window
*/

void CHooksClientThread::PrepareToClose()
{
	if(m_pClientWnd)
	{
		m_pClientWnd->DestroyWindow();
		delete m_pClientWnd;
		m_pClientWnd = NULL;
	}
}

/*
** Initialize the thread
*/

BOOL CHooksClientThread::InitInstance()
{
	BOOL bReturn = FALSE;
	
	// Create the client window
	m_pClientWnd = new CHooksClientWnd(m_pClient);
	if(m_pClientWnd)
	{
		LPCSTR szTempClass = AfxRegisterWndClass(0);

		if(m_pClientWnd->CreateEx(0, szTempClass, HOOKWINDOWNAME, WS_OVERLAPPEDWINDOW, CRect(0, 0, 0, 0), NULL, 0))
		{
			m_pMainWnd = m_pClientWnd;
			bReturn = TRUE;
		}
		else
		{
			TRACE0("Unable to create client window\n");
		}
	}

	SetEvent(CHooksClientThread::m_hEventHooksClientWindowCreated);
	return bReturn;
}

/*
** Terminate the thread
*/

int CHooksClientThread::ExitInstance()
{
	if(m_pClient)
		m_pClient->m_pClientThread = NULL;

	if(m_pClientWnd)
	{
		delete m_pClientWnd;
		m_pClientWnd = NULL;
	}

	return CWinThread::ExitInstance();
}

/*
** Custom delete operator - mutli-threaded charged :)
*/

void CHooksClientThread::operator delete(void* p)
{
	// The exiting main application thread waits for this event before completely
	// terminating in order to avoid a false memory leak detection. 

	SetEvent(m_hEventHooksClientThreadKilled);

	CWinThread::operator delete(p);
}

/*
** *******************
** * CHooksClientWnd *
** *******************
*/

/*
** MFC Stuff
*/

BEGIN_MESSAGE_MAP(CHooksClientWnd, CWnd)
	//{{AFX_MSG_MAP(CHooksClientWnd)
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_COPYDATA, OnFixedCopyData)
END_MESSAGE_MAP()

/*
** Construction and Destruction
*/

CHooksClientWnd::CHooksClientWnd(CHooksClient *pClient)
{
	SetClient(pClient);
}

CHooksClientWnd::~CHooksClientWnd()
{
}

/*
** Window pre-creation
*/

BOOL CHooksClientWnd::PreCreateWindow(CREATESTRUCT& cs) 
{
	WNDCLASS wndcls;
	BOOL bResult = CWnd::PreCreateWindow(cs);
	HINSTANCE hInst = AfxGetInstanceHandle();

	// See if the class already exists
	if (!::GetClassInfo(hInst, HOOKWINDOWCLASS, &wndcls))
	{
		// Get default stuff
		::GetClassInfo(hInst, cs.lpszClass, &wndcls);
		wndcls.style &= ~(CS_HREDRAW|CS_VREDRAW);
		// Register a new class
		wndcls.lpszClassName = HOOKWINDOWCLASS;
		if (!AfxRegisterClass(&wndcls))
			AfxThrowResourceException();
	}
	
	// Set new class name
	cs.lpszClass = HOOKWINDOWCLASS;
	
	return bResult;
}

/*
** Save client
*/

void CHooksClientWnd::SetClient(CHooksClient *pClient)
{
	m_pClient = pClient;
}

/*
** Handler for WM_COPYDATA - __DON'T__ use MFC OnCopyData since MFC
** Uses lParam both for the CWnd * parameter and for the 
** COPYDATASTRUCT * parameter.
** *** This is of course a bug in MFC.
*/

LRESULT CHooksClientWnd::OnFixedCopyData(WPARAM wParam, LPARAM lParam)
{
	CWnd* pWnd = CWnd::FromHandle((HWND) wParam);
	COPYDATASTRUCT* pCopyDataStruct = (COPYDATASTRUCT*) lParam;

	if(pCopyDataStruct && m_pClient && pWnd && ::IsWindow(pWnd->GetSafeHwnd()))
	{
		HWND hwnd = pWnd->m_hWnd;
		UINT nMessage = pCopyDataStruct->dwData;
		WPARAM wParam = ((PCLIENTMSGDATA) pCopyDataStruct->lpData)->wParam;
		LPARAM lParam = ((PCLIENTMSGDATA) pCopyDataStruct->lpData)->lParam;

		m_pClient->ProcessHookMessage(hwnd, nMessage, wParam, lParam);
	}

	return TRUE;
}

