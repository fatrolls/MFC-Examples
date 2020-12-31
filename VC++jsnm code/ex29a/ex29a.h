// ex29a.h : main header file for the EX29A application
//
#if !defined(AFX_EX29A_H__87130E75_8817_11D0_86C5_F5A2C72DE570__INCLUDED_)
#define AFX_EX29A_H__87130E75_8817_11D0_86C5_F5A2C72DE570__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CEx29aApp:
// See ex29a.cpp for the implementation of this class
//

class CEx29aApp : public CWinApp
{
public:
	CEx29aApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx29aApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CEx29aApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX29A_H__87130E75_8817_11D0_86C5_F5A2C72DE570__INCLUDED_)
