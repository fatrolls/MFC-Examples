#include <wfc.h>
#include <imagehlp.h>
#pragma hdrstop

/*
** Author: Samuel R. Blackburn
** Internet: wfc@pobox.com
*/

// include the right library in the linker stage
#pragma comment( lib, "imagehlp.lib" )

int _tmain( int number_of_command_line_arguments, LPCTSTR command_line_arguments )
{
   WFCTRACEINIT( TEXT( "_tmain()" ) );

   TCHAR undecorated_name[ 513 ];

   ZeroMemory( undecorated_name, sizeof( undecorated_name ) );

   // It is unclear if the third parameter should be the size of the buffer or
   // the number of characters undecorated_name can hold. Documentation is shoddy

   CString decorated_name( TEXT( "?DT_GetCur@@YAJXZ" ) );

   if ( number_of_command_line_arguments < 2 )
   {
      if ( UnDecorateSymbolName( decorated_name, undecorated_name, sizeof( undecorated_name ), UNDNAME_COMPLETE ) > 0 )
      {
         WFCTRACEVAL( TEXT( "Undecorated name " ), CString( undecorated_name ) );
         _tprintf( TEXT( "%s\n" ), undecorated_name );
      }
      else
      {
         WFCTRACEVAL( TEXT( "This doesn't demangle " ), decorated_name );
         _tprintf( TEXT( "Unknown\n" ) );
      }
   }
   else
   {
      int index = 1;

      while( index < number_of_command_line_arguments )
      {
         decorated_name = command_line_arguments[ index ];

         if ( UnDecorateSymbolName( decorated_name, undecorated_name, sizeof( undecorated_name ), UNDNAME_COMPLETE ) > 0 )
         {
            WFCTRACEVAL( TEXT( "Undecorated name " ), CString( undecorated_name ) );
            _tprintf( TEXT( "%s\n" ), undecorated_name );
         }
         else
         {
            WFCTRACEVAL( TEXT( "This doesn't demangle " ), decorated_name );
            _tprintf( TEXT( "Unknown\n" ) );
         }

         index++;
      }
   }

   return( EXIT_SUCCESS );
}