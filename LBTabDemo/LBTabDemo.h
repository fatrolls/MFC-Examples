// LBTabDemo.h : main header file for the LBTABDEMO application
//

#if !defined(AFX_LBTABDEMO_H__D7B746A5_C6B1_11D3_BB51_CD4AD9600417__INCLUDED_)
#define AFX_LBTABDEMO_H__D7B746A5_C6B1_11D3_BB51_CD4AD9600417__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CLBTabDemoApp:
// See LBTabDemo.cpp for the implementation of this class
//

class CLBTabDemoApp : public CWinApp
{
public:
	CLBTabDemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLBTabDemoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CLBTabDemoApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LBTABDEMO_H__D7B746A5_C6B1_11D3_BB51_CD4AD9600417__INCLUDED_)
