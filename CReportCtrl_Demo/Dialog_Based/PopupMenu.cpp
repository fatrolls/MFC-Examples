#include "stdafx.h"

void CmdRouteMenu(CWnd* pWnd,CMenu* pPopupMenu)
{
	CCmdUI state;
	state.m_pMenu = pPopupMenu;
	state.m_pParentMenu = pPopupMenu;
	state.m_nIndexMax = pPopupMenu->GetMenuItemCount();

	for (state.m_nIndex = 0; 
	     state.m_nIndex < state.m_nIndexMax; 
	     state.m_nIndex++) 
	{
		state.m_nID = pPopupMenu->GetMenuItemID(state.m_nIndex);

		// menu separator or invalid cmd - ignore it
		if (state.m_nID == 0) continue; 

		if (state.m_nID == (UINT)-1)
		{
			// possibly a popup menu, route to child menu if so
			CMenu* pSub=pPopupMenu->GetSubMenu(state.m_nIndex);
			if(pSub) CmdRouteMenu(pWnd,pSub);
		}
		else 
		{
			// normal menu item, Auto disable if command is 
			// _not_ a system command.
			state.m_pSubMenu = NULL;
			state.DoUpdate(pWnd, FALSE);
		}
	}
}

BOOL PopupMenu(CMenu* pPopupMenu, CWnd* pParentWnd)
{
	CmdRouteMenu(pParentWnd, pPopupMenu);
	POINT pt;
	::GetCursorPos(&pt);
	if (pParentWnd != NULL)
		pParentWnd->SetForegroundWindow();
	BOOL bRes = pPopupMenu->TrackPopupMenu(TPM_RIGHTBUTTON, pt.x, pt.y, pParentWnd, NULL);
	if (pParentWnd != NULL)
		pParentWnd->PostMessage(WM_NULL, 0, 0);
	return bRes;
}

BOOL PopupMenu(UINT nMenuID, UINT nSubMenuPos, CWnd* pParentWnd)
{
	CMenu menu;
	if (!menu.LoadMenu(nMenuID))
		return FALSE;

	CMenu* pSub = menu.GetSubMenu(nSubMenuPos);
	if (pSub == NULL)
		return FALSE;

	return PopupMenu(pSub, pParentWnd);
}
