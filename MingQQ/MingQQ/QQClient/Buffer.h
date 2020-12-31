#pragma once

class CBuffer
{
public:
	CBuffer();
	~CBuffer(void);

public:
	void SetSize(DWORD dwNewSize);
	void SetGrowBy(DWORD dwGrowBy);
	BOOL Add(const CHAR* lpStr);
	BOOL Add(const WCHAR* lpStr);
	BOOL Add(CBuffer& src);
	BOOL Add(const BYTE* lpData, DWORD dwSize);
	const BYTE* GetData();
	DWORD GetSize();
	void Release();

private:
	BOOL ReAlloc(DWORD dwSize);

private:
	BYTE m_cFixData[1024 * 4];
	BYTE* m_lpData;
	DWORD m_dwSize;
	DWORD m_dwMaxSize;
	DWORD m_dwGrowBy;
};
