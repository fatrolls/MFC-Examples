#include "stdafx.h"
#include "SSITaskbarIcon.h"

#include "resource.h"		// main symbols

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSSITaskbarIcon

BEGIN_MESSAGE_MAP(CSSITaskbarIcon, COXTaskbarIcon)
	//{{AFX_MSG_MAP(CSSITaskbarIcon)
	ON_WM_LBUTTONDBLCLK()
	ON_WM_RBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


void CSSITaskbarIcon::OnRButtonUp(UINT nFlags, CPoint point) 
{
	UNREFERENCED_PARAMETER(nFlags);
	UNREFERENCED_PARAMETER(point);
	// on right click show menu
	DoPopupMenu();
}

void CSSITaskbarIcon::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	UNREFERENCED_PARAMETER(nFlags);
	UNREFERENCED_PARAMETER(point);
	// on double click restore the position of window on screen
	::PostMessage(m_pPopupOwner->m_hWnd, WM_COMMAND, IDM_RESTORE, (LPARAM)m_hWnd);
}

void CSSITaskbarIcon::DoPopupMenu()
{
	CMenu popMenu;
	VERIFY(popMenu.LoadMenu(IDR_TRAYICON_POPUPMENU));

	// set default item
	MENUITEMINFO itemInfo={ sizeof(MENUITEMINFO) };
	itemInfo.fMask=MIIM_STATE;
	itemInfo.fState=MFS_DEFAULT;
	::SetMenuItemInfo(popMenu.m_hMenu,IDM_RESTORE,FALSE,&itemInfo);
	
	CPoint posMouse;
	GetCursorPos(&posMouse);
	
	// show menu
	m_pPopupOwner->SendMessage(WM_NCACTIVATE,FALSE);
	popMenu.GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON,
		posMouse.x, posMouse.y, m_pPopupOwner);
}

