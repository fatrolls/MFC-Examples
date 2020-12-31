// IPTestDlg.h : header file
//

#if !defined(AFX_IPTESTDLG_H__A20D9496_2062_11D1_9EA9_AA000400C8FE__INCLUDED_)
#define AFX_IPTESTDLG_H__A20D9496_2062_11D1_9EA9_AA000400C8FE__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "ipaddr.h"

/////////////////////////////////////////////////////////////////////////////
// CIPTestDlg dialog

class CIPTestDlg : public CDialog
{
// Construction
public:
	CIPTestDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CIPTestDlg)
	enum { IDD = IDD_IPTEST_DIALOG };
	CButton	m_CHECK_Enable;
	//}}AFX_DATA
	unsigned char m_nAddr[4];

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIPTestDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CIPTestDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnCheckedEnable();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CIPAddrCtl* m_pIPAddrCtl;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IPTESTDLG_H__A20D9496_2062_11D1_9EA9_AA000400C8FE__INCLUDED_)
