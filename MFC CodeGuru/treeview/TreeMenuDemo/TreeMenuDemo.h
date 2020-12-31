// TreeMenuDemo.h : main header file for the TREEMENUDEMO application
//

#if !defined(AFX_TREEMENUDEMO_H__96C46D86_E5C6_11D1_92D4_0080C882060B__INCLUDED_)
#define AFX_TREEMENUDEMO_H__96C46D86_E5C6_11D1_92D4_0080C882060B__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols


/////////////////////////////////////////////////////////////////////////////
// CTreeMenuDemoApp:
// See TreeMenuDemo.cpp for the implementation of this class
//

class CTreeMenuDemoApp : public CWinApp
{
public:
	CTreeMenuDemoApp();
	
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTreeMenuDemoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CTreeMenuDemoApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TREEMENUDEMO_H__96C46D86_E5C6_11D1_92D4_0080C882060B__INCLUDED_)
