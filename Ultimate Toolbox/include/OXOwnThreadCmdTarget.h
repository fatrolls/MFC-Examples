// ==========================================================================
// 							Class Specification : COXOwnThreadCmdTarget
// ==========================================================================

// Header file : OXOwnThreadCmdTarget.h

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
//	This class is an alternative for CCmdTarget. It offers multi-threading
//	functionality to your automation server.
//	By deriving from this class instead of CCmdTarget, all your OLE calls
//	are handled by a separate Own thread. In that way more concurrently 
//	calls can be handled simultaneously.
//	The main part of the implementation is done in the COXOwnThread class, so 
//	the code can be shared by other derivation of CCmdTarget (see COXOwnThreadDocument).

// HOW TO USE -> it is as easy as this:
//	As said above, you need to derive from this class instead of CCmdTarget.
//	Further more you need to call the 'EnableOwnthread' function from within
//	the constructor of your derived class.
//	If you are overriding the 'OnFinalRelease' function of CCmdTarget
//	you need also to call 'FinalReleaseRouter()' (see 'FinalReleaseRouter' further on)

//	For derivation of CDocument you have to use COXOwnThreadDocument.
//	For other derivation you can build your own class analogue to COXOwnThreadCmdTarget
//	and COXOwnThreadDocument.

// Remark:
//		

// Prerequisites (necessary conditions):
//		

/////////////////////////////////////////////////////////////////////////////

#ifndef __OXOWNTHREADCMDTARGET_H__
#define __OXOWNTHREADCMDTARGET_H__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "OXDllExt.h"


/////////////////////////////////////////////////////////////////////////////
// COwnThreadCmdTarget command target

#include "OXOwnThread.h"


class OX_CLASS_DECL COXOwnThreadCmdTarget : public CCmdTarget, public COXOwnThread
{
DECLARE_DYNCREATE(COXOwnThreadCmdTarget)

// Data Members
public:

protected:

private:

// Member Functions
public:

//	The public interface of this class contains 3 easy functions.
//	They are defined in COXOwnThread where this class is derived from:

//	BOOL EnableOwnThread();
	// --- In  : none
	// --- Out : none
	// --- Returns : If the own thread is started successful or not
	//				 This function should always succeed unless
	//				 the operating systems is extremely low on resources
	// --- Effect :  All the OLE Calls to this object will be re-routed
	//				 by the own thread.
	//				 Different objects can be served simultaneous.

//	BOOL HasOwnThread();
	// --- In  : none
	// --- Out : none
	// --- Returns : if the CmdTarget has a own thread started.
	// --- Effect : 

//	BOOL FinalReleaseRouter();
	// --- In  : none
	// --- Out : none
	// --- Returns : if the call is re-routed or not
	// --- Effect : If you override the virtual member function 'OnFinalRelease' of CCmdTarget,
	//				you have to call this function before you do anything else.
	//				If the call returns TRUE, you have to return immediately.
	//	Example:
	//	void CMyCmdTarget::OnFinalRelease()
	//	{
	//		if (FinalReleaseRouter())
	//			return;
	//
	//		// TODO: Add your specialised code here and/or call the base class
	//
	//		CCmdTarget::OnFinalRelease();
	//	}


	virtual LPDISPATCH GetIDispatch(BOOL bAddRef);
	// --- In  : bAddRef: Specifies whether to increment the reference count for the object.
	// --- Out : none
	// --- Returns : The IDispatch pointer associated with the object
	// --- Effect : provides access to the IDispatch handle
	//				Is used by the COXOwnThread base class


	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COXOwnThreadCmdTarget)
	public:
	virtual void OnFinalRelease();
	//}}AFX_VIRTUAL


protected:
	COXOwnThreadCmdTarget();           // protected constructor used by dynamic creation
	virtual ~COXOwnThreadCmdTarget();

	virtual LPUNKNOWN GetInterfaceHook(const void*);

	// Generated message map functions
	//{{AFX_MSG(COXOwnThreadCmdTarget)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(COXOwnThreadCmdTarget)
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()

private:

};
#endif //__OXOWNTHREADCMDTARGET_H__


/////////////////////////////////////////////////////////////////////////////
