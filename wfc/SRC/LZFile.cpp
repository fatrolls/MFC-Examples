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
** $Workfile: lzfile.cpp $
** $Revision: 27 $
** $Modtime: 1/17/00 9:28a $
** $Reuse Tracing Code: 1 $
*/

#if defined( _DEBUG ) && ! defined( WFC_STL )
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif // _DEBUG

CLZFile::CLZFile()
{
   WFCLTRACEINIT( TEXT( "CLZFile::CLZFile()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   m_Initialize();
}

CLZFile::~CLZFile()
{
   WFCLTRACEINIT( TEXT( "CLZFile::~CLZFile()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   Close();
}

void CLZFile::Close( void )
{
   WFCLTRACEINIT( TEXT( "CLZFile::Close()" ) );

   if ( m_LZFileHandle >= 0 )
   {
      WFCTRACE( TEXT( "LZ File was open" ) );
      ::LZClose( m_LZFileHandle );
      m_LZFileHandle = LZERROR_BADINHANDLE;
      m_hFile = (UINT) CFile::hFileNull;
   }

   m_Initialize();
}

BOOL CLZFile::Copy( const CLZFile * source_p )
{
   WFCLTRACEINIT( TEXT( "CLZFile::Copy( const CLZFile * )" ) );
   return( Copy( *source_p ) );
}

BOOL CLZFile::Copy( const CLZFile& source )
{
   WFCLTRACEINIT( TEXT( "CLZFile::Copy( const CLZFile& )" ) );

   LONG size_of_destination_file = 0;

   size_of_destination_file = ::LZCopy( source.m_LZFileHandle, m_LZFileHandle );

   if ( size_of_destination_file < 0 )
   {
      m_ErrorCode = size_of_destination_file;
      return( FALSE );
   }

   return( TRUE );
}

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

void CLZFile::Dump( CDumpContext& dump_context ) const
{
   CDummyFile::Dump( dump_context );

   dump_context << TEXT( "m_LZFileHandle       = " ) << m_LZFileHandle << TEXT( "\n" );
   dump_context << TEXT( "m_OpenFileStructure is " );
   m_OpenFileStructure.Dump( dump_context );
}

#endif // _DEBUG

BOOL CLZFile::GetExpandedName( LPTSTR name_of_compressed_file, CString& original_file_name )
{
   WFCLTRACEINIT( TEXT( "CLZFile::GetExpandedName()" ) );

   TCHAR file_name[ _MAX_PATH ];

   ::ZeroMemory( file_name, sizeof( file_name ) );

   // We were passed a pointer, don't trust it

   try
   {
      if ( ::GetExpandedName( name_of_compressed_file, file_name ) == 1 )
      {
         original_file_name = file_name;
         return( TRUE );
      }
      else
      {
         original_file_name.Empty();
         return( FALSE );
      }
   }
   catch( ... )
   {
      m_ErrorCode = ERROR_EXCEPTION_IN_SERVICE;
      original_file_name.Empty();
      return( FALSE );
   }
}

void CLZFile::m_Initialize( void )
{
   m_LZFileHandle = 0;
   m_OpenFileStructure.Empty();
}

#if ! defined( WFC_STL )
BOOL CLZFile::Open( LPCTSTR file_name, UINT style, CFileException * )
#else // WFC_STL
BOOL CLZFile::Open( LPCTSTR file_name, UINT style )
#endif // WFC_STL
{
   WFCLTRACEINIT( TEXT( "CLZFile::Open()" ) );

   if ( file_name == NULL )
   {
      WFCTRACE( TEXT( "file_name is NULL!" ) );
      return( FALSE );
   }

   // We were passed a pointer, do not trust it

   try
   {
      // First parameter to LZOpenFile is mis-typed. It is not const-correct

      CString non_const_string( file_name );

      m_LZFileHandle = ::LZOpenFile( non_const_string.GetBuffer( non_const_string.GetLength() + 1 ), &m_OpenFileStructure, (WORD) style );

      if ( m_LZFileHandle < 0 )
      {
         m_ErrorCode = m_LZFileHandle;
         return( FALSE );
      }

#if ! defined( WFC_STL )
      m_strFileName = file_name;
#else // WFC_STL
      m_FileName = file_name;
#endif // WFC_STL

      return( TRUE );
   }
   catch( ... )
   {
      m_ErrorCode = ERROR_EXCEPTION_IN_SERVICE;
      return( FALSE );
   }
}

UINT CLZFile::Read( void *buffer, UINT size_of_buffer )
{
   WFCLTRACEINIT( TEXT( "CLZFile::Read()" ) );

   INT number_of_bytes_read = 0;

   // We were passed a pointer, don't trust it

   try
   {
      number_of_bytes_read = ::LZRead( m_LZFileHandle, (char *) buffer, size_of_buffer );

      if ( number_of_bytes_read < 0 )
      {
         m_ErrorCode = number_of_bytes_read;
         return( 0 );
      }

      return( (UINT) number_of_bytes_read );
   }
   catch( ... )
   {
      m_ErrorCode = ERROR_EXCEPTION_IN_SERVICE;
      return( 0 );
   }
}

LONG CLZFile::Seek( LONG offset, UINT from )
{
   WFCLTRACEINIT( TEXT( "CLZFile::Seek()" ) );

	ASSERT( m_hFile != (UINT) CFile::hFileNull );
	ASSERT( from == begin || from == end || from == current );
	ASSERT( begin == FILE_BEGIN && end == FILE_END && current == FILE_CURRENT );

	LONG offset_from_beginning_of_file = ::LZSeek( m_LZFileHandle, offset, from );

   if ( offset_from_beginning_of_file < 0 )
   {
      m_ErrorCode = offset_from_beginning_of_file;
   }

	return( offset_from_beginning_of_file );
}

void CLZFile::TranslateErrorCode( int error_code, CString& error_message )
{
   WFCLTRACEINIT( TEXT( "CLZFile::TranslateErrorCode()" ) );

   switch( error_code )
   {
      case LZERROR_BADINHANDLE:

         error_message = TEXT( "Invalid input handle" );
         return;

      case LZERROR_BADOUTHANDLE:

         error_message = TEXT( "Invalid output handle" );
         return;

      case LZERROR_READ:

         error_message = TEXT( "Corrupt compressed file format" );
         return;

      case LZERROR_WRITE:

         error_message = TEXT( "Out of space for output file" );
         return;

      case LZERROR_GLOBALLOC:

         error_message = TEXT( "Insufficient memory for LZFile struct" );
         return;

      case LZERROR_GLOBLOCK:

         error_message = TEXT( "Bad global handle" );
         return;

      case LZERROR_BADVALUE:

         error_message = TEXT( "Input parameter out of acceptable range" );
         return;

      case LZERROR_UNKNOWNALG:

         error_message = TEXT( "Compression algorithm not recognized" );
         return;

      default:

         error_message.Format( TEXT( "Unknown error number %d" ), error_code );
         return;
   }
}

// End of source

#if 0
<HTML>

<HEAD>
<TITLE>WFC - CLZFile</TITLE>
<META name="keywords" content="WFC, MFC extension library, freeware class library, Win32, source code">
<META name="description" content="The C++ class that handles LZ compressed files.">
</HEAD>

<BODY>

<H1>CLZFile : <A HREF="DumyFile.htm">CDummyFile</A></H1>
$Revision: 27 $<BR><HR>

<H2>Description</H2>

This class makes it easy to play with LZ compressed files. It encapsulates the LZ API.

<H2>Data Members</H2>

None.

<H2>Methods</H2>

<DL COMPACT>

<DT><PRE>void <B>Close</B>( void )</PRE><DD>Closes the LZ File.

<DT><PRE>BOOL <B>Copy</B>( const CLZFile&amp; source )
BOOL <B>Copy</B>( const CLZFile * source )</PRE><DD>
Copies one CLZFile to this one.

<DT><PRE>BOOL <B>GetExpandedName</B>( LPTSTR name_of_compressed_file, CString&amp; original_file_name )</PRE><DD>
Retrieves what the name of the expanded file will be.

<DT><PRE>BOOL <B>Open</B>( const char *channel_name, UINT style = OF_READ, CFileException* pError = NULL )</PRE><DD>
Opens an LZ compressed file for expanding.

<DT><PRE>UINT <B>Read</B>( void * buffer, UINT size_of_buffer )</PRE><DD>
Expands data stored in the compressed file.

<DT><PRE>LONG <B>Seek</B>( LONG offset, UINT from )</PRE><DD>
Moves the file pointer.

<DT><PRE>static void <B>TranslateErrorCode</B>( int error_code, CString&amp; error_message )</PRE><DD>
Translates an error code ( LZERROR_xxx) into a human readable string.

</DL>

<H2>Example</H2>
<PRE><CODE>#include &lt;wfc.h&gt;

void test_CLZFile( LPTSTR lz_file_name )
{
   <A HREF="WfcTrace.htm">WFCTRACEINIT</A>( TEXT( &quot;test_CLZFile()&quot; ) );

   <B>CLZFile</B> lz_file;

   if ( lz_file_name == (LPTSTR) NULL )
   {
      return;
   }

   CString expanded_name;

   lz_file.GetExpandedName( lz_file_name, expanded_name );

   _tprintf( TEXT( &quot;LZ File \&quot;%s\&quot; expanded name is \&quot;%s\&quot;\n&quot; ), lz_file_name, (LPCTSTR) expanded_name );

   if ( lz_file.Open( lz_file_name ) != FALSE )
   {
      <B>CLZFile</B> output_file;

      if ( output_file.Open( expanded_name, OF_CREATE ) != FALSE )
      {
         if ( output_file.Copy( lz_file ) != FALSE )
         {
            _tprintf( TEXT( &quot;Successfully copied\n&quot; ) );
         }
         else
         {
            CString error_message_string;
            CLZFile::TranslateErrorCode( (int) lz_file.GetErrorCode(), error_message_string );
            _tprintf( TEXT( &quot;Can't Copy because %s\n&quot; ), (LPCTSTR) error_message_string );
         }
      }
      else
      {
         CString error_message_string;
         CLZFile::TranslateErrorCode( (int) output_file.GetErrorCode(), error_message_string );
         _tprintf( TEXT( &quot;Can't open LZ output file because %s\n&quot; ), (LPCTSTR) error_message_string );
      }
   }
   else
   {
      CString error_message_string;
      CLZFile::TranslateErrorCode( (int) lz_file.GetErrorCode(), error_message_string );
      _tprintf( TEXT( &quot;Can't open LZ file \&quot;%s\&quot; because \n&quot; ), lz_file_name, (LPCTSTR) error_message_string );
   }
}</CODE></PRE>

<H2>API's Used</H2>

<B>CLZFile</B> uses the following API's:

<UL>
<LI>GetExpandedName
<LI>LZClose
<LI>LZCopy
<LI>LZOpenFile
<LI>LZRead
<LI>LZSeek
</UL>

<HR><I>Copyright, 2000, <A HREF="mailto:wfc@pobox.com">Samuel R. Blackburn</A></I><BR>
$Workfile: lzfile.cpp $<BR>
$Modtime: 1/17/00 9:28a $
</BODY>
</HTML>
#endif
