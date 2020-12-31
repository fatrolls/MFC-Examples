// proctestDlg.h : header file
//

#if !defined(AFX_PROCTESTDLG_H__3F3A24B7_FFCD_11D1_A30F_0000B481E689__INCLUDED_)
#define AFX_PROCTESTDLG_H__3F3A24B7_FFCD_11D1_A30F_0000B481E689__INCLUDED_

#include "Win32Process.h"	// Added by ClassView
#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CProctestDlg dialog

class CProctestDlg : public CDialog
{
// Construction
public:
	CProctestDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CProctestDlg)
	enum { IDD = IDD_PROCTEST_DIALOG };
	CListBox	m_ctrlProcLB;
	CString	m_strOs;
	CString	m_strProcessToCheck;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProctestDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	Win32Process m_win32proc;
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CProctestDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnGetallprocs();
	afx_msg void OnCheckifactive();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROCTESTDLG_H__3F3A24B7_FFCD_11D1_A30F_0000B481E689__INCLUDED_)
