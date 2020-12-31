// AdvEditDemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AdvEditDemo.h"
#include "AdvEditDemoDlg.h"

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
// CAdvEditDemoDlg dialog

CAdvEditDemoDlg::CAdvEditDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAdvEditDemoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAdvEditDemoDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAdvEditDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAdvEditDemoDlg)
	DDX_Control(pDX, IDC_EDIT2, m_edt2);
	DDX_Control(pDX, IDC_EDIT1, m_edt);
	//}}AFX_DATA_MAP
	for(int i = 0; i < 7; i ++)
		DDX_Control(pDX, IDC_EDIT3 + i, m_AdvEdit[i]);
}

BEGIN_MESSAGE_MAP(CAdvEditDemoDlg, CDialog)
	//{{AFX_MSG_MAP(CAdvEditDemoDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAdvEditDemoDlg message handlers

BOOL CAdvEditDemoDlg::OnInitDialog()
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
//	m_edt.SetPasswordChar('·');

	for(int i = 0; i < 7; i ++)
		m_AdvEdit[i].SetGrayTipString("请输入数据");

	m_AdvEdit[0].SetTextColor(RGB(13, 250, 128));
	m_AdvEdit[0].SetCursor(IDC_CURSOR1);

	m_AdvEdit[1].SetTextColor(RGB(138, 138, 255));
	m_AdvEdit[1].SetCursor("plane.cur");

	m_AdvEdit[2].SetTextColor(RGB(255, 0, 0));
	m_AdvEdit[2].SetBkgndColor(RGB(255, 255, 0));
	m_AdvEdit[2].SetBorderColor(RGB(132, 195, 242), RGB(16, 158, 234));
	m_AdvEdit[2].SetShadowColor(RGB(240, 240, 230), RGB(158, 158, 158));

//	m_AdvEdit[3].SetBorderColor(RGB(140, 200, 130), RGB(150, 230, 100));
	m_AdvEdit[3].SetBorderColor(RGB(170, 192, 216), RGB(255, 211, 100));
	m_AdvEdit[3].SetShadowColor(RGB(244, 244, 244), RGB(219, 219, 219));
	m_AdvEdit[3].SetHoverStyle(FOCUS_ENLARGE | FOCUS_BKCOLOR,
		250, RGB(255, 255, 228));	

	m_AdvEdit[4].SetFont(200, "华文行楷");
	m_AdvEdit[5].SetBorderCorner(CPoint(15, 15));
	m_AdvEdit[6].SetBorderCorner(CPoint(0, 0));

	m_AdvEdit[6].SetHoverStyle(FOCUS_ENLARGE | FOCUS_BKCOLOR | FOCUS_BORDERTHICK,
		250, RGB(255, 255, 228), 2);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CAdvEditDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CAdvEditDemoDlg::OnPaint() 
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
HCURSOR CAdvEditDemoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

