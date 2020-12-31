#include <wfc.h>
#pragma hdrstop

int _tmain( int argc, LPCTSTR argv[] )
{
   WFCTRACEINIT( TEXT( "_tmain()" ) );

   if ( argc > 1 )
   {
      WFCTRACEVAL( TEXT( "Enabling logging on " ), CString( argv[ 1 ] ) );
      CRemoteAccessService::EnableLogging( TRUE, argv[ 1 ] );
   }
   else
   {
      CRemoteAccessService::EnableLogging( TRUE, NULL );
   }

   return( EXIT_SUCCESS );
}
