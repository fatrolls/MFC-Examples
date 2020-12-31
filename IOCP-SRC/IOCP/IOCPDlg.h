// IOCPDlg.h : header file
//

#if !defined(AFX_IOCPCLIENTDLG_H__4D989A18_3849_4786_B4FD_102DDDDAEA09__INCLUDED_)
#define AFX_IOCPDlg_H__4D989A18_3849_4786_B4FD_102DDDDAEA09__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CIOCPDlg dialog
#include "MyListCtrl.h"
#include "HistoryEdit.h"
#include "MyIOCP.h"
#include "IOCPSettingsDlg.h"
#include "IOCP.h"
#include "afxwin.h"
class CIOCPDlg : public CDialog
{
// Construction
public:

	

	
	
	CIOCPDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CIOCPDlg)
	enum { IDD = IDD_IOCP_DIALOG };
	CHistoryEdit	m_CtrlLogg;
	MyListCtrl	m_CtrlClientList;
	CString	m_Adress;
	CString	m_sReceivedTxt;
	CString	m_sSendTxt;
	BOOL	m_bFlood;
	int		m_MsgPerSec;
	BOOL	m_bRandomConnect;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIOCPDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	MyIOCP m_iocp;
	IOCPSettingsDlg m_ConfigDlg;
	// Generated message map functions
	//{{AFX_MSG(CIOCPDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	afx_msg void OnDestroy();
	afx_msg void OnDisconnectall();
	afx_msg void OnSend();
	afx_msg void OnDisconnect();
	afx_msg void OnClickClientlist(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnFlood();
	afx_msg void OnStopstart();
	afx_msg void OnSettings();
	afx_msg void OnRandomdisconnect();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void UpdateClientData();
	void UpdateList();
	void EnableClientPanel();
	void DisableClientPanel();
	void DisableAllPanels();
	void EnableAllPanels();
	void StartTheSystem();
	LRESULT OnClientDisconnected(WPARAM wParam, LPARAM lParam);
	LRESULT OnNewClient(WPARAM wParam, LPARAM lParam);
	LRESULT OnAppendLog(WPARAM wParam, LPARAM lParam);
	int m_ihTimer;
	int m_iCurrentClientID;
	// We put all the Context String2Pointer HashMap copy of ContextMapLock
	// used to update user info about the clients. 
	CCriticalSection m_GUIListLock;
	//CMapStringToPtr m_GUIContextMap;
public:
	// SendButton Controll 
	CButton m_CtrlSendBtn;
	afx_msg void OnBnClickedSendfile();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IOCPCLIENTDLG_H__4D989A18_3849_4786_B4FD_102DDDDAEA09__INCLUDED_)
