//********************************************
// Tool.cpp 
//********************************************
// pierre.alliez@cnet.francetelecom.fr
// Created :
// Modified
//********************************************


#include "stdafx.h"
#include "Tool.h"

#include "DlgAbout.h"
#include "MainFrm.h"
#include "ChildFrm.h"
#include "ToolDoc.h"
#include "RenderView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CToolApp

BEGIN_MESSAGE_MAP(CToolApp, CWinApp)
	//{{AFX_MSG_MAP(CToolApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CToolApp construction

CToolApp::CToolApp()
{
	// Options
	m_OptionColorGlBack = RGB(0,0,0);
	// ****** TODO ******
	m_OptionColorGlLightAmbient = RGB(200,200,200); 
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CToolApp object

CToolApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CToolApp initialization

BOOL CToolApp::InitInstance()
{
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

	// Change the registry key under which our settings are stored.
	// You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("3D Toolbox"));

	LoadStdProfileSettings(10);  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(
		IDR_MODELTYPE,
		RUNTIME_CLASS(CToolDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CRenderView));
	AddDocTemplate(pDocTemplate);

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

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// Load options
	LoadOptions();

	// The main window has been initialized, so show and update it.
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();

	return TRUE;
}


// App command to run the dialog
void CToolApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CToolApp commands

int CToolApp::ExitInstance() 
{
	SaveOptions();	
	return CWinApp::ExitInstance();
}




//**************************************************
// LoadOptions
// Load from registry
//**************************************************
BOOL CToolApp::LoadOptions()
{
	unsigned int red,green,blue;

	// Gl back color
	red = GetProfileInt("OpenGL back color","Red",0);
	green = GetProfileInt("OpenGL back color","Green",0);
	blue = GetProfileInt("OpenGL back color","Blue",0);
	m_OptionColorGlBack = RGB(red,green,blue);

	// Gl light ambient color
	red = GetProfileInt("OpenGL light ambient color","Red",200);
	green = GetProfileInt("OpenGL light ambient color","Green",200);
	blue = GetProfileInt("OpenGL light ambient color","Blue",200);
	m_OptionColorGlLightAmbient = RGB(red,green,blue);
	
	return TRUE;
}

//**************************************************
// SaveOptions
// Load from registry
//**************************************************
BOOL CToolApp::SaveOptions()
{
	unsigned char red,green,blue;

	// Gl back color
	red = GetRValue(m_OptionColorGlBack);
	green = GetGValue(m_OptionColorGlBack);
	blue = GetBValue(m_OptionColorGlBack);
	WriteProfileInt("OpenGL back color","Red",red);
	WriteProfileInt("OpenGL back color","Green",green);
	WriteProfileInt("OpenGL back color","Blue",blue);
	
	// Gl light ambient color
	red = GetRValue(m_OptionColorGlLightAmbient);
	green = GetGValue(m_OptionColorGlLightAmbient);
	blue = GetBValue(m_OptionColorGlLightAmbient);
	WriteProfileInt("OpenGL light ambient color","Red",red);
	WriteProfileInt("OpenGL light ambient color","Green",green);
	WriteProfileInt("OpenGL light ambient color","Blue",blue);
	
	return TRUE;
}

