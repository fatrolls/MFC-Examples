
//////////////////////////////////////////////////////////////////////
// StringEx.cpp
//

#include "stdafx.h"
#include "StringEx.h"


// Insert	- Inserts a sub string into the string
// Returns	- Reference to the same string object
// pos		- Position to insert at. Extends the string with spaces if needed
// s		- Sub string to insert
CStringEx& CStringEx::Insert(int pos, LPCTSTR s)
{
	int len = lstrlen(s);
	if ( len == 0 )
		return *this;

	int oldlen = GetLength();
	int newlen = oldlen + len;
	LPTSTR str;
	if ( pos >= oldlen ) 
	{			
		// insert after end of string
		newlen += pos - oldlen ;
		str = GetBuffer( newlen );
		_tcsnset( str+oldlen, _T(' '), pos-oldlen );
		_tcsncpy( str+pos, s, len );
	} 
	else 
	{	
		// normal insert
		str = GetBuffer( newlen );
		memmove( str+pos+len, str+pos, sizeof(_T(' ')) *(oldlen-pos) );
		_tcsncpy( str+pos, s, len );
	}
	ReleaseBuffer( newlen );

	return *this;
}


// Insert	- Inserts a character into the string
// Returns	- Reference to the same string object
// pos		- Position to insert at. Extends the string with spaces if needed
// c		- Char to insert
CStringEx& CStringEx::Insert(int pos, TCHAR c)
{
	TCHAR buf[2];
	buf[0] = c;
	buf[1] = _T('\0');
	return Insert( pos, buf );
}


// Delete	- Deletes a segment of the string and resizes it
// Returns	- Reference to the same string object
// pos		- Position of the string segment to remove
// len		- Number of characters to remove
CStringEx& CStringEx::Delete(int pos, int len)
{
	int strLen = GetLength();

	if( pos >= strLen)
		return *this;
	if(len < 0 ||len > strLen - pos)
		len = strLen - pos;

	LPTSTR str = GetBuffer( strLen );
	memmove(str+pos, str+pos+len, sizeof(_T(' ')) *(strLen-(pos+len)));

	ReleaseBuffer( strLen - len );

	return *this;
}


// Replace	- Replaces a substring with another
// Returns	- Reference to the same string object
// pos		- Position of the substring
// len		- Length of substring to be replaced
// s		- New substring
CStringEx& CStringEx::Replace(int pos, int len, LPCTSTR s)
{
	Delete(pos, len);
	Insert(pos, s);

	return *this;
}


// Find 	- Finds the position of a character in a string
// Returns	- A zero-based index
// ch		- Character to look for
// startpos	- Position to start looking from
int CStringEx::Find( TCHAR ch, int startpos /*= 0*/ ) const
{
	// find first single character
	LPTSTR lpsz = _tcschr(m_pchData + startpos, (_TUCHAR)ch);

	// return -1 if not found and index otherwise
	return (lpsz == NULL) ? -1 : (int)(lpsz - m_pchData);
}


// Find 	- Finds the position of a substring in a string
// Returns	- A zero-based index
// lpszSub	- Substring to look for
// startpos	- Position to start looking from
int CStringEx::Find( LPCTSTR lpszSub, int startpos /*= 0*/ ) const
{
	ASSERT(AfxIsValidString(lpszSub, FALSE));

	// find first matching substring
	LPTSTR lpsz = _tcsstr(m_pchData+startpos, lpszSub);

	// return -1 for not found, distance from beginning otherwise
	return (lpsz == NULL) ? -1 : (int)(lpsz - m_pchData);
}


// FindNoCase	- Case insensitive find
// Returns	- A zero-based index
// ch		- Char to search for
// startpos 	- Position to start looking from
int CStringEx::FindNoCase( TCHAR ch, int startpos /*= 0*/ ) const
{
	unsigned int locase = Find( tolower( ch ), startpos );
	unsigned int upcase = Find( toupper( ch ), startpos );

	return locase < upcase ? locase : upcase;
}


// FindNoCase	- Case insensitive find
// Returns	- A zero-based index
// lpszSub	- Substring to search for
// startpos 	- Position to start looking from
int CStringEx::FindNoCase( LPCTSTR lpszSub, int startpos /*= 0*/ ) const
{
	CStringEx sLowerThis = *this;
	sLowerThis.MakeLower();

	CStringEx sLowerSub = lpszSub;
	sLowerSub.MakeLower();

	return sLowerThis.Find( sLowerSub, startpos );
}


// FindReplace		- Find a substring and replace with another
// Returns		- Number of instances replaced
// lpszSub		- Substring to look for
// lpszReplaceWith	- Substring to replace with
// bGlobal		- Flag to indicate whether all occurances 
//					  should be replaced
int CStringEx::FindReplace( LPCTSTR lpszSub, LPCTSTR lpszReplaceWith, 
					BOOL bGlobal /*= TRUE*/ )
{
	int iReplaced = 0;

	// find first matching substring
	LPTSTR lpsz;
	
	int pos = 0;
	int lenSub = lstrlen( lpszSub );
	int lenReplaceWith = lstrlen( lpszReplaceWith );
	while( (lpsz = _tcsstr(m_pchData + pos, lpszSub)) != NULL )
	{
		pos = (int)(lpsz - m_pchData);
		Replace( pos, lenSub, lpszReplaceWith );
		pos += lenReplaceWith;
		iReplaced++;
		if( !bGlobal ) break;
	}

	return iReplaced;
}


// FindReplaceNoCase	- Find a substring and replace with another
//			  Does case insensitive search
// Returns		- Number of instances replaced
// lpszSub		- Substring to look for
// lpszReplaceWith	- Substring to replace with
// bGlobal		- Flag to indicate whether all occurances 
//			  should be replaced
int CStringEx::FindReplaceNoCase( LPCTSTR lpszSub, LPCTSTR lpszReplaceWith, 
					 BOOL bGlobal /*= TRUE*/ )
{
	CStringEx sLowerThis = *this;
	sLowerThis.MakeLower();

	CStringEx sLowerSub = lpszSub;
	sLowerSub.MakeLower();

	int iReplaced = 0;

	// find first matching substring
	LPTSTR lpsz;
	
	int pos = 0, offset = 0;
	int lenSub = lstrlen( lpszSub );
	int lenReplaceWith = lstrlen( lpszReplaceWith );
	while( (lpsz = _tcsstr(sLowerThis.m_pchData + pos, sLowerSub.m_pchData)) != NULL )
	{
		pos = (int)(lpsz - sLowerThis.m_pchData);
		Replace( pos+offset, lenSub, lpszReplaceWith );
		offset += lenReplaceWith - lenSub;
		pos += lenSub;
		iReplaced++;
		if( !bGlobal ) break;
	}

	return iReplaced;
}


// ReverseFind	- Searches for the last match of a substring
// Returns	- A zero-based index
// lpszSub	- Substring to search for
// startpos 	- Position to start looking from, in reverse dir
int CStringEx::ReverseFind( LPCTSTR lpszSub, int startpos /*= -1*/ ) const
{
	int lenSub = lstrlen( lpszSub );
	int len = lstrlen( m_pchData );

	if(0 < lenSub && 0 < len)
	{
		if( startpos == -1 || startpos >= len ) startpos = len - 1;
		for ( LPTSTR lpszReverse = m_pchData + startpos ; 
						lpszReverse != m_pchData ; --lpszReverse)
			if (_tcsncmp(lpszSub, lpszReverse, lenSub ) == 0)
				return (lpszReverse - m_pchData);
	}
	return -1;
}


// ReverseFindNoCase	- Searches for the last match of a substring
//			  Search is case insensitive
// Returns		- A zero-based index
// lpszSub		- Character to search for
// startpos 		- Position to start looking from, in reverse dir
int CStringEx::ReverseFindNoCase(TCHAR ch, int startpos /*= -1*/ ) const
{
	TCHAR a[2];
	a[1] = ch;
	a[2] = 0;
	return ReverseFindNoCase( a, startpos );
}


// ReverseFindNoCase	- Searches for the last match of a substring
//			  Search is case insensitive
// Returns		- A zero-based index
// lpszSub		- Substring to search for
// startpos 		- Position to start looking from, in reverse dir
int CStringEx::ReverseFindNoCase( LPCTSTR lpszSub, int startpos /*= -1*/ ) const
{
	//LPTSTR lpszEnd = m_pchData + lstrlen

	int lenSub = lstrlen( lpszSub );
	int len = lstrlen( m_pchData );
	

	if(0 < lenSub && 0 < len)
	{
		if( startpos == -1 || startpos >= len ) startpos = len - 1;
		for ( LPTSTR lpszReverse = m_pchData + startpos ; 
				lpszReverse >= m_pchData ; --lpszReverse)
			if (_tcsnicmp(lpszSub, lpszReverse, lenSub ) == 0)
				return (lpszReverse - m_pchData);
	}
	return -1;
}


// GetField 	- Gets a delimited field
// Returns	- A CStringEx object that contains a copy of 
//		  the specified field
// delim	- The delimiter string
// fieldnum 	- The field index - zero is the first
// NOTE 	- Returns the whole string for field zero
//		  if delim not found
//		  Returns empty string if # of delim found
//		  is less than fieldnum
CStringEx CStringEx::GetField( LPCTSTR delim, int fieldnum)
{
	LPTSTR lpsz, lpszRemainder = m_pchData, lpszret;
	int retlen, lenDelim = lstrlen( delim );

	while( fieldnum-- >= 0 )
	{
		lpszret = lpszRemainder;
		lpsz = _tcsstr(lpszRemainder, delim);
		if( lpsz )
		{
			// We did find the delim
			retlen = lpsz - lpszRemainder;
			lpszRemainder = lpsz + lenDelim;
		}
		else
		{
			retlen = lstrlen( lpszRemainder );
			lpszRemainder += retlen;	// change to empty string
		}
	}
	return Mid( lpszret - m_pchData, retlen );
}

// GetField 	- Gets a delimited field
// Returns	- A CStringEx object that contains a copy of 
//		  the specified field
// delim	- The delimiter char
// fieldnum 	- The field index - zero is the first
// NOTE 	- Returns the whole string for field zero
//		  if delim not found
//		  Returns empty string if # of delim found
//		  is less than fieldnum
CStringEx CStringEx::GetField( TCHAR delim, int fieldnum)
{
	LPTSTR lpsz, lpszRemainder = m_pchData, lpszret;
	int retlen;

	while( fieldnum-- >= 0 )
	{
		lpszret = lpszRemainder;
		lpsz = _tcschr(lpszRemainder, (_TUCHAR)delim);
		if( lpsz )
		{
			// We did find the delim
			retlen = lpsz - lpszRemainder;
			lpszRemainder = lpsz + 1;
		}
		else
		{
			retlen = lstrlen( lpszRemainder );
			lpszRemainder += retlen;	// change to empty string
		}
	}
	return Mid( lpszret - m_pchData, retlen );
}


// GetFieldCount	- Get number of fields in a string
// Returns		- The number of fields
//			  Is always greater than zero
// delim		- The delimiter character
int CStringEx::GetFieldCount( TCHAR delim )
{
	TCHAR a[2];
	a[1] = delim;
	a[2] = 0;
	return GetFieldCount( a );
}


// GetFieldCount	- Get number of fields in a string
// Returns		- The number of fields
//			  Is always greater than zero
// delim		- The delimiter string
int CStringEx::GetFieldCount( LPCTSTR delim )
{
	LPTSTR lpsz, lpszRemainder = m_pchData;
	int lenDelim = lstrlen( delim );

	int iCount = 1;
	while( (lpsz = _tcsstr(lpszRemainder, delim)) != NULL )
	{
		lpszRemainder = lpsz + lenDelim;
		iCount++;
	}

	return iCount;
}


// GetDelimitedField	- Finds a field delimited on both ends
// Returns		- A CStringEx object that contains a copy of 
//			  the specified field
// delimStart		- Delimiter at the start of the field
// delimEnd 		- Delimiter at the end of the field
CStringEx CStringEx::GetDelimitedField( LPCTSTR delimStart, LPCTSTR delimEnd, int fieldnum /*= 0*/)
{
	LPTSTR lpsz, lpszEnd, lpszRet, lpszRemainder = m_pchData ;
	int lenDelimStart = lstrlen( delimStart ), lenDelimEnd = lstrlen( delimEnd );

	while( fieldnum-- >= 0 )
	{
		lpsz = _tcsstr(lpszRemainder, delimStart);
		if( lpsz )
		{
			// We did find the Start delim
			lpszRet = lpszRemainder = lpsz + lenDelimStart;
			lpszEnd = _tcsstr(lpszRemainder, delimEnd);
			if( lpszEnd == NULL ) return"";
			lpszRemainder = lpsz + lenDelimEnd;
		}
		else return "";
	}
	return Mid( lpszRet - m_pchData, lpszEnd - lpszRet );
}