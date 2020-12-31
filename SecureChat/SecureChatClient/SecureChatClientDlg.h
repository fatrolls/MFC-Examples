// SecureChatClientDlg.h : header file
//

#if !defined(AFX_SECURECHATCLIENTDLG_H__A72696A9_0551_491B_9D94_A4A16F3DBF5E__INCLUDED_)
#define AFX_SECURECHATCLIENTDLG_H__A72696A9_0551_491B_9D94_A4A16F3DBF5E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CSecureChatClientDlg dialog



#include "../SecureChatIOCP.h" // The IOCP protocol 
#include "../HistoryEdit.h" // Log ctrl. 
#include "../RanDialog.h" // Random dialog (for collecting entropy) 

class CSecureChatClientDlg : public CDialog
{

private:
	// Message Handler from Server
	LRESULT OnClientDisconnected(WPARAM wParam, LPARAM lParam);
	LRESULT OnNewClient(WPARAM wParam, LPARAM lParam);
	LRESULT OnAppendLog(WPARAM wParam, LPARAM lParam);
	
	// Public key P
	DWORD* m_pPublicKey;
	UINT  m_nSizePublicKey;
	// The random dialog used to generate entropy. 
	CRanDialog m_RandomDlg;  

public:
	// wrapper for connect thread. 
	static UINT ThreadWrapperConnect(LPVOID pParam);
	// Used with ThreadWrapperConnect to make a connection and public key.
	void MakeConnection();
	// Changes the GUI to reflect different mode. 
	void SetGuiConnectedMode(BOOL bConnected=TRUE);
	// Helper Function
	inline void  EnableCtrl(int nCtrlID,BOOL bShow);
	CSecureChatClientDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CSecureChatClientDlg)
	enum { IDD = IDD_SECURECHATCLIENT_DIALOG };
	CButton	m_cBtnConnect;
	CHistoryEdit	m_cLogg;
	CString	m_sIP;
	CString	m_sMessage;
	CString	m_sName;
	UINT	m_nKeySize;
	UINT	m_nPort;
	BOOL	m_bUseSavedPubKey;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSecureChatClientDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	SecureChatIOCP m_iocp;

	// Generated message map functions
	//{{AFX_MSG(CSecureChatClientDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	afx_msg void OnDestroy();
	afx_msg void OnConnect();
	afx_msg void OnSend();
	afx_msg void OnClearwindow();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SECURECHATCLIENTDLG_H__A72696A9_0551_491B_9D94_A4A16F3DBF5E__INCLUDED_)
