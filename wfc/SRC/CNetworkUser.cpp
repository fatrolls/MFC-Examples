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
** $Workfile: CNetworkUser.cpp $
** $Revision: 24 $
** $Modtime: 1/04/00 5:18a $
** $Reuse Tracing Code: 1 $
*/

#if defined( _DEBUG ) && ! defined( WFC_STL )
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

#if ! defined(  WFC_NO_SERIALIZATION )
IMPLEMENT_SERIAL( CNetworkUsers, CNetwork, 1 )
#endif // WFC_NO_SERIALIZATION

#if defined( _DEBUG ) && ! defined( WFC_STL )
#define new DEBUG_NEW
#endif // _DEBUG

CNetworkUsers::CNetworkUsers()
{
   WFCLTRACEINIT( TEXT( "CNetworkUsers::CNetworkUsers()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   m_Initialize();
}

CNetworkUsers::CNetworkUsers( LPCTSTR machine_name )
{
   WFCLTRACEINIT( TEXT( "CNetworkUsers::CNetworkUsers( LPCTSTR )" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   m_Initialize();
   Open( machine_name );
}

CNetworkUsers::~CNetworkUsers()
{
   WFCLTRACEINIT( TEXT( "CNetworkUsers::~CNetworkUsers()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   Close();
   m_Initialize();
}

BOOL CNetworkUsers::Add( const CNetworkUserInformation& user_to_add )
{
   WFCLTRACEINIT( TEXT( "CNetworkUsers::Add()" ) );

   USER_INFO_2 user_information;
   WCHAR wide_name[ 1024 ];
   WCHAR wide_password[ 1024 ];
   WCHAR wide_home_directory[ 1024 ];
   WCHAR wide_comment[ 1024 ];
   WCHAR wide_script_path[ 1024 ];
   WCHAR wide_full_name[ 1024 ];
   WCHAR wide_user_comment[ 1024 ];
   WCHAR wide_parameters[ 1024 ];
   WCHAR wide_workstations[ 1024 ];
   WCHAR wide_logon_server[ 1024 ];

   ::ZeroMemory( &user_information,   sizeof( user_information    ) );
   ::ZeroMemory( wide_name,           sizeof( wide_name           ) );
   ::ZeroMemory( wide_password,       sizeof( wide_password       ) );
   ::ZeroMemory( wide_home_directory, sizeof( wide_home_directory ) );
   ::ZeroMemory( wide_comment,        sizeof( wide_comment        ) );
   ::ZeroMemory( wide_script_path,    sizeof( wide_script_path    ) );
   ::ZeroMemory( wide_full_name,      sizeof( wide_full_name      ) );
   ::ZeroMemory( wide_user_comment,   sizeof( wide_user_comment   ) );
   ::ZeroMemory( wide_parameters,     sizeof( wide_parameters     ) );
   ::ZeroMemory( wide_workstations,   sizeof( wide_workstations   ) );
   ::ZeroMemory( wide_logon_server,   sizeof( wide_logon_server   ) );

#if ! defined( UNICODE )

   // We need to convert the ASCII strings to UNICODE

   ::ASCII_to_UNICODE( user_to_add.Name,          wide_name           );
   ::ASCII_to_UNICODE( user_to_add.Password,      wide_password       );
   ::ASCII_to_UNICODE( user_to_add.HomeDirectory, wide_home_directory );
   ::ASCII_to_UNICODE( user_to_add.Comment,       wide_comment        );
   ::ASCII_to_UNICODE( user_to_add.ScriptPath,    wide_script_path    );
   ::ASCII_to_UNICODE( user_to_add.FullName,      wide_full_name      );
   ::ASCII_to_UNICODE( user_to_add.UserComment,   wide_user_comment   );
   ::ASCII_to_UNICODE( user_to_add.Parameters,    wide_parameters     );
   ::ASCII_to_UNICODE( user_to_add.Workstations,  wide_workstations   );
   ::ASCII_to_UNICODE( user_to_add.LogonServer,   wide_logon_server   );

#else

   // We're already UNICODE

   ::wcscpy( (LPTSTR) wide_name,           user_to_add.Name          );
   ::wcscpy( (LPTSTR) wide_password,       user_to_add.Password      );
   ::wcscpy( (LPTSTR) wide_home_directory, user_to_add.HomeDirectory );
   ::wcscpy( (LPTSTR) wide_comment,        user_to_add.Comment       );
   ::wcscpy( (LPTSTR) wide_script_path,    user_to_add.ScriptPath    );
   ::wcscpy( (LPTSTR) wide_full_name,      user_to_add.FullName      );
   ::wcscpy( (LPTSTR) wide_user_comment,   user_to_add.UserComment   );
   ::wcscpy( (LPTSTR) wide_parameters,     user_to_add.Parameters    );
   ::wcscpy( (LPTSTR) wide_workstations,   user_to_add.Workstations  );
   ::wcscpy( (LPTSTR) wide_logon_server,   user_to_add.LogonServer   );

#endif

   user_information.usri2_name           = wide_name;
   user_information.usri2_password       = wide_password;
   user_information.usri2_password_age   = 0;
   user_information.usri2_priv           = user_to_add.Privileges;
   user_information.usri2_home_dir       = wide_home_directory;
   user_information.usri2_comment        = wide_comment;
   user_information.usri2_flags          = user_to_add.Flags;
   user_information.usri2_script_path    = wide_script_path;
   user_information.usri2_auth_flags     = user_to_add.AuthenticationFlags;
   user_information.usri2_full_name      = wide_full_name;
   user_information.usri2_usr_comment    = wide_user_comment;
   user_information.usri2_parms          = wide_parameters;
   user_information.usri2_workstations   = wide_workstations;
   user_information.usri2_last_logon     = 0;
   user_information.usri2_last_logoff    = 0;
   user_information.usri2_acct_expires   = 0;
   user_information.usri2_max_storage    = user_to_add.MaximumStorage;
   user_information.usri2_units_per_week = user_to_add.UnitsPerWeek;
//   user_information.usri2_logon_hours    = user_to_add.LogonHours.GetData();
   user_information.usri2_bad_pw_count   = user_to_add.BadPasswordCount;
   user_information.usri2_num_logons     = user_to_add.NumberOfLogons;
   user_information.usri2_logon_server   = wide_logon_server;
   user_information.usri2_country_code   = user_to_add.CountryCode;
   user_information.usri2_code_page      = user_to_add.CodePage;

   BYTE logon_hours[ 21 ];

   int index = 0;

   while( index < user_to_add.LogonHours.GetSize() )
   {
      if ( index < 21 )
      {
         logon_hours[ index ] = user_to_add.LogonHours.GetAt( index );
      }

      index++;
   }

   while( index < 21 )
   {
      logon_hours[ index ] = 0xFF;
      index++;
   }

   DWORD parameter_causing_the_error = 0;

   m_ErrorCode = ::NetUserAdd( m_WideDoubleBackslashPreceededMachineName,
                               2,
                     (BYTE *) &user_information,
                              &parameter_causing_the_error );

   if ( m_ErrorCode != NERR_Success ) 
   {
      WFCTRACE( TEXT( "NetUserAdd() Failed" ) );

#if defined( _DEBUG )
      if ( m_ErrorCode == ERROR_INVALID_PARAMETER )
      {
         switch( parameter_causing_the_error )
         {
            case USER_NAME_PARMNUM:

               WFCTRACE( TEXT( "Invalid USER_NAME_PARMNUM parameter" ) );
               break;

            case USER_PASSWORD_PARMNUM:

               WFCTRACE( TEXT( "Invalid USER_PASSWORD_PARMNUM parameter" ) );
               break;

            case USER_PASSWORD_AGE_PARMNUM:

               WFCTRACE( TEXT( "Invalid USER_PASSWORD_AGE_PARMNUM parameter" ) );
               break;

            case USER_PRIV_PARMNUM:

               WFCTRACE( TEXT( "Invalid USER_PRIV_PARMNUM parameter" ) );
               break;

            case USER_HOME_DIR_PARMNUM:

               WFCTRACE( TEXT( "Invalid USER_HOME_DIR_PARMNUM parameter" ) );
               break;

            case USER_COMMENT_PARMNUM:

               WFCTRACE( TEXT( "Invalid USER_COMMENT_PARMNUM parameter" ) );
               break;

            case USER_FLAGS_PARMNUM:

               WFCTRACE( TEXT( "Invalid USER_FLAGS_PARMNUM parameter" ) );
               break;

            case USER_SCRIPT_PATH_PARMNUM:

               WFCTRACE( TEXT( "Invalid USER_SCRIPT_PATH_PARMNUM parameter" ) );
               break;

            case USER_AUTH_FLAGS_PARMNUM:

               WFCTRACE( TEXT( "Invalid USER_AUTH_FLAGS_PARMNUM parameter" ) );
               break;

            case USER_FULL_NAME_PARMNUM:

               WFCTRACE( TEXT( "Invalid USER_FULL_NAME_PARMNUM parameter" ) );
               break;

            case USER_USR_COMMENT_PARMNUM:

               WFCTRACE( TEXT( "Invalid USER_USR_COMMENT_PARMNUM parameter" ) );
               break;

            case USER_PARMS_PARMNUM:

               WFCTRACE( TEXT( "Invalid USER_PARMS_PARMNUM parameter" ) );
               break;

            case USER_WORKSTATIONS_PARMNUM:

               WFCTRACE( TEXT( "Invalid USER_WORKSTATIONS_PARMNUM parameter" ) );
               break;

            case USER_LAST_LOGON_PARMNUM:

               WFCTRACE( TEXT( "Invalid USER_LAST_LOGON_PARMNUM parameter" ) );
               break;

            case USER_LAST_LOGOFF_PARMNUM:

               WFCTRACE( TEXT( "Invalid USER_LAST_LOGOFF_PARMNUM parameter" ) );
               break;

            case USER_ACCT_EXPIRES_PARMNUM:

               WFCTRACE( TEXT( "Invalid USER_ACCT_EXPIRES_PARMNUM parameter" ) );
               break;

            case USER_MAX_STORAGE_PARMNUM:

               WFCTRACE( TEXT( "Invalid USER_MAX_STORAGE_PARMNUM parameter" ) );
               break;

            case USER_UNITS_PER_WEEK_PARMNUM:

               WFCTRACE( TEXT( "Invalid USER_UNITS_PER_WEEK_PARMNUM parameter" ) );
               break;

            case USER_LOGON_HOURS_PARMNUM:

               WFCTRACE( TEXT( "Invalid USER_LOGON_HOURS_PARMNUM parameter" ) );
               break;

            case USER_PAD_PW_COUNT_PARMNUM:

               WFCTRACE( TEXT( "Invalid USER_PAD_PW_COUNT_PARMNUM parameter" ) );
               break;

            case USER_NUM_LOGONS_PARMNUM:

               WFCTRACE( TEXT( "Invalid USER_NUM_LOGONS_PARMNUM parameter" ) );
               break;

            case USER_LOGON_SERVER_PARMNUM:

               WFCTRACE( TEXT( "Invalid USER_LOGON_SERVER_PARMNUM parameter" ) );
               break;

            case USER_COUNTRY_CODE_PARMNUM:

               WFCTRACE( TEXT( "Invalid USER_COUNTRY_CODE_PARMNUM parameter" ) );
               break;

            case USER_CODE_PAGE_PARMNUM:

               WFCTRACE( TEXT( "Invalid USER_CODE_PAGE_PARMNUM parameter" ) );
               break;

            case USER_PRIMARY_GROUP_PARMNUM:

               WFCTRACE( TEXT( "Invalid USER_PRIMARY_GROUP_PARMNUM parameter" ) );
               break;

            case USER_PROFILE_PARMNUM:

               WFCTRACE( TEXT( "Invalid USER_PROFILE_PARMNUM parameter" ) );
               break;

            case USER_HOME_DIR_DRIVE_PARMNUM:

               WFCTRACE( TEXT( "Invalid USER_HOME_DIR_DRIVE_PARMNUM parameter" ) );
               break;

            default:

               WFCTRACE( TEXT( "Unknown parameter error" ) );
               break;
         }
      }
#endif

      return( FALSE );
   }

   return( TRUE );
}

void CNetworkUsers::Close( void )
{
   WFCLTRACEINIT( TEXT( "CNetworkUsers::Close()" ) );

   CNetwork::Close();

   if ( m_3InformationBuffer != NULL )
   {
      WFCTRACE( TEXT( "Freeing buffer 3" ) );
      ::NetApiBufferFree( m_3InformationBuffer );
      m_3InformationBuffer = NULL;
   }

   if ( m_2InformationBuffer != NULL )
   {
      WFCTRACE( TEXT( "Freeing buffer 2" ) );
      ::NetApiBufferFree( m_2InformationBuffer );
      m_2InformationBuffer = NULL;
   }

   if ( m_1InformationBuffer != NULL )
   {
      WFCTRACE( TEXT( "Freeing buffer 1" ) );
      ::NetApiBufferFree( m_1InformationBuffer );
      m_1InformationBuffer = NULL;
   }

   if ( m_10InformationBuffer != NULL )
   {
      WFCTRACE( TEXT( "Freeing buffer 10" ) );
      ::NetApiBufferFree( m_10InformationBuffer );
      m_10InformationBuffer = NULL;
   }

   if ( m_0InformationBuffer != NULL )
   {
      WFCTRACE( TEXT( "Freeing buffer 0" ) );
      ::NetApiBufferFree( m_0InformationBuffer );
      m_0InformationBuffer = NULL;
   }
}

BOOL CNetworkUsers::CreateComputerAccount( LPCTSTR computer_name, DWORD type_of_account )
{
   WFCLTRACEINIT( TEXT( "CNetworkUsers::CreateComputerAccount()" ) );

   // This method is described in Knowledge Base Article Q136867

   // Creating a computer account establishes the "permitted to
   // trust this domain" side of the domain trust relationship.
   // Article Q145697 discusses the manipulation of the "Trusted Domains" 
   // side of the domain trust relationship, at the domain controller level.

   if ( type_of_account != accountMachine                &&
        type_of_account != accountBackupDomainController &&
        type_of_account != accountInterdomain )
   {
      WFCTRACE( TEXT( "type_of_account isn't accountMachine, accountBackupDomainController or accountInterdomain" ) );
      m_ErrorCode = ERROR_INVALID_PARAMETER;
      return( FALSE );
   }

   CString account_name;

   CNetworkUserInformation information;

   information.SetAddDefaults();

   // We were passed a pointer, don't trust it

   try
   {
      information.Name = computer_name;
      
      /*
      ** The computer account name should be all uppercase for consistency
      ** with Windows NT account management utilities.
      */

      information.Name.MakeUpper();

      /*
      ** The maximum computer name length is MAX_COMPUTERNAME_LENGTH (15).
      ** This length does not include the trailing dollar sign ($). 
      */

      if ( information.Name.GetLength() > MAX_COMPUTERNAME_LENGTH )
      {
         WFCTRACE( TEXT( "Computer name is too long" ) );
         m_ErrorCode = ERROR_INVALID_ACCOUNT_NAME;
         return( FALSE );
      }

      /*
      ** The password for a new computer account should be the lowercase 
      ** representation of the computer account name, without the trailing 
      ** dollar sign ($). For interdomain trust, the password can be an 
      ** arbitrary value that matches the value specified on the trust 
      ** side of the relationship.
      */

      information.Password = information.Name;
      information.Password.MakeLower();

      /*
      ** The maximum password length is LM20_PWLEN (14). The password
      ** should be truncated to this length if the computer account name
      ** exceeds this length.
      */

      if ( information.Password.GetLength() > LM20_PWLEN )
      {
         information.Password = information.Password.Left( LM20_PWLEN );
      }

      /*
      ** A computer account name always has a trailing dollar sign ($). 
      ** Any APIs used to manage computer accounts must build the computer
      ** name such that the last character of the computer account name 
      ** is a dollar sign ($). For interdomain trust, the account name is 
      ** TrustingDomainName$. 
      */

      if ( information.Name.GetAt( information.Name.GetLength() - 1 ) != TEXT( '$' ) )
      {
         information.Name += TEXT( "$" );
      }

      /*
      ** The SeMachineAccountPrivilege can be granted on the target computer
      ** to give specified users the ability to create computer accounts.
      ** This gives non-administrators the ability to create computer
      ** accounts. The caller needs to enable this privilege prior to adding
      ** the computer account.
      */

      /*
      ** Computer account management should take place on the primary
      ** domain controller for the target domain.
      */

      BYTE * buffer_p = NULL;

      if ( ::NetGetDCName( NULL, NULL, &buffer_p ) != NERR_Success )
      {
         WFCTRACE( TEXT( "Can't get DCName" ) );
         return( FALSE );
      }

      information.Privileges = USER_PRIV_USER;
      information.Flags = type_of_account | UF_SCRIPT;

      CString primary_domain_controller;

#if ! defined( UNICODE )

      // We ain't UNICODE so we need to convert

      ::wfc_convert_lpcwstr_to_cstring( (LPCWSTR) buffer_p, primary_domain_controller );

#else

      // We're already UNICODE so we should be OK

      primary_domain_controller = (LPCTSTR) buffer_p;

#endif // UNICODE

      // We no longer need the buffer

      ::NetApiBufferFree( buffer_p );

      CNetworkUsers user_to_add( primary_domain_controller );

      user_to_add.SetPrivilege( SE_MACHINE_ACCOUNT_NAME, TRUE );
      
      if ( user_to_add.Add( information ) == FALSE )
      {
         m_ErrorCode = user_to_add.GetErrorCode();
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

BOOL CNetworkUsers::Delete( const CNetworkUserInformation& user_to_delete )
{
   WFCLTRACEINIT( TEXT( "CNetworkUsers::Delete()" ) );

   WCHAR wide_name[ 1024 ];

   ::ZeroMemory( wide_name, sizeof( wide_name ) );

#if ! defined( UNICODE )

   // We need to convert the ASCII strings to UNICODE

   ::ASCII_to_UNICODE( user_to_delete.Name, wide_name );

#else

   // We're already UNICODE

   ::_tcscpy( (LPTSTR) wide_name, user_to_delete.Name );

#endif // UNICODE

   m_ErrorCode = ::NetUserDel( m_WideDoubleBackslashPreceededMachineName, wide_name );

   if ( m_ErrorCode == NERR_Success )
   {
      return( TRUE );
   }

   return( FALSE );
}

BOOL CNetworkUsers::Delete( const CString& user_to_delete )
{
   CNetworkUserInformation user;
   
   user.Name = user_to_delete;

   return( Delete( user ) );
}

BOOL CNetworkUsers::Enumerate( void )
{
   WFCLTRACEINIT( TEXT( "CNetworkUsers::Enumerate()" ) );

   // Search order is 3, 2, 1, 10, 0

   if ( m_3InformationBuffer != NULL )
   {
      WFCTRACE( TEXT( "Freeing Buffer 3" ) );
      ::NetApiBufferFree( m_3InformationBuffer );
      m_3InformationBuffer = NULL;
   }

   m_3CurrentEntryNumber       = 0;
   m_3Index                    = 0;
   m_3NumberOfEntriesRead      = 0;
   m_3ResumeHandle             = 0;
   m_3TotalNumberOfEntries     = 0;

   if ( m_2InformationBuffer != NULL )
   {
      WFCTRACE( TEXT( "Freeing Buffer 2" ) );
      ::NetApiBufferFree( m_2InformationBuffer );
      m_2InformationBuffer = NULL;
   }

   m_2CurrentEntryNumber       = 0;
   m_2Index                    = 0;
   m_2NumberOfEntriesRead      = 0;
   m_2ResumeHandle             = 0;
   m_2TotalNumberOfEntries     = 0;

   if ( m_1InformationBuffer != NULL )
   {
      WFCTRACE( TEXT( "Freeing Buffer 1" ) );
      ::NetApiBufferFree( m_1InformationBuffer );
      m_1InformationBuffer = NULL;
   }

   m_1CurrentEntryNumber       = 0;
   m_1Index                    = 0;
   m_1NumberOfEntriesRead      = 0;
   m_1ResumeHandle             = 0;
   m_1TotalNumberOfEntries     = 0;

   if ( m_10InformationBuffer != NULL )
   {
      WFCTRACE( TEXT( "Freeing Buffer 10" ) );
      ::NetApiBufferFree( m_10InformationBuffer );
      m_10InformationBuffer = NULL;
   }

   m_10CurrentEntryNumber       = 0;
   m_10Index                    = 0;
   m_10NumberOfEntriesRead      = 0;
   m_10ResumeHandle             = 0;
   m_10TotalNumberOfEntries     = 0;

   if ( m_0InformationBuffer != NULL )
   {
      WFCTRACE( TEXT( "Freeing Buffer 0" ) );
      ::NetApiBufferFree( m_0InformationBuffer );
      m_0InformationBuffer = NULL;
   }

   m_0CurrentEntryNumber       = 0;
   m_0Index                    = 0;
   m_0NumberOfEntriesRead      = 0;
   m_0ResumeHandle             = 0;
   m_0TotalNumberOfEntries     = 0;

   return( m_GetChunk() );
}

DWORD CNetworkUsers::GetLevel( void ) const
{
   if ( m_3InformationBuffer != NULL )
   {
      return( 3 );
   }

   if ( m_2InformationBuffer != NULL )
   {
      return( 2 );
   }

   if ( m_1InformationBuffer != NULL )
   {
      return( 1 );
   }

   if ( m_10InformationBuffer != NULL )
   {
      return( 10 );
   }

   if ( m_0InformationBuffer != NULL )
   {
      return( 0 );
   }

   return( 0xFFFFFFFF );
}

BOOL CNetworkUsers::GetNext( CNetworkUserInformation& information )
{
   WFCLTRACEINIT( TEXT( "CNetworkUsers::GetNext()" ) );

   // Rapoport Sergey [radio-city@utn.e-burg.ru]

   // We need to see which buffer we're working with...

   if ( m_3InformationBuffer != NULL )
   {
      if ( m_3Index < m_3NumberOfEntriesRead )
      {
         WFCTRACEVAL( TEXT( "Copying index " ), m_3Index );
         WFCTRACEVAL( TEXT( "Number of entries read is " ), m_3NumberOfEntriesRead );

         information.Copy( &m_3InformationBuffer[ m_3Index ] );
         m_3Index++;

         return( TRUE );
      }
      else
      {
         // We need another chunk

         if ( m_GetChunk() != FALSE )
         {
            return( GetNext( information ) );
         }
         else
         {
            return( FALSE );
         }
      }
   }
   else if ( m_2InformationBuffer != NULL )
   {
      if ( m_2Index < m_2NumberOfEntriesRead )
      {
         information.Copy( &m_2InformationBuffer[ m_2Index ] );
         m_2Index++;
         return( TRUE );
      }
      else
      {
         // We need another chunk

         if ( m_GetChunk() != FALSE )
         {
            return( GetNext( information ) );
         }
         else
         {
            return( FALSE );
         }
      }
   }
   else if ( m_1InformationBuffer != NULL )
   {
      if ( m_1Index < m_1NumberOfEntriesRead )
      {
         information.Copy( &m_1InformationBuffer[ m_1Index ] );
         m_1Index++;
         return( TRUE );
      }
      else
      {
         // We need another chunk

         if ( m_GetChunk() != FALSE )
         {
            return( GetNext( information ) );
         }
         else
         {
            return( FALSE );
         }
      }
   }
   else if ( m_10InformationBuffer != NULL )
   {
      if ( m_10Index < m_10NumberOfEntriesRead )
      {
         information.Copy( &m_10InformationBuffer[ m_10Index ] );
         m_10Index++;
         return( TRUE );
      }
      else
      {
         // We need another chunk

         if ( m_GetChunk() != FALSE )
         {
            return( GetNext( information ) );
         }
         else
         {
            return( FALSE );
         }
      }
   }
   else if ( m_0InformationBuffer != NULL )
   {
      if ( m_0Index < m_0NumberOfEntriesRead )
      {
         information.Copy( &m_0InformationBuffer[ m_0Index ] );
         m_0Index++;
         return( TRUE );
      }
      else
      {
         // We need another chunk

         if ( m_GetChunk() != FALSE )
         {
            return( GetNext( information ) );
         }
         else
         {
            return( FALSE );
         }
      }
   }

   information.Empty();
   return( FALSE );
}

BOOL CNetworkUsers::m_GetChunk( void )
{
   WFCLTRACEINIT( TEXT( "CNetworkUsers::m_GetChunk()" ) );

   // Try to get the most information as possible. Start off by asking for
   // data that requires lots of security access privileges

   WFCTRACE( TEXT( "Getting Level 3 information" ) );

   m_3Index = 0;

   WFCTRACEVAL( TEXT( "Before NetUserEnum() m_3ResumeHandle is " ), m_3ResumeHandle );

   // Let's see if we have already been reading

   if ( m_3NumberOfEntriesRead != 0 && m_3ResumeHandle == NULL )
   {
      // Yup, we've finished reading
      WFCTRACE( TEXT( "Freeing Buffer 3" ) );
      ::NetApiBufferFree( m_3InformationBuffer );
      m_3InformationBuffer        = NULL;
      m_3CurrentEntryNumber       = 0;
      m_3NumberOfEntriesRead      = 0;
      m_3ResumeHandle             = 0;
      m_3TotalNumberOfEntries     = 0;
      return( FALSE );
   }

   m_ErrorCode = ::NetUserEnum(           m_WideDoubleBackslashPreceededMachineName,
                                          3,
                                          0,
                              (LPBYTE *) &m_3InformationBuffer,
                                          64 * 1024,
                                         &m_3NumberOfEntriesRead,
                                         &m_3TotalNumberOfEntries,
                                         &m_3ResumeHandle );

   if ( m_ErrorCode == NERR_Success || m_ErrorCode == ERROR_MORE_DATA )
   {
      WFCTRACEVAL( TEXT( "m_3NumberOfEntriesRead  is " ), m_3NumberOfEntriesRead  );
      WFCTRACEVAL( TEXT( "m_3TotalNumberOfEntries is " ), m_3TotalNumberOfEntries );

      // Thanks go to Dirk Tolson (dirk.tolson@srs.gov) for finding a bug
      // here. When there were more accounts than could be read in one read,
      // I would go into an endless loop. DOH!

      if ( m_ErrorCode == NERR_Success )
      {
         WFCTRACE( TEXT( "m_3ResumeHandle is set to NULL" ) );
         m_3ResumeHandle = 0;
      }

      WFCTRACE( TEXT( "Returning TRUE" ) );
      return( TRUE );
   }
    
   if ( m_3InformationBuffer == NULL )
   {
      WFCTRACE( TEXT( "well, that's funny. m_3InformationBuffer is NULL!\n" ) );
   }

   // Make really sure the OS didn't modify our variables...

   if ( m_3InformationBuffer != NULL )
   {
      WFCTRACE( TEXT( "Freeing Buffer 3" ) );
      ::NetApiBufferFree( m_3InformationBuffer );
      m_3InformationBuffer = NULL;
   }

   m_3CurrentEntryNumber   = 0;
   m_3NumberOfEntriesRead  = 0;
   m_3ResumeHandle         = 0;
   m_3TotalNumberOfEntries = 0;

   if ( m_ErrorCode != ERROR_ACCESS_DENIED )
   {
      return( FALSE );
   }

   WFCTRACE( TEXT( "Failed, trying at Level 2 information" ) );

   m_2Index = 0;

   // Let's see if we have already been reading

   if ( m_2NumberOfEntriesRead != 0 && m_2ResumeHandle == NULL )
   {
      // Yup, we've finished reading
      WFCTRACE( TEXT( "Freeing Buffer 2" ) );
      ::NetApiBufferFree( m_2InformationBuffer );
      m_2InformationBuffer        = NULL;
      m_2CurrentEntryNumber       = 0;
      m_2NumberOfEntriesRead      = 0;
      m_2ResumeHandle             = 0;
      m_2TotalNumberOfEntries     = 0;
      return( FALSE );
   }

   m_ErrorCode = ::NetUserEnum(           m_WideDoubleBackslashPreceededMachineName,
                                          2,
                                          0,
                              (LPBYTE *) &m_2InformationBuffer,
                                          65535,
                                         &m_2NumberOfEntriesRead,
                                         &m_2TotalNumberOfEntries,
                                         &m_2ResumeHandle );

   if ( m_ErrorCode == NERR_Success && m_2InformationBuffer != NULL )
   {
      WFCTRACEVAL( TEXT( "m_2NumberOfEntriesRead  is " ), m_2NumberOfEntriesRead  );
      WFCTRACEVAL( TEXT( "m_2TotalNumberOfEntries is " ), m_2TotalNumberOfEntries );

      // Thanks go to Dirk Tolson (dirk.tolson@srs.gov) for finding a bug
      // here. When there were more accounts than could be read in one read,
      // I would go into an endless loop. DOH!

      if ( m_ErrorCode == NERR_Success )
      {
         WFCTRACE( TEXT( "m_2ResumeHandle is set to NULL" ) );
         m_2ResumeHandle = 0;
      }

      WFCTRACE( TEXT( "Returning TRUE" ) );
      return( TRUE );
   }

   // Make really sure the OS didn't modify our variables...

   if ( m_2InformationBuffer != NULL )
   {
      WFCTRACE( TEXT( "Freeing Buffer 2" ) );
      ::NetApiBufferFree( m_2InformationBuffer );
      m_2InformationBuffer = NULL;
   }

   m_2CurrentEntryNumber   = 0;
   m_2NumberOfEntriesRead  = 0;
   m_2ResumeHandle         = 0;
   m_2TotalNumberOfEntries = 0;

   if ( m_ErrorCode != ERROR_ACCESS_DENIED )
   {
      return( FALSE );
   }

   WFCTRACE( TEXT( "Access is denied, trying at Level 1" ) );

   m_1Index = 0;

   // Let's see if we have already been reading

   if ( m_1NumberOfEntriesRead != 0 && m_1ResumeHandle == NULL )
   {
      // Yup, we've finished reading
      WFCTRACE( TEXT( "Freeing Buffer 1" ) );
      ::NetApiBufferFree( m_1InformationBuffer );
      m_1InformationBuffer        = NULL;
      m_1CurrentEntryNumber       = 0;
      m_1NumberOfEntriesRead      = 0;
      m_1ResumeHandle             = 0;
      m_1TotalNumberOfEntries     = 0;
      return( FALSE );
   }

   m_ErrorCode = ::NetUserEnum(           m_WideDoubleBackslashPreceededMachineName,
                                          1, 
                                          0,
                              (LPBYTE *) &m_1InformationBuffer,
                                          65535,
                                         &m_1NumberOfEntriesRead,
                                         &m_1TotalNumberOfEntries,
                                         &m_1ResumeHandle );

   if ( m_ErrorCode == NERR_Success && m_1InformationBuffer != NULL )
   {
      WFCTRACE( TEXT( "Got Level 1 information" ) );
      WFCTRACEVAL( TEXT( "m_1NumberOfEntriesRead  is " ), m_1NumberOfEntriesRead  );
      WFCTRACEVAL( TEXT( "m_1TotalNumberOfEntries is " ), m_1TotalNumberOfEntries );

      // Thanks go to Dirk Tolson (dirk.tolson@srs.gov) for finding a bug
      // here. When there were more accounts than could be read in one read,
      // I would go into an endless loop. DOH!

      if ( m_ErrorCode == NERR_Success )
      {
         WFCTRACE( TEXT( "m_1ResumeHandle is set to NULL" ) );
         m_1ResumeHandle = 0;
      }

      WFCTRACE( TEXT( "Returning TRUE" ) );
      return( TRUE );
   }

   // Make really sure the OS didn't modify our variables...

   if ( m_1InformationBuffer != NULL )
   {
      WFCTRACE( TEXT( "Freeing Buffer 1" ) );
      ::NetApiBufferFree( m_1InformationBuffer );
      m_1InformationBuffer = NULL;
   }

   m_1CurrentEntryNumber   = 0;
   m_1NumberOfEntriesRead  = 0;
   m_1ResumeHandle         = 0;
   m_1TotalNumberOfEntries = 0;

   if ( m_ErrorCode != ERROR_ACCESS_DENIED )
   {
      return( FALSE );
   }

   // Go after level 10 data
   WFCTRACE( TEXT( "Access is denied, trying at Level 10" ) );

   m_10Index = 0;

   // Let's see if we have already been reading

   if ( m_10NumberOfEntriesRead != 0 && m_10ResumeHandle == NULL )
   {
      // Yup, we've finished reading
      WFCTRACE( TEXT( "Freeing Buffer 10" ) );
      ::NetApiBufferFree( m_10InformationBuffer );
      m_10InformationBuffer        = NULL;
      m_10CurrentEntryNumber       = 0;
      m_10NumberOfEntriesRead      = 0;
      m_10ResumeHandle             = 0;
      m_10TotalNumberOfEntries     = 0;
      return( FALSE );
   }

   m_ErrorCode = ::NetUserEnum(          m_WideDoubleBackslashPreceededMachineName,
                                         10, 
                                         0,
                             (LPBYTE *) &m_10InformationBuffer,
                                         65535,
                                        &m_10NumberOfEntriesRead,
                                        &m_10TotalNumberOfEntries,
                                        &m_10ResumeHandle );

   if ( m_ErrorCode == NERR_Success && m_10InformationBuffer != NULL )
   {
      WFCTRACE( TEXT( "Got Level 10 information" ) );
      WFCTRACEVAL( TEXT( "m_10NumberOfEntriesRead  is " ), m_10NumberOfEntriesRead  );
      WFCTRACEVAL( TEXT( "m_10TotalNumberOfEntries is " ), m_10TotalNumberOfEntries );

      // Thanks go to Dirk Tolson (dirk.tolson@srs.gov) for finding a bug
      // here. When there were more accounts than could be read in one read,
      // I would go into an endless loop. DOH!

      if ( m_ErrorCode == NERR_Success )
      {
         WFCTRACE( TEXT( "m_10ResumeHandle is set to NULL" ) );
         m_10ResumeHandle = 0;
      }

      WFCTRACE( TEXT( "Returning TRUE" ) );
      return( TRUE );
   }

   // Make really sure the OS didn't modify our variables...

   if ( m_10InformationBuffer != NULL )
   {
      WFCTRACE( TEXT( "Freeing Buffer 10" ) );
     ::NetApiBufferFree( m_10InformationBuffer );
      m_10InformationBuffer = NULL;
   }

   m_10CurrentEntryNumber   = 0;
   m_10NumberOfEntriesRead  = 0;
   m_10ResumeHandle         = 0;
   m_10TotalNumberOfEntries = 0;

   if ( m_ErrorCode != ERROR_ACCESS_DENIED )
   {
      return( FALSE );
   }

   // Go after level 0 data
   WFCTRACE( TEXT( "Access is denied, trying at Level 0" ) );

   m_0Index = 0;

   // Let's see if we have already been reading

   if ( m_0NumberOfEntriesRead != 0 && m_0ResumeHandle == NULL )
   {
      // Yup, we've finished reading
      WFCTRACE( TEXT( "Freeing Buffer 0" ) );
      ::NetApiBufferFree( m_0InformationBuffer );
      m_0InformationBuffer        = NULL;
      m_0CurrentEntryNumber       = 0;
      m_0NumberOfEntriesRead      = 0;
      m_0ResumeHandle             = 0;
      m_0TotalNumberOfEntries     = 0;
      return( FALSE );
   }

   m_ErrorCode = ::NetUserEnum(          m_WideDoubleBackslashPreceededMachineName,
                                         0,
                                         0,
                             (LPBYTE *) &m_0InformationBuffer,
                                         65535,
                                        &m_0NumberOfEntriesRead,
                                        &m_0TotalNumberOfEntries,
                                        &m_0ResumeHandle );

   if ( m_ErrorCode == NERR_Success && m_0InformationBuffer != NULL )
   {
      WFCTRACE( TEXT( "Got Level 0 information" ) );
      WFCTRACEVAL( TEXT( "m_0NumberOfEntriesRead  is " ), m_0NumberOfEntriesRead  );
      WFCTRACEVAL( TEXT( "m_0TotalNumberOfEntries is " ), m_0TotalNumberOfEntries );

      // Thanks go to Dirk Tolson (dirk.tolson@srs.gov) for finding a bug
      // here. When there were more accounts than could be read in one read,
      // I would go into an endless loop. DOH!

      if ( m_ErrorCode == NERR_Success )
      {
         WFCTRACE( TEXT( "m_0ResumeHandle is set to NULL" ) );
         m_0ResumeHandle = 0;
      }

      WFCTRACE( TEXT( "Returning TRUE" ) );
      return( TRUE );
   }

   // Make really sure the OS didn't modify our variables...

   if ( m_0InformationBuffer != NULL )
   {
      WFCTRACE( TEXT( "Freeing Buffer 0" ) );
      ::NetApiBufferFree( m_0InformationBuffer );
      m_0InformationBuffer = NULL;
   }

   m_0CurrentEntryNumber   = 0;
   m_0NumberOfEntriesRead  = 0;
   m_0ResumeHandle         = 0;
   m_0TotalNumberOfEntries = 0;

   WFCTRACE( TEXT( "Can't get anything" ) );

   return( FALSE );
}

void CNetworkUsers::m_Initialize( void )
{
   WFCLTRACEINIT( TEXT( "CNetworkUsers::m_Initialize()" ) );
   m_ErrorCode             = 0;

   m_3InformationBuffer    = NULL;
   m_3ResumeHandle         = 0;
   m_3CurrentEntryNumber   = 0;
   m_3NumberOfEntriesRead  = 0;
   m_3TotalNumberOfEntries = 0;

   m_2InformationBuffer    = NULL;
   m_2ResumeHandle         = 0;
   m_2CurrentEntryNumber   = 0;
   m_2NumberOfEntriesRead  = 0;
   m_2TotalNumberOfEntries = 0;

   m_1InformationBuffer    = NULL;
   m_1ResumeHandle         = 0;
   m_1CurrentEntryNumber   = 0;
   m_1NumberOfEntriesRead  = 0;
   m_1TotalNumberOfEntries = 0;

   m_10InformationBuffer    = NULL;
   m_10ResumeHandle         = 0;
   m_10CurrentEntryNumber   = 0;
   m_10NumberOfEntriesRead  = 0;
   m_10TotalNumberOfEntries = 0;

   m_0InformationBuffer    = NULL;
   m_0ResumeHandle         = 0;
   m_0CurrentEntryNumber   = 0;
   m_0NumberOfEntriesRead  = 0;
   m_0TotalNumberOfEntries = 0;
}

// End of source

#if 0
<HTML>

<HEAD>
<TITLE>WFC - CNetworkUsers</TITLE>
<META name="keywords" content="WFC, MFC extension library, freeware class library, Win32, source code">
<META name="description" content="The C++ class that handles network users. You can use this class to add or delete user accounts.">
</HEAD>

<BODY>

<H1>CNetworkUsers : <A HREF="CNetwork.htm">CNetwork</A></H1>
$Revision: 24 $<BR>
<HR>

<H2>Description</H2>
This class allows you to add, delete or enumerate user accounts in Win32.
It will also create computer accounts.

<H2>Constructors</H2>

<DL COMPACT>

<DT><PRE><B>CNetworkUsers</B>()
<B>CNetworkUsers</B>( LPCTSTR machine_name )</PRE><DD>
Creates the object and let's you specify which machine to 
execute on (i.e. which machine's accounts you want to play with).

</DL>

<H2>Methods</H2>

<DL COMPACT>

<DT><PRE>BOOL <B>Add</B>( const CNetworkUserInformation&amp; user_to_add )</PRE><DD>
Creates a new user account with the options you specify.
The return value will be TRUE if the account was created, FALSE otherwise.

<DT><PRE>void <B>Close</B>( void )</PRE><DD>
Closes the connection with the machine and cleans up any
internal buffers used.

<DT><PRE>BOOL <B>CreateComputerAccount</B>( LPCTSTR computer_name = NULL, DWORD type = accountMachine )</PRE><DD>
Creates a computer account. If <CODE>computer_name</CODE> is NULL, the name
of the computer where this function executes will be used. <CODE>type</CODE>
can be one of the following:

<UL>
<LI>accountBackupDomainController
<LI>accountInterdomain
<LI>accountMachine
</UL>

The return value will be TRUE if the account was created, FALSE otherwise.
<B>CreateComputerAccount</B>() uses the method described in the Microsoft
Knowledge Base article
<A HREF="http://www.microsoft.com/kb/articles/q136/8/67.htm">Q136867</A>
to create the account.

<DT><PRE>BOOL <B>Delete</B>( const CNetworkUserInformation&amp; user_to_delete )
BOOL <B>Delete</B>( const CString&amp; user_to_delete )</PRE><DD>
Deletes a user's account.
The return value will be TRUE if the account was deleted, FALSE otherwise.

<DT><PRE>BOOL <B>Enumerate</B>( void )</PRE><DD>
Initializes the object for enumeration.

<DT><PRE>DWORD <B>GetLevel</B>( void ) const</PRE><DD>
When <B>Enumerate</B>() has successfully been called, this
method will return the level of information it is returning.
If it returns 0xFFFFFFFF, then it has failed. The return
value maps to the <CODE>USER_INFO_xxx</CODE> data structures.
For example, if <B>GetLevel</B>() returns 3, it means it is retrieving
<CODE>USER_INFO_3</CODE> data structures from the server.

<DT><PRE>BOOL <B>GetNext</B>( CNetworkUserInformation&amp; information )</PRE><DD>
Retrieves the next CNetworkUserInformation.
When you reach the end of the list, <B>GetNext</B>() will return FALSE.

</DL>

<H2>Example</H2>
<PRE><CODE>#include &lt;wfc.h&gt;
#pragma hdrstop

void test_CNetworkUsers( LPCTSTR machine_name )
{
   <A HREF="WfcTrace.htm">WFCLTRACEINIT</A>( TEXT( &quot;test_CNetworkUsers()&quot; ) );

   <B>CNetworkUsers</B> users( machine_name );

   CNetworkUserInformation user_information;

   if ( users.Enumerate() != FALSE )
   {
      _tprintf( TEXT( &quot;User Information for %s:\n&quot; ), (LPCTSTR) users.GetMachineName() );

      while( users.GetNext( user_information ) != FALSE )
      {
         _tprintf( TEXT( &quot; Name                 - \&quot;%s\&quot;\n&quot; ), (LPCTSTR) user_information.Name          );
         _tprintf( TEXT( &quot; Full Name            - \&quot;%s\&quot;\n&quot; ), (LPCTSTR) user_information.FullName      );
         _tprintf( TEXT( &quot; Comment              - \&quot;%s\&quot;\n&quot; ), (LPCTSTR) user_information.Comment       );
         _tprintf( TEXT( &quot; User Comment         - \&quot;%s\&quot;\n&quot; ), (LPCTSTR) user_information.UserComment   );
         _tprintf( TEXT( &quot; ID                   - %lu\n&quot; ),              user_information.UserID        );
         _tprintf( TEXT( &quot; Flags                - %lX\n&quot; ),              user_information.Flags         );
         _tprintf( TEXT( &quot; Privileges           - %lX\n&quot; ),              user_information.Privileges    );
         _tprintf( TEXT( &quot; Password             - \&quot;%s\&quot;\n&quot; ), (LPCTSTR) user_information.Password      );
         _tprintf( TEXT( &quot; Password Age         - %d Days %d Hours %d Minutes %d seconds\n&quot; ),
                   user_information.PasswordAge.GetDays(),
                   user_information.PasswordAge.GetHours(),
                   user_information.PasswordAge.GetMinutes(),
                   user_information.PasswordAge.GetSeconds() );
         _tprintf( TEXT( &quot; HomeDirectory        - \&quot;%s\&quot;\n&quot; ), (LPCTSTR) user_information.HomeDirectory );
         _tprintf( TEXT( &quot; Script Path          - \&quot;%s\&quot;\n&quot; ), (LPCTSTR) user_information.ScriptPath    );
         _tprintf( TEXT( &quot; Parameters           - \&quot;%s\&quot;\n&quot; ), (LPCTSTR) user_information.Parameters    );
         _tprintf( TEXT( &quot; Workstations         - \&quot;%s\&quot;\n&quot; ), (LPCTSTR) user_information.Workstations  );
         _tprintf( TEXT( &quot; LastLogon            - \&quot;%s\&quot;\n&quot; ), (LPCTSTR) user_information.LastLogon.Format( &quot;%a %d %b %y, %H:%M:%S&quot; ) );
         _tprintf( TEXT( &quot; LastLogoff           - \&quot;%s\&quot;\n&quot; ), (LPCTSTR) user_information.LastLogoff.Format( &quot;%a %d %b %y, %H:%M:%S&quot; ) );
         _tprintf( TEXT( &quot; Account Expires      - \&quot;%s\&quot;\n&quot; ), (LPCTSTR) user_information.AccountExpires.Format( &quot;%a %d %b %y, %H:%M:%S&quot; ) );
         _tprintf( TEXT( &quot; Maximum Storage      - %lu\n&quot; ),              user_information.MaximumStorage     );
         _tprintf( TEXT( &quot; Bad Password Count   - %lu\n&quot; ),              user_information.BadPasswordCount   );
         _tprintf( TEXT( &quot; Number Of Logons     - %lu\n&quot; ),              user_information.NumberOfLogons     );
         _tprintf( TEXT( &quot; Logon Server         - \&quot;%s\&quot;\n&quot; ), (LPCTSTR) user_information.LogonServer        );
         _tprintf( TEXT( &quot; Country Code         - %lX\n&quot; ),              user_information.CountryCode        );
         _tprintf( TEXT( &quot; Code Page            - %lX\n&quot; ),              user_information.CodePage           );
         _tprintf( TEXT( &quot; Primary Group ID     - %lu\n&quot; ),              user_information.PrimaryGroupID     );
         _tprintf( TEXT( &quot; Home Directory Drive - \&quot;%s\&quot;\n&quot; ), (LPCTSTR) user_information.HomeDirectoryDrive );
         _tprintf( TEXT( &quot; Profile              - \&quot;%s\&quot;\n&quot; ), (LPCTSTR) user_information.Profile            );
         _tprintf( TEXT( &quot; Password Has Expired - %lu\n&quot; ),              user_information.PasswordHasExpired );
         _tprintf( TEXT( &quot; Encrypted Password: &quot; ) );

         int index = 0;

         while( index &lt; user_information.EncryptedPassword.GetSize() )
         {
            _tprintf( TEXT( &quot;%02X&quot; ), (int) user_information.EncryptedPassword.GetAt( index ) );
            index++;
         }

         _tprintf( TEXT( &quot;\n\n&quot; ) );
      }
   }
   else
   {
      DWORD error_code = users.GetErrorCode();

      CString error_message;

      Convert_NERR_Code_to_String( error_code, error_message );

      _tprintf( TEXT( &quot;CNetworkUsers.Enumerate( user_information ), ErrorCode == %d \&quot;%s\&quot;\n&quot; ), error_code, (LPCTSTR) error_message );
   }

   user_information.Empty();

   user_information.Name     = TEXT( &quot;Laura&quot; );
   user_information.Password = TEXT( &quot;LovesSammy&quot; );

   user_information.SetAddDefaults();

   if ( users.Add( user_information ) != FALSE )
   {
      _tprintf( TEXT( &quot;Laura Added.\n&quot; ) );
   }
   else
   {
      _tprintf( TEXT( &quot;Can't Add User\n&quot; ) );
   }

   if ( users.Delete( &quot;Laura&quot; ) != FALSE )
   {
      _tprintf( TEXT( &quot;Deleted Laura\n&quot; ) );
   }
   else
   {
      _tprintf( TEXT( &quot;Can't delete Laura\n&quot; ) );
   }
}</CODE></PRE>

<H2>API's Used</H2>

<B>CNetworkUsers</B> uses the following API's:

<UL>
<LI>NetApiBufferFree
<LI>NetGetDCName
<LI>NetUserAdd
<LI>NetUserDel
<LI>NetUserEnum
</UL>

<HR><I>Copyright, 2000, <A HREF="mailto:wfc@pobox.com">Samuel R. Blackburn</A></I><BR>
$Workfile: CNetworkUser.cpp $<BR>
$Modtime: 1/04/00 5:18a $
</BODY>

</HTML>
</WFC_DOCUMENTATION>
#endif
