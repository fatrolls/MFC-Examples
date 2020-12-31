// SpinEx.h : main header file for the SPINEX application
//

#if !defined(AFX_SPINEX_H__B6E68EB8_1621_11D1_A271_0000929B340A__INCLUDED_)
#define AFX_SPINEX_H__B6E68EB8_1621_11D1_A271_0000929B340A__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CSpinExApp:
// See SpinEx.cpp for the implementation of this class
//

class CSpinExApp : public CWinApp
{
public:
	CSpinExApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSpinExApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CSpinExApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SPINEX_H__B6E68EB8_1621_11D1_A271_0000929B340A__INCLUDED_)
