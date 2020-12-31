// SkinMenuTest.h : main header file for the SKINMENUTEST application
//

#if !defined(AFX_SKINMENUTEST_H__47DC495B_3F63_4DC0_B6AB_169AC95C3338__INCLUDED_)
#define AFX_SKINMENUTEST_H__47DC495B_3F63_4DC0_B6AB_169AC95C3338__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CSkinMenuTestApp:
// See SkinMenuTest.cpp for the implementation of this class
//

class CSkinMenuTestApp : public CWinApp
{
public:
	CSkinMenuTestApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSkinMenuTestApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CSkinMenuTestApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SKINMENUTEST_H__47DC495B_3F63_4DC0_B6AB_169AC95C3338__INCLUDED_)
