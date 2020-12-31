#include <windows.h>
#include <stdlib.h>
#include <objbase.h>
#include <assert.h>

#define __OUTPROC_SERVER_ // To get the proper definition of trace
#include "util.h"
#undef __OUTPROC_SERVER_ 

#include "Free.h"

static inline void trace(char* msg)
	{ Util::Trace("Free thread", msg, S_OK) ;} 
static inline void trace(char* msg, HRESULT hr)
	{ Util::Trace("Free thread", msg, hr) ;}

///////////////////////////////////////////////////////////
//
// Constructor
//
CSimpleFree::CSimpleFree() 
{
	m_ThreadId = 0 ;	
	m_hThread = NULL ;
	m_hCreateComponentEvent = NULL ;
	m_hComponentReadyEvent = NULL ;
	m_hStopThreadEvent = NULL ;
	m_pIStream = NULL ;
	m_hr = S_OK ;
	m_piid = NULL ;
	m_pclsid = NULL ;
	m_WaitTime = 500 ;
} 

///////////////////////////////////////////////////////////
//
// Destructor
//
CSimpleFree::~CSimpleFree()
{
	// The thread must be stopped before we are deleted
	// because the WorkerFunction is in the derived class.
	assert(m_hThread == NULL) ;
}

///////////////////////////////////////////////////////////
//
// StartThread
//   - Create and start the thread.
//
BOOL CSimpleFree::StartThread(DWORD WaitTime) 
{
	if (IsThreadStarted())
	{
		return FALSE ;
	}

	// Create the thread.
	m_hThread
		= ::CreateThread(NULL,             // Default security
		                 0,                // Default stack size
		                 RealThreadProc, 
		                 (void*)this,
		                 CREATE_SUSPENDED, // Create the thread suspended.
		                 &m_ThreadId) ;    // Get the Thread ID.
	if (m_hThread == NULL)
	{
		trace("StartThread failed to create thread.", GetLastError()) ; 
		return FALSE ;
	}
	trace("StartThread successfully created thread.") ;

	// Create an event to signal the thread to create the component. 
	m_hCreateComponentEvent = ::CreateEvent(NULL, FALSE, FALSE, NULL) ;
	if (m_hCreateComponentEvent == NULL)
	{
		return FALSE ;
	}

	// Create an event for the thread to signal when it is finished. 
	m_hComponentReadyEvent = ::CreateEvent(NULL, FALSE, FALSE, NULL) ;
	if (m_hComponentReadyEvent == NULL)
	{
		return FALSE ;
	}

	// Create an event to tell the free thread to stop.
	m_hStopThreadEvent = ::CreateEvent(NULL, FALSE, FALSE, NULL) ;
	if (m_hStopThreadEvent == NULL)
	{
		return FALSE ;
	}

	trace("StartThread successfully created the events.") ;

	// Initialize the wait time.
	m_WaitTime = WaitTime ;

	// Thread was created suspended; start the thread.
	DWORD r = ::ResumeThread(m_hThread) ;
	assert(r != 0xffffffff) ;

	// Wait for the thread to start up before we continue.
	WaitWithMessageLoop(m_hComponentReadyEvent) ;

	// Make sure that thread is still running and that
	// there isn't an error.
	DWORD dwReturn = 0 ;
	BOOL b = ::GetExitCodeThread(m_hThread, &dwReturn) ;
	assert(b) ;
	if (dwReturn != STILL_ACTIVE)
	{
		trace("There was an error. Thread is not running.") ;
		m_hThread = NULL ;
		return FALSE ;
	}

	return TRUE ;
}

///////////////////////////////////////////////////////////
//
// StopThread
//
void CSimpleFree::StopThread()
{
	if (m_hThread != NULL)
	{
		// Stop the thread.
		// PostThreadMessage(m_ThreadId, WM_QUIT, 0,0) ;
		SetEvent(m_hStopThreadEvent) ;

		// Wait for thread to stop.
		WaitWithMessageLoop(m_hComponentReadyEvent) ;

		m_hThread = NULL ;
	}
}
	
///////////////////////////////////////////////////////////
//
// Current thread status
//
BOOL CSimpleFree::IsThreadStarted()
{
	return (m_hThread != NULL) ;
}

///////////////////////////////////////////////////////////
//
// Thread procedure
//
DWORD WINAPI CSimpleFree::RealThreadProc(void* pv) 
{
	CSimpleFree* pFree = reinterpret_cast<CSimpleFree*>(pv) ;
	return pFree->ClassThreadProc() ;
}

///////////////////////////////////////////////////////////
//
// Thread procedure
//
BOOL CSimpleFree::ClassThreadProc()
{
	BOOL bReturn = FALSE ;

	// Check for the existence of CoInitializeEx.
	typedef HRESULT (__stdcall *FPCOMINITIALIZE)(void*, DWORD) ;
	FPCOMINITIALIZE pCoInitializeEx = 
		reinterpret_cast<FPCOMINITIALIZE>(
			::GetProcAddress(::GetModuleHandle("ole32"),
			                 "CoInitializeEx")) ;
	if (pCoInitializeEx == NULL)
	{
		trace("This program requires the free-thread support in DCOM.") ;
		SetEvent(m_hComponentReadyEvent) ;
		return FALSE ;
	}

	// Initialize the COM Library.
	HRESULT hr = pCoInitializeEx(0, COINIT_MULTITHREADED) ; //@
	if (SUCCEEDED(hr))
	{
		// Signal that we are starting.
		SetEvent(m_hComponentReadyEvent) ;

		// Set up array of events.
		HANDLE hEventArray[2] = { m_hCreateComponentEvent,
		                          m_hStopThreadEvent } ;

		// Wait for the signal to create a component.
		BOOL bContinue = TRUE ;
		while (bContinue)
		{
			//@
			switch(::WaitForMultipleObjects(2,
			                                hEventArray,
			                                FALSE,
			                                m_WaitTime)) 
			{
			// Create the component.
			case WAIT_OBJECT_0:			
				CreateComponentOnThread() ;	
				break ;

			// Stop the thread.
			case (WAIT_OBJECT_0 +1):
				bContinue = FALSE ;
				bReturn = TRUE ;
				break ;

			// Do background processing.
			case WAIT_TIMEOUT:
				WorkerFunction() ; 
				break ;

			default:
				trace("Wait failed.", GetLastError()) ; 
			}
		}
		// Uninitialize the COM Library.
		CoUninitialize() ;
	}

	// Signal that we have finished.
	SetEvent(m_hComponentReadyEvent) ;
	return bReturn ;
}


///////////////////////////////////////////////////////////
//
// CreateComponent helper function
//
HRESULT CSimpleFree::CreateComponent(const CLSID& clsid,
                                     const IID& iid,
                                     IUnknown** ppI)
{
	// Initialize the shared data.
	m_pIStream = NULL ;
	m_piid = &iid ;
	m_pclsid = &clsid ;

	// Signal the thread to create a component.
	SetEvent(m_hCreateComponentEvent) ;

	// Wait for the component to be created.
	trace("Wait for the component to be created.") ;
	if (WaitWithMessageLoop(m_hComponentReadyEvent))
	{
		trace("The wait succeeded.") ;

		if (FAILED(m_hr))        // Did GetClassFactory fail?
		{
			return m_hr ;
		}

		if (m_pIStream == NULL)  // Did the marshaling fail?
		{
			return E_FAIL ;
		}

		trace("Unmarshal the interface pointer.") ;
		// Unmarshal the interface.
		HRESULT hr = ::CoGetInterfaceAndReleaseStream(m_pIStream,
		                                              iid,
		                                              (void**)ppI) ;
		m_pIStream = NULL ;
		if (FAILED(hr))
		{
			trace("CoGetInterfaceAndReleaseStream failed.", hr) ; 
			return E_FAIL ;
		}
		return S_OK ;
	}
	trace("What happened here?") ;
	return E_FAIL ;
}

///////////////////////////////////////////////////////////
//
// CreateComponentOnThread helper function
//   - This function packages the parameters for the
//     CoCreateComponentOnThread function.
//
void CSimpleFree::CreateComponentOnThread()
{
	IUnknown* pI = NULL;
	// Call the derived class to actually create the component.
	m_hr = CreateComponentOnThread(*m_pclsid, *m_piid, &pI) ;
	if (SUCCEEDED(m_hr))
	{
      trace("Successfully created component.") ;
		// Marshal the interface pointer to the server.
		HRESULT hr = ::CoMarshalInterThreadInterfaceInStream(*m_piid,
		                                                     pI,
		                                                     &m_pIStream) ;
		assert(SUCCEEDED(hr)) ;

		// Release the pI Pointer.
		pI->Release() ;
	}
	else
	{
		trace("CreateComponentOnThread failed.", m_hr);
	}

	trace("Signal the main thread that the component is ready.") ;
	SetEvent(m_hComponentReadyEvent) ;

}
///////////////////////////////////////////////////////////
//
// BOOL WaitWithMessageLoop(HANDLE hEvent)
//
BOOL CSimpleFree::WaitWithMessageLoop(HANDLE hEvent)
{
	while (TRUE)
	{
		// Wait for the event and for messages.
		DWORD dwReturn = ::MsgWaitForMultipleObjects(1,
		                                             &hEvent,
		                                             FALSE,
		                                             INFINITE,
		                                             QS_ALLINPUT) ;
		if (dwReturn == WAIT_OBJECT_0)
		{
			// Our event happened.
			return TRUE ;
		}
		else if (dwReturn == WAIT_OBJECT_0 + 1)
		{
			// Handle message to keep client alive.
			MSG msg ;
			while(::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
				::DispatchMessage(&msg) ;
			}
		}
		else
		{
			trace("WaitWithMessageLoop failed.", GetLastError()) ; 
			return FALSE ;
		}
	}
}
