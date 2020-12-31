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
** $Workfile: TCNet.CPP $
** $Revision: 2 $
** $Modtime: 3/08/98 3:30p $
*/

void test_CNetWorkstation( LPCTSTR machine_name )
{
   WFCTRACEINIT( TEXT( "test_CNetWorkstation()" ) );

   CNetWorkstation workstation( machine_name );

   CWorkstationInformation workstation_information;

   if ( workstation.EnumerateInformation() != FALSE )
   {
      _tprintf( TEXT( "Workstation Machine Information:\n" ) );

      while( workstation.GetNext( workstation_information ) != FALSE )
      {
         _tprintf( TEXT( " PlatformID            - %d\n" ),               workstation_information.PlatformID            );
         _tprintf( TEXT( " Name                  - \"%s\"\n" ), (LPCTSTR) workstation_information.ComputerName          );
         _tprintf( TEXT( " LANGroup              - \"%s\"\n" ), (LPCTSTR) workstation_information.LANGroup              );
         _tprintf( TEXT( " MajorVersion          - %d\n" ),               workstation_information.MajorVersion          );
         _tprintf( TEXT( " MinorVersion          - %d\n" ),               workstation_information.MinorVersion          );
         _tprintf( TEXT( " LANRoot               - \"%s\"\n" ), (LPCTSTR) workstation_information.LANRoot               );
         _tprintf( TEXT( " NumberOfLoggedOnUsers - %d\n" ),               workstation_information.NumberOfLoggedOnUsers );
      }
   }
   else
   {
      DWORD error_code = workstation.GetErrorCode();

      CString error_message;

      Convert_NERR_Code_to_String( error_code, error_message );

      _tprintf( TEXT( "CNetWorkstation.Enumerate( workstation_information ), ErrorCode == %d \"%s\"\n" ), error_code, (LPCTSTR) error_message );
   }

   CWorkstationUser user_information;

   if ( workstation.EnumerateUsers() != FALSE )
   {
      _tprintf( TEXT( "\nWorkstation User Information:\n" ) );

      WCHAR wide_machine_name[ 256 ];
      WCHAR wide_domain_name[ 256 ];

      LPSTR buffer = NULL;

      ZeroMemory( wide_machine_name, sizeof( wide_machine_name ) );
      ZeroMemory( wide_domain_name,  sizeof( wide_domain_name  ) );

      while( workstation.GetNext( user_information ) != FALSE )
      {
         ASCII_to_UNICODE( (LPCTSTR) user_information.LogonServer, wide_machine_name );
         ASCII_to_UNICODE( (LPCTSTR) user_information.LogonDomain, wide_domain_name  );

         NetGetDCName( wide_machine_name, wide_domain_name, (LPBYTE *) &buffer );
         UNICODE_to_ASCII( (LPCWSTR) buffer, buffer );

         _tprintf( TEXT( " User Name     - \"%s\"\n" ),      (LPCTSTR) user_information.UserName     );
         _tprintf( TEXT( " Logon Domain  - \"%s\" [%s]\n" ), (LPCTSTR) user_information.LogonDomain, (LPSTR) buffer );
         _tprintf( TEXT( " Other Domains - \"%s\"\n" ),      (LPCTSTR) user_information.OtherDomains );
         _tprintf( TEXT( " Logon Server  - \"%s\"\n\n" ),    (LPCTSTR) user_information.LogonServer  );
      }
   }
   else
   {
      DWORD error_code = workstation.GetErrorCode();

      CString error_message;

      Convert_NERR_Code_to_String( error_code, error_message );

      _tprintf( TEXT( "CNetWorkstation.Enumerate( user_information ), ErrorCode == %d \"%s\"\n" ), error_code, (LPCTSTR) error_message );
   }

   user_information.Empty();

   if ( workstation.GetCurrentUser( user_information ) != FALSE )
   {
      _tprintf( TEXT( "\nWorkstation Current User Information:\n" ) );
      _tprintf( TEXT( " User Name     - \"%s\"\n" ), (LPCTSTR) user_information.UserName     );
      _tprintf( TEXT( " Logon Domain  - \"%s\"\n" ), (LPCTSTR) user_information.LogonDomain  );
      _tprintf( TEXT( " Other Domains - \"%s\"\n" ), (LPCTSTR) user_information.OtherDomains );
      _tprintf( TEXT( " Logon Server  - \"%s\"\n" ), (LPCTSTR) user_information.LogonServer  );
   }
   else
   {
      DWORD error_code = workstation.GetErrorCode();

      CString error_message;

      Convert_NERR_Code_to_String( error_code, error_message );

      _tprintf( TEXT( "CNetWorkstation.GetCurrentUser( user_information ), ErrorCode == %d \"%s\"\n" ), error_code, (LPCTSTR) error_message );
   }

   CWorkstationTransport transport_information;

   if ( workstation.EnumerateTransports() != FALSE )
   {
      _tprintf( TEXT( "\nWorkstation Transport Information:\n" ) );

      while( workstation.GetNext( transport_information ) != FALSE )
      {
         _tprintf( TEXT( " Quality of Service         - %d\n" ), transport_information.QualityOfService        );
         _tprintf( TEXT( " Number Of Virtual Circuits - %d\n" ), transport_information.NumberOfVirtualCircuits );
         _tprintf( TEXT( " Name                       - \"%s\"\n" ), (LPCTSTR) transport_information.Name      );
         _tprintf( TEXT( " Address                    - \"%s\"\n" ), (LPCTSTR) transport_information.Address   );
   
         if ( transport_information.WANish != FALSE )
         {
            _tprintf( TEXT( " WANish                     - TRUE\n\n" ) );
         }
         else
         {
            _tprintf( TEXT( " WANish                     - FALSE\n\n" ) );
         }
      }
   }
   else
   {
      DWORD error_code = workstation.GetErrorCode();

      CString error_message;

      Convert_NERR_Code_to_String( error_code, error_message );

      _tprintf( TEXT( "CNetWorkstation.Enumerate( transport_information ), ErrorCode == %d \"%s\"\n" ), error_code, (LPCTSTR) error_message );
   }
}

