// NGenericMenu.h: interface for the CNGenericMenu class.
//
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
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_NGENERICMENU_H__F5167101_A3AF_11D1_B0D4_00A0C94457BF__INCLUDED_)
#define AFX_NGENERICMENU_H__F5167101_A3AF_11D1_B0D4_00A0C94457BF__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "NGenericToolBar.h"
#include "NGenericPopup.h"

#ifndef NGTB_PROJECT
#define NGTB_EXPORT __declspec(dllimport)
#else
#define NGTB_EXPORT __declspec(dllexport)
#endif

#undef AFX_DATA
#define AFX_DATA NGTB_EXPORT

///////////////////////////////////////////////////////////////////////////
// Class styles to be used by client applications
///////////////////////////////////////////////////////////////////////////

class CNGenericMenu : public CNGenericToolBar  
{
	DECLARE_DYNAMIC(CNGenericMenu)
public:
	NGTB_EXPORT CNGenericMenu();
	NGTB_EXPORT virtual ~CNGenericMenu();
	NGTB_EXPORT BOOL Create(CFrameWnd* pParent);
	NGTB_EXPORT BOOL SetMenu(HMENU hMenu);
	NGTB_EXPORT BOOL SetMenu(UINT idMenu) { CMenu m; m.LoadMenu(idMenu); return SetMenu(m.Detach()); }
	NGTB_EXPORT BOOL DrawMenuBar();
protected:
	CFrameWnd* m_pParent;
	HMENU m_hMenu;
	CNGenericPopup m_popup;
	BOOL m_bItemDropped;
	int m_iItem;

	void ShowDropDown(BOOL bFromKey, int iItem);
	virtual BOOL TranslateMenuChar(UINT nChar);
	virtual BOOL KeyboardFilter(UINT nChar, UINT nRepCnt, UINT nFlags);
	virtual CSize CalcFixedLayout(BOOL bStretch, BOOL bHorz);
	virtual void OnOverSysMenu();

protected:
	//{{AFX_MSG(CNGenericMenu)
	afx_msg void OnNcPaint();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	//}}AFX_MSG
	afx_msg void	OnDropDown(NMHDR * pNotifyStruct, LRESULT* result);
	afx_msg void	OnHotChange(NMHDR * pNotifyStruct, LRESULT* result);
	afx_msg void	OnMenuUpdate(CCmdUI* pCmd);
	afx_msg LRESULT OnDismiss(WPARAM wParam, LPARAM lParam);
	afx_msg void	OnIdleUpdateCmdUI();

	DECLARE_MESSAGE_MAP()
};

class CNMDIGenericMenu : public CNGenericMenu  
{
	DECLARE_DYNAMIC(CNMDIGenericMenu)
public:
	NGTB_EXPORT void SubclassMDIClient(HWND hWndClient);

};

#undef AFX_DATA
#define AFX_DATA

#endif // !defined(AFX_NGENERICMENU_H__F5167101_A3AF_11D1_B0D4_00A0C94457BF__INCLUDED_)
