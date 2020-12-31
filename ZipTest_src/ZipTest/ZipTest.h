// ZipTest.h : main header file for the ZIPTEST application
//

#if !defined(AFX_ZIPTEST_H__B4E31130_A3AD_4826_8BAA_EDD91645BC0A__INCLUDED_)
#define AFX_ZIPTEST_H__B4E31130_A3AD_4826_8BAA_EDD91645BC0A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CZipTestApp:
// See ZipTest.cpp for the implementation of this class
//

class CZipTestApp : public CWinApp
{
public:
	CZipTestApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CZipTestApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CZipTestApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZIPTEST_H__B4E31130_A3AD_4826_8BAA_EDD91645BC0A__INCLUDED_)
