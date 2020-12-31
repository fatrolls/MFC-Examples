// Tangram.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "objbase.h"
#include "Tangram.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTangramApp

BEGIN_MESSAGE_MAP(CTangramApp, CWinApp)
	//{{AFX_MSG_MAP(CTangramApp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTangramApp construction

CTangramApp::CTangramApp()
{
}

CTangramApp::~CTangramApp()
{
	// Uninitialize the COM Library.
	::CoUninitialize() ;
}


/////////////////////////////////////////////////////////////////////////////
// The one and only CTangramApp object

CTangramApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CTangramApp initialization

BOOL CTangramApp::InitInstance()
{

	// Initialize the COM Library.
	::CoInitialize(NULL) ;

	// Create the main window.
	CMainFrame* pMainWnd = new CMainFrame ;
	ASSERT(pMainWnd) ;

	// Create the main window.
	if (pMainWnd->Create())
	{
		m_pMainWnd = pMainWnd ;
		return TRUE ;
	}
	else
	{
		TRACE0("CTangramApp::InitInstance CMainWnd::Create Failed.\r\n") ;
		// We do not need to delete pMainWnd. PostNcDestory does it for us.
		//delete pMainWnd ;
		return FALSE ;
	}
}

/////////////////////////////////////////////////////////////////////////////
// CTangramApp commands
