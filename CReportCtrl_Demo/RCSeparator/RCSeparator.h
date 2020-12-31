// RCSeparator.h : main header file for the RCSEPARATOR application
//

#if !defined(AFX_RCSEPARATOR_H__E55C7048_23FC_4729_854B_8334E2E6A9C2__INCLUDED_)
#define AFX_RCSEPARATOR_H__E55C7048_23FC_4729_854B_8334E2E6A9C2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CRCSeparatorApp:
// See RCSeparator.cpp for the implementation of this class
//

class CRCSeparatorApp : public CWinApp
{
public:
	CRCSeparatorApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRCSeparatorApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CRCSeparatorApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RCSEPARATOR_H__E55C7048_23FC_4729_854B_8334E2E6A9C2__INCLUDED_)
