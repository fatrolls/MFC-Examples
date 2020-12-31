// -----------------------------------------------------------------------------
// AudioControlsDlg.cpp : implementation file
//
//  Copyright (C) 2008 Peter C. Studt
//
//  This software is provided 'as-is', without any express or implied
//  warranty.  In no event will the author be held liable for any damages
//  arising from the use of this software. It can be redistributed and/or 
//  modified under the terms of The Code Project Open License (CPOL)
//
// -----------------------------------------------------------------------------

#include "stdafx.h"
#include "VolumeControl.h"
#include "VolumeControlDlg.h"
// Notes - 
// Libs to add to project properties->Linkier->Input->Additional Depencencies:
// Winmm.lib
// ..\MixerLib\AudioMixerAPI.lib  (assuming the .lib was copied to MixerLib) 
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// -----------------------------------------------------------------------------
// CAboutDlg dialog used for App About      
// -----------------------------------------------------------------------------
class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

// -----------------------------------------------------------------------------
CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

// -----------------------------------------------------------------------------
void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

// -----------------------------------------------------------------------------

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// -----------------------------------------------------------------------------
// CVolumeControlDlg dialog
// -----------------------------------------------------------------------------
CVolumeControlDlg::CVolumeControlDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CVolumeControlDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

// -----------------------------------------------------------------------------
void CVolumeControlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

// -----------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(CVolumeControlDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE( MM_MIXM_CONTROL_CHANGE, OnMixerControlChange )	// Mixer message
	//}}AFX_MSG_MAP
	ON_WM_VSCROLL()
END_MESSAGE_MAP()


// -----------------------------------------------------------------------------
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	// --------------- Initialize the volume slider control  --------------- 
	mpVolCtrl = (CSliderCtrl*)GetDlgItem( IDC_VOL_SLIDER ) ;
	unsigned int nSize ;
	int nChannels ;
	MIXERCONTROL mixerControl ;
	sStateData stateData ;
	int mixerCount = mixerGetNumDevs() ;

	mpVolCtrl->ShowWindow( SW_HIDE ) ;
	if( !mixerCount )
	{
		MessageBox( TEXT("No audio mixers found"), TEXT("Error"), MB_OK ) ;
		return TRUE ;
	}

	mCMixer.Init( 0, GetSafeHwnd() ) ;		// Select the zeroth mixer
	if( !mCMixer.GetDestinationCount() )	// Ensure the destination has controls
	{
		MessageBox( TEXT("Mixer Destination Has No Controls"), TEXT("Error"), MB_OK ) ;
		return TRUE ;
	}

	// Select the first mixer vol control of the zeroth destination of this mixer.  
	mCtrlID = 0xffff ;
	int controlCount = mCMixer.GetDestinationControlCount( 0 ) ;
	for( int n1=0 ; n1<controlCount ; n1++ )
	{								
		mCMixer.GetDestControlMetrics( 0, n1, &mixerControl ) ;
		if( mixerControl.dwControlType == MIXERCONTROL_CONTROLTYPE_VOLUME )
		{	
			// Init the volume slider
			mCtrlID = mixerControl.dwControlID ;
			nChannels = mCMixer.GetControlChannelCount( mCtrlID ) ;
			nSize = sizeof(stateData) ;
			mCMixer.GetDestControlState( 0, n1, &stateData, &nSize ) ;
			InitVolSlider( mixerControl, nChannels, &stateData ) ;
			break ;
		}
	}
	mpVolCtrl->ShowWindow( SW_SHOW ) ;

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// -----------------------------------------------------------------------------
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

// -----------------------------------------------------------------------------
// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.
void CVolumeControlDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

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

// -----------------------------------------------------------------------------
// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CVolumeControlDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// -----------------------------------------------------------------------------
// Vol control specific functions
// -----------------------------------------------------------------------------
int CVolumeControlDlg::InitVolSlider(MIXERCONTROL mixerControl, int nChannels, 
									 sStateData* state)
{
	mnRangeMax = mixerControl.Bounds.dwMaximum ;
	mnRangeMin = mixerControl.Bounds.dwMinimum ; 
	mnDelta = mnRangeMax - mnRangeMin ;
	DWORD dwMaxVol ;
	int thumbPos ;
	int n1 ;

	mnVolStep = mnDelta / mixerControl.Metrics.cSteps ;	// Volume change step size
	mpVolCtrl->SetRangeMin( 0, FALSE ) ;		// Slider minimum is zero	
	mpVolCtrl->SetRangeMax( mnDelta, TRUE  ); 	// Slider maximum is mnDelta

	for( n1=0 ; n1<6 ; n1++ )		// 7 Tics
	{
		thumbPos = (n1*mnDelta)/6 ;
		mpVolCtrl->SetTic( thumbPos ) ;
	}

	// Save state data
	memcpy( (void*)&mStateData, (void*)state, sizeof(sStateData) ) ;
	mBalLeft  = mStateData.Left.dwValue  < 1 ? 1 : mStateData.Left.dwValue ; 
	mBalRight = mStateData.Right.dwValue < 1 ? 1 : mStateData.Right.dwValue ;
	dwMaxVol = ( mBalLeft < mBalRight ) ? mBalRight : mBalLeft ;	// Get max volume

	mpVolCtrl->SetPos( mnDelta - dwMaxVol ) ;

	return 1 ;
}

// -----------------------------------------------------------------------------
// Get the current slider position in terms of the volume range. Assumes that if  
// the channels are in balance, both L and R vol values are the same and equal 
// to the volume range, mnDelta. 
// -----------------------------------------------------------------------------
int CVolumeControlDlg::GetCurrentPos( DWORD* vol, DWORD* range )
{
	*vol = mnDelta - mpVolCtrl->GetPos() ;
	*range = mnDelta ;

	return *vol ;
}

// -----------------------------------------------------------------------------
int CVolumeControlDlg::SetCurrentPos( unsigned int volLeft, unsigned int volRight )
{
	int maxVol = ( volLeft < volRight ) ? volRight : volLeft ;	// Get max volume
	mpVolCtrl->SetPos( mnDelta - maxVol ) ; 

	return maxVol ;
}

// -----------------------------------------------------------------------------
//
// Event message handler for the Mixer generated control change message.
//
// There will be one message for each open mixer assuming the CALLBACK_WINDOW 
// option was set in the mixerOpen call. For example, if there are three mixers 
// opened this way, there will be three messages received, regardless of which 
// mixer control changed. It is not possible to directly determine which mixer 
// generated the message, but the (LPARAM) dwControlID value will be correct. 
// If necessary, each mixer.dwControlID can be checked for a changed state to 
// determine which mixer generated the control change message. 
// -----------------------------------------------------------------------------
long CVolumeControlDlg::OnMixerControlChange( WPARAM wParam, LPARAM lParam )
{
	unsigned long balThreshold = mnVolStep ;
	unsigned int nSize ;
	sStateData state ;
	int nRet = 0 ;

	// Just return if its not our mixer volume control.
	if( mCtrlID != lParam )
		return 0 ;

	// Get control state for the passed mixer ID
	nSize = sizeof(sStateData) ;
	nRet = mCMixer.GetControlState( (DWORD)lParam, &state, &nSize ) ;
	if( nRet < 0 )
		return 0 ;

	// Only save balance state when above the state tracking threshold
	if( state.Left.dwValue > balThreshold ||  state.Right.dwValue > balThreshold )
	{
		mBalLeft  = state.Left.dwValue ;	
		mBalRight = state.Right.dwValue ;	
	}

	// Move the slider thumb 
	SetCurrentPos( state.Left.dwValue, state.Right.dwValue ) ;

	return 0 ;
}

// -----------------------------------------------------------------------------
// Vertical slider and scroll bar message handler. 
void CVolumeControlDlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	sStateData state ;
	unsigned long nVol, nRange ;
	unsigned int nSize = sizeof(sStateData) ;

	// Get ID of the vertical slider control that sent the message
	int nCtrlID = pScrollBar->GetDlgCtrlID() ;

	if( nCtrlID != 0 )	// A zero ID is for the dialog window vertical scroll bar
	{
		// Get windows volume control state info
		GetCurrentPos( &nVol, &nRange );

		// Adjust the volume of each channel according to the volume control position
		if( mBalLeft > mBalRight )
		{
			state.Left.dwValue  = nVol ;
			state.Right.dwValue = (nVol * mBalRight) / mBalLeft  ;
		}
		else
		{
			state.Right.dwValue  = nVol ;
			state.Left.dwValue =  (nVol * mBalLeft) / mBalRight  ;
		}

		// Set mixer control state														   
		mCMixer.SetControlState( mCtrlID, &state, &nSize ) ;	
	}

	CDialog::OnVScroll(nSBCode, nPos, pScrollBar);
}

// -----------------------------------------------------------------------------
