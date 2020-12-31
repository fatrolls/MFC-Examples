// TestPrintForm.h : main header file for the TESTPRINTFORM application
//

#if !defined(AFX_TESTPRINTFORM_H__F2067424_101A_11D2_8432_0000B43382FE__INCLUDED_)
#define AFX_TESTPRINTFORM_H__F2067424_101A_11D2_8432_0000B43382FE__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CTestPrintFormApp:
// See TestPrintForm.cpp for the implementation of this class
//

class CTestPrintFormApp : public CWinApp
{
public:
	CTestPrintFormApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestPrintFormApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CTestPrintFormApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTPRINTFORM_H__F2067424_101A_11D2_8432_0000B43382FE__INCLUDED_)
