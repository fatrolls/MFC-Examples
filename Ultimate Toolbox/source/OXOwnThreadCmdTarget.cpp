// ==========================================================================
// 							Class Implementation : COXOwnThreadCmdTarget
// ==========================================================================

// Source file : OXOwnThreadCmdTarget.cpp

// This software along with its related components, documentation and files ("The Libraries")
// is © 1994-2007 The Code Project (1612916 Ontario Limited) and use of The Libraries is
// governed by a software license agreement ("Agreement").  Copies of the Agreement are
// available at The Code Project (www.codeproject.com), as part of the package you downloaded
// to obtain this file, or directly from our office.  For a copy of the license governing
// this software, you may contact us at legalaffairs@codeproject.com, or by calling 416-849-8900.
                          
// //////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OXOwnThreadCmdTarget.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_DYNCREATE(COXOwnThreadCmdTarget, CCmdTarget)

#define new DEBUG_NEW

/////////////////////////////////////////////////////////////////////////////
// COXOwnThreadCmdTarget


COXOwnThreadCmdTarget::COXOwnThreadCmdTarget()
// --- In  : none
// --- Out : none
// --- Returns : nothing
// --- Effect : constructs the object
{
}

COXOwnThreadCmdTarget::~COXOwnThreadCmdTarget()
// --- In  : none
// --- Out : none
// --- Returns : nothing
// --- Effect : destructs the object
{
}

void COXOwnThreadCmdTarget::OnFinalRelease()
// --- In  : none
// --- Out : none
// --- Returns : nothing
// --- Effect : will re-route the call if necessary
//				It is important that the destruction of the object is done
//				by the same thread that constructed the object.
//				There for 'FinalReleaseRouter' will check if the call is made by
//				the Owner thread or by the Own thread;
//				In case it is made by the Own thread the call is re-routed and
//				OnFinalRelease returns immediately
{
	if (FinalReleaseRouter())
		return;
	CCmdTarget::OnFinalRelease();
}

LPDISPATCH COXOwnThreadCmdTarget::GetIDispatch(BOOL bAddRef)
{
	return CCmdTarget::GetIDispatch(bAddRef);
}

BEGIN_MESSAGE_MAP(COXOwnThreadCmdTarget, CCmdTarget)
	//{{AFX_MSG_MAP(COXOwnThreadCmdTarget)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(COXOwnThreadCmdTarget, CCmdTarget)
	//{{AFX_DISPATCH_MAP(COXOwnThreadCmdTarget)
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()


LPUNKNOWN COXOwnThreadCmdTarget::GetInterfaceHook(const void* CIID)
// --- In  : Class ID of the wanted interface
// --- Out : none
// --- Returns : The interface handle
// --- Effect : Re-routes this function to the COXOwnThread base class
//				which will determine to hook the marshalled IDispatch handle
//				in case this call is done by the Owner thread
{
	return COXOwnThread::GetInterfaceHook(CIID);	
}



