// DHtmlEditDemo.h : main header file for the DHTMLEDITDEMO application
//

#if !defined(AFX_DHTMLEDITDEMO_H__FC2DA8A9_F895_48C1_9DDD_EA01F62D23E6__INCLUDED_)
#define AFX_DHTMLEDITDEMO_H__FC2DA8A9_F895_48C1_9DDD_EA01F62D23E6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CDHtmlEditDemoApp:
// See DHtmlEditDemo.cpp for the implementation of this class
//

class CDHtmlEditDemoApp : public CWinApp
{
public:
	CDHtmlEditDemoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDHtmlEditDemoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CDHtmlEditDemoApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DHTMLEDITDEMO_H__FC2DA8A9_F895_48C1_9DDD_EA01F62D23E6__INCLUDED_)
