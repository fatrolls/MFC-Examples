// TaskBarNotifierDemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TaskBarNotifierDemo.h"
#include "TaskBarNotifierDemoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CTaskBarNotifierDemoDlg dialog



CTaskBarNotifierDemoDlg::CTaskBarNotifierDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTaskBarNotifierDemoDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTaskBarNotifierDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT, m_wndEdit);
}

BEGIN_MESSAGE_MAP(CTaskBarNotifierDemoDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, OnBnClickedButton4)
	ON_MESSAGE(WM_TASKBARNOTIFIERCLICKED,OnTaskbarNotifierClicked)
END_MESSAGE_MAP()


// CTaskBarNotifierDemoDlg message handlers

BOOL CTaskBarNotifierDemoDlg::OnInitDialog()
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

	m_wndTaskbarNotifier1.Create(this);
	m_wndTaskbarNotifier1.SetSkin(IDB_SKIN_MSN);
	m_wndTaskbarNotifier1.SetTextFont("Arial",90,TN_TEXT_NORMAL,TN_TEXT_UNDERLINE);
 	m_wndTaskbarNotifier1.SetTextColor(RGB(0,0,0),RGB(0,0,200));
	m_wndTaskbarNotifier1.SetTextRect(CRect(10,40,m_wndTaskbarNotifier1.m_nSkinWidth-10,m_wndTaskbarNotifier1.m_nSkinHeight-25));

	m_wndTaskbarNotifier2.Create(this);
	m_wndTaskbarNotifier2.SetSkin(IDB_SKIN_BOX,255,255,255);
	m_wndTaskbarNotifier2.SetTextFont("Arial Black",90,TN_TEXT_NORMAL,TN_TEXT_UNDERLINE | TN_TEXT_BOLD);
	m_wndTaskbarNotifier2.SetTextColor(RGB(255,255,255),RGB(200,0,0));
	m_wndTaskbarNotifier2.SetTextRect(CRect(20,25,m_wndTaskbarNotifier2.m_nSkinWidth-20,m_wndTaskbarNotifier2.m_nSkinHeight-15));

	m_wndTaskbarNotifier3.Create(this);
	m_wndTaskbarNotifier3.SetSkin(IDB_SKIN_BOARD,255,0,255);
	m_wndTaskbarNotifier3.SetTextFont("Arial Black",90,TN_TEXT_NORMAL,TN_TEXT_UNDERLINE | TN_TEXT_BOLD);
	m_wndTaskbarNotifier3.SetTextColor(RGB(255,255,255),RGB(200,0,0));
	m_wndTaskbarNotifier3.SetTextRect(CRect(10,20,m_wndTaskbarNotifier3.m_nSkinWidth-10,m_wndTaskbarNotifier3.m_nSkinHeight-20));
	
	m_wndTaskbarNotifier4.Create(this);
	m_wndTaskbarNotifier4.SetSkin(IDB_SKIN_GUY,255,0,255);
	m_wndTaskbarNotifier4.SetTextFont("Impact",110,TN_TEXT_NORMAL,TN_TEXT_UNDERLINE | TN_TEXT_BOLD);
	m_wndTaskbarNotifier4.SetTextColor(RGB(255,255,255),RGB(200,200,200));
	m_wndTaskbarNotifier4.SetTextRect(CRect(25,40,m_wndTaskbarNotifier4.m_nSkinWidth-30,m_wndTaskbarNotifier4.m_nSkinHeight-80));
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CTaskBarNotifierDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CTaskBarNotifierDemoDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

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

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CTaskBarNotifierDemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CTaskBarNotifierDemoDlg::OnBnClickedButton1()
{
	CString str;
	m_wndEdit.GetWindowText(str);
	m_wndTaskbarNotifier1.Show(str);
}

void CTaskBarNotifierDemoDlg::OnBnClickedButton2()
{
	CString str;
	m_wndEdit.GetWindowText(str);
	m_wndTaskbarNotifier2.Show(str);
}

void CTaskBarNotifierDemoDlg::OnBnClickedButton3()
{
	CString str;
	m_wndEdit.GetWindowText(str);
	m_wndTaskbarNotifier3.Show(str);
}

void CTaskBarNotifierDemoDlg::OnBnClickedButton4()
{
	CString str;
	m_wndEdit.GetWindowText(str);
	m_wndTaskbarNotifier4.Show(str);
}

LRESULT CTaskBarNotifierDemoDlg::OnTaskbarNotifierClicked(WPARAM wParam,LPARAM lParam)
{
	MessageBox("A Taskbar Notifier was clicked!!","Hi",MB_OK);
	return 0;
}