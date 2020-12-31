// VolumeControlDlg.cpp : implementation file
//

#include "stdafx.h"
#include "VolumeControl.h"
#include "VolumeControlDlg.h"
#include "SystrayIcon.h"
#include "MouseHook.h"

#include "iTunesCOMInterface.h"

#include <WtsApi32.h>
#include <MMSystem.h>

//Messages to monitor session Lock and Unlock
#define WM_WTSSESSION_CHANGE            0x02B1
#define WTS_SESSION_LOCK                   0x7
#define WTS_SESSION_UNLOCK                 0x8

//Messages to monitor Jet Audio status.
#define WM_REMOCON_GETSTATUS    (WM_APP+740)
#define WM_REMOCON_SENDCOMMAND	(WM_APP+741)
#define GET_STATUS_STATUS       (1)
#define JRC_ID_PLAY             5104

const CLSID CLSID_iTunesApp = {0xDC0C2640,0x1415,0x4644,{0x87,0x5C,0x6F,0x4D,0x76,0x98,0x39,0xBA}};
const IID IID_IiTunes = {0x9DD6680B,0x3EDC,0x40db,{0xA7,0x71,0xE6,0xFE,0x48,0x32,0xE3,0x4A}};

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define WM_TRAY_NOTIFY WM_APP+1000

	// Icon AND bitmask 
	BYTE ANDmaskIcon[] = {0xF0, 0x00, 0x00, 0x0F,   // line 1 
						  0xF0, 0x00, 0x00, 0x0F,   // line 2 
						  0xF0, 0x00, 0x00, 0x0F,   // line 3 
						  0xF0, 0x00, 0x00, 0x0F,   // line 4 
 
						  0xF0, 0x00, 0x00, 0x0F,   // line 5 
						  0xF0, 0x00, 0x00, 0x0F,   // line 6 
						  0xF0, 0x00, 0x00, 0x0F,   // line 7 
						  0xF0, 0x00, 0x00, 0x0F,   // line 8 
 
						  0xF0, 0x00, 0x00, 0x0F,   // line 9 
						  0xF0, 0x00, 0x00, 0x0F,   // line 10 
						  0xF0, 0x00, 0x00, 0x0F,   // line 11 
						  0xF0, 0x00, 0x00, 0x0F,   // line 12 
 
						  0xF0, 0x00, 0x00, 0x0F,   // line 13 
						  0xF0, 0x00, 0x00, 0x0F,   // line 14 
						  0xF0, 0x00, 0x00, 0x0F,   // line 15 
						  0xF0, 0x00, 0x00, 0x0F,   // line 16 
 
						  0xF0, 0x00, 0x00, 0x0F,   // line 17 
						  0xF0, 0x00, 0x00, 0x0F,   // line 18 
						  0xF0, 0x00, 0x00, 0x0F,   // line 19 
						  0xF0, 0x00, 0x00, 0x0F,   // line 20 
 
						  0xF0, 0x00, 0x00, 0x0F,   // line 21 
						  0xF0, 0x00, 0x00, 0x0F,   // line 22 
						  0xF0, 0x00, 0x00, 0x0F,   // line 23 
						  0xF0, 0x00, 0x00, 0x0F,   // line 24 
 
						  0xF0, 0x00, 0x00, 0x0F,   // line 25 
						  0xF0, 0x00, 0x00, 0x0F,   // line 26 
						  0xF0, 0x00, 0x00, 0x0F,   // line 27 
						  0xF0, 0x00, 0x00, 0x0F,   // line 28 
 
						  0xF0, 0x00, 0x00, 0x0F,   // line 29 
						  0xF0, 0x00, 0x00, 0x0F,   // line 30 
						  0xF0, 0x00, 0x00, 0x0F,   // line 31 
						  0xF0, 0x00, 0x00, 0x0F};  // line 32 

	// Icon XOR bitmask  
	BYTE XORmaskIcon[] = {0x00, 0x00, 0x00, 0x00,   // line 1 
						  0x00, 0x00, 0x00, 0x00,   // line 2 
						  0x00, 0x00, 0x00, 0x00,   // line 3 
						  0x00, 0x00, 0x00, 0x00,   // line 4 
 
						  0x00, 0x00, 0x00, 0x00,   // line 5 
						  0x00, 0x00, 0x00, 0x00,   // line 6 
						  0x00, 0x00, 0x00, 0x00,   // line 7 
						  0x00, 0x00, 0x00, 0x00,   // line 8 
 
						  0x00, 0x00, 0x00, 0x00,   // line 9 
						  0x00, 0x00, 0x00, 0x00,   // line 10 
						  0x00, 0x00, 0x00, 0x00,   // line 11 
						  0x00, 0x00, 0x00, 0x00,   // line 12 
 
						  0x00, 0x00, 0x00, 0x00,   // line 13 
						  0x00, 0x00, 0x00, 0x00,   // line 14 
						  0x00, 0x00, 0x00, 0x00,   // line 15 
						  0x00, 0x00, 0x00, 0x00,   // line 16 
 
						  0x00, 0x00, 0x00, 0x00,   // line 17 
						  0x00, 0x00, 0x00, 0x00,   // line 18 
						  0x00, 0x00, 0x00, 0x00,   // line 19 
						  0x00, 0x00, 0x00, 0x00,   // line 20 
 
						  0x00, 0x00, 0x00, 0x00,   // line 21 
						  0x00, 0x00, 0x00, 0x00,   // line 22 
						  0x00, 0x00, 0x00, 0x00,   // line 23 
						  0x00, 0x00, 0x00, 0x00,   // line 24 
 
						  0x00, 0x00, 0x00, 0x00,   // line 25 
						  0x00, 0x00, 0x00, 0x00,   // line 26 
						  0x00, 0x00, 0x00, 0x00,   // line 27 
						  0x00, 0x00, 0x00, 0x00,   // line 28 
 
						  0x00, 0x00, 0x00, 0x00,   // line 29 
						  0x00, 0x00, 0x00, 0x00,   // line 30 
						  0x00, 0x00, 0x00, 0x00,   // line 31 
						  0x00, 0x00, 0x00, 0x00};  // line 32 

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
// CVolumeControlDlg dialog

CVolumeControlDlg::CVolumeControlDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CVolumeControlDlg::IDD, pParent),
	m_hMixer( NULL ),
	m_dwVolumeValue( 0 ),
	m_pTrayIcon( 0 ),
	m_pMouseHook( 0 ),
	m_bIsMute( false ),
	m_dwPrevVolumeValue( 32768 ),
    m_bWasJetAudioMutedByUs( false ),
    m_bWasWmpMutedByUs( false ),
    m_bWasWinampMutedByUs( false ),
    m_bWasiTunesMutedByUs( false )
{
	//{{AFX_DATA_INIT(CVolumeControlDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	//m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CVolumeControlDlg::~CVolumeControlDlg()
{
	m_pMouseHook->DisableHook();

	delete m_pMouseHook;
	delete m_pTrayIcon;
}

void CVolumeControlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CVolumeControlDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CVolumeControlDlg, CDialog)
	//{{AFX_MSG_MAP(CVolumeControlDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_MOUSEWHEEL()
	ON_COMMAND(ID_MENU_EXIT, OnMenuExit)
	ON_MESSAGE( MM_MIXM_CONTROL_CHANGE, OnMixerControlChange )
	ON_MESSAGE( WM_TRAY_NOTIFY, OnTrayNotify )
	ON_MESSAGE( WM_MBUTTONUP, OnMButtonUp )
    ON_MESSAGE( WM_WTSSESSION_CHANGE, OnSessionChange )
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVolumeControlDlg message handlers

BOOL CVolumeControlDlg::OnInitDialog()
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

	SetWindowText( PROG_NAME );

	InitializeMixer();
	GetMasterVolumeControl();
	GetMasterVolumeValue( m_dwVolumeValue );
	if( m_dwVolumeValue == 0 )
	{
		m_bIsMute = true;
	}

	RedrawIcon();

	m_pTrayIcon = new SystrayIcon( this, WM_TRAY_NOTIFY, "Volume Control",
								   &m_hIcon );
	m_pTrayIcon->SetState();
	
    m_pMouseHook = ( MouseHook* )
                            AfxBeginThread( RUNTIME_CLASS( MouseHook ));

    m_pMouseHook->EnableHook( m_hWnd );

    WTSRegisterSessionNotification( this->m_hWnd, NOTIFY_FOR_THIS_SESSION );
    
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CVolumeControlDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CVolumeControlDlg::OnPaint() 
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

		::ShowWindow( m_hWnd, SW_HIDE );

		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CVolumeControlDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CVolumeControlDlg::RedrawIcon( bool bMute /* = true  */ )
{
//    if( bMute )
//    {
//        HICON hIcon = 0;
//        hIcon = AfxGetApp()->LoadIcon( IDI_ICON_MUTE );
//        
//        SetIcon( hIcon, TRUE);			// Set big icon
//	    SetIcon( hIcon, FALSE);		// Set small icon
//	    
//	    if( m_pTrayIcon )
//	    {
//		    m_pTrayIcon->SetState( hIcon );
//	    }
//    }
//    else if( !bMute )
    {
        InvalidateIcon();
    }
}

void CVolumeControlDlg::InvalidateIcon() 
{
	UINT nRgnStartIndx = 0;

	nRgnStartIndx = ( UINT )(( m_dwVolumeValue /( float )65536 ) * 20 );

	nRgnStartIndx += 4;
	nRgnStartIndx *= 4;	

	nRgnStartIndx = 112 - nRgnStartIndx;

	BYTE* XORArray = new BYTE [ sizeof( XORmaskIcon ) ];
	memcpy( XORArray, XORmaskIcon, sizeof( XORmaskIcon ));

	for( UINT i = nRgnStartIndx + 1; i < nRgnStartIndx + 20; i += 4  )
	{
		XORArray[ i ] = 0xFF;
		XORArray[ i + 1 ] = 0xFF;		
	}

	m_hIcon = CreateIcon(AfxGetInstanceHandle(), // application instance  
			  32,              // icon width 
			  32,              // icon height 
			  1,               // number of XOR planes 
			  1,               // number of bits per pixel 
			  ANDmaskIcon,     // AND bitmask  
			  XORArray );   // XOR bitmask  


	SetIcon( m_hIcon, TRUE);			// Set big icon
	SetIcon( m_hIcon, FALSE);		// Set small icon
	
	if( m_pTrayIcon )
	{
		m_pTrayIcon->SetState();
	}
}

BOOL CVolumeControlDlg::InitializeMixer()
{
	ASSERT(m_hMixer == NULL);

	// get the number of mixer devices present in the system
	m_nNumMixers = ::mixerGetNumDevs();

	m_hMixer = NULL;
	::ZeroMemory(&m_mxcaps, sizeof(MIXERCAPS));

	m_strDstLineName.Empty();
	m_strVolumeControlName.Empty();
	m_dwMinimum = 0;
	m_dwMaximum = 0;
	m_dwVolumeControlID = 0;

	// open the first mixer
	// A "mapper" for audio mixer devices does not currently exist.
	if (m_nNumMixers != 0)
	{
		if (::mixerOpen(&m_hMixer,
						0,
						reinterpret_cast<DWORD>(this->GetSafeHwnd()),
						NULL,
						MIXER_OBJECTF_MIXER | CALLBACK_WINDOW)
			!= MMSYSERR_NOERROR)
		{
			return FALSE;
		}

		if (::mixerGetDevCaps(reinterpret_cast<UINT>(m_hMixer),
							  &m_mxcaps, sizeof(MIXERCAPS))
			!= MMSYSERR_NOERROR)
		{
			return FALSE;
		}
	}

	return TRUE;
}

BOOL CVolumeControlDlg::UninitializeMixer()
{
	BOOL bSucc = TRUE;

	if (m_hMixer != NULL)
	{
		bSucc = (::mixerClose(m_hMixer) == MMSYSERR_NOERROR);
		m_hMixer = NULL;
	}

	return bSucc;
}

BOOL CVolumeControlDlg::GetMasterVolumeControl()
{
	if (m_hMixer == NULL)
	{
		return FALSE;
	}

	// get dwLineID
	MIXERLINE mxl;
	mxl.cbStruct = sizeof(MIXERLINE);
	mxl.dwComponentType = MIXERLINE_COMPONENTTYPE_DST_SPEAKERS;
	if (::mixerGetLineInfo(reinterpret_cast<HMIXEROBJ>(m_hMixer),
						   &mxl,
						   MIXER_OBJECTF_HMIXER |
						   MIXER_GETLINEINFOF_COMPONENTTYPE)
		!= MMSYSERR_NOERROR)
	{
		return FALSE;
	}

	// get dwControlID
	MIXERCONTROL mxc;
	MIXERLINECONTROLS mxlc;
	mxlc.cbStruct = sizeof(MIXERLINECONTROLS);
	mxlc.dwLineID = mxl.dwLineID;
	mxlc.dwControlType = MIXERCONTROL_CONTROLTYPE_VOLUME;
	mxlc.cControls = 1;
	mxlc.cbmxctrl = sizeof(MIXERCONTROL);
	mxlc.pamxctrl = &mxc;
	if (::mixerGetLineControls(reinterpret_cast<HMIXEROBJ>(m_hMixer),
							   &mxlc,
							   MIXER_OBJECTF_HMIXER |
							   MIXER_GETLINECONTROLSF_ONEBYTYPE)
		!= MMSYSERR_NOERROR)
	{
		return FALSE;
	}

	// store dwControlID
	m_strDstLineName = mxl.szName;
	m_strVolumeControlName = mxc.szName;
	m_dwMinimum = mxc.Bounds.dwMinimum;
	m_dwMaximum = mxc.Bounds.dwMaximum;
	m_dwVolumeControlID = mxc.dwControlID;

	return TRUE;
}

BOOL CVolumeControlDlg::GetMasterVolumeValue(DWORD &dwVal) const
{
	if (m_hMixer == NULL)
	{
		return FALSE;
	}

	MIXERCONTROLDETAILS_UNSIGNED mxcdVolume;
	MIXERCONTROLDETAILS mxcd;
	mxcd.cbStruct = sizeof(MIXERCONTROLDETAILS);
	mxcd.dwControlID = m_dwVolumeControlID;
	mxcd.cChannels = 1;
	mxcd.cMultipleItems = 0;
	mxcd.cbDetails = sizeof(MIXERCONTROLDETAILS_UNSIGNED);
	mxcd.paDetails = &mxcdVolume;
	if (::mixerGetControlDetails(reinterpret_cast<HMIXEROBJ>(m_hMixer),
								 &mxcd,
								 MIXER_OBJECTF_HMIXER |
								 MIXER_GETCONTROLDETAILSF_VALUE)
		!= MMSYSERR_NOERROR)
	{
		return FALSE;
	}
	
	dwVal = mxcdVolume.dwValue;

	return TRUE;
}

BOOL CVolumeControlDlg::SetMasterVolumeValue(DWORD dwVal) const
{
	if (m_hMixer == NULL)
	{
		return FALSE;
	}

	MIXERCONTROLDETAILS_UNSIGNED mxcdVolume = { dwVal };
	MIXERCONTROLDETAILS mxcd;
	mxcd.cbStruct = sizeof(MIXERCONTROLDETAILS);
	mxcd.dwControlID = m_dwVolumeControlID;
	mxcd.cChannels = 1;
	mxcd.cMultipleItems = 0;
	mxcd.cbDetails = sizeof(MIXERCONTROLDETAILS_UNSIGNED);
	mxcd.paDetails = &mxcdVolume;
	if (::mixerSetControlDetails(reinterpret_cast<HMIXEROBJ>(m_hMixer),
								 &mxcd,
								 MIXER_OBJECTF_HMIXER |
								 MIXER_SETCONTROLDETAILSF_VALUE)
		!= MMSYSERR_NOERROR)
	{
		return FALSE;
	}
	
	return TRUE;
}

BOOL CVolumeControlDlg::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) 
{
	int nScrollValue = ( zDelta /  120 );
	nScrollValue *= 1024;

	if( nScrollValue < 0 && m_dwVolumeValue < ( UINT )abs( nScrollValue ))
	{
		m_dwVolumeValue = 0;
	}
	else
	{
		m_dwVolumeValue += nScrollValue;
	}

	if( m_dwVolumeValue > 65536 )
	{
		m_dwVolumeValue = 65536;
	}
	else if( m_dwVolumeValue < 0 )
	{
		m_dwVolumeValue = 0;
	}
	
	SetMasterVolumeValue( m_dwVolumeValue );
	GetMasterVolumeValue( m_dwVolumeValue );
	RedrawIcon();
	m_bIsMute = false;
	
	return CDialog::OnMouseWheel(nFlags, zDelta, pt);
}

void CVolumeControlDlg::OnMixerControlChange( WPARAM wPrm, LPARAM lPrm )
{
	HMIXER hMixer = ( HMIXER )wPrm;

	if( m_dwVolumeControlID == ( unsigned )lPrm )
	{
		GetMasterVolumeValue( m_dwVolumeValue );
		RedrawIcon();
	}
}

void CVolumeControlDlg::OnMenuExit() 
{
	CDialog::OnCancel();
	
}

void CVolumeControlDlg::OnCancel() 
{	
	//CDialog::OnCancel();
}

LONG CVolumeControlDlg::OnTrayNotify ( WPARAM wParam, LPARAM lParam )
{
	switch ( lParam )
	{
		case WM_LBUTTONDOWN:
		case WM_RBUTTONDOWN:
		{
			CMenu menu ;

			VERIFY(menu.LoadMenu(IDR_MENU1));
			CMenu* pPopup = menu.GetSubMenu (0) ;
			ASSERT(pPopup != NULL);

			// Get the cursor position
			POINT pt ;
			GetCursorPos (&pt) ;

			// Fix Microsofts' BUG!!!!
			SetForegroundWindow();

			///////////////////////////////////
			// Display The Menu
			pPopup->TrackPopupMenu(TPM_LEFTALIGN |
			TPM_RIGHTBUTTON,pt.x, pt.y, AfxGetMainWnd());
			
			break ;
		}
	}
	return 0;
}

void CVolumeControlDlg::OnMButtonUp( WPARAM wPrm, LPARAM lPrm )
{
    m_bIsMute = !m_bIsMute;

    MuteVolume( m_bIsMute );
    RedrawIcon( m_bIsMute );
}

void CVolumeControlDlg::OnSessionChange( WPARAM wPrm, LPARAM lPrm )
{
    if( WTS_SESSION_LOCK == wPrm )
    {
        m_bIsMute = true;
    }
    else if( WTS_SESSION_UNLOCK == wPrm )
    {
        m_bIsMute = false;		
    }

    PauseWinamp( m_bIsMute );
    PauseJetAudio( m_bIsMute );
    PauseiTunes( m_bIsMute );
    PauseWMP( m_bIsMute );

    MuteVolume( m_bIsMute );
	RedrawIcon( m_bIsMute );
}

void CVolumeControlDlg::MuteVolume( bool bMute /* = true  */ )
{
    if( bMute )
    {
        m_dwPrevVolumeValue = m_dwVolumeValue;
        SetMasterVolumeValue( 0 );		
		GetMasterVolumeValue( m_dwVolumeValue );
    }
    else
    {
        SetMasterVolumeValue( m_dwPrevVolumeValue );
		GetMasterVolumeValue( m_dwVolumeValue );
    }
}

void CVolumeControlDlg::PauseJetAudio( bool bMute /* = true  */ )
{
    HWND hWndJetAudio = NULL;
    hWndJetAudio = ::FindWindow( "COWON Jet-Audio Remocon Class",
                                  "Jet-Audio Remote Control" );

    if( hWndJetAudio )
    {
        int nStatus = ::SendMessage( hWndJetAudio,
                                     WM_REMOCON_GETSTATUS,
                                     ( WPARAM )GetSafeHwnd(),
                                     GET_STATUS_STATUS );

        if( bMute )
        {
            if( MCI_MODE_PLAY == nStatus )
            {
                ::SendMessage( hWndJetAudio, 
                               WM_REMOCON_SENDCOMMAND,
                               0,
                               MAKELPARAM( JRC_ID_PLAY, 0 ));
            
                m_bWasJetAudioMutedByUs = true;
            }
        }
        else
        {
            if( MCI_MODE_PLAY != nStatus &&
                m_bWasJetAudioMutedByUs )
            {
                ::SendMessage( hWndJetAudio, 
                               WM_REMOCON_SENDCOMMAND,
                               0,
                               MAKELPARAM( JRC_ID_PLAY, 0 ));
            }

            m_bWasJetAudioMutedByUs = false;
        }
    }
}

void CVolumeControlDlg::PauseWinamp( bool bMute /* = true  */ )
{
    HWND hWndWinamp = NULL;
    hWndWinamp = ::FindWindow ( "Winamp v1.x", NULL );

    if( hWndWinamp )
    {
        CString csWinampText;

        ::GetWindowText( hWndWinamp, csWinampText.GetBuffer( 0 ), MAX_PATH );

        if( bMute )
        {
            if( -1 == csWinampText.Find( "[Stopped]" ) && 
                -1 == csWinampText.Find( "[Paused]" ) &&
                -1 != csWinampText.Find( "- Winamp" ))
            {
                ::SendMessage( hWndWinamp, WM_KEYDOWN, ( WPARAM )0x43, 0 );

                m_bWasWinampMutedByUs = true;
            }
        }
        else
        {
            if( m_bWasWinampMutedByUs && 
                ( -1 != csWinampText.Find( "[Paused]" )))
            {
                ::SendMessage( hWndWinamp, WM_KEYDOWN, ( WPARAM )0x43, 0 );
            }

            m_bWasWinampMutedByUs = false;
        }
    }
}

void CVolumeControlDlg::PauseiTunes( bool bMute /* = true  */ )
{
    IiTunes *iITunes = NULL;
    HRESULT hRes = -1;

    HWND hWndiTunes = NULL;
    hWndiTunes = ::FindWindow ( "iTunes", NULL );

    if( hWndiTunes )
    {
        CoInitialize( NULL );

        hRes = CoCreateInstance( CLSID_iTunesApp,
                                 NULL, CLSCTX_LOCAL_SERVER,
                                 IID_IiTunes, ( LPVOID* ) &iITunes );
    }    

    if( hRes == S_OK )
    {
        ITPlayerState state = ITPlayerStateStopped;

        iITunes->get_PlayerState( &state );

        if( bMute )
        {
            if( ITPlayerStatePlaying == state )
            {
                iITunes->Pause();
                m_bWasiTunesMutedByUs = true;
            }
        }
        else
        {
            if( ITPlayerStateStopped == state &&
                m_bWasiTunesMutedByUs )
            {
                iITunes->Play();
            }

            m_bWasiTunesMutedByUs = false;
        }
    }
}

void CVolumeControlDlg::PauseWMP( bool bMute /* = true  */ )
{
    HWND hWndWMP= NULL;
    hWndWMP = ::FindWindow( "WMPlayerApp", NULL );

    if( hWndWMP )
    {
        if( bMute )
        {
            ::PostMessage( hWndWMP, WM_COMMAND, 84345, 0 );
        }
    }
}