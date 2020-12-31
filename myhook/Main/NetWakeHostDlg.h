#if !defined(AFX_NETWAKEHOSTDLG_H__AF92AA3E_51D6_4D22_8C5B_E59585D6E0A6__INCLUDED_)
#define AFX_NETWAKEHOSTDLG_H__AF92AA3E_51D6_4D22_8C5B_E59585D6E0A6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NetWakeHostDlg.h : header file
//
#include "RootDlg.h"
/////////////////////////////////////////////////////////////////////////////
// CNetWakeHostDlg dialog

class CNetWakeHostDlg : public CRootDlg
{
	DECLARE_DYNCREATE(CNetWakeHostDlg)
// Construction
public:
	CNetWakeHostDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CNetWakeHostDlg)
	enum { IDD = IDD_NET_WAKE_MACHINE_DLG };
	CListBox	m_lstIP;
	CListBox	m_lstMac;
	CListBox	m_lstHost;
	CButton	m_btnWake;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNetWakeHostDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CNetWakeHostDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeListHost();
	afx_msg void OnSelchangeListMac();
	afx_msg void OnSelchangeListIp();
	afx_msg void OnBtnWake();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void InitializeControls();
	void StringToMac(CString strMac,unsigned  char mac[6]);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NETWAKEHOSTDLG_H__AF92AA3E_51D6_4D22_8C5B_E59585D6E0A6__INCLUDED_)
