#ifndef __MMIO_H__
#define __MMIO_H__

#include <MMSystem.h>

//-----------------------------------------------------------------
// CMMChunk Class - Multimedia RIFF Chunk Object
//-----------------------------------------------------------------
class CMMChunk : public MMCKINFO
{
protected:
	CMMChunk() { };
};

//-----------------------------------------------------------------
// CMMIdChunk Class - Multimedia RIFF Id Chunk Object
//-----------------------------------------------------------------
class CMMIdChunk : public CMMChunk
{
public:
	CMMIdChunk(char c0, char c1, char c2, char c3);
	CMMIdChunk(LPCSTR psz, UINT uiFlags = 0u);
};

//-----------------------------------------------------------------
// CMMTypeChunk Class - Multimedia RIFF Type Chunk Object
//-----------------------------------------------------------------
class CMMTypeChunk : public CMMChunk
{
public:
	CMMTypeChunk(char c0, char c1, char c2, char c3);
	CMMTypeChunk(LPCSTR psz, UINT uiFlags = 0u);
};

//-----------------------------------------------------------------
// CMMIOInfo Class - Multimedia RIFF I/O Info Object
//-----------------------------------------------------------------
class CMMIOInfo : public MMIOINFO
{
public:
	CMMIOInfo();
};

//-----------------------------------------------------------------
// CMMMemoryIOInfo Class - Multimedia RIFF Memory I/O Info Object
//-----------------------------------------------------------------
class CMMMemoryIOInfo : public CMMIOInfo
{
public:
	CMMMemoryIOInfo(LONG lBuffer, DWORD dwMinExpansion = 0);
	CMMMemoryIOInfo(HPSTR pBuffer, LONG lBuffer, DWORD dwMinExpansion = 0);
};

//-----------------------------------------------------------------
// CMMIO Class - Multimedia RIFF I/O Object
//-----------------------------------------------------------------
class CMMIO : public CObject
{
public:
	CMMIO();
	CMMIO(HMMIO hmmio);
	CMMIO(const char* pszFileName, DWORD dwOpenFlag = MMIO_READ);
	CMMIO(CMMMemoryIOInfo& mmioinfo);

  // Public Methods
public:
	void      Open(const char* pszFileName, DWORD dwOpenFlags =
			  MMIO_READ);
	void      Open(CMMMemoryIOInfo &mmioinfo);
	MMRESULT  Close(UINT uiFlags = 0u);

	MMRESULT  Ascend(CMMChunk &mmckInfo, UINT uiFlags = 0u);
	MMRESULT  Descend(CMMChunk &mmckInfo, UINT uiFlags = 0u);
	MMRESULT  Descend(CMMChunk &mmckInfo, CMMChunk &mmckParent, UINT uiFlags = 0u);

	LONG      Read(HPSTR pData, LONG lLen);
	LONG      Write(const char* pData, LONG lLen);
	LONG      Seek(LONG lOffset, int iOrigin);

	LRESULT   SendMessage(UINT uiMsg, LPARAM lParam1, LPARAM lParam2);
	MMRESULT  SetBuffer(LPSTR pBuffer, LONG lBuffer, UINT uiFlags = 0u);

	MMRESULT  GetInfo(CMMIOInfo &, UINT uiFlags = 0);
	MMRESULT  SetInfo(CMMIOInfo &, UINT uiFlags = 0);
	MMRESULT  Advance(CMMIOInfo &, UINT uiFlags);

	// Public Data
public:
	HMMIO m_hmmio;
};


//-----------------------------------------------------------------
// CMMIdChunk Inline Public Constructor(s)/Destructor
//-----------------------------------------------------------------
inline CMMIdChunk::CMMIdChunk(char c0, char c1, char c2, char c3)
{
	ckid = mmioFOURCC(c0, c1, c2, c3);
}

inline CMMIdChunk::CMMIdChunk(LPCSTR psz, UINT uiFlags)
{
	ckid = ::mmioStringToFOURCC(psz, uiFlags);
}

//-----------------------------------------------------------------
// CMMTypeChunk Inline Public Constructor(s)/Destructor
//-----------------------------------------------------------------
inline CMMTypeChunk::CMMTypeChunk(char c0, char c1, char c2, char c3)
{
	fccType = mmioFOURCC(c0, c1, c2, c3);
}

inline CMMTypeChunk::CMMTypeChunk(LPCSTR psz, UINT uiFlags)
{
	fccType = ::mmioStringToFOURCC(psz, uiFlags);
}

//-----------------------------------------------------------------
// CMMIOInfo Inline Public Constructor(s)/Destructor
//-----------------------------------------------------------------
inline CMMIOInfo::CMMIOInfo()
{
	::ZeroMemory(this, sizeof(MMIOINFO));
}

//-----------------------------------------------------------------
// CMMMemoryIOInfo Inline Public Constructor(s)/Destructor
//-----------------------------------------------------------------
inline CMMMemoryIOInfo::CMMMemoryIOInfo(LONG lBuffer, DWORD dwMinExpansion)
{
	pIOProc = NULL;
	fccIOProc = FOURCC_MEM;
	pchBuffer = NULL;
	cchBuffer = lBuffer;
	adwInfo[0] = dwMinExpansion;
}

inline CMMMemoryIOInfo::CMMMemoryIOInfo(HPSTR pBuffer, LONG cchBuf, DWORD dwMinExpansion)
{
	pIOProc = NULL;
	fccIOProc = FOURCC_MEM;
	pchBuffer = pBuffer;
	cchBuffer = cchBuf;
	adwInfo[0] = dwMinExpansion;
}

//-----------------------------------------------------------------
// CMMIO Inline Public Constructor(s)/Destructor
//-----------------------------------------------------------------
inline CMMIO::CMMIO() : m_hmmio(NULL)
{
}

inline CMMIO::CMMIO(HMMIO hmmio) : m_hmmio(hmmio)
{
}

inline CMMIO::CMMIO(const char* pszFileName, DWORD dwOpenFlag)
{
	Open(pszFileName, dwOpenFlag);
}

inline CMMIO::CMMIO(CMMMemoryIOInfo &mmioinfo)
{
	Open(mmioinfo);
}

//-----------------------------------------------------------------
// CMMIO Inline Public Methods
//-----------------------------------------------------------------
inline MMRESULT CMMIO::Close(UINT uiFlags)
{
	ASSERT(m_hmmio != NULL);
	MMRESULT mmr = ::mmioClose(m_hmmio, uiFlags);  
	m_hmmio = NULL;
	return mmr;
}

inline LONG CMMIO::Read(HPSTR pData, LONG lLen)
{
	ASSERT(m_hmmio != NULL);
	return ::mmioRead(m_hmmio, pData, lLen);
}

inline MMRESULT CMMIO::Ascend(CMMChunk &mmckInfo, UINT uiFlags)
{
	ASSERT(m_hmmio != NULL);
	return ::mmioAscend(m_hmmio, &mmckInfo, uiFlags);
}

inline MMRESULT CMMIO::Descend(CMMChunk &mmckInfo, UINT uiFlags)
{
	ASSERT(m_hmmio != NULL);
	return ::mmioDescend(m_hmmio, &mmckInfo, 0, uiFlags);
}

inline MMRESULT CMMIO::Descend(CMMChunk &mmckInfo, CMMChunk &mmckParent, UINT uiFlags)
{
	ASSERT(m_hmmio != NULL);
	return ::mmioDescend(m_hmmio, &mmckInfo, &mmckParent, uiFlags);
}

inline LONG CMMIO::Seek(LONG lOffset, int iOrigin)
{
	ASSERT(m_hmmio != NULL);
	return ::mmioSeek(m_hmmio, lOffset, iOrigin);
}

inline LRESULT CMMIO::SendMessage(UINT uiMsg, LPARAM lParam1, LPARAM lParam2)
{
	ASSERT(m_hmmio != NULL);
	return ::mmioSendMessage(m_hmmio, uiMsg, lParam1, lParam2);
}

inline MMRESULT CMMIO::SetBuffer(LPSTR pBuffer, LONG lBuffer, UINT uiFlags)
{
	ASSERT(m_hmmio != NULL);
	return ::mmioSetBuffer(m_hmmio, pBuffer, lBuffer, uiFlags);  
}

inline LONG CMMIO::Write(const char* pData, LONG lLen)
{
	ASSERT(m_hmmio != NULL);
	return ::mmioWrite(m_hmmio, pData, lLen);
}

inline MMRESULT CMMIO::GetInfo(CMMIOInfo &Info, UINT uiFlags)
{
	ASSERT(m_hmmio != NULL);
	return ::mmioGetInfo(m_hmmio, &Info, uiFlags);
}

inline MMRESULT CMMIO::SetInfo(CMMIOInfo &Info, UINT uiFlags)
{
	ASSERT(m_hmmio != NULL);
	return ::mmioSetInfo(m_hmmio, &Info, uiFlags);
}

inline MMRESULT CMMIO::Advance(CMMIOInfo &Info, UINT uiFlags)
{
	ASSERT(m_hmmio != NULL);
	return ::mmioAdvance(m_hmmio, &Info, uiFlags);
}

#endif
