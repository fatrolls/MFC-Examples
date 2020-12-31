#include <wfc.h>
#include "../CSimpleClass.hpp"
#pragma hdrstop

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
}

void _tmain( void )
{
   WFCTRACEINIT( TEXT( "_tmain()" ) );

   // Let's get some data to send

   test_CRandomNumberGenerator();
   return;

   CSimpleClass an_object;

   an_object.CharacterValue = 'A';
   an_object.ByteValue      = 0xFE;
   an_object.WordValue      = 0x1234;
   an_object.LongValue      = 81234;
   an_object.DwordValue     = 0x11223344;
   an_object.FloatValue     = (float) 3.14159;
   an_object.DoubleValue    = 99.44;
   an_object.StringValue    = TEXT( "Sam Loves Laura" );
   an_object.ByteArray.Add( 1 );
   an_object.ByteArray.Add( 2 );
   an_object.ByteArray.Add( 3 );
   an_object.ByteArray.Add( 4 );
   an_object.StringArray.Add( TEXT( "Laura Loves Sam" ) );
   an_object.StringArray.Add( TEXT( "Mad About The Bard" ) );
   an_object.StringArray.Add( TEXT( "They have been at a great feast of languages and stol'n the scraps." ) );
   an_object.StringArray.Add( TEXT( "Boy, what sign is it when a man of great spirit grows melancholy?" ) );
   an_object.StringArray.Add( TEXT( "A great sign, sir, that he will look sad." ) );
   an_object.DwordArray.Add( 0x22334455 );
   an_object.DwordArray.Add( 0x55667788 );
   an_object.DwordArray.Add( 0xFFFEFDFC );
   an_object.WordArray.Add(  99 );
   an_object.WordArray.Add( 100 );
   an_object.WordArray.Add( 101 );

   // Now that we have some data, let's package it up and send it out

   CDataChunk chunk; // Where the data will be stored

   chunk.Identifier = MAKE_DATA_ID( 'S', 'I', 'M', 'P' );

   CDataArchive archive; // That which knows how to store/restore stuff in a chunk

   archive.WriteTo( &chunk );

   an_object.Serialize( archive ); // Look familiar?

   // OK, now we've got a chunk of data to transmit, let's transmit it
   // using a TCP/IP socket

   CString ip_address;
   CSimpleSocket::GetMyAddress( ip_address ); // Open a socket to myself

   short port_number = 6060;

   CTalkingSocket socket( ip_address, port_number );

   if ( socket.Open() != FALSE )
   {
      CDataSocket data_socket( &socket );

      _tprintf( TEXT( "Sending " ) );

      an_object.Dump();

      // "adding" the chunk to the CDataSocket causes it to be transmitted

      data_socket.AddData( chunk );
   }
   else
   {
      TCHAR error_message[ 513 ];

      ZeroMemory( error_message, sizeof( error_message ) );

      CSimpleSocket::TranslateErrorCode( socket.GetErrorCode(), error_message, DIMENSION_OF( error_message ) );

      _tprintf( TEXT( "Couldn't open \"%s\" port %d because %s\n" ), (LPCTSTR) ip_address, (int) port_number, error_message );
   }
}
