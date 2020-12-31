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
** $Workfile: lsockets.cpp $
** $Revision: 28 $
** $Modtime: 2/14/00 5:03a $
** $Reuse Tracing Code: 1 $
*/

#if defined( _DEBUG ) && ! defined( WFC_STL )
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif // _DEBUG

#if ! defined( SOMAXCONN )
#define SOMAXCONN (0x7fffffff)
#endif // SOMAXCONN

CListeningSocket::CListeningSocket()
{
   WFCLTRACEINIT( TEXT( "CListeningSocket::CListeningSocket()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   m_Initialize();
}

CListeningSocket::~CListeningSocket()
{
   WFCLTRACEINIT( TEXT( "CListeningSocket::~CListeningSocket()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
}

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

void CListeningSocket::Dump( CDumpContext &dump_context ) const
{
   CSimpleSocket::Dump( dump_context );
   dump_context << TEXT( "{\n" );
   dump_context << TEXT( "   m_NumberOfSimultaneousSocketsToAllow = " ) << m_NumberOfSimultaneousSocketsToAllow << TEXT( "\n" );
   dump_context << TEXT( "}\n" );
}

#endif // _DEBUG

unsigned long CListeningSocket::GetBindToAddress( void ) const
{
   WFCLTRACEINIT( TEXT( "CListeningSocket::GetBindToAddress()" ) );

   return( m_BindToAddress );
}

int CListeningSocket::GetConnectionBacklog( void ) const
{
   WFCLTRACEINIT( TEXT( "CListeningSocket::GetConnectionBacklog()" ) );

   return( m_NumberOfSimultaneousSocketsToAllow );
}

void CListeningSocket::m_Initialize( void )
{
   WFCLTRACEINIT( TEXT( "CListeningSocket::m_Initialize()" ) );

   /*
   ** Make sure that everything is empty
   */

   m_SocketID                           = INVALID_SOCKET;
   m_NumberOfSimultaneousSocketsToAllow = SOMAXCONN;
   m_BindToAddress                      = INADDR_ANY;
}

BOOL CListeningSocket::Open( void )
{
   WFCLTRACEINIT( TEXT( "CListeningSocket::Open( void )" ) );
   ASSERT( m_Thunk_p != NULL );

   if ( m_SocketID != INVALID_SOCKET )
   {
      WFCTRACE( TEXT( "Server socket already created" ) );
      return( TRUE );
   }

   if ( m_PortNumberInNetworkByteOrder == 0 )
   {
      WFCTRACE( TEXT( "Can't create server socket without a port number" ) );
      return( FALSE );
   }

   /*
   ** Create the server (or listening) socket thingy
   */

   m_SocketID = m_Thunk_p->socket( AF_INET, SOCK_STREAM, 0 );

   if ( m_SocketID == INVALID_SOCKET )
   {
      WFCTRACEVAL( TEXT( "socket() failed at line " ), __LINE__ );

      m_ErrorCode = m_Thunk_p->WSAGetLastError();
      WFCTRACEERROR( m_ErrorCode );
      return( FALSE );
   }

   /*
   ** We've got a socket thingy but its useless. It doesn't have an address. Let's give it one.
   ** We do this by bind'ing an address and port number to it.
   */

   SOCKADDR_IN socket_address;

   socket_address.sin_family      = AF_INET;
   socket_address.sin_port        = m_PortNumberInNetworkByteOrder;
   socket_address.sin_addr.s_addr = m_Thunk_p->htonl( m_BindToAddress ); // We'll let anybody connect to us

   if ( m_Thunk_p->bind( m_SocketID, (LPSOCKADDR) &socket_address, sizeof( socket_address ) ) == SOCKET_ERROR )
   {
      WFCTRACEVAL( TEXT( "bind() failed at line " ), __LINE__ );

      m_ErrorCode = m_Thunk_p->WSAGetLastError();
      WFCTRACEERROR( m_ErrorCode );
      return( FALSE );
   }

   /*
   ** Now the socket thingy has an address and port number.
   */

   /*
   ** Now we make it a listening socket and start listening, program execution halts here
   */
   
   if ( m_Thunk_p->listen( m_SocketID, m_NumberOfSimultaneousSocketsToAllow ) == SOCKET_ERROR )
   {
      WFCTRACEVAL( TEXT( "Can't listen() at line " ), __LINE__ );

      m_ErrorCode = m_Thunk_p->WSAGetLastError();
      WFCTRACEERROR( m_ErrorCode );
      return( FALSE );
   }

   return( TRUE );
}

#pragma warning( disable : 4100 )

#if ! defined( WFC_STL )
BOOL CListeningSocket::Open( LPCTSTR ChannelName, UINT port_number, CFileException *pError )
#else // WFC_STL
BOOL CListeningSocket::Open( LPCTSTR ChannelName, UINT port_number )
#endif // WFC_STL
{
   WFCLTRACEINIT( TEXT( "CListeningSocket::Open( LPCTSTR )" ) );

   SetPort( (short) port_number );

   return( Open() );
}

void CListeningSocket::SetBindToAddress( unsigned long address )
{
   WFCLTRACEINIT( TEXT( "CListeningSocket::SetBindToAddress()" ) );
   m_BindToAddress = address;
}

void CListeningSocket::SetConnectionBacklog( int backlog )
{
   WFCLTRACEINIT( TEXT( "CListeningSocket::SetConnectionBacklog()" ) );
   m_NumberOfSimultaneousSocketsToAllow = backlog;
}

#pragma warning( default : 4100 )

BOOL CListeningSocket::WaitForConnection( void )
{
   WFCLTRACEINIT( TEXT( "CListeningSocket::WaitForConnection()" ) );
   ASSERT( m_Thunk_p != NULL );

   if ( m_PortNumberInNetworkByteOrder == 0 )
   {
      return( FALSE );
   }

   if ( m_SocketID == INVALID_SOCKET )
   {
      if ( Open() == FALSE )
      {
         WFCTRACEVAL( TEXT( "Can't open() at line " ), __LINE__ );
         return( FALSE );
      }
   }

   SOCKADDR incoming_socket_address;

   int byte_count = 0;

   byte_count = sizeof( incoming_socket_address );

   ::ZeroMemory( &incoming_socket_address, byte_count );

   // The filename should be the host name followed by IP address then port number.
   // Example: "Sammy (195.99.72.1) Port: 23"

   short port_number = 0;

   GetPort( port_number );

#if ! defined( WFC_STL )
   m_strFileName.Format( TEXT( "%s (%s) Port: %d" ), (LPCTSTR) Name, (LPCTSTR) Address, (int) port_number );
#else // WFC_STL
   m_FileName.Format( TEXT( "%s (%s) Port: %d" ), (LPCTSTR) Name, (LPCTSTR) Address, (int) port_number );
#endif // WFC_STL

   /*
   ** PROGRAM EXECUTION STOPS HERE!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
   **
   ** accept() is a blocking call meaning that the this thread of execution is paused
   ** (ie goes to sleep) until someone on the network connects to us. We will "wake up"
   ** when that happens and continue along our merry way.
   */

   int socket_id = 0;

   socket_id = m_Thunk_p->accept( m_SocketID, &incoming_socket_address, &byte_count );

   if ( socket_id == INVALID_SOCKET )
   {
      m_ErrorCode = m_Thunk_p->WSAGetLastError();
      WFCTRACEERROR( m_ErrorCode );
      return( FALSE );
   }

   /*
   ** The method for actually converting the incoming address to something that is human
   ** readable is either undocumented or extremely poorly documented. Not suprising since
   ** the idea of sockets came out of the Unix world...
   */

   LPSTR dotted_ip_address = (LPSTR) NULL;
    
   struct in_addr internet_address;

   /*
   ** Aren't these structure member names intuitively obvious??
   */

   internet_address.S_un.S_un_b.s_b1 = incoming_socket_address.sa_data[ 2 ];
   internet_address.S_un.S_un_b.s_b2 = incoming_socket_address.sa_data[ 3 ];
   internet_address.S_un.S_un_b.s_b3 = incoming_socket_address.sa_data[ 4 ];
   internet_address.S_un.S_un_b.s_b4 = incoming_socket_address.sa_data[ 5 ];

   dotted_ip_address = m_Thunk_p->inet_ntoa( internet_address );

   if ( dotted_ip_address == (LPSTR) NULL )
   {
      m_ErrorCode = WSAEINVAL;
	  return( FALSE );
   }

   ULONG temp_long = 0L;

   temp_long = m_Thunk_p->inet_addr( (LPCSTR) dotted_ip_address );

   if ( temp_long == INADDR_NONE )
   {
      m_ErrorCode = WSAEINVAL;
	  return( FALSE );
   }

   // Now see if we should resolve the IP address to a machine name
   // This is a performance hit since we have to consult DNS for the
   // answer.

   if ( ( m_Options & optionsDontResolveHostName ) )
   {
      // User doesn't care about the machine name in a humanly readable form

      CString dotted_ip_address_string;

      ::wfc_convert_lpcstr_to_cstring( dotted_ip_address, dotted_ip_address_string );

      WFCTRACEVAL( TEXT( "Connected established with " ), dotted_ip_address_string );

      OnNewConnection( socket_id, dotted_ip_address_string, dotted_ip_address_string );

      return( TRUE );
   }

   LPHOSTENT host_entry_p = (LPHOSTENT) NULL;

   host_entry_p = m_Thunk_p->gethostbyaddr( (const char *) &temp_long, 4, PF_INET );

   if ( host_entry_p == (LPHOSTENT) NULL )
   {
      m_ErrorCode = m_Thunk_p->WSAGetLastError();
      WFCTRACEERROR( m_ErrorCode );
      return( FALSE );
   }

   CString host_name_string;
   CString dotted_ip_address_string;

   ::wfc_convert_lpcstr_to_cstring( host_entry_p->h_name, host_name_string );
   ::wfc_convert_lpcstr_to_cstring( dotted_ip_address, dotted_ip_address_string );

   WFCTRACEVAL( TEXT( "Connected established with " ), host_name_string );
   WFCTRACEVAL( TEXT( "Their IP address is " ), dotted_ip_address_string );

   OnNewConnection( socket_id, host_name_string, dotted_ip_address_string );

   return( TRUE );
}

BOOL CListeningSocket::WaitForConnection( const int port_number )
{
   WFCLTRACEINIT( TEXT( "CListeningSocket::WaitForConnection( const int port_number )" ) );
   ASSERT( port_number > 0 );

   SetPort( (short) port_number );

   return( WaitForConnection() );
}

BOOL CListeningSocket::WaitForConnection( LPCTSTR p_name )
{
   WFCLTRACEINIT( TEXT( "CListeningSocket::WaitForConnection( LPCTSTR p_name )" ) );
   ASSERT( p_name != NULL );

   if ( p_name == NULL )
   {
      m_ErrorCode = ERROR_INVALID_PARAMETER;
      return( FALSE );
   }

   SetPort( p_name );

   return( WaitForConnection() );
}

// End of source

#if 0
<HTML>

<HEAD>
<TITLE>WFC - CListeningSocket</TITLE>
<META name="keywords" content="WFC, MFC extension library, freeware class library, Win32, source code">
<META name="description" content="The C++ class that encapsulates server side sockets.">
</HEAD>

<BODY>

<H1>CListeningSocket : <A HREF="sockets.htm">CSimpleSocket</A></H1>
$Revision: 28 $
<HR>

<H2>Description</H2>

This class creates a socket that others can connect to.

<H2>Methods</H2>

<DL COMPACT>

<DT><PRE>unsigned long <B><A NAME="GetBindToAddress">GetBindToAddress</A></B>( void ) const</PRE><DD>
Returns the address of the local end of the socket. By default,
this is <CODE>INADDR_ANY</CODE> meaning any network transport on
the local machine will be the end point for the socket.

<DT><PRE>int <B><A NAME="GetConnectionBacklog">GetConnectionBacklog</A></B>( void ) const</PRE><DD>
Returns the number of simultaneous connections that TCP/IP
will pause before sending ECONNREFUSED errors to the would-be
connectors. This is set to <CODE>SOMAXCONN</CODE> by default.

<DT><PRE>void <B><A NAME="OnNewConnection">OnNewConnection</A></B>( SOCKET socket_id, LPCTSTR host_name, LPCTSTR dotted_ip_address ) = 0</PRE><DD>
This method is called when a connection has been made to your socket. It is a
pure virtual function because <B>CListeningSocket</B> has no idea what you
want to do when someone connects to you. This is where you will put your
business logic.

<DT><PRE>BOOL <B><A NAME="Open">Open</A></B>( void )
BOOL <B>Open</B>( LPCTSTR machine_name_or_address, UINT port_number = 23, CFileException * = NULL )</PRE><DD>
Creates the listening socket. It does not wait for someone to connect to this
fledgling socket.

<DT><PRE>void <B><A NAME="SetBindToAddress">SetBindToAddress</A></B>( unsigned long address )</PRE><DD>
Let's you specify which network transport will be used to establish
the local end of the socket. If you have two (or more) LAN cards in
your computer, each with their own IP address, you can specify which
one of those cards will be used for the socket by putting its address
in the <CODE>address</CODE> parameter before calling <B>Open</B>.

<DT><PRE>void <B><A NAME="SetConnectionBacklog">SetConnectionBacklog</A></B>( int backlog )</PRE><DD>
Let's you specify the number of incoming connections that will
be queued up. If two clients attempt to connect at the exact
same time, one will be immediately accepted while the other will
be queued (waiting for <B>OnNewConnection</B> to return).

<DT><PRE>BOOL <B><A NAME="WaitForConnection">WaitForConnection</A></B>( LPCTSTR port_name )
BOOL <B>WaitForConnection</B>( const int port_number )
BOOL <B>WaitForConnection</B>( void )</PRE><DD>
Begins the waiting process. Program execution will halt here until someone
connects to your socket. <B>OnNewConnection</B>() will be called by this
method before it returns. It will return TRUE if the connection was made or
FALSE if there was a problem.

</DL>

<H2>Example</H2>

<PRE><CODE>#include &lt;wfc.h&gt;

class CTimeSocket : <B>CListeningSocket</B>
{
   public:

      virtual void OnNewConnection( SOCKET socket_id, const char *host_name, const char *dotted_ip_address_string );
};

void CTimeSocket::OnNewConnection( SOCKET socket_id, const char *host_name, const char *dotted_ip_address )
{
   <A HREF="WfcTrace.htm">WFCTRACEINIT</A>( TEXT( &quot;CTimeSocket::OnNewConnection()&quot; ) );

   // This class sends the new client the time then disconnects

   CSimpleSocketFile socket( socket_id, host_name, dotted_ip_address );

   DWORD number_of_seconds_since_1970 = 0;

   CTime time_now = CTime::GetCurrentTime();

   number_of_seconds_since_1970 time_now.GetTime();

   socket.Write( (const VOID *) &number_of_seconds_since_1970, (long) 4 );
   // the socket is closed in the CSimpleSocketFile class destructor
}

int _tmain( int number_of_command_line_arguments, LPCTSTR command_line_arguments[] )
{
   <A HREF="WfcTrace.htm">WFCTRACEINIT</A>( TEXT( &quot;_tmain()&quot; ) );

   CTimeSocket time_service;

   // Wait on port 37 (the &quot;time&quot; port)

   while( time_service.WaitForConnection( 37 ) != FALSE )
   {
      _tprintf( TEXT( &quot;We had a connection\n&quot; ) );
   }

   return( EXIT_SUCCESS );
}</CODE></PRE>

<H2>API's Used</H2>

<B>CListeningSocket</B> uses the following API's:

<UL>
<LI>accept
<LI>bind
<LI>gethostbyaddr
<LI>htonl
<LI>inet_addr
<LI>inet_ntoa
<LI>listen
<LI>socket
<LI>WSAGetLastError
</UL>

<HR><I>Copyright, 2000, <A HREF="mailto:wfc@pobox.com">Samuel R. Blackburn</A></I><BR>
$Workfile: lsockets.cpp $<BR>
$Modtime: 2/14/00 5:03a $
</BODY>

</HTML>
The following line should go in AUTOEXP.DAT so the debugging tooltips will format properly
ToolTipFormatLine=CSimpleSocket=hFile=<m_hFile> name=<m_strFileName.m_pchData,s>
#endif
