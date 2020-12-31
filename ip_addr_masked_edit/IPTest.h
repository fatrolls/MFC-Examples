// IPTest.h : main header file for the IPTEST application
//

#if !defined(AFX_IPTEST_H__A20D9494_2062_11D1_9EA9_AA000400C8FE__INCLUDED_)
#define AFX_IPTEST_H__A20D9494_2062_11D1_9EA9_AA000400C8FE__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CIPTestApp:
// See IPTest.cpp for the implementation of this class
//

class CIPTestApp : public CWinApp
{
public:
	CIPTestApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIPTestApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CIPTestApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IPTEST_H__A20D9494_2062_11D1_9EA9_AA000400C8FE__INCLUDED_)
