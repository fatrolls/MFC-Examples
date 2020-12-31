// ListBoxDemo.h : main header file for the LISTBOXDEMO application
//

#if !defined(AFX_LISTBOXDEMO_H__1A90F7B7_5A11_4469_8CD8_241B1FA14DFA__INCLUDED_)
#define AFX_LISTBOXDEMO_H__1A90F7B7_5A11_4469_8CD8_241B1FA14DFA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CListBoxDemoApp:
// See ListBoxDemo.cpp for the implementation of this class
//

class CListBoxDemoApp : public CWinApp
{
public:
	CListBoxDemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CListBoxDemoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CListBoxDemoApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LISTBOXDEMO_H__1A90F7B7_5A11_4469_8CD8_241B1FA14DFA__INCLUDED_)
