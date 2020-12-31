// URLCheckerDlg.h : header file
//

#if !defined(AFX_URLCHECKERDLG_H__FCAEF619_60D9_11D1_87FE_00001C302581__INCLUDED_)
#define AFX_URLCHECKERDLG_H__FCAEF619_60D9_11D1_87FE_00001C302581__INCLUDED_

#include "TrayIcon.h"	// Added by ClassView
#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CURLCheckerDlg dialog

class CURLCheckerDlg : public CDialog
{
// Construction
public:
	LRESULT OnTrayNotification(WPARAM wParam, LPARAM lParam);
	CURLCheckerDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CURLCheckerDlg)
	enum { IDD = IDD_URLCHECKER_DIALOG };
	CString	m_URL;
	int		m_Duration;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CURLCheckerDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CURLCheckerDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnEndbtn();
	afx_msg void OnStartbtn();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnConfigure();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnAboutdlg();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CTrayIcon m_TrayIcon;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_URLCHECKERDLG_H__FCAEF619_60D9_11D1_87FE_00001C302581__INCLUDED_)
