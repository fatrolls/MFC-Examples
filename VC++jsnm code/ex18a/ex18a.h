// ex18a.h : main header file for the EX18A application
//

#if !defined(AFX_EX18A_H__3E2BDA83_892A_11D0_8FE3_00C04FC2A0C2__INCLUDED_)
#define AFX_EX18A_H__3E2BDA83_892A_11D0_8FE3_00C04FC2A0C2__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CEx18aApp:
// See ex18a.cpp for the implementation of this class
//

class CEx18aApp : public CWinApp
{
public:
	CEx18aApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx18aApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CEx18aApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX18A_H__3E2BDA83_892A_11D0_8FE3_00C04FC2A0C2__INCLUDED_)
