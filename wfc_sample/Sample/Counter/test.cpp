#include "counter.h"
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
** Copyright, 1996, Samuel R. Blackburn
**
** $Workfile: $
** $Revision: $
** $Modtime: $
*/

void main()
{
   CPerformanceData data;

   CString counter_name;

   data.GetName( 870, counter_name );
   _tprintf( TEXT( "870 == \"%s\"\n" ), (LPCTSTR) counter_name );

   data.GetName( 872, counter_name );
   _tprintf( TEXT( "872 == \"%s\"\n" ), (LPCTSTR) counter_name );

   _tprintf( TEXT( "There are %lu performance objects\n" ), data.GetNumberOfObjects() );

   data.DumpPerfDataBlock( afxDump );
}
