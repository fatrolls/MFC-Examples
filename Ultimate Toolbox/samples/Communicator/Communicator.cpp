// Communicator.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "Communicator.h"
#include "utsampleAbout.h"
#include "MainFrm.h"
#include "ChildFrm.h"
#include "CommunicatorDoc.h"
#include "CommunicatorView.h"
#include "HexView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCommunicatorApp

BEGIN_MESSAGE_MAP(CCommunicatorApp, CWinApp)
	//{{AFX_MSG_MAP(CCommunicatorApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCommunicatorApp construction

CCommunicatorApp::CCommunicatorApp()
	:
	m_pHexDocTemplate(NULL)
	{
	}

/////////////////////////////////////////////////////////////////////////////
// The one and only CCommunicatorApp object

CCommunicatorApp theApp;
static HINSTANCE g_hRichEdDLL=NULL;

// This identifier was generated to be statistically unique for your app.
// You may change it if you prefer to choose a specific identifier.

// {F44C48E0-6DD7-11CF-8508-00AA0021F02C}
static const CLSID clsid =
{ 0xf44c48e0, 0x6dd7, 0x11cf, { 0x85, 0x8, 0x0, 0xaa, 0x0, 0x21, 0xf0, 0x2c } };

/////////////////////////////////////////////////////////////////////////////
// CCommunicatorApp initialization

BOOL CCommunicatorApp::InitInstance()
{
	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}

	// Initialize RichEdit control
	// for About Dialog
	if(g_hRichEdDLL==NULL)
	{
		g_hRichEdDLL=::LoadLibrary(_T("RICHED32.DLL"));
		if(g_hRichEdDLL==NULL)
			TRACE(_T("Cannot load library to display RichEditTextControl"));
	}


	// Initialize OLE libraries
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}



#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(
		IDR_COMMTYPE,
		RUNTIME_CLASS(CCommunicatorDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CCommunicatorView));
	AddDocTemplate(pDocTemplate);

	m_pHexDocTemplate = new CMultiDocTemplate(
		IDR_COMMTYPE,
		RUNTIME_CLASS(CCommunicatorDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CHexView));

	// Connect the COleTemplateServer to the document template.
	//  The COleTemplateServer creates new documents on behalf
	//  of requesting OLE containers by using information
	//  specified in the document template.
	m_server.ConnectTemplate(clsid, pDocTemplate, FALSE);

	// Register all OLE server factories as running.  This enables the
	//  OLE libraries to create objects from other applications.
	COleTemplateServer::RegisterAll();
		// Note: MDI applications register all server objects without regard
		//  to the /Embedding or /Automation on the command line.

	// create main MDI Frame window
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
		return FALSE;
	m_pMainWnd = pMainFrame;

	// Enable drag/drop open
	m_pMainWnd->DragAcceptFiles();

	// Enable DDE Execute open
	EnableShellOpen();
	RegisterShellFileTypes(TRUE);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// Check to see if launched as OLE server
	if (cmdInfo.m_bRunEmbedded || cmdInfo.m_bRunAutomated)
	{
		// Application was run with /Embedding or /Automation.  Don't show the
		//  main window in this case.
		return TRUE;
	}

	// When a server application is launched stand-alone, it is a good idea
	//  to update the system registry in case it has been damaged.
	m_server.UpdateRegistry(OAT_DISPATCH_OBJECT);
	COleObjectFactory::UpdateRegistryAll();

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// The main window has been initialized, so show and update it.
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About



// App command to run the dialog
void CCommunicatorApp::OnAppAbout()
{
	CUTSampleAboutDlg  aboutDlg(IDR_MAINFRAME,ID_DESCRIPTION_FILE);
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CCommunicatorApp commands

int CCommunicatorApp::ExitInstance() 
	{
	if (m_pHexDocTemplate != NULL)
		delete m_pHexDocTemplate;

	// unload the library
	if(g_hRichEdDLL!=NULL)
		::FreeLibrary(g_hRichEdDLL);

	return CWinApp::ExitInstance();
	}
