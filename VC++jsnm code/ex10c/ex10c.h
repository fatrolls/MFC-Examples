// ex10c.h : main header file for the EX10C application
//

#if !defined(AFX_EX10C_H__1A050A17_6602_11D0_8FD6_00C04FC2A0C2__INCLUDED_)
#define AFX_EX10C_H__1A050A17_6602_11D0_8FD6_00C04FC2A0C2__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CEx10cApp:
// See ex10c.cpp for the implementation of this class
//

class CEx10cApp : public CWinApp
{
public:
	CEx10cApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx10cApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CEx10cApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX10C_H__1A050A17_6602_11D0_8FD6_00C04FC2A0C2__INCLUDED_)
