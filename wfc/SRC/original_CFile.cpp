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
** $Workfile: wfc.h $
** $Revision: 55 $
** $Modtime: 9/05/99 2:07p $
*/

#if defined( WFC_STL )

CFile::CFile()
{
   WFCLTRACEINIT( "CFile::CFile()" );
   m_File_p        = (FILE *) NULL;
   m_CloseOnDelete = FALSE;
}

CFile::CFile( const char * file_name, UINT open_flags )
{
   WFCLTRACEINIT( "CFile::CFile::( const char *, UINT )" );
   Open( file_name, open_flags );
}

CFile::~CFile()
{
   WFCLTRACEINIT( "CFile::~CFile()" );

   if ( m_File_p != (FILE *) NULL && m_CloseOnDelete )
   {
      Close();
   }
}

void CFile::Close()
{
   if ( m_File_p != (FILE *) NULL )
   {
      ::fclose( m_File_p );
   }

   m_File_p        = (FILE *) NULL;
   m_CloseOnDelete = FALSE;
   m_strFileName.Empty();
}

void CFile::Flush()
{
   if ( m_File_p == (FILE *) NULL )
   {
      return;
   }

   fflush( m_File_p );
}

CString CFile::GetFileName( void ) const
{
   return( m_strFileName );
}

UINT32 CFile::GetLength() const
{
   UINT32 length           = 0;
   UINT32 current_position = 0; 

   // Seek is a non const operation
   CFile* file_p = (CFile*) this;

   current_position = file_p->Seek( 0L, current );
   length = file_p->SeekToEnd();
   file_p->Seek( current_position, begin );

   return( length );
}

UINT32 CFile::GetPosition() const
{
   ASSERT( m_File_p != (FILE *) NULL );

   if ( m_File_p == (FILE *) NULL )
   {
      return( 0 );
   }

   return( ::ftell( m_File_p ) );
}

BOOL CFile::Open( const char * lpszFileName, UINT nOpenFlags )
{
   WFCLTRACEINIT( "CFile::Open()" );

   Close();

   m_CloseOnDelete = FALSE;
   m_File_p        = (FILE *) NULL;
   m_strFileName.Empty();

   m_strFileName = lpszFileName;

   CString open_flags;

   // map read/write mode

   ASSERT((modeRead|modeWrite|modeReadWrite) == 3);

   if ( nOpenFlags & modeCreate )
   {
      if ( nOpenFlags & modeNoTruncate )
      {
         open_flags = "a";
      }
      else
      {
         open_flags = "w";
      }
   }
   else if ( nOpenFlags & modeWrite ) // We ain't creating the file
   {
      if ( nOpenFlags & modeNoTruncate )
      {
         open_flags = "a";
      }
      else
      {
         open_flags = "w";
      }
   }
   else if ( nOpenFlags & modeReadWrite )
   {
      if ( nOpenFlags & modeNoTruncate )
      {
         open_flags = "a";
      }
      else
      {
         open_flags = "w";
      }
   }
   else
   {
      // Default to modeRead
      open_flags = "r";
   }

   // attempt file creation

   FILE * file_p = ::fopen( lpszFileName, open_flags );

   if ( file_p == (FILE *) NULL )
   {
      TRACEVAL( "Can't open ", lpszFileName );
      return( FALSE );
   }

   setvbuf( file_p, (char *) NULL, _IOFBF, 65535 );

   m_File_p        = file_p;
   m_CloseOnDelete = TRUE;

   return( TRUE );
}

UINT CFile::Read( void* buffer, UINT number_of_bytes_to_read )
{
   WFCLTRACEINIT( "CFile::Read()" );

   ASSERT( m_File_p != (FILE *) NULL );

   if ( m_File_p == (FILE *) NULL )
   {
      TRACEMSG( "m_File_p is NULL" );
      return( 0 );
   }

   if ( number_of_bytes_to_read == 0 )
   {
      TRACEMSG( "number of bytes to read is zero" );
      return( 0 );   // avoid Win32 "null-read"
   }

   ASSERT( buffer != NULL );

   if ( buffer == NULL )
   {
      TRACEMSG( "buffer is NULL" );
      return( 0 );
   }

   size_t number_of_bytes_read = 0;

   number_of_bytes_read = ::fread( buffer, 1, number_of_bytes_to_read, m_File_p );

   TRACEVAL( "number of bytes read is ", number_of_bytes_read );

   return( number_of_bytes_read );
}

long CFile::Seek( long offset, UINT from )
{
   ASSERT( m_File_p != (FILE *) NULL );
   ASSERT( from == begin || from == end || from == current );
   ASSERT( begin == 0 && end == 2 && current == 1 );

   if ( m_File_p == (FILE *) NULL )
   {
      return( 0 );
   }

   int whence = 0;

   switch( from )
   {
      case begin:

         whence = SEEK_SET;
         break;

      case current:

         whence = SEEK_CUR;
         break;

      default:

         whence = SEEK_END;
         break;
   }

   ::fseek( m_File_p, offset, whence );

   return( ::ftell( m_File_p ) );
}

void CFile::Write( const void* buffer, UINT number_of_bytes_to_write )
{
   ASSERT( m_File_p != (FILE *) NULL );

   if ( m_File_p == (FILE *) NULL )
   {
      return;
   }

   if ( number_of_bytes_to_write == 0 )
   {
      return;     // avoid Win32 "null-write" option
   }

   ASSERT( buffer != NULL );

   size_t number_of_bytes_written = 0;

   BYTE * write_buffer = (BYTE *) buffer;

   size_t total_number_of_bytes_written = 0;

   UINT number_of_bytes_to_write_in_this_pass = number_of_bytes_to_write;

   int number_of_tries = 0;

   while( total_number_of_bytes_written < number_of_bytes_to_write && number_of_tries < 1000 )
   {
      // we are writing items that are 1 byte in size

      number_of_bytes_written = ::fwrite( &write_buffer[ total_number_of_bytes_written ],
                                          1,
                                          number_of_bytes_to_write_in_this_pass,
                                          m_File_p );

      total_number_of_bytes_written += number_of_bytes_written;

      if ( number_of_bytes_written != number_of_bytes_to_write_in_this_pass )
      {
         CString error_message;

         error_message.Format( "Only wrote %d bytes to the file when it should have written %d\n",
                               (int) number_of_bytes_written,
                               number_of_bytes_to_write_in_this_pass );

         __DEBUG_OUTPUT( error_message );

         Flush();

         if ( ferror( m_File_p ) != 0 )
         {
            error_message.Format( "Error occurred, errno is %d\n", errno );
            __DEBUG_OUTPUT( error_message );
            return;
         }
         else
         {
            __DEBUG_OUTPUT( "NO error occurred\n" );

           number_of_bytes_to_write_in_this_pass -= number_of_bytes_written;
         }
      }

      number_of_tries++;
   }

   ASSERT( total_number_of_bytes_written == number_of_bytes_to_write );
}

CFile::operator FILE *() const
{
   return( m_File_p );
}

UINT32 CFile::SeekToEnd()
{
   return( Seek( 0, CFile::end ) );
}

void CFile::SeekToBegin()
{
   Seek( 0, CFile::begin );
}

#endif // WFC_STL

// End of source

#if 0
<HTML>

<HEAD>
<TITLE>Zia Foundation Classes - CFile</TITLE>
</HEAD>

<BODY>

<H1>CFile</H1>

$Revision: 1.1 $

<BR><HR>

<H2>Description</H2>

This class makes it easy to play with files.

<H2>Constructors</H2>

<DL COMPACT>

<DT><PRE><B>CFile</B>()
<B>CFile</B>( const char * file_name, UINT open_flags )</PRE><DD>

</DL>

<H2>Methods</H2>

<DL COMPACT>

<DT><PRE>void <B>Close</B>( void )</PRE><DD>
Closes the file.

<DT><PRE>void <B>Flush</B>( void )</PRE><DD>
Flushes any internal file system buffers.

<DT><PRE><A HREF="CString.html">CString</A> <B>GetFileName</B>( void ) const</PRE><DD>
Returns the name of the file.

<DT><PRE>UINT32 <B>GetLength</B>( void ) const</PRE><DD>
returns the length of the file.

<DT><PRE>UINT32 <B>GetPosition</B>( void ) const</PRE><DD>
Returns the current position of the file pointer.

<DT><PRE>BOOL <B>Open</B>( const char * file_name, UINT open_flags )</PRE><DD>
Opens the specified files. <CODE>open_flags</CODE> can be one of:

<UL>
<LI>modeRead
<LI>modeWrite
<LI>modeReadWrite
<LI>modeCreate
<LI>modeNoTruncate
</UL>

<DT><PRE>UINT <B>Read</B>( void * buffer, UINT number_of_bytes_to_read )</PRE><DD>
Reads <CODE>number_of_bytes_to_read</CODE> from the file and stores in in <CODE>buffer</CODE>.
It returns the number of bytes actually read.

<DT><PRE>long <B>Seek</B>( long offset, UINT from )</PRE><DD>
Moves the file pointer <CODE>offset</CODE> bytes from <CODE>from</CODE>
location. <CODE>from</CODE> can be one of the following:

<UL>
<LI>begin
<LI>current
<LI>end
</UL>

<DT><PRE>void <B>SeekToBegin</B>( void )</PRE><DD>
Moves the file pointer to the beginning of the file.

<DT><PRE>UINT32 <B>SeekToEnd</B>( void )</PRE><DD>
Moves the file pointer to the end of the file.

<DT><PRE>void <B>Write</B>( const void * buffer, UINT number_of_bytes_to_write )</PRE><DD>
Writes <CODE>number_of_bytes_to_write</CODE> from the memory location specified
by <CODE>buffer</CODE> to the file.

</DL>

<H2>Example</H2>

<PRE><CODE>void dump_file( <B>CFile</B>&amp; file )
{
   <A HREF="CTrace.html">TRACEINIT</A>( &quot;dump_file()&quot;, 0 );

   <A HREF="CString.html">CString</A> file_name;

   file_name = file.GetFileName();

   long length = 0;

   length = file.GetLength();

   // Move to the end of the file

   file.Seek( 0, CFile::end );

   // Move to the beginning of the file

   file.SeekToBegin();

   printf( &quot;%s is %ld bytes long\n&quot;, (const char *) file_name, length );
}

void main( int number_of_command_line_arguments, char *command_line_arguments[] )
{
   <A HREF="CTrace.html">TRACEINIT</A>( &quot;main()&quot;, 0 );

   if ( number_of_command_line_arguments &gt; 1 )
   {
      <B>CFile</B> my_file;

      if ( my_file.Open( command_line_arguments[ 1 ], CFile::modeRead ) == TRUE )
      {
         dump_file( my_file );
      }
   }
}</CODE></PRE>
If you want to append data to an existing file, you would use
<CODE>modeNoTruncate</CODE>
in conjunction with
<CODE>modeWrite</CODE>.
<PRE><CODE>void append_time_to_file( const <A HREF="CString.html">CString</A>&amp; filename )
{
   <A HREF="CTrace.html">TRACEINIT</A>( &quot;append_time_to_file()&quot;, 0 );

   <A HREF="CTimeEx.html">CTimeEx</A> the_time;

   <A HREF="CTimeEx.html">CTimeEx</A>::GetCurrentTime( the_time );

   <A HREF="CString.html">CString</A> time_string;

   time_string = the_time.Format( &quot;m%d6/5/98M%S&quot; );

   <B>CFile</B> file;

   // Open the file for appending

   if ( file.Open( filename, CFile::modeWrite | CFile::modeNoTruncate ) == FALSE )
   {
      printf( &quot;Can&#39;t open %s\n&quot;, (const char *) filename );
      return;
   }

   file.Write( (const char *) filename, filename.GetLength() );
   file.Close();
}</CODE></PRE>

<H2>API&#39;s Used</H2>

<B>CFile</B> uses the following Unix functions:

<DL COMPACT>

<LI>fclose
<LI>fflush
<LI>fopen
<LI>fread
<LI>fseek
<LI>ftell
<LI>fwrite

</DL>

<HR>

Copyright, 2000, <A HREF="mailto:sam_blackburn@pobox.com">Samuel R. Blackburn</A>
</BODY>

</HTML>
#endif // 0
