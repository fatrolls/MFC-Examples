// SoundManagerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SoundManager.h"
#include "SoundManagerDlg.h"
#include "OXSoundCustomizeDlg.h"

#include "UTBStrOp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// message to react on "About" action
static UINT g_nAboutMsgID=RegisterWindowMessage(_T("AboutSoundEffectOrganizer"));

/////////////////////////////////////////////////////////////////////////////
// CSoundManagerDlg dialog

CSoundManagerDlg::CSoundManagerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSoundManagerDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSoundManagerDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSoundManagerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSoundManagerDlg)
	DDX_Control(pDX, IDC_STATIC_OPTION9, m_ctlClose);
	DDX_Control(pDX, IDC_STATIC_OPTION8, m_ctlCustomize);
	DDX_Control(pDX, IDC_STATIC_OPTION7, m_ctlOption7);
	DDX_Control(pDX, IDC_STATIC_OPTION6, m_ctlOption6);
	DDX_Control(pDX, IDC_STATIC_OPTION5, m_ctlOption5);
	DDX_Control(pDX, IDC_STATIC_ABOUT, m_ctlAbout);
	DDX_Control(pDX, IDC_STATIC_OPTION4, m_ctlOption4);
	DDX_Control(pDX, IDC_STATIC_OPTION3, m_ctlOption3);
	DDX_Control(pDX, IDC_STATIC_OPTION2, m_ctlOption2);
	DDX_Control(pDX, IDC_STATIC_OPTION1, m_ctlOption1);
	DDX_Control(pDX, IDC_STATIC_INFO, m_ctlInfo);
	DDX_Control(pDX, IDC_ANIMATE_MFC, m_animMFC);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSoundManagerDlg, CDialog)
	//{{AFX_MSG_MAP(CSoundManagerDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_REGISTERED_MESSAGE(g_nAboutMsgID,OnAboutActivated)
	ON_MESSAGE(WM_APP_CUSTOMIZE,OnCustomize)
	ON_MESSAGE(WM_APP_CLOSE,OnClose)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSoundManagerDlg message handlers

BOOL CSoundManagerDlg::OnInitDialog()
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
	LOGFONT lf;

	// set action as userdefined 
	// don't forget to set callback message and handle to recipient window
	if(GetFont()->GetObject(sizeof(lf), &lf))
	{
		lf.lfHeight=-12;
		lf.lfUnderline=FALSE;
		lf.lfWeight=FW_BOLD;
		UTBStr::tcsncpy(lf.lfFaceName, LF_FACESIZE, _T("Arial"),LF_FACESIZE);
		m_ctlAbout.SetTextLogFont(&lf);
	}
	m_ctlAbout.SetUnvisitedColor(RGB(0,128,128));
	m_ctlAbout.SetAction(ID_HLACTION_USERDEFINED,NULL,NULL,NULL,
		SW_SHOWNORMAL,g_nAboutMsgID,GetSafeHwnd());
	m_ctlAbout.SetShowToolTip(TRUE);
	m_ctlAbout.SetToolTipText(_T("Information about COXSoundEffectOrganizer"));
	m_ctlAbout.SetFitToText(FALSE);
	VERIFY(m_SoundEffectOrganizer.RegisterPlayEvent(&m_ctlAbout,HWM_MOUSEENTER,
		_T(".\\Sound\\HeartBeat2.wav"),TRUE,-1,TRUE));
	VERIFY(m_SoundEffectOrganizer.RegisterPlayEvent(&m_ctlAbout,WM_LBUTTONDOWN,
		_T(".\\Sound\\Camera.wav")));
	VERIFY(m_SoundEffectOrganizer.RegisterStopEvent(&m_ctlAbout,HWM_MOUSELEAVE));

	// menu options
	COLORREF clrText=::GetSysColor(COLOR_BTNTEXT);
	COLORREF clrBack=::GetSysColor(COLOR_BTNFACE);
	int nFontHeight=24;
	int nFontWeight=FW_BOLD;
	CString sFontName=_T("Times New Roman");
	BOOL bEmboss=TRUE;
	int nHorzAlignment=OX_ALIGNHORZ_LEFT;
	int nVertAlignment=OX_ALIGNVERT_CENTER;
	CString sEnterSound=_T(".\\Sound\\camera.wav");
	CString sClickSound=_T(".\\Sound\\deal.wav");

	SetupStaticControl(&m_ctlOption1,clrText,clrBack,nFontHeight,nFontWeight,
		sFontName,bEmboss,nHorzAlignment,nVertAlignment, sEnterSound, sClickSound);
	SetupStaticControl(&m_ctlOption2,clrText,clrBack,nFontHeight,nFontWeight,
		sFontName,bEmboss,nHorzAlignment,nVertAlignment, sEnterSound, sClickSound);
	SetupStaticControl(&m_ctlOption3,clrText,clrBack,nFontHeight,nFontWeight,
		sFontName,bEmboss,nHorzAlignment,nVertAlignment, sEnterSound, sClickSound);
	SetupStaticControl(&m_ctlOption4,clrText,clrBack,nFontHeight,nFontWeight,
		sFontName,bEmboss,nHorzAlignment,nVertAlignment, sEnterSound, sClickSound);
	SetupStaticControl(&m_ctlOption5,clrText,clrBack,nFontHeight,nFontWeight,
		sFontName,bEmboss,nHorzAlignment,nVertAlignment, sEnterSound, sClickSound);
	SetupStaticControl(&m_ctlOption6,clrText,clrBack,nFontHeight,nFontWeight,
		sFontName,bEmboss,nHorzAlignment,nVertAlignment, sEnterSound, sClickSound);
	SetupStaticControl(&m_ctlOption7,clrText,clrBack,nFontHeight,nFontWeight,
		sFontName,bEmboss,nHorzAlignment,nVertAlignment, sEnterSound, sClickSound);
	sFontName=_T("Arial");
	nFontHeight=24;
	nFontWeight=FW_NORMAL;
	SetupStaticControl(&m_ctlCustomize,clrText,clrBack,nFontHeight,nFontWeight,
		sFontName,bEmboss,nHorzAlignment,nVertAlignment, sEnterSound, sClickSound);
	SetupStaticControl(&m_ctlClose,clrText,clrBack,nFontHeight,nFontWeight,
		sFontName,bEmboss,nHorzAlignment,nVertAlignment, sEnterSound, sClickSound);


	// logo
	m_ctlInfo.SetTextColor(::GetSysColor(COLOR_BTNFACE));
	m_ctlInfo.SetBkColor(::GetSysColor(COLOR_BTNSHADOW));
	m_ctlInfo.SetHorzAlignment(OX_ALIGNHORZ_CENTER);
	m_ctlInfo.SetVertAlignment(OX_ALIGNVERT_BOTTOM);
	if(m_ctlInfo.GetLogFont(&lf))
	{
		lf.lfHeight=36;
		lf.lfWidth=0;
		lf.lfWeight=FW_BOLD;
		m_ctlInfo.SetLogFont(&lf);
	}
	m_ctlInfo.SetFontName(_T("Arial"));

	m_ctlInfo.SetEmboss();
	m_ctlInfo.SetCharSet(ANSI_CHARSET);
	m_ctlInfo.SetStringAngle(900,TRUE);

	// animation
	m_animMFC.Open(IDR_ANIMATEDLOGO);
	VERIFY(m_SoundEffectOrganizer.
		RegisterPlayEvent(&m_animMFC,HWM_MOUSEENTER,IDR_DRUMROLL));

	// load saved in registry sound effects
	m_SoundEffectOrganizer.LoadState(&m_animMFC,_T("Animation"));
	m_SoundEffectOrganizer.LoadState(&m_ctlAbout,_T("About Shortcut"));
	m_SoundEffectOrganizer.LoadState(&m_ctlOption1,_T("Option1"));
	m_SoundEffectOrganizer.LoadState(&m_ctlOption2,_T("Option2"));
	m_SoundEffectOrganizer.LoadState(&m_ctlOption3,_T("Option3"));
	m_SoundEffectOrganizer.LoadState(&m_ctlOption4,_T("Option4"));
	m_SoundEffectOrganizer.LoadState(&m_ctlOption5,_T("Option5"));
	m_SoundEffectOrganizer.LoadState(&m_ctlOption6,_T("Option6"));
	m_SoundEffectOrganizer.LoadState(&m_ctlOption7,_T("Option7"));
	m_SoundEffectOrganizer.LoadState(&m_ctlCustomize,_T("Customize"));
	m_SoundEffectOrganizer.LoadState(&m_ctlClose,_T("Close"));

	// Install caption painter
	m_Caption.Attach(this);
	COXCaptionInfo* pCI=m_Caption.GetCaptionInfo(TRUE);
	pCI->SetBackgroundColor(RGB(0xff,0x68,0x20));
	pCI=m_Caption.GetCaptionInfo(FALSE);
	pCI->SetBackgroundColor(RGB(0xD2,0xB4,0x8C));
	SendMessage(WM_NCPAINT);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CSoundManagerDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CSoundManagerDlg::OnPaint() 
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
HCURSOR CSoundManagerDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CSoundManagerDlg::SetupStaticControl(CMyStatic* m_pctl, COLORREF clrText,
										  COLORREF clrBack, int nFontHeight, 
										  int nFontWeight,CString sFontName,
										  BOOL bEmboss, int nHorzAlignment,
										  int nVertAlignment, CString sEnterSound,
										  CString sClickSound) 
{
	m_pctl->SetTextColor(clrText);
	m_pctl->SetBkColor(clrBack);
	LOGFONT lf;
	if(m_pctl->GetLogFont(&lf))
	{
		lf.lfHeight=nFontHeight;
		lf.lfWeight=nFontWeight;
		m_pctl->SetLogFont(&lf);
	}
	m_pctl->SetFontName(sFontName);

	m_pctl->SetEmboss(bEmboss);
	m_pctl->SetHorzAlignment(nHorzAlignment);
	m_pctl->SetVertAlignment(nVertAlignment);
	m_pctl->SetCharSet(ANSI_CHARSET,TRUE);

	VERIFY(m_SoundEffectOrganizer.
		RegisterPlayEvent(m_pctl,WM_LBUTTONDOWN,sEnterSound));
	VERIFY(m_SoundEffectOrganizer.RegisterPlayEvent(m_pctl,HWM_MOUSEENTER,
		sClickSound,FALSE,-1,FALSE));
}

// "About" action was activated
LONG CSoundManagerDlg::OnAboutActivated(UINT wParam, LONG lParam)
{
	UNREFERENCED_PARAMETER(wParam);
	UNREFERENCED_PARAMETER(lParam);

	CUTSampleAboutDlg dlgAbout(IDR_MAINFRAME, ID_DESCRIPTION_FILE);
	dlgAbout.DoModal();

	return (LONG)1;
}

LONG CSoundManagerDlg::OnCustomize(UINT wParam, LONG lParam) 
{
	// TODO: Add your control notification handler code here

	UNREFERENCED_PARAMETER(wParam);
	UNREFERENCED_PARAMETER(lParam);

	COXSoundCustomizeDlg customizeDlg(this,&m_SoundEffectOrganizer,
		LT_EVENT,SCDS_NOTOGGLE|SCDS_SAVESTATE|SCDS_LOADSTATE);
	customizeDlg.DoModal();

	return (LONG)0;
}

LONG CSoundManagerDlg::OnClose(UINT wParam, LONG lParam) 
{
	// TODO: Add your control notification handler code here

	UNREFERENCED_PARAMETER(wParam);
	UNREFERENCED_PARAMETER(lParam);

	// save in registry sound effects
	m_SoundEffectOrganizer.SaveState(&m_animMFC,_T("Animation"));
	m_SoundEffectOrganizer.SaveState(&m_ctlAbout,_T("About Shortcut"));
	m_SoundEffectOrganizer.SaveState(&m_ctlOption1,_T("Option1"));
	m_SoundEffectOrganizer.SaveState(&m_ctlOption2,_T("Option2"));
	m_SoundEffectOrganizer.SaveState(&m_ctlOption3,_T("Option3"));
	m_SoundEffectOrganizer.SaveState(&m_ctlOption4,_T("Option4"));
	m_SoundEffectOrganizer.SaveState(&m_ctlOption5,_T("Option5"));
	m_SoundEffectOrganizer.SaveState(&m_ctlOption6,_T("Option6"));
	m_SoundEffectOrganizer.SaveState(&m_ctlOption7,_T("Option7"));
	m_SoundEffectOrganizer.SaveState(&m_ctlCustomize,_T("Customize"));
	m_SoundEffectOrganizer.SaveState(&m_ctlClose,_T("Close"));

	CDialog::OnOK();

	return (LONG)0;
}

