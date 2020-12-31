// CalUser.h : main header file for the CALUSER application
//

#if !defined(AFX_CALUSER_H__85FDD587_470B_11D2_AC96_006008A8274D__INCLUDED_)
#define AFX_CALUSER_H__85FDD587_470B_11D2_AC96_006008A8274D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CCalUserApp:
// See CalUser.cpp for the implementation of this class
//

class CCalUserApp : public CWinApp
{
public:
	CCalUserApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCalUserApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CCalUserApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CALUSER_H__85FDD587_470B_11D2_AC96_006008A8274D__INCLUDED_)
