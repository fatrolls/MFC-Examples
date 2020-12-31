// SoundStudioDlg.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include <assert.h>
#include <strsafe.h>
#include "FFT.hpp"
#include "SoundStudioDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


using namespace std;
using namespace Ernzo::DSP;

const UINT WM_AUDIO_DONE = WM_USER+0x100;

//const int METER_FREQUENCY[] = { 30, 60, 80, 90, 100, 150, 200, 330, 480, 660, 880, 1000, 1500, 2000, 3000, 5000, 8000, 12000, 16000 };
const int METER_FREQUENCY[] = { 30, 60, 100, 160, 240, 300, 350, 400, 440, 500, 600, 800, 1000, 1500, 2000, 2600, 3000, 4000, 6000, 8000, 10000, 14000, 16000 };
const int NUM_FREQUENCY = sizeof(METER_FREQUENCY)/sizeof(int);
const double FFT_SPEED = 0.06;

// CAboutDlg dialog used for App About

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

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CSoundStudioDlg dialog


CSoundStudioDlg::CSoundStudioDlg(CWnd* pParent /*=NULL*/)
    : CDialog(CSoundStudioDlg::IDD, pParent)
{
    m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
    m_pWaveBuffer = NULL;
    m_dwMuteControlID = 0;
    m_dwVolumeControlID = 0;
}

void CSoundStudioDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_CTL_METER1, m_PeakMeter1);
}

BEGIN_MESSAGE_MAP(CSoundStudioDlg, CDialog)
    ON_WM_SYSCOMMAND()
    ON_WM_PAINT()
    ON_WM_QUERYDRAGICON()
    //}}AFX_MSG_MAP
    ON_BN_CLICKED(IDC_BTN_OPEN, &CSoundStudioDlg::OnBnClickedBtnOpen)
    ON_BN_CLICKED(IDC_BTN_PLAY, &CSoundStudioDlg::OnBnClickedBtnPlay)
    ON_BN_CLICKED(IDC_BTN_PLAYSTOP, &CSoundStudioDlg::OnBnClickedBtnPlaystop)
    ON_BN_CLICKED(IDC_BTN_MUTE, &CSoundStudioDlg::OnBnClickedBtnMute)
    ON_WM_DESTROY()
    ON_MESSAGE(WM_AUDIO_DONE, &CSoundStudioDlg::OnAudioDataDone)
    ON_MESSAGE(MM_MIXM_CONTROL_CHANGE, &CSoundStudioDlg::OnMixerControlChange )
    ON_WM_HSCROLL()
END_MESSAGE_MAP()


// CSoundStudioDlg message handlers
BOOL CSoundStudioDlg::PreTranslateMessage(MSG* pMsg)
{
    if ( pMsg->message == WM_KEYDOWN )
    {
        if ( pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE )
        {
            if ( pMsg->wParam == VK_RETURN )
            {
                TCHAR szClassName[40] = { 0 };
                CWnd* pWnd = GetFocus();
                if ( pWnd )
                {
                    GetClassName(pWnd->GetSafeHwnd(), szClassName, 40);
                    if ( lstrcmpi(_T("EDIT"), szClassName) == 0 )
                    {
                        return FALSE;
                    }
                }
            }
            return TRUE;
        }
    }

    return CDialog::PreTranslateMessage(pMsg);
}

BOOL CSoundStudioDlg::OnInitDialog()
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
    SetIcon(m_hIcon, TRUE);         // Set big icon
    SetIcon(m_hIcon, FALSE);        // Set small icon

    // TODO: Add extra initialization here
    m_MeterData.resize( NUM_FREQUENCY );
    m_PeakMeter1.SetMeterBands(NUM_FREQUENCY, 20);
    m_PeakMeter1.Start(33);
    m_waveOutput.SetNotifyHandler( this );

    return TRUE;  // return TRUE  unless you set the focus to a control
}

void CSoundStudioDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CSoundStudioDlg::OnPaint()
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

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CSoundStudioDlg::OnQueryDragIcon()
{
    return static_cast<HCURSOR>(m_hIcon);
}

HRESULT CSoundStudioDlg::SetupMixer()
{
    HRESULT hr;
    hr = m_mixerDevice.Open( static_cast<UINT>(m_waveOutput.GetId()), CALLBACK_WINDOW|MIXER_OBJECTF_HWAVEOUT, GetSafeHwnd());
    MixerControl  mxc;
    MixerLineInfo mxli;
    MixerLineControls mxlcs;
    MixerControlDetails mxcd;
    MIXERCONTROLDETAILS_BOOLEAN mxMute;
    MIXERCONTROLDETAILS_SIGNED mxVolume;

    mxli.dwComponentType = MIXERLINE_COMPONENTTYPE_DST_SPEAKERS;
    hr = m_mixerDevice.GetLineInfo( mxli, MIXER_GETLINEINFOF_COMPONENTTYPE);

    mxlcs.dwLineID = mxli.dwLineID;
    mxlcs.cControls = 1;
    mxlcs.dwControlType = MIXERCONTROL_CONTROLTYPE_MUTE;
    mxlcs.cbmxctrl = mxc.Size();
    mxlcs.pamxctrl = mxc;
    hr = m_mixerDevice.GetLineControls( mxlcs, MIXER_GETLINECONTROLSF_ONEBYTYPE);
    m_dwMuteControlID = mxc.dwControlID;

    mxlcs.dwLineID = mxli.dwLineID;
    mxlcs.cControls = 1;
    mxlcs.dwControlType = MIXERCONTROL_CONTROLTYPE_VOLUME;
    mxlcs.cbmxctrl = mxc.Size();
    mxlcs.pamxctrl = mxc;
    hr = m_mixerDevice.GetLineControls( mxlcs, MIXER_GETLINECONTROLSF_ONEBYTYPE);
    m_dwVolumeControlID = mxc.dwControlID;

    if ( SUCCEEDED(hr) )
    {
        SendDlgItemMessage(IDC_CTL_VOLUME, TBM_SETRANGEMIN, FALSE, mxc.Bounds.lMinimum);
        SendDlgItemMessage(IDC_CTL_VOLUME, TBM_SETRANGEMAX, TRUE, mxc.Bounds.lMaximum);
        SendDlgItemMessage(IDC_CTL_VOLUME, TBM_SETTICFREQ, (mxc.Bounds.lMaximum-mxc.Bounds.lMinimum)/10, NULL);
        TRACE(_T("Volume range : %d - %d\n"), mxc.Bounds.lMinimum, mxc.Bounds.lMaximum);
    }

    mxcd.dwControlID = m_dwMuteControlID;
    mxcd.cChannels = 1;
    mxcd.cMultipleItems = 0;
    mxcd.cbDetails = sizeof(mxMute);
    mxcd.paDetails = &mxMute;
    hr = m_mixerDevice.GetControlDetails( mxcd, MIXER_GETCONTROLDETAILSF_VALUE);

    mxcd.dwControlID = m_dwVolumeControlID;
    mxcd.cChannels = 1;
    mxcd.cMultipleItems = 0;
    mxcd.cbDetails = sizeof(mxVolume);
    mxcd.paDetails = &mxVolume;
    hr = m_mixerDevice.GetControlDetails( mxcd, MIXER_GETCONTROLDETAILSF_VALUE);

    SendDlgItemMessage(IDC_BTN_MUTE, BM_SETCHECK, (mxMute.fValue == 0 ? BST_UNCHECKED : BST_CHECKED));
    SendDlgItemMessage(IDC_CTL_VOLUME, TBM_SETPOS, TRUE, mxVolume.lValue);
    return hr;
}

void CSoundStudioDlg::Terminate()
{
    m_mixerDevice.Close();
    m_waveOutput.Close();
    m_AudioStream.ReleaseMediaStream();
    m_MediaStream.Terminate();
    delete []m_pWaveBuffer;
    m_pWaveBuffer = NULL;

    m_RealIn_RT.clear();
    m_RealIn_LT.clear();
    m_RealOut.clear();
    m_ImagOut.clear();
    m_Ampl.clear();
}

bool CSoundStudioDlg::GetAudioData(const LPBYTE pbData, size_t cbSize, const WaveFormat& wfmt)
{
    bool samplesReady = false;
    switch( wfmt.wBitsPerSample )
    {
    case 8:
        {
            if ( wfmt.nChannels == 1 ) // mono
            {
                for (size_t i = 0; i < cbSize; ++i)
                {
                    m_RealIn_RT[i] = static_cast<float>((pbData[i] - 128) << 6);// Out = (In-128)*64
                    m_RealIn_LT[i] = m_RealIn_RT[i];
                }
                m_nNumSamples = cbSize;
            }
            else if ( wfmt.nChannels == 2 ) // stereo
            {
                // Stereo has Left+Right channels
                size_t Samples = cbSize >> 1;
                for (size_t i = 0, j=0; i < Samples; ++i, j+=2)
                {
                    m_RealIn_RT[i] = static_cast<float>((pbData[j] - 128) << 6); // Out = (In-128)*64
                    m_RealIn_LT[i] = static_cast<float>((pbData[j+1] - 128) <<6); // Out = (In-128)*64
                }
                m_nNumSamples = Samples;
            }
            samplesReady = (m_nNumSamples != 0);
        }
        break;
    case 16:
        {
            const short *pfData = reinterpret_cast<const short*>(pbData);
            if ( wfmt.nChannels == 1 ) // mono
            {
                size_t Samples = cbSize >> 1;
                for (size_t i = 0; i < Samples; ++i)
                {
                    m_RealIn_RT[i] = static_cast<float>(pfData[i]);
                    m_RealIn_LT[i] = m_RealIn_RT[i];
                }
                m_nNumSamples = Samples;
            }
            else if ( wfmt.nChannels == 2 ) // stereo
            {
                // Stereo has Left+Right channels
                size_t Samples = cbSize >> 2;
                for (size_t i = 0, j=0; i < Samples; ++i, j+=2)
                {
                    m_RealIn_RT[i] = static_cast<float>( pfData[j] );
                    m_RealIn_LT[i] = static_cast<float>( pfData[j+1] );
                }
                m_nNumSamples = Samples;
            }
            samplesReady = (m_nNumSamples != 0);
        }
        break;
    default:
        assert( false ); // not supported
        break;
    }
    return samplesReady;
}

bool CSoundStudioDlg::PutAudioData(LPBYTE pbData, size_t cbSize, size_t recvBytes, const WaveFormat& wfmt)
{
    bool samplesReady = true;
    switch( wfmt.wBitsPerSample )
    {
    case 8:
        {
            // fill with silence - no smoothing
            if ( cbSize > recvBytes )
            {
                memset(pbData+recvBytes, 0x80, cbSize-recvBytes);
            }
        }
        break;
    case 16:
    default:
        {
            // fill with silence - no smoothing
            if ( cbSize > recvBytes )
            {
                memset(pbData+recvBytes, 0x00, cbSize-recvBytes);
            }
        }
        break;
    }
    return samplesReady;
}

void CSoundStudioDlg::ComputeFFT(const LPBYTE pbData, size_t cbSize)
{
    WaveFormat wfmt = m_AudioStream.GetWaveFormat();
    if ( GetAudioData(pbData, cbSize, wfmt) )
    {
        //TRACE(_T("Computing FFT (%d samples)\n"), m_nNumSamples);
        FFT::Compute<float>(m_nNumSamples, &m_RealIn_RT[0], NULL, &m_RealOut[0], &m_ImagOut[0]);

        size_t index = 0;
        // We can skip N/2 to N samples (mirror frequencies) - Digital samples are real integer
        FFT::Norm<float>(m_nNumSamples/2, &m_RealOut[0], &m_ImagOut[0], &m_Ampl[0]);
      
        double maxAmpl = ( wfmt.wBitsPerSample == 8) ? (127.0*127.0) : (32767.0*32767.0);

        // update meter
        int centerFreq = static_cast<int>(wfmt.nSamplesPerSec/2);
        for(int i=0; i < NUM_FREQUENCY; ++i)
        {
            if ( METER_FREQUENCY[i] > centerFreq )
                m_MeterData[i] = 0;
            else
            {
                int indice = static_cast<int>( METER_FREQUENCY[i] * m_nNumSamples / wfmt.nSamplesPerSec );
                int value  = static_cast<int>( 20.0*log10(m_Ampl[indice]/maxAmpl) );
                m_MeterData[i] = value;
            }
        }
        m_PeakMeter1.SetData(&m_MeterData[0], 0, NUM_FREQUENCY);
        m_nNumSamples = 0; // ready to do it again
    }
}

void CSoundStudioDlg::OnDestroy()
{
    Terminate();
    m_waveOutput.SetNotifyHandler( NULL );

    CDialog::OnDestroy();
}

void CSoundStudioDlg::ProcessEvent(IWaveDevice* pDevice, UINT uMsg, WaveBuffer* pwbuf)
{
    if ( pDevice == &m_waveOutput )
    {
        switch( uMsg )
        {
            case WOM_OPEN:
                {
                    OutputDebugString( _T("WaveOut opened.\n") );
                }
                break;
            case WOM_DONE:
                {
                    PostMessage(WM_AUDIO_DONE, 0, (LPARAM)pwbuf);
                }
                break;
            case WOM_CLOSE:
                {
                    OutputDebugString( _T("WaveOut closed.\n") );
                }
                break;
        }
    }
}

void CSoundStudioDlg::OnBnClickedBtnOpen()
{
    static LPCTSTR pszFilter = _T("Audio Files (*.wav;*.mp3;*.wma)|*.wav;*.mp3;*.wma||");
    CFileDialog fileOpen(TRUE, _T("wav"), NULL,
        OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, pszFilter, this);
    if ( IDOK == fileOpen.DoModal() )
    {
        SetDlgItemText(IDC_TXT_FILENAME, fileOpen.GetPathName());
    }
}

void CSoundStudioDlg::OnBnClickedBtnPlay()
{
    // TODO: Add your control notification handler code here
    if ( !m_waveOutput.IsOpen() )
    {
        // primary audio output
        HRESULT hr;
        CString strPath;
        GetDlgItemText(IDC_TXT_FILENAME, strPath);
        hr = m_MediaStream.Initialize(STREAMTYPE_READ, AMMSF_NOGRAPHTHREAD, NULL);
        if ( SUCCEEDED(hr) )
        {
            CComPtr<IMediaStream> pAudioStream;
            hr = m_MediaStream.AddMediaStream(NULL, &MSPID_PrimaryAudio, 0, &pAudioStream);
            hr = m_MediaStream.OpenFile( strPath, AMMSF_RUN);
            
            if ( SUCCEEDED(hr) )
            {
                hr = m_AudioStream.SetMediaStream(pAudioStream);
                WaveFormat wfmt = m_AudioStream.GetWaveFormat();
                hr = m_waveOutput.Open(WAVE_MAPPER, wfmt);
                // calculate required buffer
                m_nBufferSize = FFT::NextPowerOfTwo( static_cast<size_t>(wfmt.nAvgBytesPerSec * FFT_SPEED) );
                TRACE(_T("FMT(%d): Freq:%d Hz - %d bits %d channel(s)\n"), wfmt.wFormatTag, wfmt.nSamplesPerSec, wfmt.wBitsPerSample, wfmt.nChannels);
                delete []m_pWaveBuffer;
                m_pWaveBuffer = new WaveBuffer[NUM_BUFFERS];
                for( int index=0; index < NUM_BUFFERS; ++index)
                {
                    // realloc memory
                    m_pWaveBuffer[index].Allocate(static_cast<DWORD>(m_nBufferSize));
                    m_pWaveBuffer[index].SetFlags(0);
                }
                m_nNumSamples = m_nBufferSize / wfmt.nBlockAlign;
                m_RealIn_RT.resize( m_nNumSamples );
                m_RealIn_LT.resize( m_nNumSamples );
                m_RealOut.resize( m_nNumSamples );
                m_ImagOut.resize( m_nNumSamples );
                m_Ampl.resize( m_nNumSamples );
                TRACE(_T("BufferSize:%d  NumSamples:%d\n"), m_nBufferSize, m_nNumSamples);
                m_nNumSamples = 0;
                m_nNumOutBuffers = 0;
                if ( SUCCEEDED(hr) )
                {
                    DWORD dwBytes;
                    for( int index=0; index < NUM_BUFFERS; ++index)
                    {
                        WaveBuffer& curBuffer = m_pWaveBuffer[index];
                        dwBytes = curBuffer.GetBufferLength();

                        hr = m_AudioStream.GetSampleData(reinterpret_cast<LPBYTE>(curBuffer.GetBuffer()), dwBytes);
                        if ( SUCCEEDED(hr) && dwBytes > 0 )
                        {
                            HRESULT whr;
                            whr = m_waveOutput.PrepareBuffer( curBuffer );
                            whr = m_waveOutput.AddBuffer( curBuffer );
                            ::InterlockedIncrement(&m_nNumOutBuffers);
                            if ( index == 0 ) {
                                whr = m_waveOutput.Start();
                            }
                        }
                        else
                        {
                            break;
                        }
                    }
                    
                    // setup mixer
                    hr = SetupMixer();
                }
            }
        }
    }
}

void CSoundStudioDlg::OnBnClickedBtnPlaystop()
{
    // TODO: Add your control notification handler code here
    Terminate();
}

void CSoundStudioDlg::OnBnClickedBtnMute()
{
    if ( m_mixerDevice.IsOpen() )
    {
        HRESULT hr;
        MixerControlDetails mxcd;
        MIXERCONTROLDETAILS_BOOLEAN mxMute;

        mxMute.fValue = ( SendDlgItemMessage(IDC_BTN_MUTE, BM_GETCHECK, NULL, NULL) == BST_CHECKED );
        mxMute.fValue = !mxMute.fValue; // don't need this for AUTOCHECKBOX
        mxcd.dwControlID = m_dwMuteControlID;
        mxcd.cChannels = 1;
        mxcd.cMultipleItems = 0;
        mxcd.cbDetails = sizeof(mxMute);
        mxcd.paDetails = &mxMute;
        hr = m_mixerDevice.SetControlDetails( mxcd, MIXER_SETCONTROLDETAILSF_VALUE);
        hr = hr;
    }
}

LRESULT CSoundStudioDlg::OnAudioDataDone(WPARAM, LPARAM lParam)
{
    HRESULT hr;
    DWORD dwBytes;

    WaveBuffer* pwbuf = reinterpret_cast<WaveBuffer*>( lParam );
    WaveBuffer& curBuffer = *pwbuf;
    hr = m_waveOutput.UnprepareBuffer( curBuffer );
    ::InterlockedDecrement(&m_nNumOutBuffers);
    dwBytes = curBuffer.GetBufferLength();

    // compute FFT
    if ( m_waveOutput.GetDeviceStatus() == waveStarted )
    {
        ComputeFFT(reinterpret_cast<LPBYTE>(curBuffer.GetBuffer()), dwBytes);
    }

    hr = m_AudioStream.GetSampleData(reinterpret_cast<LPBYTE>(curBuffer.GetBuffer()), dwBytes);
    if ( SUCCEEDED(hr) )
    {
        if ( hr == S_OK )
        {
            if ( m_waveOutput.GetDeviceStatus() == waveStarted )
            {
                HRESULT whr;

                // Append silence if necessary
                WaveFormat wfmt = m_AudioStream.GetWaveFormat();
                PutAudioData(reinterpret_cast<LPBYTE>(curBuffer.GetBuffer()), m_nBufferSize, dwBytes, wfmt);

                whr = m_waveOutput.PrepareBuffer( curBuffer );
                whr = m_waveOutput.AddBuffer( curBuffer );
                ::InterlockedIncrement(&m_nNumOutBuffers);
            }
        }
        else if ( m_nNumOutBuffers == 0 ) // all buffers done
        {
            // stop
            SendMessage(WM_COMMAND, MAKEWPARAM(IDC_BTN_PLAYSTOP, BN_CLICKED), 0);
        }
    }
    return 0;
}

LRESULT CSoundStudioDlg::OnMixerControlChange(WPARAM wParam, LPARAM lParam)
{
    if ( m_mixerDevice.IsOpen() )
    {
        MIXERCONTROLDETAILS_SIGNED mxVolume = { 0 };
        MIXERCONTROLDETAILS_BOOLEAN mxMute  = { 0 };

        MixerControlDetails mxcd;
        mxcd.dwControlID = static_cast<DWORD>(lParam);
        mxcd.cChannels = 1;
        HRESULT hr = S_FALSE;
        if ( static_cast<DWORD>(lParam) == m_dwMuteControlID )
        {
            mxcd.paDetails = &mxMute;
            mxcd.cbDetails = sizeof(mxMute);
            hr = S_OK;
        }
        else if ( static_cast<DWORD>(lParam) == m_dwVolumeControlID )
        {
            mxcd.paDetails = &mxVolume;
            mxcd.cbDetails = sizeof(mxVolume);
            hr = S_OK;
        }
        if ( hr == S_OK )
        {
            hr = m_mixerDevice.GetControlDetails( mxcd, MIXER_GETCONTROLDETAILSF_VALUE );
            CString sInfo;
            if ( static_cast<DWORD>(lParam) == m_dwMuteControlID )
            {
                SendDlgItemMessage(IDC_BTN_MUTE, BM_SETCHECK, (mxMute.fValue == 0 ? BST_UNCHECKED : BST_CHECKED));
                sInfo.Format(_T("MIXER (%p) - Control: MUTE (Value:%d)\n"), wParam, mxMute.fValue);
            }
            else if ( static_cast<DWORD>(lParam) == m_dwVolumeControlID )
            {
                SendDlgItemMessage(IDC_CTL_VOLUME, TBM_SETPOS, TRUE, mxVolume.lValue);
                sInfo.Format(_T("MIXER (%p) - Control: VOLUME (Value:%d)\n"), wParam, mxVolume.lValue);
            }

            ATLTRACE( sInfo );
        }
    }
    return 0;
}

void CSoundStudioDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
    if ( m_mixerDevice.IsOpen() )
    {
        MIXERCONTROLDETAILS_SIGNED mxVolume;
        mxVolume.lValue = static_cast<USHORT>(nPos);
        MixerControlDetails mxcd;
        mxcd.dwControlID = m_dwVolumeControlID;
        mxcd.cChannels = 1;
        mxcd.paDetails = &mxVolume;
        mxcd.cbDetails = sizeof(mxVolume);
        HRESULT hr;
        if ( nSBCode != SB_ENDSCROLL )
        {
            hr = m_mixerDevice.SetControlDetails( mxcd, MIXER_SETCONTROLDETAILSF_VALUE );
        }
    }

    __super::OnHScroll(nSBCode, nPos, pScrollBar);
}
