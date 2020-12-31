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
** $Workfile: service.cpp $
** $Revision: 7 $
** $Modtime: 5/02/00 6:20p $
*/

void list_services( LPCTSTR );
void print_error( LPCTSTR, DWORD );
void usage( void );

int _tmain( int number_of_command_line_arguments, LPCTSTR command_line_arguments[] )
{
   if ( number_of_command_line_arguments < 2 )
   {
      list_services( NULL );
   }
   else
   {
      if ( _tcsicmp( command_line_arguments[ 1 ], TEXT( "/?" ) ) == 0 )
      {
         usage();
      }
      else
      {
         list_services( command_line_arguments[ 1 ] );
      }
   }

   return( EXIT_SUCCESS );
}

void list_services( LPCTSTR machine_name )
{
   CServiceControlManager manager;

   if ( manager.Open( SC_MANAGER_ENUMERATE_SERVICE, NULL, machine_name ) == FALSE )
   {
      print_error( TEXT( "Can't open service control manager" ), manager.GetErrorCode() );
   }

   if ( machine_name == NULL )
   {
      _tprintf( TEXT( "Services Running:\n" ) );
   }
   else
   {
      _tprintf( TEXT( "Services Running on %s:\n" ), machine_name );
   }

   if  ( manager.EnumerateStatus() != FALSE )
   {
      CStringArray services;
      CStringArray display_names;
      CServiceNameAndStatus status;

      int longest_service = 0;

      while( manager.GetNext( status ) != FALSE )
      {
         if ( status.ServiceStatus.dwCurrentState == SERVICE_RUNNING )
         {
            services.Add( status.lpServiceName );
            display_names.Add( status.lpDisplayName );

            if ( _tcslen( status.lpServiceName ) > (size_t) longest_service )
            {
               longest_service = _tcslen( status.lpServiceName );
            }
         }
      }

      /*
      ** Now sort them for easy reading
      */

      BOOL sorted = FALSE;
      int here    = 0;
      int last_element = services.GetUpperBound();

      while( sorted == FALSE )
      {
         sorted = TRUE;
         here   = 0;

         while( here < last_element )
         {
            if ( services[ here ].CompareNoCase( services[ here + 1 ] ) > 0 )
            {
               CString temp_string;

               temp_string = services[ here ];
               services[ here ] = (LPCTSTR) services[ here + 1 ];
               services[ here + 1 ] = (LPCTSTR) temp_string;

               temp_string = display_names[ here ];
               display_names[ here ] = (LPCTSTR) display_names[ here + 1 ];
               display_names[ here + 1 ] = (LPCTSTR) temp_string;

               sorted = FALSE;
            }

            here++;
         }
      }

      here = 0;

      while( here <= last_element )
      {
         _tprintf( TEXT( "%-*s \"%s\"\n" ), longest_service, (LPCTSTR) services[ here ], (LPCTSTR) display_names[ here ] );
         here++;
      }
   }
   else
   {
      print_error( TEXT( "Can't enumerate status\n" ), manager.GetErrorCode() );
   }
}

void usage( void )
{
   _tprintf( TEXT( "Show active services on a machine. Samuel R. Blackburn\n\n" ) );
   _tprintf( TEXT( "Service [[/?][machine_name]]\n\n" ) );
   _tprintf( TEXT( "Examples:\n" ) );
   _tprintf( TEXT( "\"service /?\"         displays this screen\n" ) );
   _tprintf( TEXT( "\"service\"            shows active services on this your machine\n" ) );
   _tprintf( TEXT( "\"service Enterprise\" shows active services on the machine named Enterprise\n" ) ); 
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
