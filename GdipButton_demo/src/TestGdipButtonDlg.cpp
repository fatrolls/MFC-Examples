// TestGdipButtonDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TestGdipButton.h"
#include "TestGdipButtonDlg.h"

#include "MemDC.h"


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
// CTestGdipButtonDlg dialog

CTestGdipButtonDlg::CTestGdipButtonDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTestGdipButtonDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTestGdipButtonDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTestGdipButtonDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTestGdipButtonDlg)
	DDX_Control(pDX, IDC_GEAR,		m_cGear);
	DDX_Control(pDX, IDC_PLAY2,		m_cPlayHi);
	DDX_Control(pDX, IDC_PLAY3,		m_cPlayDis);
	DDX_Control(pDX, IDC_EXIT,		m_cShutDn);
	DDX_Control(pDX, IDC_PLAY,		m_cPlay);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTestGdipButtonDlg, CDialog)
	//{{AFX_MSG_MAP(CTestGdipButtonDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_EXIT, OnShutdn)
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestGdipButtonDlg message handlers

BOOL CTestGdipButtonDlg::OnInitDialog()
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

	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// load the standard image and alternate image
	m_cPlay.LoadStdImage(IDR_PLAY, _T("PNG"));
	m_cPlay.LoadAltImage(IDR_PAUSE, _T("PNG"));
	m_cPlay.EnableToggle(TRUE);

	// just to show highlight state for article
	m_cPlayHi.LoadStdImage(IDR_PLAY, _T("PNG"));

	// set as disabled
	m_cPlayDis.LoadStdImage(IDR_PLAY, _T("PNG"));
	m_cPlayDis.EnableButton(FALSE);

	// show a larger button type
	m_cGear.LoadStdImage(IDR_GEAR, _T("PNG"));

	// replace the OK button with something
	m_cShutDn.LoadStdImage(IDR_EXIT, _T("PNG"));
	m_cShutDn.SetToolTipText(_T("Close Program"));
		
	///////////////////////////////////////////////////////////////////////////////////////
	//
	// Put something interesting in the background
	// This has nothing to do with the GdipButtons
	//
	
	HBITMAP		hBitmap			= NULL;
	HINSTANCE	hInstResource	= NULL;

	// Find correct resource handle
	hInstResource = AfxFindResourceHandle(MAKEINTRESOURCE(IDB_BKGND), RT_BITMAP);

	// Load bitmap In
	m_hBitmap = (HBITMAP)::LoadImage(hInstResource, MAKEINTRESOURCE(IDB_BKGND), IMAGE_BITMAP, 0, 0, 0);

	///////////////////////////////////////////////////////////////////////////////////////


	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CTestGdipButtonDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CTestGdipButtonDlg::OnPaint() 
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

HCURSOR CTestGdipButtonDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CTestGdipButtonDlg::OnShutdn() 
{
	CDialog::OnOK();
}

BOOL CTestGdipButtonDlg::OnEraseBkgnd(CDC* pDC)
{
	CDialog::OnEraseBkgnd(pDC);

	CRect rect;
	GetClientRect(rect);

	CMemDC pDevC(pDC, rect);

	/////////////////////////////////////////////////////////////////////////////////
	// just put something in the background - unrelated to GdipButton
	/////////////////////////////////////////////////////////////////////////////////
	if (m_hBitmap)
	{
		pDevC->SelectObject(m_hBitmap);
	}
	/////////////////////////////////////////////////////////////////////////////////


	/////////////////////////////////////////////////////////////////////////////////
	// Since this function just painted the background into the memory DC,
	// this is the correct information that can be provided to the buttons
	/////////////////////////////////////////////////////////////////////////////////
	SetButtonBackGrounds(pDevC);
	/////////////////////////////////////////////////////////////////////////////////

	return TRUE;
}

void CTestGdipButtonDlg::SetButtonBackGrounds(CDC *pDC)
{
	// call with a memory DC or don't even bother since
	// it will defeat the purpose of doing this
	m_cPlay.SetBkGnd(pDC);
	m_cPlayHi.SetBkGnd(pDC);
	m_cPlayDis.SetBkGnd(pDC);
	m_cShutDn.SetBkGnd(pDC);
}


