// PCTest.h : main header file for the PCTEST application
//

#if !defined(AFX_PCTEST_H__D1BB4167_804D_11D1_80B6_080009CC78D8__INCLUDED_)
#define AFX_PCTEST_H__D1BB4167_804D_11D1_80B6_080009CC78D8__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CPCTestApp:
// See PCTest.cpp for the implementation of this class
//

class CPCTestApp : public CWinApp
{
public:
	CPCTestApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPCTestApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CPCTestApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PCTEST_H__D1BB4167_804D_11D1_80B6_080009CC78D8__INCLUDED_)
