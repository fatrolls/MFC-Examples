// docktest.h : main header file for the DOCKTEST application
//
// Docktest demo of MRCEXT functionality
// $Revision:   1.0  $
// $Author:   MRC  $
// $Date:   11 Jul 1996 13:14:32  $

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CDocktestApp:
// See docktest.cpp for the implementation of this class
//

class CDocktestApp : public CWinApp
{
public:
	CDocktestApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDocktestApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CDocktestApp)
	afx_msg void OnAppAbout();
	afx_msg void OnVideoClip();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////
