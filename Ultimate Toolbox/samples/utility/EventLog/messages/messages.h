// messages.h : main header file for the MESSAGES DLL
//

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CMessagesApp
// See messages.cpp for the implementation of this class
//

class CMessagesApp : public CWinApp
{
public:
	CMessagesApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMessagesApp)
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CMessagesApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////
