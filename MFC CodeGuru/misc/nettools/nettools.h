// nettools.h : main header file for the NETTOOLS application
//

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols
#define WM_USER_PING_DONE (WM_USER + 1)
#define WM_USER_PING_PRINT (WM_USER + 2)
#define WM_USER_INET_DONE  (WM_USER+ 3)
#define WM_USER_INET_PRINT (WM_USER+ 4)
#define WM_USER_INET_TABS (WM_USER+ 5)

/////////////////////////////////////////////////////////////////////////////
// CNettoolsApp:
// See nettools.cpp for the implementation of this class
//

class CNettoolsApp : public CWinApp
{
public:
	CNettoolsApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNettoolsApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CNettoolsApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////
