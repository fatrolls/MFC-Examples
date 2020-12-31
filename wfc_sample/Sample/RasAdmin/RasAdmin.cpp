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
** Copyright, 1996, Samuel R. Blackburn
**
** $Workfile: registry.cpp $
** $Revision: 12 $
** $Modtime: 11/25/96 4:41a $
*/

#if defined( _DEBUG )
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif // _DEBUG

void dump_ports( CRemoteAccessServiceAdministration& ras )
{
   WFCTRACEINIT( TEXT( "dump_ports()" ) );

   if ( ras.EnumeratePorts() == FALSE )
   {
      CString error_string;
      ras.GetErrorString( ras.GetErrorCode(), error_string );

      WFCTRACEVAL( TEXT( "Error calling EnumeratePorts, " ), error_string );
      _tprintf( TEXT( "Error! %s\n" ), (LPCTSTR) error_string );
      return;
   }

   CRemoteAccessServicePort port;

   while( ras.GetNext( port ) != FALSE )
   {
#if defined( _DEBUG )
      port.Dump( afxDump );
#else
      _tprintf( TEXT( "Name               - %s\n"  ), (LPCTSTR) port.Name         );
      _tprintf( TEXT( "Device Type        - %s\n"  ), (LPCTSTR) port.DeviceType   );
      _tprintf( TEXT( "Device Name        - %s\n"  ), (LPCTSTR) port.DeviceName   );
      _tprintf( TEXT( "Media Name         - %s\n"  ), (LPCTSTR) port.MediaName    );
      _tprintf( TEXT( "Media ID           - %lu\n" ), port.MediaID                );
      _tprintf( TEXT( "User Name          - %s\n"  ), (LPCTSTR) port.UserName     );
      _tprintf( TEXT( "Computer Name      - %s\n"  ), (LPCTSTR) port.ComputerName );
      _tprintf( TEXT( "Session Start Time - %s\n"  ), (LPCTSTR) port.SessionStartTime.Format( WFC_STANDARD_TIME_FORMAT ) );
      _tprintf( TEXT( "Logon Domain Name  - %s\n"  ), (LPCTSTR) port.LogonDomainName );
      _tprintf( TEXT( "Advanced Server?   - %s\n"  ), ( port.IsAdvancedServer != FALSE ) ? TEXT( "Yes" ) : TEXT( "No" ) );
#endif // _DEBUG
   }
}

void dump_ras( void )
{
   WFCTRACEINIT( TEXT( "dump_ras()" ) );
   CRemoteAccessServiceAdministration ras_admin;
   dump_ports( ras_admin );
}

int _tmain( int argc, LPCTSTR argv[] )
{
   WFCTRACEINIT( TEXT( "main()" ) );

   CRemoteAccessServicePortStatistics statistics_1;
   CRemoteAccessServicePortStatistics statistics_2;

   statistics_1.NumberOfBytesTransmitted             = 1;
   statistics_1.NumberOfBytesReceived                = 1;
   statistics_1.NumberOfFramesTransmitted            = 1;
   statistics_1.NumberOfFramesReceived               = 1;
   statistics_1.NumberOfCRCErrors                    = 1;
   statistics_1.NumberOfTimeoutErrors                = 1;
   statistics_1.NumberOfAlignmentErrors              = 1;
   statistics_1.NumberOfHardwareOverrunErrors        = 1;
   statistics_1.NumberOfFramingErrors                = 1;
   statistics_1.NumberOfBufferOverrunErrors          = 1;
   statistics_1.NumberOfBytesTransmittedUncompressed = 1;
   statistics_1.NumberOfBytesReceivedUncompressed    = 1;
   statistics_1.NumberOfBytesTransmittedCompressed   = 1;
   statistics_1.NumberOfBytesReceivedCompressed      = 1;

   statistics_2.NumberOfBytesTransmitted             = 2;
   statistics_2.NumberOfBytesReceived                = 2;
   statistics_2.NumberOfFramesTransmitted            = 2;
   statistics_2.NumberOfFramesReceived               = 2;
   statistics_2.NumberOfCRCErrors                    = 2;
   statistics_2.NumberOfTimeoutErrors                = 2;
   statistics_2.NumberOfAlignmentErrors              = 2;
   statistics_2.NumberOfHardwareOverrunErrors        = 2;
   statistics_2.NumberOfFramingErrors                = 2;
   statistics_2.NumberOfBufferOverrunErrors          = 2;
   statistics_2.NumberOfBytesTransmittedUncompressed = 2;
   statistics_2.NumberOfBytesReceivedUncompressed    = 2;
   statistics_2.NumberOfBytesTransmittedCompressed   = 2;
   statistics_2.NumberOfBytesReceivedCompressed      = 2;

   if ( statistics_1 == statistics_2 )
   {
      _tprintf( TEXT( "OOPS!\n" ) );
   }

   if ( statistics_1 < statistics_2 )
   {
      _tprintf( TEXT( "less than works\n" ) );
   }

   if ( statistics_2 > statistics_1 )
   {
      _tprintf( TEXT( "greater than works\n" ) );
   }

   dump_ras();
   return( EXIT_SUCCESS );
}
