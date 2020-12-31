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
** $Workfile: CJulianDate.cpp $
** $Revision: 5 $
** $Modtime: 1/05/00 4:19a $
** $Reuse Tracing Code: 1 $
*/

#if defined( _DEBUG ) && ! defined( WFC_STL )
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif // _DEBUG

CJulianDate::~CJulianDate()
{
   WFCLTRACEINIT( TEXT( "CJulianDate::~CJulianDate()" ) );
   m_JulianDays = 0.0;
}

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

void CJulianDate::Dump( CDumpContext& dump_context ) const
{
   dump_context << TEXT( " a CJulianDate at " ) << (VOID *) this << TEXT( "\n{\n" );
   dump_context << TEXT( "   m_JulianDays is " ) << m_JulianDays << TEXT( "\n" );
   dump_context << TEXT( "}\n" );
}

#endif // _DEBUG

int CJulianDate::GetDayOfWeek( void ) const
{
   long julian_day = (long) m_JulianDays;

   int day_of_week = ( ( julian_day % 7L ) + 1 );

   return( ( day_of_week == 7 ) ? 0 : day_of_week );
}

BOOL CJulianDate::Set( int year, int month, int day, int hours, int minutes, int seconds )
{
   WFCLTRACEINIT( TEXT( "CJulianDate::Set()" ) );

   double x = 0.0;

   if ( year == 1582 )
   {
      if ( month == 10 )
      {
         if ( day > 4 && day < 15 )
         {
            day = 15;
         }
      }
   }

   x = (double) ( ( 12 * ( year + 4800 ) ) + month - 3 );
   m_JulianDays = ( 2 * ( x - ( ::floor( x / 12.0 ) * 12 ) ) + 7 + ( 365 * x ) ) / 12;
   m_JulianDays = ::floor( m_JulianDays ) + day + ::floor( x / 48.0 ) - 32083;

   if ( m_JulianDays > 2299170L )
   {
      m_JulianDays = m_JulianDays + ::floor( x / 4800.0 ) - ::floor( x / 1200.0 ) + 38;
   }

   double double_hours   = (double) hours;
   double double_minutes = (double) minutes;
   double double_seconds = (double) seconds;

   double_hours   /= 24.0;
   double_minutes /= 1440.0;
   double_seconds /= 86400.0;

   m_JulianDays += ( ( double_hours + double_minutes + double_seconds ) - 0.5 );

   return( TRUE );
}

// End of source

#if 0
<HTML>

<HEAD>
<TITLE>WFC - CJulianDate</TITLE>
<META name="keywords" content="WFC, MFC extension library, freeware class library, Win32">
<META name="description" content="The C++ class that handles dates and times.">
</HEAD>

<BODY>

<H1>CJulianDate</H1>
$Revision: 5 $<BR>
<HR>

<H2>Description</H2>

This class allows you to play with dates.
<STRONG>It is still under development so don&#39;t use it.</STRONG>

<H2>Data Members</H2>
None.

<H2>Methods</H2>

<DL COMPACT>

<DT><PRE>BOOL <B>Set</B>( int year, int month, int day, int hours, int minutes, int seconds )</PRE><DD>
Sets the date and time of the object.

</DL>

<H2>Example</H2>

<PRE><CODE>Sorry.</CODE></PRE>

<HR><I>Copyright, 2000, Samuel R. Blackburn</I><BR>
$Workfile: CJulianDate.cpp $<BR>
$Modtime: 1/05/00 4:19a $

</BODY>
</HTML>
#endif
