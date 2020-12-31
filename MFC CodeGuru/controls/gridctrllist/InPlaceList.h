
#ifndef __AFX_INPLACELIST_H_INCLUDED__
#define __AFX_INPLACELIST_H_INCLUDED__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// InPlaceList.h : header file
//
//
// Written by Motty Cohen Copyright (c) 1998.
// Based on Chris Maunder's InPlaceEdit class
// 
//
// This code may be used in compiled form in any way you desire. This
// file may be redistributed unmodified by any means PROVIDING it is 
// not sold for profit without the authors written consent, and 
// providing that this notice and the authors name is included. If 
// the source code in  this file is used in any commercial application 
// then acknowledgement must be made to the author of this file 
// (in whatever form you wish).
//
// This file is provided "as is" with no expressed or implied warranty.
// The author accepts no liability for any damage/loss of business that
// this product may cause.
//
// Expect bugs!
//
/////////////////////////////////////////////////////////////////////////////

#define IDC_IPLIST 7
#define IPLM_FILL  WM_USER + 1000

/////////////////////////////////////////////////////////////////////////////
// CInPlaceList window

class CInPlaceList : public CListBox
{
// Construction
public:
	CInPlaceList(CWnd* pParent, CRect& rect, DWORD dwStyle, int nRow, int nColumn, 
				 CString sInitText, UINT nFirstChar);

// Attributes
public:

// Operations
public:
	void EndSelect();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInPlaceList)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CInPlaceList();

	// Generated message map functions
protected:
	//{{AFX_MSG(CInPlaceList)
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnNcDestroy();
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonUp( UINT nFlag, CPoint pt );
	//}}AFX_MSG

	// afx_msg void OnCloseup(); // for combobox
	DECLARE_MESSAGE_MAP()

private:
	int		m_nNumLines;
	CString m_sInitText;
	int		m_nRow;
	int		m_nCol;
 	char    m_nLastChar; 
	BOOL	m_bExitOnArrows; 
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(__AFX_INPLACELIST_H_INCLUDED__)
