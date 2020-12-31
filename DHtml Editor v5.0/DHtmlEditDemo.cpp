// DHtmlEditDemo.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "DHtmlEditDemo.h"
#include "DHtmlEditDemoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDHtmlEditDemoApp

BEGIN_MESSAGE_MAP(CDHtmlEditDemoApp, CWinApp)
	//{{AFX_MSG_MAP(CDHtmlEditDemoApp)
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDHtmlEditDemoApp construction

CDHtmlEditDemoApp::CDHtmlEditDemoApp()
{
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CDHtmlEditDemoApp object

CDHtmlEditDemoApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CDHtmlEditDemoApp initialization

BOOL CDHtmlEditDemoApp::InitInstance()
{
	#if _MSC_VER <= 1200 // Visual Studio 6
		#error This project is a special version for Visual Studio 7 ONLY! Please download the Visual Studio 6 version from CodeProject.com!!
	#endif

	InitCommonControls();

	CWinApp::InitInstance();

	CDHtmlEditDemoDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
	}
	else if (nResponse == IDCANCEL)
	{
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

