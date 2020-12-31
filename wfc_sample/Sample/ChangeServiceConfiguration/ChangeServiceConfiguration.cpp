#include "wfc.h"
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
** $Workfile: ChangeServiceConfiguration.cpp $
** $Revision: 3 $
** $Modtime: 4/02/98 7:30a $
*/

void print_error( LPCTSTR, DWORD );
void usage( void );

#if defined( UNICODE )
extern "C"
#endif // UNICODE

int _tmain( int number_of_command_line_arguments, LPCTSTR command_line_arguments[] )
{
   WFCTRACEINIT( TEXT( "_tmain()" ) );

   if ( number_of_command_line_arguments < 3 )
   {
      usage();
   }

   CServiceControlManager manager;

   if ( manager.Open() == FALSE )
   {
      print_error( TEXT( "Can't open service control manager" ), manager.GetErrorCode() );
      return( EXIT_SUCCESS );
   }

   if ( _tcsicmp( command_line_arguments[ 2 ], TEXT( "Auto" ) ) == 0 )
   {
      if ( manager.SetConfiguration( command_line_arguments[ 1 ], SERVICE_AUTO_START ) == FALSE )
      {
         print_error( TEXT( "Auto" ), manager.GetErrorCode() );
      }
      else
      {
         _tprintf( TEXT( "%s set to auto\n" ), command_line_arguments[ 1 ] );
      }
   }
   else if ( _tcsicmp( command_line_arguments[ 2 ], TEXT( "Manual" ) ) == 0 )
   {
      if ( manager.SetConfiguration( command_line_arguments[ 1 ], SERVICE_DEMAND_START ) == FALSE )
      {
         print_error( TEXT( "Manual" ), manager.GetErrorCode() );
      }
      else
      {
         _tprintf( TEXT( "%s set to manual\n" ), command_line_arguments[ 1 ] );
      }
   }
   else
   {
      usage();
   }

   return( EXIT_SUCCESS );
}

void print_error( LPCTSTR message, DWORD error_code )
{
   LPVOID message_buffer = (LPVOID) NULL;

   FormatMessage( FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
                  NULL,
                  error_code,
                  MAKELANGID( LANG_ENGLISH, SUBLANG_ENGLISH_US ),
        (LPTSTR) &message_buffer,
                  0,
                  NULL );

   if ( message_buffer != NULL )
   {
      _tprintf( TEXT( "%s\nError is %s\n" ), message, (LPCTSTR) message_buffer );

      LocalFree( message_buffer );
   }
   else
   {
      _tprintf( TEXT( "%s\nError Code is %d\n" ), message, error_code );
   }
}

void usage( void )
{
   _tprintf( TEXT( "ChangeServiceConfiguration name_of_service Auto|Manual\n" ) );
}
