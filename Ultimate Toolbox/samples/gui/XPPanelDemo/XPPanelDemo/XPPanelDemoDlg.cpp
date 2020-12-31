// XPPanelDemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "XPPanelDemo.h"
#include "XPPanelDemoDlg.h"

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


// CXPPanelDemoDlg dialog




CXPPanelDemoDlg::CXPPanelDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CXPPanelDemoDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CXPPanelDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CXPPanelDemoDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


// CXPPanelDemoDlg message handlers

BOOL CXPPanelDemoDlg::OnInitDialog()
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
	CRect rect;
	GetClientRect(&rect);	
	if(!m_TaskPanel.Create(rect,this, 1000))
	{
		MessageBox(_T("Creation failed!"));
	}
	else
	{
		TaskGroup* it = m_TaskPanel.AddGroup(_T("File and Folder Tasks"));

		Item i1;
		i1.m_nIconID = IDI_NEWFOLDER;
		i1.m_strText = "Run Notepad";
		i1.m_strCmd = "notepad.exe";

		Item i2;
		i2.m_nIconID = IDI_WHEEL;
		i2.m_strText = "Launch Google";
		i2.m_strCmd = "www.google.com";

		it->AddItem(i1);
		it->AddItem(i2);

		it = m_TaskPanel.AddGroup(_T("Other Places"));

		i1.m_strText = "Run Notepad";
		i1.m_strCmd = "notepad.exe";
		i2.m_strText = "Run Paintbrush";
		i2.m_strCmd = "mspaint.exe";
		it->AddItem(i1);
		it->AddItem(i2);

		i1.m_strText = "The Code Project";
		i1.m_strCmd = "www.codeproject.com";
		i2.m_strText = "Run Notepad";
		i2.m_strCmd = "notepad.exe";
		it->AddItem(i1);
		it->AddItem(i2);

		i1.m_strText = "Run Paintbrush";
		i1.m_strCmd = "mspaint.exe";
		i2.m_strText = "The Code Project";
		i2.m_strCmd = "www.codeproject.com";
		it->AddItem(i1);
		it->AddItem(i2);

		it = m_TaskPanel.AddGroup(_T("Microsoft Office"));
		i1.m_strText = "Run Word";
		i1.m_nIconID = IDI_WORD;
		i1.m_strCmd = "winword.exe";
		it->AddItem(i1);

		i1.m_strText = "Run Excel";
		i1.m_nIconID = IDI_EXCEL;
		i1.m_strCmd = "excel.exe";
		it->AddItem(i1);

		i1.m_strText = "Run Powerpoint";
		i1.m_strCmd = "powerpnt.exe";
		i1.m_nIconID = IDI_WHEEL;
		it->AddItem(i1);
	}

	return TRUE;  
}

void CXPPanelDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CXPPanelDemoDlg::OnPaint()
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
HCURSOR CXPPanelDemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

