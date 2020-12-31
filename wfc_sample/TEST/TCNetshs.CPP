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
** $Workfile: TCNetshs.CPP $
** $Revision: 2 $
** $Modtime: 3/08/98 3:32p $
*/

void test_CNetworkShares( LPCTSTR machine_name )
{
   WFCTRACEINIT( TEXT( "test_CNetworkShares()" ) );

   CNetworkShares shares( machine_name );

   CNetworkShareInformation share_information;

   if ( shares.Enumerate() != FALSE )
   {
      _tprintf( TEXT( "Share Information for %s:\n" ), (LPCTSTR) shares.GetMachineName() );

      while( shares.GetNext( share_information ) != FALSE )
      {
         _tprintf( TEXT( " NetworkName         - \"%s\"\n" ), (LPCTSTR) share_information.NetworkName         );
         _tprintf( TEXT( " Type                - %lu " ),               share_information.Type                );

         switch( share_information.Type )
         {
            case STYPE_DISKTREE:

               _tprintf( TEXT( "Disk" ) );
               break;

            case STYPE_PRINTQ:

               _tprintf( TEXT( "Printer" ) );
               break;

            case STYPE_DEVICE:

               _tprintf( TEXT( "Communications Device" ) );
               break;

            case STYPE_IPC:

               _tprintf( TEXT( "IPC" ) );
               break;

#if 0
            case STYPE_DFS:

               _tprintf( TEXT( "Distributed File System" ) );
               break;
#endif
            case STYPE_SPECIAL:

               _tprintf( TEXT( "Special" ) );
               break;

            default:

               _tprintf( TEXT( "Unknown Type" ) );
               break;
         }

         _tprintf( TEXT( "\n" ) );
         _tprintf( TEXT( " Remark              - \"%s\"\n" ), (LPCTSTR) share_information.Remark              );
         _tprintf( TEXT( " Permissions         - %lu\n" ),              share_information.Permissions         );
         _tprintf( TEXT( " MaximumNumberOfUses - %d\n" ),               share_information.MaximumNumberOfUses );
         _tprintf( TEXT( " CurrentNumberOfUses - %d\n" ),               share_information.CurrentNumberOfUses );
         _tprintf( TEXT( " PathName            - \"%s\"\n" ), (LPCTSTR) share_information.PathName            );
         _tprintf( TEXT( " Password            - \"%s\"\n\n" ), (LPCTSTR) share_information.Password          );
      }
   }
   else
   {
      DWORD error_code = shares.GetErrorCode();

      CString error_message;

      Convert_NERR_Code_to_String( error_code, error_message );

      _tprintf( TEXT( "CNetworkShares.Enumerate( share_information ), ErrorCode == %d \"%s\"\n" ), error_code, (LPCTSTR) error_message );
   }
}
