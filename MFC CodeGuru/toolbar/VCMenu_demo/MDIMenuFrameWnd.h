#if !defined(AFX_MDIMENUFRAMEWND_H__2F686113_A464_11D1_B0D4_00A0C94457BF__INCLUDED_)
#define AFX_MDIMENUFRAMEWND_H__2F686113_A464_11D1_B0D4_00A0C94457BF__INCLUDED_
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

/////////////////////////////////////////////////////////////////////////////
// CMDIMenuFrameWnd window

class CMDIMenuFrameWnd : public CMDIFrameWnd
{
	DECLARE_DYNAMIC(CMDIMenuFrameWnd)
// Construction
public:
	CMDIMenuFrameWnd();

// Attributes
public:
	HMENU m_hDefaultMenu;
	CNGenericMenu m_wndMenu;

	void EnableDocking(DWORD dwDockStyle);
	virtual BOOL LoadFrame( UINT nIDResource, DWORD dwDefaultStyle = WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, CWnd* pParentWnd = NULL, CCreateContext* pContext = NULL );


// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMDIMenuFrameWnd)
	protected:
	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMDIMenuFrameWnd();

	// Generated message map functions
protected:
	//{{AFX_MSG(CMDIMenuFrameWnd)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg LRESULT OnMenuChar(UINT nChar, UINT nFlags, CMenu* pMenu);
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MDIMENUFRAMEWND_H__2F686113_A464_11D1_B0D4_00A0C94457BF__INCLUDED_)
