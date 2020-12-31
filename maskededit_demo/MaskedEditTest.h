// MaskedEditTest.h : main header file for the MASKEDEDITTEST application
//
/////////////////////////////////////////////////////////////////////////////

#ifndef __MaskedEditTest_h__
#define __MaskedEditTest_h__

#ifndef __AFXWIN_H__
#error include 'stdafx.h' before including this file for PCH
#endif

#include "MaskedEditTestResource.h"  // main symbols

/////////////////////////////////////////////////////////////////////////////
// CMaskedEditTestApp: See MaskedEditTest.cpp for the implementation of this class

class CMaskedEditTestApp : public CWinApp
	{
	public:
		CMaskedEditTestApp() ;
		
		// Overrides
		// ClassWizard generated virtual function overrides
		//{{AFX_VIRTUAL(CMaskedEditTestApp)
	public:
		virtual BOOL InitInstance() ;
	virtual int ExitInstance();
	//}}AFX_VIRTUAL
		
		// Implementation
		
		//{{AFX_MSG(CMaskedEditTestApp)
		//}}AFX_MSG
		DECLARE_MESSAGE_MAP()
	} ;

#endif // __MaskedEditTest_h__
/////////////////////////////////////////////////////////////////////////////
