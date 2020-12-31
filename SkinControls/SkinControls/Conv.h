
#ifndef CONV_H_
#define CONV_H_
#pragma once

// ±àÂë×ª»»·â×°

// UTF8 TO UNICODE
template<int t_nBufferLength = 260>
class CUtf8ToUnicode
{
public:
	CUtf8ToUnicode(const char* psz) : m_psz(m_szBuffer)
	{
		Initialize(psz);
	}

	~CUtf8ToUnicode() throw()
	{
		if (m_psz != m_szBuffer)
		{
			delete []m_psz;
		}
	}

	operator const wchar_t*() const
	{
		return m_psz;
	}

	size_t CharCount() const
	{
		if (m_psz == NULL)
			return 0;

		return m_nCharCount;
	}

private:
	void Initialize(const char* psz)
	{
		if (psz == NULL)
		{
			m_psz = NULL;
			return;
		}

		m_nCharCount = MultiByteToWideChar(CP_UTF8, 0, psz, -1, NULL, 0);
		if (m_nCharCount > t_nBufferLength)
		{
			m_psz = new wchar_t[m_nCharCount];
			if (m_psz == NULL)
			{
				throw E_OUTOFMEMORY;
			}
		}

		m_nCharCount = MultiByteToWideChar(CP_UTF8, 0, psz, -1, m_psz, static_cast<int>(m_nCharCount));
	}

	wchar_t* m_psz;
	wchar_t m_szBuffer[t_nBufferLength];
	size_t m_nCharCount;	 
};

// UNICODE TO UTF8
template<int t_nBufferLength = 260>
class CUnicodeToUtf8
{
public:
	CUnicodeToUtf8(const wchar_t* psz) : m_psz(m_szBuffer)
	{
		Initialize(psz);
	}

	~CUnicodeToUtf8() throw()
	{
		if (m_psz != m_szBuffer)
		{
			delete []m_psz;
		}
	}

	operator const char*() const
	{
		return m_psz;
	}

	size_t CharCount() const
	{
		if (m_psz == NULL)
			return 0;

		return m_nCharCount;
	}

private:
	void Initialize(const wchar_t* psz)
	{
		if (psz == NULL)
		{
			m_psz = NULL;
			return;
		}

		m_nCharCount = WideCharToMultiByte(CP_UTF8, 0, psz, -1, NULL, 0, NULL, NULL);
		if (m_nCharCount > t_nBufferLength)
		{
			m_psz = new char[m_nCharCount];
			if (m_psz == NULL)
			{
				throw E_OUTOFMEMORY;
			}
		}

		m_nCharCount = WideCharToMultiByte(CP_UTF8, 0, psz, -1, m_psz, static_cast<int>(m_nCharCount), NULL, NULL);
	}

	char* m_psz;
	char m_szBuffer[t_nBufferLength];
	size_t m_nCharCount;	 
};

#define UTF8_TO_UNICODE(a) (LPCWSTR)CUtf8ToUnicode<>(a)
#define UNICODE_TO_UTF8(a) (LPCSTR)CUnicodeToUtf8<>(a)

#define UTF8_TO_ANSI(a) (LPCSTR)CW2A(((LPCWSTR)CUtf8ToUnicode<>(a)))
#define ANSI_TO_UTF8(a) ((LPCSTR)CUnicodeToUtf8<>(CA2W(a)))

#ifdef _UNICODE
#define CU82T UTF8_TO_UNICODE
#define CT2U8 UNICODE_TO_UTF8
#else
#define CU82T UTF8_TO_ANSI
#define CT2U8 ANSI_TO_UTF8
#endif

#endif // CONV_H_




