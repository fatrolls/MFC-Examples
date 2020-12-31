// TestDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TestDialog.h"
#include "TestDlg.h"
#include	"MyPropertySheet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/*
 * NEW HERE:
 * - Replaced CDialog by cdxCSizingDialog
 * - Edited OnInitDialog() (see there)
 * - Edit OnClose(), OnCancel() and OnOK() (see there; below OnInitDialog())
 */

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public cdxCSizingDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	CButton	m_wndOK;
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
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : cdxCSizingDialog(CAboutDlg::IDD,NULL,fdHoriz)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	cdxCSizingDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	DDX_Control(pDX, IDOK, m_wndOK);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, cdxCSizingDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CAboutDlg::OnInitDialog() 
{
	cdxCSizingDialog::OnInitDialog();

	AddSzXControl(m_wndOK,mdRepos);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}




/////////////////////////////////////////////////////////////////////////////
// CTestDlg dialog

CTestDlg::CTestDlg(CWnd* pParent /*=NULL*/)
	: cdxCSizingDialog(CTestDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTestDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTestDlg::DoDataExchange(CDataExchange* pDX)
{
	cdxCSizingDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTestDlg)
	DDX_Control(pDX, IDOK, m_wndOK);
	DDX_Control(pDX, IDCANCEL, m_wndCancel);
	DDX_Control(pDX, IDC_RESIZE, m_wndResize);
	DDX_Control(pDX, IDC_REPOS2, m_wndRepos2);
	DDX_Control(pDX, IDC_REL2, m_wndRel2);
	DDX_Control(pDX, IDC_REPOS, m_wndRepos);
	DDX_Control(pDX, IDC_REL, m_wndRel);
	DDX_Control(pDX, IDC_NONE, m_wndNone);
	DDX_Control(pDX, IDC_HEADER, m_wndHeader);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTestDlg, cdxCSizingDialog)
	//{{AFX_MSG_MAP(CTestDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestDlg message handlers

BOOL CTestDlg::OnInitDialog()
{
	cdxCSizingDialog::OnInitDialog();

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
	
	//////////////////////////////////////////////////////
	// NEW: AddSzControl()s and RestoreWindowPosition))
	//
	
	AddSzControl(m_wndHeader,mdRelative,mdRelative);

	AddSzControl(m_wndResize,	mdResize,	mdRelative);
	AddSzControl(m_wndRepos,	mdRepos,		mdRelative);
	AddSzControl(m_wndRepos2,	mdRepos,		mdRelative);
	AddSzControl(m_wndNone,		mdNone,		mdRelative);
	AddSzControl(m_wndRel,		mdRelative,	mdRelative);
	AddSzControl(m_wndRel2,		mdRelative,	mdRelative);

	// here we use the advanced version of AddSzControl():
	AddSzControlEx(m_wndOK,		exMaximum/4,exMaximum/2,exMaximum,exMaximum);
	AddSzControlEx(m_wndCancel,exMaximum/2,(3*exMaximum)/4,exMaximum,exMaximum);

	RestoreWindowPosition(CString(_T("test")));

	// EON

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CTestDlg::OnOK() 
{
	CMyPropertySheet	sh(this);
	sh.DoModal();
/*
   THIS would be used if you really have a OK button
	StoreWindowPosition(CString(_T("test")));	// NEW
	cdxCSizingDialog::OnOK();
*/
}

void CTestDlg::OnCancel() 
{
	StoreWindowPosition(CString(_T("test")));	// NEW
	cdxCSizingDialog::OnCancel();
}

void CTestDlg::OnClose() 
{
	OnCancel();	// NEW: Close equals to cancel
}

// others follow

void CTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		cdxCSizingDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTestDlg::OnPaint() 
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
		cdxCSizingDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CTestDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}











