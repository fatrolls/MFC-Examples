// RulerBar.h : main header file for the RULERBAR application
//

#if !defined(AFX_RULERBAR_H__12E49E89_E788_11D2_A7F6_525400DAF3CE__INCLUDED_)
#define AFX_RULERBAR_H__12E49E89_E788_11D2_A7F6_525400DAF3CE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CRulerBarApp:
// See RulerBar.cpp for the implementation of this class
//

class CRulerBarApp : public CWinApp
{
public:
	CRulerBarApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRulerBarApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CRulerBarApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RULERBAR_H__12E49E89_E788_11D2_A7F6_525400DAF3CE__INCLUDED_)
