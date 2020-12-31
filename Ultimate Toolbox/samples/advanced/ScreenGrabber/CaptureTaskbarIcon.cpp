#include "stdafx.h"
#include "CaptureTaskbarIcon.h"

#include "resource.h"		// main symbols

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCaptureTaskbarIcon

BEGIN_MESSAGE_MAP(CCaptureTaskbarIcon, COXTaskbarIcon)
	//{{AFX_MSG_MAP(CCaptureTaskbarIcon)
	ON_WM_LBUTTONDBLCLK()
	ON_WM_RBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


void CCaptureTaskbarIcon::OnRButtonDown(UINT nFlags, CPoint point) 
{
	UNREFERENCED_PARAMETER(nFlags);
	UNREFERENCED_PARAMETER(point);
	// on right click show menu
	DoPopupMenu();
}

void CCaptureTaskbarIcon::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	UNREFERENCED_PARAMETER(nFlags);
	UNREFERENCED_PARAMETER(point);
	// on double click restore the position of window on screen
	::PostMessage(m_pPopupOwner->m_hWnd, WM_COMMAND, ID_OPEN, (LPARAM)m_hWnd);
}

void CCaptureTaskbarIcon::DoPopupMenu()
{
	CMenu popMenu;
	VERIFY(popMenu.LoadMenu(IDR_POPUPMENU));
	
	CPoint posMouse;
	GetCursorPos(&posMouse);
	
	// show menu
	popMenu.GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON,
		posMouse.x, posMouse.y, m_pPopupOwner);
}

