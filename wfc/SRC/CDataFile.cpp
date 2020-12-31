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
** $Workfile: CDataFile.cpp $
** $Revision: 14 $
** $Modtime: 1/17/00 8:56a $
** $Reuse Tracing Code: 1 $
*/

#if defined( _DEBUG ) && ! defined( WFC_STL )
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif // _DEBUG

void CDataChunk::GetIdentifier( DWORD identifier, CString& string )
{
   string.Empty();

   TCHAR character = 0;

   character = (BYTE) ( identifier & 0xFF );

   if ( character == 0 )
   {
      return;
   }

   string += character;

   identifier >>= 8;

   character = (BYTE) ( identifier & 0xFF );

   if ( character == 0 )
   {
      return;
   }

   string += character;

   identifier >>= 8;

   character = (BYTE) ( identifier & 0xFF );

   if ( character == 0 )
   {
      return;
   }

   string += character;

   identifier >>= 8;

   character = (BYTE) ( identifier & 0xFF );

   if ( character == 0 )
   {
      return;
   }

   string += character;
}

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

void CDataChunk::Dump( CDumpContext& dump_context ) const
{
   dump_context << TEXT( "a CDataChunk at " ) << (VOID *) this << TEXT( "\n{\n" );
   dump_context << TEXT( "   Identifier is " );

   CString debug_string;

   GetIdentifier( Identifier, debug_string );

   dump_context << debug_string << TEXT( "\n" );

   dump_context << TEXT( "   Data is " );

   Data.Dump( dump_context );
   dump_context << TEXT( "}\n" );
}

#endif // _DEBUG

CDataFile::CDataFile()
{
   WFCLTRACEINIT( TEXT( "CDataFile::CDataFile()" ) );
}

CDataFile::~CDataFile()
{
   WFCLTRACEINIT( TEXT( "CDataFile::~CDataFile()" ) );
}

BOOL CDataFile::AddData( const CDataChunk& data )
{
   WFCLTRACEINIT( TEXT( "CDataFile::AddData( CDataChunk )" ) );
   return( AddData( data.Identifier, data.Data ) );
}

BOOL CDataFile::AddData( DWORD identifier, const CByteArray& data )
{
   WFCLTRACEINIT( TEXT( "CDataFile::AddData( DWORD, CByteArray )" ) );
   return( AddData( identifier, data.GetData(), data.GetSize() ) );
}

BOOL CDataFile::AddData( DWORD identifier, const BYTE * buffer_p, DWORD number_of_bytes )
{
   WFCLTRACEINIT( TEXT( "CDataFile::AddData( DWORD, BYTE *, DWORD )" ) );

   SeekToEnd();

   // Write the identifier

   BYTE byte_1 = 0;
   BYTE byte_2 = 0;
   BYTE byte_3 = 0;
   BYTE byte_4 = 0;

   DWORD temp_long = identifier;

   byte_1 = (BYTE) (temp_long & 0xFF );
   temp_long >>= 8;

   byte_2 = (BYTE) (temp_long & 0xFF );
   temp_long >>= 8;

   byte_3 = (BYTE) (temp_long & 0xFF );
   temp_long >>= 8;

   byte_4 = (BYTE) (temp_long & 0xFF );

   BYTE buffer[ 9 ];

   buffer[ 0 ] = byte_1;
   buffer[ 1 ] = byte_2;
   buffer[ 2 ] = byte_3;
   buffer[ 3 ] = byte_4;

   // Now add the length

   temp_long = number_of_bytes;

   byte_1 = (BYTE) (temp_long & 0xFF );
   temp_long >>= 8;

   byte_2 = (BYTE) (temp_long & 0xFF );
   temp_long >>= 8;

   byte_3 = (BYTE) (temp_long & 0xFF );
   temp_long >>= 8;

   byte_4 = (BYTE) (temp_long & 0xFF );

   buffer[ 4 ] = byte_1;
   buffer[ 5 ] = byte_2;
   buffer[ 6 ] = byte_3;
   buffer[ 7 ] = byte_4;

   Write( buffer, 8 );

   // Now write the bytes

   Write( buffer_p, number_of_bytes );

   return( TRUE );
}

BOOL CDataFile::GetData( CDataChunk& data )
{
   WFCLTRACEINIT( TEXT( "CDataFile::GetData( CDataChunk )" ) );
   return( GetData( data.Identifier, data.Data ) );
}

BOOL CDataFile::GetData( DWORD& identifier, CByteArray& data )
{
   WFCLTRACEINIT( TEXT( "CDataFile::GetData( DWORD, CByteArray )" ) );

   BYTE bytes[ 9 ];

   UINT number_of_bytes_read = 0;

   try
   {
      // Get the identifier

      number_of_bytes_read = Read( &bytes, 8 );

      if ( number_of_bytes_read < 8 )
      {
         WFCTRACE( TEXT( "Can't read identifier and length" ) );
         return( FALSE );
      }

      identifier = MAKE_DATA_ID( bytes[ 0 ], bytes[ 1 ], bytes[ 2 ], bytes[ 3 ] );

#if defined( _DEBUG )

      CString debug_string;

      CDataChunk::GetIdentifier( identifier, debug_string );
      WFCTRACEVAL( TEXT( "Identifier is " ), debug_string );

#endif // _DEBUG

      // Now get the number of bytes in the chunk

      DWORD length = MAKE_DATA_LENGTH( bytes[ 4 ], bytes[ 5 ], bytes[ 6 ], bytes[ 7 ] );

      data.SetSize( length );

      number_of_bytes_read = Read( data.GetData(), length );

      if ( number_of_bytes_read < length )
      {
         WFCTRACE( TEXT( "Can't get all of the data" ) );
         identifier = 0;
         data.RemoveAll();
         return( FALSE );
      }

      return( TRUE );
   }
   catch( ... )
   {
      return( FALSE );
   }
}

// End of source

#if 0
<HTML>

<HEAD>
<TITLE>WFC - CDataFile</TITLE>
<META name="keywords" content="WFC, MFC extension library, freeware class library, Win32, source code">
<META name="description" content="The C++ class that handles chunks of RIFF data in a file.">
</HEAD>

<BODY>

<H1>CDataFile : CFile</H1>
$Revision: 14 $<BR>
<HR>

<H2>Description</H2>

This class allows you handle the input and output of
<A HREF="CDataChunk.htm">CDataChunk</A> objects easily.

<H2>Data Members</H2>
None.

<H2>Methods</H2>

<DL COMPACT>

<DT><PRE>BOOL <B>AddData</B>( DWORD identifier, const CByteArray&amp; data )
BOOL <B>AddData</B>( DWORD identifier, const BYTE * data, DWORD number_of_bytes )
BOOL <B>AddData</B>( const <A HREF="CDataChunk.htm">CDataChunk</A>&amp; data_chunk )</PRE><DD>
Sends the data chunk to the file.

<DT><PRE>BOOL <B>GetData</B>( DWORD&amp; identifier, CByteArray&amp; data )
BOOL <B>GetData</B>( <A HREF="CDataChunk.htm">CDataChunk</A>&amp; data_chunk )</PRE><DD>
Reads a data chunk from the file.

</DL>

<H2>Example</H2>
<PRE><CODE>#include &lt;wfc.h&gt;

void read_next_chunk( <B>CDataFile</B>&amp; file, <A HREF="CDataChunk.htm">CDataChunk</A>&amp; data )
{
   <A HREF="WfcTrace.htm">WFCTRACEINIT</A>( TEXT( &quot;read_next_chunk()&quot; ) );

   if ( file.GetData( data ) != FALSE )
   {
      _tprintf( TEXT( &quot;Read %lu bytes\n&quot; ), data.Data.GetSize() );
   }
}</CODE></PRE>

<HR><I>Copyright, 2000, <A HREF="mailto:wfc@pobox.com">Samuel R. Blackburn</A></I><BR>
$Workfile: CDataFile.cpp $<BR>
$Modtime: 1/17/00 8:56a $
</BODY>

</HTML>
#endif
