// ex07a.h : main header file for the EX07A application
//

#if !defined(AFX_EX07A_H__4A59A8D7_5797_11D0_8FCF_00C04FC2A0C2__INCLUDED_)
#define AFX_EX07A_H__4A59A8D7_5797_11D0_8FCF_00C04FC2A0C2__INCLUDED_

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CEx07aApp:
// See ex07a.cpp for the implementation of this class
//

class CEx07aApp : public CWinApp
{
public:
	CEx07aApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx07aApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CEx07aApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX07A_H__4A59A8D7_5797_11D0_8FCF_00C04FC2A0C2__INCLUDED_)
