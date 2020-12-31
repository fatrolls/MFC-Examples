// AgTest.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "AgTest.h"
#include "AgTestDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAgTestApp

BEGIN_MESSAGE_MAP(CAgTestApp, CWinApp)
	//{{AFX_MSG_MAP(CAgTestApp)
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAgTestApp construction

CAgTestApp::CAgTestApp()
{
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CAgTestApp object

CAgTestApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CAgTestApp initialization

BOOL CAgTestApp::InitInstance()
{
  // Link to agent
  AgentDefineSystem(MT_SYSTEM,"Test application for Runtime Monitoring Agent");
  AgentDefineProcess(MT_SYSTEM,MT_PROCESS,"Dialog based application");
  AgentDefineFiber(MT_PROCESS,MT_INIT,"Initialization/termination events");
  AgentDefineFiber(MT_PROCESS,MT_EDIT,"Interaction with an edit control");
  AgentDefineFiber(MT_PROCESS,MT_CHECKBOX,"Interaction with a checkbox group");
  AgentDefineFiber(MT_PROCESS,MT_RADIO,"Interaction with a radio button group");
  AgentDefineFiber(MT_PROCESS,MT_THREAD,"Background worker thread");

  // Standard initialization
  AGENT(MT_INIT,"Program initialization",0);

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	CAgTestDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
	}
	else if (nResponse == IDCANCEL)
	{
	}

  AGENT(MT_INIT,"Program termination",0);

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
