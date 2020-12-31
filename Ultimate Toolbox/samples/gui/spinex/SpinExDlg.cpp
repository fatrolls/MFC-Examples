// SpinExDlg.cpp : implementation file
//

#include "stdafx.h"
#include "utsampleabout.h"
#include "SpinEx.h"
#include "SpinExDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
// CSpinExDlg dialog

CSpinExDlg::CSpinExDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSpinExDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSpinExDlg)
	m_nBuddy4 = 0;
	m_nBuddy1 = 0;
	m_nBuddy3 = 0;
	m_nBuddy2 = 0;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_nColorBarHei = 0;
	m_nColorBarWid = 0;
}

void CSpinExDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSpinExDlg)
	DDX_Control(pDX, IDC_COLORBAR, m_ColorBar);
	DDX_Control(pDX, IDC_BUDDY4, m_Buddy4);
	DDX_Control(pDX, IDC_SPINEX3, m_SpinEx3);
	DDX_Control(pDX, IDC_BUDDY3, m_Buddy3);
	DDX_Control(pDX, IDC_BUDDY2, m_Buddy2);
	DDX_Control(pDX, IDC_SPINEX2, m_SpinEx2);
	DDX_Control(pDX, IDC_BUDDY1, m_Buddy1);
	DDX_Control(pDX, IDC_SPINEX1, m_SpinEx1);
	DDX_Text(pDX, IDC_BUDDY4, m_nBuddy4);
	DDX_Text(pDX, IDC_BUDDY1, m_nBuddy1);
	DDX_Text(pDX, IDC_BUDDY3, m_nBuddy3);
	DDX_Text(pDX, IDC_BUDDY2, m_nBuddy2);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSpinExDlg, CDialog)
	//{{AFX_MSG_MAP(CSpinExDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_RADIO1, OnRadio1)
	ON_BN_CLICKED(IDC_RADIO2, OnRadio2)
	ON_EN_CHANGE(IDC_BUDDY4, OnChangeBuddy4)
	ON_EN_CHANGE(IDC_BUDDY1, OnChangeBuddy1)
	ON_EN_CHANGE(IDC_BUDDY2, OnChangeBuddy1)
	ON_EN_CHANGE(IDC_BUDDY3, OnChangeBuddy1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSpinExDlg message handlers

BOOL CSpinExDlg::OnInitDialog()
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
	// when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// Set the COXSpinCtrl objects, which are mapped to a common Spin Controls (Red, Green and Blue spins).
	m_SpinEx1.SetBuddy(&m_Buddy1);
	m_SpinEx1.SetRange(0, 255);
	m_SpinEx1.SetPos(100);
	m_SpinEx2.SetBuddy(&m_Buddy2);
	m_SpinEx2.SetRange(0, 255);
	m_SpinEx2.SetPos(100);
	m_SpinEx3.SetBuddy(&m_Buddy3);
	m_SpinEx3.SetRange(0, 255);
	m_SpinEx3.SetPos(100);

	// Create a new COXSpinCtrl object (Size spin).
	m_nColorBarHei = 160;	// Color Bar height.
	m_nColorBarWid = 220;	// Color Bar width.
	RECT rectSpinPos;
	m_Buddy4.GetWindowRect(&rectSpinPos);
	ScreenToClient(&rectSpinPos);
	int nBuddyHei = rectSpinPos.bottom - rectSpinPos.top;
	rectSpinPos.top = rectSpinPos.bottom + 1;
	rectSpinPos.bottom = rectSpinPos.top + nBuddyHei;
	m_SpinEx4.Create(WS_VISIBLE | UDS_HORZ | UDS_SETBUDDYINT, rectSpinPos, this, IDC_SPINEX4);
	m_SpinEx4.SetBuddy(&m_Buddy4);
	m_SpinEx4.SetRange((short)m_nColorBarWid - 150, (short)m_nColorBarWid);
	m_SpinEx4.SetPos(m_nColorBarWid);

	// Set a default COXSpinCtrl method of delta value computation (Delta pixel = Delta value).
	m_SpinEx1.SetComputationMethod(OX_SPIN_DELTA_PIXEL_IS_DELTA_VALUE);
	m_SpinEx2.SetComputationMethod(OX_SPIN_DELTA_PIXEL_IS_DELTA_VALUE);
	m_SpinEx3.SetComputationMethod(OX_SPIN_DELTA_PIXEL_IS_DELTA_VALUE);
	m_SpinEx4.SetComputationMethod(OX_SPIN_DELTA_PIXEL_IS_DELTA_VALUE);
	CheckRadioButton(IDC_RADIO1, IDC_RADIO2, IDC_RADIO1);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CSpinExDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CUTSampleAboutDlg dlgAbout(IDR_MAINFRAME,ID_DESCRIPTION_FILE);
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

void CSpinExDlg::OnPaint() 
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
HCURSOR CSpinExDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CSpinExDlg::OnRadio1()
// Set a COXSpinCtrl method of delta value computation (Delta pixel = Delta value).
{
	m_SpinEx1.SetComputationMethod(OX_SPIN_DELTA_PIXEL_IS_DELTA_VALUE);
	m_SpinEx2.SetComputationMethod(OX_SPIN_DELTA_PIXEL_IS_DELTA_VALUE);
	m_SpinEx3.SetComputationMethod(OX_SPIN_DELTA_PIXEL_IS_DELTA_VALUE);
	m_SpinEx4.SetComputationMethod(OX_SPIN_DELTA_PIXEL_IS_DELTA_VALUE);
}

void CSpinExDlg::OnRadio2()
// Set a COXSpinCtrl method of delta value computation (Screen limits).
{
	m_SpinEx1.SetComputationMethod(OX_SPIN_SCREEN_AREA);
	m_SpinEx2.SetComputationMethod(OX_SPIN_SCREEN_AREA);
	m_SpinEx3.SetComputationMethod(OX_SPIN_SCREEN_AREA);
	m_SpinEx4.SetComputationMethod(OX_SPIN_SCREEN_AREA);
}

void CSpinExDlg::OnChangeBuddy1()
// Update color of Color Bar (as result of color component change).
{
	UpdateData(TRUE);
	m_ColorBar.SetBarColor(m_nBuddy2/*Red*/, m_nBuddy1/*Green*/, m_nBuddy3/*Blue*/);
}

void CSpinExDlg::OnChangeBuddy4()
// Change the Color Bar size.
{
	RECT	rectBarPos;
	int		newWid, newHei;

	m_ColorBar.GetWindowRect(&rectBarPos);
	ScreenToClient(&rectBarPos);
	UpdateData(TRUE);
	if (m_nBuddy4 <=220 && m_nBuddy4 >=70)
	{	newWid = m_nBuddy4;
	newHei = m_nColorBarHei - m_nColorBarWid + m_nBuddy4;
	m_ColorBar.MoveWindow(rectBarPos.left, rectBarPos.top, newWid, newHei);
	}
	else 
		MessageBox(_T("Value should not be greater than 220 nor less than 70"));
}
