// HooksTestDlg.cpp : implementation file
//

#include "stdafx.h"
#include "HooksTest.h"
#include "HooksTestDlg.h"

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
// CHooksTestDlg dialog

CHooksTestDlg::CHooksTestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CHooksTestDlg::IDD, pParent), CHooksClient()
{
	//{{AFX_DATA_INIT(CHooksTestDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	if(m_fileLog.Open("Hook.Log", CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite))
	{
		m_pDump = new CDumpContext(&m_fileLog);
		(*m_pDump) << "Testing one two three.\r\n";
	}
	else
	{
		m_pDump = NULL;
	}
}

CHooksTestDlg::~CHooksTestDlg()
{
	if(m_pDump)
	{
		delete m_pDump;
		m_fileLog.Close();
	}
}

void CHooksTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHooksTestDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CHooksTestDlg, CDialog)
	//{{AFX_MSG_MAP(CHooksTestDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_TEST, OnTest)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHooksTestDlg message handlers

BOOL CHooksTestDlg::OnInitDialog()
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

	HWND hCalcWnd = ::FindWindow("Notepad", NULL);
	if(hCalcWnd)
		InstallWindowHook(hCalcWnd);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CHooksTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CHooksTestDlg::OnPaint() 
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
HCURSOR CHooksTestDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CHooksTestDlg::ProcessHookMessage(HWND hwnd, UINT nMessage, WPARAM wParam, LPARAM lParam)
{
	CString buf, title;

	if(::IsWindow(hwnd))
	{
		CString temp;
		CWnd::FromHandle(hwnd)->GetWindowText(temp);
		title = "(" + temp + ") ";
	}

	if(m_pDump)
	{
		CString msg;
		
		buf.Format("Received Move Message hwnd:%8.8x %smsg:%d\r\n", hwnd, title, nMessage);
		(*m_pDump) << buf;
	}

	if( ((nMessage == WM_MOVE) || (nMessage == WM_SIZE)) && (hwnd) && (::IsWindow(hwnd)) && (!::GetParent(hwnd)) )
	{
		CRect rect, cRect;

		GetWindowRect(&cRect);
		::GetWindowRect(hwnd, &rect);
		SetWindowPos(NULL, rect.left, rect.bottom, rect.Width(), cRect.Height(), SWP_NOZORDER | SWP_SHOWWINDOW);
	}

	if(!::GetParent(hwnd))
	{
		if(nMessage == WM_ACTIVATE)
		{
			if( (wParam == WA_ACTIVE) || (wParam == WA_CLICKACTIVE) )
				afxDump << "Got focus to " << title << "\n";
			else
			{
				CString buf;

				HWND hOld = (HWND) lParam;
				HWND hParent = ::GetParent(hOld);

				while(hParent)
				{
					hOld = hParent;
					hParent = ::GetParent(hParent);
				}
				
				buf.Format(" - to handle %8.8x", hOld);
				if(!::IsChild(hOld, hwnd))
					afxDump << "Lost focus from " << title << buf << "\n";
			}
		}
	}
	
}

void CHooksTestDlg::OnTest() 
{
/*
	CWnd *pWnd = CWnd::FindWindow(HOOKWINDOWCLASS, HOOKWINDOWNAME);
//	CWnd *pWnd = CWnd::FindWindow(NULL, HOOKWINDOWNAME);

	if(pWnd)
	{
		for(int i = 1; i < 100 ; i++)
		{
			pWnd->SendMessage(WM_HOOK_COPYDATA, 0, 0);
		}
	}
*/
}

