// dtset.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "resource.h"
#include "dtset.h"
#include "dtsetDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDTSetApp

BEGIN_MESSAGE_MAP(CDTSetApp, CWinApp)
	//{{AFX_MSG_MAP(CDTSetApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDTSetApp construction

CDTSetApp::CDTSetApp()
{
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CDTSetApp object

CDTSetApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CDTSetApp initialization

BOOL CDTSetApp::InitInstance()
{
	Enable3dControls();

  //use the main help file for the dtime package
  m_sHelpFilePath = m_pszHelpFilePath;
  int nIndex = m_sHelpFilePath.ReverseFind('\\');
  m_sHelpFilePath = m_sHelpFilePath.Left(nIndex+1) + CString("DTIME.HLP");
  m_pszHelpFilePath = m_sHelpFilePath;

  //Initialise the DTime package
  InitDTime();

  //create the settings dialog
	CDTSetDlg dlg;
	m_pMainWnd = &dlg;

  //load the settings from the registry
  dlg.LoadSettings();

  //bring up the dialog
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		//update the settings in the registry
    dlg.SaveSettings();
	}
	
  // Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

void CDTSetApp::WinHelp(DWORD /*dwData*/, UINT /*nCmd*/) 
{
  //always bring up the contents page
	CWinApp::WinHelp(0, HELP_CONTENTS);
}



int CDTSetApp::ExitInstance() 
{
	//finished with the DTime package
  TermDTime();
	
	return CWinApp::ExitInstance();
}
