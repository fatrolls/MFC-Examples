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
** $Workfile: TCNSrc.cpp $
** $Revision: 2 $
** $Modtime: 3/08/98 3:30p $
*/

void print_resource( CNetworkResourceInformation& information )
{
   _tprintf( TEXT( "\"%s\" - \"%s\" - \"%s\" - \"%s\"\n" ),
           (LPCTSTR) information.LocalName,
           (LPCTSTR) information.RemoteName,
           (LPCTSTR) information.Comment,
           (LPCTSTR) information.Provider );
}

void test_CNetResource( void )
{
   WFCTRACEINIT( TEXT( "test_CNetResource()" ) );

   CNetworkResources net_resource;

   CNetworkResourceInformation information;

   information.Scope = CNetworkResources::scopeAll;
   information.Usage = CNetworkResources::usageConnectable | CNetworkResources::usageContainer;
   information.Type  = CNetworkResources::typeDisk;

   if ( net_resource.Enumerate( information ) != FALSE )
   {
      print_resource( information );

      while( net_resource.GetNext( information ) != FALSE )
      {
         print_resource( information );
      }

      DWORD error_code = net_resource.GetErrorCode();

      CString error_message;

      Convert_NERR_Code_to_String( error_code, error_message );

      _tprintf( TEXT( "CNetSession.ErrorCode == %d \"%s\"\n" ), error_code, (LPCTSTR) error_message );
   }
   else
   {
      DWORD error_code = net_resource.GetErrorCode();

      CString error_message;

      Convert_NERR_Code_to_String( error_code, error_message );

      _tprintf( TEXT( "CNetSession.ErrorCode == %d \"%s\"\n" ), error_code, (LPCTSTR) error_message );
   }
}

