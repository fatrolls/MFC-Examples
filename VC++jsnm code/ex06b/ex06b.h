// ex06b.h : main header file for the EX06B application
//

#if !defined(AFX_EX06B_H__6F45AD91_561B_11D0_8FCF_00C04FC2A0C2__INCLUDED_)
#define AFX_EX06B_H__6F45AD91_561B_11D0_8FCF_00C04FC2A0C2__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CEx06bApp:
// See ex06b.cpp for the implementation of this class
//

class CEx06bApp : public CWinApp
{
public:
	CEx06bApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx06bApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CEx06bApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX06B_H__6F45AD91_561B_11D0_8FCF_00C04FC2A0C2__INCLUDED_)
