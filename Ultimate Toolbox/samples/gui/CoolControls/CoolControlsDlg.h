// CoolControlsDlg.h : header file
//

#if !defined(AFX_COOLCONTROLSDLG_H__3696ECDA_C73B_11D2_A7CA_525400DAF3CE__INCLUDED_)
#define AFX_COOLCONTROLSDLG_H__3696ECDA_C73B_11D2_A7CA_525400DAF3CE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CCoolControlsDlg dialog

class CCoolControlsDlg : public CPropertySheet
{
// Construction
public:
	CCoolControlsDlg(UINT nIDCaption, CWnd *pParentWnd = NULL, 
		UINT iSelectPage = 0);
	CCoolControlsDlg(LPCTSTR pszCaption, CWnd *pParentWnd = NULL, 
		UINT iSelectPage = 0);

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CCoolControlsDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COOLCONTROLSDLG_H__3696ECDA_C73B_11D2_A7CA_525400DAF3CE__INCLUDED_)
