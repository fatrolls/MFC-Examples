// ShortcutBar.h : main header file for the SHORTCUTBAR application
//

#if !defined(AFX_SHORTCUTBAR_H__427CC918_FEDC_11D1_8872_0080C83F712F__INCLUDED_)
#define AFX_SHORTCUTBAR_H__427CC918_FEDC_11D1_8872_0080C83F712F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CShortcutBarApp:
// See ShortcutBar.cpp for the implementation of this class
//

class CShortcutBarApp : public CWinApp
{
public:
	CShortcutBarApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CShortcutBarApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CShortcutBarApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SHORTCUTBAR_H__427CC918_FEDC_11D1_8872_0080C83F712F__INCLUDED_)
