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
** $Workfile: CTimeEx.cpp $
** $Revision: 4 $
** $Modtime: 5/02/00 6:08p $
** $Reuse Tracing Code: 1 $
*/

#if defined( WIN32 ) && defined( _DEBUG ) && ! defined( WFC_STL )
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif // WIN32

#if defined( WFC_STL )

/*
** This module uses exception handling to trap
** for errant pointers. This is useless on Unix
** systems because they are too stupid to detect
** such conditions. On Windows NT machines the
** errant pointers are trapped and the catch()
** block of the handler is executed.
*/

#define NUMBER_OF_NANOSECONDS_IN_ONE_SECOND (1000000000)

#if defined( WFC_STL )

CString CTimeSpan::Format( LPCTSTR format_string ) const
{
   WFCLTRACEINIT( TEXT( "CTimeSpan::Format()" ) );

   CString return_value;

   try
   {
      CString number_string;

      int format_string_index = 0;

      TCHAR character = 0;

      character = format_string[ format_string_index ];

      while( character != 0 )
      {
         if ( character == '%' )
         {
            format_string_index++;
            character = format_string[ format_string_index ];

            switch( character )
            {
               case '%':

                  return_value += TEXT( '%' );
                  break;

               case 'D':

                  number_string.Format( TEXT( "%ld" ), GetDays() );
                  return_value += number_string;
                  break;

               case 'H':

                  number_string.Format( TEXT( "%02ld" ), GetHours() );
                  return_value += number_string;
                  break;

               case 'M':

                  number_string.Format( TEXT( "%02ld" ), GetMinutes() );
                  return_value += number_string;
                  break;

               case 'S':

                  number_string.Format( TEXT( "%02ld" ), GetSeconds() );
                  return_value += number_string;
                  break;
            }
         }
         else
         {
            return_value += format_string[ format_string_index ];
         }

         format_string_index++;
      }
   }
   catch( ... )
   {
   }

   return( return_value );
}

#endif // WFC_STL

CTimeEx::CTimeEx()
{
   WFCLTRACEINIT( "CTimeEx::CTimeEx()" );
   Empty();
}

CTimeEx::CTimeEx( const CTimeEx& source )
{
   WFCLTRACEINIT( "CTimeEx::CTimeEx( CTimeEx& )" );
   Copy( source );
}

CTimeEx::CTimeEx( const CTimeEx * source )
{
   WFCLTRACEINIT( "CTimeEx::CTimeEx( CTimeEx * )" );
   Copy( source );
}

CTimeEx::CTimeEx( const time_t source )
{
   WFCLTRACEINIT( "CTimeEx::CTimeEx( time_t )" );
   Copy( source );
}

CTimeEx::CTimeEx( const struct tm * time_p )
{
   WFCLTRACEINIT( "CTimeEx::CTimeEx( struct tm * )" );
   Copy( time_p );
}

CTimeEx::CTimeEx( const struct tm& time_structure )
{
   WFCLTRACEINIT( "CTimeEx::CTimeEx( struct tm )" );
   Copy( time_structure );
}

CTimeEx::CTimeEx( int year, int month, int day, int hour, int minute, int second, int daylight_savings_time )
{
   WFCLTRACEINIT( "CTimeEx::CTimeEx( y, m, d, h, m, s, n )" );
   Set( year, month, day, hour, minute, second, daylight_savings_time );
}

CTimeEx::~CTimeEx()
{
   WFCLTRACEINIT( "CTimeEx::~CTimeEx()" );
   Empty();
}

int CTimeEx::Compare( const CTimeEx& source ) const
{
   WFCLTRACEINIT( "CTimeEx::Compare()" );

   if ( m_Time > source.m_Time )
   {
      // We are greater than source

      return( 1 );
   }

   if ( m_Time < source.m_Time )
   {
      // We are less than source

      return( -1 );
   }

   // We could be equal to source, need to go to the nanosecond level

   if ( m_Time > source.m_Time )
   {
      // We are greater than source

      return( 1 );
   }

   if ( m_Time < source.m_Time )
   {
      return( -1 );
   }

   // Welp, it looks like we're equal

   return( 0 );
}

void CTimeEx::Copy( const CTimeEx& source )
{
   WFCLTRACEINIT( "CTimeEx::Copy( CTimeEx& )" );
   m_Time  = source.m_Time;
}

void CTimeEx::Copy( const CTimeEx * source )
{
   WFCLTRACEINIT( "CTimeEx::Copy( CTimeEx * )" );

   // We were passed a pointer, don't trust it

   if ( source != NULL )
   {
      Copy( *source );
   }
   else
   {
      Empty();
   }
}

void CTimeEx::Copy( const time_t source )
{
   WFCLTRACEINIT( "CTimeEx::Copy( time_t )" );

   m_Time = source;
}

void CTimeEx::Copy( const struct tm * time_p )
{
   WFCLTRACEINIT( "CTimeEx::Copy( struct tm * )" );

   m_Time = m_Make_time_t( time_p );

   if ( m_Time == (-1) )
   {
      m_Time = 0;
   }
}

void CTimeEx::Copy( const struct tm& source )
{
   WFCLTRACEINIT( "CTimeEx::Copy( struct tm& )" );
   Copy( &source );
}

void CTimeEx::CopyModifiedJulianDate( double number_of_days_since_17_november_1858 )
{
   WFCLTRACEINIT( "CTimeEx::CopyModifiedJulianDate()" );

   double fractional_days = 0.0;
   double whole_days      = 0.0;

   fractional_days = modf( number_of_days_since_17_november_1858, &whole_days );

   whole_days -= 40587.0;

   // There are 40,587 days between 17 Nov 1858 and 01 Jan 1970
   // There are 86,400 seconds in one day

   double number_of_seconds_into_the_day = fractional_days * 86400.0;

   m_Time = (long) (whole_days * 86400.0);

   double whole_seconds = 0.0;
   double fractional_seconds = modf( number_of_seconds_into_the_day, &whole_seconds );

   m_Time += (long) whole_seconds;
}

void CTimeEx::CopyTo( CString& iso_8601_format_string ) const
{
   WFCLTRACEINIT( "CTimeEx::CopyTo( CString )" );

   iso_8601_format_string = Format( TEXT( "%Y-%m-%dT%H:%M:%S" ) );
   iso_8601_format_string += TEXT( "Z" );
}

void CTimeEx::CopyTo( struct tm& destination ) const
{
   WFCLTRACEINIT( "CTimeEx::CopyTo( struct tm )" );

   GreenwichMeanTime( &m_Time, &destination );
}

void CTimeEx::CopyTo( time_t& destination ) const
{
   WFCLTRACEINIT( "CTimeEx::CopyTo( time_t )" );
   destination = m_Time;
}

void CTimeEx::Empty( void )
{
   WFCLTRACEINIT( "CTimeEx::Empty()" );
   m_Time  = 0;
}

CString CTimeEx::Format( LPCTSTR format_string ) const
{
   WFCLTRACEINIT( "CTimeEx::Format()" );

   TCHAR buffer[ 4096 ];

   if ( format_string == NULL )
   {
      buffer[ 0 ] = 0x00;
      buffer[ 0 ] = 0x00;

      return( buffer );
   }

   struct tm time_structure;

   // We were passed a pointer, don't trust it

   ZeroMemory( buffer, sizeof( buffer ) );
   ZeroMemory( &time_structure, sizeof( time_structure ) );

   GreenwichMeanTime( &m_Time, &time_structure );

   _tcsftime( buffer, DIMENSION_OF( buffer ), format_string, &time_structure );

   return( buffer );
}

void CTimeEx::GetCurrentTheTime( CTimeEx& source )
{
   WFCLTRACEINIT( "CTimeEx::GetCurrentTime()" );

   struct tm time_structure;

   ZeroMemory( &time_structure, sizeof( time_structure ) );

   time_t current_time = (time_t) NULL;

   current_time = ::time( (time_t *) NULL );

   GreenwichMeanTime( &current_time, &time_structure );

   source.Copy( &time_structure );
}

int CTimeEx::GetDay( void ) const
{
   WFCLTRACEINIT( "CTimeEx::GetDay()" );

   struct tm time_structure;

   GetTime( time_structure );

   return( time_structure.tm_mday );
}

int CTimeEx::GetDayOfWeek( void ) const
{
   WFCLTRACEINIT( "CTimeEx::GetDayOfWeek()" );
   struct tm time_structure;

   GetTime( time_structure );

   return( time_structure.tm_wday + 1 );
}

int CTimeEx::GetDayOfYear( void ) const
{
   WFCLTRACEINIT( "CTimeEx::GetDayOfYear()" );
   struct tm time_structure;

   GetTime( time_structure );

   return( time_structure.tm_yday + 1 );
}

int CTimeEx::GetHour( void ) const
{
   WFCLTRACEINIT( "CTimeEx::GetHour()" );
   struct tm time_structure;

   GetTime( time_structure );

   return( time_structure.tm_hour );
}

int CTimeEx::GetMinute( void ) const
{
   WFCLTRACEINIT( "CTimeEx::GetMinute()" );
   struct tm time_structure;

   GetTime( time_structure );

   return( time_structure.tm_min );
}

int CTimeEx::GetMonth( void ) const
{
   WFCLTRACEINIT( "CTimeEx::GetMonth()" );
   struct tm time_structure;

   GetTime( time_structure );

   return( time_structure.tm_mon + 1 );
}

int CTimeEx::GetSecond( void ) const
{
   WFCLTRACEINIT( "CTimeEx::GetSecond()" );
   struct tm time_structure;

   GetTime( time_structure );

   return( time_structure.tm_sec );
}

time_t CTimeEx::GetTotalSeconds( void ) const
{
   WFCLTRACEINIT( "CTimeEx::GetTotalSeconds()" );
   return( m_Time );
}

void CTimeEx::GetTime( struct tm& time_structure ) const
{
   WFCLTRACEINIT( "CTimeEx::GetTime()" );

   GreenwichMeanTime( &m_Time, &time_structure );
}

int CTimeEx::GetYear( void ) const
{
   WFCLTRACEINIT( "CTimeEx:GetYear()" );

   struct tm time_structure;

   GetTime( time_structure );

   return( time_structure.tm_year + 1900 );
}

#define NUMBER_OF_SECONDS_IN_A_DAY           (24L * 60L * 60L)    /* secs   in a day */

#define NUMBER_OF_SECONDS_IN_A_YEAR          (365L *   NUMBER_OF_SECONDS_IN_A_DAY)    /* secs in a year */

#define NUMBER_OF_SECONDS_IN_FOUR_YEARS     (1461L *   NUMBER_OF_SECONDS_IN_A_DAY)   /* secs in a 4 year interval */

#define BASE_DAY_OF_THE_WEEK          4                    /* 01-01-70 was a Thursday */

void CTimeEx::GreenwichMeanTime( const time_t *time_t_pointer, struct tm * tm_structure_p )
{
   // This method is here because there is not a reliable gmtime() method for
   // all operating systems. Some aren't thread safe. The One of the standard
   // Unix thread safe versions is called gmtime_r() but this isn't present
   // on all of the Unixes.

   long calendar_time_to_convert = *time_t_pointer;

   int is_current_year_a_leap_year = 0;

   int temporary_time = 0;

   int days_in_a_year_by_month[ 13 ];

   if ( calendar_time_to_convert < 0L )
   {
      return;
   }

   /*
    * Determine years since 1970. First, identify the four-year interval
    * since this makes handling leap-years easy (note that 2000 IS a
    * leap year and 2100 is out-of-range).
    */

   temporary_time = (int) ( calendar_time_to_convert / NUMBER_OF_SECONDS_IN_FOUR_YEARS );

   calendar_time_to_convert -= ( (long) temporary_time * NUMBER_OF_SECONDS_IN_FOUR_YEARS );

   /*
    * Determine which year of the interval
    */

   temporary_time = ( temporary_time * 4 ) + 70;

   if ( calendar_time_to_convert >= NUMBER_OF_SECONDS_IN_A_YEAR )
   {
      temporary_time++;
      calendar_time_to_convert -= NUMBER_OF_SECONDS_IN_A_YEAR;

      if ( calendar_time_to_convert >= NUMBER_OF_SECONDS_IN_A_YEAR )
      {
         temporary_time++;
         calendar_time_to_convert -= NUMBER_OF_SECONDS_IN_A_YEAR;

         /*
          * Note, it takes 366 days-worth of seconds to get past a leap
          * year.
          */

         if ( calendar_time_to_convert >= ( NUMBER_OF_SECONDS_IN_A_YEAR + NUMBER_OF_SECONDS_IN_A_DAY ) )
         {
            temporary_time++;
            calendar_time_to_convert -= ( NUMBER_OF_SECONDS_IN_A_YEAR + NUMBER_OF_SECONDS_IN_A_DAY );
         }
         else
         {
            /*
             * In a leap year after all, set the flag.
             */

            is_current_year_a_leap_year++;
         }
      }
   }

   /*
    * temporary_time now holds the value for tm_year. calendar_time_to_convert now holds the
    * number of elapsed seconds since the beginning of that year.
    */

   tm_structure_p->tm_year = temporary_time;

   /*
    * Determine days since January 1 (0 - 365). This is the tm_yday value.
    * Leave calendar_time_to_convert with number of elapsed seconds in that day.
    */

   tm_structure_p->tm_yday = (int) ( calendar_time_to_convert / NUMBER_OF_SECONDS_IN_A_DAY );
   calendar_time_to_convert -= (long) ( tm_structure_p->tm_yday ) * NUMBER_OF_SECONDS_IN_A_DAY;

   /*
    * Determine months since January (0 - 11) and day of month (1 - 31)
    */

   if ( is_current_year_a_leap_year )
   {
      days_in_a_year_by_month[  0 ] = -1;
      days_in_a_year_by_month[  1 ] = 30;
      days_in_a_year_by_month[  2 ] = 59;
      days_in_a_year_by_month[  3 ] = 90;
      days_in_a_year_by_month[  4 ] = 120;
      days_in_a_year_by_month[  5 ] = 151;
      days_in_a_year_by_month[  6 ] = 181;
      days_in_a_year_by_month[  7 ] = 212;
      days_in_a_year_by_month[  8 ] = 243;
      days_in_a_year_by_month[  9 ] = 273;
      days_in_a_year_by_month[ 10 ] = 304;
      days_in_a_year_by_month[ 11 ] = 334;
      days_in_a_year_by_month[ 12 ] = 365;
   }
   else
   {
      days_in_a_year_by_month[  0 ] = -1;
      days_in_a_year_by_month[  1 ] = 30;
      days_in_a_year_by_month[  2 ] = 58;
      days_in_a_year_by_month[  3 ] = 89;
      days_in_a_year_by_month[  4 ] = 119;
      days_in_a_year_by_month[  5 ] = 150;
      days_in_a_year_by_month[  6 ] = 180;
      days_in_a_year_by_month[  7 ] = 211;
      days_in_a_year_by_month[  8 ] = 242;
      days_in_a_year_by_month[  9 ] = 272;
      days_in_a_year_by_month[ 10 ] = 303;
      days_in_a_year_by_month[ 11 ] = 333;
      days_in_a_year_by_month[ 12 ] = 364;
   }

   for ( temporary_time = 1 ; days_in_a_year_by_month[ temporary_time ] < tm_structure_p->tm_yday ; temporary_time++ )
   {
      ;
   }

   tm_structure_p->tm_mon = --temporary_time;

   tm_structure_p->tm_mday = tm_structure_p->tm_yday - days_in_a_year_by_month[ temporary_time ];

   /*
    * Determine days since Sunday (0 - 6)
    */

   tm_structure_p->tm_wday = ((int)( *time_t_pointer / NUMBER_OF_SECONDS_IN_A_DAY ) + BASE_DAY_OF_THE_WEEK ) % 7;

   /*
    *  Determine hours since midnight (0 - 23), minutes after the hour
    *  (0 - 59), and seconds after the minute (0 - 59).
    */

   tm_structure_p->tm_hour = (int) ( calendar_time_to_convert / 3600 );
   calendar_time_to_convert -= (long) tm_structure_p->tm_hour * 3600L;

   tm_structure_p->tm_min = (int) ( calendar_time_to_convert / 60 );
   tm_structure_p->tm_sec = (int) ( calendar_time_to_convert - (tm_structure_p->tm_min) * 60 );

   tm_structure_p->tm_isdst = 0;
}

time_t CTimeEx::m_Make_time_t( const struct tm *time_parameter )
{
/*
 * ChkAdd evaluates to TRUE if dest = src1 + src2 has overflowed
 */
#define ChkAdd(dest, src1, src2)   ( ((src1 >= 0L) && (src2 >= 0L) \
    && (dest < 0L)) || ((src1 < 0L) && (src2 < 0L) && (dest >= 0L)) )

/*
 * ChkMul evaluates to TRUE if dest = src1 * src2 has overflowed
 */
#define ChkMul(dest, src1, src2)   ( src1 ? (dest/src1 != src2) : 0 )

   long time_1 = 0;
   long time_2 = 0;
   long time_3 = 0;

   struct tm tm_time;

   ZeroMemory( &tm_time, sizeof( tm_time ) );

   tm_time.tm_year  = time_parameter->tm_year;
   tm_time.tm_mon   = time_parameter->tm_mon;
   tm_time.tm_mday  = time_parameter->tm_mday;
   tm_time.tm_hour  = time_parameter->tm_hour;
   tm_time.tm_min   = time_parameter->tm_min;
   tm_time.tm_sec   = time_parameter->tm_sec;
   tm_time.tm_isdst = time_parameter->tm_isdst;

   /*
    * First, make sure tm_year is reasonably close to being in range.
    */

   if ( ((time_1 = tm_time.tm_year) < 69L) || (time_1 > 139L) )
   {
      return( (time_t) -1 );
   }

   /*
    * Adjust month value so it is in the range 0 - 11. This is because
    * we don't know how many days are in months 12, 13, 14, etc.
    */

   if ( (tm_time.tm_mon < 0) || (tm_time.tm_mon > 11) )
   {
      /*
       * no danger of overflow because the range check above.
       */

      time_1 += (tm_time.tm_mon / 12);

      if ( (tm_time.tm_mon %= 12) < 0 )
      {
         tm_time.tm_mon += 12;
         time_1--;
      }

      /*
       * Make sure year count is still in range.
       */
      if ( (time_1 < 69) || (time_1 > 139) )
      {
         return( (time_t) -1 );
      }
   }

   /***** HERE: time_1 holds number of elapsed years *****/

   /*
    * Calculate days elapsed minus one, in the given year, to the given
    * month. Check for leap year and adjust if necessary.
    */

   const int days[ 13 ] = { -1, 30, 58, 89, 119, 150, 180, 211, 242, 272, 303, 333, 364 };

   time_2 = days[ tm_time.tm_mon ];

   if ( ! ( time_1 & 3 ) && ( tm_time.tm_mon > 1 ) )
   {
      time_2++;
   }

   /*
    * Calculate elapsed days since base date (midnight, 1/1/70, UTC)
    *
    *
    * 365 days for each elapsed year since 1970, plus one more day for
    * each elapsed leap year. no danger of overflow because of the range
    * check (above) on time_1.
    */

   time_3 = (time_1 - 70L) * 365L + ((time_1 - 1L) >> 2) - 17L;

   /*
    * elapsed days to current month (still no possible overflow)
    */

   time_3 += time_2;

   /*
    * elapsed days to current date. overflow is now possible.
    */

   time_1 = time_3 + (time_2 = (long)(tm_time.tm_mday));

   if ( ChkAdd( time_1, time_3, time_2 ) )
   {
      return( (time_1) -1 );
   }

   /***** HERE: time_1 holds number of elapsed days *****/

   /*
    * Calculate elapsed hours since base date
    */

   time_2 = time_1 * 24L;

   if ( ChkMul( time_2, time_1, 24L ) )
   {
      return( (time_1) -1 );
   }

   time_1 = time_2 + (time_3 = (long)tm_time.tm_hour);

   if ( ChkAdd( time_1, time_2, time_3 ) )
   {
      return( (time_1) -1 );
   }

   /***** HERE: time_1 holds number of elapsed hours *****/

   /*
    * Calculate elapsed minutes since base date
    */

   time_2 = time_1 * 60L;

   if ( ChkMul( time_2, time_1, 60L ) )
   {
      return( (time_1) -1 );
   }

   time_1 = time_2 + (time_3 = (long)tm_time.tm_min);

   if ( ChkAdd( time_1, time_2, time_3 ) )
   {
      return( (time_1) -1 );
   }

   /***** HERE: time_1 holds number of elapsed minutes *****/

   /*
    * Calculate elapsed seconds since base date
    */

   time_2 = time_1 * 60L;

   if ( ChkMul( time_2, time_1, 60L ) )
   {
      return( (time_t) -1 );
   }

   time_1 = time_2 + (time_3 = (long)tm_time.tm_sec);

   if ( ChkAdd( time_1, time_2, time_3 ) )
   {
      return( (time_t) -1 );
   }

   /***** HERE: time_1 holds number of elapsed seconds *****/

   return( (time_t) time_1 );
}

void CTimeEx::Set( int year, int month, int day, int hour, int minute, int second, int daylight_savings_time )
{
   WFCLTRACEINIT( "CTimeEx::Set()" );

   ASSERT( day   >= 1 && day   <= 31 );
   ASSERT( month >= 1 && month <= 12 );
   ASSERT( year  >= 1900 );

   struct tm tm_structure;

   ZeroMemory( &tm_structure, sizeof( tm_structure ) );

   tm_structure.tm_year  = year  - 1900;
   tm_structure.tm_mon   = month - 1;
   tm_structure.tm_mday  = day;
   tm_structure.tm_hour  = hour;
   tm_structure.tm_min   = minute;
   tm_structure.tm_sec   = second;
   tm_structure.tm_isdst = daylight_savings_time;

   m_Time  = m_Make_time_t( &tm_structure );

   if ( m_Time == (-1) )
   {
      m_Time  = 0;
   }
}

void CTimeEx::Set( const CString& iso_8601_string )
{
   WFCLTRACEINIT( "CTimeEx::Set( CString )" );

   // This routine is written for simplicity. This
   // means it is very long and slow. Yes, I could
   // write it to be faster but it wouldn't be as
   // easy to follow.

   Empty();

   CString temp_string( iso_8601_string );

   int year    = 0;
   int month   = 0;
   int day     = 0;
   int hours   = 0;
   int minutes = 0;
   int seconds = 0;

   unsigned long nanoseconds = 0;

   int string_length = temp_string.GetLength();

   if ( string_length < 4 )
   {
      WFCTRACE( TEXT( "Year has less than 4 digits" ) );
      return;
   }

   CString value;

   value = temp_string.Left( 4 );

   year = _ttoi( value );

   temp_string = temp_string.Right( temp_string.GetLength() - 4 );

   // Let's see if we should bail

   if ( temp_string.GetLength() == 0 )
   {
      WFCTRACE( TEXT( "Only year was specified" ) );

      // Yup, let's bail

      Set( year, 1, 1, 0, 0, 0 );
      return;
   }

   // The next character should be a -
   //     |
   //     v
   // 1963-05-02T21:30:01.45Z

   if ( temp_string.GetAt( 0 ) != '-' )
   {
      WFCTRACE( TEXT( "Separator between year and month is not a -" ) );
      return;
   }

   temp_string = temp_string.Right( temp_string.GetLength() - 1 );

   //      |
   //      v
   // 1963-05-02T21:30:01.45Z

   if ( temp_string.GetLength() == 0 )
   {
      // OK, sloppy date but we'll take it

      Set( year, 1, 1, 0, 0, 0 );
      return;
   }

   if ( temp_string.GetLength() < 2 )
   {
      WFCTRACE( TEXT( "Not enough digits to make up a month" ) );
      return;
   }

   value = temp_string.Left( 2 );

   temp_string = temp_string.Right( temp_string.GetLength() - 2 );

   month = _ttoi( value );

   // Now let's idiot proof the month

   if ( month < 1 || month > 12 )
   {
      WFCTRACEVAL( TEXT( "Invalid month of " ), month );
      return;
   }

   // Let's see if we should bail

   if ( temp_string.GetLength() == 0 )
   {
      WFCTRACE( TEXT( "Only year and month was specified" ) );

      // Yup, let's bail

      Set( year, month, 1, 0, 0, 0 );
      return;
   }

   // The next character should be a -
   //        |
   //        v
   // 1963-05-02T21:30:01.45Z

   if ( temp_string.GetAt( 0 ) != '-' )
   {
      WFCTRACE( TEXT( "Separator between month and day is not a -" ) );
      return;
   }

   temp_string = temp_string.Right( temp_string.GetLength() - 1 );

   if ( temp_string.GetLength() == 0 )
   {
      // OK, sloppy date but we'll take it

      Set( year, month, 1, 0, 0, 0 );
      return;
   }

   // We should now be sitting on the day
   //         |
   //         v
   // 1963-05-02T21:30:01.45Z

   if ( temp_string.GetLength() < 2 )
   {
      WFCTRACE( TEXT( "Not enough digits to make up a day" ) );
      return;
   }

   value = temp_string.Left( 2 );

   temp_string = temp_string.Right( temp_string.GetLength() - 2 );

   day = _ttoi( value );

   // Now let's idiot proof the day

   if ( day < 1 || day > 31 )
   {
      WFCTRACEVAL( TEXT( "Invalid day of " ), day );
      return;
   }

   // Let's see if we should bail

   if ( temp_string.GetLength() == 0 )
   {
      WFCTRACE( TEXT( "Only year, month and was specified" ) );

      // Yup, let's bail

      Set( year, month, day, 0, 0, 0 );
      return;
   }

   // The next character should be a T
   //           |
   //           v
   // 1963-05-02T21:30:01.45Z

   if ( temp_string.GetAt( 0 ) != 'T' )
   {
      WFCTRACE( TEXT( "Separator between day and hours is not a T" ) );
      return;
   }

   temp_string = temp_string.Right( temp_string.GetLength() - 1 );

   if ( temp_string.GetLength() == 0 )
   {
      // OK, sloppy date but we'll take it

      Set( year, month, day, 0, 0, 0 );
      return;
   }

   // We should now be sitting on the hours
   //            |
   //            v
   // 1963-05-02T21:30:01.45Z

   if ( temp_string.GetLength() < 2 )
   {
      WFCTRACE( TEXT( "Not enough digits for hours" ) );
      return;
   }

   value = temp_string.Left( 2 );

   hours = _ttoi( value );

   if ( hours > 24 )
   {
      WFCTRACEVAL( TEXT( "Invalid hours of " ), hours );
      return;
   }

   temp_string = temp_string.Right( temp_string.GetLength() - 2 );

   // Let's see if we're finished

   if ( temp_string.GetLength() == 0 )
   {
      Set( year, month, day, hours, 0, 0 );
      return;
   }

   // We should be at a colon
   //              |
   //              v
   // 1963-05-02T21:30:01.45Z

   if ( temp_string.Left( 1 ) != ':' )
   {
      WFCTRACE( TEXT( "Character between hours and minutes ain't a colon" ) );
      return;
   }

   temp_string = temp_string.Right( temp_string.GetLength() - 1 );

   if ( temp_string.GetLength() == 0 )
   {
      // Oddly formed but not illegal
      Set( year, month, day, hours, 0, 0 );
      return;
   }

   if ( temp_string.GetLength() < 2 )
   {
      WFCTRACE( TEXT( "Not enough characters to make minutes" ) );
      return;
   }

   value = temp_string.Left( 2 );

   minutes = _ttoi( value );

   if ( minutes > 59 )
   {
      WFCTRACEVAL( TEXT( "Invalid minutes of " ), minutes );
      return;
   }

   temp_string = temp_string.Right( temp_string.GetLength() - 2 );

   // Let's see if we are finished

   if ( temp_string.GetLength() == 0 )
   {
      Set( year, month, day, hours, minutes, 0 );
      return;
   }

   // We should be at another colon
   //                 |
   //                 v
   // 1963-05-02T21:30:01.45Z

   if ( temp_string.Left( 1 ) != ':' )
   {
      WFCTRACE( TEXT( "Character between minutes and seconds ain't a colon" ) );
      return;
   }

   temp_string = temp_string.Right( temp_string.GetLength() - 1 );

   if ( temp_string.GetLength() == 0 )
   {
      // Oddly formed but legal
      Set( year, month, day, hours, minutes, 0 );
      return;
   }

   // Now let's get them there seconds
   //                  |
   //                  v
   // 1963-05-02T21:30:01.45Z

   if ( temp_string.GetLength() < 2 )
   {
      // That ain't right
      WFCTRACE( TEXT( "There aren't enought digits for seconds" ) );
      return;
   }

   value = temp_string.Left( 2 );

   seconds = _ttoi( value );

   temp_string = temp_string.Right( temp_string.GetLength() - 2 );

   // Let's see if we're finished

   if ( temp_string.GetLength() == 0 )
   {
      Set( year, month, day, hours, minutes, seconds );
      return;
   }

   char character = (char) temp_string.GetAt( 0 );

   // Here's where it gets interesting, this can be the
   // end of the string or a fractional second

   if ( character == 'Z' )
   {
      // We be done
      Set( year, month, day, hours, minutes, seconds );
      return;
   }

   if ( character == '.' )
   {
      int character_index = temp_string.FindOneOf( TEXT( "Z+-" ) );

      if ( character_index == (-1) )
      {
         WFCTRACE( TEXT( "Ill formed fractional seconds" ) );
         return;
      }

      value = TEXT( "0." );
      value += temp_string.Left( character_index );

      double fractional_second = 0.0;

      fractional_second = _ttof( value );

      fractional_second *= (double) NUMBER_OF_NANOSECONDS_IN_ONE_SECOND;

      nanoseconds = (unsigned long) fractional_second;

      Set( year, month, day, hours, minutes, seconds, nanoseconds );

      temp_string = temp_string.Right( temp_string.GetLength() - character_index );
   }

   Set( year, month, day, hours, minutes, seconds, nanoseconds );

   if ( temp_string.GetLength() == 0 )
   {
      return;
   }

   //                       |
   //                       v
   // 1963-05-02T21:30:01.45Z

   if ( temp_string.GetAt( 0 ) == 'Z' )
   {
      return;
   }

   // OK, what's left must be a hour and minute offset

   //                       |
   //                       v
   // 1963-05-02T21:30:01.45-05:00

   if ( temp_string.GetLength() < 6 )
   {
      WFCTRACE( TEXT( "Screwed offset" ) );
      return;
   }

   //                          |
   //                          v
   // 1963-05-02T21:30:01.45-05:00

   if ( temp_string.GetAt( 3 ) != ':' )
   {
      WFCTRACE( TEXT( "Character between offset minutes and hours ain't :" ) );
      return;
   }

   int offset_hours   = 0;
   int offset_minutes = 0;

   offset_hours   = _ttoi( temp_string.Mid( 1, 2 ) );
   offset_minutes = _ttoi( temp_string.Mid( 4, 2 ) );

   CTimeSpan time_span( 0, offset_hours, offset_minutes, 0 );

   if ( temp_string.GetAt( 0 ) == '-' )
   {
      m_Time += time_span.GetTotalSeconds();
   }
   else
   {
      m_Time -= time_span.GetTotalSeconds();
   }
}

#endif // WFC_STL

// End of source

#if 0
<HTML>

<HEAD>
<TITLE>Zia Foundation Classes - CTimeEx</TITLE>
</HEAD>

<BODY>

<H1>CTimeEx : timespec </H1>

$Revision: 4 $

<BR><HR>

<H2>Description</H2>

This class extends the timespec data structure. It provides an easy way to deal
with time in C++. <B>CTimeEx</B> deals only in GMT time. If you want local time,
you will have to drop down to C.

<H2>Constructors</H2>

<DL COMPACT>

<DT><PRE><B>CTimeEx</B>()
<B>CTimeEx</B>( const CTimeEx&amp;    source )
<B>CTimeEx</B>( const CTimeEx *   source )
<B>CTimeEx</B>( const timespec&amp;   source )
<B>CTimeEx</B>( const timespec *  source )
<B>CTimeEx</B>( const time_t      source )
<B>CTimeEx</B>( const struct tm * source )
<B>CTimeEx</B>( const struct tm&amp;  source )
<B>CTimeEx</B>( int year,
       int month,
       int day,
       int hour,
       int minute,
       int second,
       unsigned long nanoseconds = 0,
       int daylight_savings_time = -1 )</PRE><DD>
Constructs the object in a whole bunch of different ways.
</DL>

<H2>Methods</H2>

<DL COMPACT>

<DT><PRE>int <B>Compare</B>( const CTimeEx&amp; source ) const</PRE><DD>
This method compares the current <B>CTimeEx</B> with a
<B>CTimeEx</B> passed. If the two are equal, the return value is zero.
If the current
<B>CTimeEx</B> is less than the <B>CTimeEx</B> passed as an argument,
the return value is 1. If the
current <B>CTimeEx</B> is less than the <B>CTimeEx</B>
passed as an argument, the return value is -1.

<DT><PRE>void <B>Copy</B>( const CTimeEx&amp;  source )
void <B>Copy</B>( const CTimeEx * source )</PRE><DD>
This method copies the contents of another <B>CTimeEx</B> object.

<DT><PRE>void <B>Copy</B>( const timespec&amp;  source )
void <B>Copy</B>( const timespec * source )</PRE><DD>
This method copies the contents of a timespec object.

<DT><PRE>void <B>Copy</B>( const time_t source )</PRE><DD>
This method copies the contents of a time_t object.

<DT><PRE>void <B>Copy</B>( const struct tm&amp;  source )
void <B>Copy</B>( const struct tm * source )</PRE><DD>
This method copies the contents of a tm structure.

<DT><PRE>void <B>CopyModifiedJulianDate</B>( double source )</PRE><DD>
Loads the data members based upon the Modified Julian Date (MJD).
MJD is the number of days since November 17, 1858. Why this date?
Why <B>NOT</B> this date?

<DT><PRE>void <B>CopyTo</B>( struct tm&amp; destination ) const
void <B>CopyTo</B>( time_t&amp; destination ) const
void <B>CopyTo</B>( timespec&amp; destination ) const
void <B>CopyTo</B>( <A HREF="CString.html">CString</A>&amp; iso_8601_string ) const</PRE><DD>
Copies the time from the <B>CTimeEx</B> to the destination specified.
If you copy to a <A HREF="CString.html">CString</A>, it will
be written in ISO8601 format.

<DT><PRE>void <B>Empty</B>( void )</PRE><DD>
This method zeroizes the data members.

<DT><PRE><A HREF="CString.html">CString</A> <B>Format</B>( const char *format_string ) const</PRE><DD>
This method lets you format the time into a string.
It uses the same arguments as <CODE>strftime()</CODE>.
The allowed percent codes are as follows:

<UL>
<LI><CODE>%%</CODE> - same as %
<LI><CODE>%a</CODE> - abbreviated weekday name
<LI><CODE>%A</CODE> - full weekday name
<LI><CODE>%b</CODE> - abbreviated month name
<LI><CODE>%B</CODE> - full month name
<LI><CODE>%c</CODE> - date and time
<LI><CODE>%C</CODE> - century number
<LI><CODE>%d</CODE> - day of month (01-31)
<LI><CODE>%D</CODE> - date as %m/%d/%y
<LI><CODE>%e</CODE> - day of month (single digits are preceeded by a space)
<LI><CODE>%h</CODE> - abbreviated month name
<LI><CODE>%H</CODE> - hour (00-23)
<LI><CODE>%I</CODE> - hour (01-12)
<LI><CODE>%j</CODE> - day number of year (001-366)
<LI><CODE>%KC</CODE> - appropriate date and time representation
<LI><CODE>%m</CODE> - month number (01-12)
<LI><CODE>%M</CODE> - minute (00-59)
<LI><CODE>%n</CODE> - same as new-line
<LI><CODE>%p</CODE> - AM or PM
<LI><CODE>%r</CODE> - time as %I:%M:%S [AM|PM]
<LI><CODE>%R</CODE> - time as %H:%M
<LI><CODE>%S</CODE> - seconds (00-61, allows for leap seconds)
<LI><CODE>%t</CODE> - same as tab
<LI><CODE>%T</CODE> - time as %H:%M:%S
<LI><CODE>%U</CODE> - week number of year (00-53) Sunday is first day of week 1
<LI><CODE>%w</CODE> - weekday number (0-6) Sunday = 0
<LI><CODE>%W</CODE> - week number of year (00-53), Monday is first day of week 1
<LI><CODE>%x</CODE> - date
<LI><CODE>%X</CODE> - time
<LI><CODE>%y</CODE> - year within century
<LI><CODE>%Y</CODE> - four digit year
<LI><CODE>%Z</CODE> - time zone name
</UL>

<DT><PRE>static void <B>GetCurrentTime</B>( CTimeEx&amp; time )</PRE><DD>
Retrieves the current time from the operating system.

<DT><PRE>int <B>GetDay</B>( void ) const</PRE><DD>Returns the day of the month (1-31).

<DT><PRE>int <B>GetDayOfWeek</B>( void ) const</PRE><DD>Returns the day of the week (1=Sunday).

<DT><PRE>int <B>GetDayOfYear</B>( void ) const</PRE><DD>Returns the day of the year (1-366).

<DT><PRE>int <B>GetHour</B>( void ) const</PRE><DD>Returns the hour of the day.

<DT><PRE>int <B>GetMinute</B>( void ) const</PRE><DD>Returns the minute of the hour.

<DT><PRE>int <B>GetMonth</B>( void ) const</PRE><DD>Returns the month of the year (1=January).

<DT><PRE>long <B>GetNanoseconds</B>( void ) const</PRE><DD>Returns the nanosecond part of the time.

<DT><PRE>int <B>GetSecond</B>( void ) const</PRE><DD>Returns the seconds in the minute.

<DT><PRE>struct tm * <B>GetTime</B>( struct tm * ) const</PRE><DD>
Returns a struct tm pointer that points to the time in GMT.

<DT><PRE>time_t <B>GetTotalSeconds</B>( void ) const</PRE><DD>Returns the total number of seconds in the time.

<DT><PRE>int <B>GetYear</B>( void ) const</PRE><DD>Returns the four digit year.

<DT><PRE>static void <B>GreenwichMeanTime</B>( const time_t * address_of_a_time_t, struct tm * address_of_a_tm_structure )</PRE><DD>
This a thread-safe and portable implementation of <CODE>gmtime()</CODE>
that will compile on all of the
standard Unixes. It converts a <CODE>time_t</CODE> to a <CODE>struct tm</CODE>.

<DT><PRE>void <B>Set</B>( int year, int month, int day, int hour, int minute, int second, unsigned long nanosecond = 0, int daylight_savings_time = -1 )
void <B>Set</B>( const <A HREF="CString.html">CString</A>&amp; iso_8601_date_string )</PRE><DD>
Allows you to set the individual year, month, day, hour,
minute, seconds and nanoseconds of the time. It will
also accept a string with a date in ISO8601 format.

</DL>

<H2>Operators</H2>

<DL COMPACT>

<DT><PRE>operator <B>time_t</B> ( void ) const</PRE></DD>
This allows you to use a <B>CTimeEx</B> anywhere you would need a
<B>time_t</B>.

<DT><PRE>operator <B>timespec *</B> ( void )</PRE><DD>
This allows you to use a <B>CTimeEx</B> anywhere you would need a
<B>timespec</B> pointer.

<DT><PRE>CTimeEx&amp; operator <B>=</B> ( const CTimeEx&amp; source )
CTimeEx&amp; operator <B>=</B> ( const timespec&amp; source )
CTimeEx&amp; operator <B>=</B> ( const time_t source )
CTimeEx&amp; operator <B>=</B> ( const struct tm&amp; source )</PRE><DD>
This allows you to copy various representations of time and put
them into a CTimeEx.

<DT><PRE>BOOL operator <B>==</B> ( const CTimeEx&amp; source ) const</PRE><DD>
This will return TRUE if this CTimeEx is equal to <CODE>source</CODE>.

<DT><PRE>BOOL operator <B>!=</B> ( const CTimeEx&amp; source ) const</PRE><DD>
This will return TRUE if this CTimeEx is
not equal to <CODE>source</CODE>.

<DT><PRE>BOOL operator <B>&gt;=</B> ( const CTimeEx&amp; source ) const</PRE><DD>
This will return TRUE if this CTimeEx is greater than or equal to
<CODE>source</CODE>.

<DT><PRE>BOOL operator <B>&lt;=</B> ( const CTimeEx&amp; source ) const</PRE><DD>
This will return TRUE if this <B>CTimeEx</B> is less than or equal to
<CODE>source</CODE>.

<DT><PRE>BOOL operator <B>&gt;</B> ( const CTimeEx&amp; source ) const</PRE><DD>
This will return TRUE if this CTimeEx is greater than <CODE>source</CODE>.

<DT><PRE>BOOL operator <B>&lt;</B> ( const CTimeEx&amp; source ) const</PRE><DD>
This will return TRUE if this CTimeEx is less than <CODE>source</CODE>.

<DT><PRE>CTimeEx operator <B>-</B> ( const <A HREF="CTimeSpan.html">CTimeSpan</A>&amp; value ) const
CTimeSpan operator <B>-</B> ( const CTimeEx&amp; source ) const</PRE><DD>
Allows you to subtract a time span from a CTimeEx.

<DT><PRE>CTimeEx operator <B>+</B> ( const <A HREF="CTimeSpan.html">CTimeSpan</A>&amp; value ) const</PRE><DD>
Allows you to add a time span to a CTimeEx.

<DT><PRE>const CTimeEx&amp; <B>+=</B> ( const <A HREF="CTimeSpan.html">CTimeSpan</A>&amp; value ) const</PRE><DD>
Allows you to increment this CTimeEx object by the amount of time in
<CODE>value</CODE>.

<DT><PRE>const CTimeEx&amp; <B>-=</B> ( const <A HREF="CTimeSpan.html">CTimeSpan</A>&amp; value ) cosnt</PRE><DD>
Allows you to decrement this CTimeEx object by the amount of time in <CODE>value</CODE>.

</DL>

<H2>Example</H2>

<PRE><CODE>void main()
{
   <A HREF="WfcTrace.htm">WFCTRACEINIT</A>( TEXT( &quot;main()&quot; ) );

   <A HREF="CTimeSpan.html">CTimeSpan</A> how_long_i_have_been_alive;

   <B>CTimeEx</B> current_time;

   <B>CTimeEx</B>::GetCurrentTime( current_time );

   <B>CTimeEx</B> my_birthday( 1963, 5, 2, 21, 22, 29, 1000000000 ); // 9:22.30pm, May 2, 1963

   how_long_i_have_been_alive = current_time - my_birthday;

   <A HREF="CString.html">CString</A> time_string;

   time_string = how_long_i_have_been_alive.Format( &quot;%D days, %H hours, %M minutes, %S seconds&quot; );

   printf( &quot;%s\n&quot;, (const char *) time_string );

   <A HREF="CTimeSpan.html">CTimeSpan</A> one_thousand_hours( 0, 1000, 0, 0 );

   current_time += one_thousand_hours;

   time_string = current_time.Format( &quot;%x %X&quot; );

   printf( &quot;A thousand hours from now is %s\n&quot;, (const char *) time_string );

   <A HREF="CString.html">CString</A> iso_date;

   current_time.CopyTo( iso_date );

   printf( &quot;Standard Date: %s\n&quot;, (const char *) iso_date );
}</CODE></PRE>

<H2>API&#39;s Used</H2>

<B>CTimeEx</B> uses the following API&#39;s:

<UL>
<LI>_tcsftime
<LI>time
</UL>

<HR>

Copyright, 2000, <A HREF="mailto:sam_blackburn@pobox.com">Samuel R. Blackburn</A>
</BODY>

</HTML>
#endif // 0
