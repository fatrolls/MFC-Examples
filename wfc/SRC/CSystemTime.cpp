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
** $Workfile: CSystemTime.cpp $
** $Revision: 27 $
** $Modtime: 1/17/00 9:25a $
** $Reuse Tracing Code: 1 $
*/

#if ! defined( WFC_STL )
#include <afxdisp.h> // for COleDateTime
#endif // WFC_STL

#if defined( _DEBUG ) && ! defined( WFC_STL )
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif // _DEBUG

// I found this algorithm on the net and converted it to a static inline
// Aaron Crane (aaron.crane@pobox.com) posted it originally, I fixed
// the 1752 problem myself. It seems no one knows about the days that 
// were dropped from September 1752. What are they teaching in schools
// these days?? This method uses Zeller's Conguruence.

static inline WORD __get_day_of_week( int year, int month, int day )
{
   if ( month <= 2 )
   {
      year++;
      month += 12;
   }

   DWORD day_of_week = 0;

   double term_1 = 0.0;

   term_1 = static_cast< double >( month + 1 ) * 3.0;
   term_1 /= 5.0;

   day_of_week  = ( day + ( month * 2 ) + static_cast< int >( term_1 ) + year + ( year / 4 ) );
   day_of_week -= ( year / 100 );
   day_of_week += ( year / 400 );
   day_of_week++;

   // Let's fix things for the Sept 3-13th that don't exist in 1752
   if ( year == 1752 )
   {
      if ( month < 9 )
      {
         day_of_week -= 10;
      }
      else if ( month == 9 )
      {
         if ( day <= 2 )
         {
            day_of_week -= 10;
         }
      }
   }
   else if ( year < 1752 )
   {
      day_of_week -= 10;
   }

   return( static_cast< WORD >( day_of_week % 7 ) );
}

CSystemTime::CSystemTime()
{
   Empty();
}

CSystemTime::CSystemTime( const CSystemTime& source )
{
   Copy( source );
}

CSystemTime::CSystemTime( const CFileTime& source )
{
   Copy( source );
}

CSystemTime::CSystemTime( const CTime& source )
{
   Copy( source );
}

#if ! defined( WFC_STL )

CSystemTime::CSystemTime( const COleDateTime& source )
{
   Copy( source );
}

#endif // WFC_STL

CSystemTime::CSystemTime( const FILETIME * source )
{
   Copy( source );
}

CSystemTime::CSystemTime( const SYSTEMTIME * source )
{
   Copy( source );
}

CSystemTime::CSystemTime( const TIME_OF_DAY_INFO * source )
{
   Copy( source );
}

CSystemTime::CSystemTime( const TIMESTAMP_STRUCT * source )
{
   Copy( source );
}

CSystemTime::~CSystemTime()
{
   Empty();
}

LONG CSystemTime::Compare( const CSystemTime& source ) const
{
   if ( wYear < source.wYear )
   {
      return( (-1) );
   }

   if ( wYear > source.wYear ) 
   {
      return( 1 );
   }

   if ( wMonth < source.wMonth )
   {
      return( (-1) );
   }

   if ( wMonth > source.wMonth ) 
   {
      return( 1 );
   }

   if ( wDay < source.wDay )
   {
      return( (-1) );
   }

   if ( wDay > source.wDay ) 
   {
      return( 1 );
   }

   if ( wHour < source.wHour )
   {
      return( (-1) );
   }

   if ( wHour > source.wHour ) 
   {
      return( 1 );
   }

   if ( wMinute < source.wMinute )
   {
      return( (-1) );
   }

   if ( wMinute > source.wMinute ) 
   {
      return( 1 );
   }

   if ( wSecond < source.wSecond )
   {
      return( (-1) );
   }

   if ( wSecond > source.wSecond ) 
   {
      return( 1 );
   }

   if ( wMilliseconds < source.wMilliseconds )
   {
      return( (-1) );
   }

   if ( wMilliseconds > source.wMilliseconds ) 
   {
      return( 1 );
   }

   return( 0 );
}

void CSystemTime::Copy( const CSystemTime& source )
{
   Copy( (const SYSTEMTIME *) &source );
}

void CSystemTime::Copy( const SYSTEMTIME * source )
{
   ASSERT( source != NULL );

   if ( source == (const SYSTEMTIME *) NULL )
   {
      Empty();
      return;
   }

   // We were passed a pointer, don't trust it

   try
   {
      wYear         = source->wYear;
      wMonth        = source->wMonth;
      wDay          = source->wDay;
      wDayOfWeek    = source->wDayOfWeek;
      wHour         = source->wHour;
      wMinute       = source->wMinute;
      wSecond       = source->wSecond;
      wMilliseconds = source->wMilliseconds;
   }
   catch( ... )
   {
      Empty();
   }
}

void CSystemTime::Copy( const CFileTime& source )
{
   Copy( (const FILETIME *) &source );
}

void CSystemTime::Copy( const FILETIME * source )
{
   ASSERT( source != NULL );

   if ( source == (const FILETIME *) NULL )
   {
      Empty();
      return;
   }

   // We were passed a pointer, don't trust it

   try
   {
      SYSTEMTIME system_time;

      if ( ::FileTimeToSystemTime( source, &system_time ) != FALSE )
      {
         Copy( &system_time );
      }
      else
      {
         Empty();
      }
   }
   catch( ... )
   {
      Empty();
   }
}

void CSystemTime::Copy( const CTime& source )
{
   wYear         = static_cast< WORD >( source.GetYear() );
   wMonth        = static_cast< WORD >( source.GetMonth() );
   wDay          = static_cast< WORD >( source.GetDay() );

   // CTime day of week says Sunday is day 1, SYSTEMTIME says Sunday is zero
   wDayOfWeek    = static_cast< WORD >( source.GetDayOfWeek() - 1 );
   wHour         = static_cast< WORD >( source.GetHour()   );
   wMinute       = static_cast< WORD >( source.GetMinute() );
   wSecond       = static_cast< WORD >( source.GetSecond() );
   wMilliseconds = 0;
}

#if ! defined( WFC_STL )

void CSystemTime::Copy( const COleDateTime& source )
{
   if ( source.GetStatus() != COleDateTime::valid )
   {
      Empty();
      return;
   }

   wYear         = static_cast< WORD >( source.GetYear() );
   wMonth        = static_cast< WORD >( source.GetMonth() );
   wDay          = static_cast< WORD >( source.GetDay() );

   // COleDateTime day of week says Sunday is day 1, SYSTEMTIME says Sunday is zero
   wDayOfWeek    = static_cast< WORD >( source.GetDayOfWeek() - 1 );
   wHour         = static_cast< WORD >( source.GetHour() );
   wMinute       = static_cast< WORD >( source.GetMinute() );
   wSecond       = static_cast< WORD >( source.GetSecond() );
   wMilliseconds = 0;
}

#endif // WFC_STL

void CSystemTime::Copy( const TIME_OF_DAY_INFO * source )
{
   ASSERT( source != NULL );

   if ( source == (const TIME_OF_DAY_INFO *) NULL )
   {
      Empty();
      return;
   }

   // We were passed a pointer, don't trust it

   try
   {
      wHour         = static_cast< WORD >( source->tod_hours );
      wMinute       = static_cast< WORD >( source->tod_mins  );
      wSecond       = static_cast< WORD >( source->tod_secs  );
      wDay          = static_cast< WORD >( source->tod_day   );
      wMonth        = static_cast< WORD >( source->tod_month );
      wYear         = static_cast< WORD >( source->tod_year  );
      wMilliseconds = static_cast< WORD >( source->tod_hunds * 10 );

      // Now let's set the day of week dude...

      CTime the_time;

      CopyTo( the_time );

      wDayOfWeek = static_cast< WORD >( the_time.GetDayOfWeek() - 1 );
   }
   catch( ... )
   {
      Empty();
   }
}

void CSystemTime::Copy( const TIMESTAMP_STRUCT * source )
{
   ASSERT( source != NULL );

   if ( source == (const TIMESTAMP_STRUCT *) NULL )
   {
      Empty();
      return;
   }

   // We were passed a pointer, don't trust it

   try
   {
      wYear         = static_cast< WORD >( source->year   );
      wMonth        = static_cast< WORD >( source->month  );
      wDay          = static_cast< WORD >( source->day    );
      wHour         = static_cast< WORD >( source->hour   );
      wMinute       = static_cast< WORD >( source->minute );
      wSecond       = static_cast< WORD >( source->second ); 
      wMilliseconds = static_cast< WORD >( source->fraction * 10 );

      wDayOfWeek = __get_day_of_week( wYear, wMonth, wDay );
   }
   catch( ... )
   {
      Empty();
   }
}

#if ! defined( WFC_STL )

void CSystemTime::CopyTo( COleDateTime& destination ) const
{
   destination = COleDateTime( wYear, wMonth, wDay, wHour, wMinute, wSecond );
}

#endif // WFC_STL

void CSystemTime::CopyTo( CTime& destination ) const
{
   destination = CTime( wYear, wMonth, wDay, wHour, wMinute, wSecond );
}

void CSystemTime::CopyTo( TIMESTAMP_STRUCT * destination ) const
{
   ASSERT( destination != NULL );

   if ( destination == (const TIMESTAMP_STRUCT *) NULL )
   {
      return;
   }

   // We were passed a pointer, don't trust it

   try
   {
      destination->year     = wYear;
      destination->month    = wMonth;
      destination->day      = wDay;
      destination->hour     = wHour;
      destination->minute   = wMinute;
      destination->second   = wSecond;
      destination->fraction = ( wMilliseconds / 10 );
   }
   catch( ... )
   {
      return;
   }
}

void CSystemTime::Empty( void )
{
   wYear         = 0;
   wMonth        = 0;
   wDay          = 0;
   wDayOfWeek    = 0;
   wHour         = 0;
   wMinute       = 0;
   wSecond       = 0;
   wMilliseconds = 0;
}

void CSystemTime::Get( void )
{
   Copy( GetTheCurrentTime() );
}

CSystemTime CSystemTime::GetTheCurrentTime( void )
{
   SYSTEMTIME system_time;

   ::GetSystemTime( &system_time );

   return( CSystemTime( &system_time ) );
}

BOOL CSystemTime::Set( void ) const
{
   WFCLTRACEINIT( TEXT( "CSystemTime::Set()" ) );

   if ( ::SetSystemTime( this ) == FALSE )
   {
      // Maybe we need to get permission...
      HANDLE token_handle = NULL;

      DWORD error_code = 0;

      if ( ::OpenProcessToken( ::GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &token_handle ) == FALSE )
      {
         error_code = ::GetLastError();
         WFCTRACE( TEXT( "Can't OpenProcessToken" ) );
         WFCTRACEERROR( error_code );
         return( FALSE );
      }

      TOKEN_PRIVILEGES token_privileges;

      ::ZeroMemory( &token_privileges, sizeof( token_privileges ) );

      if ( ::LookupPrivilegeValue( NULL, SE_SYSTEMTIME_NAME, &token_privileges.Privileges[ 0 ].Luid ) == FALSE )
      {
         error_code = ::GetLastError();
         WFCTRACE( TEXT( "Can't LookupPrivilegeValue for local machine" ) );
         WFCTRACEERROR( error_code );
         ::wfc_close_handle( token_handle );
         token_handle = NULL;
         return( FALSE );
      }

      token_privileges.PrivilegeCount             = 1;
      token_privileges.Privileges[ 0 ].Attributes = SE_PRIVILEGE_ENABLED;

      if ( ::AdjustTokenPrivileges( token_handle, FALSE, &token_privileges, 0, (PTOKEN_PRIVILEGES) NULL, 0 ) == FALSE )
      {
         error_code = ::GetLastError();
         WFCTRACE( TEXT( "Can't AdjustTokenPrivileges" ) );
         WFCTRACEERROR( error_code );
         ::wfc_close_handle( token_handle );
         token_handle = NULL;
         return( FALSE );
      }

      // Finally, let's get around to setting the time

      if ( ::SetSystemTime( this ) == FALSE )
      {
         error_code = ::GetLastError();
         WFCTRACE( TEXT( "Can't SetSystemTime" ) );
         WFCTRACEERROR( error_code );
         ::wfc_close_handle( token_handle );
         token_handle = NULL;
         return( FALSE );
      }

      ::wfc_close_handle( token_handle );
      token_handle = NULL;
      return( TRUE );
   }

   return( FALSE );
}

/*
** Operators
*/

CSystemTime& CSystemTime::operator = ( const CSystemTime& source )
{
   Copy( source );
   return( *this );
}

CSystemTime& CSystemTime::operator = ( const CFileTime& source )
{
   Copy( source );
   return( *this );
}

CSystemTime& CSystemTime::operator = ( const CTime& source )
{
   Copy( source );
   return( *this );
}

#if ! defined( WFC_STL )

CSystemTime& CSystemTime::operator = ( const COleDateTime& source )
{
   Copy( source );
   return( *this );
}

#endif // WFC_STL

BOOL CSystemTime::operator == ( const CSystemTime& source ) const
{
   if ( Compare( source ) == 0 )
   {
      return( TRUE );
   }
   else
   {
      return( FALSE );
   }
}

BOOL CSystemTime::operator > ( const CSystemTime& source ) const
{
   if ( Compare( source ) > 0 )
   {
      return( TRUE );
   }
   else
   {
      return( FALSE );
   }
}

BOOL CSystemTime::operator < ( const CSystemTime& source ) const
{
   if ( Compare( source ) < 0 )
   {
      return( TRUE );
   }
   else
   {
      return( FALSE );
   }
}

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

void CSystemTime::Dump( CDumpContext& dump_context ) const
{
   LPCTSTR months[ 12 ] = { TEXT( "(January)"   ),
                            TEXT( "(February)"  ),
                            TEXT( "(March)"     ),
                            TEXT( "(April)"     ),
                            TEXT( "(May)"       ),
                            TEXT( "(June)"      ),
                            TEXT( "(July)"      ),
                            TEXT( "(August)"    ),
                            TEXT( "(September)" ),
                            TEXT( "(October)"   ),
                            TEXT( "(November)"  ),
                            TEXT( "(December)"  )
                          };

   LPCTSTR days[ 7 ] = { TEXT( "(Sunday)"    ),
                         TEXT( "(Monday)"    ),
                         TEXT( "(Tuesday)"   ),
                         TEXT( "(Wednesday)" ),
                         TEXT( "(Thursday)"  ),
                         TEXT( "(Friday)"    ),
                         TEXT( "(Saturday)"  )
                       };

   dump_context << TEXT( "a CSystemTime at " ) << (VOID *) this << TEXT( "\n{\n" );
   dump_context << TEXT( "   wYear is  " ) << wYear << TEXT( "\n" );
   dump_context << TEXT( "   wMonth is " ) << wMonth;

   if ( wMonth > 0 && wMonth < 13 )
   {
      dump_context << TEXT( " " ) << months[ wMonth - 1 ] << TEXT( "\n" );
   }
   else
   {
      dump_context << TEXT( " (Invalid)\n" );
   }

   dump_context << TEXT( "   wDayOfWeek is " ) << wDayOfWeek;

   if ( wDayOfWeek < 7 )
   {
      dump_context << TEXT( " " ) << days[ wDayOfWeek ] << TEXT( "\n" );
   }
   else
   {
      dump_context << TEXT( " (Invalid)\n" );
   }

   dump_context << TEXT( "   wDay          is " ) << wDay          << TEXT( "\n" );
   dump_context << TEXT( "   wHour         is " ) << wHour         << TEXT( "\n" );
   dump_context << TEXT( "   wMinute       is " ) << wMinute       << TEXT( "\n" );
   dump_context << TEXT( "   wSecond       is " ) << wSecond       << TEXT( "\n" );
   dump_context << TEXT( "   wMilliseconds is " ) << wMilliseconds << TEXT( "\n" );
   dump_context << TEXT( "}\n" );
}

#endif // _DEBUG

// End of source

#if 0
<HTML>

<HEAD>
<TITLE>WFC - CSystemTime</TITLE>
<META name="keywords" content="WFC, MFC extension library, freeware class library, Win32, source code">
<META name="description" content="The C++ class that lets you set the clock in NT.">
</HEAD>

<BODY>

<H1>CSystemTime : SYSTEMTIME</H1>
$Revision: 27 $<BR><HR>

<H2>Description</H2>
This class encapsulates the SYSTEMTIME data structure in Win32. The benefit
from doing this is adding capability to convert between a bunch of time 
representations.

<H2>Constructors</H2>

<DL COMPACT>

<DT><PRE><B>CSystemTime</B>()
<B>CSystemTime</B>( const COleDateTime&amp; source )
<B>CSystemTime</B>( const CSystemTime&amp; source )
<B>CSystemTime</B>( const <A HREF="CFileTime.htm">CFileTime</A>&amp; source )
<B>CSystemTime</B>( const CTime&amp; source )
<B>CSystemTime</B>( const SYSTEMTIME * source )
<B>CSystemTime</B>( const FILETIME * source )
<B>CSystemTime</B>( const TIME_OF_DAY_INFO * source )
<B>CSystemTime</B>( const TIMESTAMP_STRUCT * source )</PRE><DD>
Constructs the object.
The constructor that takes a COleDateTime parameter is not present
in STL builds.

</DL>

<H2>Data Members</H2>

Whatever is in SYSTEMTIME.

<H2>Methods</H2>

<DL COMPACT>

<DT><PRE>LONG <B>Compare</B>( const CSystemTime&amp; source )</PRE><DD>
Returns the same values as CString::Compare().

<DT><PRE>void <B>Copy</B>( const COleDateTime&amp; source )
void <B>Copy</B>( const CSystemTime&amp; source )
void <B>Copy</B>( const <A HREF="CFileTime.htm">CFileTime</A>&amp; source )
void <B>Copy</B>( const CTime&amp; source )
void <B>Copy</B>( const SYSTEMTIME * source )
void <B>Copy</B>( const FILETIME * source )
void <B>Copy</B>( const TIME_OF_DAY_INFO * source )
void <B>Copy</B>( const TIMESTAMP_STRUCT * source )</PRE><DD>
Sets the time to what you specify, you can copy
another
<A HREF="CFileTime.htm">CFileTime</A>, <B>CSystemTime</B>, FILETIME,
SYSTEMTIME or TIME_OF_DAY_INFO.

<DT><PRE>void <B>CopyTo</B>( COleDateTime&amp; destination ) const
void <B>CopyTo</B>( CTime&amp; destination ) const
void <B>CopyTo</B>( TIMESTAMP_STRUCT * destination )</PRE>
Copies the date/time out to the various types.

<DT><PRE>void <B>Empty</B>( void )</PRE><DD>Clears the data members.

<DT><PRE>void <B>Get</B>( void )</PRE><DD>
Retrieves the current time and stores in in the object.

<DT><PRE>static CSystemTime <B>GetTheCurrentTime</B>( void )</PRE><DD>
I would have liked to call this function <B>GetCurrentTime</B>() but Microsoft
screwed me in the winbase.h file with a #define. Oh well, that's life.
This method retrieves the current time and returns it as a <B>CSystemTime</B>
object.

<DT><PRE>BOOL <B>Set</B>( void ) const</PRE><DD>
Sets the computer's clock equal to the time stored in this object.

</DL>

<H2>Example</H2>
<PRE><CODE>#include &lt;wfc.h&gt;
#pragma hdrstop

int _tmain( int number_of_command_line_arguments, LPCTSTR command_line_arguments[] )
{
   <A HREF="WfcTrace.htm">WFCTRACEINIT</A>( TEXT( &quot;_tmain()&quot; ) );

   <B>CSystemTime</B> the_time;

   the_time.Get(); // Get the current time

   the_time.wHour++;

   if ( the_time.Set() != FALSE )
   {
      _tprintf( TEXT( &quot;Time advanced by one hour\n&quot; ) );
   }
   else
   {
      _tprintf( TEXT( &quot;Can't adjust time\n&quot; ) );
   }
}</CODE></PRE>

<H2>API's Used</H2>

<UL>
<LI>AdjustTokenPrivileges
<LI>FileTimeToSystemTime
<LI>GetSystemTime
<LI>LookupPrivilegeValue
<LI>OpenProcessToken
<LI>SetSystemTime
<LI>ZeroMemory
</UL>

<HR><I>Copyright, 2000, <A HREF="mailto:wfc@pobox.com">Samuel R. Blackburn</A></I><BR>
$Workfile: CSystemTime.cpp $<BR>
$Modtime: 1/17/00 9:25a $
</BODY>

</HTML>
#endif
