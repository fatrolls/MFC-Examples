#include <wfc.h>
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
** Copyright, 2000, Samuel R. Blackburn
**
** $Workfile: wfc_get_day_of_week.cpp $
** $Revision: 4 $
** $Modtime: 1/17/00 9:33a $
** $Reuse Tracing Code: 1 $
*/

#if defined( _DEBUG ) && ! defined( WFC_STL )
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif // _DEBUG

BOOL PASCAL wfc_get_day_of_week( int year_with_century, int month, int day, int& day_of_week )
{
   WFCLTRACEINIT( TEXT( "wfc_get_day_of_week()" ) );

   day_of_week = 0;

   // This function is good only for Gregorian dates (until I find
   // source code that will handle ANY date). For now, all dates since
   // 1582 should suffice. The Gregorian calendar bagan on October 15, 1582.

   if ( year_with_century < 1582 )
   {
      WFCTRACE( TEXT( "Can't handle dates prior to 1582." ) );
      return( FALSE );
   }

   if ( year_with_century == 1582 )
   {
      if ( month < 10 )
      {
         WFCTRACE( TEXT( "Can't handle dates prior to October, 1582." ) );
         return( FALSE );
      }

      if ( month == 10 && day < 15 )
      {
         WFCTRACE( TEXT( "Can't handle dates prior to October 15, 1582." ) );
         return( FALSE );
      }
   }

   // Now, there's another little quirk, September 3rd through 13th did not
   // exist in 1752.

   if ( year_with_century == 1752 && month == 9 )
   {
      if ( day >= 3 && day <= 13 )
      {
         WFCTRACE( TEXT( "September 3rd-13th did not exist in 1752." ) );
         return( FALSE );
      }
   }

   if ( month <= 2 )
   {
      year_with_century++;
      month += 12;
   }

   DWORD temporary_day_of_week = 0;

   double term_1 = 0.0;

   term_1 = static_cast< double >( month + 1 ) * 3.0;
   term_1 /= 5.0;

   temporary_day_of_week  = ( day + ( month * 2 ) + static_cast< int >( term_1 ) + year_with_century + ( year_with_century / 4 ) );
   temporary_day_of_week -= ( year_with_century / 100 );
   temporary_day_of_week += ( year_with_century / 400 );
   temporary_day_of_week++;

   // Let's fix things for the Sept 3-13th that don't exist in 1752
   if ( year_with_century == 1752 )
   {
      if ( month < 9 )
      {
         temporary_day_of_week -= 10;
      }
      else if ( month == 9 )
      {
         if ( day <= 2 )
         {
            temporary_day_of_week -= 10;
         }
      }
   }
   else if ( year_with_century < 1752 )
   {
      temporary_day_of_week -= 10;
   }

   day_of_week = ( static_cast< int >( temporary_day_of_week % 7 ) );

   return( TRUE );
}

// End of source

#if 0
<HTML>

<HEAD>
<TITLE>WFC - wfc_get_day_of_week</TITLE>
<META name="keywords" content="WFC, MFC extension library, freeware class library, Win32">
<META name="description" content="Simple C function that computes the day of the week (taking into account September 3rd through 13th did not exist in 1752).">
</HEAD>

<BODY>

<H1>wfc_get_day_of_week</H1>
$Revision: 4 $<HR>

<H2>Declaration</H2>
<PRE>BOOL <B>wfc_get_day_of_week</B>( int year_with_century, int month, int day, int&amp; day_of_week )</PRE>

<H2>Description</H2>
This function returns TRUE if the day of week was successfully computed.
It will return 0 (Sunday) through 6 (Saturday).

<H2>Example</H2>
<PRE><CODE>bool is_monday( int year, int month, int day )
{
   <A HREF="WfcTrace.htm">WFCTRACEINIT</A>( TEXT( &quot;is_monday()&quot; ) );


   int day_of_week = 0;

   if ( <B>wfc_get_day_of_week</B>( year, month, day, day_of_week ) == FALSE )
   {
      return( FALSE );
   }

   if ( day_of_week == 1 )
   {
      return( TRUE );
   }

   return( FALSE );
}</CODE></PRE>

<H2>API's Used</H2>
<B>wfc_get_day_of_week</B>() doesn't use any API's.

<HR><I>Copyright, 2000, <A HREF="mailto:wfc@pobox.com">Samuel R. Blackburn</A></I><BR>
$Workfile: wfc_get_day_of_week.cpp $<BR>
$Modtime: 1/17/00 9:33a $
</BODY>

</HTML>
#endif
