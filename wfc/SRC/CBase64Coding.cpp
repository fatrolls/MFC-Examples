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
** $Workfile: CBase64Coding.cpp $
** $Revision: 14 $
** $Modtime: 5/12/00 3:39p $
** $Reuse Tracing Code: 1 $
*/

#if defined( _DEBUG ) && ! defined( WFC_STL )
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#define new DEBUG_NEW
#endif // _DEBUG

#define END_OF_BASE64_ENCODED_DATA           ('=')
#define BASE64_END_OF_BUFFER                 (0xFD)
#define BASE64_IGNORABLE_CHARACTER           (0xFE)
#define BASE64_UNKNOWN_VALUE                 (0xFF)
#define BASE64_NUMBER_OF_CHARACTERS_PER_LINE (72)

static inline BYTE __get_character( const BYTE * buffer, const BYTE * decoder_table, int& index, int size_of_buffer )
{
   BYTE return_value = 0;

   do
   {
      if ( index >= size_of_buffer )
      {
         return( BASE64_END_OF_BUFFER );
      }

      return_value = buffer[ index ];
      index++;
   }
   while( return_value != END_OF_BASE64_ENCODED_DATA &&
          decoder_table[ return_value ] == BASE64_IGNORABLE_CHARACTER );

   return( return_value );
}

CBase64Coding::CBase64Coding()
{
   WFCLTRACEINIT( TEXT( "CBase64Coding::CBase64Coding()" ) );
   m_DecoderTable[ 0 ] = 0x00;
}

CBase64Coding::~CBase64Coding()
{
   WFCLTRACEINIT( TEXT( "CBase64Coding::~CBase64Coding()" ) );
}

void CBase64Coding::m_InitializeDecoderTable( void )
{
   WFCLTRACEINIT( TEXT( "CBase64Coding::m_InitializeDecoderTable()" ) );

   // Fill the table with an invalid value. If the decoder receives
   // this value as a result of a lookup, it knows that the input
   // character must have been an invalid one.

   ::memset( m_DecoderTable, BASE64_UNKNOWN_VALUE, sizeof( m_DecoderTable ) );

   // Now let's fill the table with translatable values
   // The table is loaded with table[ ASCII_VALUE ] = TRANSLATED_VALUE

    m_DecoderTable[  43 ] = 62;
    m_DecoderTable[  47 ] = 63;
    m_DecoderTable[  48 ] = 52;
    m_DecoderTable[  49 ] = 53;
    m_DecoderTable[  50 ] = 54;
    m_DecoderTable[  51 ] = 55;
    m_DecoderTable[  52 ] = 56;
    m_DecoderTable[  53 ] = 57;
    m_DecoderTable[  54 ] = 58;
    m_DecoderTable[  55 ] = 59;
    m_DecoderTable[  56 ] = 60;
    m_DecoderTable[  57 ] = 61;
    m_DecoderTable[  65 ] = 0;
    m_DecoderTable[  66 ] = 1;
    m_DecoderTable[  67 ] = 2;
    m_DecoderTable[  68 ] = 3;
    m_DecoderTable[  69 ] = 4;
    m_DecoderTable[  70 ] = 5;
    m_DecoderTable[  71 ] = 6;
    m_DecoderTable[  72 ] = 7;
    m_DecoderTable[  73 ] = 8;
    m_DecoderTable[  74 ] = 9;
    m_DecoderTable[  75 ] = 10;
    m_DecoderTable[  76 ] = 11;
    m_DecoderTable[  77 ] = 12;
    m_DecoderTable[  78 ] = 13;
    m_DecoderTable[  79 ] = 14;
    m_DecoderTable[  80 ] = 15;
    m_DecoderTable[  81 ] = 16;
    m_DecoderTable[  82 ] = 17;
    m_DecoderTable[  83 ] = 18;
    m_DecoderTable[  84 ] = 19;
    m_DecoderTable[  85 ] = 20;
    m_DecoderTable[  86 ] = 21;
    m_DecoderTable[  87 ] = 22;
    m_DecoderTable[  88 ] = 23;
    m_DecoderTable[  89 ] = 24;
    m_DecoderTable[  90 ] = 25;
    m_DecoderTable[  97 ] = 26;
    m_DecoderTable[  98 ] = 27;
    m_DecoderTable[  99 ] = 28;
    m_DecoderTable[ 100 ] = 29;
    m_DecoderTable[ 101 ] = 30;
    m_DecoderTable[ 102 ] = 31;
    m_DecoderTable[ 103 ] = 32;
    m_DecoderTable[ 104 ] = 33;
    m_DecoderTable[ 105 ] = 34;
    m_DecoderTable[ 106 ] = 35;
    m_DecoderTable[ 107 ] = 36;
    m_DecoderTable[ 108 ] = 37;
    m_DecoderTable[ 109 ] = 38;
    m_DecoderTable[ 110 ] = 39;
    m_DecoderTable[ 111 ] = 40;
    m_DecoderTable[ 112 ] = 41;
    m_DecoderTable[ 113 ] = 42;
    m_DecoderTable[ 114 ] = 43;
    m_DecoderTable[ 115 ] = 44;
    m_DecoderTable[ 116 ] = 45;
    m_DecoderTable[ 117 ] = 46;
    m_DecoderTable[ 118 ] = 47;
    m_DecoderTable[ 119 ] = 48;
    m_DecoderTable[ 120 ] = 49;
    m_DecoderTable[ 121 ] = 50;
    m_DecoderTable[ 122 ] = 51;

    // OK, there's our translation table, now let's be a little
    // forgiving about end-of-lines, tabs, spaces, etc.

    m_DecoderTable[ 9               ] = BASE64_IGNORABLE_CHARACTER; // TAB character (Tabs suck!)
    m_DecoderTable[ 32              ] = BASE64_IGNORABLE_CHARACTER; // Space character
    m_DecoderTable[ CARRIAGE_RETURN ] = BASE64_IGNORABLE_CHARACTER;
    m_DecoderTable[ LINE_FEED       ] = BASE64_IGNORABLE_CHARACTER;
}

BOOL CBase64Coding::Decode( const CByteArray& source, CByteArray& destination )
{
   WFCLTRACEINIT( TEXT( "CBase64Coding::Decode()" ) );

   if ( m_DecoderTable[ 0 ] == 0x00 )
   {
      m_InitializeDecoderTable();
   }

   BOOL return_value = FALSE;

   BYTE byte_to_add = 0;
   BYTE character_1 = 0;
   BYTE character_2 = 0;
   BYTE character_3 = 0;
   BYTE character_4 = 0;

   int index                     = 0;
   int number_of_bytes_to_decode = source.GetSize();

   DWORD add_index = (DWORD) ( (double) number_of_bytes_to_decode * (double) 0.75 ) + 1;

   destination.SetSize( add_index );
   add_index = 0;

   // Since we're decoding, we are most likely in a performance-minded
   // part of an application, let's go for a speedy method for accessing
   // the source data.

   const BYTE * input_buffer = source.GetData();

   while( index < number_of_bytes_to_decode )
   {
      character_1 = __get_character( input_buffer, m_DecoderTable, index, number_of_bytes_to_decode );

      if ( character_1 != END_OF_BASE64_ENCODED_DATA )
      {
         if ( m_DecoderTable[ character_1 ] == BASE64_UNKNOWN_VALUE )
         {
            WFCTRACEVAL( TEXT( "Character 1 Failed translation at index " ), index );
            destination.RemoveAll();
            return( FALSE );
         }

         character_2 = __get_character( input_buffer, m_DecoderTable, index, number_of_bytes_to_decode );

         if ( character_2 != END_OF_BASE64_ENCODED_DATA )
         {
            if ( m_DecoderTable[ character_2 ] == BASE64_UNKNOWN_VALUE )
            {
               WFCTRACEVAL( TEXT( "Character 2 Failed translation at index " ), index );
               destination.RemoveAll();
               return( FALSE );
            }

            character_3 = __get_character( input_buffer, m_DecoderTable, index, number_of_bytes_to_decode );

            if ( character_3 != END_OF_BASE64_ENCODED_DATA )
            {
               if ( m_DecoderTable[ character_3 ] == BASE64_UNKNOWN_VALUE )
               {
                  WFCTRACEVAL( TEXT( "Character 3 Failed translation at index " ), index );
                  destination.RemoveAll();
                  return( FALSE );
               }

               character_4 = __get_character( input_buffer, m_DecoderTable, index, number_of_bytes_to_decode );

               if ( character_4 != END_OF_BASE64_ENCODED_DATA )
               {
                  if ( m_DecoderTable[ character_4 ] == BASE64_UNKNOWN_VALUE )
                  {
                     WFCTRACEVAL( TEXT( "Character 4 Failed translation at index " ), index );
                     destination.RemoveAll();
                     return( FALSE );
                  }
               }

               if ( character_2 == BASE64_END_OF_BUFFER ||
                    character_3 == BASE64_END_OF_BUFFER ||
                    character_4 == BASE64_END_OF_BUFFER )
               { 
                  WFCTRACE( TEXT( "Not enough translatable data" ) );
                  destination.RemoveAll();
                  return( FALSE );
               }
            }
            else
            {
               character_4 = END_OF_BASE64_ENCODED_DATA;
            }
         }
         else
         {
            character_3 = END_OF_BASE64_ENCODED_DATA;
            character_4 = END_OF_BASE64_ENCODED_DATA;
         }
      }
      else
      {
         character_2 = END_OF_BASE64_ENCODED_DATA;
         character_3 = END_OF_BASE64_ENCODED_DATA;
         character_4 = END_OF_BASE64_ENCODED_DATA;
      }

      if ( character_1 == END_OF_BASE64_ENCODED_DATA ||
           character_2 == END_OF_BASE64_ENCODED_DATA )
      {
         destination.SetSize( add_index );
         return( TRUE );
      }

      character_1 = m_DecoderTable[ character_1 ];
      character_2 = m_DecoderTable[ character_2 ];

      byte_to_add = static_cast< BYTE>( ( ( character_1 << 2 ) | ( ( character_2 & 0x30 ) >> 4 ) ) );

      destination.SetAt( add_index, byte_to_add );
      add_index++;

      if ( character_3 == END_OF_BASE64_ENCODED_DATA )
      {
         destination.SetSize( add_index );
         return( TRUE );
      }

      character_3 = m_DecoderTable[ character_3 ];

      byte_to_add = static_cast< BYTE >( ( ( ( ( character_2 & 0x0F ) << 4 ) | ( ( character_3 & 0x3C ) >> 2 ) ) ) );

      destination.SetAt( add_index, byte_to_add );
      add_index++;

      if ( character_4 == END_OF_BASE64_ENCODED_DATA )
      {
         destination.SetSize( add_index );
         return( TRUE );
      }

      character_4 = m_DecoderTable[ character_4 ];

      byte_to_add = static_cast< BYTE >( ( ( ( character_3 & 0x03 ) << 6 ) | character_4 ) );

      destination.SetAt( add_index, byte_to_add );
      add_index++;
   }

   destination.SetSize( add_index );

   return( return_value );
}

BOOL CBase64Coding::Decode( const CString& source, CByteArray& destination )
{
   WFCLTRACEINIT( TEXT( "CBase64Coding::Decode( CString )" ) );

   if ( m_DecoderTable[ 0 ] == 0x00 )
   {
      m_InitializeDecoderTable();
   }

   BOOL return_value = FALSE;

   BYTE byte_to_add = 0;
   BYTE character_1 = 0;
   BYTE character_2 = 0;
   BYTE character_3 = 0;
   BYTE character_4 = 0;

   int index                     = 0;
   int number_of_bytes_to_decode = source.GetLength();

   DWORD add_index = (DWORD) ( (double) number_of_bytes_to_decode * (double) 0.75 ) + 1;

   destination.SetSize( add_index );
   add_index = 0;

   // Since we're decoding, we are most likely in a performance-minded
   // part of an application, let's go for a speedy method for accessing
   // the source data.

   LPCTSTR input_buffer = source;

   while( index < number_of_bytes_to_decode )
   {
      character_1 = __get_character( reinterpret_cast< const BYTE * >( input_buffer ), m_DecoderTable, index, number_of_bytes_to_decode );

      if ( character_1 != END_OF_BASE64_ENCODED_DATA )
      {
         if ( m_DecoderTable[ character_1 ] == BASE64_UNKNOWN_VALUE )
         {
            WFCTRACEVAL( TEXT( "Character 1 Failed translation at index " ), index );
            destination.RemoveAll();
            return( FALSE );
         }

         character_2 = __get_character( reinterpret_cast< const BYTE * >( input_buffer ), m_DecoderTable, index, number_of_bytes_to_decode );

         if ( character_2 != END_OF_BASE64_ENCODED_DATA )
         {
            if ( m_DecoderTable[ character_2 ] == BASE64_UNKNOWN_VALUE )
            {
               WFCTRACEVAL( TEXT( "Character 2 Failed translation at index " ), index );
               destination.RemoveAll();
               return( FALSE );
            }

            character_3 = __get_character( reinterpret_cast< const BYTE * >( input_buffer ), m_DecoderTable, index, number_of_bytes_to_decode );

            if ( character_3 != END_OF_BASE64_ENCODED_DATA )
            {
               if ( m_DecoderTable[ character_3 ] == BASE64_UNKNOWN_VALUE )
               {
                  WFCTRACEVAL( TEXT( "Character 3 Failed translation at index " ), index );
                  destination.RemoveAll();
                  return( FALSE );
               }

               character_4 = __get_character( reinterpret_cast< const BYTE * >( input_buffer ), m_DecoderTable, index, number_of_bytes_to_decode );

               if ( character_4 != END_OF_BASE64_ENCODED_DATA )
               {
                  if ( m_DecoderTable[ character_4 ] == BASE64_UNKNOWN_VALUE )
                  {
                     WFCTRACEVAL( TEXT( "Character 4 Failed translation at index " ), index );
                     destination.RemoveAll();
                     return( FALSE );
                  }
               }

               if ( character_2 == BASE64_END_OF_BUFFER ||
                    character_3 == BASE64_END_OF_BUFFER ||
                    character_4 == BASE64_END_OF_BUFFER )
               { 
                  WFCTRACE( TEXT( "Not enough translatable data" ) );
                  destination.RemoveAll();
                  return( FALSE );
               }
            }
            else
            {
               character_4 = END_OF_BASE64_ENCODED_DATA;
            }
         }
         else
         {
            character_3 = END_OF_BASE64_ENCODED_DATA;
            character_4 = END_OF_BASE64_ENCODED_DATA;
         }
      }
      else
      {
         character_2 = END_OF_BASE64_ENCODED_DATA;
         character_3 = END_OF_BASE64_ENCODED_DATA;
         character_4 = END_OF_BASE64_ENCODED_DATA;
      }

      if ( character_1 == END_OF_BASE64_ENCODED_DATA ||
           character_2 == END_OF_BASE64_ENCODED_DATA )
      {
         destination.SetSize( add_index );
         return( TRUE );
      }

      character_1 = m_DecoderTable[ character_1 ];
      character_2 = m_DecoderTable[ character_2 ];

      byte_to_add = static_cast< BYTE>( ( ( character_1 << 2 ) | ( ( character_2 & 0x30 ) >> 4 ) ) );

      destination.SetAt( add_index, byte_to_add );
      add_index++;

      if ( character_3 == END_OF_BASE64_ENCODED_DATA )
      {
         destination.SetSize( add_index );
         return( TRUE );
      }

      character_3 = m_DecoderTable[ character_3 ];

      byte_to_add = static_cast< BYTE >( ( ( ( ( character_2 & 0x0F ) << 4 ) | ( ( character_3 & 0x3C ) >> 2 ) ) ) );

      destination.SetAt( add_index, byte_to_add );
      add_index++;

      if ( character_4 == END_OF_BASE64_ENCODED_DATA )
      {
         destination.SetSize( add_index );
         return( TRUE );
      }

      character_4 = m_DecoderTable[ character_4 ];

      byte_to_add = static_cast< BYTE >( ( ( ( character_3 & 0x03 ) << 6 ) | character_4 ) );

      destination.SetAt( add_index, byte_to_add );
      add_index++;
   }

   destination.SetSize( add_index );

   return( return_value );
}

BOOL CBase64Coding::Encode( const CByteArray& source, CByteArray& destination )
{
   WFCLTRACEINIT( TEXT( "CBase64Coding::Encode()" ) );

   // We don't want to make this static so we can reduce our
   // footprint in the library

   const char alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

   int source_index              = 0;
   int number_of_bytes_to_encode = source.GetSize();
   
   BYTE byte_to_add = 0;
   BYTE byte_1      = 0;
   BYTE byte_2      = 0;
   BYTE byte_3      = 0;

   const BYTE * input_buffer = source.GetData();

   DWORD add_index = (DWORD) ( (double) number_of_bytes_to_encode / (double) 0.75 ) + 1;
   add_index += ( ( number_of_bytes_to_encode % 3 ) + 1 );

   destination.SetSize( add_index );
   add_index = 0;

   while( source_index < number_of_bytes_to_encode )
   {
      // Output the first byte

      byte_1 = input_buffer[ source_index ];
      byte_to_add = alphabet[ ( byte_1 >> 2 ) ];

      destination.SetAt( add_index, byte_to_add );
      add_index++;

      source_index++;

      if ( source_index >= number_of_bytes_to_encode )
      {
         // We're at the end of the data to encode

         byte_2 = 0;
         byte_to_add = alphabet[ ( ( ( byte_1 & 0x03 ) << 4 ) | ( ( byte_2 & 0xF0 ) >> 4 ) ) ];

         destination.SetAt( add_index, byte_to_add );
         add_index++;

         destination.SetAt( add_index, END_OF_BASE64_ENCODED_DATA );
         add_index++;

         destination.SetAt( add_index, END_OF_BASE64_ENCODED_DATA );
         add_index++;

         destination.SetSize( add_index );
         return( TRUE );
      }
      else
      {
         byte_2 = input_buffer[ source_index ];
      }

      byte_to_add = alphabet[ ( ( ( byte_1 & 0x03 ) << 4 ) | ( ( byte_2 & 0xF0 ) >> 4 ) ) ];
      destination.SetAt( add_index, byte_to_add );
      add_index++;

      source_index++;

      if ( source_index >= number_of_bytes_to_encode )
      {
         // We ran out of bytes, we need to add the last half of byte_2 and pad
         byte_3 = 0;

         byte_to_add = alphabet[ ( ( ( byte_2 & 0x0F ) << 2 ) | ( ( byte_3 & 0xC0 ) >> 6 ) ) ];

         destination.SetAt( add_index, byte_to_add );
         add_index++;

         destination.SetAt( add_index, END_OF_BASE64_ENCODED_DATA );
         add_index++;

         destination.SetSize( add_index );
         return( TRUE );
      }
      else
      {
         byte_3 = input_buffer[ source_index ];
      }

      source_index++;

      byte_to_add = alphabet[ ( ( ( byte_2 & 0x0F ) << 2 ) | ( ( byte_3 & 0xC0 ) >> 6 ) ) ];

      destination.SetAt( add_index, byte_to_add );
      add_index++;

      byte_to_add = alphabet[ ( byte_3 & 0x3F ) ];

      destination.SetAt( add_index, byte_to_add );
      add_index++;
   }

   destination.SetAt( add_index, END_OF_BASE64_ENCODED_DATA );
   add_index++;

   destination.SetSize( add_index );
   return( TRUE );
}

BOOL CBase64Coding::Encode( const CByteArray& source, CString& destination_string )
{
   WFCLTRACEINIT( TEXT( "CBase64Coding::Encode( CString )" ) );

   const char alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

   int loop_index                = 0;
   int number_of_bytes_to_encode = source.GetSize();

   BYTE byte_to_add = 0;
   BYTE byte_1      = 0;
   BYTE byte_2      = 0;
   BYTE byte_3      = 0;

   const BYTE * input_buffer = source.GetData();

   DWORD number_of_bytes_encoded = (DWORD) ( (double) number_of_bytes_to_encode / (double) 0.75 ) + 1;

   // Now add in the CR/LF pairs, each line is truncated at 72 characters

   // 2000-05-12
   // Thanks go to Ilia Golubev (ilia@varicom.co.il) for finding a bug here.
   // I was using number_of_bytes_to_encode rather than number_of_bytes_encoded.

   number_of_bytes_encoded += (DWORD)( ( ( number_of_bytes_encoded / BASE64_NUMBER_OF_CHARACTERS_PER_LINE ) + 1 ) * 2 );

   LPTSTR destination = destination_string.GetBuffer( number_of_bytes_encoded );

   number_of_bytes_encoded = 0;

   while( loop_index < number_of_bytes_to_encode )
   {
      // Output the first byte

      byte_1 = input_buffer[ loop_index ];
      byte_to_add = alphabet[ ( byte_1 >> 2 ) ];

      destination[ number_of_bytes_encoded ] = static_cast< TCHAR >( byte_to_add );
      number_of_bytes_encoded++;

      loop_index++;

      if ( loop_index >= number_of_bytes_to_encode )
      {
         // We're at the end of the data to encode

         byte_2 = 0;
         byte_to_add = alphabet[ ( ( ( byte_1 & 0x03 ) << 4 ) | ( ( byte_2 & 0xF0 ) >> 4 ) ) ];

         destination[ number_of_bytes_encoded ] = static_cast< TCHAR >( byte_to_add );
         number_of_bytes_encoded++;

         destination[ number_of_bytes_encoded ] = static_cast< TCHAR >( END_OF_BASE64_ENCODED_DATA );
         number_of_bytes_encoded++;

         destination[ number_of_bytes_encoded ] = static_cast< TCHAR >( END_OF_BASE64_ENCODED_DATA );

         // 1999-09-01
         // Thanks go to Yurong Lin (ylin@dial.pipex.com) for finding a bug here.
         // We must NULL terminate the string before letting CString have the buffer back.

         destination[ number_of_bytes_encoded + 1 ] = 0;

         destination_string.ReleaseBuffer( -1 );

         return( TRUE );
      }
      else
      {
         byte_2 = input_buffer[ loop_index ];
      }

      byte_to_add = alphabet[ ( ( ( byte_1 & 0x03 ) << 4 ) | ( ( byte_2 & 0xF0 ) >> 4 ) ) ];

      destination[ number_of_bytes_encoded ] = static_cast< TCHAR >( byte_to_add );
      number_of_bytes_encoded++;

      loop_index++;

      if ( loop_index >= number_of_bytes_to_encode )
      {
         // We ran out of bytes, we need to add the last half of byte_2 and pad
         byte_3 = 0;

         byte_to_add = alphabet[ ( ( ( byte_2 & 0x0F ) << 2 ) | ( ( byte_3 & 0xC0 ) >> 6 ) ) ];

         destination[ number_of_bytes_encoded ] = static_cast< TCHAR >( byte_to_add );
         number_of_bytes_encoded++;

         destination[ number_of_bytes_encoded ] = static_cast< TCHAR >( END_OF_BASE64_ENCODED_DATA );

         // 1999-09-01
         // Thanks go to Yurong Lin (ylin@dial.pipex.com) for finding a bug here.
         // We must NULL terminate the string before letting CString have the buffer back.

         destination[ number_of_bytes_encoded + 1 ] = 0;

         destination_string.ReleaseBuffer( -1 );

         return( TRUE );
      }
      else
      {
         byte_3 = input_buffer[ loop_index ];
      }

      loop_index++;

      byte_to_add = alphabet[ ( ( ( byte_2 & 0x0F ) << 2 ) | ( ( byte_3 & 0xC0 ) >> 6 ) ) ];

      destination[ number_of_bytes_encoded ] = static_cast< TCHAR >( byte_to_add );
      number_of_bytes_encoded++;

      byte_to_add = alphabet[ ( byte_3 & 0x3F ) ];

      destination[ number_of_bytes_encoded ] = static_cast< TCHAR >( byte_to_add );
      number_of_bytes_encoded++;

      if ( ( number_of_bytes_encoded % BASE64_NUMBER_OF_CHARACTERS_PER_LINE ) == 0 )
      {
         destination[ number_of_bytes_encoded ] = static_cast< TCHAR >( CARRIAGE_RETURN );
         number_of_bytes_encoded++;

         destination[ number_of_bytes_encoded ] = static_cast< TCHAR >( LINE_FEED );
         number_of_bytes_encoded++;
      }
   }

   destination[ number_of_bytes_encoded ] = static_cast< TCHAR >( END_OF_BASE64_ENCODED_DATA );

   // 1999-09-01
   // Thanks go to Yurong Lin (ylin@dial.pipex.com) for finding a bug here.
   // We must NULL terminate the string before letting CString have the buffer back.

   destination[ number_of_bytes_encoded + 1 ] = 0;

   destination_string.ReleaseBuffer( -1 );

   return( TRUE );
}

// End of source

#if 0
<HTML>

<HEAD>
<TITLE>WFC - CBase64Coding</TITLE>
<META name="keywords" content="WFC, MFC extension library, freeware class library, Win32, MIME encoding, base 64, source code">
<META name="description" content="This C++ class let's you MIME encode bytes to text using base64.">
</HEAD>

<BODY>

<H1>CBase64Coding</H1>

$Revision: 14 $<BR><HR>

<H2>Description</H2>

This class gives you the ability to encode/decode data using base64.

<H2>Constructors</H2>

<DL COMPACT>

<DT><PRE><B>CBase64Coding</B>()<DD>
Constructs this object.

</DL>

<H2>Methods</H2>

<DL COMPACT>

<DT><PRE>BOOL <B><A NAME="Decode">Decode</A></B>( const CByteArray&amp; source, CByteArray&amp; destination )
BOOL <B>Decode</B>( const CString&amp;    source, CByteArray&amp; destination )</PRE><DD>
This method takes base64 encoded text and produces the bytes. It decodes
the base64 encoding.

<DT><PRE>BOOL <B><A NAME="Encode">Encode</A></B>( const CByteArray&amp; source, CByteArray&amp; destination )
BOOL <B>Encode</B>( const CByteArray&amp; source, CString&amp;    destination )</PRE><DD>
This method takes bytes and turns them into base64 text.

</DL>

<H2>Example</H2>
<PRE><CODE>#include &lt;wfc.h&gt;

int _tmain( int number_of_command_line_arguments, LPCTSTR command_line_arguments[] )
{
   <A HREF="WfcTrace.htm">WFCTRACEINIT</A>( TEXT( &quot;_tmain()&quot; ) );

   CByteArray bytes;

   get_file_contents( command_line_arguments[ 0 ], bytes );

   <B>CBase64Coding</B> encoder;

   CString encoded_data;

   if ( encoder.Encode( bytes, encoded_data ) != FALSE )
   {
      _tprintf( TEXT( &quot;%s\n&quot;, (LPCTSTR) encoded_data );
   }
}</CODE></PRE>
<HR><I>Copyright, 2000, <A HREF="mailto:wfc@pobox.com">Samuel R. Blackburn</A></I><BR>
$Workfile: CBase64Coding.cpp $<BR>
$Modtime: 5/12/00 3:39p $
</BODY>

</HTML>
#endif
