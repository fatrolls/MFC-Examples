// TCLBDemo.h : main header file for the TCLBDEMO application
//

#if !defined(AFX_TCLBDEMO_H__BC64B6E7_F097_11D1_A0F1_006097B18B90__INCLUDED_)
#define AFX_TCLBDEMO_H__BC64B6E7_F097_11D1_A0F1_006097B18B90__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CTCLBDemoApp:
// See TCLBDemo.cpp for the implementation of this class
//

class CTCLBDemoApp : public CWinApp
{
public:
	CTCLBDemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTCLBDemoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CTCLBDemoApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TCLBDEMO_H__BC64B6E7_F097_11D1_A0F1_006097B18B90__INCLUDED_)
