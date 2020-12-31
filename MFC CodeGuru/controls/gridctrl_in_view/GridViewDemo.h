// GridViewDemo.h : main header file for the GRIDVIEWDEMO application
//

#if !defined(AFX_GRIDVIEWDEMO_H__19E18FB5_DFF6_11D1_8CE7_000000000000__INCLUDED_)
#define AFX_GRIDVIEWDEMO_H__19E18FB5_DFF6_11D1_8CE7_000000000000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CGridViewDemoApp:
// See GridViewDemo.cpp for the implementation of this class
//

class CGridViewDemoApp : public CWinApp
{
public:
	CGridViewDemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGridViewDemoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CGridViewDemoApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRIDVIEWDEMO_H__19E18FB5_DFF6_11D1_8CE7_000000000000__INCLUDED_)
