// TreeList.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "TreeList.h"
#include "TreeListDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTreeListApp

BEGIN_MESSAGE_MAP(CTreeListApp, CWinApp)
	//{{AFX_MSG_MAP(CTreeListApp)
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTreeListApp construction

CTreeListApp::CTreeListApp()
{
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CTreeListApp object

CTreeListApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CTreeListApp initialization

BOOL CTreeListApp::InitInstance()
{
	// Standard initialization

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	CTLFrame::RegisterClass();

	CTreeListDlg dlg;
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
