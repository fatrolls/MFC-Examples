// testdi.h : main header file for the TESTDI application
//

#if !defined(AFX_TESTDI_H__6EA700CC_0AF3_11D2_9768_0080C858DB41__INCLUDED_)
#define AFX_TESTDI_H__6EA700CC_0AF3_11D2_9768_0080C858DB41__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CTestdiApp:
// See testdi.cpp for the implementation of this class
//

class CTestdiApp : public CWinApp
{
public:
	CTestdiApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestdiApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CTestdiApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTDI_H__6EA700CC_0AF3_11D2_9768_0080C858DB41__INCLUDED_)
