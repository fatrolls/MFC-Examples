// DIBManager.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "DIBManager.h"

#include "OXDocMgr.h"
#include "MainFrm.h"
#include "ChildFrm.h"
#include "DIBManagerDoc.h"
#include "DIBManagerView.h"
#include "WorkspaceDlg.h"
#include "ScaleRollupDlg.h"

#include "OXPreviewDialog.h"

#include "UTSampleAbout.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDIBManagerApp

BEGIN_MESSAGE_MAP(CDIBManagerApp, COXWinApp)
	//{{AFX_MSG_MAP(CDIBManagerApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_COMMAND(ID_FILE_NEW, OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	ON_COMMAND(ID_VIEW_WORKSPACE, OnViewWorkspace)
	//}}AFX_MSG_MAP
    ON_COMMAND (ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDIBManagerApp construction

CDIBManagerApp::CDIBManagerApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance

	m_pSplash=NULL;
	m_pScaleRollupDlg=NULL;
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CDIBManagerApp object

CDIBManagerApp theApp;
static HINSTANCE g_hRichEdDLL=NULL;

/////////////////////////////////////////////////////////////////////////////
// CDIBManagerApp initialization

BOOL CDIBManagerApp::InitInstance()
{
	// COXSplashWnd window
	// show splash window from the very beginning
	ShowSplashWindow(IDB_LOGO_DUMMY,ID_TIME_SHOWING_LOGO);
	Sleep(2000);

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

	// Initialize RichEdit control
	// for About Dialog
	if(g_hRichEdDLL==NULL)
	{
		g_hRichEdDLL=::LoadLibrary(_T("RICHED32.DLL"));
		if(g_hRichEdDLL==NULL)
			TRACE(_T("Cannot load library to display RichEditTextControl"));
	}

	// Change the registry key under which our settings are stored.
	// You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("Ultimate Toolbox Samples"));

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(
		IDR_DIBMANTYPE,
		RUNTIME_CLASS(CDIBManagerDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CDIBManagerView));
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

	IniAppVars();

	// The main window has been initialized, so show and update it.
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();

	// load the workspaces settings if needed
	if(m_bLoadWSOnEnter)
	{
		pMainFrame->LoadWorkspace();
	}

	// we made all preparations, so hide splash window
	HideSplashWindow();

	return TRUE;
}

// App command to run the dialog
void CDIBManagerApp::OnAppAbout()
{
	// we use our own About Dialog
	CUTSampleAboutDlg dlgAbout(IDR_MAINFRAME,ID_DESCRIPTION_FILE);
	dlgAbout.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CDIBManagerApp commands

CFileDialog* CDIBManagerApp::NewFileDialog(BOOL bOpenFileDialog, DWORD lFlags)
{
	// we provide functionality to open more than one file simultenuosly
	lFlags|=OFN_ALLOWMULTISELECT;
	// create the dialog with Preview capability
	return new COXPreviewDialog(bOpenFileDialog,NULL,NULL,
		OFN_ALLOWMULTISELECT|OFN_FILEMUSTEXIST|OFN_PATHMUSTEXIST|
		OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT);
}

void CDIBManagerApp::OnFileNew() 
{
	// TODO: Add your command handler code here
	// do nothing 
//	CWinApp::OnFileNew();
}

void CDIBManagerApp::OnFileOpen() 
{
	// TODO: Add your command handler code here
	CWinApp::OnFileOpen();
	
}

void CDIBManagerApp::OnViewWorkspace() 
{
	// TODO: Add your command handler code here

	CWorkspaceDlg workspaceDlg;

	workspaceDlg.m_bLoadOnEnter=m_bLoadWSOnEnter;
	workspaceDlg.m_bSaveOnExit=m_bSaveWSOnExit;

	if(workspaceDlg.DoModal()==IDOK)
	{
		m_bLoadWSOnEnter=workspaceDlg.m_bLoadOnEnter;
		m_bSaveWSOnExit=workspaceDlg.m_bSaveOnExit;
	}
}

int CDIBManagerApp::ExitInstance() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	// save all application variables in registry
	SaveAppVars();

	// if we used splash window then delete it
	if(m_pSplash!=NULL)
	{
		delete m_pSplash;
	}

	// unload the library
	if(g_hRichEdDLL!=NULL)
		::FreeLibrary(g_hRichEdDLL);


	return COXWinApp::ExitInstance();
}

void CDIBManagerApp::IniAppVars() 
{
	m_bLoadWSOnEnter=GetProfileInt(_T("WorkspaceOptions"),_T("LoadOnEnter"),TRUE);
	m_bSaveWSOnExit=GetProfileInt(_T("WorkspaceOptions"),_T("SaveOnExit"),TRUE);
}

void CDIBManagerApp::SaveAppVars() 
{
	WriteProfileInt(_T("WorkspaceOptions"),_T("LoadOnEnter"),m_bLoadWSOnEnter);
	WriteProfileInt(_T("WorkspaceOptions"),_T("SaveOnExit"),m_bSaveWSOnExit);
}

void CDIBManagerApp::ShowSplashWindow(UINT nBitmapID, UINT nTime) 
{
	// just load bitmap and set time to show splash window
	if(m_pSplash==NULL)
	{
		m_pSplash=new COXSplashWnd;
	}
	// the fourth parameter is level of tolerance which
	// indicates how much the color can be different from CLR_DEFAULT (which is white) 
	// before it is actually accepted as a different color 
	// for bitmap that we use in this application value of 150 is the best
	m_pSplash->LoadBitmap(nBitmapID,CLR_DEFAULT,NULL,0);
	m_pSplash->Show(nTime, NULL);
}

void CDIBManagerApp::HideSplashWindow(BOOL bRedrawMainFrame) 
{
	// if splash window was initialized then hide it and destroy
	if(m_pSplash!=NULL)
	{
		m_pSplash->Hide();
		
		delete m_pSplash;
		m_pSplash=NULL;

		// redraw mainframe if needed
		if(bRedrawMainFrame)
		{
			CMainFrame* pMainFrame=(CMainFrame*)m_pMainWnd;
			pMainFrame->RedrawWindow();
		}
	}
}

// if during loading of application error happened then hide splash window
// and notify about the error
void CDIBManagerApp::ErrorNotify(UINT nMsgID) 
{
	CString sMsg;
	sMsg.LoadString(nMsgID);
	ErrorNotify(sMsg);
}

void CDIBManagerApp::ErrorNotify(CString sMsg) 
{
	HideSplashWindow(TRUE);
	AfxMessageBox(sMsg,MB_OK|MB_ICONEXCLAMATION);
}
