// testDlg.h : header file
// Copyright (C) 1999 by Walter Oney
// All rights reserved

#if !defined(AFX_TESTDLG_H__BFD2A4C5_943B_11D2_81B5_00C04FA330A6__INCLUDED_)
#define AFX_TESTDLG_H__BFD2A4C5_943B_11D2_81B5_00C04FA330A6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

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
	CButton	m_ctlSendevent;
	CListBox	m_ctlEvents;
	//}}AFX_DATA

	HDEVNOTIFY m_hInterfaceNotification;
	HDEVNOTIFY m_hHandleNotification;
	HANDLE m_hDevice;

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
	afx_msg void OnSendevent();
	afx_msg BOOL OnDeviceChange(UINT nEventType, DWORD dwData);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	VOID EnumerateExistingDevices(const GUID* guid);
	VOID OnNewDevice(const CString& devname, const GUID* guid);
	BOOL HandleDeviceChange(DWORD evtype, PDEV_BROADCAST_DEVICEINTERFACE dip);
	BOOL HandleDeviceChange(DWORD evtype, PDEV_BROADCAST_HANDLE dhp);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTDLG_H__BFD2A4C5_943B_11D2_81B5_00C04FA330A6__INCLUDED_)
