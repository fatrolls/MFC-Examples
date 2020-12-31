// MSDIDao.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "MSDIApp.h"
#include "MSDIDao.h"

#include "MainFrm.h"
#include "MSDIFrm.h"
#include "MSDIvFrm.h"
#include "TblFrame.h"

#include "DaoSet.h"
#include "DaoDoc.h"
#include "DaoView.h"

#include "TblView.h"
#include "CategTbl.h"
#include "CustTbl.h"

#include "CategVw.h"
#include "DIBApi.h"
#include "DIBView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMSDIDaoApp

BEGIN_MESSAGE_MAP(CMSDIDaoApp, CMSDIWinApp)
	//{{AFX_MSG_MAP(CMSDIDaoApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CMSDIWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMSDIDaoApp construction

CMSDIDaoApp::CMSDIDaoApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CMSDIDaoApp object

CMSDIDaoApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CMSDIDaoApp initialization

BOOL CMSDIDaoApp::InitInstance()
{
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	AddDocTemplate(new CMultiDocTemplate(
		IDR_MDIDAOTYPE,
		RUNTIME_CLASS(CMSDIDaoDoc),
		RUNTIME_CLASS(CMSDIFrame),	// custom MDI child frame
		RUNTIME_CLASS(CMSDIDaoView)));

	AddDocTemplate(new CMultiDocTemplate(
		IDR_CATEGTYPE,
		RUNTIME_CLASS(CMSDIDaoDoc),
		RUNTIME_CLASS(CDaoTableFrame),	// custom MDI child frame
		RUNTIME_CLASS(CCategoriesTable)));

	AddDocTemplate(new CMultiDocTemplate(
		IDR_CATEGTYPE,
		RUNTIME_CLASS(CMSDIDaoDoc),
		RUNTIME_CLASS(CMSDIViewFrame),	// custom MDI child frame
		RUNTIME_CLASS(CCategoriesView)));

	AddDocTemplate(new CMultiDocTemplate(
		IDR_CUSTOTYPE,
		RUNTIME_CLASS(CMSDIDaoDoc),
		RUNTIME_CLASS(CDaoTableFrame),	// custom MDI child frame
		RUNTIME_CLASS(CCustomersTable)));

	AddDocTemplate(new CMultiDocTemplate(
		IDR_DIBTYPE,
		NULL,
		RUNTIME_CLASS(CMSDIViewFrame),	// custom MDI child frame
		RUNTIME_CLASS(CDIBView)));

	// ... ADDALL

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

	// MSDIDAO: Do not try to open a new empty document
	if (cmdInfo.m_nShellCommand != CCommandLineInfo::FileNew)
	  if (!ProcessShellCommand(cmdInfo))
	    return FALSE;

	// The main window has been initialized, so show and update it.
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
void CMSDIDaoApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CMSDIDaoApp commands
