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
** Copyright, 2000, Samuel R. Blackburn
**
** $Workfile: CCryptographicKey.cpp $
** $Revision: 30 $
** $Modtime: 1/04/00 5:09a $
** $Reuse Tracing Code: 1 $
*/

#if _MSC_VER < 1020
#pragma message( "Need Visual C++ 4.2 or later to compile CCryptographicKey" )
#else // _MSC_VER

#if defined( _DEBUG ) && ! defined( WFC_STL )
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

static BOOL wfc_trim_decrypted_data( CByteArray& decrypted_data )
{
   WFCLTRACEINIT( TEXT( "wfc_trim_decrypted_data()" ) );

   // Now that we've decrypted the data, let's strip off any padding

   if ( decrypted_data.GetSize() < 4 )
   {
      WFCTRACE( TEXT( "Not enough decrypted data." ) );
      return( FALSE );
   }

   BYTE byte_1 = 0;
   BYTE byte_2 = 0;
   BYTE byte_3 = 0;
   BYTE byte_4 = 0;

   byte_1 = decrypted_data.GetAt( 0 );
   byte_2 = decrypted_data.GetAt( 1 );
   byte_3 = decrypted_data.GetAt( 2 );
   byte_4 = decrypted_data.GetAt( 3 );

   DWORD size_of_plaintext = MAKE_DATA_LENGTH( byte_1, byte_2, byte_3, byte_4 );

   decrypted_data.RemoveAt( 0, 4 );

   ASSERT( size_of_plaintext <= (DWORD) decrypted_data.GetSize() );

   if ( size_of_plaintext > (DWORD) decrypted_data.GetSize() )
   {
      WFCTRACE( TEXT( "UH OH! Something bad happened" ) );
      return( FALSE );
   }

   // Now strip off that nasty padding....

   DWORD number_of_bytes_to_strip = decrypted_data.GetSize() - size_of_plaintext;

   decrypted_data.RemoveAt( decrypted_data.GetSize() - number_of_bytes_to_strip, number_of_bytes_to_strip );

   // Let's make one final check

   ASSERT( size_of_plaintext == (DWORD) decrypted_data.GetSize() );

   return( TRUE );
}

// Construction

CCryptographicKey::CCryptographicKey()
{
   WFCLTRACEINIT( TEXT( "CCryptographicKey::CCryptographicKey()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );

   m_Key                  = NULL;
   m_AutomaticallyDestroy = FALSE;
}

CCryptographicKey::CCryptographicKey( HCRYPTKEY source_handle, BOOL automatically_destroy )
{
   WFCLTRACEINIT( TEXT( "CCryptographicKey::CCryptographicKey( HCRYPTKEY )" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );

   m_Key                  = NULL;
   m_AutomaticallyDestroy = FALSE;

   FromHandle( source_handle, automatically_destroy );
}

CCryptographicKey::~CCryptographicKey()
{
   WFCLTRACEINIT( TEXT( "CCryptographicKey::CCryptographicKey()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );

   if ( m_AutomaticallyDestroy != FALSE )
   {
      Destroy();
   }
}

// Methods

BOOL CCryptographicKey::Decrypt( const CByteArray&          data_to_decrypt,
                                       CByteArray&          decrypted_data,
                                       BOOL                 this_is_the_last_chunk_of_data_to_be_decrypted,
                                       CCryptographicHash * hash_p,
                                       DWORD                flags )
{
   WFCLTRACEINIT( TEXT( "CCryptographicKey::Decrypt()" ) );

   BOOL return_value = FALSE;

   // This is really stupid. The CryptDecrypt function takes an in/out
   // for the buffer parameter. Besides not being const correct, it negates
   // the possibility of using memory mapped files. Normally, Microsoft
   // would notice something like this. This must be some pinhead's idea.

   HCRYPTHASH hash_handle = static_cast< HCRYPTHASH >( NULL );

   if ( hash_p == NULL )
   {
      WFCTRACE( TEXT( "Defaulting to no hash" ) );
      hash_handle = static_cast< HCRYPTHASH >( NULL );
   }

   // We were passed a pointer, don't trust it...

   try
   {
      if ( hash_p != NULL )
      {
         hash_handle = hash_p->GetHandle();
      }

      // Copy the data to decrypt over to the output buffer...

      decrypted_data.Copy( data_to_decrypt );

      DWORD data_length = decrypted_data.GetSize();

      return_value = ::CryptDecrypt( m_Key,
                                     hash_handle,
                                     this_is_the_last_chunk_of_data_to_be_decrypted,
                                     flags,
                                     decrypted_data.GetData(),
                                    &data_length );

      if ( return_value == FALSE )
      {
         m_ErrorCode = ::GetLastError();

         WFCLTRACEINIT( TEXT( "First attempt to decrypt failed." ) );

#if defined( _DEBUG )

         // Spit out a nice debugging message, these are all of the valid
         // error codes as documented in VC5

         CString debug_message;

         switch( m_ErrorCode )
         {
            case ERROR_INVALID_HANDLE:

               debug_message = TEXT( "ERROR_INVALID_HANDLE - One of the parameters specifies an invalid handle." );
               break;

            case ERROR_INVALID_PARAMETER:

               debug_message = TEXT( "ERROR_INVALID_PARAMETER - One of the parameters contains an invalid value. This is most often an illegal pointer." );
               break;

            case NTE_BAD_ALGID:

               debug_message = TEXT( "NTE_BAD_ALGID - The hKey session key specifies an algorithm that this CSP does not support." );
               break;

            case NTE_BAD_DATA:

               debug_message = TEXT( "NTE_BAD_DATA - The data to be decrypted is invalid. For example, when a block cipher is used and the Final flag FALSE, the value specified by pdwDataLen must be a multiple of the block size. This error can also be returned when the padding is found to be invalid." );
               break;

            case NTE_BAD_FLAGS:

               debug_message = TEXT( "NTE_BAD_FLAGS - The dwFlags parameter is nonzero." );
               break;

            case NTE_BAD_HASH:

               debug_message = TEXT( "NTE_BAD_HASH - The hHash parameter contains an invalid handle." );
               break;

            case NTE_BAD_KEY:

               debug_message = TEXT( "NTE_BAD_KEY - The hKey parameter does not contain a valid handle to a key." );
               break;

            case NTE_BAD_LEN:

               debug_message = TEXT( "NTE_BAD_LEN - The size of the output buffer is too small to hold the generated plaintext." );
               break;

            case NTE_BAD_UID:

               debug_message = TEXT( "NTE_BAD_UID - The CSP context that was specified when the key was created cannot be found." );
               break;

            case NTE_DOUBLE_ENCRYPT:

               debug_message = TEXT( "NTE_DOUBLE_ENCRYPT - The application attempted to decrypt the same data twice." );
               break;

            case NTE_FAIL:

               debug_message = TEXT( "NTE_FAIL - The function failed in some unexpected way." );
               break;

            default:

               debug_message.Format( TEXT( "Undocumented error %lu" ), m_ErrorCode );
               break;
         }

         WFCTRACE( debug_message );

#endif // _DEBUG

         // OK, it failed but this may not be an unrecoverable error

         if ( m_ErrorCode == NTE_BAD_LEN )
         {
            WFCTRACEVAL( TEXT( "This size wasn't enough " ), data_to_decrypt.GetSize() );
            WFCTRACEVAL( TEXT( "I had to expand to " ), data_length );

            // Ah! We need to expand our buffer to make room...

            decrypted_data.SetSize( data_length );

            WFCTRACE( TEXT( "Trying again" ) );

            return_value = ::CryptDecrypt( m_Key,
                                           hash_handle,
                                           this_is_the_last_chunk_of_data_to_be_decrypted,
                                           flags,
                                           decrypted_data.GetData(),
                                          &data_length );

            if ( return_value == FALSE )
            {
               m_ErrorCode = ::GetLastError();

               WFCTRACE( TEXT( "Second attempt failed." ) );
               WFCTRACEERROR( m_ErrorCode );

               return( FALSE );
            }
            else
            {
               // Now that we've decrypted the data, let's strip off any padding

               wfc_trim_decrypted_data( decrypted_data );
            }

            return( TRUE );
         }

         return( FALSE );
      }
      else
      {
         // Now that we've decrypted the data, let's strip off any padding

         wfc_trim_decrypted_data( decrypted_data );
      }
   }
   catch( ... )
   {
      // Something bad happened. Don't let any data out

      m_ErrorCode = ERROR_EXCEPTION_IN_SERVICE;
      decrypted_data.RemoveAll();
      return( FALSE );
   }

   return( TRUE );
}
 
BOOL CCryptographicKey::Destroy( void )
{
   WFCLTRACEINIT( TEXT( "CCryptographicKey::Destroy()" ) );

   BOOL return_value = FALSE;

   return_value = ::CryptDestroyKey( m_Key );

   if ( return_value == FALSE )
   {
      m_ErrorCode = ::GetLastError();
      WFCTRACEERROR( m_ErrorCode );
   }
   else
   {
      return_value = TRUE;
   }

   m_Key                  = NULL;
   m_AutomaticallyDestroy = FALSE;

   return( return_value );
}

BOOL CCryptographicKey::Encrypt( const CByteArray&          data_to_encrypt,
                                       CByteArray&          encrypted_data,
                                       BOOL                 this_is_the_last_chunk_of_data_to_be_encrypted,
                                       CCryptographicHash * hash_p,
                                       DWORD                flags )
{
   WFCLTRACEINIT( TEXT( "CCryptographicKey::Encrypt()" ) );

   BOOL return_value = FALSE;

   // This is really stupid. The CryptEncrypt function takes an in/out
   // for the buffer parameter. Besides not being const correct, it negates
   // the possibility of using memory mapped files. Normally, Microsoft
   // would notice something like this. This must be some pinhead's idea.

   HCRYPTHASH hash_handle = static_cast< HCRYPTHASH >( NULL );

   if ( hash_p == NULL )
   {
      WFCTRACE( TEXT( "Defaulting to no hash" ) );
      hash_handle = static_cast< HCRYPTHASH >( NULL );
   }

   // We were passed a pointer, don't trust it...

   try
   {
      // 
      if ( hash_p != NULL )
      {
         hash_handle = hash_p->GetHandle();
      }

      // We must correct for a design flaw in the CryptoAPI. What you
      // send to be encrypted is not what you get back from the
      // decrypt. Most of the time your data will be padded with
      // bytes to fill out a "block size". THIS IS STUPID! When we
      // read data from a file we do not get an entire cluster of
      // data back. Why should we put up with this from the CryptoAPI?

      // Copy the data to encrypt over to the output buffer...

      encrypted_data.Copy( data_to_encrypt );

      DWORD number_of_bytes_to_encrypt = encrypted_data.GetSize();

      // Now, to correct for the design flaw, add the number of bytes

      BYTE byte_1 = 0;
      BYTE byte_2 = 0;
      BYTE byte_3 = 0;
      BYTE byte_4 = 0;

      // Write the length

      byte_1 = (BYTE) (number_of_bytes_to_encrypt & 0xFF );
      number_of_bytes_to_encrypt >>= 8;

      byte_2 = (BYTE) (number_of_bytes_to_encrypt & 0xFF );
      number_of_bytes_to_encrypt >>= 8;

      byte_3 = (BYTE) (number_of_bytes_to_encrypt & 0xFF );
      number_of_bytes_to_encrypt >>= 8;

      byte_4 = (BYTE) (number_of_bytes_to_encrypt & 0xFF );

      // Make room for the length

      encrypted_data.InsertAt( 0, 0, 4 );

      encrypted_data.SetAt( 0, byte_1 );
      encrypted_data.SetAt( 1, byte_2 );
      encrypted_data.SetAt( 2, byte_3 );
      encrypted_data.SetAt( 3, byte_4 );

      number_of_bytes_to_encrypt = encrypted_data.GetSize();
      
      DWORD required_buffer_size = number_of_bytes_to_encrypt;

      return_value = ::CryptEncrypt( m_Key,
                                     hash_handle,
                                     this_is_the_last_chunk_of_data_to_be_encrypted,
                                     flags,
                                     encrypted_data.GetData(),
                                    &required_buffer_size,
                                     number_of_bytes_to_encrypt );

      if ( return_value == FALSE )
      {
         m_ErrorCode = ::GetLastError();

#if defined( _DEBUG )

         // Spit out a nice debugging message, these are all of the valid
         // error codes as documented in VC5

         CString debug_message;

         switch( m_ErrorCode )
         {
            case ERROR_INVALID_HANDLE:

               debug_message = TEXT( "ERROR_INVALID_HANDLE - One of the parameters specifies an invalid handle." );
               break;

            case ERROR_INVALID_PARAMETER:

               debug_message = TEXT( "ERROR_INVALID_PARAMETER - One of the parameters contains an invalid value. This is most often an illegal pointer." );
               break;

            case NTE_BAD_ALGID:

               debug_message = TEXT( "NTE_BAD_ALGID - The hKey session key specifies an algorithm that this CSP does not support." );
               break;

            case NTE_BAD_DATA:

               debug_message = TEXT( "NTE_BAD_DATA - The data to be encrypted is invalid. For example, when a block cipher is used and the Final flag is FALSE, the value specified by pdwDataLen must be a multiple of the block size." );
               break;

            case NTE_BAD_FLAGS:

               debug_message = TEXT( "NTE_BAD_FLAGS - The dwFlags parameter is nonzero." );
               break;

            case NTE_BAD_HASH:

               debug_message = TEXT( "NTE_BAD_HASH - The hHash parameter contains an invalid handle." );
               break;

            case NTE_BAD_KEY:

               debug_message = TEXT( "NTE_BAD_KEY - The hKey parameter does not contain a valid handle to a key." );
               break;

            case NTE_BAD_LEN:

               debug_message = TEXT( "NTE_BAD_LEN - The size of the output buffer is too small to hold the generated ciphertext." );
               break;

            case NTE_BAD_UID:

               debug_message = TEXT( "NTE_BAD_UID - The CSP context that was specified when the key was created cannot be found." );
               break;

            case NTE_DOUBLE_ENCRYPT:

               debug_message = TEXT( "NTE_DOUBLE_ENCRYPT - The application attempted to encrypt the same data twice." );
               break;

            case NTE_FAIL:

               debug_message = TEXT( "NTE_FAIL - The function failed in some unexpected way." );
               break;

            case NTE_NO_MEMORY:

               debug_message = TEXT( "NTE_NO_MEMORY - The CSP ran out of memory during the operation." );
               break;

            default:

               debug_message.Format( TEXT( "Undocumented error %lu" ), m_ErrorCode );
               break;
         }

         WFCTRACE( debug_message );

#endif // _DEBUG

         WFCTRACE( TEXT( "First attempt to encrypt failed." ) );

         // OK, it failed but this may not be an unrecoverable error

         // ERROR_MORE_DATA is an undocumented return code.

         if ( m_ErrorCode == ERROR_MORE_DATA )
         {
            WFCTRACEVAL( TEXT( "This size wasn't enough " ), number_of_bytes_to_encrypt );
            WFCTRACEVAL( TEXT( "I had to expand to " ), required_buffer_size );

            // Ah! We need to expand our buffer to make room...

            encrypted_data.SetSize( required_buffer_size );

            WFCTRACE( TEXT( "Trying again" ) );

            return_value = ::CryptEncrypt( m_Key,
                                           hash_handle,
                                           this_is_the_last_chunk_of_data_to_be_encrypted,
                                           flags,
                                           encrypted_data.GetData(),
                                          &number_of_bytes_to_encrypt,
                                           required_buffer_size );

            if ( return_value == FALSE )
            {
               m_ErrorCode = ::GetLastError();

               WFCTRACEVAL( TEXT( "Second attempt failed with " ), m_ErrorCode );
               WFCTRACEERROR( m_ErrorCode );

               return( FALSE );
            }

            return( TRUE );
         }

         return( FALSE );
      }
   }
   catch( ... )
   {
      // Something bad happened. Don't let any data out

      m_ErrorCode = ERROR_EXCEPTION_IN_SERVICE;
      encrypted_data.RemoveAll();
      return( FALSE );
   }

   return( TRUE );
}
 
BOOL CCryptographicKey::Export( CCryptographicKey& key_for_whoever_we_are_exporting_to,
                                CByteArray&        key_in_exported_form,
                                DWORD              format_of_exported_key,
                                DWORD              flags )
{
   WFCLTRACEINIT( TEXT( "CCryptographicKey::Export()" ) );

   BOOL return_value = FALSE;

   DWORD number_of_bytes_in_exported_key = 0;

   HCRYPTKEY their_key = key_for_whoever_we_are_exporting_to.m_Key;

   if ( format_of_exported_key == formatPublicKey )
   {
      // This parameter is unused for exporting your public key (which does not require protection)
      their_key = NULL;
   }

   // Figure out how big an exported key is

   return_value = ::CryptExportKey( m_Key,
                                    their_key,
                                    format_of_exported_key,
                                    flags,
                                    NULL,
                                   &number_of_bytes_in_exported_key );

   if ( return_value == FALSE )
   {
      m_ErrorCode = ::GetLastError();

      WFCTRACE( TEXT( "Can't determine length of exported key." ) );
      WFCTRACEERROR( m_ErrorCode );

      return( FALSE );
   }

   // Now that we know how big an exported key is, set our size...

   key_in_exported_form.SetSize( number_of_bytes_in_exported_key );

   return_value = ::CryptExportKey( m_Key,
                                    their_key,
                                    format_of_exported_key,
                                    flags,
                                    key_in_exported_form.GetData(),
                                   &number_of_bytes_in_exported_key );

   if ( return_value == FALSE )
   {
      m_ErrorCode = ::GetLastError();

#if defined( _DEBUG )

      // Spit out a nice debugging message, these are all of the valid
      // error codes as documented in VC5

      CString debug_message;

      switch( m_ErrorCode )
      {
         case ERROR_INVALID_HANDLE:

            debug_message = TEXT( "ERROR_INVALID_HANDLE - One of the parameters specifies an invalid handle." );
            break;

         case ERROR_INVALID_PARAMETER:

            debug_message = TEXT( "ERROR_INVALID_PARAMETER - One of the parameters contains an invalid value. This is most often an illegal pointer." );
            break;

         case NTE_BAD_FLAGS:

            debug_message = TEXT( "NTE_BAD_FLAGS - The dwFlags parameter is nonzero." );
            break;

         case NTE_BAD_KEY:

            debug_message = TEXT( "NTE_BAD_KEY - One or both of the keys specified by hKey and hExpKey are invalid." );
            break;

         case NTE_BAD_KEY_STATE:

            debug_message = TEXT( "NTE_BAD_KEY_STATE - You do not have permission to export the key. That is, when the hKey key was created, the CRYPT_EXPORTABLE flag was not specified" );
            break;

         case NTE_BAD_PUBLIC_KEY:

            debug_message = TEXT( "NTE_BAD_PUBLIC_KEY - The key blob type specified by dwBlobType is PUBLICKEYBLOB, but hExpKey does not contain a public key handle." );
            break;

         case NTE_BAD_TYPE:

            debug_message = TEXT( "NTE_BAD_TYPE - The dwBlobType parameter specifies an unknown blob type." );
            break;

         case NTE_BAD_UID:

            debug_message = TEXT( "NTE_BAD_UID - The CSP context that was specified when the hKey key was created cannot be found." );
            break;

         case NTE_NO_KEY:

            debug_message = TEXT( "NTE_NO_KEY - A session key is being exported and the hExpKey parameter does not specify a public key." );
            break;

         default:

            debug_message.Format( TEXT( "Undocumented error %lu" ), m_ErrorCode );
            break;
      }

      WFCTRACE( debug_message );

#endif // _DEBUG

      WFCTRACEVAL( TEXT( "Can't export key after determining the length is " ), number_of_bytes_in_exported_key );

      return( FALSE );
   }

   return( TRUE );
}

BOOL CCryptographicKey::FromHandle( HCRYPTKEY source_handle, BOOL automatically_destroy )
{
   WFCLTRACEINIT( TEXT( "CCryptographicKey::FromHandle()" ) );

   // See if we are already handling a key

   if ( m_Key != NULL )
   {
      if ( m_AutomaticallyDestroy != FALSE )
      {
         Destroy();
      }
   }

   m_Key                  = source_handle;
   m_AutomaticallyDestroy = automatically_destroy;

   return( TRUE );
}

HCRYPTKEY CCryptographicKey::GetHandle( void ) const
{
   return( m_Key );
}

BOOL CCryptographicKey::GetParameter( const DWORD parameter_to_get, BYTE *buffer, DWORD& buffer_length, const DWORD flags )
{
   WFCLTRACEINIT( TEXT( "CCryptographicKey::GetParameter()" ) );

   BOOL return_value = FALSE;

   return_value = ::CryptGetKeyParam( m_Key, parameter_to_get, buffer, &buffer_length, flags );

   if ( return_value == FALSE )
   {
      m_ErrorCode = ::GetLastError();

#if defined( _DEBUG )

      // Spit out a nice debugging message, these are all of the valid
      // error codes as documented in VC5

      CString debug_message;

      switch( m_ErrorCode )
      {
         case ERROR_INVALID_HANDLE:

            debug_message = TEXT( "ERROR_INVALID_HANDLE - One of the parameters specifies an invalid handle." );
            break;

         case ERROR_INVALID_PARAMETER:

            debug_message = TEXT( "ERROR_INVALID_PARAMETER - One of the parameters contains an invalid value. This is most often an illegal pointer." );
            break;

         case NTE_BAD_FLAGS:

            debug_message = TEXT( "NTE_BAD_FLAGS - The dwFlags parameter is nonzero." );
            break;

         case NTE_BAD_KEY:

            debug_message = TEXT( "NTE_BAD_KEY - The key specified by the hKey parameter is invalid." );
            break;

         case NTE_NO_KEY:

            debug_message = TEXT( "NTE_BAD_KEY - The key specified by the hKey parameter is invalid." );
            break;

         case NTE_BAD_TYPE:

            debug_message = TEXT( "NTE_BAD_TYPE - The dwParam parameter specifies an unknown parameter number." );
            break;

         case NTE_BAD_UID:

            debug_message = TEXT( "NTE_BAD_UID - The CSP context that was specified when the hKey key was created cannot be found." );
            break;

         default:

            debug_message.Format( TEXT( "Undocumented error %lu" ), m_ErrorCode );
            break;
      }

      WFCTRACE( debug_message );

#endif // _DEBUG
   }

   return( return_value );
}

BOOL CCryptographicKey::GetAlgorithmIdentifier( DWORD& identifier )
{
   WFCLTRACEINIT( TEXT( "CCryptographicKey::GetAlgorithmIdentifier()" ) );

   DWORD buffer_length = sizeof( identifier );

   return( GetParameter( parameterAlgorithmIdentifier, (BYTE *) &identifier, buffer_length ) );
}

BOOL CCryptographicKey::GetBlockLength( DWORD& block_length )
{
   WFCLTRACEINIT( TEXT( "CCryptographicKey::GetBlockLength()" ) );

   DWORD buffer_length = sizeof( block_length );

   return( GetParameter( parameterBlockLengthInBytes, (BYTE *) &block_length, buffer_length ) );
}

BOOL CCryptographicKey::GetCipherMode( DWORD& cipher_mode )
{
   WFCLTRACEINIT( TEXT( "CCryptographicKey::GetCipherMode()" ) );

   DWORD buffer_length = sizeof( cipher_mode );

   return( GetParameter( parameterCipherMode, (BYTE *) &cipher_mode, buffer_length ) );
}

BOOL CCryptographicKey::GetInitializationVector( CByteArray& initialization_vector )
{
   WFCLTRACEINIT( TEXT( "CCryptographicKey::GetInitializationVector()" ) );

   initialization_vector.SetSize( 65536 ); // A Massive initialization vector

   DWORD buffer_length = initialization_vector.GetSize();

   BOOL return_value = FALSE;

   return_value = GetParameter( parameterInitializationVector, initialization_vector.GetData(), buffer_length );

   if ( return_value != FALSE )
   {
      initialization_vector.SetSize( buffer_length );
   }

   return( return_value );
}

BOOL CCryptographicKey::GetNumberOfBitsProcessedPerCycle( DWORD& number_of_bits )
{
   WFCLTRACEINIT( TEXT( "CCryptographicKey::GetNumberOfBitsProcessedPerCycle()" ) );

   DWORD buffer_length = sizeof( number_of_bits );

   return( GetParameter( parameterNumberOfBitsProcessedPerCycle, (BYTE *) &number_of_bits, buffer_length ) );
}

BOOL CCryptographicKey::GetPaddingMode( DWORD& padding_mode )
{
   WFCLTRACEINIT( TEXT( "CCryptographicKey::GetPaddingMode()" ) );

   DWORD buffer_length = sizeof( padding_mode );

   return( GetParameter( parameterPaddingMode, (BYTE *) &padding_mode, buffer_length ) );
}

BOOL CCryptographicKey::GetPermissions( DWORD& permissions )
{
   WFCLTRACEINIT( TEXT( "CCryptographicKey::GetPermissions()" ) );

   DWORD buffer_length = sizeof( permissions );

   return( GetParameter( parameterPermissions, (BYTE *) &permissions, buffer_length ) );
}

BOOL CCryptographicKey::GetSalt( CByteArray& salt )
{
   WFCLTRACEINIT( TEXT( "CCryptographicKey::GetSalt()" ) );

   salt.SetSize( 65536 ); // A Massive grain of salt

   DWORD buffer_length = salt.GetSize();

   BOOL return_value = FALSE;

   return_value = GetParameter( parameterSalt, salt.GetData(), buffer_length );

   if ( return_value != FALSE )
   {
      salt.SetSize( buffer_length );
   }

   return( return_value );
}

BOOL CCryptographicKey::SetCipherMode( DWORD mode )
{
   WFCLTRACEINIT( TEXT( "CCryptographicKey::SetCipherMode()" ) );

   return( SetParameter( parameterCipherMode, (BYTE *) mode ) );
}

BOOL CCryptographicKey::SetInitializationVector( BYTE *buffer )
{
   WFCLTRACEINIT( TEXT( "CCryptographicKey::SetInitializationVector()" ) );

   return( SetParameter( parameterInitializationVector, buffer ) );
}

BOOL CCryptographicKey::SetNumberOfBitsProcessedPerCycle( DWORD number_of_bits )
{
   WFCLTRACEINIT( TEXT( "CCryptographicKey::SetNumberOfBitsProcessedPerCycle()" ) );

   return( SetParameter( parameterNumberOfBitsProcessedPerCycle, (BYTE *) number_of_bits ) );
}

BOOL CCryptographicKey::SetPaddingMode( DWORD mode )
{
   WFCLTRACEINIT( TEXT( "CCryptographicKey::SetPaddingMode()" ) );

   return( SetParameter( parameterPaddingMode, (BYTE *) mode ) );
}

BOOL CCryptographicKey::SetParameter( const DWORD parameter_to_set, BYTE *buffer, const DWORD flags )
{
   WFCLTRACEINIT( TEXT( "CCryptographicKey::SetParameter()" ) );

   BOOL return_value = FALSE;

   // The buffer parameter to CryptSetKeyParam is not const correct. It is
   // described in the documentation as an [in] parameter. This means the
   // CryptoAPI promises not to modify it. However, the parameter is not
   // typed as const. This means they screwed up the prototype.

   return_value = ::CryptSetKeyParam( m_Key, parameter_to_set, buffer, flags );

   if ( return_value == FALSE )
   {
      m_ErrorCode = ::GetLastError();

#if defined( _DEBUG )

      // Spit out a nice debugging message, these are all of the valid
      // error codes as documented in VC5

      CString debug_message;

      switch( m_ErrorCode )
      {
         case ERROR_INVALID_HANDLE:

            debug_message = TEXT( "ERROR_INVALID_HANDLE - One of the parameters specifies an invalid handle." );
            break;

         case ERROR_BUSY:

            debug_message = TEXT( "ERROR_BUSY - The CSP context is currently being used by another process (i.e. you've got a crappy crypto provider)." );
            break;

         case ERROR_INVALID_PARAMETER:

            debug_message = TEXT( "ERROR_INVALID_PARAMETER - One of the parameters contains an invalid value. This is most often an illegal pointer." );
            break;

         case NTE_BAD_FLAGS:

            debug_message = TEXT( "NTE_BAD_FLAGS - The dwFlags parameter is nonzero or the pbData buffer contains an invalid value." );
            break;

         case NTE_BAD_TYPE:

            debug_message = TEXT( "NTE_BAD_TYPE - The dwParam parameter specifies an unknown parameter number." );
            break;

         case NTE_BAD_UID:

            debug_message = TEXT( "NTE_BAD_UID - The CSP context that was specified when the hKey key was created cannot be found." );
            break;

         case NTE_FAIL:

            debug_message = TEXT( "NTE_FAIL - The function failed in some unexpected way." );
            break;

         default:

            debug_message.Format( TEXT( "Undocumented error %lu" ), m_ErrorCode );
            break;
      }

      WFCTRACE( debug_message );

#endif // _DEBUG
   }
   else
   {
      return_value = TRUE;
   }

   return( return_value );
}

BOOL CCryptographicKey::SetPermissions( DWORD permissions )
{
   WFCLTRACEINIT( TEXT( "CCryptographicKey::SetPermissions()" ) );

   return( SetParameter( parameterPermissions, (BYTE *) permissions ) );
}

BOOL CCryptographicKey::SetSalt( BYTE *buffer )
{
   WFCLTRACEINIT( TEXT( "CCryptographicKey::SetSalt()" ) );

   return( SetParameter( parameterSalt, buffer ) );
}

#endif // _MSC_VER

// End of source

#if 0
<HTML>

<HEAD>
<TITLE>WFC - CCryptographicKey</TITLE>
<META name="keywords" content="WFC, MFC extension library, freeware class library, Win32, source code">
<META name="description" content="The C++ class that handles CryptoAPI keys.">
</HEAD>

<BODY>

<H1>CCryptographicKey : <A HREF="CCryptography.htm">CCryptography</A></H1>
$Revision: 30 $<BR><HR>

<H2>Description</H2>

This class encapsulates cryptographic keys.

<H2>Constructors</H2>

<DL COMPACT>

<DT><PRE><B>CCryptographicKey</B>()
<B>CCryptographicKey</B>( HCRYPTKEY source_handle, BOOL automatically_destroy = TRUE )</PRE><DD>
Constructs a new object or allows you to treat an existing HCRYPTKEY as an object.

</DL>

<H2>Data Members</H2>None.

<H2>Methods</H2>

<DL COMPACT>

<DT><PRE>BOOL <B>Decrypt</B>( const CByteArray&amp;          data_to_decrypt,
                    CByteArray&amp;          decrypted_data, 
                    BOOL                 this_is_the_last_chunk_of_data_to_be_decrypted = TRUE,
                    <A HREF="CCryptographicHash.htm">CCryptographicHash</A> * hash_p = NULL,
                    DWORD                flags = 0 )</PRE><DD>
This method decrypts data.

<DT><PRE>BOOL <B>Destroy</B>( void )</PRE><DD>
Destroys the key.

<DT><PRE>BOOL <B>Encrypt</B>( const CByteArray&amp;          data_to_encrypt,
                    CByteArray&amp;          encrypted_data,
                    BOOL                 this_is_the_last_chunk_to_be_encrypted = TRUE,
                    <A HREF="CCryptographicHash.htm">CCryptographicHash</A> * hash_p = NULL,
                    DWORD                flags  = 0 )</PRE><DD>
This method encrypts data.

<DT><PRE>BOOL <B>Export</B>( CCryptographicKey&amp; key_for_whoever_we_are_exporting_to,
                    CByteArray&amp; key_in_exported_form,
                    DWORD       export_format = formatSimple,
                    DWORD       flags         = 0 )</PRE><DD>
Exports the key so you can send it to others.

<DT><PRE>BOOL <B>FromHandle</B>( HCRYPTKEY source_handle, BOOL automatically_destroy = TRUE )</PRE><DD>
Tells the class to start playing with the HCRYPTKEY provided. If
<CODE>automatically_destroy</CODE> is set to TRUE, <B>Destroy</B>() will be
called by the destructor.

<DT><PRE>BOOL <B>GetAlgorithmIdentifier</B>( DWORD&amp; identifier )</PRE><DD>
Retrieves the identifier for the algorithm. It basically calls <B>GetParameter</B>()
with <CODE>parameterAlgorithmIdentifier</CODE>.

<DT><PRE>BOOL <B>GetBlockLength</B>( DWORD&amp; block_length )</PRE><DD>
Retrieves the block length. It basically calls <B>GetParameter</B>()
with <CODE>parameterBlockLengthInBytes</CODE>.

<DT><PRE>BOOL <B>GetCipherMode</B>( DWORD&amp; cipher_mode )</PRE><DD>
Retrieves the cipher mode. It basically calls <B>GetParameter</B>()
with <CODE>parameterCipherMode</CODE>.
The <CODE>cipher_mode</CODE> will be set to one of the following:
<UL>
<LI>modeCipherBlockChaining
<LI>modeCipherFeedback
<LI>modeElectronicCodebook
<LI>modeOutputFeedback
</UL>

<DT><PRE>HCRYPTKEY <B>GetHandle</B>( void ) const</PRE><DD>
Returns the underlying HCRYPTKEY so you can call the API directly.

<DT><PRE>BOOL <B>GetInitializationVector</B>( CByteArray&amp; initialization_vector )</PRE><DD>
Retrieves the initialization vector. It calls <B>GetParameter</B>() with
<CODE>parameterInitializationVector</CODE>.

<DT><PRE>BOOL <B>GetNumberOfBitsProcessedPerCycle</B>( DWORD&amp; number_of_bits )</PRE><DD>
Retrieves the
number of bits processed per cycle if the cipher mode is modeCipherFeedback or
modeOutputFeedback.

<DT><PRE>BOOL <B>GetPaddingMode</B>( DWORD&amp; padding_mode )</PRE><DD>
Retrieves the padding mode. Currently the only padding mode is PKCS5_PADDING.

<DT><PRE>BOOL <B>GetParameter</B>( const DWORD parameter_to_get, BYTE *buffer, DWORD&amp; buffer_length, const DWORD flags = 0 )</PRE><DD>
Retrieves one of the following bits of information (i.e. 
<CODE>parameter_to_get</CODE> can be one of):
<UL>
<LI>parameterAlgorithmIdentifier
<LI>parameterBlockLengthInBytes
<LI>parameterCipherMode
<LI>parameterInitializationVector
<LI>parameterNumberOfBitsProcessedPerCycle
<LI>parameterPaddingMode
<LI>parameterPermissions
<LI>parameterSalt
</UL>

<DT><PRE>BOOL <B>GetPermissions</B>( DWORD&amp; permissions )</PRE><DD>
Retrieves the permissions.

<DT><PRE>BOOL <B>GetSalt</B>( CByteArray&amp; salt )</PRE><DD>
Retrieves the Salt.

<DT><PRE>BOOL <B>SetCipherMode</B>( DWORD mode )</PRE><DD>
Sets the cipher mode to be used. The <CODE>mode</CODE> parameter can
be one of the following:
<UL>
<LI>modeCipherBlockChaining
<LI>modeCipherFeedback
<LI>modeElectronicCodebook
<LI>modeOutputFeedback
</UL>

<DT><PRE>BOOL <B>SetInitializationVector</B>( BYTE * buffer )</PRE><DD>
Sets the initialization vector.

<DT><PRE>BOOL <B>SetNumberOfBitsProcessedPerCycle</B>( DWORD number_of_bits )</PRE><DD>
Sets the number of bits
processed per cycle. This is valid only if the cipher mode is modeCipherFeedback
or modeOutputFeedback.

<DT><PRE>BOOL <B>SetPaddingMode</B>( DWORD mode )</PRE><DD>
Sets the padding mode to be used by the cipher.

<DT><PRE>BOOL <B>SetParameter</B>( const DWORD parameter_to_set, BYTE * buffer, const DWORD flags = 0 )</PRE><DD>
Sets a parameter of the key. You can set one of these parameters
(i.e. <CODE>parameter_to_set</CODE> can be one of these values):
<UL>
<LI>parameterCipherMode
<LI>parameterInitializationVector
<LI>parameterNumberOfBitsProcessedPerCycle
<LI>parameterPaddingMode
<LI>parameterPermissions
<LI>parameterSalt
</UL>

<DT><PRE>BOOL <B>SetPermissions</B>( DWORD permissions )</PRE><DD>
Sets permissions on the key. The <CODE>permissions</CODE> can be:
<UL>
<LI>permissionDecrypt
<LI>permissionEncrypt
<LI>permissionExport
<LI>permissionMAC
<LI>permissionRead
<LI>permissionWrite
</UL>

<DT><PRE>BOOL <B>SetSalt</B>( BYTE * buffer )</PRE><DD>
Sets the salt value.

</DL>

<H2>Example</H2><PRE><CODE>Sorry.</CODE></PRE>

<H2>API's Used</H2>
<UL>
<LI>CryptDecrypt
<LI>CryptDestroyKey
<LI>CryptEncrypt
<LI>CryptExportKey
<LI>CryptGetKeyParam
<LI>CryptSetKeyParam
</UL>

<HR><I>Copyright, 2000, <A HREF="mailto:wfc@pobox.com">Samuel R. Blackburn</A></I><BR>
$Workfile: CCryptographicKey.cpp $<BR>
$Modtime: 1/04/00 5:09a $
</BODY>

</HTML>
#endif
