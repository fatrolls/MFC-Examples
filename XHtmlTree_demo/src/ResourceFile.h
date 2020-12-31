// ResourceFile.h  Version 1.0 - article available at www.codeproject.com
//
// Author:  Hans Dietrich
//          hdietrich@gmail.com
//
// License:
//     This software is released into the public domain.  You are free to use
//     it in any way you like, except that you may not sell this source code.
//
//     This software is provided "as is" with no expressed or implied warranty.
//     I accept no liability for any damage or loss of business that this 
//     software may cause.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef RESOURCEFILE_H
#define RESOURCEFILE_H

class CResourceFile
{
// Construction
public:
	CResourceFile();
	CResourceFile(const CResourceFile&);
	CResourceFile& operator=(const CResourceFile&);
	virtual ~CResourceFile();

// Attributes
	BYTE *	GetByteBuffer()			{ return m_pBytes; }
	int		GetLength()				{ return m_nBufLen; }
	int		GetPosition()			{ return m_nPosition; }
	BOOL	IsAtEOF()				{ return m_nPosition >= GetLength(); }
	BOOL	IsOpen()				{ return m_bIsOpen; }

// Operations
public:
	virtual void	Close();
	virtual BYTE *	DetachByteBuffer();
	virtual BYTE *	DuplicateByteBuffer();
	virtual BOOL	Open(HINSTANCE hInstance, 
					LPCTSTR lpszResId, 
					LPCTSTR lpszResType);
	virtual int		Read(BYTE *buf, int nBufLen);
	virtual int		Seek(int offset, int origin); 
	virtual int		SeekToBegin();
	virtual int		SeekToEnd();
	virtual void	SetByteBuffer(BYTE * buf, DWORD len);

// Implementation
protected:
	BYTE  *		m_pBytes;				// binary buffer
	int			m_nBufLen;				// size of m_pszResource: TCHARs for text, 
										// bytes for binary
	int			m_nPosition;			// buffer position: TCHARs for text, 
										// bytes for binary
	BOOL		m_bText;				// TRUE = text, FALSE = binary
	BOOL		m_bIsOpen;				// TRUE = text file resource is open
	BOOL		m_bDoNotDeleteBuffer;	// TRUE = buffer allocated externally
										// or detached; do not delete
};

#endif //RESOURCEFILE_H
