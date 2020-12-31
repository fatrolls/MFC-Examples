#if !defined(AFX_JCOMBO_H__409A6B13_4498_11D1_AEB1_00A0240D05AF__INCLUDED_)
#define AFX_JCOMBO_H__409A6B13_4498_11D1_AEB1_00A0240D05AF__INCLUDED_


#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
/////////////////////////////////////////////////////////////////////////////
// Copyright (C) 1997 by Jakawan Ratiwanich
// All rights reserved
//
// This JCombo is done by courtesy of Jak. You can distribute,
// EXCEPT: don't remove my name from the source or
// documentation (don't take credit for my work), mark your changes (don't
// get me blamed for your possible bugs), don't alter or remove this
// notice.

// No warrantee of any kind, express or implied, is included with this
// software; use at your own risk, responsibility for damages (if any) to
// anyone resulting from the use of this software rests entirely with the
// user.
//
// Send bug reports, bug fixes, enhancements, requests, flames, etc., and
// Fell free to e-mail me at jack@fsec.ucf.edu
// CTitletip --> Special thanks for Zafir to give me some idea

#define TITLETIP_CLASSNAME _T("ComboboxTitleTip")
/////////////////////////////////////////////////////////////////////////////
// CTitleTip window

class CTitleTip : public CWnd
{
// Construction
public:
	CTitleTip();
	BOOL TITLETIP_SHOW;
	void Show(CRect rectTitle, LPCTSTR lpszTitleText, int xoffset = 0);
	virtual BOOL Create(CWnd * pParentWnd);
	virtual ~CTitleTip();


protected:
	CDC * dc;
	BOOL bFocusRect;
	CWnd * m_pParentWnd;

};

//////////////////////////////////////////////////////////////////////////////////
// JCombo.h : header file

#ifndef __JCOMBO_H__
#define __JCOMBO_H__

#define ITEM_HEIGHT		30
#define OFFSET_END		300 
#define TEXT_PER_PIXEL	6


#define NORMAL			0x1000
#define HIGH_LIGHT		0x1001
#define CHECKED			0x1002

#define EDGE			0xf000
#define EDGE_NORMAL		0xf001
#define EDGE_HIGHLIGHT	0xf002	

class CJCombo : public CComboBox
{
// Construction
public:
	CJCombo();	
	CTitleTip m_titletip;	
	int		  SetCurSel(int nSelect);
	int		  GetLBText(int col,int nIndex,CString & rString);
	void	  FormatList(int tCol,int nJustify=DT_LEFT,BOOL bCheckBox=FALSE,UINT nEdge=NORMAL);
	BOOL	  AddItem(
					    CString strItem,int nCol,int nRow,
						int nMask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM,
						int nFmt = LVCFMT_LEFT);


	//////////////////////////////////////////////////////////////////////
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CJCombo)
	public:
	virtual int CompareItem(LPCOMPAREITEMSTRUCT lpCompareItemStruct);
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL


	// Generated message map functions
protected:
	virtual ~CJCombo();
	int		JUSTIFY;
	BOOL	CHECKBOX;
	int		ColWidth[5];
	UINT	EDGE_STYLE;
	int		TotalCol;
	int		CurSel;
	CString cItem[5][200];
	int		PrevRow;
	void	DrawDropList(LPDRAWITEMSTRUCT lpDrawItemStruct,UINT STATE= NORMAL);
	int		DrawThisText(CDC * pDC,CRect rcText,int nColumn,int nItem);

	//{{AFX_MSG(CJCombo)
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnCloseup();
	//}}AFX_MSG
//	afx_msg BOOL OnToolTipNotify(UINT id, NMHDR * pTTTStruct, LRESULT * pResult);


	DECLARE_MESSAGE_MAP()
private:
	CRect	OnDrawThisText(CDC* pDC,CRect rcItem,int itemID);

};

#endif __JCOMBO_H__		// include class CJCombo

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_JCOMBO_H__409A6B13_4498_11D1_AEB1_00A0240D05AF__INCLUDED_)

