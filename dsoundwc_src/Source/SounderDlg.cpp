// SounderDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Sounder.h"
#include "SounderDlg.h"
#include <afxMt.h>
#include <DSound.h>

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
// CSounderDlg dialog

CSounderDlg	*CSounderDlg::pThis;


CSounderDlg::CSounderDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSounderDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSounderDlg)
	m_strPath = _T("");
	m_bRepeat = FALSE;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	////////////////////
	m_bRunning = FALSE;

	// Note: CSounderDlg will have only one instance in this app
	CSounderDlg::pThis = this; // Refered in the callback function
}

void CSounderDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSounderDlg)
	DDX_Control(pDX, IDC_SLIDER_VOLUME, m_sliderVolume);
	DDX_Control(pDX, IDC_SLIDER_PAN, m_sliderPan);
	DDX_Control(pDX, IDC_SLIDER_FREQUANCY, m_sliderFreq);
	DDX_Text(pDX, IDC_EDIT_PATH, m_strPath);
	DDV_MaxChars(pDX, m_strPath, 256);
	DDX_Check(pDX, IDC_CHECK_REPEAT, m_bRepeat);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSounderDlg, CDialog)
	//{{AFX_MSG_MAP(CSounderDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BROWSE, OnBrowse)
	ON_BN_CLICKED(IDC_PLAYSTOP, OnPlayStop)
	ON_WM_DESTROY()
	ON_WM_VSCROLL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSounderDlg message handlers

BOOL CSounderDlg::OnInitDialog()
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

	m_dsound.Create();
	m_dsound.SetCooperativeLevel(GetSafeHwnd());

	m_sliderVolume.SetRange(0, 100);
	m_sliderVolume.SetPos(50);
	m_sliderVolume.EnableWindow(0);
	SetDlgItemInt(IDC_STATIC_VOL, 50);

	m_sliderFreq.SetRange(DSBFREQUENCY_MIN, DSBFREQUENCY_MAX);
	m_sliderFreq.SetPos((DSBFREQUENCY_MAX + DSBFREQUENCY_MIN) / 2);
	m_sliderFreq.EnableWindow(0);
	SetDlgItemInt(IDC_STATIC_FRE, (DSBFREQUENCY_MAX + DSBFREQUENCY_MIN) / 2);
	
	m_sliderPan.SetRange(DSBPAN_LEFT-DSBPAN_LEFT, DSBPAN_RIGHT-DSBPAN_LEFT);
	m_sliderPan.SetPos((DSBPAN_LEFT + DSBPAN_RIGHT) / 2 - DSBPAN_LEFT);
	m_sliderPan.EnableWindow(0);
	SetDlgItemInt(IDC_STATIC_PAN, (DSBPAN_LEFT + DSBPAN_RIGHT) / 2);

	GetDlgItem(IDC_PLAYSTOP)->EnableWindow(0);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CSounderDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CSounderDlg::OnPaint() 
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
HCURSOR CSounderDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

BOOL CSounderDlg::_Load()
{
	UpdateData();
	CString strPath = m_strPath;
	m_player.Destroy();
	BOOL fOk = m_player.Create(&m_dsound, strPath, DSBCAPS_CTRLPOSITIONNOTIFY | DSBCAPS_REGULAR);
	m_player.SetCurrentPosition(0); ///
	m_sliderVolume.EnableWindow();
	m_sliderFreq.EnableWindow();
	m_sliderPan.EnableWindow();

	m_sliderFreq.SetPos(DSBFREQUENCY_MIN + DSBFREQUENCY_MAX - m_player.GetFrequency());
	OnVScroll(0, 0, (CScrollBar *) &m_sliderFreq); // update UI

	m_sliderVolume.SetPos(m_player.GetVolume());
	OnVScroll(0, 0, (CScrollBar *) &m_sliderVolume); // update UI

	m_sliderPan.SetPos(m_player.GetPan() - DSBPAN_LEFT);
	OnVScroll(0, 0, (CScrollBar *) &m_sliderPan); // update UI

	GetDlgItem(IDC_PLAYSTOP)->EnableWindow(fOk);

	return fOk;
}

void CSounderDlg::OnBrowse() 
{
	CFileDialog dlg(TRUE, _T("wav"), 
		NULL, OFN_FILEMUSTEXIST,
		_T("Wave files (*.wav) |*.wav|")
		_T("All files (*.*) |*.*|"));
	if (IDOK == dlg.DoModal())
	{
		m_strPath = dlg.GetPathName();
		UpdateData(0);
		VERIFY(_Load());

		m_player.SetNotifyFunction(CSounderDlg::NotifyCallback);
		DWORD dwOffset[] = { 0, DSBPN_OFFSETSTOP };
		m_player.SetNotificationPositions(dwOffset, 2);
	}
}

void CSounderDlg::OnPlayStop() 
{
	UpdateData();
	CString strCaption;
	if (m_bRunning)
	{
		strCaption = TEXT("Play");
		m_player.Stop();
	}
	else
	{
		strCaption = TEXT("Stop");
		m_player.SetCurrentPosition(0);
		m_player.Play(m_bRepeat);
	}
	GetDlgItem(IDC_PLAYSTOP)->SetWindowText(strCaption);
	GetDlgItem(IDC_CHECK_REPEAT)->EnableWindow(m_bRunning);
	m_bRunning ^= 1;
}

void CSounderDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	m_player.Destroy();
	m_dsound.Destroy();
}

void CSounderDlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	if (!pScrollBar || !::IsWindow(pScrollBar->m_hWnd))
		return;

	CSliderCtrl *pSlider = (CSliderCtrl *) pScrollBar;
	nPos = pSlider->GetPos();
	int nReal;

	switch (pSlider->GetDlgCtrlID())
	{
	case IDC_SLIDER_VOLUME:
		nReal = 100 - nPos;
		SetDlgItemInt(IDC_STATIC_VOL, nReal);
		m_player.SetVolume(DSVOLUME_TO_DB(nReal));
		break;
	case IDC_SLIDER_FREQUANCY:
		nReal = DSBFREQUENCY_MIN + DSBFREQUENCY_MAX - nPos;
		SetDlgItemInt(IDC_STATIC_FRE, nReal);
		m_player.SetFrequency(nReal);
		break;
	case IDC_SLIDER_PAN:
		nReal = DSBPAN_LEFT + DSBPAN_RIGHT - nPos - DSBPAN_LEFT;
		SetDlgItemInt(IDC_STATIC_PAN, nReal);
		m_player.SetPan(nReal);
		break;
	default:
		__assume(0); // no default
	}

	CDialog::OnVScroll(nSBCode, nPos, pScrollBar);
}

LONG CSounderDlg::NotifyCallback(LONG f) // static function
{
	TRACE("- CSounderDlg::NotifyCallback: %d\n", f);
	if (0 == f)
	{
		CSounderDlg::pThis->SetDlgItemText(IDC_STATIC_EVENT, TEXT("started"));
	}
	else if (DSBPN_OFFSETSTOP == f) // -1
	{
		CSounderDlg::pThis->SetDlgItemText(IDC_STATIC_EVENT, TEXT("stopped"));
		CSounderDlg::pThis->GetDlgItem(IDC_PLAYSTOP)->SetWindowText("Play");
		CSounderDlg::pThis->GetDlgItem(IDC_CHECK_REPEAT)->EnableWindow();
		CSounderDlg::pThis->m_bRunning = FALSE;
	}
	return 0;
}
