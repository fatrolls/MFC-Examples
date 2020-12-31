// ==========================================================================
// 							Class Specification : COXFinalReleaseWnd
// ==========================================================================

// Header file : OXFinalReleaseWnd.h

// This software along with its related components, documentation and files ("The Libraries")
// is © 1994-2007 The Code Project (1612916 Ontario Limited) and use of The Libraries is
// governed by a software license agreement ("Agreement").  Copies of the Agreement are
// available at The Code Project (www.codeproject.com), as part of the package you downloaded
// to obtain this file, or directly from our office.  For a copy of the license governing
// this software, you may contact us at legalaffairs@codeproject.com, or by calling 416-849-8900.
                         
// //////////////////////////////////////////////////////////////////////////

// Properties:
//	NO	Abstract class (does not have any objects)

//	YES	Is a Cwnd.                     
//	NO	Two stage creation (constructor & Create())
//	NO	Has a message map
//	NO	Needs a resource (template)

//	NO	Persistent objects (saveable on disk)      
//	YES	Uses exceptions

// //////////////////////////////////////////////////////////////////////////

// Description :         
//	This object serves as a message sink for the COXOwnThread object
//	It's important that the COXOwnThread object is deleted by the same
//	thread that instantiation ed the object (the Owner thread).
//	The OnFinalRelease function of COXOwnThread will check which thread 
//	(Owner or Own thread) tries to delete the object. If it is the Own
//	thread, a message is send to this object (which is a data member of 
//	the COWOwnThread object). Because this object is a window created by
//	the Owner thread, the message will be handled by the Owner thread and 
//	consequently the COXOwnThread object can be safely destroyed from here.

// Remark:
//		

// Prerequisites (necessary conditions):
//		

/////////////////////////////////////////////////////////////////////////////

#ifndef __OXFINALERELEASEWND_H__
#define __OXFINALERELEASEWND_H__


#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "OXDllExt.h"

#define WMOX_FINAL_RELEASE WM_USER+1


class COXOwnThread;

class OX_CLASS_DECL COXFinalReleaseWnd : public CWnd
{
// Data Members
public:

protected:
	static CString m_sClassName;	// the class name used for registration
	COXOwnThread* m_pOwnThread;		// a pointer to the parent object
									// initialized by constructor

private:

// Member Functions
public:
	COXFinalReleaseWnd(COXOwnThread* pOwnThread);
	// --- In  : pOwnThread: a pointer to the parent object COXOwnThread
	//				so that we can delete the parent from within this object
	// --- Out : none
	// --- Returns : 
	// --- Effect : Constructs the object

	virtual ~COXFinalReleaseWnd();
	// --- In  : none
	// --- Out : none
	// --- Returns : 
	// --- Effect : Destructs the object

protected:
	afx_msg LONG OnObjectFinalRelease(UINT, LONG);

	DECLARE_MESSAGE_MAP()

private:

};

#endif //__OXFINALERELEASEWND_H__


/////////////////////////////////////////////////////////////////////////////
