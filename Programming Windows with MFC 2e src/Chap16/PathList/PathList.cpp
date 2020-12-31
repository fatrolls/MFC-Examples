// PathList.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "PathList.h"
#include "PathComboBox.h"
#include "PathListDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPathListApp

BEGIN_MESSAGE_MAP(CPathListApp, CWinApp)
	//{{AFX_MSG_MAP(CPathListApp)
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPathListApp construction

CPathListApp::CPathListApp()
{
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CPathListApp object

CPathListApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CPathListApp initialization

BOOL CPathListApp::InitInstance()
{
	// Standard initialization

	CPathListDlg dlg;
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
