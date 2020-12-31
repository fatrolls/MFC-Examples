#include "sender.h"
#pragma hdrstop

void main( void )
{
   WFCTRACEINIT( TEXT( "main()" ) );

   DWORD number_of_rounds = 10;
   DWORD test_buffer_size = ( 16 * 1024 ) + 1;
   DWORD checksum         = 0;
   DWORD loop_index       = 0;
   DWORD number_of_bytes_to_send = test_buffer_size * sizeof( DWORD );

   DWORD * test_buffer = NULL;

   CSerialFile serial;

   CString port( TEXT( "COM1:38400,n,8,1" ) );

   if ( serial.Open( port ) == FALSE )
   {
      WFCTRACEVAL( TEXT( "Can't open " ), port );
      _tprintf( TEXT( "Can't open %s\n" ), (LPCTSTR) port );
      return;
   }

   CRandomNumberGenerator2 random;

   while( loop_index < number_of_rounds )
   {
      prepare_buffer( random, test_buffer, test_buffer_size, checksum );
      serial.Write( &number_of_bytes_to_send, sizeof( number_of_bytes_to_send ) );
      serial.Write( test_buffer, number_of_bytes_to_send );
      serial.Write( &checksum, sizeof( checksum ) );

      loop_index++;
   }

   number_of_bytes_to_send = 0xFFFFFFFF;

   serial.Write( &number_of_bytes_to_send, sizeof( number_of_bytes_to_send ) );
   serial.Close();
}
