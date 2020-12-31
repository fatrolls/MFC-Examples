// SpawnMDIFrameWnd.cpp : implementation file
//

#include "stdafx.h"
#include "ToolbarMenuDemoMDI.h"
#include "SpawnMDIFrameWnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// 3D HIGHLIGHT CODE
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
// 3D HIGHLIGHT CODE END

/////////////////////////////////////////////////////////////////////////////
// CSpawnMDIFrameWnd

IMPLEMENT_DYNCREATE(CSpawnMDIFrameWnd, CMDIFrameWnd)

CSpawnMDIFrameWnd::CSpawnMDIFrameWnd()
{
// 3D HIGHLIGHT CODE
	oldMenuBarRc.SetRect(0,0,0,0);
	bMenuLooping = false;
	uiTimerId = 0;
// 3D HIGHLIGHT CODE END
}

CSpawnMDIFrameWnd::~CSpawnMDIFrameWnd()
{
}


BEGIN_MESSAGE_MAP(CSpawnMDIFrameWnd, CMDIFrameWnd)
	//{{AFX_MSG_MAP(CSpawnMDIFrameWnd)
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
// CSpawnMDIFrameWnd message handlers

void CSpawnMDIFrameWnd::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	if (!cSpawn.DrawItem(lpDrawItemStruct))
		CMDIFrameWnd::OnDrawItem(nIDCtl, lpDrawItemStruct);
}

void CSpawnMDIFrameWnd::OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct) 
{
	if (!cSpawn.MeasureItem(lpMeasureItemStruct))
		CMDIFrameWnd::OnMeasureItem(nIDCtl, lpMeasureItemStruct);
}

void CSpawnMDIFrameWnd::OnInitMenu(CMenu* pMenu) 
{
	cSpawn.RemapMenu(pMenu);	
	CMDIFrameWnd::OnInitMenu(pMenu);
}

void CSpawnMDIFrameWnd::OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu) 
{
	cSpawn.RemapMenu(pPopupMenu);
	CMDIFrameWnd::OnInitMenuPopup(pPopupMenu, nIndex, bSysMenu);
}

LRESULT CSpawnMDIFrameWnd::OnMenuChar(UINT nChar, UINT nFlags, CMenu* pMenu) 
{
	LRESULT lRes = CMDIFrameWnd::OnMenuChar(nChar, nFlags, pMenu);
	if (nFlags != MF_SYSMENU)
	{
		if (HIWORD(lRes) != 2) cSpawn.FindKeyboardShortcut(nChar, nFlags, pMenu, lRes);
	}
	return lRes;
}

// 3D HIGHLIGHT CODE
UINT CSpawnMDIFrameWnd::OnNcHitTest(CPoint point) 
{
	UINT res = CMDIFrameWnd::OnNcHitTest(point);
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

void CSpawnMDIFrameWnd::OnTimer(UINT nIDEvent) 
{
	if (uiTimerId == nIDEvent && !bMenuLooping)
	{
		CPoint pt;
		GetCursorPos(&pt);
		LRESULT res = SendMessage(WM_NCHITTEST, 0, MAKELONG(pt.x, pt.y));
	}
	CMDIFrameWnd::OnTimer(nIDEvent);
}

void CSpawnMDIFrameWnd::OnEnterMenuLoop(BOOL bIsTrackPopupMenu)
{
	if (!(oldMenuBarRc.IsRectEmpty()))
	{
		CWindowDC dc(this);
		dc.Draw3dRect(oldMenuBarRc,cSpawn.crMenu, cSpawn.crMenu);
		oldMenuBarRc.SetRect(0,0,0,0);
	}

	bMenuLooping = true;
}

void CSpawnMDIFrameWnd::OnExitMenuLoop(BOOL bIsTrackPopupMenu)
{
	bMenuLooping = false;
}

int CSpawnMDIFrameWnd::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	uiTimerId = GfxSetSafeTimer(this, 100);
	
	return 0;
}

void CSpawnMDIFrameWnd::OnDestroy() 
{
	if (uiTimerId) KillTimer(uiTimerId);
	CMDIFrameWnd::OnDestroy();
}
// 3D HIGHLIGHT CODE END