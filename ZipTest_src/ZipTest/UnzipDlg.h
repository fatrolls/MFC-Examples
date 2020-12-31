// UnzipDlg.h : header file
//

#if !defined(AFX_UNZIPDLG_H__C451CE7F_7A6A_4FA3_8523_7240856DBAA1__INCLUDED_)
#define AFX_UNZIPDLG_H__C451CE7F_7A6A_4FA3_8523_7240856DBAA1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CUnzipDlg dialog

#include "..\zipunzip\Unzipper.h"

class CUnzipDlg : public CDialog
{
// Construction
public:
	CUnzipDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CUnzipDlg)
	enum { IDD = IDD_UNZIP_DIALOG };
	CListCtrl	m_lcDetails;
	CString	m_sZipPath;
	int		m_nFileCount;
	int		m_nFolderCount;
	DWORD	m_nTotalCompSize;
	DWORD	m_nTotalUncompSize;
	CString	m_sFileExt;
	BOOL	m_bIgnorePath;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUnzipDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CUnzipper m_uz;

	// Generated message map functions
	//{{AFX_MSG(CUnzipDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnBrowse();
	afx_msg void OnUnzip();
	afx_msg void OnUpdatedetails();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:
	void ShowDetails();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_UNZIPDLG_H__C451CE7F_7A6A_4FA3_8523_7240856DBAA1__INCLUDED_)
