// ex08a.h : main header file for the EX08A application
//

#if !defined(AFX_EX08A_H__1917788B_6F24_11D0_8FD9_00C04FC2A0C2__INCLUDED_)
#define AFX_EX08A_H__1917788B_6F24_11D0_8FD9_00C04FC2A0C2__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CEx08aApp:
// See ex08a.cpp for the implementation of this class
//

class CEx08aApp : public CWinApp
{
public:
	CEx08aApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx08aApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CEx08aApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX08A_H__1917788B_6F24_11D0_8FD9_00C04FC2A0C2__INCLUDED_)
