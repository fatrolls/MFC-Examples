#if !defined(AFX_HOOKFIREWALLDLG_H__F0C9FDD2_BD8E_4F51_8A9F_B98050F6126D__INCLUDED_)
#define AFX_HOOKFIREWALLDLG_H__F0C9FDD2_BD8E_4F51_8A9F_B98050F6126D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// HookFirewallDlg.h : header file
//

#include "RootDlg.h"
#include "ProtocolTypes.h"
/////////////////////////////////////////////////////////////////////////////
// CHookFirewallDlg dialog
class CHookDriver;

class CHookFirewallDlg : public CRootDlg
{
	DECLARE_DYNCREATE(CHookFirewallDlg)
// Construction
public:
	CHookFirewallDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CHookFirewallDlg)
	enum { IDD = IDD_HOOK_FIREWALL_DLG };
	CListCtrl	m_lstRules;
	CBCGPMenuButton	m_btnMenu;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHookFirewallDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CHookFirewallDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnMenu();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	CMenu menu;
private:
	void DeleteRule();
	void InstallRules();
	void AddRule();
	void StopHook();
	void StartHook();
	bool AddRule(unsigned long sourceIP, unsigned long sourceMask, unsigned short sourcePort, unsigned long destIP, unsigned long destMask, unsigned short destPort, int protocol, BOOL bDrop);
	void ClearRules();
	void UpdateRuleList();
	void ImportRules();
	void SaveRulesToFile();

	vector<IPFilterRule> m_aRules;
	CHookDriver* m_pDriver;
	bool m_bStarted;
};

class CRuleDlg : public CDialog
{
public:
	UINT m_srcIP;
	UINT m_srcMask;
	USHORT m_srcPort;

	UINT m_destIP;
	UINT m_destMask;
	USHORT m_destPort;

	UINT m_nProtocol;
	BOOL m_bDrop;

// Construction
public:
	CRuleDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CRuleDlg)
	enum { IDD = IDD_ADDRULEDLG };
	CComboBox	m_cmbProtocol;
	CComboBox	m_cmbAction;
	CString	m_strSourceIP;
	CString	m_strDestIP;
	CString	m_strDestMask;
	CString	m_strSourceMask;
	UINT	m_nDestPort;
	UINT	m_nSourcePort;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRuleDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CRuleDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HOOKFIREWALLDLG_H__F0C9FDD2_BD8E_4F51_8A9F_B98050F6126D__INCLUDED_)
