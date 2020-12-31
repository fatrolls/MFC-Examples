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
** $Workfile: CDataMemory.cpp $
** $Revision: 16 $
** $Modtime: 1/17/00 9:00a $
** $Reuse Tracing Code: 1 $
*/

#if defined( _DEBUG ) && ! defined( WFC_STL )
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif // _DEBUG

CDataMemory::CDataMemory()
{
   WFCLTRACEINIT( TEXT( "CDataMemory::CDataMemory()" ) );
   m_Position = 0;
}

CDataMemory::CDataMemory( const CDataMemory& source )
{
   WFCLTRACEINIT( TEXT( "CDataMemory::CDataMemory( CDataMemory )" ) );
   Copy( source );
}

CDataMemory::CDataMemory( const BYTE * buffer_p, DWORD number_of_bytes )
{
   WFCLTRACEINIT( TEXT( "CDataMemory::CDataMemory( BYTE, DWORD )" ) );
   Copy( buffer_p, number_of_bytes );
}

CDataMemory::CDataMemory( const CByteArray& source )
{
   WFCLTRACEINIT( TEXT( "CDataMemory::CDataMemory( CByteArray )" ) );
   Copy( source );
}

CDataMemory::~CDataMemory()
{
   WFCLTRACEINIT( TEXT( "CDataMemory::~CDataMemory()" ) );
   m_Position = 0;
}

void CDataMemory::Append( const CByteArray& data )
{
   WFCLTRACEINIT( TEXT( "CDataMemory::Apend( CByteArray )" ) );

   m_Data.Append( data );
   m_Position = m_Data.GetSize();
}

void CDataMemory::Append( const CDataMemory& source )
{
   WFCLTRACEINIT( TEXT( "CDataMemory::Apend( CDataMemory )" ) );
   Append( source.m_Data );
}

void CDataMemory::AppendTo( CByteArray& destination )
{
   WFCLTRACEINIT( TEXT( "CDataMemory::AppendTo()" ) );
   destination.Append( m_Data );
}

void CDataMemory::Close( void )
{
   WFCLTRACEINIT( TEXT( "CDataMemory::Close()" ) );
   m_Position = 0;
   m_Data.RemoveAll();
}

void CDataMemory::Copy( const BYTE * buffer_p, DWORD number_of_bytes )
{
   WFCLTRACEINIT( TEXT( "CDataMemory::Copy( BYTE )" ) );

   m_Position = 0;

   // We were passed a pointer, don't trust it

   try
   {
      m_Data.SetSize( number_of_bytes );
      ::memcpy( m_Data.GetData(), buffer_p, number_of_bytes );
   }
   catch( ... )
   {
      // Do Nothing
   }
}

void CDataMemory::Copy( const CByteArray& source )
{
   WFCLTRACEINIT( TEXT( "CDataMemory::Copy( CByteArray )" ) );

   m_Position = 0;
   m_Data.Copy( source );
}

void CDataMemory::Copy( const CDataMemory& source )
{
   WFCLTRACEINIT( TEXT( "CDataMemory::Copy( CDataMemory )" ) );

   m_Data.Copy( source.m_Data );
   m_Position = source.m_Position;
}

void CDataMemory::CopyTo( CByteArray& data )
{
   WFCLTRACEINIT( TEXT( "CDataMemory::CopyTo()" ) );
   data.Copy( m_Data );
}

void CDataMemory::Empty( void )
{
   WFCLTRACEINIT( TEXT( "CDataMemory::Empty()" ) );
   m_Position = 0;
   m_Data.RemoveAll();
}

void CDataMemory::Flush( void )
{
   WFCLTRACEINIT( TEXT( "CDataMemory::Flush()" ) );
}

const BYTE * CDataMemory::GetData( void ) const
{
   WFCLTRACEINIT( TEXT( "CDataMemory::GetData()" ) );
   return( m_Data.GetData() );
}

DWORD CDataMemory::GetLength( void ) const
{
   WFCLTRACEINIT( TEXT( "CDataMemory::GetLength()" ) );
   return( m_Data.GetSize() );
}

DWORD CDataMemory::GetPosition( void ) const
{
   WFCLTRACEINIT( TEXT( "CDataMemory::GetPosition()" ) );
   return( m_Position );
}

BOOL CDataMemory::Open( LPCTSTR filename, UINT )
{
   WFCLTRACEINIT( TEXT( "CDataMemory::Open()" ) );

   m_Position = 0;

   // We were passed a pointer, don't trust it
   try
   {
#if ! defined( WFC_STL )
      m_strFileName = filename;
#else // WFC_STL
      m_FileName = filename;
#endif // WFC_STL
      return( TRUE );
   }
   catch( ... )
   {
      return( FALSE );
   }
}

UINT CDataMemory::Read( void * buffer, UINT number_of_bytes_to_read )
{
   WFCLTRACEINIT( TEXT( "CDataMemory::Read()" ) );

   if ( number_of_bytes_to_read == 0 )
   {
      return( 0 );
   }

   if ( buffer == NULL )
   {
      return( 0 );
   }

   // The user passed us a pointer, don't trust it

   try
   {
      UINT number_of_bytes_read = 0;

      if ( ( m_Position + number_of_bytes_to_read ) > (DWORD) m_Data.GetSize() )
      {
         number_of_bytes_to_read = m_Data.GetSize() - m_Position;
      }

      BYTE * byte_buffer = reinterpret_cast<BYTE *>( buffer );

      if ( number_of_bytes_to_read > 0 )
      {
         for ( UINT index = 0; index < number_of_bytes_to_read; index++ )
         {
            byte_buffer[ index ] = m_Data.GetAt( m_Position );
            m_Position++;
         }

         number_of_bytes_read = number_of_bytes_to_read;
      }
      else
      {
         number_of_bytes_read = 0;
      }

      return( number_of_bytes_read );
   }
   catch( ... )
   {
      return( 0 );
   }
}

long CDataMemory::Seek( long offset, UINT from )
{
   WFCLTRACEINIT( TEXT( "CDataMemory::Seek()" ) );

   switch( from )
   {
      case begin:

         m_Position = offset;
         break;

      case current:

         m_Position += offset;
         break;

      case end:

         m_Position = m_Data.GetSize() - offset;
         break;
   }

   if ( m_Position >= m_Data.GetSize() )
   {
      m_Position = m_Data.GetSize() - 1;
   }

   if ( m_Position < 0 )
   {
      m_Position = 0;
   }

   return( m_Position );
}

void CDataMemory::Write( const void * buffer, UINT number_of_bytes_to_write )
{
   WFCLTRACEINIT( TEXT( "CDataMemory::Write()" ) );

   if ( number_of_bytes_to_write == 0 )
   {
      return;
   }

   if ( buffer == NULL )
   {
      return;
   }

   // The user sent us a pointer, don't trust it

   try
   {
      const BYTE * byte_buffer = reinterpret_cast<const BYTE *>( buffer );

      UINT index = 0;

      while( index < number_of_bytes_to_write )
      {
         // Thanks go to Darin Greaham (greaham@cyberramp.net) for finding
         // where I was not incrementing index. That caused an endless loop
         // to occur. DOH!
         // 1998-08-09

         m_Data.Add( byte_buffer[ index++ ] );
         // m_Data.Append( (const BYTE *) buffer, number_of_bytes_to_write );
      }
   }
   catch( ... )
   {
      return;
   }
}

const CDataMemory& CDataMemory::operator=( const CDataMemory& source )
{
   WFCLTRACEINIT( TEXT( "CDataMemory::operator=( CDataMemory )" ) );
   Copy( source );
   return( *this );
}

const CDataMemory& CDataMemory::operator=( const CByteArray& source )
{
   WFCLTRACEINIT( TEXT( "CDataMemory::operator=( CByteArray )" ) );
   Copy( source );
   return( *this );
}

const CDataMemory& CDataMemory::operator+=( const CByteArray& source )
{
   WFCLTRACEINIT( TEXT( "CDataMemory::operator+=( CByteArray )" ) );
   Append( source );
   return( *this );
}

const CDataMemory& CDataMemory::operator+=( const CDataMemory& source )
{
   WFCLTRACEINIT( TEXT( "CDataMemory::operator+=( CByteArray )" ) );
   Append( source );
   return( *this );
}

// End of source

#if 0
<HTML>

<HEAD>
<TITLE>WFC - CDataMemory</TITLE>
<META name="keywords" content="WFC, MFC extension library, freeware class library, Win32, source code">
<META name="description" content="The C++ class that handles chunks of RIFF data in memory.">
</HEAD>

<BODY>

<H1>CDataMemory : <A HREF="CDataFile.htm">CDataFile</A></H1>
$Revision: 16 $<BR>
<HR>

<H2>Description</H2>

This is the interesting <A HREF="CDataFile.htm">CDataFile</A>
derivative. It allows you to treat a chunk of memory like
it was a file. This makes it easy to embed <A HREF="CDataChunk.htm">CDataChunk</A>'s
within other chunks (i.e. a chunk of chunks).

<H2>Data Members</H2>
None.

<H2>Constructors</H2>

<DL COMPACT>

<DT><PRE><B>CDataMemory</B>()
<B>CDataMemory</B>( const CDataMemory&amp; source )
<B>CDataMemory</B>( const BYTE * buffer_p, DWORD number_of_bytes )
<B>CDataMemory</B>( const CByteArray&amp; source )</PRE><DD>
Constructs the object.

</DL>

<H2>Methods</H2>

<DL COMPACT>

<DT><PRE>void <B>Append</B>( const CByteArray&amp; source )
void <B>Append</B>( const CDataMemory&amp; source )</PRE><DD>
Appends the contents of <CODE>source</CODE> to this object.

<DT><PRE>void <B>AppendTo</B>( CByteArray&amp; data )</PRE><DD>
Appends the contents of this object to <CODE>data</CODE>.

<DT><PRE>void <B>Close</B>( void )</PRE><DD>
Closes the &quot;file&quot;.

<DT><PRE>void <B>Copy</B>( const BYTE * buffer, DWORD number_of_bytes_to_copy )
void <B>Copy</B>( const CByteArray&amp; buffer )
void <B>Copy</B>( const CDataMemory&amp; buffer )</PRE><DD>
Copies the contents of <CODE>buffer</CODE> to this object. It
replaces the current contents of this object with whatever is
in <CODE>buffer</CODE>.

<DT><PRE>void <B>CopyTo</B>( CByteArray&amp; data )</PRE><DD>
Replaces the contents of <CODE>data</CODE> with the contents
of this object.

<DT><PRE>void <B>Empty</B>( void )</PRE><DD>
Empties this objects.

<DT><PRE>void <B>Flush</B>( void )</PRE><DD>
Does nothing, just intercept the call.
Since we aren't really a file, it would just cause
the base class to blow up.

<DT><PRE>const BYTE * <B>GetData</B>( void ) const</PRE><DD>
Returns a pointer to the raw data.

<DT><PRE>DWORD <B>GetLength</B>( void ) const</PRE><DD>
Returns the number of bytes currently in the buffer.

<DT><PRE>DWORD <B>GetPosition</B>( void ) const</PRE><DD>
Returns the current file pointer.

<DT><PRE>BOOL <B>Open</B>( LPCTSTR filename, UINT mode )</PRE><DD>
Doesn't do anything.

<DT><PRE>UINT <B>Read</B>( void * buffer, UINT number_of_bytes_to_read )</PRE><DD>
Reads data from the buffer.

<DT><PRE>long <B>Seek</B>( long offset, UINT from )</PRE><DD>
Positions the file pointer.

<DT><PRE>void <B>Write</B>( const void * buffer, UINT number_of_bytes_to_write )</PRE><DD>
Appends data to the buffer.

</DL>

<H2>Operators</H2>

<DL COMPACT>

<DT><PRE>const CDataMemory&amp; operator <B>=</B> ( const CDataMemory&amp; source )
const CDataMemory&amp; operator <B>=</B> ( const CByteArray&amp; source )</PRE><DD>
Calls the <B>Copy</B>() method.

<DT><PRE>const CDataMemory&amp; operator <B>+=</B> ( const CDataMemory&amp; source )
const CDataMemory&amp; operator <B>+=</B> ( const CByteArray&amp; source )</PRE><DD>
Calls the <B>Append</B>() method.

</DL>

<H2>Example</H2>
<PRE><CODE>#include &lt;wfc.h&gt;

void read_next_chunk( <B>CDataMemory</B>&amp; data_in_memory, <A HREF="CDataChunk.htm">CDataChunk</A>&amp; data )
{
   <A HREF="WfcTrace.htm">WFCTRACEINIT</A>( TEXT( &quot;read_next_chunk()&quot; ) );

   data_in_memory.GetData( data );

   _tprintf( TEXT( &quot;Read %lu bytes\n&quot; ), data.Data.GetSize() );
}</CODE></PRE>

<HR><I>Copyright, 2000, <A HREF="mailto:wfc@pobox.com">Samuel R. Blackburn</A></I><BR>
$Workfile: CDataMemory.cpp $<BR>
$Modtime: 1/17/00 9:00a $
</BODY>
</HTML>
#endif
