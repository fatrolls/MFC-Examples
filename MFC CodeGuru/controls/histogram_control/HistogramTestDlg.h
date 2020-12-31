// HistogramTestDlg.h : header file
//

#if !defined(AFX_HISTOGRAMTESTDLG_H__C5FA53C6_EACC_11D1_9DF0_0060970863EE__INCLUDED_)
#define AFX_HISTOGRAMTESTDLG_H__C5FA53C6_EACC_11D1_9DF0_0060970863EE__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "HistogramCtrl.h"

/////////////////////////////////////////////////////////////////////////////
// CHistogramTestDlg dialog

class CHistogramTestDlg : public CDialog
{
// Construction
public:
	CHistogramTestDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CHistogramTestDlg)
	enum { IDD = IDD_HISTOGRAMTEST_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHistogramTestDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	CHistogramCtrl m_HistogramCtrl;
	BOOL           m_bStartStop;

	// Generated message map functions
	//{{AFX_MSG(CHistogramTestDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnTest();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HISTOGRAMTESTDLG_H__C5FA53C6_EACC_11D1_9DF0_0060970863EE__INCLUDED_)
