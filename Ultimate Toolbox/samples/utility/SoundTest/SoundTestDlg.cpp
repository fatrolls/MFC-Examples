// SoundTestDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SoundTest.h"
#include "SoundTestDlg.h"
#include "OXSound.h"

#include "utsampleabout.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSoundTestDlg dialog

CSoundTestDlg::CSoundTestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSoundTestDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSoundTestDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSoundTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSoundTestDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSoundTestDlg, CDialog)
	//{{AFX_MSG_MAP(CSoundTestDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_OPEN, OnOpen)
	ON_BN_CLICKED(IDC_PLAY, OnPlay)
	ON_BN_CLICKED(IDC_STOP, OnStop)
	ON_BN_CLICKED(IDC_ASYNC, OnAsync)
	ON_MESSAGE(WM_OX_SOUNDPLAYBACKCOMPLETE, OnPlayComplete)
	ON_MESSAGE(WM_OX_SOUNDPLAYLOOPING, OnPlayLoop)
	ON_BN_CLICKED(IDC_RADIO1, OnRadio1)
	ON_BN_CLICKED(IDC_RADIO2, OnRadio2)
	ON_BN_CLICKED(IDC_RADIO3, OnRadio3)
	ON_BN_CLICKED(IDC_INFO, OnInfo)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSoundTestDlg message handlers

BOOL CSoundTestDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	m_oxSound.SetCallbackWnd(this) ;

	// Can this machine playback waves?
	if (!m_oxSound.CanPlay())
	{
		AfxMessageBox(_T("A waveout device does not exist for sound playback")) ;

		GetDlgItem(IDC_RADIO1)->EnableWindow(FALSE) ;
		GetDlgItem(IDC_RADIO2)->EnableWindow(FALSE) ;
		GetDlgItem(IDC_RADIO3)->EnableWindow(FALSE) ;
		GetDlgItem(IDC_OPEN)->EnableWindow(FALSE) ;
		GetDlgItem(IDC_PLAY)->EnableWindow(FALSE) ;
		GetDlgItem(IDC_ASYNC)->EnableWindow(FALSE) ;
		GetDlgItem(IDC_LOOP)->EnableWindow(FALSE) ;
		GetDlgItem(IDC_LOOPCOUNT)->EnableWindow(FALSE) ;
		GetDlgItem(IDC_STOP)->EnableWindow(FALSE) ;
		GetDlgItem(IDC_INFO)->EnableWindow(FALSE) ;
	}

	CheckRadioButton(IDC_RADIO1, IDC_RADIO3, IDC_RADIO1) ;

	ShowStatus(NULL) ;

	COXSound* pSound=new COXSound;
	delete pSound;
	pSound=NULL;

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CSoundTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CSoundTestDlg::OnPaint() 
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
HCURSOR CSoundTestDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CSoundTestDlg::OnOpen() 
{
	static TCHAR BASED_CODE szFilter[] = _T("Wave Files (*.wav)||");
  	CFileDialog	theDlg(TRUE, _T("*.wav"), _T("*.wav"), OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, this) ;
	CString	sFilename ;
	CString	buffer ;

	ShowStatus(_T("Opening WAVE file...")) ;

	if (theDlg.DoModal())
	{
		sFilename = theDlg.GetPathName() ;
		SetDlgItemText(IDC_FILENAME, sFilename) ;

		if (m_oxSound.Open(sFilename))
		{
			// Enable the play button
			GetDlgItem(IDC_PLAY)->EnableWindow(TRUE) ;
			buffer.Format(_T("File: %s opened successfully"), sFilename) ;
			ShowStatus(buffer) ;
		}
		else
		{
			buffer.Format(_T("Could not open %s"), sFilename) ;
			ShowStatus(buffer) ;
		}
	}
}

void CSoundTestDlg::OnPlay() 
{
	BOOL	bLoop = IsDlgButtonChecked(IDC_LOOP) ;
	BOOL	bAsync = IsDlgButtonChecked(IDC_ASYNC) ;

	CWaitCursor	theCursor ;

	GetDlgItem(IDC_STOP)->EnableWindow(bAsync) ;
	GetDlgItem(IDC_PLAY)->EnableWindow(FALSE) ;

	CString	buffer ;

	buffer = _T("Playing WAVE ") ;

	if (bAsync)
		buffer += "a" ;
	
	buffer += _T("synchronously...") ;

	ShowStatus(buffer) ;

	SetDlgItemInt(IDC_LOOPCOUNT, bLoop) ;

	m_oxSound.Play(bLoop, bAsync) ;

	if (!bAsync)
		ShowStatus(_T("Wave playback complete...")) ;

	GetDlgItem(IDC_PLAY)->EnableWindow(!bAsync) ;
}

void CSoundTestDlg::OnStop() 
{
	// Stop the current sound from playing...
	m_oxSound.Stop() ;

	ShowStatus(_T("WAVE stopped playing...")) ;

	GetDlgItem(IDC_PLAY)->EnableWindow(TRUE) ;
	GetDlgItem(IDC_STOP)->EnableWindow(FALSE) ;
}

void CSoundTestDlg::OnAsync() 
{
	if (!IsDlgButtonChecked(IDC_ASYNC))
	{
		CheckDlgButton(IDC_LOOP, FALSE) ;
	}

	GetDlgItem(IDC_LOOP)->EnableWindow(IsDlgButtonChecked(IDC_ASYNC)) ;
	GetDlgItem(IDC_LOOPCOUNT)->EnableWindow(IsDlgButtonChecked(IDC_ASYNC)) ;

}


LRESULT CSoundTestDlg::OnPlayComplete(WPARAM /* wParam */, LPARAM /* lParam */)
{
	// Notification message to let us know the sound has completed playback...

	OnStop() ;

	return (0) ;
}

LRESULT CSoundTestDlg::OnPlayLoop(WPARAM /* wParam */, LPARAM /* lParam */)
{
	// Notification message to let us know the sound is looping...

	int iCount = (int) GetDlgItemInt(IDC_LOOPCOUNT) ;
	iCount++ ;
	SetDlgItemInt(IDC_LOOPCOUNT, iCount) ;

	return (0) ;
}

void CSoundTestDlg::OnRadio1() 
{
	// Loaded from file...
	GetDlgItem(IDC_OPEN)->EnableWindow(TRUE) ;
}

void CSoundTestDlg::OnRadio2() 
{
	// Load from IDW_GUITAR resource...

	if (m_oxSound.Open(IDW_GUITAR, AfxGetResourceHandle()))
	{
		// Enable the play button
		GetDlgItem(IDC_PLAY)->EnableWindow(TRUE) ;
	}

	GetDlgItem(IDC_OPEN)->EnableWindow(FALSE) ;
}

void CSoundTestDlg::OnRadio3() 
{
	// Load from IDW_PHOTON resource...

	if (m_oxSound.Open(IDW_PHOTON, AfxGetResourceHandle()))
	{
		// Enable the play button
		GetDlgItem(IDC_PLAY)->EnableWindow(TRUE) ;
	}

	GetDlgItem(IDC_OPEN)->EnableWindow(FALSE) ;	
}

void CSoundTestDlg::ShowStatus(LPCTSTR pStatus)
{
	SetDlgItemText(IDC_STATUS, pStatus) ;
}

void CSoundTestDlg::OnInfo() 
{
	WAVEFORMATEX	wfx ;
	CString			buffer ;

	if (m_oxSound.IsWaveLoaded())
	{
		m_oxSound.GetWaveFormat(&wfx) ;

		buffer.Format(_T("nChannels = %d\nnSamplesPerSec = %u\nwBitsPerSample=%u"), wfx.nChannels, wfx.nSamplesPerSec, wfx.wBitsPerSample) ;
		MessageBox(buffer) ;
	}
}


