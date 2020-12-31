#if !defined(EX08C_H__6084D1F5_488C_11D0_8488_00400526305B__INCLUDED_)
#define EX08C_H__6084D1F5_488C_11D0_8488_00400526305B__INCLUDED_

// ex08c.h : main header file for the EX08C application
//

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CEx08cApp:
// See ex08c.cpp for the implementation of this class
//

class CEx08cApp : public CWinApp
{
public:
	CEx08cApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx08cApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CEx08cApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(EX08C_H__6084D1F5_488C_11D0_8488_00400526305B__INCLUDED)
