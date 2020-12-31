#if !defined(AFX_COLORPAGE_H__418271A2_90D4_11D2_8E53_006008A82731__INCLUDED_)
#define AFX_COLORPAGE_H__418271A2_90D4_11D2_8E53_006008A82731__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ColorPage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CColorPage dialog

class CColorPage : public CPropertyPage
{
	DECLARE_DYNCREATE(CColorPage)

// Construction
public:
	CColorPage();
	~CColorPage();
	static const COLORREF m_clrColors[3];

// Dialog Data
	//{{AFX_DATA(CColorPage)
	enum { IDD = IDD_COLOR_PAGE };
	int		m_nColor;
	//}}AFX_DATA

// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CColorPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CColorPage)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	afx_msg void OnChange ();
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COLORPAGE_H__418271A2_90D4_11D2_8E53_006008A82731__INCLUDED_)
