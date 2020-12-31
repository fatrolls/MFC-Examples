// URLChecker.h : main header file for the URLCHECKER application
//

#if !defined(AFX_URLCHECKER_H__FCAEF617_60D9_11D1_87FE_00001C302581__INCLUDED_)
#define AFX_URLCHECKER_H__FCAEF617_60D9_11D1_87FE_00001C302581__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CURLCheckerApp:
// See URLChecker.cpp for the implementation of this class
//

class CURLCheckerApp : public CWinApp
{
public:
	CURLCheckerApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CURLCheckerApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CURLCheckerApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_URLCHECKER_H__FCAEF617_60D9_11D1_87FE_00001C302581__INCLUDED_)
