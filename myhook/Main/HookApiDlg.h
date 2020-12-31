#if !defined(AFX_HOOKAPIDLG_H__ADB95BCA_CEBF_496C_9A5F_85FBD7CFD2F4__INCLUDED_)
#define AFX_HOOKAPIDLG_H__ADB95BCA_CEBF_496C_9A5F_85FBD7CFD2F4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// HookApiDlg.h : header file
//
#include "RootDlg.h"
/////////////////////////////////////////////////////////////////////////////
// CHookApiDlg dialog

class CULHook;
class CHookApiDlg : public CRootDlg
{
	DECLARE_DYNCREATE(CHookApiDlg)
// Construction
public:
	CHookApiDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CHookApiDlg)
	enum { IDD = IDD_HOOKAPI_DLG };
	CListCtrl	m_lstData;
	CEdit	m_edtDeatilData;
	CButton	m_btnTopMost;
	CButton	m_btnCloseSend;
	CButton	m_btnCloseRecv;
	CButton	m_btnTarget;
	CButton	m_btnPause;
	CButton	m_btnClose;
	CButton	m_btnClear;
	BOOL	m_bCloseRecv;
	BOOL	m_bCloseSend;
	BOOL	m_bTopMost;
	CString	m_strDetail;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHookApiDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CHookApiDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnPause();
	afx_msg void OnCheckTopmost();
	afx_msg void OnBtnClear();
	afx_msg void OnClickListData(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBtnTarget();
	afx_msg void OnBtnClose();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	afx_msg LRESULT OnReceive(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnSend(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()

	CStatusBarCtrl m_bar;	// ×´Ì¬À¸¿Ø¼þ
	bool m_bOpen;
	bool m_bPause;
private:
	bool SetHook(BOOL bInstall, DWORD dwThreadId = 0, HWND hWndCaller = NULL);
	void UiControl();
};

/////////////////////////////////////////////////////////////////////////////
// CEnumProcessDlg dialog

class CEnumProcessDlg : public CDialog
{
// Construction
public:
	CEnumProcessDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CEnumProcessDlg)
	enum { IDD = IDD_ENUMDIALOG };
	CListCtrl	m_lstProcess;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEnumProcessDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CEnumProcessDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	DWORD m_dwThreadID;
	CString m_strExeName;
private:
	void UpdateProcess();
};
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HOOKAPIDLG_H__ADB95BCA_CEBF_496C_9A5F_85FBD7CFD2F4__INCLUDED_)
