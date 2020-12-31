// AdvancedTrace.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "AdvancedTrace.h"
#include "AdvancedTraceDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAdvancedTraceApp

BEGIN_MESSAGE_MAP(CAdvancedTraceApp, CWinApp)
	//{{AFX_MSG_MAP(CAdvancedTraceApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAdvancedTraceApp construction

CAdvancedTraceApp::CAdvancedTraceApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CAdvancedTraceApp object

CAdvancedTraceApp theApp;
static HINSTANCE g_hRichEdDLL=NULL;

/////////////////////////////////////////////////////////////////////////////
// CAdvancedTraceApp initialization

BOOL CAdvancedTraceApp::InitInstance()
{
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

	OXTRACE_SETDUMPFILE(_T("TraceTest.txt"));
	OXTRACE_SETFLUSH(TRUE);

	OXTRACE(_T("AdvancedTrace Demo"));

	OXTRACE_WRITE(_T("Enable 3D controls"));
#if _MSC_VER < 1400
#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif
#endif

	OXTRACE_WRITE(_T("Initialize RichEdit control"));
	// Initialize RichEdit control
	// for About Dialog
	if(g_hRichEdDLL==NULL)
	{
		g_hRichEdDLL=::LoadLibrary(_T("RICHED32.DLL"));
		if(g_hRichEdDLL==NULL)
			TRACE(_T("Cannot load library to display RichEditTextControl"));
	}

	OXTRACE_WRITE(_T("Create Dialog"));

	CAdvancedTraceDlg dlg;
	m_pMainWnd = &dlg;
	switch(dlg.DoModal())
	{
	case IDOK:
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
		break;
	case IDCANCEL:
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}
		break;
	}

	OXTRACE_WRITE(_T("Close Application"));

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}

int CAdvancedTraceApp::ExitInstance() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	OXTRACE(_T("Clean up"));
	OXTRACE_WRITE(_T("Unload the library for rich edit text support"));
	// unload the library
	if(g_hRichEdDLL!=NULL)
		::FreeLibrary(g_hRichEdDLL);

	return CWinApp::ExitInstance();
}
