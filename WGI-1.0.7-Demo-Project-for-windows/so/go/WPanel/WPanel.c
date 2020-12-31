/**
 *
 * 文 件 名：WPanel.c
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

#include "WPanel.h"


RESULT  WPanel_I_Open(OBJECT* This, const VR* pCaller);


/*=====================+ OICC label +====================*/

/*<oicc>*/
/*<ibn> WObject </ibn>*/
/*<crt>*/
/*</crt>*/
/*</oicc>*/

/*=====================+ Interface +=====================*/

/**
*
* 名称：WPanel_Open
*/
static  RESULT  WPanel_Open(OBJECT* This, const VR* pCaller)
{
	VR    caller;

	caller.cr = pCaller->cr;
	caller.mr = This->OID;

	OBS_OBJECT_OPEN_;

	/* 在下面完成接口自己的任务。*/

	return WPanel_I_Open(This, &caller);
}

/**
*
* 名称：WPanel_Input
*/
static  RESULT  WPanel_Input(OBJECT* This, BYTE* IStrm, BYTKTY Qty, const VR* pCaller)
{

	/* ... */


	/* 在上面完成接口自己的任务。*/

	SBO_OBJECT_INPUT;
}

/**
*
* 名称：WPanel_Output
*/
static  RESULT  WPanel_Output(OBJECT* This, BYTE* OStrm, BYTKTY Cty, BYTKTY* pQty, const VR* pCaller)
{

	/* ... */


	/* 在上面完成接口自己的任务。*/

	SBO_OBJECT_OUTPUT;
}

/**
*
* 名称：WPanel_IOput
*/
static  RESULT  WPanel_IOput(OBJECT* This, BYTE* IStrm, BYTKTY Qty, BYTE* OStrm, BYTKTY Cty, BYTKTY* pQty, const VR* pCaller)
{

	/* ... */


	/* 在上面完成接口自己的任务。*/

	SBO_OBJECT_IOPUT;
}

/**
*
* 名称：WPanel_Interact0
*/
static  RESULT  WPanel_Interact0(OBJECT* This, ACTION Act, const VR* pCaller)
{

	/* ... */


	/* 在上面完成接口自己的任务。*/

	SBO_OBJECT_INTERACT0;
}

/**
*
* 名称：WPanel_Interact1
*/
static  RESULT  WPanel_Interact1(OBJECT* This, ACTION Act, BYTE* OStrm, BYTKTY Cty, BYTKTY* pQty, const VR* pCaller)
{

	/* ... */


	/* 在上面完成接口自己的任务。*/

	SBO_OBJECT_INTERACT1;
}

/**
*
* 名称：WPanel_Interact2
*/
static  RESULT  WPanel_Interact2(OBJECT* This, ACTION  Act, BYTE* IStrm, BYTKTY Qty, const VR* pCaller)
{

	/* ... */


	/* 在上面完成接口自己的任务。*/

	SBO_OBJECT_INTERACT2;
}

/**
*
* 名称：WPanel_Interact3
*/
static  RESULT  WPanel_Interact3(OBJECT* This, ACTION Act, BYTE* IStrm, BYTKTY Qty, BYTE* OStrm, BYTKTY Cty, BYTKTY* pQty, const VR* pCaller)
{

	/* ... */


	/* 在上面完成接口自己的任务。*/

	SBO_OBJECT_INTERACT3;
}

/**
*
* 名称：WPanel_Close
*/
static  RESULT  WPanel_Close(OBJECT* This, const VR* pCaller)
{
	OBS_OBJECT_CLOSE_;

	/* 在下面完成接口自己的任务。*/


	if(0 == This->RefCnt)
		return RP_RCZERO;


	return R_P;
}

/*========================+ TOG +========================*/

/**
*
* 名称：TOG_WPanel
*/
VOID  TOG_WPanel(OBJECT* pObj)
{
	pObj->Open = WPanel_Open;
	pObj->Input = WPanel_Input;
	pObj->Output = WPanel_Output;
	pObj->IOput = WPanel_IOput;
	pObj->Interact0 = WPanel_Interact0;
	pObj->Interact1 = WPanel_Interact1;
	pObj->Interact2 = WPanel_Interact2;
	pObj->Interact3 = WPanel_Interact3;
	pObj->Close = WPanel_Close;
}

/*====================+ Function(s) +====================*/
/* ... */

/*=======================================================*/

/**
*
* NAME: WPanel_I_Open
*/
RESULT  WPanel_I_Open(OBJECT* This, const VR* pCaller)
{
	EM_WPANEL*      pem = (EM_WPANEL*)This->pEM;
	
	if(1 == This->RefCnt)
	{
		pem->pOIOIC = GetBN(This, MSN_OIOIC);
		pem->pVObject = GetBN(This, MSN_VOBJECT);
		pem->pWObject = GetBN(This, MSN_WOBJECT);

		return RP_RCONE;
	}
	
	return R_P;
}

