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
** $Workfile: CPingRes.cpp $
** $Revision: 22 $
** $Modtime: 1/17/00 9:10a $
** $Reuse Tracing Code: 1 $
*/

#if defined( _DEBUG ) && ! defined( WFC_STL )
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

#if ! defined(  WFC_NO_SERIALIZATION )
IMPLEMENT_SERIAL( CPingResults, CObject, 1 )
#endif // WFC_NO_SERIALIZATION

#if defined( _DEBUG ) && ! defined( WFC_STL )
#define new DEBUG_NEW
#endif // _DEBUG

CPingResults::CPingResults()
{
   WFCLTRACEINIT( TEXT( "CPingResults::CPingResults()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   Empty();
}

CPingResults::CPingResults( const CPingResults& source )
{
   WFCLTRACEINIT( TEXT( "CPingResults::CPingResults( CPingResults& )" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   Copy( source );
}

CPingResults::CPingResults( const CPingResults * source )
{
   WFCLTRACEINIT( TEXT( "CPingResults::CPingResults( CPingResults * )" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   Copy( source );
}

CPingResults::CPingResults( const IP_ECHO_REPLY& source )
{
   WFCLTRACEINIT( TEXT( "CPingResults::CPingResults(IP_ECHO_REPLY& )" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   Copy( source );
}

CPingResults::CPingResults( const IP_ECHO_REPLY * source )
{
   WFCLTRACEINIT( TEXT( "CPingResults::CPingResults( IP_ECHO_REPLY * )" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   Copy( source );
}

CPingResults::~CPingResults()
{
   WFCLTRACEINIT( TEXT( "CPingResults::~CPingResults()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   Empty();
}

void CPingResults::Copy( const CPingResults& source )
{
   WFCLTRACEINIT( TEXT( "CPingResults::Copy( CPingResults& )" ) );

   // Copying ourself is a silly thing to do

   if ( &source == this )
   {
      WFCTRACE( TEXT( "Attempt to make a copy of ourself (such silliness)." ) );
      return;
   }

   Address                     = source.Address;
   RoundTripTimeInMilliseconds = source.RoundTripTimeInMilliseconds;
   TimeToLive                  = source.TimeToLive;
}

void CPingResults::Copy( const CPingResults * source )
{
   WFCLTRACEINIT( TEXT( "CPingResults::Copy( CPingResults * )" ) );
   ASSERT( source != NULL );

   // We were passed a pointer, don't trust it

   try
   {
      if ( source != NULL )
      {
         Copy( *source );
      }
      else
      {
         Empty();
      }
   }
   catch( ... )
   {
      Empty();
   }
}

void CPingResults::Copy( const IP_ECHO_REPLY& source )
{
   WFCLTRACEINIT( TEXT( "CPingResults::Copy( IP_ECHO_REPLY& )" ) );
   Address.Format( TEXT( "%d.%d.%d.%d" ),
             (int) LOBYTE( LOWORD( source.Address ) ),
             (int) HIBYTE( LOWORD( source.Address ) ),
             (int) LOBYTE( HIWORD( source.Address ) ),
             (int) HIBYTE( HIWORD( source.Address ) ) );
   RoundTripTimeInMilliseconds = source.RoundTripTime;
   TimeToLive                  = source.Options.Ttl;
}

void CPingResults::Copy( const IP_ECHO_REPLY * source )
{
   WFCLTRACEINIT( TEXT( "CPingResults::Copy( IP_ECHO_REPLY * )" ) );
   ASSERT( source != NULL );

   // We were passed a pointer, don't trust it

   try
   {
      if ( source != NULL )
      {
         Copy( *source );
      }
      else
      {
         Empty();
      }
   }
   catch( ... )
   {
      Empty();
   }
}

void CPingResults::Empty( void )
{
   WFCLTRACEINIT( TEXT( "CPingResults::Empty()" ) );
   Address.Empty();
   RoundTripTimeInMilliseconds = 0;
   TimeToLive = 0;
}

#if ! defined(  WFC_NO_SERIALIZATION )

void CPingResults::Serialize( CArchive& archive )
{
   WFCLTRACEINIT( TEXT( "CPingResults::Serialize()" ) );

   CObject::Serialize( archive );

   if ( archive.IsStoring() )
   {
      archive << Address;
      archive << RoundTripTimeInMilliseconds;
      archive << TimeToLive;
   }
   else
   {
      archive >> Address;
      archive >> RoundTripTimeInMilliseconds;
      archive >> TimeToLive;
   }
}

#endif // WFC_NO_SERIALIZATION

CPingResults& CPingResults::operator = ( const CPingResults& source )
{
   WFCLTRACEINIT( TEXT( "CPingResults::operator = ()" ) );
   Copy( source );
   return( *this );
}

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

void CPingResults::Dump( CDumpContext& dump_context ) const
{
   CObject::Dump( dump_context );

   dump_context << TEXT( "{\n" );
   dump_context << TEXT( "   Address is                   \"" ) << Address << TEXT( "\"\n" );
   dump_context << TEXT( "   RoundTripTimeInMilliseconds is " ) << RoundTripTimeInMilliseconds << TEXT( "\n" );
   dump_context << TEXT( "   TimeToLive                  is " ) << TimeToLive << TEXT( "\n" );
   dump_context << TEXT( "}\n" );
}

#endif // _DEBUG

// End of source

#if 0
<HTML>

<HEAD>
<TITLE>WFC - CPingResults</TITLE>
<META name="keywords" content="WFC, MFC extension library, freeware class library, Win32, source code">
<META name="description" content="The C++ class that holds the results of a ping.">
</HEAD>

<BODY>
<H1>CPingResults</H1>
$Revision: 22 $
<HR>

<H2>Description</H2>
This class is filled in by
<A HREF="CPing.htm">CPing::Ping()</A>. It contains the data gathered in the ping.

<H2>Constructors</H2>

<DL COMPACT>

<DT><PRE><B>CPingResults</B>()
<B>CPingResults</B>( const CPingResults&amp;   source )
<B>CPingResults</B>( const CPingResults *  source )
<B>CPingResults</B>( const IP_ECHO_REPLY&amp;  source )
<B>CPingResults</B>( const IP_ECHO_REPLY * source )</PRE><DD>
Constructs the object.

</DL>

<H2>Data Members</H2>

<DL COMPACT>

<DT><PRE>CString <B>Address</B></PRE><DD>The dotted IP address of the pinged host.

<DT><PRE>DWORD <B>RoundTripTimeInMilliseconds</B></PRE><DD>How many milliseconds it took for the packet to go and come back.

<DT><PRE>BYTE <B>TimeToLive</B></PRE><DD>Number of &quothops&quot

</DL>

<H2>Methods</H2>

<DL COMPACT>

<DT><PRE>void <B>Copy</B>( const CPingResults&amp;   source )
void <B>Copy</B>( const CPingResults *  source )
void <B>Copy</B>( const IP_ECHO_REPLY&amp;  source )
void <B>Copy</B>( const IP_ECHO_REPLY * source )</PRE><DD>
Copies other <B>CPingResults</B> classes or IP_ECHO_REPLY structures.

<DT><PRE>void <B>Dump</B>( CDumpContext&amp; dump_context ) const</PRE><DD>
Present only in debug builds. Dumps the contents of this object to the
<CODE>dump_context</CODE>.

<DT><PRE>void <B>Empty</B>( void )</PRE><DD>
Resets all data members to an emtpy state.

</DL>

<H2>Example</H2>

<PRE><CODE>#include &lt;wfc.h&gt;
#pragma hdrstop

int _tmain( int number_of_command_line_arguments, LPCTSTR command_line_arguments[] )
{
   <A HREF="WfcTrace.htm">WFCTRACEINIT</A>( TEXT( &quot;_tmain()&quot; ) );

   <A HREF="SOCKETS.htm">CSimpleSocket</A>::StartWindowsSockets();

   <A HREF="CPing.htm">CPing</A> ping;

   DWORD return_value = 0;

   <B>CPingResults</B> results;

   return_value = ping.Ping( TEXT( &quot;20.2.1.3&quot; ), &results );

   if ( return_value == 0 )
   {
      DWORD error_code = ping.GetErrorCode();

      CString error_message;

      ping.ConvertErrorToString( error_code, error_message );

      _tprintf( TEXT( &quot;Ping Error: %s\n&quot; ), (LPCTSTR) error_message );
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

<HR><I>Copyright, 2000, <A HREF="mailto:wfc@pobox.com">Samuel R. Blackburn</A></I><BR>
$Workfile: CPingRes.cpp $<BR>
$Modtime: 1/17/00 9:10a $
</BODY>

</HTML>
#endif
