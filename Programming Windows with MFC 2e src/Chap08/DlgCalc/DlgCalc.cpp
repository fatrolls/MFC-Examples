// DlgCalc.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "DlgCalc.h"
#include "DlgCalcDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgCalcApp

BEGIN_MESSAGE_MAP(CDlgCalcApp, CWinApp)
	//{{AFX_MSG_MAP(CDlgCalcApp)
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgCalcApp construction

CDlgCalcApp::CDlgCalcApp()
{
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CDlgCalcApp object

CDlgCalcApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CDlgCalcApp initialization

BOOL CDlgCalcApp::InitInstance()
{
	CDlgCalcDlg dlg;
	m_pMainWnd = &dlg;
	dlg.DoModal ();
	return FALSE;
}
