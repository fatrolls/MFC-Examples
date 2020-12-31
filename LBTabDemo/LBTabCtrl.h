// LBTabCtrl.h : header file
//
// Copyright © 2000 Oleg Lobach, All Rights Reserved.
//
// mailto:oleglb@mail.ru
//or
// mailto:oleg@alexen.ru
//
//
// This source file may be redistributed unmodified by any means PROVIDING 
// it is NOT sold for profit without the authors expressed written 
// consent, and providing that this notice and the authors name and all 
// copyright notices remain intact. This software is by no means to be 
// included as part of any third party components library, or as part any
// development solution that offers MFC extensions that are sold for profit. 
// 
// If the source code is used in any commercial applications then a statement 
// along the lines of:
// 
// "Portions Copyright © 1999 Oleg Lobach" must be included in the "Startup 
// Banner", "About Box" or "Printed Documentation". This software is provided 
// "as is" without express or implied warranty. The author accepts no 
// liability for any damage/loss of business that this  product may cause.
//
/////////////////////////////////////////////////////////////////////////////
//****************************************************************************
#if !defined(AFX_LBTABCTRL_H__B97CFD04_ADAD_11D3_BB51_E0079DB8CB25__INCLUDED_)
#define AFX_LBTABCTRL_H__B97CFD04_ADAD_11D3_BB51_E0079DB8CB25__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif

#include "LBSpinButtonCtrl.h"

#define ITEM_DEFLATE 1
#define HINT_ACTIVATE_RIGHT_SIDE 1
#define HINT_ACTIVE_ITEM 2
#define FLOAT_ITEM_HEIGHT_SHIFT 2
#define ACTIVE_ITEM_HEIGHT_SHIFT 2
#define SHIFT_FROM_CUT_TO_SPIN 4
/////////////////////////////////////////////////////////////////////////////
// CLBTabCtrl window

class CLBTabCtrl : public CTabCtrl
{
// Construction
public:
	CLBTabCtrl();

// Attributes
protected:
	bool m_bFloatPaint;
	bool m_bOverTab;
	int m_nActiveItem;
	short m_nPrevPointedItem;
	CLBSpinButtonCtrl m_Spin;
	CRect m_rctPage;
	CRect m_rectUpDn;
	HPEN m_hPenShadow;
	HPEN m_hPenLight;
	HPEN m_hPenItemShadow;
	HFONT m_hMenuFont;

private:
	bool m_bAutoRaising;
// Operations
private:
	bool m_bHasFocus;
	UINT FindLeftDownItem() const;
	void DrawFocus(CDC &dc);
	
public:
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLBTabCtrl)
	protected:
	virtual void PreSubclassWindow();
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL
// Implementation
protected:
	virtual void  DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual void  DrawItemRect(CDC& dc,CRect& rcItem,int nHint=0);
public:
	bool SetAutoRaising(bool bOn);
	virtual ~CLBTabCtrl();

// Generated message map functions
protected:
	//{{AFX_MSG(CLBTabCtrl)
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg BOOL OnSelchange ( NMHDR * pNotifyStruct, LRESULT* result );
	afx_msg BOOL OnSelchanging(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg LRESULT OnMouseLeave(WPARAM, LPARAM);
	afx_msg void OnPaint();   
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_LBTABCTRL_H__B97CFD04_ADAD_11D3_BB51_E0079DB8CB25__INCLUDED_)
