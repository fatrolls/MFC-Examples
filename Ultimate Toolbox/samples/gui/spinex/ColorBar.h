#if !defined(AFX_OXCOLORBAR_H__4433107A_2442_11D1_A281_0000929B340A__INCLUDED_)
#define AFX_OXCOLORBAR_H__4433107A_2442_11D1_A281_0000929B340A__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// OXColorBar.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CColorBar window

class CColorBar : public CStatic
{
// Construction
public:
	CColorBar();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CColorBar)
	//}}AFX_VIRTUAL

// Implementation
public:
	CPalette* m_pSpecialPalette;
	void SetBarColor(int nRed, int nGreen, int nBlue);
	virtual ~CColorBar();

	// Generated message map functions
protected:
	CPalette* SetSpecialPalette(CPaintDC* pdc);
	int m_nRed;
	int m_nGreen;
	int m_nBlue;
	//{{AFX_MSG(CColorBar)
	afx_msg void OnPaint();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OXCOLORBAR_H__4433107A_2442_11D1_A281_0000929B340A__INCLUDED_)
