// HooksTestDlg.h : header file
//

#if !defined(AFX_HOOKSTESTDLG_H__5C461C9F_543B_11D1_BB79_006097B82032__INCLUDED_)
#define AFX_HOOKSTESTDLG_H__5C461C9F_543B_11D1_BB79_006097B82032__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CHooksTestDlg dialog

#include "..\HooksClient\HooksClient.h"

class CHooksTestDlg : public CDialog, public CHooksClient
{
// Construction
public:
	CHooksTestDlg(CWnd* pParent = NULL);	// standard constructor
	~CHooksTestDlg();

	CDumpContext *m_pDump;
	CFile m_fileLog;

	void ProcessHookMessage(HWND hwnd, UINT nMessage, WPARAM wParam, LPARAM lParam);

// Dialog Data
	//{{AFX_DATA(CHooksTestDlg)
	enum { IDD = IDD_HOOKSTEST_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHooksTestDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CHooksTestDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnTest();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HOOKSTESTDLG_H__5C461C9F_543B_11D1_BB79_006097B82032__INCLUDED_)
