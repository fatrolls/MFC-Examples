// DemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CBitmapSlider Demo.h"
#include "DemoDlg.h"

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
// CDemoDlg dialog

CDemoDlg::CDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDemoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDemoDlg)
	m_nMax = 0;
	m_nMin = 0;
	m_nPos = 0;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_bEnable = TRUE;
}

void CDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDemoDlg)
	DDX_Control(pDX, IDC_SLIDER_VOL2, m_sliderVol2);
	DDX_Control(pDX, IDC_SLIDER_VOL, m_sliderVol);
	DDX_Control(pDX, IDC_SLIDER_ROAD, m_sliderBus);
	DDX_Control(pDX, IDC_SLIDER_MP, m_sliderMP);
	DDX_Control(pDX, IDC_SLIDER_BIRD, m_sliderBird);
	DDX_Control(pDX, IDC_SLIDER_BALLOON, m_sliderBalloon);
	DDX_Text(pDX, IDC_MAX, m_nMax);
	DDX_Text(pDX, IDC_MIN, m_nMin);
	DDX_Text(pDX, IDC_POS, m_nPos);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDemoDlg, CDialog)
	//{{AFX_MSG_MAP(CDemoDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_APPLY, OnApply)
	ON_WM_RBUTTONDOWN()
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_BITMAPSLIDER_MOVED, OnBitmapSliderMoved)
	ON_MESSAGE(WM_BITMAPSLIDER_MOVING, OnBitmapSliderMoving)
	ON_BN_CLICKED(IDC_BUTTON_DISABLE, &CDemoDlg::OnBnClickedButtonDisable)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDemoDlg message handlers

BOOL CDemoDlg::OnInitDialog()
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

	// Slider 1 - Normal Volume
	m_sliderVol.SetBitmapChannel( IDB_VOL_OFF, IDB_VOL_ON );
	m_sliderVol.SetRange( 0, 100 );
	m_sliderVol.SetPos( 30 );
	m_sliderVol.SetMarginLeft( 8 );
	m_sliderVol.SetMarginRight( 8 );
	m_sliderVol.SetPageSize( 10 );
	m_sliderVol.DrawFocusRect( FALSE );

	// Slider 2	- Transparent Volume
	m_sliderVol2.SetBitmapChannel( IDB_VOL_OFF, IDB_VOL_ON, TRUE );
	m_sliderVol2.SetRange( 0, 100 );
	m_sliderVol2.SetPos( 30 );
	m_sliderVol2.SetMarginLeft( 8 );
	m_sliderVol2.SetMarginRight( 8 );
	m_sliderVol2.SetPageSize( 25 );
	m_sliderVol2.DrawFocusRect( FALSE );

	// Slider 3 - Media Player
	m_sliderMP.SetCustomerSetSize();
	m_sliderMP.SetBitmapChannel( IDB_MP_CHANNEL, IDB_MP_CHANNEL_ACTIVE );
	m_sliderMP.SetBitmapThumb( IDB_MP_THUMB, IDB_MP_THUMB_ACTIVE, IDB_MP_THUMB_DISABLE,TRUE );
	m_sliderMP.DrawFocusRect( FALSE );

	m_nMin = 0;
	m_nMax = 400;
	m_nPos = 30;

	m_sliderMP.SetRange( m_nMin, m_nMax );
	m_sliderMP.SetPos( m_nPos );

	m_sliderMP.SetMargin( 2, 3, 2, 0 );

	// Slider 4 - Balloon
	m_sliderBalloon.SetBitmapChannel( IDB_SKY );
	m_sliderBalloon.SetBitmapThumb( IDB_BALLOON, NULL, NULL,TRUE );
	m_sliderBalloon.SetMargin( 14, 10, 0, 30 );
	m_sliderBalloon.SetVertical();
	m_sliderBalloon.SetPos( 70 );

	// Slider 5 - Bird
	m_sliderBird.SetBitmapThumb( IDB_BIRD, NULL,NULL, TRUE );
	m_sliderBird.SetVertical();
	m_sliderBird.DrawFocusRect( FALSE );

	// Slider 6 - Bus
	m_sliderBus.SetBitmapChannel( IDB_ROAD, NULL, TRUE );
	m_sliderBus.SetBitmapThumb( IDB_BUS, NULL,NULL, TRUE );
	m_sliderBus.DrawFocusRect( TRUE );

	UpdateData( FALSE );

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CDemoDlg::OnPaint() 
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
HCURSOR CDemoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CDemoDlg::OnApply() 
{
	UpdateData();
	
	m_sliderMP.SetRange( m_nMin, m_nMax );
	m_sliderMP.SetPos( m_nPos );

	m_sliderMP.GetRange( m_nMin, m_nMax );
	m_nPos = m_sliderMP.GetPos();

	UpdateData( FALSE );
}

LRESULT CDemoDlg::OnBitmapSliderMoved(WPARAM wParam, LPARAM lParam)
{
	CString sMsg;

	switch( wParam ) {

	case IDC_SLIDER_VOL :
		m_sliderVol2.SetPos( m_sliderVol.GetPos() );
		break;

	case IDC_SLIDER_VOL2 :
		m_sliderVol.SetPos( m_sliderVol2.GetPos() );
		break;

	case IDC_SLIDER_BALLOON :

		sMsg.Format( "%d", lParam );
		AfxMessageBox( sMsg );
		break;
	}
	return 0;
}

LRESULT CDemoDlg::OnBitmapSliderMoving(WPARAM wParam, LPARAM lParam)
{
	switch( wParam ) {

	case IDC_SLIDER_VOL :
		m_sliderVol2.SetPos( m_sliderVol.GetPos() );
		break;

	case IDC_SLIDER_VOL2 :
		m_sliderVol.SetPos( m_sliderVol2.GetPos() );
		break;

	case IDC_SLIDER_MP :
		m_nPos = m_sliderMP.GetPos();
		UpdateData( FALSE );
		break;
	}

	return 0;
}

void CDemoDlg::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// Toggle
	m_bEnable = !m_bEnable;

	m_sliderMP.Enable( m_bEnable );
	m_sliderBus.Enable( m_bEnable );
	
	CDialog::OnRButtonDown(nFlags, point);
}


void CDemoDlg::OnBnClickedButtonDisable()
{
	// TODO: Add your control notification handler code here
	static BOOL enable;
	enable = !enable;
	m_sliderMP.Enable(enable);
	m_sliderVol.Enable(enable);
	m_sliderVol2.Enable(enable);
	m_sliderBus.Enable( enable );
}
