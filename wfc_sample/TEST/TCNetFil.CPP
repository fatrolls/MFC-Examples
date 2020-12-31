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
** $Workfile: TCNetFil.CPP $
** $Revision: 2 $
** $Modtime: 3/08/98 3:31p $
*/

// Why don't cannabals eat clowns? They taste funny.

void test_CNetworkFiles( LPCTSTR machine_name )
{
   WFCTRACEINIT( TEXT( "test_CNetworkFiles()" ) );

   CNetworkFiles network_files( machine_name );

   CNetworkFileInformation network_files_information;

   if ( network_files.Enumerate() != FALSE )
   {
      _tprintf( TEXT( "Network Files Information:\n" ) );

      while( network_files.GetNext( network_files_information ) != FALSE )
      {
         _tprintf( TEXT( " ID            - %d\n" ),               network_files_information.ID            );
         _tprintf( TEXT( " PathName      - \"%s\"\n" ), (LPCTSTR) network_files_information.PathName      );
         _tprintf( TEXT( " UserName      - \"%s\"\n" ), (LPCTSTR) network_files_information.UserName      );
         _tprintf( TEXT( " Permissions   - %d\n" ),               network_files_information.Permissions   );
         _tprintf( TEXT( " NumberOfLocks - %d\n" ),               network_files_information.NumberOfLocks );
      }
   }
   else
   {
      DWORD error_code = network_files.GetErrorCode();

      CString error_message;

      Convert_NERR_Code_to_String( error_code, error_message );

      _tprintf( TEXT( "CNetworkFiles.Enumerate( CNetworkFileInformation ), ErrorCode == %d \"%s\"\n" ), error_code, (LPCTSTR) error_message );
   }
}
