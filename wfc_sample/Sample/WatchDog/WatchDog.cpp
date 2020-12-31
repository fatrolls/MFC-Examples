#include <wfc.h>
#include "messages.h"
#pragma hdrstop

/*
** Author: Samuel R. Blackburn
** Internet: wfc@pobox.com
**
** This is freeware as always...
**
** You can use it any way you like.
**
** Sample program that watches other services and restarts them if they fail.
**
** Registration Database Entries:
**
** MachineName, REG_SZ, name of machine to monitor, default is local machine
** NumberOfSecondsBetweenChecks, REG_DWORD, how long to sleep between heartbeats
** Services, REG_MULTI_SZ, names of services to watch for
**
** Demonstrates the following classes in action:
**   CRegistry
**   CService 
**   CServiceControlManager
**   CServiceNameAndStatus
*/

#if defined( _DEBUG )
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif // _DEBUG

DWORD WINAPI worker_thread( LPVOID unused_parameter );
VOID set_default_parameters( void );

#if defined( UNICODE ) && defined( __cplusplus )
extern "C"
#endif

int __cdecl _tmain( int number_of_command_line_arguments, LPCTSTR command_line_arguments[] )
{
   if ( number_of_command_line_arguments == 1 )
   {
      CService service( worker_thread );
      service.Initialize( TEXT( "WatchDog" ) );

      return( EXIT_SUCCESS );
   }

   if ( number_of_command_line_arguments == 2 )
   {
      if ( _tcsicmp( command_line_arguments[ 1 ], TEXT( "install" ) ) == 0 )
      {
         CServiceControlManager service_control_manager;

         service_control_manager.Open();

         if ( service_control_manager.Install( TEXT( "WatchDog" ), TEXT( "WatchDog" ), TEXT( "%SystemRoot%\\System32\\WatchDog.exe" ) ) == FALSE )
         {
            _tprintf( TEXT( "Install failed, please see Application Log for details\n" ) );
         }

         set_default_parameters();

         return( EXIT_SUCCESS );
      }
      else if ( _tcsicmp( command_line_arguments[ 1 ], TEXT( "remove" ) ) == 0 )
      {
         CServiceControlManager service_control_manager;

         service_control_manager.Open();

         if ( service_control_manager.Remove( TEXT( "WatchDog" ) ) == FALSE )
         {
            _tprintf( TEXT( "Removing failed, please see Application Log for details\n" ) );
         }

         return( EXIT_SUCCESS );
      }
      else if ( _tcsicmp( command_line_arguments[ 1 ], TEXT( "run" ) ) == 0 )
      {
         worker_thread( (LPVOID) 1 );
         return( EXIT_SUCCESS );
      }
      else
      {
         _tprintf( TEXT( "Samuel R. Blackburn, WFC Sample Application\nUsage: %s [install|remove]\n" ), command_line_arguments[ 0 ] );
      }
   }
   else
   {
      _tprintf( TEXT( "Samuel R. Blackburn, WFC Sample Application\nUsage: %s [install|remove]\n" ), command_line_arguments[ 0 ] );
   }

   return( EXIT_SUCCESS );
}


DWORD WINAPI worker_thread( LPVOID )
{
   {
      CEventLog log( TEXT( "WatchDog" ) );

      log.Report( CEventLog::eventInformation, 0, MSG_WATCHDOG_SERVICE_STARTED );
   }

   CStringArray names_of_services_to_keep_alive;

   DWORD number_of_seconds_to_sleep = 0;

   CString machine_name( TEXT( "" ) );

   BOOL return_value = TRUE;

   {
      CRegistry registry;

      if ( registry.Connect( (HKEY) CRegistry::keyLocalMachine ) == FALSE )
      {
         return( 0 );
      }

      CString key_name( TEXT( "SYSTEM\\CurrentControlSet\\Services\\WatchDog\\Parameters" ) );

      if ( registry.Open( key_name ) == FALSE )
      {
         return( 0 );
      }

      registry.GetValue( TEXT( "Services" ), names_of_services_to_keep_alive );
      registry.GetValue( TEXT( "NumberOfSecondsBetweenChecks" ), number_of_seconds_to_sleep );
      registry.GetValue( TEXT( "MachineName" ), machine_name );
   }

   DWORD sleep_time = 1000 * number_of_seconds_to_sleep;

   if ( sleep_time < 2000 )
   {
      /*
      ** Minimum sleep time is 2 seconds, this give the OS time to do other things
      */

      sleep_time = 2000;
   }

   int number_of_services_to_keep_alive = names_of_services_to_keep_alive.GetSize();

   CServiceControlManager service_control_manager;

   /*
   ** Sleep for one minute, this is in case we are starting during boot-up. We want
   ** to give the service control manager time to start all necessary services before
   ** we begin restarting stopped services.
   */

   Sleep( 60000 );

   do
   {
      if ( machine_name.IsEmpty() )
      {
         return_value = service_control_manager.Open( GENERIC_READ, NULL, (LPCTSTR) NULL );
      }
      else
      {
         return_value = service_control_manager.Open( GENERIC_READ, NULL, machine_name );
      }

      if ( return_value != FALSE )
      {
         if ( service_control_manager.EnumerateStatus( SERVICE_INACTIVE ) != FALSE )
         {
            CStringArray stopped_services;

            CServiceNameAndStatus status;

            while( service_control_manager.GetNext( status ) != FALSE )
            {
               stopped_services.Add( status.lpServiceName );
            }

            /*
            ** Now that we have the service names, we need to see which services need to be started
            */

            int number_of_stopped_services = stopped_services.GetSize();
            int alive_index   = 0;
            int stopped_index = 0;

            while( alive_index < number_of_services_to_keep_alive )
            {
               stopped_index = 0;

               while( stopped_index < number_of_stopped_services )
               {
                  if ( names_of_services_to_keep_alive[ alive_index ].CompareNoCase( stopped_services[ stopped_index ] ) == 0 )
                  {
                     /*
                     ** We found one that died, let's start it
                     */

                     service_control_manager.Start( names_of_services_to_keep_alive[ alive_index ] );

                     /*
                     ** We restarted a service, time to record the event
                     */

                     LPCTSTR string_array[ 1 ];

                     string_array[ 0 ] = (LPCTSTR) names_of_services_to_keep_alive[ alive_index ];

                     CEventLog event_log( TEXT( "WatchDog" ) );
                     event_log.Report( CEventLog::eventInformation, 0, MSG_WATCHDOG_RESTARTING_SERVICE, 1, (LPCTSTR *) string_array );

                     /*
                     ** pop out of the loop
                     */

                     stopped_index = number_of_stopped_services;
                  }

                  stopped_index++;
               }

               alive_index++;
            }
         }
      }
      else
      {
         LPVOID message_buffer = (LPVOID) NULL;

         ::FormatMessage( FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
                          NULL,
                          service_control_manager.GetErrorCode(),
                          MAKELANGID( LANG_ENGLISH, SUBLANG_ENGLISH_US ),
                (LPTSTR) &message_buffer,
                          0,
                          NULL );

         CEventLog event_log( TEXT( "WatchDog" ) );
         event_log.ReportError( (LPCTSTR) message_buffer );

         if ( message_buffer != NULL )
         {
            ::LocalFree( message_buffer );
         }
      }

      service_control_manager.Close();
      Sleep( sleep_time );
   }
   while( 1 );

   return( 0 );
}

void set_default_parameters( void )
{
   CRegistry registry;

   if ( registry.Connect( (HKEY) CRegistry::keyLocalMachine ) != FALSE )
   {
      if ( registry.Create( TEXT( "SYSTEM\\CurrentControlSet\\Services\\WatchDog\\Parameters" ) ) != FALSE )
      {
         DWORD default_sleep_time = 60;

         if ( registry.SetValue( TEXT( "NumberOfSecondsBetweenChecks" ), default_sleep_time ) == FALSE )
         {
            LPVOID message_buffer = (LPVOID) NULL;

            ::FormatMessage( FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
                             NULL,
                             registry.GetErrorCode(),
                             MAKELANGID( LANG_ENGLISH, SUBLANG_ENGLISH_US ),
                   (LPTSTR) &message_buffer,
                             0,
                             NULL );

            LPCTSTR string_array[ 2 ];

            string_array[ 0 ] = TEXT( "SYSTEM\\CurrentControlSet\\Services\\WatchDog\\Parameters\\NumberOfSecondsBetweenChecks" );
            string_array[ 1 ] = (LPCTSTR) message_buffer;

            CEventLog event_log( TEXT( "WatchDog" ) );
            event_log.Report( CEventLog::eventError, 0, MSG_CANT_SET_REGISTRY_ENTRY, 2, (LPCTSTR *) string_array );

            if ( message_buffer != NULL )
            {
               ::LocalFree( message_buffer );
            }
         }

         CStringArray strings;

         strings.RemoveAll();

         strings.Add( TEXT( "" ) );

         if ( registry.SetValue( TEXT( "Services" ), strings ) == FALSE )
         {
            LPVOID message_buffer = (LPVOID) NULL;

            ::FormatMessage( FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
                             NULL,
                             registry.GetErrorCode(),
                             MAKELANGID( LANG_ENGLISH, SUBLANG_ENGLISH_US ),
                   (LPTSTR) &message_buffer,
                             0,
                             NULL );

            LPCTSTR string_array[ 2 ];

            string_array[ 0 ] = TEXT( "SYSTEM\\CurrentControlSet\\Services\\WatchDog\\Parameters\\Services" );
            string_array[ 1 ] = (LPCTSTR) message_buffer;

            CEventLog event_log( TEXT( "WatchDog" ) );
            event_log.Report( CEventLog::eventError, 0, MSG_CANT_SET_REGISTRY_ENTRY, 2, (LPCTSTR *) string_array );

            if ( message_buffer != NULL )
            {
               ::LocalFree( message_buffer );
            }
         }
      }
      else
      {
         LPVOID message_buffer = (LPVOID) NULL;

         ::FormatMessage( FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
                          NULL,
                          registry.GetErrorCode(),
                          MAKELANGID( LANG_ENGLISH, SUBLANG_ENGLISH_US ),
                (LPTSTR) &message_buffer,
                          0,
                          NULL );

         LPCTSTR string_array[ 2 ];

         string_array[ 0 ] = TEXT( "SYSTEM\\CurrentControlSet\\Services\\WatchDog\\Parameters" );
         string_array[ 1 ] = (LPCTSTR) message_buffer;

         CEventLog event_log( TEXT( "WatchDog" ) );
         event_log.Report( CEventLog::eventError, 0, MSG_CANT_CREATE_REGISTRY_KEY, 2, (LPCTSTR *) string_array );

         if ( message_buffer != NULL )
         {
            ::LocalFree( message_buffer );
         }
      }
   }
   else
   {
      LPVOID message_buffer = (LPVOID) NULL;

      ::FormatMessage( FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
                       NULL,
                       registry.GetErrorCode(),
                       MAKELANGID( LANG_ENGLISH, SUBLANG_ENGLISH_US ),
             (LPTSTR) &message_buffer,
                       0,
                       NULL );

      LPCTSTR string_array[ 2 ];

      string_array[ 0 ] = TEXT( "keyLocalMachine" );
      string_array[ 1 ] = (LPCTSTR) message_buffer;

      CEventLog event_log( TEXT( "WatchDog" ) );
      event_log.Report( CEventLog::eventError, 0, MSG_CANT_CONNECT_TO_REGISTRY, 2, (LPCTSTR *) string_array );

      if ( message_buffer != NULL )
      {
         ::LocalFree( message_buffer );
      }
   }
}
