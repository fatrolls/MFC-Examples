// ex26a.h : main header file for the EX26A application
//

#if !defined(AFX_EX26A_H__BE454449_5F51_11D0_848F_00400526305B__INCLUDED_)
#define AFX_EX26A_H__BE454449_5F51_11D0_848F_00400526305B__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CEx26aApp:
// See ex26a.cpp for the implementation of this class
//

class CEx26aApp : public CWinApp
{
public:
	CEx26aApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx26aApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CEx26aApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX26A_H__BE454449_5F51_11D0_848F_00400526305B__INCLUDED_)
