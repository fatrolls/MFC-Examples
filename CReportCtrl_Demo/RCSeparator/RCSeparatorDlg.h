// RCSeparatorDlg.h : header file
//

#if !defined(AFX_RCSEPARATORDLG_H__D166947C_0922_487F_A0B3_EC1C7E31CF0A__INCLUDED_)
#define AFX_RCSEPARATORDLG_H__D166947C_0922_487F_A0B3_EC1C7E31CF0A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ReportCtrl.h"

/////////////////////////////////////////////////////////////////////////////
// CRCSeparatorDlg dialog

class CRCSeparatorDlg : public CDialog
{
// Construction
public:
	CRCSeparatorDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CRCSeparatorDlg)
	enum { IDD = IDD_RCSEPARATOR_DIALOG };
	CReportCtrl	m_wndList;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRCSeparatorDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CRCSeparatorDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButton1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RCSEPARATORDLG_H__D166947C_0922_487F_A0B3_EC1C7E31CF0A__INCLUDED_)
