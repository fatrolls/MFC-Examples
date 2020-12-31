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
** Copyright, 2000, Samuel R. Blackburn
**
** $Workfile: CServiceApplication.cpp $
** $Revision: 4 $
** $Modtime: 1/17/00 9:19a $
** $Reuse Tracing Code: 1 $
*/

#if defined( _DEBUG ) && ! defined( WFC_STL )
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif // _DEBUG

CServiceApplication::CServiceApplication( int number_of_command_line_arguments,
                           LPCTSTR command_line_arguments[],
                           LPCTSTR service_name,
                           LPCTSTR friendly_service_name,
                           LPCTSTR executable_path,
                           LPTHREAD_START_ROUTINE worker_thread,
                           SHOW_USAGE_ROUTINE show_usage,
                           SET_DEFAULTS_ROUTINE set_defaults,
                           DWORD   installation_configuration )
{
   WFCLTRACEINIT( TEXT( "CServiceApplication::CServiceApplication()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   ASSERT( worker_thread != NULL );

   m_Main( number_of_command_line_arguments,
           command_line_arguments,
           service_name,
           friendly_service_name,
           executable_path,
           installation_configuration,
           worker_thread,
           show_usage,
           set_defaults );
}

CServiceApplication::~CServiceApplication( void )
{
   WFCLTRACEINIT( TEXT( "CServiceApplication::~CServiceApplication()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
}

int CServiceApplication::m_Main( int number_of_command_line_arguments,
                                 LPCTSTR command_line_arguments[],
                                 LPCTSTR service_name,
                                 LPCTSTR friendly_service_name,
                                 LPCTSTR executable_path,
                                 DWORD   installation_configuration,
                                 LPTHREAD_START_ROUTINE worker_thread,
                                 SHOW_USAGE_ROUTINE show_usage,
                                 SET_DEFAULTS_ROUTINE set_defaults )
{
   WFCLTRACEINIT( TEXT( "CServiceApplication::m_Main()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );

   if ( number_of_command_line_arguments == 1 )
   {
      CService service( worker_thread );
      service.Initialize( service_name );

      return( EXIT_SUCCESS );
   }

   if ( number_of_command_line_arguments > 1 )
   {
      if ( _tcsicmp( command_line_arguments[ 1 ], TEXT( "install" ) ) == 0 )
      {
         CServiceControlManager service_control_manager;

         if ( service_control_manager.Open() == FALSE )
         {
            WFCTRACE( TEXT( "Can't open service control manager because " ) );
            WFCTRACEERROR( service_control_manager.GetErrorCode() );
            _tprintf( TEXT( "Can't open service control manager, INSTALL FAILED!\n" ) );
            return( EXIT_FAILURE );
         }

         if ( service_control_manager.Install( service_name, friendly_service_name, executable_path ) == FALSE )
         {
            WFCTRACE( TEXT( "Can't install service because " ) );
            WFCTRACEERROR( service_control_manager.GetErrorCode() );
            _tprintf( TEXT( "Install failed. Please see Application Log for details.\n" ) );
            return( EXIT_FAILURE );
         }

         if ( service_control_manager.SetConfiguration( service_name, installation_configuration ) == FALSE )
         {
            WFCTRACE( TEXT( "Can't set configuration because " ) );
            WFCTRACEERROR( service_control_manager.GetErrorCode() );
            _tprintf( TEXT( "Can't set service configuration.\n" ) );
            return( EXIT_FAILURE );
         }

         if ( set_defaults != NULL )
         {
            // We were passed a pointer, don't trust it...

            try
            {
               set_defaults();
            }
            catch( ... )
            {
            }
         }

         return( EXIT_SUCCESS );
      }
      else if ( _tcsicmp( command_line_arguments[ 1 ], TEXT( "remove" ) ) == 0 )
      {
         CServiceControlManager service_control_manager;

         if ( service_control_manager.Open() == FALSE )
         {
            WFCTRACE( TEXT( "Can't open service control manager because " ) );
            WFCTRACEERROR( service_control_manager.GetErrorCode() );
            _tprintf( TEXT( "Can't open service control manager, attempting to carry on...\n" ) );
         }

         if ( service_control_manager.Remove( service_name ) == FALSE )
         {
            WFCTRACE( TEXT( "Can't remove service " ) );
            WFCTRACEERROR( service_control_manager.GetErrorCode() );
            _tprintf( TEXT( "Can't remove service, see Application Log for details.\n" ) );
            return( EXIT_FAILURE );
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
         if ( show_usage != NULL )
         {
            // We were passed a pointer, don't trust it...

            try
            {
               show_usage( command_line_arguments[ 0 ] );
            }
            catch( ... )
            {
            }
         }
      }
   }
   else
   {
      if ( show_usage != NULL )
      {
         // We were passed a pointer, don't trust it...

         try
         {
            show_usage( command_line_arguments[ 0 ] );
         }
         catch( ... )
         {
         }
      }
   }

   return( EXIT_SUCCESS );
}

// End of source

#if 0
<HTML>

<HEAD>
<TITLE>WFC - CServiceApplication</TITLE>
<META name="keywords" content="WFC, MFC extension library, freeware class library, Win32, source code">
<META name="description" content="The C++ class that makes it easy to create NT services.">
</HEAD>

<BODY>

<H1>CServiceApplication</H1>
$Revision: 4 $
<HR>

<H2>Description</H2>

This class encapsulates the basic logic behind a service application. It
takes care of installing, removing and starting a service as a console
application.

<H2>Construction</H2>

<DL COMPACT>

<DT><PRE><B>CServiceApplication</B>( int number_of_command_line_arguments,
                           LPCTSTR command_line_arguments[],
                           LPCTSTR service_name,
                           LPCTSTR friendly_service_name,
                           LPCTSTR executable_path,
                           LPTHREAD_START_ROUTINE worker_thread,
                           SHOW_USAGE_ROUTINE show_usage,
                           SET_DEFAULTS_ROUTINE set_defaults,
                           DWORD   installation_configuration )</PRE><DD>
That's pretty much it.

</DL>

<H2>Data Members</H2>

None.

<H2>Methods</H2>

None.

<H2>Example</H2>
<PRE><CODE>#include &lt;wfc.h&gt;
#include &quot;messages.h&quot;
#pragma hdrstop

DWORD WINAPI worker_thread( LPVOID pointer_to_parent_CService_class );
VOID set_default_parameters( void );

int __cdecl _tmain( int number_of_command_line_arguments, LPCTSTR command_line_arguments[] )
{
   <A HREF="WfcTrace.htm">WFCTRACEINIT</A>( TEXT( &quot;_tmain()&quot; ) );

   <B>CServiceApplication</B> application( number_of_command_line_arguments,
                                    command_line_arguments,
                                    TEXT( &quot;WatchDog&quot; ),
                                    TEXT( &quot;Service Watch Dog&quot; ),
                                    command_line_arguments[ 0 ],
                                    worker_thread,
                                    NULL,
                                    set_default_parameters );

   return( EXIT_SUCCESS );
}

DWORD WINAPI worker_thread( LPVOID )
{
   <A HREF="WfcTrace.htm">WFCTRACEINIT</A>( TEXT( &quot;worker_thread()&quot; ) );

   {
      <A HREF="CEVNTLOG.htm">CEventLog</A> log( TEXT( &quot;WatchDog&quot; ) );
      log.Report( CEventLog::eventInformation, 0, MSG_WATCHDOG_SERVICE_STARTED );
   }

   CStringArray names_of_services_to_keep_alive;

   DWORD number_of_seconds_to_sleep = 0;

   CString machine_name( TEXT( &quot;&quot; ) );

   BOOL return_value = TRUE;

   {
      <A HREF="REGISTRY.htm">CRegistry</A> registry;

      if ( registry.Connect( CRegistry::keyLocalMachine ) == FALSE )
      {
         return( 0 );
      }

      CString key_name( TEXT( &quot;SYSTEM\\CurrentControlSet\\Services\\WatchDog\\Parameters&quot; ) );

      if ( registry.Open( key_name ) == FALSE )
      {
         return( 0 );
      }

      registry.GetValue( TEXT( &quot;Services&quot; ), names_of_services_to_keep_alive );
      registry.GetValue( TEXT( &quot;NumberOfSecondsBetweenChecks&quot; ), number_of_seconds_to_sleep );
      registry.GetValue( TEXT( &quot;MachineName&quot; ), machine_name );
   }

   DWORD sleep_time = 1000 * number_of_seconds_to_sleep;

   if ( sleep_time &lt; 2000 )
   {
      // Minimum sleep time is 2 seconds, this give the OS time to do other things
      sleep_time = 2000;
   }

   int number_of_services_to_keep_alive = names_of_services_to_keep_alive.GetSize();

   <A HREF="CSvcMgr.htm">CServiceControlManager</A> service_control_manager;

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
         return_value = service_control_manager.Open( GENERIC_READ, NULL, (LPCTSTR *) NULL );
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

            // Now that we have the service names, we need to see which services need to be started

            int number_of_stopped_services = stopped_services.GetSize();
            int alive_index                = 0;
            int stopped_index              = 0;

            while( alive_index &lt; number_of_services_to_keep_alive )
            {
               stopped_index = 0;

               while( stopped_index &lt; number_of_stopped_services )
               {
                  if ( names_of_services_to_keep_alive[ alive_index ].CompareNoCase( stopped_services[ stopped_index ] ) == 0 )
                  {
                     // We found one that died, let's start it

                     service_control_manager.Start( names_of_services_to_keep_alive[ alive_index ] );

                     // We restarted a service, time to record the event

                     LPCTSTR string_array[ 1 ];

                     string_array[ 0 ] = (LPCTSTR) names_of_services_to_keep_alive[ alive_index ];

                     <A HREF="CEVNTLOG.htm">CEventLog</A> event_log( TEXT( &quot;WatchDog&quot; ) );

                     event_log.Report( CEventLog::eventInformation,
                                       0,
                                       MSG_WATCHDOG_RESTARTING_SERVICE,
                                       1,
                           (LPCTSTR *) string_array );

                     // pop out of the loop

                     stopped_index = number_of_stopped_services;
                  }

                  stopped_index++;
               }

               alive_index++;
            }
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
   <A HREF="WfcTrace.htm">WFCTRACEINIT</A>( TEXT( &quot;set_default_parameters()&quot; ) );

   <A HREF="REGISTRY.htm">CRegistry</A> registry;

   if ( registry.Connect( CRegistry::keyLocalMachine ) != FALSE )
   {
      if ( registry.Create( TEXT( &quot;SYSTEM\\CurrentControlSet\\Services\\WatchDog\\Parameters&quot; ) ) != FALSE )
      {
         DWORD default_sleep_time = 60;

         if ( registry.SetValue( TEXT( &quot;NumberOfSecondsBetweenChecks&quot; ), default_sleep_time ) == FALSE )
         {
            LPVOID message_buffer = (LPVOID) NULL;

            ::FormatMessage( FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
                             NULL,
                             registry.GetErrorCode(),
                             MAKELANGID( LANG_ENGLISH, SUBLANG_ENGLISH_US ),
                   (LPTSTR) &amp;message_buffer,
                             0,
                             NULL );

            LPCTSTR string_array[ 2 ];

            string_array[ 0 ] = TEXT( &quot;SYSTEM\\CurrentControlSet\\Services\\WatchDog\\Parameters\\NumberOfSecondsBetweenChecks&quot; );
            string_array[ 1 ] = (LPCTSTR) message_buffer;

            <A HREF="CEVNTLOG.htm">CEventLog</A> event_log( TEXT( &quot;WatchDog&quot; ) );

            event_log.Report( CEventLog::eventError,
                              0,
                              MSG_CANT_SET_REGISTRY_ENTRY,
                              2,
                  (LPCTSTR *) string_array );

            if ( message_buffer != NULL )
            {
               ::LocalFree( message_buffer );
            }
         }

         CStringArray strings;

         strings.RemoveAll();
         strings.Add( TEXT( &quot;&quot; ) );

         if ( registry.SetValue( TEXT( &quot;Services&quot; ), strings ) == FALSE )
         {
            LPVOID message_buffer = (LPVOID) NULL;

            ::FormatMessage( FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
                             NULL,
                             registry.GetErrorCode(),
                             MAKELANGID( LANG_ENGLISH, SUBLANG_ENGLISH_US ),
                   (LPTSTR) &amp;message_buffer,
                             0,
                             NULL );

            LPCTSTR string_array[ 2 ];

            string_array[ 0 ] = TEXT( &quot;SYSTEM\\CurrentControlSet\\Services\\WatchDog\\Parameters\\Services&quot; );
            string_array[ 1 ] = (LPCTSTR) message_buffer;

            <A HREF="CEVNTLOG.htm">CEventLog</A> event_log( TEXT( &quot;WatchDog&quot; ) );

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
                (LPTSTR) &amp;message_buffer,
                          0,
                          NULL );

         LPCTSTR string_array[ 2 ];

         string_array[ 0 ] = TEXT( &quot;SYSTEM\\CurrentControlSet\\Services\\WatchDog\\Parameters&quot; );
         string_array[ 1 ] = (LPCTSTR) message_buffer;

         <A HREF="CEVNTLOG.htm">CEventLog</A> event_log( &quot;WatchDog&quot; );

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
             (LPTSTR) &amp;message_buffer,
                       0,
                       NULL );

      LPCTSTR string_array[ 2 ];

      string_array[ 0 ] = TEXT( &quot;keyLocalMachine&quot; );
      string_array[ 1 ] = (LPCTSTR) message_buffer;

      <A HREF="CEVNTLOG.htm">CEventLog</A> event_log( TEXT( &quot;WatchDog&quot; ) );

      event_log.Report( CEventLog::eventError, 0, MSG_CANT_CONNECT_TO_REGISTRY, 2, (LPCTSTR *) string_array );

      if ( message_buffer != NULL )
      {
         ::LocalFree( message_buffer );
      }
   }
}</CODE></PRE>

<HR><I>Copyright, 2000, <A HREF="mailto:wfc@pobox.com">Samuel R. Blackburn</A></I><BR>
$Workfile: CServiceApplication.cpp $<BR>
$Modtime: 1/17/00 9:19a $
</BODY>

</HTML>
#endif
