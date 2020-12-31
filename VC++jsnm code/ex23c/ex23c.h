// ex23c.h : main header file for the EX23C application
//

#if !defined(AFX_EX23C_H__4F329AF3_5DF1_11D0_848F_00400526305B__INCLUDED_)
#define AFX_EX23C_H__4F329AF3_5DF1_11D0_848F_00400526305B__INCLUDED_

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CEx23cApp:
// See ex23c.cpp for the implementation of this class
//

class CEx23cApp : public CWinApp
{
public:
	CEx23cApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx23cApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CEx23cApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX23C_H__4F329AF3_5DF1_11D0_848F_00400526305B__INCLUDED_)
