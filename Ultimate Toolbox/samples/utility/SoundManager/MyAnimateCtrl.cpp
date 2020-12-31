// MyAnimateCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "SoundManager.h"
#include "MyAnimateCtrl.h"

#include "OXHookWnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyAnimateCtrl

CMyAnimateCtrl::CMyAnimateCtrl()
{
}

CMyAnimateCtrl::~CMyAnimateCtrl()
{
}


BEGIN_MESSAGE_MAP(CMyAnimateCtrl, CAnimateCtrl)
	//{{AFX_MSG_MAP(CMyAnimateCtrl)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
    ON_MESSAGE(HWM_MOUSEENTER, OnMouseEnter)
    ON_MESSAGE(HWM_MOUSELEAVE, OnMouseLeave)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyAnimateCtrl message handlers

LONG CMyAnimateCtrl::OnMouseEnter(WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(wParam);
	UNREFERENCED_PARAMETER(lParam);

	Play(0,(UINT)-1,1);

	return (LONG)0;
}

LONG CMyAnimateCtrl::OnMouseLeave(WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(wParam);
	UNREFERENCED_PARAMETER(lParam);

	return (LONG)0;
}
