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
** $Workfile: cnetwork.cpp $
** $Revision: 41 $
** $Modtime: 5/02/00 6:03p $
** $Reuse Tracing Code: 1 $
*/

#if defined( _DEBUG ) && ! defined( WFC_STL )
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

#if ! defined(  WFC_NO_SERIALIZATION )
IMPLEMENT_SERIAL( CNetwork, CObject, 1 )
#endif // WFC_NO_SERIALIZATION

#if defined( _DEBUG ) && ! defined( WFC_STL )
#define new DEBUG_NEW
#endif // _DEBUG

/*
** CNetwork stuff
*/

CNetwork::CNetwork( LPCTSTR machine_name )
{
   WFCLTRACEINIT( TEXT( "CNetwork::CNetwork( LPCTSTR )" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   m_Initialize();
   Open( machine_name );
}

CNetwork::~CNetwork()
{
   WFCLTRACEINIT( TEXT( "CNetwork::~CNetwork()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   Close();
   m_Initialize();
}

BOOL CNetwork::AbortShutdown( void )
{
   WFCLTRACEINIT( TEXT( "CNetwork::AbortShutdown()" ) );

   HANDLE token_handle = NULL;

   if ( ::OpenProcessToken( ::GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &token_handle ) == FALSE )
   {
      m_ErrorCode = ::GetLastError();
      WFCTRACE( TEXT( "Can't OpenProcessToken()" ) );
      WFCTRACEERROR( m_ErrorCode );
      return( FALSE );
   }

   TOKEN_PRIVILEGES token_privileges;

   ::ZeroMemory( &token_privileges, sizeof( token_privileges ) );

   LPCSTR machine_name = NULL;

   // Check to see if we've opened ourselves...

   TCHAR this_machine_name[ 1024 ];

   ::ZeroMemory( this_machine_name, sizeof( this_machine_name ) );

   DWORD temp_dword = 1024;

   if ( ::GetComputerName( this_machine_name, &temp_dword ) == FALSE )
   {
      m_ErrorCode = ::GetLastError();
      WFCTRACE( TEXT( "Can't GetComputerName" ) );
      WFCTRACEERROR( m_ErrorCode );
      return( FALSE );
   }

   // Something changed in service pack 3 for NT 3.51. You used to be able
   // to specify the local machine name and get SE_REMOTE_SHUTDOWN privilege
   // and shut down the machine. Not any more. You can no longer remotely
   // shut down your local machine. And no, I couldn't find this documented
   // anywhere...

   if ( m_MachineName.CompareNoCase( this_machine_name ) == 0 )
   {
      machine_name = NULL;
   }

   if ( machine_name != NULL )
   {
      // Shutdown a machine somewhere on the network

      if ( ::LookupPrivilegeValue( m_MachineName, SE_REMOTE_SHUTDOWN_NAME, &token_privileges.Privileges[ 0 ].Luid ) == FALSE )
      {
         m_ErrorCode = ::GetLastError();
         WFCTRACE( TEXT( "Can't LookupPrivilegeValue for remote machine" ) );
         WFCTRACEERROR( m_ErrorCode );
         return( FALSE );
      }
   }
   else
   {
      // Shutdown this computer

      if ( ::LookupPrivilegeValue( NULL, SE_SHUTDOWN_NAME, &token_privileges.Privileges[ 0 ].Luid ) == FALSE )
      {
         m_ErrorCode = ::GetLastError();
         WFCTRACE( TEXT( "Can't LookupPrivilege for local machine" ) );
         WFCTRACEERROR( m_ErrorCode );
         return( FALSE );
      }
   }

   token_privileges.PrivilegeCount             = 1;
   token_privileges.Privileges[ 0 ].Attributes = SE_PRIVILEGE_ENABLED;

   if ( ::AdjustTokenPrivileges( token_handle, FALSE, &token_privileges, 0, (PTOKEN_PRIVILEGES) NULL, 0 ) == FALSE )
   {
      m_ErrorCode = ::GetLastError();
      WFCTRACE( TEXT( "Can't AdjustTokenPrivileges" ) );
      WFCTRACEERROR( m_ErrorCode );
      return( FALSE );
   }

   wfc_close_handle( token_handle );

   if ( machine_name != NULL )
   {
      // AbortSystemShutdown() is not const correct
      // The first parameter of AbortSystemShutdown() is a LPTSTR when it should be 
      // a LPCTSTR (const). Because it ain't, we gotta code around it.

      _tcscpy( this_machine_name, (LPCTSTR) m_MachineName );

      if ( ::AbortSystemShutdown( this_machine_name ) == FALSE )
      {
         m_ErrorCode = ::GetLastError();
         WFCTRACE( TEXT( "Can't AbortSystemShutdown on remote machine" ) );
         WFCTRACEERROR( m_ErrorCode );
         return( FALSE );
      }
   }
   else
   {
      if ( ::AbortSystemShutdown( NULL ) == FALSE )
      {
         m_ErrorCode = ::GetLastError();
         WFCTRACE( TEXT( "Can't AbortSystemShutdown on local machine" ) );
         WFCTRACEERROR( m_ErrorCode );
         return( FALSE );
      }
   }

   return( TRUE );
}

void CNetwork::Close( void )
{
   WFCLTRACEINIT( TEXT( "CNetwork::Close()" ) );

   if ( m_WideMachineName != NULL )
   {
      WFCTRACE( TEXT( "Deleting wide machine name" ) );
      delete [] m_WideMachineName;
      m_WideMachineName = NULL;
   }

   if ( m_WideDoubleBackslashPreceededMachineName != NULL )
   {
      WFCTRACE( TEXT( "Deleting wide double backslash preceeded machine name" ) );
      delete [] m_WideDoubleBackslashPreceededMachineName;
      m_WideDoubleBackslashPreceededMachineName = NULL;
   }

   if ( m_PortBuffer != NULL )
   {
      WFCTRACE( TEXT( "Deleting port array" ) );
      delete [] m_PortBuffer;
      m_PortBuffer = NULL;
   }

   m_MachineName.Empty();
   m_FriendlyMachineName.Empty();
   m_PortNumber    = 0;
   m_NumberOfPorts = 0;
}

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

void CNetwork::Dump( CDumpContext& dump_context ) const
{
   CObject::Dump( dump_context );

   dump_context << TEXT( "m_MachineName         = \"" ) << m_MachineName         << TEXT( "\"\n" );
   dump_context << TEXT( "m_FriendlyMachineName = \"" ) << m_FriendlyMachineName << TEXT( "\"\n" );
   dump_context << TEXT( "m_PortNumber          = "   ) << m_PortNumber          << TEXT( "\n"   );
   dump_context << TEXT( "m_NumberOfPorts       = "   ) << m_NumberOfPorts       << TEXT( "\n"   );
   dump_context << TEXT( "m_ErrorCode           = "   ) << m_ErrorCode           << TEXT( "\n"   );
}

#endif // _DEBUG

BOOL CNetwork::EnumeratePorts( void )
{
   WFCLTRACEINIT( TEXT( "CNetwork::EnumeratePorts()" ) );

   m_PortNumber = 0;

   if ( m_PortBuffer != NULL )
   {
      WFCTRACE( TEXT( "Clearing data from previous call" ) );
      delete [] m_PortBuffer;
      m_PortBuffer    = NULL;
      m_NumberOfPorts = 0;
   }

   // First, we call EnumPorts to find out how big our buffer needs to be...

   DWORD number_of_bytes_needed = 0;

   BYTE pseudo_buffer[ 10 ];

   BOOL return_value = FALSE;

   // EnumPorts is not const correct, therefore we have to code around it...

   TCHAR machine_name[ MAX_PATH ];

   ::ZeroMemory( machine_name, sizeof( machine_name ) );

   _tcscpy( machine_name, CString( m_WideDoubleBackslashPreceededMachineName ) );

   return_value = ::EnumPorts( machine_name,
                               1,
                               pseudo_buffer,
                               sizeof( pseudo_buffer ),
                              &number_of_bytes_needed,
                              &m_NumberOfPorts );

   m_ErrorCode = ::GetLastError();

   if ( return_value != FALSE )
   {
      WFCTRACE( TEXT( "Something is bad wrong." ) );
      WFCTRACEERROR( m_ErrorCode );
      // Something bad wrong here...

      return( FALSE );
   }

   if ( m_ErrorCode != ERROR_INSUFFICIENT_BUFFER )
   {
      WFCTRACEVAL( TEXT( "Unexpected error at line " ), __LINE__ );
      WFCTRACEERROR( m_ErrorCode );
      return( FALSE );
   }

   WFCTRACEVAL( TEXT( "Allocating a buffer of size " ), number_of_bytes_needed );

   try
   {
      m_PortBuffer = new BYTE[ number_of_bytes_needed ];
   }
   catch( ... )
   {
      m_PortBuffer = NULL;
   }

   if ( m_PortBuffer == NULL )
   {
      m_ErrorCode = ::GetLastError();
      WFCTRACE( TEXT( "Can't get memory for new data buffer" ) );
      WFCTRACEERROR( m_ErrorCode );
      return( FALSE );
   }

   return_value = ::EnumPorts( machine_name,
                               1,
                               m_PortBuffer,
                               number_of_bytes_needed,
                              &number_of_bytes_needed,
                              &m_NumberOfPorts );

   if ( return_value == FALSE )
   {
      m_ErrorCode = ::GetLastError();
      WFCTRACE( TEXT( "Can't enumerate ports" ) );
      WFCTRACEERROR( m_ErrorCode );
      delete [] m_PortBuffer;
      m_PortBuffer    = NULL;
      m_NumberOfPorts = 0;
   }
   else
   {
      return_value = TRUE;
   }

   return( return_value );
}

BOOL CNetwork::GetNext( CPortInformation& port )
{
   WFCLTRACEINIT( TEXT( "CNetwork::GetNext( CPortInformation& )" ) );

   if ( m_PortBuffer == NULL )
   {
      WFCTRACE( TEXT( "You didn't call EnumeratePorts yet" ) );
      return( FALSE );
   }

   if ( m_PortNumber < m_NumberOfPorts )
   {
      PORT_INFO_1 *port_p = (PORT_INFO_1 *) m_PortBuffer;

      port.Copy( (PORT_INFO_1 *) &port_p[ m_PortNumber ] );
      m_PortNumber++;
      return( TRUE );
   }
   else
   {
      // We've retrieved the last one so clean up...

      delete [] m_PortBuffer;
      m_PortBuffer    = NULL;
      m_PortNumber    = 0;
      m_NumberOfPorts = 0;
      return( FALSE );
   }
}

DWORD CNetwork::GetErrorCode( void ) const
{
   WFCLTRACEINIT( TEXT( "CNetwork::GetErrorCode()" ) );
   return( m_ErrorCode );
}

void CNetwork::GetFriendlyMachineName( CString& machine_name ) const
{
   machine_name = m_FriendlyMachineName;
}

LPCTSTR CNetwork::GetMachineName( void )
{
   WFCLTRACEINIT( TEXT( "CNetwork::GetMachineName()" ) );
   return( (LPCTSTR) m_MachineName );
}

BOOL CNetwork::GetTime( CTime& machine_time )
{
   WFCLTRACEINIT( TEXT( "CNetwork::GetTime( CTime )" ) );

   TIME_OF_DAY_INFO * time_of_day = NULL;

   if ( ::NetRemoteTOD( m_WideMachineName, (LPBYTE *) &time_of_day ) == NERR_Success )
   {
      machine_time = CTime( time_of_day->tod_elapsedt );
      return( TRUE );
   }
   else
   {
      m_ErrorCode = ::GetLastError();
      WFCTRACEERROR( m_ErrorCode );
      return( FALSE );
   }
}

BOOL CNetwork::GetTime( CSystemTime& machine_time )
{
   WFCLTRACEINIT( TEXT( "CNetwork::GetTime( CSystemTime )" ) );

   TIME_OF_DAY_INFO * time_of_day = NULL;

   if ( ::NetRemoteTOD( m_WideMachineName, (LPBYTE *) &time_of_day ) == NERR_Success )
   {
      machine_time.Copy( time_of_day );
      return( TRUE );
   }
   else
   {
      m_ErrorCode = ::GetLastError();
      WFCTRACEERROR( m_ErrorCode );
      return( FALSE );
   }
}

BOOL CNetwork::IsRebootable( void )
{
   WFCLTRACEINIT( TEXT( "CNetwork::IsRebootable()" ) );

   HANDLE token_handle = NULL;

   if ( ::OpenProcessToken( ::GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &token_handle ) == FALSE )
   {
      m_ErrorCode = ::GetLastError();
      WFCTRACE( TEXT( "Can't OpenProcessToken" ) );
      WFCTRACEERROR( m_ErrorCode );
      return( FALSE );
   }

   TOKEN_PRIVILEGES token_privileges;

   ::ZeroMemory( &token_privileges, sizeof( token_privileges ) );

   LPCSTR machine_name = NULL;

   // Check to see if we've opened ourselves...

   TCHAR this_machine_name[ 1024 ];

   ::ZeroMemory( this_machine_name, sizeof( this_machine_name ) );

   DWORD temp_dword = 1024;

   if ( ::GetComputerName( this_machine_name, &temp_dword ) == FALSE )
   {
      m_ErrorCode = ::GetLastError();
      WFCTRACE( TEXT( "Can't GetComputerName" ) );
      WFCTRACEERROR( m_ErrorCode );
      return( FALSE );
   }

   // Something changed in service pack 3 for NT 3.51. You used to be able
   // to specify the local machine name and get SE_REMOTE_SHUTDOWN privilege
   // and shut down the machine. Not any more. You can no longer remotely
   // shut down your local machine. And no, I couldn't find this documented
   // anywhere...

   if ( m_MachineName.CompareNoCase( this_machine_name ) == 0 )
   {
      machine_name = NULL;
   }

   if ( machine_name != NULL )
   {
      // Shutdown a machine somewhere on the network

      if ( ::LookupPrivilegeValue( m_MachineName, SE_REMOTE_SHUTDOWN_NAME, &token_privileges.Privileges[ 0 ].Luid ) == FALSE )
      {
         m_ErrorCode = ::GetLastError();
         WFCTRACE( TEXT( "Can't LookupPrivilegeValue for remote machine" ) );
         WFCTRACEERROR( m_ErrorCode );
         return( FALSE );
      }
   }
   else
   {
      // Shutdown this computer

      if ( ::LookupPrivilegeValue( NULL, SE_SHUTDOWN_NAME, &token_privileges.Privileges[ 0 ].Luid ) == FALSE )
      {
         m_ErrorCode = ::GetLastError();
         WFCTRACE( TEXT( "Can't LookupPrivilegeValue for local machine" ) );
         WFCTRACEERROR( m_ErrorCode );
         return( FALSE );
      }
   }

   token_privileges.PrivilegeCount             = 1;
   token_privileges.Privileges[ 0 ].Attributes = SE_PRIVILEGE_ENABLED;

   if ( ::AdjustTokenPrivileges( token_handle, FALSE, &token_privileges, 0, (PTOKEN_PRIVILEGES) NULL, 0 ) == FALSE )
   {
      m_ErrorCode = ::GetLastError();
      WFCTRACE( TEXT( "Can't AdjustTokenPrivileges" ) );
      WFCTRACEERROR( m_ErrorCode );
      return( FALSE );
   }

   // If we get this far it means we can reboot the machine...

   return( TRUE );
}

void CNetwork::m_Initialize( void )
{
   WFCLTRACEINIT( TEXT( "CNetwork::m_Initialize()" ) );
   m_MachineName.Empty();
   m_FriendlyMachineName.Empty();
   m_WideMachineName = NULL;
   m_WideDoubleBackslashPreceededMachineName = NULL;
   m_ErrorCode       = 0;
   m_PortBuffer      = NULL;
   m_NumberOfPorts   = 0;
   m_PortNumber      = 0;
}

void CNetwork::Open( LPCTSTR machine_name )
{
   WFCLTRACEINIT( TEXT( "CNetwork::Open()" ) );

   // First, make sure we're closed...

   Close();

   // We were passed a pointer, don't trust it

   try
   {
      if ( machine_name != NULL )
      {
         // Thanks go to Ullrich Pollahne (u.pollaehne@online.de)
         // for finding a bug here. I was not correctly counting
         // the number of bytes needed for a buffer.

         int additional_characters = 1; // For the 0x00 at the end

         CString temporary_machine_name( machine_name );

         WFCTRACEVAL( TEXT( "Opening " ), temporary_machine_name );

         // Strip off the \\ if present

         if ( temporary_machine_name.GetLength() > 1 )
         {
            if ( temporary_machine_name.GetAt( 0 ) == TEXT( '\\' ) )
            {
               temporary_machine_name = temporary_machine_name.Right( temporary_machine_name.GetLength() - 1 );
               additional_characters++;
            }

            if ( temporary_machine_name.GetAt( 0 ) == TEXT( '\\' ) )
            {
               temporary_machine_name = temporary_machine_name.Right( temporary_machine_name.GetLength() - 1 );
               additional_characters++;
            }
         }

         // We now have a backslash-free name

         m_FriendlyMachineName = temporary_machine_name;

         try
         {
            m_WideMachineName = new WCHAR[ temporary_machine_name.GetLength() + additional_characters ];
         }
         catch( ... )
         {
            m_WideMachineName = NULL;
         }

         if ( m_WideMachineName != NULL )
         {
#if defined( UNICODE )
            ::_tcscpy( m_WideMachineName, machine_name );
#else
            ::ASCII_to_UNICODE( machine_name, m_WideMachineName );
#endif
         }

         m_MachineName = machine_name;

         // Now, add those stinking backslashes

         temporary_machine_name  = TEXT( "\\\\" );
         temporary_machine_name += m_FriendlyMachineName;

         try
         {
            m_WideDoubleBackslashPreceededMachineName = new WCHAR[ temporary_machine_name.GetLength() + 1 ];
         }
         catch( ... )
         {
            m_WideDoubleBackslashPreceededMachineName = NULL;
         }

         if ( m_WideDoubleBackslashPreceededMachineName != NULL )
         {
#if defined( UNICODE )
            ::_tcscpy( m_WideDoubleBackslashPreceededMachineName, temporary_machine_name );
#else
            ::ASCII_to_UNICODE( temporary_machine_name, m_WideDoubleBackslashPreceededMachineName );
#endif
         }
      }
      else
      {
         // The machine name is NULL, that means the user wants to play
         // with the local machine. That's OK, all we need to do is put
         // the name of the computer into m_FriendlyName

         TCHAR this_machine_name[ MAX_COMPUTERNAME_LENGTH + 1 ];

         DWORD string_size = MAX_COMPUTERNAME_LENGTH + 1;

         ZeroMemory( this_machine_name, sizeof( this_machine_name ) );

         if ( ::GetComputerName( this_machine_name, &string_size ) == FALSE )
         {
            // CRAP! The computer name is too long.

            TCHAR * new_string = new TCHAR[ string_size + 1 ];

            string_size++;

            if ( ::GetComputerName( new_string, &string_size ) == FALSE )
            {
               // DOUBLE CRAP!
               return;
            }

            m_FriendlyMachineName = new_string;

            delete [] new_string;
         }
         else
         {
            m_FriendlyMachineName = this_machine_name;
         }
      }
   }
   catch( ... )
   {
      m_Initialize();
   }
}

#if ! defined(  WFC_NO_SERIALIZATION )

void CNetwork::Serialize( CArchive& archive )
{
   WFCLTRACEINIT( TEXT( "CNetwork::Serialize()" ) );

   CObject::Serialize( archive );

   if ( archive.IsStoring() )
   {
      WFCTRACE( TEXT( "Storing" ) );
      archive << m_MachineName;
      archive << m_ErrorCode;
   }
   else
   {
      WFCTRACE( TEXT( "Restoring" ) );
      CString temp_string;
      archive >> temp_string;
      archive >> m_ErrorCode;
      Open( temp_string );
   }
}

#endif // WFC_NO_SERIALIZATION

BOOL CNetwork::SetPrivilege( LPCTSTR privilege_name, BOOL add_privilege )
{
   WFCLTRACEINIT( TEXT( "CNetwork::SetPrivilege()" ) );

   HANDLE token_handle = NULL;

   // We were passed a pointer, don't trust it

   try
   {
      if ( ::OpenProcessToken( ::GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &token_handle ) == FALSE )
      {
         m_ErrorCode = ::GetLastError();
         WFCTRACE( TEXT( "Can't OpenProcessToken" ) );
         WFCTRACEERROR( m_ErrorCode );
         return( FALSE );
      }

      TOKEN_PRIVILEGES token_privileges;
      TOKEN_PRIVILEGES previous_token_privileges;

      LUID locally_unique_identifier;

      ::ZeroMemory( &token_privileges, sizeof( token_privileges ) );
      ::ZeroMemory( &previous_token_privileges, sizeof( previous_token_privileges ) );
      ::ZeroMemory( &locally_unique_identifier, sizeof( locally_unique_identifier ) );
   
      if ( ::LookupPrivilegeValue( m_MachineName, privilege_name, &locally_unique_identifier ) == FALSE )
      {
         m_ErrorCode = ::GetLastError();
         WFCTRACE( TEXT( "Can't LookupPrivilegeValue for remote machine" ) );
         WFCTRACEERROR( m_ErrorCode );
         ::wfc_close_handle( token_handle );
         token_handle = NULL;
         return( FALSE );
      }

      token_privileges.PrivilegeCount             = 1;
      token_privileges.Privileges[ 0 ].Luid       = locally_unique_identifier;
      token_privileges.Privileges[ 0 ].Attributes = 0;

      DWORD sizeof_previous_token_privileges = sizeof( previous_token_privileges );

      if ( ::AdjustTokenPrivileges( token_handle, 
                                    FALSE, 
                                   &token_privileges, 
                                    sizeof( token_privileges ),
                                   &previous_token_privileges,
                                   &sizeof_previous_token_privileges ) == FALSE )
      {
         m_ErrorCode = ::GetLastError();
         WFCTRACE( TEXT( "Can't AdjustTokenPrivileges" ) );
         WFCTRACEERROR( m_ErrorCode );
         ::wfc_close_handle( token_handle );
         token_handle = NULL;
         return( FALSE );
      }

      previous_token_privileges.PrivilegeCount       = 1;
      previous_token_privileges.Privileges[ 0 ].Luid = locally_unique_identifier;
      
      if ( add_privilege != FALSE )
      {
         previous_token_privileges.Privileges[ 0 ].Attributes |= (SE_PRIVILEGE_ENABLED);
      }
      else
      {
         previous_token_privileges.Privileges[ 0 ].Attributes ^= ( (SE_PRIVILEGE_ENABLED) & previous_token_privileges.Privileges[ 0 ].Attributes );
      }

      if ( ::AdjustTokenPrivileges( token_handle, 
                                    FALSE, 
                                   &previous_token_privileges, 
                                    sizeof_previous_token_privileges,
                                    NULL,
                                    NULL ) == FALSE )
      {
         m_ErrorCode = ::GetLastError();
         WFCTRACE( TEXT( "Can't AdjustTokenPrivileges for the second time" ) );
         WFCTRACEERROR( m_ErrorCode );
         ::wfc_close_handle( token_handle );
         token_handle = NULL;
         return( FALSE );
      }

      // YIPPEE! We succeeded!

      ::wfc_close_handle( token_handle );
      token_handle = NULL;

      return( TRUE );
   }
   catch( ... )
   {
      // Let the caller know an exception occurred
      m_ErrorCode = ERROR_EXCEPTION_IN_SERVICE;
      return( FALSE );
   }
}

BOOL CNetwork::Shutdown( BOOL reboot, BOOL force_applications_to_close, LPCTSTR message_to_display, DWORD number_of_seconds_before_shutdown )
{
   WFCLTRACEINIT( TEXT( "CNetwork::Shutdown()" ) );

   HANDLE token_handle = NULL;

   if ( ::OpenProcessToken( ::GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &token_handle ) == FALSE )
   {
      m_ErrorCode = ::GetLastError();
      WFCTRACE( TEXT( "Can't OpenProcessToken" ) );
      WFCTRACEERROR( m_ErrorCode );
      return( FALSE );
   }

   TOKEN_PRIVILEGES token_privileges;

   ::ZeroMemory( &token_privileges, sizeof( token_privileges ) );

   // 1999-11-12
   // Thanks go to Karl Spaelti (karl.spaelti@qps.ch) for finding a bug
   // here. machine_name was a LPCSTR when it should have been LPCTSTR.

   LPCTSTR machine_name = NULL;

   // Check to see if we've opened ourselves...

   TCHAR this_machine_name[ 1024 ];

   ::ZeroMemory( this_machine_name, sizeof( this_machine_name ) );

   DWORD temp_dword = 1024;

   if ( ::GetComputerName( this_machine_name, &temp_dword ) == FALSE )
   {
      m_ErrorCode = ::GetLastError();
      WFCTRACE( TEXT( "Can't GetComputerName" ) );
      WFCTRACEERROR( m_ErrorCode );
      ::wfc_close_handle( token_handle );
      token_handle = NULL;
      return( FALSE );
   }

   // Something changed in service pack 3 for NT 3.51. You used to be able
   // to specify the local machine name and get SE_REMOTE_SHUTDOWN privilege
   // and shut down the machine. Not any more. You can no longer remotely
   // shut down your local machine. And no, I couldn't find this documented
   // anywhere...

   if ( m_MachineName.CompareNoCase( this_machine_name ) == 0 )
   {
      machine_name = NULL;
   }
   else
   {
      machine_name = (LPCTSTR) m_MachineName;
   }

   if ( machine_name != NULL )
   {
      // Shutdown a machine somewhere on the network

      if ( ::LookupPrivilegeValue( m_MachineName, SE_REMOTE_SHUTDOWN_NAME, &token_privileges.Privileges[ 0 ].Luid ) == FALSE )
      {
         m_ErrorCode = ::GetLastError();
         WFCTRACE( TEXT( "Can't LookupPrivilegeValue for remote machine" ) );
         WFCTRACEERROR( m_ErrorCode );
         ::wfc_close_handle( token_handle );
         token_handle = NULL;
         return( FALSE );
      }
   }
   else
   {
      // Shutdown this computer

      if ( ::LookupPrivilegeValue( NULL, SE_SHUTDOWN_NAME, &token_privileges.Privileges[ 0 ].Luid ) == FALSE )
      {
         m_ErrorCode = ::GetLastError();
         WFCTRACE( TEXT( "Can't LookupPrivilegeValue for local machine" ) );
         WFCTRACEERROR( m_ErrorCode );
         ::wfc_close_handle( token_handle );
         token_handle = NULL;
         return( FALSE );
      }
   }

   token_privileges.PrivilegeCount             = 1;
   token_privileges.Privileges[ 0 ].Attributes = SE_PRIVILEGE_ENABLED;

   if ( ::AdjustTokenPrivileges( token_handle, FALSE, &token_privileges, 0, (PTOKEN_PRIVILEGES) NULL, 0 ) == FALSE )
   {
      m_ErrorCode = ::GetLastError();
      WFCTRACE( TEXT( "Can't AdjustTokenPrivileges" ) );
      WFCTRACEERROR( m_ErrorCode );
      ::wfc_close_handle( token_handle );
      token_handle = NULL;
      return( FALSE );
   }

   // Whoever wrote InitiateSystemShutdown() (nor the QA/tester) didn't understand the
   // concept of const pointers. The way InitiateSystemShutdown() is prototyped, one
   // would expect it to be returning strings from the operating system. It doesn't
   // (or if it does it isn't documented but Microsoft would never ever ever not
   // document an API parameter) return any data in the string parameters. So, we are
   // left with either a programmer that didn't fully understand what they were doing
   // or it is yet another undocumented feature of the system.

   // InitiateSystemShutdown() is not const correct.
   // The second parameter of InitiateSystemShutdown() is a LPTSTR when it should be
   // a LPCTSTR (const). Because it ain't, we gotta code around it.

   TCHAR message_string[ 1024 ];

   ::ZeroMemory( message_string, sizeof( message_string ) );

   LPTSTR corrected_message_parameter = NULL;

   // We were passed a pointer, don't trust it

   try
   {
      if ( message_to_display != NULL )
      {
         _tcsncpy( message_string, message_to_display, 1023 );
         corrected_message_parameter = message_string;
      }
      else
      {
         corrected_message_parameter = NULL;
      }

      if ( machine_name != NULL )
      {
         // The first parameter of InitiateSystemShutdown() is a LPTSTR when it should be 
         // a LPCTSTR (const). Because it ain't, we gotta code around it.

         _tcscpy( this_machine_name, (LPCTSTR) m_MachineName );

         if ( ::InitiateSystemShutdown( this_machine_name, corrected_message_parameter, number_of_seconds_before_shutdown, force_applications_to_close, reboot ) == FALSE )
         {
            m_ErrorCode = ::GetLastError();
            WFCTRACE( TEXT( "Can't InitiateSystemShutdown for remote machine" ) );
            WFCTRACEERROR( m_ErrorCode );
            ::wfc_close_handle( token_handle );
            token_handle = NULL;
            return( FALSE );
         }
      }
      else
      {
         if ( ::InitiateSystemShutdown( NULL, corrected_message_parameter, number_of_seconds_before_shutdown, force_applications_to_close, reboot ) == FALSE )
         {
            m_ErrorCode = ::GetLastError();
            WFCTRACE( TEXT( "Can't InitiateSystemShutdown for local machine" ) );
            WFCTRACEERROR( m_ErrorCode );
            ::wfc_close_handle( token_handle );
            token_handle = NULL;
            return( FALSE );
         }
      }

      ::wfc_close_handle( token_handle );
      token_handle = NULL;
      return( TRUE );
   }
   catch( ... )
   {
      m_ErrorCode = ERROR_EXCEPTION_IN_SERVICE;
      ::wfc_close_handle( token_handle );
      token_handle = NULL;
      return( FALSE );
   }
}

// End of source

#if 0
<HTML>

<HEAD>
<TITLE>WFC - CNetwork</TITLE>
<META name="keywords" content="WFC, MFC extension library, freeware class library, Win32, source code">
<META name="description" content="The C++ base class for the networking classes.">
</HEAD>

<BODY>
<H1>CNetwork : CObject</H1>
$Revision: 41 $<BR><HR>

<H2>Description</H2>
This class is the base class for the WFC networking classes. It is not a pure
virtual base class in that it provides some interesting (and hopefully
useful) functions.

<H2>Constructors</H2>

<DL COMPACT>

<DT><PRE><B>CNetwork</B>( LPCTSTR machine_name = NULL )</PRE><DD>
Constructs the object.

</DL>

<H2>Data Members</H2>None.

<H2>Methods</H2>

<DL COMPACT>

<DT><PRE>BOOL <B>AbortShutdown</B>( void )</PRE><DD>
Will abort a shutdown started by <B>Shutdown</B>().

<DT><PRE>void <B>Close</B>( void )</PRE><DD>
Closes the connection to the machine.

<DT><PRE>BOOL <B>EnumeratePorts</B>( void )</PRE><DD>
Prepares to enumerate the ports on the machine.

<DT><PRE>DWORD <B>GetErrorCode</B>( void ) const</PRE><DD>
Retrieves the error code. This is set when a
member function returns FALSE.

<DT><PRE>void <B>GetFriendlyMachineName</B>( CString&amp; machine_name )</PRE><DD>
Fills <CODE>machine_name</CODE> with the name of the machine
that has been <B>Open</B>()'ed. This names doesn't have those
annoying backslashes preceeding it.

<DT><PRE>LPCTSTR <B>GetMachineName</B>( void )</PRE><DD>
Retrieves the name of the machine this class
is working with.

<DT><PRE>BOOL <B>GetNext</B>( <A HREF="PortInformation.htm">CPortInformation</A>&amp; port_information )</PRE><DD>
Gets the next <B><A HREF="PortInformation.htm">CPortInformation</A></B> (used in conjunction with
<B>EnumeratePorts</B>()).

<DT><PRE>BOOL <B>GetTime</B>( CTime&amp; time )
BOOL <B>GetTime</B>( <A HREF="CSystemTime.htm">CSystemTime</A>&amp; time )</PRE><DD>
Gets the time from the machine as a CTime or a 
<A HREF="CSystemTime.htm">CSystemTime</A> (more accurate).

<DT><PRE>BOOL <B>IsRebootable</B>( void )</PRE><DD>
Returns TRUE if you have permissions to reboot the machine.
In other words, a call to <B>Shutdown</B>() should succeed.

<DT><PRE>void <B>Open</B>( LPCTSTR machine_name = NULL )</PRE><DD>
Tells the class to work with the machine you specify.

<DT><PRE>void <B>Serialize</B>( CArchive&amp; archive )</PRE><DD>
After all we are a CObject...

<DT><PRE>BOOL <B>SetPrivilege</B>( LPCTSTR privilege_name, BOOL add_privilege = TRUE )</PRE><DD>
Adds or removes a privilege. If <CODE>add_privilege</CODE> is FALSE, the 
privilege is removed, otherwise it is added. <CODE>privilege_name</CODE>
can be one of the following (as of NT4.0SP2/VC42b):

<UL>
<LI>SE_CREATE_TOKEN_NAME
<LI>SE_ASSIGNPRIMARYTOKEN_NAME
<LI>SE_LOCK_MEMORY_NAME
<LI>SE_INCREASE_QUOTA_NAME
<LI>SE_UNSOLICITED_INPUT_NAME
<LI>SE_MACHINE_ACCOUNT_NAME
<LI>SE_TCB_NAME
<LI>SE_SECURITY_NAME
<LI>SE_TAKE_OWNERSHIP_NAME
<LI>SE_LOAD_DRIVER_NAME
<LI>SE_SYSTEM_PROFILE_NAME
<LI>SE_SYSTEMTIME_NAME
<LI>SE_PROF_SINGLE_PROCESS_NAME
<LI>SE_INC_BASE_PRIORITY_NAME
<LI>SE_CREATE_PAGEFILE_NAME
<LI>SE_CREATE_PERMANENT_NAME
<LI>SE_BACKUP_NAME
<LI>SE_RESTORE_NAME
<LI>SE_SHUTDOWN_NAME
<LI>SE_DEBUG_NAME
<LI>SE_AUDIT_NAME
<LI>SE_SYSTEM_ENVIRONMENT_NAME
<LI>SE_CHANGE_NOTIFY_NAME
<LI>SE_REMOTE_SHUTDOWN_NAME
</UL>

<DT><PRE>BOOL <B>Shutdown</B>( BOOL    reboot                            = TRUE,
               BOOL    force_applocations_to_close       = TRUE,
               LPCTSTR message_to_display                = NULL,
               DWORD   number_of_seconds_before_shutdown = 0 )</PRE><DD>
Will reboot the machine set by <B>Open</B>().

</DL>

<H2>Example</H2><PRE><CODE>void test_CNetwork( LPCTSTR machine_name )
{
   <A HREF="WfcTrace.htm">WFCTRACEINIT</A>( TEXT( &quot;test_CNetwork()&quot; ) );

   <B>CNetwork</B> machine( machine_name );

   if ( machine.EnumeratePorts() )
   {
      if ( machine_name != NULL )
      {
         _tprintf( TEXT( &quot;Ports on %s\n&quot; ), machine_name );
      }
      else
      {
         _tprintf( TEXT( &quot;Ports on local machine\n&quot; ) );
      }

      <A HREF="PortInformation.htm">CPortInformation</A> port;

      while( machine.GetNext( port ) )
      {
         _tprintf( TEXT( &quot;Name:        %s\n&quot; ), (LPCTSTR) port.Name        );
         _tprintf( TEXT( &quot;Monitor:     %s\n&quot; ), (LPCTSTR) port.Monitor     );
         _tprintf( TEXT( &quot;Description: %s\n&quot; ), (LPCTSTR) port.Description );
         _tprintf( TEXT( &quot;Type:        %04lX\n&quot; ), port.Type );
         _tprintf( TEXT( &quot;TypeName:    %s\n\n&quot; ), (LPCTSTR) port.TypeName );
      }
   }
   else
   {
      DWORD error_code = machine.GetErrorCode();
      ReportError( error_code );
      _tprintf( TEXT( &quot;Can't EnumeratePorts, reason code %lu\n&quot; ), error_code );
   }

   if ( machine.IsRebootable() )
   {
      if ( machine_name != NULL )
      {
         _tprintf( TEXT( &quot;Yes, I can reboot %s\n&quot; ), machine_name );
      }
      else
      {
         _tprintf( TEXT( &quot;Yes, I can reboot this machine\n&quot; ) );
      }
   }
}</CODE></PRE>

<H2>API's Used</H2>

<UL>
<LI>AbortSystemShutdown
<LI>AdjustTokenPrivileges
<LI>EnumPorts
<LI>GetComputerName
<LI>GetCurrentProcess
<LI>GetLastError
<LI>InitiateSystemShutdown
<LI>LookupPrivilegeValue
<LI>NetRemoteTOD
<LI>OpenProcessToken
<LI>ZeroMemory
</UL>

<HR><I>Copyright, 2000, <A HREF="mailto:wfc@pobox.com">Samuel R. Blackburn</A></I><BR>
$Workfile: cnetwork.cpp $<BR>
$Modtime: 5/02/00 6:03p $
</BODY>

</HTML>
#endif
