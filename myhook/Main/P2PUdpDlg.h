#if !defined(AFX_P2PUDPDLG_H__C892D374_81EC_443E_87CD_A0AEF5A330D3__INCLUDED_)
#define AFX_P2PUDPDLG_H__C892D374_81EC_443E_87CD_A0AEF5A330D3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// P2PUdpDlg.h : header file
//
#include "RootDlg.h"
/////////////////////////////////////////////////////////////////////////////
// CP2PUdpServerDlg dialog
class CMyP2pUDPServer;

class CP2PUdpServerDlg : public CRootDlg
{
	DECLARE_DYNCREATE(CP2PUdpServerDlg)
// Construction
public:
	void SetListBoxPos(CListBox& lstbox);
	CP2PUdpServerDlg(CWnd* pParent = NULL);   // standard constructor
    ~CP2PUdpServerDlg();
// Dialog Data
	//{{AFX_DATA(CP2PUdpServerDlg)
	enum { IDD = IDD_P2P_UDP_SERVER_DLG };
	CListBox	m_lstUser;
	CListBox	m_lstInfo;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CP2PUdpServerDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CP2PUdpServerDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
protected:
	CMyP2pUDPServer* m_pServer;
};

/////////////////////////////////////////////////////////////////////////////
// CP2PUdpClientDlg dialog
class CMyP2pUDPClient;

class CP2PUdpClientDlg : public CRootDlg
{
	DECLARE_DYNCREATE(CP2PUdpClientDlg)
// Construction
public:
	void SetListBoxPos(CListBox& lstbox);
	CP2PUdpClientDlg(CWnd* pParent = NULL);   // standard constructor
    ~CP2PUdpClientDlg();
// Dialog Data
	//{{AFX_DATA(CP2PUdpClientDlg)
	enum { IDD = IDD_P2P_UDP_CLIENT_DLG };
	CListBox	m_lstUser;
	CListBox	m_lstInfo;
	CListBox	m_lstContent;
	CEdit	m_edtContent;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CP2PUdpClientDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CP2PUdpClientDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnSend();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
protected:
	CMyP2pUDPClient* m_pClient;
};
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_P2PUDPDLG_H__C892D374_81EC_443E_87CD_A0AEF5A330D3__INCLUDED_)
