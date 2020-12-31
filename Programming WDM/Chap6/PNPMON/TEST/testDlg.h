// testDlg.h : header file
// Copyright (C) 1999 by Walter Oney
// All rights reserved

#if !defined(AFX_TESTDLG_H__BFD2A4C5_943B_11D2_81B5_00C04FA330A6__INCLUDED_)
#define AFX_TESTDLG_H__BFD2A4C5_943B_11D2_81B5_00C04FA330A6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define PWM_EVENT (WM_USER + 0x100)

/////////////////////////////////////////////////////////////////////////////
// CTestDlg dialog

class CTestDlg : public CDialog
{
// Construction
public:
	CTestDlg(CWnd* pParent = NULL);	// standard constructor
	virtual ~CTestDlg();

// Dialog Data
	//{{AFX_DATA(CTestDlg)
	enum { IDD = IDD_TEST_DIALOG };
	CListBox	m_ctlEvents;
	//}}AFX_DATA

	HANDLE m_hevent;
	HANDLE m_hevkill;

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CTestDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg LRESULT OnEvent(WPARAM, LPARAM);
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTDLG_H__BFD2A4C5_943B_11D2_81B5_00C04FA330A6__INCLUDED_)
