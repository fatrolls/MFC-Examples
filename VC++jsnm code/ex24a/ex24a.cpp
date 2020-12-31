// ex24a.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "ex24a.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx24aApp

BEGIN_MESSAGE_MAP(CEx24aApp, CWinApp)
	//{{AFX_MSG_MAP(CEx24aApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx24aApp construction

CEx24aApp::CEx24aApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CEx24aApp object

CEx24aApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CEx24aApp initialization

BOOL CEx24aApp::InitInstance()
{
	AfxOleInit();
	if (RunEmbedded() || RunAutomated())
	{
		// component started by COM	
		COleTemplateServer::RegisterAll();
		return TRUE;
	}
	// Component is being run directly by the user
	COleObjectFactory::UpdateRegistryAll();
	AfxMessageBox("Bank component is registered"); // add this line
	return FALSE;
}
