#include "stdafx.h"

#include "AudioStream.h"
#include "FastFourierTransform.h"
#include "CriticalSection.h"
#include "IO.h"
#include "Stream.h"
#include "Thread.h"
#include "Utils.h"

#ifndef INCLUDE_BASICPLAYER
#define INCLUDE_BASICPLAYER

// pre-defined class
class CBasicPlayer;
class CSpectrumAnalyser;

/* constants used in direct sound */
#define DEFAULT_BUFFER_SIZE 88200
#define DEFAULT_SAMPLE_RATE 44100.0F
#define DEFAULT_FRAME_SIZE	4
#define DEFAULT_BITS_PER_SAMPLE	16
#define DEFAULT_CHANNELS	2
#define DEFAULT_SECONDS		2
#define DEFAULT_DS_BUFFER_SIZE	DEFAULT_SECONDS*DEFAULT_SAMPLE_RATE*(DEFAULT_BITS_PER_SAMPLE>>3)*DEFAULT_CHANNELS

/* constants used in digital signal process */
#define DEFAULT_WIDTH 300
#define DEFAULT_HEIGHT 180
#define DEFAULT_SAMPLE_SIZE 2048
#define DEFAULT_FPS 30
#define DEFAULT_SPECTRUM_ANALYSER_FFT_SAMPLE_SIZE 512
#define DEFAULT_SPECTRUM_ANALYSER_BAND_COUNT 30
#define DEFAULT_SPECTRUM_ANALYSER_DECAY 0.05F
#define DEFAULT_SPECTRUM_ANALYSER_PEAK_DELAY 5 /* the value is more lower, fall faster */
#define DEFAULT_SPECTRUM_ANALYSER_PEAK_DELAY_FPS_RATIO 0.4F
#define DEFAULT_SPECTRUM_ANALYSER_PEAK_DELAY_FPS_RATIO_RANGE 0.1F
#define MIN_SPECTRUM_ANALYSER_DECAY	0.02F
#define MAX_SPECTRUM_ANALYSER_DECAY 0.08F
#define SAMPLE_TYPE_EIGHT_BIT 1
#define SAMPLE_TYPE_SIXTEEN_BIT 2
#define CHANNEL_MODE_MONO 1
#define CHANNEL_MODE_STEREO 2

/************************************************************************/
/* CSystem                                                              */
/************************************************************************/
typedef __int64				jlong;
typedef unsigned int		juint;
typedef unsigned __int64	julong;
typedef long				jint;
typedef signed char			jbyte;

#define CONST64(x)				(x ## LL)
#define NANOS_PER_SEC			CONST64(1000000000)
#define NANOS_PER_MILLISEC		1000000

jlong as_long(LARGE_INTEGER x);
void set_high(jlong* value, jint high);
void set_low(jlong* value, jint low);

class CSystem
{
private:
	static jlong frequency;
	static int ready;

	static void init()
	{
		LARGE_INTEGER liFrequency = {0};
		QueryPerformanceFrequency(&liFrequency);
		frequency = as_long(liFrequency);
		ready = 1;
	}
public:
	static jlong nanoTime()
	{
		if(ready != 1)
			init();

		LARGE_INTEGER liCounter = {0};
		QueryPerformanceCounter(&liCounter);
		double current = as_long(liCounter);
		double freq = frequency;
		return (jlong)((current / freq) * NANOS_PER_SEC);
	}
};

/************************************************************************/
/* CPlayThread                                                          */
/************************************************************************/
class CPlayThread : public CThread
{
private:
	CBasicPlayer* m_Player;
	CCriticalSection* m_cs;
protected:
	void Execute();
public:
	CPlayThread(CBasicPlayer* pPlayer);
	~CPlayThread(void);
};

/************************************************************************/
/* CSpectrumAnalyserThread                                              */
/************************************************************************/
class CSpectrumAnalyserThread : public CThread
{
private:
	CBasicPlayer* m_Player;
	CSpectrumAnalyser* m_SpectrumAnalyser;
	CCriticalSection* m_cs;
	BOOL m_process;
	jlong m_lfp;
	int m_frameSize;

	int calculateSamplePosition();
	void processSamples(int pPosition);
protected:
	void Execute();
public:
	CSpectrumAnalyserThread(CSpectrumAnalyser* pSpectrumAnalyser);
	~CSpectrumAnalyserThread(void);
};

/************************************************************************/
/* CSpectrumAnalyser                                                    */
/************************************************************************/
class CSpectrumAnalyser
{
friend class CSpectrumAnalyserThread;
private:
	CBasicPlayer* m_Player;
	CSpectrumAnalyserThread* m_SpectrumAnalyserThread;
	CFastFourierTransform* m_FFT;

	/* digital signal process */
	DWORD m_AudioDataBufferLength;
	jbyte* m_AudioDataBuffer;
	INT m_SampleSize;
	LONG m_FpsAsNS;
	LONG m_DesiredFpsAsNS;
	FLOAT* m_Left;
	FLOAT* m_Right;
	INT m_position;
	INT m_offset;
	INT m_sampleType;
	INT m_channelMode;

	/* spectrum analyser */
	INT m_width;
	INT m_height;
	INT* m_peaks;
	INT* m_peaksDelay;
	FLOAT* m_oldFFT;
	INT m_saFFTSampleSize;
	INT m_saBands;
	FLOAT m_saMultiplier;
	FLOAT m_saDecay;
	INT m_barOffset;
	INT m_peakDelay;
	BOOL m_peaksEnabled;
	FLOAT m_saColorScale;

	/* draw spectrum analyser */
	HDC m_hdcScreen;
	HDC m_hdcMem;
	HDC m_hdcMem1;
	HBITMAP m_hbmMem;
	HBITMAP m_hbmMem1;
	HBITMAP m_hOld;
	HBITMAP m_hOld1;
	HBRUSH m_hbrush;
	HBRUSH m_hbrush1;
	HBRUSH m_hbrushOld;
	HBRUSH m_hbrushOld1;
	INT m_winwidth, m_winheight;

	void drawSpectrumAnalyserBar(RECT* pRect, int pX, int pY, int pWidth, int pHeight, int band);
	void prepare();
public:
	CSpectrumAnalyser(CBasicPlayer* pPlayer);
	~CSpectrumAnalyser(void);

	void Start();
	void Stop();
	void Process(float pFrameRateRatioHint);

	jbyte* GetAudioDataBuffer() { return m_AudioDataBuffer; }

	INT GetPosition() { return m_position; }
	void SetPosition(INT pPosition) { m_position = pPosition; }

	DWORD GetAudioDataBufferLength() { return m_AudioDataBufferLength; }
	void SetAudioDataBufferLength(DWORD pAudioDataBufferLength) { m_AudioDataBufferLength = pAudioDataBufferLength; }
};

/************************************************************************/
/* CBasicPlayer                                                         */
/************************************************************************/
class CBasicPlayer
{
//friend class declare
friend class CPlayThread;
friend class CSpectrumAnalyser;

private:
	CPlayThread* m_PlayThread;
	CSpectrumAnalyser* m_SpectrumAnalyser;
	CCriticalSection* m_cs;
	CFileIn* m_Input;
	CWMIn* m_WMInput;
	CMP3In* m_MP3Input;
	CWaveIn* m_WAVInput;
	CVorbisIn* m_VorbisInput;
	BOOL m_Playing;

	DS_Info* m_info;
	volatile long m_bytePosition;

	/* the parameters to create direct sound */
	DWORD m_BufferSize;
	FLOAT m_SampleRate;
	WORD m_FrameSize;
	WORD m_BitPerSample;
	WORD m_Channels;

	/* draw spectrum analyzer */
	HWND m_hWnd;
public:
	CBasicPlayer(HWND hWnd, TCHAR* pszFileName);
	~CBasicPlayer(void);

	BOOL IsPlaying() { return m_Playing; }

	DWORD GetBufferSize() { return m_BufferSize; }
	void SetBufferSize(DWORD pBufferSize) { m_BufferSize = pBufferSize; }

	FLOAT GetSampleRate() { return m_SampleRate; }
	void SetSampleRate(FLOAT pSampleRate) { m_SampleRate = pSampleRate; }

	WORD GetFrameSize() { return m_FrameSize; }
	void SetFrameSize(WORD pFrameSize) { m_FrameSize = pFrameSize; }

	WORD GetBitsPerSample() { return m_BitPerSample; }
	void SetBitsPerSample(WORD pBitsPerSample) { m_BitPerSample = pBitsPerSample; }

	WORD GetChannels() { return m_Channels; }
	void SetChannels(WORD pChannels) { m_Channels = pChannels; }

	CPlayThread* GetPlayThread() { return m_PlayThread; }
	DS_Info* GetDSInfo() { return m_info; }
	long GetBytePosition() { return m_bytePosition; }
	CFileIn* GetInput() { return m_Input; }

	void Start();
	void Stop();
	jlong GetLongFramePosition();
};
#endif