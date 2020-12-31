// ==========================================================================
//				Class Implementation : COXCommunicator
// ==========================================================================

// Source file : OXCommunicator.cpp

// This software along with its related components, documentation and files ("The Libraries")
// is © 1994-2007 The Code Project (1612916 Ontario Limited) and use of The Libraries is
// governed by a software license agreement ("Agreement").  Copies of the Agreement are
// available at The Code Project (www.codeproject.com), as part of the package you downloaded
// to obtain this file, or directly from our office.  For a copy of the license governing
// this software, you may contact us at legalaffairs@codeproject.com, or by calling 416-849-8900.                      
			  
// //////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OXCommunicator.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC(COXCommunicator, CSocket)

/////////////////////////////////////////////////////////////////////////////
// Definition of static members
HCLIENT_COMMUNICATOR COXCommunicator::m_nLastUsedHandle = 0;
CMap<UINT, UINT, COXCommunicator*, COXCommunicator*> COXCommunicator::m_TimerToCommunicator;

// Data members -------------------------------------------------------------
// protected:
	// COXCommunicator* m_pMasterCommunicator;
	// --- The master communicator to which events should be routed
	//     Null if this communicator does not have a master

	// CMap<COXCommunicator*, COXCommunicator*, HCLIENT_COMMUNICATOR, HCLIENT_COMMUNICATOR> m_connections;
	// --- Map from the client communicator objects to their handle

	// CSocketFile* m_pFile;
	// --- Socket file used for communication.  This will be constructed when the 
	//     communication is executed for the first time

	// CArchive* m_pInStream;
	// CArchive* m_pOutStream;
	// --- In (load) and out (store) stream used on top of m_pFile

	// HWND m_hCancelWindow;
	// --- Handle of the window which messages will be dispatch during a blocking call

	// UINT m_nTimeOut;
	// --- Time out value of a blocking call

	// UINT m_nTimerID;
	// --- ID of the timer used to notify of a time out

// private:
	
// Member functions ---------------------------------------------------------
// public:
COXCommunicator::COXCommunicator(UINT nStreamBufferSize /* = 4096 */, 
	COXCommunicator* pMasterCommunicator /* = NULL */)
	:
	m_nStreamBufferSize(nStreamBufferSize),
	m_pMasterCommunicator(pMasterCommunicator),
	m_pFile(NULL),
	m_pInStream(NULL),
	m_pOutStream(NULL),
	m_nTimerID(0),
	m_hCancelWindow(NULL),
	m_nTimeOut(0)
	{
	ASSERT_VALID(this);
	}

HCLIENT_COMMUNICATOR COXCommunicator::GetClientHandle(COXCommunicator* pClientCommunicator)
	{
	HCLIENT_COMMUNICATOR hClientCommunicator;
	if (m_connections.Lookup(pClientCommunicator, hClientCommunicator))
		return hClientCommunicator;
	else
		{
		TRACE(_T("COXCommunicator::GetClientHandle : Client communicator not found, returning 0\n"));
		return (HCLIENT_COMMUNICATOR)0;
		}
	}

COXCommunicator* COXCommunicator::GetClientCommunicator(HCLIENT_COMMUNICATOR hClient)
	{
	COXCommunicator* pCommunicator;
	HCLIENT_COMMUNICATOR hClientCommunicator;
	POSITION pos;
	pos = m_connections.GetStartPosition();
	while (pos != NULL)
		{
		m_connections.GetNextAssoc(pos, pCommunicator, hClientCommunicator);
		if (hClient == hClientCommunicator)
			return pCommunicator;
		}
	TRACE(_T("COXCommunicator::GetClientCommunicator : Handle not found, returning NULL\n"));
	return  NULL;
	}

void COXCommunicator::Initialize(UINT uTimeOut /* = 10000 */, CWnd* pCancelWnd /* = NULL */)
	{
	SetTimeOut(uTimeOut);
	SetCancelWindow(pCancelWnd);
	}

void COXCommunicator::SetCancelWindow(CWnd* pWnd)
	{
	m_hCancelWindow = pWnd->GetSafeHwnd();
	}

void COXCommunicator::SetTimeOut(UINT uTimeOut)
	{
	m_nTimeOut = uTimeOut;
	}

BOOL COXCommunicator::IsOpen()
	{
	return (m_hSocket != INVALID_SOCKET);
	}

BOOL COXCommunicator::IsListening()
	{
	BOOL bListening;
	int nSize = sizeof(bListening);
	if (GetSockOpt(SO_ACCEPTCONN, &bListening, &nSize))
		return bListening;
	else
		{
		TRACE(_T("COXCommunicator::IsListening : Could not get the listening state\n"));
		return FALSE;
		}
	}

BOOL COXCommunicator::IsBlocking()
	{
	return (m_pbBlocking != NULL) && *m_pbBlocking;
	}

BOOL COXCommunicator::AreAnyBlocking()
	{
	BOOL bBlocking;
	// Get the blocking state of this communicator
	bBlocking = IsBlocking();

	// Get the blocking state of all clients
	COXCommunicator* pCommunicator;
	HCLIENT_COMMUNICATOR hDummy;
	POSITION pos;
	pos = m_connections.GetStartPosition();
	while (!bBlocking && (pos != NULL))
		{
		m_connections.GetNextAssoc(pos, pCommunicator, hDummy);
		bBlocking = pCommunicator->IsBlocking();
		}

	return bBlocking;
	}

void COXCommunicator::CancelAllBlockingCalls()
	{
	// Cancel blocking call of this communicator
	CancelBlockingCall();

	// Cancel blocking call of all clients
	COXCommunicator* pCommunicator;
	HCLIENT_COMMUNICATOR hDummy;
	POSITION pos;
	pos = m_connections.GetStartPosition();
	while (pos != NULL)
		{
		m_connections.GetNextAssoc(pos, pCommunicator, hDummy);
		pCommunicator->CancelBlockingCall();
		}
	}

DWORD COXCommunicator::GetMaxReadable()
	{
	DWORD nNumberReadable;
	if (IOCtl(FIONREAD, &nNumberReadable))
		return nNumberReadable;
	else
		{
		TRACE(_T("COXCommunicator::GetMaxReadable : Function IOCtl() failed, returning 0\n"));
		return 0;
		}
	}

CArchive* COXCommunicator::GetInStream()
	{
	if (m_pFile == NULL)
		m_pFile = new CSocketFile(this);
	if (m_pInStream == NULL)
		m_pInStream = new CArchive(m_pFile,CArchive::load, m_nStreamBufferSize);
	return m_pInStream;
	}

CArchive* COXCommunicator::GetOutStream()
	{
	if (m_pFile == NULL)
		m_pFile = new CSocketFile(this);
	if (m_pOutStream == NULL)
		m_pOutStream = new CArchive(m_pFile,CArchive::store, m_nStreamBufferSize);
	return m_pOutStream;
	}


void COXCommunicator::OnClientCreate(HCLIENT_COMMUNICATOR /* hClient */, COXCommunicator* /* pClientCommunicator */)
	{
	// Do nothing by default
	}

void COXCommunicator::OnClientReceive(HCLIENT_COMMUNICATOR /* hClient */, COXCommunicator* /* pClientCommunicator */, DWORD /* nSize */, int /* nErrorCode */)
	{
	// Do nothing by default
	}

void COXCommunicator::OnClientClose(HCLIENT_COMMUNICATOR /* hClient */, COXCommunicator* /* pClientCommunicator */, int /* nErrorCode */)
	{
	// Do nothing by default
	}

void COXCommunicator::OnClientDestroy(HCLIENT_COMMUNICATOR /* hClient */, COXCommunicator* /* pClientCommunicator */)
	{
	// Do nothing by default
	}

void COXCommunicator::OnServerReceive(DWORD /* nSize */, int /* nErrorCode */)
	{
	// Do nothing by default
	}

void COXCommunicator::OnServerClose(int /* nErrorCode */)
	{
	// Do nothing by default
	}

BOOL COXCommunicator::OnMessagePending()
	{
	// NOTE : When the function returns 
	//	TRUE : Allow user-interface updates (pThread->OnIdle(-1);)
	//	FALSE : No work to do -- allow CPU to sleep (WaitMessage();)

	MSG msg;
	// Check for messages for the cancel window and 
	// timer message and WM_QUIT
	if( ((m_hCancelWindow != NULL) && ::PeekMessage(&msg, m_hCancelWindow, NULL, NULL, PM_REMOVE)) ||
	    ::PeekMessage(&msg, NULL, WM_TIMER, WM_TIMER, PM_REMOVE) ||
	    ::PeekMessage(&msg, NULL, WM_QUIT, WM_QUIT, PM_REMOVE) )
		{
		// Abort loop on WM_QUIT
		if (msg.message == WM_QUIT)
			{
			// ... Cancel the current blocking call
			TRACE(_T("COXCommunicator::OnMessagePending : WM_QUIT detected, reposting"));
			CancelBlockingCall();
			AfxPostQuitMessage(0);
			// ... No need for idle time processing
			return FALSE;  
			}
		// Pump message			
		if (!AfxGetThread()->PreTranslateMessage(&msg))
			{
			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
			}
		// ... No need for idle time processing
		return FALSE;  
		};
	// Call base class implementation (will process WM_PAINT)
	return CSocket::OnMessagePending();
	}

BOOL COXCommunicator::Accept(CAsyncSocket& rConnectedSocket,
		SOCKADDR* lpSockAddr /* = NULL */, int* lpSockAddrLen /* = NULL */)
	{
	BOOL bRet;
	// ... Start a new timer if necessary
	CreateTimer();
	bRet = CSocket::Accept(rConnectedSocket, lpSockAddr, lpSockAddrLen);
	CloseTimer();
	return bRet;
	}

int COXCommunicator::Receive(void* lpBuf, int nBufLen, int nFlags /* = 0 */)
	{
	int nRet;
	// ... Start a new timer if necessary
	CreateTimer();
	nRet = CSocket::Receive(lpBuf, nBufLen, nFlags);
	CloseTimer();
	return nRet;
	}

int COXCommunicator::Send(const void* lpBuf, int nBufLen, int nFlags /* = 0 */)
	{
	int nRet;
	// ... Start a new timer if necessary
	CreateTimer();
	nRet = CSocket::Send(lpBuf, nBufLen, nFlags);
	CloseTimer();
	return nRet;
	}

void COXCommunicator::Close()
	{
	// First close all the client connectiosn
	COXCommunicator* pCommunicator;
	HCLIENT_COMMUNICATOR hClientCommunicator;
	POSITION pos;
	pos = m_connections.GetStartPosition();
	while (pos != NULL)
		{
		m_connections.GetNextAssoc(pos, pCommunicator, hClientCommunicator);
		pCommunicator->Close();
		OnClientDestroy(hClientCommunicator, pCommunicator);
		delete pCommunicator;
		}
	m_connections.RemoveAll();

	// ... Start a new timer if necessary
	CreateTimer();
	CSocket::Close();
	CloseTimer();
	}

#ifdef _DEBUG
void COXCommunicator::AssertValid() const
	{
	CSocket::AssertValid();
	}

void COXCommunicator::Dump(CDumpContext& dc) const
	{
	CSocket::Dump(dc);
	}
#endif //_DEBUG

COXCommunicator::~COXCommunicator()
	{
	COXCommunicator* pCommunicator;
	HCLIENT_COMMUNICATOR hClientCommunicator;
	POSITION pos;
	pos = m_connections.GetStartPosition();
	while (pos != NULL)
		{
		m_connections.GetNextAssoc(pos, pCommunicator, hClientCommunicator);
		OnClientDestroy(hClientCommunicator, pCommunicator);
		delete pCommunicator;
		}
	m_connections.RemoveAll();

	// Clean everything up
	delete m_pOutStream;
	delete m_pInStream;
	delete m_pFile;

	// If we still have a timer running, stop it now
	if (m_nTimerID != 0)
		StopTimer(m_nTimerID);
	}

// protected:
void COXCommunicator::OnAccept(int nErrorCode)
	// --- In  : nErrorCode : The most recent error code of the communicator
	// --- Out : 
	// --- Returns : 
	// --- Effect : Creates a new client socket and accepts the call
	{
	CSocket::OnAccept(nErrorCode);

	COXCommunicator* pCommunicator = new COXCommunicator(m_nStreamBufferSize, this);

	if (Accept(*pCommunicator))
		{
		// Inherit timeout and cancel window from parent
		pCommunicator->Initialize(m_nTimeOut, CWnd::FromHandle(m_hCancelWindow));
		m_connections.SetAt(pCommunicator, ++m_nLastUsedHandle);
		OnClientCreate(m_nLastUsedHandle, pCommunicator);
		}
	else
		delete pCommunicator;
	}

void COXCommunicator::OnReceive(int nErrorCode)
	// --- In  : nErrorCode : The most recent error code of the communicator
	// --- Out : 
	// --- Returns : 
	// --- Effect : Notifies the master communicator or calls the notification function
	{
	CSocket::OnReceive(nErrorCode);
	if (m_pMasterCommunicator != NULL)
		m_pMasterCommunicator->OnNotifyReceive(this, GetMaxReadable(), nErrorCode);
	else
		OnServerReceive(GetMaxReadable(), nErrorCode);
	}

void COXCommunicator::OnClose(int nErrorCode)
	// --- In  : nErrorCode : The most recent error code of the communicator
	// --- Out : 
	// --- Returns : 
	// --- Effect : Notifies the master communicator or calls the notification function
	{
	CSocket::OnClose(nErrorCode);
	if (m_pMasterCommunicator != NULL)
		m_pMasterCommunicator->OnNotifyClose(this, nErrorCode);
	else
		OnServerClose(nErrorCode);
	// The other connection has closed its socket, we close ours as well
	Close();
	}

void COXCommunicator::OnNotifyReceive(COXCommunicator* pClientCommunicator, DWORD nSize, int nErrorCode)
	// --- In  : pClientCommunicator : The client communicator from which the notification originates
	//			 nErrorCode : The most recent error code of the communicator
	// --- Out : 
	// --- Returns : 
	// --- Effect : Handles a notification of a client communicatorNotifies the master communicator or calls the notification function
	{
	HCLIENT_COMMUNICATOR hClientCommunicator;
	VERIFY(m_connections.Lookup(pClientCommunicator, hClientCommunicator));
	OnClientReceive(hClientCommunicator, pClientCommunicator, nSize, nErrorCode);
	}

void COXCommunicator::OnNotifyClose(COXCommunicator* pClientCommunicator, int nErrorCode)
	// --- In  : pClientCommunicator : The client communicator from which the notification originates
	//			 nErrorCode : The most recent error code of the communicator
	// --- Out : 
	// --- Returns : 
	// --- Effect : Handles a notification of a client communicatorNotifies the master communicator or calls the notification function
	{
	HCLIENT_COMMUNICATOR hClientCommunicator;
	VERIFY(m_connections.Lookup(pClientCommunicator, hClientCommunicator));
	OnClientClose(hClientCommunicator, pClientCommunicator, nErrorCode);
	}

void COXCommunicator::OnNotifyKill(COXCommunicator* pClientCommunicator, int /* nErrorCode */)
	// --- In  : pClientCommunicator : The client communicator from which the notification originates
	//			 nErrorCode : The most recent error code of the communicator
	// --- Out : 
	// --- Returns : 
	// --- Effect : Handles a notification of a client communicatorNotifies the master communicator or calls the notification function
	{
	HCLIENT_COMMUNICATOR hClientCommunicator;
	VERIFY(m_connections.Lookup(pClientCommunicator, hClientCommunicator));
	OnClientDestroy(hClientCommunicator, pClientCommunicator);
	// Delete client connection (has already been closed)
	ASSERT(pClientCommunicator->IsOpen());
	m_connections.RemoveKey(pClientCommunicator);
	delete pClientCommunicator;
	}

void COXCommunicator::CreateTimer()
	// --- In  : 
	// --- Out : 
	// --- Returns : 
	// --- Effect : Starts a new timer and stores the timer id
	{
	// ... Start new timer
	ASSERT(m_nTimerID == 0);
	if (m_nTimeOut != 0)
		m_nTimerID = StartTimer(this, m_nTimeOut);
	}

void COXCommunicator::CloseTimer()
	// --- In  : 
	// --- Out : 
	// --- Returns : 
	// --- Effect : Closes the started timer (if any)
	{
	// ... Stop previous timer if still running
	if (m_nTimerID != 0)
		StopTimer(m_nTimerID);
	m_nTimerID = 0;
	}

UINT COXCommunicator::StartTimer(COXCommunicator* pCommunicator, UINT nTimeOut)
	// --- In  : pCommunicator : The communicator that requests a timer
	//			 nTimeOut : The time out in milli seconds
	// --- Out : 
	// --- Returns : The timer id of the started timer
	// --- Effect : Starts a new timer and registers the specified communicator
	{
	ASSERT(nTimeOut != 0);
	// ... Should not yet have a timer
	ASSERT(pCommunicator->m_nTimerID == 0);

	UINT nTimerID;
	// ... Start timer
	nTimerID = ::SetTimer(NULL, 0, nTimeOut, TimerProc);
	if (nTimerID == 0)
		AfxThrowResourceException();
	// ... Store mapping from timer ID to object
	m_TimerToCommunicator.SetAt(nTimerID, pCommunicator);
	return nTimerID;
	}

void COXCommunicator::StopTimer(UINT nTimerID)
	// --- In  : nTimerID
	// --- Out : 
	// --- Returns : 
	// --- Effect : Stops the specified timer
	{
	// ... Remove mapping from timer ID to object
	m_TimerToCommunicator.RemoveKey(nTimerID);
	// ... Stop timer
	::KillTimer(NULL, nTimerID);
	}

VOID CALLBACK COXCommunicator::TimerProc(HWND /* hWnd */, UINT /* nMsg */, UINT nTimerID, DWORD /* dwTime */)
	// --- In  : hWnd :
	//			 nMsg : 
	//			 nTimerID : 
	//			 dwTime)
	// --- Out : 
	// --- Returns : 
	// --- Effect : Function that handles a timed out timer
	//				It will cancel the blocking call of the associated communicator
{
	ASSERT(nTimerID != 0);
	// Warn object that started the timer
	COXCommunicator* pCommunicator;
	if (m_TimerToCommunicator.Lookup(nTimerID, pCommunicator))
	{
		TRACE(_T("COXCommunicator::TimerProc : Time out reached, cancelling blocking call ...\n"));
		pCommunicator->CancelBlockingCall();
		pCommunicator->m_nTimerID = 0;
	}
	// Stop the timer
	StopTimer(nTimerID);
}

BOOL COXCommunicator::ConnectHelper(const SOCKADDR* lpSockAddr, int nSockAddrLen)
	// Same as base class but with a timer
	{
	BOOL bRet;
	// ... Start a new timer if necessary
	CreateTimer();
	bRet = CSocket::ConnectHelper(lpSockAddr, nSockAddrLen);
	CloseTimer();
	return bRet;
	}

int COXCommunicator::ReceiveFromHelper(void* lpBuf, int nBufLen,
		SOCKADDR* lpSockAddr, int* lpSockAddrLen, int nFlags)
	// Same as base class but with a timer
	{
	int nRet;
	// ... Start a new timer if necessary
	CreateTimer();
	nRet = CSocket::ReceiveFromHelper(lpBuf, nBufLen, lpSockAddr, lpSockAddrLen, nFlags);
	CloseTimer();
	return nRet;
	}

int COXCommunicator::SendToHelper(const void* lpBuf, int nBufLen,
		const SOCKADDR* lpSockAddr, int nSockAddrLen, int nFlags)
	// Same as base class but with a timer
	{
	int nRet;
	// ... Start a new timer if necessary
	CreateTimer();
	nRet = CSocket::SendToHelper(lpBuf, nBufLen, lpSockAddr, nSockAddrLen, nFlags);
	CloseTimer();
	return nRet;
	}

// private:

// ==========================================================================
