// LayoutManager.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "LayoutManager.h"
#include "UTSampleAbout.h"
#include "MainFrm.h"
#include "LayoutManagerDoc.h"
#include "LayoutManagerView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLayoutManagerApp

BEGIN_MESSAGE_MAP(CLayoutManagerApp, CWinApp)
	//{{AFX_MSG_MAP(CLayoutManagerApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLayoutManagerApp construction

CLayoutManagerApp::CLayoutManagerApp()
{
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CLayoutManagerApp object

CLayoutManagerApp theApp;
static HINSTANCE g_hRichEdDLL=NULL;

/////////////////////////////////////////////////////////////////////////////
// CLayoutManagerApp initialization

BOOL CLayoutManagerApp::InitInstance()
{
	// Standard initialization

#if _MSC_VER < 1400
#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif
#endif


	LoadStdProfileSettings(0);  // Load standard INI file options (including MRU)

	// Initialize RichEdit control
	// for About Dialog
	if(g_hRichEdDLL==NULL)
	{
		g_hRichEdDLL=::LoadLibrary(_T("RICHED32.DLL"));
		if(g_hRichEdDLL==NULL)
			TRACE(_T("Cannot load library to display RichEditTextControl"));
	}

	// Register document templates

	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CLayoutManagerDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CLayoutManagerView));
	AddDocTemplate(pDocTemplate);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	return TRUE;
}

// App command to run the dialog
void CLayoutManagerApp::OnAppAbout()
{
	CUTSampleAboutDlg aboutDlg(IDR_MAINFRAME,ID_DESCRIPTION_FILE);
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CLayoutManagerApp commands

int CLayoutManagerApp::ExitInstance() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	// unload the library
	if(g_hRichEdDLL!=NULL)
		::FreeLibrary(g_hRichEdDLL);

	return CWinApp::ExitInstance();
}
