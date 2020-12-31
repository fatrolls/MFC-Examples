// ResourceFile.cpp  Version 1.0 - article available at www.codeproject.com
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
//   DetachByteBuffer()     Return pointer to byte buffer and set flag so buffer
//                          will not be deleted when resource is closed
//   DuplicateByteBuffer()  Duplicate the buffer associated with the binary file 
//                          resource
//   GetByteBuffer()        Get pointer to binary file resource buffer
//   GetLength()            Get length of file resource
//   GetPosition()          Get current file position of file resource
//   IsAtEOF()              Check if file pointer is at end of file
//   IsOpen()               Check if file resource is open
//   Open()                 Open a file resource
//   Read()                 Read bytes from the binary file resource
//   Seek()                 Move pointer to specified position in resource buffer
//   SeekToBegin()          Position pointer to beginning of resource buffer
//   SeekToEnd()            Position pointer to end of resource buffer
//   SetByteBuffer()        Set a new buffer for the binary file resource
//
///////////////////////////////////////////////////////////////////////////////

#define STRICT
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <malloc.h>
#include <crtdbg.h>
#include "ResourceFile.h"

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
CResourceFile::CResourceFile()
  : m_pBytes(NULL),
	m_bText(FALSE),
	m_nBufLen(0),
	m_nPosition(0),
	m_bIsOpen(FALSE),
	m_bDoNotDeleteBuffer(FALSE)
{
	TRACE(_T("in CResourceFile::CResourceFile\n"));
}

///////////////////////////////////////////////////////////////////////////////
// copy ctor
CResourceFile::CResourceFile(const CResourceFile& rf)
{
	TRACE(_T("in CResourceFile::CResourceFile(const CResourceFile& rf)\n"));

	if (rf.m_bDoNotDeleteBuffer)
	{
		// buffer is allocated externally or has been detached
		m_pBytes = rf.m_pBytes;
	}
	else
	{
		m_pBytes = new BYTE [rf.m_nBufLen + 2];
		memset(m_pBytes, 0, rf.m_nBufLen+2);
		memcpy(m_pBytes, rf.m_pBytes, rf.m_nBufLen);
	}

	m_nBufLen = rf.m_nBufLen;
	m_nPosition = 0;
	m_bIsOpen = rf.m_bIsOpen;
	m_bText = rf.m_bText;
	m_bDoNotDeleteBuffer = rf.m_bDoNotDeleteBuffer;
}

///////////////////////////////////////////////////////////////////////////////
// assignment operator
CResourceFile& CResourceFile::operator=(const CResourceFile& rf)
{
	TRACE(_T("in CResourceFile::operator=\n"));

	if (m_pBytes != rf.m_pBytes)		// check for a = a
	{
		if (m_pBytes && !m_bDoNotDeleteBuffer)
			delete [] m_pBytes;

		if (rf.m_bDoNotDeleteBuffer)
		{
			// buffer is allocated externally or has been detached
			m_pBytes = rf.m_pBytes;
		}
		else
		{
			m_pBytes = new BYTE [rf.m_nBufLen + 2];
			memset(m_pBytes, 0, rf.m_nBufLen+2);
			memcpy(m_pBytes, rf.m_pBytes, rf.m_nBufLen);
		}

		m_nBufLen = rf.m_nBufLen;
		m_nPosition = 0;
		m_bIsOpen = rf.m_bIsOpen;
		m_bText = rf.m_bText;
		m_bDoNotDeleteBuffer = rf.m_bDoNotDeleteBuffer;
	}

	return *this;
}

///////////////////////////////////////////////////////////////////////////////
// dtor
CResourceFile::~CResourceFile()
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
//
// Returns:     BOOL           - returns TRUE if resource opened ok, otherwise FALSE
//
BOOL CResourceFile::Open(HINSTANCE hInstance, 
						 LPCTSTR lpszResId, 
						 LPCTSTR lpszResType)
{
	BOOL rc = FALSE;

	Close();

	_ASSERTE(lpszResId);
	_ASSERTE(lpszResType);

	if (lpszResId && lpszResType)
	{
		TCHAR *pszRes = NULL;

		// is this a resource name string or an id?
		if (HIWORD(lpszResId) == 0)
		{
			// id
			pszRes = MAKEINTRESOURCE(LOWORD((UINT)(UINT_PTR)lpszResId));
		}
		else
		{
			// string
			pszRes = (TCHAR *)lpszResId;
			TRACE(_T("pszRes=%s\n"), pszRes);
		}

		HRSRC hrsrc = FindResource(hInstance, pszRes, lpszResType);
		_ASSERTE(hrsrc);

		if (hrsrc)
		{
			DWORD dwSize = SizeofResource(hInstance, hrsrc);	// in bytes
			TRACE(_T("dwSize=%d\n"), dwSize);

			HGLOBAL hglob = LoadResource(hInstance, hrsrc);
			_ASSERTE(hglob);

			if (hglob)
			{
				LPVOID lplock = LockResource(hglob);
				_ASSERTE(lplock);

				if (lplock)
				{
					// save resource as byte buffer

					m_pBytes = new BYTE [dwSize+16];
					memset(m_pBytes, 0, dwSize+16);
					m_nBufLen = (int) dwSize;
					memcpy(m_pBytes, lplock, m_nBufLen);

					m_nPosition = 0;
					m_bIsOpen = TRUE;
					m_bDoNotDeleteBuffer = FALSE;	// ok to delete the buffer
					rc = TRUE;
				}
			}
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
void CResourceFile::Close()
{
	TRACE(_T("in CResourceFile::Close\n"));
	m_bIsOpen = FALSE;
	if (m_pBytes && !m_bDoNotDeleteBuffer)
		delete [] m_pBytes;
	m_pBytes = NULL;
	m_nBufLen = 0;
	m_nPosition = 0;
}

///////////////////////////////////////////////////////////////////////////////
//
// DetachByteBuffer()
//
// Purpose:     Returns pointer to byte buffer and sets flag so that the buffer
//              will not be deleted when resource is closed;  caller must 
//              delete buffer with delete.
//
// Parameters:  None
//
// Returns:     BYTE * - returns pointer to buffer, or NULL if not open or text
//
BYTE * CResourceFile::DetachByteBuffer()
{
	BYTE *p = NULL;

	if (m_bIsOpen && !m_bText)
	{
		m_bDoNotDeleteBuffer = TRUE; 
		p = m_pBytes;
	}
	
	return p;
}

///////////////////////////////////////////////////////////////////////////////
//
// DuplicateByteBuffer()
//
// Purpose:     Duplicate the buffer associated with the binary file resource
//
// Parameters:  None
//
// Returns:     BYTE * - returns pointer to duplicated buffer, or NULL
//
// Notes:       The buffer is duplicated by calling the function malloc().
//              It must be freed by the caller by using the free() function.
//
BYTE * CResourceFile::DuplicateByteBuffer()
{
	BYTE *dup = NULL;

	if (IsOpen() && !m_bText)
	{
		dup = (BYTE *) malloc(m_nBufLen+2);
		memset(dup, 0, m_nBufLen+2);
		memcpy(dup, m_pBytes, m_nBufLen);
	}

	return dup;
}

///////////////////////////////////////////////////////////////////////////////
//
// SetByteBuffer()
//
// Purpose:     Set a new buffer for the binary file resource.  This may be 
//              useful if the buffer is obtained from some external source,
//              and you wish to treat it like an in-memory file.
//
// Parameters:  buf - pointer to new buffer
//              len - buffer length in bytes
//
// Returns:     None
//
void CResourceFile::SetByteBuffer(BYTE * buf, DWORD len)
{
	_ASSERTE(buf);
	_ASSERTE(len != 0);
	_ASSERTE(m_pBytes == NULL);

	if (buf && (len > 0))
	{
		m_pBytes = buf;
		m_nBufLen = len;
		m_bText = FALSE;
		m_bDoNotDeleteBuffer = TRUE;	// do not delete this buffer
		m_bIsOpen = TRUE;
	}
	else
	{
		TRACE(_T("ERROR - SetByteBuffer: bad parameters\n"));
	}
}

///////////////////////////////////////////////////////////////////////////////
//
// Read()
//
// Purpose:     Read bytes from the binary file resource
//
// Parameters:  buf     - pointer to buffer that receives bytes
//              nBufLen - buffer length in bytes
//
// Returns:     int     - number of bytes returned
//
// Notes:       To determine how large the buffer should be, call Read() first 
//              with a NULL buf parameter - this will return the size of the 
//              required buffer.
//
int CResourceFile::Read(BYTE *buf, int nBufLen)
{
	int nOldPosition = m_nPosition;
	int nIndex = 0;
	if (buf)
		*buf = _T('\0');

	if (m_bIsOpen && m_pBytes && !m_bText)
	{
		while (!IsAtEOF())
		{
			BYTE b = m_pBytes[m_nPosition++];

			if (buf && (nIndex < nBufLen))
				buf[nIndex] = b;

			nIndex++;
		}
	}

	// if we were just getting buffer size, restore position
	if (!buf)
		m_nPosition = nOldPosition;

	return nIndex;
}

///////////////////////////////////////////////////////////////////////////////
//
// SeekToBegin()
//
// Purpose:     Position pointer to beginning of resource file buffer
//
// Parameters:  None
//
// Returns:     int - new file position (zero based), or -1
//
int CResourceFile::SeekToBegin()
{
	return Seek(0, SEEK_SET);
}

///////////////////////////////////////////////////////////////////////////////
//
// SeekToEnd()
//
// Purpose:     Position pointer to end of resource file buffer
//
// Parameters:  None
//
// Returns:     int - new file position (zero based), or -1
//
int CResourceFile::SeekToEnd()
{
	return Seek(0, SEEK_END);
}

///////////////////////////////////////////////////////////////////////////////
//
// Seek()
//
// Purpose:     Move pointer to specified position in resource file buffer
//
// Parameters:  offset - number of TCHARs/bytes from origin (can be negative)
//              origin - initial position; must be one of:
//                          SEEK_SET = beginning of file
//                          SEEK_CUR = current position of file pointer
//                          SEEK_END = end of file
//
// Returns:     int - new file position (zero based), or -1
//
int CResourceFile::Seek(int offset, int origin)
{
	int rc = -1;

	if (IsOpen())
	{
		switch (origin)
		{
			default:
			case SEEK_SET:		// beginning of file
				if (offset <= m_nBufLen)
				{
					m_nPosition = offset;
					rc = m_nPosition;
				}
				break;

			case SEEK_CUR:		// current position of file pointer
				if ((m_nPosition + offset) <= m_nBufLen)
				{
					m_nPosition += offset;
					rc = m_nPosition;
				}
				break;

			case SEEK_END:		// end of file
				m_nPosition = m_nBufLen;
				rc = m_nPosition;
				break;
		}
	}

	return rc;
}
