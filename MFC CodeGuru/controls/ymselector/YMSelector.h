// YMSelector.h
// Control to select year and month
// Designed and developed by Shekar Narayanan
// ShekarNarayanan@Hotmail.com
// 

#if !defined(AFX_YMSELECTOR_H__12C342F1_008C_11D2_AECD_0004AC31E75C__INCLUDED_)
#define AFX_YMSELECTOR_H__12C342F1_008C_11D2_AECD_0004AC31E75C__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// YMSelector.h : header file
//

#define     START_YEAR      1900
#define     END_YEAR        2050    
#define     YM_SELECTED     WM_USER + 50
#define     YM_ABORTED      WM_USER + 51

/////////////////////////////////////////////////////////////////////////////
// CYMPopUp window
// Used by the YMSelector control

class CYMPopUp : public CWnd
{
// Construction
public:
	CYMPopUp(CPoint p, CWnd* pParent, int nYear = -1, int nMonth = -1);

// Attributes
public:

// Operations
public:
    BOOL Create(CPoint p, CWnd* pParent);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CYMPopUp)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CYMPopUp();

	// Generated message map functions
protected:
    int     m_nYear;
    int     m_nMonth;
    CBrush  m_bkBrush;
    CWnd*   m_pParent;
    CRect   m_rCells[12];
    CRect   m_rMinus;
    CRect   m_rPlus;
    CRect   m_rYear;

	//{{AFX_MSG(CYMPopUp)
	afx_msg void OnNcDestroy();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CYMSelector window

class CYMSelector : public CButton
{
// Construction
public:
	CYMSelector();

// Attributes
public:

    void    SetYear(int y);
    void    SetMonth(int m);
    int     GetYear();
    int     GetMonth();
    LPCTSTR GetMonthString();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CYMSelector)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CYMSelector();

	// Generated message map functions
protected:
    int m_nMonth;
    int m_nYear;
	//{{AFX_MSG(CYMSelector)
	afx_msg void OnClicked();
	//}}AFX_MSG
    afx_msg LONG YMSelected(WPARAM wParam = 0, LPARAM lParam = 0);
    afx_msg LONG YMAborted (WPARAM wParam = 0, LPARAM lParam = 0);

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_YMSELECTOR_H__12C342F1_008C_11D2_AECD_0004AC31E75C__INCLUDED_)
