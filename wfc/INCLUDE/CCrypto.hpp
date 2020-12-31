#if ! defined( CRYPTO_API_CLASS_HEADER )

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
** $Workfile: CCrypto.hpp $
** $Revision: 20 $
** $Modtime: 5/04/00 6:37p $
*/

#define CRYPTO_API_CLASS_HEADER

#if _MSC_VER >= 1020

#include "wfc_crypto.h"

class CCryptography
#if ! defined(  WFC_NO_SERIALIZATION )
: public CObject
#endif // WFC_NO_SERIALIZATION
{
   protected:

      DWORD m_ErrorCode;

   public:

      CCryptography();
      virtual ~CCryptography();

      virtual DWORD GetErrorCode( void ) const;
};

// Need forward declaration because of Catch-22...
class CCryptographicKey;

class CCryptographicHash : public CCryptography
{
   private:

      // Don't allow canonical behavior (i.e. don't allow this class
      // to be passed by value)

      CCryptographicHash( const CCryptographicHash& ) {};
      CCryptographicHash& operator=( const CCryptographicHash& ) { return( *this ); };

   protected:

      HCRYPTHASH m_Hash;

      BOOL m_AutomaticallyDestroy;

   public:

      // Construction

      CCryptographicHash();
      CCryptographicHash( HCRYPTHASH source_handle, BOOL automatically_destroy = TRUE );
      virtual ~CCryptographicHash();

      // Properties

      enum _Parameters
      {
         parameterAlgorithmIdentifier = HP_ALGID,
         parameterLength              = HP_HASHSIZE,
         parameterValue               = HP_HASHVAL
      };

      // Methods

      virtual BOOL Destroy( void ); // CryptDestroyHash
      virtual BOOL FromHandle( HCRYPTHASH source_handle, BOOL automatically_destroy = TRUE );
      virtual HCRYPTHASH GetHandle( void ) const;
      virtual BOOL GetParameter( const DWORD parameter_to_get, BYTE *buffer, DWORD& buffer_length, const DWORD flags = 0 ); // CryptGetKeyParam

      // GetParameter helpers

      virtual BOOL GetAlgorithmIdentifier( DWORD& identifier );
      virtual BOOL GetLength( DWORD& length );
      virtual BOOL GetValue( CByteArray& value );
      virtual BOOL Hash( CByteArray& data_to_compute_a_hash_on, DWORD flags = CRYPT_USERDATA ); // CryptHashData
      virtual BOOL Hash( const CCryptographicKey& key_to_hash, DWORD flags = 0 ); // CryptHashSessionKey
      
      // All of the Setxxx methods parameters cannot be properly typed because
      // the CryptSetHashParam() API is mis-typed. The buffer parameter should
      // be const but it is not. Looks like they didn't think it through enough.

      virtual BOOL SetParameter( const DWORD parameter_to_set, BYTE *buffer, const DWORD flags = 0 ); // CryptSetKeyParam

      // SetParameter helpers

      virtual BOOL SetValue( CByteArray& value );
      virtual BOOL Sign( DWORD which_key_to_sign_with, CString& password, CByteArray& signature, DWORD flags = 0 ); // CryptSignHash
      virtual BOOL VerifySignature( CByteArray& signature, CCryptographicKey& public_key_to_verify_with, CString& password, DWORD flags = 0 ); // CryptVerifySignature
};

class CCryptographicAlgorithm
#if ! defined(  WFC_NO_SERIALIZATION )
: public CObject
#endif // WFC_NO_SERIALIZATION
{
#if ! defined(  WFC_NO_SERIALIZATION )
   DECLARE_SERIAL( CCryptographicAlgorithm )
#endif // WFC_NO_SERIALIZATION

   protected:

      DWORD m_Identifier;

   public:

      // Construction

      CCryptographicAlgorithm();
      CCryptographicAlgorithm( const CCryptographicAlgorithm& source );
      CCryptographicAlgorithm( const PROV_ENUMALGS& source );
      virtual ~CCryptographicAlgorithm();

      // Properties

      enum _Classes
      {
         classAny            = ALG_CLASS_ANY,
         classSignature      = ALG_CLASS_SIGNATURE,
         classMessageEncrypt = ALG_CLASS_MSG_ENCRYPT,
         classDataEncrypt    = ALG_CLASS_DATA_ENCRYPT,
         classHash           = ALG_CLASS_HASH,
         classKeyExchange    = ALG_CLASS_KEY_EXCHANGE,
         classAll            = ALG_CLASS_ALL,
      };

      enum _Types
      {
         typeAny                      = ALG_TYPE_ANY,
         typeDigitalSignatureStandard = ALG_TYPE_DSS,
         typeRSA                      = ALG_TYPE_RSA,
         typeBlock                    = ALG_TYPE_BLOCK,
         typeStream                   = ALG_TYPE_STREAM,
         typeDiffieHellman            = ALG_TYPE_DH,
         typeSecureChannel            = ALG_TYPE_SECURECHANNEL,
      };

      enum _RSASubIdentifiers
      {
         rsaAny             = ALG_SID_RSA_ANY,
         rsaPKCS            = ALG_SID_RSA_PKCS,
         rsaMicrosoftAtWork = ALG_SID_RSA_MSATWORK,
         rsaEntrust         = ALG_SID_RSA_ENTRUST,
         rsaPGP             = ALG_SID_RSA_PGP,
      };

      enum _DSSSubIdentifiers
      {
         dssAny                    = ALG_SID_DSS_ANY,
         dssPKCS                   = ALG_SID_DSS_PKCS,
         dssDefenseMessagingSystem = ALG_SID_DSS_DMS
      };

      enum _BlockCipherSubIdentifiers
      {
         blockDigitalEncryptionStandard = ALG_SID_DES,
         blockRC2                       = ALG_SID_RC2,
         blockTripleDES                 = ALG_SID_3DES,
         blockDESX                      = ALG_SID_DESX,
         blockIDEA                      = ALG_SID_IDEA,
         blockCAST                      = ALG_SID_CAST,
         blockSaferSK64                 = ALG_SID_SAFERSK64,
         blockSaferSK128                = ALG_SID_SAFERSK128,
         block3DES112                   = ALG_SID_3DES_112,
         blockCylinkMEK                 = ALG_SID_CYLINK_MEK,
         blockRC5                       = ALG_SID_RC5,
         blockSkipJack                  = ALG_SID_SKIPJACK,
         blockTEK                       = ALG_SID_TEK,
      };

      enum _StreamSubIdentifiers
      {
         streamRC4  = ALG_SID_RC4,
         streamSeal = ALG_SID_SEAL
      };

      enum _HashSubIdentifiers
      {
         hashMD2       = ALG_SID_MD2,
         hashMD4       = ALG_SID_MD4,
         hashMD5       = ALG_SID_MD5,
         hashSHA       = ALG_SID_SHA,
         hashMAC       = ALG_SID_MAC,
         hashRipeMD    = ALG_SID_RIPEMD,
         hashRipeMD160 = ALG_SID_RIPEMD160,
         hashSSLMD5    = ALG_SID_SSL3SHAMD5,
         hashTLS1PRF   = ALG_SID_TLS1PRF,
      };

      DWORD   Identifier;
      DWORD   BitLength;
      CString Name;

      // Methods

      virtual void Copy( const CCryptographicAlgorithm& source );
      virtual void Copy( const PROV_ENUMALGS& source );
      virtual void Copy( const PROV_ENUMALGS * source );
      virtual void Empty( void );
      virtual BOOL IsDataEncrypt( void ) const;
      virtual BOOL IsHash( void ) const;
      virtual BOOL IsKeyExchange( void ) const;
      virtual BOOL IsMessageEncrypt( void ) const;
      virtual BOOL IsSignature( void ) const;

#if ! defined( WFC_NO_SERIALIZATION )
      virtual void Serialize( CArchive& archive );
#endif // WFC_NO_SERIALIZATION

      // Operators

      virtual CCryptographicAlgorithm& operator=( const CCryptographicAlgorithm& source );
      virtual CCryptographicAlgorithm& operator=( const PROV_ENUMALGS& source );

      // Instrumentation

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

      virtual void Dump( CDumpContext& dump_context ) const;

#endif // _DEBUG
};

class CCryptographicKey : public CCryptography
{
   private:

      // Don't allow canonical behavior (i.e. don't allow this class
      // to be passed by value)

      CCryptographicKey( const CCryptographicKey& ) {};
      CCryptographicKey& operator=( const CCryptographicKey& ) { return( *this ); };

   protected:

      HCRYPTKEY m_Key;

      BOOL m_AutomaticallyDestroy;

   public:

      // Construction

      CCryptographicKey();
      CCryptographicKey( HCRYPTKEY source_handle, BOOL automatically_destroy = TRUE );
      virtual ~CCryptographicKey();

      // Properties
      enum _Parameters
      {
         parameterAlgorithmIdentifier           = KP_ALGID,
         parameterBlockLengthInBytes            = KP_BLOCKLEN,
         parameterSalt                          = KP_SALT,
         parameterPermissions                   = KP_PERMISSIONS,
         parameterInitializationVector          = KP_IV,
         parameterPaddingMode                   = KP_PADDING,
         parameterCipherMode                    = KP_MODE,
         parameterNumberOfBitsProcessedPerCycle = KP_MODE_BITS,

#if defined( KP_PUB_EX_VAL )
         // New Parameters
         parameterKeyLengthInBits                  = KP_KEYLEN,
         parameterLengthOfSaltInBytes              = KP_SALT_EX,
         parameterDSSDiffieHellmanPValue           = KP_P,
         parameterDSSDiffieHellmanGValue           = KP_G,
         parameterDSSQValue                        = KP_Q,
         parameterDiffieHellmanXValue              = KP_X,
         parameterYValue                           = KP_Y,
         parameterFortezzaRAValue                  = KP_RA,
         parameterFortezzaRBValue                  = KP_RB,
         parameterRSAEnvelopeInformation           = KP_INFO,
         parameterRC2EffectiveKeyLength            = KP_EFFECTIVE_KEYLEN,
         parameterSecureChannelAlgorithm           = KP_SCHANNEL_ALG,
         parameterSecureChannelClientRandomData    = KP_CLIENT_RANDOM,
         parameterSecureChannelServerRandomData    = KP_SERVER_RANDOM,
         parameterRP                               = KP_RP,
         parameterPrecompiledMD5                   = KP_PRECOMP_MD5,
         parameterPrecmopiledSHA                   = KP_PRECOMP_SHA,
         parameterSecureChannelCertificateDataPCT1 = KP_CERTIFICATE,
         parameterSecureChannelClearKeyDataPCT1    = KP_CLEAR_KEY,
         parameterPubExLength                      = KP_PUB_EX_LEN,
         parameterPubExValue                       = KP_PUB_EX_VAL,
#endif // KP_PUB_EX_VAL
      };

      enum _CipherModes
      {
         modeElectronicCodebook                             = CRYPT_MODE_ECB,
         modeCipherBlockChaining                            = CRYPT_MODE_CBC,
         modeOutputFeedback                                 = CRYPT_MODE_OFB,
         modeCipherFeedback                                 = CRYPT_MODE_CFB,
         modeCiphertextStealing                             = CRYPT_MODE_CTS,
         modeAnsiCipherBlockChaningInterleaved              = CRYPT_MODE_CBCI,
         modeAnsiCipherFeedbackPipelined                    = CRYPT_MODE_CFBP,
         modeAnsiOutputFeedbackPipelined                    = CRYPT_MODE_OFBP,
         modeAnsiCipherBlockChainingAndOFMasking            = CRYPT_MODE_CBCOFM,
         modeAnsiCipherBlockChainingAndOFMaskingInterleaved = CRYPT_MODE_CBCOFMI
      };

      enum _Permissions
      {
         permissionEncrypt = CRYPT_ENCRYPT,
         permissionDecrypt = CRYPT_DECRYPT,
         permissionExport  = CRYPT_EXPORT,
         permissionRead    = CRYPT_READ,
         permissionWrite   = CRYPT_WRITE,
         permissionMAC     = CRYPT_MAC
      };

      enum _KeyFormats
      {
         formatSimple     = SIMPLEBLOB,
         formatPublicKey  = PUBLICKEYBLOB,
         formatPrivateKey = PRIVATEKEYBLOB
      };

      // Methods

      virtual BOOL Decrypt( const CByteArray&          data_to_decrypt,
                                  CByteArray&          decrypted_data,
                                  BOOL                 this_is_the_last_chunk_of_data_to_be_decrypted = TRUE,
                                  CCryptographicHash * hash_p = NULL,
                                  DWORD                flags  = 0 ); // CryptDecrypt

      virtual BOOL Destroy( void ); // CryptDestroyKey

      virtual BOOL Encrypt( const CByteArray&          data_to_encrypt,
                                  CByteArray&          encrypted_data,
                                  BOOL                 this_is_the_last_chunk_of_data_to_be_encrypted = TRUE,
                                  CCryptographicHash * hash_p = NULL,
                                  DWORD                flags  = 0 ); // CryptEncrypt

      virtual BOOL Export( CCryptographicKey& key_for_whoever_we_are_exporting_to,
                           CByteArray& key_in_exported_form,
                           DWORD       export_format = formatSimple,
                           DWORD       flags         = 0 );
      virtual BOOL FromHandle( HCRYPTKEY source_handle, BOOL automatically_destroy = TRUE );
      virtual HCRYPTKEY GetHandle( void ) const;
      virtual BOOL GetParameter( const DWORD parameter_to_get, BYTE *buffer, DWORD& buffer_length, const DWORD flags = 0 ); // CryptGetKeyParam

      // Helpers for GetParameter

      virtual BOOL GetAlgorithmIdentifier( DWORD& identifier );
      virtual BOOL GetBlockLength( DWORD& block_length );
      virtual BOOL GetCipherMode( DWORD& cipher_mode );
      virtual BOOL GetInitializationVector( CByteArray& initialization_vector );
      virtual BOOL GetNumberOfBitsProcessedPerCycle( DWORD& number_of_bits );
      virtual BOOL GetPaddingMode( DWORD& padding_mode );
      virtual BOOL GetPermissions( DWORD& permissions );
      virtual BOOL GetSalt( CByteArray& salt );
      
      // All of the Setxxx methods parameters cannot be properly typed because
      // the CryptSetKeyParam() API is mis-typed. The buffer parameter should
      // be const but it is not. Looks like they didn't think it through enough.

      virtual BOOL SetParameter( const DWORD parameter_to_set, BYTE *buffer, const DWORD flags = 0 ); // CryptSetKeyParam
      
      // Helpers for SetParameter
      virtual BOOL SetPermissions( DWORD permissions );
      virtual BOOL SetSalt( BYTE *buffer );
      virtual BOOL SetInitializationVector( BYTE *buffer );
      virtual BOOL SetPaddingMode( DWORD mode );
      virtual BOOL SetCipherMode( DWORD mode );
      virtual BOOL SetNumberOfBitsProcessedPerCycle( DWORD number_of_bits );
};

class CCryptographicProvider : public CCryptography
{
   private:

      // Don't allow canonical behavior (i.e. don't allow this class
      // to be passed by value)

      CCryptographicProvider( const CCryptographicProvider& ) {};
      CCryptographicProvider& operator=( const CCryptographicProvider& ) { return( *this ); };

   protected:

      HCRYPTPROV m_CryptographicProvider;

      void m_Initialize( void );

   public:

      // Construction

      CCryptographicProvider();
      virtual ~CCryptographicProvider();

      // Properties

      enum _Providers
      {
         RsaFull                  = PROV_RSA_FULL,
         RsaSignature             = PROV_RSA_SIG,
         DigitalSignatureStandard = PROV_DSS,
         Clipper                  = PROV_FORTEZZA,
         MicrosoftMail            = PROV_MS_MAIL,
         STTMer                   = PROV_STT_MER,
         STTAcq                   = PROV_STT_ACQ,
         STTBrnd                  = PROV_STT_BRND,
         STTRoot                  = PROV_STT_ROOT,
         STTIss                   = PROV_STT_ISS,
         SecureSocketsLayer       = PROV_SSL,
         RSASChannel              = PROV_RSA_SCHANNEL,
         DSSDiffieHellman         = PROV_DSS_DH,
         ECDSASignature           = PROV_EC_ECDSA_SIG,
         ECNRASignature           = PROV_EC_ECNRA_SIG,
         ECDSAFull                = PROV_EC_ECDSA_FULL,
         ECNRAFull                = PROV_EC_ECNRA_FULL,
         SpyrusLynks              = PROV_SPYRUS_LYNKS,
         DiffieHellmanSecureChannel = PROV_DH_SCHANNEL,
         RandomNumberGenerator    = PROV_RNG,
         IntelSecurity            = PROV_INTEL_SEC,   
      };

      enum _Parameters
      {
         parameterEnumerateAlgorithms      = PP_ENUMALGS,
         parameterEnumerateContainers      = PP_ENUMCONTAINERS,
         parameterImplementationType       = PP_IMPTYPE,
         parameterName                     = PP_NAME,
         parameterVersion                  = PP_VERSION,
         parameterCurrentKeyContainerName  = PP_CONTAINER,
         parameterClientWindowHandle       = PP_CLIENT_HWND,

#if defined( PP_ENUMALGS_EX )
         parameterChangePassword           = PP_CHANGE_PASSWORD,
         parameterKeysetSecurityDescriptor = PP_KEYSET_SEC_DESCR,
         parameterCertificateChain         = PP_CERTCHAIN,
         parameterKeyTypeSubType           = PP_KEY_TYPE_SUBTYPE,
         parameterProviderType             = PP_KEY_TYPE_SUBTYPE,
         parameterKeyStorage               = PP_KEYSTORAGE,
         parameterApplicationCertificate   = PP_APPLI_CERT,
         parameterSymmetricKeySize         = PP_SYM_KEYSIZE,
         parameterSessionKeySize           = PP_SESSION_KEYSIZE,
         parameterUserInterfacePrompt      = PP_UI_PROMPT,
         parameterEnumerateAlgorithmsEx    = PP_ENUMALGS_EX,
         parameterContextInformation       = PP_CONTEXT_INFO,
         parameterKeyExchangeKeySize       = PP_KEYEXCHANGE_KEYSIZE,
         parameterSignatureKeySize         = PP_SIGNATURE_KEYSIZE,
         parameterKeyExchangeAlgorithm     = PP_KEYEXCHANGE_ALG,
         parameterSignatureAlgorithm       = PP_SIGNATURE_ALG,
         parameterDeleteKey                = PP_DELETEKEY,
#endif // PP_ENUMALGS_EX
         parameterEnumerateMandatoryRoots  = PP_ENUMMANDROOTS,
         parameterEnumerateElectedRoots    = PP_ENUMELECTROOTS,
         parameterKeySetType               = PP_KEYSET_TYPE,
         parameterAdministratorPersonalIdentificationNumber = PP_ADMIN_PIN,
         parameterKeyExchangePersonalIdentificationNumber = PP_KEYEXCHANGE_PIN,
         parameterSignaturePersonalIdentificationNumber = PP_SIGNATURE_PIN,
         parameterSignatureKeySizeIncrement   = PP_SIG_KEYSIZE_INC,
         parameterKeyExchangeKeySizeIncrement = PP_KEYX_KEYSIZE_INC,
         parameterUniqueContainer             = PP_UNIQUE_CONTAINER,
         parameterSGCInformation              = PP_SGC_INFO,
         parameterUseHardwareRandomNumberGenerator = PP_USE_HARDWARE_RNG,
         parameterKeySpecification                 = PP_KEYSPEC,
         parameterEnumerateSigningProtection       = PP_ENUMEX_SIGNING_PROT,
      };

      enum _Flags
      {
         VerifyContext = CRYPT_VERIFYCONTEXT,
         NewKeySet     = CRYPT_NEWKEYSET,
         DeleteKeySet  = CRYPT_DELETEKEYSET,
         MachineKeySet = CRYPT_MACHINE_KEYSET,
         Silent        = CRYPT_SILENT,
      };

      enum _KeyFlags
      {
         keyflagExportable     = CRYPT_EXPORTABLE,
         keyflagCreateSalt     = CRYPT_CREATE_SALT,
         keyflagUserProtected  = CRYPT_USER_PROTECTED,
         keyflagCryptUpdateKey = CRYPT_UPDATE_KEY,
         keyflagNoSalt         = CRYPT_NO_SALT,
         keyflagPreGenerated   = CRYPT_PREGEN,
         keyflagRecipient      = CRYPT_RECIPIENT,
         keyflagInitiator      = CRYPT_INITIATOR,
         keyflagOnLine         = CRYPT_ONLINE,
         keyflagSF             = CRYPT_SF,
         keyflagCreateInitialVector = CRYPT_CREATE_IV,
         keyflagKeyExchangeKey = CRYPT_KEK,
         keyflagDataKey        = CRYPT_DATA_KEY,
         keyflagVolatile       = CRYPT_VOLATILE,
         keyflagSGCKey         = CRYPT_SGCKEY,
      };

      // Methods
      
      virtual BOOL  Open( LPCTSTR container_name = NULL,
                          LPCTSTR provider_name  = NULL,
                          DWORD   provider_type  = RsaFull,
                          DWORD   flags          = 0 ); // CryptAcquireContext
      virtual void  Close( void ); // CryptReleaseContext
      virtual BOOL  CreateHash( const CCryptographicAlgorithm& which_algorithm_you_want_the_key_for, 
                                const CCryptographicKey&       key_for_algorithms_that_need_it,
                                      CCryptographicHash&      destination_hash,
                                      DWORD                    flags = 0 ); //
      virtual BOOL  CreateKey( const CCryptographicAlgorithm& which_algorithm_you_want_the_key_for, 
                                     CCryptographicKey&       destination_key,
                                     DWORD                    flags = CRYPT_EXPORTABLE,
                                     WORD                     number_of_bits_in_key = 0 ); // CryptGenKey
      virtual BOOL  CreateKeySet( LPCTSTR container_name = NULL, LPCTSTR provider_name = NULL, DWORD provider_type = RsaFull );

      virtual BOOL  ImportKey( CByteArray& exported_key_data,
                               CCryptographicKey& key,
                               DWORD       format = CCryptographicKey::formatSimple,
                               DWORD       flags  = 0 ); // CryptImportKey

      virtual BOOL  DeriveKey( const CCryptographicAlgorithm& algorithm, 
                               const CCryptographicHash&      hash,
                                     CCryptographicKey&       key,
                                     DWORD                    flags = keyflagExportable );
      virtual void  EnumerateAlgorithms( DWORD& enumerator );
      virtual BOOL  GenerateRandomBytes( CByteArray& bytes, DWORD number_of_bytes = 0 ); // CryptGenRandom
      virtual BOOL  GetNext( DWORD& enumerator, CCryptographicAlgorithm& algorithm );
      virtual BOOL  GetParameter( const DWORD what_to_get, CByteArray& buffer, const DWORD flags ); // CryptGetProvParam
      virtual BOOL  GetUserKey( DWORD which_user_key_to_get, CCryptographicKey& key );
      virtual BOOL  SetDefault( const CString& name, DWORD type ); // CryptSetProvider
      virtual HCRYPTPROV GetHandle( void ) const;

#if defined( _DEBUG ) && ! defined( WFC_NO_DUMPING )

      virtual void Dump( CDumpContext& dump_context ) const;

#endif // _DEBUG
};

#endif // _MSC_VER

#endif // CRYPTO_API_CLASS_HEADER
