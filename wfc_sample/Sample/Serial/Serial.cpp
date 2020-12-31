#include "Serial.h"
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
** $Workfile: Serial.cpp $
** $Revision: 4 $
** $Modtime: 3/08/98 3:19p $
*/

int _tmain( int argc, LPCTSTR argv[] )
{
   WFCTRACEINIT( TEXT( "main()" ) );

   CSerialFile serial_port;

   if ( serial_port.Open( TEXT( "COM2:4800,n,8,1" ) ) == FALSE )
   {
      WFCTRACE( TEXT( "Can't open serial port" ) );
      return( EXIT_SUCCESS );
   }

   CCommunicationProperties properties;

   if ( serial_port.GetProperties( properties ) == FALSE )
   {
      WFCTRACEVAL( TEXT( "Can't get properties. Reason " ), serial_port.GetErrorCode() );
   }
   else
   {
#if defined( _DEBUG )

      properties.Dump( afxDump );

#endif // _DEBUG
   }

   CString nmea_string( TEXT( "$GPGLL,4916.45,N,12311.12,W*71\r\n" ) );

   while( 1 )
   {
      serial_port.Write( nmea_string );
      _tprintf( nmea_string );
      Sleep( 2000 );
   }

   return( EXIT_SUCCESS );
}
