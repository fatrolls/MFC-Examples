#include "pipe.h"
#pragma hdrstop

BOOL create_server_pipe( LPCTSTR pipe_name )
{
   CNamedPipe server_pipe;

   if ( server_pipe.Open( pipe_name ) == FALSE )
   {
      CString error_string;

      DWORD error_code = server_pipe.GetError();

      Convert_NERR_Code_to_String( error_code, error_string );

      TRACE( TEXT( "Can't open \"%s\" because %s (%ld)\n" ), pipe_name, (LPCTSTR) error_string, error_code );

      return( FALSE );
   }

   return( TRUE );
}

