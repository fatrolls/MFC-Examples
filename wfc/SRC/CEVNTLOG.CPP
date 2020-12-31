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
** $Workfile: cevntlog.cpp $
** $Revision: 38 $
** $Modtime: 3/17/00 4:28p $
** $Reuse Tracing Code: 1 $
*/

#if defined( _DEBUG ) && ! defined( WFC_STL )
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

#if ! defined(  WFC_NO_SERIALIZATION )
IMPLEMENT_DYNAMIC( CEventLog, CObject );
#endif // WFC_NO_SERIALIZATION

#if defined( _DEBUG ) && ! defined( WFC_STL )
#define new DEBUG_NEW
#endif // _DEBUG

CEventLog::CEventLog()
{
   WFCLTRACEINIT( TEXT( "CEventLog::CEventLog()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   m_Initialize();
}

CEventLog::CEventLog( LPCTSTR source_name )
{
   WFCLTRACEINIT( TEXT( "CEventLog::CEventLog( LPCTSTR )" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );

   m_Initialize();
   RegisterSource( source_name );
}

CEventLog::~CEventLog()
{
   WFCLTRACEINIT( TEXT( "CEventLog::~CEventLog()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );

   if ( m_EventSourceHandle != (HANDLE) INVALID_HANDLE_VALUE )
   {
      DeregisterSource();
   }

   if ( m_LogHandle != (HANDLE) INVALID_HANDLE_VALUE )
   {
      Close();
   }

   m_Initialize();
}

void CEventLog::m_Initialize( void )
{
   WFCLTRACEINIT( TEXT( "CEventLog::m_Initialize()" ) );

   ComputerName.Empty();
   LogName.Empty();

   m_LogHandle                 = (HANDLE) INVALID_HANDLE_VALUE;
   m_EventSourceHandle         = (HANDLE) INVALID_HANDLE_VALUE;
   m_ErrorCode                 = 0;
   m_NumberOfBytesRead         = 0;
   m_NumberOfBytesInNextRecord = 0;
}

BOOL CEventLog::Backup( LPCTSTR name_of_backup_file )
{
   WFCLTRACEINIT( TEXT( "CEventLog::Backup()" ) );
   ASSERT( name_of_backup_file != NULL );

   if ( name_of_backup_file == NULL )
   {
      m_ErrorCode = ERROR_INVALID_PARAMETER;
      return( FALSE );
   }

   // We were passed a pointer, do not trust it

   try
   {
      WFCTRACEVAL( TEXT( "Backing up to " ), CString( name_of_backup_file ) );

      BOOL return_value = ::BackupEventLog( m_LogHandle, name_of_backup_file );

      if ( return_value == FALSE )
      {
         m_ErrorCode = ::GetLastError();
         WFCTRACEERROR( m_ErrorCode );
      }
      else
      {
         return_value = TRUE;
      }

      return( return_value );
   }
   catch( ... )
   {
      m_ErrorCode = ERROR_EXCEPTION_IN_SERVICE;
      return( FALSE );
   }
}

BOOL CEventLog::Clear( LPCTSTR name_of_backup_file )
{
   WFCLTRACEINIT( TEXT( "CEventLog::Clear()" ) );

   /*
   ** name_of_backup_file can be NULL
   */

   // We were passed a pointer, do not trust it

   try
   {
#if defined( _DEBUG )

      if ( name_of_backup_file != NULL )
      {
         WFCTRACEVAL( TEXT( "name of backup file is " ), CString( name_of_backup_file ) );
      }
      else
      {
         WFCTRACE( TEXT( "name of backup file is NULL" ) );
      }

#endif // _DEBUG

      BOOL return_value = ::ClearEventLog( m_LogHandle, name_of_backup_file );

      if ( return_value == FALSE )
      {
         m_ErrorCode = ::GetLastError();
         WFCTRACEERROR( m_ErrorCode );
      }
      else
      {
         return_value = TRUE;
      }

      return( return_value );
   }
   catch( ... )
   {
      m_ErrorCode = ERROR_EXCEPTION_IN_SERVICE;
      return( FALSE );
   }
}

BOOL CEventLog::Close( void )
{
   WFCLTRACEINIT( TEXT( "CEventLog::Close()" ) );

   BOOL return_value = ::CloseEventLog( m_LogHandle );

   if ( return_value == FALSE )
   {
      m_ErrorCode = ::GetLastError();
      WFCTRACEERROR( m_ErrorCode );
   }
   else
   {
      return_value = TRUE;
   }

   m_LogHandle = (HANDLE) INVALID_HANDLE_VALUE;

   return( return_value );
}

BOOL CEventLog::CreateApplicationLog( LPCTSTR application_name, LPCTSTR message_resource_file, DWORD supported_types )
{
   WFCLTRACEINIT( TEXT( "CEventLog::CreateApplicationLog()" ) );
   ASSERT( application_name      != NULL );
   ASSERT( message_resource_file != NULL );

   if ( application_name == NULL || message_resource_file == NULL )
   {
      m_ErrorCode = ERROR_INVALID_PARAMETER;
      return( FALSE );
   }

   // We were passed a pointer, do not trust it

   try
   {
      WFCTRACEVAL( TEXT( "application is " ), CString( application_name ) );
      WFCTRACEVAL( TEXT( "message resource is " ), CString( message_resource_file ) );

      if ( application_name[ 0 ] == 0x00 || message_resource_file[ 0 ] == 0x00 )
      {
         return( FALSE );
      }

      CRegistry registry;

      if ( registry.Connect( (HKEY) CRegistry::keyLocalMachine ) == FALSE )
      {
         m_ErrorCode = registry.GetErrorCode();
         return( FALSE );
      }

      CString log_key_name( TEXT( "SYSTEM\\CurrentControlSet\\Services\\EventLog\\Application\\" ) );

      log_key_name += application_name;

      if ( registry.Create( log_key_name ) == FALSE )
      {
         m_ErrorCode = registry.GetErrorCode();
         return( FALSE );
      }

      // 1999-08-17
      // Thanks go to Donald Hartzog (donhartzog@usa.net) for finding a UNICODE
      // bug here. I was assuming _tcslen() == sizeof() a string. DOH!

      if ( registry.SetValue( TEXT( "EventMessageFile" ), CRegistry::typeUnexpandedString, (LPBYTE) message_resource_file, ( _tcslen( message_resource_file ) + 1 ) * sizeof( TCHAR ) ) == FALSE )
      {
         m_ErrorCode = registry.GetErrorCode();
         return( FALSE );
      }

      if ( registry.SetValue( TEXT( "TypesSupported" ), supported_types ) == FALSE )
      {
         m_ErrorCode = registry.GetErrorCode();
         return( FALSE );
      }

      /*
      ** Many thanks go to Juha Jalovaara (Juha@compuserve.com) for
      ** searching out the fact that I was not adding to the Sources value.
      ** I may be forgetful, but I thought the Win32 RegisterEventSource
      ** used to do this. Oh well, no harm no foul.
      */

      if ( registry.Open( TEXT( "SYSTEM\\CurrentControlSet\\Services\\EventLog\\Application" ) ) != FALSE )
      {
         CStringArray sources;

         if ( registry.GetValue( TEXT( "Sources" ), sources ) != FALSE )
         {
            int index             = 0;
            int number_of_sources = sources.GetSize();

            BOOL application_was_found = FALSE;

            while( index < number_of_sources )
            {
               if ( sources.GetAt( index ) == application_name )
               {
                  application_was_found = TRUE;
                  index = number_of_sources;
               }

               index++;
            }

            if ( application_was_found == FALSE )
            {
               // The application isn't listed as a source, we must add it

               sources.Add( application_name );
               registry.SetValue( TEXT( "Sources" ), sources );
            }
         }
      }

      return( TRUE );
   }
   catch( ... )
   {
      m_ErrorCode = ERROR_EXCEPTION_IN_SERVICE;
      return( FALSE );
   }
}

BOOL CEventLog::CreateCustomLog( LPCTSTR log_name_parameter, LPCTSTR log_filename_parameter, DWORD maximum_size_in_bytes, DWORD overwrite_after_this_many_seconds )
{
   WFCLTRACEINIT( TEXT( "CEventLog::CreateCustomLog()" ) );
   ASSERT( log_name_parameter != NULL );

   if ( log_name_parameter == NULL )
   {
      m_ErrorCode = ERROR_INVALID_PARAMETER;
      return( FALSE );
   }

   // Let's normallize the file size to a 64K boundary (round up if needed)

   maximum_size_in_bytes += ( maximum_size_in_bytes % 0x10000 );

   if ( maximum_size_in_bytes == 0 )
   {
      maximum_size_in_bytes = 0x10000;
   }

   CString log_name;
   CString log_filename;

   // We were passed a pointer, do not trust it

   try
   {
      log_name = log_name_parameter;

      if ( log_filename_parameter == NULL )
      {
         log_filename  = TEXT( "%SystemRoot%\\System32\\config\\" );
         log_filename += log_name;
         log_filename += TEXT( ".Evt" );
      }
      else
      {
         log_filename = log_filename_parameter;
      }

      WFCTRACEVAL( TEXT( "Log name     is " ), log_name );
      WFCTRACEVAL( TEXT( "Log filename is " ), log_filename );

      CRegistry registry;

      if ( registry.Connect( (HKEY) CRegistry::keyLocalMachine ) == FALSE )
      {
         WFCTRACE( TEXT( "Can't connect to HKEY_LOCAL_MACHINE" ) );
         m_ErrorCode = registry.GetErrorCode();
         return( FALSE );
      }

      CString log_key_name( TEXT( "SYSTEM\\CurrentControlSet\\Services\\EventLog\\" ) );

      log_key_name += log_name;

      if ( registry.Create( log_key_name ) == FALSE )
      {
         WFCTRACE( TEXT( "Can't create new key under SYSTEM\\CurrentControlSet\\Services\\EventLog" ) );
         m_ErrorCode = registry.GetErrorCode();
         return( FALSE );
      }

      if ( registry.SetValue( TEXT( "File" ), CRegistry::typeUnexpandedString, (LPBYTE) log_filename.GetBuffer( log_name.GetLength() + 1 ), log_filename.GetLength() ) == FALSE )
      {
         m_ErrorCode = registry.GetErrorCode();
         return( FALSE );
      }

      if ( registry.SetValue( TEXT( "MaxSize" ), maximum_size_in_bytes ) == FALSE )
      {
         m_ErrorCode = registry.GetErrorCode();
         return( FALSE );
      }

      if ( registry.SetValue( TEXT( "Retention" ), overwrite_after_this_many_seconds ) == FALSE )
      {
         m_ErrorCode = registry.GetErrorCode();
         return( FALSE );
      }

      log_key_name += TEXT( "\\WFC" );

      if ( registry.Create( log_key_name ) == FALSE )
      {
         WFCTRACEVAL( TEXT( "Can't create new key " ), log_key_name );
         m_ErrorCode = registry.GetErrorCode();
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

BOOL CEventLog::Delete( LPCTSTR log_name )
{
   WFCLTRACEINIT( TEXT( "CEventLog::Delete()" ) );
   ASSERT( log_name != NULL );

   // We were passed a pointer, don't trust it

   try
   {
      CString log_to_delete( log_name );

      if ( log_to_delete.GetLength() <= 0 )
      {
         WFCTRACE( TEXT( "Nothing to delete." ) );
         return( FALSE );
      }

      WFCTRACEVAL( TEXT( "Deleting " ), log_to_delete );

      // OK. If the caller is going to delete a default NT log, let's make
      // really sure they want to do this. By using ASSERT, Visual C++ will
      // popup an Abort, Retry, or Ignore window.

      ASSERT( log_to_delete.CompareNoCase( TEXT( "Application" ) ) != 0 );
      ASSERT( log_to_delete.CompareNoCase( TEXT( "Security"    ) ) != 0 );
      ASSERT( log_to_delete.CompareNoCase( TEXT( "System"      ) ) != 0 );

      CRegistry registry;

      if ( registry.Connect( (HKEY) CRegistry::keyLocalMachine ) == FALSE )
      {
         m_ErrorCode = registry.GetErrorCode();
         return( FALSE );
      }

      CString log_key_name( TEXT( "SYSTEM\\CurrentControlSet\\Services\\EventLog\\" ) );

      // Should I delete the EVT file? Let's be safe and not do that right now

      log_key_name += log_to_delete;

      if ( registry.DeleteKey( log_key_name ) == FALSE )
      {
         m_ErrorCode = registry.GetErrorCode();
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

BOOL CEventLog::DeleteApplicationLog( LPCTSTR application_name )
{
   WFCLTRACEINIT( TEXT( "CEventLog::DeleteApplicationLog()" ) );
   ASSERT( application_name != NULL );

   // We were passed a pointer, do not trust it

   try
   {
      if ( application_name == NULL )
      {
         m_ErrorCode = ERROR_INVALID_PARAMETER;
         return( FALSE );
      }

      if ( application_name[ 0 ] == 0x00 )
      {
         return( FALSE );
      }

      WFCTRACEVAL( TEXT( "application is " ), CString( application_name ) );

      CRegistry registry;

      if ( registry.Connect( (HKEY) CRegistry::keyLocalMachine ) == FALSE )
      {
         m_ErrorCode = registry.GetErrorCode();
         return( FALSE );
      }

      // Thanks to Bejan Aminifard <bejan@ix.netcom.com> for finding a bug here

      CString log_key_name( TEXT( "SYSTEM\\CurrentControlSet\\Services\\EventLog\\Application\\" ) );

      log_key_name += application_name;

      if ( registry.DeleteKey( log_key_name ) == FALSE )
      {
         m_ErrorCode = registry.GetErrorCode();
         return( FALSE );
      }

      /*
      ** Microsoft has a bug in this area. Even though we deleted the application from the
      ** HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Services\EventLog\Application\
      ** registry area, they don't provide a way to delete the application from the 
      ** HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Services\EventLog\Application\Sources
      ** value. The application name is one of the strings in this REG_MULTI_SZ value. We
      ** still need to delete it from there. The names listed in this value appear in the 
      ** "Source" combobox of the Event Viewer application View->Filter Events... menu selection.
      */

      if ( registry.Open( TEXT( "SYSTEM\\CurrentControlSet\\Services\\EventLog\\Application" ) ) != FALSE )
      {
         CStringArray sources;

         if ( registry.GetValue( TEXT( "Sources" ), sources ) != FALSE )
         {
            int index             = 0;
            int number_of_sources = sources.GetSize();

            BOOL application_was_found = FALSE;

            while( index < number_of_sources )
            {
               if ( sources.GetAt( index ) == application_name )
               {
                  application_was_found = TRUE;
                  sources.RemoveAt( index );
                  index = number_of_sources;
               }

               index++;
            }

            if ( application_was_found != FALSE )
            {
               registry.SetValue( TEXT( "Sources" ), sources );
            }
         }
      }

      return( TRUE );
   }
   catch( ... )
   {
      m_ErrorCode = ERROR_EXCEPTION_IN_SERVICE;
      return( FALSE );
   }
}

BOOL CEventLog::DeregisterSource( void )
{
   WFCLTRACEINIT( TEXT( "CEventLog::DeregisterSource()" ) );

   BOOL return_value = TRUE;

   if ( m_EventSourceHandle != (HANDLE) INVALID_HANDLE_VALUE )
   {
      return_value = ::DeregisterEventSource( m_EventSourceHandle );

      if ( return_value == FALSE )
      {
         m_ErrorCode = ::GetLastError();
         WFCTRACEERROR( m_ErrorCode );
      }
      else
      {
         return_value = TRUE;
      }

      m_EventSourceHandle = (HANDLE) INVALID_HANDLE_VALUE;
   }

   return( return_value );
}

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

void CEventLog::Dump( CDumpContext& dump_context ) const
{
   CObject::Dump( dump_context );

   dump_context << TEXT( "m_LogHandle                 =  "  ) << m_LogHandle                 << TEXT( "\n" );
   dump_context << TEXT( "m_EventSourceHandle         =  "  ) << m_EventSourceHandle         << TEXT( "\n" );
   dump_context << TEXT( "m_ErrorCode                 =  "  ) << m_ErrorCode                 << TEXT( "\n" );
   dump_context << TEXT( "m_NumberOfBytesRead         =  "  ) << m_NumberOfBytesRead         << TEXT( "\n" );
   dump_context << TEXT( "m_NumberOfBytesInNextRecord =  "  ) << m_NumberOfBytesInNextRecord << TEXT( "\n" );
   dump_context << TEXT( "ComputerName                = \"" ) << ComputerName                << TEXT( "\"\n" );
   dump_context << TEXT( "LogName                     = \"" ) << LogName                     << TEXT( "\"\n" );
}

#endif // _DEBUG

BOOL CEventLog::EnumerateLogs( DWORD& enumerator ) const
{
   enumerator = 0;
   return( TRUE );
}

DWORD CEventLog::GetErrorCode( void ) const
{
   WFCLTRACEINIT( TEXT( "CEventLog::GetErrorCode()" ) );
   return( m_ErrorCode );
}

HANDLE CEventLog::GetHandle( void ) const
{
   return( m_LogHandle );
}

BOOL CEventLog::GetNextLog( DWORD& enumerator, CString& log_name )
{
   WFCLTRACEINIT( TEXT( "CEventLog::GetNextLog()" ) );

   CRegistry registry;

   BOOL return_value = FALSE;

   if ( ComputerName.GetLength() > 0 )
   {
      WFCTRACEVAL( TEXT( "Connecting to " ), ComputerName );
      return_value = registry.Connect( (HKEY) CRegistry::keyLocalMachine, ComputerName );
   }
   else
   {
      WFCTRACE( TEXT( "Connecting to local machine" ) );
      return_value = registry.Connect( (HKEY) CRegistry::keyLocalMachine, NULL );
   }

   if ( return_value == FALSE )
   {
      m_ErrorCode = registry.GetErrorCode();
      WFCTRACE( TEXT( "Can't Connect to HKEY_LOCAL_MACHINE because" ) );
      WFCTRACEERROR( m_ErrorCode ); 
      return( FALSE );
   }

   DWORD permissions = CRegistry::permissionEnumerateSubKeys | CRegistry::permissionRead;

   return_value = registry.Open( TEXT( "SYSTEM\\CurrentControlSet\\Services\\EventLog" ), static_cast< CRegistry::CreatePermissions >( permissions ) );

   if ( return_value == FALSE )
   {
      m_ErrorCode = registry.GetErrorCode();
      WFCTRACE( TEXT( "Can't Open SYSTEM\\CurrentControlSet\\Services\\EventLog because" ) );
      WFCTRACEERROR( m_ErrorCode ); 
      return( FALSE );
   }

   DWORD key_index = 0;

   CString class_name;

   while( registry.EnumerateKeys( key_index, log_name, class_name ) != FALSE )
   {
      if ( key_index == enumerator )
      {
         enumerator++;
         return( TRUE );
      }

      key_index++;
   }

   enumerator++;

   return( FALSE );
}

BOOL CEventLog::GetNumberOfRecords( DWORD& number_of_records )
{
   WFCLTRACEINIT( TEXT( "CEventLog::GetNumberOfRecords()" ) );

   number_of_records = 0; // Always start at a known state

   BOOL return_value = ::GetNumberOfEventLogRecords( m_LogHandle, &number_of_records );

   if ( return_value == FALSE )
   {
      m_ErrorCode = ::GetLastError();
      WFCTRACEVAL( TEXT( "GetNumberOfEventLogRecords() failed with " ), m_ErrorCode );
      WFCTRACEERROR( m_ErrorCode );
   }
   else
   {
      return_value = TRUE;
   }

   return( return_value );
}

DWORD CEventLog::GetOldestRecordNumber( void )
{
   WFCLTRACEINIT( TEXT( "CEventLog::GetOldestRecordNumber()" ) );

   DWORD return_value = 0;

   if ( ::GetOldestEventLogRecord( m_LogHandle, &return_value ) != FALSE )
   {
      return( return_value );
   }

   m_ErrorCode = ::GetLastError();

   WFCTRACE( TEXT( "GetOldestEventLogRecord() failed" ) );
   WFCTRACEERROR( m_ErrorCode );

   return( 0 );
}

BOOL CEventLog::NotifyChange( HANDLE event_handle, HANDLE user_log_handle )
{
   WFCLTRACEINIT( TEXT( "CEventLog::NotifyChange()" ) );
   ASSERT( event_handle != (HANDLE) INVALID_HANDLE_VALUE );

   if ( event_handle == (HANDLE) INVALID_HANDLE_VALUE )
   {
      m_ErrorCode = ERROR_INVALID_PARAMETER;
      return( FALSE );
   }

   if ( user_log_handle == (HANDLE) INVALID_HANDLE_VALUE || user_log_handle == NULL )
   {
      user_log_handle = m_LogHandle;
   }

   BOOL return_value = ::NotifyChangeEventLog( user_log_handle, event_handle );

   if ( return_value == FALSE )
   {
      m_ErrorCode = ::GetLastError();
      WFCTRACEERROR( m_ErrorCode );
   }
   else
   {
      return_value = TRUE;
   }

   return( return_value );
}

BOOL CEventLog::Open( LPCTSTR log_name, LPCTSTR name_of_computer )
{
   WFCLTRACEINIT( TEXT( "CEventLog::Open()" ) );
   ASSERT( log_name != NULL );

   /*
   ** name_of_computer can be NULL
   */

   // We were passed a pointer, do not trust it

   try
   {
      if ( log_name == NULL )
      {
         m_ErrorCode = ERROR_INVALID_PARAMETER;
         return( FALSE );
      }

      WFCTRACEVAL( TEXT( "Opening " ), CString( log_name ) );

      BOOL return_value = TRUE;

      m_LogHandle = ::OpenEventLog( name_of_computer, log_name );

      if ( m_LogHandle == NULL )
      {
         m_ErrorCode  = ::GetLastError();
         m_LogHandle  = (HANDLE) INVALID_HANDLE_VALUE;
         return_value = FALSE;

         WFCTRACEVAL( TEXT( "OpenEventLog failed with " ), m_ErrorCode );
         WFCTRACEERROR( m_ErrorCode );
      }
      else
      {
         if ( name_of_computer == NULL )
         {
            TCHAR computer_name[ MAX_PATH ];

            ZeroMemory( computer_name, sizeof( computer_name ) );

            DWORD size = DIMENSION_OF( computer_name );

            if ( ::GetComputerName( computer_name, &size ) != FALSE )
            {
               ComputerName = computer_name;
            }
            else
            {
               ComputerName.Empty();
            }
         }
         else
         {
           ComputerName = name_of_computer;
         }
      }

      return( return_value );
   }
   catch( ... )
   {
      m_ErrorCode = ERROR_EXCEPTION_IN_SERVICE;
      return( FALSE );
   }
}

BOOL CEventLog::OpenBackup( LPCTSTR name_of_backup_file, LPCTSTR name_of_computer )
{
   WFCLTRACEINIT( TEXT( "CEventLog::OpenBackup()" ) );
   ASSERT( name_of_backup_file != NULL );

   /*
   ** name_of_computer can be NULL
   */

   // We were passed a pointer, do not trust it

   try
   {
      if ( name_of_backup_file == NULL )
      {
         m_ErrorCode = ERROR_INVALID_PARAMETER;
         return( FALSE );
      }

      BOOL return_value = TRUE;

      m_LogHandle = ::OpenBackupEventLog( name_of_computer, name_of_backup_file );

      if ( m_LogHandle == NULL )
      {
         m_LogHandle = (HANDLE) INVALID_HANDLE_VALUE;
         m_ErrorCode = ::GetLastError();
         WFCTRACEERROR( m_ErrorCode );
         return_value = FALSE;
      }
      else
      {
         if ( name_of_computer == NULL )
         {
            TCHAR computer_name[ MAX_PATH ];

            ZeroMemory( computer_name, sizeof( computer_name ) );

            DWORD size = DIMENSION_OF( computer_name );

            if ( ::GetComputerName( computer_name, &size ) != FALSE )
            {
               ComputerName = computer_name;
            }
            else
            {
               ComputerName.Empty();
            }
         }
         else
         {
            ComputerName = name_of_computer;
         }
      }

      return( return_value );
   }
   catch( ... )
   {
      m_ErrorCode = ERROR_EXCEPTION_IN_SERVICE;
      return( FALSE );
   }
}

BOOL CEventLog::Read( DWORD record_number, CEventLogRecord& record, DWORD how_to_read )
{
   WFCLTRACEINIT( TEXT( "CEventLog::Read( CEventLogRecord )" ) );
   ASSERT( m_LogHandle != (HANDLE) INVALID_HANDLE_VALUE );

   // We were passed a pointer, do not trust

   try
   {
      if ( m_LogHandle == (HANDLE) INVALID_HANDLE_VALUE )
      {
         m_ErrorCode = ERROR_INVALID_PARAMETER;
         return( FALSE );
      }

      /*
      ** OK, time for a lecture.
      ** Microsoft coded ReadEventLog() so it would read as many records from
      ** the event log as would fit in the memory buffer you sent it. This is
      ** all well and good but it increases the number of calls when all you
      ** want to do is read one stinking little record at a time. Yes, this
      ** is an awfully inefficient way of doing it but it is simple.
      */

      BOOL return_value = FALSE;

      // First, find out how many bytes we need for this record

      BYTE temporary_buffer[ 1 ]; // a throw-away valid memory address

      DWORD number_of_bytes_to_read = 0;

      return_value = Read( record_number, temporary_buffer, number_of_bytes_to_read, how_to_read );

      m_ErrorCode = ::GetLastError();

      if ( return_value == FALSE && m_ErrorCode != ERROR_INSUFFICIENT_BUFFER )
      {
         WFCTRACEVAL( TEXT( "Can't determine how large record is because " ), m_ErrorCode );
         WFCTRACEERROR( m_ErrorCode );
         return( FALSE );
      }

      m_ErrorCode = 0;

      // m_NumberOfBytesInNextRecord now contains the size our buffer should be

      BYTE * buffer = NULL;
      
      try
      {
         buffer = new BYTE[ m_NumberOfBytesInNextRecord ];
      }
      catch( ... )
      {
         buffer = NULL;
      }

      if ( buffer == NULL )
      {
         return( FALSE );
      }

      // Always always always zero your buffers

      ZeroMemory( buffer, m_NumberOfBytesInNextRecord );

      return_value = Read( record_number, buffer, m_NumberOfBytesInNextRecord, how_to_read );

      if ( return_value == FALSE )
      {
         m_ErrorCode = ::GetLastError();
         WFCTRACEVAL( TEXT( "Read FAILED because " ), m_ErrorCode );
         WFCTRACEERROR( m_ErrorCode );
      }
      else
      {
         WFCTRACE( TEXT( "Read OK" ) );
         record.Copy( (EVENTLOGRECORD *) buffer );
      }

      delete [] buffer;

      return( return_value );
   }
   catch( ... )
   {
      m_ErrorCode = ERROR_EXCEPTION_IN_SERVICE;
      return( FALSE );
   }
}

BOOL CEventLog::Read( DWORD record_number, LPVOID buffer, DWORD& number_of_bytes_to_read, DWORD how_to_read )
{
   WFCLTRACEINIT( TEXT( "CEventLog::Read()" ) );
   ASSERT( buffer != NULL );
   ASSERT( m_LogHandle != (HANDLE) INVALID_HANDLE_VALUE );

   // We were passed a pointer, do not trust

   try
   {
      if ( buffer == NULL || m_LogHandle == (HANDLE) INVALID_HANDLE_VALUE )
      {
         m_ErrorCode = ERROR_INVALID_PARAMETER;
         return( FALSE );
      }

      BOOL return_value = ::ReadEventLog( m_LogHandle,
                                          how_to_read,
                                          record_number,
                                          buffer,
                                          number_of_bytes_to_read,
                                         &m_NumberOfBytesRead,
                                         &m_NumberOfBytesInNextRecord );

      if ( return_value == FALSE )
      {
         m_ErrorCode = ::GetLastError();
         WFCTRACEVAL( TEXT( "ReadEventLog(), failed with " ), m_ErrorCode );
         WFCTRACEERROR( m_ErrorCode );
      }
      else
      {
         return_value = TRUE;
      }

      return( return_value );
   }
   catch( ... )
   {
      m_ErrorCode = ERROR_EXCEPTION_IN_SERVICE;
      return( FALSE );
   }
}

BOOL CEventLog::RegisterSource( LPCTSTR source_name, LPCTSTR name_of_computer )
{
   WFCLTRACEINIT( TEXT( "CEventLog::RegisterSource()" ) );
   ASSERT( source_name != NULL );

   /*
   ** name_of_computer can be NULL
   */

   // We were passed a pointer, do not trust it

   try
   {
      if ( source_name == NULL )
      {
         m_ErrorCode = ERROR_INVALID_PARAMETER;
         return( FALSE );
      }

      WFCTRACEVAL( TEXT( "source is " ), CString( source_name ) );

      BOOL return_value = TRUE;

      if ( m_EventSourceHandle != (HANDLE) INVALID_HANDLE_VALUE )
      {
         DeregisterSource();
      }

      m_EventSourceHandle = ::RegisterEventSource( name_of_computer, source_name );

      if ( m_EventSourceHandle == NULL )
      {
         m_ErrorCode         = ::GetLastError();
         WFCTRACE( TEXT( "RegisterEventSource returned NULL" ) );
         WFCTRACEERROR( m_ErrorCode );
         m_EventSourceHandle = (HANDLE) INVALID_HANDLE_VALUE;
         return_value        = FALSE;
      }

      return( return_value );
   }
   catch( ... )
   {
      m_ErrorCode = ERROR_EXCEPTION_IN_SERVICE;
      return( FALSE );
   }
}

BOOL CEventLog::Report( EventType event_type,
                        WORD      category,
                        DWORD     event_identifier,
                        WORD      number_of_strings,
                        LPCTSTR * string_array,
                        DWORD     number_of_raw_data_bytes,
                        LPVOID    raw_data_buffer,
                        PSID      user_security_identifier )
{
   WFCLTRACEINIT( TEXT( "CEventLog::Report()" ) );

   BYTE security_identifier_buffer[ 4096 ];

   DWORD size_of_security_identifier_buffer = sizeof( security_identifier_buffer );

   // We were passed a pointer, don't trust it

   try
   {
      if ( user_security_identifier == NULL )
      {
         TCHAR user_name[ 256 ];
         DWORD size_of_user_name  = DIMENSION_OF( user_name );

         TCHAR domain_name[ 256 ];
         DWORD size_of_domain_name = DIMENSION_OF( domain_name );

         SID_NAME_USE type_of_security_identifier;

         ::ZeroMemory( user_name, sizeof( user_name ) );
         ::ZeroMemory( domain_name, sizeof( domain_name ) );
         ::ZeroMemory( security_identifier_buffer, size_of_security_identifier_buffer );

         ::GetUserName( user_name, &size_of_user_name );

         if ( ::LookupAccountName( NULL,
                                   user_name,
                                  &security_identifier_buffer,
                                  &size_of_security_identifier_buffer,
                                   domain_name,
                                  &size_of_domain_name,
                                  &type_of_security_identifier ) != FALSE )
         {
            user_security_identifier = security_identifier_buffer;
         }
      }

      BOOL return_value = FALSE;

      if ( m_EventSourceHandle != (HANDLE) INVALID_HANDLE_VALUE )
      {
         return_value = ::ReportEvent( m_EventSourceHandle,
                                (WORD) event_type,
                                       category,
                                       event_identifier,
                                       user_security_identifier,
                                       number_of_strings,
                                       number_of_raw_data_bytes,
                                       string_array,
                                       raw_data_buffer );

         if ( return_value == FALSE )
         {
            m_ErrorCode = ::GetLastError();
            WFCTRACEERROR( m_ErrorCode );
         }
         else
         {
            return_value = TRUE;
         }
      }
      else
      {
         m_ErrorCode = ERROR_INVALID_HANDLE;
      }

     return( return_value );
   }
   catch( ... )
   {
      m_ErrorCode = ERROR_EXCEPTION_IN_SERVICE;
      return( FALSE );
   }
}

BOOL CEventLog::Report( LPCTSTR log_name, DWORD message_string_resource_identifier, WORD number_of_strings, LPCTSTR* string_array )
{
   WFCLTRACEINIT( TEXT( "CEventLog::Report()" ) );
   ASSERT( log_name != NULL );

   if ( log_name == NULL )
   {
      m_ErrorCode = ERROR_INVALID_PARAMETER;
      return( FALSE );
   }

   // We were passed a pointer, don't trust it

   try
   {
      if ( string_array == (LPCTSTR *) NULL )
      {
         m_ErrorCode = ERROR_INVALID_HANDLE;
         return( FALSE );
      }

      if ( RegisterSource( log_name ) != FALSE )
      {
         if ( Report( eventError, 0, message_string_resource_identifier, number_of_strings, string_array ) == FALSE )
         {
            DeregisterSource();
            return( FALSE );
         }

         DeregisterSource();
      }
      else
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

void CEventLog::ReportError( LPCTSTR string_to_report )
{
   WFCLTRACEINIT( TEXT( "CEventLog::ReportError()" ) );

   LPCTSTR string_array[ 1 ];

   if ( string_to_report == (LPCTSTR) NULL )
   {
      string_array[ 0 ] = TEXT( "CEventLog::ReportError( NULL )" );
   }
   else
   {
      string_array[ 0 ] = string_to_report;
   }

   Report( eventError, 0, 0, 1, string_array );
}

void CEventLog::ReportInformation( LPCTSTR string_to_report )
{
   WFCLTRACEINIT( TEXT( "CEventLog::ReportInformation()" ) );

   LPCTSTR string_array[ 1 ];

   if ( string_to_report == (LPCTSTR) NULL )
   {
      string_array[ 0 ] = TEXT( "CEventLog::ReportInformation( NULL )" );
   }
   else
   {
      string_array[ 0 ] = string_to_report;
   }

   Report( eventInformation, 0, 0, 1, string_array );
}

// End of source

#if 0
<HTML>

<HEAD>
<TITLE>WFC - CEventLog</TITLE>
<META name="keywords" content="WFC, MFC extension library, freeware class library, Win32, source code">
<META name="description" content="The C++ class that handles the Win32 event logger.">
</HEAD>

<BODY>

<H1>CEventLog</H1>
$Revision: 38 $
<HR>

<H2>Description</H2>

This class handles playing with NT's Event Logger.

<H2>Data Members</H2>

<B>ComputerName</B> - Name of the computer where the event log resides.<P>
<B>LogName</B> - Name of the log you're playing with.

<H2>Methods</H2>

<DL COMPACT>

<DT><PRE>BOOL <B><A NAME="Backup">Backup</A></B>( LPCTSTR name_of_backup_file )</PRE><DD>
Saves the log to <CODE>name_of_backup_file</CODE>.

<DT><PRE>BOOL <B><A NAME="Clear">Clear</A></B>( LPCTSTR name_of_backup_file )</PRE><DD>
Empties the event log and will optionally save it to a backup file specified
by <CODE>name_of_backup_file</CODE>. If <CODE>name_of_backup_file</CODE>
is NULL, no backup is made.

<DT><PRE>BOOL <B><A NAME="Close">Close</A></B>( void )</PRE><DD>
Closes your session with the event log.

<DT><PRE>BOOL <B><A NAME="CreateApplicationLog">CreateApplicationLog</A></B>( LPCTSTR application_name, LPCTSTR file_containing_message_table_resource, DWORD supported_types )</PRE><DD>
This creates a source of strings for the event
log. Basically, it registers your executable with the event logger.
This allows the event logger to go to your executable's message
table resource for strings to display to the user via the Event Viewer.

<DT><PRE>BOOL <B><A NAME="CreateCustomLog">CreateCustomLog</A></B>( LPCTSTR log_name,
                      LPCTSTR log_filename = NULL,
                      DWORD   maximum_file_size = 0x800000,
                      DWORD   overwrite_after_this_many_seconds = 604800 )</PRE><DD>
This allows you to create your own custom event log file. The
<CODE>maximum_file_size</CODE> specifies the maximum size of the event
log file. The <CODE>overwrite_after_this_many_seconds</CODE> let's
you specify the age of an entry before it will be overwritten. The
default for these parameters is 8MB file size and 7 days before
events will be overwritten.

<DT><PRE><B><A NAME="Delete">Delete</A></B>( LPCTSTR log_name )</PRE><DD>
This will delete an event log. <STRONG>WARNING!</STRONG>
This is a very dangerous method. It will delete any and all
event logs in the system. Use with caution.

<DT><PRE>BOOL <B><A NAME="DeleteApplicationLog">DeleteApplicationLog</A></B>( LPCTSTR application_name )</PRE><DD>
Disconnects the application from the Event Log.

<DT><PRE>BOOL <B><A NAME="DeregisterSource">DeregisterSource</A></B>( void )</PRE><DD>
Deregisters the source. It basically releases the source of event strings.

<DT><PRE>BOOL <B><A NAME="EnumerateLogs">EnumerateLogs</A></B>( DWORD&amp; enumerator ) const</PRE><DD>
Initializes <CODE>enumerator</CODE> so you can enumerate through
the logs that are installed on the system.

<DT><PRE>DWORD <B><A NAME="GetErrorCode">GetErrorCode</A></B>( void ) const</PRE><DD>
Retrieves the error code. Call this function
to find out why any other class member returned FALSE.

<DT><PRE>HANDLE <B><A NAME="GetHandle">GetHandle</A></B>( void ) const</PRE><DD>
Returns the encapsulated event log handle so you can
call the Win32 API directly (i.e. you don't have to use
this class).

<DT><PRE>BOOL <B><A NAME="GetNextLog">GetNextLog</A></B>( DWORD&amp; enumerator, CString&amp; log_name )</PRE><DD>
Allows you to get the next log while enumerating them.
The <CODE>enumerator</CODE> must be initialized via the
<B><A HREF="#EnumerateLogs">EnumerateLogs</A></B>() method.
Normally, when you enumerate the logs, you will get the
default three logs:

<UL>
<LI>Application
<LI>Security
<LI>System
</UL>

However, when an application creates a custom log, it will show up
in this list.

<DT><PRE>BOOL <B><A NAME="GetNumberOfRecords">GetNumberOfRecords</A></B>( DWORD&amp; number_of_records )</PRE><DD>
This function is gets the number of records in the log.

<DT><PRE>DWORD <B><A NAME="GetOldestRecordNumber">GetOldestRecordNumber</A></B>( void )</PRE><DD>
Returns the record number of the oldest record in the log. If it returns zero,
the call failed.

<DT><PRE>BOOL <B><A NAME="NotifyChange">NotifyChange</A></B>( HANDLE event_handle, HANDLE log_handle = NULL )</PRE><DD>
Allows you to watch a log and be notified if it changes.

<DT><PRE>BOOL <B><A NAME="OpenBackup">OpenBackup</A></B>( LPCTSTR name_of_backup_file, LPCTSTR name_of_computer = NULL )</PRE><DD>
Opens a log that has been backed up to a file. If <CODE>name_of_computer</CODE>
is NULL, the local backup is openend.

<DT><PRE>BOOL <B><A NAME="Open">Open</A></B>( LPCTSTR log_name, LPCTSTR name_of_computer = NULL )</PRE><DD>
Opens a specified log on a specified machine. If <CODE>name_of_computer</CODE>
is NULL, the local log is openend.

<DT><PRE>BOOL <B><A NAME="Read">Read</A></B>( DWORD  record_number, 
           LPVOID buffer, 
           DWORD&amp; number_of_bytes_to_read, 
           DWORD  how_to_read = EVENTLOG_FORWARDS_READ | EVENTLOG_SEQUENTIAL_READ )
BOOL <B>Read</B>( DWORD record_number,
                  <A HREF="CEVENT~1.HTM">CEventLogRecord</A>&amp; record,
                  DWORD how_to_read = EVENTLOG_FORWARDS_READ | EVENTLOG_SEQUENTIAL_READ )</PRE><DD>
Reads a specific record from the log.

<DT><PRE>BOOL <B><A NAME="RegisterSource">RegisterSource</A></B>( LPCTSTR source_name, LPCTSTR name_of_computer )</PRE><DD>
Basically loads the event strings for <CODE>source_name</CODE>. If <CODE>name_of_computer</CODE>
is NULL, the local source is openend.

<DT><PRE>BOOL <B><A NAME="Report">Report</A></B>( EventType event_type,
             WORD      category,
             DWORD     event_id,
             WORD      number_of_strings   = 0,
             LPCTSTR * string_array        = NULL,
             DWORD     number_of_raw_bytes = 0,
             LPVOID    raw_data_buffer     = NULL,
             PSID      user_sid            = NULL )</PRE><DD>
Makes an entry into the log. The <CODE>event_type</CODE> parameter
may be one of the following:

<UL>
<LI>eventError
<LI>eventWarning
<LI>eventInformation
<LI>eventSuccess
<LI>eventFailure
</UL>

<DT><PRE>BOOL <B><A NAME="ReportError">ReportError</A></B>( LPCTSTR string_to_report )</PRE><DD>
Makes an entry into the log flagged as an Error message. This is the lazy man's
way of writing to the event log. It calls <B><A HREF="#Report">Report</A></B>() with eventError.

<DT><PRE>BOOL <B><A NAME="ReportInformation">ReportInformation</A></B>( LPCTSTR string_to_report )</PRE><DD>
Makes an entry into the log flagged as an Informational message. This is the
lazy man's way of writing to the event log. It calls <B><A HREF="#Report">Report</A></B>() with
eventInformation.

</DL>

<H2>Example</H2>

<PRE><CODE>#include &lt;wfc.h&gt;
void test_CEventLog( void )
{
   <A HREF="WfcTrace.htm">WFCTRACEINIT</A>( TEXT( &quot;test_CEventLog()&quot; ) );

   <B>CEventLog</B> log( TEXT( &quot;Dodah&quot; ) );

   LPCTSTR string_array[ 1 ];

   string_array[ 0 ] = TEXT( &quot;Hello World&quot; );

   log.<A HREF="#Report">Report</A>( CEventLog::eventInformation, 0, 0, 1, string_array );
   log.<A HREF="#ReportInformation">ReportInformation</A>( TEXT( &quot;ReportInformation&quot; ) );
   log.<A HREF="#ReportError">ReportError</A>( TEXT( &quot;ReportError&quot; ) );
}</CODE></PRE>

<H2>API's Used</H2>

<UL>
<LI>BackupEventLog
<LI>ClearEventLog
<LI>CloseEventLog
<LI>DeregisterEventSource
<LI>GetComputerName
<LI>GetNumberOfEventLogRecords
<LI>GetOldestEventLogRecord
<LI>GetUserName
<LI>LookupAccountName
<LI>NotifyChangeEventLog
<LI>OpenBackupEventLog
<LI>OpenEventLog
<LI>ReadEventLog
<LI>RegisterEventSource
<LI>ReportEvent
</UL>

<HR><I>Copyright, 2000, <A HREF="mailto:wfc@pobox.com">Samuel R. Blackburn</A></I><BR>
$Workfile: cevntlog.cpp $<BR>
$Modtime: 3/17/00 4:28p $

</BODY>

</HTML>
#endif
