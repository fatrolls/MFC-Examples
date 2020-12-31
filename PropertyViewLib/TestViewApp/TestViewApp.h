// TestViewApp.h : main header file for the TESTVIEWAPP application
//

#if !defined(AFX_TESTVIEWAPP_H__5B5E10FA_4B09_4709_81C9_D7CC28778BE8__INCLUDED_)
#define AFX_TESTVIEWAPP_H__5B5E10FA_4B09_4709_81C9_D7CC28778BE8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CTestViewAppApp:
// See TestViewApp.cpp for the implementation of this class
//

class CTestViewAppApp : public CWinApp
{
public:
	CTestViewAppApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestViewAppApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CTestViewAppApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTVIEWAPP_H__5B5E10FA_4B09_4709_81C9_D7CC28778BE8__INCLUDED_)
