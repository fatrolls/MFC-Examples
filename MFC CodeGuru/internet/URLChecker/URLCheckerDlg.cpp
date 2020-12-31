// URLCheckerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "URLChecker.h"
#include "URLCheckerDlg.h"
#include "webworld.h"
#include "aboutdlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define WM_ICON_NOTIFY  WM_USER+10

/////////////////////////////////////////////////////////////////////////////
// CURLCheckerDlg dialog

CURLCheckerDlg::CURLCheckerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CURLCheckerDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CURLCheckerDlg)
	m_URL = _T("");
	m_Duration = 0;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CURLCheckerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CURLCheckerDlg)
	DDX_Text(pDX, IDC_URL, m_URL);
	DDX_Text(pDX, IDC_DURATION, m_Duration);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CURLCheckerDlg, CDialog)
	//{{AFX_MSG_MAP(CURLCheckerDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(ID_EXIT, OnEndbtn)
	ON_BN_CLICKED(IDC_STARTBTN, OnStartbtn)
	ON_WM_TIMER()
	ON_COMMAND(ID_CONFIGURE, OnConfigure)
	ON_WM_SYSCOMMAND()
	ON_MESSAGE(WM_ICON_NOTIFY, OnTrayNotification)
	ON_BN_CLICKED(ID_ABOUTDLG, OnAboutdlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CURLCheckerDlg message handlers

BOOL CURLCheckerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

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
//	CSpinButtonCtrl* SpinDuration = (CSpinButtonCtrl *) GetDlgItem(IDC_SPINDURATION);
//	SpinDuration->SetBuddy(GetDlgItem(IDC_DURATION));
//	SpinDuration->SetPos(1);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CURLCheckerDlg::OnPaint() 
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
HCURSOR CURLCheckerDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CURLCheckerDlg::OnEndbtn() 
{
	CDialog::OnOK();	
}

void CURLCheckerDlg::OnStartbtn() 
{
	HICON hIcon;

	hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_TrayIcon.Create(this, WM_ICON_NOTIFY, "URLChecker", 
                          hIcon, IDR_POPUP_MENU);
	ShowWindow(SW_HIDE);
	UpdateData();
	SetTimer(1, m_Duration*10000, NULL);
}

LRESULT CURLCheckerDlg::OnTrayNotification(WPARAM wParam, LPARAM lParam)
{
    // Delegate all the work back to the default implementation in CTrayIcon.
    return m_TrayIcon.OnTrayNotification(wParam, lParam);

}

void CURLCheckerDlg::OnTimer(UINT nIDEvent) 
{
	CWebWorld a; 
	CString PageContent;
	
	a.SetErrorMessage("ERROR");
	PageContent= a.GetWebPage(m_URL);
	if(PageContent.Compare("ERROR")==0)
		MessageBeep(0xFFFFFFFF);

}

void CURLCheckerDlg::OnConfigure() 
{
	KillTimer(1);
	ShowWindow(SW_SHOWNORMAL);
	m_TrayIcon.RemoveIcon();	
	
}

void CURLCheckerDlg::OnSysCommand(UINT nID, LPARAM lParam) 
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

void CURLCheckerDlg::OnAboutdlg() 
{
	CAboutDlg dlgAbout;
	dlgAbout.DoModal();	
}
