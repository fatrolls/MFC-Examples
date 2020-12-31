// docktest.cpp : Defines the class behaviors for the application.
//
// Docktest demo of Dockable Views functionality

#include "stdafx.h"
#include "utsampleabout.h"
#include "docktest.h"

#include "mainfrm.h"
#include "docktdoc.h"
#include "docktvw.h"
#include "dockchil.h"

#include "OXWorkspaceState.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDocktestApp

BEGIN_MESSAGE_MAP(CDocktestApp, CWinApp)
	//{{AFX_MSG_MAP(CDocktestApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDocktestApp construction

CDocktestApp::CDocktestApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CDocktestApp object

CDocktestApp theApp;
static HINSTANCE g_hRichEdDLL=NULL;

/////////////////////////////////////////////////////////////////////////////
// CDocktestApp initialization

BOOL CDocktestApp::InitInstance()
{
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.
	
#if _MSC_VER < 1400
	Enable3dControls();
#endif
   	SetRegistryKey(_T("DockTest"));

	// Initialize RichEdit control
	// for About Dialog
	if(g_hRichEdDLL==NULL)
	{
		g_hRichEdDLL=::LoadLibrary(_T("RICHED32.DLL"));
		if(g_hRichEdDLL==NULL)
			TRACE(_T("Cannot load library to display RichEditTextControl"));
	}

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(
		IDR_DOCKTETYPE,
		RUNTIME_CLASS(CDocktestDoc),
		RUNTIME_CLASS(CDockChildWnd),          // standard MDI child frame
		RUNTIME_CLASS(CDocktestView));
	AddDocTemplate(pDocTemplate);

	// create main MDI Frame window
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
		return FALSE;
	m_pMainWnd = pMainFrame;

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// The main window has been initialized, so show and update it.
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();

	// Since we allow floating control bars MDI child windows, and these can only be created once
	// we have a main window, we need to restore the bar size state here. (not on CMainFrame::OnCreate())
	pMainFrame->LoadSizeBarState(_T("DocktestBars"));
	pMainFrame->RecalcLayout();

	return TRUE;
}

// App command to run the dialog
void CDocktestApp::OnAppAbout()
{
	CUTSampleAboutDlg aboutDlg(IDR_MAINFRAME,ID_DESCRIPTION_FILE);
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CDocktestApp commands

void CDocktestApp::OnFileNew()
{
	static BOOL bFirstTime=TRUE;
	if(!bFirstTime)
		CWinApp::OnFileNew();
	bFirstTime=FALSE;
}


int CDocktestApp::ExitInstance() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	// unload the library
	if(g_hRichEdDLL!=NULL)
		::FreeLibrary(g_hRichEdDLL);

	return CWinApp::ExitInstance();
}
