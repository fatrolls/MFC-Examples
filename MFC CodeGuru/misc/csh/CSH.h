// CSH.h : main header file for the CSH application
//

#if !defined(AFX_CSH_H__73AC62D8_CCD6_11D1_8018_A601086D0638__INCLUDED_)
#define AFX_CSH_H__73AC62D8_CCD6_11D1_8018_A601086D0638__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CCSHApp:
// See CSH.cpp for the implementation of this class
//

class CCSHApp : public CWinApp
{
public:
	CCSHApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCSHApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CCSHApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CSH_H__73AC62D8_CCD6_11D1_8018_A601086D0638__INCLUDED_)
