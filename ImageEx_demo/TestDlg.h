// TestDlg.h : main header file for the TESTDLG application
//

#if !defined(AFX_TESTDLG_H__00ACB8F1_829F_4751_86F5_FB3DA13C4564__INCLUDED_)
#define AFX_TESTDLG_H__00ACB8F1_829F_4751_86F5_FB3DA13C4564__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CTestDlgApp:
// See TestDlg.cpp for the implementation of this class
//

class CTestDlgApp : public CWinApp
{
public:
	CTestDlgApp();

   // GDI+
   GdiplusStartupInput		m_gdiplusStartupInput;
   ULONG_PTR				m_gdiplusToken;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestDlgApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CTestDlgApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTDLG_H__00ACB8F1_829F_4751_86F5_FB3DA13C4564__INCLUDED_)
