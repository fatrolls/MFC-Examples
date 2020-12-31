/**
 *
 * 文 件 名：ho.c
 *
 * 描    述：
 *
 * 创 建 者：
 *
 * 创建日期：
 *
 * 备    注：
 *
 *
 * * 维护历史 *
 *
 *   <日期>                <修改者>
 *   <修改内容...>
 *
 **/

#include "ho.h"


/*====================+ Definition +=====================*/

/*
*
* 名称：DOID
* 描述：记录已销毁对象的OID。
* 备注：DOID，Destroyed Object's ID。
*/
typedef struct TAG_DOID
{
	MLDSN  msn;
	OBJID  oid;
}DOID;

/*
*
* 名称：TARRDOID
* 描述：DOID数组结构体。
*/
typedef struct TAG_ARRDOID
{
	SI32    neo; /* 存在的对象个数，即没有销毁的对象个数。eo - existent object */
	DOID*   pad; /* 指向元素类型为DOID的数组，这个数组动态分配。ad - the array of DOID */
	SI32    lad; /* pad所指数组的空间长度，以元素为单位。lad - the length of array of DOID */
	SI32    nwe; /* pad所指数组中已填写过的元素个数。nwe - the number of written element */
	OBJID   oid; /* 传给CRT函数的OID。*/
}TARRDOID;

/*
*
* 名称：STP_GLAD
* 描述：宏，DOID数组空间增长步长，以数组元素为单位。
* 备注：STP - step，LAD - the length of array of DOID，GLAD - the growth of LAD。
*/
#define    STP_GLAD        10


/*====================+ Variable(s) +====================*/

static  TARRDOID   gs_tad = {0, NULL, 0, 0, OID_};


/*=================+ __CreateObject__ +==================*/

/**
*
* 名称：__CreateObject__
* 描述：创建对象。
* 参数：Msn --- [IN] 模序号，指定创建哪个模的对象；
*       IQCty --- [IN] 输入队列的容量；
*       OQCty --- [IN] 输出队列的容量；
*       NumCR --- [IN] 来访者数量；
*       ppObj --- [OUT] 输出创建的对象；
*       pExotic --- [IN] 在外面为IC分配的空间，适用于创建静态对象（如函数内的局部对象）。
* 返回：成功返回P结果，失败返回N结果。
* 备注：1. NumCR必须大于0；
*       2. ppObj和pExotic不能都为NULL或非NULL；
*       3. 如果pExotic不是NULL，表示IC空间已在外面分配好了。
*/
RESULT  __CreateObject__(MLDSN Msn, BYTKTY IQCty, BYTKTY OQCty, SI32 NumCR, OBJECT** ppObj, BYTE* pExotic)
{
	/* extern  RESULT  CRT_xxx(OBJID* pOID, BYTKTY IQCty, BYTKTY OQCty, SI32 NumCR, OBJECT** ppObj, BYTE* pExotic); */
	extern  RESULT  CRT_MyDialog(OBJID* pOID, BYTKTY IQCty, BYTKTY OQCty, SI32 NumCR, OBJECT** ppObj, BYTE* pExotic);
	extern  RESULT  CRT_CButton(OBJID* pOID, BYTKTY IQCty, BYTKTY OQCty, SI32 NumCR, OBJECT** ppObj, BYTE* pExotic);
	extern  RESULT  CRT_MyButton(OBJID* pOID, BYTKTY IQCty, BYTKTY OQCty, SI32 NumCR, OBJECT** ppObj, BYTE* pExotic);
	extern  RESULT  CRT_MyButton2(OBJID* pOID, BYTKTY IQCty, BYTKTY OQCty, SI32 NumCR, OBJECT** ppObj, BYTE* pExotic);


	RESULT        fr;
	OBJID         oidbak;

	EM_OIOIC*     pem;
	SI32          idd; /* DOID的指标。idd - the index of DOID */

	assert( NumCR > 0 );
	assert( !(NULL == ppObj && NULL == pExotic) );
	assert( !(ppObj != NULL && pExotic != NULL) );

	oidbak = gs_tad.oid;

	for(idd = 0; idd < gs_tad.nwe; idd++)
	{
		if((Msn == (gs_tad.pad+idd)->msn) && ((gs_tad.pad+idd)->oid != 0))
		{
			gs_tad.oid = (gs_tad.pad+idd)->oid;
			break;
		}
	}

	switch(Msn)
	{
		case MSN_MYDIALOG:
			fr = CRT_MyDialog(&gs_tad.oid, IQCty, OQCty, NumCR, ppObj, pExotic);
			break;
		case MSN_CBUTTON:
			fr = CRT_CButton(&gs_tad.oid, IQCty, OQCty, NumCR, ppObj, pExotic);
			break;
		case MSN_MYBUTTON:
			fr = CRT_MyButton(&gs_tad.oid, IQCty, OQCty, NumCR, ppObj, pExotic);
			break;
		case MSN_MYBUTTON2:
			fr = CRT_MyButton2(&gs_tad.oid, IQCty, OQCty, NumCR, ppObj, pExotic);
			break;
		default:
			fr = R_N;
			break;
	}

	if(!RN(fr))
	{
		if(idd < gs_tad.nwe)
		{
			gs_tad.oid = oidbak;
			(gs_tad.pad+idd)->oid = 0;
		}else if((MSKSO & gs_tad.oid) < (MSKSO & oidbak))
		{
			gs_tad.oid = oidbak;

			pem = (EM_OIOIC*)GetEMofBN(*ppObj, MSN_OIOIC);
			if(pem->IQ.Dtrm != NULL)
				free(pem->IQ.Dtrm);
			if(pem->OQ.Dtrm != NULL)
				free(pem->OQ.Dtrm);

			if(NULL == pExotic)
			{
				free(*ppObj);
				*ppObj = NULL;
			}

			return RN_LACKOID;
		}

		gs_tad.neo++;

	}else
	{
		gs_tad.oid = oidbak;
	}

	return  fr;
}

/*=================+ __DestroyObject__ +=================*/

/*
*
* 名称：__DestroyObject__
* 描述：销毁对象。
* 参数：pObj --- [IN] 指向对象。
* 返回：TRUE - 成功，FALSE - 失败。
* 备注：静态对象（如函数内的局部对象）也须用此函数销毁。
*/
BOOL  __DestroyObject__(OBJECT*  pObj)
{
	DOID*       ptr;
	SI32        idd;   /* DOID的指标。idd - the index of DOID */
	EM_OIOIC*   pem;

	assert( pObj != NULL );

	pem = (EM_OIOIC*)GetEMofBN(pObj, MSN_OIOIC);

	if(NULL == gs_tad.pad)
	{
		if(gs_tad.neo-1 > 0)
		{
			gs_tad.pad = (DOID*)calloc(STP_GLAD, sizeof(DOID));
			if(NULL == gs_tad.pad)
				return FALSE;
			gs_tad.pad->msn = pObj->MSN;
			gs_tad.pad->oid = pObj->OID;
			gs_tad.lad = STP_GLAD;
			gs_tad.nwe = 1;
		}else if(0 == gs_tad.neo-1)
		{
			gs_tad.oid = OID_;
		}else
		{
			return FALSE;
		}
	}else
	{
		for(idd = 0; idd < gs_tad.nwe; idd++)
		{
			if((pObj->MSN == (gs_tad.pad+idd)->msn) && (0 == (gs_tad.pad+idd)->oid))
			{
				(gs_tad.pad+idd)->oid = pObj->OID;
				break;
			}
		}

		if(idd == gs_tad.nwe)
		{
			if(idd == gs_tad.lad)
			{
				ptr = (DOID*)calloc(gs_tad.lad + STP_GLAD, sizeof(DOID));
				if(NULL == ptr)
					return FALSE;
				memcpy(ptr, gs_tad.pad, gs_tad.nwe*sizeof(DOID));
				free(gs_tad.pad);
				gs_tad.pad = ptr;
				gs_tad.lad += STP_GLAD;
			}
			(gs_tad.pad+gs_tad.nwe)->msn = pObj->MSN;
			(gs_tad.pad+gs_tad.nwe)->oid = pObj->OID;
			gs_tad.nwe++;
		}
	}

	if(pem->IQ.Dtrm != NULL)
		free(pem->IQ.Dtrm);
	if(pem->OQ.Dtrm != NULL)
		free(pem->OQ.Dtrm);

	gs_tad.neo--;

	if(gs_tad.pad != NULL && 0 == gs_tad.neo)
	{
		free(gs_tad.pad);
		gs_tad.pad = NULL;
		gs_tad.lad = 0;
		gs_tad.nwe = 0;
		gs_tad.oid = OID_;
	}

	return TRUE;
}


/*=============+ Global object pointer(s) +==============*/

OBJECT*   g_poMainWnd = NULL;
