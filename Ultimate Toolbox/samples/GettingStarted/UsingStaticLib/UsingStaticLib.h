// UsingStaticLib.h : main header file for the USINGSTATICLIB application
//

#if !defined(AFX_USINGSTATICLIB_H__0B90D75A_A148_4832_8142_849A8EB21940__INCLUDED_)
#define AFX_USINGSTATICLIB_H__0B90D75A_A148_4832_8142_849A8EB21940__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CUsingStaticLibApp:
// See UsingStaticLib.cpp for the implementation of this class
//

class CUsingStaticLibApp : public CWinApp
{
public:
	CUsingStaticLibApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUsingStaticLibApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CUsingStaticLibApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_USINGSTATICLIB_H__0B90D75A_A148_4832_8142_849A8EB21940__INCLUDED_)
