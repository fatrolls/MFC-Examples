/**
 *
 * 文 件 名：o.c
 *
 * 描    述：o.c 文件。
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
#include "o.h"
#include "oioic.h"


/*=============+ InitAIBofND & InitABNofND +=============*/

/* 注：InitAIBofND 和 InitABNofND只由CRT函数调用。*/

/**
*
* 名称：InitAIBofND
* 描述：初始化ND的AIB。
* 参数：pND --- [IN] ND指针；
*       pMsn --- [IN] IB的MSN数组；
*       nib --- [IN] pMsn所指数组的元素个数，即IB的数量。
* 备注：1. 只由CRT函数调用。
*       2. 注意，pMsn所指数组元素的排序决定了IB的访问顺序。
*/
VOID  InitAIBofND(OBJECT* pND, MLDSN* pMsn, NUMIB nib)
{
	NUMND   i;
	NUMIB   j;
	
	pND->NIB = nib;
	
	while(nib)
	{
		j = pND->NIB-nib;
		for(i=1; i<pND->NND; i++)
		{
			if( *(pMsn+j) == (pND->po_AND+i)->MSN )
			{
				*(pND->ppo_AIB+j) = pND->po_AND+i;
				break;
			}
		}
		nib--;
	}
}	

/**
*
* 名称：InitABNofND
* 描述：初始化ND的ABN。
* 参数：pND --- [IN] ND指针；
*       pMsn --- [IN] BN的MSN数组；
*       nbn --- [IN] pMsn所指数组的元素个数，即BN的数量。
* 备注：只由CRT函数调用。
*/
VOID  InitABNofND(OBJECT* pND, MLDSN* pMsn, NUMBN nbn)
{
	NUMND  i;
	NUMBN  j;
	
	pND->NBN = nbn;
	
	while(nbn)
	{
		j = pND->NBN-nbn;
		for(i=1; i<pND->NND; i++)
		{
			if( *(pMsn+j) == (pND->po_AND+i)->MSN )
			{
				*(pND->ppo_ABN+j) = pND->po_AND+i;
				break;
			}
		}
		nbn--;
	}
}

/*=============+ CallerCome & CallerLeave +==============*/

/* 注：不允许外面使用 CallerCome 和 CallerLeave。*/

/**
*
* 名称：CallerCome
* 描述：来访者来访，登记来访记录。
* 参数：pND --- [IN] ND地址；
*       pCaller --- [IN] 来访者。
* 备注：不允许外面使用。
*/
RESULT  CallerCome(OBJECT* pND, const VR* pCaller)
{    
	NUMCS   i;
	VR*     pVR; 
	
	/* 先检查有没有这个VR。 */
	for(i=0; i<pND->NCS; i++)
	{
		pVR = pND->pvr_ACS+i;
		if((pVR->cr == pCaller->cr) && (pVR->mr == pCaller->mr))
			return RN_HASVR; /* 已经有这个VR了。*/
	}

	/* 加上这个VR。 */
	for(i=0; i<pND->NCS; i++)
	{
		pVR = pND->pvr_ACS+i;
		if( 0 == pVR->cr )
		{
			*pVR = *pCaller;
			return R_P;
		}
	}
		
	return R_N;  
}

/**
*
* 名称：CallerLeave
* 描述：来访者离开，清除来访记录。
* 参数：pND --- [IN] ND地址；
*       pCaller --- [IN] 来访者。
* 备注：不允许外面使用。
*/
RESULT  CallerLeave(OBJECT* pND, const VR* pCaller)
{
	NUMBN  i;
	NUMCS  j;
	VR*    pVR;
	
	/* 首先ND的BN */
	for(i=0; i<pND->NBN; i++)
	{
		for(j=0; j<(*(pND->ppo_ABN+i))->NCS; j++)
		{
			pVR = (*(pND->ppo_ABN+i))->pvr_ACS+j;
		  	if((pVR->cr == pCaller->cr) && (pVR->mr == pCaller->mr))
				pVR->cr = pVR->mr = 0;
		}
	}
	
	/* 然后ND自己 */
	for(j=0; j<pND->NCS; j++)
	{
		pVR = pND->pvr_ACS+j;
		if((pVR->cr == pCaller->cr) && (pVR->mr == pCaller->mr))
			pVR->cr = pVR->mr = 0;
	} 

	return R_P;
}

/*==================+ Enqueue & Dequeue +================*/

/**
*
* 名称：Enqueue
* 描述：向指定的队列入列指定数量的Byte。
* 参数：IData --- [IN] 入列数据；
*       Qty --- [IN] 入列的Byte数量。
*/
RESULT  Enqueue(QUEUE* pq, BYTE* IData, BYTKTY Qty)
{
    BYTE*     newRear;  /* 入列成功后pq->Rear应该所处的位置。*/
	BYTKTY    ctyFree, qtyEnq;
	
	assert( pq != NULL );
	assert( IData != NULL );
	
	ctyFree = pq->Cty - pq->Qty;
	qtyEnq = (ctyFree > Qty) ? Qty : ctyFree;

	
	if( 0 == qtyEnq )
	{
		if( Qty > 0 )
		{
			pq->Lost = Qty;  /* 丢失了 Qty 个Byte ！*/
			return RN_LOST;
		}

		return RO_VAINLY;
	}

		
	newRear = pq->Dtrm + (pq->Rear + qtyEnq - pq->Dtrm ) % pq->Cty; 
	if(newRear > pq->Rear) /* 如果入列成功，pq->Rear不须循环？*/
	{
		memcpy(pq->Rear+1, IData, qtyEnq);
	}else /* 如果入列成功，pq->Rear须循环。*/
	{	
		BYTKTY   qty1, qty2;
		qty1 = pq->Dtrm + pq->Cty - pq->Rear - 1;
		if(qty1 > 0)
			memcpy(pq->Rear+1, IData, qty1);
		qty2 = qtyEnq - qty1;
		memcpy(pq->Dtrm, IData + qty1, qty2);
	}

	pq->Rear = newRear;
	pq->Qty += qtyEnq;

	if(pq->Dtrm-1 == pq->Front)
		pq->Front = pq->Dtrm;

	if(ctyFree < Qty)
	{
	   pq->Lost = Qty - ctyFree;  /* 丢失了 Qty - ctyFree 个Byte ！*/
	   return RN_LOST;
	}
	
	return R_P;
}

/**
*
* 名称：Dequeue
* 描述：从指定队列出列Byte。
* 参数：OData --- [OUT] 出列数据的存储位置；
*       Cty --- [IN] OData所指存储空间的容量；
*       pQty --- [OUT] 指向实际出列的Byte数量。
*/
RESULT  Dequeue(QUEUE* pq, BYTE* OData, BYTKTY Cty, BYTKTY* pQty)
{
	BYTE*    newFront;  /* 出列成功后pq->Front应该所处的位置。*/
    BYTKTY   qtyDeq;  /* 实际出列数据量。*/

	assert( pq != NULL );
	assert( OData != NULL );
	assert( Cty != 0 );
	assert( pQty != NULL );
	
	*pQty = 0; /* 先将出列数置0。*/
	
	if( pq->Qty != 0 )
	{
		qtyDeq = (Cty > pq->Qty) ? pq->Qty : Cty;

		newFront = pq->Dtrm + (pq->Front + qtyDeq - pq->Dtrm) % pq->Cty;
		if(newFront > pq->Front) /* 出列后，pq->Front不须循环? */
		{
			memcpy(OData, pq->Front, qtyDeq);
		}else /* 出列后，pq->Front须循环。*/
		{
			BYTKTY   qty1, qty2;
			qty1 = pq->Dtrm + pq->Cty - pq->Front;
			qty2 = qtyDeq - qty1;
			memcpy(OData, pq->Front, qty1);
			memcpy(OData + qty1, pq->Dtrm, qty2);
		}

		pq->Qty -= qtyDeq;

		if(0 == pq->Qty)
			pq->Front = pq->Rear = pq->Dtrm -1;
		else
			pq->Front = newFront;

	}else
	{
	   return RO_VAINLY;
	}

	*pQty = qtyDeq;
	
	if(pq->Lost > 0)
	{
	   pq->Lost = 0;
	   return  RN_LOST;
	}	

	return R_P;
} 

/*=================+ GetBN & GetEMofBN +=================*/

/**
*
* 名称：GetBN
* 描述：获取指定BN的地址。
* 参数：pND --- [IN] ND指针；
*       msn --- [IN] BN的M。
* 返回：BN的指针。
*/
OBJECT*  GetBN(OBJECT* pND, MLDSN msn)
{
	NUMBN   i;
	
	assert( pND != NULL );

	for(i=0; i<pND->NBN; i++)
	{
		if( msn == (*(pND->ppo_ABN+i))->MSN )
			return  *(pND->ppo_ABN+i);
	}
	
	return NULL;  /* 没有这个BN。*/
}

/**
*
* 名称：GetEMofBN
* 描述：获取指定BN的EM地址。
* 参数：pND --- [IN] ND指针；
*       msn --- [IN] BN的M。
* 返回：EM的指针。
*/
EM*  GetEMofBN(OBJECT* pND, MLDSN msn)
{
	NUMBN   i;
	
	assert( pND != NULL );

	for(i=0; i<pND->NBN; i++)
	{
		if( msn == (*(pND->ppo_ABN+i))->MSN )
			return  (*(pND->ppo_ABN+i))->pEM;
	}
	
	return NULL; 
}	

/*===================+ GetIQ & GetOQ +===================*/

/**
*
* 名称：GetIQ
* 描述：获取节点的IQ指针。
* 参数：pND --- [IN] 节点指针。
* 返回：IQ的指针。
*/
QUEUE*  GetIQ(OBJECT* pND)
{
	NUMBN   i;
	
	assert( pND != NULL );

	for(i=0; i<pND->NBN; i++)
	{
		if( MSN_OIOIC == (*(pND->ppo_ABN+i))->MSN )
			return  &((EM_OIOIC*)((*(pND->ppo_ABN+i))->pEM))->IQ;
	}
	
	return NULL; 
}

/**
*
* 名称：GetOQ
* 描述：获取节点的OQ指针。
* 参数：pND --- [IN] 节点指针。
* 返回：OQ的指针。
*/
QUEUE*  GetOQ(OBJECT* pND)
{
	NUMBN   i;
	
	assert( pND != NULL );

	for(i=0; i<pND->NBN; i++)
	{
		if( MSN_OIOIC == (*(pND->ppo_ABN+i))->MSN )
			return  &((EM_OIOIC*)((*(pND->ppo_ABN+i))->pEM))->OQ;
	}
	
	return NULL; 
}


/*==================+  非内联VO函数  +===================*/

/* 注意：内联VO函数和非内联VO函数的功能是完全相同的。*/


#if INLINE_VOFUNCTION == 0

/**
*
* 名称：VO_Open
* 描述：接口Open的VO函数。
* 参数：pObject --- [IN] 指向对象；
*       pCaller --- [IN] 来访者。
*/    	             
RESULT  VO_Open(OBJECT* pObject, const VR* pCaller)
{
	extern  RESULT  CallerCome(OBJECT* pND, const VR* pCaller);
	extern  RESULT  CallerLeave(OBJECT* pND, const VR* pCaller);

	RESULT  ir = R_O;

	assert( pObject != NULL );
	assert( pCaller->cr != 0 );
	assert( pCaller->mr != 0 );
	
	if( R_P == CallerCome(pObject, pCaller) )
	{
		ir = pObject->Open(pObject, pCaller);
		CallerLeave(pObject, pCaller);
	}else { ir = R_N; }
	
	return ir;
}
       
/**
*
* 名称：VO_Input
* 描述：接口Input的VO函数。
* 参数：pObject --- [IN] 指向对象； 
*       IStrm --- [IN] 输入流；
*       Qty --- [IN] 输入的Byte数量；
*       pCaller --- [IN] 来访者。
*/          
RESULT  VO_Input(OBJECT* pObject, BYTE* IStrm, BYTKTY Qty, const VR* pCaller)
{
	extern  RESULT  CallerCome(OBJECT* pND, const VR* pCaller);
	extern  RESULT  CallerLeave(OBJECT* pND, const VR* pCaller);

	RESULT  ir = R_O;

	assert( pObject != NULL );
	assert( IStrm != NULL );
	assert( Qty > 0 );
	assert( pCaller->cr != 0 );
	assert( pCaller->mr != 0 );

	if( R_P == CallerCome(pObject, pCaller) ) 
	{ 
		ir = pObject->Input(pObject, IStrm, Qty, pCaller); 
		CallerLeave(pObject, pCaller); 
	}else { ir = R_N; }
	
	return ir;
}

/**
*
* 名称：VO_Output
* 描述：接口Output的VO函数。
* 参数：pObject --- [IN] 指向对象； 
*       OStrm --- [OUT] 输出流的流向；
*       Cty --- [IN] OStrm所指存储空间的容量；
*       pQty --- [OUT] 指向实际输出的Byte数量；
*       pCaller --- [IN] 来访者。
*/      
RESULT  VO_Output(OBJECT* pObject, BYTE* OStrm, BYTKTY Cty, BYTKTY* pQty, const VR* pCaller) 
{
	extern  RESULT  CallerCome(OBJECT* pND, const VR* pCaller);
	extern  RESULT  CallerLeave(OBJECT* pND, const VR* pCaller);

	RESULT  ir = R_O;

	assert( pObject != NULL );
	assert( OStrm != NULL );
	assert( Cty > 0 );
	assert( pQty != NULL );
	assert( pCaller->cr != 0 );
	assert( pCaller->mr != 0 );

	*pQty = 0;

	if( R_P == CallerCome(pObject, pCaller) ) 
	{ 
		ir = pObject->Output(pObject, OStrm, Cty, pQty, pCaller); 
		CallerLeave(pObject, pCaller); 
	}else { ir = R_N; }
	
	return ir;
}

/**
*
* 名称：VO_IOput
* 描述：接口IOput的VO函数。
* 参数：pObject --- [IN] 指向对象； 
*       IStrm --- [IN] 输入流；
*       Qty --- [IN] 输入的Byte数量；
*       OStrm --- [OUT] 输出流的流向；
*       Cty --- [IN] OStrm所指存储空间的容量；
*       pQty --- [OUT] 指向实际输出的Byte数量；
*       pCaller --- [IN] 来访者。
*/  
RESULT  VO_IOput(OBJECT* pObject, BYTE* IStrm, BYTKTY Qty, BYTE* OStrm, BYTKTY Cty, BYTKTY* pQty, const VR* pCaller)
{
	extern  RESULT  CallerCome(OBJECT* pND, const VR* pCaller);
	extern  RESULT  CallerLeave(OBJECT* pND, const VR* pCaller);
	
	RESULT  ir = R_O;

	assert( pObject != NULL );
	assert( IStrm != NULL );
	assert( Qty > 0 );
	assert( OStrm != NULL );
	assert( Cty > 0 );
	assert( pQty != NULL );
	assert( pCaller->cr != 0 );
	assert( pCaller->mr != 0 );
	
	*pQty = 0;

	if( R_P == CallerCome(pObject, pCaller) ) 
	{ 
		ir = pObject->IOput(pObject, IStrm, Qty, OStrm, Cty, pQty, pCaller); 
		CallerLeave(pObject, pCaller); 
	}else { ir = R_N; }
	
	return ir;
}

/**
*
* 名称：VO_Interact0
* 描述：接口Interact0的VO函数。
* 参数：pObject --- [IN] 指向对象；
*       Act --- [IN] 交互行为；
*       pCaller --- [IN] 来访者。
*/	       
RESULT  VO_Interact0(OBJECT* pObject, ACTION Act, const VR* pCaller) 
{
	extern  RESULT  CallerCome(OBJECT* pND, const VR* pCaller);
	extern  RESULT  CallerLeave(OBJECT* pND, const VR* pCaller);

	RESULT  ir = R_O;

	assert( pObject != NULL );
	assert( (MSKAC & Act) == AC0 );
	assert( pCaller->cr != 0 );
	assert( pCaller->mr != 0 );
	
	if( R_P == CallerCome(pObject, pCaller) )
	{
		ir = pObject->Interact0(pObject, Act, pCaller);
		CallerLeave(pObject, pCaller);
	}else { ir = R_N; }
	
	return ir;
}

/**
*
* 名称：VO_Interact1
* 描述：接口Interact1的VO函数。
* 参数：pObject --- [IN] 指向对象；
*       Act --- [IN] 交互行为；
*       OStrm --- [OUT] 输出流的流向；
*       Cty --- [IN] OStrm所指存储空间的容量；
*       pQty --- [OUT] 指向实际输出的Byte数量；
*       pCaller --- [IN] 来访者。
*/       
RESULT  VO_Interact1(OBJECT* pObject, ACTION Act, BYTE* OStrm, BYTKTY Cty, BYTKTY* pQty, const VR* pCaller) 
{
	extern  RESULT  CallerCome(OBJECT* pND, const VR* pCaller);
	extern  RESULT  CallerLeave(OBJECT* pND, const VR* pCaller);

	RESULT  ir = R_O;

	assert( pObject != NULL );
	assert( (MSKAC & Act) == AC1 );
	assert( OStrm != NULL );
	assert( Cty > 0 );
	assert( pQty != NULL );
	assert( pCaller->cr != 0 );
	assert( pCaller->mr != 0 );

	*pQty = 0;

	if( R_P == CallerCome(pObject, pCaller) ) 
	{ 
		ir = pObject->Interact1(pObject, Act, OStrm, Cty, pQty, pCaller); 
		CallerLeave(pObject, pCaller); 
	}else { ir = R_N; }
	
	return ir;
}

/**
*
* 名称：VO_Interact2
* 描述：接口Interact2的VO函数。
* 参数：pObject --- [IN] 指向对象；
*       Act --- [IN] 交互行为；
*       IStrm --- [IN] 输入流；
*       Qty --- [IN] 输入的Byte数量；
*       pCaller --- [IN] 来访者。
*/       
RESULT  VO_Interact2(OBJECT* pObject, ACTION Act, BYTE* IStrm, BYTKTY Qty, const VR* pCaller)  
{
	extern  RESULT  CallerCome(OBJECT* pND, const VR* pCaller);
	extern  RESULT  CallerLeave(OBJECT* pND, const VR* pCaller);

	RESULT  ir = R_O;
	
	assert( pObject != NULL );
	assert( (MSKAC & Act) == AC2 );
	assert( IStrm != NULL );
	assert( Qty > 0 );
	assert( pCaller->cr != 0 );
	assert( pCaller->mr != 0 );

	if( R_P == CallerCome(pObject, pCaller) ) 
	{ 
		ir = pObject->Interact2(pObject, Act, IStrm, Qty, pCaller); 
		CallerLeave(pObject, pCaller); 
	}else { ir = R_N; }
	
	return ir;
}

/**
*
* 名称：VO_Interact3
* 描述：接口Interact3的VO函数。
* 参数：pObject --- [IN] 指向对象；
*       Act --- [IN] 交互行为；
*       IStrm --- [IN] 输入流；
*       Qty --- [IN] 输入的Byte数量；
*       OStrm --- [OUT] 输出流的流向；
*       Cty --- [IN] OStrm所指存储空间的容量；
*       pQty --- [OUT] 指向实际输出的Byte数量；
*       pCaller --- [IN] 来访者。
*/       
RESULT  VO_Interact3(OBJECT* pObject, ACTION Act, BYTE* IStrm, BYTKTY Qty, BYTE* OStrm, BYTKTY Cty, BYTKTY* pQty, const VR* pCaller)  
{
	extern  RESULT  CallerCome(OBJECT* pND, const VR* pCaller);
	extern  RESULT  CallerLeave(OBJECT* pND, const VR* pCaller);

	RESULT  ir = R_O;

	assert( pObject != NULL );
	assert( (MSKAC & Act) == AC3 );
	assert( IStrm != NULL );
	assert( Qty > 0 );
	assert( OStrm != NULL );
	assert( Cty > 0 );
	assert( pQty != NULL );
	assert( pCaller->cr != 0 );
	assert( pCaller->mr != 0 );

	*pQty = 0;

	if( R_P == CallerCome(pObject, pCaller) ) 
	{ 
		ir = pObject->Interact3(pObject, Act, IStrm, Qty, OStrm, Cty, pQty, pCaller); 
		CallerLeave(pObject, pCaller); 
	}else { ir = R_N; }
	
	return ir;
}

/**
*
* 名称：VO_Close
* 描述：接口Close的VO函数。
* 参数：pObject --- [IN] 指向对象； 
*       pCaller --- [IN] 来访者。
*/       
RESULT  VO_Close(OBJECT* pObject, const VR* pCaller) 
{
	extern  RESULT  CallerCome(OBJECT* pND, const VR* pCaller);
	extern  RESULT  CallerLeave(OBJECT* pND, const VR* pCaller);

	RESULT  ir = R_O;
	
	assert( pObject != NULL );
	assert( pCaller->cr != 0 );
	assert( pCaller->mr != 0 );

	if( R_P == CallerCome(pObject, pCaller) ) 
	{ 
		ir = pObject->Close(pObject, pCaller); 
		CallerLeave(pObject, pCaller); 
	}else { ir = R_N; }
	
	return ir;
}

#endif  /* #if INLINE_VOFUNCTION == 0 */
