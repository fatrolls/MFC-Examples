/*
 * Copyright Bruce Liang (ldcsaa@gmail.com)
 *
 * Version	: 2.3.2
 * Author	: Bruce Liang
 * Website	: http://www.jessma.org
 * Porject	: https://code.google.com/p/ldcsaa
 * Bolg		: http://www.cnblogs.com/ldcsaa
 * WeiBo	: http://weibo.com/u/1402935851
 * QQ Group	: 75375912
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
 
/******************************************************************************
Module:  BigString.h
Notices: Copyright (c) 2006 Bruce Liang
Purpose: 管理大字符串, 提高内存申请/释放的效率.
Desc:
******************************************************************************/

#pragma once

#include <memory.h>
#include <malloc.h>

template< typename TCharType, size_t t_iPageSize = 4096 * sizeof(TCharType) >
class CBigStringT
{
public:
	CBigStringT()							{Reset();}
	CBigStringT(const TCharType* pszSrc)	{Reset(); Copy(pszSrc);}
	CBigStringT(CBigStringT& strSrc)		{Reset(); Copy(strSrc);}

	CBigStringT& operator =		(const TCharType* pszSrc)	{if(m_pszData != pszSrc) Copy(pszSrc);	return *this;}
	CBigStringT& operator =		(CBigStringT& strSrc)		{if(this != &strSrc) Copy(strSrc);		return *this;}

	CBigStringT& operator +=	(const TCharType* pszSrc)	{if(m_pszData != pszSrc) Cat(pszSrc);	return *this;}

	bool operator == (const TCharType* pszSrc)
	{
		if(IsNull() && pszSrc == NULL)
			return true;
		return (_StrCmp(m_pszData, pszSrc) == 0);
	}

	~CBigStringT()						{if(!IsNull()) free(m_pszData);}

	operator const		TCharType* ()	{return m_pszData;}
	size_t				GetStrLen()		{return m_iDataLen;}
	const TCharType*	GetStr()		{return *this;}

	size_t Copy(const TCharType* pszSrc)
	{
		if(!IsNull())
			free(m_pszData);

		size_t srclen = _StrLen(pszSrc);
		if(srclen > 0)
		{
			m_iDataLen		= srclen;
			m_iBufferLen	= (srclen + 1) * sizeof(TCharType);
			m_pszData		= (TCharType*)malloc(m_iBufferLen);
			memcpy(m_pszData, pszSrc, m_iBufferLen);
		}
		else
			Reset();
		return m_iDataLen;
	}

	size_t Cat(const TCharType* pszSrc)
	{
		return Insert((int)m_iDataLen, pszSrc);
	}

	size_t Insert(int index, const TCharType* pszSrc)
	{
		if(m_iDataLen == 0)
			return Copy(pszSrc);

		size_t srclen	= _StrLen(pszSrc);
		if(srclen > 0)
		{
			index = (index < 0 ? 0 :
						(index > (int)m_iDataLen ? (int)m_iDataLen : index));

			size_t wantlen	= (m_iDataLen + srclen + 1) * sizeof(TCharType);
			if(wantlen > m_iBufferLen)
			{
				m_iBufferLen	= max(wantlen, min(wantlen * 2, m_iBufferLen + t_iPageSize));
				m_pszData		= (TCharType*)realloc(m_pszData, m_iBufferLen);
			}

			memmove(m_pszData + index + srclen, m_pszData + index, (m_iDataLen - index + 1) * sizeof(TCharType));
			memcpy(m_pszData + index, pszSrc, srclen * sizeof(TCharType));
			m_iDataLen += srclen;
		}
		return m_iDataLen;
	}

	size_t ReleaseExtra()
	{
		if(m_iDataLen == 0)
			return 0;

		size_t iBufferLen	= (m_iDataLen + 1) * sizeof(TCharType);
		size_t iReleaseLen	= m_iBufferLen - iBufferLen;
		if(iReleaseLen != 0)
		{
			m_iBufferLen	= iBufferLen;
			m_pszData		= (TCharType*)realloc(m_pszData, m_iBufferLen);

		}
		return iReleaseLen;
	}

	void Format(const TCharType* pszFormat, ...)
	{
		va_list argList;
		va_start( argList, pszFormat );
		FormatV( pszFormat, argList );
		va_end( argList );
	}

private:
	void Reset()
	{
		m_pszData		= (TCharType*)_Null(TCharType(0));
		m_iDataLen		= 0;
		m_iBufferLen	= 0;
	}

	bool IsNull() {return (m_pszData == _Null(TCharType(0)));}

	void FormatV(const TCharType* pszFormat, va_list args)
	{
		if(!IsNull())
			free(m_pszData);

		int len = _GetFormattedLength(pszFormat, args);
		if(len > 0)
		{
			m_iDataLen		= len;
			m_iBufferLen	= (len + 1) * sizeof(TCharType);
			m_pszData		= (TCharType*)malloc(m_iBufferLen);
			_VSprintf(m_pszData, pszFormat, args);
		}
		else
			Reset();
	}

	static size_t _StrLen(const char* psz)
	{
		return (psz != NULL ? strlen(psz) : 0);
	}

	static size_t _StrLen(const wchar_t* psz)
	{
		return (psz != NULL ? wcslen(psz) : 0);
	}

	static int _StrCmp(const char* psz1, const char* psz2)
	{
		return strcmp(psz1, psz2);
	}

	static int _StrCmp(const wchar_t* psz1, const wchar_t* psz2)
	{
		return wcscmp(psz1, psz2);
	}

	/*** 为提高效率, 用 memcpy 实现 strcpy 和 strcat. 

	static char* _StrCopy(char* pszDest, const char* pszSrc)
	{
		return strcpy(pszDest, pszSrc);
	}

	static wchar_t* _StrCopy(wchar_t* pszDest, const wchar_t* pszSrc)
	{
		return wcscpy(pszDest, pszSrc);
	}

	static char* _StrCat(char* pszDest, const char* pszSrc)
	{
		return strcat(pszDest, pszSrc);
	}

	static wchar_t* _StrCat(wchar_t* pszDest, const wchar_t* pszSrc)
	{
		return wcscat(pszDest, pszSrc);
	}

	***/

	static int _GetFormattedLength(const char* pszFormat, va_list args)
	{
		return _vscprintf(pszFormat, args);
	}

	static int _GetFormattedLength(const wchar_t* pszFormat, va_list args)
	{
		return _vscwprintf(pszFormat, args);
	}

	static int _VSprintf(char* pszBuffer, const char* pszFormat, va_list args)
	{
		return vsprintf(pszBuffer, pszFormat, args);
	}

	static int _VSprintf(wchar_t* pszBuffer, const wchar_t* pszFormat, va_list args)
	{
		return vswprintf(pszBuffer, pszFormat, args);
	}

	static const char* _Null(char)
	{
		return "";
	}

	static const wchar_t* _Null(wchar_t)
	{
		return L"";
	}

private:
	TCharType*	m_pszData;
	size_t		m_iDataLen;
	size_t		m_iBufferLen;
};

typedef CBigStringT<char>			CBigStringA;
typedef CBigStringT<wchar_t>		CBigStringW;

#ifdef _UNICODE
	typedef CBigStringW	CBigString;
#else
	typedef CBigStringA	CBigString;
#endif
