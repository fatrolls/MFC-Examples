// PrintManager.h : main header file for the PRINTMANAGER application
//

#if !defined(AFX_PRINTMANAGER_H__8BEC3134_9E36_11D1_8BB1_0000B43382FE__INCLUDED_)
#define AFX_PRINTMANAGER_H__8BEC3134_9E36_11D1_8BB1_0000B43382FE__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CPrintManagerApp:
// See PrintManager.cpp for the implementation of this class
//

class CPrintManagerApp : public CWinApp
{
public:
	CPrintManagerApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPrintManagerApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CPrintManagerApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PRINTMANAGER_H__8BEC3134_9E36_11D1_8BB1_0000B43382FE__INCLUDED_)
