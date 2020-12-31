// ex10a.h : main header file for the EX10A application
//

#if !defined(AFX_EX10A_H__297A65E5_652F_11D0_8FD4_00C04FC2A0C2__INCLUDED_)
#define AFX_EX10A_H__297A65E5_652F_11D0_8FD4_00C04FC2A0C2__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CEx10aApp:
// See ex10a.cpp for the implementation of this class
//

class CEx10aApp : public CWinApp
{
public:
	CEx10aApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx10aApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CEx10aApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX10A_H__297A65E5_652F_11D0_8FD4_00C04FC2A0C2__INCLUDED_)
