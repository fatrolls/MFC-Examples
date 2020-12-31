/*
 *
 * Copyright 2010  Robert Guan 
 * All rights reserved.
 * to use is subject to license terms.
 *  
 */

#include "StdAfx.h"
#include "EfAES.h"
#include "AESInterns.h"





void InvMixColumnsDecKey(uint32 * pInput, uint32 * pOutput)
{
	uint32 a1,state; 

	state = pInput[0];
	a1 = RevRawTable1[ (byte) state ];
	a1^= RevRawTable2[ (( regs *) &state)->ah ];
	state = state >> 16;
	a1^= RevRawTable3[ (byte) state ];
	a1^= RevRawTable4[ (( regs *) &state)->ah ];
	pOutput[0] = a1;


	state = pInput[1];
	a1 = RevRawTable1[ (byte) state ];
	a1^= RevRawTable2[ (( regs *) &state)->ah ];
	state = state >> 16;
	a1^= RevRawTable3[ (byte) state ];
	a1^= RevRawTable4[ (( regs *) &state)->ah ];
	pOutput[1] = a1;


	state = pInput[2];
	a1 = RevRawTable1[ (byte) state ];
	a1^= RevRawTable2[ (( regs *) &state)->ah ];
	state = state >> 16;
	a1^= RevRawTable3[ (byte) state ];
	a1^= RevRawTable4[ (( regs *) &state)->ah ];
	pOutput[2] = a1;


	state = pInput[3];
	a1 = RevRawTable1[ (byte) state ];
	a1^= RevRawTable2[ (( regs *) &state)->ah ];
	state = state >> 16;
	a1^= RevRawTable3[ (byte) state ];
	a1^= RevRawTable4[ (( regs *) &state)->ah ];
	pOutput[3] = a1;

}



__forceinline void AES_DECRYPT( uint32 keyLength , uint32 * _pInput, uint32 * _pOutput, uint32 * local_key, uint32 * local_temp)  {
	
	register uint32 a1,a2,a3,a4,state;

	state        =_pInput[0]^local_key[0];
	local_temp[1]=_pInput[1]^local_key[1];
	local_temp[2]=_pInput[2]^local_key[2];
	local_temp[3]=_pInput[3]^local_key[3];


	a1=RevTable1[ (byte)state  ];
	a2=RevTable2[ (( regs *) &state)->ah ];
	state = state >> 16;
	a3=RevTable3[ (byte)state  ];
	a4=RevTable4[ (( regs *) &state)->ah  ];


	state = local_temp[1];
	a2^=RevTable1[ (byte)state  ];
	a3^=RevTable2[ (( regs *) &state)->ah ];
	state = state >> 16;
	a4^=RevTable3[ (byte)state  ];
	a1^=RevTable4[ (( regs *) &state)->ah  ];

	state = local_temp[2];
	a3^=RevTable1[ (byte)state  ];
	a4^=RevTable2[ (( regs *) &state)->ah ];
	state = state >> 16;
	a1^=RevTable3[ (byte)state  ];
	a2^=RevTable4[ (( regs *) &state)->ah  ];

	state = local_temp[3];
	a4^=RevTable1[ (byte)state  ];
	a1^=RevTable2[ (( regs *) &state)->ah ];
	state = state >> 16;
	a2^=RevTable3[ (byte)state  ];
	a3^=RevTable4[ (( regs *) &state)->ah  ];

	state        =a1^local_key[4];
	local_temp[1]=a2^local_key[5];
	local_temp[2]=a3^local_key[6];
	local_temp[3]=a4^local_key[7];

	a1=RevTable1[ (byte)state  ];
	a2=RevTable2[ (( regs *) &state)->ah ];
	state = state >> 16;
	a3=RevTable3[ (byte)state  ];
	a4=RevTable4[ (( regs *) &state)->ah  ];


	state = local_temp[1];
	a2^=RevTable1[ (byte)state  ];
	a3^=RevTable2[ (( regs *) &state)->ah ];
	state = state >> 16;
	a4^=RevTable3[ (byte)state  ];
	a1^=RevTable4[ (( regs *) &state)->ah  ];

	state = local_temp[2];
	a3^=RevTable1[ (byte)state  ];
	a4^=RevTable2[ (( regs *) &state)->ah ];
	state = state >> 16;
	a1^=RevTable3[ (byte)state  ];
	a2^=RevTable4[ (( regs *) &state)->ah  ];

	state = local_temp[3];
	a4^=RevTable1[ (byte)state  ];
	a1^=RevTable2[ (( regs *) &state)->ah ];
	state = state >> 16;
	a2^=RevTable3[ (byte)state  ];
	a3^=RevTable4[ (( regs *) &state)->ah  ];

	state        =a1^local_key[8];
	local_temp[1]=a2^local_key[9];
	local_temp[2]=a3^local_key[10];
	local_temp[3]=a4^local_key[11];

	a1=RevTable1[ (byte)state  ];
	a2=RevTable2[ (( regs *) &state)->ah ];
	state = state >> 16;
	a3=RevTable3[ (byte)state  ];
	a4=RevTable4[ (( regs *) &state)->ah  ];


	state = local_temp[1];
	a2^=RevTable1[ (byte)state  ];
	a3^=RevTable2[ (( regs *) &state)->ah ];
	state = state >> 16;
	a4^=RevTable3[ (byte)state  ];
	a1^=RevTable4[ (( regs *) &state)->ah  ];

	state = local_temp[2];
	a3^=RevTable1[ (byte)state  ];
	a4^=RevTable2[ (( regs *) &state)->ah ];
	state = state >> 16;
	a1^=RevTable3[ (byte)state  ];
	a2^=RevTable4[ (( regs *) &state)->ah  ];

	state = local_temp[3];
	a4^=RevTable1[ (byte)state  ];
	a1^=RevTable2[ (( regs *) &state)->ah ];
	state = state >> 16;
	a2^=RevTable3[ (byte)state  ];
	a3^=RevTable4[ (( regs *) &state)->ah  ];

	state        =a1^local_key[12];
	local_temp[1]=a2^local_key[13];
	local_temp[2]=a3^local_key[14];
	local_temp[3]=a4^local_key[15];

	a1=RevTable1[ (byte)state  ];
	a2=RevTable2[ (( regs *) &state)->ah ];
	state = state >> 16;
	a3=RevTable3[ (byte)state  ];
	a4=RevTable4[ (( regs *) &state)->ah  ];


	state = local_temp[1];
	a2^=RevTable1[ (byte)state  ];
	a3^=RevTable2[ (( regs *) &state)->ah ];
	state = state >> 16;
	a4^=RevTable3[ (byte)state  ];
	a1^=RevTable4[ (( regs *) &state)->ah  ];

	state = local_temp[2];
	a3^=RevTable1[ (byte)state  ];
	a4^=RevTable2[ (( regs *) &state)->ah ];
	state = state >> 16;
	a1^=RevTable3[ (byte)state  ];
	a2^=RevTable4[ (( regs *) &state)->ah  ];

	state = local_temp[3];
	a4^=RevTable1[ (byte)state  ];
	a1^=RevTable2[ (( regs *) &state)->ah ];
	state = state >> 16;
	a2^=RevTable3[ (byte)state  ];
	a3^=RevTable4[ (( regs *) &state)->ah  ];

	state        =a1^local_key[16];
	local_temp[1]=a2^local_key[17];
	local_temp[2]=a3^local_key[18];
	local_temp[3]=a4^local_key[19];

	a1=RevTable1[ (byte)state  ];
	a2=RevTable2[ (( regs *) &state)->ah ];
	state = state >> 16;
	a3=RevTable3[ (byte)state  ];
	a4=RevTable4[ (( regs *) &state)->ah  ];


	state = local_temp[1];
	a2^=RevTable1[ (byte)state  ];
	a3^=RevTable2[ (( regs *) &state)->ah ];
	state = state >> 16;
	a4^=RevTable3[ (byte)state  ];
	a1^=RevTable4[ (( regs *) &state)->ah  ];

	state = local_temp[2];
	a3^=RevTable1[ (byte)state  ];
	a4^=RevTable2[ (( regs *) &state)->ah ];
	state = state >> 16;
	a1^=RevTable3[ (byte)state  ];
	a2^=RevTable4[ (( regs *) &state)->ah  ];

	state = local_temp[3];
	a4^=RevTable1[ (byte)state  ];
	a1^=RevTable2[ (( regs *) &state)->ah ];
	state = state >> 16;
	a2^=RevTable3[ (byte)state  ];
	a3^=RevTable4[ (( regs *) &state)->ah  ];

	state        =a1^local_key[20];
	local_temp[1]=a2^local_key[21];
	local_temp[2]=a3^local_key[22];
	local_temp[3]=a4^local_key[23];

	a1=RevTable1[ (byte)state  ];
	a2=RevTable2[ (( regs *) &state)->ah ];
	state = state >> 16;
	a3=RevTable3[ (byte)state  ];
	a4=RevTable4[ (( regs *) &state)->ah  ];


	state = local_temp[1];
	a2^=RevTable1[ (byte)state  ];
	a3^=RevTable2[ (( regs *) &state)->ah ];
	state = state >> 16;
	a4^=RevTable3[ (byte)state  ];
	a1^=RevTable4[ (( regs *) &state)->ah  ];

	state = local_temp[2];
	a3^=RevTable1[ (byte)state  ];
	a4^=RevTable2[ (( regs *) &state)->ah ];
	state = state >> 16;
	a1^=RevTable3[ (byte)state  ];
	a2^=RevTable4[ (( regs *) &state)->ah  ];

	state = local_temp[3];
	a4^=RevTable1[ (byte)state  ];
	a1^=RevTable2[ (( regs *) &state)->ah ];
	state = state >> 16;
	a2^=RevTable3[ (byte)state  ];
	a3^=RevTable4[ (( regs *) &state)->ah  ];

	state        =a1^local_key[24];
	local_temp[1]=a2^local_key[25];
	local_temp[2]=a3^local_key[26];
	local_temp[3]=a4^local_key[27];

	a1=RevTable1[ (byte)state  ];
	a2=RevTable2[ (( regs *) &state)->ah ];
	state = state >> 16;
	a3=RevTable3[ (byte)state  ];
	a4=RevTable4[ (( regs *) &state)->ah  ];


	state = local_temp[1];
	a2^=RevTable1[ (byte)state  ];
	a3^=RevTable2[ (( regs *) &state)->ah ];
	state = state >> 16;
	a4^=RevTable3[ (byte)state  ];
	a1^=RevTable4[ (( regs *) &state)->ah  ];

	state = local_temp[2];
	a3^=RevTable1[ (byte)state  ];
	a4^=RevTable2[ (( regs *) &state)->ah ];
	state = state >> 16;
	a1^=RevTable3[ (byte)state  ];
	a2^=RevTable4[ (( regs *) &state)->ah  ];

	state = local_temp[3];
	a4^=RevTable1[ (byte)state  ];
	a1^=RevTable2[ (( regs *) &state)->ah ];
	state = state >> 16;
	a2^=RevTable3[ (byte)state  ];
	a3^=RevTable4[ (( regs *) &state)->ah  ];

	state        =a1^local_key[28];
	local_temp[1]=a2^local_key[29];
	local_temp[2]=a3^local_key[30];
	local_temp[3]=a4^local_key[31];


	a1=RevTable1[ (byte)state  ];
	a2=RevTable2[ (( regs *) &state)->ah ];
	state = state >> 16;
	a3=RevTable3[ (byte)state  ];
	a4=RevTable4[ (( regs *) &state)->ah  ];


	state = local_temp[1];
	a2^=RevTable1[ (byte)state  ];
	a3^=RevTable2[ (( regs *) &state)->ah ];
	state = state >> 16;
	a4^=RevTable3[ (byte)state  ];
	a1^=RevTable4[ (( regs *) &state)->ah  ];

	state = local_temp[2];
	a3^=RevTable1[ (byte)state  ];
	a4^=RevTable2[ (( regs *) &state)->ah ];
	state = state >> 16;
	a1^=RevTable3[ (byte)state  ];
	a2^=RevTable4[ (( regs *) &state)->ah  ];

	state = local_temp[3];
	a4^=RevTable1[ (byte)state  ];
	a1^=RevTable2[ (( regs *) &state)->ah ];
	state = state >> 16;
	a2^=RevTable3[ (byte)state  ];
	a3^=RevTable4[ (( regs *) &state)->ah  ];

	state        =a1^local_key[32];
	local_temp[1]=a2^local_key[33];
	local_temp[2]=a3^local_key[34];
	local_temp[3]=a4^local_key[35];

	a1=RevTable1[ (byte)state  ];
	a2=RevTable2[ (( regs *) &state)->ah ];
	state = state >> 16;
	a3=RevTable3[ (byte)state  ];
	a4=RevTable4[ (( regs *) &state)->ah  ];

	state = local_temp[1];
	a2^=RevTable1[ (byte)state  ];
	a3^=RevTable2[ (( regs *) &state)->ah ];
	state = state >> 16;
	a4^=RevTable3[ (byte)state  ];
	a1^=RevTable4[ (( regs *) &state)->ah  ];

	state = local_temp[2];
	a3^=RevTable1[ (byte)state  ];
	a4^=RevTable2[ (( regs *) &state)->ah ];
	state = state >> 16;
	a1^=RevTable3[ (byte)state  ];
	a2^=RevTable4[ (( regs *) &state)->ah  ];

	state = local_temp[3];
	a4^=RevTable1[ (byte)state  ];
	a1^=RevTable2[ (( regs *) &state)->ah ];
	state = state >> 16;
	a2^=RevTable3[ (byte)state  ];
	a3^=RevTable4[ (( regs *) &state)->ah  ];

	state        =a1^local_key[36];
	local_temp[1]=a2^local_key[37];
	local_temp[2]=a3^local_key[38];
	local_temp[3]=a4^local_key[39];




	if( keyLength == AES_KEY_128BIT ) {

		a1= RSb  [(byte) state];
		a2= RSb_8[(( regs *) &state)->ah];
		state = state >> 16;
		a3= RSb_16[(byte) state ];
		a4= RSb_24[(( regs *) &state)->ah];
	
		state = local_temp[1];
		a2|= RSb  [(byte) state];
		a3|= RSb_8[(( regs *) &state)->ah];
		state = state >> 16;
		a4|= RSb_16[(byte) state ];
		a1|= RSb_24[(( regs *) &state)->ah];

		state = local_temp[2];
		a3|= RSb  [(byte) state];
		a4|= RSb_8[(( regs *) &state)->ah];
		state = state >> 16;
		a1|= RSb_16[(byte) state ];
		a2|= RSb_24[(( regs *) &state)->ah];

		state = local_temp[3];
		a4|= RSb  [(byte) state]; 
		a1|= RSb_8[(( regs *) &state)->ah]; 
		state = state >> 16;
		a2|= RSb_16[(byte) state ]; 
		a3|= RSb_24[(( regs *) &state)->ah]; 

		_pOutput[0]= a1 ^ local_key[40];
		_pOutput[1]= a2 ^ local_key[41];
		_pOutput[2]= a3 ^ local_key[42];
		_pOutput[3]= a4 ^ local_key[43];
		return;
	}

	a1=RevTable1[ (byte)state  ];
	a2=RevTable2[ (( regs *) &state)->ah ];
	state = state >> 16;
	a3=RevTable3[ (byte)state  ];
	a4=RevTable4[ (( regs *) &state)->ah  ];

	state = local_temp[1];
	a2^=RevTable1[ (byte)state  ];
	a3^=RevTable2[ (( regs *) &state)->ah ];
	state = state >> 16;
	a4^=RevTable3[ (byte)state  ];
	a1^=RevTable4[ (( regs *) &state)->ah  ];

	state = local_temp[2];
	a3^=RevTable1[ (byte)state  ];
	a4^=RevTable2[ (( regs *) &state)->ah ];
	state = state >> 16;
	a1^=RevTable3[ (byte)state  ];
	a2^=RevTable4[ (( regs *) &state)->ah  ];

	state = local_temp[3];
	a4^=RevTable1[ (byte)state  ];
	a1^=RevTable2[ (( regs *) &state)->ah ];
	state = state >> 16;
	a2^=RevTable3[ (byte)state  ];
	a3^=RevTable4[ (( regs *) &state)->ah  ];


	state        =a1^local_key[40];
	local_temp[1]=a2^local_key[41];
	local_temp[2]=a3^local_key[42];
	local_temp[3]=a4^local_key[43];


	a1=RevTable1[ (byte)state  ];
	a2=RevTable2[ (( regs *) &state)->ah ];
	state = state >> 16;
	a3=RevTable3[ (byte)state  ];
	a4=RevTable4[ (( regs *) &state)->ah  ];

	state = local_temp[1];
	a2^=RevTable1[ (byte)state  ];
	a3^=RevTable2[ (( regs *) &state)->ah ];
	state = state >> 16;
	a4^=RevTable3[ (byte)state  ];
	a1^=RevTable4[ (( regs *) &state)->ah  ];

	state = local_temp[2];
	a3^=RevTable1[ (byte)state  ];
	a4^=RevTable2[ (( regs *) &state)->ah ];
	state = state >> 16;
	a1^=RevTable3[ (byte)state  ];
	a2^=RevTable4[ (( regs *) &state)->ah  ];

	state = local_temp[3];
	a4^=RevTable1[ (byte)state  ];
	a1^=RevTable2[ (( regs *) &state)->ah ];
	state = state >> 16;
	a2^=RevTable3[ (byte)state  ];
	a3^=RevTable4[ (( regs *) &state)->ah  ];

	state        =a1^local_key[44];
	local_temp[1]=a2^local_key[45];
	local_temp[2]=a3^local_key[46];
	local_temp[3]=a4^local_key[47];


	if( keyLength == AES_KEY_192BIT ) {
		a1= RSb  [(byte) state];
		a2= RSb_8[(( regs *) &state)->ah];
		state = state >> 16;
		a3= RSb_16[(byte) state ];
		a4= RSb_24[(( regs *) &state)->ah];
	
		state = local_temp[1];
		a2|= RSb  [(byte) state];
		a3|= RSb_8[(( regs *) &state)->ah];
		state = state >> 16;
		a4|= RSb_16[(byte) state ];
		a1|= RSb_24[(( regs *) &state)->ah];

		state = local_temp[2];
		a3|= RSb  [(byte) state];
		a4|= RSb_8[(( regs *) &state)->ah];
		state = state >> 16;
		a1|= RSb_16[(byte) state ];
		a2|= RSb_24[(( regs *) &state)->ah];

		state = local_temp[3];
		a4|= RSb  [(byte) state]; 
		a1|= RSb_8[(( regs *) &state)->ah]; 
		state = state >> 16;
		a2|= RSb_16[(byte) state ]; 
		a3|= RSb_24[(( regs *) &state)->ah]; 

		_pOutput[0]= a1 ^ local_key[48];
		_pOutput[1]= a2 ^ local_key[49];
		_pOutput[2]= a3 ^ local_key[50];
		_pOutput[3]= a4 ^ local_key[51];
		return;
	}

	a1=RevTable1[ (byte)state  ];
	a2=RevTable2[ (( regs *) &state)->ah ];
	state = state >> 16;
	a3=RevTable3[ (byte)state  ];
	a4=RevTable4[ (( regs *) &state)->ah  ];

	state = local_temp[1];
	a2^=RevTable1[ (byte)state  ];
	a3^=RevTable2[ (( regs *) &state)->ah ];
	state = state >> 16;
	a4^=RevTable3[ (byte)state  ];
	a1^=RevTable4[ (( regs *) &state)->ah  ];

	state = local_temp[2];
	a3^=RevTable1[ (byte)state  ];
	a4^=RevTable2[ (( regs *) &state)->ah ];
	state = state >> 16;
	a1^=RevTable3[ (byte)state  ];
	a2^=RevTable4[ (( regs *) &state)->ah  ];

	state = local_temp[3];
	a4^=RevTable1[ (byte)state  ];
	a1^=RevTable2[ (( regs *) &state)->ah ];
	state = state >> 16;
	a2^=RevTable3[ (byte)state  ];
	a3^=RevTable4[ (( regs *) &state)->ah  ];

	state        =a1^local_key[48];
	local_temp[1]=a2^local_key[49];
	local_temp[2]=a3^local_key[50];
	local_temp[3]=a4^local_key[51];


	a1=RevTable1[ (byte)state  ];
	a2=RevTable2[ (( regs *) &state)->ah ];
	state = state >> 16;
	a3=RevTable3[ (byte)state  ];
	a4=RevTable4[ (( regs *) &state)->ah  ];

	state = local_temp[1];
	a2^=RevTable1[ (byte)state  ];
	a3^=RevTable2[ (( regs *) &state)->ah ];
	state = state >> 16;
	a4^=RevTable3[ (byte)state  ];
	a1^=RevTable4[ (( regs *) &state)->ah  ];

	state = local_temp[2];
	a3^=RevTable1[ (byte)state  ];
	a4^=RevTable2[ (( regs *) &state)->ah ];
	state = state >> 16;
	a1^=RevTable3[ (byte)state  ];
	a2^=RevTable4[ (( regs *) &state)->ah  ];

	state = local_temp[3];
	a4^=RevTable1[ (byte)state  ];
	a1^=RevTable2[ (( regs *) &state)->ah ];
	state = state >> 16;
	a2^=RevTable3[ (byte)state  ];
	a3^=RevTable4[ (( regs *) &state)->ah  ];

	state        =a1^local_key[52];
	local_temp[1]=a2^local_key[53];
	local_temp[2]=a3^local_key[54];
	local_temp[3]=a4^local_key[55];


	a1= RSb  [(byte) state];
	a2= RSb_8[(( regs *) &state)->ah];
	state = state >> 16;
	a3= RSb_16[(byte) state ];
	a4= RSb_24[(( regs *) &state)->ah];
	
	state = local_temp[1];
	a2|= RSb  [(byte) state];
	a3|= RSb_8[(( regs *) &state)->ah];
	state = state >> 16;
	a4|= RSb_16[(byte) state ];
	a1|= RSb_24[(( regs *) &state)->ah];

	state = local_temp[2];
	a3|= RSb  [(byte) state];
	a4|= RSb_8[(( regs *) &state)->ah];
	state = state >> 16;
	a1|= RSb_16[(byte) state ];
	a2|= RSb_24[(( regs *) &state)->ah];

	state = local_temp[3];
	a4|= RSb  [(byte) state]; 
	a1|= RSb_8[(( regs *) &state)->ah]; 
	state = state >> 16;
	a2|= RSb_16[(byte) state ]; 
	a3|= RSb_24[(( regs *) &state)->ah]; 


	_pOutput[0]= a1 ^ local_key[56];
	_pOutput[1]= a2 ^ local_key[57];
	_pOutput[2]= a3 ^ local_key[58];
	_pOutput[3]= a4 ^ local_key[59];
}


void AesDecryptECB( AesCtx * pContext , void * pOutput, void * pInput ,int iSize )
{
	ALIGN uint32 local_temp[4];
	ALIGN uint32 local_key[BLOCKBUFSZ];
	//ALIGN uint32 state,a1,a2,a3,a4;	

	//iSize = padding( pInput , iSize ); , actually decode doesn't need padding.

	memcpy( local_key, ((AESContext*)pContext)->AesDecKey , BLOCKBUFSZ * 4);

	while(iSize>0)
	{			
		AES_DECRYPT( ((AESContext*)pContext)->iKeyLength , ((uint32 *)pInput) , ((uint32 *) pOutput) ,local_key, local_temp);
		pInput=(uint32 *) pInput + 4;
		pOutput=(uint32 *) pOutput + 4;
		iSize -= 16;
	}

}


// AES CBC mode 
extern void AesDecryptCBC_Normal( AesCtx * pContext, void * pOutput,void * pInput ,int iSize )
{

//	ALIGN uint32 a1,a2,a3,a4,state;
	ALIGN uint32 local_temp[4];
	ALIGN uint32 local_key[BLOCKBUFSZ];
	ALIGN uint32 * pInitialVector = ((AESContext*)pContext)->InitialVector;

	memcpy( local_key, ((AESContext*)pContext)->AesDecKey , BLOCKBUFSZ * 4);


	while(iSize>0)
	{
		
		AES_DECRYPT(((AESContext*)pContext)->iKeyLength , ((uint32 *) pInput),local_temp,local_key,local_temp);
		
		XOR2_MACRO( local_temp , pInitialVector ,  pOutput);

		pInitialVector =(uint32 *) pInput;
		
		pInput=(uint32 *) pInput + 4;
		pOutput=(uint32 *) pOutput + 4;
		iSize -= 16;
	}
	memcpy( ((AESContext*)pContext)->InitialVector, pInitialVector , 16);
}
extern void AesDecryptCBC_InPlace( AesCtx * pContext, void * pOutput,void * pInput ,int iSize )
{

	//ALIGN uint32 a1,a2,a3,a4,state;
	ALIGN uint32 local_temp[4];
	ALIGN uint32 local_key[BLOCKBUFSZ];
	ALIGN uint32 prev_vector[4];
	ALIGN uint32 reserved_input[4];

	//ALIGN uint32 * pInitialVector = ((AESContext*)pContext)->InitialVector;

	memcpy( local_key, ((AESContext*)pContext)->AesDecKey , BLOCKBUFSZ * 4);
	memcpy( prev_vector , ((AESContext*)pContext)->InitialVector , 16);


	while(iSize>0)
	{
		AES_DECRYPT(((AESContext*)pContext)->iKeyLength , ((uint32 *) pInput),local_temp,local_key,local_temp);

		reserved_input[0] = ((uint32 *) pInput)[0];
		reserved_input[1] = ((uint32 *) pInput)[1];
		reserved_input[2] = ((uint32 *) pInput)[2];
		reserved_input[3] = ((uint32 *) pInput)[3];
		
		XOR2_MACRO( local_temp , prev_vector ,  pOutput);

		prev_vector[0] = reserved_input[0];
		prev_vector[1] = reserved_input[1];
		prev_vector[2] = reserved_input[2];
		prev_vector[3] = reserved_input[3];
		
		pInput=(uint32 *) pInput + 4;
		pOutput=(uint32 *) pOutput + 4;
		iSize -= 16;
	}
	memcpy( ((AESContext*)pContext)->InitialVector, prev_vector , 16);
}

extern void AesDecryptCBC( AesCtx * pContext, void * pOutput,void * pInput ,int iSize )
{
	if( pInput == pOutput )
	{
		AesDecryptCBC_InPlace(pContext, pOutput, pInput ,iSize);
	} else {
		AesDecryptCBC_Normal(pContext, pOutput, pInput ,iSize);
	}
}


void AesDecryptPCBC_Normal( AesCtx * pContext,void * pOutput,void * pInput ,int iSize )
{
//	ALIGN uint32 a1,a2,a3,a4,state;
	ALIGN uint32 local_temp[4];
	ALIGN uint32 prev_vector[4];
	ALIGN uint32 local_key[BLOCKBUFSZ];

	memcpy(local_key,((AESContext*)pContext)->AesDecKey,BLOCKBUFSZ*4);
	memcpy(prev_vector,((AESContext*)pContext)->InitialVector, 16);

	while(iSize>0)
	{
		AES_DECRYPT( ((AESContext*)pContext)->iKeyLength , ((uint32*)pInput),local_temp,local_key,local_temp);
		XOR2_MACRO (prev_vector, local_temp ,pOutput);
		XOR2_MACRO (pInput     ,pOutput     ,prev_vector);

		pInput=(uint32*)pInput+4;
		pOutput=(uint32*)pOutput+4;
		iSize -= 16;
	}

	memcpy( ((AESContext*)pContext)->InitialVector , prev_vector, 16 );
}

void AesDecryptPCBC_InPlace( AesCtx * pContext,void * pOutput,void * pInput ,int iSize )
{
//	ALIGN uint32 a1,a2,a3,a4,state;
	ALIGN uint32 local_temp[4];
	ALIGN uint32 prev_vector[4];
	ALIGN uint32 reserved_input[4];
	ALIGN uint32 local_key[BLOCKBUFSZ];


	memcpy(local_key,((AESContext*)pContext)->AesDecKey,BLOCKBUFSZ*4);
	memcpy(prev_vector,((AESContext*)pContext)->InitialVector, 16);

	while(iSize>0)
	{

		AES_DECRYPT( ((AESContext*)pContext)->iKeyLength , ((uint32*)pInput),local_temp,local_key,local_temp);
		reserved_input[0]=((uint32*)pInput)[0];
		reserved_input[1]=((uint32*)pInput)[1];
		reserved_input[2]=((uint32*)pInput)[2];
		reserved_input[3]=((uint32*)pInput)[3];
		XOR2_MACRO (prev_vector, local_temp ,pOutput);
		XOR2_MACRO (reserved_input,pOutput, prev_vector);
	
		pInput=(uint32*)pInput+4;
		pOutput=(uint32*)pOutput+4;
		iSize -= 16;
	}

	memcpy( ((AESContext*)pContext)->InitialVector , prev_vector, 16 );
}



void AesDecryptPCBC( AesCtx * pContext,void * pOutput,void * pInput ,int iSize )
{
	iSize = padding( pInput , iSize );

	if( pInput == pOutput )
	{
		AesDecryptPCBC_InPlace(pContext,pOutput,pInput,iSize);
	} else {
		AesDecryptPCBC_Normal(pContext,pOutput,pInput,iSize);
	}
}                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                     