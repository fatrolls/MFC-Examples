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
** $Workfile: CFileTime.CPP $
** $Revision: 28 $
** $Modtime: 1/04/00 5:11a $
** $Reuse Tracing Code: 1 $
*/

#if defined( _DEBUG ) && ! defined( WFC_STL )
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif // _DEBUG

CFileTime::CFileTime()
{
   Empty();
}

CFileTime::CFileTime( const CFileTime& source )
{
   Copy( source );
}

CFileTime::CFileTime( const CSystemTime& source )
{
   Copy( source );
}

CFileTime::CFileTime( const FILETIME * source )
{
   Copy( source );
}

CFileTime::CFileTime( const SYSTEMTIME * source )
{
   Copy( source );
}

CFileTime::CFileTime( WORD ms_dos_date, WORD ms_dos_time )
{
   Copy( ms_dos_date, ms_dos_time );
}

CFileTime::~CFileTime()
{
   Empty();
}

LONG CFileTime::Compare( const CFileTime& source ) const
{
   // David LeBlanc (whisper@accessone.com) had problems with VC4.2
   // not compiling dynamic_cast's correctly. That is why the old-style
   // casts are used here.
   // 1998-08-19
   return( ::CompareFileTime( (const FILETIME *) this, (const FILETIME *) &source ) );
}

void CFileTime::Copy( const CFileTime& source )
{
   // David LeBlanc (whisper@accessone.com) had problems with VC4.2
   // not compiling dynamic_cast's correctly. That is why the old-style
   // casts are used here.
   // 1998-08-19
   Copy( (const FILETIME *) &source );
}

void CFileTime::Copy( const CSystemTime& source )
{
   // David LeBlanc (whisper@accessone.com) had problems with VC4.2
   // not compiling dynamic_cast's correctly. That is why the old-style
   // casts are used here.
   // 1998-08-19
   Copy( (const SYSTEMTIME *) &source );
}

void CFileTime::Copy( const FILETIME * source )
{
   ASSERT( source != NULL );

   // Copying ourself is a silly thing to do

   if ( source == this )
   {
      return;
   }

   if ( source == NULL )
   {
      Empty();
      return;
   }

   // We were passed a pointer, don't trust it

   try
   {
      dwLowDateTime  = source->dwLowDateTime;
      dwHighDateTime = source->dwHighDateTime;
   }
   catch( ... )
   {
      Empty();
      return;
   }
}

void CFileTime::Copy( const SYSTEMTIME * source )
{
   ASSERT( source != NULL );

   if ( source == (const SYSTEMTIME *) NULL )
   {
      Empty();
      return;
   }

   FILETIME file_time;

   // We were passed a pointer, don't trust it

   try
   {
      if ( ::SystemTimeToFileTime( source, &file_time ) != FALSE )
      {
         Copy( &file_time );
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

void CFileTime::Copy( WORD ms_dos_date, WORD ms_dos_time )
{
   FILETIME file_time;

   if ( ::DosDateTimeToFileTime( ms_dos_date, ms_dos_time, &file_time ) != FALSE )
   {
      Copy( &file_time );
   }
   else
   {
      Empty();
   }
}

#if ! defined( WFC_STL )

void CFileTime::CopyTo( COleDateTime& destination ) const
{
   CSystemTime system_time( this );

   system_time.CopyTo( destination );
}

#endif // WFC_STL

void CFileTime::CopyTo( CTime& destination ) const
{
   CSystemTime system_time( this );

   system_time.CopyTo( destination );
}

void CFileTime::Empty( void )
{
   dwLowDateTime  = 0;
   dwHighDateTime = 0;
}

/*
** Operators
*/

CFileTime& CFileTime::operator = ( const CFileTime& source )
{
   Copy( source );
   return( *this );
}

CFileTime& CFileTime::operator = ( const CSystemTime& source )
{
   Copy( source );
   return( *this );
}

BOOL CFileTime::operator == ( const CFileTime& source ) const
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

BOOL CFileTime::operator < ( const CFileTime& source ) const
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

BOOL CFileTime::operator > ( const CFileTime& source ) const
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

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

void CFileTime::Dump( CDumpContext& dump_context ) const
{
   dump_context << TEXT( "a CFileTime at " ) << (VOID *) this << TEXT( "\n{\n" );
   dump_context << TEXT( "   dwLowDateTime is  " ) << dwLowDateTime  << TEXT( "\n" );
   dump_context << TEXT( "   dwHighDateTime is " ) << dwHighDateTime << TEXT( "\n" );
   dump_context << TEXT( "}\n" );
}

#endif // _DEBUG

// End of source

#if 0
<HTML>

<HEAD>
<TITLE>WFC - CFileTime</TITLE>
<META name="keywords" content="WFC, MFC extension library, freeware class library, Win32">
<META name="description" content="The C++ class that handles Win32 file timestamps.">
</HEAD>

<BODY>

<H1>CFileTime : FILETIME</H1>

$Revision: 28 $<BR>

<HR>

<H2>Description</H2>

This class encapsulates the FILETIME data structure in Win32. The benefit
from doing this is adding capability to convert between tons of other
time types.

<H2>Data Members</H2>
Whatever is in FILETIME.

<H2>Constructors</H2>

<DL COMPACT>

<DT><PRE><B>CFileTime</B>()
<B>CFileTime</B>( const CFileTime&amp; source )
<B>CFileTime</B>( const <A HREF="CSystemTime.htm">CSystemTime</A>&amp; source )
<B>CFileTime</B>( WORD ms_dos_date, WORD ms_dos_time )
<B>CFileTime</B>( const FILETIME * source )
<B>CFileTime</B>( const SYSTEMTIME * source )</PRE><DD>
These should just about do the job of constructing a new CFileTime.

</DL>

<H2>Methods</H2>

<DL COMPACT>

<DT><PRE>LONG <B>Compare</B>( const CFileTime&amp; source )</PRE><DD>
Returns the same values as CString::Compare().

<DT><PRE>void <B>Copy</B>( const CFileTime&amp; source )
void <B>Copy</B>( const <A HREF="CSystemTime.htm">CSystemTime</A>&amp; source )
void <B>Copy</B>( WORD ms_dos_date, WORD ms_dos_time )
void <B>Copy</B>( const FILETIME * source )
void <B>Copy</B>( const SYSTEMTIME * source )</PRE><DD>
Sets the time to what you specify, you can copy
another CFileTime, CSystemTime, FILETIME, SYSTEMTIME or an MS-DOS date/time.

<DT><PRE>void <B>Empty</B>( void )</PRE><DD>Clears the data members.

</DL>

<H2>Example</H2>

<PRE><CODE>Sorry.</CODE></PRE>

<H2>API's Used</H2>

<B>CFileTime</B> uses the following API's:

<UL>
<LI>CompareFileTime
<LI>DosDateTimeToFileTime
<LI>SystemTimeToFileTime
</UL>

<HR><I>Copyright, 2000, Samuel R. Blackburn</I><BR>
$Workfile: CFileTime.CPP $<BR>
$Modtime: 1/04/00 5:11a $
</BODY>

</HTML>
#endif
