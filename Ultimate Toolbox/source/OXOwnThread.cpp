// ==========================================================================
// 							Class Implementation : COXOwnThread
// ==========================================================================

// Source file : OXOwnThread.h

// This software along with its related components, documentation and files ("The Libraries")
// is © 1994-2007 The Code Project (1612916 Ontario Limited) and use of The Libraries is
// governed by a software license agreement ("Agreement").  Copies of the Agreement are
// available at The Code Project (www.codeproject.com), as part of the package you downloaded
// to obtain this file, or directly from our office.  For a copy of the license governing
// this software, you may contact us at legalaffairs@codeproject.com, or by calling 416-849-8900.
                          
// //////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OXOwnThread.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// Remarks about the protected data members
//	BOOL		m_bHasOwnThread;	//	if the own thread is enabled or not
//	HANDLE		m_hCreatedEvent;	//	event for synchronisation during thread startup
//	HANDLE		m_hThreadEvent;		//	see 'SetThreadEvent' and 'OnThreadEvent' functions
//	HANDLE		m_hEndEvent;		//	event for synchronisation during thread cleanup
//	HRESULT		m_hCreateResult;	//	result value of the creation of the own thread
//	LPUNKNOWN 	m_pMarshalledPunk;	//	the marshalled object pointer; to be passed to the Owner thread
//	BOOL		m_bEndThread;		//	ends the Own thread when set to TRUE
//	DWORD		m_nOwnerThreadID;	//	ThreadID of the owner thread (thread that created the object)
//	DWORD		m_nOwnThreadID;		//	ThreadID of the Own thread
//	COXDispatchMarshaller
//				m_dispatchMarshaller;	// Encapsulation of the marshal stream	
//	COXFinalReleaseWnd 
//				m_finalReleaseWnd;		// Helper window for re-routing the releasing of the object from 
//										// the Own thread to the Owner thread
//
//	//	The COXFinalReleaseWnd must be able to call a protected member function
//	//	of this COXOwnThread object in order to release this object
//	friend COXFinalReleaseWnd;			


/////////////////////////////////////////////////////////////////////////////
// COXOwnThread

COXOwnThread::COXOwnThread() :
  	m_hCreatedEvent(NULL),
	m_hThreadEvent(NULL),
	m_hEndEvent(NULL),
	m_pMarshalledPunk(NULL),
	m_bEndThread(FALSE),
	m_nOwnerThreadID(0),
	m_nOwnThreadID(0),
#pragma warning(disable : 4355)  // turn off the
	m_finalReleaseWnd(this),
#pragma warning (default : 4355)  // Turn the warning back on
	m_bHasOwnThread(FALSE)
// --- In  : none
// --- Out : none
// --- Returns : nothing
// --- Effect : Constructs the object and retrieves the thread ID of the Owners thread
//				in order to be able to re-route later the releasing from the Own thread
//				back to the Owners Thread.
{
	m_nOwnerThreadID = AfxGetThread()->m_nThreadID;
}

COXOwnThread::~COXOwnThread()
// --- In  : none
// --- Out : none
// --- Returns : nothing
// --- Effect : Destructs the object and waits until the own thread is terminated
{
	// The destructor can only be called from the same thread
	// that called the constructor !
	ASSERT(AfxGetThread()->m_nThreadID==m_nOwnerThreadID);
	m_finalReleaseWnd.DestroyWindow();
	EndThread();	
	if (m_hCreatedEvent) CloseHandle(m_hCreatedEvent);
	if (m_hThreadEvent) CloseHandle(m_hThreadEvent);
	if (m_hEndEvent) CloseHandle(m_hEndEvent);
}

BOOL COXOwnThread::EnableOwnThread()
{
	// This function can only be called from the same thread
	// that called the constructor !
	ASSERT(AfxGetThread()->m_nThreadID==m_nOwnerThreadID);

	if (m_dispatchMarshaller.CheckStream() && m_finalReleaseWnd.m_hWnd)
	{

		m_hCreatedEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
		m_hThreadEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
		m_hEndEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

		AfxBeginThread(StartThread, this);

		WaitForSingleObject(m_hCreatedEvent, INFINITE);
		if (m_hCreateResult==S_OK)
		{
		    // unmarshal an IUnknown from the scratch stream. if unmarshalling
		    // fails, it takes care of releasing the object inside the marshal-data
		    HRESULT hr = m_dispatchMarshaller.Unmarshal((void **)&m_pMarshalledPunk);
		    if (hr==S_OK)
				m_bHasOwnThread = TRUE;
			else
			{
				m_bEndThread=TRUE;
				SetThreadEvent();
				WaitForSingleObject(m_hEndEvent, INFINITE);
			}
		}
	}
#ifdef _DEBUG
	if (!m_bHasOwnThread)
		TRACE(_T("Can't enable own thread in 'COXOwnThreadCmdTarget::EnableOwnThread' \n'OLE_NO_OWNTRHEAD'-macro defined !\n"));
#endif
	return m_bHasOwnThread;
}

BOOL COXOwnThread::HasOwnThread()
{
	return m_bHasOwnThread;
}

BOOL COXOwnThread::FinalReleaseRouter()
{
	if (AfxGetThread()->m_nThreadID==m_nOwnerThreadID)
		return FALSE;
	else if (AfxGetThread()->m_nThreadID==m_nOwnThreadID)
	{
		if (m_finalReleaseWnd.m_hWnd)
			m_finalReleaseWnd.PostMessage(WMOX_FINAL_RELEASE);
	}
#ifdef _DEBUG
	else
	{
		ASSERT(FALSE);
		TRACE(_T("Call from an illegal thread !\n"));
	}
#endif
	return TRUE;
}

void COXOwnThread::SetThreadEvent()
{
	SetEvent(m_hThreadEvent);
}

// protected function

void COXOwnThread::Run()
// --- In  : none
// --- Out : none
// --- Returns : nothing
// --- Effect : this function keeps the Own thread running until m_bEndThread is set 
//				to TRUE.
{
    MSG     msg;

	m_nOwnThreadID = AfxGetThread()->m_nThreadID;

    // initialize COM
    m_hCreateResult = CoInitialize(NULL);
    if (m_hCreateResult==S_OK)
    {
		m_hCreateResult = m_dispatchMarshaller.Marshal(GetIDispatch(FALSE));
		SetEvent(m_hCreatedEvent);

		// apartment message/event loop
		// (see SDK documentation for MsgWaitForMultipleObjects)
		// here worker message loops last forever. in situations without a
		// static number of worker threads, the loop could easily be terminated by
		// WM_QUITs sent from the main thread which might manage the worker thread
		// pool more carefully.
		
		if (m_hCreateResult==S_OK)
		{
			DWORD dwWaitResult;

			while (!m_bEndThread)
			{
				// wait for any message sent or posted to this queue
				// or for one of the passed handles to become signaled
				dwWaitResult = MsgWaitForMultipleObjects(1, &m_hThreadEvent, FALSE, INFINITE, QS_ALLINPUT);

				// result tells us the type of event we have:
				// a message or a signaled handle

				// if there are one or more messages in the queue ...
				if (dwWaitResult == (WAIT_OBJECT_0 + 1))
				{
					// dispatch all of the messages in this next loop
					// (here is where we'd check for WM_QUITs to end this
					// worker thread if we wanted to)
					while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
						DispatchMessage(&msg);
				}
				else if (!m_bEndThread)
					OnThreadEvent();
	    	}
		}
    }
	else
		SetEvent(m_hCreatedEvent);
	OnThreadDestroy();
    CoUninitialize();
	SetEvent(m_hEndEvent);
}

UINT __cdecl COXOwnThread::StartThread(LPVOID pOwnThread)
// --- In  : pOwnThread: the this pointer passed by the creating of the thread
// --- Out : none
// --- Returns : always zero
// --- Effect : this is a static function so we pass the control to a non static function (Run)
{
	((COXOwnThread*) pOwnThread)->Run();
	return 0;
}

LPUNKNOWN COXOwnThread::GetInterfaceHook(const void*)
// --- In  : none
// --- Out : none
// --- Returns : the marshalled IDispatch handle if the call is done by the Owner thread
// --- Effect :  This is a first chance hook function.
//				 If the call is done by the Own thread we return NULL (in this case
//				 we don't want to hook). If the call is done by the Owner thread
//				 we return the marshalled IDispatch handle.
{
	if (m_bHasOwnThread)
	{
		if (AfxGetThread()->m_nThreadID==m_nOwnerThreadID)
			return m_pMarshalledPunk;
#ifdef _DEBUG
		else if (AfxGetThread()->m_nThreadID!=m_nOwnThreadID)
		{
			ASSERT(FALSE);
			TRACE(_T("Call from an illegal thread !\n"));
		}
#endif
	}
	return NULL;	
}

void COXOwnThread::EndThread()
// --- In  : none
// --- Out : none
// --- Returns : nothing
// --- Effect : This function is called by the destructor and ends
//				the own thread.
{
	if (HasOwnThread())
	{
		m_bEndThread=TRUE;
		SetThreadEvent();
		WaitForSingleObject(m_hEndEvent, INFINITE);
	}
}

void COXOwnThread::OnThreadEvent()
// --- In  : none
// --- Out : none
// --- Returns : nothing
// --- Effect : You can override this function, if you want to let the
//				Own thread handle some specific things.
//				If you call the SetThreadEvent from within the Owner thread
//				then this notification will be handled by the Own thread.
{
}

void COXOwnThread::OnThreadDestroy()
// --- In  : none
// --- Out : none
// --- Returns : nothing
// --- Effect : You can override this function, if you have some things
//				to be cleaned up by the own thread.
{
}

