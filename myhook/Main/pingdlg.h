#if !defined(AFX_PINGDLG_H__EF0B1A05_97C8_4716_BC54_B93320A9E905__INCLUDED_)
#define AFX_PINGDLG_H__EF0B1A05_97C8_4716_BC54_B93320A9E905__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PingDlg.h : header file
//
#include "RootDlg.h"
#include <winsock2.h>

/////////////////////////////////////////////////////////////////////////////
// CComboBoxEx window

class CAutoComplete : public CComboBox
{
// Construction
public:
	CAutoComplete();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAutoComplete)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CAutoComplete();

	BOOL m_bAutoComplete;

	// Generated message map functions
protected:
	//{{AFX_MSG(CAutoComplete)
	afx_msg void OnEditUpdate();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CPingDlg dialog
#define WM_MSG_STATUS WM_USER+100
#define WM_PING_END WM_USER+101

class CPing; 

class CPingDlg : public CRootDlg
{
	DECLARE_DYNCREATE(CPingDlg)
// Construction

   friend class CPing;
public:
	CPingDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPingDlg)
	enum { IDD = IDD_PING_DLG };
	CSpinButtonCtrl	m_spin;
	CButton	m_CheckPing;
	CStatic	m_wndEndIP;
	CStatic	m_wndPicTo;
	CStatic	m_wndPicFrom;
	CListCtrl	m_lstInfo;
	CAutoComplete	m_cmbStartIP;
	CAutoComplete	m_cmbEndIP;
	BOOL	m_bCheckPing;
	CString	m_strEndIP;
	CString	m_strStartIP;
	UINT	m_iPingTimes;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPingDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	
	// Generated message map functions
	//{{AFX_MSG(CPingDlg)
	afx_msg void OnCheckPing();
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnBtnStartPing();
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	afx_msg LRESULT OnSetStatus(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnPingEnd(WPARAM, LPARAM);
	DECLARE_MESSAGE_MAP()
private:
	CPoint CountPos(CPoint ptFrom, CPoint ptTo);
	void DrawAnimation(CPaintDC& dc);
	bool CheckError();
	void InitializeControls();

	CImageList m_imglst;
    bool m_bDraw;
	int m_nPos;
	bool m_bIncrease;
	CRect m_rcInvalidate;
};



/////////////////////////////////////////////////////////////////////////////
// CPingThread thread

class CPingThread : public CWinThread
{
	DECLARE_DYNCREATE(CPingThread)
protected:
	CPingThread();           // protected constructor used by dynamic creation

// Attributes
public:

// Operations
public:
	void StartPing(CPingDlg* pDlg);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPingThread)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	virtual int Run();
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CPingThread();

	// Generated message map functions
	//{{AFX_MSG(CPingThread)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

private:
	CPingDlg* m_pDlg;
	CEvent m_event;
};

/////////////////////////////////////////////////////////////////////////////

class CPing  
{
public:
	bool StartPing(CPingDlg* pDlg);
	CPing();
	virtual ~CPing();
private:
	DWORD RecvEchoReply(SOCKET s, LPSOCKADDR_IN lpsaFrom, u_char *pTTL) ;
	int WaitForEchoReply(SOCKET s);
	void SendEchoRequest(SOCKET s, sockaddr_in& addr);
	bool PingSingleMachine(SOCKET s, CString strIP);
	void GetHosts(CString strStartIP, CString strEndIP, map<CString, bool>& aHosts);
	void PostErrorMsg(CString strError);
	void PostSuccessMsg(int index, CString strError);
	bool GetMachineMac(DWORD dwAddr, CString& strMac);
	void GetHostsMac(map<CString, bool>& aHosts);

	CPingDlg* m_pDlg;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PINGDLG_H__EF0B1A05_97C8_4716_BC54_B93320A9E905__INCLUDED_)
