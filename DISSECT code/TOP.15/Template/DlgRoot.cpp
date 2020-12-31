// $$root$$.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "$$root$$.h"
#include "$$dlg_hfile$$.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// $$APP_CLASS$$

BEGIN_MESSAGE_MAP($$APP_CLASS$$, $$APP_BASE_CLASS$$)
	//{{AFX_MSG_MAP($$APP_CLASS$$)
$$IF(VERBOSE)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
$$ENDIF
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// $$APP_CLASS$$ construction

$$APP_CLASS$$::$$APP_CLASS$$()
{
$$IF(VERBOSE)	
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
$$ENDIF
}

/////////////////////////////////////////////////////////////////////////////
// The one and only $$APP_CLASS$$ object

$$APP_CLASS$$ theApp;

/////////////////////////////////////////////////////////////////////////////
// $$APP_CLASS$$ initialization

BOOL $$APP_CLASS$$::InitInstance()
{
$$IF(SOCKETS)
	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}

$$ENDIF //SOCKETS
$$IF(AUTOMATION)
	// Initialize OLE libraries
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

$$ENDIF //AUTOMATION
$$IF(OLECTL)
	AfxEnableControlContainer();

$$ENDIF //OLECTL
	// Standard initialization
$$IF(VERBOSE)
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.
$$ENDIF

$$IF(3D)
#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

$$ENDIF //3D
$$IF(AUTOMATION)
$$IF(VERBOSE)
	// Parse the command line to see if launched as OLE server
$$ENDIF
	if (RunEmbedded() || RunAutomated())
	{
$$IF(VERBOSE)
		// Register all OLE server (factories) as running.  This enables the
		//  OLE libraries to create objects from other applications.
$$ENDIF
		COleTemplateServer::RegisterAll();
	}
	else
	{
$$IF(VERBOSE)
		// When a server application is launched stand-alone, it is a good idea
		//  to update the system registry in case it has been damaged.
$$ENDIF
		COleObjectFactory::UpdateRegistryAll();
	}

$$ENDIF //AUTOMATION
	$$DLG_CLASS$$ dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
$$IF(VERBOSE)
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
$$ENDIF
	}
	else if (nResponse == IDCANCEL)
	{
$$IF(VERBOSE)
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
$$ENDIF
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
