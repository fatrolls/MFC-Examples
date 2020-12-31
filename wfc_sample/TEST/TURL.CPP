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
** $Workfile: TURL.CPP $
** $Revision: 3 $
** $Modtime: 3/08/98 3:32p $
*/

void test_CUniformResourceLocator( void )
{
   WFCTRACEINIT( TEXT( "test_CUniformResourceLocator()" ) );

   CUniformResourceLocator url( TEXT( "Serial://COM2:9600,n,8,1/Settings.ini" ) );

#if 0
   if ( url.ProtocolName == TEXT( "Serial" )     &&  
        url.MachineName  == TEXT( "COM2" )       &&
        url.PortName     == TEXT( "9600,n,8,1" ) &&
        url.PathName     == TEXT( "Settings.ini" ) )
   {
      _tprintf( TEXT( "CUniformResourceLocator passed\n" ) );
   }
   else
   {
      _tprintf( TEXT( "CUniformResourceLocator FAILED!\n" ) );
      _tprintf( TEXT( "ProtocolName == \"%s\" when it should be \"Serial\"\n" ),     (LPCTSTR) url.ProtocolName );
      _tprintf( TEXT( "MachineName  == \"%s\" when it should be \"COM2\"\n" ),       (LPCTSTR) url.MachineName  );
      _tprintf( TEXT( "PortName     == \"%s\" when it should be \"9600,n,8,1\n" ),   (LPCTSTR) url.PortName     );
      _tprintf( TEXT( "Pathname     == \"%s\" when it should be \"Settings.ini\n" ), (LPCTSTR) url.PathName     );
   }
#endif
}

