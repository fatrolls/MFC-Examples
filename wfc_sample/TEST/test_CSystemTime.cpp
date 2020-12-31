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
** $Workfile: test_CSystemTime.cpp $
** $Revision: 2 $
** $Modtime: 1/31/00 7:47p $
*/

void test_CSystemTime( void )
{
   WFCTRACEINIT( TEXT( "test_CSystemTime()" ) );

   TIMESTAMP_STRUCT timestamp_struct;

   timestamp_struct.year     = 1752;
   timestamp_struct.month    = 9;
   timestamp_struct.day      = 2;
   timestamp_struct.hour     = 7;
   timestamp_struct.minute   = 32;
   timestamp_struct.second   = 22;
   timestamp_struct.fraction = 14;

   CSystemTime system_time( &timestamp_struct );

#if defined( _DEBUG ) && ! defined( WFC_STL )

   system_time.Dump( afxDump );

#endif // _DEBUG

   WFCTRACEVAL( "Day of week should be 6 and it is ", system_time.wDayOfWeek );
}
