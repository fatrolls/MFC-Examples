// MyToolTipCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "GridDemo.h"
#include "MyToolTipCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyToolTipCtrl

CMyToolTipCtrl::CMyToolTipCtrl()
{
}

CMyToolTipCtrl::~CMyToolTipCtrl()
{
}


BEGIN_MESSAGE_MAP(CMyToolTipCtrl, CToolTipCtrl)
	//{{AFX_MSG_MAP(CMyToolTipCtrl)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyToolTipCtrl message handlers

BOOL CMyToolTipCtrl::AddWindowTool(CWnd *pWnd, LPCTSTR pszText)
{
    TOOLINFO ti;
    ti.cbSize = sizeof (TOOLINFO);
    ti.uFlags = TTF_IDISHWND | TTF_SUBCLASS;
    ti.hwnd = pWnd->GetParent ()->GetSafeHwnd ();
    ti.uId = (UINT) pWnd->GetSafeHwnd ();
    ti.hinst = AfxGetInstanceHandle ();
    ti.lpszText = (LPTSTR) pszText;

    return (BOOL) SendMessage (TTM_ADDTOOL, 0, (LPARAM) &ti);
}

BOOL CMyToolTipCtrl::AddRectTool(CWnd *pWnd, LPCTSTR pszText, LPCRECT pRect, UINT nIDTool)
{
    TOOLINFO ti;
    ti.cbSize = sizeof (TOOLINFO);
    ti.uFlags = TTF_SUBCLASS;
    ti.hwnd = pWnd->GetSafeHwnd ();
    ti.uId = nIDTool;
    ti.hinst = AfxGetInstanceHandle ();
    ti.lpszText = (LPTSTR) pszText;
    ::CopyRect (&ti.rect, pRect);

    return (BOOL) SendMessage (TTM_ADDTOOL, 0, (LPARAM) &ti);
}
