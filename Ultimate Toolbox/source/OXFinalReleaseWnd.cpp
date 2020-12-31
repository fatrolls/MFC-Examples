// ==========================================================================
// 							Class Implementation : COXFinalReleaseWnd
// ==========================================================================

// Source file : OXFinalReleaseWnd.h

// This software along with its related components, documentation and files ("The Libraries")
// is © 1994-2007 The Code Project (1612916 Ontario Limited) and use of The Libraries is
// governed by a software license agreement ("Agreement").  Copies of the Agreement are
// available at The Code Project (www.codeproject.com), as part of the package you downloaded
// to obtain this file, or directly from our office.  For a copy of the license governing
// this software, you may contact us at legalaffairs@codeproject.com, or by calling 416-849-8900.
                          
// //////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OXFinalReleaseWnd.h"
#include "OXOwnThread.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


// Static members
// m_sClassName is a static member so that it can be used for the registration 
//	of all the COXFinalReleaseWnd objects in the same process space
CString	COXFinalReleaseWnd::m_sClassName;

/////////////////////////////////////////////////////////////////////////////
// COXFinalReleaseWnd 

COXFinalReleaseWnd::COXFinalReleaseWnd(COXOwnThread* pOwnThread) :
	m_pOwnThread(pOwnThread)
{
	if (m_sClassName.IsEmpty())
		m_sClassName = AfxRegisterWndClass(0);
	CreateEx(0, m_sClassName, _T("OwnThreadFinalReleaseWnd"),0,0,0,0,0,NULL,NULL);
}

COXFinalReleaseWnd::~COXFinalReleaseWnd()
{
}

BEGIN_MESSAGE_MAP(COXFinalReleaseWnd, CWnd)
	ON_MESSAGE(WMOX_FINAL_RELEASE, OnObjectFinalRelease)
END_MESSAGE_MAP()

LONG COXFinalReleaseWnd::OnObjectFinalRelease(UINT, LONG)
// --- In  : none
// --- Out : none
// --- Returns : always zero
// --- Effect : calls the OnFinalRelease function of our parent COXOwnThread object
{
	m_pOwnThread->OnFinalRelease();
	return 0;
}



