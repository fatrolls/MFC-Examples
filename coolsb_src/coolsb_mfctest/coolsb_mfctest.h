// coolsb_mfctest.h : main header file for the COOLSB_MFCTEST application
//

#if !defined(AFX_COOLSB_MFCTEST_H__0EE2E7BC_7D56_4625_A192_F3F130C253E1__INCLUDED_)
#define AFX_COOLSB_MFCTEST_H__0EE2E7BC_7D56_4625_A192_F3F130C253E1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CCoolsb_mfctestApp:
// See coolsb_mfctest.cpp for the implementation of this class
//

class CCoolsb_mfctestApp : public CWinApp
{
public:
	CCoolsb_mfctestApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCoolsb_mfctestApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CCoolsb_mfctestApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COOLSB_MFCTEST_H__0EE2E7BC_7D56_4625_A192_F3F130C253E1__INCLUDED_)
