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
** $Workfile: CUUCoding.cpp $
** $Revision: 6 $
** $Modtime: 1/17/00 9:25a $
** $Reuse Tracing Code: 1 $
*/

#if defined( _DEBUG ) && ! defined( WFC_STL )
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif // _DEBUG

#define UU_DECODE_CHARACTER( _c ) static_cast< BYTE >( ( (_c) - 0x20 ) & 0x3F )
#define UU_ENCODE_BYTE(      _c ) static_cast< BYTE >( (_c) ? ( (_c) & 0x3F ) + 0x20 : '`' )

CUUCoding::CUUCoding()
{
   WFCLTRACEINIT( TEXT( "CUUCoding::CUUCoding()" ) );
}

CUUCoding::~CUUCoding()
{
   WFCLTRACEINIT( TEXT( "CUUCoding::~CUUCoding()" ) );
}

BOOL CUUCoding::Decode( const CByteArray& source, CByteArray& destination )
{
   WFCLTRACEINIT( TEXT( "CUUCoding::Decode()" ) );

   // Start with an empty destination

   destination.RemoveAll();

   BOOL return_value = FALSE;

   BYTE byte_to_add = 0;
   BYTE character_1 = 0;
   BYTE character_2 = 0;
   BYTE character_3 = 0;
   BYTE character_4 = 0;

   int index                             = 0;
   int number_of_bytes_to_decode         = source.GetSize();
   int number_of_characters_in_this_line = 0;
   int line_index                        = 0;

   // Since we're decoding, we are most likely in a performance-minded
   // part of an application, let's go for a speedy method for accessing
   // the source data.

   const BYTE * input_buffer = source.GetData();

   while( index < number_of_bytes_to_decode )
   {
      // Skip space characters...

      while( index < number_of_bytes_to_decode &&
             ( input_buffer[ index ] == CARRIAGE_RETURN ||
               input_buffer[ index ] == LINE_FEED       ) )
      {
         index++;
      }

      if ( index >= number_of_bytes_to_decode )
      {
         return( TRUE );
      }

      number_of_characters_in_this_line = UU_DECODE_CHARACTER( input_buffer[ index ] );

      index++;

      line_index = 0;

      while( line_index < number_of_characters_in_this_line )
      {
         if ( index < number_of_bytes_to_decode )
         {
            character_1 = UU_DECODE_CHARACTER( input_buffer[ index ] );
            index++;
         }
         else
         {
            character_1 = 0xFF; // Invalid character
         }

         if ( index < number_of_bytes_to_decode )
         {
            character_2 = UU_DECODE_CHARACTER( input_buffer[ index ] );
            index++;
         }
         else
         {
            character_2 = 0xFF; // Invalid character
         }

         if ( index < number_of_bytes_to_decode )
         {
            character_3 = UU_DECODE_CHARACTER( input_buffer[ index ] );
            index++;
         }
         else
         {
            character_3 = 0xFF; // Invalid character
         }

         if ( index < number_of_bytes_to_decode )
         {
            character_4 = UU_DECODE_CHARACTER( input_buffer[ index ] );
            index++;
         }
         else
         {
            character_4 = 0xFF; // Invalid character
         }

         // Whew! If we get here it means we can translate the 4 characters
         // to three bytes.

         line_index++;

         if ( line_index <= number_of_characters_in_this_line )
         {
            byte_to_add = static_cast< BYTE >( ( character_1 << 2 ) | ( character_2 >> 4 ) );
            destination.Add( byte_to_add );
         }

         line_index++;

         if ( line_index <= number_of_characters_in_this_line )
         {
            byte_to_add = static_cast< BYTE >( ( character_2 << 4 ) | ( character_3 >> 2 ) );
            destination.Add( byte_to_add );
         }

         line_index++;

         if ( line_index <= number_of_characters_in_this_line )
         {
            byte_to_add = static_cast< BYTE >( ( character_3 << 6 ) | ( character_4 ) );
            destination.Add( byte_to_add );
         }
      }
   }

   return( return_value );
}

BOOL CUUCoding::Decode( const CString& source, CByteArray& destination )
{
   WFCLTRACEINIT( TEXT( "CUUCoding::Decode( CString )" ) );

   // Start with an empty destination

   BOOL return_value = FALSE;

   int loop_index                = 0;
   int number_of_bytes_to_decode = source.GetLength();

   // Since we're decoding, we are most likely in a performance-minded
   // part of an application, let's go for a speedy method for accessing
   // the source data.

   LPCTSTR input_buffer = (LPCTSTR) source;

   CByteArray bytes_to_decode;

   bytes_to_decode.SetSize( number_of_bytes_to_decode );

   BYTE * buffer = bytes_to_decode.GetData();

   try
   {
      while( loop_index < number_of_bytes_to_decode )
      {
         buffer[ loop_index ] = static_cast< BYTE >( input_buffer[ loop_index ] );
         loop_index++;
      }

      return_value = Decode( bytes_to_decode, destination );
   }
   catch( ... )
   {
      return( FALSE );
   }

   return( return_value );
}

BOOL CUUCoding::Encode( const CByteArray& source, CByteArray& destination )
{
   WFCLTRACEINIT( TEXT( "CUUCoding::Encode()" ) );

   // Always start with an empty destination
   destination.RemoveAll();

   // Output bytes 45 at a time

   int number_of_bytes_to_encode = source.GetSize();
   int index                     = 0;
   int line_index                = 0;

   BYTE byte_to_encode_1 = 0;
   BYTE byte_to_encode_2 = 0;
   BYTE byte_to_encode_3 = 0;

   BYTE character_to_output_1 = 0;
   BYTE character_to_output_2 = 0;
   BYTE character_to_output_3 = 0;
   BYTE character_to_output_4 = 0;

   const BYTE * input_buffer = source.GetData();

   while( index < number_of_bytes_to_encode )
   {
      line_index = 0;

      if ( index > 0 && ( ( index % 44 ) == 0 ) )
      {
         WFCTRACE( TEXT( "TROUBLE!" ) );
      }

      if ( ( number_of_bytes_to_encode - index ) >= 45 )
      {
         // Output the number of bytes in this line
         destination.Add( UU_ENCODE_BYTE( 45 ) );

         while( line_index < 45 )
         {
            byte_to_encode_1 = input_buffer[ index ];
            line_index++;
            index++;

            byte_to_encode_2 = input_buffer[ index ];
            line_index++;
            index++;

            byte_to_encode_3 = input_buffer[ index ];
            line_index++;
            index++;

            character_to_output_1 = static_cast< BYTE >( byte_to_encode_1 >> 2 );
            character_to_output_2 = static_cast< BYTE >( ( ( byte_to_encode_1 << 4 ) & 0x30 ) | ( ( byte_to_encode_2 >> 4 ) & 0x0F ) );
            character_to_output_3 = static_cast< BYTE >( ( ( byte_to_encode_2 << 2 ) & 0x3C ) | ( ( byte_to_encode_3 >> 6 ) & 0x03 ) );
            character_to_output_4 = static_cast< BYTE >( byte_to_encode_3 & 0x3F );

            // These lines are here for easy debugging

            character_to_output_1 = UU_ENCODE_BYTE( character_to_output_1 );
            character_to_output_2 = UU_ENCODE_BYTE( character_to_output_2 );
            character_to_output_3 = UU_ENCODE_BYTE( character_to_output_3 );
            character_to_output_4 = UU_ENCODE_BYTE( character_to_output_4 );

            destination.Add( character_to_output_1 );
            destination.Add( character_to_output_2 );
            destination.Add( character_to_output_3 );
            destination.Add( character_to_output_4 );
         }
      }
      else
      {
         // Output the number of bytes in this line
         destination.Add( UU_ENCODE_BYTE( number_of_bytes_to_encode - index ) );

         while( index < number_of_bytes_to_encode )
         {
            if ( index < number_of_bytes_to_encode )
            {
               byte_to_encode_1 = input_buffer[ index ];
            }
            else
            {
               byte_to_encode_1 = 0x00;
            }

            index++;

            if ( index < number_of_bytes_to_encode )
            {
               byte_to_encode_2 = input_buffer[ index ];
            }
            else
            {
               byte_to_encode_2 = 0x00;
            }

            index++;

            if ( index < number_of_bytes_to_encode )
            {
               byte_to_encode_3 = input_buffer[ index ];
            }
            else
            {
               byte_to_encode_3 = 0x00;
            }

            index++;

            character_to_output_1 = static_cast< BYTE >( byte_to_encode_1 >> 2 );
            character_to_output_2 = static_cast< BYTE >( ( ( byte_to_encode_1 << 4 ) & 0x30 ) | ( ( byte_to_encode_2 >> 4 ) & 0x0F ) );
            character_to_output_3 = static_cast< BYTE >( ( ( byte_to_encode_2 << 2 ) & 0x3C ) | ( ( byte_to_encode_3 >> 6 ) & 0x03 ) );
            character_to_output_4 = static_cast< BYTE >( byte_to_encode_3 & 0x3F );

            destination.Add( UU_ENCODE_BYTE( character_to_output_1 ) );
            destination.Add( UU_ENCODE_BYTE( character_to_output_2 ) );
            destination.Add( UU_ENCODE_BYTE( character_to_output_3 ) );
            destination.Add( UU_ENCODE_BYTE( character_to_output_4 ) );
         }
      }

      destination.Add( CARRIAGE_RETURN );
   }

   return( TRUE );
}

BOOL CUUCoding::Encode( const CByteArray& source, CString& destination )
{
   WFCLTRACEINIT( TEXT( "CUUCoding::Encode( CString )" ) );

   destination.Empty();

   BOOL return_value = FALSE;

   CByteArray encoded_bytes;

   return_value = Encode( source, encoded_bytes );

   if ( return_value == FALSE )
   {
      return( FALSE );
   }

   // We have to do this the slow way to preserve UNICODE...

   int loop_index           = 0;
   int number_of_characters = encoded_bytes.GetSize();

   const BYTE * encoded_buffer = encoded_bytes.GetData();

   while( loop_index < number_of_characters )
   {
      destination += static_cast< TCHAR >( encoded_buffer[ loop_index ] );

      loop_index++;
   }

   return( return_value );
}

// End of source

#if 0
<HTML>

<HEAD>
<TITLE>WFC - CUUCoding</TITLE>
<META name="keywords" content="WFC, MFC extension library, freeware class library, Win32, UUENCODE, UUDECODE, source code">
<META name="description" content="This C++ class let's you encode and decode bytes to text using Unix-to-Unix (UU) coding.">
</HEAD>

<BODY>

<H1>CUUCoding</H1>
$Revision: 6 $<BR><HR>

<H2>Description</H2>
This class gives you the ability to encode/decode data using Unix-to-Unix (UU).

<H2>Constructors</H2>

<DL COMPACT>

<DT><PRE><B>CUUCoding</B>()<DD>
Constructs this object.

</DL>

<H2>Methods</H2>

<DL COMPACT>

<DT><PRE>BOOL <B>Decode</B>( const CByteArray&amp; source, CByteArray&amp; destination )
BOOL <B>Decode</B>( const CString&amp;    source, CByteArray&amp; destination )</PRE><DD>
This method takes base64 encoded text and produces the bytes. It decodes
the base64 encoding.

<DT><PRE>BOOL <B>Encode</B>( const CByteArray&amp; source, CByteArray&amp; destination )
BOOL <B>Encode</B>( const CByteArray&amp; source, CString&amp;    destination )</PRE><DD>
This method takes bytes and turns them into base64 text.

</DL>

<H2>Example</H2>
<PRE><CODE>#include &lt;wfc.h&gt;
#pragma hdrstop

int _tmain( int number_of_command_line_arguments, LPCTSTR command_line_arguments[] )
{
   <A HREF="WfcTrace.htm">WFCTRACEINIT</A>( TEXT( &quot;_tmain()&quot; ) );

   CByteArray bytes;

   get_file_contents( command_line_arguments[ 0 ], bytes );

   <B>CUUCoding</B> encoder;

   CString encoded_data;

   if ( encoder.Encode( bytes, encoded_data ) != FALSE )
   {
      _tprintf( TEXT( &quot;%s\n&quot;, (LPCTSTR) encoded_data );
   }
}</CODE></PRE>

<HR><I>Copyright, 2000, <A HREF="mailto:wfc@pobox.com">Samuel R. Blackburn</A></I><BR>
$Workfile: CUUCoding.cpp $<BR>
$Modtime: 1/17/00 9:25a $
</BODY>

</HTML>
#endif
