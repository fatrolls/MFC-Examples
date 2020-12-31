
#include "stdafx.h"
#include "DemoTaskbarIcon.h"

#include "resource.h"		// main symbols

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDemoTaskbarIcon

BEGIN_MESSAGE_MAP(CDemoTaskbarIcon, COXTaskbarIcon)
	//{{AFX_MSG_MAP(CDemoTaskbarIcon)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_RBUTTONDOWN()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


void CDemoTaskbarIcon::OnLButtonDown(UINT nFlags, CPoint point) 
{
	UNREFERENCED_PARAMETER(point);
	UNREFERENCED_PARAMETER(nFlags);
	SetTimer(IDT_TIMER, 500, (TIMERPROC) NULL);
	// half sec should be enough to tell a dblclk from a single clk
}

void CDemoTaskbarIcon::OnRButtonDown(UINT nFlags, CPoint point) 
{
	UNREFERENCED_PARAMETER(point);
	UNREFERENCED_PARAMETER(nFlags);
	// no dbl in our way, no need to implement a timer
	CString sMenuText = _T("WM_RBUTTONDOWN");
	DoPopupMenu(sMenuText);
}

void CDemoTaskbarIcon::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	UNREFERENCED_PARAMETER(point);
	UNREFERENCED_PARAMETER(nFlags);
	m_bDownFromDlbClk = TRUE;
	::PostMessage(m_pPopupOwner->m_hWnd, WM_COMMAND, ID_OPEN, (LPARAM)m_hWnd);
}

void CDemoTaskbarIcon::DoPopupMenu(LPCTSTR sDemoMenuText)
{
	CMenu popMenu;
	VERIFY(popMenu.LoadMenu(IDR_POPUPMENU));
	
	// show mouse msg in the menu text
	popMenu.ModifyMenu(ID_POPUP_MOUSEMSG, MF_BYCOMMAND, ID_POPUP_MOUSEMSG, sDemoMenuText);

	CPoint posMouse;
	GetCursorPos(&posMouse);
	
	m_pPopupOwner->SetActiveWindow();
	popMenu.GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON,
		posMouse.x, posMouse.y, m_pPopupOwner);
}

void CDemoTaskbarIcon::OnTimer(UINT nIDEvent) 
{
	KillTimer(nIDEvent);

	if (m_bDownFromDlbClk)
	{
		m_bDownFromDlbClk = FALSE;
	}
	else
	{
		CString sMenuText = _T("WM_LBUTTONDOWN");
		DoPopupMenu(sMenuText);
	}
}
