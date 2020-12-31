// Recorder.cpp: implementation of the CRecorder class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "waveInFFT.h"
#include "Recorder.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

void CALLBACK waveInProc(HWAVEIN hwi, UINT uMsg, DWORD dwInstance, DWORD dwParam1, DWORD dwParam2)
{
	Recorder* pRecorder = NULL;
	switch (uMsg)
	{
	case WIM_OPEN:
		break;
	case WIM_DATA:
		//if ((((LPWAVEHDR)dwParam1)->dwFlags) == WHDR_DONE)
		{
			pRecorder = (Recorder*)(((LPWAVEHDR)dwParam1)->dwUser);
			pRecorder->m_lpWaveHdr = (LPWAVEHDR)dwParam1;
			SetEvent(pRecorder->m_hEvent);
		}
		break;
	case WIM_CLOSE:
		break;
	default:
		break;
	}
}
DWORD CALLBACK RecorderThreadFunc(LPVOID lpThreadData)
{
	Recorder* pRecorder = NULL;
	pRecorder = (Recorder*)lpThreadData;
	while (pRecorder->IsRecording())
	{
		WaitForSingleObject(pRecorder->m_hEvent,INFINITE);
		pRecorder->ProcessNextBuffer(pRecorder->m_lpWaveHdr);
	}
	return 0;
}
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

Recorder::Recorder(int nBufferLength)
{
	m_bRecording = FALSE;
	m_bDeviceOpen = FALSE;
	m_PcmFormat.wBitsPerSample = 16;
	m_PcmFormat.wChannels = 2;
	m_PcmFormat.dwSampleRate = 44100;
	m_dwBufferSize = (nBufferLength * m_PcmFormat.wChannels * m_PcmFormat.wBitsPerSample / 8);
	fnProcessBuffer = NULL;
	m_lpWaveHdr = NULL;
	
	m_hEvent = NULL;
	m_hThread = NULL;
	for(int i=0; i<MAXNUMOFBUFFER; i++)
	{
		m_hWaveInHdr[i] = NULL;
		m_hInBuffer[i] = NULL;
	}
}
Recorder::Recorder(PCMFORMAT pcm,int nBufferLength)
{
	m_bRecording = FALSE;
	m_bDeviceOpen = FALSE;
	m_PcmFormat.wBitsPerSample = pcm.wBitsPerSample;
	m_PcmFormat.wChannels = pcm.wChannels;
	m_PcmFormat.dwSampleRate = pcm.dwSampleRate;
	m_dwBufferSize = (nBufferLength * m_PcmFormat.wChannels * m_PcmFormat.wBitsPerSample / 8);
	fnProcessBuffer = NULL;
	m_lpWaveHdr = NULL;
	
	m_hEvent = NULL;
	m_hThread = NULL;
	for(int i=0; i<MAXNUMOFBUFFER; i++)
	{
		m_hWaveInHdr[i] = NULL;
		m_hInBuffer[i] = NULL;
	}
}
Recorder::Recorder(WORD wBitsPerSample,WORD wChannels,DWORD dwSampleRate,int nBufferLength)
{
	m_bRecording = FALSE;
	m_bDeviceOpen = FALSE;
	m_PcmFormat.wBitsPerSample = wBitsPerSample;
	m_PcmFormat.wChannels = wChannels;
	m_PcmFormat.dwSampleRate = dwSampleRate;
	m_dwBufferSize = (nBufferLength * m_PcmFormat.wChannels * m_PcmFormat.wBitsPerSample / 8);
	fnProcessBuffer = NULL;
	m_lpWaveHdr = NULL;

	m_hEvent = NULL;
	m_hThread = NULL;
	for(int i=0; i<MAXNUMOFBUFFER; i++)
	{
		m_hWaveInHdr[i] = NULL;
		m_hInBuffer[i] = NULL;
	}
}

Recorder::~Recorder()
{
	if(m_bRecording)
		Stop();
	if(m_bDeviceOpen)
        Close();
	fnProcessBuffer = NULL;
}
void Recorder::Open(DWORD dwCallBack, DWORD dwCallbackType,MCIDEVICEID wMCIDeviceID)
{
    if(m_bDeviceOpen)
	{
		TRACE("Device Already Opened. Please Stop Recorder before attempting to Open\n");
		return;
	}
	if (dwCallBack == NULL)
		dwCallBack = (DWORD)waveInProc;

	for(int i=0; i<MAXNUMOFBUFFER; i++)
	{
		m_hWaveInHdr[i] = GlobalAlloc(GHND | GMEM_SHARE , sizeof(WAVEHDR));
		m_lpWaveInHdr[i] = (LPWAVEHDR)GlobalLock(m_hWaveInHdr[i]);
		m_hInBuffer[i] = GlobalAlloc(GHND | GMEM_SHARE , m_dwBufferSize);
		m_lpInBuffer[i] = (LPBYTE)GlobalLock(m_hInBuffer[i]);
		m_lpWaveInHdr[i]->lpData = (LPSTR)m_lpInBuffer[i];
		m_lpWaveInHdr[i]->dwBufferLength = m_dwBufferSize;
		m_lpWaveInHdr[i]->dwBytesRecorded = 0L;
		m_lpWaveInHdr[i]->dwUser = (DWORD)(void*)this;
		m_lpWaveInHdr[i]->dwFlags = 0L;
		m_lpWaveInHdr[i]->dwLoops = 1L;
		m_lpWaveInHdr[i]->lpNext = NULL;
		m_lpWaveInHdr[i]->reserved = 0L;
	}
	m_WaveFormat.wFormatTag = WAVE_FORMAT_PCM;
	m_WaveFormat.nChannels = m_PcmFormat.wChannels;
	m_WaveFormat.wBitsPerSample = m_PcmFormat.wBitsPerSample;
	m_WaveFormat.nSamplesPerSec = m_PcmFormat.dwSampleRate;
	m_WaveFormat.nBlockAlign = m_WaveFormat.nChannels * m_WaveFormat.wBitsPerSample/8;
	m_WaveFormat.nAvgBytesPerSec = m_WaveFormat.nBlockAlign * m_WaveFormat.nSamplesPerSec;
	m_waveClass.lpData = this;
	if(waveInOpen((LPHWAVEIN)&m_waveClass, wMCIDeviceID, &m_WaveFormat, (DWORD)dwCallBack , 0L, dwCallbackType) || m_waveClass.hWave==0)
		return;
	m_waveClass.lpData = this;
	m_hWaveIn = (HWAVEIN)m_waveClass.hWave;
	m_hEvent = CreateEvent(NULL,FALSE,FALSE,NULL);
    m_bDeviceOpen=TRUE;
}
void Recorder::Start()
{
	if(!m_bDeviceOpen)
	{
		TRACE("Device not Opened. Please open device before attempting to Start\n");
		return;
	}

	for(int i=0; i<MAXNUMOFBUFFER; i++)
	{
		// Prepare wave in header
		if(waveInPrepareHeader(m_hWaveIn, m_lpWaveInHdr[i], sizeof(WAVEHDR)) != MMSYSERR_NOERROR)
			return;

		// Add buffer into recording queue
		if(waveInAddBuffer(m_hWaveIn, m_lpWaveInHdr[i], sizeof(WAVEHDR)) != MMSYSERR_NOERROR)
			return;
	}
	// Begin sampling
	m_bRecording = TRUE;
	m_hThread = CreateThread(NULL,NULL,RecorderThreadFunc,this,NULL,NULL);
	waveInStart(m_hWaveIn);
	ASSERT(m_hThread!=NULL);
	SetPriorityClass(m_hThread,REALTIME_PRIORITY_CLASS);
	SetThreadPriority(m_hThread,THREAD_PRIORITY_HIGHEST);
}
void Recorder::Stop()
{
	if(!m_bDeviceOpen || !m_bRecording)
		return;
	if(waveInStop(m_hWaveIn) != MMSYSERR_NOERROR)
		return;
	else
		m_bRecording=FALSE;
}
void Recorder::Close()
{
	if(m_bRecording)
        Stop();
	if (m_hThread != NULL)
		CloseHandle(m_hThread);
	if(m_bDeviceOpen)
		waveInClose(m_hWaveIn);
	for(int i=0; i<MAXNUMOFBUFFER; i++)
	{
		if (m_hWaveInHdr[i] != NULL)
		{
			if (GlobalUnlock(m_hWaveInHdr[i]))
				GlobalFree(m_hWaveInHdr[i]);
			if (GlobalUnlock(m_hInBuffer[i]))
				GlobalFree(m_hInBuffer[i]);
			m_hWaveInHdr[i] = NULL;
			m_hInBuffer[i] = NULL;
		}
	}
	m_bDeviceOpen=FALSE;
	m_bRecording = FALSE;
	m_hThread = NULL;
}
void Recorder::SetFormat(LPPCMFORMAT lpPcmFormat)
{
	ASSERT(m_bDeviceOpen==false);
	m_PcmFormat.wBitsPerSample = lpPcmFormat->wBitsPerSample;
	m_PcmFormat.wChannels = lpPcmFormat->wChannels;
	m_PcmFormat.dwSampleRate = lpPcmFormat->dwSampleRate;
}
void Recorder::SetFormat(WORD wBitsPerSample,WORD wChannels,DWORD dwSampleRate)
{
	ASSERT(m_bDeviceOpen==false);
	m_PcmFormat.wBitsPerSample = wBitsPerSample;
	m_PcmFormat.wChannels = wChannels;
	m_PcmFormat.dwSampleRate = dwSampleRate;
}
BOOL Recorder::IsRecording()
{
	return m_bRecording;
}
BOOL Recorder::IsDeviceOpen()
{
	return m_bDeviceOpen;
}

void Recorder::ProcessNextBuffer(LPWAVEHDR pwh)
{
	if (fnProcessBuffer != NULL)
		fnProcessBuffer(m_lpData,pwh);
	waveInUnprepareHeader(m_hWaveIn, pwh, sizeof(WAVEHDR));
	waveInPrepareHeader (m_hWaveIn, pwh, sizeof(WAVEHDR));
	waveInAddBuffer(m_hWaveIn, pwh, sizeof(WAVEHDR));
}

DWORD Recorder::GetPosition()
{
	if (m_hWaveIn)
	{
		MMTIME mmtime;
		mmtime.wType = TIME_SAMPLES;
		if (waveInGetPosition(m_hWaveIn, &mmtime, sizeof(MMTIME)) != MMSYSERR_NOERROR)
			return -1;
		else
			return mmtime.u.sample;
	}
	return -1;
}

BOOL Recorder::Pause()
{
	if (m_hWaveIn)
	{
		if (waveInStop(m_hWaveIn) == MMSYSERR_NOERROR)
		{
			m_bRecording = FALSE;
			return TRUE;
		}
	}
	return FALSE;
}

BOOL Recorder::Continue()
{
	if (m_hWaveIn)
	{
		if (waveInStart(m_hWaveIn) == MMSYSERR_NOERROR)
		{
			m_bRecording = FALSE;
			return TRUE;
		}
	}
	return FALSE;
}
BOOL Recorder::IsFormatSupported(WAVEFORMATEX wfEx, UINT nDev)
{
	MMRESULT mm = waveInOpen(0,nDev,&wfEx,0,0,WAVE_FORMAT_QUERY);
	return (BOOL)mm == MMSYSERR_NOERROR;		
}
