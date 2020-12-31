// docktest.cpp : Defines the class behaviors for the application.
//
// Docktest demo of MRCEXT functionality
// $Revision:   1.0  $
// $Author:   MRC  $
// $Date:   11 Jul 1996 13:14:30  $

#include "stdafx.h"
#include "docktest.h"
#include "videocli.h"

#include "mainfrm.h"
#include "docktdoc.h"
#include "docktvw.h"
#include "dockchil.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDocktestApp

BEGIN_MESSAGE_MAP(CDocktestApp, CWinApp)
	//{{AFX_MSG_MAP(CDocktestApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_COMMAND(ID_VideoClip, OnVideoClip)
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
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

/////////////////////////////////////////////////////////////////////////////
// CDocktestApp initialization

BOOL CDocktestApp::InitInstance()
{
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.
	
	Enable3dControls();
   	SetRegistryKey("DockTest");

	// A simple splash screen. On a fast machine this won't appear for very long.
	// We do a check for the number of colors the hardware supports, and display different
	// bitmaps for 256 and 16-colors. This is so you can have a cool 256-color image,
	// and still look ok on a 16-color machine.
#ifndef _DEBUG			// don't do this for debugging as it can get in the way
	CMRCColorLabel * pSplash = new CMRCColorLabel;
	if (GetNumberSystemColors() < 256)
		pSplash->CreateSplash(16, 0, TRUE);
	else
		pSplash->CreateSplash(256, CLBS_BITMAP_PALETTE, TRUE);
#endif

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

	if (m_lpCmdLine[0] != '\0')
	{
		// TODO: add command line processing here
	}

	// Since we allow floating control bars MDI child windows, and these can only be created once
	// we have a main window, we need to restore the bar size state here. (not on CMainFrame::OnCreate())
	//pMainFrame->LoadSizeBarState("DocktestBars");
	pMainFrame->RecalcLayout();

	// The main window has been initialized, so show and update it.
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();

	// get rid of the splash screen...
#ifndef _DEBUG
	pSplash->DestroyWindow();
#endif

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

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
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
void CDocktestApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CDocktestApp commands

void CDocktestApp::OnVideoClip() 
{
	CVideoClipDialog dlg;
	dlg.DoModal();
}
