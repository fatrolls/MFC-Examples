// TestDlg.h : header file
//

#if !defined(AFX_TESTDLG_H__46B50EC9_D5E9_11D1_8806_0000C074BDF8__INCLUDED_)
#define AFX_TESTDLG_H__46B50EC9_D5E9_11D1_8806_0000C074BDF8__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CTestDlg dialog

/*
 * NEW HERE:
 * - Replaced cdxCSizingDialog by cdxCSizingDialog;
 * - Added #include "cdxCSizingDialog.h"
 */

#include "cdxCSizingDialog.h"

class CTestDlg : public cdxCSizingDialog
{
// Construction
public:
	CTestDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CTestDlg)
	enum { IDD = IDD_TESTDIALOG_DIALOG };
	CButton	m_wndOK;
	CButton	m_wndCancel;
	CStatic	m_wndResize;
	CStatic	m_wndRepos2;
	CStatic	m_wndRel2;
	CStatic	m_wndRepos;
	CStatic	m_wndRel;
	CStatic	m_wndNone;
	CStatic	m_wndHeader;
	//}}AFX_DATA

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
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTDLG_H__46B50EC9_D5E9_11D1_8806_0000C074BDF8__INCLUDED_)
