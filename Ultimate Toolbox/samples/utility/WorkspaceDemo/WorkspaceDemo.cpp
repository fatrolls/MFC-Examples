// WorkspaceDemo.cpp : Defines the class behaviors for the application.
//
//====================================================================
//===============  Dundas Software ==================================
//===================================================================
#include "stdafx.h"
#include "utsampleabout.h"
#include "WorkspaceDemo.h"

#include "MainFrm.h"
#include "ChildFrm.h"
#include "WorkspaceTextDoc.h"
#include "WorkspaceTextView.h"
#include "WorkspaceLengthView.h"
#include "WorkspaceGraphDoc.h"
#include "WorkspaceGraphView.h"
#include "SplitChildFrm.h"
#include "WorkspaceDlg.h"
#include "OXWorkspaceState.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWorkspaceDemoApp

BEGIN_MESSAGE_MAP(CWorkspaceDemoApp, CWinApp)
//{{AFX_MSG_MAP(CWorkspaceDemoApp)
ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
ON_COMMAND(ID_TOOLS_WORKSPACES, OnToolsWorkspaces)
ON_COMMAND(ID_WINDOW_CLOSEALL, OnWindowCloseall)
//}}AFX_MSG_MAP
// Standard file based document commands
ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
// Standard print setup command
ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWorkspaceDemoApp construction

CWorkspaceDemoApp::CWorkspaceDemoApp()
:
m_pTextDocTemplate(NULL),
m_pLengthDocTemplate(NULL),
m_pGraphDocTemplate(NULL)
	{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
	}

/////////////////////////////////////////////////////////////////////////////
// The one and only CWorkspaceDemoApp object

CWorkspaceDemoApp theApp;
static HINSTANCE g_hRichEdDLL=NULL;

/////////////////////////////////////////////////////////////////////////////
// CWorkspaceDemoApp initialization

BOOL CWorkspaceDemoApp::InitInstance()
	{
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.
	
#if _MSC_VER < 1400
#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif
#endif


	// Initialize RichEdit control
	// for About Dialog
	if(g_hRichEdDLL==NULL)
	{
		g_hRichEdDLL=::LoadLibrary(_T("RICHED32.DLL"));
		if(g_hRichEdDLL==NULL)
			TRACE(_T("Cannot load library to display RichEditTextControl"));
	}

	// Set the comapny name
	SetRegistryKey(_T("Dundas"));

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)
	
	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.
	
	m_pTextDocTemplate = new CMultiDocTemplate(
		IDR_WORKSPTYPE,
		RUNTIME_CLASS(CWorkspaceTextDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CWorkspaceTextView));
	AddDocTemplate(m_pTextDocTemplate);
	
	m_pLengthDocTemplate = new CMultiDocTemplate(
		IDR_LENGTHTYPE,
		RUNTIME_CLASS(CWorkspaceTextDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CWorkspaceLengthView));
	AddDocTemplate(m_pLengthDocTemplate);
	
	m_pGraphDocTemplate = new CMultiDocTemplate(
		IDR_GRAPHTYPE,
		RUNTIME_CLASS(CWorkspaceGraphDoc),
		RUNTIME_CLASS(CSplitChildFrame), // custom splitter MDI child frame
		RUNTIME_CLASS(CWorkspaceGraphView));
	AddDocTemplate(m_pGraphDocTemplate);
	
	// create main MDI Frame window
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
		return FALSE;
	m_pMainWnd = pMainFrame;
	
	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);
	
	// Do not open a new (empty) doc by default
	if (cmdInfo.m_nShellCommand == CCommandLineInfo::FileNew)
		cmdInfo.m_nShellCommand = CCommandLineInfo::FileNothing;
	
	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;
	
	// The main window has been initialized, so show and update it.
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();
	
	COXWorkspaceState workspaceState;
	if (!workspaceState.LoadFromRegistry())
		TRACE0("CWorkspaceDemoApp::InitInstance : Failed to load workspace from registry, continuing\n");
	
	return TRUE;
	}

CString CWorkspaceDemoApp::GetAppDir() const
	{
	CString sAppDir;
	LPTSTR pszAppDir = sAppDir.GetBuffer(_MAX_PATH);
	VERIFY(::GetModuleFileName(AfxGetInstanceHandle(), pszAppDir, _MAX_PATH));
	sAppDir.ReleaseBuffer();
	int nBackSlashPos = sAppDir.ReverseFind(_T('\\'));
	ASSERT(nBackSlashPos != -1);
	if (nBackSlashPos != -1)
		sAppDir = sAppDir.Left(nBackSlashPos + 1);
	
	return sAppDir;
	}

/////////////////////////////////////////////////////////////////////////////

// App command to run the dialog
void CWorkspaceDemoApp::OnAppAbout()
	{
	CUTSampleAboutDlg aboutDlg(IDR_MAINFRAME,ID_DESCRIPTION_FILE);
	aboutDlg.DoModal();
	}

/////////////////////////////////////////////////////////////////////////////
// CWorkspaceDemoApp commands

void CWorkspaceDemoApp::OnToolsWorkspaces() 
	{
	CWorkspaceDlg workspaceDlg;
	workspaceDlg.DoModal();
	}

void CWorkspaceDemoApp::OnWindowCloseall() 
	{
	// See also Microsoft System Journal, December 1995 Number 12, C/C++ Q&A
	
#ifdef NEVER
	// Use this if you want pressing Cancel for any doc to
	// cancel the entire Close All operation, and leave
	// ALL documents still open.
	
	if (SaveAllModified())
		CloseAllDocuments(FALSE);
#else
	// Use this if you want pressing Cancel to close whatever
	// documents the user has already said it’s OK to close,
	// but leave the remaining ones open.
	
	POSITION templatePos = GetFirstDocTemplatePosition();
	while (templatePos != NULL) 
		{
		CDocTemplate* pTemplate = GetNextDocTemplate(templatePos);
		ASSERT_KINDOF(CDocTemplate, pTemplate);
		POSITION docPos = pTemplate->GetFirstDocPosition();
		while (docPos != NULL) 
			{
			CDocument* pDoc = pTemplate->GetNextDoc(docPos);
			if (!pDoc->SaveModified())
				// ... User aborted
				return;        
			pDoc->OnCloseDocument();
			}
		}
#endif
	}

int CWorkspaceDemoApp::ExitInstance() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	// unload the library
	if(g_hRichEdDLL!=NULL)
		::FreeLibrary(g_hRichEdDLL);

	return CWinApp::ExitInstance();
}
