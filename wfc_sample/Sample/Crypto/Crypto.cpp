#include <wfc.h>
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
** Copyright, 1996, Samuel R. Blackburn
**
** $Workfile: Crypto.cpp $
** $Revision: 3 $
** $Modtime: 3/08/98 3:18p $
*/

void print_system_error( DWORD error_code )
{
   LPVOID message_buffer = (LPVOID) NULL;

   ::FormatMessage( FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
                    NULL,
                    error_code,
                    MAKELANGID( LANG_ENGLISH, SUBLANG_ENGLISH_US ),
          (LPTSTR) &message_buffer,
                    0,
                    NULL );

   _tprintf( TEXT( "%s\n" ), (LPCTSTR) message_buffer );

   if ( message_buffer != NULL )
   {
      ::LocalFree( message_buffer );
   }
}

void encrypt( CCryptographicKey& key, CByteArray& data_to_encrypt, CByteArray& encrypted_data )
{
   WFCTRACEINIT( TEXT( "encrypt()" ) );

   if ( key.Encrypt( data_to_encrypt, encrypted_data ) == FALSE )
   {
      DWORD error_code = key.GetErrorCode();

      _tprintf( TEXT( "key.Encrypt() failed with " ) );
      print_system_error( error_code );
      return;
   }
}

void decrypt( CCryptographicKey& key, CByteArray& data_to_decrypt, CByteArray& decrypted_data )
{
   WFCTRACEINIT( TEXT( "decrypt()" ) );

   if ( key.Decrypt( data_to_decrypt, decrypted_data ) == FALSE )
   {
      DWORD error_code = key.GetErrorCode();

      _tprintf( TEXT( "key.Decrypt() failed with " ) );
      print_system_error( error_code );
      return;
   }
}

void export_key( CCryptographicKey& key_to_export, CCryptographicKey& who_to_export_to, CByteArray& exported_key )
{
   WFCTRACEINIT( TEXT( "export_key()" ) );

   exported_key.RemoveAll();

   if ( key_to_export.Export( who_to_export_to, exported_key ) != FALSE )
   {
      _tprintf( TEXT( "Exported key, length is %d bytes.\n" ), exported_key.GetSize() );
   }
   else
   {
      DWORD error_code = 0;

      error_code = key_to_export.GetErrorCode();

      _tprintf( TEXT( "Can't export key because " ) );
      print_system_error( error_code );
   }
}

void generate_key( CCryptographicProvider& provider, CCryptographicAlgorithm& algorithm )
{
   WFCTRACEINIT( TEXT( "generate_key()" ) );

   CCryptographicKey key_to_export;

   CByteArray buffer;

   // Get our own key for exchanging keys with someone else.

   if ( provider.GetUserKey( AT_KEYEXCHANGE, key_to_export ) != FALSE )
   {
      WFCTRACE( TEXT( "Uh oh..." ) );
   }

   CCryptographicKey key;

   if ( provider.CreateKey( algorithm, key ) != FALSE )
   {
      _tprintf( TEXT( "Generating key succeeded.\n" ) );

      // Since we got our own export key, we are affectively exporting the generated key to ourself

      export_key( key, key_to_export, buffer );
   }
   else
   {
      DWORD crypto_error = provider.GetErrorCode();

      _tprintf( TEXT( "CreateKey() failed with " ) );

      print_system_error( crypto_error );
   }
}

void enumerate_algorithms( CCryptographicProvider& provider )
{
   WFCTRACEINIT( TEXT( "enumerate_algorithms()" ) );

   // Get Provider's name

   _tprintf( TEXT( "Algorithms provided by \n" ) );

   CCryptographicAlgorithm algorithm;

   DWORD enumerator = 0;

   provider.EnumerateAlgorithms( enumerator );

   while( provider.GetNext( enumerator, algorithm ) != FALSE )
   {
      WFCTRACEVAL( TEXT( "Name       " ), algorithm.Name       );
      WFCTRACEVAL( TEXT( "ID         " ), algorithm.Identifier );
      WFCTRACEVAL( TEXT( "Bit Length " ), algorithm.BitLength  );

      if ( algorithm.IsDataEncrypt() != FALSE )
      {
         _tprintf( TEXT( "For encrypting data:     " ) );
      }
      else if ( algorithm.IsMessageEncrypt() != FALSE )
      {
         _tprintf( TEXT( "For encrypting messages: " ) );
      }
      else if ( algorithm.IsHash() != FALSE )
      {
         _tprintf( TEXT( "For hashing:             " ) );
      }
      else if ( algorithm.IsKeyExchange() != FALSE )
      {
         _tprintf( TEXT( "For exchanging keys:     " ) );
      }
      else if ( algorithm.IsSignature() != FALSE )
      {
         _tprintf( TEXT( "For digitally signing:   " ) );
      }

      _tprintf( TEXT( "ID: %08lX Bit Length: %3lu \"%s\"\n" ),
                        algorithm.Identifier,
                        algorithm.BitLength,
              (LPCTSTR) algorithm.Name );

      generate_key( provider, algorithm );
   }
}

void test_encrypt_decrypt( CCryptographicProvider& provider )
{
   WFCTRACEINIT( TEXT( "test_encrypt_decrypt()" ) );

   CByteArray data_to_encrypt;
   CByteArray encrypted_data;
   CByteArray decrypted_data;

   CString test_data( TEXT( "I Love WFC's" ) );

   int index = 0;

   while( index < test_data.GetLength() )
   {
      data_to_encrypt.Add( test_data[ index ] );
      index++;
   }

   // Now that we have some data to encrypt, we need to decide on an algorithm

   CCryptographicAlgorithm algorithm;

   algorithm.Identifier = CALG_RC2;

   CCryptographicKey key;

   DWORD error_code = 0;

   if ( provider.CreateKey( algorithm, key ) == FALSE )
   {
      error_code = provider.GetErrorCode();
      _tprintf( TEXT( "provider.CreateKey() failed with " ) );
      print_system_error( error_code );
      return;
   }

   if ( key.Encrypt( data_to_encrypt, encrypted_data ) == FALSE )
   {
      error_code = key.GetErrorCode();
      _tprintf( TEXT( "key.Encrypt() failed with " ) );
      print_system_error( error_code );
      return;
   }
   else
   {
      WFCTRACE( TEXT( "Encrypt succeeded." ) );
   }

   _tprintf( TEXT( "before encryption, length was %d, now it is %d\n" ),
             data_to_encrypt.GetSize(),
             encrypted_data.GetSize() );

   index = 0;

   while( index < encrypted_data.GetSize() )
   {
      _tprintf( TEXT( "%d. %c (%d)\n" ), index, encrypted_data.GetAt( index ), encrypted_data.GetAt( index ) );
      index++;
   }

   if ( key.Decrypt( encrypted_data, decrypted_data ) == FALSE )
   {
      error_code = key.GetErrorCode();
      _tprintf( TEXT( "key.Decrypt() failed with " ) );
      print_system_error( error_code );
      return;
   }
   else
   {
      WFCTRACE( TEXT( "Decrypt succeeded." ) );
   }

   index = decrypted_data.GetSize();

   if ( index != data_to_encrypt.GetSize() )
   {
      _tprintf( TEXT( "What went in ain't what came out. %d went in, %d bytes came out\n" ), 
                data_to_encrypt.GetSize(), 
                decrypted_data.GetSize() );
   }

   index = 0;

   _tprintf( TEXT( "Encrypted Data:\n" ) );

   while( index < data_to_encrypt.GetSize() )
   {
      _tprintf( TEXT( "%d. %c\n" ), index, data_to_encrypt.GetAt( index ) );
      index++;
   }

   _tprintf( TEXT( "Decrypted Data:\n" ) );

   index = 0;

   while( index< decrypted_data.GetSize() )
   {
      _tprintf( TEXT( "%d. %c (%d)\n" ), index, decrypted_data.GetAt( index ), decrypted_data.GetAt( index ) );
      index++;
   }

   WFCTRACE( TEXT( "OK" ) );
}

int _tmain( int , LPCTSTR [] )
{
   WFCTRACEINIT( TEXT( "main()" ) );

   CCryptographicProvider crypto;

   if ( crypto.Open() == FALSE )
   {
      DWORD crypto_error = 0;

      crypto_error = crypto.GetErrorCode();

      print_system_error( crypto_error );

      return( EXIT_SUCCESS );
   }

   // enumerate_algorithms( crypto );

   test_encrypt_decrypt( crypto );

   crypto.Close();

   return( EXIT_SUCCESS );
}
