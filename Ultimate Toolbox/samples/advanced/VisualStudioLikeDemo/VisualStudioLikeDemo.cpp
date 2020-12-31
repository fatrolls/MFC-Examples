// VisualStudioLikeDemo.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "VisualStudioLikeDemo.h"

#include "MainFrm.h"
#include "ChildFrm.h"
#include "VisualStudioLikeDemoDoc.h"
#include "VisualStudioLikeDemoView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVisualStudioLikeDemoApp

BEGIN_MESSAGE_MAP(CVisualStudioLikeDemoApp, CWinApp)
	//{{AFX_MSG_MAP(CVisualStudioLikeDemoApp)
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
// CVisualStudioLikeDemoApp construction

CVisualStudioLikeDemoApp::CVisualStudioLikeDemoApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CVisualStudioLikeDemoApp object

CVisualStudioLikeDemoApp theApp;
static HINSTANCE g_hRichEdDLL=NULL;
COXRegistryItem g_Registry;

/////////////////////////////////////////////////////////////////////////////
// CVisualStudioLikeDemoApp initialization

BOOL CVisualStudioLikeDemoApp::InitInstance()
{

	g_Registry.SetFullRegistryItem(
		_T("\\CurrentUser\\Software\\Ultimate Toolbox Samples\\VisualStudioLikeDemo\\"));
	CString sVersion=g_Registry.GetStringValue(_T("Version"));
	if (sVersion!=_T("1.1"))
	{
		while (TRUE)
		{
			CString sSubKey=g_Registry.EnumerateSubkey(0);
			if (!sSubKey.IsEmpty())
			{
				sSubKey=_T("\\CurrentUser\\Software\\Ultimate Toolbox Samples\\VisualStudioLikeDemo\\") + sSubKey +_T("\\");
				COXRegistryItem reg;
				reg.SetFullRegistryItem((LPCTSTR) sSubKey);
				reg.Delete();
			}
			else
				break;
		}
		g_Registry.Delete();
	}

	g_Registry.Close();

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

	// Initialize OLE libraries
	if(!AfxOleInit())
	{
		TRACE(_T("CVisualStudioLikeDemoApp::InitInstance: failed to initialize OLE libraries\n"));
		return FALSE;
	}


	AfxEnableControlContainer();

	// Change the registry key under which our settings are stored.
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("Ultimate Toolbox Samples"));

	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

#ifdef _MDI_INTERFACE
	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(
		IDR_VISUALTYPE,
		RUNTIME_CLASS(CVisualStudioLikeDemoDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CVisualStudioLikeDemoView));
	AddDocTemplate(pDocTemplate);

	// create main MDI Frame window
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
		return FALSE;
	m_pMainWnd = pMainFrame;
#else
	AddDocTemplate(new CSingleDocTemplate(IDR_MAINFRAME,
		RUNTIME_CLASS(CVisualStudioLikeDemoDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CVisualStudioLikeDemoView)));
#endif


	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);
#ifdef _MDI_INTERFACE
	if(cmdInfo.m_nShellCommand==CCommandLineInfo::FileNew)
		cmdInfo.m_nShellCommand=CCommandLineInfo::FileNothing;
#endif

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

#ifdef _MDI_INTERFACE
	// The main window has been initialized, so show and update it.
	((CMainFrame*)m_pMainWnd)->LoadWorkspace();
	((CMainFrame*)m_pMainWnd)->ShowWindow(m_nCmdShow);
	((CMainFrame*)m_pMainWnd)->UpdateWindow();
#endif

	return TRUE;
}


/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

#include "OXFontComboBox.h"

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
	virtual BOOL OnInitDialog();
	virtual void OnOK();
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
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CVisualStudioLikeDemoApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CVisualStudioLikeDemoApp message handlers



BOOL CAboutDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CAboutDlg::OnOK() 
{
	// TODO: Add extra validation here

	CDialog::OnOK();
}


int CVisualStudioLikeDemoApp::ExitInstance() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	// unload the library
	if(g_hRichEdDLL!=NULL)
		::FreeLibrary(g_hRichEdDLL);

	g_Registry.SetFullRegistryItem(
		_T("CurrentUser\\Software\\Ultimate Toolbox Samples\\VisualStudioLikeDemo\\"));
	g_Registry.SetStringValue(_T("1.1"),_T("Version"));

	return CWinApp::ExitInstance();
}
