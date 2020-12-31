// ===================================================================================================
// FILE: StdString.cpp
// AUTHOR: Joe O'Leary (with help -- see comments in StdString.h)
// REMARKS:
//		This file implements the CStdString class which was declared in
//		StdString.h.  It also implements some helper functions used for
//		our own UNICODE/ANSI conversion macros.
//
// ===================================================================================================

//#include "StdAfx.h"
#include "StdString.h"
#include <xutility>

#include <algorithm>
#include <functional>
#include <locale>

#ifdef _DEBUG
void _cdecl W32Trace(PCTSTR pszFormat, ...)
{
	va_list argList;
	va_start(argList, pszFormat);
	int nBuf;
	TCHAR szBuffer[512];
	nBuf = _vsntprintf(szBuffer, 511, pszFormat, argList);
	ASSERT(nBuf < 512);
	OutputDebugString(szBuffer);
	va_end(argList);
}
#endif


// If conversion has not been explicitly turned off...
#ifndef _NO_STDCONVERSION
	
	// Global MBCS-to-UNICODE helper function
	PWSTR  StdA2WHelper(PWSTR pw, PCSTR pa, int nChars)
	{
		if (pa == NULL)
			return NULL;
		ASSERT(pw != NULL);
		pw[0] = '\0';
		VERIFY(MultiByteToWideChar(CP_ACP, 0, pa, -1, pw, nChars));
		return pw;
	}

	// Global UNICODE-to_MBCS helper function
	PSTR  StdW2AHelper(PSTR pa, PCWSTR pw, int nChars)
	{
		if (pw == NULL)
			return NULL;
		ASSERT(pa != NULL);
		pa[0] = '\0';
		VERIFY(WideCharToMultiByte(CP_ACP, 0, pw, -1, pa, nChars, NULL, NULL));
		return pa;
	}

#endif // _NO_STDCONVERSION

#if !defined(_MFC_VER)
	HINSTANCE CStdString::hInstResource = ::GetModuleHandle(NULL);
#endif

// ---------------------------------------------------------------------------------------
// FUNCTION:  CStdString::Load
//		bool Load(UINT nId)
//           
// DESCRIPTION:
//		This function attempts to load the specified string resource from application's
//		resource table.
//
// PARAMETERS: 
//		nId - the resource Identifier from the string table.
//
// RETURN VALUE: 
//		true if the function succeeds, false otherwise
// ---------------------------------------------------------------------------------------
#define MAX_LOAD_TRIES	5			// max # of times we'll attempt to load a string
#define LOAD_BUF_SIZE	256
bool CStdString::Load(UINT nId)
{
	PCTSTR lpszName = MAKEINTRESOURCE((nId>>4)+1);
	HINSTANCE hModule = CStdString::GetResourceHandle();

	if ( ::FindResource(hModule, lpszName, RT_STRING) == NULL )
		return false;
	
	int nMaxLen = 0;
	int nRetLen = 0;
	int nTries = 0;
	PTSTR pBuf = NULL;

	// Keep looping until:
	//		we have a buffer big enough to hold the string,
	//		or we exceed the maximum number of tries,
	//		or there is an error

	do
	{
		nMaxLen += LOAD_BUF_SIZE;
		pBuf = reinterpret_cast<PTSTR>(_alloca((nMaxLen) * sizeof(TCHAR)));
		nRetLen = ::LoadString(hModule, nId, pBuf, nMaxLen);
		if ( nRetLen == 0 )
			TRACE(_T("Resource ID %d does not exist -- cannot load\n"), nId);
		else if ( nRetLen < 1 )
			TRACE(_T("Error 0x%X attempting to load resource %d\n"), ::GetLastError(), nId);
		else if ( nRetLen+1 < nMaxLen )
			*this = pBuf;

	} while ( nRetLen+1 == nMaxLen && nTries++ < MAX_LOAD_TRIES );

	return true;
}



// ---------------------------------------------------------------------------------------
// FUNCTION:  CStdString::Format
//		void _cdecl Formst(CStdString& PCTSTR pszFormat, ...)
//		void _cdecl Format(PCTSTR pszFormat);
//           
// DESCRIPTION:
//		This function does sprintf/wsprintf style formatting on CStdString objects.  It
//		is very much a copy of the MFC CString::Format function.  Some might even say
//		identical, however all these people are now dead (heh, heh, heh).
//
// PARAMETERS: 
//		nId - ID of string resource holding the format string
//		pszFormat - a PCTSTR holding the format specifiers
//		argList - a va_list holding the arguments for the format specifiers.
//
// RETURN VALUE:  None.
// ---------------------------------------------------------------------------------------
// formatting (using wsprintf style formatting)
void CStdString::Format(UINT nId, ...)
{
	va_list argList;
	va_start(argList, nId);

	CStdString strFmt;
	if ( strFmt.Load(nId) )
		FormatV(strFmt, argList);

	va_end(argList);
}
void CStdString::Format(PCTSTR pszFormat, ...)
{
	va_list argList;
	va_start(argList, pszFormat);
	FormatV(pszFormat, argList);
	va_end(argList);
}

// ---------------------------------------------------------------------------------------
// FUNCTION:  CStdString::FormatV
//		void FormatV(PCTSTR pszFormat, va_list, argList);
//           
// DESCRIPTION:
//		This function formats the string much like sprintf.  It tries a default buffer
//		size (FMT_BLOCK_SIZE) and keeps increasing until it gets it right.
//
// PARAMETERS: 
//		pszFormat - a PCTSTR holding the format of the output
//		argList - a Microsoft specific va_list for variable argument lists
//
// RETURN VALUE: 
// ---------------------------------------------------------------------------------------
#define MAX_FMT_TRIES	5
#define FMT_BLOCK_SIZE	256

void CStdString::FormatV(PCTSTR pszFormat, va_list argList)
{
	va_list argListSave = argList;

	// We're just going to use the normal _vsntprintf function, assuming FMT_BLOCK_SIZE characters.
	// However, if FMT_BLOCK_SIZE characters is not be enough, we will try 2 * FMT_BLOCK_SIZE, then
	// 3 * FMT_BLOCK_SIZE, up to MAX_FMT_TRIES * FMT_BLOCK_SIZE characters.

	this->erase();
	int nTriesLeft = MAX_FMT_TRIES-1;
	int nCharsUsed = - 1;
	int nTChars = 0;

	// Keep looping until either we succeed or we have exhausted the number of tries

	do
	
	{
		nTChars += FMT_BLOCK_SIZE;		// number of TCHARS in the string

		// Allocate a buffer on the stack to hold the characters and NULL terminate it

		TCHAR* pszBuf = reinterpret_cast<TCHAR*>(_alloca((nTChars+1) * sizeof(TCHAR)));
		pszBuf[nTChars+1] = '\0';

		// Now try the actual formatting.  Note that docs say even the wide version takes the number of BYTES
		// as the second argument, not the number of characters (TCHARs).

		nCharsUsed = _vsntprintf(pszBuf, nTChars+1, pszFormat, argListSave);
		if ( nCharsUsed >= 0 )
			*this = pszBuf;

	} while ( nCharsUsed < 0 && nTriesLeft > 0);

	va_end(argListSave);
}


class NotSpace : public std::unary_function<TCHAR, bool>
{
public:
	bool operator() (TCHAR tchar) { return !isspace(tchar); };
};


// ---------------------------------------------------------------------------------------
// FUNCTION:  CStdString::TrimRight
//		CStdString& TrimRight();
//
// DESCRIPTION:
//		This function removes any whitespace characters from the right end of the string.
//
// PARAMETERS: none
// RETURN VALUE:
//		a reference to this object (*this) -- allows chaining together of
//		these calls, eg. strTest.TrimRight().TrimLeft().ToUpper();
// ---------------------------------------------------------------------------------------
CStdString& CStdString::TrimRight()
{
	CStdString::reverse_iterator iter = std::find_if(rbegin(), rend(), NotSpace());
	if ( iter != rend() )
	{
		CStdString::size_type nNewSize = find_last_of(*iter);
		erase(nNewSize+1);
	}
	else
	{
		erase();
	}
	return *this;
}


// ---------------------------------------------------------------------------------------
// FUNCTION:  CStdString::TrimLeft
//		CStdString& TrimLeft();
//
// DESCRIPTION:
//		This function removes any whitespace characters from the left end of the string.
//
// PARAMETERS: none
// RETURN VALUE:
//		a reference to this object (*this) -- allows chaining together of
//		these calls, (eg. strTest.TrimRight().TrimLeft().ToUpper();)
// ---------------------------------------------------------------------------------------
CStdString& CStdString::TrimLeft()
{
	CStdString::iterator iter = std::find_if(begin(), end(), NotSpace());
	CStdString strNew(iter, end());
	STRBASE::assign(strNew);
	return *this;
}


// ---------------------------------------------------------------------------------------
// FUNCTION:  CStdString::ToUpper
//		CStdString& ToUpper()
//           
// DESCRIPTION:
//		This function converts the CStdString to all uppercase characters using ctype
//
// PARAMETERS: 
// RETURN VALUE: 
//		a reference to this object (*this) -- allows chaining together of
//		these calls, (eg. strTest.TrimRight().TrimLeft().ToUpper();)
// ---------------------------------------------------------------------------------------
CStdString& CStdString::ToUpper()
{
	static	const std::ctype<TCHAR> myCType;					// used for upper/lower conversion
	myCType.toupper(begin(), end());
	return *this;
}


// ---------------------------------------------------------------------------------------
// FUNCTION:  CStdString::ToLower
//		CStdString& ToLower()
//           
// DESCRIPTION:
//		This function converts the CStdString to all lowercase characters using ctype
//
// PARAMETERS: 
// RETURN VALUE: 
//		a reference to this object (*this) -- allows chaining together of
//		these calls, (eg. strTest.ToLower().TrimLeft().ToUpper();)
// ---------------------------------------------------------------------------------------
CStdString& CStdString::ToLower()
{
	static	const std::ctype<TCHAR> myCType;					// used for upper/lower conversion
	myCType.tolower(begin(), end());
	return *this;
}


// ---------------------------------------------------------------------------------------
// FUNCTION:  CStdString::CopyString
//		static void CopyString(PCTSTR p_szSource, PTSTR p_szDest, int p_nMaxChars=0);
//		static void CopyString(PCOSTR p_szSource, POSTR p_szDest, int p_nMaxChars=0);
//		static void CopyString(PCSTR p_szSource, PWSTR p_szDest, int p_nMaxChars=0);
//		static void CopyString(PCWSTR p_szSource, PSTR p_szDest, int p_nMaxChars=0);
//
// DESCRIPTION:
//		These 3 overloads simplify copying one C-style string into another.
//
// PARAMETERS: 
//		p_szSource - the string to be copied FROM.  May be either an MBCS string (char) or
//					 a wide string (wchar_t)
//		p_szDest - the string to be copied TO.  Also may be either MBCS or wide
//		p_nMaxChars - the maximum number of characters to be copied into p_szDest.  Note
//					  that this is expressed in whatever a "character" means to p_szDest.
//					  If p_szDest is a wchar_t type string than this will be the maximum
//					  number of wchar_ts that my be copied.  The p_szDest string must be
//					  large enought to hold least p_nMaxChars+1 characters.
//
// RETURN VALUE: none
// ---------------------------------------------------------------------------------------
void CStdString::CopyString(PCTSTR p_szSource, PTSTR p_szDest, int p_nMaxChars)
{
	int nSrcLen = ( p_szSource == NULL ? 0 : lstrlen(p_szSource) );
	int nChars = ( p_nMaxChars > 0 ? min(p_nMaxChars,nSrcLen) : nSrcLen );
	memcpy(p_szDest, p_szSource, nChars * sizeof(TCHAR));
	p_szDest[nChars] = '\0';
}
void CStdString::CopyString(PCOSTR p_szSource, POSTR p_szDest, int p_nMaxChars)
{
#ifdef _UNICODE
	int nSrcLen = ( p_szSource == NULL ? 0 : strlen(p_szSource) );
#else
	int nSrcLen = ( p_szSource == NULL ? 0 : wcslen(p_szSource) );
#endif
	int nChars = ( p_nMaxChars > 0 ? min(p_nMaxChars,nSrcLen) : nSrcLen );
	memcpy(p_szDest, p_szSource, nChars * sizeof(TOTHER));
	p_szDest[nChars] = '\0';
}
void CStdString::CopyString(PCSTR p_szSource, PWSTR p_szDest, int p_nMaxChars)
{
	USES_CONVERSION;
	PCWSTR szConverted = (A2W(p_szSource));
	int nSrcLen = ( szConverted == NULL ? 0 : wcslen(szConverted) );
	int nChars = ( p_nMaxChars > 0 ? min(p_nMaxChars,nSrcLen) : nSrcLen );
	memcpy(p_szDest, szConverted, nChars * sizeof(wchar_t));
	p_szDest[nChars] = '\0';
}
void CStdString::CopyString(PCWSTR p_szSource, PSTR p_szDest, int p_nMaxChars)
{
	USES_CONVERSION;
	PCSTR szConverted = (W2A(p_szSource));
	int nSrcLen = ( szConverted == NULL ? 0 : strlen(szConverted) );
	int nChars = ( p_nMaxChars > 0 ? min(p_nMaxChars,nSrcLen) : nSrcLen );
	memcpy(p_szDest, szConverted, nChars);
	p_szDest[nChars] = '\0';
}


// Operators that allow us to serialize CStdStrings to CArchives.
#ifdef _MFC_VER
	CArchive& AFXAPI operator<<(CArchive& ar, const CStdString& string)
	{
		USES_CONVERSION;

		// All CStdStrings are serialized as wide strings
		PCWSTR pWide = T2CW(string.data());
		int nChars = wcslen(pWide);
		ar << nChars;
		ar.Write(pWide, nChars*sizeof(wchar_t));
		return ar;
	}

	CArchive& AFXAPI operator>>(CArchive& ar, CStdString& string)
	{
		// All CStdStrings are serialized as wide strings
		UINT nLen;
		ar >> nLen;
		if ( nLen > 0 )
		{
			UINT nByteLen = nLen * sizeof(wchar_t);
			PWSTR pWide = (PWSTR)_alloca(nByteLen+sizeof(wchar_t));
			VERIFY(ar.Read(pWide, nByteLen) == nByteLen);
			pWide[nLen] = '\0';
			string = CStdString(pWide);
		}
		else
		{
			string.erase();
		}
		return ar;
	}
#endif
