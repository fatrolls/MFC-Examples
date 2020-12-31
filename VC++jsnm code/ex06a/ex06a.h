// ex06a.h : main header file for the EX06A application
//

#if !defined(AFX_EX06A_H__0A7D2CAF_5186_11D0_8FCC_00C04FC2A0C2__INCLUDED_)
#define AFX_EX06A_H__0A7D2CAF_5186_11D0_8FCC_00C04FC2A0C2__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CEx06aApp:
// See ex06a.cpp for the implementation of this class
//

class CEx06aApp : public CWinApp
{
public:
	CEx06aApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx06aApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CEx06aApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX06A_H__0A7D2CAF_5186_11D0_8FCC_00C04FC2A0C2__INCLUDED_)
