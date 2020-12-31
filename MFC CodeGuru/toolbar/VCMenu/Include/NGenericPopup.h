#if !defined(AFX_NGENERICPOPUP_H__AD9E2C63_A3B6_11D1_B0D4_00A0C94457BF__INCLUDED_)
#define AFX_NGENERICPOPUP_H__AD9E2C63_A3B6_11D1_B0D4_00A0C94457BF__INCLUDED_
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
// NGenericPopup.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNGenericPopup window

class CNGenericToolBar;

class CNGenericPopup : public CWnd
{
	DECLARE_DYNAMIC(CNGenericPopup);
public:
	CNGenericPopup();
	virtual ~CNGenericPopup();

	BOOL ShowMenu(int nOrient, BOOL bFromKey, CNGenericToolBar* pToolbar, int x, int y, CWnd* pParent, HMENU hMenu);
	BOOL HideMenu();
	BOOL KeyboardFilter(UINT nChar, UINT nRepCnt, UINT nFlags);

protected:
	CWnd* m_pParent;
	CNGenericToolBar* m_pToolbar;
	CMenu* m_pMenu;
	CBitmap m_tick;
	CSize m_sztick;
	CArray<CRect,CRect&> m_rectItem;
	int m_nSelectedItem;
	BOOL m_bMouseInMenu;
	BOOL m_nOrient;
	struct Accel { UINT nKey; UINT nId; };
	CArray<Accel,Accel&> m_accelList;

	CSize DrawMenuItem(int nItem, CDC& dc, const CRect& rect, BOOL bHighlight, BOOL bReallyDraw);
	void SelectItem(int nItem);
	BOOL TranslateMenuChar(UINT nChar);

protected:
	//{{AFX_VIRTUAL(CNGenericPopup)
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CNGenericPopup)
	afx_msg void OnPaint();
	afx_msg void OnDestroy();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnCaptureChanged(CWnd *pWnd);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

#define WM_MENU_DISMISS (WM_APP+1000)

enum
{
	POP_MENU_LEFT,
	POP_MENU_RIGHT,
	POP_MENU_TOP,
	POP_MENU_BOTTOM
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NGENERICPOPUP_H__AD9E2C63_A3B6_11D1_B0D4_00A0C94457BF__INCLUDED_)
