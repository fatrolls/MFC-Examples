// shelldocDlg.cpp : implementation file
//

#include "stdafx.h"
#include "shelldoc.h"
#include "shelldocDlg.h"
#include "DlgProxy.h"
#include "shdocvw.h"
#include "shlguid.h"
#include "shlobj.h"
#include "initguid.h"
//13709620-C279-11CE-A49E-444553540000
DEFINE_GUID(CLSID_Shell,0x13709620,0xc279,0x11ce,0xa4,0x9e,0x44,0x45,0x53,0x54,0x00,0x00);
//9BA05971-F6A8-11CF-A442-00A0C90A8F39
DEFINE_GUID(CLSID_ShellFolderViewOC ,0x9BA05971,0xF6A8,0x11CF,0xa4,0x43,0x00,0xa0,0xc9,0x0a,0x8f,0x39);
//9BA05972-F6A8-11CF-A442-00A0C90A8F39
DEFINE_GUID(CLSID_ShellWindows,0x9BA05972,0xF6A8,0x11CF,0xa4,0x43,0x00,0xa0,0xc9,0x0a,0x8f,0x39);
//11219420-1768-11D1-95BE-00609797EA4F
DEFINE_GUID(CLSID_ShellLinkObject,0x11219420,0x1768,0x11D1,0x95,0xbe,0x00,0x60,0x97,0x97,0xea,0x4f);
//62112AA1-EBE4-11CF-A5FB-0020AFE7292D
DEFINE_GUID(CLSID_ShellFolderView,0x62112AA1,0xEBE4,0x11CF,0xA5,0xfb,0x00,0x20,0xaf,0xe7,0x29,0x2d);
//64AB4BB7-111E-11D1-8F79-00C04FC2FBE1
DEFINE_GUID(CLSID_ShellUIHelper,0x64AB4BB7,0x111E,0x11D1,0x8f,0x79,0x00,0xc0,0x4f,0xc2,0xfb,0xe1);



#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

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

/////////////////////////////////////////////////////////////////////////////
// CShelldocDlg dialog

IMPLEMENT_DYNAMIC(CShelldocDlg, CDialog);

CShelldocDlg::CShelldocDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CShelldocDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CShelldocDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pAutoProxy = NULL;
}

CShelldocDlg::~CShelldocDlg()
{
	// If there is an automation proxy for this dialog, set
	//  its back pointer to this dialog to NULL, so it knows
	//  the dialog has been deleted.
	if (m_pAutoProxy != NULL)
		m_pAutoProxy->m_pDialog = NULL;
}

void CShelldocDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CShelldocDlg)
	DDX_Control(pDX, IDC_STATICX, m_xDispName);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CShelldocDlg, CDialog)
	//{{AFX_MSG_MAP(CShelldocDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CShelldocDlg message handlers

BOOL CShelldocDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CShelldocDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CShelldocDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CShelldocDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

// Automation servers should not exit when a user closes the UI
//  if a controller still holds on to one of its objects.  These
//  message handlers make sure that if the proxy is still in use,
//  then the UI is hidden but the dialog remains around if it
//  is dismissed.

void CShelldocDlg::OnClose() 
{
	if (CanExit())
		CDialog::OnClose();
}

void CShelldocDlg::OnOK() 
{
	if (CanExit())
		CDialog::OnOK();
}

void CShelldocDlg::OnCancel() 
{
	if (CanExit())
		CDialog::OnCancel();
}

BOOL CShelldocDlg::CanExit()
{
	// If the proxy object is still around, then the automation
	//  controller is still holding on to this application.  Leave
	//  the dialog around, but hide its UI.
	if (m_pAutoProxy != NULL)
	{
		ShowWindow(SW_HIDE);
		return FALSE;
	}

	return TRUE;
}

void CShelldocDlg::OnButton1() 
{
	IShellDispatch disp;

	WCHAR szValue[80] ;
	CLSID clsid;
	HRESULT sc;
    sc = ::CoCreateInstance( CLSID_Shell, NULL, CLSCTX_SERVER, IID_IDispatch, (void**)&disp ) ;
	if (FAILED (sc))
	{
        CString str;
		str.Format(_T("Failed to create Instance :-( "));
        TRACE( str) ;
		return;
	}

	disp.FileRun();
}

void CShelldocDlg::OnButton2() 
{
	IShellDispatch disp;
	IDispatch * iDisp;

	WCHAR szValue[80] ;
	CLSID clsid;
	HRESULT sc;
    sc = ::CoCreateInstance( CLSID_Shell, NULL, CLSCTX_SERVER, IID_IDispatch, (void**)&disp ) ;
	if (FAILED (sc))
	{
        CString str;
		str.Format(_T("Failed to create Instance :-( "));
        TRACE( str) ;
		return;
	}
	VARIANT var;
	ZeroMemory (&var, sizeof (VARIANT));

	 iDisp = disp.BrowseForFolder(NULL,"Whatever",BIF_RETURNFSANCESTORS|BIF_RETURNONLYFSDIRS,var);	
	 //There has to be a check here if the user returned with cancel..
	// ASSERT (iDisp == NULL);
	Folder ifolder(iDisp);
	CString str = ifolder.GetTitle ();
	m_xDispName.SetWindowText (str);

	/* This part will invoke Open on each of the folder items.. You might have to make it work..by
	changing the pointer to get the parent and compare the folder name and invoke "Open" verb on that..
	iDisp = ifolder.Items ();
	FolderItems iitems (iDisp);

	for (short i = 0; i < iitems.GetCount();i++)
	{
		COleVariant count (i);

		iDisp = iitems.Item (count);
		FolderItem iitem (iDisp);

		iitem.InvokeVerb(var);
	}
*/
}
