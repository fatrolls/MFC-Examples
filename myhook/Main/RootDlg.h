#if !defined(AFX_ROOTDLG_H__FA318B2E_4F9D_404B_971D_012582F4B310__INCLUDED_)
#define AFX_ROOTDLG_H__FA318B2E_4F9D_404B_971D_012582F4B310__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RootDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRootDlg dialog

class CRootDlg : public CBCGPDialog
{
	DECLARE_DYNCREATE(CRootDlg)
// Construction
public:
	CRootDlg(UINT uIDD = 0, CWnd* pParent = NULL);   // standard constructor
	CRect m_rcWindow;
// Dialog Data
	//{{AFX_DATA(CRootDlg)
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRootDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CRootDlg)
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	UINT IDD;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ROOTDLG_H__FA318B2E_4F9D_404B_971D_012582F4B310__INCLUDED_)
