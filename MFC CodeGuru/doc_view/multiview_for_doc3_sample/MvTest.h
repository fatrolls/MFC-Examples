// MvTest.h : main header file for the MVTEST application
//

#if !defined(AFX_MVTEST_H__A695B2C1_DE92_11D1_B6BE_00C04FA35F76__INCLUDED_)
#define AFX_MVTEST_H__A695B2C1_DE92_11D1_B6BE_00C04FA35F76__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CMvTestApp:
// See MvTest.cpp for the implementation of this class
//

class CMvTestApp : public CWinApp
{
public:
	CMvTestApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMvTestApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	COleTemplateServer m_server;

	//{{AFX_MSG(CMvTestApp)
	afx_msg void OnAppAbout();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MVTEST_H__A695B2C1_DE92_11D1_B6BE_00C04FA35F76__INCLUDED_)
