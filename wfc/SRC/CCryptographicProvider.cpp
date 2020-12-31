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
** $Workfile: CCryptographicProvider.cpp $
** $Revision: 31 $
** $Modtime: 1/04/00 5:09a $
** $Reuse Tracing Code: 1 $
*/

#if _MSC_VER < 1020
#pragma message( "Need Visual C++ 4.2 or later to compile CCryptographicProvider" )
#else // _MSC_VER

#if defined( _DEBUG ) && ! defined( WFC_STL )
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif // _DEBUG

// Construction

CCryptographicProvider::CCryptographicProvider()
{
   WFCLTRACEINIT( TEXT( "CCryptographicProvider::CCryptographicProvider()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   m_Initialize();
}

CCryptographicProvider::~CCryptographicProvider()
{
   WFCLTRACEINIT( TEXT( "CCryptographicProvider::~CCryptographicProvider()" ) );
   WFCTRACEVAL( TEXT( "pointer is " ), (VOID *) this );
   Close();
   m_Initialize();
}

// Methods

void CCryptographicProvider::Close( void )
{
   WFCLTRACEINIT( TEXT( "CCryptographicProvider::Close()" ) );

   if ( m_CryptographicProvider != NULL )
   {
      ::CryptReleaseContext( m_CryptographicProvider, 0 );
   }

   m_CryptographicProvider = NULL;
}

BOOL CCryptographicProvider::CreateHash( const CCryptographicAlgorithm& algorithm_that_is_going_to_use_the_hash,
                                         const CCryptographicKey&       key_for_hash_algorithms_that_need_it,
                                               CCryptographicHash&      hash,
                                               DWORD                    creation_flags )
{
   WFCLTRACEINIT( TEXT( "CCryptographicProvider::CreateHash()" ) );

   BOOL return_value = FALSE;

   HCRYPTHASH hash_handle = NULL;

   return_value = ::CryptCreateHash( m_CryptographicProvider,
                                     algorithm_that_is_going_to_use_the_hash.Identifier,
                                     key_for_hash_algorithms_that_need_it.GetHandle(),
                                     creation_flags,
                                    &hash_handle );

   if ( return_value != FALSE )
   {
      hash.FromHandle( hash_handle );
   }
   else
   {
      WFCTRACE( TEXT( "CryptCreateHash() FAILED" ) );
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

         case ERROR_NOT_ENOUGH_MEMORY:

            debug_message = TEXT( "ERROR_NOT_ENOUGH_MEMORY - The operating system ran out of memory during the operation." );
            break;

         case NTE_BAD_ALGID:

            debug_message = TEXT( "NTE_BAD_ALGID - The Algid parameter specifies an algorithm that this CSP does not support." );
            break;

         case NTE_BAD_FLAGS:

            debug_message = TEXT( "NTE_BAD_FLAGS - The dwFlags parameter is nonzero." );
            break;

         case NTE_BAD_KEY:

            debug_message = TEXT( "NTE_BAD_KEY - A keyed hash algorithm (such as CALG_MAC) is specified by Algid and the hKey parameter is either zero or it specifies an invalid key handle. This error code will also be returned if the key is to a stream cipher, or if the cipher mode is anything other than CBC." );
            break;

         case NTE_NO_MEMORY:

            debug_message = TEXT( "NTE_NO_MEMORY - The CSP ran out of memory during the operation." );
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

   return( return_value );
}

BOOL CCryptographicProvider::CreateKey( const CCryptographicAlgorithm& algorithm_that_is_going_to_use_the_key,
                                              CCryptographicKey&       key,
                                              DWORD                    creation_flags,
                                              WORD                     number_of_bits_in_key )
{
   WFCLTRACEINIT( TEXT( "CCryptographicProvider::CreateKey()" ) );

   BOOL return_value = FALSE;

   HCRYPTKEY key_handle = NULL;

   // According to Jeff Spelman (jeffspel@microsoft.com), you
   // can put your request for the number of bits in the key
   // in the high word of the creation flags

   if ( number_of_bits_in_key != 0 )
   {
      WFCTRACE( TEXT( "Specifying the number of bits in the key" ) );

      WORD low_word  = 0;
      WORD high_word = 0;

      low_word  = LOWORD( creation_flags );
      high_word = HIWORD( creation_flags );

      if ( high_word != 0 )
      {
         WFCTRACE( TEXT( "WARNING! something was already set in the high word of creation flags, I might be breaking your code!!!" ) );
      }

      high_word = number_of_bits_in_key;

      creation_flags = MAKELONG( low_word, high_word );
   }

   return_value = ::CryptGenKey( m_CryptographicProvider,
                                 algorithm_that_is_going_to_use_the_key.Identifier,
                                 creation_flags,
                                &key_handle );

   if ( return_value != FALSE )
   {
      key.FromHandle( key_handle );
   }
   else
   {
      WFCTRACE( TEXT( "CryptGenKey() FAILED" ) );
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

            debug_message = TEXT( "NTE_BAD_ALGID - The Algid parameter specifies an algorithm that this CSP does not support." );
            break;

         case NTE_BAD_FLAGS:

            debug_message = TEXT( "NTE_BAD_FLAGS - The dwFlags parameter is nonzero." );
            break;

         case NTE_BAD_UID:

            debug_message = TEXT( "NTE_BAD_UID - The hProv parameter does not contain a valid context handle." );
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

   return( return_value );
}

BOOL CCryptographicProvider::CreateKeySet( LPCTSTR container_name, LPCTSTR provider_name, DWORD provider_type )
{
   WFCLTRACEINIT( TEXT( "CCryptographicProvider::CreateKeySet()" ) );

   // We were passed pointers, don't trust them

   HCRYPTPROV temp_handle = NULL;

   try
   {
      if ( ::CryptAcquireContext( &temp_handle,
                                   container_name,
                                   provider_name,
                                   provider_type,
                                   CRYPT_NEWKEYSET ) == FALSE )
      {
         m_ErrorCode = ::GetLastError();
         WFCTRACEVAL( TEXT( "CryptAcquireContext( CRYPT_NEWKEYSET ) failed with " ), m_ErrorCode );
         WFCTRACEERROR( m_ErrorCode );
         return( FALSE );
      }

      WFCTRACE( TEXT( "CRYPT_NEWKEYSET succeeded!" ) );

      ::CryptReleaseContext( temp_handle, 0 );

      return( TRUE );
   }
   catch( ... )
   {
      m_ErrorCode = ERROR_EXCEPTION_IN_SERVICE;
      return( FALSE );
   }
}

BOOL CCryptographicProvider::DeriveKey(  const CCryptographicAlgorithm& algorithm, 
                                         const CCryptographicHash&      hash,
                                               CCryptographicKey&       key,
                                               DWORD                    flags )
{
   WFCLTRACEINIT( TEXT( "CCryptographicProvider::DeriveKey()" ) );

   BOOL return_value = FALSE;

   HCRYPTKEY key_handle = NULL;

   return_value = ::CryptDeriveKey( m_CryptographicProvider,
                                    algorithm.Identifier,
                                    hash.GetHandle(),
                                    flags,
                                    &key_handle );

   if ( return_value == FALSE )
   {
      m_ErrorCode = ::GetLastError();
      WFCTRACEVAL( TEXT( "CryptDeriveKey failed with " ), m_ErrorCode );

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

            debug_message = TEXT( "NTE_BAD_ALGID - The Algid parameter specifies an algorithm that this CSP does not support." );
            break;

         case NTE_BAD_FLAGS:

            debug_message = TEXT( "NTE_BAD_FLAGS - The dwFlags parameter is nonzero." );
            break;

         case NTE_BAD_HASH:

            debug_message = TEXT( "NTE_BAD_HASH - The hBaseData parameter does not contain a valid handle to a hash object." );
            break;

         case NTE_BAD_UID:

            debug_message = TEXT( "NTE_BAD_UID - The hProv parameter does not contain a valid context handle." );
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

      return( FALSE );
   }
   else
   {
      key.FromHandle( key_handle );
   }

   return( TRUE );
}

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

void CCryptographicProvider::Dump( CDumpContext& dump_context ) const
{
   dump_context << TEXT( " a CCryptographicProvider at "  ) << (VOID *) this           << TEXT( "\n{\n" );
   dump_context << TEXT( "   m_CryptographicProvider is " ) << m_CryptographicProvider << TEXT( "\n"    );
   dump_context << TEXT( "   m_ErrorCode is "             ) << m_ErrorCode             << TEXT( "\n"    );
   dump_context << TEXT( "}\n" );
}

#endif // _DEBUG

// One of these days I'll write an EnumerateProviders() method.
// It will search HKEY_LOCAL_MACHINE\Software\Microsoft\Cryptography\Defaults
// for the different providers. Right now I only have the Microsoft
// CSP so I don't know exactly what multiple providers would look like
// in the registry.

void CCryptographicProvider::EnumerateAlgorithms( DWORD& enumerator )
{
   WFCLTRACEINIT( TEXT( "CCryptographicProvider::EnumerateAlgorithms()" ) );
   enumerator = CRYPT_FIRST;
}

BOOL CCryptographicProvider::GenerateRandomBytes( CByteArray& array, DWORD number_of_bytes_to_get )
{
   WFCLTRACEINIT( TEXT( "CCryptographicProvider::GenerateRandomBytes()" ) );

   if ( number_of_bytes_to_get == 0 )
   {
      // Overwrite all the bytes in the array with random ones

      number_of_bytes_to_get = array.GetSize();
   }
   else
   {
      array.SetSize( number_of_bytes_to_get );
   }

   BOOL return_value = FALSE;

   return_value = ::CryptGenRandom( m_CryptographicProvider, number_of_bytes_to_get, array.GetData() );

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

      return( FALSE );
   }

   return( TRUE );
}

HCRYPTPROV CCryptographicProvider::GetHandle( void ) const
{
   return( m_CryptographicProvider );
}

BOOL CCryptographicProvider::GetNext( DWORD& flags, CCryptographicAlgorithm& algorithm )
{
   WFCLTRACEINIT( TEXT( "CCryptographicProvider::GetNext()" ) );

   algorithm.Empty();

   if ( m_CryptographicProvider == NULL )
   {
      m_ErrorCode = ERROR_INVALID_HANDLE;
      return( FALSE );
   }

   CByteArray buffer;

   if ( GetParameter( parameterEnumerateAlgorithms, buffer, flags ) != FALSE )
   {
      algorithm.Copy( reinterpret_cast<PROV_ENUMALGS *>( buffer.GetData() ) );

      if ( flags == CRYPT_FIRST )
      {
         flags = CRYPT_NEXT;
      }

      return( TRUE );
   }

   return( FALSE );
}

BOOL CCryptographicProvider::GetParameter( const DWORD parameter_to_get, CByteArray& buffer, const DWORD flags )
{
   WFCLTRACEINIT( TEXT( "CCryptographicProvider::GetParameter()" ) );

   buffer.SetSize( 4096 );

   DWORD size_of_buffer = buffer.GetSize();

   if ( ::CryptGetProvParam( m_CryptographicProvider, parameter_to_get, buffer.GetData(), &size_of_buffer, flags ) == FALSE )
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

         case ERROR_NO_MORE_ITEMS:

            debug_message = TEXT( "ERROR_NO_MORE_ITEMS - The end of the enumeration list has been reached. No valid data has been placed in the pbData buffer. This error is only returned when dwParam equals PP_ENUMALGS or PP_ENUMCONTAINERS." );
            break;

         case NTE_BAD_FLAGS:

            debug_message = TEXT( "NTE_BAD_FLAGS - The dwFlags parameter is nonzero." );
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

      return( FALSE );
   }

   buffer.SetSize( size_of_buffer );

   return( TRUE );
}

BOOL CCryptographicProvider::GetUserKey( DWORD which_user_key_to_get, CCryptographicKey& key )
{
   WFCLTRACEINIT( TEXT( "CCryptographicProvider::GetUserKey()" ) );

   BOOL return_value = FALSE;

   HCRYPTKEY key_handle = NULL;

   return_value = ::CryptGetUserKey( m_CryptographicProvider,
                                     which_user_key_to_get,
                                    &key_handle );

   if ( return_value != FALSE )
   {
      key.FromHandle( key_handle );
   }
   else
   {
      WFCTRACE( TEXT( "CryptGetUserKey() FAILED" ) );
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

         case NTE_BAD_KEY:

            debug_message = TEXT( "NTE_BAD_KEY - The dwKeySpec parameter contains an invalid value." );
            break;

         case NTE_BAD_UID:

            debug_message = TEXT( "NTE_BAD_UID - The CSP context that was specified when the hKey key was created cannot be found." );
            break;

         case NTE_NO_KEY:

            debug_message = TEXT( "NTE_NO_KEY - The key requested by the dwKeySpec parameter does not exist." );
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

   return( return_value );
}

BOOL CCryptographicProvider::ImportKey( CByteArray& exported_key_data, CCryptographicKey& key, DWORD format, DWORD flags )
{
   WFCLTRACEINIT( TEXT( "CCryptographicProvider::ImportKey()" ) );

   // Start from a known state

   key.Destroy();

   BOOL return_value = FALSE;

   HCRYPTKEY key_handle = 0;

   // CryptImportKey is mis-typed. It isn't const correct.

   return_value = ::CryptImportKey( m_CryptographicProvider,
                                    exported_key_data.GetData(),
                                    exported_key_data.GetSize(),
                        (HCRYPTKEY) format,
                                    flags,
                                   &key_handle );

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

            debug_message = TEXT( "NTE_BAD_ALGID - The simple key blob you are trying to import is not encrypted with the expected key exchange algorithm." );
            break;

         case NTE_BAD_DATA:

            debug_message = TEXT( "NTE_BAD_DATA - The algorithm that works with the public key you are trying to import is not supported by this CSP." );
            break;

         case NTE_BAD_FLAGS:

            debug_message = TEXT( "NTE_BAD_FLAGS - The dwFlags parameter is nonzero." );
            break;

         case NTE_BAD_TYPE:

            debug_message = TEXT( "NTE_BAD_TYPE - The key blob type is not supported by this CSP and is possibly invalid." );
            break;

         case NTE_BAD_UID:

            debug_message = TEXT( "NTE_BAD_UID - The CSP context that was specified when the hKey key was created cannot be found." );
            break;

         case NTE_BAD_VER:

            debug_message = TEXT( "NTE_BAD_VER - The key blob’s version number does not match the CSP version. This usually indicates that the CSP needs to be upgraded." );
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

      return( FALSE );
   }

   key.FromHandle( key_handle );

   return( TRUE );
}

void CCryptographicProvider::m_Initialize( void )
{
   WFCLTRACEINIT( TEXT( "CCryptographicProvider::m_Initialize()" ) );
   m_ErrorCode             = 0;
   m_CryptographicProvider = NULL;
}

BOOL CCryptographicProvider::Open( LPCTSTR container_name, LPCTSTR provider_name, DWORD provider_type, DWORD flags )
{
   WFCLTRACEINIT( TEXT( "CCryptographicProvider::Open()" ) );

   // Since we were passed pointers, we must expect them to be invalid

   try
   {
      if ( m_CryptographicProvider != NULL )
      {
         Close();
      }

      if ( ::CryptAcquireContext( &m_CryptographicProvider,
                                   container_name,
                                   provider_name,
                                   provider_type,
                                   flags ) == FALSE )
      {
         m_ErrorCode = ::GetLastError();

#if defined( _DEBUG )

         // Spit out a nice debugging message, these are all of the valid
         // error codes as documented in VC5

         CString debug_message;

         switch( m_ErrorCode )
         {
            case ERROR_INVALID_PARAMETER:

               debug_message = TEXT( "ERROR_INVALID_PARAMETER - One of the parameters contains an invalid value. This is most often an illegal pointer." );
               break;

            case ERROR_NOT_ENOUGH_MEMORY:

               debug_message = TEXT( "ERROR_NOT_ENOUGH_MEMORY - The operating system ran out of memory during the operation." );
               break;

            case NTE_BAD_FLAGS:

               debug_message = TEXT( "NTE_BAD_FLAGS - The dwFlags parameter has an illegal value." );
               break;

            case NTE_BAD_KEYSET:

               debug_message = TEXT( "NTE_BAD_KEYSET - The Registry entry for the key container could not be opened and may not exist." );
               break;

            case NTE_BAD_KEYSET_PARAM:

               debug_message = TEXT( "NTE_BAD_KEYSET_PARAM - The pszContainer or pszProvider parameter is set to an illegal value." );
               break;

            case NTE_BAD_PROV_TYPE:

               debug_message = TEXT( "NTE_BAD_PROV_TYPE - The value of the dwProvType parameter is out of range. All provider types must be from 1 to 999, inclusive." );
               break;

            case NTE_BAD_SIGNATURE:

               debug_message = TEXT( "NTE_BAD_SIGNATURE - The provider DLL signature did not verify correctly. Either the DLL or the digital signature has been tampered with." );
               break;

            case NTE_EXISTS:

               debug_message = TEXT( "NTE_EXISTS - The dwFlags parameter is CRYPT_NEWKEYSET, but the key container already exists." );
               break;

            case NTE_KEYSET_ENTRY_BAD:

               debug_message = TEXT( "NTE_KEYSET_ENTRY_BAD - The Registry entry for the pszContainer key container was found (in the HKEY_CURRENT_USER window), but is corrupt. See the section System Administration for details about CryptoAPI’s Registry usage." );
               break;

            case NTE_KEYSET_NOT_DEF:

               debug_message = TEXT( "NTE_KEYSET_NOT_DEF - No Registry entry exists in the HKEY_CURRENT_USER window for the key container specified by pszContainer." );
               break;

            case NTE_NO_MEMORY:

               debug_message = TEXT( "NTE_NO_MEMORY - The CSP ran out of memory during the operation." );
               break;

            case NTE_PROV_DLL_NOT_FOUND:

               debug_message = TEXT( "NTE_PROV_DLL_NOT_FOUND - The provider DLL file does not exist or is not on the current path." );
               break;

            case NTE_PROV_TYPE_ENTRY_BAD:

               debug_message = TEXT( "NTE_PROV_TYPE_ENTRY_BAD - The Registry entry for the provider type specified by dwProvType is corrupt. This error may relate to either the user default CSP list or the machine default CSP list. See the section System Administration for details about CryptoAPI’s Registry usage." );
               break;

            case NTE_PROV_TYPE_NO_MATCH:

               debug_message = TEXT( "NTE_PROV_TYPE_NO_MATCH - The provider type specified by dwProvType does not match the provider type found in the Registry. Note that this error can only occur when pszProvider specifies an actual CSP name." );
               break;

            case NTE_PROV_TYPE_NOT_DEF:

               debug_message = TEXT( "NTE_PROV_TYPE_NOT_DEF - No Registry entry exists for the provider type specified by dwProvType." );
               break;

            case NTE_PROVIDER_DLL_FAIL:

               debug_message = TEXT( "NTE_PROVIDER_DLL_FAIL - The provider DLL file could not be loaded, and may not exist. If it exists, then the file is not a valid DLL." );
               break;

            case NTE_SIGNATURE_FILE_BAD:

               debug_message = TEXT( "An error occurred while loading the DLL file image, prior to verifying its signature." );
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

         if ( m_ErrorCode == NTE_BAD_KEYSET )
         {
            WFCTRACE( TEXT( "A key set has not been created for this user, automatically creating one now" ) );

            // Now that a keyset has been created, try the open again

            if ( ::CryptAcquireContext( &m_CryptographicProvider,
                                         container_name,
                                         provider_name,
                                         provider_type,
                                         CRYPT_NEWKEYSET ) == FALSE )
            {
               m_ErrorCode = ::GetLastError();
               WFCTRACE( TEXT( "Welp, CRYPT_NEWKEYSET failed too..." ) );
               WFCTRACEERROR( m_ErrorCode );
               // Give up...
               m_CryptographicProvider = NULL;
               return( FALSE );
            }

            // Now that a key set has been created, try again

            WFCTRACE( TEXT( "Key set created, now retrying the open." ) );

            if ( ::CryptAcquireContext( &m_CryptographicProvider,
                                         container_name,
                                         provider_name,
                                         provider_type,
                                         flags ) == FALSE )
            {
               m_ErrorCode = ::GetLastError();

               WFCLTRACEINIT( TEXT( "I hates dragon rabbits!" ) );
               WFCTRACEERROR( m_ErrorCode );

               m_CryptographicProvider = NULL;
               return( FALSE );
            }

            return( TRUE );
         }

         m_CryptographicProvider = NULL;
         return( FALSE );
      }

      return( TRUE );
   }
   catch( ... )
   {
      m_CryptographicProvider = NULL;
      return( FALSE );
   }
}

BOOL CCryptographicProvider::SetDefault( const CString& name, DWORD type )
{
   WFCLTRACEINIT( TEXT( "CCryptographicProvider::SetDefault()" ) );

   BOOL return_value = FALSE;

   return_value = ::CryptSetProvider( name, type );

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

         case ERROR_NOT_ENOUGH_MEMORY:

            debug_message = TEXT( "ERROR_NOT_ENOUGH_MEMORY - The operating system ran out of memory during the operation." );
            break;

         default:

            debug_message.Format( TEXT( "Undocumented error %lu" ), m_ErrorCode );
            break;
      }

      WFCTRACE( debug_message );

#endif // _DEBUG

      return( FALSE );
   }

   return( TRUE );
}

#endif // _MSC_VER

// End of source

#if 0
<HTML>

<HEAD>
<TITLE>WFC - CCryptographicProvider</TITLE>
<META name="keywords" content="WFC, MFC extension library, freeware class library, Win32, source code">
<META name="description" content="The C++ class that handles CryptoAPI providers.">
</HEAD>

<BODY>

<H1>CCryptographicProvider : <A HREF="CCryptography.htm">CCryptography</A></H1>
$Revision: 31 $<BR><HR>

<H2>Description</H2>

This class handles most of the Crypto API functionality.

<H2>Data Members</H2>None.

<H2>Methods</H2>

<DL COMPACT>

<DT><PRE>void <B>Close</B>( void )</PRE><DD>
Closes the session.

<DT><PRE>BOOL <B>CreateHash</B>( const <A HREF="CCryptographicAlgorithm.htm">CCryptographicAlgorithm</A>&amp; which_algorithm_you_want_the_key_for, 
                 const <A HREF="CCryptographicKey.htm">CCryptographicKey</A>&amp;       key_for_algorithms_that_need_it,
                       <A HREF="CCryptographicHash.htm">CCryptographicHash</A>&amp;      destination_hash,
                       DWORD                    flags = 0 )</PRE><DD>
Creates a hasher for use with a specified algorithm.

<DT><PRE>BOOL <B>CreateKey</B>(  const <A HREF="CCryptographicAlgorithm.htm">CCryptographicAlgorithm</A>&amp; which_algorithm_you_want_the_key_for, 
                       <A HREF="CCryptographicKey.htm">CCryptographicKey</A>&amp;       destination_key,
                       DWORD                    flags = CRYPT_EXPORTABLE,
                       WORD                     number_of_bits_in_key = 0 )</PRE><DD>
Creates an encryption key for use with a specified algorithm.

<DT><PRE>BOOL <B>CreateKeySet</B>( LPCTSTR container_name = NULL, 
                   LPCTSTR provider_name  = NULL, 
                   DWORD   provider_type  = RsaFull )</PRE><DD>
Creates a key set (needed to <B>Open</B> the crypto).

<DT><PRE>BOOL <B>DeriveKey</B>( const <A HREF="CCryptographicAlgorithm.htm">CCryptographicAlgorithm</A>&amp; algorithm, 
                const <A HREF="CCryptographicHash.htm">CCryptographicHash</A>&amp;      hash,
                      <A HREF="CCryptographicKey.htm">CCryptographicKey</A>&amp;       key,
                      DWORD                    flags = keyflagExportable )</PRE><DD>
This function is the same as <B>CreateKey</B>(),
except that the generated session keys are derived from base data instead 
of being random. Another difference is that the <B>DeriveKey</B>() 
method cannot be used to generate public/private key pairs.

<DT><PRE>void <B>Dump</B>( CDumpContext&amp; dump_context ) const</PRE><DD>
Present only in the Debug builds.

<DT><PRE>void <B>EnumerateAlgorithms</B>( DWORD&amp; enumerator )</PRE><DD>
Initializes an enumerator to list the algorithms
this provider provides.

<DT><PRE>BOOL <B>GenerateRandomBytes</B>( CByteArray&amp; bytes, DWORD number_of_bytes = 0 )</PRE><DD>
Generates a set of random bytes. if <CODE>number_of_bytes</CODE> is
zero, the bytes in <CODE>bytes</CODE> will be overwritten with random bytes.

<DT><PRE>BOOL <B>GetNext</B>( DWORD&amp; enumerator, CCryptographicAlgorithm&amp; algorithm )</PRE><DD>
Used to walk the list of enumerated thingies.

<DT><PRE>BOOL <B>GetParameter</B>( const DWORD what_to_get, CByteArray&amp; buffer, const DWORD flags )</PRE><DD>
Retrieves information about the crypto.
<CODE>what_to_get</CODE> may be one of the following:
<UL>
<LI>parameterEnumerateAlgorithms
<LI>parameterEnumerateContainers
<LI>parameterImplementationType
<LI>parameterName
<LI>parameterVersion
<LI>parameterCurrentKeyContainerName
<LI>parameterClientWindowHandle
</UL>

<DT><PRE>BOOL <B>GetUserKey</B>( DWORD which_user_key_to_get, <A HREF="CCryptographicKey.htm">CCryptographicKey</A>&amp; key )</PRE><DD>
Retrieves a user's key.  <CODE>which_user_key_to_get</CODE> varies from
provider to provider but it will almost always be one of the following:
<UL>
<LI>AT_KEYEXCHANGE
<LI>AT_SIGNATURE
</UL>

<DT><PRE>BOOL <B>ImportKey</B>( CByteArray&amp; exported_key_data,
                <A HREF="CCryptographicKey.htm">CCryptographicKey</A>&amp; key,
                DWORD              format = <A HREF="CCryptographicKey.htm">CCryptographicKey</A>::formatSimple,
                DWORD              flags  = 0 )</PRE><DD>
This used to transfer a cryptographic key from a key blob to the service
provider.

<DT><PRE>BOOL <B>Open</B>( LPCTSTR container_name = NULL,
           LPCTSTR provider_name  = NULL,
           DWORD   provider_type  = RsaFull,
           DWORD   flags          = 0 </PRE><DD>
Opens a session with the crypto. It will automatically create
a key set if needed.

<DT><PRE>BOOL <B>SetDefault</B>( const CString&amp; name, DWORD type )</PRE><DD>
Sets the default provider.

</DL>

<H2>Example</H2><PRE><CODE>Sorry.</CODE></PRE>

<H2>API's Used</H2>
<UL>
<LI>CryptAcquireContext
<LI>CryptCreateHash
<LI>CryptDeriveKey
<LI>CryptGenKey
<LI>CryptGenRandom
<LI>CryptGetProvParam
<LI>CryptGetUserKey
<LI>CryptImportKey
<LI>CryptReleaseContext
<LI>CryptSetProvider
</UL>

<HR><I>Copyright, 2000, <A HREF="mailto:wfc@pobox.com">Samuel R. Blackburn</A></I><BR>
$Workfile: CCryptographicProvider.cpp $<BR>
$Modtime: 1/04/00 5:09a $
</BODY>

</HTML>
#endif
