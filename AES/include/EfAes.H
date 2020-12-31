/**************************************************************

				EF AES Library 2.0

Module Name: AES.h
Abstract: Advanced Encryption Standard implementation header file
   
Author: robert Guan
	  
*************************************************************/

#ifndef __EF_AES__
#define __EF_AES__


typedef struct _AesCtx_
{
	unsigned char space[512];
} AesCtx;


//_AES_KEY_LENGTH_
#define AES_KEY_128BIT  0
#define AES_KEY_192BIT  1 
#define AES_KEY_256BIT  2



typedef enum _AES_BLOCK_MODE_ 
{
	BLOCKMODE_ECB = 0,
	BLOCKMODE_CBC    ,
	BLOCKMODE_PCBC   ,
	BLOCKMODE_OFB    ,
	BLOCKMODE_CFB    ,
	BLOCKMODE_CRT 
} BlockMode;


// the buffer padding define
#define AES_PADDING (16)

// set key and initial vector
extern void AesSetKey( AesCtx * pContext ,int iKeyLength, BlockMode iBlockMode,  void * key , void * initialVector );
extern void AesSetInitVector( AesCtx * pContext , void * initialVector );
extern void AesSetFeedbackSize(AesCtx * pContext , int iFeedbackSize );

// an util function
extern int AesRoundSize( int iSize, int iRoundSize );

// encrypt APIs
extern void AesEncryptECB( AesCtx * pContext,void * pOutput ,void * pInput ,int iSize);
extern void AesEncryptCBC( AesCtx * pContext,void * pOutput ,void * pInput ,int iSize);
extern void AesEncryptPCBC( AesCtx * pContext,void * pOutput,void * pInput ,int iSize );
extern void AesEncryptCRT( AesCtx * pContext,void * pOutput ,void * pInput ,int iSize);
extern void AesEncryptOFB( AesCtx * pContext,void * pOutput ,void * pInput ,int iSize);
extern void AesEncryptCFB( AesCtx * pContext,void * pOutput, void * pInput ,int iSize);


// decrypt APIs
extern void AesDecryptECB( AesCtx * pContext, void * pOutput,void * pInput ,int iSize );
extern void AesDecryptCBC( AesCtx * pContext,void * pOutput, void * pInput ,int iSize );
extern void AesDecryptPCBC( AesCtx * pContext,void * pOutput,void * pInput ,int iSize );
extern void AesDecryptCRT( AesCtx * pContext,void * pOutput ,void * pInput ,int iSize );
extern void AesDecryptOFB( AesCtx * pContext,void * pOutput ,void * pInput ,int iSize );
extern void AesDecryptCFB( AesCtx * pContext, void * pOutput,void * pInput ,int iSize );


#endif //__EF_AES__

