// RegEvent.h : main header file for the REGEVENT application
//

#if !defined(AFX_REGEVENT_H__8CB72080_D8EC_11D0_A21F_0000929B340A__INCLUDED_)
#define AFX_REGEVENT_H__8CB72080_D8EC_11D0_A21F_0000929B340A__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CRegEventApp:
// See RegEvent.cpp for the implementation of this class
//

class CRegEventApp : public CWinApp
{
public:
	CRegEventApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRegEventApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CRegEventApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REGEVENT_H__8CB72080_D8EC_11D0_A21F_0000929B340A__INCLUDED_)
