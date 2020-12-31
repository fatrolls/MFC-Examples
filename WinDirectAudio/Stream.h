#pragma once
#include "stdafx.h"

#ifndef INCLUDE_CSTREAM
#define INCLUDE_CSTREAM

#pragma warning(disable : 4006)
#pragma warning(disable : 4995)

/************************************************************************/
/* CStream                                                              */
/************************************************************************/
class CStream
{
public:
	CStream(void) {}
	~CStream(void) {}

	virtual DWORD Read(void* buf, DWORD size) = 0;
	virtual DWORD Write(void* buf, DWORD size) = 0;
	virtual DWORD Seek(INT offset, WORD origin) = 0;

	INT64 GetPosition(void);
	void SetPosition(INT64 position);

	virtual INT64 GetSize(void);
	virtual void SetSize(const INT64 size);
	virtual void SetSize(DWORD size);
};

/************************************************************************/
/* CHandleStream                                                        */
/************************************************************************/
class CHandleStream : public CStream
{
protected:
	HANDLE m_handle;

	void SetSize(const INT64 size);
	void SetSize(INT size);
public:
	CHandleStream(void) : m_handle(0) {}
	~CHandleStream(void) {}

	DWORD Read(void* buf, DWORD size);
	DWORD Write(void* buf, DWORD size);
	DWORD Seek(INT offset, WORD origin);
	HANDLE GetHandle() { return m_handle; }
};

/************************************************************************/
/* CCustomMemoryStream                                                  */
/************************************************************************/
class CCustomMemoryStream : public CStream
{
protected:
	void* m_Memory;
	DWORD m_Size;
	DWORD m_Position;

	void SetPointer(void* Ptr, DWORD Size);
public:

	CCustomMemoryStream(void);
	~CCustomMemoryStream(void);

	DWORD Read(void* buf, DWORD size);
	DWORD Seek(INT offset, WORD origin);
	void SaveToStream(CStream* pStream);
	void SaveToFile(TCHAR* pszFileName);
};

/************************************************************************/
/* CMemoryStream                                                        */
/************************************************************************/
class CMemoryStream : public CCustomMemoryStream
{
private:
	DWORD m_Capacity;
protected:
	void* Realloc(DWORD NewCapacity);
public:
	CMemoryStream(void);
	~CMemoryStream(void);

	void Clear();
	void LoadFromStream(CStream* pStream);
	void LoadFromFile(TCHAR* pszFileName);
	void SetSize(DWORD NewSize);
	DWORD Write(void* buf, DWORD size);
	void SetCapacity(DWORD NewCapacity);
};

/************************************************************************/
/* CFileStream                                                          */
/************************************************************************/
typedef enum _FILE_MODE {FILE_OPEN = 0, FILE_CREATE} FILE_MODE;
class CFileStream : public CHandleStream
{
public:
	CFileStream(TCHAR* pszFileName, FILE_MODE mode, DWORD rights = 0);
	~CFileStream(void);
};

/************************************************************************/
/* CWaveConverter                                                       */
/************************************************************************/
typedef struct _RiffHeader
{
	char ID[4];
	DWORD BytesFollowing;
} RiffHeader, *LPRiffHeader;

typedef struct _ACMWaveFormat
{
	union
	{
		WAVEFORMATEX format;
		BYTE RawData[128];
	};
} ACMWaveFormat, *LPACMWaveFormat;

class CWaveConverter : public CMemoryStream
{
private:
	DWORD m_MaxFmtSize;
public:
	CWaveConverter(void);
	~CWaveConverter(void);

	ACMWaveFormat CurrentFormat;
	ACMWaveFormat NewFormat;
	INT LoadStream(CStream* pStream);
	INT Convert();
	INT SaveWavToStream(CStream* pStream);
};

#endif
