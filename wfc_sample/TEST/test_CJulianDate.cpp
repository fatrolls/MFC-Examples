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
** $Workfile: test_CJulianDate.cpp $
** $Revision: 1 $
** $Modtime: 9/15/98 8:58a $
*/

void test_CJulianDate( void )
{
   WFCTRACEINIT( TEXT( "test_CJulianDate()" ) );

   CJulianDate date;

   date.Set( 32767, 12, 31 );

   double julian_date = date.Get();

   WFCTRACEVAL( TEXT( "Julian Date is " ), julian_date );

   int day_of_week = 0;

   day_of_week = date.GetDayOfWeek();

   // 0 - Sunday
   // 1 - Monday
   // 2 - Tuesday
   // 3 - Wednesday
   // 4 - Thursday
   // 5 - Friday
   // 6 - Saturday

   ASSERT( day_of_week == 2 );

   WFCTRACE( TEXT( "Passed." ) );
}
