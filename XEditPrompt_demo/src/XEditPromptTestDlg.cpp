// XEditPromptTestDlg.cpp : implementation file
//

#include "stdafx.h"
#include "XEditPromptTest.h"
#include "XEditPromptTestDlg.h"
#include "about.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#ifndef EM_SETCUEBANNER
#define	EM_SETCUEBANNER	    (0x1500 + 1)	
#endif

/////////////////////////////////////////////////////////////////////////////
// CXEditPromptTestDlg dialog

BEGIN_MESSAGE_MAP(CXEditPromptTestDlg, CDialog)
	//{{AFX_MSG_MAP(CXEditPromptTestDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_EN_SETFOCUS(IDC_EDIT1, OnSetfocusEdit1)
	ON_EN_SETFOCUS(IDC_EDIT2, OnSetfocusEdit2)
	ON_EN_UPDATE(IDC_EDIT1, OnUpdateEdit1)
	ON_EN_UPDATE(IDC_EDIT2, OnUpdateEdit2)
	ON_BN_CLICKED(IDC_RESET, OnReset)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

CXEditPromptTestDlg::CXEditPromptTestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CXEditPromptTestDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CXEditPromptTestDlg)
	m_strEdit1 = _T("");
	//m_strEdit1 = _T("test");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CXEditPromptTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CXEditPromptTestDlg)
	DDX_Control(pDX, IDC_EDIT4, m_Edit4);
	DDX_Control(pDX, IDC_EDIT1, m_Edit1);
	DDX_Control(pDX, IDC_EDIT2, m_Edit2);
	DDX_Control(pDX, IDC_EDIT3, m_Edit3);
	DDX_Text(pDX, IDC_EDIT1, m_strEdit1);
	//}}AFX_DATA_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CXEditPromptTestDlg message handlers

BOOL CXEditPromptTestDlg::OnInitDialog()
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
	
	//m_Edit1.SetInitialTextColor(GetSysColor(COLOR_3DDKSHADOW));
	m_Edit2.SetPromptText(_T("<Enter today's Bob quote>"));
	m_Edit2.SetPromptColor(RGB(255,153,0));
	m_Edit3.SendMessage(EM_SETCUEBANNER, 0, (LPARAM)(LPCWSTR) L"<Enter text here>");
	m_Edit4.SetWindowText(_T("<Enter text here>"));

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CXEditPromptTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CXEditPromptTestDlg::OnPaint() 
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
HCURSOR CXEditPromptTestDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CXEditPromptTestDlg::OnSetfocusEdit1() 
{
	TRACE(_T("in CXEditPromptTestDlg::OnSetfocusEdit1\n"));
}

void CXEditPromptTestDlg::OnSetfocusEdit2() 
{
	TRACE(_T("in CXEditPromptTestDlg::OnSetfocusEdit2\n"));
}

void CXEditPromptTestDlg::OnUpdateEdit1() 
{
	TRACE(_T("in CXEditPromptTestDlg::OnUpdateEdit1\n"));
}

void CXEditPromptTestDlg::OnUpdateEdit2() 
{
	TRACE(_T("in CXEditPromptTestDlg::OnUpdateEdit2\n"));
}

void CXEditPromptTestDlg::OnReset() 
{
	m_Edit1.SetFocus();
	m_Edit1.Reset();
	m_Edit2.Reset();
	m_Edit3.SetWindowText(_T(""));
	m_Edit3.SendMessage(EM_SETCUEBANNER, 0, (LPARAM)(LPCWSTR) L"<Enter text here>");
	m_Edit4.SetWindowText(_T("<Enter text here>"));
}
