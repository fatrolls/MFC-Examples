// SndMan.h: interface for the CSoundManager class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SNDMAN_H__8ABA8958_6B51_43EE_9BB2_9AEBE34C1CBD__INCLUDED_)
#define AFX_SNDMAN_H__8ABA8958_6B51_43EE_9BB2_9AEBE34C1CBD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#pragma warning(disable:4786)

#include "SndData.h"
#include <map>		// STL map container

using namespace std;
 
typedef map<DWORD, CSoundData*>  DSoundArray; 

// Register the windows message ID for notify play window that
// one DS buffer's play is ended and can be stopped
static const WM_DSBPLAYEND = ::RegisterWindowMessage("WM_DSBPLAYEND");

//The time seeting type
enum TIME_TYPE {TT_SECOND, TT_MILLISECOND, TT_NANOSECOND};

class CSoundManager  
{
public:
	CSoundManager();
	virtual ~CSoundManager();

	BOOL CoInitializeDSound(void);
    void CoUnInitializeDSound(void);
	void SetHwnd(HWND hWnd);
    BOOL CreatePrimaryDSB(void);
	void ReleasePrimaryDSB(void);
	BOOL CreateWorkThread(void);
	void DoTheadWorks(void);
	void CloseWorkThread(void);
    BOOL Initialize(void);

    BOOL LoadWaveFile(LPSTR szFileName, DWORD* pKey);
	BOOL AddSound(CSoundData* pSnd, DWORD* pKey);
	BOOL StartPlay(DWORD dwKey);
    BOOL StopPlay(DWORD dwKey);
    BOOL RemoveSound(DWORD dwKey);
    void PlayAllSound(void);
    void StopAllSound(void);
    void RemoveAllSound(void);
    
    BOOL GetVolume(DWORD dwKey, LONG* pVol);
	BOOL SetVolume(DWORD dwKey, LONG vol);
	BOOL GetFrequency(DWORD dwKey, DWORD* pFreq);
	BOOL SetFrequency(DWORD dwKey, DWORD dwFreq);
    BOOL GetPan(DWORD dwKey, LONG* pGain);
	BOOL SetPan(DWORD dwKey, LONG lGain);
    BOOL GetCurrentPosition(DWORD dwKey, DWORD* lpCurPlay, DWORD* lpCurWrite);
	BOOL SetCurrentPosition(DWORD dwKey, DWORD dwNewPos);
    BOOL GetVolumeMode(DWORD dwKey, VOLUMEMODE* pVMode);
    BOOL SetVolumeMode(DWORD dwKey, VOLUMEMODE VMode);
	BOOL GetPlayMode(DWORD dwKey, PLAYMODE* pPMode);
	BOOL SetPlayMode(DWORD dwKey, PLAYMODE PMode);
	BOOL SetVolParas(DWORD dwKey, LONG volLow, LONG volNormal, LONG volStep);
    BOOL GetDSBStatus(DWORD dwKey, DWORD* pStatus);
    BOOL IsPlaying(DWORD dwKey, BOOL* pPlay);
	
	// Timer functions
	HANDLE GetTimerHandle(void);
	BOOL SetTimer(int iTime, TIME_TYPE tType);
	BOOL StartTimer(void);
	BOOL StopTimer(void);
	BOOL KillTimer(void);

    friend LONG WINAPI DoThreadFunc(void *pArg); 

protected:
    BOOL IsValidWaveFile(LPSTR pszFileName);
    void TimerHandler(void);

private:
	DSoundArray         m_arrayDSnd;    // Sound data array
    DWORD               m_dwRefKey;     // Reference key to manage the 
	                                    // sound data in array

    LPDIRECTSOUND       m_pIDS;         // The pointer of DirectSound
	                                    // interface
	LPDIRECTSOUNDBUFFER m_pPrimaryDSB;  // The primary DirectSoundBuffer
	HWND                m_hWndPlay;     // The window handle of playing
	                                 	// the sound
	HANDLE              m_hThead;       // The thread handle  
    HANDLE				m_hExit;	
 

	CSafeLocker         m_Locker;

// Waitable timer
private:
	HANDLE	            m_hTimer;       // Timer handle
	LARGE_INTEGER	    m_liDueTime;    // Time interval
};

#endif // !defined(AFX_SNDMAN_H__8ABA8958_6B51_43EE_9BB2_9AEBE34C1CBD__INCLUDED_)
