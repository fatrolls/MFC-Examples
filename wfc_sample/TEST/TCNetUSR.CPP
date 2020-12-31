#include "test.h"
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
** Copyright, 1997, Samuel R. Blackburn
**
** $Workfile: TCNetUSR.CPP $
** $Revision: 3 $
** $Modtime: 1/31/00 7:33p $
*/

void test_CNetworkUsers( LPCTSTR machine_name )
{
   WFCTRACEINIT( TEXT( "test_CNetworkUsers()" ) );

   CNetworkUsers users( machine_name );

   CNetworkUserInformation user_information;

   if ( users.Enumerate() != FALSE )
   {
      _tprintf( TEXT( "User Information for %s:\n" ), (LPCTSTR) users.GetMachineName() );

      while( users.GetNext( user_information ) != FALSE )
      {
#if defined( _DEBUG ) && ! defined( WFC_STL )
         user_information.Dump( afxDump );
#endif // _DEBUG
         _tprintf( TEXT( " Name                 - \"%s\"\n" ), (LPCTSTR) user_information.Name          );
         _tprintf( TEXT( " Full Name            - \"%s\"\n" ), (LPCTSTR) user_information.FullName      );
         _tprintf( TEXT( " Comment              - \"%s\"\n" ), (LPCTSTR) user_information.Comment       );
         _tprintf( TEXT( " User Comment         - \"%s\"\n" ), (LPCTSTR) user_information.UserComment   );
         _tprintf( TEXT( " ID                   - %lu\n" ),              user_information.UserID        );
         _tprintf( TEXT( " Flags                - %lX\n" ),              user_information.Flags         );
         _tprintf( TEXT( " Privileges           - %lX\n" ),              user_information.Privileges    );
         _tprintf( TEXT( " Password             - \"%s\"\n" ), (LPCTSTR) user_information.Password      );
         _tprintf( TEXT( " Password Age         - %d Days %d Hours %d Minutes %d seconds\n" ),
                   user_information.PasswordAge.GetDays(),
                   user_information.PasswordAge.GetHours(),
                   user_information.PasswordAge.GetMinutes(),
                   user_information.PasswordAge.GetSeconds() );
         _tprintf( TEXT( " HomeDirectory        - \"%s\"\n" ), (LPCTSTR) user_information.HomeDirectory );
         _tprintf( TEXT( " Script Path          - \"%s\"\n" ), (LPCTSTR) user_information.ScriptPath    );
         _tprintf( TEXT( " Parameters           - \"%s\"\n" ), (LPCTSTR) user_information.Parameters    );
         _tprintf( TEXT( " Workstations         - \"%s\"\n" ), (LPCTSTR) user_information.Workstations  );
         _tprintf( TEXT( " LastLogon            - \"%s\"\n" ), (LPCTSTR) user_information.LastLogon.Format( TEXT( "%a %d %b %y, %H:%M:%S" ) ) );
         _tprintf( TEXT( " LastLogoff           - \"%s\"\n" ), (LPCTSTR) user_information.LastLogoff.Format( TEXT( "%a %d %b %y, %H:%M:%S" ) ) );
         _tprintf( TEXT( " Account Expires      - \"%s\"\n" ), (LPCTSTR) user_information.AccountExpires.Format( TEXT( "%a %d %b %y, %H:%M:%S" ) ) );
         _tprintf( TEXT( " Maximum Storage      - %lu\n" ),              user_information.MaximumStorage     );
         _tprintf( TEXT( " Bad Password Count   - %lu\n" ),              user_information.BadPasswordCount   );
         _tprintf( TEXT( " Number Of Logons     - %lu\n" ),              user_information.NumberOfLogons     );
         _tprintf( TEXT( " Logon Server         - \"%s\"\n" ), (LPCTSTR) user_information.LogonServer        );
         _tprintf( TEXT( " Country Code         - %lX\n" ),              user_information.CountryCode        );
         _tprintf( TEXT( " Code Page            - %lX\n" ),              user_information.CodePage           );
         _tprintf( TEXT( " Primary Group ID     - %lu\n" ),              user_information.PrimaryGroupID     );
         _tprintf( TEXT( " Home Directory Drive - \"%s\"\n" ), (LPCTSTR) user_information.HomeDirectoryDrive );
         _tprintf( TEXT( " Profile              - \"%s\"\n" ), (LPCTSTR) user_information.Profile            );
         _tprintf( TEXT( " Password Has Expired - %lu\n" ),              user_information.PasswordHasExpired );
         _tprintf( TEXT( " Encrypted Password: " ) );

         int index = 0;

         while( index < user_information.EncryptedPassword.GetSize() )
         {
            _tprintf( TEXT( "%02X" ), (int) user_information.EncryptedPassword.GetAt( index ) );
            index++;
         }

         _tprintf( TEXT( "\n\n" ) );
      }
   }
   else
   {
      DWORD error_code = users.GetErrorCode();

      CString error_message;

      Convert_NERR_Code_to_String( error_code, error_message );

      _tprintf( TEXT( "CNetworkUsers.Enumerate( user_information ), ErrorCode == %d \"%s\"\n" ), error_code, (LPCTSTR) error_message );
   }

   user_information.Empty();

   user_information.Name     = TEXT( "Laura" );
   user_information.Password = TEXT( "LovesSammy" );

   user_information.SetAddDefaults();

   if ( users.Add( user_information ) != FALSE )
   {
      _tprintf( TEXT( "Laura Added.\n" ) );
   }
   else
   {
      _tprintf( TEXT( "Can't Add User\n" ) );
   }

   if ( users.Delete( TEXT( "Laura" ) ) != FALSE )
   {
      _tprintf( TEXT( "Deleted Laura\n" ) );
   }
   else
   {
      _tprintf( TEXT( "Can't delete Laura\n" ) );
   }
}
