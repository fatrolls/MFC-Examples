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
** $Revision: 3 $
** $Modtime: 12/13/99 1:04a $
*/

void test_XML( void )
{
   WFCTRACEINIT( TEXT( "test_XML()" ) );

   CBase64Coding coder;

   CString output;

   CByteArray input;

   input.Add( '1' );
   input.Add( '1' );
   input.Add( '1' );
   input.Add( '0' );

   coder.Encode( input, output );

   WFCTRACEVAL( TEXT( "Output " ), output );

   if ( output.Compare( TEXT( "MTExMA==" ) ) != 0 )
   {
      WFCTRACE( TEXT( "Coder failed." ) );
   }
   else
   {
      WFCTRACE( TEXT( "Coder passed." ) );
   }

#if 0

   CRandomNumberGenerator2 random;

   CByteArray bytes_to_encode;

   // Generate some test data

   int loop_index         = 0;
   int number_of_integers = 16 * 1024;

   DWORD random_value = 0;

   while( loop_index < number_of_integers )
   {
      random_value = random.GetInteger();

      bytes_to_encode.Add( static_cast< BYTE >( HIBYTE( HIWORD( random_value) ) ) );
      bytes_to_encode.Add( static_cast< BYTE >( LOBYTE( HIWORD( random_value) ) ) );
      bytes_to_encode.Add( static_cast< BYTE >( HIBYTE( LOWORD( random_value) ) ) );
      bytes_to_encode.Add( static_cast< BYTE >( LOBYTE( LOWORD( random_value) ) ) );

      loop_index++;
   }

   ASSERT( bytes_to_encode.GetSize() == ( number_of_integers * 4 ) );

   CByteArray encoded_bytes;

   CBase64Coding coder;

   DWORD end_tick_count   = 0;
   DWORD start_tick_count = GetTickCount();

   // Encode the test data
   coder.Encode( bytes_to_encode, encoded_bytes );

   end_tick_count = GetTickCount();

   WFCTRACEVAL( TEXT( "Millseconds to encode " ), (DWORD) (end_tick_count - start_tick_count ) );
   WFCTRACEVAL( TEXT( "Number of bytes encoded " ), bytes_to_encode.GetSize() );
   WFCTRACEVAL( TEXT( "Encoded size " ), encoded_bytes.GetSize() );

   ASSERT( encoded_bytes.GetAt( encoded_bytes.GetSize() - 1 ) == '=' );

   CString encoded_string;

   start_tick_count = GetTickCount();
   coder.Encode( bytes_to_encode, encoded_string );
   end_tick_count = GetTickCount();

   WFCTRACEVAL( TEXT( "Millseconds to encode string " ), (DWORD) (end_tick_count - start_tick_count ) );

   CByteArray decoded_bytes;

   // Decode the test data
   start_tick_count = GetTickCount();
   coder.Decode( encoded_bytes, decoded_bytes );
   end_tick_count = GetTickCount();

   WFCTRACEVAL( TEXT( "Millseconds to decode " ), (DWORD) (end_tick_count - start_tick_count ) );

   // See if what was decoded matches the test data (what was encoded)

   int number_of_decoded_bytes = decoded_bytes.GetSize();

   if ( number_of_decoded_bytes != bytes_to_encode.GetSize() )
   {
      WFCTRACE( TEXT( "FAILED!!! What was decoded is a different size than what was encoded!" ) );
      WFCTRACEVAL( TEXT( "Number of bytes decoded is " ), number_of_decoded_bytes );
      WFCTRACEVAL( TEXT( "Number of bytes encoded is " ), bytes_to_encode.GetSize() );
      ASSERT( FALSE );
      return;
   }

   loop_index = 0;

   while( loop_index < number_of_decoded_bytes )
   {
      if ( decoded_bytes.GetAt( loop_index ) != bytes_to_encode.GetAt( loop_index ) )
      {
         WFCTRACEVAL( TEXT( "FAILED! Comparison failed at index " ), loop_index );
         WFCTRACEVAL( TEXT( "This was decoded " ), decoded_bytes.GetAt( loop_index ) );
         WFCTRACEVAL( TEXT( "This was encoded " ), bytes_to_encode.GetAt( loop_index ) );
         return;
      }

      loop_index++;
   }

   // Now test the decoding from a string

   decoded_bytes.RemoveAll();

   // Decode the test data
   start_tick_count = GetTickCount();
   coder.Decode( encoded_string, decoded_bytes );
   end_tick_count = GetTickCount();

   WFCTRACEVAL( TEXT( "Millseconds to decode string " ), (DWORD) (end_tick_count - start_tick_count ) );

   // See if what was decoded matches the test data (what was encoded)

   number_of_decoded_bytes = decoded_bytes.GetSize();

   if ( number_of_decoded_bytes != bytes_to_encode.GetSize() )
   {
      WFCTRACE( TEXT( "FAILED!!! What was decoded is a different size than what was encoded!" ) );
      WFCTRACEVAL( TEXT( "Number of bytes decoded is " ), number_of_decoded_bytes );
      WFCTRACEVAL( TEXT( "Number of bytes encoded is " ), bytes_to_encode.GetSize() );
      ASSERT( FALSE );
      return;
   }

   loop_index = 0;

   while( loop_index < number_of_decoded_bytes )
   {
      if ( decoded_bytes.GetAt( loop_index ) != bytes_to_encode.GetAt( loop_index ) )
      {
         WFCTRACEVAL( TEXT( "FAILED! Comparison failed at index " ), loop_index );
         WFCTRACEVAL( TEXT( "This was decoded " ), decoded_bytes.GetAt( loop_index ) );
         WFCTRACEVAL( TEXT( "This was encoded " ), bytes_to_encode.GetAt( loop_index ) );
         return;
      }

      loop_index++;
   }

   WFCTRACEVAL( TEXT( "Tested OK size was " ), number_of_decoded_bytes );
#endif
}
