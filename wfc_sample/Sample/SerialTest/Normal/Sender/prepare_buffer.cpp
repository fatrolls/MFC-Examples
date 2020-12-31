#include "sender.h"
#pragma hdrstop

void prepare_buffer( CRandomNumberGenerator2& random, DWORD *& buffer, DWORD size, DWORD& checksum )
{
   WFCTRACEINIT( TEXT( "prepare_buffer()" ) );

   checksum = 0xAAAAAAAA; // Initialize the checksum

   DWORD loop_index = 0;

   while( loop_index < size )
   {
      buffer[ loop_index ] = random.GetInteger();
      checksum ^= buffer[ loop_index ];

      if ( checksum != 0 )
      {
         while( bit_test( checksum, 31 ) == 1 && checksum != 0 )
         {
            checksum <<= 1;
         }
      }

      loop_index++;
   }
}
