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
** $Workfile: test_CBitArray.cpp $
** $Revision: 2 $
** $Modtime: 12/12/98 6:30a $
*/

void test_CBitArray( void )
{
   WFCTRACEINIT( TEXT( "test_CBitArray()" ) );

   CBitArray bits;

   bits.SetSize( 2 );
   bits.SetAt( 0, 1 );
   bits.SetAt( 1, 0 );

   ASSERT( bits.GetAt( 0 ) == 1 );
   ASSERT( bits.GetAt( 1 ) == 0 );

   bits.Add( 1, 34 );
   ASSERT( bits.GetSize() == 36 );

   bits.LeftTrim( 4 );
   ASSERT( bits.GetSize() == 32 );

   bits.SetSize( 10 );
   ASSERT( bits.GetSize() == 10 );

   bits.SetSize( 32 );
   ASSERT( bits.GetSize() == 32 );

   bits.SetAll( 1 );
   bits.SetAll( 0 );

   // Array should be zeroeized

   // Setup our bytes test, the array is 32 bits wide now, let's
   // setup the test so four bytes will come out with the values of:
   // Byte 0 - 130 (0x82 or 10000010)
   // Byte 1 -  65 (0x41 or 01000001)
   // Byte 2 - 125 (0x7D or 01111101)
   // Byte 3 - 190 (0xBE or 10111110)

   // Array Index: 01234567
   // Byte 1 bits: 10000010

   bits.SetAt( 0, 1 );
   bits.SetAt( 6, 1 );

   //                111111
   // Array Index: 89012345
   // Byte 2 bits: 01000001

   bits.SetAt(  9, 1 );
   bits.SetAt( 15, 1 );

   //              11112222
   // Array Index: 67890123
   // Byte 3 bits: 01111101

   bits.SetAt( 17, 1 );
   bits.SetAt( 18, 1 );
   bits.SetAt( 19, 1 );
   bits.SetAt( 20, 1 );
   bits.SetAt( 21, 1 );
   bits.SetAt( 23, 1 );

   //              22222233
   // Array Index: 45678901
   // Byte 4 bits: 10111110

   bits.SetAt( 24, 1 );
   bits.SetAt( 26, 1 );
   bits.SetAt( 27, 1 );
   bits.SetAt( 28, 1 );
   bits.SetAt( 29, 1 );
   bits.SetAt( 30, 1 );

   CByteArray bytes;

   bits.CopyTo( bytes );

   ASSERT( bytes.GetSize()  == 4    );
   ASSERT( bytes.GetAt( 0 ) == 0x82 );
   ASSERT( bytes.GetAt( 1 ) == 0x41 );
   ASSERT( bytes.GetAt( 2 ) == 0x7D );
   ASSERT( bytes.GetAt( 3 ) == 0xBE );

   // Now test the complement of that array

   bits.Complement();

   bits.CopyTo( bytes );

   ASSERT( bytes.GetSize()  == 4    );
   ASSERT( bytes.GetAt( 0 ) == 0x7D );
   ASSERT( bytes.GetAt( 1 ) == 0xBE );
   ASSERT( bytes.GetAt( 2 ) == 0x82 );
   ASSERT( bytes.GetAt( 3 ) == 0x41 );

   bits.Complement();

   bits.CopyTo( bytes );

   ASSERT( bytes.GetSize()  == 4    );
   ASSERT( bytes.GetAt( 0 ) == 0x82 );
   ASSERT( bytes.GetAt( 1 ) == 0x41 );
   ASSERT( bytes.GetAt( 2 ) == 0x7D );
   ASSERT( bytes.GetAt( 3 ) == 0xBE );

   bits.InsertAt( 0, 1 ); // 33 bits now
   ASSERT( bits.GetSize() == 33 );

   bits.CopyTo( bytes );
   ASSERT( bytes.GetSize() == 5 );
   ASSERT( bytes.GetAt( 0 ) == 0xC1 );

   bits.RemoveAt( 1 );
   ASSERT( bits.GetSize() == 32 );

   bits.CopyTo( bytes );
   ASSERT( bytes.GetSize()  == 4    );
   ASSERT( bytes.GetAt( 0 ) == 0x82 );
   ASSERT( bytes.GetAt( 1 ) == 0x41 );
   ASSERT( bytes.GetAt( 2 ) == 0x7D );
   ASSERT( bytes.GetAt( 3 ) == 0xBE );

   ASSERT( bits.GetValue(  0, 8 ) == 0x82 );
   ASSERT( bits.GetValue(  8, 8 ) == 0x41 );
   ASSERT( bits.GetValue( 16, 8 ) == 0x7D );
   ASSERT( bits.GetValue( 24, 8 ) == 0xBE );

   bits.InsertAt( 0, 1 );

   ASSERT( bits.GetSize() == 33 );
   ASSERT( bits.GetValue(  0, 8 ) == 0xC1 );
   ASSERT( bits.GetValue(  1, 8 ) == 0x82 );
   ASSERT( bits.GetValue( 24, 8 ) == 0xDF );
   ASSERT( bits.GetValue( 25, 8 ) == 0xBE );

   bits.RemoveAll();

   bits.Add( 0 );
   bits.SetAll( 1 );
   bits.Add( 0 );
   ASSERT( bits.GetAt( 1 ) == 0 );

   bits.RemoveAll();

   bits.Add( 0 );
   bits.Complement();
   bits.Add( 0 );
   ASSERT( bits.GetAt( 1 ) == 0 );

   DWORD starting_tick_count = 0;
   DWORD ending_tick_count   = 0;

   bits.RemoveAll();

   DWORD added_value = 0x55;

   bits.AddValue( added_value, 8 );

   int loop_index = 0;

   // I always like to use prime number for testing sizes. I don't know
   // why it just seems to work better for me. It avoids problems like
   // "the code works when the index is a multiple of 2". So, I like
   // primes. A list of primes can be found at
   // http://www.utm.edu/research/primes/index.html

   int number_of_bits_to_insert = 10007;

   starting_tick_count = GetTickCount();

   while( loop_index < number_of_bits_to_insert )
   {
      bits.InsertAt( 0, 1 );
      loop_index++;
   }

   ending_tick_count = GetTickCount();

   _tprintf( TEXT( "Took %lu milliseconds to insert %d bits.\n" ), (DWORD)( ending_tick_count - starting_tick_count ), number_of_bits_to_insert );

   WFCTRACEVAL( TEXT( "Inserting this many bits " ), number_of_bits_to_insert );
   WFCTRACEVAL( TEXT( "Took this many milliseconds " ), (DWORD)( ending_tick_count - starting_tick_count ) );

   DWORD value_to_check = bits.GetValue( bits.GetSize() - 8, 8 );

   WFCTRACEVAL( TEXT( "Got " ), value_to_check );

   ASSERT( added_value == value_to_check );

   WFCTRACE( TEXT( "Passed." ) );
}
