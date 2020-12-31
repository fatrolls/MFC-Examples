// WizDlg.h : header file
//

#if !defined(AFX_WIZDLG_H__591B36AA_CFF1_11D3_A166_444553540000__INCLUDED_)
#define AFX_WIZDLG_H__591B36AA_CFF1_11D3_A166_444553540000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CWizDlg dialog

class CWizDlg : public CDialog
{
// Construction
public:
	CWizDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CWizDlg)
	enum { IDD = IDD_WIZ_DIALOG };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWizDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CWizDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnDialogWiz();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WIZDLG_H__591B36AA_CFF1_11D3_A166_444553540000__INCLUDED_)
