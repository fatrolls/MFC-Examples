// SkinsDemo.h : main header file for the SKINSDEMO application
//

#if !defined(AFX_SKINSDEMO_H__698DEA13_A6F8_421B_810B_B8C827F5B9E3__INCLUDED_)
#define AFX_SKINSDEMO_H__698DEA13_A6F8_421B_810B_B8C827F5B9E3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols
#include "OXSkins.h"

/////////////////////////////////////////////////////////////////////////////
// CSkinsDemoApp:
// See SkinsDemo.cpp for the implementation of this class
//

// STEP 1 - Derive your application class from COXSkinnedApp insted of CWinApp.
class CSkinsDemoApp : public COXSkinnedApp
{
public:
	CSkinsDemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSkinsDemoApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CSkinsDemoApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SKINSDEMO_H__698DEA13_A6F8_421B_810B_B8C827F5B9E3__INCLUDED_)
