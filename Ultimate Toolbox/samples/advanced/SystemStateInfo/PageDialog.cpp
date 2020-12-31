// PageDialog.cpp : implementation file
//

#include "stdafx.h"
#include "PageDialog.h"

#include <afxpriv.h>
#ifndef __OXMFCIMPL_H__
#if _MFC_VER >= 0x0700
	#include <..\src\mfc\afximpl.h>
#else
	#include <..\src\afximpl.h>
#endif
#define __OXMFCIMPL_H__
#endif


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPageDialog dialog


BEGIN_MESSAGE_MAP(CPageDialog, CWnd)
	//{{AFX_MSG_MAP(CPageDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPageDialog message handlers

// virtual override of CWnd::Create
BOOL CPageDialog::Create(LPCTSTR lpszTemplateName, CWnd* pParentWnd, CRect rect, 
						 UINT nID, DWORD dwStyle/*=WS_VISIBLE|WS_CHILD*/)
{
	ASSERT(pParentWnd!=NULL);
	ASSERT(lpszTemplateName!=NULL);

	// initialize common controls
	VERIFY(AfxDeferRegisterClass(AFX_WNDCOMMCTLS_REG));

	// call PreCreateWindow to get prefered extended style
	CREATESTRUCT cs={ 0 };
	cs.style=dwStyle;
	if(!PreCreateWindow(cs))
		return FALSE;

	// create a modeless dialog
	if (!CreateDlg(lpszTemplateName, pParentWnd))
		return FALSE;

	// we use the style from the template - but make sure that
	//  the WS_BORDER bit is correct
	// the WS_BORDER bit will be whatever is in dwRequestedStyle
	ModifyStyle(WS_BORDER|WS_CAPTION,(cs.style&(WS_BORDER|WS_CAPTION))|WS_CHILD);
	ModifyStyleEx(WS_EX_CLIENTEDGE,(cs.dwExStyle&WS_EX_CLIENTEDGE));

	SetDlgCtrlID(nID);

	// initialize controls etc
	if (!ExecuteDlgInit(lpszTemplateName))
		return FALSE;

	OnInitDialog();

	// force the size requested
	SetWindowPos(NULL, rect.left, rect.top,
		rect.right - rect.left, rect.bottom - rect.top,
		SWP_NOZORDER|SWP_NOACTIVATE);

	// make visible if requested
	if (dwStyle & WS_VISIBLE)
		ShowWindow(SW_NORMAL);

	return TRUE;
}


