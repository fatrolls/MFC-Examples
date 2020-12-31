// GLTEST.h : main header file for the GLTEST application
//

#if !defined(AFX_GLTEST_H__8B45E645_9455_11D1_95A6_E0175F8E7830__INCLUDED_)
#define AFX_GLTEST_H__8B45E645_9455_11D1_95A6_E0175F8E7830__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CGLTESTApp:
// See GLTEST.cpp for the implementation of this class
//

class CGLTESTApp : public CWinApp
{
public:
	CGLTESTApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGLTESTApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CGLTESTApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GLTEST_H__8B45E645_9455_11D1_95A6_E0175F8E7830__INCLUDED_)
