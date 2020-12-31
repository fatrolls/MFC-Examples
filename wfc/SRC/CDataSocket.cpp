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
** $Workfile: CDataSocket.cpp $
** $Revision: 15 $
** $Modtime: 1/17/00 8:59a $
** $Reuse Tracing Code: 1 $
*/

#if defined( _DEBUG ) && ! defined( WFC_STL )
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif // _DEBUG

CDataSocket::CDataSocket()
{
   WFCLTRACEINIT( TEXT( "CDataSocket::CDataSocket()" ) );
   m_Socket_p = NULL;
}

CDataSocket::CDataSocket( CSimpleSocket * socket_p )
{
   WFCLTRACEINIT( TEXT( "CDataSocket::CDataSocket( CSimpleSocket )" ) );
   m_Socket_p = NULL;
   Attach( socket_p );
}

CDataSocket::~CDataSocket()
{
   WFCLTRACEINIT( TEXT( "CDataSocket::~CDataSocket()" ) );
}

void CDataSocket::Attach( CSimpleSocket * socket_p )
{
   WFCLTRACEINIT( TEXT( "CDataSocket::Attach()" ) );
   m_Socket_p = socket_p;
}

UINT CDataSocket::Read( void * buffer, UINT size_of_buffer )
{
   WFCLTRACEINIT( TEXT( "CDataSocket::Read()" ) );
   ASSERT( m_Socket_p != NULL );

   if ( m_Socket_p == NULL )
   {
      WFCTRACE( TEXT( "You have no socket attached." ) );
      return( 0 );
   }

   // We were passed a pointer, don't trust it

   try
   {
      BYTE * temporary_buffer = (BYTE *) buffer;

      BOOL exit_loop = FALSE;

      UINT return_value = 0;

      int number_of_bytes_read    = 0;
      int number_of_bytes_to_read = size_of_buffer;

      while( exit_loop == FALSE )
      {
         number_of_bytes_read = m_Socket_p->Read( temporary_buffer, number_of_bytes_to_read );

         if ( number_of_bytes_read == SOCKET_ERROR || number_of_bytes_read == 0 )
         {
            WFCTRACE( TEXT( "ERROR! Can't read socket\n" ) );
            exit_loop = TRUE;
         }
         else
         {
            return_value            += number_of_bytes_read;
            temporary_buffer        += number_of_bytes_read;
            number_of_bytes_to_read -= number_of_bytes_read;

            if ( return_value >= size_of_buffer )
            {
               exit_loop = TRUE;
            }
         }
      }

      WFCTRACEVAL( TEXT( "Number of bytes read is " ), return_value );

      return( return_value );
   }
   catch( ... )
   {
      return( 0 );
   }
}

long CDataSocket::Seek( long , UINT )
{
   WFCLTRACEINIT( TEXT( "CDataSocket::Seek()" ) );
   return( 0 );
}

void CDataSocket::Write( const void * buffer, UINT number_of_bytes_to_write )
{
   WFCLTRACEINIT( TEXT( "CDataSocket::Write()" ) );

   if ( m_Socket_p == NULL )
   {
      WFCTRACE( TEXT( "You have to socket attached" ) );
      return;
   }

   // We were passed a pointer, don't trust it

   try
   {
      m_Socket_p->Write( buffer, number_of_bytes_to_write );
   }
   catch( ... )
   {
      return;
   }
}

// End of source

#if 0
<HTML>

<HEAD>
<TITLE>WFC - CDataSocket</TITLE>
<META name="keywords" content="WFC, MFC extension library, freeware class library, Win32, source code">
<META name="description" content="The C++ class that handles sending/receiving chunks of RIFF data through a TCP/IP socket. This is the basis for a generic protocol.">
</HEAD>

<BODY>

<H1>CDataSocket : <A HREF="CDataFile.htm">CDataFile</A></H1>
$Revision: 15 $<BR>
<HR>

<H2>Description</H2>

This class allows you handle the input and output of
<A HREF="CDataChunk.htm">CDataChunk</A> objects 
through a TCP/IP socket easily.

<H2>Data Members</H2>
None.

<H2>Constructors</H2>

<DL COMPACT>

<DT><PRE><B>CDataSocket</B>()
<B>CDataSocket</B>( <A HREF="SOCKETS.htm">CSimpleSocket</A> * socket_p )</PRE><DD>
Constructs the object.

</DL>

<H2>Methods</H2>

<DL COMPACT>

<DT><PRE>void <B>Attach</B>( <A HREF="SOCKETS.htm">CSimpleSocket</A> * socket_p )</PRE><DD>
Tells <B>CDataSocket</B> which socket to use.

<DT><PRE>UINT <B>Read</B>( void * buffer, UINT number_of_bytes_to_read )</PRE><DD>
Reads data from the socket.

<DT><PRE>long <B>Seek</B>( long offset, UINT from )</PRE><DD>
Intercepts this call. It doesn't make a whole lot of sense to <B>Seek</B>()
around a socket.

<DT><PRE>void <B>Write</B>( const void * buffer, UINT number_of_bytes_to_read )</PRE><DD>
Reads data from the socket.

</DL>

<H2>Example</H2>
<PRE><CODE>#include &lt;wfc.h&gt;

void read_next_chunk( <B>CDataSocket</B>&amp; socket, <A HREF="CDataChunk.htm">CDataChunk</A>&amp; data )
{
   <A HREF="WfcTrace.htm">WFCTRACEINIT</A>( TEXT( &quot;read_next_chunk()&quot; ) );

   socket.GetData( data );

   _tprintf( TEXT( &quot;Read %lu bytes\n&quot; ), data.Data.GetSize() );
}</CODE></PRE>

<HR><I>Copyright, 2000, <A HREF="mailto:wfc@pobox.com">Samuel R. Blackburn</A></I><BR>
$Workfile: CDataSocket.cpp $<BR>
$Modtime: 1/17/00 8:59a $
</BODY>

</HTML>
#endif
