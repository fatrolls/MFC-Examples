#include "stdafx.h"
#include "DirectSoundTest.h"
#include "DirectSoundTestDlg.h"
#include <dsound.h>
#include "WaveFile.h"
#include "MyDirectSound.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//<CALLBACK Function>
void CALLBACK TimerProc(UINT uTimerID, UINT uMsg, DWORD dwUser, DWORD dw1, DWORD dw2)
{
	CDirectSoundTestDlg *pDlg = (CDirectSoundTestDlg *)dwUser;
	pDlg->TimerCallback();	
}
//</TimerProc>

HRESULT CALLBACK GetSamples(LPBYTE lpDesBuf, const DWORD dwRequiredSamples, DWORD &dwRetSamples, LPVOID lpData)
{
	CDirectSoundTestDlg *pDlg = (CDirectSoundTestDlg *)lpData;
	pDlg->GetAudioSamples(lpDesBuf, dwRequiredSamples, dwRetSamples);
	return 0;
}
//</GetSamples>
//</CALLBACK Function>

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
// CDirectSoundTestDlg dialog

CDirectSoundTestDlg::CDirectSoundTestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDirectSoundTestDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	
	m_pWavFile = new CWaveFile;
	m_pMyDS = NULL;
	m_iBeginPlayPos = 0;
}

void CDirectSoundTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDirectSoundTestDlg)
	DDX_Control(pDX, IDC_SLIDER, m_ctrlPlaySlider);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDirectSoundTestDlg, CDialog)
	//{{AFX_MSG_MAP(CDirectSoundTestDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_OPEN, OnOpen)
	ON_BN_CLICKED(IDC_BTN_PLAY, OnPlay)
	ON_BN_CLICKED(IDC_BTN_PAUSE, OnPause)
	ON_BN_CLICKED(IDC_BTN_STOP, OnStop)
	ON_WM_HSCROLL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDirectSoundTestDlg message handlers

BOOL CDirectSoundTestDlg::OnInitDialog()
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
	m_ctrlPlaySlider.SetPageSize(2000);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CDirectSoundTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CDirectSoundTestDlg::OnPaint() 
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
HCURSOR CDirectSoundTestDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CDirectSoundTestDlg::OnOpen() 
{
	//Open a wave file
	CFileDialog dlgOpen(TRUE,
						_T("wav"),
						NULL,
						OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
						_T("(*.wav)|*.wav||")
						);
	if (IDCANCEL == dlgOpen.DoModal()) {
		return;
	}

	OnStop();

	m_strFileName = dlgOpen.GetPathName();
	GetDlgItem(IDC_EDIT_OPEN)->SetWindowText(m_strFileName);

	//Get the wav file information
	WAVEFORMATEX formatWav;
	m_pWavFile->Open((LPTSTR)(LPCTSTR)m_strFileName, &formatWav, WAVEFILE_READ);
	formatWav = *m_pWavFile->GetFormat();

	//Set the total progress
	DWORD dwTotalSamples = m_pWavFile->GetSize()/formatWav.nBlockAlign;
	m_ctrlPlaySlider.SetRange(0, dwTotalSamples);
	m_ctrlPlaySlider.SetPos(0);

	//Initilize CMyDirectSound
	if (NULL == m_pMyDS) {
		m_pMyDS = new CMyDirectSound;
	}
	m_pMyDS->SetFormat(formatWav);
	m_pMyDS->SetCallback(GetSamples, this);	
}
//</OnOpen>

void CDirectSoundTestDlg::OnOK() 
{
	OnStop();

	if(NULL != 	m_pWavFile)
	{		
		delete m_pWavFile;
		m_pWavFile = NULL;
	}

	if (NULL != m_pMyDS) {
		delete m_pMyDS;
		m_pMyDS = NULL;
	}

	CDialog::OnOK();
}
//</OnOK>

void CDirectSoundTestDlg::OnPlay() 
{
	if (NULL != m_pMyDS) {

		if (0 == m_ctrlPlaySlider.GetPos()) {
			
			m_pWavFile->ResetFile();
		}
		
		m_pMyDS->Play();
		m_timerID = timeSetEvent(500, 100, TimerProc, (DWORD)this, TIME_PERIODIC | TIME_CALLBACK_FUNCTION);
	}
}
//</OnPlay>

HRESULT CDirectSoundTestDlg::GetAudioSamples(LPBYTE lpDesBuf, const DWORD dwRequiredSamples, DWORD &dwRetSamples)
{
	DWORD dwRequiredBytes = 0, dwRetBytes = 0;
	WAVEFORMATEX *pWFE = m_pWavFile->GetFormat();
	dwRequiredBytes = dwRequiredSamples*pWFE->nBlockAlign;
	m_pWavFile->Read(lpDesBuf, dwRequiredBytes, &dwRetBytes);
	dwRetSamples = dwRetBytes/pWFE->nBlockAlign;
	return dwRetBytes;
}
//</GetAudioSamples>

void CDirectSoundTestDlg::OnPause() 
{
	if (NULL != m_pMyDS) {
		m_pMyDS->Pause();		
		timeKillEvent(m_timerID);
		m_timerID = 0;
	}
}
//</OnPause>

void CDirectSoundTestDlg::OnStop() 
{
	if (NULL != m_pMyDS) {
		
		m_pMyDS->Stop();
		timeKillEvent(m_timerID);
		m_timerID = 0;		
	}
	m_ctrlPlaySlider.SetPos(0);
	m_iBeginPlayPos = 0;
}
//</OnStop>

void CDirectSoundTestDlg::TimerCallback()
{
	DWORD dwSamplesPlayed = m_pMyDS->GetSamplesPlayed();
	m_ctrlPlaySlider.SetPos(dwSamplesPlayed+m_iBeginPlayPos);
	if (m_ctrlPlaySlider.GetRangeMax() < (int)(dwSamplesPlayed+m_iBeginPlayPos)) {
		
		OnStop();
	}
}
//</TimerCallback>

void CDirectSoundTestDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	m_iBeginPlayPos = m_ctrlPlaySlider.GetPos();
	if (NULL != m_pMyDS) {
	
		m_pWavFile->SetBeginSamples(m_iBeginPlayPos);
	}	
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}
//</OnHScroll>