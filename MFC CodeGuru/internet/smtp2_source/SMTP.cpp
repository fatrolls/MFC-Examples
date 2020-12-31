// SMTP.cpp: implementation of the CSMTP class.
// Copyright (c) 1998, Wes Clyburn
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ZapMail.h"
#include "SMTP.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

// Static member initializers
//

// Note: the order of the entries is important.
//       They must be synchronized with eResponse entries. 
CSMTP::response_code CSMTP::response_table[] =
{
	{ 250, "SMTP server error" },						// GENERIC_SUCCESS
	{ 220, "SMTP server not available" },				// CONNECT_SUCCESS
	{ 354, "SMTP server not ready for data" },			// DATA_SUCCESS
	{ 221, "SMTP server didn't terminate session" }  	// QUIT_SUCCESS
};


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSMTP::CSMTP( LPCTSTR szSMTPServerName, UINT nPort )
{
	ASSERT( szSMTPServerName != NULL );
	AfxSocketInit();
	m_sMailerName = _T( "WC Mail" );
	m_sSMTPServerHostName = szSMTPServerName;
	m_nPort = nPort;
	m_bConnected = FALSE;
	m_sError = _T( "OK" );
}

CSMTP::~CSMTP()
{
	if( m_bConnected )
		Disconnect();
}

CString CSMTP::GetServerHostName()
{
	return m_sSMTPServerHostName;
}

BOOL CSMTP::Connect()
{
	CString sHello;
	TCHAR local_host[ 80 ];	// Warning: arbitrary size
	if( m_bConnected )
		return TRUE;

	if( !m_wsSMTPServer.Create() )
	{
		m_sError = _T( "Unable to create the socket." );
		return FALSE;
	}
	if( !m_wsSMTPServer.Connect( GetServerHostName(), GetPort() ) )
	{
		m_sError = _T( "Unable to connect to server" );
		m_wsSMTPServer.Close();
		return FALSE;
	}
	if( !get_response( CONNECT_SUCCESS ) )
	{
		m_sError = _T( "Server didn't respond." );
		m_wsSMTPServer.Close();
		return FALSE;
	}
	gethostname( local_host, 80 );
	sHello.Format( "HELO %s\r\n", local_host );
	m_wsSMTPServer.Send( (LPCTSTR)sHello, sHello.GetLength() );
	if( !get_response( GENERIC_SUCCESS ) )
	{
		m_wsSMTPServer.Close();
		return FALSE;
	}
	m_bConnected = TRUE;
	return TRUE;
}

BOOL CSMTP::Disconnect()
{
	BOOL ret;
	if( !m_bConnected )
		return TRUE;
	// Disconnect gracefully from the server and close the socket
	CString sQuit = _T( "QUIT\r\n" );
	m_wsSMTPServer.Send( (LPCTSTR)sQuit, sQuit.GetLength() );

	// No need to check return value here.
	// If it fails, the message is available with GetLastError
	ret = get_response( QUIT_SUCCESS );
	m_wsSMTPServer.Close();

	m_bConnected = FALSE;
	return ret;
}

UINT CSMTP::GetPort()
{
	return m_nPort;
}

CString CSMTP::GetMailerName()
{
	return m_sMailerName;
}

CString CSMTP::GetLastError()
{
	return m_sError;
}

BOOL CSMTP::SendMessage(CMailMessage * msg)
{
	ASSERT( msg != NULL );
	if( !m_bConnected )
	{
		m_sError = _T( "Must be connected" );
		return FALSE;
	}
	if( FormatMailMessage( msg ) == FALSE )
	{
		return FALSE;
	}
	if( transmit_message( msg ) == FALSE )
	{
		return FALSE;
	}
	return TRUE;
}

BOOL CSMTP::FormatMailMessage( CMailMessage* msg )
{
	ASSERT( msg != NULL );
	if( prepare_header( msg ) == FALSE )
	{
		return FALSE;
	}
	// Append a CR/LF to body if necessary.
	if( msg->m_sBody.Right( 2 ) != "\r\n" )
		msg->m_sBody += "\r\n";
	return TRUE;
}

void CSMTP::SetServerProperties( LPCTSTR sServerHostName, UINT nPort)
{
	ASSERT( sServerHostName != NULL );
	// Needs to be safe in non-debug too
	if( sServerHostName == NULL )
		return;
	m_sSMTPServerHostName = sServerHostName;
	m_nPort = nPort;
}

// Create the SMTP message header as per RFC822
BOOL CSMTP::prepare_header(CMailMessage * msg)
{
	ASSERT( msg != NULL );
	CString sTo;
	CString sDate;
	CString& sHeader = msg->m_sHeader;	// Shorthand

	if( msg->GetNumRecipients() <= 0 )
	{
		m_sError = "No Recipients";
		return FALSE;
	}

	sHeader = "";	// Clear it

	// Get the recipients into a single string
	sTo = "";
	CString sEmail = "";
	CString sFriendly = "";
	for( int i = 0; i < msg->GetNumRecipients(); i++ )
	{
		msg->GetRecipient( sEmail, sFriendly, i );
		sTo += ( i > 0 ? "," : "" );
		sTo += sFriendly;
		sTo += "<";
		sTo += sEmail;
		sTo += ">";
	}
	msg->m_tDateTime = msg->m_tDateTime.GetCurrentTime();
	// Format: Mon, 01 Jun 98 01:10:30 GMT
	sDate = msg->m_tDateTime.Format( "%a, %d %b %y %H:%M:%S %Z" );
	sHeader.Format( "Date: %s\r\n"\
					"From: %s\r\n"\
					"To: %s\r\n"\
					"Subject: %s\r\n"\
					"X-Mailer: <%s>\r\n\r\n",
					// Include other extension lines if desired
					(LPCTSTR)sDate,
					(LPCTSTR)msg->m_sFrom,
					(LPCTSTR)sTo,
					(LPCTSTR)msg->m_sSubject,
					(LPCTSTR)m_sMailerName );
	return TRUE;
}

CString CSMTP::prepare_body(CMailMessage * msg)
{
	ASSERT( msg != NULL );
	CString sTemp;
	CString sCooked = "";
	LPTSTR szBad = "\r\n.\r\n";
	LPTSTR szGood = "\r\n..\r\n";
	int nPos;
	int nStart = 0;
	int nBadLength = strlen( szBad );
	sTemp = msg->m_sBody;
	if( sTemp.Left( 3 ) == ".\r\n" )
		sTemp = "." + sTemp;
	//
	// This is a little inefficient because it beings a search
	// at the beginning of the string each time. This was
	// the only thing I could think of that handled ALL variations.
	// In particular, the sequence "\r\n.\r\n.\r\n" is troublesome. 
	// (Even CStringEx's FindReplace wouldn't handle that situation
	// with the global flag set.)
	//
	while( (nPos = sTemp.Find( szBad )) > -1 )
	{
		sCooked = sTemp.Mid( nStart, nPos );
		sCooked += szGood;
		sTemp = sCooked + sTemp.Right( sTemp.GetLength() - (nPos + nBadLength) );
	}
	return sTemp;
}

BOOL CSMTP::transmit_message(CMailMessage * msg)
{
	CString sFrom;
	CString sTo;
	CString sTemp;
	CString sEmail;

	ASSERT( msg != NULL );
	if( !m_bConnected )
	{
		m_sError = _T( "Must be connected" );
		return FALSE;
	}

	// Send the MAIL command
	//
	sFrom.Format( "MAIL From: <%s>\r\n", (LPCTSTR)msg->m_sFrom );
	m_wsSMTPServer.Send( (LPCTSTR)sFrom, sFrom.GetLength() );
	if( !get_response( GENERIC_SUCCESS ) )
		return FALSE;
	
	// Send RCPT commands (one for each recipient)
	//
	for( int i = 0; i < msg->GetNumRecipients(); i++ )
	{
		msg->GetRecipient( sEmail, sTemp, i );
		sTo.Format( "RCPT TO: <%s>\r\n", (LPCTSTR)sEmail );
		m_wsSMTPServer.Send( (LPCTSTR)sTo, sTo.GetLength() );
		get_response( GENERIC_SUCCESS );
	}

	// Send the DATA command
	sTemp = "DATA\r\n";
	m_wsSMTPServer.Send( (LPCTSTR)sTemp, sTemp.GetLength() );
	if( !get_response( DATA_SUCCESS ) )
	{
		return FALSE;
	}
	// Send the header
	//
	m_wsSMTPServer.Send( (LPCTSTR)msg->m_sHeader, msg->m_sHeader.GetLength() );

	// Send the body
	//
	sTemp = prepare_body( msg );
	m_wsSMTPServer.Send( (LPCTSTR)sTemp, sTemp.GetLength() );

	// Signal end of data
	//
	sTemp = "\r\n.\r\n";
	m_wsSMTPServer.Send( (LPCTSTR)sTemp, sTemp.GetLength() );
	if( !get_response( GENERIC_SUCCESS ) )
	{
		return FALSE;
	}
	return TRUE;
}

BOOL CSMTP::get_response( UINT response_expected )
{
	ASSERT( response_expected >= GENERIC_SUCCESS );
	ASSERT( response_expected < LAST_RESPONSE );

	CString sResponse;
	UINT response;
	response_code* pResp;	// Shorthand

	if( m_wsSMTPServer.Receive( response_buf, RESPONSE_BUFFER_SIZE ) == SOCKET_ERROR )
	{
		m_sError = _T( "Socket Error" );
		return FALSE;
	}
	sResponse = response_buf;
	sscanf( (LPCTSTR)sResponse.Left( 3 ), "%d", &response );
	pResp = &response_table[ response_expected ];
	if( response != pResp->nResponse )
	{
		m_sError.Format( "%d:%s", response, (LPCTSTR)pResp->sMessage );
		return FALSE;
	}
	return TRUE;
}


