#include "receiver.h"
#pragma hdrstop

void main( void )
{
   WFCTRACEINIT( TEXT( "main()" ) );

   CSerialFile serial;

   CString port( TEXT( "COM1:38400,n,8,1" ) );

   if ( serial.Open( port ) == FALSE )
   {
      WFCTRACEERROR( GetLastError() );
      WFCTRACEVAL( TEXT( "Can't open " ), port );
      _tprintf( TEXT( "Can't open %s\n" ), (LPCTSTR) port );
      return;
   }

   // Format on the wire is in DWORDS (Intel format because my two
   // test machines, 1 Pentium, 1 486 laptop are both Intel).
   // The first DWORD is the number of bytes being sent, then
   // those bytes, then a DWORD that is a checksum of the block.

   DWORD number_of_bytes_to_read = 0;
   DWORD computed_checksum       = 0;
   DWORD reported_checksum       = 0;
   DWORD number_of_test_blocks   = 0;
   DWORD number_of_errors        = 0;

   if ( serial.Read( &number_of_bytes_to_read, sizeof( number_of_bytes_to_read ) ) == FALSE )
   {
      WFCTRACEERROR( GetLastError() );
      _tprintf( TEXT( "Can't read first block.\n" ) );
      return;
   }

   BYTE * buffer = NULL;

   while( number_of_bytes_to_read != 0xFFFFFFFF )
   {
      buffer = new BYTE[ number_of_bytes_to_read ];

      if ( buffer != NULL )
      {
         if ( serial.Read( buffer, number_of_bytes_to_read ) == FALSE )
         {
            WFCTRACEERROR( GetLastError() );
            WFCTRACEVAL( TEXT( "Can't read this many bytes " ), number_of_bytes_to_read );
            _tprintf( TEXT( "Failed to read %lu bytes.\n" ), number_of_bytes_to_read );
            number_of_errors++;
         }
         else
         {
            if ( ( number_of_bytes_to_read % sizeof( DWORD ) ) != 0 )
            {
               WFCTRACE( TEXT( "Bad sender" ) );
               _tprintf( TEXT( "Sender is not sending DWORDs. Aborting test.\n" ) );
               delete [] buffer;
               buffer = NULL;
               return;
            }

            computed_checksum = compute_checksum( (const DWORD *) buffer, number_of_bytes_to_read / sizeof( DWORD ) );

            if ( serial.Read( &reported_checksum, sizeof( reported_checksum ) ) == FALSE )
            {
               WFCTRACEERROR( GetLastError() );
               WFCTRACE( TEXT( "Can't read reported checksum." ) );
               _tprintf( TEXT( "Can't read reported checksum.\n" ) );
               number_of_errors++;
            }
            else
            {
               if ( computed_checksum != reported_checksum )
               {
                  WFCTRACE( TEXT( "Failed checksum." ) );
                  _tprintf( TEXT( "Failed checksum.\n" ) );
                  number_of_errors++;
               }
            }
         }

         delete [] buffer;
         buffer = NULL;
      }

      number_of_test_blocks++;

      if ( serial.Read( &number_of_bytes_to_read, sizeof( number_of_bytes_to_read ) ) == FALSE )
      {
         WFCTRACEERROR( GetLastError() );
         WFCTRACE( TEXT( "Giving up." ) );
         number_of_bytes_to_read = 0xFFFFFFFF;
      }
   }

   if ( buffer != NULL )
   {
      delete [] buffer;
      buffer = NULL;
   }

   WFCTRACEVAL( TEXT( "Number of tested blocks " ), number_of_test_blocks );
   WFCTRACEVAL( TEXT( "Number that failed " ), number_of_errors );

   _tprintf( TEXT( "%lu errors in %lu blocks\n" ), number_of_errors, number_of_test_blocks );

   serial.Close();
}
