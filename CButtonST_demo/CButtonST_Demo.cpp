#include "stdafx.h"
#include "CButtonST_Demo.h"
#include "CButtonST_DemoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BEGIN_MESSAGE_MAP(CCButtonST_DemoApp, CWinApp)
	//{{AFX_MSG_MAP(CCButtonST_DemoApp)
	//}}AFX_MSG
	//ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCButtonST_DemoApp construction

CCButtonST_DemoApp::CCButtonST_DemoApp()
{
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CCButtonST_DemoApp object

CCButtonST_DemoApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CCButtonST_DemoApp initialization

BOOL CCButtonST_DemoApp::InitInstance()
{
	// Standard initialization

	CCButtonST_DemoDlg dlg;
	m_pMainWnd = &dlg;
	dlg.DoModal();

	return FALSE;
} // End of InitInstance
