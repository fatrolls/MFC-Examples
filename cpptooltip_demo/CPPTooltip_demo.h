// CPPTooltip_demo.h : main header file for the CPPTOOLTIP_DEMO application
//

#if !defined(AFX_CPPTOOLTIP_DEMO_H__6AC13296_F503_4148_A139_F678ED177C6C__INCLUDED_)
#define AFX_CPPTOOLTIP_DEMO_H__6AC13296_F503_4148_A139_F678ED177C6C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CPPTooltip_demoApp:
// See CPPTooltip_demo.cpp for the implementation of this class
//

class CPPTooltip_demoApp : public CWinApp
{
public:
	CPPTooltip_demoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPPTooltip_demoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CPPTooltip_demoApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CPPTOOLTIP_DEMO_H__6AC13296_F503_4148_A139_F678ED177C6C__INCLUDED_)
