#pragma once

#if _MSC_VER > 1000
#pragma once
#endif

typedef	HRESULT	(WINAPI *LPGETAUDIOSAMPLES_PROGRESS)(LPBYTE lpDesBuf, const DWORD dwRequiredSamples, DWORD &dwRetSamples, LPVOID lpData);

class CMyDirectSound  
{
public:
		
	CMyDirectSound();
	virtual ~CMyDirectSound();

	void SetFormat(WAVEFORMATEX WFE);
	void SetCallback(LPGETAUDIOSAMPLES_PROGRESS Function_Callback, LPVOID lpData);
	void Play();
	void Pause();
	void Stop();
	DWORD GetSamplesPlayed();	
	void TimerCallback();
	
private:
	
	//<DirectSound>
	WAVEFORMATEX m_WFE;
	LPDIRECTSOUND m_lpDS;
	LPDIRECTSOUNDBUFFER m_lpDSB;
	HANDLE m_pHEvent[2];
	//</DirectSound>

	//<Audio Buffer>
	LPBYTE m_lpAudioBuf;
	LPGETAUDIOSAMPLES_PROGRESS m_lpGETAUDIOSAMPLES;
	LPVOID m_lpData;
	//</Audio Buffer>

	//<Playing>
	MMRESULT m_timerID;
	DWORD m_dwCircles1;
	DWORD m_dwCircles2;
	int m_iDB;	
	//</Playing>

	//<Error Information>
	CString m_strLastError;
	//</Error Information>
};
//</CMyDirectSound  >