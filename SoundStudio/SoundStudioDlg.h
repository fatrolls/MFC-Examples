// SoundStudioDlg.h : header file
//

#pragma once
#include "WaveOutDevice.hpp"
#include "MixerDevice.hpp"
#include "MultimediaStream.hpp"
#include "PeakMeterCtrl.h"

// CSoundStudioDlg dialog
class CSoundStudioDlg : public CDialog,
                        public IWaveNotifyHandler
{
// Construction
public:
	CSoundStudioDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_SOUNDSTUDIO_DIALOG };
	CPeakMeterCtrl	m_PeakMeter1;

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

    virtual void ProcessEvent(IWaveDevice* pDevice, UINT uMsg,  WaveBuffer* pwbuf);

// Implementation
protected:
    enum { NUM_BUFFERS = 16, MAX_BUFFER_SIZE = 8*1024 };
	HICON m_hIcon;
    LONG            m_nNumOutBuffers;
    WaveBuffer*     m_pWaveBuffer;
    WaveOutDevice   m_waveOutput;
    MixerDevice     m_mixerDevice;
    MMAudioStream   m_AudioStream;
    MultimediaStream   m_MediaStream;

    std::vector<float> m_RealIn_RT;
    std::vector<float> m_RealIn_LT;
    std::vector<float> m_RealOut;
    std::vector<float> m_ImagOut;
    std::vector<float> m_Ampl;
    std::vector<int>   m_MeterData;
    size_t             m_nNumSamples;
    size_t             m_nBufferSize;

    DWORD           m_dwMuteControlID;
    DWORD           m_dwVolumeControlID;

    HRESULT SetupMixer();
    void Terminate();
    bool GetAudioData(const LPBYTE pbData, size_t cbSize, const WaveFormat& wfmt);
    bool PutAudioData(LPBYTE pbData, size_t cbSize, size_t numBytes, const WaveFormat& wfmt);
    void ComputeFFT(const LPBYTE pbData, size_t cbSize);

    // Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
    virtual BOOL PreTranslateMessage(MSG* pMsg);
    afx_msg void OnDestroy();
    afx_msg void OnBnClickedBtnOpen();
    afx_msg void OnBnClickedBtnPlay();
    afx_msg void OnBnClickedBtnPlaystop();
    afx_msg void OnBnClickedBtnMute();
    afx_msg LRESULT OnAudioDataDone(WPARAM, LPARAM);
    afx_msg LRESULT OnMixerControlChange(WPARAM, LPARAM);
    afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
};
