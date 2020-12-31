#if !defined(AFX_TABCTRLEX_H__28407441_38AF_11D1_ABBA_00A0243D1382__INCLUDED_)
#define AFX_TABCTRLEX_H__28407441_38AF_11D1_ABBA_00A0243D1382__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// TabCtrlEx.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTabCtrlEx window

class CTabCtrlEx : public CTabCtrl
{
// Construction/destruction
public:
	CTabCtrlEx();
	virtual ~CTabCtrlEx();

// Attributes:
public:

// Operations
public:
	void SetFonts(CFont* pSelFont, CFont* pUnselFont);
	void SetFonts(int nSelWeight=FW_SEMIBOLD, BOOL bSelItalic=FALSE,   BOOL bSelUnderline=FALSE,
				  int nUnselWeight=FW_MEDIUM, BOOL bUnselItalic=FALSE, BOOL bUnselUnderline=FALSE);

	void SetColours(COLORREF bSelColour, COLORREF bUnselColour);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTabCtrlEx)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
protected:
	COLORREF m_crSelColour, m_crUnselColour;
	CFont    m_SelFont,	m_UnselFont;

// Generated message map functions
protected:
	//{{AFX_MSG(CTabCtrlEx)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TABCTRLEX_H__28407441_38AF_11D1_ABBA_00A0243D1382__INCLUDED_)
