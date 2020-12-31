#include "Test.h"
#pragma hdrstop

// $Revision: 1 $

#define NUMBER_OF_TESTS_IN_CDATAPARSER_TEST_CLASS (2)

static BOOL test_class( CDataParser& parser, int& test_number_that_failed )
{
   CParsePoint parse_point;
   CParsePoint found_at;

   if ( parser.Find( parse_point, TEXT( "DEF" ), found_at ) == FALSE )
   {
      test_number_that_failed = 1;
      return( FALSE );
   }

   if ( found_at.GetIndex() != 3 )
   {
      test_number_that_failed = 2;
      return( FALSE );
   }

   found_at.Empty();

   // void AdvanceByOneCharacter( CParsePoint& parse_point, DWORD character_parameter = 0 ) const

   parse_point.Empty();
   found_at.Empty();

   parser.AdvanceByOneCharacter( parse_point );

   if ( parse_point.GetLineIndex() != 1 )
   {
      test_number_that_failed = 3;
      return( FALSE );
   }
   parse_point.Empty();
   found_at.Empty();

   parser.AdvanceByOneCharacter( parse_point, '\n' );

   if ( parse_point.GetLineIndex() != 2 )
   {
      test_number_that_failed = 4;
      return( FALSE );
   }

   CStringArray strings;
   test_number_that_failed = 2;

   return( TRUE );
}

BOOL test_CDataParser( CString& class_name, int& test_number_that_failed )
{
   class_name = "CDataParser";

   CByteArray bytes;

   CDataParser parser;

   // ASCII Test

   bytes.Add( 'A' );
   bytes.Add( 'B' );
   bytes.Add( 'C' );
   bytes.Add( 'D' );
   bytes.Add( 'E' );
   bytes.Add( 'F' );

   parser.Initialize( &bytes );
   parser.SetTextToASCII( TRUE );

   if ( test_class( parser, test_number_that_failed ) == FALSE )
   {
      return( FALSE );
   }

   // UNICODE, Intel (little-endian)

   bytes.RemoveAll();

   bytes.Add( 'A' ); // little end
   bytes.Add(  0  ); // big end

   bytes.Add( 'B' );
   bytes.Add(  0  );

   bytes.Add( 'C' );
   bytes.Add(  0  );

   bytes.Add( 'D' );
   bytes.Add(  0  );

   bytes.Add( 'E' );
   bytes.Add(  0  );

   bytes.Add( 'F' );
   bytes.Add(  0  );

   parser.Initialize( &bytes );
   parser.SetTextToASCII( FALSE );
   parser.SetTextToBigEndian( FALSE );

   if ( test_class( parser, test_number_that_failed ) == FALSE )
   {
      test_number_that_failed += ( NUMBER_OF_TESTS_IN_CDATAPARSER_TEST_CLASS * 1 );
      return( FALSE );
   }

   // UNICODE, Sun (big-endian)

   bytes.RemoveAll();

   bytes.Add(  0  ); // big end
   bytes.Add( 'A' ); // little end

   bytes.Add(  0  );
   bytes.Add( 'B' );

   bytes.Add(  0  );
   bytes.Add( 'C' );

   bytes.Add(  0  );
   bytes.Add( 'D' );

   bytes.Add(  0  );
   bytes.Add( 'E' );

   bytes.Add(  0  );
   bytes.Add( 'F' );

   parser.Initialize( &bytes );
   parser.SetTextToASCII( FALSE );
   parser.SetTextToBigEndian( TRUE );

   if ( test_class( parser, test_number_that_failed ) == FALSE )
   {
      test_number_that_failed += ( NUMBER_OF_TESTS_IN_CDATAPARSER_TEST_CLASS * 2 );
      return( FALSE );
   }

   // UCS4-1234

   bytes.RemoveAll();

   bytes.Add(  0  ); // 1
   bytes.Add(  0  ); // 2
   bytes.Add(  0  ); // 3
   bytes.Add( 'A' ); // 4

   bytes.Add(  0  );
   bytes.Add(  0  );
   bytes.Add(  0  );
   bytes.Add( 'B' );

   bytes.Add(  0  );
   bytes.Add(  0  );
   bytes.Add(  0  );
   bytes.Add( 'C' );

   bytes.Add(  0  );
   bytes.Add(  0  );
   bytes.Add(  0  );
   bytes.Add( 'D' );

   bytes.Add(  0  );
   bytes.Add(  0  );
   bytes.Add(  0  );
   bytes.Add( 'E' );

   bytes.Add(  0  );
   bytes.Add(  0  );
   bytes.Add(  0  );
   bytes.Add( 'F' );

   parser.Initialize( &bytes );
   parser.SetTextToUCS4( TRUE );
   parser.SetUCS4Order( 1234 );

   if ( test_class( parser, test_number_that_failed ) == FALSE )
   {
      test_number_that_failed += ( NUMBER_OF_TESTS_IN_CDATAPARSER_TEST_CLASS * 3 );
      return( FALSE );
   }

   // UCS4-2143

   bytes.RemoveAll();

   bytes.Add(  0  ); // 2
   bytes.Add(  0  ); // 1
   bytes.Add( 'A' ); // 4
   bytes.Add(  0  ); // 3

   bytes.Add(  0  );
   bytes.Add(  0  );
   bytes.Add( 'B' );
   bytes.Add(  0  );

   bytes.Add(  0  );
   bytes.Add(  0  );
   bytes.Add( 'C' );
   bytes.Add(  0  );

   bytes.Add(  0  );
   bytes.Add(  0  );
   bytes.Add( 'D' );
   bytes.Add(  0  );

   bytes.Add(  0  );
   bytes.Add(  0  );
   bytes.Add( 'E' );
   bytes.Add(  0  );

   bytes.Add(  0  );
   bytes.Add(  0  );
   bytes.Add( 'F' );
   bytes.Add(  0  );

   parser.Initialize( &bytes );
   parser.SetTextToUCS4( TRUE );
   parser.SetUCS4Order( 2143 );

   if ( test_class( parser, test_number_that_failed ) == FALSE )
   {
      test_number_that_failed += ( NUMBER_OF_TESTS_IN_CDATAPARSER_TEST_CLASS * 4 );
      return( FALSE );
   }

   // UCS4-3412

   bytes.RemoveAll();

   bytes.Add(  0  ); // 3
   bytes.Add( 'A' ); // 4
   bytes.Add(  0  ); // 1
   bytes.Add(  0  ); // 2

   bytes.Add(  0  );
   bytes.Add( 'B' );
   bytes.Add(  0  );
   bytes.Add(  0  );

   bytes.Add(  0  );
   bytes.Add( 'C' );
   bytes.Add(  0  );
   bytes.Add(  0  );

   bytes.Add(  0  );
   bytes.Add( 'D' );
   bytes.Add(  0  );
   bytes.Add(  0  );

   bytes.Add(  0  );
   bytes.Add( 'E' );
   bytes.Add(  0  );
   bytes.Add(  0  );

   bytes.Add(  0  );
   bytes.Add( 'F' );
   bytes.Add(  0  );
   bytes.Add(  0  );

   parser.Initialize( &bytes );
   parser.SetTextToUCS4( TRUE );
   parser.SetUCS4Order( 3412 );

   if ( test_class( parser, test_number_that_failed ) == FALSE )
   {
      test_number_that_failed += ( NUMBER_OF_TESTS_IN_CDATAPARSER_TEST_CLASS * 5 );
      return( FALSE );
   }

   // UCS4-4321

   bytes.RemoveAll();

   bytes.Add( 'A' ); // 4
   bytes.Add(  0  ); // 3
   bytes.Add(  0  ); // 2
   bytes.Add(  0  ); // 1

   bytes.Add( 'B' );
   bytes.Add(  0  );
   bytes.Add(  0  );
   bytes.Add(  0  );

   bytes.Add( 'C' );
   bytes.Add(  0  );
   bytes.Add(  0  );
   bytes.Add(  0  );

   bytes.Add( 'D' );
   bytes.Add(  0  );
   bytes.Add(  0  );
   bytes.Add(  0  );

   bytes.Add( 'E' );
   bytes.Add(  0  );
   bytes.Add(  0  );
   bytes.Add(  0  );

   bytes.Add( 'F' );
   bytes.Add(  0  );
   bytes.Add(  0  );
   bytes.Add(  0  );

   parser.Initialize( &bytes );
   parser.SetTextToUCS4( TRUE );
   parser.SetUCS4Order( 4321 );

   if ( test_class( parser, test_number_that_failed ) == FALSE )
   {
      test_number_that_failed += ( NUMBER_OF_TESTS_IN_CDATAPARSER_TEST_CLASS * 6 );
      return( FALSE );
   }

   return( TRUE );
}
