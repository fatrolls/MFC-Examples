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
** $Workfile: TCSess.CPP $
** $Revision: 2 $
** $Modtime: 3/08/98 3:31p $
*/

void print_information( CNetworkSessionInformation& information )
{
   _tprintf( TEXT( "\"%s\" - \"%s\" - %d - %s - %s - %d - \"%s\" - \"%s\"\n" ),
           (LPCTSTR) information.ClientName,
           (LPCTSTR) information.UserName,
                     information.NumberOfOpens,
           (LPCTSTR) information.Time.Format( "%H:%M:%S" ),
           (LPCTSTR) information.IdleTime.Format( "%H:%M:%S" ),
                     information.UserFlags,
           (LPCTSTR) information.ClientTypeName,
           (LPCTSTR) information.Transport );
}

void test_CNetSession( LPCTSTR machine_name )
{
   WFCTRACEINIT( TEXT( "test_CNetSession()" ) );

   CNetworkSessions session;

   CNetworkSessionInformation information;

   session.Open( machine_name );

   if ( session.Enumerate( information ) != FALSE )
   {
      print_information( information );

      while( session.GetNext( information ) != FALSE )
      {
         print_information( information );
      }
   }
   else
   {
      DWORD error_code = session.GetErrorCode();

      CString error_message;

      Convert_NERR_Code_to_String( error_code, error_message );

      _tprintf( TEXT( "CNetSession.ErrorCode == %d \"%s\"\n" ), error_code, (LPCTSTR) error_message );
   }
}

