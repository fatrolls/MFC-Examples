#pragma once
#include "stdafx.h"
#include "AudioStream.h"
#include "CriticalSection.h"
#include "Stream.h"

#ifndef INCLUDE_IO
#define INCLUDE_IO

/************************************************************************/
/* CInput                                                               */
/************************************************************************/
class CInput
{
protected:
	LARGE_INTEGER m_Position;
	LARGE_INTEGER m_Size;
	WORD m_SampleSize;
	BOOL m_Busy;
	DWORD m_BufferStart, m_BufferEnd;
	CCriticalSection* m_DataCS;
	BOOL m_EndOfStream;

	virtual void InitInternal() = 0;
	virtual void FlushInternal() = 0;
	virtual void GetDataInternal(void** buffer, DWORD* bytes) = 0;
public:
	CInput(void);
	~CInput(void);

	virtual void Reset();
	virtual void Pause();
	virtual void Resume();
	virtual DWORD GetTotalTime();
	virtual LARGE_INTEGER GetTotalSamples();

	virtual WORD GetBitsPerSample() = 0;
	virtual WORD GetChannels() = 0;
	virtual DWORD GetSampleRate() = 0;

	LARGE_INTEGER GetSize();
	LARGE_INTEGER GetPosition();
	void GetData(void** buffer, DWORD* size);
	DWORD CopyData(void* buffer, DWORD size);
	DWORD FillBuffer(void* buffer, DWORD size, BOOL* eof);
	void Init();
	void Flush();
	void Lock();
	void Unlock();
};

/************************************************************************/
/* CStreamedInput                                                       */
/************************************************************************/
class CStreamedInput : public CInput
{
protected:
	CStream* m_pStream;
	BOOL m_StreamAssigned;
	BOOL m_Seekable;
	LARGE_INTEGER m_StartSample, m_EndSample;
	BOOL m_Loop;
	LARGE_INTEGER m_TotalSamples;

	virtual void SetStream(CStream* pStream);
	virtual BOOL SeekInternal(LARGE_INTEGER* SampleNum) = 0;
public:
	CStreamedInput(void);
	~CStreamedInput(void);

	void GetData(void** buf, DWORD* Bytes);
	BOOL Seek(LARGE_INTEGER* SampleNum);
	CStream* GetStream() { return m_pStream; }
};

/************************************************************************/
/* CFileIn                                                              */
/************************************************************************/
class CFileIn : public CStreamedInput
{
protected:
	CCriticalSection* m_OpenCS;
	TCHAR m_FileName[MAX_PATH];
	size_t m_FileNameLen;
	INT m_Opened;
	BOOL m_Valid;
	WORD m_BitsPerSample;
	DWORD m_SampleRate;
	WORD m_Channels;
	DWORD m_Time;

	void SetStream(CStream* pStream);
	void FlushInternal();
	void InitInternal();
public:
	CFileIn(void);
	~CFileIn(void);

	virtual void OpenFile() = 0;
	virtual void CloseFile() = 0;

	void SetFileName(TCHAR* pszFileName);
	size_t GetFileNameLen();
	WORD GetBitsPerSample();
	DWORD GetSampleRate();
	WORD GetChannels();
	INT GetOpened();

	BOOL GetValid();
	LARGE_INTEGER GetTotalSamples();
	DWORD GetTotalTime();

	BOOL SetStartTime(DWORD Minutes, DWORD Seconds);
	BOOL SetEndTime(DWORD Minutes, DWORD Seconds);
	void Reset();
	void Jump(INT offset);
};

/************************************************************************/
/* CWMIn                                                                */
/************************************************************************/
typedef enum _ChannelsNumber {cnMaxAvailable = 0, cnMonoOrStereo, cn5dot1, cn7dot1} ChannelsNumber;
const INT wmfDefault = -2;

class CWMIn : public CFileIn
{
private:
	WMA_SYNC_READER* m_Reader;
	DWORD m_Duration;
	BOOL m_HighPrecision;
	ChannelsNumber m_OutputChannels;
	INT m_Format;

	SHORT CNToShortInt();

protected:
	void GetDataInternal(void** buffer, DWORD* bytes);
	BOOL SeekInternal(LARGE_INTEGER* SampleNum);

public:
	CWMIn(void);
	~CWMIn(void);

	void OpenFile();
	void CloseFile();

	void SetHighPrecision(BOOL HighPrecision);
	void SetOutputChannels(ChannelsNumber OutputChannels);
	BOOL GetHasAudio();
	BOOL GetProtected();
	DWORD GetBitrate();
	BOOL GetIsVBR();
	DWORD GetFormatsCount();
	void GetFormatSpec(INT index, WMAFormatSpec* pFormatSpec);
	void SetFormat(INT iFormat);
	INT GetFormat();
};

/************************************************************************/
/* CWaveIn                                                              */
/************************************************************************/
#define BUF_SIZE 16000

#define WaveHeaderOffs 44
#define DataSizeOffs 40

#define LookingForRIFF 0
#define LookingForWave 1
#define LookingForFMT 2
#define LookingForFACT 3
#define LookingForDATA 4

#define WAVE_FORMAT_MP3 85

typedef enum _WaveType {wtUnsupported, wtPCM, wtDVIADPCM, wtMSADPCM, wtACM,
wtIEEEFloat, wtExtPCM, wtExtIEEEFloat} WaveType;

/*
_WaveHeader - Represents a RIFF file header.
Properties:
RIFF: array [0..3] of Char - 'RIFF'
FileSize: Integer - FileSize - 8
RIFFType: array [0..3] of Char - 'WAVE'
FmtChunkId: array [0..3] of Char - 'fmt' marks the beginning of the format chunk
FmtChunkSize: Integer - 16 the size of the format chunk
FormatTag: Word - One of WAVE_FORMAT_XXX constants
Channels: Word - 1=mono, 2=stereo
SampleRate: Integer; - sample rate
BytesPerSecond: Integer; - bytes per second
BlockAlign: Word; - block alignment?
BitsPerSample: Word - 8, 16 or 32 Bits/sample
DataChunkId: array [0..3] of Char - 'data' marks the beginning of the data chunk
DataSize: Integer - Data size in bytes
*/
typedef struct _WaveHeader
{
	char RIFF[4]; /* 'RIFF' offset : 0000 */
	DWORD FileSize; /* FileSize - 8 offset : 0004 */
	char RIFFType[4]; /* 'WAVE'  offset : 0008 */
	char FmtChunkId[4]; /* 'fmt '   offset : 0012 */
	DWORD FmtChunkSize; /* 16      offset : 0016 */
	WORD FormatTag; /* One of WAVE_FORMAT_XXX constants    offset : 0020 */
	WORD Channels; /* 1 - mono = 2 - stereo             offset : 0022 */
	DWORD SampleRate; /* offset : 0024 */
	DWORD BytesPerSecond; /* offset : 0028 */
	WORD BlockAlign; /* offset : 0032 */
	WORD BitsPerSample; /* 8, 16 or 32 Bits/sample offset : 0034 */
	char DataChunkId[4]; /* 'data' offset : 0036*/
	DWORD DataSize; /* Data size in bytes offset : 0040 */
} WaveHeader, *LPWaveHeader;

/*
_WaveHeaderEx - Represents a WaveFormatExtensible header.
Properties:
RIFF: array [0..3] of Char - 'RIFF'
FileSize: Integer - FileSize - 8
RIFFType: array [0..3] of Char - 'WAVE'
FmtChunkId: array [0..3] of Char - 'fmt' marks the beginning of the format chunk
FmtChunkSize: Integer - 16, the size of the format chunk
Format: <TWaveFormatExtensible> - see <TWaveFormatExtensible>
DataChunkId: array [0..3] of Char; - 'data' marks the beginning of the data chunk
DataSize: Integer; - Data size in bytes
*/
typedef struct _WaveHeaderEx
{
	char RIFF[4];
	DWORD FileSize;
	char RIFFType[4];
	char FmtChunkId[4];
	DWORD FmtChunkSize;
	WAVEFORMATEXTENSIBLE Format;
	char DataChunkId[4];
	DWORD DataSize;
} WaveHeaderEx, *LPWaveHeaderEx;

/*
RIFF file header for DVIADPCM (version NNFCAIWFLDL).
Properties:
RIFF: array [0..3] of Char - 'RIFF' begins RIFF file header
FileSize: Integer - FileSize - 8
RIFFType: array [0..3] of Char - 'WAVE'
FmtChunkId: array [0..3] of Char - 'fmt' Format chunk
FmtChunkSize: Integer - 20
FormatTag: Word - WAVE_FORMAT_DVI_ADPCM
Channels: Word - 1=mono, 2=stereo
SampleRate: Integer;
BytesPerSecond: Integer;
BlockAlign: Word;
BitsPerSample: Word - 3, 4 bits/sample
cbSize: Word - The size in bytes of the extra information
SamplesPerBlock: Word - number of samples per channel per Block
FactChunkId: array [0..3] of Char - 'fact' begin Fact Chunk
FactChunkSize : Integer - 4
DataLength : Integer;
DataChunkId: array [0..3] of Char - 'data' begin Data Chunk
DataSize: Integer -  Data size in bytes
*/
typedef struct _DVIADPCMHeader
{
	char RIFF[4];
	DWORD FileSize;
	char RIFFType[4];
	char FmtChunkId[4];
	DWORD FmtChunkSize;
	WORD FormatTag; //WAVE_FORMAT_DVI_ADPCM
	WORD Channels;
	DWORD SampleRate;
	DWORD BytesPerSecond;
	WORD BlockAlign;
	WORD BitsPerSample;
	WORD cbSize;
	WORD SamplesPerBlock;
	char FactChunkId[4];
	DWORD FactChunkSize;
	DWORD DataLength;
	char DataChunkId[4];
	DWORD DataSize;
} DVIADPCMHeader, *LPDVIADPCMHeader;

typedef struct _DVI_ADPCM_INFO
{
	WORD BlockLength;
	WORD SamplesPerBlock;
	DWORD DataSize;
} DVI_ADPCM_INFO, *LPDVI_ADPCM_INFO;

typedef struct _DVI_ADPCM_STATE_STEREO
{
	SHORT valprev_l; // Previous output value
	BYTE index_l; // Index into stepsize table
	SHORT valprev_r; // Previous output value
	BYTE index_r; // Index into stepsize table
} DVI_ADPCM_STATE_STEREO, *LPDVI_ADPCM_STATE_STEREO;

typedef struct _DVI_ADPCM_ENCODE_STATE_STEREO
{
	SHORT PredSamp_l;
	BYTE Index_l;
	SHORT PredSamp_r;
	BYTE Index_r;
} DVI_ADPCM_ENCODE_STATE_STEREO, *LPDVI_ADPCM_ENCODE_STATE_STEREO;

typedef struct _MS_ADPCM_COEF_SET
{
	SHORT Coef1;
	SHORT Coef2;
} MS_ADPCM_COEF_SET, *LPMS_ADPCM_COEF_SET;

typedef struct _MS_ADPCM_INFO
{
	WORD BlockLength;
	WORD SamplesPerBlock;
	DWORD DataSize;
	WORD NumCoeff;
	MS_ADPCM_COEF_SET CoefSets[32];
} MS_ADPCM_INFO, *LPMS_ADPCM_INFO;

typedef struct _MSADPCMBlockHeaderMono
{
	BYTE predictor;
	SHORT Delta;
	SHORT Samp1;
	SHORT Samp2;
} MSADPCMBlockHeaderMono, *LPMSADPCMBlockHeaderMono;

typedef struct _MSADPCMBlockHeaderStereo
{
	BYTE predictor[2];
	SHORT Delta[2];
	SHORT Samp1[2];
	SHORT Samp2[2];
} MSADPCMBlockHeaderStereo, *LPMSADPCMBlockHeaderStereo;

typedef struct _DVIADPCMBlockHeader
{
	SHORT Samp0;
	BYTE StepTableIndex;
	BYTE Reserved;
} DVIADPCMBlockHeader, *LPDVIADPCMBlockHeader;

class CWaveIn : public CFileIn
{
private:
	BYTE m_Buf[BUF_SIZE];
	WaveType m_WavType;
	DVI_ADPCM_INFO m_DVI_ADPCM_INFO;
	DVI_ADPCM_STATE_STEREO m_DVI_ADPCM_STATE;
	MS_ADPCM_INFO m_MS_ADPCM_INFO;
	MSADPCMBlockHeaderStereo m_MS_ADPCM_STATE;
	WORD m_HeaderSize;
	CMemoryStream* m_MS;
	CStream* m_OldStream;
	BOOL m_OldStreamAssigned;
	BOOL m_ShortIEEEFloat;

	BOOL ReadDVIADPCMBlock(void* pData);
	BOOL ReadMSADPCMBlock(void* pData);
	WaveType GetWavType();
	void ReadRIFFHeader();
	void DecodeDVIADPCMMono(BYTE* pInData, SHORT* pOutData, DWORD *len);
	void DecodeDVIADPCMStereo(BYTE* pInData, SHORT* pOutData, DWORD* len);
	void DecodeMSADPCMMono(BYTE* pInData, SHORT* pOutData, DWORD* len);
	void DecodeMSADPCMStereo(BYTE* pInData, SHORT* pOutData, DWORD* len);
protected:
	void GetDataInternal(void** buffer, DWORD* bytes);
	BOOL SeekInternal(LARGE_INTEGER* SampleNum);
public:
	CWaveIn(void);
	~CWaveIn(void);

	void OpenFile();
	void CloseFile();
};

BOOL Compare4(CHAR* S1, CHAR* S2);
void ConvertIEEEFloatTo32(INT* InOutBuf, INT InSize);
void ConvertShortIEEEFloatTo32(INT* InOutBuf, INT InSize);

/************************************************************************/
/* CMP3In                                                               */
/************************************************************************/
# define SAMPLE_DEPTH 16
# define scale(x, y) dither((x), (y))

struct xing
{
	long flags;
	unsigned long frames;
	unsigned long bytes;
	unsigned char toc[100];
	long scale;
};

enum
{
	XING_FRAMES = 0x00000001L,
	XING_BYTES  = 0x00000002L,
	XING_TOC    = 0x00000004L,
	XING_SCALE  = 0x00000008L
};

# define XING_MAGIC (('X' << 24) | ('i' << 16) | ('n' << 8) | 'g')

struct dither
{
	mad_fixed_t error[3];
	mad_fixed_t random;
};

typedef struct _ID3Tag
{
	char m_cTAG[3];  // Must equal "TAG"
	char m_cSong[30];
	char m_cArtist[30];
	char m_cAlbum[30];
	char m_cYear[4];
	char m_cComment[30];
	unsigned char m_cGenre;
} ID3Tag;

typedef struct _ID3v2Tag
{
	char m_cTAG[3];  // Must equal ID3
	unsigned char m_cVersion[2]; // Major / Minor
	unsigned char m_cFlags;
	unsigned char m_cSize_Encoded[4];
} ID3v2Tag;

typedef struct _ID3v2Frame
{
	char m_cFrameID[4];
	unsigned char m_cSize_Encoded[4];
	unsigned short m_cFlags;
} ID3v2Frame;

int parse_xing(struct xing *xing, struct mad_bitptr ptr, unsigned int bitlen);
int scan_header(CStream* pStream, struct mad_header *header, struct xing *xing);
void pack_pcm(unsigned char **pcm, unsigned int nsamples, mad_fixed_t const *ch1, mad_fixed_t const *ch2);

class CMP3In : public CFileIn
{
private:
	unsigned long m_size;
	unsigned long m_streamsize;
	unsigned int m_samplecount;
	mad_timer_t m_timer;
	mad_timer_t m_length;
	unsigned long m_rate;
	unsigned long m_frames;

	struct mad_stream m_stream;
	struct mad_frame m_frame;
	struct mad_synth m_synth;
	struct xing m_xing;
	BOOL m_vbr;

	unsigned char m_buffer[40000];
	unsigned int m_buflen;
	unsigned char m_pcmbuffer[BUF_SIZE];
protected:
	void GetDataInternal(void** buffer, DWORD* bytes);
	BOOL SeekInternal(LARGE_INTEGER* SampleNum);
public:
	CMP3In(void);
	~CMP3In(void);

	void OpenFile();
	void CloseFile();
};

/************************************************************************/
/* CVorbisIn                                                            */
/************************************************************************/
class CVorbisIn : public CFileIn
{
private:
	OggVorbis_File m_OggVorbisFile;
	int m_CurrentSection;

	unsigned char m_buffer[40000];
	unsigned int m_buflen;
	unsigned char m_pcmbuffer[BUF_SIZE];
protected:
	void GetDataInternal(void** buffer, DWORD* bytes);
	BOOL SeekInternal(LARGE_INTEGER* SampleNum);
public:
	CVorbisIn(void);
	~CVorbisIn(void);

	void OpenFile();
	void CloseFile();

};

size_t vorbisRead(void *buffer, size_t size, size_t amount, void *file);
int vorbisSeek(void *file, ogg_int64_t newpos, int set);
int vorbisClose(void *file);
long vorbisTell(void *file);

#endif

