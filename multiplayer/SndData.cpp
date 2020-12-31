// SndData.cpp: implementation of the CSoundData class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SndData.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSoundData::CSoundData()
{
	m_pbData = NULL; 
    m_uiSize = 0;
    m_pwfx = NULL;   

    m_enuPlayMode = PMODE_WAIT;  
    m_enuVolMode = VMODE_NORMAL;        

    m_pDSBuffer = NULL;      
    
	m_bPlaying = FALSE;       

    m_lVolLow = VOL_LOW;
	m_lVolNormal = VOL_NORMAL;
	m_lVolStep = VOL_STEP;

}


CSoundData::~CSoundData()
{
	if(m_pwfx)
	{
		DWORD dwSize = m_pwfx->cbSize;
        ::VirtualFree(m_pwfx, sizeof(WAVEFORMATEX) + dwSize, MEM_DECOMMIT);
		m_pwfx = NULL;
	}	
    if(m_pbData)
	{
		::VirtualFree(m_pbData, m_uiSize, MEM_DECOMMIT);
		m_pbData = NULL;
	}
    if(m_pDSBuffer)
    {
        m_pDSBuffer->Release();
        m_pDSBuffer = NULL; 
    }
}


BOOL CSoundData::IsWorkable(void)
{
	return (m_pwfx && m_pbData && m_pDSBuffer);
}


void CSoundData::ReleaseWaveData(void)
{
	if(m_pwfx)
	{
		DWORD dwSize = m_pwfx->cbSize;
        ::VirtualFree(m_pwfx, sizeof(WAVEFORMATEX) + dwSize, MEM_DECOMMIT);
		m_pwfx = NULL;
	}	
    if(m_pbData)
	{
		::VirtualFree(m_pbData, m_uiSize, MEM_DECOMMIT);
		m_pbData = NULL;
	}
 	
}


void CSoundData::SetVolumeMode(VOLUMEMODE volmode)
{
    m_enuVolMode = volmode;  

	if(m_pDSBuffer)
	{
		LONG  ds_volume;
	    if(m_enuVolMode == VMODE_FADEIN)
		    ds_volume = m_lVolLow;
	    else 
		    ds_volume = m_lVolNormal;

    	m_pDSBuffer->SetVolume(ds_volume);
	}
	
}


void CSoundData::SetPlayMode(PLAYMODE playmode)
{
    m_enuPlayMode = playmode;    

	if(m_pDSBuffer)
	{
        if(m_enuPlayMode == PMODE_LOOP) 
		{
            m_pDSBuffer->Play(0, 0, DSBPLAY_LOOPING);
        } 
		else 
		{
            m_pDSBuffer->Play(0, 0, 0);
        }
	}
}


VOLUMEMODE CSoundData::GetVolumeMode(void)
{
    return m_enuVolMode;        
}


PLAYMODE CSoundData::GetPlayMode(void)
{
    return m_enuPlayMode;    
}


void CSoundData::SetVolParas(LONG volLow, LONG volNormal, LONG volStep)
{
    m_lVolLow = volLow;
	m_lVolNormal = volNormal;
	m_lVolStep = volStep;
}


HRESULT CSoundData::SetWaveFormat(WAVEFORMATEX *pwfx)
{
	HRESULT hr = m_pDSBuffer->SetFormat(pwfx);
    
	return hr;
}


BOOL CSoundData::SetWaveData(BYTE *pbData, 
							 WAVEFORMATEX *pwfx, 
							 UINT uiSize)
{
	if(m_pwfx)
	{
		DWORD dwSize = m_pwfx->cbSize;
        ::VirtualFree(m_pwfx, sizeof(WAVEFORMATEX) + dwSize, MEM_DECOMMIT);
		m_pwfx = NULL;
	}	
    if(m_pbData)
	{
		::VirtualFree(m_pbData, m_uiSize, MEM_DECOMMIT);
		m_pbData = NULL;
	}
	m_pbData = pbData; 
    m_pwfx = pwfx;   
    m_uiSize = uiSize;
	
	return TRUE;
}


BOOL CSoundData::CreateDSBuffer(LPDIRECTSOUND pDS)
{
	if(!(m_pwfx && m_pbData))
         return FALSE; 

	if(m_pDSBuffer)
         return FALSE; 

    DSBUFFERDESC    dsbd;
    HRESULT         hr;
    BYTE            *pbData         = NULL;
    BYTE            *pbData2        = NULL;
    DWORD           dwLength;
    DWORD           dwLength2;
    CException	    except(FALSE);

    // Set up the direct sound buffer. 
    memset(&dsbd, 0, sizeof(DSBUFFERDESC));
    dsbd.dwSize  = sizeof(DSBUFFERDESC);
    dsbd.dwFlags = 0;
    dsbd.dwFlags |= DSBCAPS_STATIC;
    dsbd.dwFlags |= DSBCAPS_CTRLDEFAULT | DSBCAPS_GETCURRENTPOSITION2; 
    dsbd.dwFlags |= DSBCAPS_STICKYFOCUS;
    dsbd.dwFlags |= DSBCAPS_GLOBALFOCUS;
	
	dsbd.dwBufferBytes = m_uiSize;
    dsbd.lpwfxFormat   = m_pwfx;
    

	try
	{
		hr = pDS->CreateSoundBuffer(&dsbd, &m_pDSBuffer, NULL);

	    if(hr != S_OK)
		{
            throw &except;
		}

         // Lock the buffer, and copy the memory to it.
		hr = m_pDSBuffer->Lock(0, m_uiSize, (void**)&pbData, &dwLength,
                               (void**)&pbData2, &dwLength2, 0L);
        if(hr != S_OK)
		{
            throw &except;
		}

        ASSERT(pbData != NULL);
		// Copy the wave data to DirectSoundBuffer
        memcpy(pbData, m_pbData, m_uiSize);

        // Ok, now unlock the buffer, we don't need it anymore.
        hr = m_pDSBuffer->Unlock(pbData, m_uiSize, NULL, 0);
        if(hr != S_OK)
		{
            throw &except;
		}
        pbData = NULL;
		
		//Set volume
		LONG  ds_volume;
	    if(m_enuVolMode == VMODE_FADEIN)
		    ds_volume = m_lVolLow;
	    else 
		    ds_volume = m_lVolNormal;
    
		hr = m_pDSBuffer->SetVolume(ds_volume);
		if(hr != S_OK)
		{
            throw &except;
		}

        // Set Pan value
		hr = m_pDSBuffer->SetPan(PAN_DEFAULT);
		if (hr != S_OK)
		{
            throw &except;
		}


		m_enuPlayMode = PMODE_PLAY;
	}
	catch(CException * pException)
	{
        if(pbData != NULL)
		{
            m_pDSBuffer->Unlock(pbData, m_uiSize, NULL, 0);
            pbData = NULL;
		}

        if(m_pDSBuffer != NULL)
		{
            m_pDSBuffer->Release();
            m_pDSBuffer = NULL;
		}
		pException->Delete();
	}    

    return (hr == S_OK); 
}


void CSoundData::ReleaseDSBuffer(void)
{
    if(m_pDSBuffer != NULL)
	{
        m_pDSBuffer->Release();
        m_pDSBuffer = NULL;
	}
}


BOOL CSoundData::GetVolume(LONG* pVol)
{
	if(!IsWorkable())
		return FALSE;

	BOOL bOK;

	if(m_pDSBuffer->GetVolume(pVol) != DS_OK)
		bOK = FALSE;
	else
	    bOK = TRUE;

	return bOK;
}
	

BOOL CSoundData::SetVolume(LONG vol)
{
	if(!IsWorkable())
		return FALSE;

	LONG lData = LIMIT(vol, m_lVolLow, m_lVolNormal);

	m_pDSBuffer->SetVolume(lData);
	
	return TRUE;
}


BOOL CSoundData::IncrementVolume(void)
{
	if(!IsWorkable())
		return FALSE;

	if(!m_bPlaying)
		return TRUE;

	BOOL bOK;
	LONG Vol = 0;

	if(m_pDSBuffer->GetVolume(&Vol) != DS_OK)
		bOK = FALSE;
	else
	    bOK = TRUE;

	if(bOK)
	{
	    Vol += m_lVolStep;

	    if(Vol > m_lVolNormal)
            Vol = m_lVolNormal;

	    m_pDSBuffer->SetVolume(Vol);
	}

	return bOK;
}


BOOL CSoundData::DecrementVolume(void)
{
	if(!IsWorkable())
		return FALSE;

	if(!m_bPlaying)
		return TRUE;

	BOOL bOK;
	LONG Vol = 0;

	if(m_pDSBuffer->GetVolume(&Vol) != DS_OK)
		bOK = FALSE;
	else
	    bOK = TRUE;

	if(bOK)
	{
	    Vol -= m_lVolStep;

	    if(Vol < m_lVolLow)
            Vol = m_lVolLow;

	    m_pDSBuffer->SetVolume(Vol);
	}

	return bOK;
}


BOOL CSoundData::SetDefaultVolume(void)
{
	if(!IsWorkable())
		return FALSE;

    m_pDSBuffer->SetVolume(m_lVolNormal);

	return TRUE;
}


BOOL CSoundData::GetFrequency(DWORD* pFreq)
{
	if(!IsWorkable())
		return FALSE;

	BOOL bOK;

	if(m_pDSBuffer->GetFrequency(pFreq) != DS_OK)
		bOK = FALSE;
	else
	    bOK = TRUE;

	return bOK;
}


BOOL CSoundData::SetFrequency(DWORD dwFreq)
{
	if(!IsWorkable())
		return FALSE;

	BOOL bOK;

	DWORD dwData = LIMIT(dwFreq, DSBFREQUENCY_MIN, DSBFREQUENCY_MAX);  

	if(m_pDSBuffer->SetFrequency(dwData) != DS_OK)
		bOK = FALSE;
	else
	    bOK = TRUE;

	return bOK;
}


BOOL CSoundData::GetPan(LONG* pGain)
{
	if(!IsWorkable())
		return FALSE;

	BOOL bOK;

	if(m_pDSBuffer->GetPan(pGain) != DS_OK)
		bOK = FALSE;
	else
	    bOK = TRUE;

	return bOK;
}


BOOL CSoundData::SetPan(LONG lGain)
{
	if(!IsWorkable())
		return FALSE;

	BOOL bOK;

	LONG lData = LIMIT(lGain, DSBPAN_LEFT, DSBPAN_RIGHT);  
	if(m_pDSBuffer->SetPan(lData) != DS_OK)
		bOK = FALSE;
	else
	    bOK = TRUE;

	return bOK;
}


BOOL CSoundData::GetCurrentPosition(DWORD* lpCurPlay, DWORD* lpCurWrite)
{
	if(!IsWorkable())
		return FALSE;

	BOOL bOK;

	if(m_pDSBuffer->GetCurrentPosition(lpCurPlay, lpCurWrite) != DS_OK)
		bOK = FALSE;
	else
	    bOK = TRUE;

	return bOK;
}


BOOL CSoundData::SetCurrentPosition(DWORD dwNewPos)
{
	if(!IsWorkable())
		return FALSE;

	BOOL bOK;

	if(m_pDSBuffer->SetCurrentPosition(dwNewPos) != DS_OK)
		bOK = FALSE;
	else
	    bOK = TRUE;

	return bOK;
}


HRESULT CSoundData::GetDSBStatus(DWORD* pStatus)
{
	if(!IsWorkable())
		return E_FAIL;

    HRESULT hr;

	hr = m_pDSBuffer->GetStatus(pStatus);

	return hr;
}


BOOL CSoundData::RestoreBuffer(void)
{
	if(!IsWorkable())
		return FALSE;

	LPBYTE  pbData;
	LPBYTE  pbData2;
    DWORD   dwLen;
	DWORD   dwLen2;
    BOOL    bOK;
	HRESULT hr;
    
	bOK = FALSE;
	pbData = NULL;
	pbData2 = NULL;
    hr = m_pDSBuffer->Restore();

    if(hr == DS_OK) 
	{
        // Lock the buffer. 
       hr = m_pDSBuffer->Lock(0, m_uiSize, (void**)&pbData, 
		    &dwLen, (void**)&pbData2, &dwLen2, 0);

	   if(hr == DS_OK) 
       {
           ASSERT(pbData != NULL);
           ASSERT(m_pbData != NULL);
           
		   //Copy the buffer
		   memcpy(pbData, m_pbData, m_uiSize);

		   //Unlock the buffer
           hr = m_pDSBuffer->Unlock(pbData, dwLen, NULL, 0);

           if(hr == DS_OK) 
		   {
			   //This is playing
               if(m_bPlaying) 
			   {
                   if(m_enuPlayMode == PMODE_LOOP) 
				   {
                       m_pDSBuffer->Play(0, 0, DSBPLAY_LOOPING);
                   } 
				   else 
				   {
                       m_pDSBuffer->Play(0, 0, 0);
                   }
               }
			   bOK = TRUE;
		   }
	   }
 
	}

	return bOK;
}


HRESULT CSoundData::StartDSBPlay(void)
{
	if(!IsWorkable())
		return E_FAIL;
    
	HRESULT     hr;
    DWORD       dwLooped;
    DWORD       dwStatus;

	hr = S_OK;
    dwLooped = 0;

    if(m_enuPlayMode == PMODE_LOOP) 
	{
        dwLooped = DSBPLAY_LOOPING;
    }

	hr = m_pDSBuffer->GetStatus(&dwStatus);
    if(hr == DS_OK)
    {
        if((dwStatus & DSBSTATUS_PLAYING) == DSBSTATUS_PLAYING)
        {
            // If is playing, restart
            hr = m_pDSBuffer->SetCurrentPosition(0);
			if(hr != DS_OK)
            {
	            return hr;
            }
        }
    }

	hr = m_pDSBuffer->Play(0, 0, dwLooped);
    if(hr == DS_OK)
    {
        m_bPlaying = TRUE;
    }


	return hr;
}


HRESULT CSoundData::StopDSBPlay(void)
{
	if(!IsWorkable())
		return E_FAIL;
    
	HRESULT hr = S_OK;

    if(!m_bPlaying)
       return S_OK;
       
	// Stop sound here...
	hr = m_pDSBuffer->Stop();
    if(hr == DS_OK) 
    {
        m_bPlaying = FALSE;
    }
    
	return hr;
}


BOOL CSoundData::IsPlaying(void)
{
	return m_bPlaying;
}

