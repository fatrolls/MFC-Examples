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
** $Workfile: TCRASPORT.CPP $
** $Revision: 2 $
** $Modtime: 3/08/98 3:32p $
*/

void test_CRemoteAccessServicePort( void )
{
   WFCTRACEINIT( TEXT( "test_CRemoteAccessServicePort()" ) );

   CRemoteAccessServicePort ras_port;

   CStringArray strings;

   ras.SetConnectionCallback( dial_monitor );
   ras.SetDialOptions( CRemoteAccessService::dialAcceptPausedStates );

   if ( ras.GetPhoneBookEntries( strings ) != FALSE )
   {
      DWORD index = 0;
      DWORD number_of_entries = strings.GetSize();

      TRACE( TEXT( "Phone Book Entries:\n" ) );

      while( index < number_of_entries )
      {
         TRACE1( TEXT( "\"%s\"\n" ), (LPCTSTR) strings[ index ] );
         index++;
      }
   }

   strings.RemoveAll();

   if ( ras.GetConnections( strings ) != FALSE )
   {
      DWORD index = 0;
      DWORD number_of_entries = strings.GetSize();

      TRACE( TEXT( "\nCurrent Connections:\n" ) );

      while( index < number_of_entries )
      {
         TRACE1( TEXT( "\"%s\"\n" ), (LPCTSTR) strings[ index ] );
         index++;
      }
   }

   if ( ras.Open( TEXT( "EROLS" ) ) == FALSE )
   {
      CString error_string;
      ras.GetErrorString( error_string );
      TRACE1( TEXT( "Ras Open failed with \"%s\"!\n" ), (LPCTSTR) error_string );
   }
   else
   {
      WFCTRACE( TEXT( "RAS Open!\n" ) );
   }

   strings.RemoveAll();

   if ( ras.GetConnections( strings ) != FALSE )
   {
      DWORD index = 0;
      DWORD number_of_entries = strings.GetSize();

      TRACE( TEXT( "\nCurrent Connections:\n" ) );

      while( index < number_of_entries )
      {
         TRACE1( TEXT( "\"%s\"\n" ), (LPCTSTR) strings[ index ] );
         index++;
      }
   }

   Sleep( 5000 );

   if ( ras.Close( TEXT( "Erols" ) ) != FALSE )
   {
      WFCTRACE( TEXT( "Close OK\n" ) );
   }
}
