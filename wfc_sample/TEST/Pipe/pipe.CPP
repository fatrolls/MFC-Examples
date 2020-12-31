#include "pipe.h"
#pragma hdrstop

/*
** Author: Samuel R. Blackburn
** Internet: wfc@pobox.com
**
** You can use it any way you like.
*/

int main()
{
   // Create Server Thread

   if ( create_server_pipe( TEXT( "IPC$" ) ) != FALSE )
   {
      TRACE( TEXT( "Pipe Created\n" ) );
      _tprintf( TEXT( "Server Pipe Created\n" ) );
   }

   // Create client thread

   return( EXIT_SUCCESS );
}
