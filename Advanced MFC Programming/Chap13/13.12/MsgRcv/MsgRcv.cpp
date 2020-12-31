#include "stdafx.h"
#include "MsgRcv.h"

#include "MainFrm.h"
#include "RcvDoc.h"
#include "RcvView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BEGIN_MESSAGE_MAP(CMsgRcvApp, CWinApp)
	//{{AFX_MSG_MAP(CMsgRcvApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

CMsgRcvApp::CMsgRcvApp()
{
	m_bRegistered=FALSE;
}

CMsgRcvApp theApp;

BOOL CMsgRcvApp::InitInstance()
{
	WNDCLASS wndcls;

	memset(&wndcls, 0, sizeof(WNDCLASS));
    wndcls.style=CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW;
    wndcls.lpfnWndProc=::DefWindowProc;
    wndcls.hInstance=AfxGetInstanceHandle();
    wndcls.hIcon=LoadIcon(IDR_MAINFRAME);
    wndcls.hCursor=LoadCursor(IDC_ARROW);
    wndcls.hbrBackground=(HBRUSH)(COLOR_WINDOW+1);
    wndcls.lpszMenuName=MAKEINTRESOURCE(IDR_MAINFRAME);
    wndcls.lpszClassName=CLASS_NAME_RECIEVER;

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
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CMsgRcvDoc),
		RUNTIME_CLASS(CMainFrame),
		RUNTIME_CLASS(CMsgRcvView));
	AddDocTemplate(pDocTemplate);

	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	if(!ProcessShellCommand(cmdInfo))return FALSE;
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();

	return TRUE;
}

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	//}}AFX_VIRTUAL

protected:
	//{{AFX_MSG(CAboutDlg)
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

void CMsgRcvApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

int CMsgRcvApp::ExitInstance() 
{
	if(m_bRegistered == TRUE)
	{
		::UnregisterClass(CLASS_NAME_RECIEVER, AfxGetInstanceHandle());
	}	
	return CWinApp::ExitInstance();
}
