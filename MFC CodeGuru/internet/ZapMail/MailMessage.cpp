// MailMessage.cpp: implementation of the CMailMessage class.
// Copyright (c) 1998, Wes Clyburn
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MailMessage.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMailMessage::CMailMessage()
{
	m_sMailerName = _T( "WC Mail" );
	SetCharsPerLine( 76 );
}

CMailMessage::~CMailMessage()
{

}

BOOL CMailMessage::AddRecipient( LPCTSTR szEmailAddress, LPCTSTR szFriendlyName)
{
	ASSERT( szEmailAddress != NULL );
	ASSERT( szFriendlyName != NULL );
	CRecipient to;
	to.m_sEmailAddress = szEmailAddress;
	to.m_sFriendlyName = szFriendlyName;
	m_Recipients.Add( to );
	return TRUE;
}

// sEmailAddress and sFriendlyName are OUTPUT parameters.
// If the function fails, it will return FALSE, and the OUTPUT
// parameters will not be touched.
BOOL CMailMessage::GetRecipient(CString & sEmailAddress, CString & sFriendlyName, int nIndex)
{
	CRecipient to;
	if( nIndex < 0 || nIndex > m_Recipients.GetUpperBound() )
		return FALSE;
	to = m_Recipients[ nIndex ];
	sEmailAddress = to.m_sEmailAddress;
	sFriendlyName = to.m_sFriendlyName;
	return TRUE;
}

int CMailMessage::GetNumRecipients()
{
	return m_Recipients.GetSize();
}

BOOL CMailMessage::AddMultipleRecipients(LPCTSTR szRecipients )
{
	TCHAR* buf;
	UINT pos;
	UINT start;
	CString sTemp;
	CString sEmail;
	CString sFriendly;
	UINT length;
	int nMark;
	int nMark2;

	ASSERT( szRecipients != NULL );
	
	// Add Recipients
	//
	length = strlen( szRecipients );
	buf = new TCHAR[ length + 1 ];	// Allocate a work area (don't touch parameter itself)
	strcpy( buf, szRecipients );
	for( pos = 0, start = 0; pos <= length; pos++ )
	{
		if( buf[ pos ] == ';' ||
			buf[ pos ] == 0 )
		{
			// First, pick apart the sub-strings (separated by ';')
			//  Store it in sTemp.
			//
			buf[ pos ] = 0;	// Redundant when at the end of string, but who cares.
			sTemp = &buf[ start ];

			// Now divide the substring into friendly names and e-mail addresses.
			//
			nMark = sTemp.Find( '<' );
			if( nMark >= 0 )
			{
				sFriendly = sTemp.Left( nMark );
				nMark2 = sTemp.Find( '>' );
				if( nMark2 < nMark )
				{
					delete[] buf;
					return FALSE;
				}
				// End of mark at closing bracket or end of string
				nMark2 > -1 ? nMark2 = nMark2 : nMark2 = sTemp.GetLength() - 1;
				sEmail = sTemp.Mid( nMark + 1, nMark2 - (nMark + 1) );
			}
			else
			{
				sEmail = sTemp;
				sFriendly = _T( "" );
			}
			AddRecipient( sEmail, sFriendly );
			start = pos + 1;
		}
	}
	delete[] buf;
	return TRUE;
}

void CMailMessage::FormatMessage()
{
	start_header();
	prepare_header();
	end_header();
	prepare_body();
}

void CMailMessage::SetCharsPerLine(UINT nCharsPerLine)
{
	m_nCharsPerLine = nCharsPerLine;
}	

UINT CMailMessage::GetCharsPerLine()
{
	return m_nCharsPerLine;
}

// Create header as per RFC 822
//
void CMailMessage::prepare_header()
{
	CString sTemp;

	sTemp = _T( "" );
	// From:
	sTemp = _T( "From: " ) + m_sFrom;
	add_header_line( (LPCTSTR)sTemp );

	// To:
	sTemp = _T( "To: " );
	CString sEmail = _T( "" );
	CString sFriendly = _T( "" );
	for( int i = 0; i < GetNumRecipients(); i++ )
	{
		GetRecipient( sEmail, sFriendly, i );
		sTemp += ( i > 0 ? _T( "," ) : _T( "" ) );
		sTemp += sFriendly;
		sTemp += _T( "<" );
		sTemp += sEmail;
		sTemp += _T( ">" );
	}
	add_header_line( (LPCTSTR)sTemp );

	// Date:
	m_tDateTime = m_tDateTime.GetCurrentTime();
	// Format: Mon, 01 Jun 98 01:10:30 GMT
	sTemp = _T( "Date: " );
	sTemp += m_tDateTime.Format( "%a, %d %b %y %H:%M:%S %Z" );
	add_header_line( (LPCTSTR)sTemp );

	// Subject:
	sTemp = _T( "Subject: " ) + m_sSubject;
	add_header_line( (LPCTSTR)sTemp );

	// X-Mailer
	sTemp = _T( "X-Mailer: " ) + m_sMailerName;
	add_header_line( (LPCTSTR)sTemp );
}

void CMailMessage::prepare_body()
{
	// Append a CR/LF to body if necessary.
	if( m_sBody.Right( 2 ) != _T( "\r\n" ) )
		m_sBody += _T( "\r\n" );

}


void CMailMessage::start_header()
{
	m_sHeader = _T( "" );
}

void CMailMessage::end_header()
{
	m_sHeader += _T( "\r\n" );
}

void CMailMessage::add_header_line(LPCTSTR szHeaderLine)
{
	CString sTemp;
	sTemp.Format( _T( "%s\r\n" ), szHeaderLine );
	m_sHeader += sTemp;
}

