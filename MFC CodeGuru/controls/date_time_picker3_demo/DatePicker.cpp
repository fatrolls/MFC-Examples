// DatePicker.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "DatePicker.h"
#include "DatePickerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDatePickerApp

BEGIN_MESSAGE_MAP(CDatePickerApp, CWinApp)
	//{{AFX_MSG_MAP(CDatePickerApp)
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDatePickerApp construction

CDatePickerApp::CDatePickerApp()
{
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CDatePickerApp object

CDatePickerApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CDatePickerApp initialization

BOOL CDatePickerApp::InitInstance()
{
	AfxEnableControlContainer();

	// Standard initialization

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	CDatePickerDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
