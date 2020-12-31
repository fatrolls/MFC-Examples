#include <wfc.h>
#include "messages.h"
#pragma hdrstop

/*
** Author: Samuel R. Blackburn
** Internet: wfc@pobox.com
**
** $Date: 8/17/98 8:24a $
** $Revision: 5 $
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
** NumberOfMinutesBetweenPings, REG_DWORD, how long to sleep between heartbeats
** StartOnMinuteNumber, REG_DWORD, minute number to begin pinging (0 = top of the hour)
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

HANDLE g_TimerEvent;

DWORD WINAPI worker_thread( LPVOID unused_parameter );
DWORD WINAPI timer_thread( LPVOID unused_parameter );
VOID set_default_parameters( DWORD, CString&, DWORD );
VOID show_usage( LPSTR progam_name );

int __cdecl _tmain( int argc, LPCTSTR argv[] )
{
   if ( argc == 1 )
   {
      CService service( worker_thread );
      service.Initialize( TEXT( "Pinger" ) );

      return( EXIT_SUCCESS );
   }

   if ( argc > 1 )
   {
      if ( _tcsicmp( argv[ 1 ], TEXT( "install" ) ) == 0 )
      {
         if ( argc < 4 )
         {
            show_usage( argv[ 0 ] );
            return( EXIT_SUCCESS );
         }

         CServiceControlManager service_control_manager;

         service_control_manager.Open();

         if ( service_control_manager.Install( TEXT( "Pinger" ), TEXT( "Pinger" ), TEXT( "%SystemRoot%\\System32\\Pinger.exe" ) ) == FALSE )
         {
            _tprintf( TEXT( "Install failed, please see Application Log for details\n" ) );
         }

         DWORD minute_number = 0;

         if ( argc > 4 )
         {
            minute_number = _ttol( argv[ 4 ] );
         }

         set_default_parameters( _ttol( argv[ 2 ] ), CString( argv[ 3 ] ), minute_number );

         return( EXIT_SUCCESS );
      }
      else if ( _tcsicmp( argv[ 1 ], TEXT( "remove" ) ) == 0 )
      {
         CServiceControlManager service_control_manager;

         service_control_manager.Open();

         if ( service_control_manager.Remove( TEXT( "Pinger" ) ) == FALSE )
         {
            _tprintf( TEXT( "Removing failed, please see Application Log for details\n" ) );
         }

         return( EXIT_SUCCESS );
      }
      else if ( _tcsicmp( argv[ 1 ], TEXT( "run" ) ) == 0 )
      {
         worker_thread( (LPVOID) 1 );
         return( EXIT_SUCCESS );
      }
      else
      {
         show_usage( argv[ 0 ] );
      }
   }
   else
   {
      show_usage( argv[ 0 ] );
   }

   return( EXIT_SUCCESS );
}


DWORD WINAPI worker_thread( LPVOID )
{
   {
      CEventLog log( TEXT( "Pinger" ) );

      log.Report( CEventLog::eventInformation, 0, MSG_PINGER_SERVICE_STARTED );
   }

   DWORD number_of_minutes_to_sleep = 0;
   DWORD minute_number;
   CString machine_name( TEXT( "" ) );

   BOOL return_value = TRUE;

   {
      CRegistry registry;

      if ( registry.Connect( (HKEY) CRegistry::keyLocalMachine ) == FALSE )
      {
         return( 0 );
      }

      CString key_name( TEXT( "SYSTEM\\CurrentControlSet\\Services\\Pinger\\Parameters" ) );

      if ( registry.Open( key_name ) == FALSE )
      {
         return( 0 );
      }

      registry.GetValue( TEXT( "StartOnMinuteNumber" ), minute_number );
      registry.GetValue( TEXT( "NumberOfMinutesBetweenPings" ), number_of_minutes_to_sleep );
      registry.GetValue( TEXT( "MachineName" ), machine_name );
   }

   CString command_line;

   DWORD sleep_time = 1000 * number_of_minutes_to_sleep * 60;

   if ( sleep_time < 2000 )
   {
      /*
      ** Minimum sleep time is 2 seconds, this give the OS time to do other things
      */

      sleep_time = 2000;
   }

   if ( machine_name.IsEmpty() )
   {
      machine_name = TEXT( "20.1.10.27" );
   }

   /*
   ** Construct our command line
   */

   command_line = TEXT( "ping " );
   command_line += machine_name;

   /*
   ** See if we need to wait until our minute rolls around
   */

   if ( minute_number < 60 )
   {
      CTime current_time = CTime::GetCurrentTime();

      while( current_time.GetMinute() != (int) minute_number )
      {
         Sleep( 900 );
         current_time = CTime::GetCurrentTime();
      }
   }

   g_TimerEvent = CreateEvent( NULL, FALSE, FALSE, NULL );

   if ( g_TimerEvent == (HANDLE) NULL )
   {
      LPVOID message_buffer = (LPVOID) NULL;

      ::FormatMessage( FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
                       NULL,
                       GetLastError(),
                       MAKELANGID( LANG_ENGLISH, SUBLANG_ENGLISH_US ),
             (LPTSTR) &message_buffer,
                       0,
                       NULL );

      LPCTSTR string_array[ 1 ];

      string_array[ 0 ] = (LPCTSTR) message_buffer;

      CEventLog event_log( TEXT( "Pinger" ) );
      event_log.Report( CEventLog::eventError, 0, MSG_CANT_CREATE_TIMER_EVENT, 1, (LPCTSTR *) string_array );

      if ( message_buffer != NULL )
      {
         ::LocalFree( message_buffer );
      }

      return( 0 );
   }

   DWORD timer_thread_id = 0;

   if ( CreateThread( NULL, 0, timer_thread, (LPVOID) sleep_time, 0, &timer_thread_id ) == (HANDLE) NULL )
   {
      LPVOID message_buffer = (LPVOID) NULL;

      ::FormatMessage( FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
                       NULL,
                       GetLastError(),
                       MAKELANGID( LANG_ENGLISH, SUBLANG_ENGLISH_US ),
             (LPTSTR) &message_buffer,
                       0,
                       NULL );

      LPCTSTR string_array[ 1 ];

      string_array[ 0 ] = (LPCTSTR) message_buffer;

      CEventLog event_log( TEXT( "Pinger" ) );
      event_log.Report( CEventLog::eventError, 0, MSG_CANT_CREATE_TIMER_THREAD, 1, (LPCTSTR *) string_array );

      if ( message_buffer != NULL )
      {
         ::LocalFree( message_buffer );
      }

      return( 0 );
   }

   do
   {
      WinExec( command_line, SW_HIDE );
      WaitForSingleObject( g_TimerEvent, INFINITE );
   }
   while( 1 );

   return( 0 );
}

DWORD WINAPI timer_thread( LPVOID pulse_interval )
{
   do
   {
      PulseEvent( g_TimerEvent );
      Sleep( (DWORD) pulse_interval );
   }
   while( 1 );

   return( 0 );
}

void set_default_parameters( DWORD number_of_minutes_to_sleep, CString& machine_name, DWORD minute_number )
{
   if ( number_of_minutes_to_sleep == 0 )
   {
      number_of_minutes_to_sleep = 1;
   }

   if ( machine_name.IsEmpty() )
   {
      machine_name = TEXT( "20.1.10.27" );
   }

   // If minute_number is greater than 59 then pinger will immediately start,
   // it won't wait for a starting minute.

   CRegistry registry;

   if ( registry.Connect( (HKEY) CRegistry::keyLocalMachine ) != FALSE )
   {
      if ( registry.Create( TEXT( "SYSTEM\\CurrentControlSet\\Services\\Pinger\\Parameters" ) ) != FALSE )
      {
         /*
         ** Save the number of minutes between pings
         */

         if ( registry.SetValue( TEXT( "NumberOfMinutesBetweenPings" ), number_of_minutes_to_sleep ) == FALSE )
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

            string_array[ 0 ] = TEXT( "SYSTEM\\CurrentControlSet\\Services\\Pinger\\Parameters\\NumberOfMinutesBetweenPings" );
            string_array[ 1 ] = (LPCTSTR) message_buffer;

            CEventLog event_log( TEXT( "Pinger" ) );
            event_log.Report( CEventLog::eventError, 0, MSG_CANT_SET_REGISTRY_ENTRY, 2, (LPCTSTR *) string_array );

            if ( message_buffer != NULL )
            {
               ::LocalFree( message_buffer );
            }
         }

         /*
         ** Now save the name of the machine to ping
         */

         if ( registry.SetValue( TEXT( "MachineName" ), machine_name ) == FALSE )
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

            string_array[ 0 ] = TEXT( "SYSTEM\\CurrentControlSet\\Services\\Pinger\\Parameters\\MachineName" );
            string_array[ 1 ] = (LPCTSTR) message_buffer;

            CEventLog event_log( TEXT( "Pinger" ) );
            event_log.Report( CEventLog::eventError, 0, MSG_CANT_SET_REGISTRY_ENTRY, 2, (LPCTSTR *) string_array );

            if ( message_buffer != NULL )
            {
               ::LocalFree( message_buffer );
            }
         }

         /*
         ** Save the minute number to begin on
         */

         if ( registry.SetValue( TEXT( "StartOnMinuteNumber" ), minute_number ) == FALSE )
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

            string_array[ 0 ] = TEXT( "SYSTEM\\CurrentControlSet\\Services\\Pinger\\Parameters\\StartOnMinuteNumber" );
            string_array[ 1 ] = (LPCTSTR) message_buffer;

            CEventLog event_log( TEXT( "Pinger" ) );
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

         string_array[ 0 ] = TEXT( "SYSTEM\\CurrentControlSet\\Pinger\\Parameters" );
         string_array[ 1 ] = (LPCTSTR) message_buffer;

         CEventLog event_log( TEXT( "Pinger" ) );
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

      CEventLog event_log( TEXT( "Pinger" ) );
      event_log.Report( CEventLog::eventError, 0, MSG_CANT_CONNECT_TO_REGISTRY, 2, (LPCTSTR *) string_array );

      if ( message_buffer != NULL )
      {
         ::LocalFree( message_buffer );
      }
   }
}

VOID show_usage( LPSTR program_name )
{
   _tprintf( TEXT( "Pinger service 1.4, Samuel R. Blackburn, WFC Sample Application\n\nUsage: %s [install SleepTime MachineName StartMinute|remove|run]\n\n" ), program_name );
   _tprintf( TEXT( "To have explorer.csc.com ping'd every 60 minutes begining at the top of\nthe hour, type:\n%s install 60 explorer.sed.csc.com 0\n\n\n" ), program_name );
   _tprintf( TEXT( "This service is great for keep RAS connections open when they automatically\nclose after a certain amount of time passes without any traffic over the\nconnection.\n" ) );
}
