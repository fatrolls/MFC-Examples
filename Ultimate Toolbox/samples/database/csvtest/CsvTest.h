// CsvTest.h : main header file for the CSVTEST application
//

#if !defined(AFX_CSVTEST_H__ED9EE2A5_98D3_11D2_B0EC_0090271D78EB__INCLUDED_)
#define AFX_CSVTEST_H__ED9EE2A5_98D3_11D2_B0EC_0090271D78EB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CCsvTestApp:
// See CsvTest.cpp for the implementation of this class
//

class CCsvTestApp : public CWinApp
{
public:
	CCsvTestApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCsvTestApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CCsvTestApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CSVTEST_H__ED9EE2A5_98D3_11D2_B0EC_0090271D78EB__INCLUDED_)
