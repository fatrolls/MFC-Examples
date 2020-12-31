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
** $Workfile: registry.cpp $
** $Revision: 41 $
** $Modtime: 3/22/00 4:46a $
** $Reuse Tracing Code: 1 $
*/

#if defined( _DEBUG ) && ! defined( WFC_STL )
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

#if ! defined(  WFC_NO_SERIALIZATION )
IMPLEMENT_DYNAMIC( CRegistry, CObject );
#endif // WFC_NO_SERIALIZATION

#if defined( _DEBUG ) && ! defined( WFC_STL )
#define new DEBUG_NEW
#endif // _DEBUG

static LONG _recursively_delete_all_sub_keys( HKEY key_handle, LPCTSTR key_name )
{
   HKEY child_key_handle = NULL;

   LONG return_value = 0;

   LPTSTR temporary_key_name = NULL;

   return_value = RegOpenKeyEx( key_handle, key_name, NULL, KEY_ALL_ACCESS, &child_key_handle );

   if ( return_value != ERROR_SUCCESS )
   {
      return( return_value );
   }

   try
   {
      temporary_key_name = new TCHAR[ MAX_PATH ];
   }
   catch( ... )
   {
      temporary_key_name = NULL;
   }

   if ( temporary_key_name == NULL )
   {
      return( ERROR_NOT_ENOUGH_MEMORY );
   }

   return_value = RegEnumKey( child_key_handle, 0, temporary_key_name, MAX_PATH );

   while( return_value == ERROR_SUCCESS )
   {
      _recursively_delete_all_sub_keys( child_key_handle, temporary_key_name );

      return_value = RegEnumKey( child_key_handle, 0, temporary_key_name, MAX_PATH );
   }

   delete [] temporary_key_name;

   temporary_key_name = NULL;

   RegCloseKey( child_key_handle );

   return_value = RegDeleteKey( key_handle, key_name );

   return( return_value );
}

CRegistry::CRegistry()
{
   WFCLTRACEINIT( TEXT( "CRegistry::CRegistry()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   m_Initialize();
}

CRegistry::~CRegistry()
{
   WFCLTRACEINIT( TEXT( "CRegistry::~CRegistry()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );

   if ( m_RegistryHandle != (HKEY) NULL )
   {
      Close();
   }

   m_Initialize();
}

void CRegistry::m_Initialize( void )
{
   WFCLTRACEINIT( TEXT( "CRegistry::m_Initialize()" ) );

   /*
   ** Make sure everything is zeroed out
   */

   m_ClassName.Empty();
   m_ComputerName.Empty();
   m_KeyName.Empty();
   m_RegistryName.Empty();

   m_KeyHandle                    = (HKEY) NULL;
   m_ErrorCode                    = 0L;
   m_NumberOfSubkeys              = 0;
   m_LongestSubkeyNameLength      = 0;
   m_LongestClassNameLength       = 0;
   m_NumberOfValues               = 0;
   m_LongestValueNameLength       = 0;
   m_LongestValueDataLength       = 0;
   m_SecurityDescriptorLength     = 0;
   m_LastWriteTime.dwLowDateTime  = 0;
   m_LastWriteTime.dwHighDateTime = 0;

   // Thanks go to Chad Christenson (chadc@cwcinc.com) for finding
   // the bug where m_RegistryHandle was never initialized

   m_RegistryHandle               = (HKEY) NULL;
}

BOOL CRegistry::Close( void )
{
   WFCLTRACEINIT( TEXT( "CRegistry::Close()" ) );

   // Thanks go to Gareth Isaac (humbert@tcp.co.uk) for finding a resource leak here

   if ( m_KeyHandle != (HKEY) NULL )
   {
      ::RegCloseKey( m_KeyHandle );
      m_KeyHandle = (HKEY) NULL;
   }

   if ( m_RegistryHandle == (HKEY) NULL )
   {
      WFCTRACE( TEXT( "Registry already closed" ) );
      return( TRUE );
   }

   m_ErrorCode = ::RegCloseKey( m_RegistryHandle );

   if ( m_ErrorCode == ERROR_SUCCESS )
   {
      m_RegistryHandle = (HKEY) NULL;
      m_Initialize();

      return( TRUE );
   }
   else
   {
      WFCTRACEERROR( m_ErrorCode );
      return( FALSE );
   }
}

BOOL CRegistry::Connect( HKEY key_to_open, LPCTSTR name_of_computer )
{
   WFCLTRACEINIT( TEXT( "CRegistry::Connect()" ) );

   // We were passed a pointer, do not trust it

   try
   {
      /*
      ** name_of_computer can be NULL
      */

      if ( key_to_open == (HKEY) keyClassesRoot || key_to_open == (HKEY) keyCurrentUser )
      {
         if ( name_of_computer == NULL )
         {
            m_RegistryHandle = key_to_open;
            m_ErrorCode      = ERROR_SUCCESS;
         }
         else
         {
            /*
            ** NT won't allow you to connect to these hives via RegConnectRegistry so we'll just skip that step
            */

            WFCTRACE( TEXT( "You cannot connect to keyClassesRoot or keyCurrentUser on a remote machine" ) );
            m_ErrorCode = ERROR_INVALID_HANDLE;
         }
      }
      else
      {
         WFCTRACE( TEXT( "Connecting to registry" ) );
         
         // Thanks to Paul Ostrowski [postrowski@xantel.com] for finding UNICODE bug here
         
         // RegConnectRegistry is not const correct

         m_ErrorCode = ::RegConnectRegistry( (LPTSTR) name_of_computer, key_to_open, &m_RegistryHandle );
      }

      if ( m_ErrorCode == ERROR_SUCCESS )
      {
         if ( name_of_computer == NULL )
         {
            TCHAR computer_name[ MAX_PATH ];
            DWORD size = MAX_PATH;

            if ( ::GetComputerName( computer_name, &size ) == FALSE )
            {
               m_ComputerName.Empty();
            }
            else
            {
               m_ComputerName = computer_name;
            }
         }
         else
         {
            m_ComputerName = name_of_computer;
         }

         /*
         ** It would be nice to use a switch statement here but I get a "not integral" error!
         */

         if ( key_to_open == HKEY_LOCAL_MACHINE )
         {
            m_RegistryName = TEXT( "HKEY_LOCAL_MACHINE" );
         }
         else if ( key_to_open == HKEY_CLASSES_ROOT )
         {
            m_RegistryName = TEXT( "HKEY_CLASSES_ROOT" );
         }
         else if ( key_to_open == HKEY_USERS )
         {
            m_RegistryName = TEXT( "HKEY_USERS" );
         }
         else if ( key_to_open == HKEY_CURRENT_USER )
         {
            m_RegistryName = TEXT( "HKEY_CURRENT_USER" );
         }
         else if ( key_to_open == HKEY_PERFORMANCE_DATA )
         {
            m_RegistryName = TEXT( "HKEY_PERFORMANCE_DATA" );
         }
#if ( WINVER >= 0x400 )
         else if ( key_to_open == HKEY_CURRENT_CONFIG )
         {
            m_RegistryName = TEXT( "HKEY_CURRENT_CONFIG" );
         }
         else if ( key_to_open == HKEY_DYN_DATA )
         {
            m_RegistryName = TEXT( "HKEY_DYN_DATA" );
         }
#endif
         else
         {
            m_RegistryName = TEXT( "Unknown" );
         }

         WFCTRACEVAL( TEXT( "Connected to " ), m_ComputerName );
         WFCTRACEVAL( TEXT( "Key " ), m_RegistryName );

         return( TRUE );
      }
      else
      {
         WFCTRACEERROR( m_ErrorCode );
         return( FALSE );
      }
   }
   catch( ... )
   {
      m_ErrorCode = ERROR_EXCEPTION_IN_SERVICE;
      return( FALSE );
   }
}

BOOL CRegistry::Create( LPCTSTR               name_of_subkey, 
                        LPCTSTR               name_of_class,
                        CreateOptions         options, 
                        CreatePermissions     permissions, 
                        LPSECURITY_ATTRIBUTES security_attributes_p,
                        CreationDisposition * disposition_p )
{
   WFCLTRACEINIT( TEXT( "CRegistry::Create()" ) );
   ASSERT( name_of_subkey != NULL );

   if ( name_of_subkey == NULL )
   {
      m_ErrorCode = ERROR_INVALID_PARAMETER;
      return( FALSE );
   }

   // We were passed a pointer, do not trust it

   try
   {
      DWORD disposition = 0;

      if ( name_of_class == NULL )
      {
         name_of_class = TEXT( "" ); // Paul Ostrowski [postrowski@xantel.com]
      }

      if ( m_KeyHandle != (HKEY) NULL )
      {
         ::RegCloseKey( m_KeyHandle );
         m_KeyHandle = (HKEY) NULL;
      }

      m_ErrorCode = ::RegCreateKeyEx( m_RegistryHandle,
                                      name_of_subkey,
                              (DWORD) 0,
                             (LPTSTR) name_of_class, // Paul Ostrowski [postrowski@xantel.com]
                                      options,
                                      permissions,
                                      security_attributes_p,
                                     &m_KeyHandle,
                                     &disposition );

      if ( m_ErrorCode == ERROR_SUCCESS )
      {
         if ( disposition_p != NULL )
         {
            *disposition_p = (CreationDisposition) disposition;
         }

         m_KeyName = name_of_subkey;

         return( TRUE );
      }
      else
      {
         return( FALSE );
      }
   }
   catch( ... )
   {
      m_ErrorCode = ERROR_EXCEPTION_IN_SERVICE;
      return( FALSE );
   }
}

BOOL CRegistry::DeleteKey( LPCTSTR name_of_key_to_delete )
{
   WFCLTRACEINIT( TEXT( "CRegistry::DeleteKey()" ) );

   ASSERT( name_of_key_to_delete != NULL );

   if ( name_of_key_to_delete == NULL )
   {
      m_ErrorCode = ERROR_INVALID_PARAMETER;
      return( FALSE );
   }

   // We were passed a pointer, do not trust it

   try
   {
      /*
      ** You can't delete a key given a full path. What you have to do is back up one level and then do a delete
      */

      CString full_key_name = name_of_key_to_delete;

      if ( full_key_name.Find( TEXT( '\\' ) ) == (-1) )
      {
         /*
         ** User had not given us a full path so assume the name of the key he passed us
         ** is a key off of the current key
         */

         m_ErrorCode = ::_recursively_delete_all_sub_keys( m_KeyHandle, name_of_key_to_delete );
      }
      else
      {
         int last_back_slash_location = full_key_name.GetLength() - 1;

         /*
         ** We know this loop will succeed because a back slash was found in the above if statement
         */

         while( full_key_name[ last_back_slash_location ] != TEXT( '\\' ) )
         {
            last_back_slash_location--;
         }

         CString currently_opened_key_name = m_KeyName;

         CString parent_key_name = full_key_name.Left( last_back_slash_location );
         CString child_key_name  = full_key_name.Right( ( full_key_name.GetLength() - last_back_slash_location ) - 1 );

         /*
         ** Now we open the parent key and delete the child
         */

         if ( Open( parent_key_name ) != FALSE )
         {
            m_ErrorCode = ::_recursively_delete_all_sub_keys( m_KeyHandle, child_key_name );
         }
         else
         {
            m_KeyName = currently_opened_key_name;
            return( FALSE );
         }
      }

      if ( m_ErrorCode == ERROR_SUCCESS )
      {
         return( TRUE );
      }
      else
      {
         return( FALSE );
      }
   }
   catch( ... )
   {
      m_ErrorCode = ERROR_EXCEPTION_IN_SERVICE;
      return( FALSE );
   }
}                  

BOOL CRegistry::DeleteValue( LPCTSTR name_of_value_to_delete )
{
   WFCLTRACEINIT( TEXT( "CRegistry::DeleteValue()" ) );

   /*
   ** name_of_value_to_delete can be NULL
   */

   // We were passed a pointer, do not trust it

   try
   {
      m_ErrorCode = ::RegDeleteValue( m_KeyHandle, (LPTSTR) name_of_value_to_delete );

      if ( m_ErrorCode == ERROR_SUCCESS )
      {
         return( TRUE );
      }
      else
      {
         WFCTRACEERROR( m_ErrorCode );
         return( FALSE );
      }
   }
   catch( ... )
   {
      m_ErrorCode = ERROR_EXCEPTION_IN_SERVICE;
      return( FALSE );
   }
}

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

void CRegistry::Dump( CDumpContext& dump_context ) const
{
   CObject::Dump( dump_context );

   dump_context << TEXT( "m_KeyHandle = "                ) << m_KeyHandle                << TEXT( "\n" );
   dump_context << TEXT( "m_RegistryHandle = "           ) << m_RegistryHandle           << TEXT( "\n" );
   dump_context << TEXT( "m_ClassName = \""              ) << m_ClassName                << TEXT( "\"\n" );
   dump_context << TEXT( "m_ComputerName = \""           ) << m_ComputerName             << TEXT( "\"\n" );
   dump_context << TEXT( "m_KeyName = \""                ) << m_KeyName                  << TEXT( "\"\n" );
   dump_context << TEXT( "m_RegistryName = \""           ) << m_RegistryName             << TEXT( "\"\n" );
   dump_context << TEXT( "m_NumberOfSubkeys = "          ) << m_NumberOfSubkeys          << TEXT( "\n" );
   dump_context << TEXT( "m_NumberOfValues = "           ) << m_NumberOfValues           << TEXT( "\n" );
   dump_context << TEXT( "m_LongestSubkeyNameLength = "  ) << m_LongestSubkeyNameLength  << TEXT( "\n" );
   dump_context << TEXT( "m_LongestClassNameLength = "   ) << m_LongestClassNameLength   << TEXT( "\n" );
   dump_context << TEXT( "m_LongestValueNameLength = "   ) << m_LongestValueNameLength   << TEXT( "\n" );
   dump_context << TEXT( "m_LongestValueDataLength = "   ) << m_LongestValueDataLength   << TEXT( "\n" );
   dump_context << TEXT( "m_SecurityDescriptorLength = " ) << m_SecurityDescriptorLength << TEXT( "\n" );

   // Mike Berger (mberger@smg.seagatesoftware.com) found a bug where there was no
   // << operator for FILETIME structure. Color me stupid for not catching it...

   dump_context << TEXT( "m_LastWriteTime.dwLowDateTime  = " ) << m_LastWriteTime.dwLowDateTime  << TEXT( "\n" );
   dump_context << TEXT( "m_LastWriteTime.dwHighDateTime = " ) << m_LastWriteTime.dwHighDateTime << TEXT( "\n" );
}

#endif // _DEBUG

BOOL CRegistry::EnumerateKeys( const DWORD subkey_index, CString& subkey_name, CString& class_name )
{
   WFCLTRACEINIT( TEXT( "CRegistry::EnumerateKeys()" ) );

   TCHAR subkey_name_string[ 2048 ];
   TCHAR class_name_string[ 2048 ];

   DWORD size_of_subkey_name_string = DIMENSION_OF( subkey_name_string ) - 1;
   DWORD size_of_class_name_string  = DIMENSION_OF( class_name_string  ) - 1;

   ::ZeroMemory( subkey_name_string, sizeof( subkey_name_string ) );
   ::ZeroMemory( class_name_string,  sizeof( class_name_string  ) );

   m_ErrorCode = ::RegEnumKeyEx( m_KeyHandle, 
                                 subkey_index, 
                                 subkey_name_string, 
                                &size_of_subkey_name_string,
                                 NULL,
                                 class_name_string,
                                &size_of_class_name_string,
                                &m_LastWriteTime );

   if ( m_ErrorCode == ERROR_SUCCESS )
   {
      subkey_name = subkey_name_string;
      class_name  = class_name_string;

      return( TRUE );
   }
   else
   {
      WFCTRACEERROR( m_ErrorCode );
      return( FALSE );
   }
}

BOOL CRegistry::EnumerateValues( const DWORD    value_index, 
                                 CString&       name_of_value, 
                                 KeyValueTypes& type_code,
                                 LPBYTE         data_buffer,
                                 DWORD&         size_of_data_buffer )
{
   WFCLTRACEINIT( TEXT( "CRegistry::EnumerateValues()" ) );

   /*
   ** data_buffer and size_of_data_buffer can be NULL
   */

   DWORD temp_type_code = type_code;

   TCHAR temp_name[ 2048 ];

   ::ZeroMemory( temp_name, sizeof( temp_name ) );

   DWORD temp_name_size = DIMENSION_OF( temp_name );

   // We were passed a pointer, do not trust it

   try
   {
      m_ErrorCode = ::RegEnumValue( m_KeyHandle,
                                    value_index,
                                    temp_name,
                                   &temp_name_size,
                                    NULL,
                                   &temp_type_code,
                                    data_buffer,
                                   &size_of_data_buffer );

      if ( m_ErrorCode == ERROR_SUCCESS )
      {
         type_code     = (KeyValueTypes) temp_type_code;
         name_of_value = temp_name;

         return( TRUE );
      }
      else
      {
         WFCTRACEERROR( m_ErrorCode );
         return( FALSE );
      }
   }
   catch( ... )
   {
      m_ErrorCode = ERROR_EXCEPTION_IN_SERVICE;
      return( FALSE );
   }
}

BOOL CRegistry::Flush( void )
{
   WFCLTRACEINIT( TEXT( "CRegistry::Flush()" ) );

   m_ErrorCode = ::RegFlushKey( m_KeyHandle );

   if ( m_ErrorCode == ERROR_SUCCESS )
   {
      return( TRUE );
   }
   else
   {
      WFCTRACEERROR( m_ErrorCode );
      return( FALSE );
   }
}

BOOL CRegistry::GetBinaryValue( LPCTSTR name_of_value, CByteArray& return_array )
{
   WFCLTRACEINIT( TEXT( "CRegistry::GetBinaryValue()" ) );

   // Thanks go to Chris Hines (ChrisHines@msn.com) for finding
   // a bug here. If you add entries to the key, then the
   // information retrieved via QueryInfo() may be invalid. This
   // will screw you here. So, we must make sure our information
   // is correct before we attempt to *use* the data.

   QueryInfo();

   DWORD size_of_buffer = m_LongestValueDataLength;

   LPBYTE memory_buffer = (LPBYTE) new BYTE[ size_of_buffer ];

   if ( memory_buffer == NULL )
   {
      m_ErrorCode = ::GetLastError();
      WFCTRACEERROR( m_ErrorCode );
      return( FALSE );
   }

   BOOL return_value = TRUE;

   KeyValueTypes type = typeBinary;

   if ( QueryValue( name_of_value, type, memory_buffer, size_of_buffer ) != FALSE )
   {
      /*
      ** We've got data so give it back to the caller
      */

      return_array.RemoveAll();

      DWORD index = 0;

      while( index < size_of_buffer )
      {
         return_array.Add( memory_buffer[ index ] );
         index++;
      }

      return_value = TRUE;
   }
   else
   {
      return_value = FALSE;
   }

   delete [] memory_buffer;

   return( return_value );
}

void CRegistry::GetClassName( CString& class_name ) const
{
   WFCLTRACEINIT( TEXT( "CRegistry::GetClassName()" ) );
   class_name = m_ClassName;
}

void CRegistry::GetComputerName( CString& computer_name ) const
{
   WFCLTRACEINIT( TEXT( "CRegistry::GetComputerName()" ) );
   computer_name = m_ComputerName;
}

BOOL CRegistry::GetDoubleWordValue( LPCTSTR name_of_value, DWORD& return_value )
{
   WFCLTRACEINIT( TEXT( "CRegistry::GetDoubleWordValue()" ) );

   DWORD size_of_buffer = sizeof( DWORD );

   KeyValueTypes type = typeDoubleWord;

   return( QueryValue( name_of_value, type, (LPBYTE) &return_value, size_of_buffer ) );
}

BOOL CRegistry::GetErrorCode( void ) const
{
   WFCLTRACEINIT( TEXT( "CRegistry::GetErrorCode()" ) );
   return( m_ErrorCode );
}

void CRegistry::GetKeyName( CString& key_name ) const
{
   WFCLTRACEINIT( TEXT( "CRegistry::GetKeyName()" ) );
   key_name = m_KeyName;
}

DWORD CRegistry::GetNumberOfSubkeys( void ) const
{
   WFCLTRACEINIT( TEXT( "CRegistry::GetNumberOfSubkeys()" ) );
   return( m_NumberOfSubkeys );
}

DWORD CRegistry::GetNumberOfValues( void ) const
{
   WFCLTRACEINIT( TEXT( "CRegistry::GetNumberOfValues()" ) );
   return( m_NumberOfValues );
}

void CRegistry::GetRegistryName( CString& registry_name ) const
{
   WFCLTRACEINIT( TEXT( "CRegistry::GetRegistryName()" ) );
   registry_name = m_RegistryName;
}

BOOL CRegistry::GetSecurity( const SECURITY_INFORMATION what_you_want_to_know,
                             PSECURITY_DESCRIPTOR       data_buffer,
                             DWORD&                     size_of_data_buffer )
{
   WFCLTRACEINIT( TEXT( "CRegistry::GetSecurity()" ) );

   ASSERT( data_buffer != NULL );

   if ( data_buffer == NULL )
   {
      WFCTRACE( TEXT( "data_buffer is NULL" ) );
      m_ErrorCode = ERROR_INVALID_PARAMETER;
      return( FALSE );
   }

   // We were passed a pointer, do not trust it

   try
   {
      m_ErrorCode = ::RegGetKeySecurity( m_KeyHandle,
                                         what_you_want_to_know,
                                         data_buffer,
                                        &size_of_data_buffer );

      if ( m_ErrorCode == ERROR_SUCCESS )
      {
         return( TRUE );
      }
      else
      {
         WFCTRACEERROR( m_ErrorCode );
         return( FALSE );
      }
   }
   catch( ... )
   {
      m_ErrorCode = ERROR_EXCEPTION_IN_SERVICE;
      return( FALSE );
   }
}

BOOL CRegistry::GetStringValue( LPCTSTR name_of_value, CString& return_string )
{
   WFCLTRACEINIT( TEXT( "CRegistry::GetStringValue()" ) );

   TCHAR temp_string[ 2048 ];
   DWORD size_of_buffer = 2048;

   ::ZeroMemory( temp_string, sizeof( temp_string ) );

   KeyValueTypes type = typeString;

   if ( QueryValue( name_of_value, type, (LPBYTE) temp_string, size_of_buffer ) != FALSE )
   {
      return_string = temp_string;
      return( TRUE );
   }
   else
   {
      return_string.Empty();
      return( FALSE );
   }
}

BOOL CRegistry::GetStringArrayValue( LPCTSTR name_of_value, CStringArray& return_array )
{
   WFCLTRACEINIT( TEXT( "CRegistry::GetStringArrayValue()" ) );

   // Thanks go to Chris Hines (ChrisHines@msn.com) for finding
   // a bug here. If you add entries to the key, then the
   // information retrieved via QueryInfo() may be invalid. This
   // will screw you here. So, we must make sure our information
   // is correct before we attempt to *use* the data.

   QueryInfo();

   DWORD size_of_buffer = m_LongestValueDataLength;

   LPBYTE memory_buffer = (LPBYTE) new BYTE[ size_of_buffer ];

   if ( memory_buffer == NULL )
   {
      m_ErrorCode = ::GetLastError();
      WFCTRACEERROR( m_ErrorCode );
      return( FALSE );
   }

   BOOL return_value = TRUE;

   KeyValueTypes type = typeMultipleString; // A double NULL terminated string

   if ( QueryValue( name_of_value, type, memory_buffer, size_of_buffer ) != FALSE )
   {
      /*
      ** We've got data so give it back to the caller
      */

      LPTSTR strings = (LPTSTR) memory_buffer;

      return_array.RemoveAll();

      while( strings[ 0 ] != 0x00 )
      {
         return_array.Add( (LPCTSTR) strings );
         strings += ( _tcslen( (LPCTSTR) strings ) + 1 ); // Paul Ostrowski [postrowski@xantel.com]
      }

      return_value = TRUE;
   }
   else
   {
      return_value = FALSE;
   }

   delete [] memory_buffer;
   
   return( return_value );
}

BOOL CRegistry::GetValue( LPCTSTR name_of_value, CByteArray& return_array )
{
   WFCLTRACEINIT( TEXT( "CRegistry::GetValue()" ) );

   return( GetBinaryValue( name_of_value, return_array ) );
}

BOOL CRegistry::GetValue( LPCTSTR name_of_value, DWORD& return_value )
{
   WFCLTRACEINIT( TEXT( "CRegistry::GetValue()" ) );
   return( GetDoubleWordValue( name_of_value, return_value ) );
}

BOOL CRegistry::GetValue( LPCTSTR name_of_value, CString& return_string )
{
   WFCLTRACEINIT( TEXT( "CRegistry::GetValue()" ) );
   return( GetStringValue( name_of_value, return_string ) );
}

BOOL CRegistry::GetValue( LPCTSTR name_of_value, CStringArray& return_array )
{
   WFCLTRACEINIT( TEXT( "CRegistry::GetValue()" ) );
   return( GetStringArrayValue( name_of_value, return_array ) );
}

BOOL CRegistry::Load( LPCTSTR name_of_subkey, LPCTSTR name_of_file_containing_information )
{
   WFCLTRACEINIT( TEXT( "CRegistry::Load()" ) );

   ASSERT( name_of_subkey != NULL );
   ASSERT( name_of_file_containing_information != NULL );

   if ( name_of_subkey == NULL || name_of_file_containing_information == NULL )
   {
      m_ErrorCode = ERROR_INVALID_PARAMETER;
      return( FALSE );
   }

   // We were passeda pointer, do not trust it

   try
   {
      m_ErrorCode = ::RegLoadKey( m_RegistryHandle, name_of_subkey, name_of_file_containing_information );

      if ( m_ErrorCode == ERROR_SUCCESS )
      {
         return( TRUE );
      }
      else
      {
         WFCTRACEERROR( m_ErrorCode );
         return( FALSE );
      }
   }
   catch( ... )
   {
      m_ErrorCode = ERROR_EXCEPTION_IN_SERVICE;
      return( FALSE );
   }
}

BOOL CRegistry::NotifyChange( const HANDLE             event_handle, 
                              const NotifyChangeFilter changes_to_be_reported,
                              const BOOL               this_subkey_or_all_subkeys,
                              const BOOL               wait_for_change_or_signal_event )
{
   WFCLTRACEINIT( TEXT( "CRegistry::NotifyChange()" ) );

   m_ErrorCode = ::RegNotifyChangeKeyValue( m_KeyHandle,
                                            this_subkey_or_all_subkeys,
                                            changes_to_be_reported,
                                            event_handle,
                                            wait_for_change_or_signal_event );

   if ( m_ErrorCode == ERROR_SUCCESS )
   {
      return( TRUE );
   }
   else
   {
      WFCTRACEERROR( m_ErrorCode );
      return( FALSE );
   }
}

BOOL CRegistry::Open( LPCTSTR name_of_subkey_to_open, const CreatePermissions security_access_mask )
{
   WFCLTRACEINIT( TEXT( "CRegistry::Open()" ) );

   /*
   ** name_of_subkey_to_open can be NULL
   */

   // We were passed a pointer, do not trust it

   try
   {
      if ( m_KeyHandle != (HKEY) NULL )
      {
         ::RegCloseKey( m_KeyHandle );
         m_KeyHandle = (HKEY) NULL;
      }

      m_ErrorCode = ::RegOpenKeyEx( m_RegistryHandle, name_of_subkey_to_open, NULL, security_access_mask, &m_KeyHandle );

      if ( m_ErrorCode == ERROR_SUCCESS )
      {
         QueryInfo();
         m_KeyName = name_of_subkey_to_open;

         return( TRUE );
      }
      else
      {
         WFCTRACEERROR( m_ErrorCode );
         return( FALSE );
      }
   }
   catch( ... )
   {
      m_ErrorCode = ERROR_EXCEPTION_IN_SERVICE;
      return( FALSE );
   }
}

BOOL CRegistry::QueryInfo( void )
{
   WFCLTRACEINIT( TEXT( "CRegistry::QueryInfo()" ) );

   TCHAR class_name[ 2048 ];

   ::ZeroMemory( class_name, sizeof( class_name ) );

   DWORD size_of_class_name = DIMENSION_OF( class_name ) - 1;
   
   m_ErrorCode = ::RegQueryInfoKey( m_KeyHandle,
                                    class_name,
                                   &size_of_class_name,
                          (LPDWORD) NULL,
                                   &m_NumberOfSubkeys,
                                   &m_LongestSubkeyNameLength,
                                   &m_LongestClassNameLength,
                                   &m_NumberOfValues,
                                   &m_LongestValueNameLength,
                                   &m_LongestValueDataLength,
                                   &m_SecurityDescriptorLength,
                                   &m_LastWriteTime );

   if ( m_ErrorCode == ERROR_SUCCESS )
   {
      m_ClassName = class_name;

      return( TRUE );
   }
   else
   {
      WFCTRACEERROR( m_ErrorCode );
      return( FALSE );
   }
}

BOOL CRegistry::QueryValue( LPCTSTR        name_of_value, 
                            KeyValueTypes& value_type, 
                            LPBYTE         address_of_buffer, 
                            DWORD&         size_of_buffer )
{
   WFCLTRACEINIT( TEXT( "CRegistry::QueryValue()" ) );

   /*
   ** address_of_buffer and size_of_buffer can be NULL
   */

   // We were passed a pointer, do not trust it

   try
   {
      DWORD temp_data_type = (DWORD) value_type;

      m_ErrorCode = ::RegQueryValueEx( m_KeyHandle,
                              (LPTSTR) name_of_value,
                                       NULL,
                                      &temp_data_type,
                                       address_of_buffer,
                                      &size_of_buffer );

      if ( m_ErrorCode == ERROR_SUCCESS )
      {
         value_type = (KeyValueTypes) temp_data_type;
         return( TRUE );
      }
      else
      {
         WFCTRACEERROR( m_ErrorCode );
         return( FALSE );
      }
   }
   catch( ... )
   {
      m_ErrorCode = ERROR_EXCEPTION_IN_SERVICE;
      return( FALSE );
   }
}

BOOL CRegistry::Replace( LPCTSTR name_of_subkey,
                         LPCTSTR name_of_file_with_new_data,
                         LPCTSTR name_of_backup_file )
{
   WFCLTRACEINIT( TEXT( "CRegistry::Replace()" ) );

   ASSERT( name_of_subkey             != NULL );
   ASSERT( name_of_file_with_new_data != NULL );
   ASSERT( name_of_backup_file        != NULL );

   if ( name_of_subkey             == NULL ||
        name_of_file_with_new_data == NULL ||
        name_of_backup_file        == NULL )
   {
      m_ErrorCode = ERROR_INVALID_PARAMETER;
      return( FALSE );
   }

   // We were passed a pointer, do not trust it

   try
   {
      m_ErrorCode = ::RegReplaceKey( m_KeyHandle, 
                                     name_of_subkey,
                                     name_of_file_with_new_data,
                                     name_of_backup_file );

      if ( m_ErrorCode == ERROR_SUCCESS )
      {
         return( TRUE );
      }
      else
      {
         WFCTRACEERROR( m_ErrorCode );
         return( FALSE );
      }
   }
   catch( ... )
   {
      m_ErrorCode = ERROR_EXCEPTION_IN_SERVICE;
      return( FALSE );
   }
}

BOOL CRegistry::Restore( LPCTSTR name_of_file_holding_saved_tree, const DWORD volatility_flags )
{
   WFCLTRACEINIT( TEXT( "CRegistry::Restore()" ) );

   ASSERT( name_of_file_holding_saved_tree != NULL );

   if ( name_of_file_holding_saved_tree == NULL )
   {
      m_ErrorCode = ERROR_INVALID_PARAMETER;
      return( FALSE );
   }

   // We were passed a pointer, do not trust it

   try
   {
      m_ErrorCode = ::RegRestoreKey( m_KeyHandle,
                                     name_of_file_holding_saved_tree,
                                     volatility_flags );

      if ( m_ErrorCode == ERROR_SUCCESS )
      {
         return( TRUE );
      }
      else
      {
         WFCTRACEERROR( m_ErrorCode );

         // Maybe we need to get permission...
         HANDLE token_handle = NULL;

         DWORD error_code = 0;

         if ( ::OpenProcessToken( ::GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &token_handle ) == FALSE )
         {
            error_code = ::GetLastError();
            WFCTRACE( TEXT( "Can't OpenProcessToken" ) );
            WFCTRACEERROR( error_code );
            return( FALSE );
         }

         TOKEN_PRIVILEGES token_privileges;

         ::ZeroMemory( &token_privileges, sizeof( token_privileges ) );

         if ( ::LookupPrivilegeValue( NULL, SE_RESTORE_NAME, &token_privileges.Privileges[ 0 ].Luid ) == FALSE )
         {
            error_code = ::GetLastError();
            WFCTRACE( TEXT( "Can't LookupPrivilegeValue for local machine" ) );
            WFCTRACEERROR( error_code );
            ::wfc_close_handle( token_handle );
            token_handle = NULL;
           return( FALSE );
         }

         token_privileges.PrivilegeCount             = 1;
         token_privileges.Privileges[ 0 ].Attributes = SE_PRIVILEGE_ENABLED;

         if ( ::AdjustTokenPrivileges( token_handle, FALSE, &token_privileges, 0, (PTOKEN_PRIVILEGES) NULL, 0 ) == FALSE )
         {
            error_code = ::GetLastError();
            WFCTRACE( TEXT( "Can't AdjustTokenPrivileges" ) );
            WFCTRACEERROR( error_code );
            ::wfc_close_handle( token_handle );
            token_handle = NULL;
            return( FALSE );
         }

         // Try the restore again

         m_ErrorCode = ::RegRestoreKey( m_KeyHandle,
                                        name_of_file_holding_saved_tree,
                                        volatility_flags );

         // Regardless of the turnout, we're through with the token handle

         ::wfc_close_handle( token_handle );
         token_handle = NULL;

         if ( m_ErrorCode != ERROR_SUCCESS )
         {
#if defined( _DEBUG )
            error_code = ::GetLastError();

            WFCTRACE( TEXT( "Can't RegRestoreKey" ) );
            WFCTRACEERROR( error_code );
#endif // _DEBUG
            return( FALSE );
         }

         return( TRUE );
      }
   }
   catch( ... )
   {
      m_ErrorCode = ERROR_EXCEPTION_IN_SERVICE;
      return( FALSE );
   }
}

BOOL CRegistry::Save( LPCTSTR name_of_file_to_hold_tree, LPSECURITY_ATTRIBUTES security_attributes_p )
{
   WFCLTRACEINIT( TEXT( "CRegistry::Save()" ) );

   ASSERT( name_of_file_to_hold_tree != NULL );

   if ( name_of_file_to_hold_tree == NULL )
   {
      m_ErrorCode = ERROR_INVALID_PARAMETER;
      return( FALSE );
   }

   // We were passed a pointer, do not trust it

   try
   {
      m_ErrorCode = ::RegSaveKey( m_KeyHandle, name_of_file_to_hold_tree, security_attributes_p );

      if ( m_ErrorCode == ERROR_SUCCESS )
      {
         return( TRUE );
      }
      else
      {
         WFCTRACEERROR( m_ErrorCode );
         return( FALSE );
      }
   }
   catch( ... )
   {
      m_ErrorCode = ERROR_EXCEPTION_IN_SERVICE;
      return( FALSE );
   }
}

BOOL CRegistry::SetBinaryValue( LPCTSTR name_of_value, const CByteArray& bytes_to_write )
{
   WFCLTRACEINIT( TEXT( "CRegistry::SetBinaryValue()" ) );

   DWORD size_of_buffer = bytes_to_write.GetSize();

   LPBYTE memory_buffer = NULL;
   
   try
   {
      memory_buffer = new BYTE[ size_of_buffer ];
   }
   catch( ... )
   {
      memory_buffer = NULL;
   }

   if ( memory_buffer == NULL )
   {
      m_ErrorCode = ::GetLastError();
      WFCTRACEERROR( m_ErrorCode );
      return( FALSE );
   }

   DWORD index = 0;

   while( index < size_of_buffer )
   {
      memory_buffer[ index ] = bytes_to_write.GetAt( index );
      index++;
   }

   BOOL return_value = SetValue( name_of_value, typeBinary, memory_buffer, size_of_buffer );

   delete [] memory_buffer;

   return( return_value );
}

BOOL CRegistry::SetDoubleWordValue( LPCTSTR name_of_value, DWORD value_to_write )
{
   WFCLTRACEINIT( TEXT( "CRegistry::SetDoubleWordValue()" ) );

   return( SetValue( name_of_value, typeDoubleWord, (const PBYTE) &value_to_write, sizeof( DWORD ) ) );
}

BOOL CRegistry::SetSecurity( const SECURITY_INFORMATION& security_information,
                             const PSECURITY_DESCRIPTOR  security_descriptor_p )
{
   WFCLTRACEINIT( TEXT( "CRegistry::SetSecurity()" ) );

   ASSERT( security_descriptor_p != NULL );

   if ( security_descriptor_p == NULL )
   {
      m_ErrorCode = ERROR_INVALID_PARAMETER;
      return( FALSE );
   }

   // We were passed a pointer, do not trust it

   try
   {
      m_ErrorCode = ::RegSetKeySecurity( m_KeyHandle, security_information, security_descriptor_p );

      if ( m_ErrorCode == ERROR_SUCCESS )
      {
         return( TRUE );
      }
      else
      {
         WFCTRACEERROR( m_ErrorCode );
         return( FALSE );
      }
   }
   catch( ... )
   {
      m_ErrorCode = ERROR_EXCEPTION_IN_SERVICE;
      return( FALSE );
   }
}

BOOL CRegistry::SetStringValue( LPCTSTR name_of_value, const CString& string_value )
{
   WFCLTRACEINIT( TEXT( "CRegistry::SetStringValue()" ) );

   // Thanks to Ravi Kiran (kravi@blr.sni.de) for finding a bug here in the UNICODE build

   return( SetValue( name_of_value, typeString, (const PBYTE) (LPCTSTR) string_value, ( string_value.GetLength() + 1 ) * sizeof( TCHAR ) ) );
}

BOOL CRegistry::SetStringArrayValue( LPCTSTR name_of_value, const CStringArray& string_array )
{
   WFCLTRACEINIT( TEXT( "CRegistry::SetStringArrayValue()" ) );

   DWORD size_of_buffer = 0;

   /*
   ** Find out how big our buffer needs to be...
   */

   int index             = 0;
   int number_of_strings = string_array.GetSize();

   CString temp_string;

   while( index < number_of_strings )
   {
      temp_string = string_array.GetAt( index );

      // Thanks go to George Koukoulommatis (gemasoft@hol.gr)
      // for finding another UNICODE bug here...

      size_of_buffer += ( ( temp_string.GetLength() + 1 ) * sizeof( TCHAR ) );
      index++;
   }

   /*
   ** Don't forget the second NULL needed for double null terminated strings...
   */

   // Thanks go to George Koukoulommatis (gemasoft@hol.gr)
   // for finding another UNICODE bug here...

   size_of_buffer += sizeof( TCHAR );

   LPBYTE memory_buffer = NULL;
   
   try
   {
      memory_buffer = new BYTE[ size_of_buffer ];
   }
   catch( ... )
   {
      memory_buffer = NULL;
   }

   if ( memory_buffer == NULL )
   {
      m_ErrorCode = ::GetLastError();
      WFCTRACEERROR( m_ErrorCode );
      return( FALSE );
   }

   ::ZeroMemory( memory_buffer, size_of_buffer );

   /*
   ** OK, now add the strings to the memory buffer
   */

   LPTSTR string = (LPTSTR) memory_buffer;

   index             = 0;
   int string_length = 0;

   while( index < number_of_strings )
   {
      temp_string = string_array.GetAt( index );
      _tcscpy( &string[ string_length ], temp_string );

      // Thanks go to George Koukoulommatis (gemasoft@hol.gr)
      // for finding another UNICODE bug here...

      string_length += ( ( temp_string.GetLength() + 1 ) * sizeof( TCHAR ) );

      index++;
   }

   // Thanks go to George Koukoulommatis (gemasoft@hol.gr)
   // for finding another UNICODE bug here...

   string_length += sizeof( TCHAR );

   BOOL return_value = TRUE;

   KeyValueTypes type = typeMultipleString; // A double NULL terminated string

   if ( SetValue( name_of_value, type, memory_buffer, size_of_buffer ) == FALSE )
   {
      return_value = FALSE;
   }

   delete [] memory_buffer;

   return( return_value );
}

BOOL CRegistry::SetValue( LPCTSTR name_of_value, const CByteArray& bytes_to_write )
{
   WFCLTRACEINIT( TEXT( "CRegistry::SetValue()" ) );

   return( SetBinaryValue( name_of_value, bytes_to_write ) );
}

BOOL CRegistry::SetValue( LPCTSTR name_of_value, DWORD value )
{
   WFCLTRACEINIT( TEXT( "CRegistry::SetValue()" ) );

   return( SetDoubleWordValue( name_of_value, value ) );
}

BOOL CRegistry::SetValue( LPCTSTR name_of_value, const CStringArray& strings_to_write )
{
   WFCLTRACEINIT( TEXT( "CRegistry::SetValue()" ) );

   return( SetStringArrayValue( name_of_value, strings_to_write ) );
}

BOOL CRegistry::SetValue( LPCTSTR name_of_value, const CString& string_to_write )
{
   WFCLTRACEINIT( TEXT( "CRegistry::SetValue()" ) );

   return( SetStringValue( name_of_value, string_to_write ) );
}

BOOL CRegistry::SetValue( LPCTSTR             name_of_value, 
                          const KeyValueTypes type_of_value_to_set, 
                          const PBYTE         address_of_value_data, 
                          const DWORD         size_of_data )
{
   WFCLTRACEINIT( TEXT( "CRegistry::SetValue()" ) );

   ASSERT( name_of_value         != NULL );
   ASSERT( address_of_value_data != NULL );

   if ( name_of_value == NULL || address_of_value_data == NULL )
   {
      m_ErrorCode = ERROR_INVALID_PARAMETER;
      return( FALSE );
   }

   // We were passed a pointer, do not trust it

   try
   {
      m_ErrorCode = ::RegSetValueEx( m_KeyHandle,
                                     name_of_value,
                                     0,
                                     type_of_value_to_set,
                                     address_of_value_data,
                                     size_of_data );

      if ( m_ErrorCode == ERROR_SUCCESS )
      {
         return( TRUE );
      }
      else
      {
         WFCTRACEERROR( m_ErrorCode );
         return( FALSE );
      }
   }
   catch( ... )
   {
      m_ErrorCode = ERROR_EXCEPTION_IN_SERVICE;
      return( FALSE );
   }
}

BOOL CRegistry::UnLoad( LPCTSTR name_of_subkey_to_unload )
{
   WFCLTRACEINIT( TEXT( "CRegistry::UnLoad()" ) );

   ASSERT( name_of_subkey_to_unload != NULL );

   if ( name_of_subkey_to_unload == NULL )
   {
      m_ErrorCode = ERROR_INVALID_PARAMETER;
      return( FALSE );
   }

   // We were passed a pointer, do not trust it

   try
   {
      m_ErrorCode = ::RegUnLoadKey( m_KeyHandle, name_of_subkey_to_unload );

      if ( m_ErrorCode == ERROR_SUCCESS )
      {
         return( TRUE );
      }
      else
      {
         WFCTRACEERROR( m_ErrorCode );
         return( FALSE );
      }
   }
   catch( ... )
   {
      m_ErrorCode = ERROR_EXCEPTION_IN_SERVICE;
      return( FALSE );
   }
}

// End of source

#if 0
<HTML>

<HEAD>
<TITLE>WFC - CRegistry</TITLE>
<META name="keywords" content="WFC, MFC extension library, freeware class library, Win32, source code">
<META name="description" content="The C++ class that handles the Win32 registry.">
</HEAD>

<BODY>

<H1>CRegistry</H1>
$Revision: 41 $
<HR>

<H2>Description</H2>

This class handles the registry API. The registry is a database
that allows applications to store stuff. Microsoft has weird terms
for dealing with the registry:

<DL COMPACT>

<DT>Hive<DD>Kinda like a virtual disk drive
<DT>Key<DD>Kinda like a directory
<DT>Value<DD>Kinda like a file 

</DL>

<H2>Data Members</H2>

None

<H2>Methods</H2>

<DL COMPACT>

<DT><PRE>BOOL <B><A NAME="Close">Close</A></B>( void )</PRE><DD>
Closes the connection to the registry.

<DT><PRE>BOOL <B><A NAME="Connect">Connect</A></B>( HKEY key_to_open = HKEY_CURRENT_USER, LPCTSTR computer_name = NULL )</PRE><DD>
Connects to a registry on a computer. The default is to connect to
the local computer. If <CODE>computer_name</CODE> is not NULL,
it will connect to that machine on the network.

<DT><PRE>BOOL <B><A NAME="Create">Create</A></B>( LPCTSTR               name_of_subkey,
             LPCTSTR               name_of_class         = NULL,
             CreateOptions         options               = optionsNonVolatile,
             CreatePermissions     permissions           = permissionAllAccess,
             LPSECURITY_ATTRIBUTES security_attributes_p = NULL,
             CreationDisposition * disposition_p         = NULL )</PRE><DD>
Creates a subkey in a registry hive. <CODE>options</CODE> can
be one of:
<UL>
<LI>optionsNonVolatile
<LI>optionsVolatile
</UL>
<CODE>permissions</CODE> can be a combination of:
<UL>
<LI>permissionAllAccess
<LI>permissionCreateLink
<LI>permissionCreateSubKey
<LI>permissionEnumerateSubKeys
<LI>permissionExecute
<LI>permissionNotify
<LI>permissionQueryValue
<LI>permissionRead
<LI>permissionSetValue
<LI>permissionWrite
</UL>
<CODE>disposition_p</CODE> if not NULL, will be filled with either:
<UL>
<LI>dispositionCreatedNewKey
<LI>dispositionOpenedExistingKey
</UL>
It returns TRUE on success or FALSE on failure.
The reason for the failure can be retrieved via <B>GetErrorCode</B>().

<DT><PRE>BOOL <B><A NAME="DeleteKey">DeleteKey</A></B>( LPCTSTR name_of_subkey_to_delete )</PRE><DD>
Deletes a key and all subkeys (even in NT) of that key.
It returns TRUE on success or FALSE on failure.
The reason for the failure can be retrieved via <B>GetErrorCode</B>().

<DT><PRE>BOOL <B><A NAME="DeleteValue">DeleteValue</A></B>( LPCTSTR name_of_value_to_delete )</PRE><DD>
Deletes a specific value.
It returns TRUE on success or FALSE on failure.
The reason for the failure can be retrieved via <B>GetErrorCode</B>().

<DT><PRE>BOOL <B><A NAME="EnumerateKeys">EnumerateKeys</A></B>( const DWORD subkey_index,
                    CString&amp;    subkey_name,
                    CString&amp;    class_name )</PRE><DD>
Let's you list the names of the keys.
It returns TRUE on success or FALSE on failure.
The reason for the failure can be retrieved via <B>GetErrorCode</B>().

<DT><PRE>BOOL <B><A NAME="EnumerateValues">EnumerateValues</A></B>( const DWORD    value_index,
                      CString&amp;       name_of_value,
                      KeyValueTypes&amp; type_code,
                      LPBYTE         data_buffer,
                      DWORD&amp;         size_of_data_buffer )</PRE><DD>
Let's you list the names of the values within a key. If you do not wish
to retrieve the data, set <CODE>data_buffer</CODE> to NULL.
<CODE>size_of_data_buffer</CODE> will be filled with the number of
bytes put into <CODE>data_buffer</CODE>.
It returns TRUE on success or FALSE on failure.
The reason for the failure can be retrieved via <B>GetErrorCode</B>().
<CODE>type_code</CODE> will be one of:
<UL>
<LI>typeBinary
<LI>typeDoubleWord
<LI>typeDoubleWordLittleEndian
<LI>typeDoubleWordBigEndian
<LI>typeUnexpandedString
<LI>typeSymbolicLink
<LI>typeMultipleString
<LI>typeNone
<LI>typeResourceList
<LI>typeString
</UL>

<B>NOTE:</B> Remember that <CODE>size_of_data_buffer</CODE> must
be reset within your enumerating loop because it is set by the
function call. If you do not, you will probably get an error code
of 234 (<CODE>ERROR_MORE_DATA</CODE>). Here's what a proper loop
should look like:

<PRE><CODE>BYTE buffer[ 4096 ];

DWORD size_of_buffer = 4096;

while( registry.EnumerateValues( enumerator, name, type, buffer, size_of_buffer ) == TRUE )
{
   _tprintf( TEXT( &quot;Found %s, length is %lu\n&quot; ), (LPCTSTR) name, size_of_buffer );
   size_of_buffer = 4096;
   enumerator++;
}</CODE></PRE>

<DT><PRE>BOOL <B><A NAME="Flush">Flush</A></B>( void )</PRE><DD>
Writes all cached changes to disk.
It returns TRUE on success or FALSE on failure.
The reason for the failure can be retrieved via <B>GetErrorCode</B>().

<DT><PRE>BOOL <B><A NAME="GetBinaryValue">GetBinaryValue</A></B>( LPCTSTR name_of_value, CByteArray&amp; bytes )</PRE><DD>
Retrieves the binary data and puts it into <CODE>bytes</CODE>.
It returns TRUE on success or FALSE on failure.
The reason for the failure can be retrieved via <B>GetErrorCode</B>().

<DT><PRE>void <B><A NAME="GetClassName">GetClassName</A></B>( CString&amp; class_name ) const</PRE><DD>
Retrieves the name of the class of key you have opened.

<DT><PRE>void <B><A NAME="GetComputerName">GetComputerName</A></B>( CString&amp; computer_name ) const</PRE><DD>
Retrieves the name of the computer where the hive is located.

<DT><PRE>BOOL <B><A NAME="GetDoubleWordValue">GetDoubleWordValue</A></B>( LPCTSTR name_of_value, DWORD&amp; value )</PRE><DD>
Retrieves the DWORD data value.
It returns TRUE on success or FALSE on failure.
The reason for the failure can be retrieved via <B>GetErrorCode</B>().

<DT><PRE>DWORD <B><A NAME="GetErrorCode">GetErrorCode</A></B>( void ) const</PRE><DD>
Retrieves the error code. Call this function
if any other class method returns FALSE.

<DT><PRE>void <B><A NAME="GetKeyName">GetKeyName</A></B>( CString&amp; key_name ) const</PRE><DD>
Retrieves the name of the current key.

<DT><PRE>DWORD <B><A NAME="GetNumberOfSubKeys">GetNumberOfSubKeys</A></B>( void ) const</PRE><DD>
Retrieves the number of keys contained within the current key.

<DT><PRE>DWORD <B><A NAME="GetNumberOfValues">GetNumberOfValues</A></B>( void ) const</PRE><DD>
Retrieves the number of values contained within the current key.

<DT><PRE>void <B><A NAME="GetRegistryName">GetRegistryName</A></B>( CString&amp; registry_name ) const</PRE><DD>
Retrieves the name of the registry you are playing with.

<DT><PRE>BOOL <B><A NAME="GetSecurity">GetSecurity</A></B>( const SECURITY_INFORMATION what_you_want_to_know,
                  PSECURITY_DESCRIPTOR       data_buffer,
                  DWORD&amp;                     size_of_data_buffer )</PRE><DD>
Retrieves security information.
It returns TRUE on success or FALSE on failure.
The reason for the failure can be retrieved via <B>GetErrorCode</B>().

<DT><PRE>BOOL <B><A NAME="GetStringValue">GetStringValue</A></B>( LPCTSTR name_of_value, CString&amp; return_string )</PRE><DD>
Retrieves a string value (<CODE><B>REG_SZ</B></CODE>).
It returns TRUE on success or FALSE on failure.
The reason for the failure can be retrieved via <B>GetErrorCode</B>().

<DT><PRE>BOOL <B><A NAME="GetStringArrayValue">GetStringArrayValue</A></B>( LPCTSTR name_of_value, CStringArray&amp; return_array )</PRE><DD>
Retrieves a value containing multiple strings (REG_MULTI_SZ) and puts it into a CStringArray.
It returns TRUE on success or FALSE on failure.
The reason for the failure can be retrieved via <B>GetErrorCode</B>().

<DT><PRE>BOOL <B><A NAME="GetValue">GetValue</A></B>( LPCTSTR name_of_value, CByteArray&amp; return_array )
BOOL <B>GetValue</B>( LPCTSTR name_of_value, DWORD&amp; return_value )
BOOL <B>GetValue</B>( LPCTSTR name_of_value, CString&amp; return_string )
BOOL <B>GetValue</B>( LPCTSTR name_of_value, CStringArray&amp; return_array )</PRE><DD>
Overloaded function that calls the proper GetXValue function.
It returns TRUE on success or FALSE on failure.
The reason for the failure can be retrieved via <B>GetErrorCode</B>().

<DT><PRE>BOOL <B><A NAME="Load">Load</A></B>( LPCTSTR name_of_subkey, LPCTSTR name_of_file_containg_information )</PRE><DD>
Loads a subkey from a file.
It returns TRUE on success or FALSE on failure.
The reason for the failure can be retrieved via <B>GetErrorCode</B>().

<DT><PRE>BOOL <B><A NAME="NotifyChange">NotifyChange</A></B>( const HANDLE event_handle                       = NULL,
                   const NotifyChangeFilter changes_to_be_reported = notifyLastSet,
                   const BOOL this_subkey_or_all_subkeys           = changeSpecifiedKeyOnly,
                   const BOOL wait_for_change_or_signal_event      = WAIT_FOR_CHANGE )</PRE><DD>
Lets you watch a key (with or without subkeys) to see if anything changes.
It returns TRUE on success or FALSE on failure.
The reason for the failure can be retrieved via <B>GetErrorCode</B>().
<CODE>changes_to_be_reported</CODE> can be one of:
<UL>
<LI>notifyName
<LI>notifyAttributes
<LI>notifyLastSet
<LI>notifySecurity
</UL>

<DT><PRE>BOOL <B><A NAME="Open">Open</A></B>( LPCTSTR name_of_subkey_to_open,
           const CreatePermissions security_access_mask = permissionAllAccess )</PRE><DD>
Opens a subkey.
It returns TRUE on success or FALSE on failure.
The reason for the failure can be retrieved via <B>GetErrorCode</B>().
<CODE>security_access_mask</CODE> can be a combination of:
<UL>
<LI>permissionAllAccess
<LI>permissionCreateLink
<LI>permissionCreateSubKey
<LI>permissionEnumerateSubKeys
<LI>permissionExecute
<LI>permissionNotify
<LI>permissionQueryValue
<LI>permissionRead
<LI>permissionSetValue
<LI>permissionWrite
</UL>

<DT><PRE>BOOL <B><A NAME="QueryInfo">QueryInfo</A></B>( void )</PRE><DD>
Tells <B>CRegistry</B> to load information because you're about to call <B>QueryValue</B>().
This loads information that can be retrieved via <B>GetNumberOfSubkeys</B>()
or <B>GetNumberOfValues</B>().
It returns TRUE on success or FALSE on failure.
The reason for the failure can be retrieved via <B>GetErrorCode</B>().

<DT><PRE>BOOL <B><A NAME="QueryValue">QueryValue</A></B>( LPCTSTR        name_of_value,
                 KeyValueTypes&amp; value_type,
                 LPBYTE         address_of_buffer,
                 DWORD&amp;         size_of_buffer )</PRE><DD>
Allows you to retrieve a value without knowing it's type.
It returns TRUE on success or FALSE on failure.
The reason for the failure can be retrieved via <B>GetErrorCode</B>().
<CODE>value_type</CODE> will be filled with one of the following values:
<UL>
<LI>typeBinary
<LI>typeDoubleWord
<LI>typeDoubleWordLittleEndian
<LI>typeDoubleWordBigEndian
<LI>typeUnexpandedString
<LI>typeSymbolicLink
<LI>typeMultipleString
<LI>typeNone
<LI>typeResourceList
<LI>typeString
</UL>

<DT><PRE>BOOL <B><A NAME="Replace">Replace</A></B>( LPCTSTR name_of_subkey,
              LPCTSTR name_of_file_with_new_data,
              LPCTSTR name_of_backup_file )</PRE><DD>
Allows you to replace a subkey with data from a file.
It returns TRUE on success or FALSE on failure.
The reason for the failure can be retrieved via <B>GetErrorCode</B>().

<DT><PRE>BOOL <B><A NAME="Restore">Restore</A></B>( LPCTSTR name_of_file_holding_saved_tree, const DWORD volitility_flags = NULL )</PRE><DD>
Restores a subkey that was backed up to a file.
It returns TRUE on success or FALSE on failure.
The reason for the failure can be retrieved via <B>GetErrorCode</B>().

<DT><PRE>BOOL <B><A NAME="Save">Save</A></B>( LPCTSTR name_of_file_to_hold_tree, LPSECURITY_ATTRIBUTES security_attributes_p = NULL )</PRE><DD>
Allows you to save a subtree to a file (so you can call <B>Restore</B>()).
It returns TRUE on success or FALSE on failure.
The reason for the failure can be retrieved via <B>GetErrorCode</B>().

<DT><PRE>BOOL <B><A NAME="SetBinaryValue">SetBinaryValue</A></B>( LPCTSTR name_of_value, const CByteArray&amp; bytes_to_write )</PRE><DD>
Allows you to write a binary (raw bytes) to a value in a key.
It returns TRUE on success or FALSE on failure.
The reason for the failure can be retrieved via <B>GetErrorCode</B>().

<DT><PRE>BOOL <B><A NAME="SetDoubleWordValue">SetDoubleWordValue</A></B>( LPCTSTR name_of_value, DWORD value_to_write )</PRE><DD>
Allows you to write a DWORD value to a key.
It returns TRUE on success or FALSE on failure.
The reason for the failure can be retrieved via <B>GetErrorCode</B>().

<DT><PRE>BOOL <B><A NAME="SetSecurity">SetSecurity</A></B>( const SECURITY_INFORMATION&amp; security_information,
                  const PSECURITY_DESCRIPTOR security_descriptor_p )</PRE><DD>
Allows you to put security onto a subkey.
It returns TRUE on success or FALSE on failure.
The reason for the failure can be retrieved via <B>GetErrorCode</B>().

<DT><PRE>BOOL <B><A NAME="SetStringValue">SetStringValue</A></B>( LPCTSTR name_of_value, const CString&amp; string_value )</PRE><DD>
Allows you to write a string value to a key.
It returns TRUE on success or FALSE on failure.
The reason for the failure can be retrieved via <B>GetErrorCode</B>().

<DT><PRE>BOOL <B><A NAME="SetStringArrayValue">SetStringArrayValue</A></B>( LPCTSTR name_of_value, const CStringArray&amp; string_array )</PRE><DD>
Allows you to write a bunch of strings to a value in a key.
It returns TRUE on success or FALSE on failure.
The reason for the failure can be retrieved via <B>GetErrorCode</B>().

<DT><PRE>BOOL <B><A NAME="SetValue">SetValue</A></B>( LPCTSTR name_of_value, const CByteArray&amp; bytes_to_write );
BOOL <B>SetValue</B>( LPCTSTR name_of_value, DWORD value );
BOOL <B>SetValue</B>( LPCTSTR name_of_value, const CStringArray&amp; strings_to_write );
BOOL <B>SetValue</B>( LPCTSTR name_of_value, const CString&amp; string_to_write );
BOOL <B>SetValue</B>( LPCTSTR             name_of_subkey,
               const KeyValueTypes type_of_value_to_set,
               CONST PBYTE         address_of_value_data,
               const DWORD         size_of_data )</PRE><DD>
Overloaded method that figures out what type of value you want to set.
It returns TRUE on success or FALSE on failure.
The reason for the failure can be retrieved via <B>GetErrorCode</B>().

<DT><PRE>BOOL <B><A NAME="UnLoad">UnLoad</A></B>( LPCTSTR name_of_subkey_to_unload )</PRE><DD>
Unloads a previously <B>Load</B>()'ed key. 
It returns TRUE on success or FALSE on failure.
The reason for the failure can be retrieved via <B>GetErrorCode</B>().

</DL>

<H2>Example</H2>

<PRE><CODE>#include &lt;wfc.h&gt;
#pragma hdrstop

void test_CRegistry( void )
{
   <A HREF="WfcTrace.htm">WFCTRACEINIT</A>( TEXT( &quot;test_CRegistry()&quot; ) );

   <B>CRegistry</B> registry;

   if ( registry.Connect( CRegistry::keyLocalMachine ) == FALSE )
   {
      TRACE( TEXT( &quot;Can't connect to registry\n&quot; ) );
      return;
   }

   if ( registry.Open( TEXT( &quot;SYSTEM\\CurrentControlSet\\Services\\EventLog\\Application&quot; ),
                      (CRegistry::CreatePermissions)(CRegistry::permissionRead | CRegistry::permissionSetValue)
                     ) == FALSE )
   {
      TRACE( TEXT( &quot;Can't open key\n&quot; ) );
      
      ReportError( registry.GetErrorCode() );
      return;
   }

   CStringArray string_array;

   string_array.RemoveAll();

   if ( registry.GetStringArrayValue( TEXT( &quot;Sources&quot; ), string_array ) != FALSE )
   {
      int index = 0;
      int number_of_strings = string_array.GetSize();

      TRACE1( TEXT( &quot;There are %d strings\n&quot; ), number_of_strings );

      CString temp_string;

      while( index &lt; number_of_strings )
      {
         temp_string = string_array[ index ];

         TRACE2( TEXT( &quot;%d - \&quot;%s\&quot;\n&quot; ), index + 1, (LPCTSTR) temp_string );
         index++;
      }

      if ( registry.SetStringArrayValue( TEXT( &quot;TempSources&quot; ), string_array ) == FALSE )
      {
         ReportError( registry.GetErrorCode() );
      }
   }

   if ( registry.SetValue( TEXT( &quot;QFile&quot; ), &quot;Sammy&quot; ) == FALSE )
   {
      TRACE( TEXT( &quot;registry.SetValue failed\n&quot; ) );
      ReportError( registry.GetErrorCode() );
   }
   else
   {
      TRACE( TEXT( &quot;Set QFile to Sammy\n&quot; ) );
   }

   CString temp_sammy( TEXT( &quot;&quot; ) );

   if ( registry.GetValue( TEXT( &quot;QFile&quot; ), temp_sammy ) == FALSE )
   {
      TRACE( TEXT( &quot;registry.GetValue failed\n&quot; ) );
      ReportError( registry.GetErrorCode() );
   }
   else
   {
      if ( temp_sammy.Compare( TEXT( &quot;Sammy&quot; ) ) == 0 )
      {
         TRACE( TEXT( &quot;GetValue OK\n&quot; ) );
      }
      else
      {
         TRACE1( TEXT( &quot;FAIL! QFile is \&quot;%s\&quot;\n&quot; ), (LPCTSTR) temp_sammy );
      }
   }
}</CODE></PRE>

<H2>API's Used</H2>

<B>CRegistry</B> encapsulates the following API's:
<UL>
<LI>RegCloseKey
<LI>RegConnectRegistry
<LI>RegCreateKeyEx
<LI>RegDeleteValue
<LI>RegEnumKeyEx
<LI>RegEnumValue
<LI>RegFlushKey
<LI>RegGetKeySecurity
<LI>RegLoadKey
<LI>RegNotifyChangeKeyValue
<LI>RegOpenKeyEx
<LI>RegQueryInfoKey
<LI>RegQueryValueEx
<LI>RegReplaceKey
<LI>RegRestoreKey
<LI>RegSaveKey
<LI>RegSetKeySecurity
<LI>RegSetValueEx
<LI>RegUnLoadKey
</UL>

<HR><I>Copyright, 2000, <A HREF="mailto:wfc@pobox.com">Samuel R. Blackburn</A></I><BR>
$Workfile: registry.cpp $<BR>
$Modtime: 3/22/00 4:46a $
</BODY>

</HTML>
#endif
