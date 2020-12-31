// ex15b.h : main header file for the EX15B application
//

#if !defined(AFX_EX15B_H__4D011041_7E1C_11D0_8FE0_00C04FC2A0C2__INCLUDED_)
#define AFX_EX15B_H__4D011041_7E1C_11D0_8FE0_00C04FC2A0C2__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CEx15bApp:
// See ex15b.cpp for the implementation of this class
//

class CEx15bApp : public CWinApp
{
public:
	CEx15bApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEx15bApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CEx15bApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EX15B_H__4D011041_7E1C_11D0_8FE0_00C04FC2A0C2__INCLUDED_)
