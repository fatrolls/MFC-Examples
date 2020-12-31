// MyPad.h : main header file for the MYPAD application
//

#if !defined(AFX_MYPAD_H__0FA1D284_8471_11D2_8E53_006008A82731__INCLUDED_)
#define AFX_MYPAD_H__0FA1D284_8471_11D2_8E53_006008A82731__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CMyPadApp:
// See MyPad.cpp for the implementation of this class
//

class CMyPadApp : public CWinApp
{
public:
	CMyPadApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMyPadApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

public:
	//{{AFX_MSG(CMyPadApp)
	afx_msg void OnAppAbout();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYPAD_H__0FA1D284_8471_11D2_8E53_006008A82731__INCLUDED_)
