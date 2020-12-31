// ResourceTextFile.cpp  Version 1.0 - article available at www.codeproject.com
//
// Author:  Hans Dietrich
//          hdietrich@gmail.com
//
// History
//     Version 1.0 - 2007 July 4
//     - Initial public release
//
// License:
//     This software is released into the public domain.  You are free to use
//     it in any way you like, except that you may not sell this source code.
//
//     This software is provided "as is" with no expressed or implied warranty.
//     I accept no liability for any damage or loss of business that this 
//     software may cause.
//
// Public APIs:
//           NAME                              DESCRIPTION
//   ---------------------  ----------------------------------------------------
//   Close()                Close a file resource
//   DetachTextBuffer()     Return pointer to text buffer and set flag so buffer
//                          will not be deleted when resource is closed
//   DuplicateTextBuffer()  Duplicate the buffer associated with the text file 
//                          resource
//   GetBomAction()         Get acction to take for BOM
//   GetConvertAction()	    Get convert action
//   GetTextBuffer()        Get pointer to text file resource buffer
//   Open()                 Open a file resource
//   ReadLine()             Read a line of text from the text file resource
//   SetTextBuffer()        Set a new buffer for the text file resource
//
///////////////////////////////////////////////////////////////////////////////

#define STRICT
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <tchar.h>
#include <malloc.h>
#include <crtdbg.h>
#include "ResourceTextFile.h"

#ifndef __noop
#if _MSC_VER < 1300
#define __noop ((void)0)
#endif
#endif

#undef TRACE
#define TRACE __noop

// if you want to see the TRACE output, 
// uncomment this line:
//#include "XTrace.h"

#pragma warning(disable : 4127)	// conditional expression is constant (_ASSERTE)
#pragma warning(disable : 4996)	// disable bogus deprecation warning

///////////////////////////////////////////////////////////////////////////////
// ctor
CResourceTextFile::CResourceTextFile()
  : m_pszText(NULL),
	m_eBomAction(NoBomAction),
	m_eConvertAction(NoConvertAction)
{
	TRACE(_T("in CResourceTextFile::CResourceTextFile\n"));
	m_bText = TRUE;
}

///////////////////////////////////////////////////////////////////////////////
// copy ctor
CResourceTextFile::CResourceTextFile(const CResourceTextFile& rf)
{
	TRACE(_T("in CResourceTextFile::CResourceTextFile(const CResourceTextFile& rf)\n"));

	if (rf.m_bDoNotDeleteBuffer)
	{
		// buffer is allocated externally or has been detached
		m_pszText = rf.m_pszText;
	}
	else
	{
		m_pszText = new TCHAR [rf.m_nBufLen + 2];
		memset(m_pszText, 0, (rf.m_nBufLen+2)*sizeof(TCHAR));
		_tcsncpy(m_pszText, rf.m_pszText, rf.m_nBufLen);
	}

	m_nBufLen = rf.m_nBufLen;
	m_nPosition = 0;
	m_bIsOpen = rf.m_bIsOpen;
	m_bText = rf.m_bText;
	m_bDoNotDeleteBuffer = rf.m_bDoNotDeleteBuffer;
	m_eConvertAction = rf.m_eConvertAction;
	m_eBomAction = rf.m_eBomAction;
}

///////////////////////////////////////////////////////////////////////////////
// assignment operator
CResourceTextFile& CResourceTextFile::operator=(const CResourceTextFile& rf)
{
	TRACE(_T("in CResourceTextFile::operator=\n"));
	if (m_pszText != rf.m_pszText)		// check for a = a
	{
		if (m_pszText && !m_bDoNotDeleteBuffer)
			delete [] m_pszText;

		if (rf.m_bDoNotDeleteBuffer)
		{
			// buffer is allocated externally or has been detached
			m_pszText = rf.m_pszText;
		}
		else
		{
			m_pszText = new TCHAR [rf.m_nBufLen + 2];
			memset(m_pszText, 0, (rf.m_nBufLen+2)*sizeof(TCHAR));
			_tcsncpy(m_pszText, rf.m_pszText, rf.m_nBufLen);
		}

		m_nBufLen = rf.m_nBufLen;
		m_nPosition = 0;
		m_bIsOpen = rf.m_bIsOpen;
		m_bText = rf.m_bText;
		m_bDoNotDeleteBuffer = rf.m_bDoNotDeleteBuffer;
		m_eConvertAction = rf.m_eConvertAction;
		m_eBomAction = rf.m_eBomAction;
	}

	return *this;
}

///////////////////////////////////////////////////////////////////////////////
// dtor
CResourceTextFile::~CResourceTextFile()
{
	Close();
}

///////////////////////////////////////////////////////////////////////////////
//
// Open()
//
// Purpose:     Open a file resource
//
// Parameters:  hInstance      - instance handle for the resource.  A value of 
//                               NULL specifies the exe (default).
//              lpszResId      - resource name or id (passed via MAKEINTRESOURCE)
//              lpszResType    - resource type string to look for
//              eConvertAction - convert action to take
//              eBomAction     - action to take with BOM
//
// Returns:     BOOL           - returns TRUE if resource opened ok, otherwise FALSE
//
BOOL CResourceTextFile::Open(HINSTANCE hInstance, 
							 LPCTSTR lpszResId, 
							 LPCTSTR lpszResType /*= _T("TEXT")*/,
							 ConvertAction eConvertAction /*= NoConvertAction*/,
							 BomAction eBomAction /*= NoBomAction*/)
{
	BOOL rc = FALSE;

	Close();

	_ASSERTE(lpszResId);
	_ASSERTE(lpszResType);

	m_eConvertAction = eConvertAction;
	TRACE(_T("m_eConvertAction=%d\n"), m_eConvertAction);
	m_eBomAction = eBomAction;
	TRACE(_T("m_eBomAction=%d\n"), m_eBomAction);

	if (lpszResId && lpszResType)
	{
		rc = CResourceFile::Open(hInstance, lpszResId, lpszResType);

		if (rc)
		{
			TCHAR *cp = (TCHAR *) GetByteBuffer();
			DWORD dwSize = (DWORD) GetLength();
			TRACE(_T("dwSize=%d\n"), dwSize);

			rc = SetTextBuffer(cp, dwSize, 
					eConvertAction, eBomAction);

			if (rc)
			{
				m_bText = TRUE;
			}
			else
			{
				TRACE(_T("ERROR SetTextBuffer failed\n"));
				Close();
			}
		}
		else
		{
			TRACE(_T("ERROR Open failed\n"));
		}
	}

	return rc;
}

///////////////////////////////////////////////////////////////////////////////
//
// Close()
//
// Purpose:     Close a file resource, free memory if necessary
//
// Parameters:  None
//
// Returns:     None
//
void CResourceTextFile::Close()
{
	TRACE(_T("in CResourceTextFile::Close\n"));
	CResourceFile::Close();

	if (m_pszText && !m_bDoNotDeleteBuffer)
		delete [] m_pszText;
	m_pszText = NULL;
}

///////////////////////////////////////////////////////////////////////////////
//
// DetachTextBuffer()
//
// Purpose:     Returns pointer to text buffer and sets flag so that the buffer
//              will not be deleted when resource is closed;  caller must 
//              delete buffer with delete.
//
// Parameters:  None
//
// Returns:     TCHAR * - returns pointer to buffer, or NULL if not open 
//                        or not text.
//
TCHAR * CResourceTextFile::DetachTextBuffer()
{
	TCHAR *cp = NULL;

	if (m_bIsOpen && m_bText)
	{
		m_bDoNotDeleteBuffer = TRUE; 
		cp = m_pszText;
	}
	
	return cp; 
}

///////////////////////////////////////////////////////////////////////////////
//
// DuplicateTextBuffer()
//
// Purpose:     Duplicate the buffer associated with the text file resource
//
// Parameters:  None
//
// Returns:     TCHAR * - returns pointer to duplicated buffer, or NULL
//
// Notes:       The buffer is duplicated by calling the function _tcsdup().
//              It must be freed by the caller by using the free() function.
//
TCHAR * CResourceTextFile::DuplicateTextBuffer()
{
	TCHAR *dup = NULL;

	if (IsOpen() && m_bText)
		dup = _tcsdup(m_pszText);

	return dup;
}

///////////////////////////////////////////////////////////////////////////////
//
// SetTextBuffer()
//
// Purpose:     Set a new buffer for the text file resource.  This may be 
//              useful if the buffer is obtained from some external source,
//              and you wish to treat it like an in-memory text file.
//
// Parameters:  inbuf          - pointer to new buffer
//              len            - buffer length in bytes
//              eConvertAction - convert action to take
//              eBomAction     - action to take with BOM
//
// Returns:     None
//
BOOL CResourceTextFile::SetTextBuffer(TCHAR * inbuf, 
									  DWORD len,
									  ConvertAction eConvertAction /*= NoConvertAction*/, 
									  BomAction eBomAction /*= NoBomAction*/)
{
	TRACE(_T("in CResourceTextFile::SetTextBuffer:  len=%d\n"), len);

	BOOL rc = FALSE;

	_ASSERTE(inbuf);
	_ASSERTE(len != 0);
	_ASSERTE(m_pszText == NULL);

	if (inbuf && (len != 0))
	{
		m_bText = TRUE;

		m_eConvertAction = eConvertAction;
		TRACE(_T("m_eConvertAction=%d\n"), m_eConvertAction);
		m_eBomAction = eBomAction;
		TRACE(_T("m_eBomAction=%d\n"), m_eBomAction);

		DWORD dwSize = len;		// bytes

		// copy buffer to ensure it's null terminated
		BYTE * buf = new BYTE [dwSize+16];
		memset(buf, 0, dwSize+16);
		memcpy(buf, inbuf, dwSize);

		BOOL bFoundBom = (buf[0] == 0xFF) && (buf[1] == 0xFE);

		if (m_eConvertAction == ConvertToUnicode)
		{
			TRACE(_T("converting to unicode\n"));
			int wlen = MultiByteToWideChar(CP_ACP, 0, (LPCSTR)buf, -1, NULL, 0);
			TRACE(_T("wlen=%d\n"), wlen);
#ifndef _UNICODE
			wlen = wlen * sizeof(WCHAR);
#endif
			m_pszText = new TCHAR [wlen+16];
			memset(m_pszText, 0, (wlen+16)*sizeof(TCHAR));
			LPWSTR wp = (LPWSTR) m_pszText;
			if ((m_eBomAction == AddBom) && !bFoundBom)
			{
				// caller wants a BOM
				BYTE * p = (BYTE *)m_pszText;
				p[0] = 0xFF;
				p[1] = 0xFE;
				wp += 1;
			}
			MultiByteToWideChar(CP_ACP, 0, (LPCSTR)buf, -1, wp, wlen+2);
			m_nBufLen = (int)wcslen((WCHAR*)m_pszText);
		}
		else if (m_eConvertAction == ConvertToAnsi)
		{
			TRACE(_T("converting to ansi\n"));
			LPCWSTR wp = (LPCWSTR) buf;
			if (bFoundBom && (m_eBomAction == RemoveBom))
				wp++;	// skip over BOM
			int alen = WideCharToMultiByte(CP_ACP, 0, wp, -1,
							NULL, 0, NULL, NULL);
			TRACE(_T("alen=%d\n"), alen);
			m_pszText = new TCHAR [alen+4];
			memset(m_pszText, 0, (alen+4)*sizeof(TCHAR));
			WideCharToMultiByte(CP_ACP, 0, wp, -1, 
				(LPSTR)m_pszText, alen+1, NULL, NULL);
			m_nBufLen = (int)strlen((LPCSTR)m_pszText);
		}
		else
		{
			// no conversion
			m_pszText = new TCHAR [(dwSize + 16)/sizeof(TCHAR)];
			TCHAR *cp = m_pszText;
			memset(m_pszText, 0, dwSize+8);
			int index = 0;
			if ((m_eBomAction == AddBom) && !bFoundBom)
			{
				BYTE bom[2] = { 0xFF, 0xFE };
				memcpy(cp, bom, 2);
				cp += 2;
			}
			else if ((m_eBomAction == RemoveBom) && bFoundBom)
			{
				index = 2;
			}
			memcpy(cp, &buf[index], dwSize);
			m_nBufLen = (int)_tcslen(m_pszText);
		}
		TRACE(_T("m_nBufLen=%d\n"), m_nBufLen);

		m_nPosition = 0;
		m_bIsOpen = TRUE;
		m_bDoNotDeleteBuffer = FALSE;	// ok to delete the buffer
		delete [] buf;
		rc = TRUE;
	}

	return rc;
}

///////////////////////////////////////////////////////////////////////////////
//
// ReadLine()
//
// Purpose:     Read a line of text from the text file resource
//
// Parameters:  buf     - pointer to buffer that receives TCHARs
//              nBufLen - buffer length in TCHARs
//
// Returns:     int     - line length in TCHARs
//
// Notes:       Carriage returns and line feeds are discarded. The line will
//              always be terminated with a nul (the last character read may 
//              be lost).  To determine how large the buffer should be, call
//              ReadLine() first with a NULL buf parameter - this will return
//              the size of the required line buffer.
//
int CResourceTextFile::ReadLine(TCHAR *buf, int nBufLen)
{
	TRACE(_T("m_nPosition=%d\n"), m_nPosition);

	int nOldPosition = m_nPosition;
	int nIndex = 0;
	if (buf)
		*buf = _T('\0');

	if (m_bIsOpen && m_pszText && m_bText)
	{
		while (!IsAtEOF())
		{
			TCHAR c = m_pszText[m_nPosition++];

			if ((c == _T('\r')) || (c == _T('\n')))
			{
				if (!IsAtEOF())
				{
					// check for \r\n pair
					TCHAR prevc = c;
					c = m_pszText[m_nPosition];
					if (((prevc == _T('\r')) && (c == _T('\n'))) ||
						((prevc == _T('\n')) && (c == _T('\r'))))
					{
						m_nPosition++;
					}
				}
				break;	// end of line
			}

			if (buf && (nIndex < nBufLen))
				buf[nIndex] = c;
			nIndex++;
		}
	}

	// add terminating nul always
	if (buf)
	{
		if (nIndex >= nBufLen)
		{
			// there is not enough room, so replace last char
			nIndex = nBufLen - 1;
			if (nIndex < 0)
				nIndex = 0;
		}
		buf[nIndex] = _T('\0');
	}

	// if we were just getting buffer size, restore position
	if (!buf)
	{
		m_nPosition = nOldPosition;
	}
	else
	{
		TRACE(_T("buf=<%s>\n"), buf);
	}

	TRACE(_T("m_nPosition=%d\n"), m_nPosition);
	TRACE(_T("nIndex=%d\n"), nIndex);

	return nIndex;
}
