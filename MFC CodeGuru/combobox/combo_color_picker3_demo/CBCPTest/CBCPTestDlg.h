// CBCPTestDlg.h : header file
//

#if !defined(AFX_CBCPTESTDLG_H__D0CC2D4A_DB55_11D1_ADB6_004095247E7D__INCLUDED_)
#define AFX_CBCPTESTDLG_H__D0CC2D4A_DB55_11D1_ADB6_004095247E7D__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include	"ColorPickerCB.h"

/////////////////////////////////////////////////////////////////////////////
// CCBCPTestDlg dialog

class CCBCPTestDlg : public CDialog
{
// Construction
public:
	CCBCPTestDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CCBCPTestDlg)
	enum { IDD = IDD_CBCPTEST_DIALOG };
	CColorPickerCB	m_cpcbColorPicker;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCBCPTestDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CCBCPTestDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnDisableColorPicker();
	afx_msg void OnGetName();
	afx_msg void OnGetValue();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CBCPTESTDLG_H__D0CC2D4A_DB55_11D1_ADB6_004095247E7D__INCLUDED_)
