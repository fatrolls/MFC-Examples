/**
 *
 * 文 件 名：wgidemo.c
 *
 * 描    述：
 *
 * 创 建 者：赵平智
 *
 * 创建日期：2011.08
 *
 * 版    本：1.0.7
 *
 * 版权(C)2005-2011 赵平智。保留所有权利。　
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

#include "wgidemo.h"


/*=====================+ OICC label +====================*/

/*<oicc>*/
/*<ibn> OIOIC </ibn>*/
/*<crt>*/
/*</crt>*/
/*</oicc>*/

/*=====================+ Interface +=====================*/

/**
*
* 名称：wgidemo_Open
*/
static  RESULT  wgidemo_Open(OBJECT* This, const VR* pCaller)
{
	OBS_OBJECT_OPEN_;

	/* 在下面完成接口自己的任务。*/


	if(1 == This->RefCnt)
		return RP_RCONE;


	return R_P;
}

/**
*
* 名称：wgidemo_Input
*/
static  RESULT  wgidemo_Input(OBJECT* This, BYTE* IStrm, BYTKTY Qty, const VR* pCaller)
{

	/* ... */


	/* 在上面完成接口自己的任务。*/

	SBO_OBJECT_INPUT;
}

/**
*
* 名称：wgidemo_Output
*/
static  RESULT  wgidemo_Output(OBJECT* This, BYTE* OStrm, BYTKTY Cty, BYTKTY* pQty, const VR* pCaller)
{

	/* ... */


	/* 在上面完成接口自己的任务。*/

	SBO_OBJECT_OUTPUT;
}

/**
*
* 名称：wgidemo_IOput
*/
static  RESULT  wgidemo_IOput(OBJECT* This, BYTE* IStrm, BYTKTY Qty, BYTE* OStrm, BYTKTY Cty, BYTKTY* pQty, const VR* pCaller)
{

	/* ... */


	/* 在上面完成接口自己的任务。*/

	SBO_OBJECT_IOPUT;
}

/**
*
* 名称：wgidemo_Interact0
*/
static  RESULT  wgidemo_Interact0(OBJECT* This, ACTION Act, const VR* pCaller)
{

	/* ... */


	/* 在上面完成接口自己的任务。*/

	SBO_OBJECT_INTERACT0;
}

/**
*
* 名称：wgidemo_Interact1
*/
static  RESULT  wgidemo_Interact1(OBJECT* This, ACTION Act, BYTE* OStrm, BYTKTY Cty, BYTKTY* pQty, const VR* pCaller)
{

	/* ... */


	/* 在上面完成接口自己的任务。*/

	SBO_OBJECT_INTERACT1;
}

/**
*
* 名称：wgidemo_Interact2
*/
static  RESULT  wgidemo_Interact2(OBJECT* This, ACTION  Act, BYTE* IStrm, BYTKTY Qty, const VR* pCaller)
{

	/* ... */


	/* 在上面完成接口自己的任务。*/

	SBO_OBJECT_INTERACT2;
}

/**
*
* 名称：wgidemo_Interact3
*/
static  RESULT  wgidemo_Interact3(OBJECT* This, ACTION Act, BYTE* IStrm, BYTKTY Qty, BYTE* OStrm, BYTKTY Cty, BYTKTY* pQty, const VR* pCaller)
{

	/* ... */


	/* 在上面完成接口自己的任务。*/

	SBO_OBJECT_INTERACT3;
}

/**
*
* 名称：wgidemo_Close
*/
static  RESULT  wgidemo_Close(OBJECT* This, const VR* pCaller)
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
* 名称：TOG_wgidemo
*/
VOID  TOG_wgidemo(OBJECT* pObj)
{
	pObj->Open = wgidemo_Open;
	pObj->Input = wgidemo_Input;
	pObj->Output = wgidemo_Output;
	pObj->IOput = wgidemo_IOput;
	pObj->Interact0 = wgidemo_Interact0;
	pObj->Interact1 = wgidemo_Interact1;
	pObj->Interact2 = wgidemo_Interact2;
	pObj->Interact3 = wgidemo_Interact3;
	pObj->Close = wgidemo_Close;
}

/*====================+ Function(s) +====================*/
/* ... */

