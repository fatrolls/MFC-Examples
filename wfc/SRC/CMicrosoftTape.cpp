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
** $Workfile: CMicrosoftTape.cpp $
** $Revision: 20 $
** $Modtime: 1/04/00 5:15a $
** $Reuse Tracing Code: 1 $
*/

#if defined( _DEBUG ) && ! defined( WFC_STL )
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif // _DEBUG

/*
** CMicrosoftTape
** As documented in ftp://ftp.microsoft.com/developr/drg/Tape/MTF10.ZIP
*/

CMicrosoftTape::CMicrosoftTape()
{
   WFCLTRACEINIT( TEXT( "CMicrosoftTape::CMicrosoftTape()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   m_Initialize();
   m_AutomaticallyClose = FALSE;
}

CMicrosoftTape::~CMicrosoftTape()
{
   WFCLTRACEINIT( TEXT( "CMicrosoftTape::~CMicrosoftTape()" ) );
   m_Initialize();
}

void CMicrosoftTape::m_Initialize( void )
{
   WFCLTRACEINIT( TEXT( "CTape::m_Initialize()" ) );
   m_TapeHeader.Empty();
}

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

void CMicrosoftTape::Dump( CDumpContext& dump_context ) const
{
   dump_context << TEXT( "a CMicrosoftTape at " ) << (void *) this << TEXT( "\n" );
   dump_context << TEXT( "{\n" );
   dump_context << TEXT( "   m_TapeHeader " );
   m_TapeHeader.Dump( dump_context );
   dump_context << TEXT( "}\n" );
}

#endif // _DEBUG

void CMicrosoftTape::Empty( void )
{
   WFCLTRACEINIT( TEXT( "CMicrosoftTape::Empty()" ) );
}

BOOL CMicrosoftTape::EnumerateSets( void )
{
   WFCLTRACEINIT( TEXT( "CMicrosoctTape::EnumerateSets()" ) );
   return( TRUE );
}

BOOL CMicrosoftTape::Open( const UINT tape_drive_number_starting_at_zero )
{
   WFCLTRACEINIT( TEXT( "CMicrosoftTape::ReadHeader()" ) );

   if ( CTape::Open( tape_drive_number_starting_at_zero ) != FALSE )
   {
      WFCTRACE( TEXT( "Tape Opened." ) );
      ReadHeader();
      return( TRUE );
   }
   else
   {
      return( FALSE );
   }
}

BOOL CMicrosoftTape::ReadHeader( void )
{
   WFCLTRACEINIT( TEXT( "CMicrosoftTape::ReadHeader()" ) );
   ASSERT( m_hFile != hFileNull );

   if ( m_hFile == hFileNull )
   {
      m_ErrorCode = 0;
      return( FALSE );
   }

   //Rewind();

   DWORD number_of_bytes_read = 0;

   if ( ::ReadFile( (HANDLE) m_hFile, (LPVOID) (MTF_TAPE *) &m_TapeHeader, sizeof( MTF_TAPE ), &number_of_bytes_read, NULL ) == FALSE )
   {
      WFCTRACEVAL( TEXT( "Can't ReadFile TAPE" ), m_TapeDriveNumberStartingAtZero );
      return( FALSE );
   }

   return( TRUE );
}

// End of source

#if 0
<HTML>

<HEAD>
<TITLE>WFC - CMicrosoftTape</TITLE>
<META name="keywords" content="WFC, MFC extension library, freeware class library, Win32, source code, MTF">
<META name="description" content="The C++ class that handles the Microsoft Tape Format (MTF).">
</HEAD>

<BODY>

<H1>CMicrosoftTape : <A HREF="CTape.htm">CTape</A></H1>

$Revision: 20 $<BR>
<HR>

<H2>Description</H2>

This class is a work in progress. If you find it useful let me know and I'll
extend it further. This is basically a toy.
The Microsoft Tape format is documented in a Postscript file called
<CODE>MTF10.ZIP</CODE> which can be found at
<CODE>ftp://ftp.microsoft.com/developr/drg/Tape/MTF10.ZIP</CODE>

<H2>Data Members</H2>None.

<H2>Methods</H2>

<DL COMPACT>

<DT><B>Empty</B><DD>Clears all internal data members.

<DT><B>EnumerateSets</B><DD>This doesn't work. But if it did it would
enumerate all the sets on the tape.

<DT><B>Open</B><DD>Opens the tape drive for reading and reads the header.

<DT><B>ReadHeader</B><DD>Retrieves the header information about the
tape backup.

</DL>

<H2>Example</H2>

<PRE><CODE>Sorry.</CODE></PRE>

<HR><I>Copyright, 2000, <A HREF="mailto:wfc@pobox.com">Samuel R. Blackburn</A></I><BR>
$Workfile: CMicrosoftTape.cpp $<BR>
$Modtime: 1/04/00 5:15a $
</BODY>

</HTML>
#endif
