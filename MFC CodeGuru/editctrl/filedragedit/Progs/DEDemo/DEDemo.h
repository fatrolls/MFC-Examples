// DEDemo.h : main header file for the DEDEMO application
//

#if !defined(AFX_DEDEMO_H__1D8BBDEF_784C_11D1_8159_444553540000__INCLUDED_)
#define AFX_DEDEMO_H__1D8BBDEF_784C_11D1_8159_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CDEDemoApp:
// See DEDemo.cpp for the implementation of this class
//

class CDEDemoApp : public CWinApp
{
public:
	CDEDemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDEDemoApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CDEDemoApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DEDEMO_H__1D8BBDEF_784C_11D1_8159_444553540000__INCLUDED_)
