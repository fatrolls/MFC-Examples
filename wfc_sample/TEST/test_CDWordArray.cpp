#include "Test.h"
#pragma hdrstop

// $Revision: 2 $

BOOL test_CDWordArray( CString& class_name, int& test_number_that_failed )
{
   class_name = "CDWordArray";

   CDWordArray array_1;

   //   int         GetSize( void ) const;

   if ( array_1.GetSize() != 0 )
   {
      test_number_that_failed = 1;
      return( FALSE );
   }

   //   int         GetUpperBound( void ) const;

   if ( array_1.GetUpperBound() != (-1) )
   {
      test_number_that_failed = 2;
      return( FALSE );
   }

   //   int         Add( ARRAY_TYPE new_element );

   if ( array_1.Add( 47 ) != 0 )
   {
      test_number_that_failed = 2;
      return( FALSE );
   }

   if ( array_1.GetSize() != 1 )
   {
      test_number_that_failed = 3;
      return( FALSE );
   }

   if ( array_1.GetUpperBound() != 0 )
   {
      test_number_that_failed = 4;
      return( FALSE );
   }

   if ( array_1.Add( 50 ) != 1 )
   {
      test_number_that_failed = 5;
      return( FALSE );
   }

   if ( array_1.GetSize() != 2 )
   {
      test_number_that_failed = 6;
      return( FALSE );
   }

   if ( array_1.GetUpperBound() != 1 )
   {
      test_number_that_failed = 7;
      return( FALSE );
   }

   if ( array_1.Add( 57 ) != 2 )
   {
      test_number_that_failed = 8;
      return( FALSE );
   }

   if ( array_1.GetSize() != 3 )
   {
      test_number_that_failed = 9;
      return( FALSE );
   }

   if ( array_1.GetUpperBound() != 2 )
   {
      test_number_that_failed = 10;
      return( FALSE );
   }

   //   ARRAY_TYPE  GetAt( int array_index ) const;
   if ( array_1.GetAt( 0 ) != 47 )
   {
      test_number_that_failed = 11;
      return( FALSE );
   }

   if ( array_1.GetAt( 1 ) != 50 )
   {
      test_number_that_failed = 12;
      return( FALSE );
   }

   if ( array_1.GetAt( 2 ) != 57 )
   {
      test_number_that_failed = 13;
      return( FALSE );
   }

   //   ARRAY_TYPE& ElementAt( int array_index );

   // Element in the middle test
   array_1.ElementAt( 1 ) = 80;

   if ( array_1.GetSize() != 3 )
   {
      test_number_that_failed = 14;
      return( FALSE );
   }

   if ( array_1.GetUpperBound() != 2 )
   {
      test_number_that_failed = 15;
      return( FALSE );
   }

   if ( array_1.GetAt( 0 ) != 47 )
   {
      test_number_that_failed = 16;
      return( FALSE );
   }

   if ( array_1.GetAt( 1 ) != 80 )
   {
      test_number_that_failed = 17;
      return( FALSE );
   }

   if ( array_1.GetAt( 2 ) != 57 )
   {
      test_number_that_failed = 18;
      return( FALSE );
   }

   // Element at the beginning test

   array_1.ElementAt( 0 ) = 90;

   if ( array_1.GetSize() != 3 )
   {
      test_number_that_failed = 19;
      return( FALSE );
   }

   if ( array_1.GetUpperBound() != 2 )
   {
      test_number_that_failed = 20;
      return( FALSE );
   }

   if ( array_1.GetAt( 0 ) != 90 )
   {
      test_number_that_failed = 21;
      return( FALSE );
   }

   if ( array_1.GetAt( 1 ) != 80 )
   {
      test_number_that_failed = 22;
      return( FALSE );
   }

   if ( array_1.GetAt( 2 ) != 57 )
   {
      test_number_that_failed = 23;
      return( FALSE );
   }

   // Element at the end test

   array_1.ElementAt( 2 ) = 100;

   if ( array_1.GetSize() != 3 )
   {
      test_number_that_failed = 24;
      return( FALSE );
   }

   if ( array_1.GetUpperBound() != 2 )
   {
      test_number_that_failed = 25;
      return( FALSE );
   }

   if ( array_1.GetAt( 0 ) != 90 )
   {
      test_number_that_failed = 26;
      return( FALSE );
   }

   if ( array_1.GetAt( 1 ) != 80 )
   {
      test_number_that_failed = 27;
      return( FALSE );
   }

   if ( array_1.GetAt( 2 ) != 100 )
   {
      test_number_that_failed = 28;
      return( FALSE );
   }

	//   ARRAY_TYPE& operator[]( int array_index );

   array_1[ 0 ] = 1;

   if ( array_1.GetSize() != 3 )
   {
      test_number_that_failed = 29;
      return( FALSE );
   }

   if ( array_1.GetUpperBound() != 2 )
   {
      test_number_that_failed = 30;
      return( FALSE );
   }

   if ( array_1.GetAt( 0 ) != 1 )
   {
      test_number_that_failed = 31;
      return( FALSE );
   }

   if ( array_1.GetAt( 1 ) != 80 )
   {
      test_number_that_failed = 32;
      return( FALSE );
   }

   if ( array_1.GetAt( 2 ) != 100 )
   {
      test_number_that_failed = 33;
      return( FALSE );
   }

   array_1[ 1 ] = 2;

   if ( array_1.GetSize() != 3 )
   {
      test_number_that_failed = 34;
      return( FALSE );
   }

   if ( array_1.GetUpperBound() != 2 )
   {
      test_number_that_failed = 35;
      return( FALSE );
   }

   if ( array_1.GetAt( 0 ) != 1 )
   {
      test_number_that_failed = 36;
      return( FALSE );
   }

   if ( array_1.GetAt( 1 ) != 2 )
   {
      test_number_that_failed = 37;
      return( FALSE );
   }

   if ( array_1.GetAt( 2 ) != 100 )
   {
      test_number_that_failed = 38;
      return( FALSE );
   }

   array_1[ 2 ] = 3;

   if ( array_1.GetSize() != 3 )
   {
      test_number_that_failed = 39;
      return( FALSE );
   }

   if ( array_1.GetUpperBound() != 2 )
   {
      test_number_that_failed = 40;
      return( FALSE );
   }

   if ( array_1.GetAt( 0 ) != 1 )
   {
      test_number_that_failed = 41;
      return( FALSE );
   }

   if ( array_1.GetAt( 1 ) != 2 )
   {
      test_number_that_failed = 42;
      return( FALSE );
   }

   if ( array_1.GetAt( 2 ) != 3 )
   {
      test_number_that_failed = 43;
      return( FALSE );
   }

   //   ARRAY_TYPE operator[]( int array_index ) const;

   if ( array_1[ 0 ] != 1 )
   {
      test_number_that_failed = 44;
      return( FALSE );
   }

   if ( array_1[ 1 ] != 2 )
   {
      test_number_that_failed = 45;
      return( FALSE );
   }

   if ( array_1[ 2 ] != 3 )
   {
      test_number_that_failed = 46;
      return( FALSE );
   }

   //   void        SetAt( int array_index, ARRAY_TYPE new_element );

   array_1.SetAt( 0, 11 );

   if ( array_1.GetSize() != 3 )
   {
      test_number_that_failed = 47;
      return( FALSE );
   }

   if ( array_1.GetUpperBound() != 2 )
   {
      test_number_that_failed = 48;
      return( FALSE );
   }

   if ( array_1.GetAt( 0 ) != 11 )
   {
      test_number_that_failed = 49;
      return( FALSE );
   }

   if ( array_1.GetAt( 1 ) != 2 )
   {
      test_number_that_failed = 50;
      return( FALSE );
   }

   if ( array_1.GetAt( 2 ) != 3 )
   {
      test_number_that_failed = 51;
      return( FALSE );
   }

   array_1.SetAt( 1, 22 );

   if ( array_1.GetSize() != 3 )
   {
      test_number_that_failed = 52;
      return( FALSE );
   }

   if ( array_1.GetUpperBound() != 2 )
   {
      test_number_that_failed = 53;
      return( FALSE );
   }

   if ( array_1.GetAt( 0 ) != 11 )
   {
      test_number_that_failed = 54;
      return( FALSE );
   }

   if ( array_1.GetAt( 1 ) != 22 )
   {
      test_number_that_failed = 55;
      return( FALSE );
   }

   if ( array_1.GetAt( 2 ) != 3 )
   {
      test_number_that_failed = 56;
      return( FALSE );
   }

   array_1.SetAt( 2, 33 );

   if ( array_1.GetSize() != 3 )
   {
      test_number_that_failed = 57;
      return( FALSE );
   }

   if ( array_1.GetUpperBound() != 2 )
   {
      test_number_that_failed = 58;
      return( FALSE );
   }

   if ( array_1.GetAt( 0 ) != 11 )
   {
      test_number_that_failed = 59;
      return( FALSE );
   }

   if ( array_1.GetAt( 1 ) != 22 )
   {
      test_number_that_failed = 60;
      return( FALSE );
   }

   if ( array_1.GetAt( 2 ) != 33 )
   {
      test_number_that_failed = 61;
      return( FALSE );
   }

   //   void        RemoveAt( int array_index, int number_of_elements_to_remove = 1 );

   array_1.Add( 44 );

   // Remove at the end
   array_1.RemoveAt( array_1.GetUpperBound() );

   if ( array_1.GetSize() != 3 )
   {
      test_number_that_failed = 62;
      return( FALSE );
   }

   if ( array_1.GetUpperBound() != 2 )
   {
      test_number_that_failed = 63;
      return( FALSE );
   }

   if ( array_1.GetAt( 0 ) != 11 )
   {
      test_number_that_failed = 64;
      return( FALSE );
   }

   if ( array_1.GetAt( 1 ) != 22 )
   {
      test_number_that_failed = 65;
      return( FALSE );
   }

   if ( array_1.GetAt( 2 ) != 33 )
   {
      test_number_that_failed = 66;
      return( FALSE );
   }

   array_1.Add( 44 );

   if ( array_1.GetAt( array_1.GetUpperBound() ) != 44 )
   {
      test_number_that_failed = 66;
      return( FALSE );
   }

   // Remove at the beginning

   array_1.RemoveAt( 0 );

   if ( array_1.GetSize() != 3 )
   {
      test_number_that_failed = 67;
      return( FALSE );
   }

   if ( array_1.GetUpperBound() != 2 )
   {
      test_number_that_failed = 68;
      return( FALSE );
   }

   if ( array_1.GetAt( 0 ) != 22 )
   {
      test_number_that_failed = 69;
      return( FALSE );
   }

   if ( array_1.GetAt( 1 ) != 33 )
   {
      test_number_that_failed = 70;
      return( FALSE );
   }

   if ( array_1.GetAt( 2 ) != 44 )
   {
      test_number_that_failed = 71;
      return( FALSE );
   }

   // Remove in the middle

   array_1.RemoveAt( 1 );

   if ( array_1.GetSize() != 2 )
   {
      test_number_that_failed = 72;
      return( FALSE );
   }

   if ( array_1.GetUpperBound() != 1 )
   {
      test_number_that_failed = 73;
      return( FALSE );
   }

   if ( array_1.GetAt( 0 ) != 22 )
   {
      test_number_that_failed = 74;
      return( FALSE );
   }

   if ( array_1.GetAt( 1 ) != 44 )
   {
      test_number_that_failed = 75;
      return( FALSE );
   }

   // Remove Multiple

   array_1.RemoveAt( 0, 2 );

   if ( array_1.GetSize() != 0 )
   {
      test_number_that_failed = 76;
      return( FALSE );
   }

   if ( array_1.GetUpperBound() != (-1) )
   {
      test_number_that_failed = 77;
      return( FALSE );
   }

   array_1.Add( 11 );
   array_1.Add( 22 );
   array_1.Add( 33 );
   array_1.Add( 44 );

   array_1.RemoveAt( 1, 2 );

   if ( array_1.GetSize() != 2 )
   {
      test_number_that_failed = 78;
      return( FALSE );
   }

   if ( array_1.GetUpperBound() != 1 )
   {
      test_number_that_failed = 79;
      return( FALSE );
   }

   if ( array_1.GetAt( 0 ) != 11 )
   {
      test_number_that_failed = 80;
      return( FALSE );
   }

   if ( array_1.GetAt( 1 ) != 44 )
   {
      test_number_that_failed = 81;
      return( FALSE );
   }

   array_1.Add( 55 );

   // Remove Multiple at the end

   array_1.RemoveAt( 1, 2 );

   if ( array_1.GetSize() != 1 )
   {
      test_number_that_failed = 82;
      return( FALSE );
   }

   if ( array_1.GetUpperBound() != 0 )
   {
      test_number_that_failed = 83;
      return( FALSE );
   }

   if ( array_1.GetAt( 0 ) != 11 )
   {
      test_number_that_failed = 84;
      return( FALSE );
   }

   //   void        RemoveAll( void );
   array_1.RemoveAll();

   if ( array_1.GetSize() != 0 )
   {
      test_number_that_failed = 85;
      return( FALSE );
   }

   if ( array_1.GetUpperBound() != (-1) )
   {
      test_number_that_failed = 86;
      return( FALSE );
   }

   //   void        InsertAt( int array_index, ARRAY_TYPE new_element, int number_of_times_to_insert_it = 1 );

   array_1.InsertAt( 0, 11, 3 );

   if ( array_1.GetSize() != 3 )
   {
      test_number_that_failed = 87;
      return( FALSE );
   }

   if ( array_1.GetAt( 0 ) != 11 )
   {
      test_number_that_failed = 88;
      return( FALSE );
   }

   if ( array_1.GetAt( 1 ) != 11 )
   {
      test_number_that_failed = 89;
      return( FALSE );
   }

   if ( array_1.GetAt( 2 ) != 11 )
   {
      test_number_that_failed = 90;
      return( FALSE );
   }

   array_1.InsertAt( array_1.GetSize(), 22, 2 );

   if ( array_1.GetSize() != 5 )
   {
      test_number_that_failed = 91;
      return( FALSE );
   }

   if ( array_1.GetAt( 0 ) != 11 )
   {
      test_number_that_failed = 92;
      return( FALSE );
   }

   if ( array_1.GetAt( 1 ) != 11 )
   {
      test_number_that_failed = 93;
      return( FALSE );
   }

   if ( array_1.GetAt( 2 ) != 11 )
   {
      test_number_that_failed = 94;
      return( FALSE );
   }

   if ( array_1.GetAt( 3 ) != 22 )
   {
      test_number_that_failed = 95;
      return( FALSE );
   }

   if ( array_1.GetAt( 4 ) != 22 )
   {
      test_number_that_failed = 96;
      return( FALSE );
   }

   array_1.InsertAt( 3, 33, 2 );

   if ( array_1.GetSize() != 7 )
   {
      test_number_that_failed = 97;
      return( FALSE );
   }

   if ( array_1.GetAt( 0 ) != 11 )
   {
      test_number_that_failed = 98;
      return( FALSE );
   }

   if ( array_1.GetAt( 1 ) != 11 )
   {
      test_number_that_failed = 99;
      return( FALSE );
   }

   if ( array_1.GetAt( 2 ) != 11 )
   {
      test_number_that_failed = 100;
      return( FALSE );
   }

   if ( array_1.GetAt( 3 ) != 33 )
   {
      test_number_that_failed = 101;
      return( FALSE );
   }

   if ( array_1.GetAt( 4 ) != 33 )
   {
      test_number_that_failed = 102;
      return( FALSE );
   }

   if ( array_1.GetAt( 5 ) != 22 )
   {
      test_number_that_failed = 103;
      return( FALSE );
   }

   if ( array_1.GetAt( 6 ) != 22 )
   {
      test_number_that_failed = 104;
      return( FALSE );
   }

   //   void        Copy( const CByteArray& source );

   array_1.RemoveAll();

   array_1.Add( 1 );
   array_1.Add( 2 );
   array_1.Add( 3 );

   CDWordArray array_2;

   array_2.Copy( array_1 );

   if ( array_2.GetSize() != 3 )
   {
      test_number_that_failed = 105;
      return( FALSE );
   }

   if ( array_2.GetAt( 0 ) != 1 )
   {
      test_number_that_failed = 106;
      return( FALSE );
   }

   if ( array_2.GetAt( 1 ) != 2 )
   {
      test_number_that_failed = 107;
      return( FALSE );
   }

   if ( array_2.GetAt( 2 ) != 3 )
   {
      test_number_that_failed = 108;
      return( FALSE );
   }

   //   void        Append( const CByteArray& source );

   array_2.RemoveAll();
   array_1.RemoveAll();

   array_1.Add( 11 );
   array_2.Add( 22 );

   array_1.Append( array_2 );

   if ( array_1.GetSize() != 2 )
   {
      test_number_that_failed = 109;
      return( FALSE );
   }

   if ( array_1.GetAt( 0 ) != 11 )
   {
      test_number_that_failed = 110;
      return( FALSE );
   }

   if ( array_1.GetAt( 1 ) != 22 )
   {
      test_number_that_failed = 111;
      return( FALSE );
   }

   //   void        SetSize( int new_size, int x = 32 );

   array_1.SetSize( 3, 99 );

   if ( array_1.GetSize() != 3 )
   {
      test_number_that_failed = 112;
      return( FALSE );
   }

   if ( array_1.GetAt( 0 ) != 11 )
   {
      test_number_that_failed = 113;
      return( FALSE );
   }

   if ( array_1.GetAt( 1 ) != 22 )
   {
      test_number_that_failed = 114;
      return( FALSE );
   }

   if ( array_1.GetAt( 2 ) != 0 )
   {
      test_number_that_failed = 115;
      return( FALSE );
   }

   array_1.RemoveAll();
   array_1.SetSize( 5 );

   DWORD elements[ 5 ];

   elements[ 0 ] = 11;
   elements[ 1 ] = 22;
   elements[ 2 ] = 33;
   elements[ 3 ] = 44;
   elements[ 4 ] = 55;

   //   ARRAY_TYPE * GetData( void );
   CopyMemory( array_1.GetData(), elements, array_1.GetSize() * sizeof( DWORD ) );

   if ( array_1.GetAt( 0 ) != 11 )
   {
      test_number_that_failed = 116;
      return( FALSE );
   }

   if ( array_1.GetAt( 1 ) != 22 )
   {
      test_number_that_failed = 117;
      return( FALSE );
   }

   if ( array_1.GetAt( 2 ) != 33 )
   {
      test_number_that_failed = 118;
      return( FALSE );
   }

   if ( array_1.GetAt( 3 ) != 44 )
   {
      test_number_that_failed = 119;
      return( FALSE );
   }

   if ( array_1.GetAt( 4 ) != 55 )
   {
      test_number_that_failed = 120;
      return( FALSE );
   }

   //   const ARRAY_TYPE * GetData( void ) const;

   array_1.InsertAt( 0, (DWORD) 0 ); // Modify the buffer

   const DWORD * const_elements = array_1.GetData();

   if ( const_elements[ 0 ] != 0 )
   {
      test_number_that_failed = 121;
      return( FALSE );
   }

   if ( const_elements[ 1 ] != 11 )
   {
      test_number_that_failed = 122;
      return( FALSE );
   }

   if ( const_elements[ 2 ] != 22 )
   {
      test_number_that_failed = 123;
      return( FALSE );
   }

   if ( const_elements[ 3 ] != 33 )
   {
      test_number_that_failed = 124;
      return( FALSE );
   }

   if ( const_elements[ 4 ] != 44 )
   {
      test_number_that_failed = 125;
      return( FALSE );
   }

   if ( const_elements[ 5 ] != 55 )
   {
      test_number_that_failed = 126;
      return( FALSE );
   }

   // InsertAt( array )

   // We must test three scenarios, inserting at the beginning,
   // inserting at the end, and inserting in the middle

   // Insert in the middle

   array_1.RemoveAll();

   if ( array_1.GetSize() != 0 )
   {
      test_number_that_failed = 127;
      return( FALSE );
   }

   array_2.RemoveAll();

   if ( array_2.GetSize() != 0 )
   {
      test_number_that_failed = 128;
      return( FALSE );
   }

   array_1.Add( 1 );
   array_1.Add( 4 );
   array_1.Add( 5 );

   array_2.Add( 2 );
   array_2.Add( 3 );

   array_1.InsertAt( 1, &array_2 );

   if ( array_1.GetAt( 0 ) != 1 ||
        array_1.GetAt( 1 ) != 2 ||
        array_1.GetAt( 2 ) != 3 ||
        array_1.GetAt( 3 ) != 4 ||
        array_1.GetAt( 4 ) != 5 )
   {
      test_number_that_failed = 129;
      return( FALSE );
   }

   // Insert at the beginning

   array_1.RemoveAll();

   if ( array_1.GetSize() != 0 )
   {
      test_number_that_failed = 130;
      return( FALSE );
   }

   array_2.RemoveAll();

   if ( array_2.GetSize() != 0 )
   {
      test_number_that_failed = 131;
      return( FALSE );
   }

   array_1.Add( 3 );
   array_1.Add( 4 );
   array_1.Add( 5 );

   array_2.Add( 1 );
   array_2.Add( 2 );

   array_1.InsertAt( 0, &array_2 );

   if ( array_1.GetAt( 0 ) != 1 ||
        array_1.GetAt( 1 ) != 2 ||
        array_1.GetAt( 2 ) != 3 ||
        array_1.GetAt( 3 ) != 4 ||
        array_1.GetAt( 4 ) != 5 )
   {
      test_number_that_failed = 132;
      return( FALSE );
   }

   // Insert at the end

   array_1.RemoveAll();

   if ( array_1.GetSize() != 0 )
   {
      test_number_that_failed = 133;
      return( FALSE );
   }

   array_2.RemoveAll();

   if ( array_2.GetSize() != 0 )
   {
      test_number_that_failed = 134;
      return( FALSE );
   }

   array_1.Add( 1 );
   array_1.Add( 2 );
   array_1.Add( 3 );

   array_2.Add( 4 );
   array_2.Add( 5 );

   array_1.InsertAt( 3, &array_2 );

   if ( array_1.GetAt( 0 ) != 1 ||
        array_1.GetAt( 1 ) != 2 ||
        array_1.GetAt( 2 ) != 3 ||
        array_1.GetAt( 3 ) != 4 ||
        array_1.GetAt( 4 ) != 5 )
   {
      test_number_that_failed = 135;
      return( FALSE );
   }

   test_number_that_failed = 135;

   return( TRUE );
}
