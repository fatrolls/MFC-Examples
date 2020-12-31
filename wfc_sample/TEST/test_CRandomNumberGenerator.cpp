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
** Copyright, 1998, Samuel R. Blackburn
**
** $Workfile: test_CRandomNumberGenerator.cpp $
** $Revision: 4 $
** $Modtime: 5/26/98 5:00a $
*/

void count_ones_and_zeroes( DWORD number_of_dwords_to_test )
{
   WFCTRACEINIT( TEXT( "count_ones_and_zeroes()" ) );

   DWORD index = 0;

   DWORD number_of_ones   = 0;
   DWORD number_of_zeroes = 0;

   DWORD length_of_longest_series_of_ones   = 0;
   DWORD length_of_longest_series_of_zeroes = 0;

   DWORD number_of_consecutive_ones   = 0;
   DWORD number_of_consecutive_zeroes = 0;

   DWORD last_bit = 0;

   DWORD bit_number = 0;

   DWORD random_value = 0;

   DWORD bit = 0;

   DWORD bits[ 32 ]; // Count the one-bits in the locations

   bit_number = 0;

   while( bit_number < DIMENSION_OF( bits ) )
   {
      bits[ bit_number ] = 0;
      bit_number++;
   }

   bit_number = 0;

   CRandomNumberGenerator2 generator;
   //CRandomNumberGenerator generator;
   //CSuperRandomNumberGenerator generator;

   _tprintf( TEXT( "Testing %lu bits\n" ), number_of_dwords_to_test * 32 );

   while( index < number_of_dwords_to_test )
   {
      random_value = generator.GetInteger();

      bit_number = 0;

      while( bit_number < 32 )
      {
         bit = bit_test( random_value, bit_number );

         if ( bit == 0 )
         {
            if ( bit == last_bit )
            {
               number_of_consecutive_zeroes++;

               if ( number_of_consecutive_zeroes > length_of_longest_series_of_zeroes )
               {
                  length_of_longest_series_of_zeroes = number_of_consecutive_zeroes;
               }
            }
            else
            {
               number_of_consecutive_zeroes = 1;
            }

            number_of_zeroes++;
         }
         else
         {
            // Bit is a 1

            bits[ bit_number ]++; // Increment our count

            if ( bit == last_bit )
            {
               number_of_consecutive_ones++;

               if ( number_of_consecutive_ones > length_of_longest_series_of_ones )
               {
                  length_of_longest_series_of_ones = number_of_consecutive_ones;
               }
            }
            else
            {
               number_of_consecutive_ones = 1;
            }

            number_of_ones++;
         }

         last_bit = bit;
      
         bit_number++;
      }

      index++;
   }

   // Now that we've collected our statistics, let's report them

   WFCTRACEVAL( TEXT( "Number of Ones " ),           number_of_ones                     );
   WFCTRACEVAL( TEXT( "Number of Zeroes " ),         number_of_zeroes                   );
   WFCTRACEVAL( TEXT( "Longest series of ones " ),   length_of_longest_series_of_ones   );
   WFCTRACEVAL( TEXT( "Longest series of zeroes " ), length_of_longest_series_of_zeroes );

   _tprintf( TEXT( "Number of ones           %lu\n" ), number_of_ones                     );
   _tprintf( TEXT( "Number of zeroes         %lu\n" ), number_of_zeroes                   );
   _tprintf( TEXT( "Longest series of ones   %lu\n" ), length_of_longest_series_of_ones   );
   _tprintf( TEXT( "Longest series of zeroes %lu\n" ), length_of_longest_series_of_zeroes );

   _tprintf( TEXT( "\nDistribution of 1's in location:\n" ), length_of_longest_series_of_zeroes );
   bit_number = 0;

   CString output_string;

   while( bit_number < DIMENSION_OF( bits ) )
   {
      output_string.Format( TEXT( "bit%lu = %lu" ), bit_number, bits[ bit_number ] );
      _tprintf( TEXT( "%s\n" ), (LPCTSTR) output_string );
      WFCTRACEVAL( TEXT( " " ), output_string );
      bit_number++;
   }
}

void test_CRandomNumberGenerator( void )
{
   WFCTRACEINIT( TEXT( "test_CRandomNumberGenerator()" ) );

/************************************************************************
 This is the initialization routine for the random number generator RANMAR()
 NOTE: The seed variables can have values between:    0 <= IJ <= 31328
                                                      0 <= KL <= 30081
 The random number sequences created by these two seeds are of sufficient
 length to complete an entire calculation with. For example, if several
 different groups are working on different parts of the same calculation,
 each group could be assigned its own IJ seed. This would leave each group
 with 30000 choices for the second seed. That is to say, this random
 number generator can create 900 million different subsequences -- with
 each subsequence having a length of approximately 10^30.

 Use IJ = 1802 & KL = 9373 to test the random number generator. The
 subroutine RANMAR should be used to generate 20000 random numbers.
 Then display the next six random numbers generated multiplied by 4096*4096
 If the random number generator is working properly, the random numbers
 should be:
           6533892.0  14220222.0   7275067.0
           6172232.0   8354498.0  10633180.0
************************************************************************/

   CRandomNumberGenerator random_number( MAKELONG( 1802, 9373 ) );

   int index = 0;

   double temp_double = 0.0;

   while( index < 20000 )
   {
      temp_double = random_number.GetFloat();
      index++;
   }

   temp_double = 4096.0 * 4096.0;

   double test_number = 0.0;

   test_number = random_number.GetFloat() * temp_double;
   _tprintf( TEXT( "test #1 yields %lf when it should be 6533892.0\n" ), test_number );

   test_number = random_number.GetFloat() * temp_double;
   _tprintf( TEXT( "test #2 yields %lf when it should be 14220222.0\n" ), test_number );

   test_number = random_number.GetFloat() * temp_double;
   _tprintf( TEXT( "test #3 yields %lf when it should be 7275067.0\n" ), test_number );

   test_number = random_number.GetFloat() * temp_double;
   _tprintf( TEXT( "test #4 yields %lf when it should be 6172232.0\n" ), test_number );

   test_number = random_number.GetFloat() * temp_double;
   _tprintf( TEXT( "test #5 yields %lf when it should be 8354498.0\n" ), test_number );

   test_number = random_number.GetFloat() * temp_double;
   _tprintf( TEXT( "test #6 yields %lf when it should be 10633180.0\n" ), test_number );

   count_ones_and_zeroes( 10000000 );
   //count_ones_and_zeroes( 100000 );
}
