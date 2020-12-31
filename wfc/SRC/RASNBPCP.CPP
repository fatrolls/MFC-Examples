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
** $Workfile: RASNBPCP.CPP $
** $Revision: 10 $
** $Modtime: 1/05/00 3:40a $
*/

#if defined( _DEBUG )
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

IMPLEMENT_SERIAL( CRemoteAccessServicePortStatistics, CObject, 1 )

#if defined( _DEBUG )
#define new DEBUG_NEW
#endif

CRemoteAccessServicePortStatistics::CRemoteAccessServicePortStatistics()
{
   WFCLTRACEINIT( "CRemoteAccessServicePortStatistics::CRemoteAccessServicePortStatistics()" );
   Empty();
}

CRemoteAccessServicePortStatistics::CRemoteAccessServicePortStatistics( const CRemoteAccessServicePortStatistics& source )
{
   WFCLTRACEINIT( "CRemoteAccessServicePortStatistics( const CRemoteAccessServicePortStatistics& )" );
   Empty();
   Copy( source );
}

CRemoteAccessServicePortStatistics::CRemoteAccessServicePortStatistics( const RAS_PPP_NBFCP_RESULT * source )
{
   WFCLTRACEINIT( "CRemoteAccessServicePort( const RAS_PORT_STATISTICS * )" );
   Empty();
   Copy( source );
}

CRemoteAccessServicePortStatistics::~CRemoteAccessServicePortStatistics()
{
   WFCLTRACEINIT( "CRemoteAccessServicePortStatistics::~CRemoteAccessServicePortStatistics()" );
   Empty();
}

void CRemoteAccessServicePort::Copy( const RAS_PORT_STATISTICS * source )
{
   WFCLTRACEINIT( "CRemoteAccessServicePortStatistics::Copy( const RAS_PORT_STATISTICS * )" );
   ASSERT( source != NULL );

   // Choose to live

   if ( source == NULL )
   {
      Empty();
      return;
   }

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

void CRemoteAccessServicePortStatistics::Copy( const CRemoteAccessServicePortStatistics& source )
{
   WFCLTRACEINIT( "CRemoteAccessServicePortStatistics::Copy( const CRemoteAccessServicePortStatistics& )" );
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
   dump_context << "a CRemoteAccessServicePortStatistics at " << (VOID *) this << "\n{\n";
   dump_context << "   NumberOfBytesTransmitted is             " << NumberOfBytesTransmitted             << "\n";
   dump_context << "   NumberOfBytesReceived is                " << NumberOfBytesReceived                << "\n";
   dump_context << "   NumberOfFramesTransmitted is            " << NumberOfFramesTransmitted            << "\n";
   dump_context << "   NumberOfFramesReceived is               " << NumberOfFramesReceived               << "\n";
   dump_context << "   NumberOfCRCErrors is                    " << NumberOfCRCErrors                    << "\n";
   dump_context << "   NumberOfTimeoutErrors is                " << NumberOfTimeoutErrors                << "\n";
   dump_context << "   NumberOfAlignmentErrors is              " << NumberOfAlignmentErrors              << "\n";
   dump_context << "   NumberOfHardwareOverrunErrors is        " << NumberOfHardwareOverrunErrors        << "\n";
   dump_context << "   NumberOfFramingErrors is                " << NumberOfFramingErrors                << "\n";
   dump_context << "   NumberOfBufferOverrunErrors is          " << NumberOfBufferOverrunErrors          << "\n";
   dump_context << "   NumberOfBytesTransmittedUncompressed is " << NumberOfBytesTransmittedUncompressed << "\n";
   dump_context << "   NumberOfBytesReceivedUncompressed is    " << NumberOfBytesReceivedUncompressed    << "\n";
   dump_context << "   NumberOfBytesTransmittedCompressed is   " << NumberOfBytesTransmittedCompressed   << "\n";
   dump_context << "   NumberOfBytesReceivedCompressed is      " << NumberOfBytesReceivedCompressed      << "\n";
   dump_context << "}\n";
}

#endif

void CRemoteAccessServicePortStatistics::Empty( void )
{
   WFCLTRACEINIT( "CRemoteAccessServicePortStatistics::Empty()" );
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

void CRemoteAccessServicePortStatistics::Serialize( CArchive& archive )
{
   WFCLTRACEINIT( "CRemoteAccessServicePortStatistics::Serialize()" );

   CObject::Serialize( archive );

   if ( archive.IsStoring() )
   {
      WFCTRACE( "Storing" );
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
      WFCTRACE( "Restoring" );
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

#if 0
<WFC_DOCUMENTATION>
<HTML>
<HEAD>
<TITLE>WFC - CRemoteAccessServicePortStatistics</TITLE>
<META name="keywords" content="WFC, MFC extension library, freeware class library, Win32, RAS, Remote Access Service, Dialup networking">
</HEAD>
<BODY>
<H1>CRemoteAccessServicePortStatistics : CObject</H1>
$Revision: 10 $
<HR><H2>Description</H2>
This class is based on the RAS_PORT_STATISTICS structure.
<H2>Data Members</H2>
<B>None.</B>
<H2>Methods</H2>
<DL COMPACT>
<DT><DFN><B>Copy</B></DFN><DD>Copies another CRemoteAccessServicePortStatistics or a RAS_PORT_STATISTICS structure.
<DT><DFN><B>Empty</B></DFN><DD>Clears all data members.
<DT><DFN><B>Serialize</B></DFN><DD>After all, we are a CObject...
</DL>
<H2>Example</H2><PRE><CODE>Sorry.</CODE></PRE>
<I>Copyright, 2000, Samuel R. Blackburn</I><BR>
$Workfile: RASNBPCP.CPP $<BR>
$Modtime: 1/05/00 3:40a $
</BODY>
</HTML>
</WFC_DOCUMENTATION>
#endif
