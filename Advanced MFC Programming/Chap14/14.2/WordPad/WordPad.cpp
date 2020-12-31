#include "stdafx.h"
#include "WordPad.h"
#include "MainFrm.h"
#include "WPDoc.h"
#include "WPView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BEGIN_MESSAGE_MAP(CWordPadApp, CWinApp)
	//{{AFX_MSG_MAP(CWordPadApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

CWordPadApp theApp;

CWordPadApp::CWordPadApp()
{
}

BOOL CWordPadApp::InitInstance()
{
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

#ifdef _AFXDLL
	Enable3dControls();
#else
	Enable3dControlsStatic();
#endif

	SetRegistryKey(_T("Local AppWizard-Generated Applications"));
	LoadStdProfileSettings();

	CSingleDocTemplate *pDocTemplate;
	pDocTemplate=new CSingleDocTemplate
	(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CWordPadDoc),
		RUNTIME_CLASS(CMainFrame),
		RUNTIME_CLASS(CWordPadView)
	);
	pDocTemplate->SetContainerInfo(IDR_CNTR_INPLACE);
	AddDocTemplate(pDocTemplate);
	EnableShellOpen();
	RegisterShellFileTypes(TRUE);
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);
	if(!ProcessShellCommand(cmdInfo))return FALSE;
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
	m_pMainWnd->DragAcceptFiles();

	return TRUE;
}

void CWordPadApp::OnFileOpen() 
{
	CFileDialog	dlg(TRUE);
	CString szName;
	CRichEditDoc *pDoc;

    dlg.m_ofn.lpstrFilter=STRING_FILTER;
    dlg.m_ofn.nFilterIndex=1;
	if(dlg.DoModal() == IDOK)szName=dlg.GetPathName();
	pDoc=(CRichEditDoc *)(((CFrameWnd *)m_pMainWnd)->GetActiveDocument());
	if(dlg.m_ofn.nFilterIndex == 1)
	{
		pDoc->m_bRTF=TRUE;
	}
	else pDoc->m_bRTF=FALSE;
	OpenDocumentFile(szName);
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

void CWordPadApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}
