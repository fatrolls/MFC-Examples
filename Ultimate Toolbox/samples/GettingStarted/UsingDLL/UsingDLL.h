// UsingDLL.h : main header file for the USINGDLL application
//

#if !defined(AFX_USINGDLL_H__79D3F732_28CF_42E3_8553_1F8E40B588B7__INCLUDED_)
#define AFX_USINGDLL_H__79D3F732_28CF_42E3_8553_1F8E40B588B7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CUsingDLLApp:
// See UsingDLL.cpp for the implementation of this class
//

class CUsingDLLApp : public CWinApp
{
public:
	CUsingDLLApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUsingDLLApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CUsingDLLApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_USINGDLL_H__79D3F732_28CF_42E3_8553_1F8E40B588B7__INCLUDED_)
