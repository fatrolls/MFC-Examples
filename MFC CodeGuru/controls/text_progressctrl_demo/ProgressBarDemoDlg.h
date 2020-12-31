// ProgressBarDemoDlg.h : header file
//

#if !defined(AFX_PROGRESSBARDEMODLG_H__4C78DBB6_EFB6_11D1_AB14_203E25000000__INCLUDED_)
#define AFX_PROGRESSBARDEMODLG_H__4C78DBB6_EFB6_11D1_AB14_203E25000000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "TextProgressCtrl.h"

/////////////////////////////////////////////////////////////////////////////
// CProgressBarDemoDlg dialog

class CProgressBarDemoDlg : public CDialog
{
// Construction
public:
	CProgressBarDemoDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CProgressBarDemoDlg)
	enum { IDD = IDD_PROGRESSBARDEMO_DIALOG };
	CTextProgressCtrl	m_ProgressBar;
	BOOL	m_bShowText;
	BOOL	m_bUserText;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProgressBarDemoDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CProgressBarDemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnTest();
	afx_msg void OnShowText();
	afx_msg void OnUserText();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROGRESSBARDEMODLG_H__4C78DBB6_EFB6_11D1_AB14_203E25000000__INCLUDED_)
