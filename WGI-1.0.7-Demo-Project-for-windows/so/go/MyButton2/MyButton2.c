/**
 *
 * 文 件 名：MyButton2.c
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

#include <wchar.h>
#include "MyButton2.h"
#include "MyButton2_InitSub.h"
#include "../CObject/CObject.h"
#include "../CButton/CButton.h"


VOID  TOG_MyButton2(OBJECT* pObj);


/*=====================+ OICC label +====================*/

/*<oicc>*/
/*<ibn> CButton </ibn>*/
/*<crt>*/
RESULT  CRT_MyButton2(OBJID* pOID, BYTKTY IQCty, BYTKTY OQCty, SI32 NumCR, OBJECT** ppObj, BYTE* pExotic)
{
	extern  VOID  InitAIBofND(OBJECT* pND, MLDSN* pMsn, NUMIB nib);
	extern  VOID  InitABNofND(OBJECT* pND, MLDSN* pMsn, NUMBN nbn);
	extern  VOID  TOG_CButton(OBJECT* pObj);
	extern  VOID  TOG_CObject(OBJECT* pObj);
	extern  VOID  TOG_VObject(OBJECT* pObj);
	extern  VOID  TOG_OIOIC(OBJECT* pObj);


	UI32   ux_ND = 5; 	/* ND数量。*/
	UI32   ux_BN = 10; 	/* 各ND的BN数量之和。*/
	UI32   ux_IB = 4; 	/* 各ND的IBN数量之和。*/
	UI32   ux_CS = NumCR * 15; 	/* 各ND的最少CS数量之和。*/
	UI32   ux_EM = sizeof(EM_MYBUTTON2) + sizeof(EM_CBUTTON) + sizeof(EM_COBJECT)
		 + sizeof(EM_VOBJECT) + sizeof(EM_OIOIC); 	/* 各ND的EM尺寸之和。*/

	UI32  sum = ux_ND * sizeof(OBJECT) 	/* for AND. */
		 + ux_BN * sizeof(OBJECT*) 	/* for "ppo_ABN". */
		 + ux_IB * sizeof(OBJECT*) 	/* for "ppo_AIB". */
		 + ux_CS * sizeof(VR) + ux_EM; 	/* for "pvr_ACS" and "pEM". */


	BYTE*  pIC = NULL;

	if(NULL == pExotic)
	{
		*ppObj = NULL;
		pIC = (BYTE*)calloc(sum, 1);
	}else
	{
		pIC = pExotic;
	}


	if( pIC != NULL )
	{
		OBJECT*  pND;
		MLDSN    ArrMsn[4];
		BYTE*    p = pIC + sizeof(OBJECT) * ux_ND;


		/***  确定AND各元素  ***/

		/** MyButton2 **/
		pND = (OBJECT*)pIC;
		TOG_MyButton2(pND);
		pND->MSN = MSN_MYBUTTON2;
		pND->OID = (*pOID)++;
		pND->po_AND = (OBJECT*)pIC;
		pND->NND = ux_ND;

		/** CButton **/
		TOG_CButton(++pND);
		pND->MSN = MSN_CBUTTON;
		pND->OID = (*pOID)++;
		pND->po_AND = (OBJECT*)pIC;
		pND->NND = ux_ND;

		/** CObject **/
		TOG_CObject(++pND);
		pND->MSN = MSN_COBJECT;
		pND->OID = (*pOID)++;
		pND->po_AND = (OBJECT*)pIC;
		pND->NND = ux_ND;

		/** VObject **/
		TOG_VObject(++pND);
		pND->MSN = MSN_VOBJECT;
		pND->OID = (*pOID)++;
		pND->po_AND = (OBJECT*)pIC;
		pND->NND = ux_ND;

		/** OIOIC **/
		TOG_OIOIC(++pND);
		pND->MSN = MSN_OIOIC;
		pND->OID = (*pOID)++;
		pND->po_AND = (OBJECT*)pIC;
		pND->NND = ux_ND;


		/***  初始化各ND  ***/

		/** MyButton2 **/
		pND = (OBJECT*)pIC;

		/* - AIB - */
		pND->ppo_AIB = (OBJECT**)p;
		ArrMsn[0] = MSN_CBUTTON;
		InitAIBofND(pND, ArrMsn, 1);
		p += sizeof(OBJECT*) * 1;

		/* - ABN - */
		pND->ppo_ABN = (OBJECT**)p;
		ArrMsn[0] = MSN_CBUTTON;
		ArrMsn[1] = MSN_COBJECT;
		ArrMsn[2] = MSN_VOBJECT;
		ArrMsn[3] = MSN_OIOIC;
		InitABNofND(pND, ArrMsn, 4);
		p += sizeof(OBJECT*) * 4;

		/* - ACS - */
		pND->pvr_ACS = (VR*)p;
		pND->NCS = NumCR * 1;
		p += sizeof(VR) * pND->NCS;

		/* - EM - */
		pND->pEM = (EM*)p;
		p += sizeof(EM_MYBUTTON2);

		/** CButton **/
		++pND;

		/* - AIB - */
		pND->ppo_AIB = (OBJECT**)p;
		ArrMsn[0] = MSN_COBJECT;
		InitAIBofND(pND, ArrMsn, 1);
		p += sizeof(OBJECT*) * 1;

		/* - ABN - */
		pND->ppo_ABN = (OBJECT**)p;
		ArrMsn[0] = MSN_COBJECT;
		ArrMsn[1] = MSN_VOBJECT;
		ArrMsn[2] = MSN_OIOIC;
		InitABNofND(pND, ArrMsn, 3);
		p += sizeof(OBJECT*) * 3;

		/* - ACS - */
		pND->pvr_ACS = (VR*)p;
		pND->NCS = NumCR * 2;
		p += sizeof(VR) * pND->NCS;

		/* - EM - */
		pND->pEM = (EM*)p;
		p += sizeof(EM_CBUTTON);

		/** CObject **/
		++pND;

		/* - AIB - */
		pND->ppo_AIB = (OBJECT**)p;
		ArrMsn[0] = MSN_VOBJECT;
		InitAIBofND(pND, ArrMsn, 1);
		p += sizeof(OBJECT*) * 1;

		/* - ABN - */
		pND->ppo_ABN = (OBJECT**)p;
		ArrMsn[0] = MSN_VOBJECT;
		ArrMsn[1] = MSN_OIOIC;
		InitABNofND(pND, ArrMsn, 2);
		p += sizeof(OBJECT*) * 2;

		/* - ACS - */
		pND->pvr_ACS = (VR*)p;
		pND->NCS = NumCR * 3;
		p += sizeof(VR) * pND->NCS;

		/* - EM - */
		pND->pEM = (EM*)p;
		p += sizeof(EM_COBJECT);

		/** VObject **/
		++pND;

		/* - AIB - */
		pND->ppo_AIB = (OBJECT**)p;
		ArrMsn[0] = MSN_OIOIC;
		InitAIBofND(pND, ArrMsn, 1);
		p += sizeof(OBJECT*) * 1;

		/* - ABN - */
		pND->ppo_ABN = (OBJECT**)p;
		ArrMsn[0] = MSN_OIOIC;
		InitABNofND(pND, ArrMsn, 1);
		p += sizeof(OBJECT*) * 1;

		/* - ACS - */
		pND->pvr_ACS = (VR*)p;
		pND->NCS = NumCR * 4;
		p += sizeof(VR) * pND->NCS;

		/* - EM - */
		pND->pEM = (EM*)p;
		p += sizeof(EM_VOBJECT);

		/** OIOIC **/
		++pND;

		/* - ACS - */
		pND->pvr_ACS = (VR*)p;
		pND->NCS = NumCR * 5;
		p += sizeof(VR) * pND->NCS;

		/* - EM - */
		pND->pEM = (EM*)p;
		if( IQCty > 0 )
		{
			/* - IQ - */
			((EM_OIOIC*)(pND->pEM))->IQ.Dtrm = (BYTE*)calloc(IQCty, 1);
			if( NULL == ((EM_OIOIC*)(pND->pEM))->IQ.Dtrm)
			{
				/* 分配IQ的容量失败！*/
				if(NULL == pExotic)
					free(pIC);
				return R_N;
			}
			((EM_OIOIC*)(pND->pEM))->IQ.Front = ((EM_OIOIC*)(pND->pEM))->IQ.Rear = ((EM_OIOIC*)(pND->pEM))->IQ.Dtrm - 1;
			((EM_OIOIC*)(pND->pEM))->IQ.Cty = IQCty;
			((EM_OIOIC*)(pND->pEM))->IQ.Qty = ((EM_OIOIC*)(pND->pEM))->IQ.Lost = 0;
		}

		if( OQCty > 0 )
 		{
			/* - OQ - */
			((EM_OIOIC*)(pND->pEM))->OQ.Dtrm = (BYTE*)calloc(OQCty, 1);
			if(NULL == ((EM_OIOIC*)(pND->pEM))->OQ.Dtrm)
			{
				/* 分配OQ的容量失败！*/
				if( ((EM_OIOIC*)(pND->pEM))->IQ.Dtrm != NULL )
					free(((EM_OIOIC*)(pND->pEM))->IQ.Dtrm);
				if(NULL == pExotic)
					free(pIC);
				return R_N;
			}
			((EM_OIOIC*)(pND->pEM))->OQ.Front = ((EM_OIOIC*)(pND->pEM))->OQ.Rear = ((EM_OIOIC*)(pND->pEM))->OQ.Dtrm - 1;
			((EM_OIOIC*)(pND->pEM))->OQ.Cty = OQCty;
			((EM_OIOIC*)(pND->pEM))->OQ.Qty = ((EM_OIOIC*)(pND->pEM))->OQ.Lost = 0;
		}
		p += sizeof(EM_OIOIC);
	}else
	{
		return R_N;
	}


	if(NULL == pExotic)
		*ppObj = (OBJECT*)pIC;


	return R_P;
}
/*</crt>*/
/*</oicc>*/

/*=====================+ Interface +=====================*/

/**
*
* 名称：MyButton2_Open
*/
static  RESULT  MyButton2_Open(OBJECT* This, const VR* pCaller)
{
	VR	              caller;
	EM_MYBUTTON2*     pem;


	OBS_OBJECT_OPEN_;

	/* 在下面完成接口自己的任务。*/


	caller.cr = pCaller->cr;
	caller.mr = This->OID;

	if(1 == This->RefCnt)
	{
		pem = (EM_MYBUTTON2*)This->pEM;
		pem->pOIOIC = GetBN(This, MSN_OIOIC); 
		pem->pVObject = GetBN(This, MSN_VOBJECT); 
		pem->pCObject = GetBN(This, MSN_COBJECT); 
		pem->pCButton = GetBN(This, MSN_CBUTTON);

		CreateObject(MSN_MYBUTTON, 0, 0, 1, &pem->ArrSUB[eButton_MyButton2]);

		return RP_RCONE;
	}


	return R_P;
}

/**
*
* 名称：MyButton2_Input
*/
static  RESULT  MyButton2_Input(OBJECT* This, BYTE* IStrm, BYTKTY Qty, const VR* pCaller)
{

	/* ... */


	/* 在上面完成接口自己的任务。*/

	SBO_OBJECT_INPUT;
}

/**
*
* 名称：MyButton2_Output
*/
static  RESULT  MyButton2_Output(OBJECT* This, BYTE* OStrm, BYTKTY Cty, BYTKTY* pQty, const VR* pCaller)
{

	/* ... */


	/* 在上面完成接口自己的任务。*/

	SBO_OBJECT_OUTPUT;
}

/**
*
* 名称：MyButton2_IOput
*/
static  RESULT  MyButton2_IOput(OBJECT* This, BYTE* IStrm, BYTKTY Qty, BYTE* OStrm, BYTKTY Cty, BYTKTY* pQty, const VR* pCaller)
{

	/* ... */


	/* 在上面完成接口自己的任务。*/

	SBO_OBJECT_IOPUT;
}

/**
*
* 名称：MyButton2_Interact0
*/
static  RESULT  MyButton2_Interact0(OBJECT* This, ACTION Act, const VR* pCaller)
{
	VR                  caller;
	EM_MYBUTTON2*       pem = (EM_MYBUTTON2*)This->pEM;
	EM_VOBJECT*         pem_vob = (EM_VOBJECT*)pem->pVObject->pEM;
	int                 i;
	
    caller.cr = pCaller->cr;
	caller.mr = This->OID;

	switch(Act)
	{
	case CMD_PREPARE:
		for(i = 0; i<eNumSub_MyButton2; i++)
		{
			switch(i)
			{
			case eButton_MyButton2:
				MyButton2_InitSub_Button(This, i, &caller);
				break;
			default:
				break;
			}
		}

		for(i = 0; i<eNumSub_MyButton2; i++)
			VO_Interact0(pem->ArrSUB[i], CMD_PREPARE, &caller);

		pem_vob->pFirstSbdt = pem->ArrSUB[eButton_MyButton2];
		VO_Interact0(pem->pVObject, CMD_PREPARE, &caller);
		return R_P;
	default:
		break;
	}


	/* 在上面完成接口自己的任务。*/

	SBO_OBJECT_INTERACT0;
}

/**
*
* 名称：MyButton2_Interact1
*/
static  RESULT  MyButton2_Interact1(OBJECT* This, ACTION Act, BYTE* OStrm, BYTKTY Cty, BYTKTY* pQty, const VR* pCaller)
{

	/* ... */


	/* 在上面完成接口自己的任务。*/

	SBO_OBJECT_INTERACT1;
}

/**
*
* 名称：MyButton2_Interact2
*/
static  RESULT  MyButton2_Interact2(OBJECT* This, ACTION  Act, BYTE* IStrm, BYTKTY Qty, const VR* pCaller)
{
	VR    caller;
	EM_MYBUTTON2*       pem = (EM_MYBUTTON2*)This->pEM;
	EM_VOBJECT*         pem_vob = (EM_VOBJECT*)pem->pVObject->pEM;
	EM_VOBJECT*         pem_vob_sbdt;
	POINT               pt;
	MOVE                mv;

	caller.cr = pCaller->cr;
	caller.mr = This->OID;

	switch(Act)
	{
	case MSG_WGI_FOCUSDOWN:
		assert(sizeof(POINT) == Qty);
		VO_Interact2(pem->pVObject, MSG_WGI_FOCUSDOWN, IStrm, sizeof(POINT), &caller);
		if(pem_vob->pCFDownSbdt != NULL)
		{
			pem->lastpt = *(POINT*)IStrm;
			VO_Interact0(pem_vob->pCFDownSbdt, MSG_WGI_ACTIVATE, &caller);
		}
		return R_P;
	case MSG_WGI_FOCUSONMOVE:
		assert(sizeof(POINT) == Qty);
		VO_Interact2(pem->pVObject, MSG_WGI_FOCUSONMOVE, IStrm, sizeof(POINT), &caller);
		if(pem_vob->pCFDownSbdt != NULL)
		{
			pem_vob_sbdt = (EM_VOBJECT*)GetEMofBN(pem_vob->pCFDownSbdt, MSN_VOBJECT);
			if(NULL == pem_vob_sbdt->pCFDownSbdt)
			{
				memset(&mv, 0, sizeof(MOVE));
				pt = *(POINT*)IStrm;
				mv.dxLR = mv.dxUL = pt.x - pem->lastpt.x;
				mv.dyLR = mv.dyUL = pt.y - pem->lastpt.y;
				VO_Interact2(pem_vob->pCFDownSbdt, CMD_WGI_MOVE, (BYTE*)&mv, sizeof(MOVE), &caller);
				
				pem->lastpt = pt;
			}
		}
		return R_P;
	default:
		break;
	}


	/* 在上面完成接口自己的任务。*/

	SBO_OBJECT_INTERACT2;
}

/**
*
* 名称：MyButton2_Interact3
*/
static  RESULT  MyButton2_Interact3(OBJECT* This, ACTION Act, BYTE* IStrm, BYTKTY Qty, BYTE* OStrm, BYTKTY Cty, BYTKTY* pQty, const VR* pCaller)
{

	/* ... */


	/* 在上面完成接口自己的任务。*/

	SBO_OBJECT_INTERACT3;
}

/**
*
* 名称：MyButton2_Close
*/
static  RESULT  MyButton2_Close(OBJECT* This, const VR* pCaller)
{
	VR                  caller;
	EM_MYBUTTON2*       pem = (EM_MYBUTTON2*)This->pEM;
	int                 i;

	OBS_OBJECT_CLOSE_;

	/* 在下面完成接口自己的任务。*/

	caller.cr = pCaller->cr;
	caller.mr = This->OID;

	if(0 == This->RefCnt)
	{
		for(i = 0; i<eNumSub_MyButton2; i++)
		{
			VO_Close(pem->ArrSUB[i], &caller);
			DestroyObject(pem->ArrSUB[i]); 
		}

		return RP_RCZERO;
	}


	return R_P;
}

/*========================+ TOG +========================*/

/**
*
* 名称：TOG_MyButton2
*/
VOID  TOG_MyButton2(OBJECT* pObj)
{
	pObj->Open = MyButton2_Open;
	pObj->Input = MyButton2_Input;
	pObj->Output = MyButton2_Output;
	pObj->IOput = MyButton2_IOput;
	pObj->Interact0 = MyButton2_Interact0;
	pObj->Interact1 = MyButton2_Interact1;
	pObj->Interact2 = MyButton2_Interact2;
	pObj->Interact3 = MyButton2_Interact3;
	pObj->Close = MyButton2_Close;
}

/*====================+ Function(s) +====================*/
/* ... */




