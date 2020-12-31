// resviewer.h : main header file for the RESVIEWER application
//

#if !defined(AFX_RESVIEWER_H__213309C5_AD73_11D1_8358_00A0244DBC26__INCLUDED_)
#define AFX_RESVIEWER_H__213309C5_AD73_11D1_8358_00A0244DBC26__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CResviewerApp:
// See resviewer.cpp for the implementation of this class
//

class CResviewerApp : public CWinApp
{
public:
	CResviewerApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CResviewerApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CResviewerApp)
	afx_msg void OnAppAbout();
	afx_msg void OnFileOpen();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RESVIEWER_H__213309C5_AD73_11D1_8358_00A0244DBC26__INCLUDED_)
