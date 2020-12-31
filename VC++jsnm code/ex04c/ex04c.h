// ex04c.h : main header file for the EX04C application
//

#if !defined(AFX_EX04C_H__94911C03_4FAD_11D0_8FCB_00C04FC2A0C2__INCLUDED_)
#define AFX_EX04C_H__94911C03_4FAD_11D0_8FCB_00C04FC2A0C2__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CEx04cApp:
// See ex04c.cpp for the implementation of this class
//

class CEx04cApp : public CWinApp
{
public:
	CEx04cApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx04cApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CEx04cApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX04C_H__94911C03_4FAD_11D0_8FCB_00C04FC2A0C2__INCLUDED_)
