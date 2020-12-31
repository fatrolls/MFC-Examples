// ex04a.h : main header file for the EX04A application
//

#if !defined(AFX_EX04A_H__B188BE39_6377_11D0_8FD4_00C04FC2A0C2__INCLUDED_)
#define AFX_EX04A_H__B188BE39_6377_11D0_8FD4_00C04FC2A0C2__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CEx04aApp:
// See ex04a.cpp for the implementation of this class
//

class CEx04aApp : public CWinApp
{
public:
	CEx04aApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx04aApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CEx04aApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX04A_H__B188BE39_6377_11D0_8FD4_00C04FC2A0C2__INCLUDED_)
