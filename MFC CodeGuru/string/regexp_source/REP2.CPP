// This test program shows a different use of Regexps, here they are
// used as a way grabbing fields out of somewhat orderly string
// definitions. 
// In this example I take an email header and chop out various fields
// using Regexp subexpressions.

// For example using the regexp "^[\t ]*(.*)[\t ]*\\((.*)\\)"  against
// the string " wyrdrune.com!kelly (Kelly)\n" matches two separate
// subexpressions.  The first being "wyrdrune.com!kelly" and the
// second "Kelly".

#include <afx.h>

// The debugger can't handle symbols more than 255 characters long.
// STL often creates symbols longer than that.
#pragma warning(disable:4786) // When symbols are longer than 255 characters, the warning is disabled.
#include <xstddef>
#pragma warning(disable:4097) // typedef-name 'istream' used as synonym for class-name 'basic_istream<char,struct std::char_traits<char>>'
#pragma warning(disable:4018) // signed/unsigned mismatch
#pragma warning(disable:4100) // unreferenced formal parameter
#pragma warning(disable:4146) // unary minus operator applied to unsigned type, result still unsigned
#pragma warning(disable:4238) // nonstandard extension used : class rvalue used as lvalue
#pragma warning(disable:4244) // conversion from 'const int' to 'char', possible loss of data
#pragma warning(disable:4663) // C++ language change: to explicitly specialize class template 'char_traits' use the following syntax: template<> struct char_traits<unsigned short> ...
#pragma warning(disable:4511) // copy constructor could not be generated
#pragma warning(disable:4512) // assignment operator could not be generated
#pragma warning(disable:4245) // conversion from 'const int' to 'const unsigned int', signed/unsigned mismatch
#pragma warning(disable:4505) // unreferenced local function has been removed
#pragma warning(disable:4710) // function '...' not expanded
#pragma warning(disable:4711) // automatic inline selected
#include <iostream>
#include <istream>
#include <string>
using namespace std;

#define new DEBUG_NEW

// There ought to be a portability layer for these, but so far I haven't found it.

#if defined(_UNICODE)
	#define String	wstring
	#define Cout	wcout
	#define Cin		wcin
	#define Cerr	wcerr
	#define Ostream	wostream
#else
	#define String	string
	#define Cout	cout
	#define Cin		cin
	#define Cerr	cerr
	#define Ostream	ostream
#endif

Ostream & operator<<( Ostream & o, const CString & s )
{
	return o << (LPCTSTR)s;
}

#include "regexp.h"

void printMatch( const TCHAR * d, Regexp & r)
{
	Cout << d << _T( " = :" ) << r[1] << _T( ":" ) << endl;
}    

CString StripQuotes( const CString & s )
{
	int len = s.GetLength();
	if ( len > 2 && ( ( s[0] == '\"' && s[len-1] == '\"'  ) || ( s[0] == '\'' && s[len-1] == '\'' ) ) )
		return s.Mid( 1, len-2 );
	else
		return s;
}

void SplitMailAddress( const CString & s, CString & addr, CString & name )
{
	static Regexp pattern[3] = {_T( "^[\t \"]*([^\"]*)[\"\t ]*<(.*)>" ),
								_T( "^[\t ]*(.*)[\t ]*\\((.*)\\)" ),
								_T( "^[\t ]*(.*)$" ) };

	name.Empty(), addr.Empty();
	for ( int i = 0; addr.IsEmpty() &&  i < 3; i++ )
	{
		pattern[i].Match( s );
		switch( i )
		{
		case 0:
			if ( pattern[i].SubStrings() == 2 )
				name = pattern[i][1], addr = pattern[i][2];
			break;
		case 1:
			if ( pattern[i].SubStrings() == 2 )
				addr = pattern[i][1], name = pattern[i][2];
			break;
		default:
			if ( pattern[i].SubStrings() == 1 )
				addr = pattern[i][1];
			break;
		}
	}
	// if name exists and is quoted then remove the quotes.
	name = StripQuotes( name );
}

void main()
{
	CString Header =
		_T( "From kelly Mon Jul 26 15:08:25 0600 1993 remote from wyrdrune.com\n" )
		_T( "Message-ID: <9307261508.AA01287@wyrdrune.com>\n" )
		_T( "Received: from if.com by wyrdrune.com; Mon, 26 Jul 93 15:07 MDT\n" )
		_T( "Subject: Re: Info request\n" )
		_T( "To: wyrdrune.demon.co.uk!guy \n" )
		_T( "Date: Mon, 26 Jul 1993 15:08:25 -0600 (MDT)\n" )
		_T( "From: wyrdrune.com!kelly (Kelly)\n" )
		_T( "In-Reply-To: <743490184snx@wyrdrune.demon.co.uk> from \"Guy Gascoigne - Piggford\" at Jul 23, 93 10:03:04 pm\n" )
		_T( "Reply-To: kelly@wyrdrune.com\n" )
		_T( "Return-Path: kelly@wyrdrune.com\n" )
		_T( "X-Mailer: ELM [version 2.4 PL21]\n" )
		_T( "Content-Type: text\n" )
		_T( "Content-Length: 55706" );
	
	Regexp reSubject( _T( "Subject: *([^\n]*)" ), TRUE );
	Regexp reMessageId = _T( "Message-ID: [^\n<]*<([^\n]*)>" );
	Regexp reInReplyTo = _T( "In-Reply-To: [^\n<]*<([^\n<]*)>.*" );
	Regexp reReturnPath = _T( "Return-Path: *([^\n]*)" );
	Regexp reFrom = _T( "From: *([^\n]*)" );

	reSubject.Match( Header );
	reMessageId.Match( Header );
	reInReplyTo.Match( Header );
	reReturnPath.Match( Header );
	reFrom.Match( Header );

	if ( reFrom.SubStrings() == 1 )
	{
		CString addr, name;
		SplitMailAddress( reFrom[1], addr, name );
		Cout << _T( "From " ) << name << _T( " = " ) << addr << endl;
	}

	printMatch( _T( "Subject" ), reSubject );
	printMatch( _T( "Message-Id" ), reMessageId );
	printMatch( _T( "In-Reply-To" ), reInReplyTo );
	printMatch( _T( "Return-Path" ), reReturnPath );

	// The expected output of this is:
	//
	// From Kelly = wyrdrune.com!kelly
	// Subject = :Re: Info request:
	// Message-Id = :9307261508.AA01287@wyrdrune.com:
	// In-Reply-To = :743490184snx@wyrdrune.demon.co.uk:
	// Return-Path = :kelly@wyrdrune.com:
}

