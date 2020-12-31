// ResourceTextFile.h  Version 1.0 - article available at www.codeproject.com
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

#ifndef RESOURCETEXTFILE_H
#define RESOURCETEXTFILE_H

#include "ResourceFile.h"

class CResourceTextFile : public CResourceFile
{
// Construction
public:
	CResourceTextFile();
	CResourceTextFile(const CResourceTextFile&);
	CResourceTextFile& operator=(const CResourceTextFile&);
	virtual ~CResourceTextFile();

// Attributes
	enum ConvertAction
	{
		NoConvertAction = 0, ConvertToUnicode, ConvertToAnsi
	};

	enum BomAction
	{
		NoBomAction = 0, RemoveBom, AddBom
	};

	TCHAR *	DuplicateTextBuffer();
	TCHAR *	GetTextBuffer()				{ return m_pszText; }
	BomAction	GetBomAction()			{ return m_eBomAction; }
	ConvertAction GetConvertAction()	{ return m_eConvertAction; }

// Operations
public:
	void	Close();
	TCHAR *	DetachTextBuffer();
	BOOL	Open(HINSTANCE hInstance, 
				 LPCTSTR lpszResId, 
				 LPCTSTR lpszResType = _T("TEXT"),
				 ConvertAction eConvert = NoConvertAction, 
				 BomAction eBomAction = NoBomAction);
	int		ReadLine(TCHAR *buf, int nBufLen);
	BOOL	SetTextBuffer(TCHAR * buf, DWORD len, 
						  ConvertAction eConvert = NoConvertAction, 
						  BomAction eBomAction = NoBomAction);

// Implementation
protected:
	TCHAR *			m_pszText;			// text file buffer
	BomAction		m_eBomAction;		// BOM action requested at file open
	ConvertAction	m_eConvertAction;	// conversion requested at file open
};

#endif //RESOURCETEXTFILE_H
