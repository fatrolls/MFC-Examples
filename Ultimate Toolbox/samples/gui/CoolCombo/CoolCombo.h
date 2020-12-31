// CoolCombo.h : main header file for the COOLCOMBO application
//

#if !defined(AFX_COOLCOMBO_H__FE6B1BC9_A5BD_11D2_B475_00E0291A4FD3__INCLUDED_)
#define AFX_COOLCOMBO_H__FE6B1BC9_A5BD_11D2_B475_00E0291A4FD3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CCoolComboApp:
// See CoolCombo.cpp for the implementation of this class
//

class CCoolComboApp : public CWinApp
{
public:
	CCoolComboApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCoolComboApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CCoolComboApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COOLCOMBO_H__FE6B1BC9_A5BD_11D2_B475_00E0291A4FD3__INCLUDED_)
