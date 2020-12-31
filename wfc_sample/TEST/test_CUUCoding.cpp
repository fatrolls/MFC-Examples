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
** Copyright, 1997, Samuel R. Blackburn
**
** $Workfile: test_CUUCoding.cpp $
** $Revision: 1 $
** $Modtime: 6/22/98 9:23p $
*/

void test_CUUCoding( void )
{
   WFCTRACEINIT( TEXT( "test_CUUCoding()" ) );

   CByteArray bytes_to_encode;

   // Generate some test data

   int index = 0;

   while( index < 1024 )
   {
      bytes_to_encode.Add( static_cast< BYTE >( index ) );
      index++;
   }

   CByteArray encoded_bytes;

   CUUCoding coder;

   // Encode the test data
   coder.Encode( bytes_to_encode, encoded_bytes );

   // Save the encoded bytes off for easy viewing

   CFile output_file;

   if ( output_file.Open( TEXT( "Output.uue" ), CFile::modeCreate | CFile::modeWrite ) != FALSE )
   {
      output_file.Write( encoded_bytes.GetData(), encoded_bytes.GetSize() );
      output_file.Close();
   }

   if ( output_file.Open( TEXT( "Input.bin" ), CFile::modeCreate | CFile::modeWrite ) != FALSE )
   {
      output_file.Write( bytes_to_encode.GetData(), bytes_to_encode.GetSize() );
      output_file.Close();
   }

   CByteArray decoded_bytes;

   // Decode the test data
   coder.Decode( encoded_bytes, decoded_bytes );

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

   index = 0;

   while( index < number_of_decoded_bytes )
   {
      if ( decoded_bytes.GetAt( index ) != bytes_to_encode.GetAt( index ) )
      {
         WFCTRACEVAL( TEXT( "FAILED! Comparison failed at index " ), index );
         WFCTRACEVAL( TEXT( "This was decoded " ), decoded_bytes.GetAt( index ) );
         WFCTRACEVAL( TEXT( "This was encoded " ), bytes_to_encode.GetAt( index ) );
         return;
      }

      index++;
   }

   WFCTRACEVAL( TEXT( "Tested OK size was " ), number_of_decoded_bytes );
}
