// FastTest.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "FastTest.h"

#include "MainFrm.h"
#include "ChildFrm.h"
#include "FastTestDoc.h"
#include "FastTestView.h"
#include "SlowView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFastTestApp

BEGIN_MESSAGE_MAP(CFastTestApp, CWinApp)
	//{{AFX_MSG_MAP(CFastTestApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_COMMAND(ID_FILE_FASTVIEW, OnFileFastview)
	ON_COMMAND(ID_FILE_SLOWVIEW, OnFileSlowview)
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFastTestApp construction

CFastTestApp::CFastTestApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CFastTestApp object

CFastTestApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CFastTestApp initialization

BOOL CFastTestApp::InitInstance()
{
    INITCOMMONCONTROLSEX    icx;
    icx.dwSize  = sizeof(INITCOMMONCONTROLSEX);
    icx.dwICC   = ICC_LISTVIEW_CLASSES;

    InitCommonControlsEx(&icx);

    try
    {
        CString strConnect;
        strConnect.Format("DSN=FASTDB;");
        if  (!m_DB.OpenEx(strConnect,CDatabase::useCursorLib))
        {
            AfxMessageBox("Unable to Connect to the Specified Data Source");
            return false;
        }
        
    }
    catch(CDBException *pE)
    {
        pE->ReportError();
        pE->Delete();
        return false;
    }

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
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	m_pFastTemplate = new CMultiDocTemplate(IDR_FASTTETYPE,
		                                    RUNTIME_CLASS(CFastTestDoc),
		                                    RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		                                    RUNTIME_CLASS(CFastTestView));
	AddDocTemplate(m_pFastTemplate);

	m_pSlowTemplate = new CMultiDocTemplate(IDR_FASTTETYPE,
		                                    RUNTIME_CLASS(CFastTestDoc),
		                                    RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		                                    RUNTIME_CLASS(CSlowView));
	AddDocTemplate(m_pSlowTemplate);

	// create main MDI Frame window
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
		return FALSE;
	m_pMainWnd = pMainFrame;

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);
    cmdInfo.m_nShellCommand = CCommandLineInfo::FileNothing;
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
void CFastTestApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CFastTestApp commands

void CFastTestApp::OnFileFastview() 
{
    ASSERT(m_pFastTemplate);
    m_pFastTemplate->OpenDocumentFile(NULL);
	
}

void CFastTestApp::OnFileSlowview() 
{
    ASSERT(m_pSlowTemplate);
    m_pSlowTemplate->OpenDocumentFile(NULL);
}
