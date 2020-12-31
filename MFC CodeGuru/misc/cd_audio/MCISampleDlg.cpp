// MCISampleDlg.cpp : implementation file
//
#include "stdafx.h"
#include "MCISample.h"
#include "MCISampleDlg.h"
#include "PlaySectionDlg.h"
#include "hyperlink.h"

#include <dbt.h>

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
	CHyperLink	m_mailLink;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	virtual BOOL OnInitDialog();
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
	DDX_Control(pDX, IDC_MAIL_LINK, m_mailLink);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CAboutDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_mailLink.SetURL(_T("mailto:giancarlo@saria.com"));
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

/////////////////////////////////////////////////////////////////////////////
// CMCISampleDlg dialog

CMCISampleDlg::CMCISampleDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMCISampleDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMCISampleDlg)
	m_strTrack = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMCISampleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMCISampleDlg)
	DDX_Control(pDX, IDC_EJECT, m_btnEject);
	DDX_Control(pDX, IDC_PLAY_SECTION, m_btnPlaySection);
	DDX_Control(pDX, IDC_PLAY, m_btnPlay);
	DDX_Control(pDX, IDC_STOP, m_btnStop);
	DDX_Control(pDX, IDC_PAUSE, m_btnPause);
	DDX_Control(pDX, IDC_STATUS, m_wndStatus);
	DDX_Control(pDX, IDC_TRACKSELECT, m_comboTrack);
	DDX_CBString(pDX, IDC_TRACKSELECT, m_strTrack);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMCISampleDlg, CDialog)
	//{{AFX_MSG_MAP(CMCISampleDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_PLAY, OnPlay)
	ON_BN_CLICKED(IDC_STOP, OnStop)
	ON_CBN_SELCHANGE(IDC_TRACKSELECT, OnSelchangeTrackselect)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_PAUSE, OnPause)
	ON_BN_CLICKED(IDC_EJECT, OnEject)	
	ON_BN_CLICKED(IDC_PLAY_SECTION, OnPlaySection)
	//}}AFX_MSG_MAP
	ON_WM_DEVICECHANGE()
	ON_MESSAGE(MM_MCINOTIFY, OnMciNotify)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMCISampleDlg message handlers

BOOL CMCISampleDlg::OnInitDialog()
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

	// Set MCI error report mode
	//m_CdAudio.ReportErrors(TRUE);

	// Disable the Stop/Pause buttons
	m_btnStop.EnableWindow(FALSE);
	m_btnPause.EnableWindow(FALSE);
	
	// Open the CD audio  device
	if (m_CdAudio.Open()) {		
		m_wndStatus.SetWindowText(_T("Device not ready!"));				
		m_btnPlay.EnableWindow(FALSE);
		m_btnPlaySection.EnableWindow(FALSE);
		m_btnEject.EnableWindow(FALSE);
	}
	else {
		// Set the callback window for asynchronous operations
		m_CdAudio.SetCallbackWnd(this);
		m_wndStatus.SetWindowText(_T("Simple CD player ready"));
	}
	
	if (!m_CdAudio.IsReady()) {
		m_btnPlay.EnableWindow(FALSE);
		m_btnPlaySection.EnableWindow(FALSE);
	}

	// Set time format for CD audio
	m_CdAudio.SetTimeFormat(CCdAudio::FormatTMSF);

	// Update dialog controls
	UpdateControls();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMCISampleDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMCISampleDlg::OnPaint() 
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
HCURSOR CMCISampleDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CMCISampleDlg::OnPlay() 
{
	UpdateData();
	// Convert track to number
	m_nTrackToPlay = 
		(m_strTrack.GetAt(0)-'0')*10 + 
		(m_strTrack.GetAt(1)-'0');

	// Get track lenght
	CMsf msf = m_CdAudio.GetTrackLength(m_nTrackToPlay);
	
	m_tmsfFrom = CTmsf(m_nTrackToPlay, 0, 0, 0);
	m_tmsfTo = CTmsf(m_nTrackToPlay, 
		msf.GetMinute(), msf.GetSecond(), msf.GetFrame());
		
	// Play selected track
	if (!m_CdAudio.Play(m_tmsfFrom, m_tmsfTo)) {
		m_wndStatus.SetWindowText(_T("Playing..."));		
		m_btnStop.EnableWindow();
		m_btnPause.EnableWindow();
	}

}

void CMCISampleDlg::OnPlaySection() 
{
	CPlaySectionDlg dlg;

	if (dlg.DoModal() == IDOK) {
			// Convert track to number
		m_nTrackToPlay = 
			(m_strTrack.GetAt(0)-'0')*10 + 
			(m_strTrack.GetAt(1)-'0');

		m_tmsfFrom = CTmsf(m_nTrackToPlay, 
			dlg.m_nMinuteFrom, dlg.m_nSecondFrom, dlg.m_nFrameFrom);
		m_tmsfTo = CTmsf(m_nTrackToPlay, 
			dlg.m_nMinuteTo, dlg.m_nSecondTo, dlg.m_nFrameTo);
		
		if (!m_CdAudio.Play(m_tmsfFrom, m_tmsfTo)) {
			m_wndStatus.SetWindowText(_T("Playing..."));		
			m_btnStop.EnableWindow();
			m_btnPause.EnableWindow();
		}
	}
}

void CMCISampleDlg::OnStop() 
{
	if (!m_CdAudio.Stop()) {
		m_wndStatus.SetWindowText(_T("Stopped"));
		m_btnStop.EnableWindow(FALSE);
		m_btnPause.EnableWindow(FALSE);
		m_btnPause.SetWindowText(_T("&Pause"));
	}
}

void CMCISampleDlg::OnSelchangeTrackselect() 
{
	UpdateData();	
	// Convert track to number
	m_nTrackToPlay = 
		(m_strTrack.GetAt(0)-'0')*10 + 
		(m_strTrack.GetAt(1)-'0');
	// Seek to the selected track
	if (m_nTrackToPlay > 0)
		m_CdAudio.Seek(CTmsf(m_nTrackToPlay, 0, 0, 0));
}

void CMCISampleDlg::OnClose() 
{
	// Show the About dialog
	CAboutDlg dlg;
	dlg.DoModal();

	// Stop and close the CD-Audio
	if (m_CdAudio.IsReady()) {
		m_CdAudio.Stop();	
		m_CdAudio.Close();
	}
	
	CDialog::OnClose();
}

void CMCISampleDlg::OnPause() 
{
	if (m_CdAudio.GetMode() == CCdAudio::ModePlay) {
		// Pause playback
		if (!m_CdAudio.Pause()) {
			m_wndStatus.SetWindowText(_T("Paused"));
			m_btnPause.SetWindowText(_T("&Resume"));
		}	
	}
	else {
		// Resume playback from current position
		if (!m_CdAudio.Play(m_CdAudio.GetCurrentPos(), m_tmsfTo))
			m_btnPause.SetWindowText(_T("&Pause"));
			m_wndStatus.SetWindowText(_T("Playing..."));				
	}
}

void CMCISampleDlg::OnEject() 
{
	// Open/Close the CD door. IsReady() returns FALSE if the
	// CD door is open
	m_CdAudio.OpenDoor(m_CdAudio.IsReady());
	m_btnPause.SetWindowText(_T("&Pause"));
	BOOL bReady = m_CdAudio.IsReady();
	EnableControls(bReady, bReady);
}

// Intercept a new CD-Audio insertion
BOOL CMCISampleDlg::OnDeviceChange( UINT nEventType, DWORD dwData ) {
	DEV_BROADCAST_HDR *pdbch = (DEV_BROADCAST_HDR *) dwData;

	switch(nEventType) {
	case DBT_DEVICEARRIVAL:						// CD drawer was closed
		if (pdbch->dbch_devicetype == DBT_DEVTYP_VOLUME) {
			PDEV_BROADCAST_VOLUME pdbcv = 
				(PDEV_BROADCAST_VOLUME) dwData;
			if (pdbcv->dbcv_flags == DBTF_MEDIA)
			{
				TCHAR szDrive[4];
				// pdbcv->unitmask contains the drive bits
				for (UINT i=0; !(pdbcv->dbcv_unitmask & (1<<i)); i++);
				wsprintf(szDrive, _T("%c:\\"), 'A'+i);		
				if (GetDriveType(szDrive) == DRIVE_CDROM) {					
					UpdateControls();					
				}
			}
			else {
				// It is a network drive
			}
			break;
		}
	case DBT_DEVICEREMOVECOMPLETE:				// CD drawer was open
		EnableControls(FALSE, FALSE);
	break;
	}

	return TRUE;
}

void CMCISampleDlg::EnableControls(BOOL bEnablePlay, 
								   BOOL bEnableStop /* =TRUE*/) 
{
	m_comboTrack.EnableWindow(bEnablePlay);	
	m_btnPlay.EnableWindow(bEnablePlay);
	m_btnPlaySection.EnableWindow(bEnablePlay);
	m_btnStop.EnableWindow(bEnableStop);
	m_btnPause.EnableWindow(bEnableStop);
}

// Update the dialog controls
void CMCISampleDlg::UpdateControls() {
	// Get the number of playable tracks on the CD
	DWORD n = m_CdAudio.GetNumberOfTracks();

	m_comboTrack.ResetContent();
	CString s;
	CMsf msf;
	// Update the trackselect combobox
	for (UINT i=1; i<=n; i++) {
		msf = m_CdAudio.GetTrackLength(i);
		if (m_CdAudio.GetTrackType(i) == CCdAudio::TrackTypeAudio) {
			s.Format(_T("%02d    (%02d\':%02d\")"), i, 
				msf.GetMinute(), msf.GetSecond());
			m_comboTrack.AddString(s);
		}

	}
	// Select first track
	m_comboTrack.SetCurSel(0);
	// if no playable track, disable Playback buttons
	BOOL bCanPlay = m_comboTrack.GetCount() != 0;
	
	EnableControls(bCanPlay, FALSE);
	UpdateData();	
}

LONG CMCISampleDlg::OnMciNotify(UINT wFlags, LONG lDevId) {	
	switch(wFlags) {
	case MCI_NOTIFY_SUCCESSFUL:
		m_wndStatus.SetWindowText(_T("Playback completed"));
		break;
	case MCI_NOTIFY_FAILURE:
		m_wndStatus.SetWindowText(_T("Playback interrupted!"));
		break;
	case MCI_NOTIFY_SUPERSEDED:
		m_wndStatus.SetWindowText(_T("Playback stopped!"));
		break;
	}	
	return 0L;
}

