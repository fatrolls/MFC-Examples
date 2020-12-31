// SpecialFXDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SpecialFX.h"
#include "SpecialFXDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define BMP_WIDTH   250          //位图宽度
#define BMP_HEIGHT  210          //位图高度
#define TIMER_START 1971         //定时器ID
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
// CSpecialFXDlg dialog

CSpecialFXDlg::CSpecialFXDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSpecialFXDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSpecialFXDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSpecialFXDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSpecialFXDlg)
	DDX_Control(pDX, IDC_SLIDERPLASMAALPHA, m_sldrPlasma);
	DDX_Control(pDX, IDC_SLIDERFIREALPHA, m_sldrFire);
	DDX_Control(pDX, IDC_CHECKWATER, m_chkWater);
	DDX_Control(pDX, IDC_CHECKPLASMA, m_chkPlasma);
	DDX_Control(pDX, IDC_CHECKFIRE, m_chkFire);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSpecialFXDlg, CDialog)
	//{{AFX_MSG_MAP(CSpecialFXDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTONANIMATE, OnButtonanimate)
	ON_BN_CLICKED(IDC_BUTTONSTOP, OnButtonstop)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_CHECKFIRE, OnCheckfire)
	ON_BN_CLICKED(IDC_CHECKPLASMA, OnCheckplasma)
	ON_BN_CLICKED(IDC_CHECKWATER, OnCheckwater)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDERPLASMAALPHA, OnReleasedcaptureSliderplasmaalpha)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDERFIREALPHA, OnReleasedcaptureSliderfirealpha)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSpecialFXDlg message handlers

BOOL CSpecialFXDlg::OnInitDialog()
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
	
	//装入位图
	CPictureHolder myTmpPicture;
	myTmpPicture.CreateFromBitmap(IDB_MAP);
	m_bmpRenderSource.Create32BitFromPicture(&myTmpPicture,BMP_WIDTH,BMP_HEIGHT);
	m_bmpRenderTarget.Create32BitFromPicture(&myTmpPicture,BMP_WIDTH,BMP_HEIGHT);

	//创建水纹对象
	m_myWater.Create(BMP_WIDTH,BMP_HEIGHT);
	//创建火焰对象
	m_myFire.m_iAlpha = 30;		// 渐变 30% alpha
	m_myFire.m_iHeight = BMP_HEIGHT;
	m_myFire.m_iWidth = BMP_WIDTH;
	m_myFire.InitFire();
	m_sldrFire.SetRange(1,100,TRUE);
	m_sldrFire.SetPos(30);
	//创建岩浆对象
	m_myPlasma.Create(BMP_WIDTH,BMP_HEIGHT);
	m_myPlasma.m_iAlpha = 30;// 渐变 30 % alpha
	m_sldrPlasma.SetRange(1,100,TRUE);
	m_sldrPlasma.SetPos(30);

	//初始化变量
	m_bRunWater = TRUE;
	m_bRunFire = FALSE;
	m_bRunPlasma = FALSE;
	m_chkWater.SetCheck(TRUE);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CSpecialFXDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CSpecialFXDlg::OnPaint() 
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
		//在此重绘位图
		CPaintDC dc(this);
		CPoint ptOrigin(15,20);
		m_bmpRenderTarget.Draw(&dc,ptOrigin);

		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CSpecialFXDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CSpecialFXDlg::OnTimer(UINT nIDEvent) 
{
	if(nIDEvent == TIMER_START)
	{		
		if(!m_bRunWater)
			m_myWater.FlattenWater();  //浮动它，以便消失

		m_myWater.Render((DWORD*)m_bmpRenderSource.GetDIBits(),(DWORD*)m_bmpRenderTarget.GetDIBits());

		if(m_bRunFire)
			m_myFire.Render((DWORD*)m_bmpRenderTarget.GetDIBits(),BMP_WIDTH,BMP_HEIGHT);

		if(m_bRunPlasma)
			m_myPlasma.Render((DWORD*)m_bmpRenderTarget.GetDIBits(),BMP_WIDTH,BMP_HEIGHT,BMP_WIDTH);

		CClientDC dc(this);
		CPoint ptOrigin(15,20);
		m_bmpRenderTarget.Draw(&dc,ptOrigin);
	}
	
	CDialog::OnTimer(nIDEvent);
}

void CSpecialFXDlg::OnButtonanimate() 
{
	m_nTimer = SetTimer(TIMER_START,30,NULL);
	
}

void CSpecialFXDlg::OnButtonstop() 
{
	KillTimer(m_nTimer);
	
}

void CSpecialFXDlg::OnMouseMove(UINT nFlags, CPoint point) 
{
	CRect rcPicture;

	rcPicture.left = 15;
	rcPicture.top = 20;
	rcPicture.right = rcPicture.left + m_bmpRenderSource.GetWidth();
	rcPicture.bottom = rcPicture.top + m_bmpRenderSource.GetHeight();

	if(rcPicture.PtInRect(point) == TRUE)
	{
		//偏移到位图左上角，以便产生水纹效果
		point.y -= 20;
		point.y = BMP_HEIGHT-point.y;

		m_myWater.HeightBlob(point.x -15,point.y,5,50,m_myWater.m_iHpage);

			if(!m_bRunWater)
			m_myWater.FlattenWater();	//浮动它，以便消失

		m_myWater.Render((DWORD*)m_bmpRenderSource.GetDIBits(),(DWORD*)m_bmpRenderTarget.GetDIBits());

		if(m_bRunFire)
			m_myFire.Render((DWORD*)m_bmpRenderTarget.GetDIBits(),BMP_WIDTH,BMP_HEIGHT);

		if(m_bRunPlasma)
			m_myPlasma.Render((DWORD*)m_bmpRenderTarget.GetDIBits(),BMP_WIDTH,BMP_HEIGHT,BMP_WIDTH);

		CClientDC dc(this);
		CPoint ptOrigin(15,20);
		m_bmpRenderTarget.Draw(&dc,ptOrigin);
	}

	CDialog::OnMouseMove(nFlags, point);
}

void CSpecialFXDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CRect rcPicture;

	rcPicture.left = 15;
	rcPicture.top = 20;
	rcPicture.right = rcPicture.left + m_bmpRenderSource.GetWidth();
	rcPicture.bottom = rcPicture.top + m_bmpRenderSource.GetHeight();

	if(rcPicture.PtInRect(point) == TRUE)
	{
		//偏移到位图左上角，以便产生水纹效果
		point.y -= 20;
		point.y = BMP_HEIGHT-point.y;

		m_myWater.HeightBlob(point.x-15,point.y,50,500,m_myWater.m_iHpage);
	}
	
	CDialog::OnLButtonDown(nFlags, point);
}

void CSpecialFXDlg::OnCheckfire() 
{
	m_bRunFire = m_chkFire.GetCheck();
	
}

void CSpecialFXDlg::OnCheckplasma() 
{
	m_bRunPlasma = m_chkPlasma.GetCheck();
	
}

void CSpecialFXDlg::OnCheckwater() 
{
	m_bRunWater = m_chkWater.GetCheck();
	
}

void CSpecialFXDlg::OnReleasedcaptureSliderplasmaalpha(NMHDR* pNMHDR, LRESULT* pResult) 
{
	m_myPlasma.m_iAlpha = m_sldrPlasma.GetPos();
	
	*pResult = 0;
}

void CSpecialFXDlg::OnReleasedcaptureSliderfirealpha(NMHDR* pNMHDR, LRESULT* pResult) 
{
	m_myFire.m_iAlpha = m_sldrFire.GetPos();
	
	*pResult = 0;
}
