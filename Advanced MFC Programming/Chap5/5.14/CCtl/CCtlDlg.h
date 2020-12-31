// CCtlDlg.h : header file
//

#if !defined(AFX_CCTLDLG_H__E6660F33_04F2_11D1_9C9A_444553540000__INCLUDED_)
#define AFX_CCTLDLG_H__E6660F33_04F2_11D1_9C9A_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "TreeCtrl.h"

/////////////////////////////////////////////////////////////////////////////
// CCCtlDlg dialog

class CCCtlDlg : public CDialog
{
public:
	CCCtlDlg(CWnd* pParent = NULL);
	//{{AFX_DATA(CCCtlDlg)
	enum { IDD = IDD_CCTL_DIALOG };
	MCTreeCtrl	m_treeCtrl;
	//}}AFX_DATA
	//{{AFX_VIRTUAL(CCCtlDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	//}}AFX_VIRTUAL

protected:
	HICON m_hIcon;
	//{{AFX_MSG(CCCtlDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_CCTLDLG_H__E6660F33_04F2_11D1_9C9A_444553540000__INCLUDED_)
