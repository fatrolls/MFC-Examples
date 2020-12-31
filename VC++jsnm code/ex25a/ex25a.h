// ex25a.h : main header file for the EX25A application
//

#if !defined(AFX_EX25A_H__C4B9162B_98AE_11D0_85CF_9992596EDB70__INCLUDED_)
#define AFX_EX25A_H__C4B9162B_98AE_11D0_85CF_9992596EDB70__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CEx25aApp:
// See ex25a.cpp for the implementation of this class
//

class CEx25aApp : public CWinApp
{
public:
	CEx25aApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx25aApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CEx25aApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX25A_H__C4B9162B_98AE_11D0_85CF_9992596EDB70__INCLUDED_)
