/**
 *
 * 文 件 名：oioic.c
 *
 * 描    述：OIOIC 节点的 .c 文件。
 *
 * 创 建 者：赵平智   <bruce.zhao.zpz@gmail.com>
 *
 * 创建日期：20050310
 *
 * 版    本：1.0.18
 *
 * 版权(C)2005-2011 赵平智。保留所有权利。　　　
 *
 * 备    注：
 *
 *
 * * 维护历史 *
 *
 *   <日期>              <修改者>
 *   <修改内容...>
 *
 **/

#include <stdlib.h>
#include <string.h> 
#include "oioic.h"


/*=====================+ Interface +=====================*/

/**
*
* 名称：OIOIC_Open
* 描述：Open接口。
* 参数：pCaller --- [IN] 来访者。
*/
static  RESULT  OIOIC_Open(OBJECT* This, const VR* pCaller)
{
	This->RefCnt++; 
	return R_P;
}

/**
*
* 名称：OIOIC_Input
* 描述：Input接口。
* 参数：IStrm --- [IN] 输入流；
*       Qty --- [IN] 输入的Byte数量；
*       pCaller --- [IN] 来访者。 
*/
static  RESULT  OIOIC_Input(OBJECT* This, BYTE* IStrm, BYTKTY Qty, const VR* pCaller)
{
	return RO_SBOOIX;
}

/**
*
* 名称：OIOIC_Output
* 描述：Output接口。
* 参数：OStrm --- [OUT] 输出流的流向；
*       Cty --- [IN] OStrm所指存储空间的容量；
*       pQty --- [OUT] 指向实际输出的Byte数量；
*       pCaller --- [IN] 来访者。
*/
static  RESULT  OIOIC_Output(OBJECT* This, BYTE* OStrm, BYTKTY Cty, BYTKTY* pQty, const VR* pCaller)
{	
   	return RO_SBOOIX;
}

/**
*
* 名称：OIOIC_IOput
* 描述：IOput接口。
* 参数：IStrm --- [IN] 输入流；
*       Qty --- [IN] 输入的Byte数量；
*       OStrm --- [OUT] 输出流的流向；
*       Cty --- [IN] OStrm所指存储空间的容量；
*       pQty --- [OUT] 指向实际输出的Byte数量；
*       pCaller --- [IN] 来访者。
*/
static  RESULT  OIOIC_IOput(OBJECT* This, BYTE* IStrm, BYTKTY Qty, BYTE* OStrm, BYTKTY Cty, BYTKTY* pQty, const VR* pCaller)
{
	return RO_SBOOIX;
}

/**
*
* 名称：OIOIC_Interact0
* 描述：Interact0接口。
* 参数：Act --- [IN] 交互行为；
*       pCaller --- [IN] 来访者。
*/
static  RESULT  OIOIC_Interact0(OBJECT* This, ACTION Act, const VR* pCaller)
{
	EM_OIOIC*  pem = (EM_OIOIC*)This->pEM;

	switch( Act )
	{
		case ASK_SHARED: /* 问共享么。*/
			if(pem->mds & MOD_SHARED) 
				return R_N;
			return R_P;
		case SET_SHARED: /* 设置共享。*/
			pem->mds &= ~MOD_SHARED;
			return R_P;
		case SET_UNSHARED: /* 设置非共享。*/
			pem->mds |= MOD_SHARED;
			return R_P;
		case SET_BLOCKI: /* 设置阻断输入。*/
			pem->mds &= ~MOD_BLOCKI;
			return R_P;
		case SET_UNBLOCKI: /* 设置非阻断输入。*/
			pem->mds |= MOD_BLOCKI;
			return R_P;
		case SET_BLOCKO: /* 设置阻断输出。*/
			pem->mds &= ~MOD_BLOCKO;
			return R_P;
		case SET_UNBLOCKO: /* 设置非阻断输出。*/
			pem->mds |= MOD_BLOCKO;
			return R_P;
		case CMD_RESET: /* 重置。*/
			pem->IQ.Front = pem->IQ.Rear = pem->IQ.Dtrm - 1;
			pem->IQ.Qty = pem->IQ.Lost = 0;
			pem->OQ.Front = pem->OQ.Rear = pem->OQ.Dtrm - 1;
			pem->OQ.Qty = pem->OQ.Lost = 0;
			return R_P;
		default:
			break;					
	}

	return RO_SBOOIX;			
}

/**
*
* 名称：OIOIC_Interact1
* 描述：Interact1接口。
* 参数：Act --- [IN] 交互行为；
*       OStrm --- [OUT] 输出流的流向；
*       Cty --- [IN] OStrm所指存储空间的容量；
*       pQty --- [OUT] 指向实际输出的Byte数量；
*       pCaller --- [IN] 来访者。
*/
static  RESULT  OIOIC_Interact1(OBJECT* This, ACTION Act, BYTE* OStrm, BYTKTY Cty, BYTKTY* pQty, const VR* pCaller)
{
	EM_OIOIC*   pem = (EM_OIOIC*)(This->pEM);

	switch( Act )
	{
		case GET_IQCTY: /* 获取IQ容量。*/
			assert( Cty >= sizeof(BYTKTY) );
			*((BYTKTY*)OStrm) = pem->IQ.Cty;
			*pQty = sizeof(BYTKTY); 
			return R_P;
		case GET_OQCTY: /* 获取OQ容量。*/
			assert( Cty >= sizeof(BYTKTY) );
			*((BYTKTY*)OStrm) = pem->OQ.Cty;
			*pQty = sizeof(BYTKTY); 
			return R_P;
		default:
			break;						
	}
	
	return RO_SBOOIX;
}

/**
*
* 名称：OIOIC_Interact2
* 描述：Interact2接口。
* 参数：Act --- [IN] 交互行为；
*       IStrm --- [IN] 输入流；
*       Qty --- [IN] 输入的Byte数量；
*       pCaller --- [IN] 来访者。
*/
static  RESULT  OIOIC_Interact2(OBJECT* This, ACTION  Act, BYTE* IStrm, BYTKTY Qty, const VR* pCaller)
{
	EM_OIOIC*   pem = (EM_OIOIC*)(This->pEM);

	switch( Act )
	{
		case SET_IQCTY: /* 设置IQ容量。*/
			assert( sizeof(BYTKTY) == Qty );
			if(pem->IQ.Dtrm != NULL)
				free(pem->IQ.Dtrm); 
			pem->IQ.Dtrm = (BYTE*)calloc(*((BYTKTY*)IStrm), 1);
			if( pem->IQ.Dtrm != NULL )
			{
				pem->IQ.Front = pem->IQ.Rear = pem->IQ.Dtrm - 1;
				pem->IQ.Cty = *((BYTKTY*)IStrm);
				pem->IQ.Qty = pem->IQ.Lost = 0;
				return R_P;
			}else 
			{ 
				return R_N;
			}
		case SET_OQCTY: /* 设置OQ容量。*/
			assert( sizeof(BYTKTY) == Qty );
			if(pem->OQ.Dtrm != NULL)
				free(pem->OQ.Dtrm); 
			pem->OQ.Dtrm = (BYTE*)calloc(*((BYTKTY*)IStrm), 1);
			if( pem->OQ.Dtrm != NULL ) 
			{
				pem->OQ.Front = pem->OQ.Rear = pem->OQ.Dtrm - 1;
				pem->OQ.Cty = *((BYTKTY*)IStrm);
				pem->OQ.Qty = pem->OQ.Lost = 0;
				return R_P; 
			}else 
			{ 
				return R_N; 
			}
		default:
			break;						
	}
	
	return RO_SBOOIX;
}

/**
*
* 名称：OIOIC_Interact3
* 描述：Interact3接口。
* 参数：Act --- [IN] 交互行为；
*       IStrm --- [IN] 输入流；
*       Qty --- [IN] 输入的Byte数量；
*       OStrm --- [OUT] 输出流的流向；
*       Cty --- [IN] OStrm所指存储空间的容量；
*       pQty --- [OUT] 指向实际输出的Byte数量；
*       pCaller --- [IN] 来访者。
*/
static  RESULT  OIOIC_Interact3(OBJECT* This, ACTION Act, BYTE* IStrm, BYTKTY Qty, BYTE* OStrm, BYTKTY Cty, BYTKTY* pQty, const VR* pCaller)
{	
	return RO_SBOOIX;
}

/**
*
* 名称：OIOIC_Close
* 描述：Close接口。
* 参数：pCaller --- [IN] 来访者。
*/
static  RESULT  OIOIC_Close(OBJECT* This, const VR* pCaller)
{
	This->RefCnt--; 
	return R_P;
}

/*========================+ TOG +========================*/

/**
*
* 名称：TOG_OIOIC
*/
VOID  TOG_OIOIC(OBJECT* pObj)
{
	pObj->Open = OIOIC_Open;
	pObj->Input = OIOIC_Input;
	pObj->Output = OIOIC_Output;
	pObj->IOput = OIOIC_IOput;
	pObj->Interact0 = OIOIC_Interact0;
	pObj->Interact1 = OIOIC_Interact1;
	pObj->Interact2 = OIOIC_Interact2;
	pObj->Interact3 = OIOIC_Interact3;
	pObj->Close = OIOIC_Close;
}

/*====================+ Function(s) +====================*/
/* ... */
