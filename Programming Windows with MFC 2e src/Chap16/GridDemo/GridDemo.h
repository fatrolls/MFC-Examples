// GridDemo.h : main header file for the GRIDDEMO application
//

#if !defined(AFX_GRIDDEMO_H__A4559BA4_ABE5_11D2_8E53_006008A82731__INCLUDED_)
#define AFX_GRIDDEMO_H__A4559BA4_ABE5_11D2_8E53_006008A82731__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CGridDemoApp:
// See GridDemo.cpp for the implementation of this class
//

class CGridDemoApp : public CWinApp
{
public:
	CGridDemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGridDemoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

public:
	//{{AFX_MSG(CGridDemoApp)
	afx_msg void OnAppAbout();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRIDDEMO_H__A4559BA4_ABE5_11D2_8E53_006008A82731__INCLUDED_)
