#include "receiver.h"
#pragma hdrstop

DWORD compute_checksum( const DWORD * buffer, DWORD number_of_entries )
{
   WFCTRACEINIT( TEXT( "compute_checksum()" ) );

   DWORD checksum = 0xAAAAAAAA; // Initialize the checksum

   DWORD loop_index = 0;

   while( loop_index < number_of_entries )
   {
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

   return( checksum );
}
