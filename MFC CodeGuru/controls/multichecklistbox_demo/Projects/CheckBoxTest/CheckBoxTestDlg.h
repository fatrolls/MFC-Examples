// CheckBoxTestDlg.h : header file
//

#if !defined(AFX_CHECKBOXTESTDLG_H__D4D62F87_E758_11D1_AE66_A0B807C10000__INCLUDED_)
#define AFX_CHECKBOXTESTDLG_H__D4D62F87_E758_11D1_AE66_A0B807C10000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CCheckBoxTestDlg dialog

#include "MultiCheckListBox.h"

class CCheckBoxTestDlg : public CDialog
{
// Construction
public:
	CCheckBoxTestDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CCheckBoxTestDlg)
	enum { IDD = IDD_CHECKBOXTEST_DIALOG };
	CMultiCheckListBox	m_ListBox;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCheckBoxTestDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CCheckBoxTestDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHECKBOXTESTDLG_H__D4D62F87_E758_11D1_AE66_A0B807C10000__INCLUDED_)
