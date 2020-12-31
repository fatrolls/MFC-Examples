// YMTestDlg.h : header file
//

#if !defined(AFX_YMTESTDLG_H__12C342E9_008C_11D2_AECD_0004AC31E75C__INCLUDED_)
#define AFX_YMTESTDLG_H__12C342E9_008C_11D2_AECD_0004AC31E75C__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "YMSelector.h"
/////////////////////////////////////////////////////////////////////////////
// CYMTestDlg dialog

class CYMTestDlg : public CDialog
{
// Construction
public:
	CYMTestDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CYMTestDlg)
	enum { IDD = IDD_YMTEST_DIALOG };
	CYMSelector	m_btnStart;
	CYMSelector	m_btnEnd;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CYMTestDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CYMTestDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_YMTESTDLG_H__12C342E9_008C_11D2_AECD_0004AC31E75C__INCLUDED_)
