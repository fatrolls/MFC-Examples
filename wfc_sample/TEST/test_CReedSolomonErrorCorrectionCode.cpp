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
** $Workfile: test_CReedSolomonErrorCorrectionCode.cpp $
** $Revision: 3 $
** $Modtime: 8/23/99 8:13p $
*/

void test_CReedSolomonErrorCorrectionCode( void )
{
   WFCTRACEINIT( TEXT( "test_CReedSolomonErrorCorrectionCode()" ) );

   CReedSolomonErrorCorrectionCode transmitter;

   CRandomNumberGenerator2 random_number; // 1853265048

   int loop_index    = 0;
   int test_set_size = 4096;

   CByteArray data;

   data.SetSize( test_set_size ); // for speed

   while( loop_index < test_set_size )
   {
      data.Add( static_cast< BYTE >( random_number.GetInteger() ) );
      loop_index++;
   }

   CByteArray encoded_data;

   if ( transmitter.Encode( data, encoded_data ) == FALSE )
   {
      WFCTRACE( TEXT( "Can't encode\n" ) );
      return;
   }

   // We have encoded the data. Time to transmit it.

   // Here's our sloppy communications path. It adds errors to the data
   // Reed-Solomon is able to withstand one-bit-per-symbol errors.

   int number_of_errors_to_introduce = encoded_data.GetSize();
   int error_number                  = 0;
   int bit_number_to_smash           = 0;
   int number_of_errors_introduced   = 0;

   BYTE value = 0;

   CString debug_string;

   while( error_number < number_of_errors_to_introduce )
   {
      value = encoded_data.GetAt( error_number );

      bit_number_to_smash = random_number.GetInteger() % 8;

      if ( bit_test( value, bit_number_to_smash ) == 0 )
      {
         bit_set( value, bit_number_to_smash );
      }
      else
      {
         bit_clear( value, bit_number_to_smash );
      }

      ASSERT( value != encoded_data.GetAt( error_number ) );

      encoded_data.SetAt( error_number, value );
      number_of_errors_introduced++;

      error_number += ( ( ( random_number.GetInteger() % 8 ) + 1 ) + 16 );
   }

   WFCTRACEVAL( TEXT( "Whacked this many bits " ), number_of_errors_introduced );

   // We would now transmit data to the receiver

   CReedSolomonErrorCorrectionCode receiver;

   CByteArray decoded_data;

   int number_of_errors_corrected = receiver.Decode( encoded_data, decoded_data );

   if ( number_of_errors_corrected != (-1) )
   {
      // SUCCESS!

      WFCTRACE( TEXT( "SUCCESS!\n" ) );
      _tprintf( TEXT( "Decoded!\n" ) );
   }

   WFCTRACEVAL( TEXT( "Number of errors corrected " ), number_of_errors_corrected );
   WFCTRACEVAL( TEXT( "Number of bytes in decoded data " ), decoded_data.GetSize() );

   if ( data.GetSize() != decoded_data.GetSize() )
   {
      WFCTRACE( TEXT( "FAILED length test" ) );
      WFCTRACEVAL( TEXT( "Original length was " ), data.GetSize() );
      WFCTRACEVAL( TEXT( "Decoded length was " ), decoded_data.GetSize() );
   }

   loop_index = 0;

   while( loop_index < decoded_data.GetSize() )
   {
      if ( data.GetAt( loop_index ) != decoded_data.GetAt( loop_index ) )
      {
         WFCTRACEVAL( TEXT( "Comparison failed at byte " ), loop_index );
      }

      loop_index++;
   }
}

