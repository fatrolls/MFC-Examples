// MvTest.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "MvTest.h"

#include "MainFrm.h"
#include "ChildFrame1.h"
#include "ChildFrame2.h"
#include "MvTestDoc.h"
#include "View1.h"
#include "View2.h"
#include "View3.h"
#include "View4.h"

#include "SDIMVDocTemplate.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMvTestApp

BEGIN_MESSAGE_MAP(CMvTestApp, CWinApp)
	//{{AFX_MSG_MAP(CMvTestApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMvTestApp construction

CMvTestApp::CMvTestApp()
{
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CMvTestApp object

CMvTestApp theApp;

static const CLSID clsid =
{ 0xa695b2bd, 0xde92, 0x11d1, { 0xb6, 0xbe, 0x0, 0xc0, 0x4f, 0xa3, 0x5f, 0x76 } };

/////////////////////////////////////////////////////////////////////////////
// CMvTestApp initialization

BOOL CMvTestApp::InitInstance()
{
	// Initialize OLE libraries
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	// Standard initialization

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	// Change the registry key under which our settings are stored.
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	// Register document templates

    CSDIMVDocTemplate *pDocTemplate = new CSDIMVDocTemplate( IDR_MVTESTTYPE, RUNTIME_CLASS( CMvTestDoc ) );
    pDocTemplate->AddFrameTemplate(
        new CFrameTemplate( 
            IDR_MV1, 
            RUNTIME_CLASS( CChildFrame1 ), 
            RUNTIME_CLASS( CView1 ), 
            ID_VIEW_VIEW1, 
            SW_SHOWNORMAL, 
            TRUE ) );

    pDocTemplate->AddFrameTemplate(
        new CFrameTemplate( 
            IDR_MV2, 
            RUNTIME_CLASS( CChildFrame1 ), 
            RUNTIME_CLASS( CView2 ), 
            ID_VIEW_VIEW2, 
            SW_SHOWNORMAL, 
            TRUE ) );

    pDocTemplate->AddFrameTemplate(
        new CFrameTemplate( 
            IDR_MV3, 
            RUNTIME_CLASS( CChildFrame2 ), 
            RUNTIME_CLASS( CView3 ), 
            ID_VIEW_VIEW3, 
            SW_SHOWNORMAL, 
            TRUE ) );

    pDocTemplate->AddFrameTemplate(
        new CFrameTemplate( 
            IDR_MV4, 
            RUNTIME_CLASS( CChildFrame2 ), 
            RUNTIME_CLASS( CView4 ), 
            ID_VIEW_VIEW4, 
            SW_SHOWNORMAL, 
            TRUE ) );

	AddDocTemplate(pDocTemplate);
	m_server.ConnectTemplate(clsid, pDocTemplate, FALSE);

	COleTemplateServer::RegisterAll();

	// create main MDI Frame window
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
		return FALSE;
	m_pMainWnd = pMainFrame;

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	if (cmdInfo.m_bRunEmbedded || cmdInfo.m_bRunAutomated)
	{
		// Application was run with /Embedding or /Automation.  Don't show the
		//  main window in this case.
		return TRUE;
	}

	m_server.UpdateRegistry(OAT_DISPATCH_OBJECT);
	COleObjectFactory::UpdateRegistryAll();

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
		// No message handlers
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CMvTestApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CMvTestApp commands
