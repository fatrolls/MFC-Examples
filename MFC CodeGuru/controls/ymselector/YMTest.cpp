// YMTest.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "YMTest.h"
#include "YMTestDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CYMTestApp

BEGIN_MESSAGE_MAP(CYMTestApp, CWinApp)
	//{{AFX_MSG_MAP(CYMTestApp)
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CYMTestApp construction

CYMTestApp::CYMTestApp()
{
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CYMTestApp object

CYMTestApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CYMTestApp initialization

BOOL CYMTestApp::InitInstance()
{
	// Standard initialization

	CYMTestDlg dlg;
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
