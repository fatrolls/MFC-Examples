// Splash.h : main header file for the SPLASH application
//

#if !defined(AFX_SPLASH_H__4B41DC48_8A71_11D1_A3D5_0080C83F712F__INCLUDED_)
#define AFX_SPLASH_H__4B41DC48_8A71_11D1_A3D5_0080C83F712F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CSplashApp:
// See Splash.cpp for the implementation of this class
//

class CSplashApp : public CWinApp
{
public:
	CSplashApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSplashApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CSplashApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SPLASH_H__4B41DC48_8A71_11D1_A3D5_0080C83F712F__INCLUDED_)
