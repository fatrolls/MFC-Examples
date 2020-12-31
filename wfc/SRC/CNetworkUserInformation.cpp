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
** $Workfile: CNetworkUserInformation.cpp $
** $Revision: 6 $
** $Modtime: 1/04/00 5:18a $
** $Reuse Tracing Code: 1 $
*/

#if defined( _DEBUG ) && ! defined( WFC_STL )
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

#if ! defined(  WFC_NO_SERIALIZATION )
IMPLEMENT_SERIAL( CNetworkUserInformation, CObject, 1 )
#endif // WFC_NO_SERIALIZATION

#if defined( _DEBUG ) && ! defined( WFC_STL )
#define new DEBUG_NEW
#endif // _DEBUG

CNetworkUserInformation::CNetworkUserInformation()
{
   WFCLTRACEINIT( TEXT( "CNetworkUserInformation::CNetworkUserInformation()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   m_Initialize();
}

CNetworkUserInformation::CNetworkUserInformation( const USER_INFO_0 *source )
{
   WFCLTRACEINIT( TEXT( "CNetworkUserInformation::CNetworkUserInformation( USER_INFO_0 )" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   Copy( source );
}

CNetworkUserInformation::CNetworkUserInformation( const USER_INFO_1 *source )
{
   WFCLTRACEINIT( TEXT( "CNetworkUserInformation::CNetworkUserInformation( USER_INFO_1 )" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   Copy( source );
}

CNetworkUserInformation::CNetworkUserInformation( const USER_INFO_2 *source )
{
   WFCLTRACEINIT( TEXT( "CNetworkUserInformation::CNetworkUserInformation( USER_INFO_2 )" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   Copy( source );
}

CNetworkUserInformation::CNetworkUserInformation( const USER_INFO_3 *source )
{
   WFCLTRACEINIT( TEXT( "CNetworkUserInformation::CNetworkUserInformation( USER_INFO_3 )" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   Copy( source );
}

CNetworkUserInformation::CNetworkUserInformation( const USER_INFO_10 *source )
{
   WFCLTRACEINIT( TEXT( "CNetworkUserInformation::CNetworkUserInformation( USER_INFO_10 )" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   Copy( source );
}

CNetworkUserInformation::CNetworkUserInformation( const USER_INFO_11 *source )
{
   WFCLTRACEINIT( TEXT( "CNetworkUserInformation::CNetworkUserInformation( USER_INFO_11 )" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   Copy( source );
}

CNetworkUserInformation::CNetworkUserInformation( const USER_INFO_20 *source )
{
   WFCLTRACEINIT( TEXT( "CNetworkUserInformation::CNetworkUserInformation( USE_INFO_20 )" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   Copy( source );
}

CNetworkUserInformation::CNetworkUserInformation( const USER_INFO_21 *source )
{
   WFCLTRACEINIT( TEXT( "CNetworkUserInformation::CNetworkUserInformation( USER_INFO_21 )" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   Copy( source );
}

CNetworkUserInformation::CNetworkUserInformation( const USER_INFO_22 *source )
{
   WFCLTRACEINIT( TEXT( "CNetworkUserInformation::CNetworkUserInformation( USER_INFO_22 )" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   Copy( source );
}

CNetworkUserInformation::CNetworkUserInformation( const CNetworkUserInformation *source )
{
   WFCLTRACEINIT( TEXT( "CNetworkUserInformation::CNetworkUserInformation( CNetworkUserInformation * )" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   Copy( source );
}

CNetworkUserInformation::CNetworkUserInformation( const CNetworkUserInformation& source )
{
   WFCLTRACEINIT( TEXT( "CNetworkUserInformation::CNetworkUserInformation( CNetworkUserInformation& )" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   Copy( source );
}

CNetworkUserInformation::~CNetworkUserInformation()
{
   WFCLTRACEINIT( TEXT( "CNetworkUserInformation::~CNetworkUserInformation()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   m_Initialize();
}

void CNetworkUserInformation::Copy( const USER_INFO_0 *source )
{
   WFCLTRACEINIT( TEXT( "CNetworkUserInformation::Copy( USER_INFO_0 * )" ) );
   ASSERT( source != NULL );

   m_Initialize();

   if ( source == NULL )
   {
      return;
   }

   // We were passed a pointer, don't trust it

   try
   {
      ASSERT( source->usri0_name != NULL );

      if ( source->usri0_name == NULL )
      {
         return;
      }

      ::wfc_convert_lpcwstr_to_cstring( source->usri0_name, Name );
   }
   catch( ... )
   {
      Empty();
   }
}

void CNetworkUserInformation::Copy( const USER_INFO_1 *source )
{
   WFCLTRACEINIT( TEXT( "CNetworkUserInformation::Copy( USER_INFO_1 * )" ) );
   ASSERT( source != NULL );

   m_Initialize();

   if ( source == NULL )
   {
      return;
   }

   // We were passed a pointer, don't trust it

   try
   {
      ::wfc_convert_lpcwstr_to_cstring( source->usri1_comment,     Comment );
      ::wfc_convert_lpcwstr_to_cstring( source->usri1_home_dir,    HomeDirectory );
      ::wfc_convert_lpcwstr_to_cstring( source->usri1_name,        Name );
      ::wfc_convert_lpcwstr_to_cstring( source->usri1_password,    Password );
      ::wfc_convert_lpcwstr_to_cstring( source->usri1_script_path, ScriptPath );

      Flags       = source->usri1_flags;
      PasswordAge = CTimeSpan( source->usri1_password_age );
      Privileges  = source->usri1_priv;
   }
   catch( ... )
   {
      m_Initialize();
   }
}

void CNetworkUserInformation::Copy( const USER_INFO_2 *source )
{
   WFCLTRACEINIT( TEXT( "CNetworkUserInformation::Copy( USER_INFO_2 * )" ) );
   ASSERT( source != NULL );

   m_Initialize();

   if ( source == NULL )
   {
      return;
   }

   // We were passed a pointer, don't trust it

   try
   {
      ::wfc_convert_lpcwstr_to_cstring( source->usri2_comment,      Comment       );
      ::wfc_convert_lpcwstr_to_cstring( source->usri2_full_name,    FullName      );
      ::wfc_convert_lpcwstr_to_cstring( source->usri2_home_dir,     HomeDirectory );
      ::wfc_convert_lpcwstr_to_cstring( source->usri2_logon_server, LogonServer );
      ::wfc_convert_lpcwstr_to_cstring( source->usri2_name,         Name          );
      ::wfc_convert_lpcwstr_to_cstring( source->usri2_parms,        Parameters    );
      ::wfc_convert_lpcwstr_to_cstring( source->usri2_password,     Password      );
      ::wfc_convert_lpcwstr_to_cstring( source->usri2_script_path,  ScriptPath    );
      ::wfc_convert_lpcwstr_to_cstring( source->usri2_usr_comment,  UserComment   );
      ::wfc_convert_lpcwstr_to_cstring( source->usri2_workstations, Workstations  );
 
      AccountExpires      = CTime( (time_t) source->usri2_acct_expires );
      AuthenticationFlags = source->usri2_auth_flags;
      BadPasswordCount    = source->usri2_bad_pw_count;
      CodePage            = source->usri2_code_page;
      CountryCode         = source->usri2_country_code;
      Flags               = source->usri2_flags;
      LastLogoff          = CTime( (time_t) source->usri2_last_logoff );
      LastLogon           = CTime( (time_t) source->usri2_last_logon );
      MaximumStorage      = source->usri2_max_storage;
      NumberOfLogons      = source->usri2_num_logons;
      PasswordAge         = CTimeSpan( source->usri2_password_age );
      Privileges          = source->usri2_priv;
      UnitsPerWeek        = source->usri2_units_per_week;
   
      int index = 0;

      while( index < 21 )
      {
         LogonHours.Add( source->usri2_logon_hours[ index ] );
         index++;
      }
   }
   catch( ... )
   {
      m_Initialize();
   }
}

void CNetworkUserInformation::Copy( const USER_INFO_3 *source )
{
   WFCLTRACEINIT( TEXT( "CNetworkUserInformation::Copy( USER_INFO_3 * )" ) );
   ASSERT( source != NULL );

   m_Initialize();

   if ( source == NULL )
   {
      return;
   }

   // We were passed a pointer, don't trust it

   try
   {
      ::wfc_convert_lpcwstr_to_cstring( source->usri3_comment, Comment );
      ::wfc_convert_lpcwstr_to_cstring( source->usri3_full_name, FullName );
      ::wfc_convert_lpcwstr_to_cstring( source->usri3_home_dir, HomeDirectory );
      ::wfc_convert_lpcwstr_to_cstring( source->usri3_home_dir_drive, HomeDirectoryDrive );
      ::wfc_convert_lpcwstr_to_cstring( source->usri3_name, Name );
      ::wfc_convert_lpcwstr_to_cstring( source->usri3_logon_server, LogonServer );
      ::wfc_convert_lpcwstr_to_cstring( source->usri3_parms, Parameters );
      ::wfc_convert_lpcwstr_to_cstring( source->usri3_password, Password );
      ::wfc_convert_lpcwstr_to_cstring( source->usri3_profile, Profile );
      ::wfc_convert_lpcwstr_to_cstring( source->usri3_script_path, ScriptPath );
      ::wfc_convert_lpcwstr_to_cstring( source->usri3_usr_comment, UserComment );
      ::wfc_convert_lpcwstr_to_cstring( source->usri3_workstations, Workstations );
   
      AccountExpires      = CTime( (time_t) source->usri3_acct_expires );
      AuthenticationFlags = source->usri3_auth_flags;
      BadPasswordCount    = source->usri3_bad_pw_count;
      CodePage            = source->usri3_code_page;
      CountryCode         = source->usri3_country_code;
      Flags               = source->usri3_flags;
      LastLogoff          = CTime( (time_t) source->usri3_last_logoff );
      LastLogon           = CTime( (time_t) source->usri3_last_logon );
      MaximumStorage      = source->usri3_max_storage;
      NumberOfLogons      = source->usri3_num_logons;
      PasswordAge         = CTimeSpan( source->usri3_password_age );
      PasswordHasExpired  = source->usri3_password_expired;
      PrimaryGroupID      = source->usri3_primary_group_id;
      Privileges          = source->usri3_priv;
      UnitsPerWeek        = source->usri3_units_per_week;
      UserID              = source->usri3_user_id;

      int index = 0;

      while( index < 21 )
      {
         LogonHours.Add( source->usri3_logon_hours[ index ] );
         index++;
      }
   }
   catch( ... )
   {
      m_Initialize();
   }
}

void CNetworkUserInformation::Copy( const USER_INFO_10 *source )
{
   WFCLTRACEINIT( TEXT( "CNetworkUserInformation::Copy( USER_INFO_10 * )" ) );
   ASSERT( source != NULL );

   m_Initialize();

   if ( source == NULL )
   {
      return;
   }

   // We were passed a pointer, don't trust it

   try
   {
      ::wfc_convert_lpcwstr_to_cstring( source->usri10_comment,     Comment     );
      ::wfc_convert_lpcwstr_to_cstring( source->usri10_full_name,   FullName    );
      ::wfc_convert_lpcwstr_to_cstring( source->usri10_name,        Name        );
      ::wfc_convert_lpcwstr_to_cstring( source->usri10_usr_comment, UserComment );
   }
   catch( ... )
   {
      m_Initialize();
   }
}

void CNetworkUserInformation::Copy( const USER_INFO_11 *source )
{
   WFCLTRACEINIT( TEXT( "CNetworkUserInformation::Copy( USER_INFO_11 * )" ) );
   ASSERT( source != NULL );

   m_Initialize();

   if ( source == NULL )
   {
      return;
   }

   // We were passed a pointer, don't trust it

   try
   {
      ::wfc_convert_lpcwstr_to_cstring( source->usri11_comment,      Comment       );
      ::wfc_convert_lpcwstr_to_cstring( source->usri11_full_name,    FullName      );
      ::wfc_convert_lpcwstr_to_cstring( source->usri11_home_dir,     HomeDirectory );
      ::wfc_convert_lpcwstr_to_cstring( source->usri11_logon_server, LogonServer   );
      ::wfc_convert_lpcwstr_to_cstring( source->usri11_name,         Name          );
      ::wfc_convert_lpcwstr_to_cstring( source->usri11_parms,        Parameters    );
      ::wfc_convert_lpcwstr_to_cstring( source->usri11_usr_comment,  UserComment   );
      ::wfc_convert_lpcwstr_to_cstring( source->usri11_workstations, Workstations  );

      AuthenticationFlags = source->usri11_auth_flags;
      BadPasswordCount    = source->usri11_bad_pw_count;
      CodePage            = source->usri11_code_page;
      CountryCode         = source->usri11_country_code;
      PasswordAge         = CTimeSpan( (time_t) source->usri11_password_age );
      Privileges          = source->usri11_priv;
      LastLogon           = CTime( (time_t) source->usri11_last_logon );
      LastLogoff          = CTime( (time_t) source->usri11_last_logoff );
      MaximumStorage      = source->usri11_max_storage;
      NumberOfLogons      = source->usri11_num_logons;
      UnitsPerWeek        = source->usri11_units_per_week;
   
      int index = 0;

      while( index < 21 )
      {
         LogonHours.Add( source->usri11_logon_hours[ index ] );
         index++;
      }
   }
   catch( ... )
   {
      m_Initialize();
   }
}

void CNetworkUserInformation::Copy( const USER_INFO_20 *source )
{
   WFCLTRACEINIT( TEXT( "CNetworkUserInformation::Copy( USER_INFO_20 * )" ) );
   ASSERT( source != NULL );

   m_Initialize();

   if ( source == NULL )
   {
      return;
   }

   // We were passed a pointer, don't trust it

   try
   {
      ::wfc_convert_lpcwstr_to_cstring( source->usri20_comment,   Comment  );
      ::wfc_convert_lpcwstr_to_cstring( source->usri20_full_name, FullName );
      ::wfc_convert_lpcwstr_to_cstring( source->usri20_name,      Name     );

      Flags  = source->usri20_flags;
      UserID = source->usri20_user_id;
   }
   catch( ... )
   {
      m_Initialize();
   }
}

void CNetworkUserInformation::Copy( const USER_INFO_21 *source )
{
   WFCLTRACEINIT( TEXT( "CNetworkUserInformation::Copy( USER_INFO_21 * )" ) );
   ASSERT( source != NULL );

   m_Initialize();

   if ( source == NULL )
   {
      return;
   }

   // We were passed a pointer, don't trust it

   try
   {
      int index = 0;
   
      while( index < ENCRYPTED_PWLEN )
      {
         EncryptedPassword.Add( source->usri21_password[ index ] );
         index++;
      }
   }
   catch( ... )
   {
      m_Initialize();
   }
}

void CNetworkUserInformation::Copy( const USER_INFO_22 *source )
{
   WFCLTRACEINIT( TEXT( "CNetworkUserInformation::Copy( USER_INFO_22 * )" ) );
   ASSERT( source != NULL );

   m_Initialize();

   if ( source == NULL )
   {
      return;
   }

   // We were passed a pointer, don't trust it

   try
   {
      ::wfc_convert_lpcwstr_to_cstring( source->usri22_comment,      Comment       );
      ::wfc_convert_lpcwstr_to_cstring( source->usri22_full_name,    FullName      );
      ::wfc_convert_lpcwstr_to_cstring( source->usri22_home_dir,     HomeDirectory );
      ::wfc_convert_lpcwstr_to_cstring( source->usri22_logon_server, LogonServer   );
      ::wfc_convert_lpcwstr_to_cstring( source->usri22_name,         Name          );
      ::wfc_convert_lpcwstr_to_cstring( source->usri22_parms,        Parameters    );
      ::wfc_convert_lpcwstr_to_cstring( source->usri22_script_path,  ScriptPath    );
      ::wfc_convert_lpcwstr_to_cstring( source->usri22_usr_comment,  UserComment   );
      ::wfc_convert_lpcwstr_to_cstring( source->usri22_workstations, Workstations  );
    
      AccountExpires      = CTime( (time_t) source->usri22_acct_expires );
      AuthenticationFlags = source->usri22_auth_flags;
      BadPasswordCount    = source->usri22_bad_pw_count;
      CodePage            = source->usri22_code_page;
      CountryCode         = source->usri22_country_code;
      Flags               = source->usri22_flags;
      LastLogoff          = CTime( (time_t) source->usri22_last_logoff );
      LastLogon           = CTime( (time_t) source->usri22_last_logon );
      MaximumStorage      = source->usri22_max_storage;
      NumberOfLogons      = source->usri22_num_logons;
      PasswordAge         = CTimeSpan( (time_t) source->usri22_password_age );
      Privileges          = source->usri22_priv;
      UnitsPerWeek        = source->usri22_units_per_week;
   
      int index = 0;
   
      while( index < ENCRYPTED_PWLEN )
      {
         EncryptedPassword.Add( source->usri22_password[ index ] );
         index++;
      }
   
      index = 0;

      while( index < 21 )
      {
         LogonHours.Add( source->usri22_logon_hours[ index ] );
         index++;
      }
   }
   catch( ... )
   {
      m_Initialize();
   }
}

void CNetworkUserInformation::Copy( const CNetworkUserInformation *source )
{
   WFCLTRACEINIT( TEXT( "CNetworkUserInformation::Copy()" ) );
   ASSERT( source != NULL );

   /*
   ** Make sure we ain't copying ourselves
   */

   if ( this == NULL || this == source )
   {
      return;
   }

   // We were passed a pointer, don't trust it

   try
   {
      Copy( *source );
   }
   catch( ... )
   {
      m_Initialize();
   }
}

void CNetworkUserInformation::Copy( const CNetworkUserInformation& source )
{
   WFCLTRACEINIT( TEXT( "CNetworkUserInformation::Copy()" ) );
   ASSERT( this != &source );

   /*
   ** Make sure we ain't copying ourselves
   */

   if ( this == &source )
   {
      return;
   }

   AccountExpires      = source.AccountExpires;
   AuthenticationFlags = source.AuthenticationFlags;
   BadPasswordCount    = source.BadPasswordCount;
   CodePage            = source.CodePage;
   Comment             = source.Comment;
   CountryCode         = source.CountryCode;
   Flags               = source.Flags;
   FullName            = source.FullName;
   HomeDirectory       = source.HomeDirectory;
   LastLogoff          = source.LastLogoff;
   LastLogon           = source.LastLogon;
   LogonServer         = source.LogonServer;
   MaximumStorage      = source.MaximumStorage;
   Name                = source.Name;
   NumberOfLogons      = source.NumberOfLogons;
   Parameters          = source.Parameters;
   Password            = source.Password;
   PasswordHasExpired  = source.PasswordHasExpired;
   PasswordAge         = source.PasswordAge;
   PrimaryGroupID      = source.PrimaryGroupID;
   Privileges          = source.Privileges;
   Profile             = source.Profile;
   ScriptPath          = source.ScriptPath;
   UnitsPerWeek        = source.UnitsPerWeek;
   UserComment         = source.UserComment;
   UserID              = source.UserID;
   Workstations        = source.Workstations;
   HomeDirectoryDrive  = source.HomeDirectoryDrive;

   EncryptedPassword.Copy( source.EncryptedPassword );
   LogonHours.Copy( source.LogonHours );
}

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

void CNetworkUserInformation::Dump( CDumpContext& dump_context ) const
{
   dump_context << TEXT( "a CNetworkUserInformation at " ) << (VOID *) this << TEXT( "\n{\n" );
   dump_context << TEXT( "   AccountExpires is " ) << AccountExpires << TEXT( "\n" );
   dump_context << TEXT( "   AuthenticationFlags is " ) << AuthenticationFlags << TEXT( " (" );

   CString temp_string;

   if ( AuthenticationFlags & AF_OP_PRINT )
   {
      temp_string = TEXT( "AF_OP_PRINT" );
   }

   if ( AuthenticationFlags & AF_OP_COMM )
   {
      if ( temp_string.GetLength() > 0 )
      {
         temp_string += TEXT( " | " );
      }

      temp_string += TEXT( "AF_OP_COMM" );
   }
   
   if ( AuthenticationFlags & AF_OP_SERVER )
   {
      if ( temp_string.GetLength() > 0 )
      {
         temp_string += TEXT( " | " );
      }

      temp_string += TEXT( "AF_OP_SERVER" );
   }
   
   if ( AuthenticationFlags & AF_OP_ACCOUNTS )
   {
      if ( temp_string.GetLength() > 0 )
      {
         temp_string += TEXT( " | " );
      }

      temp_string += TEXT( "AF_OP_ACCOUNTS" );
   }

   dump_context << temp_string << TEXT( " )\n" );
   
   dump_context << TEXT( "   BadPasswordCount is " ) << BadPasswordCount << TEXT( "\n" );
   dump_context << TEXT( "   CodePage is "         ) << CodePage         << TEXT( "\n" );
   dump_context << TEXT( "   Comment is "          ) << Comment          << TEXT( "\n" );
   dump_context << TEXT( "   CountryCode is "      ) << CountryCode      << TEXT( "\n" );
   // EncryptedPassword
   
   dump_context << TEXT( "   Flags is "            ) << Flags            << TEXT( " ( " );

   temp_string.Empty();

   if ( Flags & UF_SCRIPT )
   {
      temp_string = TEXT( "UF_SCRIPT" );
   }

   if ( Flags & UF_ACCOUNTDISABLE )
   {
      if ( temp_string.GetLength() > 0 )
      {
         temp_string += TEXT( " | " );
      }

      temp_string += TEXT( "UF_ACCOUNTDISABLE" );
   }

   if ( Flags & UF_HOMEDIR_REQUIRED )
   {
      if ( temp_string.GetLength() > 0 )
      {
         temp_string += TEXT( " | " );
      }

      temp_string += TEXT( "UF_HOMEDIR_REQUIRED" );
   }

   if ( Flags & UF_PASSWD_NOTREQD )
   {
      if ( temp_string.GetLength() > 0 )
      {
         temp_string += TEXT( " | " );
      }

      temp_string += TEXT( "UF_PASSWD_NOTREQD" );
   }

   if ( Flags & UF_PASSWD_CANT_CHANGE )
   {
      if ( temp_string.GetLength() > 0 )
      {
         temp_string += TEXT( " | " );
      }

      temp_string += TEXT( "UF_PASSWD_CANT_CHANGE" );
   }

   if ( Flags & UF_LOCKOUT )
   {
      if ( temp_string.GetLength() > 0 )
      {
         temp_string += TEXT( " | " );
      }

      temp_string += TEXT( "UF_LOCKOUT" );
   }

   if ( Flags & UF_DONT_EXPIRE_PASSWD )
   {
      if ( temp_string.GetLength() > 0 )
      {
         temp_string += TEXT( " | " );
      }

      temp_string += TEXT( "UF_DONT_EXPIRE_PASSWD" );
   }

   if ( Flags & UF_NORMAL_ACCOUNT )
   {
      if ( temp_string.GetLength() > 0 )
      {
         temp_string += TEXT( " | " );
      }

      temp_string += TEXT( "UF_NORMAL_ACCOUNT" );
   }

   if ( Flags & UF_TEMP_DUPLICATE_ACCOUNT )
   {
      if ( temp_string.GetLength() > 0 )
      {
         temp_string += TEXT( " | " );
      }

      temp_string += TEXT( "UF_TEMP_DUPLICATE_ACCOUNT" );
   }

   if ( Flags & UF_WORKSTATION_TRUST_ACCOUNT )
   {
      if ( temp_string.GetLength() > 0 )
      {
         temp_string += TEXT( " | " );
      }

      temp_string += TEXT( "UF_WORKSTATION_TRUST_ACCOUNT" );
   }

   if ( Flags & UF_SERVER_TRUST_ACCOUNT )
   {
      if ( temp_string.GetLength() > 0 )
      {
         temp_string += TEXT( " | " );
      }

      temp_string += TEXT( "UF_SERVER_TRUST_ACCOUNT" );
   }

   if ( Flags & UF_INTERDOMAIN_TRUST_ACCOUNT )
   {
      if ( temp_string.GetLength() > 0 )
      {
         temp_string += TEXT( " | " );
      }

      temp_string += TEXT( "UF_INTERDOMAIN_TRUST_ACCOUNT" );
   }

   dump_context << temp_string << TEXT( " )\n" );

   dump_context << TEXT( "   FullName is " ) << FullName << TEXT( "\n" );
   dump_context << TEXT( "   HomeDirectory is " ) << HomeDirectory << TEXT( "\n" );
   dump_context << TEXT( "   HomeDirectoryDrive is " ) << HomeDirectoryDrive << TEXT( "\n" );
   dump_context << TEXT( "   LastLogoff is " ) << LastLogoff << TEXT( "\n" );
   dump_context << TEXT( "   LastLogon  is " ) << LastLogon  << TEXT( "\n" );
   //LogonHours.RemoveAll();
   dump_context << TEXT( "   LogonServer is " ) << LogonServer << TEXT( "\n" );
   dump_context << TEXT( "   MaximumStorage is " ) << MaximumStorage << TEXT( "\n" );
   dump_context << TEXT( "   Name is " ) << Name << TEXT( "\n" );
   dump_context << TEXT( "   NumberOfLogons is " ) << NumberOfLogons << TEXT( "\n" );
   dump_context << TEXT( "   Parameters is " ) << Parameters << TEXT( "\n" );
   dump_context << TEXT( "   Password is " ) << Password << TEXT( "\n" );
   dump_context << TEXT( "   PasswordAge is " ) << PasswordAge << TEXT( "\n" );
   dump_context << TEXT( "   PasswordHasExpired is " ) << PasswordHasExpired << TEXT( "\n" );
   dump_context << TEXT( "   PrimaryGroupID is " ) << PrimaryGroupID << TEXT( " ( " );

   temp_string.Empty();

   if ( PrimaryGroupID == DOMAIN_GROUP_RID_USERS )
   {
      temp_string = TEXT( "DOMAIN_GROUP_RID_USERS" );
   }
   else if ( PrimaryGroupID == DOMAIN_GROUP_RID_ADMINS )
   {
      temp_string = TEXT( "DOMAIN_GROUP_RID_ADMINS" );
   }
   else if ( PrimaryGroupID == DOMAIN_GROUP_RID_GUESTS )
   {
      temp_string = TEXT( "DOMAIN_GROUP_RID_GUESTS" );
   }
   else
   {
      temp_string = TEXT( "unknown" );
   }

   dump_context << temp_string << TEXT( " )\n" );

   dump_context << TEXT( "   Privileges is " ) << Privileges << TEXT( " ( " );

   temp_string.Empty();

   switch( Privileges )
   {
      case USER_PRIV_GUEST:

         temp_string = TEXT( "USER_PRIV_GUEST" );
         break;

      case USER_PRIV_USER:

         temp_string = TEXT( "USER_PRIV_USER" );
         break;

      case USER_PRIV_ADMIN:

         temp_string = TEXT( "USER_PRIV_ADMIN" );
         break;

      default:

         temp_string = TEXT( "unknown" );
         break;
   }

   dump_context << temp_string << TEXT( " )\n" );

   dump_context << TEXT( "   Profile is " ) << Profile << TEXT( "\n" );
   dump_context << TEXT( "   ScriptPath is " ) << ScriptPath << TEXT( "\n" );
   dump_context << TEXT( "   UnitsPerWeek is " ) << UnitsPerWeek << TEXT( " ( " );

   temp_string.Empty();

   switch( UnitsPerWeek )
   {
      case UNITS_PER_WEEK:

         temp_string = TEXT( "UNITS_PER_WEEK" );
         break;

#if 0
      case SAM_DAYS_PER_WEEK:

         temp_string = TEXT( "SAM_DAYS_PER_WEEK" );
         break;

      case SAM_HOURS_PER_WEEK:

         temp_string = TEXT( "SAM_HOURS_PER_WEEK" );
         break;

      case SAM_MINUTES_PER_WEEK:

         temp_string = TEXT( "SAM_MINUTES_PER_WEEK" );
         break;
#endif 
      default:

         temp_string = TEXT( "unknown" );
         break;
   }

   dump_context << temp_string << TEXT( " )\n" );

   dump_context << TEXT( "   UserComment is " ) << UserComment << TEXT( "\n" );
   dump_context << TEXT( "   UserID is " ) << UserID << TEXT( "\n" );
   dump_context << TEXT( "   Workstations is " ) << Workstations << TEXT( "\n" );
   dump_context << TEXT( "}\n" );
}

#endif // _DEBUG

void CNetworkUserInformation::Empty( void )
{
   WFCLTRACEINIT( TEXT( "CNetworkUserInformation::Empty()" ) );
   m_Initialize();
}

void CNetworkUserInformation::m_Initialize( void )
{
   WFCLTRACEINIT( TEXT( "CNetworkUserInformation::m_Initialize()" ) );
   AccountExpires = CTime( (time_t) 0 );
   AuthenticationFlags = 0;
   BadPasswordCount = 0;
   CodePage = 0;
   Comment.Empty();
   CountryCode = 0;
   EncryptedPassword.RemoveAll();
   Flags = 0;
   FullName.Empty();
   HomeDirectory.Empty();
   HomeDirectoryDrive.Empty();
   LastLogoff = CTime( (time_t) 0 );
   LastLogon = CTime( (time_t) 0 );
   LogonHours.RemoveAll();
   LogonServer.Empty();
   MaximumStorage = 0;
   Name.Empty();
   NumberOfLogons = 0;
   Parameters.Empty();
   Password.Empty();
   PasswordAge = CTimeSpan( 0 );
   PasswordHasExpired = 0;
   PrimaryGroupID = 0;
   Privileges = 0;
   Profile.Empty();
   ScriptPath.Empty();
   UnitsPerWeek = 0;
   UserComment.Empty();
   UserID = 0;
   Workstations.Empty();
}

#if ! defined(  WFC_NO_SERIALIZATION )

void CNetworkUserInformation::Serialize( CArchive& archive )
{
   WFCLTRACEINIT( TEXT( "CNetworkUserInformation::Serialize()" ) );

   CObject::Serialize( archive );

   EncryptedPassword.Serialize( archive );
   LogonHours.Serialize( archive );

   if ( archive.IsStoring() )
   {
      WFCTRACE( TEXT( "Storing" ) );
      archive << Name;
      archive << Password;
      archive << PasswordAge;
      archive << Privileges;
      archive << HomeDirectory;
      archive << Comment;
      archive << Flags;
      archive << ScriptPath;
      archive << AuthenticationFlags;
      archive << FullName;
      archive << UserComment;
      archive << Parameters;
      archive << Workstations;
      archive << LastLogon;
      archive << LastLogoff;
      archive << AccountExpires;
      archive << MaximumStorage;
      archive << UnitsPerWeek;
      archive << BadPasswordCount;
      archive << NumberOfLogons;
      archive << LogonServer;
      archive << CountryCode;
      archive << CodePage;
      archive << UserID;
      archive << PrimaryGroupID;
      archive << HomeDirectoryDrive;
      archive << Profile;
      archive << PasswordHasExpired;
   }
   else
   {
      WFCTRACE( TEXT( "Restoring" ) );
      archive >> Name;
      archive >> Password;
      archive >> PasswordAge;
      archive >> Privileges;
      archive >> HomeDirectory;
      archive >> Comment;
      archive >> Flags;
      archive >> ScriptPath;
      archive >> AuthenticationFlags;
      archive >> FullName;
      archive >> UserComment;
      archive >> Parameters;
      archive >> Workstations;
      archive >> LastLogon;
      archive >> LastLogoff;
      archive >> AccountExpires;
      archive >> MaximumStorage;
      archive >> UnitsPerWeek;
      archive >> BadPasswordCount;
      archive >> NumberOfLogons;
      archive >> LogonServer;
      archive >> CountryCode;
      archive >> CodePage;
      archive >> UserID;
      archive >> PrimaryGroupID;
      archive >> HomeDirectoryDrive;
      archive >> Profile;
      archive >> PasswordHasExpired;
   }
}

#endif // WFC_NO_SERIALIZATION

void CNetworkUserInformation::SetAddDefaults( void )
{
   AccountExpires      = TIMEQ_FOREVER;
   AuthenticationFlags = 0;
   CodePage            = 0;
   CountryCode         = 0;
   Flags               = UF_DONT_EXPIRE_PASSWD | 
                         UF_NORMAL_ACCOUNT     |
                         UF_SCRIPT;
   FullName            = Name;
   MaximumStorage      = USER_MAXSTORAGE_UNLIMITED;
   Privileges          = privilegeUser;
   UserComment         = TEXT( "Added by WFC" );

   Parameters.Empty();
   Workstations.Empty();
   LogonServer.Empty();

   int index = 0;

   while( index < 21 )
   {
      LogonHours.Add( 0xFF );
      index++;
   }
}

const CNetworkUserInformation& CNetworkUserInformation::operator = ( const CNetworkUserInformation& source )
{
   ASSERT( this != &source );

   if ( this != &source )
   {
      Copy( source );
   }

   return( *this );
}

// End of source
