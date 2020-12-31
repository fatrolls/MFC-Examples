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
** $Workfile: TCNetCon.CPP $
** $Revision: 2 $
** $Modtime: 3/08/98 3:32p $
*/

void test_CNetworkConnections( LPCTSTR machine_name )
{
   WFCTRACEINIT( TEXT( "test_CNetworkConnections()" ) );

   CNetworkConnections connections( machine_name );

   CNetworkConnectionInformation connection_information;

   if ( connections.Enumerate( TEXT( "data" ) ) != FALSE )
   {
      _tprintf( TEXT( "Network Connections Information:\n" ) );

      while( connections.GetNext( connection_information ) != FALSE )
      {
         _tprintf( TEXT( " ID            - %d\n" ),               connection_information.ID            );
         _tprintf( TEXT( " Type          - %d\n" ),               connection_information.Type          );
         _tprintf( TEXT( " NumberOfUsers - %d\n" ),               connection_information.NumberOfUsers );
         _tprintf( TEXT( " NumberOfOpens - %d\n" ),               connection_information.NumberOfOpens );
         _tprintf( TEXT( " Time          - %d\n" ),               connection_information.Time          );
         _tprintf( TEXT( " UserName      - \"%s\"\n" ), (LPCTSTR) connection_information.UserName      );
         _tprintf( TEXT( " NetName       - \"%s\"\n" ), (LPCTSTR) connection_information.NetName       );
      }
   }
   else
   {
      DWORD error_code = connections.GetErrorCode();

      CString error_message;

      Convert_NERR_Code_to_String( error_code, error_message );

      _tprintf( TEXT( "CNetworkConnections.Enumerate( CNetworkConnectionInformation ), ErrorCode == %d \"%s\"\n" ), error_code, (LPCTSTR) error_message );
   }
}
