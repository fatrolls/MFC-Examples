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
** $Workfile: cservice.cpp $
** $Revision: 35 $
** $Modtime: 1/17/00 9:13a $
** $Reuse Tracing Code: 1 $
*/

#if defined( _DEBUG ) && ! defined( WFC_STL )
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif // _DEBUG

CRITICAL_SECTION g_ServiceCriticalSection;

CService *CService::m_StaticService_p = 0;

CService::CService( LPTHREAD_START_ROUTINE thread_start_routine, DWORD controls_accepted, DWORD wait_hint )
{
   WFCLTRACEINIT( TEXT( "CService::CService()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   ASSERT( thread_start_routine != NULL );

   WFCTRACEVAL( TEXT( "Main tid = " ), ::GetCurrentThreadId() );

   ::InitializeCriticalSection( &g_ServiceCriticalSection );

   m_ThreadStartRoutine  = thread_start_routine;
   m_ThreadHandle        = NULL;
   m_ExitEventHandle     = NULL;
   m_ServiceStatusHandle = 0;
   m_ErrorCode           = NO_ERROR;
   m_Running             = FALSE;
   m_Paused              = FALSE;
   m_Exiting             = FALSE;
   m_Debugging           = 0;
   m_ControlsAccepted    = controls_accepted;
   m_WaitHint            = wait_hint;
   m_CurrentState        = SERVICE_START_PENDING;
   m_StaticService_p     = this;

   CommandLineParameters.RemoveAll();
}

CService::~CService( void )
{
   WFCLTRACEINIT( TEXT( "CService::~CService()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );

   ::DeleteCriticalSection( &g_ServiceCriticalSection );

   if ( m_ExitEventHandle != NULL )
   {
      ::wfc_close_handle( m_ExitEventHandle );
      m_ExitEventHandle = NULL;
   }

   if ( m_ThreadHandle != NULL )
   {
      ::wfc_close_handle( m_ThreadHandle );
      m_ThreadHandle = NULL;
   }

   CommandLineParameters.RemoveAll();
}

#if defined( _DEBUG )

void CService::AssertValid( void ) const
{
   ASSERT( m_Exiting             == FALSE );
   ASSERT( m_ExitEventHandle     != NULL  );
   ASSERT( m_ServiceStatusHandle != 0     );
   ASSERT( m_ThreadHandle        != NULL  );
   ASSERT( m_StaticService_p     != 0     );
}

#endif // _DEBUG

int CService::DialogBoxParam( HINSTANCE instance, LPCTSTR template_name, HWND parent_window, DLGPROC dialogbox_procedure, LPARAM lParam )
{
   WFCLTRACEINIT( TEXT( "CService::DialogBoxParam()" ) );

   // You must have SERVICE_INTERACTIVE_PROCESS for this to work

   int return_value = 0;

   HDESK old_desktop_handle = NULL;
   HDESK desktop_handle     = NULL;

   old_desktop_handle = ::GetThreadDesktop( ::GetCurrentThreadId() );
   desktop_handle  = ::OpenInputDesktop( 0, FALSE, DESKTOP_CREATEWINDOW );
   ::SetThreadDesktop( desktop_handle );

   return_value = ::DialogBoxParam( instance, template_name, parent_window, dialogbox_procedure, lParam );

   ::SetThreadDesktop( old_desktop_handle );

   return( return_value );
}

#if defined( _DEBUG )

void CService::DumpStatus( SERVICE_STATUS *status_p ) const
{
   WFCLTRACEINIT( TEXT( "CService::DumpStatus()" ) );
   WFCTRACE( TEXT( "calling SetServiceStatus with:" ) );

   // The user passed us a pointer, don't trust it

   try
   {
   switch( status_p->dwServiceType )
   {
      case SERVICE_WIN32_OWN_PROCESS:

         WFCTRACE( TEXT( "dwServiceType SERVICE_WIN32_OWN_PROCESS" ) );
         break;

      case SERVICE_WIN32_SHARE_PROCESS:

         WFCTRACE( TEXT( "dwServiceType SERVICE_WIN32_SHARE_PROCESS" ) );
         break;

      case SERVICE_KERNEL_DRIVER:

         WFCTRACE( TEXT( "dwServiceType SERVICE_KERNEL_DRIVER" ) );
         break;

      case SERVICE_FILE_SYSTEM_DRIVER:

         WFCTRACE( TEXT( "dwServiceType SERVICE_FILE_SYSTEM_DRIVER" ) );
         break;

      case SERVICE_INTERACTIVE_PROCESS:

         WFCTRACE( TEXT( "dwServiceType SERVICE_INTERACTIVE_PROCESS" ) );
         break;

      default:

         WFCTRACEVAL( TEXT( "Unknown dwServiceType " ), status_p->dwServiceType );
         break;
   }

   WFCTRACE( TEXT( "   SERVICE_CONTROL_INTERROGATE" ) );

   if ( status_p->dwControlsAccepted & SERVICE_ACCEPT_STOP )
   {
      WFCTRACE( TEXT( "   SERVICE_CONTROL_STOP" ) );
   }

   if ( status_p->dwControlsAccepted & SERVICE_ACCEPT_PAUSE_CONTINUE )
   {
      WFCTRACE( TEXT( "   SERVICE_CONTROL_PAUSE" ) );
      WFCTRACE( TEXT( "   SERVICE_CONTROL_CONTINUE" ) );
   }

   if ( status_p->dwControlsAccepted & SERVICE_ACCEPT_SHUTDOWN )
   {
      WFCTRACE( TEXT( "   SERVICE_CONTROL_SHUTDOWN" ) );
   }

   switch( status_p->dwCurrentState )
   {
      case SERVICE_STOPPED:

         WFCTRACE( TEXT( "dwCurrentState SERVICE_STOPPED" ) );
         break;

      case SERVICE_START_PENDING:

         WFCTRACE( TEXT( "dwCurrentState SERVICE_START_PENDING" ) );
         break;

      case SERVICE_STOP_PENDING:

         WFCTRACE( TEXT( "dwCurrentState SERVICE_STOP_PENDING" ) );
         break;

      case SERVICE_RUNNING:

         WFCTRACE( TEXT( "dwCurrentState SERVICE_RUNNING" ) );
         break;

      case SERVICE_CONTINUE_PENDING:

         WFCTRACE( TEXT( "dwCurrentState SERVICE_CONTINUE_PENDING" ) );
         break;

      case SERVICE_PAUSE_PENDING:

         WFCTRACE( TEXT( "dwCurrentState SERVICE_PAUSE_PENDING" ) );
         break;

      case SERVICE_PAUSED:

         WFCTRACE( TEXT( "dwCurrentState SERVICE_PAUSED" ) );
         break;

      default:

         WFCTRACEVAL( TEXT( "dwCurrentState " ), status_p->dwCurrentState );
         break;
   }

   if ( status_p->dwWin32ExitCode == ERROR_SERVICE_SPECIFIC_ERROR )
   {
      WFCTRACEVAL( TEXT( "dwServiceSpecificExitCode " ), status_p->dwServiceSpecificExitCode );
   }
   else
   {
      WFCTRACEVAL( TEXT( "dwWin32ExitCode " ), status_p->dwWin32ExitCode );
   }

   WFCTRACEVAL( TEXT( "dwCheckPoint " ), status_p->dwCheckPoint );
   WFCTRACEVAL( TEXT( "dwWaitHint " ), status_p->dwWaitHint );
   }
   catch( ... )
   {
      ; // Do Nothing
   }
}

#endif // _DEBUG

void CService::Exit( void )
{
   WFCLTRACEINIT( TEXT( "CService::Exit()" ) );

   ::EnterCriticalSection( &g_ServiceCriticalSection );

   m_Running      = FALSE;
   m_CurrentState = SERVICE_STOPPED;
   m_Exiting      = TRUE;

   ::LeaveCriticalSection( &g_ServiceCriticalSection );

   if ( m_ExitEventHandle != NULL )
   {
      ::SetEvent( m_ExitEventHandle );
   }
}

BOOL CService::Initialize( LPCTSTR name_of_service )
{
   WFCLTRACEINIT( TEXT( "CService::Initialize()" ) );

   /*
   ** Thank you Rob Williams (CI$ 73740,774) for fixing this function
   */

   ASSERT( name_of_service != NULL );

   // We were passed a pointer, don't trust it

   try
   {
      BOOL return_value = TRUE;

      // initialize m_ServiceTable

      _tcsncpy( m_ServiceName, name_of_service, SERVICE_NAME_LEN );

      m_ServiceTable[ 0 ].lpServiceName = m_ServiceName;
      m_ServiceTable[ 0 ].lpServiceProc = CService::ServiceMain;
      m_ServiceTable[ 1 ].lpServiceName = 0;
      m_ServiceTable[ 1 ].lpServiceProc = 0;

      // initiate conversation with SCM

      if ( ::StartServiceCtrlDispatcher( m_ServiceTable ) == FALSE )
      {
         m_ErrorCode = ::GetLastError();
         WFCTRACEERROR( m_ErrorCode );
         return_value = FALSE;
         LogEvent();
      }

      return( return_value );
   }
   catch( ... )
   {
      m_ErrorCode = ERROR_EXCEPTION_IN_SERVICE;
      return( FALSE );
   }
}

#pragma warning( disable : 4100 )

void CService::LogEvent( WORD event_type, LPTSTR message_string, DWORD error_code )
{
   WFCLTRACEINIT( TEXT( "CService::LogEvent()" ) );

   CEventLog log( m_ServiceName );

   LPTSTR strings[ 1 ];

   strings[ 0 ] = message_string;

   log.Report( (CEventLog::EventType) event_type, 0, 0, 1, (LPCTSTR *) strings );
}

// I shouldn't have to put this here but WINUSER.H wasn't doing it right...
#ifdef _WIN32_WINNT
#if (_WIN32_WINNT >= 0x0400)
#define MB_SERVICE_NOTIFICATION          0x00200000L
#else
#define MB_SERVICE_NOTIFICATION          0x00040000L
#endif
#define MB_SERVICE_NOTIFICATION_NT3X     0x00040000L
#endif

#pragma warning( default : 4100 )

int CService::MessageBox( LPCTSTR text, LPCTSTR caption, UINT type )
{
   WFCLTRACEINIT( TEXT( "CService::MessageBox()" ) );

   COperatingSystemVersionInformation version_information;

   if ( ::GetVersionEx( version_information ) != FALSE )
   {
      if ( version_information.dwMajorVersion <= 3 )
      {
         type |= MB_SERVICE_NOTIFICATION_NT3X;
      }
      else
      {
         type |= MB_SERVICE_NOTIFICATION;
      }
   }
   else
   {
      WFCTRACE( TEXT( "Can't get operating system version information." ) );
   }

   int return_value = 0;

   return_value = ::MessageBox( NULL, text, caption, type );

   return( return_value );
}

void CService::OnContinue( void )
{
   WFCLTRACEINIT( TEXT( "CService::OnContinue()" ) );
   CEventLog log( m_ServiceName );
   log.ReportInformation( TEXT( "Service Resumed" ) );
}

void CService::OnControlCode( DWORD /* control_code */ )
{
   WFCLTRACEINIT( TEXT( "CService::OnControlCode()" ) );
   // default implementation
   // handle user-defined control codes (128 - 255 inclusive)
}

void CService::OnPause( void )
{
   WFCLTRACEINIT( TEXT( "CService::OnPause()" ) );
   CEventLog log( m_ServiceName );
   log.ReportInformation( TEXT( "Service Paused" ) );
}

BOOL CService::OnPrepareServiceThread( void )
{
   WFCLTRACEINIT( TEXT( "CService::OnPrepareServiceThread()" ) );
   return( TRUE );
}

void CService::OnShutdown( void )
{
   WFCLTRACEINIT( TEXT( "CService::OnShutdown()" ) );
}

void CService::OnStop( void )
{
   WFCLTRACEINIT( TEXT( "CService::OnStop()" ) );
}

void CService::ParseCommandLineParameters( DWORD number_of_command_line_arguments, LPTSTR *command_line_arguments )
{
   WFCLTRACEINIT( TEXT( "CService::ParseCommandLineParameters()" ) );

   DWORD argument_number = 0;

   CommandLineParameters.RemoveAll();

   while( argument_number < number_of_command_line_arguments )
   {
      CommandLineParameters.Add( command_line_arguments[ argument_number ] );
      argument_number++;
   }

   // default implementation
   // parse command line parameters passed via SCM through ServiceMain

   argument_number = 1;

   while( argument_number < number_of_command_line_arguments )
   {
      if ( command_line_arguments[ argument_number ][ 0 ] == TEXT( '-' ) ||
           command_line_arguments[ argument_number ][ 0 ] == TEXT( '/' ) )
      {
         switch( command_line_arguments[ argument_number ][ 1 ] )
         {
            case TEXT( 'd' ):
            case TEXT( 'D' ):

               ::EnterCriticalSection( &g_ServiceCriticalSection );
               m_Debugging = 1;
               ::LeaveCriticalSection( &g_ServiceCriticalSection );

               break;

            case TEXT( 'i' ):
            case TEXT( 'I' ):

               TCHAR message_string[ 80 ];

               _stprintf( message_string, TEXT( "pid %#lx %ld" ), ::GetCurrentProcessId(), ::GetCurrentProcessId() );
               ::MessageBox( NULL, message_string, m_ServiceName, MB_OK );

               break;

            default:

               break;
        }
      }

      argument_number++;
   }
}

BOOL CService::SendStatusToServiceControlManager( DWORD current_state, 
                                                  DWORD win32_exit_code,
                                                  DWORD check_point,
                                                  DWORD wait_hint,
                                                  DWORD service_specific_code )
{
   WFCLTRACEINIT( TEXT( "CService::SendStatusToServiceControlManager()" ) );

   BOOL return_value = FALSE;

   SERVICE_STATUS service_status;

   ::ZeroMemory( &service_status, sizeof( service_status ) );

   // initialize service_status and send it to SCM

   if ( current_state == SERVICE_START_PENDING )
   {
      service_status.dwControlsAccepted = 0;
   }
   else
   {
      service_status.dwControlsAccepted = m_ControlsAccepted;
   }

   if ( service_specific_code == 0 )
   {
      service_status.dwWin32ExitCode = win32_exit_code;
   }
   else
   {
      service_status.dwWin32ExitCode = ERROR_SERVICE_SPECIFIC_ERROR;
   }

   service_status.dwServiceType             = SERVICE_WIN32_OWN_PROCESS;
   service_status.dwCurrentState            = current_state;
   service_status.dwServiceSpecificExitCode = service_specific_code;
   service_status.dwCheckPoint              = check_point;
   service_status.dwWaitHint                = wait_hint;

#if defined( _DEBUG )
   DumpStatus( &service_status );
#endif

   return_value = ::SetServiceStatus( m_ServiceStatusHandle, &service_status );

   if ( return_value == FALSE )
   {
      m_ErrorCode = ::GetLastError();
      WFCTRACEERROR( m_ErrorCode );
      LogEvent();
      Exit();
   }

   return( return_value );
}

void CALLBACK CService::ServiceControlManagerHandler( DWORD control_code )
{
   WFCLTRACEINIT( TEXT( "CService::ServiceControlManagerHandler()" ) );

   // entry point for service called by SCM after service is started

   ASSERT( m_StaticService_p != 0 );

   switch( control_code )
   {
      case SERVICE_CONTROL_STOP:

         WFCTRACEVAL( TEXT( "Handling SERVICE_CONTROL_STOP ThreadID " ), ::GetCurrentThreadId() );

         m_StaticService_p->SendStatusToServiceControlManager( SERVICE_STOP_PENDING, NO_ERROR, 1, m_StaticService_p->m_WaitHint );

         ::EnterCriticalSection( &g_ServiceCriticalSection );
         m_StaticService_p->m_Running      = FALSE;
         m_StaticService_p->m_CurrentState = SERVICE_STOPPED;
         ::LeaveCriticalSection( &g_ServiceCriticalSection );

         m_StaticService_p->OnStop();
         m_StaticService_p->Exit();

         return;

      case SERVICE_CONTROL_PAUSE:

         WFCTRACEVAL( TEXT( "Handling SERVICE_CONTROL_PAUSE ThreadID " ), ::GetCurrentThreadId() );

         if ( m_StaticService_p->m_Running != FALSE && m_StaticService_p->m_Paused == FALSE )
         {
            if ( m_StaticService_p->SendStatusToServiceControlManager( SERVICE_PAUSE_PENDING, NO_ERROR, 1, m_StaticService_p->m_WaitHint ) == FALSE )
            {
               return;
            }

            ::EnterCriticalSection( &g_ServiceCriticalSection );
            m_StaticService_p->m_Paused = TRUE;
            ::LeaveCriticalSection( &g_ServiceCriticalSection );

            m_StaticService_p->OnPause();
            ::SuspendThread( m_StaticService_p->m_ThreadHandle );

            ::EnterCriticalSection( &g_ServiceCriticalSection );
            m_StaticService_p->m_CurrentState = SERVICE_PAUSED;
            ::LeaveCriticalSection( &g_ServiceCriticalSection );
         }

         break;

      case SERVICE_CONTROL_CONTINUE:

         WFCTRACEVAL( TEXT( "Handling SERVICE_CONTROL_CONTINUE ThreadID " ), ::GetCurrentThreadId() );

         if ( m_StaticService_p->m_Running != FALSE && m_StaticService_p->m_Paused != FALSE )
         {
            if ( m_StaticService_p->SendStatusToServiceControlManager( SERVICE_CONTINUE_PENDING, NO_ERROR, 1, m_StaticService_p->m_WaitHint ) == FALSE )
            {
               return;
            }

            ::EnterCriticalSection( &g_ServiceCriticalSection );
            m_StaticService_p->m_Paused = FALSE;
            ::LeaveCriticalSection( &g_ServiceCriticalSection );

            ::ResumeThread( m_StaticService_p->m_ThreadHandle );
            m_StaticService_p->OnContinue();

            ::EnterCriticalSection( &g_ServiceCriticalSection );
            m_StaticService_p->m_CurrentState = SERVICE_RUNNING;
            ::LeaveCriticalSection( &g_ServiceCriticalSection );
         }

         break;

      case SERVICE_CONTROL_INTERROGATE:

         WFCTRACEVAL( TEXT( "Handling SERVICE_CONTROL_INTERROGATE ThreadID " ), ::GetCurrentThreadId() );
         break;

      case SERVICE_CONTROL_SHUTDOWN:

         WFCTRACEVAL( TEXT( "Handling SERVICE_CONTROL_SHUTDOWN ThreadID " ), ::GetCurrentThreadId() );

         m_StaticService_p->SendStatusToServiceControlManager( SERVICE_STOP_PENDING, NO_ERROR, 1, m_StaticService_p->m_WaitHint );

         ::EnterCriticalSection( &g_ServiceCriticalSection );
         m_StaticService_p->m_Running      = FALSE;
         m_StaticService_p->m_CurrentState = SERVICE_STOPPED;
         ::LeaveCriticalSection( &g_ServiceCriticalSection );

         m_StaticService_p->OnShutdown();
         m_StaticService_p->Exit();

         return;

      default:

         WFCTRACEVAL( TEXT( "Handling user-defined control code " ), control_code );
         m_StaticService_p->OnControlCode( control_code );

         break;
   }

   m_StaticService_p->SendStatusToServiceControlManager( m_StaticService_p->m_CurrentState );
}

void CALLBACK CService::ServiceMain( DWORD number_of_command_line_arguments, LPTSTR *command_line_arguments )
{
   WFCLTRACEINIT( TEXT( "CService::ServiceMain()" ) );

   // entry point for service called by SCM when service is started

   HANDLE thread_handle = NULL;

   ASSERT( m_StaticService_p != NULL );

   WFCTRACEVAL( TEXT( "ServiceMain ThreadID = " ), ::GetCurrentThreadId() );

   ::EnterCriticalSection( &g_ServiceCriticalSection );
   m_StaticService_p->m_ServiceStatusHandle = ::RegisterServiceCtrlHandler( m_StaticService_p->m_ServiceName, ServiceControlManagerHandler );
   ::LeaveCriticalSection( &g_ServiceCriticalSection );

   if ( m_StaticService_p->m_ServiceStatusHandle == (SERVICE_STATUS_HANDLE) 0 )
   {
      m_StaticService_p->m_ErrorCode = ::GetLastError();
      m_StaticService_p->LogEvent();
      m_StaticService_p->Exit();
   }
   else
   {
      if ( ! m_StaticService_p->SendStatusToServiceControlManager( SERVICE_START_PENDING, NO_ERROR, 1, m_StaticService_p->m_WaitHint ) )
      {
         goto EXIT_GOTO;
      }

      ::EnterCriticalSection( &g_ServiceCriticalSection );
      m_StaticService_p->m_ExitEventHandle = ::CreateEvent( 0, TRUE, FALSE, 0 );
      ::LeaveCriticalSection( &g_ServiceCriticalSection );

      if ( m_StaticService_p->m_ExitEventHandle == NULL )
      {
         m_StaticService_p->m_ErrorCode = ::GetLastError();
         m_StaticService_p->LogEvent();
         m_StaticService_p->Exit();
      }
      else
      {
         if ( ! m_StaticService_p->SendStatusToServiceControlManager( SERVICE_START_PENDING, NO_ERROR, 2, m_StaticService_p->m_WaitHint ) )
         {
            goto EXIT_GOTO;
         }

         m_StaticService_p->ParseCommandLineParameters( number_of_command_line_arguments, command_line_arguments );

         if ( ! m_StaticService_p->SendStatusToServiceControlManager( SERVICE_START_PENDING, NO_ERROR, 3, m_StaticService_p->m_WaitHint ) )
         {
            goto EXIT_GOTO;
         }

         if ( m_StaticService_p->OnPrepareServiceThread() != FALSE )
         {
            // Daniel Meyer (Daniel.Meyer@Digital.com) had an awsome
            // suggestion here. Change CreateThread() to _beginthreadex()
            // so the C Runtime will work correctly. Now why didn't I think
            // of that???

            thread_handle = reinterpret_cast< HANDLE >( ::_beginthreadex( 0, // Security Context
                                            0, // Default Stack Size
                                            reinterpret_cast< unsigned int (__stdcall *)( void *) >( m_StaticService_p->m_ThreadStartRoutine ),
                                            m_StaticService_p,
                                            0,
                                           reinterpret_cast< unsigned int * >( &m_StaticService_p->m_ThreadId ) ) );

            ::EnterCriticalSection( &g_ServiceCriticalSection );
            m_StaticService_p->m_ThreadHandle = thread_handle;
            ::LeaveCriticalSection( &g_ServiceCriticalSection );

            if ( m_StaticService_p->m_ThreadHandle == NULL )
            {
               m_StaticService_p->m_ErrorCode = ::GetLastError();
               m_StaticService_p->LogEvent();
               m_StaticService_p->Exit();
            }
            else
            {
               ::EnterCriticalSection( &g_ServiceCriticalSection );
               m_StaticService_p->m_Running = TRUE;
               ::LeaveCriticalSection( &g_ServiceCriticalSection );

               if ( m_StaticService_p->SendStatusToServiceControlManager( SERVICE_RUNNING ) == FALSE )
               {
                  return;
               }

               ::EnterCriticalSection( &g_ServiceCriticalSection );
               m_StaticService_p->m_CurrentState = SERVICE_RUNNING;
               ::LeaveCriticalSection( &g_ServiceCriticalSection );

               ::WaitForSingleObject( m_StaticService_p->m_ExitEventHandle, INFINITE );

               // Thanks to Daniel Meyer (Daniel.Meyer@Digital.com) for finding a bug here
               ::CloseHandle( m_StaticService_p->m_ThreadHandle );
            }
         }

EXIT_GOTO:

         // notify SCM that service has stopped

         ASSERT( m_StaticService_p != 0 );

         if ( m_StaticService_p->m_ServiceStatusHandle != 0 )
         {
            m_StaticService_p->SendStatusToServiceControlManager( SERVICE_STOPPED, m_StaticService_p->m_ErrorCode );
         }
      }
   }
}

// End of source

#if 0
<HTML>

<HEAD>
<TITLE>WFC - CService</TITLE>
<META name="keywords" content="WFC, MFC extension library, freeware class library, Win32, source code">
<META name="description" content="The C++ class that makes it easy to create NT services.">
</HEAD>

<BODY>

<H1>CService</H1>
$Revision: 35 $
<HR>

<H2>Description</H2>

This class makes it easy to create Services. This class is not well suited
to handle multiple services in a single process space. This class assumes
one service per process.

<H2>Data Members</H2>

<B>m_StaticService_p</B> - A static variable that holds a pointer to
the class (this).<P>
<B>CommandLineParameters</B> - A CStringArray that holds the command
line arguments when the service was started.

<H2>Methods</H2>

<DL COMPACT>

<DT><PRE>int <B>DialogBoxParam</B>( HINSTANCE instance, LPCTSTR template_name, HWND parent_window, DLGPROC dialogbox_procedure, LPARAM lParam = 0 )</PRE><DD>
Displays a dialog box from an interactive service.

<DT><PRE>BOOL <B>Initialize</B>( LPCTSTR name_of_service )</PRE><DD>
Initializes the service.

<DT><PRE>void <B>LogEvent</B>( WORD EventType = EVENTLOG_ERROR_TYPE, LPTSTR message_string = NULL, DWORD error_code = NO_ERROR )</PRE><DD>
Makes an entry in the Event Log for this service.

<DT><PRE>int <B>MessageBox</B>( LPCTSTR text, LPCTSTR caption, UINT type )</PRE><DD>
Displays a message box for interactive services.

</DL>

<H2>Example</H2>

<PRE><CODE>#include &lt;wfc.h&gt;
#include &quot;messages.h&quot;
#pragma hdrstop

DWORD WINAPI worker_thread( LPVOID pointer_to_parent_CService_class );
VOID set_default_parameters( void );

int __cdecl _tmain( int number_of_command_line_arguments, LPCTSTR command_line_arguments[] )
{
   <A HREF="WfcTrace.htm">WFCTRACEINIT</A>( TEXT( &quot;_tmain()&quot; ) );

   if ( number_of_command_line_arguments == 1 )
   {
      <B>CService</B> service( worker_thread );
      service.Initialize( TEXT( &quot;WatchDog&quot; ) );
      return( EXIT_SUCCESS );
   }

   if ( number_of_command_line_arguments == 2 )
   {
      if ( _tcsicmp( command_line_arguments[ 1 ], TEXT( &quot;install&quot; ) ) == 0 )
      {
         <A HREF="CSvcMgr.htm">CServiceControlManager</A> service_control_manager;

         service_control_manager.Open();

         if ( service_control_manager.Install( TEXT( &quot;WatchDog&quot; ),
                                               TEXT( &quot;WatchDog&quot; ),
            TEXT( &quot;%SystemRoot%\\System32\\WatchDog.exe&quot; ) ) == FALSE )
         {
            _tprintf( TEXT( &quot;Install failed, please see Application Log for details\n&quot; ) );
         }

         set_default_parameters();

         return( EXIT_SUCCESS );
      }
      else if ( _tcsicmp( command_line_arguments[ 1 ], TEXT( &quot;remove&quot; ) ) == 0 )
      {
         <A HREF="CSvcMgr.htm">CServiceControlManager</A> service_control_manager;

         service_control_manager.Open();

         if ( service_control_manager.Remove( TEXT( &quot;WatchDog&quot; ) ) == FALSE )
         {
            _tprintf( TEXT( &quot;Removing failed, please see Application Log for details\n&quot; ) );
         }

         return( EXIT_SUCCESS );
      }
      else if ( _tcsicmp( command_line_arguments[ 1 ], TEXT( &quot;run&quot; ) ) == 0 )
      {
         worker_thread( (LPVOID) 1 );
         return( EXIT_SUCCESS );
      }
      else
      {
         _tprintf( TEXT( &quot;Samuel R. Blackburn, WFC Sample Application\nUsage: %s [install|remove]\n&quot; ), command_line_arguments[ 0 ] );
      }
   }
   else
   {
      _tprintf( TEXT( &quot;Samuel R. Blackburn, WFC Sample Application\nUsage: %s [install|remove]\n&quot; ), command_line_arguments[ 0 ] );
   }

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

<H2>API's Used</H2>

<DL COMPACT>
<LI>CreateEvent
<LI>CreateThread
<LI>DeleteCriticalSection
<LI>DialogBoxParam
<LI>EnterCriticalSection
<LI>GetCurrentThreadId
<LI>GetLastError
<LI>GetThreadDesktop
<LI>GetVersionEx
<LI>InitializeCriticalSection
<LI>LeaveCriticalSection
<LI>MessageBox
<LI>OpenInputDesktop
<LI>RegisterServiceCtrlHandler
<LI>ResumeThread
<LI>SetEvent
<LI>SetServiceStatus
<LI>SetThreadDesktop
<LI>StartServiceCtrlDispatcher
<LI>SuspendThread
<LI>WaitForSingleObject
</DL>

<HR><I>Copyright, 2000, <A HREF="mailto:wfc@pobox.com">Samuel R. Blackburn</A></I><BR>
$Workfile: cservice.cpp $<BR>
$Modtime: 1/17/00 9:13a $
</BODY>

</HTML>
#endif
