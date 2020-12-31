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
** $Workfile: dumyfile.cpp $
** $Revision: 24 $
** $Modtime: 1/05/00 3:37a $
** $Reuse Tracing Code: 1 $
*/

#if defined( _DEBUG ) && ! defined( WFC_STL )
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

#if ! defined( WFC_NO_SERIALIZATION )
IMPLEMENT_SERIAL( CDummyFile, CFile, 1 )
#endif // WFC_NO_SERIALIZATION

#if defined( _DEBUG ) && ! defined( WFC_STL )
#define new DEBUG_NEW
#endif // _DEBUG

CDummyFile::CDummyFile()
{
   WFCLTRACEINIT( TEXT( "CDummyFile::CDummyFile()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   m_ErrorCode = 0;
   m_TemplateHandle = reinterpret_cast< HANDLE >( NULL );

#if defined( WFC_STL )
   m_FileHandle = NULL;
#endif // WFC_STL
}

CDummyFile::~CDummyFile()
{
   WFCLTRACEINIT( TEXT( "CDummyFile::~CDummyFile()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );

   Close();

   m_ErrorCode = 0;
   m_TemplateHandle = reinterpret_cast< HANDLE >( NULL );
#if defined( WFC_STL )
   m_FileHandle = NULL;
#endif // WFC_STL
}

void CDummyFile::Abort( void )
{
   WFCLTRACEINIT( TEXT( "CDummyFile::Abort()" ) );
   Close();
}

void CDummyFile::Close( void )
{
   WFCLTRACEINIT( TEXT( "CDummyFile::Close()" ) );

   /*
   ** This is here to trap calls that attempt to close an already closed file.
   ** I don't consider this an error but MFC does...
   */

   if ( GetHandle() != (HANDLE) hFileNull )
   {
      WFCTRACE( TEXT( "Calling CFile::Close()" ) );
      CFile::Close();
   }
}

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

void CDummyFile::Dump( CDumpContext& dump_context ) const
{
   CFile::Dump( dump_context );

   dump_context << TEXT( "m_ErrorCode      = " ) << m_ErrorCode      << TEXT( "\n" );
   dump_context << TEXT( "m_TemplateHandle = " ) << m_TemplateHandle << TEXT( "\n" );
}

#endif // _DEBUG

void CDummyFile::Flush( void )
{
   WFCLTRACEINIT( TEXT( "CDummyFile::Flush()" ) );
}

DWORD CDummyFile::GetErrorCode( void ) const
{
   WFCLTRACEINIT( TEXT( "CDummyFile::GetErrorCode()" ) );
   return( m_ErrorCode );
}

DWORD CDummyFile::GetLength( void ) const
{
   WFCLTRACEINIT( TEXT( "CDummyFile::GetLength()" ) );
   return( 0L );
}

DWORD CDummyFile::GetPosition( void ) const
{
   WFCLTRACEINIT( TEXT( "CDummyFile::GetPosition()" ) );
   ASSERT( FALSE ); // Unsupported function
   return( 0L );
}

#if ! defined( WFC_STL )

#pragma warning( disable : 4100 )

BOOL CDummyFile::GetStatus( CFileStatus& status )
{
   WFCLTRACEINIT( TEXT( "CDummyFile::GetStatus()" ) );
   return( FALSE );
}

BOOL CDummyFile::GetStatus( LPCTSTR Name, CFileStatus& Status )
{
   WFCLTRACEINIT( TEXT( "CDummyFile::GetStatus( LPCTSTR Name, CFileStatus& Status )" ) );
   return( FALSE );
}

#endif // WFC_STL

void CDummyFile::LockRange( DWORD Position, DWORD Count )
{
   WFCLTRACEINIT( TEXT( "CDummyFile::LockRange()" ) );
   ASSERT( FALSE ); // Unsupported function
}

DWORD CDummyFile::m_CreateCreationDistribution( void ) const
{
   WFCLTRACEINIT( TEXT( "CDummyFile::m_CreateCreationDistribution()" ) );
   return( OPEN_EXISTING );
}

DWORD CDummyFile::m_CreateDesiredAccess( void ) const
{
   WFCLTRACEINIT( TEXT( "CDummyFile::m_CreateDesiredAccess()" ) );
   return( GENERIC_READ | GENERIC_WRITE );
}

DWORD CDummyFile::m_CreateFlagsAndAttributes( void ) const
{
   WFCLTRACEINIT( TEXT( "CDummyFile::m_CreateFlagsAndAttributes()" ) );
   return( 0 );
}

LPSECURITY_ATTRIBUTES CDummyFile::m_CreateSecurityAttributes( void ) const
{
   WFCLTRACEINIT( TEXT( "CDummyFile::m_CreateSecurityAttributes()" ) );
   return( reinterpret_cast< LPSECURITY_ATTRIBUTES >( NULL ) );
}

DWORD CDummyFile::m_CreateShareMode( void ) const
{
   WFCLTRACEINIT( TEXT( "CDummyFile::m_CreateShareMode()" ) );
   return( 0 );
}

HANDLE CDummyFile::m_CreateTemplateHandle( void ) const
{
   WFCLTRACEINIT( TEXT( "CDummyFile::m_CreateTemplateHandle()" ) );
   return( m_TemplateHandle );
}

void CDummyFile::Remove( LPCTSTR name )
{
   WFCLTRACEINIT( TEXT( "CDummyFile::Remove()" ) );
   ASSERT( FALSE ); // Unsupported function
}

void CDummyFile::Rename( LPCTSTR OldName, LPCTSTR NewName )
{
   WFCLTRACEINIT( TEXT( "CDummyFile::Rename()" ) );
   ASSERT( FALSE ); // Unsupported function
}

#pragma warning( disable : 4100 )

LONG CDummyFile::Seek( LONG Offset, UINT From )
{
   WFCLTRACEINIT( TEXT( "CDummyFile::Seek()" ) );
   ASSERT( FALSE ); // Unsupported function
   return( 0L );
}

#pragma warning( default : 4100 )

#if ! defined( WFC_NO_SERIALIZATION )

void CDummyFile::Serialize( CArchive& archive )
{
   WFCLTRACEINIT( TEXT( "CDummyFile::Serialize()" ) );
   CFile::Serialize( archive );
}

#endif // WFC_NO_SERIALIZATION

#pragma warning( disable : 4100 )

void CDummyFile::SetLength( DWORD length )
{
   WFCLTRACEINIT( TEXT( "CDummyFile::SetLength()" ) );
   ASSERT( FALSE ); // Unsupported function
}

#if ! defined( WFC_STL )

void CDummyFile::SetStatus( LPCTSTR name, const CFileStatus& status )
{
   WFCLTRACEINIT( TEXT( "CDummyFile::SetStatus()" ) );
}

#endif // WFC_STL

void CDummyFile::UnlockRange( DWORD Position, DWORD Count )
{
   WFCLTRACEINIT( TEXT( "CDummyFile::UnlockRange()" ) );
   ASSERT( FALSE ); // Unsupported function
}

void CDummyFile::Write( const CString& string_to_write )
{
   WFCLTRACEINIT( TEXT( "CDummyFile::Write( const CString& string_to_write )" ) );
   CFile::Write( (const void *) (LPCTSTR) string_to_write, (UINT) string_to_write.GetLength() );
}

void CDummyFile::Write( const CByteArray& data_to_write )
{
   WFCLTRACEINIT( TEXT( "CDummyFile::Write( const CByteArray& data_to_write )" ) );
   UINT number_of_bytes_to_write = data_to_write.GetSize();

   // Well whaddya know, there's an undocumented yet "public" function
   // that let's us have quick access to the raw bytes...

   const BYTE * buffer = data_to_write.GetData();

   CFile::Write( (const void *) buffer, number_of_bytes_to_write );
}

#pragma warning( default : 4100 )

// End of source

#if 0
<HTML>

<HEAD>
<TITLE>WFC - CDummyFile</TITLE>
<META name="keywords" content="WFC, MFC extension library, freeware class library, Win32, source code">
<META name="description" content="The C++ class that intercepts calls to CFile that would blow up when your derived class isn't playing with data on a disk.">
</HEAD>

<BODY>

<H1>CDummyFile : CFile</H1>
$Revision: 24 $<BR>
<HR>

<H2>Description</H2>

This class intercepts all calls to functions in CFile that would blow up
if what your file HANDLE doesn't point to a file on a disk drive (like
a TCP/IP socket or the serial port). It also adds a couple of useful 
functions that should have been in CFile (IMHO).

<H2>Data Members</H2>

None.

<H2>Methods</H2>

<DL COMPACT>

<DT><PRE>void <B>Abort</B>( void )</PRE><DD>Closes the file.

<DT><PRE>void <B>Close</B>( void )</PRE><DD>Closes the file.

<DT><PRE>void <B>Flush</B>( void )</PRE><DD>Flushes file buffers.

<DT><PRE>DWORD <B>GetErrorCode</B>( void ) const</PRE><DD>
Retrieves the error code if a function fails or returns FALSE.

<DT><PRE>DWORD <B>GetLength</B>( void ) const</PRE><DD>
Makes no sense if you don't have a disk file. It always returns zero.

<DT><PRE>DWORD <B>GetPosition</B>( void ) const</PRE><DD>
Makes no sense. Always returns zero.

<DT><PRE>BOOL <B>GetStatus</B>( CFileStatus&amp; status )
BOOL <B>GetStatus</B>( LPCTSTR filename, CFileStatus&amp; status )</PRE><DD>Makes no sense.

<DT><PRE>void <B>LockRange</B>( DWORD position, DWORD count )</PRE><DD>Makes no sense.

<DT><PRE>void <B>Remove</B>( LPCTSTR filename )</PRE><DD>
Makes no sense. Always returns FALSE.

<DT><PRE>void <B>Rename</B>( LPCTSTR old_filename, LPCTSTR new_filename )</PRE><DD>Makes no sense.

<DT><PRE>LONG <B>Seek</B>( LONG offset, UINT from )</PRE><DD>
Makes no sense. Always returns zero.

<DT><PRE>void <B>Serialize</B>( CArchive&amp; archive )</PRE><DD>Saves/restores the object.

<DT><PRE>void <B>SetLength</B>( DWORD length )</PRE><DD>Makes no sense.

<DT><PRE>void <B>SetStatus</B>( LPCTSTR name, CFileStatus&amp; status )</PRE><DD>Makes no sense.

<DT><PRE>void <B>UnlockRange</B>( DWORD position, DWORD count )</PRE><DD>Makes no sense.

<DT><PRE>void <B>Write</B>( const CString&amp; string_to_write )
void <B>Write</B>( const CByteArray&amp; data_to_write )</PRE><DD>Adds capability to write a CString or a CByteArray.

</DL>

<H2>Example</H2>
<PRE><CODE>Sorry.</CODE></PRE>

<HR><I>Copyright, 2000, <A HREF="mailto:wfc@pobox.com">Samuel R. Blackburn</A></I><BR>
$Workfile: dumyfile.cpp $<BR>
$Modtime: 1/05/00 3:37a $
</BODY>

</HTML>
#endif
