#include "test.h"
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
** Copyright, 1999, Samuel R. Blackburn
**
** $Workfile: test_CXMLDocument.cpp $
** $Revision: 2 $
** $Modtime: 5/13/00 8:22a $
*/

// This is not a good test, it is here to simply test
// encoding options when writing xml out

void test_CXMLDocument( void )
{
   WFCTRACEINIT( TEXT( "test_CXMLDocument()" ) );

   CExtensibleMarkupLanguageDocument xml;

   CByteArray bytes;

   xml.SetWriteOptions( WFC_XML_WRITE_AS_UNICODE | WFC_XML_WRITE_AS_BIG_ENDIAN );

   xml.WriteTo( bytes );

   if ( bytes.GetSize() == 0 )
   {
      _tprintf( TEXT( "CExtensibleMarkupLanguageDocument failed test 1\n" ) );
      return;
   }

   ASSERT( bytes.GetSize() > 5 );

   // Check to make sure the Big End was In first
   // Big End In, big endian, get it?

   if ( bytes.GetAt( 0 ) != 0xFE )// fe
   {
      ASSERT( FALSE );
      _tprintf( TEXT( "CExtensibleMarkupLanguageDocument failed test 2\n" ) );
      return;
   }

   if ( bytes.GetAt( 1 ) != 0xFF )// ff
   {
      ASSERT( FALSE );
      _tprintf( TEXT( "CExtensibleMarkupLanguageDocument failed test 3\n" ) );
      return;
   }

   if ( bytes.GetAt( 2 ) != 0x00 )
   {
      ASSERT( FALSE );
      _tprintf( TEXT( "CExtensibleMarkupLanguageDocument failed test 2\n" ) );
      return;
   }

   if ( bytes.GetAt( 3 ) != 0x3C )
   {
      ASSERT( FALSE );
      _tprintf( TEXT( "CExtensibleMarkupLanguageDocument failed test 3\n" ) );
      return;
   }

   if ( bytes.GetAt( 4 ) != 0x00 )
   {
      ASSERT( FALSE );
      _tprintf( TEXT( "CExtensibleMarkupLanguageDocument failed test 4\n" ) );
      return;
   }

   if ( bytes.GetAt( 5 ) != 0x3F )
   {
      ASSERT( FALSE );
      _tprintf( TEXT( "CExtensibleMarkupLanguageDocument failed test 5\n" ) );
      return;
   }

   bytes.RemoveAll();

   // UNICODE, little endian

   xml.SetWriteOptions( WFC_XML_WRITE_AS_UNICODE );

   xml.WriteTo( bytes );

   if ( bytes.GetSize() == 0 )
   {
      _tprintf( TEXT( "CExtensibleMarkupLanguageDocument failed test 6\n" ) );
      return;
   }

   ASSERT( bytes.GetSize() > 5 );

   // Check to make sure the Little End was In first
   // Little End In, little endian, get it?

   if ( bytes.GetAt( 0 ) != 0xFF )
   {
      ASSERT( FALSE );
      _tprintf( TEXT( "CExtensibleMarkupLanguageDocument failed test 2\n" ) );
      return;
   }

   if ( bytes.GetAt( 1 ) != 0xFE )
   {
      ASSERT( FALSE );
      _tprintf( TEXT( "CExtensibleMarkupLanguageDocument failed test 3\n" ) );
      return;
   }

   if ( bytes.GetAt( 2 ) != 0x3C )
   {
      ASSERT( FALSE );
      _tprintf( TEXT( "CExtensibleMarkupLanguageDocument failed test 7\n" ) );
      return;
   }

   if ( bytes.GetAt( 3 ) != 0x00 )
   {
      ASSERT( FALSE );
      _tprintf( TEXT( "CExtensibleMarkupLanguageDocument failed test 8\n" ) );
      return;
   }

   if ( bytes.GetAt( 4 ) != 0x3F )
   {
      ASSERT( FALSE );
      _tprintf( TEXT( "CExtensibleMarkupLanguageDocument failed test 9\n" ) );
      return;
   }

   if ( bytes.GetAt( 5 ) != 0x00 )
   {
      ASSERT( FALSE );
      _tprintf( TEXT( "CExtensibleMarkupLanguageDocument failed test 10\n" ) );
      return;
   }

   bytes.RemoveAll();

   // UCS4, Big Endian

   xml.SetWriteOptions( WFC_XML_WRITE_AS_UCS4 | WFC_XML_WRITE_AS_BIG_ENDIAN );

   xml.WriteTo( bytes );

   if ( bytes.GetSize() == 0 )
   {
      _tprintf( TEXT( "CExtensibleMarkupLanguageDocument failed test 11\n" ) );
      return;
   }

   ASSERT( bytes.GetSize() > 3 );

   if ( bytes.GetAt( 0 ) != 0x00 )
   {
      ASSERT( FALSE );
      _tprintf( TEXT( "CExtensibleMarkupLanguageDocument failed test 12\n" ) );
      return;
   }

   if ( bytes.GetAt( 1 ) != 0x00 )
   {
      ASSERT( FALSE );
      _tprintf( TEXT( "CExtensibleMarkupLanguageDocument failed test 13\n" ) );
      return;
   }

   if ( bytes.GetAt( 2 ) != 0x00 )
   {
      ASSERT( FALSE );
      _tprintf( TEXT( "CExtensibleMarkupLanguageDocument failed test 14\n" ) );
      return;
   }

   if ( bytes.GetAt( 3 ) != 0x3C )
   {
      ASSERT( FALSE );
      _tprintf( TEXT( "CExtensibleMarkupLanguageDocument failed test 15\n" ) );
      return;
   }

   bytes.RemoveAll();

   // UCS4, Little Endian

   xml.SetWriteOptions( WFC_XML_WRITE_AS_UCS4 );

   xml.WriteTo( bytes );

   if ( bytes.GetSize() == 0 )
   {
      _tprintf( TEXT( "CExtensibleMarkupLanguageDocument failed test 16\n" ) );
      return;
   }

   ASSERT( bytes.GetSize() > 3 );

   if ( bytes.GetAt( 0 ) != 0x3C )
   {
      ASSERT( FALSE );
      _tprintf( TEXT( "CExtensibleMarkupLanguageDocument failed test 17\n" ) );
      return;
   }

   if ( bytes.GetAt( 1 ) != 0x00 )
   {
      ASSERT( FALSE );
      _tprintf( TEXT( "CExtensibleMarkupLanguageDocument failed test 18\n" ) );
      return;
   }

   if ( bytes.GetAt( 2 ) != 0x00 )
   {
      ASSERT( FALSE );
      _tprintf( TEXT( "CExtensibleMarkupLanguageDocument failed test 19\n" ) );
      return;
   }

   if ( bytes.GetAt( 3 ) != 0x00 )
   {
      ASSERT( FALSE );
      _tprintf( TEXT( "CExtensibleMarkupLanguageDocument failed test 20\n" ) );
      return;
   }

   bytes.RemoveAll();

   // UCS4, Unusal 2143

   xml.SetWriteOptions( WFC_XML_WRITE_AS_UCS4_UNUSUAL_2143 );

   xml.WriteTo( bytes );

   if ( bytes.GetSize() == 0 )
   {
      _tprintf( TEXT( "CExtensibleMarkupLanguageDocument failed test 21\n" ) );
      return;
   }

   ASSERT( bytes.GetSize() > 3 );

   if ( bytes.GetAt( 0 ) != 0x00 )
   {
      ASSERT( FALSE );
      _tprintf( TEXT( "CExtensibleMarkupLanguageDocument failed test 22\n" ) );
      return;
   }

   if ( bytes.GetAt( 1 ) != 0x00 )
   {
      ASSERT( FALSE );
      _tprintf( TEXT( "CExtensibleMarkupLanguageDocument failed test 23\n" ) );
      return;
   }

   if ( bytes.GetAt( 2 ) != 0x3C )
   {
      ASSERT( FALSE );
      _tprintf( TEXT( "CExtensibleMarkupLanguageDocument failed test 24\n" ) );
      return;
   }

   if ( bytes.GetAt( 3 ) != 0x00 )
   {
      ASSERT( FALSE );
      _tprintf( TEXT( "CExtensibleMarkupLanguageDocument failed test 25\n" ) );
      return;
   }

   bytes.RemoveAll();

   // UCS4, Unusal 3412

   xml.SetWriteOptions( WFC_XML_WRITE_AS_UCS4_UNUSUAL_3412 );

   xml.WriteTo( bytes );

   if ( bytes.GetSize() == 0 )
   {
      _tprintf( TEXT( "CExtensibleMarkupLanguageDocument failed test 26\n" ) );
      return;
   }

   ASSERT( bytes.GetSize() > 3 );

   if ( bytes.GetAt( 0 ) != 0x00 )
   {
      ASSERT( FALSE );
      _tprintf( TEXT( "CExtensibleMarkupLanguageDocument failed test 27\n" ) );
      return;
   }

   if ( bytes.GetAt( 1 ) != 0x3C )
   {
      ASSERT( FALSE );
      _tprintf( TEXT( "CExtensibleMarkupLanguageDocument failed test 28\n" ) );
      return;
   }

   if ( bytes.GetAt( 2 ) != 0x00 )
   {
      ASSERT( FALSE );
      _tprintf( TEXT( "CExtensibleMarkupLanguageDocument failed test 29\n" ) );
      return;
   }

   if ( bytes.GetAt( 3 ) != 0x00 )
   {
      ASSERT( FALSE );
      _tprintf( TEXT( "CExtensibleMarkupLanguageDocument failed test 30\n" ) );
      return;
   }

   // 2000-05-07
   // Test provided by Juro Gottweis (juro@asc.sk)

   xml.Empty();

   bytes.RemoveAll();

   CString test_text( TEXT( "<?xml version=\"1.0\" standalone=\"yes\"?>\n" ) );

   test_text += TEXT( "<prop>Hello</prop> <prop>World</prop>" );

   //bytes.Append( (const BYTE *) ( (LPCTSTR) test_text ), test_text.GetLength() * sizeof( TCHAR ) );

   CDataParser parser;

   parser.Initialize( &bytes, FALSE );

   DWORD parse_options = xml.GetParseOptions();

   xml.SetParseOptions( parse_options | WFC_XML_ALLOW_AMPERSANDS_IN_ELEMENTS );

   if ( xml.Parse( parser ) != TRUE )
   {
      //ASSERT( FALSE );
      _tprintf( TEXT( "CExtensibleMarkupLanguageDocument failed test 31\n" ) );
      return;
   }

   CByteArray output;

   xml.WriteTo( output );
   output.Add( 0 );
   output.Add( 0 ); // NULL terminate the string

   CString test_string_2;

   test_string_2 = (LPCTSTR) output.GetData();

   WFCTRACEVAL( TEXT( "Value is " ), test_string_2 );

   WFCTRACE( TEXT( "Passed." ) );
}
