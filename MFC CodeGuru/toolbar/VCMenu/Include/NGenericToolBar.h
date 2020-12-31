// NGenericToolBar.h: interface for the CNGenericToolBar class.
//
/*
Copyright (C) 1998 Tony Hoyle (tmh@netfusion.co.uk)

Copyright (C) 1998 George H. Stahl (GStahl@VipMail.Com)
	- Added GenericToolBarModifyStyle

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

#if !defined(AFX_NGENERICTOOLBAR_H__DE1A2044_A20C_11D1_87DF_00A0C94457BF__INCLUDED_)
#define AFX_NGENERICTOOLBAR_H__DE1A2044_A20C_11D1_87DF_00A0C94457BF__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef NGTB_PROJECT
#define NGTB_EXPORT __declspec(dllimport)
#else
#define NGTB_EXPORT __declspec(dllexport)
#endif

#undef AFX_DATA
#define AFX_DATA NGTB_EXPORT

// Command IDs.  These should really be in resource.h
#define IDM_BUTTONSONLY                 52700
#define IDM_BUTTONSANDTEXT              52701
#define IDM_TEXTONLY                    52702
#define IDM_RECALCSIZE                  52703

#define NGTB_NO_SYSMENU			0x0002L

class CNGenericToolBar : public CToolBar  
{
	friend class CNMDIMenuFrameWnd;
	friend class CNSDIMenuFrameWnd;
	friend class CNGenericPopup;
	DECLARE_DYNAMIC(CNGenericToolBar)
public:
	NGTB_EXPORT CNGenericToolBar();
	NGTB_EXPORT virtual ~CNGenericToolBar();

	// Compatibility with CToolBar
	NGTB_EXPORT BOOL Create( CWnd* pParentWnd, DWORD dwStyle = WS_CHILD | WS_VISIBLE | CBRS_TOP,
		UINT nID = AFX_IDW_TOOLBAR ) { return CreateEx(pParentWnd,TBSTYLE_FLAT|TBSTYLE_TRANSPARENT,dwStyle|CBRS_SIZE_DYNAMIC,nID); }

	// Our stuff
	NGTB_EXPORT BOOL CreateEx(CWnd* pParentWnd, DWORD dwExStyle = TBSTYLE_FLAT | TBSTYLE_TRANSPARENT,
		DWORD dwStyle = WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_SIZE_DYNAMIC,
		UINT nID = AFX_IDW_TOOLBAR, LPCTSTR szTitle = NULL);

	NGTB_EXPORT static void SetVisualState(BOOL bButtons, BOOL bText);
	NGTB_EXPORT BOOL GetVisualState(BOOL bText);

	// CToolBar implementation changes
	NGTB_EXPORT BOOL LoadToolBar(LPCTSTR lpszResourceName);
	NGTB_EXPORT BOOL LoadToolBar(UINT nIDResource) { return LoadToolBar(MAKEINTRESOURCE(nIDResource)); }
	NGTB_EXPORT BOOL SetButtonText(int nIndex, LPCTSTR lpszText);
	NGTB_EXPORT BOOL GenericToolBarModifyStyle(DWORD dwRemove, DWORD dwAdd);
	NGTB_EXPORT DWORD GetGenericToolBarStyle(){return m_dwGenericToolBarStyle;}
protected:
	// Styles
	DWORD m_dwGenericToolBarStyle;

	struct Accel { UINT nKey; UINT nId; };
	CMenu m_pop;
	BOOL m_bHasText,m_bHasBitmaps,m_bForceText;
	CArray<int,int> m_TextIds;
	CArray<Accel,Accel&> m_accelList;
	CWnd* m_pParent;
	static BOOL m_bButtons;
	static BOOL m_bText;
	BOOL m_bSysMenuIcon; // Used by menu to draw icon
	HICON m_hSysMenuIcon; // Icon to draw for above
	CRect m_rectSysMenu; // Where we drew it
	static CArray<CNGenericToolBar*,CNGenericToolBar*> m_ToolbarList;

	virtual void SettingChange();
	BOOL RecalcSize();
	static void SendToAllToolbars(UINT uMsg, WPARAM wParam = NULL, LPARAM lParam = NULL);
	void _SetButton(int nIndex, TBBUTTON* pButton);
	void DrawGripper(CWindowDC *pDC, CRect& rectWindow);
	void DrawSysMenuIcon(CWindowDC* pDC, CRect& rectWindow);
	void EraseNonClient(BOOL bRaised);
	void DrawBorders(CDC* pDC, CRect& rect);
	void RepaintBackground();
	void DrawSeparators();
	void DrawSeparators(CClientDC* pDC);
	virtual BOOL TranslateMenuChar(UINT nChar);
	virtual BOOL KeyboardFilter(UINT nChar, UINT nRepCnt, UINT nFlags);
	virtual void OnUpdateCmdUI(CFrameWnd* pTarget, BOOL bDisableIfNoHndler);
	virtual void OnOverSysMenu() { };

protected:
	//{{AFX_MSG(CNGenericToolBar)
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnDestroy();
	afx_msg UINT OnNcHitTest(CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	afx_msg void OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS* lpncsp);
	afx_msg void OnButtonsOnly();
	afx_msg void OnTextOnly();
	afx_msg void OnTextAndButtons();
	afx_msg void OnRecalcSize();
	afx_msg void OnNcPaint();
	afx_msg void OnWindowPosChanging(LPWINDOWPOS lpWndPos);
	afx_msg void OnPaint();
};

#undef AFX_DATA
#define AFX_DATA

#endif // !defined(AFX_NGENERICTOOLBAR_H__DE1A2044_A20C_11D1_87DF_00A0C94457BF__INCLUDED_)
