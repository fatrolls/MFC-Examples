// Spider.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "Spider.h"
#include "ThreadParams.h"
#include "Thread.h"

#include "MainFrm.h"
#include "ChildFrm.h"
#include "SpiderDoc.h"
#include "SpiderView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CSpiderApp

BEGIN_MESSAGE_MAP(CSpiderApp, CWinApp)
	//{{AFX_MSG_MAP(CSpiderApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSpiderApp construction

CSpiderApp::CSpiderApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CSpiderApp object

CSpiderApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CSpiderApp initialization

BOOL CSpiderApp::InitInstance()
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

	// Change the registry key under which our settings are stored.
	// You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	LoadStdProfileSettings(8);  // Load standard INI file options (including MRU)
	ReadProfile();

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(
		IDR_SPIDERTYPE,
		RUNTIME_CLASS(CSpiderDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CSpiderView));
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
	/*
if(cmdInfo.m_nShellCommand == CCommandLineInfo::FileNew)
   cmdInfo.m_nShellCommand = CCommandLineInfo::FileNothing;
*/

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
void CSpiderApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CSpiderApp commands
void CSpiderApp::WriteProfile()
{

	if(!m_HomeDir.IsEmpty())
		WriteProfileString("Directory","Home", (LPCTSTR)m_HomeDir);

}

//
// Read in the profile specific to PerlPad
//
void CSpiderApp::ReadProfile()
{
	m_HomeDir = GetProfileString("Directory", "Home",NULL);
	char lpBuffer[260];
	GetCurrentDirectory(MAX_PATH,(LPTSTR) lpBuffer);

	if(m_HomeDir.IsEmpty())
		m_HomeDir.Format("%s",lpBuffer);


}
int CSpiderApp::ExitInstance()
{

	WriteProfile();

	return CWinApp::ExitInstance();
}

void CSpiderApp::ShowURL(LPCTSTR lpFileName,CString& text) 
{
	CString  rString,strTitle;
	rString = text;

	strTitle.Format("%s",lpFileName);
	strTitle += '\0';

	int pos = strTitle.ReverseFind('/');
	if (pos > 0)
		 strTitle= strTitle.Right(strTitle.GetLength() - pos - 1);
	pos = strTitle.Find('.');
	if (pos > 0)
		 strTitle= strTitle.Left(pos);

	OnFileNew(); 

	// Open the URL as a  file.
	CSpiderDoc *PSpiderDoc = NULL;
	PSpiderDoc =CSpiderDoc::GetDoc();
	if (PSpiderDoc)
	{
		PSpiderDoc->ShowURL(rString); 	
   		PSpiderDoc->SetTitle(strTitle);
   }




}
