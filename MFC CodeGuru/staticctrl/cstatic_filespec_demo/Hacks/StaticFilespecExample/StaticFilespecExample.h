// StaticFilespecExample.h : main header file for the STATICFILESPECEXAMPLE application
//

#if !defined(AFX_STATICFILESPECEXAMPLE_H__9D5597A5_6290_11D1_8C86_0000C01C0AED__INCLUDED_)
#define AFX_STATICFILESPECEXAMPLE_H__9D5597A5_6290_11D1_8C86_0000C01C0AED__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CStaticFilespecExampleApp:
// See StaticFilespecExample.cpp for the implementation of this class
//

class CStaticFilespecExampleApp : public CWinApp
{
public:
	CStaticFilespecExampleApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStaticFilespecExampleApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CStaticFilespecExampleApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STATICFILESPECEXAMPLE_H__9D5597A5_6290_11D1_8C86_0000C01C0AED__INCLUDED_)
