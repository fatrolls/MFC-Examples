// SpawnFrameWnd.cpp : implementation file
//

#include "stdafx.h"
#include "ToolbarMenuDemoMDI.h"
#include "SpawnFrameWnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSpawnFrameWnd
extern UINT GfxSetSafeTimer(CWnd * pWnd, const UINT uiElapse);

/*
Function to set a timer; defined in SpawnMDIFrameWnd.cpp; if you include this file and not
the other, uncomment this:

UINT GfxSetSafeTimer(CWnd * pWnd, const UINT uiElapse)
{
	ASSERT(pWnd && pWnd->GetSafeHwnd());
	UINT iTimer = 1;
	while (iTimer < 10000)
	{
		UINT res = pWnd->SetTimer(1, uiElapse, NULL);
		if (res) return res;
		iTimer ++;
	}
	return 0;
}
*/

IMPLEMENT_DYNCREATE(CSpawnFrameWnd, CFrameWnd)

CSpawnFrameWnd::CSpawnFrameWnd()
{
	oldMenuBarRc.SetRect(0,0,0,0);
	bMenuLooping = false;
	uiTimerId = 0;
}

CSpawnFrameWnd::~CSpawnFrameWnd()
{
}


BEGIN_MESSAGE_MAP(CSpawnFrameWnd, CFrameWnd)
	//{{AFX_MSG_MAP(CSpawnFrameWnd)
	ON_WM_DRAWITEM()
	ON_WM_MEASUREITEM()
	ON_WM_INITMENU()
	ON_WM_INITMENUPOPUP()
	ON_WM_MENUCHAR()
	ON_WM_NCHITTEST()
	ON_WM_TIMER()
	ON_WM_CREATE()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
	ON_WM_ENTERMENULOOP()
	ON_WM_EXITMENULOOP()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSpawnFrameWnd message handlers

void CSpawnFrameWnd::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	if (!cSpawn.DrawItem(lpDrawItemStruct))
		CFrameWnd::OnDrawItem(nIDCtl, lpDrawItemStruct);
}

void CSpawnFrameWnd::OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct) 
{
	if (!cSpawn.MeasureItem(lpMeasureItemStruct))
		CFrameWnd::OnMeasureItem(nIDCtl, lpMeasureItemStruct);
}

void CSpawnFrameWnd::OnInitMenu(CMenu* pMenu) 
{
	CFrameWnd::OnInitMenu(pMenu);
	cSpawn.RemapMenu(pMenu);	
}

void CSpawnFrameWnd::OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu) 
{
	CFrameWnd::OnInitMenuPopup(pPopupMenu, nIndex, bSysMenu);
	cSpawn.RemapMenu(pPopupMenu);
}

LRESULT CSpawnFrameWnd::OnMenuChar(UINT nChar, UINT nFlags, CMenu* pMenu) 
{
	LRESULT lRes;
	if (!cSpawn.FindKeyboardShortcut(nChar, nFlags, pMenu, lRes)) 
		lRes = CFrameWnd::OnMenuChar(nChar, nFlags, pMenu);
	return lRes;
}

UINT CSpawnFrameWnd::OnNcHitTest(CPoint point) 
{
	UINT res = CFrameWnd::OnNcHitTest(point);
	if (!bMenuLooping && res == HTMENU)
	{
		CMenu * pMenu = GetMenu();
		ASSERT(pMenu);

		UINT mifp = MenuItemFromPoint(GetSafeHwnd(), pMenu->GetSafeHmenu(), point);
		if (mifp != (UINT) -1)
		{
			CRect rc, wrc;
			if (GetMenuItemRect(GetSafeHwnd(), pMenu->GetSafeHmenu(), mifp, &rc))
			{
				if (cSpawn.IsSpawnMenu(pMenu, mifp, true))
				{
					GetWindowRect(wrc);
					rc.top -= wrc.top;
					rc.bottom -= wrc.top;
					rc.left -= wrc.left;
					rc.right -= wrc.left;
					if (oldMenuBarRc != rc || oldMenuBarRc.IsRectEmpty())
					{
						CWindowDC dc(this);
						if (!(oldMenuBarRc.IsRectEmpty()))
						{
							dc.Draw3dRect(oldMenuBarRc,cSpawn.crMenu, cSpawn.crMenu);
						}
						dc.Draw3dRect(rc,cSpawn.cr3dHilight, cSpawn.cr3dShadow);
						oldMenuBarRc = rc;
					}
				}
				else
				{
					if (!(oldMenuBarRc.IsRectEmpty()))
					{
						CWindowDC dc(this);
						dc.Draw3dRect(oldMenuBarRc,cSpawn.crMenu, cSpawn.crMenu);
						oldMenuBarRc.SetRect(0,0,0,0);
					}
				}
			}
		}
	}
	else
	{
		if (!(oldMenuBarRc.IsRectEmpty()))
		{
			CWindowDC dc(this);
			dc.Draw3dRect(oldMenuBarRc,cSpawn.crMenu, cSpawn.crMenu);
			oldMenuBarRc.SetRect(0,0,0,0);
		}
	}
	
	return res;
}

void CSpawnFrameWnd::OnTimer(UINT nIDEvent) 
{
	if (uiTimerId == nIDEvent && !bMenuLooping)
	{
		CPoint pt;
		GetCursorPos(&pt);
		LRESULT res = SendMessage(WM_NCHITTEST, 0, MAKELONG(pt.x, pt.y));
	}
	
	CFrameWnd::OnTimer(nIDEvent);
}

void CSpawnFrameWnd::OnEnterMenuLoop(BOOL bIsTrackPopupMenu)
{
	if (!(oldMenuBarRc.IsRectEmpty()))
	{
		CWindowDC dc(this);
		dc.Draw3dRect(oldMenuBarRc,cSpawn.crMenu, cSpawn.crMenu);
		oldMenuBarRc.SetRect(0,0,0,0);
	}

	bMenuLooping = true;
}

void CSpawnFrameWnd::OnExitMenuLoop(BOOL bIsTrackPopupMenu)
{
	bMenuLooping = false;
}

int CSpawnFrameWnd::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	uiTimerId = GfxSetSafeTimer(this, 100);
	
	return 0;
}

void CSpawnFrameWnd::OnDestroy() 
{
	if (uiTimerId) KillTimer(uiTimerId);
	CFrameWnd::OnDestroy();
}
