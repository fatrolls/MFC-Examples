// RegistryDemo.h : main header file for the REGISTRYDEMO application
//

#if !defined(AFX_REGISTRYDEMO_H__CE454E21_E84D_11D1_8063_0A9C28000000__INCLUDED_)
#define AFX_REGISTRYDEMO_H__CE454E21_E84D_11D1_8063_0A9C28000000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols
#include "Registry.h"

/////////////////////////////////////////////////////////////////////////////
// CRegistryDemoApp:
// See RegistryDemo.cpp for the implementation of this class
//

class CRegistryDemoApp : public CWinApp
{
public:
	CRegistryDemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRegistryDemoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CRegistryDemoApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// Attributes
public:
	CRegistry mPrefs;
};

extern CRegistryDemoApp theApp;

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REGISTRYDEMO_H__CE454E21_E84D_11D1_8063_0A9C28000000__INCLUDED_)
