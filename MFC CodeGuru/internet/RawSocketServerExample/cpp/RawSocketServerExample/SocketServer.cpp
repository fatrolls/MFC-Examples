// SocketServer.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "SocketServer.h"
#include "SocketServerDlg.h"
#include <afxsock.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CSocketServerApp

BEGIN_MESSAGE_MAP(CSocketServerApp, CWinApp)
	//{{AFX_MSG_MAP(CSocketServerApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSocketServerApp construction

CSocketServerApp::CSocketServerApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CSocketServerApp object

CSocketServerApp theApp;


/////////////////////////////////////////////////////////////////////////////
// CSocketServerApp initialization

BOOL CSocketServerApp::InitInstance()
{
	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	try
		{
		Worker worker;
		CWizThreadDispatcher dispatcher (worker, 6);
		dispatcher.Start();
		CSocketServerDlg dlg(worker,dispatcher);
		m_pMainWnd = &dlg;
		dlg.DoModal();
		dispatcher.WaitShutDown();
		}
	catch(...)
		{
		ASSERT(0);
		throw;
		}
	return FALSE;
}
