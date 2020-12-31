// XEditPromptTestDlg.h : header file
//

#ifndef XEDITPROMPTTESTDLG_H
#define XEDITPROMPTTESTDLG_H

#include "XEditPrompt.h"

/////////////////////////////////////////////////////////////////////////////
// CXEditPromptTestDlg dialog

class CXEditPromptTestDlg : public CDialog
{
// Construction
public:
	CXEditPromptTestDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CXEditPromptTestDlg)
	enum { IDD = IDD_XEDITPROMPTTEST_DIALOG };
	CEdit	m_Edit4;
	CXEditPrompt	m_Edit1;
	CXEditPrompt	m_Edit2;
	CEdit			m_Edit3;
	CString	m_strEdit1;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXEditPromptTestDlg)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CXEditPromptTestDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSetfocusEdit1();
	afx_msg void OnSetfocusEdit2();
	afx_msg void OnUpdateEdit1();
	afx_msg void OnUpdateEdit2();
	afx_msg void OnReset();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif //XEDITPROMPTTESTDLG_H
