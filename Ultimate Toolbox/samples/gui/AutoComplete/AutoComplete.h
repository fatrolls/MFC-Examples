// AutoComplete.h : main header file for the AUTOCOMPLETE application
//

#if !defined(AFX_AUTOCOMPLETE_H__7945FE1A_25D3_11D4_AD2F_0050BAAB46B1__INCLUDED_)
#define AFX_AUTOCOMPLETE_H__7945FE1A_25D3_11D4_AD2F_0050BAAB46B1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CAutoCompleteApp:
// See AutoComplete.cpp for the implementation of this class
//

class CAutoCompleteApp : public CWinApp
{
public:
	CAutoCompleteApp();
 
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAutoCompleteApp)
	public:
	virtual BOOL InitInstance();
	virtual int  ExitInstance();

	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CAutoCompleteApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AUTOCOMPLETE_H__7945FE1A_25D3_11D4_AD2F_0050BAAB46B1__INCLUDED_)
