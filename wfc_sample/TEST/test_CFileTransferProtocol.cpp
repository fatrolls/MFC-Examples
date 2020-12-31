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
** $Workfile: test_CFileTransferProtocol.cpp $
** $Revision: 4 $
** $Modtime: 1/31/00 7:46p $
*/

void test_CFileTransferProtocol( void )
{
   WFCTRACEINIT( TEXT( "test_CFileTransferProtocol()" ) );

#if ! defined( WFC_STL )

   // This registry stuff is here so I can keep private bits of
   // information about myself hidden from the WFC user group.
   // I trust you with WFC but not with my passwords ;-)

   CRegistry registry;

   if ( registry.Connect( (HKEY) CRegistry::keyLocalMachine ) == FALSE )
   {
      WFCTRACE( TEXT( "Can't connect to registry" ) );
      WFCTRACEVAL( TEXT( "At Line " ), __LINE__ );
      ReportError( registry.GetErrorCode() );
      return;
   }

   // Open HKEY_LOCAL_MACHINE\SOFTWARE\WFC\TEST\CFileTransferProtocol

   if ( registry.Open( TEXT( "SOFTWARE\\WFC\\TEST\\CFileTransferProtocol" ), (CRegistry::CreatePermissions)(CRegistry::permissionRead) ) == FALSE )
   {
      WFCTRACE( TEXT( "Can't open key" ) );
      WFCTRACEVAL( TEXT( "At line " ), __LINE__ );
      ReportError( registry.GetErrorCode() );
      return;
   }

   CString url_string;
   CString user;
   CString password;

   registry.GetValue( TEXT( "url"      ), url_string );
   registry.GetValue( TEXT( "user"     ), user       );
   registry.GetValue( TEXT( "password" ), password   );

   if ( url_string.GetLength() == 0 )
   {
      WFCTRACE( TEXT( "You haven't set HKEY_LOCAL_MACHINE\\SOFTWARE\\WFC\\TEST\\CFileTransferProtocol\\url to the URL for the server to test." ) );
      return;
   }

   if ( user.GetLength() == 0 )
   {
      WFCTRACE( TEXT( "You haven't set HKEY_LOCAL_MACHINE\\SOFTWARE\\WFC\\TEST\\CFileTransferProtocol\\user to the user name for the server to test." ) );
      return;
   }

   if ( password.GetLength() == 0 )
   {
      WFCTRACE( TEXT( "You haven't set HKEY_LOCAL_MACHINE\\SOFTWARE\\WFC\\TEST\\CFileTransferProtocol\\password to the password for the server to test." ) );
      return;
   }

   CFileTransferProtocol ftp;

   ftp.SetUserName( user );
   ftp.SetPassword( password );

   CStringArray directory;

   CUniformResourceLocator url( url_string );

   ftp.GetDirectory( url, directory, "*.*" );

   _tprintf( TEXT( "Directory for %s\n" ), (LPCTSTR) url );

   int index = 0;

   while( index < directory.GetSize() )
   {
      WFCTRACE( directory.GetAt( index ) );
      _tprintf( TEXT( "%s\n" ), (LPCTSTR) directory.GetAt( index ) );
      index++;
   }

   //CByteArray file_contents;

   //url = TEXT( "ftp://ftp.microsoft.com/disclaimer.txt" );

//   ftp.GetFile( url, file_contents );

  // _tprintf( TEXT( "Retrieved %d bytes\n" ), (int) file_contents.GetSize() );
#endif // WFC_STL
}

