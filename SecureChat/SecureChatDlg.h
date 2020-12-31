// SecureChatDlg.h : header file
//

#if !defined(AFX_SECURECHATDLG_H__B5BFD331_2669_43EE_B731_C1A23D555321__INCLUDED_)
#define AFX_SECURECHATDLG_H__B5BFD331_2669_43EE_B731_C1A23D555321__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CSecureChatDlg dialog
#include "MyCryptLib.h"
#include "HistoryEdit.h"
#include "MyListCtrl.h"
#include "SecureChatIOCP.h"
#include "RanDialog.h"
#include "AFXMT.h" // for CCriticalSection 


class CSecureChatDlg : public CDialog
{
private: 
	// Move/resize Ctrls
	BOOL RelocateTo(CWnd *pCtrl, int nDestID);
	void SetDemoMode(BOOL bDemoMode=TRUE);
	inline void ShowCtrl(int nCtrlID,BOOL bShow=TRUE);
	void StartTheServer();
	void StopTheServer();

	// The random dialog used to generate entropy. 
	CRanDialog m_RandomDlg;  
	// The IOCP core and protocll
	SecureChatIOCP m_iocp;
	// Message Handler from Server
	LRESULT OnClientDisconnected(WPARAM wParam, LPARAM lParam);
	LRESULT OnNewClient(WPARAM wParam, LPARAM lParam);
	LRESULT OnAppendLog(WPARAM wParam, LPARAM lParam);
	// The index used to determine selected item in user list.. 
	int m_iCurrenClientID;
	// timer Handler
	int m_ihTimer;
public:
	void UpdateList();
	
	// The size of key used in Demo. 
	UINT m_iKeyByteSize;
	
	// The demo test. 
	void PerformDHTest();
	void PerformDSATest();
	void PerformSimpleLibTest();
	void PerformRSATest();

	// The demo test Wrappers
	static UINT ThreadWrapperDSAdemo(LPVOID pParam);
	static UINT ThreadWrapperRSAdemo(LPVOID pParam);
	static UINT ThreadWrapperLibTestDemo(LPVOID pParam);
	static UINT ThreadWrapperDHdemo(LPVOID pParam);
	
	CSecureChatDlg(CWnd* pParent = NULL);	// standard constructor
	CCriticalSection m_cProcessLock;
// Dialog Data
	//{{AFX_DATA(CSecureChatDlg)
	enum { IDD = IDD_SECURECHAT_DIALOG };
	CButton	m_cBtnDisconnect;
	CButton	m_cStartStopBtn;
	CEdit	m_cPortNr;
	CEdit	m_cNrOfIOWorkers;
	CEdit	m_cMaxNrOConnection;
	MyListCtrl	m_cUserList;
	CTabCtrl	m_cTab;
	CHistoryEdit	m_cLogg;
	UINT	m_iKeyLength;
	CString	m_sAdress;
	CString	m_sAddress;
	UINT	m_iPort;
	UINT	m_iNrOfIOWorkers;
	UINT	m_iMaximumNrOfConnections;
	CString	m_sMessage;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSecureChatDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CSecureChatDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	afx_msg void OnSimplelibtest();
	afx_msg void OnRsatest();
	afx_msg void OnGeneratekey();
	afx_msg void OnDhtest();
	afx_msg void OnSelchangeToptap(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnStartstopserver();
	afx_msg void OnClickUserlist(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDisconnect();
	afx_msg void OnDisconnectall();
	afx_msg void OnSendtxt();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnDestroy();
	afx_msg void OnClearlog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SECURECHATDLG_H__B5BFD331_2669_43EE_B731_C1A23D555321__INCLUDED_)
