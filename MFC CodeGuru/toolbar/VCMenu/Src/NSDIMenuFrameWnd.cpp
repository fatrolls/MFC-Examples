// SDIMenuFrameWnd.cpp : implementation file
//
/*
Copyright (C) 1998 Tony Hoyle (tmh@netfusion.co.uk)

Copyright (C) 1998 George H. Stahl (GStahl@VipMail.Com)
	- Converted to CNSDIMenuFrameWnd from CMDIMenuFrameWnd

This program is free software; you can redistribute it and/or modify it under the terms
of the GNU General Public License as published by the Free Software Foundation; either
version 2 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with this program;
if not, write to the Free Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
*/

#include "stdafx.h"
#include "NSDIMenuFrameWnd.h"
#include "NGenericToolBar.h"
#include "NGenericDockBar.h"
#include "NMiniDockFrameWnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CNSDIMenuFrameWnd

CNSDIMenuFrameWnd::CNSDIMenuFrameWnd()
{
}

CNSDIMenuFrameWnd::~CNSDIMenuFrameWnd()
{
}

IMPLEMENT_DYNAMIC(CNSDIMenuFrameWnd, CFrameWnd)

BEGIN_MESSAGE_MAP(CNSDIMenuFrameWnd, CFrameWnd)
	//{{AFX_MSG_MAP(CNSDIMenuFrameWnd)
	ON_WM_CREATE()
	ON_WM_MENUCHAR()
	ON_WM_ACTIVATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CNSDIMenuFrameWnd message handlers

int CNSDIMenuFrameWnd::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	m_hDefaultMenu=*GetMenu();
	SetMenu(NULL);

	if(!m_wndMenu.Create(this) ||
	   !m_wndMenu.SetMenu(m_hDefaultMenu))
	{
		TRACE0("CNSDIMenuFrameWnd: Failed to create menu\n");
		return -1;
	}

	m_wndMenu.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndMenu);
	return 0;
}

LRESULT CNSDIMenuFrameWnd::OnMenuChar(UINT nChar, UINT nFlags, CMenu* pMenu) 
{
	for(int n=0; n<CNGenericToolBar::m_ToolbarList.GetSize(); n++)
	{
		if(CNGenericToolBar::m_ToolbarList[n]->TranslateMenuChar(nChar))
			return MAKELPARAM(MNC_EXECUTE,-1); // Handled by toolbar
	}
	return CFrameWnd::OnMenuChar(nChar, nFlags, pMenu);
}


void CNSDIMenuFrameWnd::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized) 
{
	if(nState==WA_INACTIVE && pWndOther && pWndOther->IsKindOf(RUNTIME_CLASS(CNGenericPopup)))
		return; // Dump the message
	CFrameWnd::OnActivate(nState, pWndOther, bMinimized);
}

// dock bars will be created in the order specified by dwDockBarMap
// this also controls which gets priority during layout
// this order can be changed by calling EnableDocking repetitively
// with the exact order of priority
void CNSDIMenuFrameWnd::EnableDocking(DWORD dwDockStyle)
{
	// must be CBRS_ALIGN_XXX or CBRS_FLOAT_MULTI only
	ASSERT((dwDockStyle & ~(CBRS_ALIGN_ANY|CBRS_FLOAT_MULTI)) == 0);

	m_pFloatingFrameClass = RUNTIME_CLASS(CNMiniDockFrameWnd);
	for (int i = 0; i < 4; i++)
	{
		if (dwDockBarMap[i][1] & dwDockStyle & CBRS_ALIGN_ANY)
		{
			CDockBar* pDock = (CDockBar*)GetControlBar(dwDockBarMap[i][0]);
			if (pDock == NULL)
			{
				pDock = new CNGenericDockBar;
				if (!pDock->Create(this,
					WS_CLIPSIBLINGS|WS_CLIPCHILDREN|WS_CHILD|WS_VISIBLE |
						dwDockBarMap[i][1], dwDockBarMap[i][0]))
				{
					AfxThrowResourceException();
				}
			}
		}
	} 
}

BOOL CNSDIMenuFrameWnd::LoadFrame(UINT nIDResource, DWORD dwDefaultStyle,
	CWnd* pParentWnd, CCreateContext* pContext)
{
	if (!CFrameWnd::LoadFrame(nIDResource, dwDefaultStyle,
	  pParentWnd, pContext))
		return FALSE;

	// save menu to use when no active MDI child window is present
	ASSERT(m_hWnd != NULL);
	m_hMenuDefault = ::GetMenu(m_hWnd);

// This fixes a *nasty* MFC bug
// Someone at MS forgot that this would compile differently in release...
#ifdef _DEBUG
	if (m_hMenuDefault == NULL)
		TRACE0("Warning: CFrameWnd without a default menu.\n");
#endif
	return TRUE;
}


