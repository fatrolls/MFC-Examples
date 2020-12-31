// demo_toolbar.h : main header file for the DEMO_TOOLBAR application
//

#if !defined(AFX_DEMO_TOOLBAR_H__6F831B25_0710_11D2_AB9F_441100C10000__INCLUDED_)
#define AFX_DEMO_TOOLBAR_H__6F831B25_0710_11D2_AB9F_441100C10000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CDemo_toolbarApp:
// See demo_toolbar.cpp for the implementation of this class
//

class CDemo_toolbarApp : public CWinApp
{
public:
	CDemo_toolbarApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDemo_toolbarApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CDemo_toolbarApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DEMO_TOOLBAR_H__6F831B25_0710_11D2_AB9F_441100C10000__INCLUDED_)
