#include "stdafx.h"
#include "AesInterns.h"


void  AddRoundKeyTo( uint32 * pInput , int iKeyIdx, uint32 * AesEncKey, uint32 * pOutput)
{

	pOutput[0] = pInput[0] ^ AesEncKey[iKeyIdx];
	pOutput[1] = pInput[1] ^ AesEncKey[iKeyIdx+1];
	pOutput[2] = pInput[2] ^ AesEncKey[iKeyIdx+2];
	pOutput[3] = pInput[3] ^ AesEncKey[iKeyIdx+3];


}	



void  SubAndShiftAndMixAddRound(uint32 * temp, int idx , uint32 * AesEncKey)
{

#if 1
	ALIGN uint32 a1,a2,a3,a4;
	ALIGN uint32 state = temp[0];

	a1=TestTable1[ (byte)state  ];
	a4=TestTable2[ (( regs *) &state)->ah ]; 
	state = state >> 16;
	a3=TestTable3[ (byte)state  ];
	a2=TestTable4[ (( regs *) &state)->ah  ];

	state = temp[1];
	a2^=TestTable1[ (byte)state  ];
	a1^=TestTable2[ (( regs *) &state)->ah  ];
	state = state >> 16;
	a4^=TestTable3[(byte)state  ];
	a3^=TestTable4[ (( regs *) &state)->ah  ];

	state = temp[2];
	a3^=TestTable1[ (byte)state ];
	a2^=TestTable2[ (( regs *) &state)->ah ];
	state = state >> 16;
	a1^=TestTable3[ (byte)state ];
	a4^=TestTable4[ (( regs *) &state)->ah ];

	state = temp[3];
	
	a4^=TestTable1[ (byte)state ];
	a3^=TestTable2[ (( regs *) &state)->ah ];
	state = state >> 16;
	a2^=TestTable3[ (byte)state ];
	a1^=TestTable4[ (( regs *) &state)->ah ];

	temp[0]=a1^AesEncKey[idx];
	temp[1]=a2^AesEncKey[idx+1];
	temp[2]=a3^AesEncKey[idx+2];
	temp[3]=a4^AesEncKey[idx+3];
#endif 

#if 0
	ALIGN uint32 a1,a2,a3,a4;
	ALIGN uint32 state = temp[0];

	a1=TestTable1[ (byte)state  ];
	a4=TestTable2[ (( regs *) &state)->ah ]; 
	state = state >> 16;
	a3=TestTable3[ (byte)state  ];
	a2=TestTable4[ (( regs *) &state)->ah  ];

	state = temp[1];
	a2^=TestTable1[ (byte)state  ];
	a1^=TestTable2[ (( regs *) &state)->ah  ];
	state = state >> 16;
	a4^=TestTable3[(byte)state  ];
	a3^=TestTable4[ (( regs *) &state)->ah  ];

	state = temp[2];
	a3^=TestTable1[ (byte)state ];
	a2^=TestTable2[ (( regs *) &state)->ah ];
	state = state >> 16;
	a1^=TestTable3[ (byte)state ];
	a4^=TestTable4[ (( regs *) &state)->ah ];

	state = temp[3];
	
	a4^=TestTable1[ (byte)state ];
	temp[3]=a4^AesEncKey[idx+3];
	a3^=TestTable2[ (( regs *) &state)->ah ];
	temp[2]=a3^AesEncKey[idx+2];
	state = state >> 16;
	a2^=TestTable3[ (byte)state ];
	temp[1]=a2^AesEncKey[idx+1];
	a1^=TestTable4[ (( regs *) &state)->ah ];
	temp[0]=a1^AesEncKey[idx];

#endif 


#if 0
	//  temp1 N a1~a4, th
	//ALIGN uint32 a1,a2,a3,a4;
	ALIGN uint32 state = temp[0];

	temp1[0]=TestTable1[ (byte)state  ];
	temp1[3]=TestTable2[ (( regs *) &state)->ah ]; 
	state = state >> 16;
	temp1[2]=TestTable3[ (byte)state  ];
	temp1[1]=TestTable4[ (( regs *) &state)->ah  ];

	state = temp[1];
	temp1[1]^=TestTable1[ (byte)state  ];
	temp1[0]^=TestTable2[ (( regs *) &state)->ah  ];
	state = state >> 16;
	temp1[3]^=TestTable3[(byte)state  ];
	temp1[2]^=TestTable4[ (( regs *) &state)->ah  ];

	state = temp[2];
	temp1[2]^=TestTable1[ (byte)state ];
	temp1[1]^=TestTable2[ (( regs *) &state)->ah ];
	state = state >> 16;
	temp1[0]^=TestTable3[ (byte)state ];
	temp1[3]^=TestTable4[ (( regs *) &state)->ah ];

	state = temp[3];
	
	temp1[3]^=TestTable1[ (byte)state ];
	temp1[2]^=TestTable2[ (( regs *) &state)->ah ];
	state = state >> 16;
	temp1[1]^=TestTable3[ (byte)state ];
	temp1[0]^=TestTable4[ (( regs *) &state)->ah ];

	temp[0]=temp1[0]^AesEncKey[idx];
	temp[1]=temp1[1]^AesEncKey[idx+1];
	temp[2]=temp1[2]^AesEncKey[idx+2];
	temp[3]=temp1[3]^AesEncKey[idx+3];
#endif 


#if 0
	// it is not going to work
	ALIGN uint32 a14,a32,a21,a43;
	ALIGN uint32 state = temp[0];

	a14=TestTable12_32bit[ (uint16)state  ];
	state = state >> 16;
	a32=TestTable34_32bit[ state  ];

	state = temp[1];
	a21^=TestTable12_32bit[ (uint16)state  ];
	state = state >> 16;
	a43^=TestTable34_32bit[ state  ];

	state = temp[2];
	a32^=TestTable12_32bit[ (uint16)state ];
	state = state >> 16;
	a14^=TestTable34_32bit[ state ];

	state = temp[3];
	
	a43^=TestTable12_32bit[ (uint16)state ];
	state = state >> 16;
	a21^=TestTable34_32bit[ state ];

	temp[0]=a14^AesEncKey[idx];
	temp[1]=a21^AesEncKey[idx+1];
	temp[2]=a32^AesEncKey[idx+2];
	temp[3]=a43^AesEncKey[idx+3];
#endif 


#if 0
	// hΤ@ state1, A,yC@I
	ALIGN uint32 a1,a2,a3,a4;
	ALIGN uint32 state = temp[0];
	ALIGN uint32 state1 = temp[1];

	a1=TestTable1[ (byte)state  ];
	a4=TestTable2[ (( regs *) &state)->ah ]; 
	a2=TestTable1[ (byte)state1  ];
	a1^=TestTable2[ (( regs *) &state1)->ah  ];
	
	state = state >> 16;
	state1 = state1 >> 16;

	a3=TestTable3[ (byte)state  ];
	a2^=TestTable4[ (( regs *) &state)->ah  ];
	a4^=TestTable3[(byte)state1  ];
	a3^=TestTable4[ (( regs *) &state1)->ah  ];

	state = temp[2];
	state1 = temp[3];

	a3^=TestTable1[ (byte)state ];
	a2^=TestTable2[ (( regs *) &state)->ah ];
	a4^=TestTable1[ (byte)state1 ];
	a3^=TestTable2[ (( regs *) &state1)->ah ];

	state = state >> 16;
	state1 = state1 >> 16;

	a1^=TestTable3[ (byte)state ];
	a4^=TestTable4[ (( regs *) &state)->ah ];
	a2^=TestTable3[ (byte)state1 ];
	a1^=TestTable4[ (( regs *) &state1)->ah ];

	temp[0]=a1^AesEncKey[idx];
	temp[1]=a2^AesEncKey[idx+1];
	temp[2]=a3^AesEncKey[idx+2];
	temp[3]=a4^AesEncKey[idx+3];
#endif 


#if 0
	//  2-dimension array TestTableIdx
	ALIGN uint32 a1,a2,a3,a4;
	ALIGN uint32 state = temp[0];

	a1=TestTableIdx[0][ (byte)state  ];
	a4=TestTableIdx[1][ (( regs *) &state)->ah]; 
	state = state >> 16;
	a3=TestTableIdx[2][ (byte)state ];
	a2=TestTableIdx[3][ (( regs *) &state)->ah];

	state = temp[1];
	a2^=TestTableIdx[0][ (byte)state  ];
	a1^=TestTableIdx[1][ (( regs *) &state)->ah];
	state = state >> 16;
	a4^=TestTableIdx[2][(byte)state];
	a3^=TestTableIdx[3][ (( regs *) &state)->ah];

	state = temp[2];
	a3^=TestTableIdx[0][ (byte)state ];
	a2^=TestTableIdx[1][ (( regs *) &state)->ah];
	state = state >> 16;
	a1^=TestTableIdx[2][ (byte)state];
	a4^=TestTableIdx[3][ (( regs *) &state)->ah];

	state = temp[3];
	
	a4^=TestTableIdx[0][ (byte)state ];
	a3^=TestTableIdx[1][ (( regs *) &state)->ah];
	state = state >> 16;
	a2^=TestTableIdx[2][ (byte)state];
	a1^=TestTableIdx[3][ (( regs *) &state)->ah];

	temp[0]=a1^AesEncKey[idx];
	temp[1]=a2^AesEncKey[idx+1];
	temp[2]=a3^AesEncKey[idx+2];
	temp[3]=a4^AesEncKey[idx+3];

#endif 


#if 0
	// γ@ array TestTableALL
	ALIGN uint32 a1,a2,a3,a4;
	ALIGN uint32 state = temp[0];

	a1=TestTableALL[ (byte)state  ];
	a4=TestTableALL[ (( regs *) &state)->ah +256 ]; 
	state = state >> 16;
	a3=TestTableALL[ (byte)state +512 ];
	a2=TestTableALL[ (( regs *) &state)->ah + 768 ];

	state = temp[1];
	a2^=TestTableALL[ (byte)state  ];
	a1^=TestTableALL[ (( regs *) &state)->ah +256 ];
	state = state >> 16;
	a4^=TestTableALL[(byte)state  +512];
	a3^=TestTableALL[ (( regs *) &state)->ah + 768 ];

	state = temp[2];
	a3^=TestTableALL[ (byte)state ];
	a2^=TestTableALL[ (( regs *) &state)->ah +256];
	state = state >> 16;
	a1^=TestTableALL[ (byte)state +512];
	a4^=TestTableALL[ (( regs *) &state)->ah + 768];

	state = temp[3];
	
	a4^=TestTableALL[ (byte)state ];
	a3^=TestTableALL[ (( regs *) &state)->ah +256];
	state = state >> 16;
	a2^=TestTableALL[ (byte)state +512];
	a1^=TestTableALL[ (( regs *) &state)->ah + 768];

	temp[0]=a1^AesEncKey[idx];
	temp[1]=a2^AesEncKey[idx+1];
	temp[2]=a3^AesEncKey[idx+2];
	temp[3]=a4^AesEncKey[idx+3];
#endif 


#if 0
		// very slow if not working with 64bit OS 
	//ALIGN block_union bu;
	//ALIGN uint32 a1,a2,a3,a4;
	ALIGN uint64 a14,a32,a21,a43;
	ALIGN uint32 state = temp[0];

	a14=TestTable12[ (uint16)state  ];
	state = state >> 16;
	a32=TestTable34[ (uint16)state  ];

	state = temp[1];
	a21=TestTable12[ (uint16)state  ];
	state = state >> 16;
	a43=TestTable34[ (uint16)state  ];

	state = temp[2];
	a32^=TestTable12[ (uint16)state ];
	state = state >> 16;
	a14^=TestTable34[ (uint16)state ];

	state = temp[3];
	a43^=TestTable12[ (uint16)state ];
	state = state >> 16;
	a21^=TestTable34[ (uint16)state ];

	//bu.b32.a0 ^= bu.b32.a5;
	//bu.b32.a3 ^= bu.b32.a4;
	//bu.b32.a2 ^= bu.b32.a7;
	//bu.b32.a1 ^= bu.b32.a6;

	temp[0]=a21^AesEncKey[idx];
	temp[1]=a32^AesEncKey[idx+1];
	temp[2]=a43^AesEncKey[idx+2];
	temp[3]=a14^AesEncKey[idx+3];

#endif
}

// combine SubBytes and ShiftRows together
 void  SubAndShiftAndRound(uint32 * temp , int iKeyIdx ,uint32 * AesEncKey , uint32 * pOutput )
{




#if 1
	uint32 a1,a2,a3,a4;
	uint32 state;

	state = temp[0];
	a1= FSB  [(byte) state];
	a4= FSB_8[(( regs *) &state)->ah];
	state = state >> 16;
	a3= FSB_16[(byte) state ];
	a2= FSB_24[(( regs *) &state)->ah];
	
	state = temp[1];
	a2|= FSB  [(byte) state];
	a1|= FSB_8[(( regs *) &state)->ah];
	state = state >> 16;
	a4|= FSB_16[(byte) state ];
	a3|= FSB_24[(( regs *) &state)->ah];

	state = temp[2];
	a3|= FSB  [(byte) state];
	a2|= FSB_8[(( regs *) &state)->ah];
	state = state >> 16;
	a1|= FSB_16[(byte) state ];
	a4|= FSB_24[(( regs *) &state)->ah];

	state = temp[3];
	a4 |= FSB  [(byte) state]; 
	a3 |= FSB_8[(( regs *) &state)->ah]; 
	state = state >> 16;
	a2 |= FSB_16[(byte) state ]; 
	a1 |= FSB_24[(( regs *) &state)->ah]; 


	pOutput[0]= a1 ^ AesEncKey[iKeyIdx ];
	pOutput[1]= a2 ^ AesEncKey[iKeyIdx + 1];
	pOutput[2]= a3 ^ AesEncKey[iKeyIdx + 2];
	pOutput[3]= a4 ^ AesEncKey[iKeyIdx + 3];
#endif


#if 0	
	//uint32 a1,a2,a3,a4;
	uint32 state;

	state = temp[0];
	pOutput[0]= FSB  [(byte) state];
	pOutput[3]= FSB_8[(( regs *) &state)->ah];
	state = state >> 16;
	pOutput[2]= FSB_16[(byte) state ];
	pOutput[1]= FSB_24[(( regs *) &state)->ah];
	
	state = temp[1];
	pOutput[1]|= FSB  [(byte) state];
	pOutput[0]|= FSB_8[(( regs *) &state)->ah];
	state = state >> 16;
	pOutput[3]|= FSB_16[(byte) state ];
	pOutput[2]|= FSB_24[(( regs *) &state)->ah];

	state = temp[2];
	pOutput[2]|= FSB  [(byte) state];
	pOutput[1]|= FSB_8[(( regs *) &state)->ah];
	state = state >> 16;
	pOutput[0]|= FSB_16[(byte) state ];
	pOutput[3]|= FSB_24[(( regs *) &state)->ah];

	state = temp[3];
	pOutput[3] |= FSB  [(byte) state]; 
	pOutput[2] |= FSB_8[(( regs *) &state)->ah]; 
	state = state >> 16;
	pOutput[1] |= FSB_16[(byte) state ]; 
	pOutput[0] |= FSB_24[(( regs *) &state)->ah]; 


	pOutput[0] ^=  AesEncKey[iKeyIdx ];
	pOutput[1] ^=  AesEncKey[iKeyIdx + 1];
	pOutput[2] ^=  AesEncKey[iKeyIdx + 2];
	pOutput[3] ^=  AesEncKey[iKeyIdx + 3];
#endif



#if 0
	uint32 a1,a2,a3,a4;
	uint32 t1,t2,t3,t4;

	t1 = temp[0];
	t2 = temp[1];
	t3 = temp[2];
	t4 = temp[3];

	a1= FSB  [(byte) t1];
	a2= FSB  [(byte) t2];
	a3= FSB  [(byte) t3];
	a4= FSB  [(byte) t4]; 
	a4|= FSB_8[(( regs *) &t1)->ah];
	a1|= FSB_8[(( regs *) &t2)->ah];
	a2|= FSB_8[(( regs *) &t3)->ah];
	a3|= FSB_8[(( regs *) &t4)->ah]; 

	t1=t1>>16;
	t2=t2>>16;
	t3=t3>>16;
	t4=t4>>16;

	a3|= FSB_16[(byte) t1 ];
	a4|= FSB_16[(byte) t2 ];
	a1|= FSB_16[(byte) t3 ];
	a2|= FSB_16[(byte) t4 ]; 
	a2|= FSB_24[(( regs *) &t1)->ah];
	a3|= FSB_24[(( regs *) &t2)->ah];
	a4|= FSB_24[(( regs *) &t3)->ah];
	a1|= FSB_24[(( regs *) &t4)->ah]; 


	pOutput[0]= a1 ^ AesEncKey[iKeyIdx ];
	pOutput[1]= a2 ^ AesEncKey[iKeyIdx + 1];
	pOutput[2]= a3 ^ AesEncKey[iKeyIdx + 2];
	pOutput[3]= a4 ^ AesEncKey[iKeyIdx + 3];
#endif

#if 0	
	uint32 state;
	uint8 * pout = (uint8 *) pOutput;

	state = temp[0];
	pout[ 0]= u8_FSB  [(byte) state];
	pout[13]= u8_FSB[(( regs *) &state)->ah];
	state = state >> 16;
	pout[10]= u8_FSB[(byte) state ];
	pout[7]= u8_FSB[(( regs *) &state)->ah];
	
	state = temp[1];
	pout[4]= u8_FSB  [(byte) state];
	pout[1]= u8_FSB[(( regs *) &state)->ah];
	state = state >> 16;
	pout[14]= u8_FSB[(byte) state ];
	pout[11]= u8_FSB[(( regs *) &state)->ah];

	state = temp[2];
	pout[8]= u8_FSB  [(byte) state];
	pout[5]= u8_FSB[(( regs *) &state)->ah];
	state = state >> 16;
	pout[2]= u8_FSB[(byte) state ];
	pout[15]= u8_FSB[(( regs *) &state)->ah];

	state = temp[3];
	pout[12]= u8_FSB  [(byte) state];
	pout[9]= u8_FSB[(( regs *) &state)->ah];
	state = state >> 16;
	pout[6]= u8_FSB[(byte) state ];
	pout[3]= u8_FSB[(( regs *) &state)->ah];

	pOutput[0] ^=  AesEncKey[iKeyIdx ];
	pOutput[1] ^=  AesEncKey[iKeyIdx + 1];
	pOutput[2] ^=  AesEncKey[iKeyIdx + 2];
	pOutput[3] ^=  AesEncKey[iKeyIdx + 3];

#endif




#if 0
	block * pblk = (block *) temp;
	pOutput[0] = (FSB   [ pblk->a0 ]     |
				 FSB_8 [pblk->a5 ]     |
				 FSB_16[pblk->a10 ]     |
				 FSB_24[pblk->a15 ] ) ^AesEncKey[iKeyIdx ];

	pOutput[1] = (FSB[pblk->a4 ]     |
	             FSB_8[pblk->a9 ]     |
				 FSB_16[pblk->a14 ]     |
				 FSB_24[pblk->a3 ]    )^AesEncKey[iKeyIdx + 1];

	pOutput[2] = (FSB[pblk->a8 ]     |
				 FSB_8[pblk->a13 ]     |
				 FSB_16[pblk->a2 ]     |
				 FSB_24[pblk->a7 ]   )^AesEncKey[iKeyIdx + 2];

	pOutput[3] = (FSB[pblk->a12 ]     |
				 FSB_8[pblk->a1 ]     |
				 FSB_16[pblk->a6 ]     |
				 FSB_24[pblk->a11 ]   )^AesEncKey[iKeyIdx + 3];

#endif

#if 0	
	uint32 a1,a2,a3,a4;

	a1 = pState[0];
	a2 = pState[1];
	a3 = pState[2];
	a4 = pState[3];

	pOutput[0]= FSB[(a1 & 0xff)          ] | FSB_8[(a2 & 0xff00) >> 8     ] | FSB_16[(a3 & 0xff0000)  >>16] | FSB_24[(a4 & 0xff000000) >> 24] ;
	pOutput[1]= FSB[(a1 & 0xff000000)>>24] | FSB_8[(a2 & 0xff)            ] | FSB_16[(a3 & 0xff00)    >>8]  | FSB_24[(a4 & 0xff0000)>>16 ];
	pOutput[2]= FSB[(a1 & 0xff0000)>>16  ] | FSB_8[(a2 & 0xff000000) >> 24] | FSB_16[(a3 & 0xff)      ]     | FSB_24[(a4 & 0xff00)>>8 ];
	pOutput[3]= FSB[(a1 & 0xff00) >>8    ] | FSB_8[(a2 & 0xff0000) >> 16  ] | FSB_16[(a3 & 0xff000000)>>24] | FSB_24[(a4 & 0xff) ];
#endif

}



/*
inline void SubAndShiftAndRound( uint8 * pState ,uint32 * pRoundKey, uint32 * pOutput )
{

	pOutput[0] = (FSB[pState[0]]     |
				  FSB_8[pState[5]]   |
				  FSB_16[pState[10]] |
				  FSB_24[pState[15]]) ^ pRoundKey[0];

	pOutput[1] = (FSB[pState[4]]     |
	              FSB_8[pState[9]]   |
				  FSB_16[pState[14]] |
				  FSB_24[pState[3]])  ^ pRoundKey[1];

	pOutput[2] = (FSB[pState[8]]     |
				  FSB_8[pState[13]]  |
				  FSB_16[pState[2]]  |
				  FSB_24[pState[7]] ) ^ pRoundKey[2];

	pOutput[3] = (FSB[pState[12]]    |
				  FSB_8[pState[1]]   |
				  FSB_16[pState[6]]  |
				  FSB_24[pState[11]]) ^ pRoundKey[3];

}
*/

#if 0
//  the most original,just for reference
void SubAndShiftAndMixRound(uint8 * pState ,uint32 * pRoundKey , uint32 * p32Output)
{
	uint32 a1,a2,a3,a4; // use 32-bit is faster..

	a1=pState[0];
	a2=pState[5];
	a3=pState[10];
	a4=pState[15];

	*p32Output++ = ((SboxXTime2[a1] ^ SboxXTime3[a2] ^ FSB[a3]        ^ FSB[a4] ) |
				    ((FSB[a1]        ^ SboxXTime2[a2] ^ SboxXTime3[a3] ^ FSB[a4] ) << 8) |
				    ((FSB[a1]        ^ FSB[a2]        ^ SboxXTime2[a3] ^ SboxXTime3[a4]) << 16 )|
				    ((SboxXTime3[a1] ^ FSB[a2]        ^ FSB[a3]        ^ SboxXTime2[a4]) << 24) ) ^ *pRoundKey++;

	// mixing column 1
	a1=pState[4];
	a2=pState[9];
	a3=pState[14];
	a4=pState[3];

	*p32Output++ = ((SboxXTime2[a1] ^ SboxXTime3[a2] ^ FSB[a3]        ^ FSB[a4] ) |
				    ((FSB[a1]        ^ SboxXTime2[a2] ^ SboxXTime3[a3] ^ FSB[a4] ) << 8) |
				    ((FSB[a1]        ^ FSB[a2]        ^ SboxXTime2[a3] ^ SboxXTime3[a4]) << 16 )|
				    ((SboxXTime3[a1] ^ FSB[a2]        ^ FSB[a3]        ^ SboxXTime2[a4]) << 24) ) ^ *pRoundKey++;

	// mixing column 2
	a1=pState[8];
	a2=pState[13];
	a3=pState[2];
	a4=pState[7];
	*p32Output++ = ((SboxXTime2[a1] ^ SboxXTime3[a2] ^ FSB[a3]        ^ FSB[a4] ) |
				    ((FSB[a1]        ^ SboxXTime2[a2] ^ SboxXTime3[a3] ^ FSB[a4] ) << 8) |
				    ((FSB[a1]        ^ FSB[a2]        ^ SboxXTime2[a3] ^ SboxXTime3[a4]) << 16 )|
				    ((SboxXTime3[a1] ^ FSB[a2]        ^ FSB[a3]        ^ SboxXTime2[a4]) << 24) ) ^ *pRoundKey++;

	// mixing column 3
	a1=pState[12];
	a2=pState[1];
	a3=pState[6];
	a4=pState[11];
	*p32Output++ = ((SboxXTime2[a1] ^ SboxXTime3[a2] ^ FSB[a3]        ^ FSB[a4] ) |
				    ((FSB[a1]        ^ SboxXTime2[a2] ^ SboxXTime3[a3] ^ FSB[a4] ) << 8) |
				    ((FSB[a1]        ^ FSB[a2]        ^ SboxXTime2[a3] ^ SboxXTime3[a4]) << 16 )|
				    ((SboxXTime3[a1] ^ FSB[a2]        ^ FSB[a3]        ^ SboxXTime2[a4]) << 24) ) ^ *pRoundKey++;

}
#endif

#if 0
void aes_encrypt(uint32 * pInput , uint32 * pOutput)
{

	ALIGN uint32 a1,a2,a3,a4;
	ALIGN uint32 state;

	state   = pInput[0] ^ AesEncKey[0];
	temp[1] = pInput[1] ^ AesEncKey[1];
	temp[2] = pInput[2] ^ AesEncKey[2];
	temp[3] = pInput[3] ^ AesEncKey[3];


	a1=TestTable1[ (byte)state  ];
	a4=TestTable2[ (( regs *) &state)->ah ]; 
	state = state >> 16;
	a3=TestTable3[ (byte)state  ];
	a2=TestTable4[ (( regs *) &state)->ah  ];

	state = temp[1];
	a2^=TestTable1[ (byte)state  ];
	a1^=TestTable2[ (( regs *) &state)->ah  ];
	state = state >> 16;
	a4^=TestTable3[(byte)state  ];
	a3^=TestTable4[ (( regs *) &state)->ah  ];

	state = temp[2];
	a3^=TestTable1[ (byte)state ];
	a2^=TestTable2[ (( regs *) &state)->ah ];
	state = state >> 16;
	a1^=TestTable3[ (byte)state ];
	a4^=TestTable4[ (( regs *) &state)->ah ];

	state = temp[3];
	
	a4^=TestTable1[ (byte)state ];
	a3^=TestTable2[ (( regs *) &state)->ah ];
	state = state >> 16;
	a2^=TestTable3[ (byte)state ];
	a1^=TestTable4[ (( regs *) &state)->ah ];

	state=a1^AesEncKey[4];
	temp[1]=a2^AesEncKey[5];
	temp[2]=a3^AesEncKey[6];
	temp[3]=a4^AesEncKey[7];
//==============================================
	a1=TestTable1[ (byte)state  ];
	a4=TestTable2[ (( regs *) &state)->ah ]; 
	state = state >> 16;
	a3=TestTable3[ (byte)state  ];
	a2=TestTable4[ (( regs *) &state)->ah  ];

	state = temp[1];
	a2^=TestTable1[ (byte)state  ];
	a1^=TestTable2[ (( regs *) &state)->ah  ];
	state = state >> 16;
	a4^=TestTable3[(byte)state  ];
	a3^=TestTable4[ (( regs *) &state)->ah  ];

	state = temp[2];
	a3^=TestTable1[ (byte)state ];
	a2^=TestTable2[ (( regs *) &state)->ah ];
	state = state >> 16;
	a1^=TestTable3[ (byte)state ];
	a4^=TestTable4[ (( regs *) &state)->ah ];

	state = temp[3];
	
	a4^=TestTable1[ (byte)state ];
	a3^=TestTable2[ (( regs *) &state)->ah ];
	state = state >> 16;
	a2^=TestTable3[ (byte)state ];
	a1^=TestTable4[ (( regs *) &state)->ah ];

	state=a1^AesEncKey[8];
	temp[1]=a2^AesEncKey[9];
	temp[2]=a3^AesEncKey[10];
	temp[3]=a4^AesEncKey[11];

//===============================================
	a1=TestTable1[ (byte)state  ];
	a4=TestTable2[ (( regs *) &state)->ah ]; 
	state = state >> 16;
	a3=TestTable3[ (byte)state  ];
	a2=TestTable4[ (( regs *) &state)->ah  ];

	state = temp[1];
	a2^=TestTable1[ (byte)state  ];
	a1^=TestTable2[ (( regs *) &state)->ah  ];
	state = state >> 16;
	a4^=TestTable3[(byte)state  ];
	a3^=TestTable4[ (( regs *) &state)->ah  ];

	state = temp[2];
	a3^=TestTable1[ (byte)state ];
	a2^=TestTable2[ (( regs *) &state)->ah ];
	state = state >> 16;
	a1^=TestTable3[ (byte)state ];
	a4^=TestTable4[ (( regs *) &state)->ah ];

	state = temp[3];
	
	a4^=TestTable1[ (byte)state ];
	a3^=TestTable2[ (( regs *) &state)->ah ];
	state = state >> 16;
	a2^=TestTable3[ (byte)state ];
	a1^=TestTable4[ (( regs *) &state)->ah ];

	state=a1^AesEncKey[12];
	temp[1]=a2^AesEncKey[13];
	temp[2]=a3^AesEncKey[14];
	temp[3]=a4^AesEncKey[15];
//=======================================================

	a1=TestTable1[ (byte)state  ];
	a4=TestTable2[ (( regs *) &state)->ah ]; 
	state = state >> 16;
	a3=TestTable3[ (byte)state  ];
	a2=TestTable4[ (( regs *) &state)->ah  ];

	state = temp[1];
	a2^=TestTable1[ (byte)state  ];
	a1^=TestTable2[ (( regs *) &state)->ah  ];
	state = state >> 16;
	a4^=TestTable3[(byte)state  ];
	a3^=TestTable4[ (( regs *) &state)->ah  ];

	state = temp[2];
	a3^=TestTable1[ (byte)state ];
	a2^=TestTable2[ (( regs *) &state)->ah ];
	state = state >> 16;
	a1^=TestTable3[ (byte)state ];
	a4^=TestTable4[ (( regs *) &state)->ah ];

	state = temp[3];
	
	a4^=TestTable1[ (byte)state ];
	a3^=TestTable2[ (( regs *) &state)->ah ];
	state = state >> 16;
	a2^=TestTable3[ (byte)state ];
	a1^=TestTable4[ (( regs *) &state)->ah ];

	state =a1^AesEncKey[16];
	temp[1]=a2^AesEncKey[17];
	temp[2]=a3^AesEncKey[18];
	temp[3]=a4^AesEncKey[19];
//================================================
	a1=TestTable1[ (byte)state  ];
	a4=TestTable2[ (( regs *) &state)->ah ]; 
	state = state >> 16;
	a3=TestTable3[ (byte)state  ];
	a2=TestTable4[ (( regs *) &state)->ah  ];

	state = temp[1];
	a2^=TestTable1[ (byte)state  ];
	a1^=TestTable2[ (( regs *) &state)->ah  ];
	state = state >> 16;
	a4^=TestTable3[(byte)state  ];
	a3^=TestTable4[ (( regs *) &state)->ah  ];

	state = temp[2];
	a3^=TestTable1[ (byte)state ];
	a2^=TestTable2[ (( regs *) &state)->ah ];
	state = state >> 16;
	a1^=TestTable3[ (byte)state ];
	a4^=TestTable4[ (( regs *) &state)->ah ];

	state = temp[3];
	
	a4^=TestTable1[ (byte)state ];
	a3^=TestTable2[ (( regs *) &state)->ah ];
	state = state >> 16;
	a2^=TestTable3[ (byte)state ];
	a1^=TestTable4[ (( regs *) &state)->ah ];

	state=a1^AesEncKey[20];
	temp[1]=a2^AesEncKey[21];
	temp[2]=a3^AesEncKey[22];
	temp[3]=a4^AesEncKey[23];
//==================================================

	a1=TestTable1[ (byte)state  ];
	a4=TestTable2[ (( regs *) &state)->ah ]; 
	state = state >> 16;
	a3=TestTable3[ (byte)state  ];
	a2=TestTable4[ (( regs *) &state)->ah  ];

	state = temp[1];
	a2^=TestTable1[ (byte)state  ];
	a1^=TestTable2[ (( regs *) &state)->ah  ];
	state = state >> 16;
	a4^=TestTable3[(byte)state  ];
	a3^=TestTable4[ (( regs *) &state)->ah  ];

	state = temp[2];
	a3^=TestTable1[ (byte)state ];
	a2^=TestTable2[ (( regs *) &state)->ah ];
	state = state >> 16;
	a1^=TestTable3[ (byte)state ];
	a4^=TestTable4[ (( regs *) &state)->ah ];

	state = temp[3];
	
	a4^=TestTable1[ (byte)state ];
	a3^=TestTable2[ (( regs *) &state)->ah ];
	state = state >> 16;
	a2^=TestTable3[ (byte)state ];
	a1^=TestTable4[ (( regs *) &state)->ah ];

	state=a1^AesEncKey[24];
	temp[1]=a2^AesEncKey[25];
	temp[2]=a3^AesEncKey[26];
	temp[3]=a4^AesEncKey[27];
//====================================================

	a1=TestTable1[ (byte)state  ];
	a4=TestTable2[ (( regs *) &state)->ah ]; 
	state = state >> 16;
	a3=TestTable3[ (byte)state  ];
	a2=TestTable4[ (( regs *) &state)->ah  ];

	state = temp[1];
	a2^=TestTable1[ (byte)state  ];
	a1^=TestTable2[ (( regs *) &state)->ah  ];
	state = state >> 16;
	a4^=TestTable3[(byte)state  ];
	a3^=TestTable4[ (( regs *) &state)->ah  ];

	state = temp[2];
	a3^=TestTable1[ (byte)state ];
	a2^=TestTable2[ (( regs *) &state)->ah ];
	state = state >> 16;
	a1^=TestTable3[ (byte)state ];
	a4^=TestTable4[ (( regs *) &state)->ah ];

	state = temp[3];
	
	a4^=TestTable1[ (byte)state ];
	a3^=TestTable2[ (( regs *) &state)->ah ];
	state = state >> 16;
	a2^=TestTable3[ (byte)state ];
	a1^=TestTable4[ (( regs *) &state)->ah ];

	state=a1^AesEncKey[28];
	temp[1]=a2^AesEncKey[29];
	temp[2]=a3^AesEncKey[30];
	temp[3]=a4^AesEncKey[31];
//===============================================
	a1=TestTable1[ (byte)state  ];
	a4=TestTable2[ (( regs *) &state)->ah ]; 
	state = state >> 16;
	a3=TestTable3[ (byte)state  ];
	a2=TestTable4[ (( regs *) &state)->ah  ];

	state = temp[1];
	a2^=TestTable1[ (byte)state  ];
	a1^=TestTable2[ (( regs *) &state)->ah  ];
	state = state >> 16;
	a4^=TestTable3[(byte)state  ];
	a3^=TestTable4[ (( regs *) &state)->ah  ];

	state = temp[2];
	a3^=TestTable1[ (byte)state ];
	a2^=TestTable2[ (( regs *) &state)->ah ];
	state = state >> 16;
	a1^=TestTable3[ (byte)state ];
	a4^=TestTable4[ (( regs *) &state)->ah ];

	state = temp[3];
	
	a4^=TestTable1[ (byte)state ];
	a3^=TestTable2[ (( regs *) &state)->ah ];
	state = state >> 16;
	a2^=TestTable3[ (byte)state ];
	a1^=TestTable4[ (( regs *) &state)->ah ];

	state=a1^AesEncKey[32];
	temp[1]=a2^AesEncKey[33];
	temp[2]=a3^AesEncKey[34];
	temp[3]=a4^AesEncKey[35];
//===============================================
	a1=TestTable1[ (byte)state  ];
	a4=TestTable2[ (( regs *) &state)->ah ]; 
	state = state >> 16;
	a3=TestTable3[ (byte)state  ];
	a2=TestTable4[ (( regs *) &state)->ah  ];

	state = temp[1];
	a2^=TestTable1[ (byte)state  ];
	a1^=TestTable2[ (( regs *) &state)->ah  ];
	state = state >> 16;
	a4^=TestTable3[(byte)state  ];
	a3^=TestTable4[ (( regs *) &state)->ah  ];

	state = temp[2];
	a3^=TestTable1[ (byte)state ];
	a2^=TestTable2[ (( regs *) &state)->ah ];
	state = state >> 16;
	a1^=TestTable3[ (byte)state ];
	a4^=TestTable4[ (( regs *) &state)->ah ];

	state = temp[3];
	
	a4^=TestTable1[ (byte)state ];
	a3^=TestTable2[ (( regs *) &state)->ah ];
	state = state >> 16;
	a2^=TestTable3[ (byte)state ];
	a1^=TestTable4[ (( regs *) &state)->ah ];

	state=a1^AesEncKey[36];
	temp[1]=a2^AesEncKey[37];
	temp[2]=a3^AesEncKey[38];
	temp[3]=a4^AesEncKey[39];
//===============================================

	a1= FSB  [(byte) state];
	a4= FSB_8[(( regs *) &state)->ah];
	state = state >> 16;
	a3= FSB_16[(byte) state ];
	a2= FSB_24[(( regs *) &state)->ah];
	
	state = temp[1];
	a2|= FSB  [(byte) state];
	a1|= FSB_8[(( regs *) &state)->ah];
	state = state >> 16;
	a4|= FSB_16[(byte) state ];
	a3|= FSB_24[(( regs *) &state)->ah];

	state = temp[2];
	a3|= FSB  [(byte) state];
	a2|= FSB_8[(( regs *) &state)->ah];
	state = state >> 16;
	a1|= FSB_16[(byte) state ];
	a4|= FSB_24[(( regs *) &state)->ah];

	state = temp[3];
	a4 |= FSB  [(byte) state]; 
	a3 |= FSB_8[(( regs *) &state)->ah]; 
	state = state >> 16;
	a2 |= FSB_16[(byte) state ]; 
	a1 |= FSB_24[(( regs *) &state)->ah]; 


	pOutput[0]= a1 ^ AesEncKey[40 ];
	pOutput[1]= a2 ^ AesEncKey[41];
	pOutput[2]= a3 ^ AesEncKey[42];
	pOutput[3]= a4 ^ AesEncKey[43];


}

#endif




void InvShiftRows(uint32 * pInput)
{
	uint8 * pSource = (uint8 *) pInput;
	uint8 pTarget[16];

	pTarget[0 ]=pSource[0];
	pTarget[1 ]=pSource[13];
	pTarget[2 ]=pSource[10];
	pTarget[3 ]=pSource[7];
	pTarget[4 ]=pSource[4];
	pTarget[5 ]=pSource[1];
	pTarget[6 ]=pSource[14];
	pTarget[7 ]=pSource[11];
	pTarget[8 ]=pSource[8];
	pTarget[9 ]=pSource[5];
	pTarget[10]=pSource[2];
	pTarget[11]=pSource[15];
	pTarget[12]=pSource[12];
	pTarget[13]=pSource[9];
	pTarget[14]=pSource[6];
	pTarget[15]=pSource[3];

	memcpy( pInput, pTarget,  16);
}

void InvSubBytes(uint32 * pState)
{
	uint8 * pSource = (uint8 *) pState;
	uint8 * pTarget = (uint8 *) pState;
	for(int i=0;i<16;i++)
	{
		pTarget[i] = RSb[ pSource[i] ] ;
	}
}


void InvSubShiftRows(uint32 * pInput , int idx,uint32 * AesDecKey, uint32 * pOutput)
{
	uint32 a1,a2,a3,a4;

	uint32 state;

	state = pInput[0];
	a1= RSb  [(byte) state];
	a2= RSb_8[(( regs *) &state)->ah];
	state = state >> 16;
	a3= RSb_16[(byte) state ];
	a4= RSb_24[(( regs *) &state)->ah];
	
	state = pInput[1];
	a2|= RSb  [(byte) state];
	a3|= RSb_8[(( regs *) &state)->ah];
	state = state >> 16;
	a4|= RSb_16[(byte) state ];
	a1|= RSb_24[(( regs *) &state)->ah];

	state = pInput[2];
	a3|= RSb  [(byte) state];
	a4|= RSb_8[(( regs *) &state)->ah];
	state = state >> 16;
	a1|= RSb_16[(byte) state ];
	a2|= RSb_24[(( regs *) &state)->ah];

	state = pInput[3];
	a4 |= RSb  [(byte) state]; 
	a1 |= RSb_8[(( regs *) &state)->ah]; 
	state = state >> 16;
	a2 |= RSb_16[(byte) state ]; 
	a3 |= RSb_24[(( regs *) &state)->ah]; 


	pOutput[0]= a1 ^ AesDecKey[idx ];
	pOutput[1]= a2 ^ AesDecKey[idx + 1];
	pOutput[2]= a3 ^ AesDecKey[idx + 2];
	pOutput[3]= a4 ^ AesDecKey[idx + 3];

}



void InvMixColumns(uint32 * pState)
{
	uint32 a1,a2,a3,a4; // use 32-bit is faster..
	uint32 state;

#if 1
	state=pState[0];

	a1=RevTable1[ (byte)state  ];
	a2=RevTable2[ (( regs *) &state)->ah ]; // the compiler will do better optimize
	state = state >> 16;
	a3=RevTable3[ (byte)state  ];
	a4=RevTable4[ (( regs *) &state)->ah  ];


	state = pState[1];
	a2^=RevTable1[ (byte)state  ];
	a3^=RevTable2[ (( regs *) &state)->ah ]; // the compiler will do better optimize
	state = state >> 16;
	a4^=RevTable3[ (byte)state  ];
	a1^=RevTable4[ (( regs *) &state)->ah  ];

	state = pState[2];
	a3^=RevTable1[ (byte)state  ];
	a4^=RevTable2[ (( regs *) &state)->ah ]; // the compiler will do better optimize
	state = state >> 16;
	a1^=RevTable3[ (byte)state  ];
	a2^=RevTable4[ (( regs *) &state)->ah  ];

	state = pState[3];
	a4^=RevTable1[ (byte)state  ];
	a1^=RevTable2[ (( regs *) &state)->ah ]; // the compiler will do better optimize
	state = state >> 16;
	a2^=RevTable3[ (byte)state  ];
	a3^=RevTable4[ (( regs *) &state)->ah  ];

	pState[0]=a1;
	pState[1]=a2;
	pState[2]=a3;
	pState[3]=a4;

#endif

	
	/*

	// original form
	uint8 * tmp  = (uint8 *) temp;
	a1=tmp[0];
	a2=tmp[1];
	a3=tmp[2];
	a4=tmp[3];

	temp1[0] =      ((RSBXTime_e[a1] ^ RSBXTime_b[a2] ^ RSBXTime_d[a3] ^ RSBXTime_9[a4] ) |
				    ((RSBXTime_9[a1] ^ RSBXTime_e[a2] ^ RSBXTime_b[a3] ^ RSBXTime_d[a4] ) << 8) |
				    ((RSBXTime_d[a1] ^ RSBXTime_9[a2] ^ RSBXTime_e[a3] ^ RSBXTime_b[a4]) << 16 )|
				    ((RSBXTime_b[a1] ^ RSBXTime_d[a2] ^ RSBXTime_9[a3] ^ RSBXTime_e[a4]) << 24) );

	*/
}

void AddRoundDecKeyTo(uint32 * pInput,int idx,uint32 * AesDecKey,uint32 * pOutput)
{
	pOutput[0]=pInput[0]^AesDecKey[idx];
	pOutput[1]=pInput[1]^AesDecKey[idx+1];
	pOutput[2]=pInput[2]^AesDecKey[idx+2];
	pOutput[3]=pInput[3]^AesDecKey[idx+3];
}

/*
void aes_decrypt(uint32 * pInput , uint32 * pOutput, uint32 * pKey)
{
	uint32 temp[4];

	AddRoundDecKeyTo(  pInput ,0 ,pKey ,temp);

	for(int round = 1 ; round < Nr ; round++)
	{
		InvMixColumns(temp);
		AddRoundDecKeyTo(temp, Nb * round ,pKey , temp);
	}
	InvSubShiftRows(temp , 40 ,pKey,pOutput);
}
*/

void  aes_encrypt( uint32 * pInput , uint32 * pOutput, uint32 * pKey )
{
//	ALIGN uint32 a1,a2,a3,a4,state;
	ALIGN uint32 temp[4];

	AddRoundKeyTo (pInput , 0, pKey  , temp);
	
	SubAndShiftAndMixAddRound(temp, 4 ,pKey);
	SubAndShiftAndMixAddRound(temp, 8 ,pKey);
	SubAndShiftAndMixAddRound(temp, 12,pKey);
	SubAndShiftAndMixAddRound(temp, 16,pKey);
	SubAndShiftAndMixAddRound(temp, 20,pKey);
	SubAndShiftAndMixAddRound(temp, 24,pKey);
	SubAndShiftAndMixAddRound(temp, 28,pKey);
	SubAndShiftAndMixAddRound(temp, 32,pKey);
	SubAndShiftAndMixAddRound(temp, 36,pKey);
	SubAndShiftAndMixAddRound(temp, 40,pKey);
	SubAndShiftAndMixAddRound(temp, 44,pKey);
	SubAndShiftAndMixAddRound(temp, 48,pKey);
	SubAndShiftAndMixAddRound(temp, 52,pKey);

	SubAndShiftAndRound(temp, 56 ,pKey, pOutput);
}



                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            