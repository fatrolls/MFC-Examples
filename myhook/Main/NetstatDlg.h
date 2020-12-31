#if !defined(AFX_NETSTATDLG_H__5E2A7B6D_0B28_4ACF_A6C5_B19D44C6E847__INCLUDED_)
#define AFX_NETSTATDLG_H__5E2A7B6D_0B28_4ACF_A6C5_B19D44C6E847__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NetstatDlg.h : header file
//
#include "RootDlg.h"
#include <TLHELP32.H>

// 扩展函数原型
typedef DWORD (WINAPI *PFAllocateAndGetTcpExTableFromStack)(PMIB_TCPEXTABLE* pTcpTable, BOOL bOrder, HANDLE heap, DWORD zero, DWORD flags);
typedef DWORD (WINAPI *PFNAllocateAndGetUdpExTableFromStack)(PMIB_UDPEXTABLE *pUdpTable, BOOL bOrder, HANDLE heap, DWORD zero, DWORD flags);

/////////////////////////////////////////////////////////////////////////////
// CNetstatDlg dialog

class CNetstatDlg : public CRootDlg
{
    DECLARE_DYNCREATE(CNetstatDlg)
// Construction
public:
	CNetstatDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CNetstatDlg)
	enum { IDD = IDD_NETSTAT_DLG };
	CListCtrl	m_lstUdpTable;
	CListCtrl	m_lstTcpTable;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNetstatDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CNetstatDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnRefresh();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CString ProcessPidToName(HANDLE hSnap, DWORD dwProcessId);
	void GetUdpTable();
	void GetTcpTable();
	PFAllocateAndGetTcpExTableFromStack m_pGetTcpTable;
	PFNAllocateAndGetUdpExTableFromStack m_pGetUdpTable;
	HMODULE m_hDll;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NETSTATDLG_H__5E2A7B6D_0B28_4ACF_A6C5_B19D44C6E847__INCLUDED_)
