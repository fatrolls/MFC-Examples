#if ! defined( WINCRYPT_PATCH_HEADER_FILE )

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
** $Workfile: wfc_crypto.h $
** $Revision: 8 $
** $Modtime: 5/04/00 6:45p $
*/

#define WINCRYPT_PATCH_HEADER_FILE

// 2000-01-26
// Thanks go to Erich Einfalt (eeinfalt@amaonline.com) for
// pointing out my laziness in this header file

#if ! defined( ALG_SID_3DES )
#define ALG_SID_3DES (3)
#endif

#if ! defined( ALG_SID_DESX )
#define ALG_SID_DESX (4)
#endif

#if ! defined( ALG_SID_IDEA )
#define ALG_SID_IDEA (5)
#endif

#if ! defined( ALG_SID_CAST )
#define ALG_SID_CAST (6)
#endif

#if ! defined( ALG_SID_SAFERSK64 )
#define ALG_SID_SAFERSK64 (7)
#endif

#if ! defined( ALD_SID_SAFERSK128 )
#define ALD_SID_SAFERSK128 (8)
#endif

#if ! defined( ALG_SID_SAFERSK128 )
// Fix a Microsoft typo
#define ALG_SID_SAFERSK128 (8)
#endif // ALG_SID_SAFERSK128

// KP_MODE
#if ! defined( CRYPT_MODE_CBCI )
#define CRYPT_MODE_CBCI     (6)  // ANSI CBC Interleaved
#endif

#if ! defined( CRYPT_MODE_CFBP )
#define CRYPT_MODE_CFBP     (7)  // ANSI CFB Pipelined
#endif

#if ! defined( CRYPT_MODE_OFBP )
#define CRYPT_MODE_OFBP     (8)  // ANSI OFB Pipelined
#endif

#if ! defined( CRYPT_MODE_CBCOFM )
#define CRYPT_MODE_CBCOFM   (9)  // ANSI CBC + OF Masking
#endif

#if ! defined( CRYPT_MODE_CBCOFMI )
#define CRYPT_MODE_CBCOFMI (10)  // ANSI CBC + OFM Interleaved
#endif

// Hash sub ids
#if ! defined( ALG_SID_RIPEMD )
#define ALG_SID_RIPEMD     (6)
#endif

#if ! defined( ALG_SID_RIPEMD160 )
#define ALG_SID_RIPEMD160  (7)
#endif

#if ! defined( ALG_SID_SSL3SHAMD5 )
#define ALG_SID_SSL3SHAMD5 (8)
#endif

#if ! defined( ALG_SID_HMAC )
#define ALG_SID_HMAC       (9)
#endif

// exported key blob definitions
#if ! defined( PRIVATEKEYBLOB )
#define PRIVATEKEYBLOB (0x7)
#endif // PRIVATEKEYBLOB

#if ! defined( PP_CLIENT_HWND )
#define PP_CLIENT_HWND         (1)
#endif // PP_CLIENT_HWND

#if ! defined( PROV_SSL )
#define PROV_SSL                (6)
#endif

#if ! defined( PROV_RSA_SCHANNEL )
#define PROV_RSA_SCHANNEL       (12)
#endif

#if ! defined( PROV_DSS_DH )
#define PROV_DSS_DH             (13)
#endif

#if ! defined( PROV_EC_ECDSA_SIG )
#define PROV_EC_ECDSA_SIG       (14)
#endif

#if ! defined( PROV_EC_ECNRA_SIG )
#define PROV_EC_ECNRA_SIG       (15)
#endif

#if ! defined( PROV_EC_ECDSA_FULL )
#define PROV_EC_ECDSA_FULL      (16)
#endif

#if ! defined( PROV_EC_ECNRA_FULL )
#define PROV_EC_ECNRA_FULL      (17)
#endif

#if ! defined( PROV_SPYRUS_LYNKS )
#define PROV_SPYRUS_LYNKS       (20)
#endif

// Microsoft redefined a provider!!! I really hate when they break my code

#if ! defined( PROV_MS_MAIL )
#define PROV_MS_MAIL (5)
#endif // PROV_MS_MAIL

#if ! defined( CRYPT_MACHINE_KEYSET )
#define CRYPT_MACHINE_KEYSET (0x00000020)
#endif // CRYPT_MACHINE_KEYSET

// New NT5 defined constants. They first appeared (or I first noticed them)
// in the Jan 2000 version of the Platform SDK.

#if ! defined( PROV_DH_SCHANNEL )
#define PROV_DH_SCHANNEL (18)
#endif // PROV_DH_SCHANNEL

#if ! defined( PROV_RNG )
#define PROV_RNG (21)
#endif // PROV_DH_SCHANNEL

#if ! defined( PROV_INTEL )
#define PROV_INTEL_SEC (22)
#endif // PROV_DH_SCHANNEL

#if ! defined( ALG_CLASS_ALL )
#define ALG_CLASS_ALL (7 << 13)
#endif // ALG_CLASS_ALL

#if ! defined( ALG_TYPE_DH )
#define ALG_TYPE_DH (5 << 9)
#endif // ALG_TYPE_DH

#if ! defined( ALG_TYPE_SECURECHANNEL )
#define ALG_TYPE_SECURECHANNEL (6 << 9)
#endif // ALG_TYPE_SECURECHANNEL

#if ! defined( ALG_SID_3DES_112 )
#define ALG_SID_3DES_112 (9)
#endif // ALG_SID_3DES_112

#if ! defined( ALG_SID_CYLINK_MEK )
#define ALG_SID_CYLINK_MEK (12)
#endif // ALG_SID_CYLINK_MEK

#if ! defined( ALG_SID_RC5 )
#define ALG_SID_RC5 (13)
#endif // ALG_SID_RC5

#if ! defined( ALG_SID_SKIPJACK )
#define ALG_SID_SKIPJACK (10)
#endif // ALG_SID_SKIPJACK

#if ! defined( ALG_SID_TEK )
#define ALG_SID_TEK (11)
#endif // ALG_SID_TEK

#if ! defined( CRYPT_MACHINE_KEYSET )
#define CRYPT_MACHINE_KEYSET (0x20)
#endif // CRYPT_MACHINE_KEYSET

#if ! defined( CRYPT_SILENT )
#define CRYPT_SILENT (0x40)
#endif // CRYPT_SILENT

#if ! defined( CRYPT_NO_SALT )
#define CRYPT_NO_SALT (0x10)
#endif // CRYPT_NO_SALT

#if ! defined( CRYPT_PREGEN )
#define CRYPT_PREGEN (0x40)
#endif // CRYPT_PREGEN

#if ! defined( CRYPT_RECIPIENT )
#define CRYPT_RECIPIENT (0x10)
#endif // CRYPT_RECIPIENT

#if ! defined( CRYPT_INITIATOR )
#define CRYPT_INITIATOR (0x40)
#endif // CRYPT_INITIATOR

#if ! defined( CRYPT_ONLINE )
#define CRYPT_ONLINE (0x80)
#endif // CRYPT_ONLINE

#if ! defined( CRYPT_SF )
#define CRYPT_SF (0x100)
#endif // CRYPT_SF

#if ! defined( CRYPT_CREATE_IV )
#define CRYPT_CREATE_IV (0x200)
#endif // CRYPT_CREATE_IV

#if ! defined( CRYPT_KEK )
#define CRYPT_KEK (0x400)
#endif // CRYPT_KEK

#if ! defined( CRYPT_DATA_KEY )
#define CRYPT_DATA_KEY (0x800)
#endif // CRYPT_DATA_KEY

#if ! defined( CRYPT_VOLATILE )
#define CRYPT_VOLATILE (0x1000)
#endif // CRYPT_VOLATILE

#if ! defined( CRYPT_SGCKEY )
#define CRYPT_SGCKEY (0x2000)
#endif // CRYPT_SGCKEY

#if ! defined( PP_ENUMMANDROOTS )
#define PP_ENUMMANDROOTS (25)
#endif // PP_ENUMMANDROOTS

#if ! defined( PP_ENUMELECTROOTS )
#define PP_ENUMELECTROOTS (26)
#endif // PP_ENUMELECTROOTS

#if ! defined( PP_KEYSET_TYPE )
#define PP_KEYSET_TYPE (27)
#endif // PP_KEYSET_TYPE

#if ! defined( PP_ADMIN_PIN )
#define PP_ADMIN_PIN (31)
#endif // PP_ADMIN_PIN

#if ! defined( PP_KEYEXCHANGE_PIN )
#define PP_KEYEXCHANGE_PIN (32)
#endif // PP_KEYEXCHANGE_PIN

#if ! defined( PP_SIGNATURE_PIN )
#define PP_SIGNATURE_PIN (33)
#endif // PP_KEYEXCHANGE_PIN

#if ! defined( PP_SIG_KEYSIZE_INC )
#define PP_SIG_KEYSIZE_INC (34)
#endif // PP_SIG_KEYSIZE_INC

#if ! defined( PP_KEYX_KEYSIZE_INC )
#define PP_KEYX_KEYSIZE_INC (35)
#endif // PP_KEYX_KEYSIZE_INC

#if ! defined( PP_UNIQUE_CONTAINER )
#define PP_UNIQUE_CONTAINER (36)
#endif // PP_UNIQUE_CONTAINER

#if ! defined( PP_SGC_INFO )
#define PP_SGC_INFO (37)
#endif // PP_SGC_INFO

#if ! defined( PP_USE_HARDWARE_RNG )
#define PP_USE_HARDWARE_RNG (38)
#endif // PP_USE_HARDWARE_RNG

#if ! defined( PP_KEYSPEC )
#define PP_KEYSPEC (39)
#endif // PP_KEYSPEC

#if ! defined( PP_ENUMEX_SIGNING_PROT )
#define PP_ENUMEX_SIGNING_PROT (40)
#endif // PP_ENUMEX_SIGNING_PROT

#if ! defined( ALG_SID_TLS1PRF )
#define ALG_SID_TLS1PRF (10)
#endif // ALG_SID_TLS1PRF

#if ! defined( CALG_DESX )
#define CALG_DESX (ALG_CLASS_DATA_ENCRYPT|ALG_TYPE_BLOCK|ALG_SID_DESX)
#endif // CALG_DESX

#if ! defined( CALG_TLS1PRF )
#define CALG_TLS1PRF (ALG_CLASS_DHASH|ALG_TYPE_ANY|ALG_SID_TLS1PRF)
#endif // CALG_TLS1PRF

// Some Satan worshiper works at Microsoft. Using the Sign
// of the Beast for the crypto service provider signature resource number???
#if ! defined( SIGNATURE_RESOURCE_NUMBER )
#define SIGNATURE_RESOURCE_NUMBER (666)
#endif // SIGNATURE_RESOURCE_NUMBER

#endif // WINCRYPT_PATCH_HEADER_FILE
