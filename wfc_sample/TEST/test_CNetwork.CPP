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
** $Workfile: test_CNetwork.CPP $
** $Revision: 2 $
** $Modtime: 3/08/98 3:31p $
*/

void test_CNetwork( LPCTSTR machine_name )
{
   WFCTRACEINIT( TEXT( "test_CNetwork()" ) );

   CNetwork machine( machine_name );

   if ( machine.EnumeratePorts() )
   {
      if ( machine_name != NULL )
      {
         _tprintf( TEXT( "Ports on %s\n" ), machine_name );
      }
      else
      {
         _tprintf( TEXT( "Ports on local machine\n" ) );
      }

      CPortInformation port;

      while( machine.GetNext( port ) != FALSE )
      {
         _tprintf( TEXT( "Name:        %s\n" ), (LPCTSTR) port.Name        );
         _tprintf( TEXT( "Monitor:     %s\n" ), (LPCTSTR) port.Monitor     );
         _tprintf( TEXT( "Description: %s\n" ), (LPCTSTR) port.Description );
         _tprintf( TEXT( "Type:        %04lX\n" ), port.Type );
         _tprintf( TEXT( "TypeName:    %s\n\n" ), (LPCTSTR) port.TypeName );
      }
   }
   else
   {
      DWORD error_code = machine.GetErrorCode();
      ReportError( error_code );
      _tprintf( TEXT( "Can't EnumeratePorts, reason code %lu\n" ), error_code );
   }

   if ( machine.IsRebootable() )
   {
      if ( machine_name != NULL )
      {
         _tprintf( TEXT( "Yes, I can reboot %s\n" ), machine_name );
      }
      else
      {
         _tprintf( TEXT( "Yes, I can reboot this machine\n" ) );
      }
   }
}
