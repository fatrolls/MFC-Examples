#if !defined(AFX_DDEDLG_H__747EBB3A_49F6_11D1_9C9A_444553540000__INCLUDED_)
#define AFX_DDEDLG_H__747EBB3A_49F6_11D1_9C9A_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif

#include "DDEML.H"

class CDDECliDlg : public CDialog
{
public:
	static HDDEDATA CALLBACK DdeCallback(UINT, UINT, HCONV,	HSZ, HSZ, HDDEDATA,	DWORD, DWORD);
	static void InitializeDDE();
	static HSZ ObtainHsz(CString);
	static void UnobtainHsz(HSZ);
	static void Printf(const char *, ...);
	CDDECliDlg(CWnd *pParent=NULL);
	//{{AFX_DATA(CDDECliDlg)
	enum { IDD = IDD_DDECLI_DIALOG };
	CButton	m_btnAdvise;
	CButton	m_btnRequest;
	CButton	m_btnConnect;
	CEdit	m_ecMsg;
	CString	m_szTopic;
	CString	m_szTimeItem;
	CString	m_szText;
	//}}AFX_DATA
	//{{AFX_VIRTUAL(CDDECliDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	//}}AFX_VIRTUAL

protected:
	static DWORD m_dwInst;
	static HSZ m_hszServiceName;
	static HSZ m_hszTopicName;
	static TCHAR m_szService[];
	static HCONV m_hConvClient;
	static BOOL m_bAdvise;
	HICON m_hIcon;
	//{{AFX_MSG(CDDECliDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonConnect();
	afx_msg void OnClose();
	afx_msg void OnButtonRequest();
	afx_msg void OnButtonAdvise();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//{{AFX_INSERT_LOCATION}}
#endif // !defined(AFX_DDEDLG_H__747EBB3A_49F6_11D1_9C9A_444553540000__INCLUDED_)
