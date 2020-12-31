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
** $Workfile: wfc_parse_iso_8601_string.cpp $
** $Revision: 7 $
** $Modtime: 1/24/00 6:11p $
** $Reuse Tracing Code: 1 $
*/

#if defined( _DEBUG ) && ! defined( WFC_STL )
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif // _DEBUG

static BOOL __parse_ymdhms( LPCTSTR time_string,
                            int&    year,
                            int&    month,
                            int&    day,
                            int&    hours,
                            int&    minutes,
                            int&    seconds,
                            TCHAR&  offset_character,
                            int&    offset_hours,
                            int&    offset_minutes )
{
   WFCLTRACEINIT( TEXT( "__parse_ymdhms()" ) );

   // Here's a sample ISO8601 date string
   //
   // 1969-07-20T22:56:15-04:00

   // Do a little idiot checking

   if ( time_string == NULL )
   {
      WFCTRACE( TEXT( "time string is NULL!" ) );
      return( FALSE );
   }

   // Start with some believable defaults

   year             = 0;
   month            = 1;
   day              = 1;
   hours            = 0;
   minutes          = 0;
   seconds          = 0;
   offset_character = TEXT( 'Z' );
   offset_hours     = 0;
   offset_minutes   = 0;

   // We were passed a pointer, don't trust it

   try
   {
      if ( _tcslen( time_string ) < 4 ) 
      {
         // There ain't enough characters to even attempt to parse

         WFCTRACE( TEXT( "Not enough character to even attempt to parse" ) );
         return( FALSE );
      }

      // OK, let's start parsing

      if ( _istdigit( time_string[ 0 ] ) == 0 )
      {
         WFCTRACE( TEXT( "First character is not a digit" ) );
         return( FALSE );
      }

      if ( _istdigit( time_string[ 1 ] ) == 0 )
      {
         WFCTRACE( TEXT( "Second character is not a digit" ) );
         return( FALSE );
      }

      if ( _istdigit( time_string[ 2 ] ) == 0 )
      {
         WFCTRACE( TEXT( "Third character is not a digit" ) );
         return( FALSE );
      }

      if ( _istdigit( time_string[ 3 ] ) == 0 )
      {
         WFCTRACE( TEXT( "Fourth character is not a digit" ) );
         return( FALSE );
      }

      // If we get here, it means we've got 4 good digits

      TCHAR temp_string[ 5 ];

      temp_string[ 0 ] = time_string[ 0 ];
      temp_string[ 1 ] = time_string[ 1 ];
      temp_string[ 2 ] = time_string[ 2 ];
      temp_string[ 3 ] = time_string[ 3 ];
      temp_string[ 4 ] = 0x00;

      year = _ttoi( temp_string );

      DWORD index = 4;

      // index should be pointing here
      //     |
      //     v
      // 1969-07-20T22:56:15-04:00

      if ( time_string[ index ] == 0x00 )
      {
         // We're at the end of the string

         return( TRUE );
      }

      if ( time_string[ index ] != TEXT( '-' ) )
      {
         WFCTRACE( TEXT( "The separator between year and month is not -" ) );
         return( FALSE );
      }

      index++;

      // index should be pointing here
      //      |
      //      v
      // 1969-07-20T22:56:15-04:00

      if ( time_string[ index ] == 0x00 )
      {
         // We're at the end of the string
         return( TRUE );
      }

      if ( _istdigit( time_string[ index ] ) == 0 )
      {
         WFCTRACE( TEXT( "First digit of month field isn't a digit at all" ) );
         return( FALSE );
      }

      index++;

      // index should be pointing here
      //       |
      //       v
      // 1969-07-20T22:56:15-04:00

      // This test is safe because we could be sitting on a NULL

      if ( _istdigit( time_string[ index ] ) == 0 )
      {
         WFCTRACE( TEXT( "Second digit of month field isn't a digit at all" ) );
         return( FALSE );
      }

      temp_string[ 0 ] = time_string[ index - 1 ];
      temp_string[ 1 ] = time_string[ index ];
      temp_string[ 2 ] = 0x00;

      month = _ttoi( temp_string );

      // Do a little idiot proofing

      if ( month < 1 || month > 12 )
      {
         WFCTRACE( TEXT( "Funky month" ) );
         return( FALSE );
      }

      index++;

      // index should be pointing here
      //        |
      //        v
      // 1969-07-20T22:56:15-04:00

      if ( time_string[ index ] == 0x00 )
      {
         return( TRUE );
      }

      if ( time_string[ index ] != TEXT( '-' ) )
      {
         WFCTRACE( TEXT( "The separator between month and day fields is not -" ) );
         return( FALSE );
      }

      index++;

      // index should be pointing here
      //         |
      //         v
      // 1969-07-20T22:56:15-04:00

      if ( time_string[ index ] == 0x00 )
      {
         // Odd, but not illegal
         return( TRUE );
      }

      if ( _istdigit( time_string[ index ] ) == 0 )
      {
         WFCTRACE( TEXT( "First digit of day field isn't a digit at all" ) );
         return( FALSE );
      }

      index++;

      // index should be pointing here
      //          |
      //          v
      // 1969-07-20T22:56:15-04:00

      // This test is safe because we could be sitting on a NULL

      if ( _istdigit( time_string[ index ] ) == 0 )
      {
         WFCTRACE( TEXT( "Second digit of month field isn't a digit at all" ) );
         return( FALSE );
      }

      temp_string[ 0 ] = time_string[ index - 1 ];
      temp_string[ 1 ] = time_string[ index ];

      // We don't need to set temp_string[ 2 ] because we did that at line 158 above

      day = _ttoi( temp_string );

      // Do a very little bit of error checking

      if ( day < 1 || day > 31 )
      {
         WFCTRACE( TEXT( "Funky day" ) );
         return( FALSE );
      }

      index++;

      // index should be pointing here
      //           |
      //           v
      // 1969-07-20T22:56:15-04:00

      if ( time_string[ index ] == 0x00 )
      {
         // Odd, but not illegal
         return( TRUE );
      }

      if ( time_string[ index ] != TEXT( 'T' ) )
      {
         WFCTRACE( TEXT( "Separator between date and time ain't T" ) );
         return( FALSE );
      }

      index++;

      // index should be pointing here
      //            |
      //            v
      // 1969-07-20T22:56:15-04:00

      if ( time_string[ index ] == 0x00 )
      {
         // Odd, but not illegal
         return( TRUE );
      }

      if ( _istdigit( time_string[ index ] ) == 0 )
      {
         WFCTRACE( TEXT( "First digit of hours field isn't a digit at all" ) );
         return( FALSE );
      }

      index++;

      // index should be pointing here
      //             |
      //             v
      // 1969-07-20T22:56:15-04:00

      // This test is safe because we could be sitting on a NULL

      if ( _istdigit( time_string[ index ] ) == 0 )
      {
         WFCTRACE( TEXT( "Second digit of month field isn't a digit at all" ) );
         return( FALSE );
      }

      temp_string[ 0 ] = time_string[ index - 1 ];
      temp_string[ 1 ] = time_string[ index ];

      // We don't need to set temp_string[ 2 ] because we did that at line 158 above

      hours = _ttoi( temp_string );

      index++;

      // index should be pointing here
      //              |
      //              v
      // 1969-07-20T22:56:15-04:00

      if ( time_string[ index ] == 0x00 )
      {
         // Odd, but not illegal
         return( TRUE );
      }

      if ( time_string[ index ] != TEXT( ':' ) )
      {
         WFCTRACE( TEXT( "Separator between hours and minutes ain't :" ) );
         return( FALSE );
      }

      index++;

      // index should be pointing here
      //               |
      //               v
      // 1969-07-20T22:56:15-04:00

      if ( time_string[ index ] == 0x00 )
      {
         // Odd, but not illegal
         return( TRUE );
      }

      if ( _istdigit( time_string[ index ] ) == 0 )
      {
         WFCTRACE( TEXT( "First digit of time ain't no digit" ) );
         return( FALSE );
      }

      index++;

      // index should be pointing here
      //                |
      //                v
      // 1969-07-20T22:56:15-04:00

      if ( _istdigit( time_string[ index ] ) == 0 )
      {
         WFCTRACE( TEXT( "First digit of time ain't no digit" ) );
         return( FALSE );
      }

      temp_string[ 0 ] = time_string[ index - 1 ];
      temp_string[ 1 ] = time_string[ index ];

      minutes = _ttoi( temp_string );

      index++;

      // index should be pointing here
      //                 |
      //                 v
      // 1969-07-20T22:56:15-04:00

      if ( time_string[ index ] == 0x00 )
      {
         return( TRUE );
      }

      if ( time_string[ index ] != TEXT( ':' ) )
      {
         WFCTRACE( TEXT( "Separator between minutes and seconds ain't :" ) );
         return( FALSE );
      }

      index++;

      // index should be pointing here
      //                  |
      //                  v
      // 1969-07-20T22:56:15-04:00

      if ( time_string[ index ] == 0x00 )
      {
         // Odd, but not illegal
         return( TRUE );
      }

      if ( _istdigit( time_string[ index ] ) == 0 )
      {
         WFCTRACE( TEXT( "First digit of seconds ain't no digit" ) );
         return( FALSE );
      }

      index++;

      // index should be pointing here
      //                   |
      //                   v
      // 1969-07-20T22:56:15-04:00

      if ( _istdigit( time_string[ index ] ) == 0 )
      {
         WFCTRACE( TEXT( "Second digit of seconds ain't no digit" ) );
         return( FALSE );
      }

      temp_string[ 0 ] = time_string[ index - 1 ];
      temp_string[ 1 ] = time_string[ index ];

      seconds = _ttoi( temp_string );

      index++;

      // index should be pointing here
      //                    |
      //                    v
      // 1969-07-20T22:56:15-04:00

      if ( time_string[ index ] == 0x00 ||
           time_string[ index ] == TEXT( 'Z' ) )
      {
         return( TRUE );
      }

      // OK, now is the time when parsing gets interesting
      // The current index may be sitting on a partial second.
      // Since CTime can't deal with partial seconds, we
      // will just skip that part entirely.

      if ( time_string[ index ] == TEXT( '.' ) )
      {
         index++;

         BOOL exit_loop = FALSE;

         while( exit_loop == FALSE )
         {
            if ( time_string[ index ] == 0x00 )
            {
               return( TRUE );
            }

            if ( _istdigit( time_string[ index ] ) == 0 )
            {
               exit_loop = TRUE;
            }
            else
            {
               index++;
            }
         }
      }

      // If we get here, we should be sitting on a Z, + or -

      if ( time_string[ index ] == TEXT( 'Z' ) )
      {
         return( TRUE );
      }

      if ( time_string[ index ] != TEXT( '+' ) &&
           time_string[ index ] != TEXT( '-' ) )
      {
         WFCTRACE( TEXT( "Time zone designator ain't beginning with + or -" ) );
         return( FALSE );
      }

      offset_character = time_string[ index ];

      index++;

      // index should be pointing here
      //                     |
      //                     v
      // 1969-07-20T22:56:15-04:00

      if ( _istdigit( time_string[ index ] ) == 0 )
      {
         WFCTRACE( TEXT( "first digit of hours offset ain't a digit" ) );
         return( FALSE );
      }

      index++;

      // index should be pointing here
      //                      |
      //                      v
      // 1969-07-20T22:56:15-04:00

      if ( _istdigit( time_string[ index ] ) == 0 )
      {
         WFCTRACE( TEXT( "second digit of hours offset ain't a digit" ) );
         return( FALSE );
      }

      temp_string[ 0 ] = time_string[ index - 1 ];
      temp_string[ 1 ] = time_string[ index ];

      offset_hours = _ttoi( temp_string );

      index++;

      // index should be pointing here
      //                       |
      //                       v
      // 1969-07-20T22:56:15-04:00

      if ( time_string[ index ] != TEXT( ':' ) )
      {
         WFCTRACE( TEXT( "Separator between offset hours and minutes ain't a :" ) );
         return( FALSE );
      }

      index++;

      // index should be pointing here
      //                        |
      //                        v
      // 1969-07-20T22:56:15-04:00

      if ( _istdigit( time_string[ index ] ) == 0 )
      {
         WFCTRACE( TEXT( "First digit of minutes offset ain't a digit" ) );
         return( FALSE );
      }

      index++;

      // index should be pointing here
      //                        |
      //                        v
      // 1969-07-20T22:56:15-04:00

      if ( _istdigit( time_string[ index ] ) == 0 )
      {
         WFCTRACE( TEXT( "Second digit of minutes offset ain't a digit" ) );
         return( FALSE );
      }

      temp_string[ 0 ] = time_string[ index - 1 ];
      temp_string[ 1 ] = time_string[ index ];

      offset_minutes = _ttoi( temp_string );

      return( TRUE );
   }
   catch( ... )
   {
      return( FALSE );
   }
}

BOOL PASCAL wfc_parse_iso_8601_string( LPCTSTR time_string, CFileTime& the_time )
{
   WFCLTRACEINIT( TEXT( "wfc_parse_iso_8601_string( CFileTime )" ) );

   the_time.Empty();

   CSystemTime system_time;

   if ( wfc_parse_iso_8601_string( time_string, system_time ) == FALSE )
   {
      return( FALSE );
   }

   the_time = system_time;

   return( TRUE );
}

#if ! defined( WFC_STL )

BOOL PASCAL wfc_parse_iso_8601_string( LPCTSTR time_string, COleDateTime& the_time )
{
   WFCLTRACEINIT( TEXT( "wfc_parse_iso_8601_string( COleDateTime )" ) );

   the_time = COleDateTime( static_cast< time_t >( 0 ) );

   // Do a little idiot checking

   if ( time_string == NULL )
   {
      WFCTRACE( TEXT( "time_string is NULL!" ) );
      return( FALSE );
   }

   int year    = 0;
   int month   = 0;
   int day     = 0;
   int hours   = 0;
   int minutes = 0;
   int seconds = 0;

   TCHAR offset_character = 0;

   int offset_hours   = 0;
   int offset_minutes = 0;

   if ( __parse_ymdhms( time_string, year, month, day, hours, minutes, seconds, offset_character, offset_hours, offset_minutes ) == FALSE )
   {
      WFCTRACE( TEXT( "Can't parse string" ) );
      return( FALSE );
   }

   the_time = COleDateTime( year, month, day, hours, minutes, seconds );

   if ( offset_character != TEXT( 'Z' ) )
   {
      COleDateTimeSpan time_zone_offset( 0, offset_hours, offset_minutes, 0 );

      if ( offset_character == TEXT( '-' ) )
      {
         the_time += time_zone_offset;
      }
      else if ( offset_character == TEXT( '+' ) )
      {
         the_time -= time_zone_offset;
      }
   }

   return( TRUE );
}

#endif // WFC_STL

BOOL PASCAL wfc_parse_iso_8601_string( LPCTSTR time_string, CSystemTime& the_time )
{
   WFCLTRACEINIT( TEXT( "wfc_parse_iso_8601_string( CSystemTime )" ) );

   the_time.Empty();

   // Do a little idiot checking

   if ( time_string == NULL )
   {
      WFCTRACE( TEXT( "time_string is NULL!" ) );
      return( FALSE );
   }

   int year    = 0;
   int month   = 0;
   int day     = 0;
   int hours   = 0;
   int minutes = 0;
   int seconds = 0;

   TCHAR offset_character = 0;

   int offset_hours   = 0;
   int offset_minutes = 0;

   if ( __parse_ymdhms( time_string, year, month, day, hours, minutes, seconds, offset_character, offset_hours, offset_minutes ) == FALSE )
   {
      WFCTRACE( TEXT( "Can't parse string" ) );
      return( FALSE );
   }

   CTime ole_time = CTime( year, month, day, hours, minutes, seconds );

   if ( offset_character != TEXT( 'Z' ) )
   {
      CTimeSpan time_zone_offset( 0, offset_hours, offset_minutes, 0 );

      if ( offset_character == TEXT( '-' ) )
      {
         ole_time += time_zone_offset;
      }
      else if ( offset_character == TEXT( '+' ) )
      {
         ole_time -= time_zone_offset;
      }
   }

   the_time = ole_time;

   return( TRUE );
}

BOOL PASCAL wfc_parse_iso_8601_string( LPCTSTR time_string, CTime& the_time )
{
   WFCLTRACEINIT( TEXT( "wfc_parse_iso_8601_string( CTime )" ) );

   the_time = CTime( static_cast< time_t >( 0 ) );

   // Do a little idiot checking

   if ( time_string == NULL )
   {
      WFCTRACE( TEXT( "time_string is NULL!" ) );
      return( FALSE );
   }

   int year    = 0;
   int month   = 0;
   int day     = 0;
   int hours   = 0;
   int minutes = 0;
   int seconds = 0;

   TCHAR offset_character = 0;

   int offset_hours   = 0;
   int offset_minutes = 0;

   if ( __parse_ymdhms( time_string, year, month, day, hours, minutes, seconds, offset_character, offset_hours, offset_minutes ) == FALSE )
   {
      WFCTRACE( TEXT( "Can't parse string" ) );
      return( FALSE );
   }

   the_time = CTime( year, month, day, hours, minutes, seconds );

   if ( offset_character != TEXT( 'Z' ) )
   {
      CTimeSpan time_zone_offset( 0, offset_hours, offset_minutes, 0 );

      if ( offset_character == TEXT( '-' ) )
      {
         the_time += time_zone_offset;
      }
      else if ( offset_character == TEXT( '+' ) )
      {
         the_time -= time_zone_offset;
      }
   }

   return( TRUE );
}

// End of source

#if 0
<HTML>

<HEAD>
<TITLE>WFC - wfc_parse_iso_8601_string</TITLE>
<META name="keywords" content="WFC, MFC extension library, freeware class library, Win32">
<META name="description" content="Simple C function that parses a time string (in ISO8601 format) into a CTime object.">
</HEAD>

<BODY>

<H1>wfc_parse_iso_8601_string</H1>
$Revision: 7 $<HR>

<H2>Declaration</H2>
<PRE>BOOL <B>wfc_parse_iso_8601_string</B>( LPCTSTR time_string, CFileTime&amp;    the_time )
BOOL <B>wfc_parse_iso_8601_string</B>( LPCTSTR time_string, COleDateTime&amp; the_time )
BOOL <B>wfc_parse_iso_8601_string</B>( LPCTSTR time_string, CSystemTime&amp;  the_time )
BOOL <B>wfc_parse_iso_8601_string</B>( LPCTSTR time_string, CTime&amp;        the_time )</PRE>

<H2>Description</H2>
This function parses <CODE>time_string</CODE> and puts the results into <CODE>the_time</CODE>.

<H2>Example</H2>

<PRE><CODE>void test_time( void )
{
   <A HREF="WfcTrace.htm">WFCTRACEINIT</A>( TEXT( &quot;test_time()&quot; ) );

   CTime the_time;

   if ( <B>wfc_parse_iso_8601_string</B>( the_time ) == FALSE )
   {
      _tprintf( TEXT( &quot;Can't parse\n&quot; ) );
   }
   else
   {
      _tprintf( TEXT( &quot;Parsed OK\n&quot; ) );
   }

}</CODE></PRE>

<H2>API's Used</H2>
<B>wfc_get_operating_system_version_string</B>() uses the following API's:
<UL>
<LI>GetVersionEx
</UL>

<HR><I>Copyright, 2000, <A HREF="mailto:wfc@pobox.com">Samuel R. Blackburn</A></I><BR>
$Workfile: wfc_parse_iso_8601_string.cpp $<BR>
$Modtime: 1/24/00 6:11p $
</BODY>

</HTML>
#endif
