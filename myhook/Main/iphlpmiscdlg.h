#if !defined(AFX_IPHLPMISCDLG_H__60F7E441_2396_49B4_825F_8C7358266482__INCLUDED_)
#define AFX_IPHLPMISCDLG_H__60F7E441_2396_49B4_825F_8C7358266482__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// IpHlpMiscDlg.h : header file
//

#include "RootDlg.h"

/////////////////////////////////////////////////////////////////////////////
// CIpHlpMiscDlg dialog

class CIpHlpMiscDlg : public CRootDlg
{
	DECLARE_DYNCREATE(CIpHlpMiscDlg)
// Construction
public:
	CIpHlpMiscDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CIpHlpMiscDlg)
	enum { IDD = IDD_IPHLP_MISC };
	CIPAddressCtrl	m_IPHost;
	CIPAddressCtrl	m_IPGateWay;
	CString	m_strFirstInterfaceDesc;
	CString	m_strAdapterName;
	CString	m_strAdapterIndex;
	CString	m_strAdapterNum;
	CString	m_strMac;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIpHlpMiscDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CIpHlpMiscDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnChangeDefaultGateway();
	afx_msg void OnBtnGetMac();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void GetAdapterInfo();
	void GetFirstInterfaceDescription();
	PMIB_IPFORWARDTABLE GetIpForwardTable();
};

/////////////////////////////////////////////////////////////////////////////
// CIpHlpMiscDlg2 dialog

class CIpHlpMiscDlg2 : public CRootDlg
{
	DECLARE_DYNCREATE(CIpHlpMiscDlg2)
// Construction
public:
	CIpHlpMiscDlg2(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CIpHlpMiscDlg2)
	enum { IDD = IDD_IPHLP_MISC3 };
	CIPAddressCtrl	m_IPAddress;
	CComboBox	m_CmbIpAddr;
	CComboBox	m_CombIndex;
	CBCGPMenuButton	m_btnArpFunc;
	CString	m_strIndex;
	CString	m_strIpAddr;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIpHlpMiscDlg2)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CIpHlpMiscDlg2)
	virtual BOOL OnInitDialog();
	afx_msg void OnButton1();
	afx_msg void OnSelchangeComboIndex();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void SendRawUdpPacket();
	void DeleteArpEntry();
	void AddARPEntry();
	void RefreshArpControl();
	bool RefreshArpTable();
	CMenu menu;
	map<int, vector<CString> > m_aArpTable;
};
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IPHLPMISCDLG_H__60F7E441_2396_49B4_825F_8C7358266482__INCLUDED_)
