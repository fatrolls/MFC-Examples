// MarkupDlg.h : header file
//
// Markup Release 11.5
// Copyright (C) 2011 First Objective Software, Inc. All rights reserved
// Go to www.firstobject.com for the latest CMarkup and EDOM documentation
// Use in commercial applications requires written permission
// This software is provided "as is", with no warranty.

#if !defined(_MARKUPDLG_H_INCLUDED_)
#define _MARKUPDLG_H_INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CMarkupDlg dialog

class CMarkupDlg : public CDialog
{
// Construction
public:
	CMarkupDlg(CWnd* pParent = NULL);	// standard constructor

	BOOL m_bAutoExit;

// Dialog Data
	//{{AFX_DATA(CMarkupDlg)
	enum { IDD = IDD_MARKUP_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMarkupDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void LoadSystemSettings();
	void SaveSystemSettings();

// Util
	static CString AddNumSeps( int nVal )
	{
		CString csNum;
		csNum.Format(_T("%d"),nVal);
		for ( int nOffset = csNum.GetLength()-3; nOffset > 0; nOffset -= 3 )
			csNum = csNum.Left(nOffset) + "," + csNum.Mid(nOffset);
		return csNum;
	};

	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMarkupDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonBrowse();
	afx_msg void OnButtonParse();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(_MARKUPDLG_H_INCLUDED_)
