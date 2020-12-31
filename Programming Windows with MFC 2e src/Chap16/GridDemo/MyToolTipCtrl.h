#if !defined(AFX_MYTOOLTIPCTRL_H__A4559BB1_ABE5_11D2_8E53_006008A82731__INCLUDED_)
#define AFX_MYTOOLTIPCTRL_H__A4559BB1_ABE5_11D2_8E53_006008A82731__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyToolTipCtrl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMyToolTipCtrl window

class CMyToolTipCtrl : public CToolTipCtrl
{
// Construction
public:
	CMyToolTipCtrl();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyToolTipCtrl)
	//}}AFX_VIRTUAL

// Implementation
public:
	BOOL AddRectTool (CWnd* pWnd, LPCTSTR pszText, LPCRECT pRect, UINT nIDTool);
	BOOL AddWindowTool (CWnd* pWnd, LPCTSTR pszText);
	virtual ~CMyToolTipCtrl();

	// Generated message map functions
protected:
	//{{AFX_MSG(CMyToolTipCtrl)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYTOOLTIPCTRL_H__A4559BB1_ABE5_11D2_8E53_006008A82731__INCLUDED_)
