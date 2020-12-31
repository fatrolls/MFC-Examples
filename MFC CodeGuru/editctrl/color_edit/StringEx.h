//////////////////////////////////////////////////////////////////////
// StringEx.h
//

#ifndef __STRINGEX_H_
#define __STRINGEX_H_

class CStringEx : public CString
{
public:
	CStringEx() : CString( ){};
	CStringEx( const CString& stringSrc) : CString( stringSrc ){};
	CStringEx( const CStringEx& stringSrc) : CString( stringSrc ){};
	CStringEx( TCHAR ch, int nRepeat = 1 ) : CString( ch, nRepeat ){};
	CStringEx( LPCTSTR lpch, int nLength ) : CString( lpch, nLength ){};
	CStringEx( const unsigned char* psz ) : CString( psz ){};
	CStringEx( LPCWSTR lpsz ) : CString( lpsz ){};
	CStringEx( LPCSTR lpsz ) : CString( lpsz ){};

	CStringEx& Insert(int pos, LPCTSTR s);
	CStringEx& Insert(int pos, TCHAR c);

	CStringEx& Delete(int pos, int len);
	CStringEx& Replace(int pos, int len, LPCTSTR s);

	int Find( TCHAR ch, int startpos = 0 ) const;
	int Find( LPCTSTR lpszSub, int startpos = 0 ) const;
	int FindNoCase( TCHAR ch, int startpos = 0 ) const;
	int FindNoCase( LPCTSTR lpszSub, int startpos = 0 ) const;

	int FindReplace( LPCTSTR lpszSub, LPCTSTR lpszReplaceWith, BOOL bGlobal = TRUE );
	int FindReplaceNoCase( LPCTSTR lpszSub, LPCTSTR lpszReplaceWith, 
				BOOL bGlobal = TRUE );

	int ReverseFind( TCHAR ch ) const{ return CString::ReverseFind(ch);};
	int ReverseFind( LPCTSTR lpszSub, int startpos = -1 ) const;
	int ReverseFindNoCase( TCHAR ch, int startpos = -1  ) const;
	int ReverseFindNoCase( LPCTSTR lpszSub, int startpos = -1 ) const;

	CStringEx GetField( LPCTSTR delim, int fieldnum);
	CStringEx GetField( TCHAR delim, int fieldnum);
	int GetFieldCount( LPCTSTR delim );
	int GetFieldCount( TCHAR delim );

	CStringEx GetDelimitedField( LPCTSTR delimStart, LPCTSTR delimEnd, 
				int fieldnum = 0);
};


#endif
/////////////////////////////////////////////////////////////////////

