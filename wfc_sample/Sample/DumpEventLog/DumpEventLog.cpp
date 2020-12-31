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
** $Workfile: DumpEventLog.cpp $
** $Revision: 3 $
** $Modtime: 3/08/98 3:18p $
*/

void dump_event_log( CString& computer_name )
{
   WFCTRACEINIT( TEXT( "dump_event_log()" ) );

   CEventLog event_log;

   BYTE array[ 512 ];

   ZeroMemory( array, sizeof( array ) );

   DWORD size = sizeof( array );

   if ( event_log.Open( TEXT( "Application" ) ) == FALSE )
   {
      WFCTRACE( TEXT( "Can't open log" ) );
      return;
   }

   if ( event_log.Read( 0, array, size ) != FALSE )
   {
      WFCTRACEVAL( TEXT( "Number of bytes read is " ), size );

      DWORD index = 0;

      CString output_string;

      while( index < size )
      {
         output_string.Format( TEXT( "%04lu - %02X - %c\n" ), index, array[ index ], ( array[ index ] == 0 ? 32 : array[ index ] ));
         OutputDebugString( output_string );
         index++;
      }

      CEventLogRecord record;

      record.Copy( reinterpret_cast<EVENTLOGRECORD *>( array ) );

#if defined( _DEBUG )

      record.Dump( afxDump );

#endif // _DEBUG
   }
   else
   {
      WFCTRACE( TEXT( "Sorry" ) );
   }
}

int __cdecl _tmain( int argc, LPCTSTR argv[] )
{
   WFCTRACEINIT( TEXT( "main()" ) );
   dump_event_log( CString( TEXT( "SAMMY" ) ) );
   return( EXIT_SUCCESS );
}
