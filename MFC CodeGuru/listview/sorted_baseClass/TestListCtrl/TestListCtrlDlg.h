// TestListCtrlDlg.h : header file
//

#if !defined(AFX_TESTLISTCTRLDLG_H__CBAA678A_F21D_11D1_9F9F_84E5D3000000__INCLUDED_)
#define AFX_TESTLISTCTRLDLG_H__CBAA678A_F21D_11D1_9F9F_84E5D3000000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "MyListCtrl.h"
#include "MyItemInfo.h"

/////////////////////////////////////////////////////////////////////////////
// CTestListCtrlDlg dialog

class CTestListCtrlDlg : public CDialog
{
// Construction
public:
	CTestListCtrlDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CTestListCtrlDlg)
	enum { IDD = IDD_TESTLISTCTRL_DIALOG };
	CMyListCtrl	m_ListCtrl;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestListCtrlDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	void ExtraInit();
	void FillList();


	// Generated message map functions
	//{{AFX_MSG(CTestListCtrlDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTLISTCTRLDLG_H__CBAA678A_F21D_11D1_9F9F_84E5D3000000__INCLUDED_)
