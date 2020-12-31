// TestDialogApp.h : main header file for the TESTDIALOGAPP application
//

#if !defined(AFX_TESTDIALOGAPP_H__A436497C_AD94_4CAF_8975_5ACB8B8187BC__INCLUDED_)
#define AFX_TESTDIALOGAPP_H__A436497C_AD94_4CAF_8975_5ACB8B8187BC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CTestDialogAppApp:
// See TestDialogApp.cpp for the implementation of this class
//

class CTestDialogAppApp : public CWinApp
{
public:
	CTestDialogAppApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestDialogAppApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CTestDialogAppApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTDIALOGAPP_H__A436497C_AD94_4CAF_8975_5ACB8B8187BC__INCLUDED_)
