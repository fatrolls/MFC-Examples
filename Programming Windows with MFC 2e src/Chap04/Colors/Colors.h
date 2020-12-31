// Colors.h : main header file for the COLORS application
//

#if !defined(AFX_COLORS_H__1B036BE8_5C6F_11D2_8E53_006008A82731__INCLUDED_)
#define AFX_COLORS_H__1B036BE8_5C6F_11D2_8E53_006008A82731__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CColorsApp:
// See Colors.cpp for the implementation of this class
//

class CColorsApp : public CWinApp
{
public:
	CColorsApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CColorsApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

public:
	//{{AFX_MSG(CColorsApp)
	afx_msg void OnAppAbout();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COLORS_H__1B036BE8_5C6F_11D2_8E53_006008A82731__INCLUDED_)
