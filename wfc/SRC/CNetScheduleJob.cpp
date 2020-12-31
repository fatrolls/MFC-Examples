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
** $Workfile: CNetScheduleJob.cpp $
** $Revision: 9 $
** $Modtime: 1/04/00 5:16a $
** $Reuse Tracing Code: 1 $
*/

#if defined( _DEBUG ) && ! defined( WFC_STL )
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

#if ! defined(  WFC_NO_SERIALIZATION )
IMPLEMENT_SERIAL( CNetworkScheduleJob, CObject, 1 )
#endif // WFC_NO_SERIALIZATION

#if defined( _DEBUG ) && ! defined( WFC_STL )
#define new DEBUG_NEW
#endif // _DEBUG

/*
** CNetworkScheduleJob stuff
*/

CNetworkScheduleJob::CNetworkScheduleJob()
{
   WFCLTRACEINIT( TEXT( "CNetworkScheduleJob::CNetworkScheduleJob()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   m_Initialize();
}

CNetworkScheduleJob::CNetworkScheduleJob( const AT_ENUM *source )
{
   WFCLTRACEINIT( TEXT( "CNetworkScheduleJob::CNetworkScheduleJob( AT_ENUM )" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   Copy( source );
}

CNetworkScheduleJob::CNetworkScheduleJob( const AT_INFO *source )
{
   WFCLTRACEINIT( TEXT( "CNetworkScheduleJob::CNetworkScheduleJob( AT_ENUM )" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   Copy( source );
}

CNetworkScheduleJob::CNetworkScheduleJob( const CNetworkScheduleJob& source )
{
   WFCLTRACEINIT( TEXT( "CNetworkScheduleJob::CNetworkScheduleJob( CNetworkFileInformation )" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   Copy( source );
}

CNetworkScheduleJob::~CNetworkScheduleJob()
{
   WFCLTRACEINIT( TEXT( "CNetworkScheduleJob::~CNetworkScheduleJob()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   m_Initialize();
}

void CNetworkScheduleJob::Copy( const AT_ENUM *source )
{
   WFCLTRACEINIT( TEXT( "CNetworkScheduleJob::Copy( AT_ENUM )" ) );
   ASSERT( source != NULL );

   if ( source == NULL )
   {
      m_Initialize();
      return;
   }

   // We were passed a pointer, don't trust it

   try
   {
      ID                               = source->JobId;
      NumberOfMillisecondsFromMidnight = source->JobTime;
      DaysOfTheMonth                   = source->DaysOfMonth;
      DaysOfTheWeek                    = source->DaysOfWeek;
      Flags                            = source->Flags;

#if defined( UNICODE )
      Command = source->Command;
#else

      // These strings are UNICODE.
      WCHAR unicode_string[ 4096 ];

      ZeroMemory( unicode_string, sizeof( unicode_string ) );

      wcsncpy( unicode_string, source->Command, DIMENSION_OF( unicode_string ) - 1 );

      char ascii_string[ 4096 ];

      ZeroMemory( ascii_string, sizeof( ascii_string ) );

      ::UNICODE_to_ASCII( unicode_string, ascii_string );

      Command = ascii_string;
#endif // UNICODE
   }
   catch( ... )
   {
      m_Initialize();
      return;
   }
}

void CNetworkScheduleJob::Copy( const AT_INFO *source )
{
   WFCLTRACEINIT( TEXT( "CNetworkScheduleJob::Copy( AT_INFO )" ) );
   ASSERT( source != NULL );

   if ( source == NULL )
   {
      m_Initialize();
      return;
   }

   // We were passed a pointer, don't trust it

   try
   {
      ID                               = 0;
      NumberOfMillisecondsFromMidnight = source->JobTime;
      DaysOfTheMonth                   = source->DaysOfMonth;
      DaysOfTheWeek                    = source->DaysOfWeek;
      Flags                            = source->Flags;

#if defined( UNICODE )
      Command = source->Command;
#else

      // These strings are UNICODE.
      WCHAR unicode_string[ 4096 ];

      ZeroMemory( unicode_string, sizeof( unicode_string ) );

      wcsncpy( unicode_string, source->Command, DIMENSION_OF( unicode_string ) - 1 );

      char ascii_string[ 4096 ];

      ZeroMemory( ascii_string, sizeof( ascii_string ) );

      ::UNICODE_to_ASCII( unicode_string, ascii_string );

      Command = ascii_string;
#endif // UNICODE
   }
   catch( ... )
   {
      m_Initialize();
      return;
   }
}

void CNetworkScheduleJob::Copy( const CNetworkScheduleJob& source )
{
   WFCLTRACEINIT( TEXT( "CNetworkScheduleJob::Copy()" ) );
   ASSERT( this != &source );

   /*
   ** Make sure we ain't copying ourselves
   */

   if ( this == &source )
   {
      return;
   }

   ID                               = source.ID;
   NumberOfMillisecondsFromMidnight = source.NumberOfMillisecondsFromMidnight;
   DaysOfTheMonth                   = source.DaysOfTheMonth;
   DaysOfTheWeek                    = source.DaysOfTheWeek;
   Flags                            = source.Flags;
   Command                          = source.Command;
}

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

void CNetworkScheduleJob::Dump( CDumpContext& dump_context ) const
{
   CObject::Dump( dump_context );

   dump_context << TEXT( "{\n" );
   dump_context << TEXT( "   ID                               = " ) << ID                               << TEXT( "\n" );
   dump_context << TEXT( "   NumberOfMillisecondsFromMidnight = " ) << NumberOfMillisecondsFromMidnight << TEXT( "\n" );
   dump_context << TEXT( "   DaysOfTheMonth                   = " ) << DaysOfTheMonth                   << TEXT( " ( " );

   CString temp_string;
   CString number_string;

   int index = 0;

   while( index < 32 )
   {
      if ( bit_test( DaysOfTheMonth, index ) == 1 )
      {
         number_string.Format( TEXT( "%d, " ), index + 1 );
         temp_string += number_string;
      }

      index++;
   }

   dump_context << temp_string << TEXT( ")\n" );

   dump_context << TEXT( "   DaysOfTheWeek                    = " ) << DaysOfTheWeek                    << TEXT( " (" );

   temp_string.Empty();

   if ( bit_test( DaysOfTheWeek, 0 ) == 1 )
   {
      temp_string += TEXT( "Monday" );
   }

   if ( bit_test( DaysOfTheWeek, 1 ) == 1 )
   {
      if ( temp_string.GetLength() > 0 )
      {
         temp_string += TEXT( ", " );
      }

      temp_string += TEXT( "Tuesday" );
   }

   if ( bit_test( DaysOfTheWeek, 2 ) == 1 )
   {
      if ( temp_string.GetLength() > 0 )
      {
         temp_string += TEXT( ", " );
      }

      temp_string += TEXT( "Wednesday" );
   }

   if ( bit_test( DaysOfTheWeek, 3 ) == 1 )
   {
      if ( temp_string.GetLength() > 0 )
      {
         temp_string += TEXT( ", " );
      }

      temp_string += TEXT( "Thursday" );
   }

   if ( bit_test( DaysOfTheWeek, 4 ) == 1 )
   {
      if ( temp_string.GetLength() > 0 )
      {
         temp_string += TEXT( ", " );
      }

      temp_string += TEXT( "Friday" );
   }

   if ( bit_test( DaysOfTheWeek, 5 ) == 1 )
   {
      if ( temp_string.GetLength() > 0 )
      {
         temp_string += TEXT( ", " );
      }

      temp_string += TEXT( "Saturday" );
   }

   if ( bit_test( DaysOfTheWeek, 6 ) == 1 )
   {
      if ( temp_string.GetLength() > 0 )
      {
         temp_string += TEXT( ", " );
      }

      temp_string += TEXT( "Sunday" );
   }

   dump_context << temp_string << TEXT( " )\n" );

   dump_context << TEXT( "   Flags                            = " ) << Flags                            << TEXT( " ( " );

   if ( Flags & JOB_RUN_PERIODICALLY )
   {
      temp_string = TEXT( "JOB_RUN_PERIODICALLY" );
   }

   if ( Flags & JOB_EXEC_ERROR )
   {
      if ( temp_string.GetLength() > 0 )
      {
         temp_string += TEXT( " | " );
      }

      temp_string += TEXT( "JOB_EXEC_ERROR" );
   }

   if ( Flags & JOB_RUNS_TODAY )
   {
      if ( temp_string.GetLength() > 0 )
      {
         temp_string += TEXT( " | " );
      }

      temp_string += TEXT( "JOB_RUNS_TODAY" );
   }

   if ( Flags & JOB_ADD_CURRENT_DATE )
   {
      if ( temp_string.GetLength() > 0 )
      {
         temp_string += TEXT( " | " );
      }

      temp_string += TEXT( "JOB_ADD_CURRENT_DATE" );
   }

   if ( Flags & JOB_NONINTERACTIVE )
   {
      if ( temp_string.GetLength() > 0 )
      {
         temp_string += TEXT( " | " );
      }

      temp_string += TEXT( "JOB_NONINTERACTIVE" );
   }

   dump_context << temp_string << TEXT( " )" );

   temp_string.Empty();

   if ( Flags == JOB_INPUT_FLAGS )
   {
      dump_context << TEXT( " also known as JOB_INPUT_FLAGS" );
   }

   if ( Flags == JOB_OUTPUT_FLAGS )
   {
      dump_context << TEXT( " also known as JOB_OUTPUT_FLAGS" );
   }

   dump_context << TEXT( "\n" );

   dump_context << TEXT( "   Command                          = " ) << Command                          << TEXT( "\n" );
   dump_context << TEXT( "}\n" );
}

#endif // _DEBUG

void CNetworkScheduleJob::Empty( void )
{
   WFCLTRACEINIT( TEXT( "CNetworkScheduleJob::Empty()" ) );
   m_Initialize();
}

void CNetworkScheduleJob::m_Initialize( void )
{
   WFCLTRACEINIT( TEXT( "CNetworkScheduleJob::m_Initialize()" ) );
   ID                               = 0;
   NumberOfMillisecondsFromMidnight = 0;
   DaysOfTheMonth                   = 0;
   DaysOfTheWeek                    = 0;
   Flags                            = 0;
   Command.Empty();
}

#if ! defined(  WFC_NO_SERIALIZATION )

void CNetworkScheduleJob::Serialize( CArchive& archive )
{
   WFCLTRACEINIT( TEXT( "CNetworkScheduleJob::Serialize()" ) );

   CObject::Serialize( archive );

   if ( archive.IsStoring() )
   {
      WFCTRACE( TEXT( "Storing" ) );
      archive << ID;
      archive << NumberOfMillisecondsFromMidnight;
      archive << DaysOfTheMonth;
      archive << DaysOfTheWeek;
      archive << Flags;
      archive << Command;
   }
   else
   {
      WFCTRACE( TEXT( "Restoring" ) );
      archive >> ID;
      archive >> NumberOfMillisecondsFromMidnight;
      archive >> DaysOfTheMonth;
      archive >> DaysOfTheWeek;
      archive >> Flags;
      archive >> Command;
   }
}

#endif // WFC_NO_SERIALIZATION

const CNetworkScheduleJob& CNetworkScheduleJob::operator = ( const CNetworkScheduleJob& source )
{
   ASSERT( this != &source );

   if ( this != &source )
   {
      Copy( source );
   }

   return( *this );
}

// End of source

#if 0
<HTML>

<HEAD>
<TITLE>WFC - CNetworkScheduleJob</TITLE>
<META name="keywords" content="WFC, MFC extension library, freeware class library, Win32, at, winat, source code">
<META name="description" content="The C++ class that lets you schedule programs to run at certain times.">
</HEAD>

<BODY>
<H1>CNetworkScheduleJob : CObject</H1>
$Revision: 9 $<BR>
<HR>

<H2>Description</H2>
This handles the same information as AT_ENUM and AT_INFO.
It is used to schedule jobs that run unattended.

<H2>Construction</H2>

<DL COMPACT>

<DT><PRE><B>CNetworkScheduleJob</B>()
<B>CNetworkScheduleJob</B>( const AT_ENUM * source )
<B>CNetworkScheduleJob</B>( const AT_INFO * source )
<B>CNetworkScheduleJob</B>( const CNetworkScheduleJob&amp; source )</PRE><DD>
Constructs the object.

</DL>

<H2>Data Members</H2>

<DL COMPACT>

<DT><PRE>DWORD <B>ID</B></PRE><DD>
Contains the job identifier.

<DT><PRE>DWORD <B>NumberOfMillisecondsFromMidnight</B></PRE><DD>
Contains the number of milliseconds from midnight that the job
will execute.

<DT><PRE>DWORD <B>DaysOfTheMonth</B></PRE><DD>
A bitmapped field of the days of the month when the job
will execute. Bit zero corresponds to the first day of the month.

<DT><PRE>DWORD <B>DaysOfTheWeek</B></PRE><DD>
A bitmapped field of the days of the week when the job
will execute. Bit zero corresponds to Monday.

<DT><PRE>DWORD <B>Flags</B></PRE><DD>
A bitmapped field describing job properties.

<DT><PRE>CString <B>Command</B></PRE><DD>
The actual command line that will be executed.

</DL>

<H2>Methods</H2>

<DL COMPACT>

<DT><PRE>void <B>Copy</B>( const AT_ENUM * source )
void <B>Copy</B>( const AT_INFO * source )
void <B>Copy</B>( const CNetworkScheduleJob&amp; source )</PRE><DD>
Copies the contents of source.

<DT><PRE>void <B>Dump</B>( CDumpContext&amp; dump_context ) const</PRE><DD>
Present only in debug builds. Dumps useful information to the 
debugging window.

<DT><PRE>void <B>Empty</B>( void )</PRE><DD>
Zeroizes the object.

<DT><PRE>void <B>Serialize</B>( CArchive&amp; archive )</PRE><DD>
After all we are a CObject...

</DL>

<H2>Example</H2>

<PRE><CODE>Sorry.</CODE></PRE>

<H2>API's Used</H2>

<B>CNetworkScheduleJob</B> encapsulates the following data structures:

<UL>
<LI>AT_ENUM
<LI>AT_INFO
</UL>

<HR><I>Copyright, 2000, <A HREF="mailto:wfc@pobox.com">Samuel R. Blackburn</A></I><BR>
$Workfile: CNetScheduleJob.cpp $<BR>
$Modtime: 1/04/00 5:16a $
</BODY>

</HTML>
#endif
