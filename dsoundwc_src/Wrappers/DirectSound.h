// Copyright (C) 2004-2006,July  Arman Sahakyan

// Updated at October/2004 by Arman Sahakyan.
// As it was in the past, now also is in use DirectSound 
// (I mean - 1st version). But added a few functionality.
// In addition, class name 'CDirectSound' has been changed for
// 'CDSound' and class name 'CDSSound' has been changed for
// 'CDSoundPlay'.


#ifndef __MODULE_USER_ARM_S__2004_7_5_22_14__MSKW__DIRECTSOUND_H_
#define __MODULE_USER_ARM_S__2004_7_5_22_14__MSKW__DIRECTSOUND_H_

// Note: 'wave.h' (by Arman) is in VC98 Include directory and
// 'wave.cpp' in WaveLib.dll (by Arman), which is in 
// SYSTEM32 directory. 
// Note: 'wave.h' must be first in these includes.
// Attantion: You must link with WaveLib.lib library
#include "wave.h"

// Attantion: You must link with dsound.lib library
#include <DSound.h>
#include <AtlBase.h>
#include <AfxMt.h>

namespace DirectSound
{
//////////////////////// Definations ////////////////////////

// DirectX 7.0 compatibility
#ifndef DSBCAPS_CTRLDEFAULT
#define DSBCAPS_CTRLDEFAULT (DSBCAPS_CTRLFREQUENCY | DSBCAPS_CTRLPAN | DSBCAPS_CTRLVOLUME )
#endif

// For our convenience
#define DSBCAPS_REGULAR (DSBCAPS_CTRLDEFAULT | DSBCAPS_STATIC | DSBCAPS_LOCSOFTWARE)
// DSBCAPS_CTRL3D 

#define DSOUND_ERR -1;

/////////////////////////// Macros //////////////////////////

#define DSVOLUME_TO_DB(volume) ((DWORD)(-30 * (100 - volume)))

/////////////////////////////////////////////////////////////

class CDSound
{
	CComPtr<IDirectSound8> m_pDirectSound;
public:
	CDSound();
	~CDSound();
	void Destroy() { m_pDirectSound = NULL; }

	BOOL Create();
	BOOL SetCooperativeLevel(HWND hWnd, DWORD dwLevel = DSSCL_NORMAL);

	operator LPDIRECTSOUND8 () { return m_pDirectSound; }
	LPDIRECTSOUND8 operator -> () { return m_pDirectSound; }
};

class CDSBuffer
{
	CComPtr<IDirectSoundBuffer8> m_pDSBuffer;
	CComPtr<IDirectSound8> m_pDirectSound;
	CComPtr<IDirectSoundNotify8> m_pDSNotify;
	UINT m_uIDRcsrWave;
	DWORD m_dwFlags; // Create flags
public:
	CDSBuffer();
	~CDSBuffer();
	void Destroy() {
		m_pDirectSound = NULL;
		m_pDSBuffer = NULL;
		m_pDSNotify = NULL;
	}

	BOOL Create(IDirectSound8 * pDirectSound, UINT uIDRscrWave, DWORD dwFlags, HMODULE hMod = AfxGetInstanceHandle());
	BOOL Create(IDirectSound8 * pDirectSound, LPCTSTR lpszFileName, DWORD dwFlags);
	BOOL Create(IDirectSound8 * pDirectSound, const CWave &wave, DWORD dwFlags);
	BOOL Restore();

	LPDIRECTSOUNDNOTIFY8 GetDSNotify() { return m_pDSNotify; }

	LPDIRECTSOUNDBUFFER8 operator -> () { return m_pDSBuffer; }
};

//----------------------------------------- CDSoundPlay
//This class represents an high level interface for sound playing.
class CDSoundPlay
{
	CDSound *m_pDirectSound; // points to an outer object
	UINT m_uIDRsrcWave;
	mutable CDSBuffer m_DSBuffer;

public:
	// - CONSTRUCTION MANAGEMENT -
	CDSoundPlay();
	~CDSoundPlay();
	void Destroy();
	BOOL Create(CDSound *pDSound, UINT uIDRsrcWave, DWORD dwFlags = DSBCAPS_REGULAR, HMODULE hMod = AfxGetInstanceHandle());
	BOOL Create(CDSound *pDSound, LPCTSTR lpszFileName, DWORD dwFlags = DSBCAPS_REGULAR);


	// - PLAY MANAGEMENT -
	// returns current play position
	DWORD GetCurrentPosition(LPDWORD lpdwCurrentWriteCursor) const;
	BOOL Play(BOOL bLooping = FALSE); // or - !DSBPLAY_LOOPING
	BOOL SetCurrentPosition(DWORD dwNewPosition);
	BOOL Stop();


	// - SOUND MANAGEMENT -
	DWORD GetFrequency() const;
	LONG GetPan() const;
	LONG GetVolume() const;

	// New frequency, in hertz (Hz), at which to play the audio samples. 
	// The value must be in the range DSBFREQUENCY_MIN to DSBFREQUENCY_MAX
	BOOL SetFrequency(DWORD dwFrequancy);

	// The value in lPan is measured in hundredths of a decibel (dB),
	//	 in the range of DSBPAN_LEFT to DSBPAN_RIGHT
	BOOL SetPan(LONG lPan);

	// The volume is specified in hundredths of decibels (dB). 
	// Allowable values are between DSBVOLUME_MAX (no attenuation)
	// and DSBVOLUME_MIN (silence). 
	BOOL SetVolume(LONG lVolume);

	
	// - STATUS MANAGEMENT -
	// Returns a combination of the following flags.
	// DSBSTATUS_BUFFERLOST,	DSBSTATUS_LOOPING,		DSBSTATUS_PLAYING, 
	// DSBSTATUS_LOCSOFTWARE,	DSBSTATUS_LOCHARDWARE,	DSBSTATUS_TERMINATED
	DWORD GetStatus() const;

	// The following are a few separate variations of GetStatus.
	BOOL IsPlaying() const { return DSBSTATUS_PLAYING == (DSBSTATUS_PLAYING & GetStatus()); } // FALSE means STOPPED
	BOOL IsLooping() const { return DSBSTATUS_LOOPING == (DSBSTATUS_LOOPING & GetStatus()); }
	BOOL IsBufferLost() const { return DSBSTATUS_BUFFERLOST == (DSBSTATUS_BUFFERLOST & GetStatus()); }

	// Restores the memory allocation for a lost sound buffer.
	BOOL Restore() { return m_DSBuffer.Restore(); }


	// - NOTIFICATION MANAGEMENT -
	// Typedefs a pointer to callback function
	typedef LONG (*PNOTIFYFUNC) (LONG );

	void SetNotifyFunction(PNOTIFYFUNC pfn) { 
		ASSERT(pfn || !pfn && !m_pThread); // No thread should be running when pfn is NULL
		m_pFunc = pfn; 
	}

	// Returns FALSE if called during playback or in case of invalid 
	// parameter or lack of memory. If dwOffsets is NULL, the waiting
	// thread (and thus notifications if any) will be canceled.
	BOOL SetNotificationPositions(DWORD dwOffsets[], SIZE_T nSize);

private:
	// Don't bother with these stuff.
	PNOTIFYFUNC m_pFunc;
	HANDLE *m_phEvents;
	HANDLE m_hEventThreadStop;
	typedef struct _INFO
	{
		HANDLE *hEvents;
		DWORD *dwOffsets;
		SIZE_T nSize;
		PNOTIFYFUNC pFunc;
	} *PINFO;
	CWinThread *m_pThread;
	static UINT _ThreadProc(PVOID pParam);
};

} // namespace DirectSound

#endif // __MODULE_USER_ARM_S__2004_7_5_22_14__MSKW__DIRECTSOUND_H_

