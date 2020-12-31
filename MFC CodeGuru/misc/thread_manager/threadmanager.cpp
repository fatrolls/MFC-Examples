#include "StdAfx.h"
//#include <conio.h>
#include <process.h>
#include <afxmt.h>		// used for the Critical section stuff
#include "ThreadManager.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNAMIC( CThreadManager, CObject )

//////////////////////////////////////////////////////////////////////////////
// HISTROY
//////////////////////////////////////////////////////////////////////////////
//
// 1997-09-11	2.10 Removed the functionality for a global pointers
// 1997-09-08	2.01 Call Closehandles
// 1997-09-11	2.00 Make a call to the Stop to force a clear up
// 1997-05-23	1.00 Development Started
//
//
//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////
// Helper Declarations for this module
UINT APIPRIVATE ThreadCareTakerFunction( PVOID pvThreadData );
//////////////////////////////////////////////////////////////////////////////
class CHandle : public CObject
{ 
	DECLARE_DYNAMIC( CHandle )
public: 
	HANDLE m_ThreadHandle; 
};

IMPLEMENT_DYNAMIC( CHandle, CObject )

//////////////////////////////////////////////////////////////////////////////
class CThreadCareTaker : public CObject
{
DECLARE_DYNAMIC( CThreadCareTaker )
public:
	CThreadCareTaker();
	~CThreadCareTaker();
	CBOOL IsValid();
	void AddHandle( CONST HANDLE cHandle );
	void StopThreadCareTaker();
	void CloseThreadHandles();
	static CThreadCareTaker& GetCThreadCareTaker();

	CObList	m_ObList;
	HANDLE m_Handle;
	CCriticalSection m_ThreadCriticalSection;
	CEvent m_AddEvent;
	BOOL m_bKeepGoing;
};

IMPLEMENT_DYNAMIC( CThreadCareTaker, CObject )
//////////////////////////////////////////////////////////////////////////////
// Global Declarations

//////////////////////////////////////////////////////////////////////////////
// StopThreadManager
// 1997-09-11	Removed the functionality from this call
// 1997-09-08	Call Closehandles
//
void StopThreadManager( CDWORD cdwTimeToWait/*=INFINITE*/ )
{ 
	UNREFERENCED_PARAMETER( cdwTimeToWait );
	// Just give it enough time to perform normal tidy up
	Sleep( 510 );
}		// End StopThreadManager


//////////////////////////////////////////////////////////////////////////////
// GetCThreadCareTaker
// 1997-09-11	Function created
// This static object will be destroyed when the main(WinMain) loses functional
// focus
//
CThreadCareTaker & CThreadCareTaker::GetCThreadCareTaker()
{
	static CThreadCareTaker __CThreadCareTaker;
	return( __CThreadCareTaker );
}		// End CThreadCareTaker::GetCThreadCareTaker
//////////////////////////////////////////////////////////////////////////////
// CThreadCareTaker
// 1997-05-23	Development Started
//
CThreadCareTaker::CThreadCareTaker()
	: m_AddEvent(FALSE, TRUE)			// Manual mode on m_AddEvent
	 ,m_Handle( HANDLE( NULL ) )
{
	m_AddEvent.ResetEvent();		// Set our Event to empty
	m_bKeepGoing = TRUE;
	UINT nThreadId = 0;
	PCHAR cpszBuffer = new char;
	m_Handle = (HANDLE)_beginthreadex( NULL, 0, ThreadCareTakerFunction, PVOID( cpszBuffer ), 0/*CREATE_SUSPENDED*/, &nThreadId );
}		// End CThreadCareTaker::CThreadCareTaker


//////////////////////////////////////////////////////////////////////////////
// ~CThreadCareTaker
// 1997-09-11	Make a call to the Stop to force a clear up
// 1997-05-23	Development Started
//
CThreadCareTaker::~CThreadCareTaker()
{
	StopThreadCareTaker();
}		// End CThreadCareTaker::~CThreadCareTaker


//////////////////////////////////////////////////////////////////////////////
// IsValid
// 1997-05-01	Function Created
//
CBOOL CThreadCareTaker::IsValid()
{
	BOOL bValid_Status = FALSE;
	if ( (this != NULL)
		&& AfxIsValidAddress( this, sizeof( CThreadCareTaker ) )
		)
		bValid_Status = TRUE;
	return( bValid_Status );
}		// End CThreadCareTaker::IsValid


//////////////////////////////////////////////////////////////////////////////
// AddHandle
// 1997-05-23	Development started
//
void CThreadCareTaker::AddHandle( CONST HANDLE cHandle )
{
	CHandle *pHandle = new CHandle;
	pHandle->m_ThreadHandle = cHandle;
	m_ObList.AddTail( pHandle );
	m_AddEvent.PulseEvent();
}		// End CThreadCareTaker::AddHandle


//////////////////////////////////////////////////////////////////////////////
// StopThreadCareTaker
// 1997-09-11	Function Created
//
void CThreadCareTaker::StopThreadCareTaker()
{ 	// Allow CloseThreadHandles to be called naturally
	m_bKeepGoing = FALSE;
	m_AddEvent.SetEvent();
	// Forcibly remove the contents as the static is going out of scope
	if ( m_ObList.GetCount() )
	{
		POSITION pos1, pos2;
		CHandle *pHandle = (CHandle *)NULL;
		DWORD dwExitCode = 0L;
		for( pos1=m_ObList.GetHeadPosition(); (pos2=pos1)!=POSITION(NULL); )
		{
			pHandle = DYNAMIC_DOWNCAST( CHandle, m_ObList.GetNext( pos1 ) );
			CSingleLock SingleLock( &m_ThreadCriticalSection, FALSE );
			VERIFY( ::GetExitCodeThread( pHandle->m_ThreadHandle, &dwExitCode ) );
			if ( dwExitCode == STILL_ACTIVE )
			{	// Thread is active so have to force a close
				// If the target thread owns a critical section, the critical 
				// section will not be released. 
				// If the target thread is executing certain kernel32 calls 
				// when it is terminated, the kernel32 state for the thread’s 
				// process could be inconsistent. 
				// If the target thread is manipulating the global state of a 
				// shared DLL, the state of the DLL could be destroyed, 
				// affecting other users of the DLL. 
//				::TerminateThread( pHandle->m_ThreadHandle, &dwExitCode );
				CBOOL cbThread_Still_Active = FALSE;
				if ( cbThread_Still_Active )
					OutputDebugString( "A Thread is still active on close of CareTaker\n" );
			}
			if ( SingleLock.Lock( 1000 ) )
			{
				m_ObList.RemoveAt( pos2 );	// Have to use old position
				VERIFY( SingleLock.Unlock() );
//				VERIFY( ::CloseHandle( pHandle->m_ThreadHandle ) );
				delete pHandle;
				pHandle = (CHandle *)NULL;
			}
		}
	}
	if ( m_Handle != HANDLE( NULL ) )
	{	// Free the Caretaker Thread function handle
		::WaitForSingleObject( m_Handle, 1000 );
		VERIFY( ::CloseHandle( m_Handle ) );
		m_Handle = HANDLE( NULL );
	}
}		// End CThreadCareTaker::StopThreadCareTaker


//////////////////////////////////////////////////////////////////////////////
// CloseThreadHandles
// 1997-09-08	Put an If around the SingleLock
// 1997-05-23	Function Moved
//
void CThreadCareTaker::CloseThreadHandles()
{
	if ( m_ObList.GetCount() )
	{
		POSITION pos1, pos2;
		CHandle *pHandle = (CHandle *)NULL;
		DWORD dwExitCode = 0L;
		for( pos1=m_ObList.GetHeadPosition(); (pos2=pos1)!=POSITION(NULL); )
		{
			pHandle = DYNAMIC_DOWNCAST( CHandle, m_ObList.GetNext( pos1 ) );
			VERIFY( ::GetExitCodeThread( pHandle->m_ThreadHandle, &dwExitCode ) );
//			if ( (dwExitCode == 0)
//				|| (dwExitCode == 1)
//				)
			if ( dwExitCode != STILL_ACTIVE )
			{
				CSingleLock SingleLock( &m_ThreadCriticalSection, FALSE );
				if ( SingleLock.Lock( 1000 ) )
				{
					m_ObList.RemoveAt( pos2 );	// Have to use old position
					VERIFY( SingleLock.Unlock() );
					VERIFY( ::CloseHandle( pHandle->m_ThreadHandle ) );
					delete pHandle;
					pHandle = (CHandle *)NULL;
				}
			}
		}
	}
}		// End CThreadCareTaker::CloseThreadHandles


//////////////////////////////////////////////////////////////////////////////
// ThreadCareTakerFunction
// 1997-05-23	Development Started
//
UINT APIPRIVATE ThreadCareTakerFunction( PVOID pvThreadData )
{
	delete pvThreadData;
	HANDLE hCurrentThread = GetCurrentThread();
	SetThreadPriority( hCurrentThread, THREAD_PRIORITY_LOWEST );
	while ( CThreadCareTaker::GetCThreadCareTaker().m_bKeepGoing )
	{
		CThreadCareTaker::GetCThreadCareTaker().m_AddEvent.Lock( 500 );	// sleep for 1/2 secs or until our event is triggered
		CThreadCareTaker::GetCThreadCareTaker().CloseThreadHandles();
	}
	CThreadCareTaker::GetCThreadCareTaker().CloseThreadHandles();
	SetThreadPriority( hCurrentThread, THREAD_PRIORITY_NORMAL );
	return( 0 );
}		// End ThreadCareTakerFunction


//////////////////////////////////////////////////////////////////////////////
// CThreadManager
// 1997-05-23	Development Started
//
CThreadManager::CThreadManager( CONSOLETHREADPROC pfnThreadProc, LPVOID pParam )
{
	UINT nThreadId = 0;
	_ASSERTE( CThreadCareTaker::GetCThreadCareTaker().IsValid() );
	m_Handle = (HANDLE)_beginthreadex( NULL, 0, pfnThreadProc, pParam, CREATE_SUSPENDED, &nThreadId );
	if ( CThreadCareTaker::GetCThreadCareTaker().m_bKeepGoing )
	{
		CSingleLock SingleLock( &CThreadCareTaker::GetCThreadCareTaker().m_ThreadCriticalSection, FALSE );
		VERIFY( SingleLock.Lock( 1000 ) );
		ASSERT( m_Handle );
		CThreadCareTaker::GetCThreadCareTaker().AddHandle( m_Handle );
	}
	else
	{
		static BOOL bDisplayed = FALSE;
		static CBOOL scbThreadCareTaker_IsValid_Failed = FALSE;
		if ( !bDisplayed )
		{
			bDisplayed = TRUE;
			_ASSERTE( scbThreadCareTaker_IsValid_Failed );
			bDisplayed = FALSE;
		}
	}
}		// End CThreadManager::CThreadManager


//////////////////////////////////////////////////////////////////////////////
// CThreadManager
// 1997-05-23	Development Started
//
CThreadManager::~CThreadManager()
{
}		// End CThreadManager::~CThreadManager


//////////////////////////////////////////////////////////////////////////////
// public: RunThread
// 1997-07-17	Now return the success of restarting
// 1997-05-23	Development Started
//
CBOOL CThreadManager::RunThread()
{
	return( ::ResumeThread( m_Handle ) != 0xFFFFFFFF );
}		// End CThreadManager::RunThread
