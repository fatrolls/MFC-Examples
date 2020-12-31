// ComboExDemo.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "ComboExDemo.h"
#include "ComboExDemoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CComboExDemoApp

BEGIN_MESSAGE_MAP(CComboExDemoApp, CWinApp)
	//{{AFX_MSG_MAP(CComboExDemoApp)
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CComboExDemoApp construction

CComboExDemoApp::CComboExDemoApp()
{
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CComboExDemoApp object

CComboExDemoApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CComboExDemoApp initialization

BOOL CComboExDemoApp::InitInstance()
{
	// Standard initialization

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	CComboExDemoDlg dlg;
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
