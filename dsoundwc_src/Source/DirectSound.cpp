// Copyright(C) 2004-2006, Arman Sahakyan

#include "stdAfx.h"
#include "directsound.h"

// This comment-directives perform linking with libraries.
// If You order linking through Project/Settings/Link tab,
// You may remove this comment-diractives.
#pragma comment(lib, "Wavelib.lib")
#pragma comment(lib, "dsound.lib")

using namespace DirectSound;

//------------------------------------ CDSound
CDSound::CDSound()
{
	m_pDirectSound = NULL;
}

CDSound::~CDSound()
{
	Destroy();
}

BOOL CDSound::Create()
{
	if (::DirectSoundCreate(NULL, &m_pDirectSound, NULL) != DS_OK)
	{
		TRACE("Cannot create DirectSound object!", MB_OK, MB_ICONERROR);
		Destroy();
		return FALSE;
	}
	return TRUE;
}

BOOL CDSound::SetCooperativeLevel(HWND hWnd, DWORD dwLevel /* = DSSCL_NORMAL*/)
{
	if (m_pDirectSound->SetCooperativeLevel(hWnd, dwLevel) != DS_OK)
	{
		TRACE("Cannot set cooperative level!", MB_OK, MB_ICONERROR);
		Destroy();
		return FALSE;
	}
	return TRUE;
}


//---------------------------------------- CDSBuffer

CDSBuffer::CDSBuffer()
{
	m_pDSBuffer = NULL;
	m_uIDRcsrWave = -1;
	m_dwFlags = 0;
}

CDSBuffer::~CDSBuffer()
{
}

BOOL CDSBuffer::Create(IDirectSound *pDirectSound, const CWave &wave, DWORD dwFlags)
{
	DWORD dwDataLen = wave.GetDataLen();
	WAVEFORMATEX wfFormat;
	wave.GetFormat(wfFormat);
	DSBUFFERDESC dsbdDesc;
	ZeroMemory(&dsbdDesc, sizeof (DSBUFFERDESC));
	dsbdDesc.dwSize = sizeof (DSBUFFERDESC);
	dsbdDesc.dwFlags = dwFlags;
		//DSBCAPS_CTRLDEFAULT | DSBCAPS_STATIC | DSBCAPS_LOCSOFTWARE
		//| DSBCAPS_CTRLPOSITIONNOTIFY ;
	dsbdDesc.dwBufferBytes = dwDataLen;
	dsbdDesc.lpwfxFormat = &wfFormat;
	HRESULT hr;
	CComPtr<IDirectSoundBuffer> lpDSB;
	if ((hr = pDirectSound->CreateSoundBuffer(&dsbdDesc, &lpDSB, NULL)) != DS_OK)
	{
		CString str(TEXT(""));
		if (hr == DSERR_BADFORMAT) str = TEXT(" The specified wave format is not supported.");
		TRACE("Cannot craete SoundBuffer object! " +  str);
		return FALSE;
	}
	if( FAILED( hr = lpDSB->QueryInterface(IID_IDirectSoundBuffer, (LPVOID *) &m_pDSBuffer)))
	{
		TRACE("Cannot query SoundBuffer8 object! ");
		return hr;
	}
	PBYTE pDSBuffData;
	if (m_pDSBuffer->Lock(0, dwDataLen, (PVOID *) &pDSBuffData, 
		&dwDataLen, NULL, 0, 0) != DS_OK)
	{
		TRACE("Fail to lock SoundBuffer object!", MB_OK, MB_ICONERROR);
		return FALSE;
	}
	// putting WAV datas into sound buffer
	dwDataLen = wave.GetData(pDSBuffData, dwDataLen);
	if (m_pDSBuffer->Unlock(pDSBuffData, dwDataLen, NULL, 0) != DS_OK)
	{
		TRACE("Fail to unlock SoundBuffer object!", MB_OK, MB_ICONERROR);
		return FALSE;
	}
	m_pDirectSound = pDirectSound;

	hr = m_pDSBuffer->QueryInterface(IID_IDirectSoundNotify, (void **) &m_pDSNotify);
	if (FAILED(hr))
	{
		TRACE("Fail to query IDirectSoundNotify object!", MB_OK, MB_ICONERROR);
		return FALSE;
	}
	return TRUE;
}

BOOL CDSBuffer::Create(IDirectSound * pDirectSound, UINT uIDRcsrWave, DWORD dwFlags, HMODULE hMod /*= AfxGetInstanceHandle()*/)
{
	CWave wave ;
	wave.Create(uIDRcsrWave, hMod);
	return Create(pDirectSound, wave, dwFlags);
}

BOOL CDSBuffer::Create(IDirectSound * pDirectSound, LPCTSTR lpszFileName, DWORD dwFlags)
{
	CWave wave;
	wave.Create(lpszFileName);
	return Create(pDirectSound, wave, dwFlags);
}

BOOL CDSBuffer::Restore()
{
	if (m_pDSBuffer->Restore() != DS_OK)
		return FALSE;
	return Create(m_pDirectSound, m_uIDRcsrWave, m_dwFlags);
}

//////------------------ CDSoundPlay
CDSoundPlay::CDSoundPlay()
{
	m_pDirectSound = NULL;
	m_pFunc = NULL;
	m_phEvents = NULL;
	m_pThread = NULL;
}

CDSoundPlay::~CDSoundPlay()
{
	this->Destroy();
}

void CDSoundPlay::Destroy()
{
	if (m_pThread)
	{
		::PulseEvent(m_hEventThreadStop);
		::WaitForSingleObject(m_pThread->m_hThread, INFINITE);
	}
	m_pFunc = NULL;
	m_phEvents = NULL;
	m_pThread = NULL;
	m_hEventThreadStop = NULL;
	m_DSBuffer.Destroy();
}

BOOL CDSoundPlay::Create(CDSound *pDSound, UINT uIDRsrcWave, DWORD dwFlags, HMODULE hMod /*= AfxGetInstanceHandle()*/)
{
	m_pDirectSound = pDSound;
	return m_DSBuffer.Create(*m_pDirectSound, uIDRsrcWave, dwFlags, hMod);
}

BOOL CDSoundPlay::Create(CDSound *pDSound, LPCTSTR lpszFileName, DWORD dwFlags)
{
	m_pDirectSound = pDSound;
	return m_DSBuffer.Create(*m_pDirectSound, lpszFileName, dwFlags);
}

DWORD CDSoundPlay::GetCurrentPosition(LPDWORD lpdwCurrentWriteCursor) const
{
	DWORD dwCurrPlayPos;
	HRESULT hr;
	hr = m_DSBuffer->GetCurrentPosition(&dwCurrPlayPos, lpdwCurrentWriteCursor);
	if (FAILED(hr))
	{
		TRACE("- fail: GetCurrentPosition: hresult = 0x%x\n", hr);
		return (DWORD)DSOUND_ERR;
	}
	return dwCurrPlayPos;
}

DWORD CDSoundPlay::GetFrequency() const
{
	DWORD dwFreq;
	HRESULT hr;
	hr = m_DSBuffer->GetFrequency(&dwFreq);
	if (FAILED(hr))
	{
		TRACE("- fail: GetFrequency: hresult = 0x%x\n", hr);
		return (DWORD)DSOUND_ERR;
	}
	return dwFreq;
}

LONG CDSoundPlay::GetPan() const
{
	LONG lPan;
	HRESULT hr;
	hr = m_DSBuffer->GetPan(&lPan);
	if (FAILED(hr))
	{
		TRACE("- fail: GetPan: hresult = 0x%x\n", hr);
		return DSOUND_ERR;
	}
	return lPan;
}

LONG CDSoundPlay::GetVolume() const
{
	LONG lVol;
	HRESULT hr;
	hr = m_DSBuffer->GetVolume(&lVol);
	if (FAILED(hr))
	{
		TRACE("- fail: GetVolume: hresult = 0x%x\n", hr);
		return DSOUND_ERR;
	}
	return lVol;
}

DWORD CDSoundPlay::GetStatus() const
{
	DWORD dwStatus;
	HRESULT hr;
	hr = m_DSBuffer->GetStatus(&dwStatus);
	if (FAILED(hr))
	{
		TRACE("- fail: GetStatus: hresult = 0x%x\n", hr);
		return (DWORD)DSOUND_ERR;
	}
	return dwStatus;
}

BOOL CDSoundPlay::Play(BOOL bLooping /* = FALSE */)
{
	HRESULT hr;
	hr = m_DSBuffer->Play(0, 0, bLooping ? DSBPLAY_LOOPING : 0);
	if (FAILED(hr))
	{
		TRACE("- fail: Play: hresult = 0x%x\n", hr);
		return FALSE;
	}
	return TRUE;
}

BOOL CDSoundPlay::SetCurrentPosition(DWORD dwNewPos)
{
	HRESULT hr;
	hr = m_DSBuffer->SetCurrentPosition(dwNewPos);
	if (FAILED(hr))
	{
		TRACE("- fail: SetCurrentPosition: hresult = 0x%x\n", hr);
		return FALSE;
	}
	return TRUE;
}

BOOL CDSoundPlay::SetFrequency(DWORD dwFreq)
{
	HRESULT hr;
	hr = m_DSBuffer->SetFrequency(dwFreq);
	if (FAILED(hr))
	{
		TRACE("- fail: SetFrequency: hresult = 0x%x\n", hr);
		return FALSE;
	}
	return TRUE;
}

BOOL CDSoundPlay::SetPan(LONG lPan)
{
	HRESULT hr;
	hr = m_DSBuffer->SetPan(lPan);
	if (FAILED(hr))
	{
		TRACE("- fail: SetPan: hresult = 0x%x\n", hr);
		return FALSE;
	}
	return TRUE;
}

BOOL CDSoundPlay::SetVolume(LONG lVolume)
{
	HRESULT hr;
	hr = m_DSBuffer->SetVolume(lVolume);
	if (FAILED(hr))
	{
		TRACE("- fail: SetVolume: hresult = 0x%x\n", hr);
		return FALSE;
	}
	return TRUE;
}

BOOL CDSoundPlay::Stop()
{
	HRESULT hr;
	hr = m_DSBuffer->Stop();
	if (FAILED(hr))
	{
		TRACE("- fail: Stop: hresult = 0x%x\n", hr);
		return FALSE;
	}
	return TRUE;
}

BOOL CDSoundPlay::SetNotificationPositions(DWORD dwOffsets[], SIZE_T nSize)
{
	if (NULL == dwOffsets && m_pThread)
	{ // Cancel
		::PulseEvent(m_hEventThreadStop);
		::WaitForSingleObject(m_pThread->m_hThread, INFINITE); // wait until the thread ends
		m_pThread = NULL;
		m_hEventThreadStop = NULL;
		return TRUE;
	}

	if (!m_pFunc)
		return FALSE;

	delete [] m_phEvents;
	m_phEvents = new HANDLE[nSize + 1];

	LPDSBPOSITIONNOTIFY pdsb = new DSBPOSITIONNOTIFY[nSize];

	for (SIZE_T j = 0; j < nSize; j ++)
	{
		pdsb[j].dwOffset = dwOffsets[j];
		pdsb[j].hEventNotify = m_phEvents[j] = ::CreateEvent(NULL, FALSE, FALSE, NULL);
	}

	HRESULT hr = m_DSBuffer.GetDSNotify()->SetNotificationPositions(nSize, pdsb);
	delete [] pdsb;

	if (FAILED(hr))
	{
		TRACE("- fail: SetNotificationPositions: hresult = 0x%x\n", hr);
		delete [] m_phEvents;
		return FALSE;
	}

	PINFO pInfo = new _INFO;
	pInfo->dwOffsets = new DWORD[nSize];
	for (SIZE_T t = 0; t < nSize; t ++)
	{
		pInfo->dwOffsets[t] = dwOffsets[t];
	}
	pInfo->pFunc = m_pFunc;
	pInfo->hEvents = m_phEvents;
	m_phEvents = NULL; // the memory will be deleted in the thread via pInfo->hEvents
	pInfo->hEvents[nSize] = m_hEventThreadStop = ::CreateEvent(NULL, FALSE, FALSE, NULL);
	pInfo->nSize = nSize;

	if (m_pThread)
	{ // If running we should stop it and then start again
		::PulseEvent(m_hEventThreadStop);
		::WaitForSingleObject(m_pThread->m_hThread, INFINITE);
	}
	m_pThread = AfxBeginThread(_ThreadProc, pInfo);

	return TRUE;
}

UINT CDSoundPlay::_ThreadProc(PVOID pParam)
{
	TRACE("- CDSoundPlay::_ThreadProc: start...\n");

	PINFO pInfo = reinterpret_cast<PINFO> (pParam);

	while (TRUE)
	{
		DWORD dwReason = ::WaitForMultipleObjects(pInfo->nSize + 1, pInfo->hEvents, FALSE, INFINITE);
		if (WAIT_FAILED == dwReason)
		{ // Some error (you may do something reasonable in here)
			break;
		}
		if (WAIT_OBJECT_0 + pInfo->nSize == dwReason)
		{ // Stop
			break;
		}
		for (SIZE_T j = 0; j < pInfo->nSize; j ++)
		{
			if (WAIT_OBJECT_0 + j == dwReason)
			{
				ASSERT(pInfo->pFunc);
				pInfo->pFunc(pInfo->dwOffsets[j]);
			}
		}
	}

	for (SIZE_T j = 0; j < pInfo->nSize + 1; j ++)
	{
		::CloseHandle(pInfo->hEvents[j]);
	}
	delete [] pInfo->dwOffsets;
	delete [] pInfo->hEvents;
	delete pInfo;
	TRACE("- CDSoundPlay::_ThreadProc: exit.\n");
	return 0;
}
