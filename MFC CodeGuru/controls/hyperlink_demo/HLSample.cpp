// HLSample.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "HLSample.h"
#include "HLSampleDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHLSampleApp

BEGIN_MESSAGE_MAP(CHLSampleApp, CWinApp)
	//{{AFX_MSG_MAP(CHLSampleApp)
	//}}AFX_MSG
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHLSampleApp construction

CHLSampleApp::CHLSampleApp()
{
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CHLSampleApp object

CHLSampleApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CHLSampleApp initialization

BOOL CHLSampleApp::InitInstance()
{
	// Standard initialization

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	CHLSampleDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
