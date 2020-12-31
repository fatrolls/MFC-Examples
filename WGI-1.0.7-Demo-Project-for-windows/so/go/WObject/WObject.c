/**
 *
 * 文 件 名：WObject.c
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

#include "WObject.h"


RESULT  WObject_I_Open(OBJECT* This, const VR* pCaller);
RESULT  WObject__CRT_WGI_WINDOW(OBJECT* This, const VR* pCaller);
RESULT  WObject__DTR_WGI_WINDOW(OBJECT* This, const VR* pCaller);
RESULT  WObject__CMD_INITIALIZE(OBJECT* This, const INIT_WOBJECT* piwob, const VR* pCaller);


/*=====================+ OICC label +====================*/

/*<oicc>*/
/*<ibn> VObject </ibn>*/
/*<crt>*/
/*</crt>*/
/*</oicc>*/

/*=====================+ Interface +=====================*/

/**
*
* 名称：WObject_Open
*/
static  RESULT  WObject_Open(OBJECT* This, const VR* pCaller)
{
	VR    caller;

	caller.cr = pCaller->cr;
	caller.mr = This->OID;
	
	OBS_OBJECT_OPEN_;

	/* 在下面完成接口自己的任务。*/

	return WObject_I_Open(This, &caller);
}

/**
*
* 名称：WObject_Input
*/
static  RESULT  WObject_Input(OBJECT* This, BYTE* IStrm, BYTKTY Qty, const VR* pCaller)
{

	/* ... */


	/* 在上面完成接口自己的任务。*/

	SBO_OBJECT_INPUT;
}

/**
*
* 名称：WObject_Output
*/
static  RESULT  WObject_Output(OBJECT* This, BYTE* OStrm, BYTKTY Cty, BYTKTY* pQty, const VR* pCaller)
{

	/* ... */


	/* 在上面完成接口自己的任务。*/

	SBO_OBJECT_OUTPUT;
}

/**
*
* 名称：WObject_IOput
*/
static  RESULT  WObject_IOput(OBJECT* This, BYTE* IStrm, BYTKTY Qty, BYTE* OStrm, BYTKTY Cty, BYTKTY* pQty, const VR* pCaller)
{

	/* ... */


	/* 在上面完成接口自己的任务。*/

	SBO_OBJECT_IOPUT;
}

/**
*
* 名称：WObject_Interact0
*/
static  RESULT  WObject_Interact0(OBJECT* This, ACTION Act, const VR* pCaller)
{
	VR                  caller;
	
    caller.cr = pCaller->cr;
	caller.mr = This->OID;

	switch(Act)
	{
	case CRT_WGI_WINDOW:
		return WObject__CRT_WGI_WINDOW(This, &caller);
	case DTR_WGI_WINDOW:
		return WObject__DTR_WGI_WINDOW(This, &caller);
	default:
		break;
	}
	/* 在上面完成接口自己的任务。*/

	SBO_OBJECT_INTERACT0;
}

/**
*
* 名称：WObject_Interact1
*/
static  RESULT  WObject_Interact1(OBJECT* This, ACTION Act, BYTE* OStrm, BYTKTY Cty, BYTKTY* pQty, const VR* pCaller)
{

	/* ... */


	/* 在上面完成接口自己的任务。*/

	SBO_OBJECT_INTERACT1;
}

/**
*
* 名称：WObject_Interact2
*/
static  RESULT  WObject_Interact2(OBJECT* This, ACTION  Act, BYTE* IStrm, BYTKTY Qty, const VR* pCaller)
{
	VR    caller;

	caller.cr = pCaller->cr;
	caller.mr = This->OID;

	switch(Act)
	{
	case CMD_INITIALIZE:
		assert(sizeof(INIT_WOBJECT) == Qty);
		return WObject__CMD_INITIALIZE(This, (INIT_WOBJECT*)IStrm, &caller);
	default:
		break;
	}


	/* 在上面完成接口自己的任务。*/

	SBO_OBJECT_INTERACT2;
}

/**
*
* 名称：WObject_Interact3
*/
static  RESULT  WObject_Interact3(OBJECT* This, ACTION Act, BYTE* IStrm, BYTKTY Qty, BYTE* OStrm, BYTKTY Cty, BYTKTY* pQty, const VR* pCaller)
{

	/* ... */


	/* 在上面完成接口自己的任务。*/

	SBO_OBJECT_INTERACT3;
}

/**
*
* 名称：WObject_Close
*/
static  RESULT  WObject_Close(OBJECT* This, const VR* pCaller)
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
* 名称：TOG_WObject
*/
VOID  TOG_WObject(OBJECT* pObj)
{
	pObj->Open = WObject_Open;
	pObj->Input = WObject_Input;
	pObj->Output = WObject_Output;
	pObj->IOput = WObject_IOput;
	pObj->Interact0 = WObject_Interact0;
	pObj->Interact1 = WObject_Interact1;
	pObj->Interact2 = WObject_Interact2;
	pObj->Interact3 = WObject_Interact3;
	pObj->Close = WObject_Close;
}

/*====================+ Function(s) +====================*/
/* ... */

/*=======================================================*/

/**
*
* NAME: WObject_I_Open
*/
RESULT  WObject_I_Open(OBJECT* This, const VR* pCaller)
{
	EM_WOBJECT*      pem = (EM_WOBJECT*)This->pEM;
	
	if(1 == This->RefCnt)
	{
		pem->pOIOIC = GetBN(This, MSN_OIOIC);
		pem->pVObject = GetBN(This, MSN_VOBJECT);

		return RP_RCONE;
	}
	
	return R_P;
}

/**
*
* NAME: WObject__CRT_WGI_WINDOW
*/
RESULT  WObject__CRT_WGI_WINDOW(OBJECT* This, const VR* pCaller)
{
	EM_WOBJECT*         pem = (EM_WOBJECT*)This->pEM;
	EM_VOBJECT*         pem_vob = (EM_VOBJECT*)pem->pVObject->pEM;
	EM_WOBJECT*         pem_wob_sup = NULL;
	HWND                hWndParent;
	
	if(pem->hWnd != NULL)
		return RO_VAINLY;

	if(pem_vob->pSuperior != NULL)
		pem_wob_sup = (EM_WOBJECT*)GetEMofBN(pem_vob->pSuperior, MSN_WOBJECT);

	hWndParent = (pem_wob_sup != NULL) ? pem_wob_sup->hWnd : NULL;
	
	pem->hWnd = CreateWindowEx(WS_EX_APPWINDOW, pem->pClassName, pem->pWindowName, WS_POPUP | WS_VISIBLE, 
		pem_vob->rsc.rcouter.left, pem_vob->rsc.rcouter.top, 
		pem_vob->rsc.rcouter.right - pem_vob->rsc.rcouter.left, 
		pem_vob->rsc.rcouter.bottom - pem_vob->rsc.rcouter.top, 
		hWndParent, NULL, pem->hInstance, NULL);
	
	if(NULL == pem->hWnd)
		return R_N;

	pem_vob->pWndHandle = &pem->hWnd;
	SetWindowLong(pem->hWnd, GWL_USERDATA, (LONG)This->po_AND);

	return R_P;

}

/**
*
* NAME: WObject__DTR_WGI_WINDOW
*/
RESULT  WObject__DTR_WGI_WINDOW(OBJECT* This, const VR* pCaller)
{
	EM_WOBJECT*         pem = (EM_WOBJECT*)This->pEM;
	EM_VOBJECT*         pem_vob = (EM_VOBJECT*)pem->pVObject->pEM;
	
	if(NULL == pem->hWnd)
		return RO_VAINLY;

	if(!DestroyWindow(pem->hWnd))
		return R_N;

	pem->hWnd = NULL;
	return R_P;
}

/**
*
* NAME: WObject__CMD_INITIALIZE
*/
RESULT  WObject__CMD_INITIALIZE(OBJECT* This, const INIT_WOBJECT* piwob, const VR* pCaller)
{
	EM_WOBJECT*      pem = (EM_WOBJECT*)This->pEM;
	
	pem->hInstance = piwob->hInstance;
	pem->pClassName = piwob->pClassName;
	pem->pWindowName = piwob->pWindowName;
	
	return R_P;
}
