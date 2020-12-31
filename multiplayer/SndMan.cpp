// SndMan.cpp: implementation of the CSoundManager class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SndMan.h"
#include "NWaveio.h"
#include <mmreg.h>
#include <msacm.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


//////////////////////////////////////////////////////////////////////
// Thread callback function
//////////////////////////////////////////////////////////////////////
LONG WINAPI DoThreadFunc(void *pArg)
{
	CSoundManager* pSMan = (CSoundManager*)pArg;

    pSMan->DoTheadWorks();

	return 1L;
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CSoundManager::CSoundManager()
{
    m_pIDS = NULL;    
    m_pPrimaryDSB = NULL;
	m_hWndPlay = NULL;

	m_dwRefKey = 0;

	m_hThead = NULL;
	m_arrayDSnd.clear();

	// Create waitable timer, default time interval 
	// is 10s
	m_liDueTime.QuadPart = (ULONGLONG)(-10000000);
    m_hTimer = NULL;
	m_hTimer = ::CreateWaitableTimer(NULL, FALSE, NULL);	

}

CSoundManager::~CSoundManager()
{
	KillTimer();
	CloseWorkThread();
	RemoveAllSound();
	ReleasePrimaryDSB();
    CoUnInitializeDSound();
}


BOOL CSoundManager::CoInitializeDSound(void)
{
	HRESULT  hr;
	GUID     guID;
	
	// Clear the GUID
	::memset(&guID, 0, sizeof(GUID));

	// Initialize COM service, create STA 
	hr = ::CoInitialize(NULL);

    if(FAILED(hr))
	{
        return FALSE;
    }
    
	// Create the IDirectSound object with the realiable way (create
	// standard COM object)
	hr = CoCreateInstance(CLSID_DirectSound, NULL, CLSCTX_INPROC_SERVER,
              IID_IDirectSound, (void**)&m_pIDS);


    if(FAILED(hr))
	{
		CoUninitialize();
        return FALSE;
    }

	if(m_pIDS == NULL)
	{
		::CoUninitialize();
		return FALSE;
	}

	// Initialize the IDirectSound object
    hr = IDirectSound_Initialize(m_pIDS, &guID);

    if(FAILED(hr))
	{
		CoUnInitializeDSound();
		return FALSE;
	}

	return TRUE;
}


void CSoundManager::CoUnInitializeDSound(void)
{
    if(m_pIDS)
	{
        m_pIDS->Release();
        m_pIDS = NULL;
		::CoUninitialize();
	}	
}


void CSoundManager::SetHwnd(HWND hWnd)
{
	ASSERT(hWnd);
	m_hWndPlay = hWnd;
}


BOOL CSoundManager::CreatePrimaryDSB(void)
{
	ASSERT(m_pIDS && m_hWndPlay);
	if(!m_pIDS || !m_hWndPlay)
        return FALSE;

    DWORD         dwSize;
    WAVEFORMATEX  *pwfx; 
	DSBUFFERDESC  dsbd;
	HRESULT       hr;

    
	// Get the largest waveformatex structure.
    if(acmMetrics(NULL, ACM_METRIC_MAX_SIZE_FORMAT, &dwSize) !=
	   MMSYSERR_NOERROR)
    {
        return FALSE;
    }

	pwfx = (WAVEFORMATEX*)::VirtualAlloc(NULL, dwSize, MEM_COMMIT, PAGE_READWRITE);
	if(pwfx == NULL)
	{
		return FALSE;
	}    

	// Set default WAVEFORMATEX data for primary DirectSoundBuffer 
    pwfx->wFormatTag = WAVE_FORMAT_PCM;
    pwfx->nChannels = 2;
    pwfx->nSamplesPerSec = 22050;
    pwfx->nAvgBytesPerSec = 22050*2*2;
    pwfx->nBlockAlign = 4;
    pwfx->wBitsPerSample = 16;
    pwfx->cbSize = 0;

    // Set cooperative level 
	hr = m_pIDS->SetCooperativeLevel(m_hWndPlay, DSSCL_PRIORITY);
    
	if(hr == DS_OK)
	{
        // Set up the primary DirectSound buffer.
        ZeroMemory(&dsbd, sizeof(dsbd));
        dsbd.dwSize = sizeof(dsbd);
        dsbd.dwFlags = DSBCAPS_PRIMARYBUFFER;
        hr = m_pIDS->CreateSoundBuffer(&dsbd, &m_pPrimaryDSB, NULL);
        if(hr == DS_OK) 
		{
            hr = m_pPrimaryDSB->SetFormat(pwfx);
			if(hr != DS_OK)
            {
                m_pPrimaryDSB->Release();
                m_pPrimaryDSB = NULL;
				return FALSE;
            }

			// Set play loop of primary DirectSound buffer.
			hr = m_pPrimaryDSB->Play(0, 0, DSBPLAY_LOOPING);
            if(hr != DS_OK)
			{
                m_pPrimaryDSB->Release();
                m_pPrimaryDSB = NULL;
				return FALSE;
            }
		}
		else
        {
			return FALSE;
		}
	}

	return TRUE;
}


void CSoundManager::ReleasePrimaryDSB(void)
{
	if(m_pPrimaryDSB)
	{
        m_pPrimaryDSB->Release();
        m_pPrimaryDSB = NULL;
	}
}


BOOL CSoundManager::CreateWorkThread(void)
{
	DWORD dwID;

	m_hExit = ::CreateEvent(NULL, TRUE, FALSE, NULL);
	
	m_hThead = ::CreateThread(NULL, 
			                  0, 
							  (LPTHREAD_START_ROUTINE)DoThreadFunc,
							  (void *)this,
							  0,
							  &dwID);


    if(m_hThead)
		return TRUE;
	else
		return FALSE;
}


void CSoundManager::DoTheadWorks(void)
{
	
    // Wait for the timer event
    HANDLE  hTimer = GetTimerHandle();	
	DWORD dwSignal;

    // Build the event array
    HANDLE Handles[] = {hTimer, m_hExit};

    // calculate the total number of handles
	const DWORD HandleNum = sizeof(Handles)/sizeof(HANDLE);

	BOOL  IsRun = TRUE;


	while(IsRun)
	{

		// wait for input from any handle
		dwSignal = ::WaitForMultipleObjects(HandleNum,
			                                Handles,
											FALSE,	
										    INFINITE);
        switch(dwSignal - WAIT_OBJECT_0)
		{
		    case 0:  // Timer event
				 TimerHandler();
				 break;
			case 1:  // Exit 
			     IsRun = FALSE;
				 break;
            default:
			     IsRun = FALSE;
				 break;
		}
	}
}


void CSoundManager::CloseWorkThread(void)
{
	if(m_hThead)
	{
		::SetEvent(m_hExit);

	    ::WaitForSingleObject(m_hThead, INFINITE);
		::CloseHandle(m_hThead);
		::CloseHandle(m_hExit);
	}
}


BOOL CSoundManager::Initialize(void)
{
	if(!CoInitializeDSound())
		return FALSE;

    if(!CreatePrimaryDSB())
	{
		CoUnInitializeDSound();
		return FALSE;
	}

	if(!StartTimer())
	{
		ReleasePrimaryDSB();
		CoUnInitializeDSound();
		return FALSE;
	}

	if(!CreateWorkThread())
	{
		KillTimer();
		ReleasePrimaryDSB();
		CoUnInitializeDSound();
		return FALSE;
	}

	return TRUE;
}


BOOL CSoundManager::LoadWaveFile(LPSTR szFileName, DWORD* pKey)
{
    ASSERT(m_pIDS != NULL && m_pPrimaryDSB != NULL);
	if(m_pIDS == NULL || m_pPrimaryDSB == NULL)
		return FALSE;
 
	if(!IsValidWaveFile(szFileName))
		return FALSE;

    CSoundData   *pSndData = NULL;
	BYTE         *pbData = NULL;
    WAVEFORMATEX *pwfx = NULL;  
    UINT         uiSize;   
    int          nError = 0;

	nError = NWaveIO::LoadWaveFile(szFileName, &uiSize, &pwfx, &pbData);

	if(nError != NWaveIO::ERR_NONE)
		return FALSE;

    ASSERT(pbData != NULL && pwfx != NULL);
	if(pbData == NULL && pwfx == NULL)
		return FALSE;

    pSndData = new CSoundData();
	ASSERT(pSndData != NULL);
    if(pSndData == NULL)
	{
        ::VirtualFree(pwfx, sizeof(WAVEFORMATEX) + pwfx->cbSize, MEM_DECOMMIT);
		::VirtualFree(pbData, uiSize, MEM_DECOMMIT);

		return FALSE;
	}	

	if(!pSndData->SetWaveData(pbData, pwfx, uiSize))
	{
        ::VirtualFree(pwfx, sizeof(WAVEFORMATEX) + pwfx->cbSize, MEM_DECOMMIT);
		pwfx = NULL;
		::VirtualFree(pbData, uiSize, MEM_DECOMMIT);
		pbData = NULL;

        delete pSndData;
		
		return FALSE;
	}

	if(!pSndData->CreateDSBuffer(m_pIDS))
	{
        delete pSndData; // pbData and pwfx will be released by
		                 // pSndData's destructor
		return FALSE;
	}

	if(!AddSound(pSndData, pKey))
	{
        delete pSndData; // pbData and pwfx will be released by
		                 // pSndData's destructor
		return FALSE;
	}

	return TRUE;
}


BOOL CSoundManager::AddSound(CSoundData* pSnd, DWORD* pKey)
{
	ASSERT(pSnd);

	if(!pSnd)
		return FALSE;

    m_Locker.Lock();
    
	DWORD refKey = m_dwRefKey;

	m_arrayDSnd.insert(make_pair(refKey, pSnd));
    *pKey = refKey;
    m_dwRefKey++;

    m_Locker.UnLock();

	return TRUE;
}


BOOL CSoundManager::StartPlay(DWORD dwKey)
{
    HRESULT hr;

    m_Locker.Lock();

	if(m_arrayDSnd.count(dwKey) > 0)
	{
		hr = m_arrayDSnd[dwKey]->StartDSBPlay();
		if(hr == S_OK)
			return TRUE;
		else
			return FALSE;
	}

    m_Locker.UnLock();

	return FALSE;
}


BOOL CSoundManager::StopPlay(DWORD dwKey)
{
    HRESULT hr;

    m_Locker.Lock();

	if(m_arrayDSnd.count(dwKey) > 0)
	{
		hr = m_arrayDSnd[dwKey]->StopDSBPlay();
		if(hr == S_OK)
			return TRUE;
		else
			return FALSE;
	}

    m_Locker.UnLock();

	return FALSE;
}


BOOL CSoundManager::RemoveSound(DWORD dwKey)
{
    m_Locker.Lock();

	if(m_arrayDSnd.count(dwKey) > 0)
	{
		if(m_arrayDSnd[dwKey]->IsPlaying())
            m_arrayDSnd[dwKey]->StopDSBPlay();
		
		delete m_arrayDSnd[dwKey];
		m_arrayDSnd.erase(dwKey);
	}

    m_Locker.UnLock();

    return TRUE;
}


void CSoundManager::PlayAllSound(void)
{
	DSoundArray::iterator  iterCount;

    m_Locker.Lock();

	if(!m_arrayDSnd.empty())         
	{
	    for(iterCount = m_arrayDSnd.begin(); 
		    iterCount != m_arrayDSnd.end(); 
			iterCount++)
		{
            ((*iterCount).second)->StartDSBPlay();
		}
	}	
    
	m_Locker.UnLock();

}


void CSoundManager::StopAllSound(void)
{
	DSoundArray::iterator  iterCount;

    m_Locker.Lock();

	if(!m_arrayDSnd.empty())         
	{
	    for(iterCount = m_arrayDSnd.begin(); 
		    iterCount != m_arrayDSnd.end(); 
			iterCount++)
		{
            ((*iterCount).second)->StopDSBPlay();
		}
	}	

    m_Locker.UnLock();

}


void CSoundManager::RemoveAllSound(void)
{
	DSoundArray::iterator  iterCount;

    m_Locker.Lock();

	if(!m_arrayDSnd.empty())         
	{
	    for(iterCount = m_arrayDSnd.begin(); 
		    iterCount != m_arrayDSnd.end(); 
			iterCount++)
		{
            ((*iterCount).second)->StopDSBPlay();
		    delete (*iterCount).second;  
		}
        m_arrayDSnd.clear();
	}	

	m_dwRefKey = 0;
    
	m_Locker.UnLock();
}


BOOL CSoundManager::GetVolume(DWORD dwKey, LONG* pVol)
{
    BOOL bResult = FALSE;

    m_Locker.Lock();

	if(m_arrayDSnd.count(dwKey) > 0)
	{
		bResult = m_arrayDSnd[dwKey]->GetVolume(pVol);
	}

    m_Locker.UnLock();

	return bResult;
}


BOOL CSoundManager::SetVolume(DWORD dwKey, LONG vol)
{
    BOOL bResult = FALSE;

    m_Locker.Lock();

	if(m_arrayDSnd.count(dwKey) > 0)
	{
		bResult = m_arrayDSnd[dwKey]->SetVolume(vol);
	}

    m_Locker.UnLock();

	return bResult;
}


BOOL CSoundManager::GetFrequency(DWORD dwKey, DWORD* pFreq)
{
    BOOL bResult = FALSE;

    m_Locker.Lock();
	
	if(m_arrayDSnd.count(dwKey) > 0)
	{
		bResult = m_arrayDSnd[dwKey]->GetFrequency(pFreq);
	}

    m_Locker.UnLock();

	return bResult;
}


BOOL CSoundManager::SetFrequency(DWORD dwKey, DWORD dwFreq)
{
    BOOL bResult = FALSE;

    m_Locker.Lock();

	if(m_arrayDSnd.count(dwKey) > 0)
	{
		bResult = m_arrayDSnd[dwKey]->SetFrequency(dwFreq);
	}

    m_Locker.UnLock();

	return bResult;
}


BOOL CSoundManager::GetPan(DWORD dwKey, LONG* pGain)
{
    BOOL bResult = FALSE;

    m_Locker.Lock();

	if(m_arrayDSnd.count(dwKey) > 0)
	{
		bResult = m_arrayDSnd[dwKey]->GetPan(pGain);
	}

    m_Locker.UnLock();

	return bResult;
}


BOOL CSoundManager::SetPan(DWORD dwKey, LONG lGain)
{
    BOOL bResult = FALSE;

    m_Locker.Lock();

	if(m_arrayDSnd.count(dwKey) > 0)
	{
		bResult = m_arrayDSnd[dwKey]->SetPan(lGain);
	}

    m_Locker.UnLock();

	return bResult;
}


BOOL CSoundManager::GetCurrentPosition(DWORD dwKey, 
									   DWORD* lpCurPlay, 
									   DWORD* lpCurWrite)
{
    BOOL bResult = FALSE;

    m_Locker.Lock();

	if(m_arrayDSnd.count(dwKey) > 0)
	{
		bResult = 
			m_arrayDSnd[dwKey]->GetCurrentPosition(lpCurPlay, 
			                                      lpCurWrite);
	}
   
	m_Locker.UnLock();

	return bResult;
}


BOOL CSoundManager::SetCurrentPosition(DWORD dwKey, DWORD dwNewPos)
{
    BOOL bResult = FALSE;

    m_Locker.Lock();

	if(m_arrayDSnd.count(dwKey) > 0)
	{
		bResult = 
			m_arrayDSnd[dwKey]->SetCurrentPosition(dwNewPos);
	}

    m_Locker.UnLock();

	return bResult;
}


BOOL CSoundManager::GetVolumeMode(DWORD dwKey, VOLUMEMODE* pVMode)
{
    m_Locker.Lock();

	if(m_arrayDSnd.count(dwKey) > 0)
	{
		*pVMode = m_arrayDSnd[dwKey]->GetVolumeMode();
        m_Locker.UnLock();
		return TRUE;
	}

    m_Locker.UnLock();

	return FALSE;
}


BOOL CSoundManager::SetVolumeMode(DWORD dwKey, VOLUMEMODE VMode)
{
    m_Locker.Lock();

	if(m_arrayDSnd.count(dwKey) > 0)
	{
		m_arrayDSnd[dwKey]->SetVolumeMode(VMode);
        m_Locker.UnLock();
		return TRUE;
	}

    m_Locker.UnLock();
	return FALSE;
}


BOOL CSoundManager::GetPlayMode(DWORD dwKey, PLAYMODE* pPMode)
{
    m_Locker.Lock();

	if(m_arrayDSnd.count(dwKey) > 0)
	{
		*pPMode = m_arrayDSnd[dwKey]->GetPlayMode();
        m_Locker.UnLock();
		return TRUE;
	}

    m_Locker.UnLock();
	return FALSE;
}


BOOL CSoundManager::SetPlayMode(DWORD dwKey, PLAYMODE PMode)
{
    m_Locker.Lock();

	if(m_arrayDSnd.count(dwKey) > 0)
	{
		m_arrayDSnd[dwKey]->SetPlayMode(PMode);
        m_Locker.UnLock();
		return TRUE;
	}

    m_Locker.UnLock();
	return FALSE;
}


BOOL CSoundManager::SetVolParas(DWORD dwKey, LONG volLow, 
								LONG volNormal, LONG volStep)
{
    m_Locker.Lock();

	if(m_arrayDSnd.count(dwKey) > 0)
	{
		m_arrayDSnd[dwKey]->SetVolParas(volLow, volNormal, volStep);
        m_Locker.UnLock();
		return TRUE;
	}

    m_Locker.UnLock();
	return FALSE;
}


BOOL CSoundManager::GetDSBStatus(DWORD dwKey, DWORD* pStatus)
{
    HRESULT hr;

    m_Locker.Lock();
	if(m_arrayDSnd.count(dwKey) > 0)
	{
        hr = m_arrayDSnd[dwKey]->GetDSBStatus(pStatus);
		if(hr == S_OK)
		{
            m_Locker.UnLock();
			return TRUE;
		}
	}

    m_Locker.UnLock();

	return FALSE;
}


BOOL CSoundManager::IsPlaying(DWORD dwKey, BOOL* pPlay)
{
    BOOL  bOK = FALSE;

    m_Locker.Lock();
	if(m_arrayDSnd.count(dwKey) > 0)
	{
		*pPlay = FALSE;
        *pPlay = m_arrayDSnd[dwKey]->IsPlaying();
		bOK = TRUE;
	}

    m_Locker.UnLock();

	return bOK;
}


HANDLE CSoundManager::GetTimerHandle(void)
{
	return m_hTimer;
}


BOOL CSoundManager::SetTimer(int iTime, TIME_TYPE tType)
{
    if(tType == TT_SECOND)
        m_liDueTime.QuadPart = (ULONGLONG)(-1)*abs(iTime * 1000000);
	else if(tType == TT_MILLISECOND)
        m_liDueTime.QuadPart = (ULONGLONG)(-1)*abs(iTime * 1000);
	else if(tType == TT_NANOSECOND)
        m_liDueTime.QuadPart = (ULONGLONG)(-1)*abs(iTime); 
	
	StopTimer();

	if(StartTimer())
		return TRUE;
	else
		return FALSE;
}


BOOL CSoundManager::StartTimer(void)
{
	if(m_hTimer == NULL)
		return FALSE;

	if(m_liDueTime.QuadPart == 0)
		return FALSE;

	BOOL bOK;

	bOK = ::SetWaitableTimer(m_hTimer, 
		                     &m_liDueTime, 
				             0, 
		                     NULL,		
					         NULL,		
					         FALSE);	

	return bOK;
}


BOOL CSoundManager::StopTimer(void)
{
	if(m_hTimer == NULL)
		return FALSE;

	if(m_liDueTime.QuadPart == 0)
		return FALSE;

	BOOL bOK;

    bOK = ::CancelWaitableTimer(m_hTimer);	

	return bOK;
}


BOOL CSoundManager::KillTimer(void)
{
	if(m_hTimer == NULL)
		return TRUE;

    StopTimer();

	if(::CloseHandle(m_hTimer))
	{
	    m_hTimer = NULL;
		return TRUE;
	}
	else
	{
	    return FALSE;
	}
}


BOOL CSoundManager::IsValidWaveFile(LPSTR pszFileName)
{
    BOOL            fReturn     = FALSE;
    int             nError      = 0;
    HMMIO           hmmio;
    MMCKINFO        mmck;
    WAVEFORMATEX    *pwfx;

	nError = NWaveIO::OpenReadWaveFile(pszFileName, &hmmio, &pwfx, &mmck);

    if (nError != NWaveIO::ERR_NONE)
    {       
        return FALSE;
    }

    NWaveIO::CloseReadWaveFile(&hmmio, &pwfx);

    return TRUE;
}


void CSoundManager::TimerHandler(void)
{
	DSoundArray::iterator  iterCount;
	
	StopTimer();

    if(!m_arrayDSnd.empty())         
	{
	    CSoundData* pSnd;
        DWORD       dwKey;
        DWORD       dwStatus; 
        HRESULT     hr;


	    for(iterCount = m_arrayDSnd.begin(); 
		    iterCount != m_arrayDSnd.end(); 
			iterCount++)
		{
            pSnd = (*iterCount).second;
            dwKey = (*iterCount).first;
            // Check and set volume, if fade-in or fade-out
            switch(pSnd->GetVolumeMode())
			{
			    case VMODE_FADEIN:
					 pSnd->IncrementVolume();
					 break; 
				case VMODE_FADEOUT:
					 pSnd->DecrementVolume();
					 break;
				default:
					 break;
			}

			hr = pSnd->GetDSBStatus(&dwStatus);
			
			//If failed, go to next
			if(FAILED(hr))
				continue;
             
			// If the sound data play over, restore it.
			if(dwStatus & DSBSTATUS_BUFFERLOST) 
			{
                pSnd->RestoreBuffer();
			}
			hr = pSnd->GetDSBStatus(&dwStatus);
	
			
			//If failed, go to next
			if(FAILED(hr))
				continue;

			// Tell the user that this one is end and can be stopped
            if(!(dwStatus & DSBSTATUS_BUFFERLOST))
			{
                if((pSnd->IsPlaying()) && 
				   (!(dwStatus & DSBSTATUS_PLAYING)))
				{
					if(pSnd->StopDSBPlay() == S_OK)
					{
					   ::SendMessage(m_hWndPlay, WM_DSBPLAYEND, (LPARAM)dwKey, 0);
					}
				}
			}
		}
	}	
	StartTimer();
}