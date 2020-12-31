#include "stdafx.h"
#include "GenericMFC.h"
#include "GenericMFCDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGenericMFCApp

BEGIN_MESSAGE_MAP(CGenericMFCApp, CWinApp)
	//{{AFX_MSG_MAP(CGenericMFCApp)
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGenericMFCApp construction

CGenericMFCApp::CGenericMFCApp()
{
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CGenericMFCApp object

CGenericMFCApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CGenericMFCApp initialization

BOOL CGenericMFCApp::InitInstance()
{
	CGenericMFCDlg dlg;
	m_pMainWnd = &dlg;
	dlg.DoModal();

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
} // End of InitInstance
