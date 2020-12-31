// waveInFFTDlg.cpp : implementation file
//

#include "stdafx.h"
#include "waveInFFT.h"
#include "waveInFFTDlg.h"
#include "fourier.h"
#include <math.h>
#include ".\waveinfftdlg.h"

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
// CWaveInFFTDlg dialog

CWaveInFFTDlg::CWaveInFFTDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWaveInFFTDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CWaveInFFTDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CWaveInFFTDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWaveInFFTDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CWaveInFFTDlg, CDialog)
	//{{AFX_MSG_MAP(CWaveInFFTDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_EQ_MODE, OnEqMode)
	ON_BN_CLICKED(IDC_MICRO_EQ, OnMicroEq)
	ON_BN_CLICKED(IDC_OSCILLOSCOPE, OnOscilloscope)
	ON_BN_CLICKED(IDC_PEAK, OnPeak)
	ON_BN_CLICKED(IDC_PEAK_ALT, OnPeakAlt)
	ON_BN_CLICKED(IDC_PIXELGRAM, OnPixelgram)
	ON_BN_CLICKED(IDC_SPECTRUM, OnSpectrum)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWaveInFFTDlg message handlers
inline double GetFrequencyIntensity(double re, double im)
{
	return sqrt((re*re)+(im*im));
}
#define mag_sqrd(re,im) (re*re+im*im)
#define Decibels(re,im) ((re == 0 && im == 0) ? (0) : 10.0 * log10(double(mag_sqrd(re,im))))
#define Amplitude(re,im,len) (GetFrequencyIntensity(re,im)/(len))
#define AmplitudeScaled(re,im,len,scale) ((int)Amplitude(re,im,len)%scale)
BOOL Process(void* lpData, LPWAVEHDR pwh)
{
#define FFT_LEN 2048
	double finleft[FFT_LEN/2],finright[FFT_LEN/2],fout[FFT_LEN],foutimg[FFT_LEN],fdraw[FFT_LEN/2];
	DWORD nCount = 0;
	for (DWORD dw = 0; dw < FFT_LEN; dw++)
	{
		{
			//copy audio signal to fft real component for left channel
			finleft[nCount] = (double)((short*)pwh->lpData)[dw++];
			//copy audio signal to fft real component for right channel
			finright[nCount++] = (double)((short*)pwh->lpData)[dw];
		}
	}
	//Perform FFT on left channel
	fft_double(FFT_LEN/2,0,finleft,NULL,fout,foutimg);
	float re,im,fmax=-99999.9f,fmin=99999.9f;
	for(int i=1;i < FFT_LEN/4;i++)//Use FFT_LEN/4 since the data is mirrored within the array.
	{
		re = (float)fout[i];
		im = (float)foutimg[i];
		//get amplitude and scale to 0..256 range
		//fdraw[i]=AmplitudeScaled(re,im,FFT_LEN/2,256);
		fdraw[i] = ((int)mag_sqrd(re,im))%256;
		if (fdraw[i] > fmax)
		{
			fmax = (float)fdraw[i];
		}
		if (fdraw[i] < fmin)
		{
			fmin = (float)fdraw[i];
		}
	}
	//Use this to send the average band amplitude to something
	int nAvg, nBars=16, nCur = 0;
	for(int i=1;i < FFT_LEN/4;i++)
	{
		nAvg = 0;
		for (int n=0; n < nBars; n++)
		{
			nAvg += (int)fdraw[i];
		}
		nAvg /= nBars;
		//Send data here to something,
		//nothing to send it to so we print it.
		TRACE("Average for Bar#%d is %d\n",nCur++,nAvg);
		i+=nBars-1;
	}
	DataHolder* pDataHolder = (DataHolder*)lpData;
	// Draw left channel
	CFrequencyGraph* pPeak = (CFrequencyGraph*)pDataHolder->pData;
	if (::IsWindow(pPeak->GetSafeHwnd()))
	{
		pPeak->SetYRange(0,256);
		pPeak->Update(FFT_LEN/4,fdraw);
	}
	
	// Perform FFT on right channel
	fmax=-99999.9f,fmin=99999.9f;
	fft_double(FFT_LEN/2,0,finright,NULL,fout,foutimg);
	fdraw[0] = fdraw[FFT_LEN/4] = 0;
	for(int i=1;i < FFT_LEN/4;i++)//Use FFT_LEN/4 since the data is mirrored within the array.
	{
		re = (float)fout[i];
		im = (float)foutimg[i];
		//get Decibels in 0-110 range
		fdraw[i] = Decibels(re,im);
		if (fdraw[i] > fmax)
		{
			fmax = (float)fdraw[i];
		}
		if (fdraw[i] < fmin)
		{
			fmin = (float)fdraw[i];
		}
	}
	//Draw right channel
	CFrequencyGraph* pPeak2 = (CFrequencyGraph*)pDataHolder->pData2;
	if (::IsWindow(pPeak2->GetSafeHwnd()))
	{
		pPeak2->SetNumberOfSteps(FFT_LEN/64);
		//pPeak2->SetLogScale(TRUE);
		pPeak2->SetYRange((int)0,(int)110);//Use updated dynamic range for scaling
		pPeak2->Update(FFT_LEN/4,fdraw);
	}
	return TRUE;
}

BOOL CWaveInFFTDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	CRect rct(0,20,375,150);
	m_graph.Create("STATIC","",WS_VISIBLE|WS_CHILD,rct,this,1001);
	rct = CRect(0,175,375,325);
	m_graph2.Create("STATIC","",WS_VISIBLE|WS_CHILD,rct,this,1002);
	m_data.pData = &m_graph;
	m_data.pData2 = &m_graph2;
	m_rec.Open();
	m_rec.SetBufferFunction((void*)&m_data,Process);
	m_rec.Start();
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
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CWaveInFFTDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CWaveInFFTDlg::OnPaint() 
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
HCURSOR CWaveInFFTDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CWaveInFFTDlg::OnEqMode() 
{
	// TODO: Add your control notification handler code here
	m_graph.SetGraphType(FG_EQ_CHANNEL);
	m_graph2.SetGraphType(FG_EQ_CHANNEL);
}

void CWaveInFFTDlg::OnMicroEq() 
{
	// TODO: Add your control notification handler code here
	m_graph.SetGraphType(FG_MICRO_EQ);
	m_graph2.SetGraphType(FG_MICRO_EQ);
}

void CWaveInFFTDlg::OnOscilloscope() 
{
	// TODO: Add your control notification handler code here
	m_graph.SetGraphType(FG_OSCILLOSCOPE);
	m_graph2.SetGraphType(FG_OSCILLOSCOPE);
}

void CWaveInFFTDlg::OnPeak() 
{
	// TODO: Add your control notification handler code here
	m_graph.SetGraphType(FG_PEAK);
	m_graph2.SetGraphType(FG_PEAK);
}

void CWaveInFFTDlg::OnPeakAlt() 
{
	// TODO: Add your control notification handler code here
	m_graph.SetGraphType(FG_PEAK2);
	m_graph2.SetGraphType(FG_PEAK2);
}

void CWaveInFFTDlg::OnPixelgram() 
{
	// TODO: Add your control notification handler code here
	m_graph.SetGraphType(FG_PIXELGRAM);
	m_graph2.SetGraphType(FG_PIXELGRAM);
}

void CWaveInFFTDlg::OnSpectrum() 
{
	// TODO: Add your control notification handler code here
	m_graph.SetGraphType(FG_SPECTRUM);
	m_graph2.SetGraphType(FG_SPECTRUM);
}

BOOL CWaveInFFTDlg::DestroyWindow()
{
	// TODO: Add your specialized code here and/or call the base class
	m_rec.Stop();
	m_rec.SetBufferFunction((void*)&m_data,NULL);
	return CDialog::DestroyWindow();
}
