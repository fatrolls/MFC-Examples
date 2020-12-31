// SpawnMDIChildWnd.cpp : implementation file
//

#include "stdafx.h"
#include "ToolbarMenuDemoMDI.h"
#include "SpawnMDIChildWnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSpawnMDIChildWnd

IMPLEMENT_DYNCREATE(CSpawnMDIChildWnd, CMDIChildWnd)

CSpawnMDIChildWnd::CSpawnMDIChildWnd()
{
}

CSpawnMDIChildWnd::~CSpawnMDIChildWnd()
{
}


BEGIN_MESSAGE_MAP(CSpawnMDIChildWnd, CMDIChildWnd)
	//{{AFX_MSG_MAP(CSpawnMDIChildWnd)
	ON_WM_DRAWITEM()
	ON_WM_MEASUREITEM()
	ON_WM_INITMENUPOPUP()
	ON_WM_MENUCHAR()
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSpawnMDIChildWnd message handlers

void CSpawnMDIChildWnd::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	if (!cSpawn.DrawItem(lpDrawItemStruct))
		CMDIChildWnd::OnDrawItem(nIDCtl, lpDrawItemStruct);
}

void CSpawnMDIChildWnd::OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct) 
{
	if (!cSpawn.MeasureItem(lpMeasureItemStruct))
		CMDIChildWnd::OnMeasureItem(nIDCtl, lpMeasureItemStruct);
}

void CSpawnMDIChildWnd::OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu) 
{
	CMDIChildWnd::OnInitMenuPopup(pPopupMenu, nIndex, bSysMenu);
	cSpawn.RemapMenu(pPopupMenu);	
}

LRESULT CSpawnMDIChildWnd::OnMenuChar(UINT nChar, UINT nFlags, CMenu* pMenu) 
{
	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL && pSysMenu->GetSafeHmenu() == pMenu->GetSafeHmenu())
	{
		LRESULT lRes = 0;
		cSpawn.FindKeyboardShortcut(nChar, nFlags, pMenu, lRes);
		return lRes;
	}
	return CMDIChildWnd::OnMenuChar(nChar, nFlags, pMenu);
}

int CSpawnMDIChildWnd::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CMDIChildWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	return 0;
}
