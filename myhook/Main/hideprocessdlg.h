#if !defined(AFX_HIDEPROCESSDLG_H__16AC6790_DB0E_4950_956C_163BF7E81779__INCLUDED_)
#define AFX_HIDEPROCESSDLG_H__16AC6790_DB0E_4950_956C_163BF7E81779__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// HideProcessDlg.h : header file
//
#include "RootDlg.h"
/////////////////////////////////////////////////////////////////////////////
// CHideProcessDlg dialog

class CHideProcessDlg : public CRootDlg
{
	DECLARE_DYNCREATE(CHideProcessDlg)
// Construction
public:
	CHideProcessDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CHideProcessDlg)
	enum { IDD = IDD_HIDE_PROCESS_DLG };
	CBCGPEdit	m_edtDriverPath;
	CBCGPMenuButton	m_btnTool;
	CString	m_strDriverPath;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHideProcessDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CHideProcessDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnButton1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
protected:
	CMenu menu;
	HANDLE m_hDriver;

	void InstallDriver();
    void UninstallDriver();
    void StartDriver();
    void StopDriver();
	void OpenControlDevice();
	void HideProcess();
};

/////////////////////////////////////////////////////////////////////////////
// CHideProcessDetailDlg dialog

class CHideProcessDetailDlg : public CDialog
{
// Construction
public:
	CHideProcessDetailDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CHideProcessDetailDlg)
	enum { IDD = IDD_HIDEPROCESS_DETAIL_DLG };
	CString	m_strPath1;
	CString	m_strPath2;
	CString	m_strPath3;
	CString	m_strPath4;
	CString	m_strPath5;
	CString	m_strPath6;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHideProcessDetailDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CHideProcessDetailDlg)
	afx_msg void OnBtnHide();
	afx_msg void OnBtnShow();
	afx_msg void OnBtnClear();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	HANDLE m_hDriver;
protected:
	bool GetProcessName(CStringArray& aNames);
};
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HIDEPROCESSDLG_H__16AC6790_DB0E_4950_956C_163BF7E81779__INCLUDED_)
