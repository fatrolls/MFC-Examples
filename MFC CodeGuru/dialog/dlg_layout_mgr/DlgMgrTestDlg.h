// DlgMgrTestDlg.h : header file
//

#if !defined(AFX_DLGMGRTESTDLG_H__6FFAC338_E064_11D1_801C_4854E82A1622__INCLUDED_)
#define AFX_DLGMGRTESTDLG_H__6FFAC338_E064_11D1_801C_4854E82A1622__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "DialogMgr.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgMgrTestDlg dialog

class CDlgMgrTestDlg : public CDialogMgr
{
// Construction
public:
	CDlgMgrTestDlg(CWnd* pParent = NULL);	// standard constructor
	DECLARE_LAYOUT();

// Dialog Data
	//{{AFX_DATA(CDlgMgrTestDlg)
	enum { IDD = IDD_DLGMGRTEST_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgMgrTestDlg)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CDlgMgrTestDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGMGRTESTDLG_H__6FFAC338_E064_11D1_801C_4854E82A1622__INCLUDED_)
