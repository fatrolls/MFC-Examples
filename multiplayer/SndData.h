// SndData.h: interface for the CSoundData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SNDDATA_H__50DDF8AA_6B65_4233_A9A3_EF87D709AD9C__INCLUDED_)
#define AFX_SNDDATA_H__50DDF8AA_6B65_4233_A9A3_EF87D709AD9C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "NWaveio.h"
#include "SafeLocker.h"
#include <dsound.h>

#ifndef DSBCAPS_CTRLDEFAULT         
#define DSBCAPS_CTRLDEFAULT         0x000000E0  // Pan + volume + frequency.
#endif

#ifndef DSBCAPS_CTRLALL
#define DSBCAPS_CTRLALL             0x000000F0  // All control capabilities
#endif

#define VOL_LOW         -4000
#define VOL_NORMAL      0
#define VOL_STEP        200
#define PAN_DEFAULT     0

#define LIMIT(Data, Min, Max)     min(max((Data), (Min)), (Max))


enum VOLUMEMODE {VMODE_NORMAL, VMODE_FADEIN, VMODE_FADEOUT};
enum PLAYMODE {PMODE_WAIT, PMODE_PLAY, PMODE_LOOP};

class CSoundData  
{
public:
	CSoundData();
	virtual ~CSoundData();

	BOOL        IsWorkable(void);
    void        ReleaseWaveData(void);
    void        SetVolumeMode(VOLUMEMODE volmode);
    VOLUMEMODE  GetVolumeMode(void);
	void        SetPlayMode(PLAYMODE playmode);
	PLAYMODE    GetPlayMode(void);
	void        SetVolParas(LONG volLow, LONG volNormal, LONG volStep);
	HRESULT     SetWaveFormat(WAVEFORMATEX *pwfx);
    BOOL        SetWaveData(BYTE *pbData, WAVEFORMATEX *pwfx, UINT uiSize);
	BOOL        CreateDSBuffer(LPDIRECTSOUND pDS);
	void        ReleaseDSBuffer(void);
    BOOL        GetVolume(LONG* pVol);
	BOOL        SetVolume(LONG vol);
	BOOL        IncrementVolume(void);
	BOOL        DecrementVolume(void);
	BOOL        SetDefaultVolume(void);
	BOOL        GetFrequency(DWORD* pFreq);
	BOOL        SetFrequency(DWORD dwFreq);
    BOOL        GetPan(LONG* pGain);
	BOOL        SetPan(LONG lGain);
    BOOL        GetCurrentPosition(DWORD* lpCurPlay, DWORD* lpCurWrite);
	BOOL        SetCurrentPosition(DWORD dwNewPos);
    HRESULT     GetDSBStatus(DWORD* pStatus);
    BOOL        RestoreBuffer(void);
    HRESULT     StartDSBPlay(void);
    HRESULT     StopDSBPlay(void);
    BOOL        IsPlaying(void);

private:
	BYTE                *m_pbData;        // Pointer to actual data of file.
    WAVEFORMATEX        *m_pwfx;          // Pointer to waveformatex structure.
    UINT                m_uiSize;         // Size of data.
    PLAYMODE            m_enuPlayMode;    // Wait, Play or Looped?
    VOLUMEMODE          m_enuVolMode;        
    LPDIRECTSOUNDBUFFER m_pDSBuffer;      // Pointer to direct sound buffer.
    BOOL                m_bPlaying;       // Is this one playing?

    LONG                m_lVolLow;
	LONG                m_lVolNormal;
	LONG                m_lVolStep;
};

#endif // !defined(AFX_SNDDATA_H__50DDF8AA_6B65_4233_A9A3_EF87D709AD9C__INCLUDED_)
