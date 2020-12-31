// StatText.h : main header file for the STATTEXT application
//

#if !defined(AFX_STATTEXT_H__A9D6005F_542B_11D1_A98F_0000929B340A__INCLUDED_)
#define AFX_STATTEXT_H__A9D6005F_542B_11D1_A98F_0000929B340A__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CStatTextApp:
// See StatText.cpp for the implementation of this class
//

class CStatTextApp : public CWinApp
{
public:
	CStatTextApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStatTextApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CStatTextApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STATTEXT_H__A9D6005F_542B_11D1_A98F_0000929B340A__INCLUDED_)
