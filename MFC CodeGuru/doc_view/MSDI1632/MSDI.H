// msdi.h : main header file for the MSDI application
//

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CMsdiApp:
// See msdi.cpp for the implementation of this class
//

class CMsdiApp : public CMSDIWinApp
{
public:
	CMsdiApp();

// Overrides
	virtual BOOL InitInstance();

// Implementation

	//{{AFX_MSG(CMsdiApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////
