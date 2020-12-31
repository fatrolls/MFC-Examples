// SkinMenuTest.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "SkinMenuTest.h"
#include "SkinMenuTestDlg.h"

#include "..\skinwindows\skinmenumgr.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSkinMenuTestApp

BEGIN_MESSAGE_MAP(CSkinMenuTestApp, CWinApp)
	//{{AFX_MSG_MAP(CSkinMenuTestApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSkinMenuTestApp construction

CSkinMenuTestApp::CSkinMenuTestApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CSkinMenuTestApp object

CSkinMenuTestApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CSkinMenuTestApp initialization

BOOL CSkinMenuTestApp::InitInstance()
{
	AfxEnableControlContainer();
	AfxInitRichEdit();

	CSkinMenuTestDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

int CSkinMenuTestApp::ExitInstance() 
{
	return CWinApp::ExitInstance();
}
