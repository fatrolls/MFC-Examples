#include "stdafx.h"
#include "MyDirectSound.h"
//#include "math.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//<CALLBACK Function>
void CALLBACK TimerProcess(UINT uTimerID, UINT uMsg, DWORD dwUser, DWORD dw1, DWORD dw2)
{
	CMyDirectSound *pDDS = (CMyDirectSound *)dwUser;
	pDDS->TimerCallback();	
}
//</TimerProc>

CMyDirectSound::CMyDirectSound()
{
	//<DirectSound>
	ZeroMemory(&m_WFE, sizeof(m_WFE));
	m_lpDS = NULL;
	m_lpDSB = NULL;
	m_pHEvent[0] = CreateEvent(NULL, FALSE, FALSE, _T("Direct_Sound_Buffer_Notify_0"));
	m_pHEvent[1] = CreateEvent(NULL, FALSE, FALSE, _T("Direct_Sound_Buffer_Notify_1"));	
	//</DirectSound>

	//<Audio Buffer>
	m_lpAudioBuf = NULL;
	m_lpGETAUDIOSAMPLES = NULL;
	m_lpData = NULL;
	//</Audio Buffer>
	
	//<Playing>
	m_dwCircles1 = 0;
	m_dwCircles2 = 0;
	//</Playing>	
}
//</CMyDirectSound>

CMyDirectSound::~CMyDirectSound()
{
	if (NULL != m_lpAudioBuf) {
		delete []m_lpAudioBuf;
		m_lpAudioBuf = NULL;
	}
}
//</~CMyDirectSound>

void CMyDirectSound::SetFormat(WAVEFORMATEX WFE)
{
	m_WFE = WFE;	

	//Create DirectSound
	if ( FAILED(DirectSoundCreate(NULL, &m_lpDS, NULL)) ) {
		OutputDebugString(_T("Create DirectSound Failed!"));
		m_strLastError = _T("MyDirectSound SetFormat Failed!");
		return;
	}

	//Set Cooperative Level
	HWND hWnd = GetForegroundWindow();
	if (hWnd == NULL)
	{
		hWnd = GetDesktopWindow();
	}
	
	if ( FAILED(m_lpDS->SetCooperativeLevel(hWnd, DSSCL_PRIORITY)) ) {
		OutputDebugString(_T("SetCooperativeLevel Failed"));
		m_strLastError = _T("MyDirectSound SetFormat Failed!");
		return;
	}

	//Create Primary Buffer 
	DSBUFFERDESC dsbd;
	ZeroMemory(&dsbd, sizeof(dsbd));
	dsbd.dwSize = sizeof(DSBUFFERDESC);
	dsbd.dwFlags = DSBCAPS_PRIMARYBUFFER;
	dsbd.dwBufferBytes = 0;
	dsbd.lpwfxFormat = NULL;

	LPDIRECTSOUNDBUFFER lpDSB = NULL;
	if ( FAILED(m_lpDS->CreateSoundBuffer(&dsbd, &lpDSB, NULL)) ) {
		OutputDebugString(_T("Create Primary Sound Buffer Failed!"));
		m_strLastError = _T("MyDirectSound SetFormat Failed!");
		return;
	}
	
	//Set Primary Buffer Format
	if ( FAILED(lpDSB->SetFormat(&m_WFE)) ) {
		OutputDebugString(_T("Set Primary Format Failed!"));
		m_strLastError = _T("MyDirectSound SetFormat Failed!");
		return;
	}
	
	//Create Second Sound Buffer
	dsbd.dwFlags = DSBCAPS_CTRLPOSITIONNOTIFY | DSBCAPS_GLOBALFOCUS;
	dsbd.dwBufferBytes = 2*m_WFE.nAvgBytesPerSec; //2 Seconds Buffer
	dsbd.lpwfxFormat = &m_WFE;

	if ( FAILED(m_lpDS->CreateSoundBuffer(&dsbd, &m_lpDSB, NULL)) ) {
		OutputDebugString(_T("Create Second Sound Buffer Failed!"));
		m_strLastError = _T("MyDirectSound SetFormat Failed!");
		return;
	}

	//Query DirectSoundNotify
	LPDIRECTSOUNDNOTIFY lpDSBNotify;
	if ( FAILED(m_lpDSB->QueryInterface(IID_IDirectSoundNotify, (LPVOID *)&lpDSBNotify)) ) {
		OutputDebugString(_T("QueryInterface DirectSoundNotify Failed!"));
		m_strLastError = _T("MyDirectSound SetFormat Failed!");
		return;
	}

	//Set Direct Sound Buffer Notify Position
	DSBPOSITIONNOTIFY pPosNotify[2];
	pPosNotify[0].dwOffset = m_WFE.nAvgBytesPerSec/2 - 1;
	pPosNotify[1].dwOffset = 3*m_WFE.nAvgBytesPerSec/2 - 1;		
	pPosNotify[0].hEventNotify = m_pHEvent[0];
	pPosNotify[1].hEventNotify = m_pHEvent[1];	

	if ( FAILED(lpDSBNotify->SetNotificationPositions(2, pPosNotify)) ) {
		OutputDebugString(_T("Set NotificationPosition Failed!"));
		m_strLastError = _T("MyDirectSound SetFormat Failed!");
		return;
	}	

	//New audio buffer
	if (NULL != m_lpAudioBuf) {
		delete []m_lpAudioBuf;
		m_lpAudioBuf = NULL;		
	}
	m_lpAudioBuf = new BYTE[m_WFE.nAvgBytesPerSec];

	//Init Audio Buffer
	memset(m_lpAudioBuf, 0, m_WFE.nAvgBytesPerSec);
}
//</SetFormat>

void CMyDirectSound::Play()
{
	//Check if the DirectSound was created successfully
	if (NULL == m_lpDS) {
		m_strLastError = _T("DirectSound was not created!");
		OutputDebugString(m_strLastError);		
		return;
	}

	//Check if the callback function is valid
	if (NULL == m_lpGETAUDIOSAMPLES) {
		m_strLastError = _T("Callback Function is NULL!");
		OutputDebugString(m_strLastError);		
		return;
	}

	//Check if SetFormat successfully
	if ( !m_strLastError.CompareNoCase(_T("MyDirectSound SetFormat Failed!")) ) {
		OutputDebugString(m_strLastError);
		return;
	}

	if (0 == m_dwCircles1) {
		
		//Get audio data by callback function
		DWORD dwRetSamples = 0, dwRetBytes = 0;
		m_lpGETAUDIOSAMPLES(m_lpAudioBuf, m_WFE.nSamplesPerSec, dwRetSamples, m_lpData);
		dwRetBytes = dwRetSamples*m_WFE.nBlockAlign;
		
		//Write the audio data to DirectSoundBuffer
		LPVOID lpvAudio1 = NULL, lpvAudio2 = NULL;
		DWORD dwBytesAudio1 = 0, dwBytesAudio2 = 0;	
		
		//Lock DirectSoundBuffer
		HRESULT hr = m_lpDSB->Lock(0, m_WFE.nAvgBytesPerSec, &lpvAudio1, &dwBytesAudio1, &lpvAudio2, &dwBytesAudio2, 0);
		if ( FAILED(hr) ) {
			m_strLastError = _T("Lock DirectSoundBuffer Failed!");
			OutputDebugString(m_strLastError);
			return;
		}
		
		//Init lpvAudio1
		if (NULL != lpvAudio1) {			
			memset(lpvAudio1, 0, dwBytesAudio1);			
		}
		
		//Init lpvAudio2
		if (NULL != lpvAudio2) {			
			memset(lpvAudio2, 0, dwBytesAudio2);			
		}

		//Copy Audio Buffer to DirectSoundBuffer
		if (NULL == lpvAudio2) {
			memcpy(lpvAudio1, m_lpAudioBuf, dwRetBytes);
		}
		else {
			memcpy(lpvAudio1, m_lpAudioBuf, dwBytesAudio1);
			memcpy(lpvAudio2, m_lpAudioBuf + dwBytesAudio1, dwBytesAudio2);
		}
		
		//Unlock DirectSoundBuffer
		m_lpDSB->Unlock(lpvAudio1, dwBytesAudio1, lpvAudio2, dwBytesAudio2);
	}

	
	//Beging Play
	m_lpDSB->Play(0, 0, DSBPLAY_LOOPING);

	//timeSetEvent
	m_timerID = timeSetEvent(300, 100, TimerProcess, (DWORD)this, TIME_PERIODIC | TIME_CALLBACK_FUNCTION);
}
//</Play>

void CMyDirectSound::Pause()
{
	if (NULL != m_lpDSB) {
		m_lpDSB->Stop();
		timeKillEvent(m_timerID);
	}
}
//</Pause>

void CMyDirectSound::Stop()
{
	if (NULL != m_lpDSB) {

		m_lpDSB->Stop();
		timeKillEvent(m_timerID);
		
		//Empty the buffer
		LPVOID lpvAudio1 = NULL;
		DWORD dwBytesAudio1 = 0;
		HRESULT hr = m_lpDSB->Lock(0, 0, &lpvAudio1, &dwBytesAudio1, NULL, NULL, DSBLOCK_ENTIREBUFFER);
		if ( FAILED(hr) ) {
			m_strLastError = _T("Lock entirebuffer failed! Stop Failed!");
			OutputDebugString(m_strLastError);
			return;
		}
		memset(lpvAudio1, 0, dwBytesAudio1);
		m_lpDSB->Unlock(lpvAudio1, dwBytesAudio1, NULL, NULL);

		//Move the current play position to begin
		m_lpDSB->SetCurrentPosition(0);	
		
		//Reset Event
		ResetEvent(m_pHEvent[0]);
		ResetEvent(m_pHEvent[1]);

		//Set Circles1 and Circles2 0
		m_dwCircles1 = 0;
		m_dwCircles2 = 0;
	}	
}
//</Stop>

DWORD CMyDirectSound::GetSamplesPlayed()
{
	if (NULL == m_lpDSB) {
		return 0;
	}

	//Get curren play position
	DWORD dwCurPlayPos = 0, dwCurPlaySample = 0;
	m_lpDSB->GetCurrentPosition(&dwCurPlayPos, NULL);
	dwCurPlaySample = dwCurPlayPos/m_WFE.nBlockAlign;

	//Caculate the samples played
	DWORD dwSamplesPlayed = 0;
	if (m_dwCircles2 < 1) {
		return dwCurPlaySample;
	}
	
	dwSamplesPlayed = (m_dwCircles2-1)*2*m_WFE.nSamplesPerSec + 3*m_WFE.nSamplesPerSec/2;		
	if (dwCurPlaySample > (3*m_WFE.nSamplesPerSec/2)) {

		if (m_dwCircles2 < m_dwCircles1) {

			dwSamplesPlayed = (m_dwCircles1-1)*2*m_WFE.nSamplesPerSec + 3*m_WFE.nSamplesPerSec/2;
		}

		dwSamplesPlayed += dwCurPlaySample - 3*m_WFE.nSamplesPerSec/2 + 1;				
	}
	else {
		
		dwSamplesPlayed += dwCurPlaySample + m_WFE.nSamplesPerSec/2;
	}

	CString strSamplesPlayed;
	strSamplesPlayed.Format(_T("Samples Played: %d \n"), dwSamplesPlayed);
	OutputDebugString(strSamplesPlayed);

	return dwSamplesPlayed;
}
//</GetSamplePlaying>

void CMyDirectSound::SetCallback(LPGETAUDIOSAMPLES_PROGRESS Function_Callback, LPVOID lpData)
{
	m_lpGETAUDIOSAMPLES = Function_Callback;
	m_lpData = lpData;
}
//</SetCallback>

void CMyDirectSound::TimerCallback()
{
	LPVOID lpvAudio1 = NULL, lpvAudio2 = NULL;
	DWORD dwBytesAudio1 = 0, dwBytesAudio2 = 0;
	DWORD dwRetSamples = 0, dwRetBytes = 0;

	HRESULT hr = WaitForMultipleObjects(2, m_pHEvent, FALSE, 0);
	if(WAIT_OBJECT_0 == hr) {

		m_dwCircles1++;

		//Lock DirectSoundBuffer Second Part
		HRESULT hr = m_lpDSB->Lock(m_WFE.nAvgBytesPerSec, m_WFE.nAvgBytesPerSec, &lpvAudio1, &dwBytesAudio1, &lpvAudio2, &dwBytesAudio2, 0);
		if ( FAILED(hr) ) {
			m_strLastError = _T("Lock DirectSoundBuffer Failed!");
			OutputDebugString(m_strLastError);
			return;
		}		
	}
	else if (WAIT_OBJECT_0 + 1 == hr) {		

		m_dwCircles2++;

		//Lock DirectSoundBuffer First Part
		HRESULT hr = m_lpDSB->Lock(0, m_WFE.nAvgBytesPerSec, &lpvAudio1, &dwBytesAudio1, &lpvAudio2, &dwBytesAudio2, 0);
		if ( FAILED(hr) ) {
			m_strLastError = _T("Lock DirectSoundBuffer Failed!");
			OutputDebugString(m_strLastError);
			return;
		}		
	}
	else {
		return;
	}

	//Get 1 Second Audio Buffer 
	m_lpGETAUDIOSAMPLES(m_lpAudioBuf, m_WFE.nSamplesPerSec, dwRetSamples, m_lpData);
	dwRetBytes = dwRetSamples*m_WFE.nBlockAlign;
	
	//If near the end of the audio data
	if (dwRetSamples < m_WFE.nSamplesPerSec) {
		DWORD dwRetBytes = dwRetSamples*m_WFE.nBlockAlign;
		memset(m_lpAudioBuf+dwRetBytes, 0, m_WFE.nAvgBytesPerSec - dwRetBytes);				
	}
	
	//Copy AudioBuffer to DirectSoundBuffer
	if (NULL == lpvAudio2) {
		memcpy(lpvAudio1, m_lpAudioBuf, dwBytesAudio1);
	}
	else {
		memcpy(lpvAudio1, m_lpAudioBuf, dwBytesAudio1);
		memcpy(lpvAudio2, m_lpAudioBuf + dwBytesAudio1, dwBytesAudio2);
	}
	
	//Unlock DirectSoundBuffer
	m_lpDSB->Unlock(lpvAudio1, dwBytesAudio1, lpvAudio2, dwBytesAudio2);
}
//</TimerCallback>
