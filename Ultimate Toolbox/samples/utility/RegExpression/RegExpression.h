// RegExpression.h : main header file for the REGEXPRESSION application
//

#if !defined(AFX_REGEXPRESSION_H__6858411A_9E83_11D3_AC4A_0050BAAB46B1__INCLUDED_)
#define AFX_REGEXPRESSION_H__6858411A_9E83_11D3_AC4A_0050BAAB46B1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CRegExpressionApp:
// See RegExpression.cpp for the implementation of this class
//

class CRegExpressionApp : public CWinApp
{
public:
	CRegExpressionApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRegExpressionApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CRegExpressionApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REGEXPRESSION_H__6858411A_9E83_11D3_AC4A_0050BAAB46B1__INCLUDED_)
