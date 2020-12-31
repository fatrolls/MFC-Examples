// SMTP.cpp: implementation of the CSMTP class.
// Copyright (c) 1998, Wes Clyburn
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
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
	// GENERIC_SUCCESS
	{ 250, _T( "SMTP server error" ) },

	// CONNECT_SUCCESS
	{ 220, _T( "SMTP server not available" ) },

	// DATA_SUCCESS
	{ 354, _T( "SMTP server not ready for data" ) },

	// QUIT_SUCCESS
	{ 221, _T( "SMTP server didn't terminate session" ) }
};


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSMTP::CSMTP( LPCTSTR szSMTPServerName, UINT nPort )
{
	ASSERT( szSMTPServerName != NULL );
	AfxSocketInit();
	m_sSMTPServerHostName = szSMTPServerName;
	m_nPort = nPort;
	m_bConnected = FALSE;
	m_sError = _T( "OK" );
	response_buf = NULL;
}

CSMTP::~CSMTP()
{
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
	
	try
	{
		// This will be deleted in Disconnect();
		response_buf = new TCHAR[ RESPONSE_BUFFER_SIZE ];

		// I can't count on all class users' applications
		// to have exception-throwing operator-new implementations,
		// so I'll soul-kiss the ones that don't.
		if( response_buf == NULL )
		{
			m_sError = _T( "Not enough memory" );
			return FALSE;
		}
	}
	catch( CException *e )
	{
		response_buf = NULL;
		m_sError = _T( "Not enough memory" );
		delete e;
		return FALSE;
	}

	if( !m_wsSMTPServer.Create() )
	{
		m_sError = _T( "Unable to create the socket." );
		delete response_buf;
		response_buf = NULL;
		return FALSE;
	}
	if( !m_wsSMTPServer.Connect( GetServerHostName(), GetPort() ) )
	{
		m_sError = _T( "Unable to connect to server" );
		m_wsSMTPServer.Close();
		delete response_buf;
		response_buf = NULL;
		return FALSE;
	}
	if( !get_response( CONNECT_SUCCESS ) )
	{
		m_sError = _T( "Server didn't respond." );
		m_wsSMTPServer.Close();
		delete response_buf;
		response_buf = NULL;
		return FALSE;
	}
	gethostname( local_host, 80 );
	sHello.Format( _T( "HELO %s\r\n" ), local_host );
	m_wsSMTPServer.Send( (LPCTSTR)sHello, sHello.GetLength() );
	if( !get_response( GENERIC_SUCCESS ) )
	{
		m_wsSMTPServer.Close();
		delete response_buf;
		response_buf = NULL;
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

	if( response_buf != NULL )
	{
		delete[] response_buf;
		response_buf = NULL;
	}

	m_bConnected = FALSE;
	return ret;
}

UINT CSMTP::GetPort()
{
	return m_nPort;
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
	if( msg->GetNumRecipients() == 0 )
	{
		m_sError = _T( "No Recipients" );
		return FALSE;
	}
	msg->FormatMessage();
	return TRUE;
}

void CSMTP::SetServerProperties( LPCTSTR szSMTPServerName, UINT nPort)
{
	ASSERT( szSMTPServerName != NULL );
	// Needs to be safe in non-debug too
	if( szSMTPServerName == NULL )
		return;
	m_sSMTPServerHostName = szSMTPServerName;
	m_nPort = nPort;
}


CString CSMTP::cook_body(CMailMessage * msg)
{
	ASSERT( msg != NULL );
	CString sTemp;
	CString sCooked = _T( "" );
	LPTSTR szBad = _T( "\r\n.\r\n" );
	LPTSTR szGood = _T( "\r\n..\r\n" );
	int nPos;
	int nStart = 0;
	int nBadLength = strlen( szBad );
	sTemp = msg->m_sBody;
	if( sTemp.Left( 3 ) == _T( ".\r\n" ) )
		sTemp = _T( "." ) + sTemp;
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
	sFrom.Format( _T( "MAIL From: <%s>\r\n" ), (LPCTSTR)msg->m_sFrom );
	m_wsSMTPServer.Send( (LPCTSTR)sFrom, sFrom.GetLength() );
	if( !get_response( GENERIC_SUCCESS ) )
		return FALSE;
	
	// Send RCPT commands (one for each recipient)
	//
	for( int i = 0; i < msg->GetNumRecipients(); i++ )
	{
		msg->GetRecipient( sEmail, sTemp, i );
		sTo.Format( _T( "RCPT TO: <%s>\r\n" ), (LPCTSTR)sEmail );
		m_wsSMTPServer.Send( (LPCTSTR)sTo, sTo.GetLength() );
		get_response( GENERIC_SUCCESS );
	}

	// Send the DATA command
	sTemp = _T( "DATA\r\n" );
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
	sTemp = cook_body( msg );
	m_wsSMTPServer.Send( (LPCTSTR)sTemp, sTemp.GetLength() );

	// Signal end of data
	//
	sTemp = _T( "\r\n.\r\n" );
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
	sscanf( (LPCTSTR)sResponse.Left( 3 ), _T( "%d" ), &response );
	pResp = &response_table[ response_expected ];
	if( response != pResp->nResponse )
	{
		m_sError.Format( _T( "%d:%s" ), response, (LPCTSTR)pResp->sMessage );
		return FALSE;
	}
	return TRUE;
}


