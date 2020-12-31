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
** $Workfile: RASPSTAT.CPP $
** $Revision: 13 $
** $Modtime: 1/05/00 3:43a $
** $Reuse Tracing Code: 1 $
*/

#if defined( _DEBUG ) && ! defined( WFC_STL )
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

#if ! defined(  WFC_NO_SERIALIZATION )
IMPLEMENT_SERIAL( CRemoteAccessServicePortStatistics, CObject, 1 )
#endif // WFC_NO_SERIALIZATION

#if defined( _DEBUG ) && ! defined( WFC_STL )
#define new DEBUG_NEW
#endif // _DEBUG

CRemoteAccessServicePortStatistics::CRemoteAccessServicePortStatistics()
{
   WFCLTRACEINIT( TEXT( "CRemoteAccessServicePortStatistics::CRemoteAccessServicePortStatistics()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   Empty();
}

CRemoteAccessServicePortStatistics::CRemoteAccessServicePortStatistics( const CRemoteAccessServicePortStatistics& source )
{
   WFCLTRACEINIT( TEXT( "CRemoteAccessServicePortStatistics( CRemoteAccessServicePortStatistics& )" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   Empty();
   Copy( source );
}

CRemoteAccessServicePortStatistics::CRemoteAccessServicePortStatistics( const RAS_PORT_STATISTICS * source )
{
   WFCLTRACEINIT( TEXT( "CRemoteAccessServicePort( RAS_PORT_STATISTICS * )" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   Empty();
   Copy( source );
}

CRemoteAccessServicePortStatistics::~CRemoteAccessServicePortStatistics()
{
   WFCLTRACEINIT( TEXT( "CRemoteAccessServicePortStatistics::~CRemoteAccessServicePortStatistics()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   Empty();
}

int CRemoteAccessServicePortStatistics::Compare( const CRemoteAccessServicePortStatistics& right_port ) const
{
   WFCLTRACEINIT( TEXT( "CRemoteAccessServicePort::Compare()" ) );

   if ( NumberOfBytesTransmitted < right_port.NumberOfBytesTransmitted )
   {
      return( -1 );
   }
   else if ( NumberOfBytesTransmitted > right_port.NumberOfBytesTransmitted )
   {
      return( 1 );
   }

   if ( NumberOfBytesReceived < right_port.NumberOfBytesReceived )
   {
      return( -1 );
   }
   else if ( NumberOfBytesReceived > right_port.NumberOfBytesReceived )
   {
      return( 1 );
   }

   if ( NumberOfFramesTransmitted < right_port.NumberOfFramesTransmitted )
   {
      return( -1 );
   }
   else if ( NumberOfFramesTransmitted > right_port.NumberOfFramesTransmitted )
   {
      return( 1 );
   }

   if ( NumberOfFramesReceived < right_port.NumberOfFramesReceived )
   {
      return( -1 );
   }
   else if ( NumberOfFramesReceived > right_port.NumberOfFramesReceived )
   {
      return( 1 );
   }

   if ( NumberOfCRCErrors < right_port.NumberOfCRCErrors )
   {
      return( -1 );
   }
   else if ( NumberOfCRCErrors > right_port.NumberOfCRCErrors )
   {
      return( 1 );
   }

   if ( NumberOfTimeoutErrors < right_port.NumberOfTimeoutErrors )
   {
      return( -1 );
   }
   else if ( NumberOfTimeoutErrors > right_port.NumberOfTimeoutErrors )
   {
      return( 1 );
   }

   if ( NumberOfAlignmentErrors < right_port.NumberOfAlignmentErrors )
   {
      return( -1 );
   }
   else if ( NumberOfAlignmentErrors > right_port.NumberOfAlignmentErrors )
   {
      return( 1 );
   }

   if ( NumberOfHardwareOverrunErrors < right_port.NumberOfHardwareOverrunErrors )
   {
      return( -1 );
   }
   else if ( NumberOfHardwareOverrunErrors > right_port.NumberOfHardwareOverrunErrors )
   {
      return( 1 );
   }

   if ( NumberOfFramingErrors < right_port.NumberOfFramingErrors )
   {
      return( -1 );
   }
   else if ( NumberOfFramingErrors > right_port.NumberOfFramingErrors )
   {
      return( 1 );
   }

   if ( NumberOfBufferOverrunErrors < right_port.NumberOfBufferOverrunErrors )
   {
      return( -1 );
   }
   else if ( NumberOfBufferOverrunErrors > right_port.NumberOfBufferOverrunErrors )
   {
      return( 1 );
   }

   if ( NumberOfBytesTransmittedUncompressed < right_port.NumberOfBytesTransmittedUncompressed )
   {
      return( -1 );
   }
   else if ( NumberOfBytesTransmittedUncompressed > right_port.NumberOfBytesTransmittedUncompressed )
   {
      return( 1 );
   }

   if ( NumberOfBytesReceivedUncompressed < right_port.NumberOfBytesReceivedUncompressed )
   {
      return( -1 );
   }
   else if ( NumberOfBytesReceivedUncompressed > right_port.NumberOfBytesReceivedUncompressed )
   {
      return( 1 );
   }

   if ( NumberOfBytesTransmittedCompressed < right_port.NumberOfBytesTransmittedCompressed )
   {
      return( -1 );
   }
   else if ( NumberOfBytesTransmittedCompressed > right_port.NumberOfBytesTransmittedCompressed )
   {
      return( 1 );
   }

   if ( NumberOfBytesReceivedCompressed < right_port.NumberOfBytesReceivedCompressed )
   {
      return( -1 );
   }
   else if ( NumberOfBytesReceivedCompressed > right_port.NumberOfBytesReceivedCompressed )
   {
      return( 1 );
   }

   return( 0 );
}

void CRemoteAccessServicePortStatistics::Copy( const RAS_PORT_STATISTICS * source )
{
   WFCLTRACEINIT( TEXT( "CRemoteAccessServicePortStatistics::Copy( RAS_PORT_STATISTICS * )" ) );
   ASSERT( source != NULL );

   // Choose to live

   if ( source == NULL )
   {
      Empty();
      return;
   }

   // We were passed a pointer, don't trust it

   try
   {
      NumberOfBytesTransmitted             = source->dwBytesXmited;
      NumberOfBytesReceived                = source->dwBytesRcved;
      NumberOfFramesTransmitted            = source->dwFramesXmited;
      NumberOfFramesReceived               = source->dwFramesRcved;
      NumberOfCRCErrors                    = source->dwCrcErr;
      NumberOfTimeoutErrors                = source->dwTimeoutErr;
      NumberOfAlignmentErrors              = source->dwAlignmentErr;
      NumberOfHardwareOverrunErrors        = source->dwHardwareOverrunErr;
      NumberOfFramingErrors                = source->dwFramingErr;
      NumberOfBufferOverrunErrors          = source->dwBufferOverrunErr;
      NumberOfBytesTransmittedUncompressed = source->dwBytesXmitedUncompressed;
      NumberOfBytesReceivedUncompressed    = source->dwBytesRcvedUncompressed;
      NumberOfBytesTransmittedCompressed   = source->dwBytesXmitedCompressed;
      NumberOfBytesReceivedCompressed      = source->dwBytesRcvedCompressed;
   }
   catch( ... )
   {
      Empty();
      return;
   }
}

void CRemoteAccessServicePortStatistics::Copy( const CRemoteAccessServicePortStatistics& source )
{
   WFCLTRACEINIT( TEXT( "CRemoteAccessServicePortStatistics::Copy( CRemoteAccessServicePortStatistics& )" ) );

   // Copying ourself is a silly thing to do

   if ( &source == this )
   {
      WFCTRACE( TEXT( "Attempt to make a copy of ourself (such silliness)." ) );
      return;
   }

   NumberOfBytesTransmitted             = source.NumberOfBytesTransmitted;
   NumberOfBytesReceived                = source.NumberOfBytesReceived;
   NumberOfFramesTransmitted            = source.NumberOfFramesTransmitted;
   NumberOfFramesReceived               = source.NumberOfFramesReceived;
   NumberOfCRCErrors                    = source.NumberOfCRCErrors;
   NumberOfTimeoutErrors                = source.NumberOfTimeoutErrors;
   NumberOfAlignmentErrors              = source.NumberOfAlignmentErrors;
   NumberOfHardwareOverrunErrors        = source.NumberOfHardwareOverrunErrors;
   NumberOfFramingErrors                = source.NumberOfFramingErrors;
   NumberOfBufferOverrunErrors          = source.NumberOfBufferOverrunErrors;
   NumberOfBytesTransmittedUncompressed = source.NumberOfBytesTransmittedUncompressed;
   NumberOfBytesReceivedUncompressed    = source.NumberOfBytesReceivedUncompressed;
   NumberOfBytesTransmittedCompressed   = source.NumberOfBytesTransmittedCompressed;
   NumberOfBytesReceivedCompressed      = source.NumberOfBytesReceivedCompressed;
}

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

void CRemoteAccessServicePortStatistics::Dump( CDumpContext& dump_context ) const
{
   dump_context << TEXT( "a CRemoteAccessServicePortStatistics at " ) << (VOID *) this << TEXT( "\n{\n" );
   dump_context << TEXT( "   NumberOfBytesTransmitted is             " ) << NumberOfBytesTransmitted             << TEXT( "\n" );
   dump_context << TEXT( "   NumberOfBytesReceived is                " ) << NumberOfBytesReceived                << TEXT( "\n" );
   dump_context << TEXT( "   NumberOfFramesTransmitted is            " ) << NumberOfFramesTransmitted            << TEXT( "\n" );
   dump_context << TEXT( "   NumberOfFramesReceived is               " ) << NumberOfFramesReceived               << TEXT( "\n" );
   dump_context << TEXT( "   NumberOfCRCErrors is                    " ) << NumberOfCRCErrors                    << TEXT( "\n" );
   dump_context << TEXT( "   NumberOfTimeoutErrors is                " ) << NumberOfTimeoutErrors                << TEXT( "\n" );
   dump_context << TEXT( "   NumberOfAlignmentErrors is              " ) << NumberOfAlignmentErrors              << TEXT( "\n" );
   dump_context << TEXT( "   NumberOfHardwareOverrunErrors is        " ) << NumberOfHardwareOverrunErrors        << TEXT( "\n" );
   dump_context << TEXT( "   NumberOfFramingErrors is                " ) << NumberOfFramingErrors                << TEXT( "\n" );
   dump_context << TEXT( "   NumberOfBufferOverrunErrors is          " ) << NumberOfBufferOverrunErrors          << TEXT( "\n" );
   dump_context << TEXT( "   NumberOfBytesTransmittedUncompressed is " ) << NumberOfBytesTransmittedUncompressed << TEXT( "\n" );
   dump_context << TEXT( "   NumberOfBytesReceivedUncompressed is    " ) << NumberOfBytesReceivedUncompressed    << TEXT( "\n" );
   dump_context << TEXT( "   NumberOfBytesTransmittedCompressed is   " ) << NumberOfBytesTransmittedCompressed   << TEXT( "\n" );
   dump_context << TEXT( "   NumberOfBytesReceivedCompressed is      " ) << NumberOfBytesReceivedCompressed      << TEXT( "\n" );
   dump_context << TEXT( "}\n" );
}

#endif // _DEBUG

void CRemoteAccessServicePortStatistics::Empty( void )
{
   WFCLTRACEINIT( TEXT( "CRemoteAccessServicePortStatistics::Empty()" ) );
   NumberOfBytesTransmitted             = 0;
   NumberOfBytesReceived                = 0;
   NumberOfFramesTransmitted            = 0;
   NumberOfFramesReceived               = 0;
   NumberOfCRCErrors                    = 0;
   NumberOfTimeoutErrors                = 0;
   NumberOfAlignmentErrors              = 0;
   NumberOfHardwareOverrunErrors        = 0;
   NumberOfFramingErrors                = 0;
   NumberOfBufferOverrunErrors          = 0;
   NumberOfBytesTransmittedUncompressed = 0;
   NumberOfBytesReceivedUncompressed    = 0;
   NumberOfBytesTransmittedCompressed   = 0;
   NumberOfBytesReceivedCompressed      = 0;
}

#if ! defined(  WFC_NO_SERIALIZATION )

void CRemoteAccessServicePortStatistics::Serialize( CArchive& archive )
{
   WFCLTRACEINIT( TEXT( "CRemoteAccessServicePortStatistics::Serialize()" ) );

   CObject::Serialize( archive );

   if ( archive.IsStoring() )
   {
      WFCTRACE( TEXT( "Storing" ) );
      archive << NumberOfBytesTransmitted;
      archive << NumberOfBytesReceived;
      archive << NumberOfFramesTransmitted;
      archive << NumberOfFramesReceived;
      archive << NumberOfCRCErrors;
      archive << NumberOfTimeoutErrors;
      archive << NumberOfAlignmentErrors;
      archive << NumberOfHardwareOverrunErrors;
      archive << NumberOfFramingErrors;
      archive << NumberOfBufferOverrunErrors;
      archive << NumberOfBytesTransmittedUncompressed;
      archive << NumberOfBytesReceivedUncompressed;
      archive << NumberOfBytesTransmittedCompressed;
      archive << NumberOfBytesReceivedCompressed;
   }
   else
   {
      WFCTRACE( TEXT( "Restoring" ) );
      archive >> NumberOfBytesTransmitted;
      archive >> NumberOfBytesReceived;
      archive >> NumberOfFramesTransmitted;
      archive >> NumberOfFramesReceived;
      archive >> NumberOfCRCErrors;
      archive >> NumberOfTimeoutErrors;
      archive >> NumberOfAlignmentErrors;
      archive >> NumberOfHardwareOverrunErrors;
      archive >> NumberOfFramingErrors;
      archive >> NumberOfBufferOverrunErrors;
      archive >> NumberOfBytesTransmittedUncompressed;
      archive >> NumberOfBytesReceivedUncompressed;
      archive >> NumberOfBytesTransmittedCompressed;
      archive >> NumberOfBytesReceivedCompressed;
   }
}

#endif // WFC_NO_SERIALIZATION

CRemoteAccessServicePortStatistics& CRemoteAccessServicePortStatistics::operator = ( const CRemoteAccessServicePortStatistics& source )
{
   WFCLTRACEINIT( TEXT( "CRemoteAccessServicePortStatistics::operator=()" ) );
   Copy( source );
   return( *this );
}

BOOL CRemoteAccessServicePortStatistics::operator==( const CRemoteAccessServicePortStatistics& right_side ) const
{
   WFCLTRACEINIT( TEXT( "CRemoteAccessServicePortStatistics::operator==()" ) );

   if ( Compare( right_side ) == 0 )
   {
      return( TRUE );
   }

   return( FALSE );
}

BOOL CRemoteAccessServicePortStatistics::operator<( const CRemoteAccessServicePortStatistics& right_side ) const
{
   WFCLTRACEINIT( TEXT( "CRemoteAccessServicePortStatistics::operator<()" ) );

   if ( Compare( right_side ) == (-1) )
   {
      return( TRUE );
   }
   
   return( FALSE );
}

BOOL CRemoteAccessServicePortStatistics::operator>( const CRemoteAccessServicePortStatistics& right_side ) const
{
   WFCLTRACEINIT( TEXT( "CRemoteAccessServicePortStatistics::operator>()" ) );

   if ( Compare( right_side ) == 1 )
   {
      return( TRUE );
   }

   return( FALSE );
}

BOOL CRemoteAccessServicePortStatistics::operator<=( const CRemoteAccessServicePortStatistics& right_side ) const
{
   WFCLTRACEINIT( TEXT( "CRemoteAccessServicePortStatistics::operator<=()" ) );

   if ( Compare( right_side ) < 1 )
   {
      return( TRUE );
   }

   return( FALSE );
}

BOOL CRemoteAccessServicePortStatistics::operator>=( const CRemoteAccessServicePortStatistics& right_side ) const
{
   WFCLTRACEINIT( TEXT( "CRemoteAccessServicePortStatistics::operator>=()" ) );

   if ( Compare( right_side ) > (-1) )
   {
      return( TRUE );
   }

   return( FALSE );
}

// End of source

#if 0
<HTML>

<HEAD>
<TITLE>WFC - CRemoteAccessServicePortStatistics</TITLE>
<META name="keywords" content="WFC, MFC extension library, freeware class library, Win32, RAS, Remote Access Service, Dialup networking">
</HEAD>

<BODY>

<H1>CRemoteAccessServicePortStatistics : CObject</H1>
$Revision: 13 $
<HR>

<H2>Description</H2>
This class is based on the RAS_PORT_STATISTICS structure.

<H2>Data Members</H2>
NumberOfBytesTransmitted<BR>
NumberOfBytesReceived<BR>
NumberOfFramesTransmitted<BR>
NumberOfFramesReceived<BR>
NumberOfCRCErrors<BR>
NumberOfTimeoutErrors<BR>
NumberOfAlignmentErrors<BR>
NumberOfHardwareOverrunErrors<BR>
NumberOfFramingErrors<BR>
NumberOfBufferOverrunErrors<BR>
NumberOfBytesTransmittedUncompressed<BR>
NumberOfBytesReceivedUncompressed<BR>
NumberOfBytesTransmittedCompressed<BR>
NumberOfBytesReceivedCompressed<BR>

<H2>Methods</H2>

<DL COMPACT>

<DT><B>Compare</B><DD>Same as CString::Compare().
<DT><B>Copy</B><DD>Copies another CRemoteAccessServicePortStatistics or a RAS_PORT_STATISTICS structure.
<DT><B>Empty</B><DD>Clears all data members.
<DT><B>Serialize</B><DD>After all, we are a CObject...

</DL>

<H2>Operators</H2>

<B>=<BR>==<BR>&lt;<BR>&gt;<BR>&lt;=<BR>&gt;=</B>

<H2>Example</H2>

<PRE><CODE>Sorry.</CODE></PRE>

<HR><I>Copyright, 2000, <A HREF="mailto:wfc@pobox.com">Samuel R. Blackburn</A></I><BR>
$Workfile: RASPSTAT.CPP $<BR>
$Modtime: 1/05/00 3:43a $
</BODY>

</HTML>
#endif
