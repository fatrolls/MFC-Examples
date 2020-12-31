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
** $Workfile: cping.cpp $
** $Revision: 28 $
** $Modtime: 3/17/00 4:36p $
** $Reuse Tracing Code: 1 $
*/

#if defined( _DEBUG ) && ! defined( WFC_STL )
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif // _DEBUG

CPing::CPing()
{
   WFCLTRACEINIT( TEXT( "CPing::CPing()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );

   m_ICMP_DLL_Instance = ::LoadLibrary( TEXT( "ICMP.DLL" ) );

   if ( m_ICMP_DLL_Instance != NULL )
   {
      WFCTRACE( TEXT( "Loaded ICMP.DLL" ) );
      m_Open     = (ICMP_OPEN_FUNCTION)      ::GetProcAddress( m_ICMP_DLL_Instance, "IcmpCreateFile"  ); // Cannot be UNICODE string
      m_Close    = (ICMP_CLOSE_FUNCTION)     ::GetProcAddress( m_ICMP_DLL_Instance, "IcmpCloseHandle" ); // Cannot be UNICODE string
      m_SendEcho = (ICMP_SEND_ECHO_FUNCTION) ::GetProcAddress( m_ICMP_DLL_Instance, "IcmpSendEcho"    ); // Cannot be UNICODE string
   }
   else
   {
      WFCTRACE( TEXT( "Can't load ICMP.DLL" ) );
      WFCTRACEERROR( ::GetLastError() );
      m_Open     = NULL;
      m_Close    = NULL;
      m_SendEcho = NULL;
   }
}

CPing::~CPing()
{
   WFCLTRACEINIT( TEXT( "CPing::CPing()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );

   if ( m_ICMP_DLL_Instance != (HMODULE) NULL )
   {
      WFCTRACE( TEXT( "Freeing ICMP.DLL" ) );
      ::FreeLibrary( m_ICMP_DLL_Instance );
   }

   m_Open     = NULL;
   m_Close    = NULL;
   m_SendEcho = NULL;
}

void CPing::ConvertErrorToString( DWORD error_code, CString& meaning ) const
{
   WFCLTRACEINIT( TEXT( "CPing::ConvertErrorToString()" ) );

   switch( error_code )
   {
      case IP_SUCCESS:

         meaning = TEXT( "IP_SUCCESS: Success" );
         break;

      case IP_BUF_TOO_SMALL:

         meaning = TEXT( "IP_BUFF_TOO_SMALL: Buffer too small" );
         break;

      case IP_DEST_NET_UNREACHABLE:

         meaning = TEXT( "IP_DEST_NET_UNREACHABLE: Network unreachable" );
         break;

      case IP_DEST_HOST_UNREACHABLE:

         meaning = TEXT( "IP_DEST_HOST_UNREACHABLE: Destination Host Unreachable" );
         break;

      case IP_DEST_PROT_UNREACHABLE:

         meaning = TEXT( "IP_DEST_PROT_UNREACHABLE" );
         break;

      case IP_DEST_PORT_UNREACHABLE:

         meaning = TEXT( "IP_DEST_PORT_UNREACHABLE" );
         break;

      case IP_NO_RESOURCES:

         meaning = TEXT( "IP_NO_RESOURCES" );
         break;

      case IP_BAD_OPTION:

         meaning = TEXT( "IP_BAD_OPTION" );
         break;

      case IP_HW_ERROR:

         meaning = TEXT( "IP_HW_ERROR: Hardware Error" );
         break;

      case IP_PACKET_TOO_BIG:

         meaning = TEXT( "IP_PACKET_TOO_BIG: Packet too big" );
         break;

      case IP_REQ_TIMED_OUT:

         meaning = TEXT( "IP_REQ_TIMED_OUT: Request timed out" );
         break;

      case IP_BAD_REQ:

         meaning = TEXT( "IP_BAD_REQ" );
         break;

      case IP_BAD_ROUTE:

         meaning = TEXT( "IP_BAD_ROUTE" );
         break;

      case IP_TTL_EXPIRED_TRANSIT:

         meaning = TEXT( "IP_TTL_EXPIRED_TRANSIT" );
         break;

      case IP_TTL_EXPIRED_REASSEM:

         meaning = TEXT( "IP_TTL_EXPIRED_REASSEM" );
         break;

      case IP_PARAM_PROBLEM:

         meaning = TEXT( "IP_PARAM_PROBLEM" );
         break;

      case IP_SOURCE_QUENCH:

         meaning = TEXT( "IP_SOURCE_QUENCH" );
         break;

      case IP_OPTION_TOO_BIG:

         meaning = TEXT( "IP_OPTION_TOO_BIG" );
         break;

      case IP_BAD_DESTINATION:

         meaning = TEXT( "IP_BAD_DESTINATION" );
         break;

      case IP_ADDR_DELETED:

         meaning = TEXT( "IP_ADDR_DELETED" );
         break;

      case IP_SPEC_MTU_CHANGE:

         meaning = TEXT( "IP_SPEC_MTU_CHANGE" );
         break;

      case IP_MTU_CHANGE:

         meaning = TEXT( "IP_MTU_CHANGE" );
         break;

      case IP_GENERAL_FAILURE:

         meaning = TEXT( "IP_GENERAL_FAILURE" );
         break;

      case IP_PENDING:

         meaning = TEXT( "IP_PENDING" );
         break;

      default:

         meaning.Format( TEXT( "Unknown error %lu" ), error_code );
         break;
   }
}

DWORD CPing::Ping( const CString& name_or_address, CPingResults * results_p, short desired_time_to_live )
{
   WFCLTRACEINIT( TEXT( "CPing::Ping()" ) );

   if ( m_Open == NULL )
   {
      WFCTRACE( TEXT( "m_Open is not set" ) );
      m_ErrorCode = ERROR_INVALID_ADDRESS;
      return( 0 );
   }

   // We were passed a pointer, don't trust it

   try
   {
      HANDLE icmp_handle = m_Open();

      if ( icmp_handle == (HANDLE) INVALID_HANDLE_VALUE )
      {
         m_ErrorCode = ERROR_INVALID_HANDLE;
         return( 0 );
      }

      DWORD status = 0;

      BYTE buffer[ 60 ];

      ::ZeroMemory( buffer, sizeof( buffer ) );

      // OK, I'll get a little vain, Yes, this is ASCII strings and not UNICODE dependent

      ::strcpy( (char *) buffer, "Samuel R. Blackburn " ); // 20
      ::strcat( (char *) buffer, "Samuel R. Blackburn " ); // 40
      ::strcat( (char *) buffer, "Samuel R. Blackburn"  ); // 59

      IP_ECHO_REPLY * echo_reply_p = (IP_ECHO_REPLY *) GlobalAllocPtr( GHND, sizeof( IP_ECHO_REPLY ) + 59 );

      if ( echo_reply_p != NULL )
      {
         SetAddress( name_or_address );

         echo_reply_p->Options.Ttl = (unsigned char) desired_time_to_live;
         echo_reply_p->Data        = (VOID *) (LPCTSTR) Name;
         echo_reply_p->DataSize    = 59;

         if ( m_SendEcho == NULL )
         {
            WFCTRACE( TEXT( "m_SendEcho not set" ) );
            m_ErrorCode = ERROR_INVALID_ADDRESS;
            return( 0 );
         }

         // Thanks go to Curits Yanko (cyanko@ziplink.net) for finding
         // a boo boo here. I was linking inet_addr() and not thunking it.

         ULONG internet_address = 0L;

         // DANGER! DANGER! DANGER! inet_addr() is not UNICODE correct!!!

#if defined( _UNICODE )

         {
            char address[ 20 ];

            ZeroMemory( address, sizeof( address ) );

            ::UNICODE_to_ASCII( Address, address );

            internet_address = m_Thunk_p->inet_addr( (const char *) address );
         }

#else

         internet_address = m_Thunk_p->inet_addr( (const char *) Address );

#endif // _UNICODE

         if ( internet_address == INADDR_NONE )
         {
            WFCTRACEERROR( GetLastError() );

            CString meaning;

            ConvertErrorToString( GetLastError(), meaning );

            WFCTRACEVAL( TEXT( "Or " ), meaning );
         }

         // Now that we're done with the thunker...

         status = m_SendEcho( icmp_handle,
                              internet_address,
                              buffer,
                              59,
                              NULL,
                              echo_reply_p,
                              sizeof( IP_ECHO_REPLY ) + 59,
                              5000 );

         if ( status != 0 )
         {
            if ( results_p != NULL )
            {
               results_p->Copy( echo_reply_p );
            }
         }
         else
         {
            m_ErrorCode = ::GetLastError();
            WFCTRACEERROR( m_ErrorCode );

            CString meaning;

            ConvertErrorToString( m_ErrorCode, meaning );
            WFCTRACEVAL( TEXT( "384 Or " ), meaning );
         }

         GlobalFreePtr( echo_reply_p );
         echo_reply_p = NULL;
      }

      m_Close( icmp_handle );

      return( status );
   }
   catch( ... )
   {
      m_ErrorCode = ERROR_EXCEPTION_IN_SERVICE;
      return( 0 );
   }
}

BOOL CPing::Open( void )
{
   WFCLTRACEINIT( TEXT( "CPing::Open()" ) );
   return( TRUE );
}

#if ! defined( WFC_STL )
BOOL CPing::Open( const char *, UINT, CFileException* )
#else // WFC_STL
BOOL CPing::Open( const char *, UINT )
#endif // WFC_STL
{
   WFCLTRACEINIT( TEXT( "CPing::Open( const char * )" ) );
   return( TRUE );
}

// End of source

#if 0
<HTML>

<HEAD>
<TITLE>WFC - CPing</TITLE>
<META name="keywords" content="WFC, MFC extension library, freeware class library, Win32, source code">
<META name="description" content="The C++ class that lets you ping TCP/IP hosts.">
</HEAD>

<BODY>

<H1>CPing : <A HREF="sockets.htm">CSimpleSocket</A></H1>
$Revision: 28 $
<HR>

<H2>Description</H2>
This class makes it easy for you to ping another TCP/IP host.

<H2>Data Members</H2><B>None.</B><P>

<H2>Methods</H2>

<DL COMPACT>

<DT><PRE>void <B>ConvertErrorToString</B>( DWORD error_code, CString&amp; meaning ) const</PRE><DD>
If <B>Ping</B>() should fail, this will translate the error code into
something humanly readable.

<DT><PRE>DWORD <B>Ping</B>( const CString&amp; name_or_address, <A HREF="CPingRes.htm">CPingResults</A> * results_p, short desired_time_to_live )</PRE><DD>
Sends the ping request and received the results. Results are put into a
<A HREF="CPingRes.htm">CPingResults</A> object. It returns the number of
replies received.

</DL>

<H2>Example</H2><PRE><CODE>#include &lt;wfc.h&gt;
#pragma hdrstop

int _tmain( int number_of_command_line_arguments, TCHAR *command_line_arguments[] )
{
   <A HREF="WfcTrace.htm">WFCTRACEINIT</A>( TEXT( &quot;_tmain()&quot; ) );

   <A HREF="SOCKETS.htm">CSimpleSocket</A>::StartWindowsSockets();

   <B>CPing</B> ping;

   DWORD return_value = 0;

   <A HREF="CPingRes.htm">CPingResults</A> results;

   return_value = ping.Ping( TEXT( &quot;20.2.1.3&quot; ), &results );

   if ( return_value == 0 )
   {
      DWORD error_code = ping.GetErrorCode();

      CString error_message;

      ping.ConvertErrorToString( error_code, error_message );

      _tprintf( TEXT( &quot;Ping Error: %s\n&quot; ) ), (LPCTSTR) error_message );
   }
   else
   {
      _tprintf( TEXT( &quot;Ping: %s Round Trip %lums TTL: %d\n&quot; ), 
              (LPCTSTR) results.Address,
              results.RoundTripTimeInMilliseconds,
              (int) results.TimeToLive );
   }

   <A HREF="SOCKETS.htm">CSimpleSocket</A>::StopWindowsSockets();

   return( EXIT_SUCCESS );
}</CODE></PRE>

<H2>API's Used</H2>

<B>CPing</B> uses the following API's:

<UL>
<LI>FreeLibrary
<LI>GlobalAllocPtr
<LI>GlobalFreePtr
<LI>IcmpCloseHandle
<LI>IcmpCreateFile
<LI>IcmpSendEcho
<LI>inet_addr
<LI>LoadLibrary
<LI>ZeroMemory
</UL>

<HR><I>Copyright, 2000, <A HREF="mailto:wfc@pobox.com">Samuel R. Blackburn</A></I><BR>
$Workfile: cping.cpp $<BR>
$Modtime: 3/17/00 4:36p $
</BODY>

</HTML>
#endif
