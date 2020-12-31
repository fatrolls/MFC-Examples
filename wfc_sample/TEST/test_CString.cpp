#include "Test.h"
#pragma hdrstop

// $Revision: 4 $

#if ! defined( INTERNAL_STRING_BUFFER_SIZE )
#define INTERNAL_STRING_BUFFER_SIZE (16)
#endif // INTERNAL_STRING_BUFFER_SIZE

BOOL test_CString( CString& class_name, int& test_number_that_failed )
{
   class_name = "CString";

   CString string_1;

   if ( string_1.GetLength() != 0 )
   {
      test_number_that_failed = 1;
      return( FALSE );
   }

#if defined( WFC_STL )

   string_1.Copy( "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789" );

#else // WFC_STL

   string_1 = TEXT( "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789" );

#endif // WFC_STL

   if ( string_1.GetLength() != 36 )
   {
      test_number_that_failed = 2;
      return( FALSE );
   }

   CString string_2( string_1 );

   if ( string_1.Compare( string_2 ) != 0 )
   {
      test_number_that_failed = 3;
      return( FALSE );
   }

   string_1.MakeLower();

   if ( string_1.Compare( "abcdefghijklmnopqrstuvwxyz0123456789" ) != 0 )
   {
      test_number_that_failed = 4;
      return( FALSE );
   }

   string_1.MakeUpper();

   if ( string_1.Compare( string_2 ) != 0 )
   {
      test_number_that_failed = 5;
      return( FALSE );
   }

   string_2 = string_1.Left( 26 );

   if ( string_2.Compare( "ABCDEFGHIJKLMNOPQRSTUVWXYZ" ) != 0 )
   {
      test_number_that_failed = 6;
      return( FALSE );
   }

   if ( string_2.CompareNoCase( "abcDEFGHIJKLMNOPQRSTUVWXYZ" ) != 0 )
   {
      test_number_that_failed = 7;
      return( FALSE );
   }

   string_2 = string_1.Right( 10 );

   if ( string_2.Compare( "0123456789" ) != 0 )
   {
      test_number_that_failed = 8;
      return( FALSE );
   }

   // OK, we've got the basic tests out of the way, now let's methodically
   // go through the interface and make sure we test everything.

   // CString::CString( char )

   string_2 = CString( 'A' );

   if ( string_2.GetLength() != 1 )
   {
      test_number_that_failed = 9;
      return( FALSE );
   }

   if ( string_2.GetAt( 0 ) != 'A' )
   {
      test_number_that_failed = 10;
      return( FALSE );
   }

   // Now test to see if we can add more than one character...

   string_2 = CString( 'A', 5 );

   if ( string_2.GetLength() != 5 )
   {
      test_number_that_failed = 11;
      return( FALSE );
   }

   if ( string_2.GetAt( 4 ) != 'A' )
   {
      test_number_that_failed = 12;
      return( FALSE );
   }

   // CString::CString( const char * )

   CString string_3( "ABCDE" );

   if ( string_3.GetLength() != 5 )
   {
      test_number_that_failed = 13;
      return( FALSE );
   }

   if ( string_3.GetAt( 4 ) != 'E' )
   {
      test_number_that_failed = 14;
      return( FALSE );
   }

   if ( string_3.Compare( "ABCDE" ) != 0 )
   {
      test_number_that_failed = 15;
      return( FALSE );
   }

   // CString::CString( unsigned char *, long )

   unsigned char byte_buffer[ 5 ];

   byte_buffer[ 0 ] = 'a';
   byte_buffer[ 1 ] = 'b';
   byte_buffer[ 2 ] = 'c';
   byte_buffer[ 3 ] = 'd';
   byte_buffer[ 4 ] = 0xFF; // NOT NULL TERMINATED!

   CString string_4( (const char *) byte_buffer, 4 );

   if ( string_4.GetLength() != 4 )
   {
      test_number_that_failed = 16;
      return( FALSE );
   }

   if ( string_4.GetAt( 3 ) != 'd' )
   {
      test_number_that_failed = 17;
      return( FALSE );
   }

   if ( string_4.Compare( "abcd" ) != 0 )
   {
      test_number_that_failed = 18;
      return( FALSE );
   }

   byte_buffer[ 4 ] = 0x00; // NULL TERMINATE

   CString string_5( (const char *) byte_buffer );

   if ( string_5.GetLength() != 4 )
   {
      test_number_that_failed = 19;
      return( FALSE );
   }

   if ( string_5.GetAt( 3 ) != 'd' )
   {
      test_number_that_failed = 20;
      return( FALSE );
   }

   if ( string_5.Compare( "abcd" ) != 0 )
   {
      test_number_that_failed = 21;
      return( FALSE );
   }

   // CString::Empty()

   string_5.Empty();

   if ( string_5.GetLength() != 0 )
   {
      test_number_that_failed = 22;
      return( FALSE );
   }

   // CString::IsEmpty()

   if ( string_5.IsEmpty() != TRUE )
   {
      test_number_that_failed = 23;
      return( FALSE );
   }

   // CString::Append( const CString& )

   // Be careful to use only functions that have already been tested above

#if defined( WFC_STL )

   string_1.Copy( "ABC" );
   string_2.Copy( "DEF" );

   string_1.Append( string_2 );

#else // WFC_STL

   string_1 = TEXT( "ABC" );
   string_2 = TEXT( "DEF" );

   string_1 += string_2;

#endif // WFC_STL

   if ( string_1.Compare( "ABCDEF" ) != 0 )
   {
      test_number_that_failed = 23;
      return( FALSE );
   }

   // CString::Append( const char * )

#if defined( WFC_STL )

   string_1.Append( "GHI" );

#else // WFC_STL

   string_1 += TEXT( "GHI" );

#endif // WFC_STL

   if ( string_1.Compare( "ABCDEFGHI" ) != 0 )
   {
      test_number_that_failed = 24;
      return( FALSE );
   }

   // CString::Append( char )

#if defined( WFC_STL )

   string_1.Append( 'J' );

#else // WFC_STL

   string_1 += TEXT( 'J' );

#endif // WFC_STL

   if ( string_1.Compare( "ABCDEFGHIJ" ) != 0 )
   {
      test_number_that_failed = 25;
      return( FALSE );
   }

   // CString::Append( unsigned char * )

#if defined( WFC_STL )

   string_1.Append( (const char *) byte_buffer );

#else // WFC_STL

   string_1 += (const char *) byte_buffer;

#endif // WFC_STL

   if ( string_1.Compare( "ABCDEFGHIJabcd" ) != 0 )
   {
      test_number_that_failed = 26;
      return( FALSE );
   }

   // CString::Collate()

   if ( string_1.Collate( "ABCDEFGHIJabcd" ) != 0 )
   {
      test_number_that_failed = 27;
      return( FALSE );
   }

   // CString::Copy( unsigned char *, long, long )

#if defined( WFC_STL )

   string_1.Copy( (const char *) byte_buffer, 2, 1 );

   if ( string_1.GetLength() != 2 )
   {
      test_number_that_failed = 28;
      return( FALSE );
   }

   if ( string_1.Compare( "bc" ) != 0 )
   {
      test_number_that_failed = 29;
      return( FALSE );
   }

   // Test the non-unsigned version of Copy()

   string_1.Copy( (const char *) "abcd", 2, 1 );

   if ( string_1.GetLength() != 2 )
   {
      test_number_that_failed = 30;
      return( FALSE );
   }

   if ( string_1.Compare( "bc" ) != 0 )
   {
      test_number_that_failed = 31;
      return( FALSE );
   }

   // CString::Copy( const CString&, long, long )

   string_2 = "WXYZ";

   string_1.Copy( string_2, 2, 1 );

   if ( string_1.GetLength() != 2 )
   {
      test_number_that_failed = 32;
      return( FALSE );
   }

   if ( string_1.Compare( "XY" ) != 0 )
   {
      test_number_that_failed = 33;
      return( FALSE );
   }

#endif // WFC_STL

   // CString::Find( char )

   int found_at_index = 0;

   string_1 = "WXYZ";

   found_at_index = string_1.Find( 'Z' );

   if ( found_at_index != 3 )
   {
      test_number_that_failed = 34;
      return( FALSE );
   }

   // CString::Find( char * )

   found_at_index = string_1.Find( "XY" );

   if ( found_at_index != 1 )
   {
      test_number_that_failed = 35;
      return( FALSE );
   }

   // CString::FindOneOf()

   found_at_index = string_1.FindOneOf( "AbZ" );

   if ( found_at_index != 3 )
   {
      test_number_that_failed = 36;
      return( FALSE );
   }

   // CString::GetSize()

#if defined( WFC_STL )

   if ( string_1.GetSize() != 4 )

#else // WFC_STL

   if ( string_1.GetLength() != 4 )

#endif // WFC_STL
   {
      test_number_that_failed = 37;
      return( FALSE );
   }

   // CString::MakeReverse()

   string_1 = TEXT( "ABCD12345" ); // An Odd-numbered length

   string_1.MakeReverse();

   if ( string_1.Compare( TEXT( "54321DCBA" ) ) != 0 )
   {
      test_number_that_failed = 38;
      return( FALSE );
   }

   string_1.MakeReverse();

   if ( string_1.Compare( TEXT( "ABCD12345" ) ) != 0 )
   {
      test_number_that_failed = 39;
      return( FALSE );
   }

   string_1 = TEXT( "ABCD1234" ); // An Even-numbered length

   string_1.MakeReverse();

   if ( string_1.Compare( TEXT( "4321DCBA" ) ) != 0 )
   {
      test_number_that_failed = 40;
      return( FALSE );
   }

   string_1.MakeReverse();

   if ( string_1.Compare( TEXT( "ABCD1234" ) ) != 0 )
   {
      test_number_that_failed = 41;
      return( FALSE );
   }

   // CString::Mid( long, long )

   string_2 = string_1.Mid( 2, 4 );

   if ( string_2.Compare( TEXT( "CD12" ) ) != 0 )
   {
      test_number_that_failed = 42;
      return( FALSE );
   }

   // CString::Mid( long )

   string_2 = string_1.Mid( 2 );

   if ( string_2.Compare( TEXT( "CD1234" ) ) != 0 )
   {
      test_number_that_failed = 43;
      return( FALSE );
   }

   // CString::ReverseFind()

   string_1 = "AZA";

   found_at_index = string_1.ReverseFind( 'A' );

   if ( found_at_index != 2 )
   {
      test_number_that_failed = 44;
      return( FALSE );
   }

   // CString::SetAt()

   string_1.SetAt( 1, 'A' );

   if ( string_1.Compare( TEXT( "AAA" ) ) != 0 )
   {
      test_number_that_failed = 45;
      return( FALSE );
   }

   // CString::SpanExcluding()

   string_1 = TEXT( "AABBCCDDYYZZ" );

   string_2 = string_1.SpanExcluding( TEXT( "ZY" ) );

   if ( string_2.Compare( TEXT( "AABBCCDD" ) ) != 0 )
   {
      test_number_that_failed = 46;
      return( FALSE );
   }

   // CString::SpanIncluding()

   string_2 = string_1.SpanIncluding( TEXT( "BAC" ) );

   if ( string_2.Compare( TEXT( "AABBCC" ) ) != 0 )
   {
      test_number_that_failed = 47;
      return( FALSE );
   }

   // CString::TrimLeft()

   string_1 = TEXT( " \t\r  ABCD" );

   string_1.TrimLeft();

   if ( string_1.Compare( TEXT( "ABCD" ) ) != 0 )
   {
      test_number_that_failed = 48;
      return( FALSE );
   }

   // CString::TrimRight()

   string_1 = TEXT( "ABCD \t\r " );

   string_1.TrimRight();

   if ( string_1.Compare( TEXT( "ABCD" ) ) != 0 )
   {
      test_number_that_failed = 49;
      return( FALSE );
   }

   // Whew, those were the easy functions, now let's do the easy operators

   // CString operator=( const CString& )

   string_2 = string_1;

   if ( string_2.Compare( TEXT( "ABCD" ) ) != 0 )
   {
      test_number_that_failed = 50;
      return( FALSE );
   }

   // CString::operator=( char )

   string_2 = 'A';

   if ( string_2.Compare( TEXT( "A" ) ) != 0 )
   {
      test_number_that_failed = 51;
      return( FALSE );
   }

   // CString::operator[]

   if ( string_1[ 1 ] != 'B' )
   {
      test_number_that_failed = 52;
      return( FALSE );
   }

   // CString::operator=( const unsigned char )

   string_2 = byte_buffer;

   if ( string_2.Compare( TEXT( "abcd" ) ) != 0 )
   {
      test_number_that_failed = 53;
      return( FALSE );
   }

   // CString::operator += ( CString& )

   string_1 = TEXT( "ABC" );
   string_2 = TEXT( "DEF" );

   string_1 += string_2;

   if ( string_1.Compare( TEXT( "ABCDEF" ) ) != 0 )
   {
      test_number_that_failed = 54;
      return( FALSE );
   }

   // CString::operator += ( char )

   string_1 += 'G';

   if ( string_1.Compare( TEXT( "ABCDEFG" ) ) != 0 )
   {
      test_number_that_failed = 55;
      return( FALSE );
   }

   // CString::operator += ( const char * )

   string_1 += TEXT( "HIJ" );

   if ( string_1.Compare( TEXT( "ABCDEFGHIJ" ) ) != 0 )
   {
      test_number_that_failed = 56;
      return( FALSE );
   }

   // friend + ( CString&, CString& )

   string_1 = TEXT( "ABC" );
   string_2 = TEXT( "DEF" );

   string_3 = string_1 + string_2;

   if ( string_3.Compare( TEXT( "ABCDEF" ) ) != 0 )
   {
      test_number_that_failed = 57;
      return( FALSE );
   }

   // friend + ( CString&, char )

   string_3 = string_1 + 'D';

   if ( string_3.Compare( TEXT( "ABCD" ) ) != 0 )
   {
      _tprintf( TEXT( "String should have been \"ABCD\" but it is \"%s\"\n" ), (LPCTSTR) string_3 );
      test_number_that_failed = 58;
      return( FALSE );
   }

   // friend + ( char, CString& )

   string_3 = 'C' + string_2;

   if ( string_3.Compare( TEXT( "CDEF" ) ) != 0 )
   {
      test_number_that_failed = 59;
      return( FALSE );
   }

   // friend + ( CString&, const char * )

   string_3 = string_1 + TEXT( "DEF" );

   if ( string_3.Compare( TEXT( "ABCDEF" ) ) != 0 )
   {
      test_number_that_failed = 60;
      return( FALSE );
   }

   // friend + ( const char *, CString )

   string_3 = TEXT( "ABC" ) + string_2;

   if ( string_3.Compare( TEXT( "ABCDEF" ) ) != 0 )
   {
      test_number_that_failed = 61;
      return( FALSE );
   }

   // Enough with the friends aleady. Now is the time for helper operators

   // operator == ( CString&, CString& )

   string_1 = TEXT( "ABC" );
   string_2 = TEXT( "ABC" );

   if ( ! ( string_1 == string_2 ) )
   {
      test_number_that_failed = 62;
      return( FALSE );
   }

   // operator == ( CString&, const char * )

   if ( ! ( string_1 == TEXT( "ABC" ) ) )
   {
      test_number_that_failed = 63;
      return( FALSE );
   }

   // operator == ( const char *, CString& )

   if ( ! ( TEXT( "ABC" ) == string_1 ) )
   {
      test_number_that_failed = 64;
      return( FALSE );
   }

   // operator != ( CString&, CString& )

   string_2 = TEXT( "abc" );

   if ( ! ( string_1 != string_2 ) )
   {
      test_number_that_failed = 65;
      return( FALSE );
   }

   // operator != ( CString&, const char * )

   if ( ! ( string_1 != TEXT( "abc" ) ) )
   {
      test_number_that_failed = 66;
      return( FALSE );
   }

   // operator != ( const char *, CString& )

   if ( ! ( TEXT( "abc" ) != string_1 ) )
   {
      test_number_that_failed = 67;
      return( FALSE );
   }

   // operator < ( CString&, CString& )

   string_1 = TEXT( "ABC" );
   string_2 = TEXT( "ABc" );

   if ( ! ( string_1 < string_2 ) )
   {
      test_number_that_failed = 68;
      return( FALSE );
   }

   // operator < ( CString&, const char * )

   if ( ! ( string_1 < TEXT( "ABc" ) ) )
   {
      test_number_that_failed = 69;
      return( FALSE );
   }

   // operator < ( const char *, CString& )

   if ( ! ( TEXT( "AAB" ) < string_1 ) )
   {
      test_number_that_failed = 70;
      return( FALSE );
   }

   // operator > ( CString&, CString& )

   string_1 = TEXT( "ABc" );
   string_2 = TEXT( "ABC" );

   if ( ! ( string_1 > string_2 ) )
   {
      test_number_that_failed = 71;
      return( FALSE );
   }

   // operator > ( CString&, const char * )

   if ( ! ( string_1 > TEXT( "ABC" ) ) )
   {
      test_number_that_failed = 72;
      return( FALSE );
   }

   // operator > ( const char *, CString& )

   string_1 = TEXT( "ABC" );

   if ( ! ( TEXT( "ABc" ) > string_1 ) )
   {
      test_number_that_failed = 73;
      return( FALSE );
   }

   // operator <= ( CString&, CString& )

   // Test the "less than" part of "less than or equal to"

   string_1 = TEXT( "ABC" );
   string_2 = TEXT( "ABc" );

   if ( ! ( string_1 <= string_2 ) )
   {
      test_number_that_failed = 74;
      return( FALSE );
   }

   // operator <= ( CString&, const char * )

   if ( ! ( string_1 <= "ABc" ) )
   {
      test_number_that_failed = 75;
      return( FALSE );
   }

   // operator <= ( const char *, CString& )

   if ( ! ( "AAB" <= string_1 ) )
   {
      test_number_that_failed = 76;
      return( FALSE );
   }

   // Now test the "equal to" part of "less than or equal to"
   // operator <= ( CString&, CString& )

   string_1 = "ABC";
   string_2 = "ABC";

   if ( ! ( string_1 <= string_2 ) )
   {
      test_number_that_failed = 77;
      return( FALSE );
   }

   // operator <= ( CString&, const char * )

   if ( ! ( string_1 <= "ABC" ) )
   {
      test_number_that_failed = 78;
      return( FALSE );
   }

   // operator <= ( const char *, CString& )

   if ( ! ( "ABC" <= string_1 ) )
   {
      test_number_that_failed = 79;
      return( FALSE );
   }

   // Test the "greater than" part of "greater than or equal to"
   // operator >= ( CString&, CString& )

   string_1 = "ABc";
   string_2 = "ABC";

   if ( ! ( string_1 >= string_2 ) )
   {
      test_number_that_failed = 80;
      return( FALSE );
   }

   // operator >= ( CString&, const char * )

   if ( ! ( string_1 >= "ABC" ) )
   {
      test_number_that_failed = 81;
      return( FALSE );
   }

   // operator >= ( const char *, CString& )

   string_1 = "ABC";

   if ( ! ( "ABc" >= string_1 ) )
   {
      test_number_that_failed = 82;
      return( FALSE );
   }

   // Now test the "equal to" part of "greater than or equal to"
   // operator >= ( CString&, CString& )

   string_1 = "ABC";
   string_2 = "ABC";

   if ( ! ( string_1 >= string_2 ) )
   {
      test_number_that_failed = 83;
      return( FALSE );
   }

   // operator >= ( CString&, const char * )

   if ( ! ( string_1 >= "ABC" ) )
   {
      test_number_that_failed = 84;
      return( FALSE );
   }

   // operator >= ( const char *, CString& )

   if ( ! ( "ABC" >= string_1 ) )
   {
      test_number_that_failed = 85;
      return( FALSE );
   }

   string_1.Empty();

   if ( string_1.GetLength() != 0 )
   {
      test_number_that_failed = 86;
      return( FALSE );
   }

   long loop_index                   = 0;
   long number_of_characters_to_test = INTERNAL_STRING_BUFFER_SIZE * 2;
   long previous_length              = 0;

   while( loop_index < number_of_characters_to_test )
   {
      previous_length = string_1.GetLength();

#if defined( WFC_STL )

      string_1.Append( 'A' );

#else // WFC_STL

      string_1 += TEXT( 'A' );

#endif // WFC_STL

      if ( previous_length != (string_1.GetLength() - 1 ) )
      {
         printf( "previous length (%lu) failed, length in error is %lu\n",
                 (unsigned long) previous_length,
                 (unsigned long) string_1.GetLength() - 1 );

         test_number_that_failed = 87;
         return( FALSE );
      }

      loop_index++;
   }

   if ( string_1.GetLength() != number_of_characters_to_test )
   {
      printf( "Length is %lu while it should have been %lu\n",
              (unsigned long) string_1.GetLength(),
              (unsigned long) number_of_characters_to_test );

      test_number_that_failed = 88;
      return( FALSE );
   }

   string_1 = "0123456789";

   if ( string_1.GetLength() != 10 )
   {
      test_number_that_failed = 89;
      return( FALSE );
   }

   if ( string_1.Compare( "0123456789" ) != 0 )
   {
      test_number_that_failed = 90;
      return( FALSE );
   }

#if defined( WFC_STL )

   string_1.SetLength( 9 );

   if ( string_1.GetLength() != 9 )
   {
      printf( "Length should have been 9 but it was %lu\n", (unsigned long) string_1.GetLength() );
      test_number_that_failed = 91;
      return( FALSE );
   }

#endif // WFC_STL

   if ( string_1.Compare( "012345678" ) != 0 )
   {
      printf( "String is \"%s\" when is should have been \"012345678\"\n", (const char *) string_1 );
      test_number_that_failed = 92;
      return( FALSE );
   }

   string_1.Empty();

   if ( string_1.GetLength() != 0 )
   {
      test_number_that_failed = 93;
      return( FALSE );
   }

   // CString::Format()
 
   string_1.Format( "This is the %d", 1 );

   if ( string_1.Compare( "This is the 1" ) != 0 )
   {
      test_number_that_failed = 94;
      return( FALSE );
   }

   string_1.Format( "This is the %d, %lu, %02d \"%s\"", 1, (unsigned long) 2, 3, "Sam Loves Laura" );

   if ( string_1.Compare( "This is the 1, 2, 03 \"Sam Loves Laura\"" ) != 0 )
   {
      test_number_that_failed = 95;
      return( FALSE );
   }

   unsigned char bytes[ 5 ];

   bytes[ 0 ] = 'A';
   bytes[ 1 ] = 'B';
   bytes[ 2 ] = 'C';
   bytes[ 3 ] = 'D';
   bytes[ 4 ] = 0x00;

   // const CString& operator=( const unsigned char * source );

   string_1 = bytes;

   if ( string_1.Compare( "ABCD" ) != 0 )
   {
      test_number_that_failed = 96;
      return( FALSE );
   }

   // CString( LPCWSTR lpsz );

   CString string_6( L"ABCD" );

   if ( string_6.Compare( "ABCD" ) != 0 )
   {
      test_number_that_failed = 97;
      return( FALSE );
   }

   // CString( LPCWSTR lpsz, int length );

   CString string_7( L"ABCD", 2 );

   if ( string_7.Compare( "AB" ) != 0 )
   {
      test_number_that_failed = 98;
      return( FALSE );
   }

   // const CString& operator=( LPCWSTR source );

   string_7 = L"WXYZ";

   if ( string_7.Compare( "WXYZ" ) != 0 )
   {
      test_number_that_failed = 99;
      return( FALSE );
   }

   test_number_that_failed = 99;

   return( TRUE );
}
