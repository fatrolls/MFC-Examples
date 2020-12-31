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
** $Workfile: csvcmgr.cpp $
** $Revision: 43 $
** $Modtime: 4/01/00 8:45a $
** $Reuse Tracing Code: 1 $
*/

#if defined( _DEBUG ) && ! defined( WFC_STL )
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif // _DEBUG

CServiceControlManager::CServiceControlManager()
{
   WFCLTRACEINIT( TEXT( "CServiceControlManager::CServiceControlManager()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   m_Initialize();
}

CServiceControlManager::~CServiceControlManager()
{
   WFCLTRACEINIT( TEXT( "CServiceControlManager::~CServiceControlManager()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );

   Close();

   if ( m_Buffer != NULL )
   {
      WFCTRACE( TEXT( "Freeing buffer" ) );
      delete [] m_Buffer;
      m_Buffer     = reinterpret_cast< ENUM_SERVICE_STATUS * >( NULL );
      m_BufferSize = 0;
   }
}

void CServiceControlManager::Close( void )
{
   WFCLTRACEINIT( TEXT( "CServiceControlManager::Close()" ) );

   // We don't want to close while the database is locked

   UnlockDatabase();

   if ( m_ManagerHandle != NULL )
   {
      WFCTRACE( TEXT( "Closing manager handle" ) );

      if ( ::CloseServiceHandle( m_ManagerHandle ) == FALSE )
      {
         m_ErrorCode = ::GetLastError();
         WFCTRACEERROR( m_ErrorCode );
      }

      m_ManagerHandle = reinterpret_cast< SC_HANDLE >( NULL );
   }
}

BOOL CServiceControlManager::Continue( LPCTSTR service_name )
{
   WFCLTRACEINIT( TEXT( "CServiceControlManager::Continue()" ) );
   ASSERT( service_name != NULL );

   if ( m_ManagerHandle == NULL )
   {
      WFCTRACE( TEXT( "manager handle is NULL" ) );
      m_ErrorCode = ERROR_INVALID_HANDLE;
      return( FALSE );
   }

   if ( service_name == NULL )
   {
      WFCTRACE( TEXT( "service name is NULL" ) );
      m_ErrorCode = ERROR_INVALID_HANDLE;
      return( FALSE );
   }

   // We were passed a pointer, don't trust it

   try
   {
      SC_HANDLE service_handle = ::OpenService( m_ManagerHandle, service_name, SERVICE_PAUSE_CONTINUE );

      if ( service_handle == (SC_HANDLE) NULL )
      {
         WFCTRACE( TEXT( "Can't open service" ) );
         m_ErrorCode = ::GetLastError();
         WFCTRACEERROR( m_ErrorCode );
         return( FALSE );
      }

      SERVICE_STATUS service_status;

      ::ZeroMemory( &service_status, sizeof( service_status ) );

      BOOL return_value = ::ControlService( service_handle, SERVICE_CONTROL_CONTINUE, &service_status );

      if ( return_value == FALSE )
      {
         m_ErrorCode = ::GetLastError();
         WFCTRACEERROR( m_ErrorCode );
      }
      else
      {
         return_value = TRUE;
      }

      ::CloseServiceHandle( service_handle );

      // 2000-03-17
      // Thanks go to Steve Loughran (steve@iseran.com) for finding a bug
      // where I wasn't casting INVALID_HANDLE_VALUE to SC_HANDLE.

      service_handle = (SC_HANDLE) INVALID_HANDLE_VALUE;

      return( return_value );
   }
   catch( ... )
   {
      m_ErrorCode = ERROR_EXCEPTION_IN_SERVICE;
      return( FALSE );
   }
}

BOOL CServiceControlManager::EnableInteractiveServices( BOOL enable_interactive_services )
{
   WFCLTRACEINIT( TEXT( "CServiceControlManager::EnableInteractiveServices()" ) );

   BOOL return_value = TRUE;

   CRegistry registry;

   if ( m_MachineName.GetLength() == 0 )
   {
      return_value = registry.Connect( HKEY_LOCAL_MACHINE );
   }
   else
   {
      return_value = registry.Connect( HKEY_LOCAL_MACHINE, m_MachineName );
   }

   if ( return_value == FALSE )
   {
      m_ErrorCode = registry.GetErrorCode();
      WFCTRACE( TEXT( "Can't connect to registry" ) );
      return( FALSE );
   }

   CString sub_key_name( TEXT( "System\\CurrentControlSet\\Control\\Windows" ) );

   return_value = registry.Open( sub_key_name );

   if ( return_value == FALSE )
   {
      m_ErrorCode = registry.GetErrorCode();
      WFCTRACEVAL( TEXT( "Can't open sub-key " ), sub_key_name );
      return( FALSE );
   }

   DWORD no_interactive_services = 0;

   if ( enable_interactive_services != FALSE )
   {
      // Allow interactive services
      no_interactive_services = 0;
   }
   else
   {
      // Do not allow interactive services
      no_interactive_services = 1;
   }

   if ( registry.SetValue( TEXT( "NoInteractiveServices" ), no_interactive_services ) == FALSE )
   {
      m_ErrorCode = registry.GetErrorCode();
      WFCTRACEVAL( TEXT( "Can't set NoInteractiveServices value to " ), no_interactive_services );
      return( FALSE );
   }

   return( TRUE );
}

BOOL CServiceControlManager::EnumerateStatus( DWORD state, DWORD type )
{
   WFCLTRACEINIT( TEXT( "CServiceControlManager::EnumerateStatus()" ) );

   /*
   ** For GetNext() calls
   */

   if ( m_ManagerHandle == NULL )
   {
      WFCTRACE( TEXT( "manager handle is NULL" ) );
      m_ErrorCode = ERROR_INVALID_HANDLE;
      return( FALSE );
   }

   if ( m_Buffer == NULL )
   {
      WFCTRACE( TEXT( "Allocating buffer" ) );

      m_BufferSize = 2 * sizeof( ENUM_SERVICE_STATUS );

      m_Buffer = (ENUM_SERVICE_STATUS *) new BYTE[ m_BufferSize ];

      if ( m_Buffer == NULL )
      {
         m_BufferSize = 0;
         m_ErrorCode = ::GetLastError();
         WFCTRACEERROR( m_ErrorCode );
         return( FALSE );
      }
   }

   DWORD number_of_bytes_needed      = 0;
   DWORD number_of_services_returned = 0;
   DWORD resume_handle               = 0;

   if ( ::EnumServicesStatus( m_ManagerHandle,
                              type,
                              state,
                              m_Buffer,
                              m_BufferSize,
                             &number_of_bytes_needed,
                             &number_of_services_returned,
                             &resume_handle ) != FALSE )
   {
      m_CurrentEntryNumber = 0;
      m_NumberOfEntries    = number_of_services_returned;

      return( TRUE );
   }

   m_ErrorCode = ::GetLastError();
   WFCTRACEERROR( m_ErrorCode );

   if ( m_ErrorCode == ERROR_MORE_DATA )
   {
      WFCTRACE( TEXT( "Buffer too small, increasing now" ) );

      delete [] m_Buffer;

      // Thanks go to Ullrich Pollaehne [Ullrich_Pollaehne@ka2.maus.de]
      // for finding a serious flaw in my logic here.

      m_Buffer = (ENUM_SERVICE_STATUS *) new BYTE[ number_of_bytes_needed + m_BufferSize ];

      if ( m_Buffer != NULL )
      {
         m_BufferSize += number_of_bytes_needed;
      }
      else
      {
         m_ErrorCode = ::GetLastError();
         WFCTRACEVAL( TEXT( "Can't allocate buffer whose size is " ), number_of_bytes_needed );
         return( FALSE );
      }

      number_of_bytes_needed      = 0;
      number_of_services_returned = 0;
      resume_handle               = 0;

      if ( ::EnumServicesStatus( m_ManagerHandle,
                                 type,
                                 state,
                                 m_Buffer,
                                 m_BufferSize,
                                &number_of_bytes_needed,
                                &number_of_services_returned,
                                &resume_handle ) != FALSE )
      {
         m_CurrentEntryNumber = 0;
         m_NumberOfEntries    = number_of_services_returned;

         return( TRUE );
      }
      else
      {
         m_ErrorCode = ::GetLastError();
         WFCTRACEERROR( m_ErrorCode );

         m_CurrentEntryNumber = 0;
         m_NumberOfEntries    = 0;

         WFCTRACEVAL( TEXT( "Still can't get data with a buffer size of " ), m_BufferSize );

         return( FALSE );
      }
   }

   WFCTRACE( TEXT( "Returning default of FALSE" ) );

   return( FALSE );
}

BOOL CServiceControlManager::GetConfiguration( LPCTSTR service_name, CServiceConfiguration& configuration )
{
   WFCLTRACEINIT( TEXT( "CServiceControlManager::GetConfiguration()" ) );
   ASSERT( service_name != NULL );

   if ( service_name == NULL )
   {
      WFCTRACE( TEXT( "service_name is NULL" ) );
      m_ErrorCode = ERROR_INVALID_PARAMETER;
      return( FALSE );
   }

   // We were passed a pointer, don't trust it

   try
   {
      ASSERT( m_ManagerHandle != NULL );

      if ( m_ManagerHandle == NULL )
      {
         WFCTRACE( TEXT( "manager handle is NULL" ) );
         m_ErrorCode = ERROR_INVALID_HANDLE;

         return( FALSE );
      }

      configuration.Empty();

      SC_HANDLE service_handle = ::OpenService( m_ManagerHandle, service_name, SERVICE_QUERY_CONFIG );

      if ( service_handle == (SC_HANDLE) NULL )
      {
         m_ErrorCode = ::GetLastError();
         WFCTRACE( TEXT( "Can't OpenService" ) );
         WFCTRACEERROR( m_ErrorCode );
         return( FALSE );
      }

      BYTE * buffer = reinterpret_cast< BYTE * >( NULL );
      
      try
      {
         buffer = new BYTE[ 4000 ];
      }
      catch( ... )
      {
         buffer = reinterpret_cast< BYTE * >( NULL );
      }

      if ( buffer == NULL )
      {
         return( FALSE );
      }

      DWORD number_of_bytes_needed = 0;

      BOOL return_value = ::QueryServiceConfig( service_handle, 
                       (QUERY_SERVICE_CONFIG *) buffer,
                                                4000,
                                               &number_of_bytes_needed );

      if ( return_value == FALSE )
      {
         m_ErrorCode = ::GetLastError();
         WFCTRACEERROR( m_ErrorCode );

         if ( m_ErrorCode == ERROR_INSUFFICIENT_BUFFER )
         {
#if ! defined( WFC_STL )
            TRACE( TEXT( "CServiceControlManager::GetConfiguration() line %d, Sent in a buffer of %lu bytes, needed %lu bytes (%lu more)\n" ),
                   __LINE__,
                   4000,
                   (DWORD) number_of_bytes_needed,
                   (DWORD) number_of_bytes_needed - 4000 ); 
#endif
         }
      }
      else
      {
         return_value = TRUE;
         QUERY_SERVICE_CONFIG * service_configuration_p = (QUERY_SERVICE_CONFIG *) buffer;
         configuration.Copy( service_configuration_p );
      }

      delete [] buffer;
      buffer = reinterpret_cast< BYTE * >( NULL );

      ::CloseServiceHandle( service_handle );

      return( return_value );
   }
   catch( ... )
   {
      m_ErrorCode = ERROR_EXCEPTION_IN_SERVICE;
      return( FALSE );
   }
}

BOOL CServiceControlManager::GetDependencies( LPCTSTR service_name, CStringArray& dependencies )
{
   WFCLTRACEINIT( TEXT( "CServiceControlManager::GetDependencies()" ) );
   ASSERT( m_ManagerHandle != NULL );

   dependencies.RemoveAll();

   SC_HANDLE service_handle = reinterpret_cast< SC_HANDLE >( NULL );

   // We were passed a pointer, don't trust it

   try
   {
      service_handle = ::OpenService( m_ManagerHandle, service_name, SERVICE_ENUMERATE_DEPENDENTS );

      if ( service_handle == NULL )
      {
         m_ErrorCode = ::GetLastError();
         WFCTRACEERROR( m_ErrorCode );
         return( FALSE );
      }

      DWORD number_of_services_returned = 0;
      DWORD number_of_bytes_needed      = 0;
      DWORD buffer_size                 = 0;

      ENUM_SERVICE_STATUS * status_array = reinterpret_cast< ENUM_SERVICE_STATUS * >( NULL );

      try
      {
         status_array = new ENUM_SERVICE_STATUS[ 512 ]; // an insane amount
      }
      catch( ... )
      {
         status_array = reinterpret_cast< ENUM_SERVICE_STATUS * >( NULL );
      }

      if ( status_array == NULL )
      {
         m_ErrorCode = ERROR_NOT_ENOUGH_MEMORY;
         ::CloseServiceHandle( service_handle );

         return( FALSE );
      }

      buffer_size = 512 * sizeof( ENUM_SERVICE_STATUS );

      ZeroMemory( status_array, buffer_size );

      BOOL return_value = FALSE;

      return_value = ::EnumDependentServices( service_handle,
                                              SERVICE_STATE_ALL, // Both running and stopped services
                                              status_array,
                                              buffer_size,
                                             &number_of_bytes_needed,
                                             &number_of_services_returned );
      if ( return_value != FALSE )
      {
         DWORD index = 0;

         while( index < number_of_services_returned )
         {
            dependencies.Add( status_array[ index ].lpServiceName );
            index++;
         }
      }

      delete [] status_array;
      status_array = reinterpret_cast< ENUM_SERVICE_STATUS * >( NULL );

      ::CloseServiceHandle( service_handle );

      return( return_value );
   }
   catch( ... )
   {
      m_ErrorCode = ERROR_EXCEPTION_IN_SERVICE;
      return( FALSE );
   }
}

BOOL CServiceControlManager::GetDisplayName( LPCTSTR key_name, CString& display_name )
{
   WFCLTRACEINIT( TEXT( "CServiceControlManager::GetDisplayName()" ) );
   ASSERT( m_ManagerHandle != NULL );

   // We were passed a pointer, don't trust it

   try
   {
      display_name.Empty();

      BOOL return_value = FALSE;

      DWORD buffer_size = 8192; // insanely large buffer

      LPTSTR display_string = reinterpret_cast< LPTSTR >( NULL );

      try
      {
         display_string = new TCHAR[ buffer_size ];
      }
      catch( ... )
      {
         display_string = reinterpret_cast< LPTSTR >( NULL );
      }

      if ( display_string == NULL )
      {
         return( FALSE );
      }

      return_value = ::GetServiceDisplayName( m_ManagerHandle,
                                              key_name,
                                              display_string,
                                             &buffer_size );
      if ( return_value != FALSE )
      {
         display_name = display_string;
      }
      else
      {
         m_ErrorCode = ::GetLastError();
         WFCTRACEERROR( m_ErrorCode );
      }

      delete [] display_string;
      display_string = reinterpret_cast< LPTSTR >( NULL );

	  if ( return_value == FALSE )
	  {
		  return( FALSE );
	  }

	  return( TRUE );
   }
   catch( ... )
   {
      m_ErrorCode = ERROR_EXCEPTION_IN_SERVICE;
      return( FALSE );
   }
}

DWORD CServiceControlManager::GetErrorCode( void ) const
{
   WFCLTRACEINIT( TEXT( "CServiceControlManager::GetErrorCode()" ) );
   return( m_ErrorCode );
}

SC_HANDLE CServiceControlManager::GetHandle( void ) const
{
   return( m_ManagerHandle );
}

BOOL CServiceControlManager::GetKeyName( LPCTSTR display_name, CString& key_name )
{
   WFCLTRACEINIT( TEXT( "CServiceControlManager::GetKeyName()" ) );
   ASSERT( m_ManagerHandle != NULL );

   // We were passed a pointer, don't trust it

   try
   {
      key_name.Empty();

      BOOL return_value = FALSE;

      DWORD buffer_size = 8192; // insanely large buffer

      LPTSTR key_string = reinterpret_cast< LPTSTR >( NULL );

      try
      {
         key_string = new TCHAR[ buffer_size ];
      }
      catch( ... )
      {
         key_string = reinterpret_cast< LPTSTR >( NULL );
      }

      if ( key_string == NULL )
      {
         return( FALSE );
      }

      return_value = ::GetServiceKeyName( m_ManagerHandle,
                                          display_name,
                                          key_string,
                                         &buffer_size );
      if ( return_value != FALSE )
      {
         key_name = key_string;
      }
      else
      {
         m_ErrorCode = ::GetLastError();
         WFCTRACEERROR( m_ErrorCode );
      }

      delete [] key_string;
      key_string = reinterpret_cast< LPTSTR >( NULL );

   	  if ( return_value == FALSE )
	  {
		  return( FALSE );
	  }

	  return( TRUE );
   }
   catch( ... )
   {
      m_ErrorCode = ERROR_EXCEPTION_IN_SERVICE;
      return( FALSE );
   }
}

BOOL CServiceControlManager::GetNext( CServiceNameAndStatus& status )
{
   WFCLTRACEINIT( TEXT( "CServiceControlManager::GetNext()" ) );

   if ( m_CurrentEntryNumber < m_NumberOfEntries )
   {
      status.Copy( &m_Buffer[ m_CurrentEntryNumber ] );
      m_CurrentEntryNumber++;
      return( TRUE );
   }

   return( FALSE );
}

BOOL CServiceControlManager::Install( LPCTSTR service_name, LPCTSTR friendly_name, LPCTSTR name_of_executable_file )
{
   WFCLTRACEINIT( TEXT( "CServiceControlManager::Install()" ) );
   ASSERT( service_name            != NULL );
   ASSERT( friendly_name           != NULL );
   ASSERT( name_of_executable_file != NULL );

   if ( service_name            == (LPCTSTR) NULL ||
        friendly_name           == (LPCTSTR) NULL ||
        name_of_executable_file == (LPCTSTR) NULL )
   {
      WFCTRACE( TEXT( "invalid parameter" ) );
      m_ErrorCode = ERROR_INVALID_PARAMETER;
      return( FALSE );
   }

   // Microsoft has a bug in NT. I know what you're thinking, "THAT'S IMPOSSIBLE"
   // The programmers at Microsoft are only human so things slip through.
   // A programmer named Lee Ott (not of Microsoft) discovered a bug while
   // debugging Tom Horsley's NTPTime program (highly recommended by me).
   // If your executable name has a space in it (like "c:\Program files\myservice.exe"
   // The service control manager will fail with helpful message of "Event ID 7000:
   // %1 Not A Valid Windows NT Application" Lee discovered that if you put
   // the exeuteable anme in quotes, it will work properly.

   CString normalized_executable_name( name_of_executable_file );

   if ( normalized_executable_name.GetLength() < 1 )
   {
      WFCTRACE( TEXT( "Executable name is empty." ) );
      m_ErrorCode = ERROR_INVALID_PARAMETER;
      return( FALSE );
   }

   if ( normalized_executable_name.Find( TEXT( " " ) ) != (-1) )
   {
      // The name contains a space. We must make sure the name is in quotes

      if ( normalized_executable_name.GetAt( 0 ) != TEXT( '\"' ) )
      {
         CString new_name( TEXT( "\"" ) );

         new_name += normalized_executable_name;
         normalized_executable_name = new_name;
      }

      if ( normalized_executable_name.GetAt( normalized_executable_name.GetLength() - 1 ) != TEXT( '\"' ) )
      {
         normalized_executable_name += TEXT( "\"" );
      }
   }

   // We were passed a pointer, don't trust it

   try
   {
      ASSERT( m_ManagerHandle != NULL );

      if ( m_ManagerHandle == NULL )
      {
         WFCTRACE( TEXT( "manager handle is NULL" ) );
         m_ErrorCode = ERROR_INVALID_HANDLE;
         return( FALSE );
      }

      DWORD supported_types = EVENTLOG_ERROR_TYPE       | 
                              EVENTLOG_WARNING_TYPE     |
                              EVENTLOG_INFORMATION_TYPE |
                              EVENTLOG_AUDIT_SUCCESS    |
                              EVENTLOG_AUDIT_FAILURE;

      // Thanks go to Patrik Sjoberg (pasjo@wmdata.com) for finding a bug here.
      // Install() would fail in unattended installations. Event logging
      // is now a non-fatal error

      CEventLog * event_log = new CEventLog;

      if ( event_log != NULL )
      {
         if ( event_log->CreateApplicationLog( service_name, normalized_executable_name, supported_types ) == FALSE )
         {
            delete event_log;
            event_log = reinterpret_cast< CEventLog * >( NULL );
         }
      }

      if ( event_log != NULL )
      {
         if ( event_log->RegisterSource( service_name ) == FALSE )
         {
            delete event_log;
            event_log = reinterpret_cast< CEventLog * >( NULL );
         }
      }

      SC_HANDLE service_handle = reinterpret_cast< SC_HANDLE >( NULL );
   
      service_handle = ::CreateService( m_ManagerHandle,
                                        service_name,
                                        friendly_name,
                                        SERVICE_ALL_ACCESS,
                                        SERVICE_WIN32_OWN_PROCESS,
                                        SERVICE_DEMAND_START,
                                        SERVICE_ERROR_NORMAL,
                                        normalized_executable_name,
                                        NULL,
                                        NULL,
                                        TEXT( "EventLog\0\0" ),
                                        NULL,
                                        NULL );

      if ( service_handle == (SC_HANDLE) NULL )
      {
         m_ErrorCode = ::GetLastError();
         WFCTRACEERROR( m_ErrorCode );

         if ( event_log != NULL )
         {
            LPVOID message_buffer = reinterpret_cast< LPVOID >( NULL );

            ::FormatMessage( FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
                             NULL,
                             m_ErrorCode,
                             MAKELANGID( LANG_ENGLISH, SUBLANG_ENGLISH_US ),
                   (LPTSTR) &message_buffer,
                             0,
                             NULL );

            if ( message_buffer != NULL )
            {
               CString temp_string;

               temp_string.Format( TEXT( "Can't create service because %s at line %d of CSvcMgr.cpp" ), message_buffer, __LINE__ );

               WFCTRACE( temp_string );

               event_log->ReportError( temp_string );

               ::LocalFree( message_buffer );
               message_buffer = reinterpret_cast< LPVOID >( NULL );
            }

            delete event_log;
            event_log = reinterpret_cast< CEventLog * >( NULL );
         }

         return( FALSE );
      }

      ::CloseServiceHandle( service_handle );
      service_handle = reinterpret_cast< SC_HANDLE >( NULL );

      /*
      ** We successfully installed a new service, this is something we should log
      */

      if ( event_log != NULL )
      {
         TCHAR user_name[ 2048 ];
         TCHAR temp_string[ 2100 ];

         DWORD size_of_user_name = DIMENSION_OF( user_name );

         ::ZeroMemory( user_name,   sizeof( user_name   ) );
         ::ZeroMemory( temp_string, sizeof( temp_string ) );

         ::GetUserName( user_name, &size_of_user_name );

         _stprintf( temp_string, TEXT( "Service successfully installed by %s" ), user_name );

         event_log->ReportInformation( temp_string );

         delete event_log;
         event_log = reinterpret_cast< CEventLog * >( NULL );
      }

      return( TRUE );
   }
   catch( ... )
   {
      m_ErrorCode = ERROR_EXCEPTION_IN_SERVICE;
      return( FALSE );
   }
}

BOOL CServiceControlManager::IsDatabaseLocked( CString& who_locked_it, CTimeSpan& how_long_it_has_been_locked )
{
   WFCLTRACEINIT( TEXT( "CServiceControlManager::IsDatabaseLocked()" ) );
   ASSERT( m_ManagerHandle != NULL );

   // First, initialize the return values

   who_locked_it.Empty();
   how_long_it_has_been_locked = CTimeSpan( 0 );

   if ( m_ManagerHandle == NULL )
   {
      WFCTRACE( TEXT( "The service control manager has not been opened" ) );
      return( FALSE );
   }

   BOOL return_value = FALSE;

   DWORD buffer_size            = 8192; // insanely large buffer
   DWORD number_of_bytes_needed = 0;

   BYTE *buffer = reinterpret_cast< BYTE * >( NULL );

   try
   {
      buffer = new BYTE[ buffer_size ];
   }
   catch( ... )
   {
      buffer = reinterpret_cast< BYTE * >( NULL );
   }

   if ( buffer == NULL )
   {
      return( FALSE );
   }

   // Always always always zero buffers

   ::ZeroMemory( buffer, buffer_size );

   return_value = ::QueryServiceLockStatus( m_ManagerHandle,
              (LPQUERY_SERVICE_LOCK_STATUS) buffer,
                                            buffer_size,
                                           &number_of_bytes_needed );
   if ( return_value != FALSE )
   {
      // Get the data from the structure
      LPQUERY_SERVICE_LOCK_STATUS status_p = reinterpret_cast< LPQUERY_SERVICE_LOCK_STATUS >( buffer );

      if ( status_p->fIsLocked != 0 )
      {
         // The database is locked
         return_value = TRUE;
         who_locked_it = status_p->lpLockOwner;
         how_long_it_has_been_locked = CTimeSpan( status_p->dwLockDuration );
      }
      else
      {
         // The database is not locked
         return_value = FALSE;
      }
   }

   delete buffer;
   buffer = reinterpret_cast< BYTE * >( NULL );

   return( return_value );
}

BOOL CServiceControlManager::LockDatabase( void )
{
   WFCLTRACEINIT( TEXT( "CServiceControlManager::LockDatabase()" ) );

   if ( m_DatabaseLockHandle != NULL )
   {
      // The database is already locked, unlock it
      UnlockDatabase();
   }

   m_DatabaseLockHandle = ::LockServiceDatabase( m_ManagerHandle );

   if ( m_DatabaseLockHandle == NULL )
   {
      m_ErrorCode = ::GetLastError();

      WFCTRACE( TEXT( "Failed." ) );
      WFCTRACEERROR( m_ErrorCode );

      return( FALSE );
   }

   return( TRUE );
}

void CServiceControlManager::m_Initialize( void )
{
   WFCLTRACEINIT( TEXT( "CServiceControlManager::m_Initialize()" ) );
   m_ManagerHandle      = reinterpret_cast< SC_HANDLE >( NULL );
   m_ErrorCode          = 0;
   m_Buffer             = reinterpret_cast< ENUM_SERVICE_STATUS * >( NULL );
   m_BufferSize         = 0;
   m_CurrentEntryNumber = 0;
   m_NumberOfEntries    = 0;
   m_DatabaseLockHandle = reinterpret_cast< SC_LOCK >( NULL );
}

BOOL CServiceControlManager::Open( DWORD what_to_open, LPCTSTR database_name, LPCTSTR machine_name )
{
   WFCLTRACEINIT( TEXT( "CServiceControlManager::Open()" ) );

   /*
   ** database_name can be NULL
   */

   if ( m_ManagerHandle != NULL )
   {
      Close();
   }

   // We were passed a pointer, don't trust it

   try
   {
      if ( machine_name == NULL )
      {
         m_MachineName.Empty(); // Should go and get our machine's name
      }
      else
      {
         m_MachineName = machine_name;
      }

      m_ManagerHandle = ::OpenSCManager( machine_name, database_name, what_to_open );

      if ( m_ManagerHandle == NULL )
      {
         m_ErrorCode = ::GetLastError();
         WFCTRACEERROR( m_ErrorCode );
         return( FALSE );
      }
      else
      {
         return( TRUE );
      }
   }
   catch( ... )
   {
      m_ErrorCode = ERROR_EXCEPTION_IN_SERVICE;
      return( FALSE );
   }
}

BOOL CServiceControlManager::Pause( LPCTSTR service_name )
{
   WFCLTRACEINIT( TEXT( "CServiceControlManager::Pause()" ) );
   ASSERT( service_name != NULL );

   if ( service_name == NULL )
   {
      m_ErrorCode = ERROR_INVALID_PARAMETER;
      return( FALSE );
   }

   // We were passed a pointer, don't trust it

   try
   {
      ASSERT( m_ManagerHandle != NULL );

      if ( m_ManagerHandle == NULL )
      {
         m_ErrorCode = ERROR_INVALID_HANDLE;
         return( FALSE );
      }

      SC_HANDLE service_handle = ::OpenService( m_ManagerHandle, service_name, SERVICE_PAUSE_CONTINUE );

      if ( service_handle == (SC_HANDLE) NULL )
      {
         m_ErrorCode = ::GetLastError();
         WFCTRACEERROR( m_ErrorCode );
         return( FALSE );
      }

      SERVICE_STATUS service_status;

      ::ZeroMemory( &service_status, sizeof( service_status ) );

      BOOL return_value = ::ControlService( service_handle, SERVICE_CONTROL_PAUSE, &service_status );

      if ( return_value == FALSE )
      {
         m_ErrorCode = ::GetLastError();
         WFCTRACEERROR( m_ErrorCode );
      }
      else
      {
         return_value = TRUE;
      }

      ::CloseServiceHandle( service_handle );

      return( return_value );
   }
   catch( ... )
   {
      m_ErrorCode = ERROR_EXCEPTION_IN_SERVICE;
      return( FALSE );
   }
}

BOOL CServiceControlManager::Remove( LPCTSTR service_name )
{
   WFCLTRACEINIT( TEXT( "CServiceControlManager::Remove()" ) );
   ASSERT( service_name != NULL );

   if ( service_name == (LPCTSTR) NULL )
   {
      m_ErrorCode = ERROR_INVALID_PARAMETER;
      return( FALSE );
   }

   // We were passed a pointer, don't trust it

   try
   {
      ASSERT( m_ManagerHandle != NULL );

      if ( m_ManagerHandle == NULL )
      {
         m_ErrorCode = ERROR_INVALID_HANDLE;
         return( FALSE );
      }

      SC_HANDLE service_handle = (SC_HANDLE) NULL;

      service_handle = ::OpenService( m_ManagerHandle, service_name, SERVICE_ALL_ACCESS );

      if ( service_handle == (SC_HANDLE) NULL )
      {
         m_ErrorCode = ::GetLastError();
         WFCTRACEERROR( m_ErrorCode );
         return( FALSE );
      }

      /*
      ** We're gonna delete the service, this is something we should record
      */

      {
         TCHAR user_name[ 2048 ];
         TCHAR temp_string[ 2100 ];

         DWORD size_of_user_name = DIMENSION_OF( user_name );

         ::ZeroMemory( user_name,   sizeof( user_name   ) );
         ::ZeroMemory( temp_string, sizeof( temp_string ) );

         ::GetUserName( user_name, &size_of_user_name );

         _stprintf( temp_string, TEXT( "Service being removed by %s" ), user_name );

         CEventLog event_log( service_name );

         event_log.ReportInformation( temp_string );
      }

      BOOL return_value = ::DeleteService( service_handle );

      if ( return_value == FALSE )
      {
         m_ErrorCode = ::GetLastError();
         WFCTRACEERROR( m_ErrorCode );

         /*
         ** We couldn't delete the service, let's record why...
         */

         LPVOID message_buffer = (LPVOID) NULL;

         ::FormatMessage( FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
                          NULL,
                          m_ErrorCode,
                          MAKELANGID( LANG_ENGLISH, SUBLANG_ENGLISH_US ),
                (LPTSTR) &message_buffer,
                          0,
                          NULL );

         if ( message_buffer != NULL )
         {
            TCHAR temp_string[ 255 ];

            _stprintf( temp_string, TEXT( "Can't delete service because %s" ), message_buffer );

            CEventLog event_log( service_name );
            event_log.ReportError( temp_string );

            ::LocalFree( message_buffer );
         }

         return( FALSE );
      }

      // We no longer need the service handle...

      ::CloseServiceHandle( service_handle );
      service_handle = (SC_HANDLE) NULL;

      /*
      ** Now that we've deleted the service, we need to remove it from the event logger
      */

      CEventLog event_log;

      event_log.DeleteApplicationLog( service_name );

      return( TRUE );
   }
   catch( ... )
   {
      m_ErrorCode = ERROR_EXCEPTION_IN_SERVICE;
      return( FALSE );
   }
}

BOOL CServiceControlManager::SetConfiguration( LPCTSTR service_name,
                                               DWORD   when_to_start,
                                               DWORD   type_of_service,
                                               DWORD   error_control,
                                               LPCTSTR name_of_executable_file,
                                               LPCTSTR load_order_group,
                                               LPCTSTR dependencies,
                                               LPCTSTR start_name,
                                               LPCTSTR password,
                                               LPCTSTR display_name )
{
   WFCLTRACEINIT( TEXT( "CServiceControlManager::SetConfiguration()" ) );
   ASSERT( service_name != NULL );

   if ( service_name == NULL )
   {
      m_ErrorCode = ERROR_INVALID_PARAMETER;
      return( FALSE );
   }

   ASSERT( m_ManagerHandle != NULL );

   if ( m_ManagerHandle == NULL )
   {
      m_ErrorCode = ERROR_INVALID_HANDLE;
      return( FALSE );
   }

   SC_HANDLE service_handle = (SC_HANDLE) NULL;

   // We were passed a bunch of pointers, don't trust them

   try
   {
      service_handle = ::OpenService( m_ManagerHandle, service_name, SERVICE_ALL_ACCESS );

      if ( service_handle == (SC_HANDLE) NULL )
      {
         m_ErrorCode = ::GetLastError();
         WFCTRACEERROR( m_ErrorCode );
         return( FALSE );
      }

      // Lock the database so we can safely make the changes

      BOOL return_value = FALSE;

      return_value = LockDatabase();

      if ( return_value != FALSE )
      {
         // Microsoft has a bug in NT. I know what you're thinking, "THAT'S IMPOSSIBLE"
         // The programmers at Microsoft are only human so things slip through.
         // A programmer named Lee Ott (not of Microsoft) discovered a bug while
         // debugging Tom Horsley's NTPTime program (highly recommended by me).
         // If your executable name has a space in it (like "c:\Program files\myservice.exe"
         // The service control manager will fail with helpful message of "Event ID 7000:
         // %1 Not A Valid Windows NT Application" Lee discovered that if you put
         // the exeuteable anme in quotes, it will work properly.

         CString normalized_executable_name( name_of_executable_file );

         if ( normalized_executable_name.GetLength() < 1 )
         {
            WFCTRACE( TEXT( "Executable name is empty." ) );
            m_ErrorCode = ERROR_INVALID_PARAMETER;
            UnlockDatabase();
            return( FALSE );
         }

         if ( normalized_executable_name.Find( TEXT( " " ) ) != (-1) )
         {
            // The name contains a space. We must make sure the name is in quotes

            if ( normalized_executable_name.GetAt( 0 ) != TEXT( '\"' ) )
            {
               CString new_name( TEXT( "\"" ) );

               new_name += normalized_executable_name;
               normalized_executable_name = new_name;
            }

            if ( normalized_executable_name.GetAt( normalized_executable_name.GetLength() - 1 ) != TEXT( '\"' ) )
            {
               normalized_executable_name += TEXT( "\"" );
            }
         }

         return_value = ::ChangeServiceConfig( service_handle,
                                               type_of_service,
                                               when_to_start,
                                               error_control,
                                               normalized_executable_name,
                                               load_order_group,
                                               NULL,
                                               dependencies,
                                               start_name,
                                               password,
                                               display_name );

         if ( return_value == FALSE )
         {
            m_ErrorCode = ::GetLastError();
            WFCTRACEERROR( m_ErrorCode );
         }
         else
         {
            return_value = TRUE;
         }

         UnlockDatabase();

         ::CloseServiceHandle( service_handle );
         return( return_value );
      }
      else
      {
         WFCTRACE( TEXT( "Can't lock database" ) );

         // LockDatabase already set m_ErrorCode

         ::CloseServiceHandle( service_handle );
         return( FALSE );
      }
   }
   catch( ... )
   {
      m_ErrorCode = ERROR_EXCEPTION_IN_SERVICE;
      return( FALSE );
   }
}

BOOL CServiceControlManager::Start( LPCTSTR service_name, DWORD service_argc, LPCTSTR *service_argv )
{
   WFCLTRACEINIT( TEXT( "CServiceControlManager::Start()" ) );
   ASSERT( service_name != NULL );

   if ( service_name == NULL )
   {
      m_ErrorCode = ERROR_INVALID_PARAMETER;
      return( FALSE );
   }

   // We were passed a pointer, don't trust it

   try
   {
      ASSERT( m_ManagerHandle != NULL );

      if ( m_ManagerHandle == NULL )
      {
         m_ErrorCode = ERROR_INVALID_HANDLE;
         return( FALSE );
      }

      SC_HANDLE service_handle = ::OpenService( m_ManagerHandle, service_name, SERVICE_START );

      if ( service_handle == (SC_HANDLE) NULL )
      {
         m_ErrorCode = ::GetLastError();
         WFCTRACEERROR( m_ErrorCode );
         return( FALSE );
      }

      BOOL return_value = ::StartService( service_handle, service_argc, service_argv );

      if ( return_value == FALSE )
      {
         m_ErrorCode = ::GetLastError();
         WFCTRACEERROR( m_ErrorCode );
      }
      else
      {
         return_value = TRUE;
      }

      ::CloseServiceHandle( service_handle );

      return( return_value );
   }
   catch( ... )
   {
      m_ErrorCode = ERROR_EXCEPTION_IN_SERVICE;
      return( FALSE );
   }
}

BOOL CServiceControlManager::Stop( LPCTSTR service_name )
{
   WFCLTRACEINIT( TEXT( "CServiceControlManager::Stop()" ) );
   ASSERT( service_name != NULL );

   if ( service_name == NULL )
   {
      m_ErrorCode = ERROR_INVALID_PARAMETER;
      return( FALSE );
   }

   // We were passed a pointer, don't trust it

   try
   {
      ASSERT( m_ManagerHandle != NULL );

      if ( m_ManagerHandle == NULL )
      {
         m_ErrorCode = ERROR_INVALID_HANDLE;
         return( FALSE );
      }

      // Thanks go to Rainer Kukasch (rk@sicom.de) for finding a bug here.
      // I was not opening the service with permission to query it's status.
      // That caused the QueryServiceStatus() later on to fail.

      SC_HANDLE service_handle = ::OpenService( m_ManagerHandle, service_name, SERVICE_STOP | SERVICE_QUERY_STATUS );

      if ( service_handle == (SC_HANDLE) NULL )
      {
         m_ErrorCode = ::GetLastError();
         WFCTRACEERROR( m_ErrorCode );
         return( FALSE );
      }

      SERVICE_STATUS service_status;

      ::ZeroMemory( &service_status, sizeof( service_status ) );

      BOOL return_value = ::ControlService( service_handle, SERVICE_CONTROL_STOP, &service_status );

      if ( return_value == FALSE )
      {
         m_ErrorCode = ::GetLastError();
         WFCTRACEERROR( m_ErrorCode );
         ::CloseServiceHandle( service_handle );

         return( return_value );
      }

      DWORD old_checkpoint  = 0;
      DWORD number_of_tries = 0;

      while( service_status.dwCurrentState != SERVICE_STOPPED )
      {
         old_checkpoint = service_status.dwCheckPoint;

         // Stop pestering the service with status requests

         ::Sleep( service_status.dwWaitHint );

         if ( ::QueryServiceStatus( service_handle, &service_status ) == FALSE )
         {
            WFCTRACE( TEXT( "Can't QueryServiceStatus" ) );
            ::CloseServiceHandle( service_handle );
            return( FALSE );
         }

         if ( old_checkpoint >= service_status.dwCheckPoint )
         {
            number_of_tries++;

            if ( number_of_tries >= 100 )
            {
               WFCTRACE( TEXT( "Service hung while stopping" ) );
               ::CloseServiceHandle( service_handle );
               return( FALSE );
            }
         }
         else
         {
            number_of_tries = 0;
         }
      }

      ::CloseServiceHandle( service_handle );
      return( TRUE );
   }
   catch( ... )
   {
      m_ErrorCode = ERROR_EXCEPTION_IN_SERVICE;
      return( FALSE );
   }
}

BOOL CServiceControlManager::UnlockDatabase( void )
{
   WFCLTRACEINIT( TEXT( "CServiceControlManager::UnlockDatabase()" ) );

   BOOL return_value = FALSE;

   if ( m_DatabaseLockHandle == NULL )
   {
      // Already unlocked
      return( TRUE );
   }

   return_value = ::UnlockServiceDatabase( m_DatabaseLockHandle );

   if ( return_value == FALSE )
   {
      m_ErrorCode = ::GetLastError();
      WFCTRACEERROR( m_ErrorCode );
   }
   else
   {
      return_value = TRUE;
   }

   m_DatabaseLockHandle = reinterpret_cast< SC_LOCK >( NULL );

   return( return_value );
}

CServiceNameAndStatusA::CServiceNameAndStatusA()
{
   Empty();
}

CServiceNameAndStatusA::~CServiceNameAndStatusA()
{
   Empty();
}

void CServiceNameAndStatusA::Copy( const _ENUM_SERVICE_STATUSA *source_p )
{
   WFCLTRACEINIT( TEXT( "CServiceNameAndStatusA::Copy()" ) );
   ASSERT( source_p != NULL );

   if ( source_p == NULL )
   {
      Empty();
      return;
   }

   // We were passed a pointer, don't trust it

   try
   {
      lpServiceName                           = source_p->lpServiceName;
      lpDisplayName                           = source_p->lpDisplayName;
      ServiceStatus.dwServiceType             = source_p->ServiceStatus.dwServiceType;
      ServiceStatus.dwCurrentState            = source_p->ServiceStatus.dwCurrentState;
      ServiceStatus.dwControlsAccepted        = source_p->ServiceStatus.dwControlsAccepted;
      ServiceStatus.dwWin32ExitCode           = source_p->ServiceStatus.dwWin32ExitCode;
      ServiceStatus.dwServiceSpecificExitCode = source_p->ServiceStatus.dwServiceSpecificExitCode;
      ServiceStatus.dwCheckPoint              = source_p->ServiceStatus.dwCheckPoint;
      ServiceStatus.dwWaitHint                = source_p->ServiceStatus.dwWaitHint;
   }
   catch( ... )
   {
      Empty();
   }
}

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

void CServiceNameAndStatusA::Dump( CDumpContext& dump_context ) const
{
   dump_context << TEXT( "a CServiceNameAndStatusA at " ) << (VOID *) this << TEXT( "\n{\n" );
   dump_context << TEXT( "   lpServicename                           = " ) << lpServiceName << TEXT( "\n" );
   dump_context << TEXT( "   lpDisplayName                           = " ) << lpDisplayName << TEXT( "\n" );
   dump_context << TEXT( "   ServiceStatus.dwServiceType             = " ) << ServiceStatus.dwServiceType << TEXT( " (" );

   CString temp_string( TEXT( "" ) );

   if ( ServiceStatus.dwServiceType & SERVICE_WIN32_OWN_PROCESS )
   {
      temp_string = TEXT( "SERVICE_WIN32_OWN_PROCESS" );
   }

   if ( ServiceStatus.dwServiceType & SERVICE_WIN32_SHARE_PROCESS )
   {
      if ( temp_string.GetLength() > 0 )
      {
         temp_string += TEXT( " | " );
      }

      temp_string += TEXT( "SERVICE_WIN32_SHARE_PROCESS" );
   }

   if ( ServiceStatus.dwServiceType & SERVICE_KERNEL_DRIVER  )
   {
      if ( temp_string.GetLength() > 0 )
      {
         temp_string += TEXT( " | " );
      }

      temp_string += TEXT( "SERVICE_KERNEL_DRIVER" );
   }

   if ( ServiceStatus.dwServiceType & SERVICE_FILE_SYSTEM_DRIVER )
   {
      if ( temp_string.GetLength() > 0 )
      {
         temp_string += TEXT( " | " );
      }

      temp_string += TEXT( "SERVICE_FILE_SYSTEM_DRIVER" );
   }

   if ( ServiceStatus.dwServiceType & SERVICE_INTERACTIVE_PROCESS )
   {
      if ( temp_string.GetLength() > 0 )
      {
         temp_string += TEXT( " | " );
      }

      temp_string += TEXT( "SERVICE_INTERACTIVE_PROCESS" );
   }

   dump_context << temp_string << TEXT( ")\n" );

   dump_context << TEXT( "   ServiceStatus.dwCurrentState            = " ) << ServiceStatus.dwCurrentState << TEXT( " (" );

   temp_string = TEXT( "" );

   switch( ServiceStatus.dwCurrentState )
   {
      case SERVICE_STOPPED:

         temp_string = TEXT( "SERVICE_STOPPED" );
         break;

      case SERVICE_START_PENDING:

         temp_string = TEXT( "SERVICE_START_PENDING" );
         break;

      case SERVICE_STOP_PENDING:

         temp_string = TEXT( "SERVICE_STOP_PENDING" );
         break;

      case SERVICE_RUNNING:

         temp_string = TEXT( "SERVICE_RUNNING" );
         break;

      case SERVICE_CONTINUE_PENDING:

         temp_string = TEXT( "SERVICE_CONTINUE_PENDING" );
         break;

      case SERVICE_PAUSE_PENDING:

         temp_string = TEXT( "SERVICE_PAUSE_PENDING" );
         break;

      case SERVICE_PAUSED:

         temp_string = TEXT( "SERVICE_PAUSED" );
         break;

      default:

         temp_string = TEXT( "Unknown" );
         break;
   }

   dump_context << temp_string << TEXT( ")\n" );

   dump_context << TEXT( "   ServiceStatus.dwControlsAccepted        = " ) << ServiceStatus.dwControlsAccepted << TEXT( " (" );

   temp_string = TEXT( "" );

   if ( ServiceStatus.dwControlsAccepted & SERVICE_ACCEPT_STOP )
   {
      temp_string = TEXT( "SERVICE_ACCEPT_STOP" );
   }

   if ( ServiceStatus.dwControlsAccepted & SERVICE_ACCEPT_PAUSE_CONTINUE )
   {
      if ( temp_string.GetLength() > 0 )
      {
         temp_string += TEXT( " | " );
      }

      temp_string += TEXT( "SERVICE_ACCEPT_PAUSE_CONTINUE" );
   }

   if ( ServiceStatus.dwControlsAccepted & SERVICE_ACCEPT_SHUTDOWN )
   {
      if ( temp_string.GetLength() > 0 )
      {
         temp_string += TEXT( " | " );
      }

      temp_string += TEXT( "SERVICE_ACCEPT_SHUTDOWN" );
   }

   dump_context << temp_string << TEXT( ")\n" );

   dump_context << TEXT( "   ServiceStatus.dwWin32ExitCode           = " ) << ServiceStatus.dwWin32ExitCode           << TEXT( "\n" );
   dump_context << TEXT( "   ServiceStatus.dwServiceSpecificExitCode = " ) << ServiceStatus.dwServiceSpecificExitCode << TEXT( "\n" );
   dump_context << TEXT( "   ServiceStatus.dwCheckPoint              = " ) << ServiceStatus.dwCheckPoint              << TEXT( "\n" );
   dump_context << TEXT( "   ServiceStatus.dwWaitHint                = " ) << ServiceStatus.dwWaitHint                << TEXT( "\n" );
   dump_context << TEXT( "}\n" );
}

#endif // _DEBUG

void CServiceNameAndStatusA::Empty( void )
{
   WFCLTRACEINIT( TEXT( "CServiceNameAndStatusA::Empty()" ) );

   lpServiceName                           = reinterpret_cast< LPSTR >( NULL );
   lpDisplayName                           = reinterpret_cast< LPSTR >( NULL );
   ServiceStatus.dwServiceType             = 0;
   ServiceStatus.dwCurrentState            = 0;
   ServiceStatus.dwControlsAccepted        = 0;
   ServiceStatus.dwWin32ExitCode           = 0;
   ServiceStatus.dwServiceSpecificExitCode = 0;
   ServiceStatus.dwCheckPoint              = 0;
   ServiceStatus.dwWaitHint                = 0;
}

CServiceNameAndStatusW::CServiceNameAndStatusW()
{
   Empty();
}

CServiceNameAndStatusW::~CServiceNameAndStatusW()
{
   Empty();
}

void CServiceNameAndStatusW::Copy( const _ENUM_SERVICE_STATUSW *source_p )
{
   WFCLTRACEINIT( TEXT( "CServiceNameAndStatusW::Copy()" ) );
   ASSERT( source_p != NULL );

   if ( source_p == NULL )
   {
      Empty();
      return;
   }

   // We were passed a pointer, don't trust it

   try
   {
      lpServiceName                           = source_p->lpServiceName;
      lpDisplayName                           = source_p->lpDisplayName;
      ServiceStatus.dwServiceType             = source_p->ServiceStatus.dwServiceType;
      ServiceStatus.dwCurrentState            = source_p->ServiceStatus.dwCurrentState;
      ServiceStatus.dwControlsAccepted        = source_p->ServiceStatus.dwControlsAccepted;
      ServiceStatus.dwWin32ExitCode           = source_p->ServiceStatus.dwWin32ExitCode;
      ServiceStatus.dwServiceSpecificExitCode = source_p->ServiceStatus.dwServiceSpecificExitCode;
      ServiceStatus.dwCheckPoint              = source_p->ServiceStatus.dwCheckPoint;
      ServiceStatus.dwWaitHint                = source_p->ServiceStatus.dwWaitHint;
   }
   catch( ... )
   {
      Empty();
   }
}

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

void CServiceNameAndStatusW::Dump( CDumpContext& dump_context ) const
{
   dump_context << TEXT( "a CServiceNameAndStatusW at " ) << (VOID *) this << TEXT( "\n{\n" );
   dump_context << TEXT( "   lpServicename                           = " ) << lpServiceName << TEXT( "\n" );
   dump_context << TEXT( "   lpDisplayName                           = " ) << lpDisplayName << TEXT( "\n" );
   dump_context << TEXT( "   ServiceStatus.dwServiceType             = " ) << ServiceStatus.dwServiceType << TEXT( " (" );

   CString temp_string( TEXT( "" ) );

   if ( ServiceStatus.dwServiceType & SERVICE_WIN32_OWN_PROCESS )
   {
      temp_string = TEXT( "SERVICE_WIN32_OWN_PROCESS" );
   }

   if ( ServiceStatus.dwServiceType & SERVICE_WIN32_SHARE_PROCESS )
   {
      if ( temp_string.GetLength() > 0 )
      {
         temp_string += TEXT( " | " );
      }

      temp_string += TEXT( "SERVICE_WIN32_SHARE_PROCESS" );
   }

   if ( ServiceStatus.dwServiceType & SERVICE_KERNEL_DRIVER  )
   {
      if ( temp_string.GetLength() > 0 )
      {
         temp_string += TEXT( " | " );
      }

      temp_string += TEXT( "SERVICE_KERNEL_DRIVER" );
   }

   if ( ServiceStatus.dwServiceType & SERVICE_FILE_SYSTEM_DRIVER )
   {
      if ( temp_string.GetLength() > 0 )
      {
         temp_string += TEXT( " | " );
      }

      temp_string += TEXT( "SERVICE_FILE_SYSTEM_DRIVER" );
   }

   if ( ServiceStatus.dwServiceType & SERVICE_INTERACTIVE_PROCESS )
   {
      if ( temp_string.GetLength() > 0 )
      {
         temp_string += TEXT( " | " );
      }

      temp_string += TEXT( "SERVICE_INTERACTIVE_PROCESS" );
   }

   dump_context << temp_string << TEXT( ")\n" );

   dump_context << TEXT( "   ServiceStatus.dwCurrentState            = " ) << ServiceStatus.dwCurrentState << TEXT( " (" );

   temp_string = TEXT( "" );

   switch( ServiceStatus.dwCurrentState )
   {
      case SERVICE_STOPPED:

         temp_string = TEXT( "SERVICE_STOPPED" );
         break;

      case SERVICE_START_PENDING:

         temp_string = TEXT( "SERVICE_START_PENDING" );
         break;

      case SERVICE_STOP_PENDING:

         temp_string = TEXT( "SERVICE_STOP_PENDING" );
         break;

      case SERVICE_RUNNING:

         temp_string = TEXT( "SERVICE_RUNNING" );
         break;

      case SERVICE_CONTINUE_PENDING:

         temp_string = TEXT( "SERVICE_CONTINUE_PENDING" );
         break;

      case SERVICE_PAUSE_PENDING:

         temp_string = TEXT( "SERVICE_PAUSE_PENDING" );
         break;

      case SERVICE_PAUSED:

         temp_string = TEXT( "SERVICE_PAUSED" );
         break;

      default:

         temp_string = TEXT( "Unknown" );
         break;
   }

   dump_context << temp_string << TEXT( ")\n" );

   dump_context << TEXT( "   ServiceStatus.dwControlsAccepted        = " ) << ServiceStatus.dwControlsAccepted << TEXT( " (" );

   temp_string = TEXT( "" );

   if ( ServiceStatus.dwControlsAccepted & SERVICE_ACCEPT_STOP )
   {
      temp_string = TEXT( "SERVICE_ACCEPT_STOP" );
   }

   if ( ServiceStatus.dwControlsAccepted & SERVICE_ACCEPT_PAUSE_CONTINUE )
   {
      if ( temp_string.GetLength() > 0 )
      {
         temp_string += TEXT( " | " );
      }

      temp_string += TEXT( "SERVICE_ACCEPT_PAUSE_CONTINUE" );
   }

   if ( ServiceStatus.dwControlsAccepted & SERVICE_ACCEPT_SHUTDOWN )
   {
      if ( temp_string.GetLength() > 0 )
      {
         temp_string += TEXT( " | " );
      }

      temp_string += TEXT( "SERVICE_ACCEPT_SHUTDOWN" );
   }

   dump_context << temp_string << TEXT( ")\n" );

   dump_context << TEXT( "   ServiceStatus.dwWin32ExitCode           = " ) << ServiceStatus.dwWin32ExitCode           << TEXT( "\n" );
   dump_context << TEXT( "   ServiceStatus.dwServiceSpecificExitCode = " ) << ServiceStatus.dwServiceSpecificExitCode << TEXT( "\n" );
   dump_context << TEXT( "   ServiceStatus.dwCheckPoint              = " ) << ServiceStatus.dwCheckPoint              << TEXT( "\n" );
   dump_context << TEXT( "   ServiceStatus.dwWaitHint                = " ) << ServiceStatus.dwWaitHint                << TEXT( "\n" );
   dump_context << TEXT( "}\n" );
}

#endif // _DEBUG

void CServiceNameAndStatusW::Empty( void )
{
   WFCLTRACEINIT( TEXT( "CServiceNameAndStatusW::Empty()" ) );

   lpServiceName                           = reinterpret_cast< LPWSTR >( NULL );
   lpDisplayName                           = reinterpret_cast< LPWSTR >( NULL );
   ServiceStatus.dwServiceType             = 0;
   ServiceStatus.dwCurrentState            = 0;
   ServiceStatus.dwControlsAccepted        = 0;
   ServiceStatus.dwWin32ExitCode           = 0;
   ServiceStatus.dwServiceSpecificExitCode = 0;
   ServiceStatus.dwCheckPoint              = 0;
   ServiceStatus.dwWaitHint                = 0;
}

// End of source

#if 0
<HTML>

<HEAD>
<TITLE>WFC - CServiceControlManager</TITLE>
<META name="keywords" content="WFC, MFC extension library, freeware class library, Win32, source code">
<META name="description" content="The C++ class that makes it easy to manage NT services. Let's you start/stop/install or remove services.">
</HEAD>

<BODY>

<H1>CServiceControlManager</H1>
$Revision: 43 $
<HR>

<H2>Description</H2>
This class handles playing with NT's Service Control Manager (SCM).
The SCM manages the starting/stopping/installing/removing/etc. of services.

<H2>Data Members</H2>
None.

<H2>Methods</H2>

<DL COMPACT>

<DT><PRE>void <B>Close</B>( void )</PRE><DD>
Closes your session with the SCM.

<DT><PRE>BOOL <B>Continue</B>( LPCTSTR service_name )</PRE><DD>
You give this function the name of a paused service. It will
tell the named service to continue.

<DT><PRE>BOOL <B>EnableInteractiveServices</B>( BOOL enable_interactive_services = TRUE )</PRE><DD>
This function returns TRUE if the setting was set, FALSE if there was a problem.
Calling <B>EnableInteractiveServices</B>() with <CODE>enable_interactive_services</CODE>
set to FALSE will prevent any service from interacting with the desktop/user.

<DT><PRE>BOOL <B>EnumerateStatus</B>( DWORD state = SERVICE_ACTIVE, type = SERVICE_WIN32 )</PRE><DD>
This function allows you to enumerate services that have a particular status.
The <CODE>state</CODE> parameter may be one of:

<UL>
<LI>SERVICE_ACTIVE
<LI>SERVICE_INACTIVE
<LI>SERVICE_STATE_ALL
</UL>

The <CODE>type</CODE> parameter may be one of:

<UL>
<LI>SERVICE_WIN32
<LI>SERVICE_DRIVER
</UL>

<DT><PRE>BOOL <B>GetConfiguration</B>( LPCTSTR service_name, CServiceConfiguration&amp; configuration )</PRE><DD>
This function retrieves useful information about how a service is configured.

<DT><PRE>BOOL <B>GetDependencies</B>( LPCTSTR service_name, CStringArray&amp; dependencies )</PRE><DD>
Fills <CODE>dependencies</CODE> with the names of services that must be running before
the <CODE>service_name</CODE> service can run.

<DT><PRE>DWORD <B>GetErrorCode</B>( void ) const</PRE><DD>
Retrieves the error code. Call this function to find out why any other class member returned FALSE.

<DT><PRE>SC_HANDLE <B>GetHandle</B>( void ) const</PRE><DD>
Returns the encapsulated SC_HANDLE.
Use this method if you want to call the Win32 API directly
(i.e. you don't want to use WFC).

<DT><PRE>BOOL <B>GetKeyName</B>( LPCTSTR display_name, CString&amp; key_name )</PRE><DD>
Retrieves a service's internal name (real name) from the user-friendly name.

<DT><PRE>BOOL <B>GetNext</B>( CServiceNameAndStatus&amp; status )</PRE><DD>
This function is called to retrieve the next name and status (CServiceNameAndStatus)
being enumerated via <B>EnumerateStatus</B>. It will return FALSE
when the last enumerated service has been retrieved.

<DT><PRE>BOOL <B>Install</B>( LPCTSTR service_name, LPCTSTR friendly_name, LPCTSTR name_of_executable_file )</PRE><DD>
This function will install a new service.

<DT><PRE>BOOL <B>IsDatabaseLocked</B>( CString&amp; who_locked_it, CTimeSpan&amp; how_long_it_has_been_locked )</PRE><DD>
If <B>IsDatabaseLocked</B>() returns TRUE, the database is locked, <CODE>who_locked_it</CODE>
will be filled with the name of the user who locked it, <CODE>how_long_it_has_been_locked</CODE>
will be filled with how long that user has had the database locked. If
<B>IsDatabaseLocked</B>() returns FALSE, <CODE>who_locked_it</CODE> will be
empty and <CODE>how_long_it_has_been_locked</CODE> will be zero.

<DT><PRE>BOOL <B>LockDatabase</B>( void )</PRE><DD>
Locks the service control database. Only one process can lock the database at
any given time. You cannot start a service when the database is locked.The lock
prevents the service control manager from starting a service while it is
being reconfigured. 

<DT><PRE>BOOL <B>Open</B>( DWORD   what_to_open  = SC_MANAGER_ALL_ACCESS,
           LPCTSTR database_name = NULL,
           LPCTSTR machine_name  = NULL )</PRE><DD>
Opens a connection to the SCM on a machine.

<DT><PRE>BOOL <B>Pause</B>( LPCTSTR service_name )</PRE><DD>
Pauses the named service.

<DT><PRE>BOOL <B>Remove</B>( LPCTSTR service_name )</PRE><DD>
Un-installs a service. <B>WARNING!</B> This does a lot
of stuff for you. One of the things it will screw up is the Event Log. It removes the source of messages so you will no longer be
able to read entries in the log that the removed service made.

<DT><PRE><B>SetConfiguration</B>( LPCTSTR service_name,
                  DWORD   when_to_start           = SERVICE_NO_CHANGE,
                  DWORD   type_of_service         = SERVICE_NO_CHANGE,
                  DWORD   error_control           = SERVICE_NO_CHANGE,
                  LPCTSTR name_of_executable_file = NULL,
                  LPCTSTR load_order_group        = NULL,
                  LPCTSTR dependencies            = NULL,
                  LPCTSTR start_name              = NULL,
                  LPCTSTR password                = NULL,
                  LPCTSTR display_name            = NULL )</PRE><DD>
Changes a service's configuration. You can change 
when a service is to start, type, name of the executable file, etc.

<DT><PRE>BOOL <B>Start</B>( LPCTSTR service_name, DWORD service_argc = 0, LPCTSTR *service_argv = NULL )</PRE><DD>
Starts a service by name. You supply the startup parameters.

<DT><PRE>BOOL <B>Stop</B>( LPCTSTR service_name )</PRE><DD>
Stops a service by name.

<DT><PRE>BOOL <B>UnlockDatabase</B>( void )</PRE><DD>
Unlocks the service control database.

</DL>

<H2>Example</H2>
<PRE><CODE>#include &lt;wfc.h&gt;
#include &quot;messages.h&quot;
#pragma hdrstop

#if defined( _DEBUG )
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

DWORD WINAPI worker_thread( LPVOID pointer_to_parent_CService_class );
VOID set_default_parameters( void );

int __cdecl _tmain( int number_of_command_line_arguments, LPCTSTR command_line_arguments[] )
{
   <A HREF="WfcTrace.htm">WFCTRACEINIT</A>( TEXT( &quot;_tmain()&quot; ) );

   if ( number_of_command_line_arguments == 1 )
   {
      <A HREF="CService.htm">CService</A> service( worker_thread );
      service.Initialize( TEXT( &quot;WatchDog&quot; ) );
      return( EXIT_SUCCESS );
   }

   if ( number_of_command_line_arguments == 2 )
   {
      if ( _tcsicmp( command_line_arguments[ 1 ], TEXT( &quot;install&quot; ) ) == 0 )
      {
         <B>CServiceControlManager</B> service_control_manager;

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
         <B>CServiceControlManager</B> service_control_manager;

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

      if ( registry.Connect( <A HREF="REGISTRY.htm">CRegistry</A>::keyLocalMachine ) == FALSE )
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

   <B>CServiceControlManager</B> service_control_manager;

   /*
   ** Sleep for one minute, this is in case we are starting during boot-up. We want
   ** to give the service control manager time to start all necessary services before
   ** we begin restarting stopped services.
   */

   Sleep( 60 );

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

                     event_log.Report( <A HREF="CEVNTLOG.htm">CEventLog</A>::eventInformation,
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
      if ( registry.Create( TEXT( &quot;SYSTEM\\CurrentControlSet\\Services\\WatchDog\\Parameters&quot; ) != FALSE ) )
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

            event_log.Report( <A HREF="CEVNTLOG.htm">CEventLog</A>::eventError,
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

            event_log.Report( <A HREF="CEVNTLOG.htm">CEventLog</A>::eventError, 0, MSG_CANT_SET_REGISTRY_ENTRY, 2, (LPCTSTR *) string_array );

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

         <A HREF="CEVNTLOG.htm">CEventLog</A> event_log( TEXT( &quot;WatchDog&quot; ) );

         event_log.Report( <A HREF="CEVNTLOG.htm">CEventLog</A>::eventError, 0, MSG_CANT_CREATE_REGISTRY_KEY, 2, (LPCTSTR *) string_array );

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

      event_log.Report( <A HREF="CEVNTLOG.htm">CEventLog</A>::eventError, 0, MSG_CANT_CONNECT_TO_REGISTRY, 2, (LPCTSTR *) string_array );

      if ( message_buffer != NULL )
      {
         ::LocalFree( message_buffer );
      }
   }
}</CODE></PRE>

<H2>API's Used</H2>

<B>CServiceControlManager</B> encapsulates the following API's:
<UL>
<LI>ChangeServiceConfig
<LI>CloseServiceHandle
<LI>ControlService
<LI>CreateService
<LI>DeleteService
<LI>EnumDependentServices
<LI>EnumServicesStatus
<LI>FormatMessage
<LI>GetLastError
<LI>GetServiceDisplayName
<LI>GetServiceKeyName
<LI>LocalFree
<LI>LockServiceDatabase
<LI>OpenSCManager
<LI>OpenService
<LI>QueryServiceConfig
<LI>QueryServiceLockStatus
<LI>Sleep
<LI>StartService
<LI>UnlockServiceDatabase
</UL>

<HR><I>Copyright, 2000, <A HREF="mailto:wfc@pobox.com">Samuel R. Blackburn</A></I><BR>
$Workfile: csvcmgr.cpp $<BR>
$Modtime: 4/01/00 8:45a $
</BODY>

</HTML>
#endif
