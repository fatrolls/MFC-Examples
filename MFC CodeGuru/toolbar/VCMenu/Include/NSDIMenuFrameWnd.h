#if !defined(AFX_SDIMENUFRAMEWND_H__2F686113_A464_11D1_B0D4_00A0C94457BF__INCLUDED_)
#define AFX_SDIMENUFRAMEWND_H__2F686113_A464_11D1_B0D4_00A0C94457BF__INCLUDED_
/*
Copyright (C) 1998 Tony Hoyle (tmh@netfusion.co.uk)

This program is free software; you can redistribute it and/or modify it under the terms
of the GNU General Public License as published by the Free Software Foundation; either
version 2 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with this program;
if not, write to the Free Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
*/

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// MDIMenuFrameWnd.h : header file
//

#include "NGenericMenu.h"

#ifndef NGTB_PROJECT
#define NGTB_EXPORT __declspec(dllimport)
#else
#define NGTB_EXPORT __declspec(dllexport)
#endif

#undef AFX_DATA
#define AFX_DATA NGTB_EXPORT

/////////////////////////////////////////////////////////////////////////////
// CNSDIMenuFrameWnd window

class CNSDIMenuFrameWnd : public CFrameWnd
{
	DECLARE_DYNAMIC(CNSDIMenuFrameWnd)
public:
	HMENU m_hDefaultMenu;
	CNGenericMenu m_wndMenu;

	NGTB_EXPORT CNSDIMenuFrameWnd();
	NGTB_EXPORT virtual ~CNSDIMenuFrameWnd();
	NGTB_EXPORT void EnableDocking(DWORD dwDockStyle);
	NGTB_EXPORT virtual BOOL LoadFrame( UINT nIDResource, DWORD dwDefaultStyle = WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, CWnd* pParentWnd = NULL, CCreateContext* pContext = NULL );
	NGTB_EXPORT virtual void DrawMenuBar() { m_wndMenu.DrawMenuBar(); }

protected:
	//{{AFX_VIRTUAL(CNSDIMenuFrameWnd)
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CNSDIMenuFrameWnd)
	NGTB_EXPORT afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	NGTB_EXPORT afx_msg LRESULT OnMenuChar(UINT nChar, UINT nFlags, CMenu* pMenu);
	NGTB_EXPORT afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#undef AFX_DATA
#define AFX_DATA

#endif // !defined(AFX_MDIMENUFRAMEWND_H__2F686113_A464_11D1_B0D4_00A0C94457BF__INCLUDED_)
