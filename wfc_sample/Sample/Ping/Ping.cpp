#include <wfc.h>
#pragma hdrstop

/*
** Author: Samuel R. Blackburn
** Internet: sblackbu@csc.com
**
** You can use it any way you like as long as you don't try to sell it.
**
** Any attempt to sell WFC in source code form must have the permission
** of the original author. You can produce commercial executables with
** WFC but you can't sell WFC.
**
** Copyright, 1996, Samuel R. Blackburn
**
** $Workfile: Ping.cpp $
** $Revision: 4 $
** $Modtime: 6/06/98 6:25a $
*/

int _tmain( int number_of_command_line_arguments, LPCTSTR command_line_arguments[] )
{
   WFCTRACELEVELON( 31 );
   WFCTRACEINIT( TEXT( "_tmain()" ) );

   CPing ping;

   DWORD return_value = 0;

   CPingResults results;

   return_value = ping.Ping( TEXT( "24.3.46.1" ), &results );

   if ( return_value == 0 )
   {
      DWORD error_code = ping.GetErrorCode();

      CString error_message;

      ping.ConvertErrorToString( error_code, error_message );

      WFCTRACEVAL( TEXT( "Ping error " ), error_message );
      _tprintf( TEXT( "Ping Error: %s\n" ), (LPCTSTR) error_message );
   }
   else
   {
      WFCTRACEVAL( TEXT( "Ping OK to " ), results.Address );
      WFCTRACEVAL( TEXT( "Time in ms " ), results.RoundTripTimeInMilliseconds );

      _tprintf( TEXT( "Ping: %s Round Trip %lums TTL: %d\n" ),
                (LPCTSTR) results.Address,
                results.RoundTripTimeInMilliseconds,
                (int) results.TimeToLive );
   }

   return( EXIT_SUCCESS );
}
