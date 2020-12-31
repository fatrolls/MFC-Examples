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
** $Workfile: TCSrvr.CPP $
** $Revision: 2 $
** $Modtime: 3/08/98 3:32p $
*/

void test_CServer( LPCTSTR machine_name )
{
   WFCTRACEINIT( TEXT( "test_CServer()" ) );

   CServer server;

   server.Open( machine_name );

   CString name;
   CString comment;
   CString path;
   CString os;
   CString domain;

   DWORD major_version   = 0;
   DWORD minor_version   = 0;
   DWORD type            = 0;
   DWORD users           = 0;
   DWORD number_of_users = 0;
   DWORD number_of_opens = 0;

   server.GetUserPath( path );
   server.GetName( name );
   server.GetComment( comment );
   server.GetPlatformName( os );
   server.GetDomain( domain );

   major_version   = server.GetMajorVersion();
   minor_version   = server.GetMinorVersion();
   type            = server.GetType();
   users           = server.GetUsers();
   number_of_users = server.GetNumberOfUsers();
   number_of_opens = server.GetNumberOfOpens();

   _tprintf( TEXT( "Server Name:      \"%s\"\n" ), (LPCTSTR) name    );
   _tprintf( TEXT( "Server Domain:    \"%s\"\n" ), (LPCTSTR) domain  );
   _tprintf( TEXT( "Server Comment:   \"%s\"\n" ), (LPCTSTR) comment );
   _tprintf( TEXT( "Server User Path: \"%s\"\n" ), (LPCTSTR) path    );
   _tprintf( TEXT( "Server OS:        \"%s\"\n" ), (LPCTSTR) os      );
   _tprintf( TEXT( "Server Version:    %d.%d\n" ), major_version, minor_version );
   _tprintf( TEXT( "Server Users:      %d\n" ),    users );
   _tprintf( TEXT( "Number Of Users:   %d\n" ),    number_of_users );
   _tprintf( TEXT( "Number Of Opens:   %d\n" ),    number_of_opens );
}

