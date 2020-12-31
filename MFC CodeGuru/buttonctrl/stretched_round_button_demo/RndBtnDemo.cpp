// RndBtnDemo.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "RndBtnDemo.h"
#include "RndBtnDemoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRndBtnDemoApp

BEGIN_MESSAGE_MAP(CRndBtnDemoApp, CWinApp)
	//{{AFX_MSG_MAP(CRndBtnDemoApp)
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRndBtnDemoApp construction

CRndBtnDemoApp::CRndBtnDemoApp()
{
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CRndBtnDemoApp object

CRndBtnDemoApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CRndBtnDemoApp initialization

BOOL CRndBtnDemoApp::InitInstance()
{
	// Standard initialization

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	CRndBtnDemoDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();

	return FALSE;
}
