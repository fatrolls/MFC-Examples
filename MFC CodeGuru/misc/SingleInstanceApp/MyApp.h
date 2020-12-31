// MyApp.h : main header file for the MYAPP application
//

#if !defined(AFX_MYAPP_H__F5A1912B_E409_11D1_A6DF_00A0C9A23BCD__INCLUDED_)
#define AFX_MYAPP_H__F5A1912B_E409_11D1_A6DF_00A0C9A23BCD__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols
#include "SingleInstance.h"

/////////////////////////////////////////////////////////////////////////////
// CMyAppApp:
// See MyApp.cpp for the implementation of this class
//

class CMyAppApp : public CWinApp
{
public:
	CMyAppApp();
    CSingleInstance m_singleInstance;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyAppApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMyAppApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYAPP_H__F5A1912B_E409_11D1_A6DF_00A0C9A23BCD__INCLUDED_)
