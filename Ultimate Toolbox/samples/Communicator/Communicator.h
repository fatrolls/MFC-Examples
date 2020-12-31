// Communicator.h : main header file for the COMMUNICATOR application
//
//----------------- Dundas Software ----------------------------------------                          
//========================================================================

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CCommunicatorApp:
// See Communicator.cpp for the implementation of this class
//

class CCommunicatorApp : public CWinApp
{
public:
	CCommunicatorApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCommunicatorApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
	COleTemplateServer m_server;
		// Server object for document creation

	CMultiDocTemplate* m_pHexDocTemplate;

	//{{AFX_MSG(CCommunicatorApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////
