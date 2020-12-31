// VolumeControl.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "VolumeControl.h"
#include "VolumeControlDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVolumeControlApp

BEGIN_MESSAGE_MAP(CVolumeControlApp, CWinApp)
	//{{AFX_MSG_MAP(CVolumeControlApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVolumeControlApp construction

CVolumeControlApp::CVolumeControlApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CVolumeControlApp object

CVolumeControlApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CVolumeControlApp initialization

BOOL CVolumeControlApp::InitInstance()
{
	CreateMutex( NULL, TRUE, PROG_INSTANCE_NAME );
	if( GetLastError() == ERROR_ALREADY_EXISTS ) 
    { 
		HWND hChatterWnd = FindWindow( NULL, PROG_NAME );
		ShowWindow( hChatterWnd, SW_RESTORE );

        MessageBox( NULL, "Volume Control already running", "Volume Control",
			MB_OK | MB_ICONASTERISK ); 
		
        return FALSE;
    }

	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif	

	CVolumeControlDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
