#if !defined(AFX_PAGECSSSTYLES_H__24B75D54_2C0F_42DA_B7F9_5988A7387EA0__INCLUDED_)
#define AFX_PAGECSSSTYLES_H__24B75D54_2C0F_42DA_B7F9_5988A7387EA0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PageCssStyles.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPageCssStyles dialog

class CPageCssStyles : public CPropertyPage
{
	DECLARE_DYNCREATE(CPageCssStyles)
// Construction
public:
	CPageCssStyles();
	~CPageCssStyles();

// Dialog Data
	//{{AFX_DATA(CPageCssStyles)
	enum { IDD = IDD_PAGE_CSS_STYLES };
	CEdit	m_edit_css_styles;
	CString	m_css_styles;
	CString	m_tag;
	CString	m_styles;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPageCssStyles)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CFont m_font;

	// Generated message map functions
	//{{AFX_MSG(CPageCssStyles)
	virtual BOOL OnInitDialog();
	afx_msg void OnApplyCssStyles();
	afx_msg void OnSetIndividualStyle();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAGECSSSTYLES_H__24B75D54_2C0F_42DA_B7F9_5988A7387EA0__INCLUDED_)
