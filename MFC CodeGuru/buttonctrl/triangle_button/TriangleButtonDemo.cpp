// TriangleButtonDemo.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "TriangleButtonDemo.h"
#include "TriangleButtonDemoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTriangleButtonDemoApp

BEGIN_MESSAGE_MAP(CTriangleButtonDemoApp, CWinApp)
	//{{AFX_MSG_MAP(CTriangleButtonDemoApp)
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTriangleButtonDemoApp construction

CTriangleButtonDemoApp::CTriangleButtonDemoApp()
{
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CTriangleButtonDemoApp object

CTriangleButtonDemoApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CTriangleButtonDemoApp initialization

BOOL CTriangleButtonDemoApp::InitInstance()
{
	// Standard initialization

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	CTriangleButtonDemoDlg dlg;
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
