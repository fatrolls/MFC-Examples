#include "stdafx.h"
#include "Once.h"

#include "MainFrm.h"
#include "ChildFrm.h"
#include "OnceDoc.h"
#include "OnceView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BEGIN_MESSAGE_MAP(COnceApp, CWinApp)
	//{{AFX_MSG_MAP(COnceApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

COnceApp::COnceApp()
{
	m_bRegistered=FALSE;
}

COnceApp theApp;

BOOL COnceApp::InitInstance()
{
	CWnd *pWndFrame;
	CWnd *pWndChild;
	WNDCLASS wndcls;

	if(pWndFrame=CWnd::FindWindow(ONCE_CLASSNAME, NULL))
	{
		pWndChild=pWndFrame->GetLastActivePopup();
		pWndFrame->BringWindowToTop();
		if(pWndFrame->IsIconic())pWndFrame->ShowWindow(SW_RESTORE);
		if(pWndFrame != pWndChild)pWndChild->SetForegroundWindow();
		return FALSE;
	}

    memset(&wndcls, 0, sizeof(WNDCLASS));
    wndcls.style=CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW;
    wndcls.lpfnWndProc=::DefWindowProc;
    wndcls.hInstance=AfxGetInstanceHandle();
    wndcls.hIcon=LoadIcon(IDR_MAINFRAME);
    wndcls.hCursor=LoadCursor(IDC_ARROW);
    wndcls.hbrBackground=(HBRUSH)(COLOR_WINDOW+1);
    wndcls.lpszMenuName=NULL;
    wndcls.lpszClassName=ONCE_CLASSNAME;

    if(!AfxRegisterClass(&wndcls))
    {
      TRACE("Class Registration Failed\n");
      return FALSE;
    }
    m_bRegistered=TRUE;

#ifdef _AFXDLL
	Enable3dControls();
#else
	Enable3dControlsStatic();
#endif

	SetRegistryKey(_T("Local AppWizard-Generated Applications"));
	LoadStdProfileSettings();
	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(
		IDR_ONCETYPE,
		RUNTIME_CLASS(COnceDoc),
		RUNTIME_CLASS(CChildFrame),
		RUNTIME_CLASS(COnceView));
	AddDocTemplate(pDocTemplate);

	CMainFrame* pMainFrame = new CMainFrame;
	if(!pMainFrame->LoadFrame(IDR_MAINFRAME))return FALSE;
	m_pMainWnd = pMainFrame;

	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	if(!ProcessShellCommand(cmdInfo))return FALSE;
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
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void COnceApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

int COnceApp::ExitInstance() 
{
	if(m_bRegistered == TRUE)
	{
		::UnregisterClass(ONCE_CLASSNAME, AfxGetInstanceHandle());
	}
	return CWinApp::ExitInstance();
}
