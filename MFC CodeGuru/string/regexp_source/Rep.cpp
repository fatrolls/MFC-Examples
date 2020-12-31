// Version Altered by Guy Gascoigne - Piggford
// munged to work with his C++ version of Regexp

/*
 * Simple test program for regexp(3) stuff.  Knows about debugging hooks.
 *
 *	Copyright (c) 1986 by University of Toronto.
 *	Written by Henry Spencer.  Not derived from licensed software.
 *
 *	Permission is granted to anyone to use this software for any
 *	purpose on any computer system, and to redistribute it freely,
 *	subject to the following restrictions:
 *
 *	1. The author is not responsible for the consequences of use of
 *		this software, no matter how awful, even if they arise
 *		from defects in it.
 *
 *	2. The origin of this software must not be misrepresented, either
 *		by explicit claim or by omission.
 *
 *	3. Altered versions must be plainly marked as such, and must not
 *		be misrepresented as being the original software.
 *
 * Usage: TryOut re [string [output [-]]]
 * The re is compiled and dumped, regexeced against the string, the result
 * is applied to output using regsub().  The - triggers a running narrative
 * from regexec().  Dumping and narrative don't happen unless DEBUG.
 *
 * If there are no arguments, stdin is assumed to be a stream of lines with
 * five fields:  a r.e., a string to match it against, a result code, a
 * source string for regsub, and the proper result.  Result codes are 'c'
 * for compile failure, 'y' for match success, 'n' for match failure.
 * Field separator is tab.
 */
#include "stdafx.h"
#include "regexp.h"

#define new DEBUG_NEW

int status = 0;			/* Exit status. */

void multiple( FILE * fp );
void TryOut( TCHAR ** );
void complain( TCHAR *, TCHAR *, Regexp * r = 0 );

void main(int argc, TCHAR ** argv)
{
	if (argc == 2) {
		FILE * fp = 0;

#if defined(_UNICODE)
		// Haven't worked out how to get the unicode command line args to work - go figure.
		_tprintf( _T( "Working from hard coded file name!!!\n" ) );
		if ( (fp = _tfopen( _T( "E:\\MyProjects\\Regexp\\Work\\Tests.txt" ), _T( "r" ) ) ) != NULL )
#else
		if ( (fp = _tfopen( argv[1], _T( "r" ) ) ) != NULL )
#endif
		{
			_tprintf( _T( "If the test runs correctly there will be no further output.\n" ) );
			multiple( fp );
			fclose(fp);
		}
		else
			_tprintf( _T( "error %d\n" ), errno );
		exit(status);
	}

	exit(status);
}

int lineno;
Regexp badregexp;

void multiple( FILE * fp )
{
	TCHAR rbuf[BUFSIZ];
	TCHAR *field[5];
	TCHAR *scan;
	int i;

	Regexp r;

	lineno = 0;
	while (_fgetts(rbuf, sizeof(rbuf), fp) != NULL) {
		rbuf[_tcslen(rbuf)-1] = '\0';	/* Dispense with \n. */
		lineno++;
		scan = rbuf;
		for (i = 0; i < 5; i++) {
			field[i] = scan;
			if (field[i] == NULL) {
				complain(_T( "bad testfile format" ), _T( "" ));
				exit(1);
			}
			scan = _tcschr(scan, '\t');
			if (scan != NULL)
				*scan++ = '\0';
		}
		TryOut(field);
	}

	/* And finish up with some internal testing... */
	lineno = 9990;
	r = Regexp((TCHAR *)NULL);
	if ( r.CompiledOK() != 0 || r.GetErrorString().IsEmpty() )
		complain(_T( "regcomp(NULL) doesn't complain" ), _T( "" ), &r );

	lineno = 9991;
	r = Regexp();		// clean it out
	if ( r.Match(_T( "foo" )) || r.GetErrorString().IsEmpty() )
		complain(_T( "regexec(NULL, ...) doesn't complain" ), _T( "" ), &r );

	lineno = 9992;
	r = Regexp(_T( "foo" ));
	if ( ! r.CompiledOK() ) {
		complain(_T( "regcomp(\"foo\") fails" ), _T( "" ), &r );
		return;
	}

	lineno = 9993;
	if ( r.Match((TCHAR *)NULL) || r.GetErrorString().IsEmpty() )
		complain(_T( "regexec(..., NULL) doesn't complain" ), _T( "" ), &r );

	lineno = 9994;
	r = Regexp();
	CString repl = r.GetReplaceString( _T( "foo" ) );
	if ( r.GetErrorString().IsEmpty())
		complain(_T( "GetReplaceString(NULL, ..., ...) doesn't complain" ), _T( "" ), &r );

	lineno = 9995;
	repl = r.GetReplaceString((TCHAR *)NULL );
	if ( r.GetErrorString().IsEmpty() )
		complain(_T( "GetReplaceString(..., NULL, ...) doesn't complain" ), _T( "" ), &r );
	
	lineno = 9997;
	if (badregexp.Match( _T( "foo" )) || badregexp.GetErrorString().IsEmpty() )
		complain(_T( "regexec(nonsense, ...) doesn't complain" ), _T( "" ), &badregexp );

	lineno = 9998;
	repl = badregexp.GetReplaceString( _T( "foo" ) );
	if (badregexp.GetErrorString().IsEmpty() )
		complain(_T( "GetReplaceString(nonsense, ..., ...) doesn't complain" ), _T( "" ), &badregexp );

	lineno = 10000;
	Regexp reg1( _T( "[abc]+" ) );
	if ( ! reg1.CompiledOK() ) {
		complain(_T( "regcomp(\"[abc]*\") fails" ), _T( "" ), &reg1 );
		return;
	}
	lineno = 10001;
	if ( ! reg1.Match( _T( "test string 1 - aaa" ) ) || reg1.GetErrorString().GetLength() )
		complain(_T( "Match failed\n"), _T(""), &reg1 );
	lineno = 10003;
	if ( reg1[0] != _T( "aaa" ) )
		complain(_T( "Match failed\n"), _T(""), &reg1 );

	lineno = 10004;
	Regexp reg2( reg1 );

	if ( ! reg1.Match( _T( "test string 1 - aaa" ) ) || reg1.GetErrorString().GetLength() )
		complain(_T( "Match failed\n"), _T(""), &reg1 );
	lineno = 10005;
	if ( reg1[0] != _T( "aaa" ) )
		complain(_T( "Match failed\n"), _T(""), &reg1 );

	lineno = 10006;
	if ( ! reg2.Match( _T( "test string 2 - bbb" ) ) || reg2.GetErrorString().GetLength() )
		complain(_T( "Match failed\n"), _T(""), &reg2 );
	lineno = 10007;
	repl = reg2.GetReplaceString( _T( "&" ) );
	if ( reg2[0] != _T( "bbb" ) )
		complain(_T( "Match failed\n"), _T(""), &reg2 );

	lineno = 10008;
	Regexp reg3 ( reg1 );

	if ( ! reg3.Match( _T( "test string 3 - ccc" ) ) || reg3.GetErrorString().GetLength() )
		complain(_T( "Match failed\n"), _T(""), &reg3 );
	lineno = 10009;
	if ( reg3[0] != _T( "ccc" ) )
		complain(_T( "Match failed\n"), _T(""), &reg3 );

	lineno = 10010;		// make sure that the copy didn't screw anything up
	if ( reg1[0] != _T( "aaa" ) )
		complain(_T( "Match failed\n"), _T(""), &reg1 );

}

void TryOut(TCHAR **fields)
{
	Regexp r;
	TCHAR dbuf[BUFSIZ];

	r = Regexp (fields[0]);
	if (! r.CompiledOK() ) {
		if (*fields[2] != _T( 'c' ))
			complain(_T( "regcomp failure in `%s'" ), fields[0], &r );
		return;
	}
	if (*fields[2] == _T( 'c' )) {
		complain(_T( "unexpected regcomp success in `%s'" ), fields[0], &r );
		return;
	}

	if (! r.Match(fields[1])) {
		if (*fields[2] != 'n')
			complain(_T( "regexec failure in `%s'" ), _T( "" ), &r );
		return;
	}
	if (*fields[2] == _T( 'n' )) {
		complain(_T( "unexpected regexec success" ), _T( "" ), &r );
		return;
	}

	Regexp r2(r);
	CString repl = r2.GetReplaceString( fields[3] );
	if ( r2.GetErrorString().GetLength() ) {
		complain(_T( "GetReplaceString complaint" ), _T( "" ), &r2 );
		return;
	}
	if ( repl.Compare( fields[4] ) != 0)
		complain(_T( "regsub result `%s' wrong" ), dbuf, &r2 );
}

void complain(TCHAR * s1, TCHAR * s2, Regexp * r )
{
	_ftprintf(stderr, _T( "TryOut: %d: " ), lineno );
	_ftprintf(stderr, s1, s2 );

	if ( r )
		_ftprintf(stderr, _T( " (%s)" ), (LPCTSTR)r->GetErrorString() );

	_ftprintf(stderr, _T( "\n" ) );
	status = 1;
}

