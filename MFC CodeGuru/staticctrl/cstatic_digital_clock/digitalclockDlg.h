// digitalclockDlg.h : header file
//

#if !defined(AFX_DIGITALCLOCKDLG_H__F094230B_65D3_11D1_8544_0000217A077A__INCLUDED_)
#define AFX_DIGITALCLOCKDLG_H__F094230B_65D3_11D1_8544_0000217A077A__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CDigitalclockDlg dialog

#include "EDClock.h"

class CDigitalclockDlg : public CDialog
{
// Construction
public:
	CDigitalclockDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CDigitalclockDlg)
	enum { IDD = IDD_DIGITALCLOCK_DIALOG };
	CXJWDigitClock	m_clock1;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDigitalclockDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	CXJWDigitClock	m_clock2;
	CXJWDigitClock	m_clock3;

	// Generated message map functions
	//{{AFX_MSG(CDigitalclockDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButton1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIGITALCLOCKDLG_H__F094230B_65D3_11D1_8544_0000217A077A__INCLUDED_)
