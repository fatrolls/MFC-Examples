/*
 *
 * Copyright 2010  Robert Guan 
 * All rights reserved.
 * to use is subject to license terms.
 *  
 */

#ifndef __AES_INTERNAL__
#define __AES_INTERNAL__




#define BLOCKBUFSZ  60


#ifdef _WIN64
#define ALIGN  __declspec(align(64))
#else
#define ALIGN  __declspec(align(32))
#endif


#ifndef uint8
typedef unsigned char uint8;
#endif

#ifndef uint16
typedef unsigned short uint16;
#endif 

#ifndef uint32
typedef unsigned int uint32;
#endif

#ifndef uint64
typedef unsigned __int64 uint64;
#endif



typedef struct _AESContext_
{
	uint32 AesEncKey[BLOCKBUFSZ];
	uint32 AesDecKey[BLOCKBUFSZ];
	uint32 InitialVector[4];
	uint32 iFeedBackSz;
	uint32 iKeyLength;  // 128,192,256
	uint32 iNk; // Number of 32-bit words comprising the Cipher Key
	uint32 iNr; // Number of rounds
} AESContext;


extern void AddRoundKey( uint32 * pInput , int iKeyIdx);
extern void  AddRoundKeyTo( uint32 * pInput , int iKeyIdx,uint32 * pOutput);


extern ALIGN const uint32 TestTable1[256];
extern ALIGN const uint32 TestTable2[256];
extern ALIGN const uint32 TestTable3[256];
extern ALIGN const uint32 TestTable4[256];


extern ALIGN const uint32 RevTable1[256];
extern ALIGN const uint32 RevTable2[256];
extern ALIGN const uint32 RevTable3[256];
extern ALIGN const uint32 RevTable4[256];


extern ALIGN const uint32 RevRawTable1[256];
extern ALIGN const uint32 RevRawTable2[256];
extern ALIGN const uint32 RevRawTable3[256];
extern ALIGN const uint32 RevRawTable4[256];

extern ALIGN const uint32 FSB[256];
extern ALIGN const uint32 FSB_8[256];
extern ALIGN const uint32 FSB_16[256];
extern ALIGN const uint32 FSB_24[256];


extern ALIGN const uint32 RSb[256];
extern ALIGN const uint32 RSb_8[256];
extern ALIGN const uint32 RSb_16[256];
extern ALIGN const uint32 RSb_24[256];

extern void InvMixColumns(uint32 * pState);
extern void InvMixColumnsDecKey(uint32 * pInput, uint32 * pOutput);



void AddCounter( uint8 * pCnt );

#ifndef XOR2_MACRO
#ifdef _WIN64
#define XOR2_MACRO(a,b,c)	XOR2_64((uint64 *) a , (uint64 *) b ,(uint64 *) c)
extern void XOR2_64(uint64 * src , uint64 * src2 ,uint64 * dest);
#else
#define XOR2_MACRO(a,b,c)	XOR2_32((uint32 *) a , (uint32 *) b ,(uint32 *) c)
extern void XOR2_32(uint32 * src , uint32 * src2 ,uint32 * dest);
#endif
#endif  // end of XOR2_MACRO




extern int padding(void * pToPad,int iSize);

typedef struct _reg_ {
	uint8 al;
	uint8 ah;
	uint8 eal;
	uint8 eah;
} regs;

typedef struct _reg32_ {
	uint16 al;
	uint16 ah;
} reg32;

typedef struct _reg64_ {
	uint16 al;
	uint16 ah;
	uint32 ax2;
} reg64;

#endif //__AES_INTERNAL__