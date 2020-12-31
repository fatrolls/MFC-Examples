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
** $Workfile: test_CBase64Coding.cpp $
** $Revision: 4 $
** $Modtime: 5/12/00 7:17p $
*/

BOOL test_CBase64Coding( CString& class_name, int& test_number_that_failed )
{
   WFCTRACEINIT( TEXT( "test_CBase64Coding()" ) );

   class_name = TEXT( "CBase64Coding" );

   test_number_that_failed = 0;

   CBase64Coding coder;

   CByteArray bytes_to_encode;
   CByteArray encoded_bytes;
   CByteArray decoded_bytes;

   bytes_to_encode.Add( '1' );
   bytes_to_encode.Add( '1' );
   bytes_to_encode.Add( '1' );
   bytes_to_encode.Add( '0' );

   CString encoded_string;

   coder.Encode( bytes_to_encode, encoded_string );

   if ( encoded_string.Compare( TEXT( "MTExMA==" ) ) != 0 )
   {
      WFCTRACE( TEXT( "Coder failed." ) );
      test_number_that_failed = 1;
      return( FALSE );
   }

   CRandomNumberGenerator2 random;

   int test_index      = 2;
   int number_of_tests = 72 * 5; // 72 characters per line
   int loop_index      = 0;

   test_number_that_failed = test_index;

   // Test encoding to and from a CByteArray

   while( test_index < number_of_tests )
   {
      // Prepare to test

      bytes_to_encode.RemoveAll();
      encoded_bytes.RemoveAll();
      decoded_bytes.RemoveAll();

      // Generate some test data

      loop_index = 0;

      while( loop_index < test_index )
      {
         bytes_to_encode.Add( static_cast< BYTE >( random.GetInteger() ) );
         loop_index++;
      }

      // Encode the test data
      coder.Encode( bytes_to_encode, encoded_bytes );

      // Decode the test data
      coder.Decode( encoded_bytes, decoded_bytes );

      // See if what was decoded matches the test data (what was encoded)

      if ( decoded_bytes.GetSize() != bytes_to_encode.GetSize() )
      {
         return( FALSE );
      }

      loop_index = 0;

      while( loop_index < decoded_bytes.GetSize() )
      {
         if ( decoded_bytes.GetAt( loop_index ) != bytes_to_encode.GetAt( loop_index ) )
         {
            return( FALSE );
         }

         loop_index++;
      }

      test_number_that_failed++;
      test_index++;
   }

   // Test encoding to and from a CString

   test_index = 2;

   while( test_index < number_of_tests )
   {
      // Prepare to test

      bytes_to_encode.RemoveAll();
      encoded_string.Empty();
      decoded_bytes.RemoveAll();

      // Generate some test data

      loop_index = 0;

      while( loop_index < test_index )
      {
         bytes_to_encode.Add( static_cast< BYTE >( random.GetInteger() ) );
         loop_index++;
      }

      // Encode the test data
      coder.Encode( bytes_to_encode, encoded_bytes );

      // Decode the test data
      coder.Decode( encoded_bytes, decoded_bytes );

      // See if what was decoded matches the test data (what was encoded)

      if ( decoded_bytes.GetSize() != bytes_to_encode.GetSize() )
      {
         return( FALSE );
      }

      loop_index = 0;

      while( loop_index < decoded_bytes.GetSize() )
      {
         if ( decoded_bytes.GetAt( loop_index ) != bytes_to_encode.GetAt( loop_index ) )
         {
            return( FALSE );
         }

         loop_index++;
      }

      test_number_that_failed++;
      test_index++;
   }

   return( TRUE );
}
