// HyperbarDemo.h : main header file for the HYPERBARDEMO application
//

#if !defined(AFX_HYPERBARDEMO_H__B1D15F19_634B_434A_BDCF_477E6E64EA2C__INCLUDED_)
#define AFX_HYPERBARDEMO_H__B1D15F19_634B_434A_BDCF_477E6E64EA2C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CHyperbarDemoApp:
// See HyperbarDemo.cpp for the implementation of this class
//

class CHyperbarDemoApp : public CWinApp
{
public:
	CHyperbarDemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHyperbarDemoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CHyperbarDemoApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HYPERBARDEMO_H__B1D15F19_634B_434A_BDCF_477E6E64EA2C__INCLUDED_)
