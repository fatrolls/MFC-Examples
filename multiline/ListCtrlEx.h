#if !defined(AFX_LISTCTRLEX_H__30509656_B8A5_11D5_8CEB_00E098800D6B__INCLUDED_)
#define AFX_LISTCTRLEX_H__30509656_B8A5_11D5_8CEB_00E098800D6B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ListCtrlEx.h : header file
//
#include "HeaderCtrlEx.h"
/////////////////////////////////////////////////////////////////////////////
// CListCtrlEx window


static _TCHAR *_gszColumnLabel[4] =
{
	_T("Color\nName"), _T("Red\nColor"), _T("Blue\nColor"), _T("Black\nColor")
};


static int _gnColumnWidth[4] =
{
	150, 100, 150, 80
};


static int _gnColumnFmt[4] =
{
	LVCFMT_LEFT, LVCFMT_RIGHT, LVCFMT_RIGHT
};


static _TCHAR *_gszItem[2][4] =
{
	_T("Yellow\nY"),  _T("255\n255"), _T("30"), _T("50"),
	_T("Red\nR"),     _T("255"), _T("30"), _T("50") 
};

class CListCtrlEx : public CListCtrl
{
// Construction
public:
	CListCtrlEx();

// Attributes
public:
	int		m_nLinesPerRow;	
	int     m_nColumns, m_nRows ;

	CFont			m_NewListFont;
	CHeaderCtrlEx	m_HeaderCtrl ;

	void OnInitialUpdate() ;
	void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) ;

	void SetNoOfLinesPerRow(int n)  { m_nLinesPerRow = n ; }
	void SetNoOfColumns(int n=1)	{ m_nColumns = n ; }
	void SetNoOfRows(int n=0)		{ m_nRows = n ; }

	afx_msg LRESULT	OnSetFont(WPARAM wParam, LPARAM lParam);
	afx_msg void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CListCtrlEx)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CListCtrlEx();

	// Generated message map functions
protected:
	//{{AFX_MSG(CListCtrlEx)
	afx_msg void OnMeasureItem(int nIDCtl, LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LISTCTRLEX_H__30509656_B8A5_11D5_8CEB_00E098800D6B__INCLUDED_)
