// ==========================================================================
// 							Class Specification : COXOwnThread
// ==========================================================================

// Header file : OXOwnThread.h

// This software along with its related components, documentation and files ("The Libraries")
// is © 1994-2007 The Code Project (1612916 Ontario Limited) and use of The Libraries is
// governed by a software license agreement ("Agreement").  Copies of the Agreement are
// available at The Code Project (www.codeproject.com), as part of the package you downloaded
// to obtain this file, or directly from our office.  For a copy of the license governing
// this software, you may contact us at legalaffairs@codeproject.com, or by calling 416-849-8900.
                          
// //////////////////////////////////////////////////////////////////////////

// Properties:
//	NO	Abstract class (does not have any objects)

//	NO	Is a Cwnd.                     
//	NO	Two stage creation (constructor & Create())
//	NO	Has a message map
//	NO	Needs a resource (template)

//	NO	Persistent objects (saveable on disk)      
//	YES	Uses exceptions

// //////////////////////////////////////////////////////////////////////////

// Description :         
//	The purpose of this class is to serve as a base class for COXOwnThreadCmdTarget, 
//	COXOwnThreadDocument or user derived classes from CCmdTarget (Encapsulation around
//	a IDispatch OLE object).
//	The class mainly encapsulates the marshalling of IDispatch object between the 
//	Owner thread (the thread that created the object) and the Own thread (a own 
//	message loop). 
//	By marshalling the IDispatch object, the OLE calls to the object will be 
//	re-routed to the Own thread.  
//	The derived class needs to derive from CCmdTarget (or other derived class from
//	CCmdTarget) and from this class, in order to re-route the OLE calls complete 
//	transparently. COXOwnThreadCmdTarget and COXOwnThreadDocument are 2 (ready to use)
//	examples of how to use this COwnThread engine class.

// Remark:
//		

// Prerequisites (necessary conditions):
//		

/////////////////////////////////////////////////////////////////////////////

#ifndef __OXOWNTHREAD_H__
#define __OXOWNTHREAD_H__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "OXDllExt.h"


#include "OXDispatchMarshaller.h"
#include "OXFinalReleaseWnd.h"


/////////////////////////////////////////////////////////////////////////////
// COwnThread engine

class OX_CLASS_DECL COXOwnThread
{
// Data Members
public:

protected:
	BOOL		m_bHasOwnThread;
	HANDLE		m_hCreatedEvent;
	HANDLE		m_hThreadEvent;
	HANDLE		m_hEndEvent;
	HRESULT		m_hCreateResult;
	LPUNKNOWN 	m_pMarshalledPunk;
	BOOL		m_bEndThread;
	DWORD		m_nOwnerThreadID;
	DWORD		m_nOwnThreadID;
	COXDispatchMarshaller
				m_dispatchMarshaller;
	COXFinalReleaseWnd 
				m_finalReleaseWnd;

	friend COXFinalReleaseWnd;			

private:


// Member Functions
public:
	COXOwnThread();
	// --- In  : none
	// --- Out : none
	// --- Returns : nothing
	// --- Effect :  constructs the object

	virtual ~COXOwnThread();
	// --- In  : none
	// --- Out : none
	// --- Returns : nothing
	// --- Effect :  constructs the object

	BOOL EnableOwnThread();
	// --- In  : none
	// --- Out : none
	// --- Returns : If the own thread is started successful or not
	//				 This function should always succeed unless
	//				 the operating systems is extremely low on resources
	// --- Effect :  All the OLE Calls to this object will be re-routed
	//				 by the own thread.
	//				 Different objects can be served simultaneous.

	BOOL HasOwnThread();
	// --- In  : none
	// --- Out : none
	// --- Returns : if the CmdTarget has a own thread started.
	// --- Effect : 

	BOOL FinalReleaseRouter();
	// --- In  : none
	// --- Out : none
	// --- Returns : if the call is re-routed or not
	// --- Effect : If you override the virtual member function 'OnFinalRelease' of CCmdTarget,
	//				you have to call this function before you do anything else.
	//				If the call returns TRUE, you have to return immediately.
	//	Example with CMyCmdTarget derived from COXOwnThreadCmdTarget
	//	void CMyCmdTarget::OnFinalRelease()   
	//	{
	//		if (FinalReleaseRouter())
	//			return;
	//
	//		// TODO: Add your specialised code here and/or call the base class
	//
	//		CCmdTarget::OnFinalRelease();
	//	}

	void SetThreadEvent();
	// --- In  : none
	// --- Out : none
	// --- Returns : nothing
	// --- Effect : Fires an event to the own thread, which will call the overridable
	//				function 'OnThreadEvent'.

	virtual LPDISPATCH GetIDispatch(BOOL bAddRef) = 0;
	// --- In  : bAddRef: Specifies whether to increment the reference count for the object.
	// --- Out : none
	// --- Returns : The IDispatch pointer associated with the object
	// --- Effect : This is a pure virtual function, so the implementation of the derived class is used.
	//				This declaration is needed to give access to the real CCmdTarget implementation of this function

protected:
	LPUNKNOWN GetInterfaceHook(const void*);
	virtual void OnFinalRelease() = 0;
	void Run();
	static UINT __cdecl StartThread(LPVOID pOwnThread);
	void EndThread();
	virtual void OnThreadEvent();
	virtual void OnThreadDestroy();


private:

};

#endif //__OXOWNTHREAD_H__


/////////////////////////////////////////////////////////////////////////////
