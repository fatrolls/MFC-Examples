// ex07b.h : main header file for the EX07B application
//

#if !defined(AFX_EX07B_H__1096E327_5958_11D0_8FCF_00C04FC2A0C2__INCLUDED_)
#define AFX_EX07B_H__1096E327_5958_11D0_8FCF_00C04FC2A0C2__INCLUDED_

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CEx07bApp:
// See ex07b.cpp for the implementation of this class
//

class CEx07bApp : public CWinApp
{
public:
	CEx07bApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx07bApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CEx07bApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX07B_H__1096E327_5958_11D0_8FCF_00C04FC2A0C2__INCLUDED_)
