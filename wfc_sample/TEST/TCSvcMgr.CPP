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
** $Workfile: TCSvcMgr.CPP $
** $Revision: 3 $
** $Modtime: 1/31/00 7:43p $
*/

void test_CServiceControlManager( void )
{
   WFCTRACELEVELON( 31 );
   WFCTRACEINIT( TEXT( "test_CServiceControlManager()" ) );

   CServiceControlManager manager;

   CString machine_name( TEXT( "Sammy" ) );

   if ( manager.Open( GENERIC_READ, NULL, machine_name ) == FALSE )
   {
      WFCTRACE( TEXT( "Can't open manager" ) );
      WFCTRACEERROR( manager.GetErrorCode() );
      _tprintf( TEXT( "Can't Open ServiceControlManager\n" ) );
      return;
   }

   if ( manager.EnumerateStatus( SERVICE_STATE_ALL, SERVICE_TYPE_ALL ) != FALSE )
   {
      WFCTRACEVAL( TEXT( "Services on " ), machine_name );
      _tprintf( TEXT( "Services on %s:\n" ), (LPCTSTR) machine_name );

      CServiceNameAndStatus status;

      while( manager.GetNext( status ) != FALSE )
      {
#if defined( _DEBUG ) && ! defined( WFC_STL )
         status.Dump( afxDump );
#endif // _DEBUG
         _tprintf( TEXT( "%s - \"%s\"\n" ), status.lpServiceName, status.lpDisplayName );
      }
   }
   else
   {
      WFCTRACE( TEXT( "Can't enumerate" ) );
      WFCTRACEERROR( manager.GetErrorCode() );
      _tprintf( TEXT( "Can't Enumerate\n" ) );
   }
}
