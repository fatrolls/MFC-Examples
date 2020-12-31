// Saverdlg.cpp : implementation file
//

#include "stdafx.h"
#include "collect.h"
#include "DlgScrSaver.h"
#include "drawwnd.h"
#include "Saverdlg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
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

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//{{AFX_MSG(CAboutDlg)
	virtual BOOL OnInitDialog();
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
// CAboutDlg message handlers

BOOL CAboutDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	CenterWindow();
	
	// TODO: Add extra about dlg initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

/////////////////////////////////////////////////////////////////////////////
// CSaverDlg dialog

CSaverDlg::CSaverDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSaverDlg::IDD, pParent), m_wndPreview(FALSE)
{
	//{{AFX_DATA_INIT(CSaverDlg)
	BitmapPath = _T("");
	m_nSpeed = 0;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSaverDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSaverDlg)
	DDX_Control(pDX, IDC_SCROLLBAR_SPEED, m_scrollSpeed);
	DDX_Text(pDX, IDC_EDIT_BITMAPPATH, BitmapPath);
	DDX_Scroll(pDX, IDC_SCROLLBAR_SPEED, m_nSpeed);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSaverDlg, CDialog)
	//{{AFX_MSG_MAP(CSaverDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_HSCROLL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSaverDlg message handlers

BOOL CSaverDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	CRect rect;
	GetDlgItem(IDC_PREVIEW)->GetWindowRect(&rect);
	ScreenToClient(&rect);
	m_wndPreview.Create(NULL, WS_VISIBLE|WS_CHILD, rect, this, NULL);
	m_wndPreview.SetSpeed(m_nSpeed);

	m_scrollSpeed.SetScrollRange(1, 100);
	m_scrollSpeed.SetScrollPos(m_nSpeed);


	CenterWindow();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	CString strAboutMenu;
	strAboutMenu.LoadString(IDS_ABOUTBOX);
	if (!strAboutMenu.IsEmpty())
	{
		pSysMenu->AppendMenu(MF_SEPARATOR);
		pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
	}
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CSaverDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CSaverDlg::OnPaint() 
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
HCURSOR CSaverDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CSaverDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	ASSERT(pScrollBar != NULL);
	int nCurPos = pScrollBar->GetScrollPos();
	switch (nSBCode)
	{
	case SB_LEFT: //    Scroll to far left.
		nCurPos = 1;
		break;
	case SB_LINELEFT: //    Scroll left.
		nCurPos--;
		break;
	case SB_LINERIGHT: //    Scroll right.
		nCurPos++;
		break;
	case SB_PAGELEFT: //    Scroll one page left.
		nCurPos -= 10;
		break;
	case SB_PAGERIGHT: //    Scroll one page right.
		nCurPos += 10;
		break;
	case SB_RIGHT: //    Scroll to far right.
		nCurPos = 100;
		break;
	case SB_THUMBPOSITION: //    Scroll to absolute position. The current position is specified by the nPos parameter.
	case SB_THUMBTRACK: //    Drag scroll box to specified position. The current position is specified by the nPos parameter.
		nCurPos = nPos;
	}
	if (nCurPos < 1)
		nCurPos = 1;
	if (nCurPos > 100)
		nCurPos = 100;
	pScrollBar->SetScrollPos(nCurPos);

	m_wndPreview.SetSpeed(m_scrollSpeed.GetScrollPos());

	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

