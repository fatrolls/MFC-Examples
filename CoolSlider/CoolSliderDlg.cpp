// CoolSliderDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CoolSlider.h"
#include "CoolSliderDlg.h"

#include "BitItem.h"

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
// CCoolSliderDlg dialog

CCoolSliderDlg::CCoolSliderDlg(CWnd* pParent /*=NULL*/)
  : CDialog(CCoolSliderDlg::IDD, pParent),
	m_lpNormal(NULL),
	m_lpActive(NULL),
	m_lpThumb(NULL),
	m_hHandCur(NULL)
{
	//{{AFX_DATA_INIT(CCoolSliderDlg)
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CCoolSliderDlg::~CCoolSliderDlg()
{
	if( m_lpNormal != NULL )
	{
		delete m_lpNormal;
		m_lpNormal = NULL;
	}
	if( m_lpActive != NULL )
	{
		delete m_lpActive;
		m_lpActive = NULL;
	}
	if( m_lpThumb != NULL )
	{
		delete m_lpThumb;
		m_lpThumb = NULL;
	}
}

void CCoolSliderDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCoolSliderDlg)
	DDX_Control(pDX, IDC_SLIDER_VERTICAL2, m_ctlVert2);
	DDX_Control(pDX, IDC_SLIDER_VERTICAL1, m_ctlVert1);
	DDX_Control(pDX, IDC_SLIDER_SHARE3, m_ctlShare3);
	DDX_Control(pDX, IDC_SLIDER_SHARE2, m_ctlShare2);
	DDX_Control(pDX, IDC_SLIDER_SHARE1, m_ctlShare1);
	DDX_Control(pDX, IDC_COOL_SLIDER, m_ctlSlider);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CCoolSliderDlg, CDialog)
	//{{AFX_MSG_MAP(CCoolSliderDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_ERASEBKGND()
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_COOL_SLIDER, OnReleasedcaptureCoolSlider)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCoolSliderDlg message handlers

BOOL CCoolSliderDlg::OnInitDialog()
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

	this->BuildCoolSlider();		// Build your cool-slider in simple mode...
	this->BuildShareSlider();		// Build your cool-slider in shared resource mode...:)

	this->BuildVerticalSlider();
	
	return TRUE;
}

void CCoolSliderDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CCoolSliderDlg::OnPaint() 
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
HCURSOR CCoolSliderDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

HCURSOR	CCoolSliderDlg::GetSysHandCursor()
{
	TCHAR		strWinDir[MAX_PATH] = {0};
	HCURSOR		hHandCursor			= NULL;
	hHandCursor = ::LoadCursor(NULL, MAKEINTRESOURCE(32649));
	
	// Still no cursor handle - load the WinHelp hand cursor
	if( hHandCursor == NULL )
	{
		GetWindowsDirectory(strWinDir, MAX_PATH);
		strcat(strWinDir, _T("\\winhlp32.exe"));
		
		// This retrieves cursor #106 from winhlp32.exe, which is a hand pointer
		HMODULE hModule = ::LoadLibrary(strWinDir);
		DWORD	dwErr = GetLastError();
		if( hModule != NULL )
		{
			HCURSOR	 hTempCur = ::LoadCursor(hModule, MAKEINTRESOURCE(106));
			hHandCursor = (hTempCur != NULL) ? CopyCursor(hTempCur) : NULL;
			FreeLibrary(hModule);
		}
	}
	return hHandCursor;
}

void CCoolSliderDlg::BuildCoolSlider()
{
	m_hHandCur = this->GetSysHandCursor();
	ASSERT( m_hHandCur != NULL );
	
	m_ctlSlider.SetFlipCursor(m_hHandCur);
	m_ctlSlider.BuildThumbItem(IDB_BITMAP_THUMB, 6, 12);
	m_ctlSlider.BuildBackItem(IDB_BITMAP_NORMAL, IDB_BITMAP_ACTIVE);
	m_ctlSlider.SetTopOffset(3);
	m_ctlSlider.SetRange(0, 100);
	m_ctlSlider.SetLineSize(0);
	m_ctlSlider.SetPos(20);
}

void CCoolSliderDlg::BuildShareSlider()
{
	ASSERT( m_hHandCur != NULL );

	ASSERT( m_lpActive == NULL );
	ASSERT( m_lpNormal == NULL );
	ASSERT( m_lpThumb == NULL );

	m_lpActive = new CBitItem(IDB_BITMAP_ACTIVE, 0, 0);
	m_lpNormal = new CBitItem(IDB_BITMAP_NORMAL, 0, 0);
	m_lpThumb  = new CBitItem(IDB_BITMAP_THUMB, 6, 12);

	m_ctlShare1.SetFlipCursor(m_hHandCur);
	m_ctlShare1.BuildThumbItem(m_lpThumb);
	m_ctlShare1.BuildBackItem(m_lpNormal, m_lpActive);
	m_ctlShare1.SetTopOffset(3);
	m_ctlShare1.SetRange(0, 100);
	m_ctlShare1.SetLineSize(0);
	m_ctlShare1.SetPos(40);

	m_ctlShare2.SetFlipCursor(m_hHandCur);
	m_ctlShare2.BuildThumbItem(m_lpThumb);
	m_ctlShare2.BuildBackItem(m_lpNormal, m_lpActive);
	m_ctlShare2.SetTopOffset(3);
	m_ctlShare2.SetRange(0, 100);
	m_ctlShare2.SetLineSize(0);
	m_ctlShare2.SetPos(60);

	m_ctlShare3.SetFlipCursor(m_hHandCur);
	m_ctlShare3.BuildThumbItem(m_lpThumb);
	m_ctlShare3.BuildBackItem(m_lpNormal, m_lpActive);
	m_ctlShare3.SetTopOffset(3);
	m_ctlShare3.SetRange(0, 100);
	m_ctlShare3.SetLineSize(0);
	m_ctlShare3.SetPos(80);
}

void CCoolSliderDlg::BuildVerticalSlider()
{
	m_ctlVert1.SetFlipCursor(m_hHandCur);
	m_ctlVert1.BuildThumbItem(IDB_VERTICAL_THUMB, 12, 6);
	m_ctlVert1.BuildBackItem(IDB_VERTICAL_NORMAL, IDB_VERTICAL_ACTIVE);
	m_ctlVert1.SetLeftOffset(3);
	m_ctlVert1.SetRange(0, 100);
	m_ctlVert1.SetLineSize(0);
	m_ctlVert1.SetPos(50);

	m_ctlVert2.SetFlipCursor(m_hHandCur);
	m_ctlVert2.BuildThumbItem(IDB_VERTICAL_THUMB, 12, 6);
	m_ctlVert2.BuildBackItem(IDB_VERTICAL_NORMAL, IDB_VERTICAL_ACTIVE);
	m_ctlVert2.SetLeftOffset(3);
	m_ctlVert2.SetRange(0, 100);
	m_ctlVert2.SetLineSize(0);
	m_ctlVert2.SetPos(50);
}

BOOL CCoolSliderDlg::OnEraseBkgnd(CDC* pDC) 
{
	CRect	rcRect;
	this->GetClientRect(rcRect);
	
	pDC->FillSolidRect(rcRect, RGB(96, 123, 189));

	return TRUE;
}

void CCoolSliderDlg::OnReleasedcaptureCoolSlider(NMHDR* pNMHDR, LRESULT* pResult) 
{
	*pResult = 0;
}




