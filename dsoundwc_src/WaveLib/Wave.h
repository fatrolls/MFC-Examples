// Wave.h
#ifndef __WAVE_H__
#define __WAVE_H__

#include <MMSystem.h>


class AFX_EXT_CLASS CWave : public CObject
{
	BYTE* m_pImageData;
	DWORD m_dwImageLen;
	BOOL  m_bResource;
public:
	CWave();
	CWave(LPCTSTR lpszFileName);
	CWave(UINT nResID, HMODULE hMod = AfxGetInstanceHandle());
	virtual ~CWave();

public:
	BOOL    Create(LPCTSTR lpszFileName);
	BOOL    Create(UINT uiResID, HMODULE hMod =	AfxGetInstanceHandle());
	BOOL    IsValid() const { return (m_pImageData ? TRUE :	FALSE); };
	BOOL    Play(BOOL bAsync = TRUE, BOOL bLooped = FALSE) const;
	BOOL    GetFormat(WAVEFORMATEX& wfFormat) const;
	DWORD   GetDataLen() const;
	DWORD   GetData(BYTE*& pWaveData, DWORD dwMaxToCopy) const;

protected:
	BOOL    Free();
};

#endif // __WAVE_H__
