#if !defined(AFX_PROPERTYSHEETWITHLOGODLG_H__D17EA810_E6A4_11D1_BB81_0040F684401F__INCLUDED_)
#define AFX_PROPERTYSHEETWITHLOGODLG_H__D17EA810_E6A4_11D1_BB81_0040F684401F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// PropertySheetWithLogoDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPropertySheetWithLogoDlg

class CPropertySheetWithLogoDlg : public CPropertySheet
{
	DECLARE_DYNAMIC(CPropertySheetWithLogoDlg)

// Construction
public:
	CPropertySheetWithLogoDlg(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CPropertySheetWithLogoDlg(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPropertySheetWithLogoDlg)
	public:
	virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL

// Implementation
public:
	void SetLogoFont(CString Name, int nHeight = 24, int nWeight = FW_BOLD,
		BYTE bItalic = true, BYTE bUnderline = false);
	void SetLogoText(CString Text);
	virtual ~CPropertySheetWithLogoDlg();

	// Generated message map functions
protected:
	//{{AFX_MSG(CPropertySheetWithLogoDlg)
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	CFont 	m_fontLogo;
	CString m_LogoText;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROPERTYSHEETWITHLOGODLG_H__D17EA810_E6A4_11D1_BB81_0040F684401F__INCLUDED_)
