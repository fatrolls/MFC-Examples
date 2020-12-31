// StaticFilespecExampleDlg.h : header file
//

#if !defined(AFX_STATICFILESPECEXAMPLEDLG_H__9D5597A7_6290_11D1_8C86_0000C01C0AED__INCLUDED_)
#define AFX_STATICFILESPECEXAMPLEDLG_H__9D5597A7_6290_11D1_8C86_0000C01C0AED__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "StaticFilespec.h"

/////////////////////////////////////////////////////////////////////////////
// CStaticFilespecExampleDlg dialog

class CStaticFilespecExampleDlg : public CDialog
{
// Construction
public:
	CStaticFilespecExampleDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CStaticFilespecExampleDlg)
	enum { IDD = IDD_STATICFILESPECEXAMPLE_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStaticFilespecExampleDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON             m_hIcon;
	CStaticFilespec   m_wndStaticFileEnd;
	CStaticFilespec   m_wndStaticFilePath;

	// Generated message map functions
	//{{AFX_MSG(CStaticFilespecExampleDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBtnUpdate();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STATICFILESPECEXAMPLEDLG_H__9D5597A7_6290_11D1_8C86_0000C01C0AED__INCLUDED_)
