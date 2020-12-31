// DriveTree.h : main header file for the DRIVETREE application
//

#if !defined(AFX_DRIVETREE_H__090B3825_959D_11D2_8E53_006008A82731__INCLUDED_)
#define AFX_DRIVETREE_H__090B3825_959D_11D2_8E53_006008A82731__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CDriveTreeApp:
// See DriveTree.cpp for the implementation of this class
//

class CDriveTreeApp : public CWinApp
{
public:
	CDriveTreeApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDriveTreeApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CDriveTreeApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DRIVETREE_H__090B3825_959D_11D2_8E53_006008A82731__INCLUDED_)
