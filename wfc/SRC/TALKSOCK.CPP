#include <wfc.h>
#pragma hdrstop

/*
** Author: Samuel R. Blackburn
** Internet: wfc@pobox.com
**
** You can use it any way you like as long as you don't try to sell it.
**
** Any attempt to sell WFC in source code form must have the permission
** of the original author. You can produce commercial executables with
** WFC but you can't sell WFC.
**
** Copyright, 2000, Samuel R. Blackburn
**
** $Workfile: talksock.cpp $
** $Revision: 20 $
** $Modtime: 1/09/00 4:22p $
** $Reuse Tracing Code: 1 $
*/

#if defined( _DEBUG ) && ! defined( WFC_STL )
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif // _DEBUG

CTalkingSocket::CTalkingSocket()
{
   WFCLTRACEINIT( TEXT( "CTalkingSocket::CTalkingSocket()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   m_Initialize();
}

CTalkingSocket::CTalkingSocket( const CString& a_host_name, const CString& p_name )
{
   WFCLTRACEINIT( TEXT( "CTalkingSocket::CTalkingSocket( host_name, port_name )" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   m_Initialize();

   SetAddress( a_host_name );
   SetPort( p_name );
}

CTalkingSocket::CTalkingSocket( const CString& address, const short p_number )
{
   WFCLTRACEINIT( TEXT( "CTalkingSocket::CTalkingSocket( address, port_number )" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   m_Initialize();

   SetAddress( address );
   SetPort( p_number );
}

CTalkingSocket::~CTalkingSocket()
{
   WFCLTRACEINIT( TEXT( "CTalkingSocket::~CTalkingSocket()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
}

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

void CTalkingSocket::Dump( CDumpContext &dump_context ) const
{
   CSimpleSocket::Dump( dump_context );
}

#endif // _DEBUG

void CTalkingSocket::m_Initialize( void )
{
   WFCLTRACEINIT( TEXT( "CTalkingSocket::m_Initialize()" ) );
}

/*
** The Socket manipulation routines
*/

BOOL CTalkingSocket::Open( void )
{
   WFCLTRACEINIT( TEXT( "CTalkingSocket::Open()" ) );
   ASSERT( m_Thunk_p != NULL );

   if ( Address.IsEmpty() )
   {
      /*
      ** We don't have an address
      */

      WFCTRACE( TEXT( "Address is empty()" ) );
      return( FALSE );
   }

   if ( m_SocketID != INVALID_SOCKET )
   {
      // Someone (the user) is trying to open us twice!

      Close();
   }

   SOCKADDR_IN server_address;

   /*
   ** Create the socket
   */

   m_SocketID = m_Thunk_p->socket( AF_INET, SOCK_STREAM, 0 );

   if ( m_SocketID == INVALID_SOCKET )
   {
      m_ErrorCode = m_Thunk_p->WSAGetLastError();
      WFCTRACEVAL( TEXT( "socket call failed at line " ), __LINE__ );
      WFCTRACEERROR( m_ErrorCode );
      return( FALSE );
   }

   /*
   ** Now fill in a socket address structure with the necessary information about the remote
   ** server node (remote node IP address and port for incoming connections) and attempt to
   ** connect to the server. This connect call will block until the remote server has accepted
   ** the connection or the connection request times out.
   */

   server_address.sin_family = AF_INET;
   server_address.sin_port   = m_PortNumberInNetworkByteOrder;

#if ! defined( UNICODE )

   server_address.sin_addr.s_addr = m_Thunk_p->inet_addr( (const char *) Address );

#else

   char ascii_address_string[ 100 ];

   ::ZeroMemory( ascii_address_string, sizeof( ascii_address_string ) );

   ::UNICODE_to_ASCII( Address, ascii_address_string );

   server_address.sin_addr.s_addr = m_Thunk_p->inet_addr( ascii_address_string );

#endif // UNICODE

   int connection_status = 0;

   connection_status = m_Thunk_p->connect( m_SocketID, (LPSOCKADDR) &server_address, sizeof( server_address ) );

   if ( connection_status == SOCKET_ERROR )
   {
      m_ErrorCode = m_Thunk_p->WSAGetLastError();

      WFCTRACEVAL( TEXT( "connect() Address" ), Address );
      WFCTRACEVAL( TEXT( "connect() failed with error code " ), m_ErrorCode );
      WFCTRACEERROR( m_ErrorCode );

      Close();
      return( FALSE );
   }

   m_hFile = (UINT) m_SocketID;

   // The filename should be the host name followed by IP address then port number.
   // Example: "Sammy (195.99.72.1) Port: 23"

   short port_number = 0;

   GetPort( port_number );

#if ! defined( WFC_STL )
   m_strFileName.Format( TEXT( "%s (%s) Port: %d" ), (LPCTSTR) Name, (LPCTSTR) Address, (int) port_number );
#else // WFC_STL
   m_FileName.Format( TEXT( "%s (%s) Port: %d" ), (LPCTSTR) Name, (LPCTSTR) Address, (int) port_number );
#endif // WFC_STL

   return( TRUE );
}

#pragma warning( disable : 4100 )

#if ! defined( WFC_STL )
BOOL CTalkingSocket::Open( LPCTSTR a, UINT port_number, CFileException *perror )
#else // WFC_STL
BOOL CTalkingSocket::Open( LPCTSTR a, UINT port_number )
#endif // WFC_STL
{
   WFCLTRACEINIT( TEXT( "CTalkingSocket::Open( name, port number, exception )" ) );
   ASSERT( a != NULL );

   if ( a == NULL )
   {
      WFCTRACE( TEXT( "filename parameter is NULL" ) );
      m_ErrorCode = ERROR_INVALID_PARAMETER;
      return( FALSE );
   }

   SetAddress( a );
   SetPort( (short) port_number );

   return( Open() );
}

#pragma warning( default : 4100 )

BOOL CTalkingSocket::Open( const CString& a, const short p )
{
   WFCLTRACEINIT( TEXT( "CTalkingSocket::Open( host_name, port_number )" ) );
   ASSERT( p > 0 );

   SetAddress( a );
   SetPort( p );

   return( Open() );
}

BOOL CTalkingSocket::Open( const CString& _host_name, const CString& _port_name )
{
   WFCLTRACEINIT( TEXT( "CTalkingSocket::Open( host_name, port_name )" ) );

   SetAddress( _host_name );
   SetPort( _port_name );

   return( Open() );
}

// End of source
