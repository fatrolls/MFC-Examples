
// Copyright (C) 1999 by Walter Oney
// All rights reserved
#if !defined(AFX_SHUTDOWNDLG_H__8BC9EF40_DBBB_11D2_81B5_00C04FA330A6__INCLUDED_)
#define AFX_SHUTDOWNDLG_H__8BC9EF40_DBBB_11D2_81B5_00C04FA330A6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ShutdownDlg.h : header file
//

#include "resource.h"

/////////////////////////////////////////////////////////////////////////////
// CShutdownDlg dialog

class CShutdownDlg : public CDialog
{
// Construction
public:
	CShutdownDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CShutdownDlg)
	enum { IDD = IDD_ASKSHUTDOWN };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CShutdownDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CShutdownDlg)
	afx_msg void OnNo();
	afx_msg void OnYes();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SHUTDOWNDLG_H__8BC9EF40_DBBB_11D2_81B5_00C04FA330A6__INCLUDED_)
