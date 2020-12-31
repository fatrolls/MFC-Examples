/**
 *
 * 文 件 名：VObject.c
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

#include "VObject.h"


RESULT  VObject_I_Open(OBJECT* This, const VR* pCaller);
RESULT  VObject__CMD_INITIALIZE(OBJECT* This, const INIT_VOBJECT* pivob, const VR* pCaller);
RESULT  VObject__MAK_WGI_CURRENTBITMAP0(OBJECT* This, const VR* pCaller);
RESULT  VObject__MAK_WGI_CURRENTBITMAP2(OBJECT* This, const HBITMAP hBmpBkgd, const VR* pCaller);
RESULT  VObject__CMD_WGI_PAINT(OBJECT* This, const VR* pCaller);
RESULT  VObject__MSG_WGI_FOCUSOVERLEAVE(OBJECT* This, const VR* pCaller);
RESULT  VObject__MSG_WGI_FOCUSONLEAVE(OBJECT* This, const VR* pCaller);
RESULT  VObject__MSG_WGI_FOCUSOVERMOVE(OBJECT* This, const POINT pt, const VR* pCaller);
RESULT  VObject__MSG_WGI_FOCUSDOWN(OBJECT* This, const POINT pt, const VR* pCaller);
RESULT  VObject__MSG_WGI_FOCUSUP(OBJECT* This, const POINT pt, const VR* pCaller);
RESULT  VObject__MSG_WGI_FOCUSONMOVE(OBJECT* This, const POINT pt, const VR* pCaller);
RESULT  VObject__MSG_WGI_ACTIVATE(OBJECT* This, const VR* pCaller);
RESULT  VObject__MSG_WGI_DEACTIVATE(OBJECT* This, const VR* pCaller);
RESULT  VObject__CMD_PREPARE(OBJECT* This, const VR* pCaller);
RESULT  VObject_I_Close(OBJECT* This, const VR* pCaller);
RESULT  VObject__CMD_WGI_REPAINTSUPERIOR(OBJECT* This, const VR* pCaller);


static void MakeCurrentBitmap(OBJECT* This, const HBITMAP hBmpBackground);
static void Deactivate(OBJECT* This);


/*=====================+ OICC label +====================*/

/*<oicc>*/
/*<ibn> OIOIC </ibn>*/
/*<crt>*/
/*</crt>*/
/*</oicc>*/

/*=====================+ Interface +=====================*/

/**
*
* 名称：VObject_Open
*/
static  RESULT  VObject_Open(OBJECT* This, const VR* pCaller)
{
	VR    caller;

	caller.cr = pCaller->cr;
	caller.mr = This->OID;

	OBS_OBJECT_OPEN_;

	/* 在下面完成接口自己的任务。*/

	return VObject_I_Open(This, &caller);
}

/**
*
* 名称：VObject_Input
*/
static  RESULT  VObject_Input(OBJECT* This, BYTE* IStrm, BYTKTY Qty, const VR* pCaller)
{

	/* ... */


	/* 在上面完成接口自己的任务。*/

	SBO_OBJECT_INPUT;
}

/**
*
* 名称：VObject_Output
*/
static  RESULT  VObject_Output(OBJECT* This, BYTE* OStrm, BYTKTY Cty, BYTKTY* pQty, const VR* pCaller)
{

	/* ... */


	/* 在上面完成接口自己的任务。*/

	SBO_OBJECT_OUTPUT;
}

/**
*
* 名称：VObject_IOput
*/
static  RESULT  VObject_IOput(OBJECT* This, BYTE* IStrm, BYTKTY Qty, BYTE* OStrm, BYTKTY Cty, BYTKTY* pQty, const VR* pCaller)
{

	/* ... */


	/* 在上面完成接口自己的任务。*/

	SBO_OBJECT_IOPUT;
}

/**
*
* 名称：VObject_Interact0
*/
static  RESULT  VObject_Interact0(OBJECT* This, ACTION Act, const VR* pCaller)
{
	VR      caller;

	caller.cr = pCaller->cr;
	caller.mr = This->OID;

	switch(Act)
	{
	case CMD_PREPARE:
		return VObject__CMD_PREPARE(This, &caller);
	case MAK_WGI_CURRENTBITMAP0:
		return VObject__MAK_WGI_CURRENTBITMAP0(This, &caller);
	case CMD_WGI_PAINT:
		return VObject__CMD_WGI_PAINT(This, &caller);
	case MSG_WGI_FOCUSOVERLEAVE:
		return VObject__MSG_WGI_FOCUSOVERLEAVE(This, &caller);
	case MSG_WGI_FOCUSONLEAVE:
		return VObject__MSG_WGI_FOCUSONLEAVE(This, &caller);
	case MSG_WGI_ACTIVATE:
		return VObject__MSG_WGI_ACTIVATE(This, &caller);
	case MSG_WGI_DEACTIVATE:
		return VObject__MSG_WGI_DEACTIVATE(This, &caller);
	case CMD_WGI_REPAINTSUPERIOR:
		return VObject__CMD_WGI_REPAINTSUPERIOR(This, &caller);
	default:
		break;
	}

	/* 在上面完成接口自己的任务。*/

	SBO_OBJECT_INTERACT0;
}

/**
*
* 名称：VObject_Interact1
*/
static  RESULT  VObject_Interact1(OBJECT* This, ACTION Act, BYTE* OStrm, BYTKTY Cty, BYTKTY* pQty, const VR* pCaller)
{

	/* ... */


	/* 在上面完成接口自己的任务。*/

	SBO_OBJECT_INTERACT1;
}

/**
*
* 名称：VObject_Interact2
*/
static  RESULT  VObject_Interact2(OBJECT* This, ACTION  Act, BYTE* IStrm, BYTKTY Qty, const VR* pCaller)
{
	VR    caller;

	caller.cr = pCaller->cr;
	caller.mr = This->OID;

	switch(Act)
	{
	case CMD_INITIALIZE:
		assert(sizeof(INIT_VOBJECT) == Qty);
		return VObject__CMD_INITIALIZE(This, (INIT_VOBJECT*)IStrm, &caller);
	case MAK_WGI_CURRENTBITMAP2:
		assert(sizeof(HBITMAP) == Qty);
		return VObject__MAK_WGI_CURRENTBITMAP2(This, *(HBITMAP*)IStrm, &caller);
	case MSG_WGI_FOCUSOVERMOVE:
		assert(sizeof(POINT) == Qty);
		return VObject__MSG_WGI_FOCUSOVERMOVE(This, *(POINT*)IStrm, &caller);
	case MSG_WGI_FOCUSUP:
		assert(sizeof(POINT) == Qty);
		return VObject__MSG_WGI_FOCUSUP(This, *(POINT*)IStrm, &caller);
	case MSG_WGI_FOCUSDOWN:
		assert(sizeof(POINT) == Qty);
		return VObject__MSG_WGI_FOCUSDOWN(This, *(POINT*)IStrm, &caller);
	case MSG_WGI_FOCUSONMOVE:
		assert(sizeof(POINT) == Qty);
		return VObject__MSG_WGI_FOCUSONMOVE(This, *(POINT*)IStrm, &caller);
	default:
		break;
	}


	/* 在上面完成接口自己的任务。*/

	SBO_OBJECT_INTERACT2;
}

/**
*
* 名称：VObject_Interact3
*/
static  RESULT  VObject_Interact3(OBJECT* This, ACTION Act, BYTE* IStrm, BYTKTY Qty, BYTE* OStrm, BYTKTY Cty, BYTKTY* pQty, const VR* pCaller)
{

	/* ... */


	/* 在上面完成接口自己的任务。*/

	SBO_OBJECT_INTERACT3;
}

/**
*
* 名称：VObject_Close
*/
static  RESULT  VObject_Close(OBJECT* This, const VR* pCaller)
{
	VR    caller;
	
	caller.cr = pCaller->cr;
	caller.mr = This->OID;
	
	OBS_OBJECT_CLOSE_;
	
	/* 在下面完成接口自己的任务。*/
	
	return VObject_I_Close(This, &caller);
}

/*========================+ TOG +========================*/

/**
*
* 名称：TOG_VObject
*/
VOID  TOG_VObject(OBJECT* pObj)
{
	pObj->Open = VObject_Open;
	pObj->Input = VObject_Input;
	pObj->Output = VObject_Output;
	pObj->IOput = VObject_IOput;
	pObj->Interact0 = VObject_Interact0;
	pObj->Interact1 = VObject_Interact1;
	pObj->Interact2 = VObject_Interact2;
	pObj->Interact3 = VObject_Interact3;
	pObj->Close = VObject_Close;
}

/*====================+ Function(s) +====================*/

/**
*
* 需求编号：	
* 需求功能：	刷新pFirstIIRSbdt所指的双向循环链表。
* 函    数：	void  Refresh_DCLL_pFirstIIRSbdt(OBJECT* This)
* 描    述：	刷新pFirstIIRSbdt所指的双向循环链表。VObject节点函数。
* 参    数：	
* 返    回：	
* 定 义 者：	赵平智
* 设 计 者：	赵平智
* 实 现 者：	赵平智
* 使 用 者：	
* 版    本：	V1.0.8
* 更新日期：	20110713
* 备    注：	DCLL - Doubly Circularly Linked List，双向循环链表。
* 修改记录：	
* 测试要点：	
*/
static void  Refresh_DCLL_pFirstIIRSbdt(OBJECT* This)
{
	EM_VOBJECT*     pem = (EM_VOBJECT*)This->pEM;
	OBJECT*         pSbdt;
	OBJECT*         pIIRSbdt;
	EM_VOBJECT*     pem_sbdt;
	EM_VOBJECT*     pem_IIRsbdt;
	RECT            rc;

	
	if(NULL == pem->pFirstSbdt)
		return;

	pSbdt = pem->pFirstSbdt;
	pIIRSbdt = pem->pFirstIIRSbdt = NULL;
	do
	{
		pem_sbdt = (EM_VOBJECT*)GetEMofBN(pSbdt, MSN_VOBJECT);

		rc = pem_sbdt->rsc.rcouter;
		rc.left += pem->rsc.rcinner.left;
		rc.top += pem->rsc.rcinner.top;
		rc.right += pem->rsc.rcinner.left;
		rc.bottom += pem->rsc.rcinner.top;

		if(IsInter2Rects(&pem->rsc.rcinner, &rc, NULL))
		{
			if(NULL == pem_sbdt->hBmpCurrent)
			{
				/* 没有当前位图，有可能是因为这个下级对象之前不在显示区而被销毁，所以现在需要重新生成当前位图。*/
				MakeCurrentBitmap(GetBN(pSbdt, MSN_VOBJECT), NULL);	
			}

			if(NULL == pIIRSbdt)
			{
				pem->pFirstIIRSbdt = pIIRSbdt = pSbdt;
			}else
			{
				pem_IIRsbdt = (EM_VOBJECT*)GetEMofBN(pIIRSbdt, MSN_VOBJECT);
				pem_IIRsbdt->pNextISIRCodt = pSbdt;
				pem_IIRsbdt = (EM_VOBJECT*)GetEMofBN(pSbdt, MSN_VOBJECT);
				pem_IIRsbdt->pPrevISIRCodt = pIIRSbdt;
				pIIRSbdt = pSbdt;
			}
		}else if(pem_sbdt->hBmpCurrent != NULL)
		{		
			/* 为了节省内存空间，销毁不在显示区的下级对象的当前位图。*/
			DeleteObject(pem_sbdt->hBmpCurrent);
			pem_sbdt->hBmpCurrent = NULL;
		}

		pSbdt = pem_sbdt->pNextCodt;

	}while(pSbdt != pem->pFirstSbdt);

	if(pIIRSbdt != NULL)
	{
		pem_IIRsbdt = (EM_VOBJECT*)GetEMofBN(pIIRSbdt, MSN_VOBJECT);
		pem_IIRsbdt->pNextISIRCodt = pem->pFirstIIRSbdt;
		pem_IIRsbdt = (EM_VOBJECT*)GetEMofBN(pem->pFirstIIRSbdt, MSN_VOBJECT);
		pem_IIRsbdt->pPrevISIRCodt = pIIRSbdt;
	}

	return;
}

/**
*
* 需求编号：	
* 需求功能：	做好内部矩形滚动前的一些数值计算。
* 函    数：	void  CalculateIRRoll(OBJECT* This, long dx, long dy)
* 描    述：	做好内部矩形滚动前的一些数值计算。节点函数，VObject。
* 参    数：	This - [IN] 对象自己；
*               dx - [IN] 沿X坐标轴的滚动增量，可以为负值；
*               dy - [IN] 沿Y坐标轴的滚动增量，可以为负值。
* 返    回：	
* 定 义 者：	赵平智
* 设 计 者：	赵平智
* 实 现 者：	赵平智
* 使 用 者：	
* 版    本：	V1.0.8
* 更新日期：	20110713
* 备    注：	IR - Inner Rectangle。
* 修改记录：	
* 测试要点：	
*/
static  void  CalculateIRRoll(OBJECT* This, long dx, long dy)
{
	EM_VOBJECT*     pem = (EM_VOBJECT*)This->pEM;
	OBJECT*         pSbdt;
	EM_VOBJECT*     pem_sbdt;
	SI32            adx, ady;  /* a: actual */
	SI32            w, h;

    w = pem->rsc.rcinner.right - pem->rsc.rcinner.left;
	h = pem->rsc.rcinner.bottom - pem->rsc.rcinner.top;

	adx = -pem->ox_irr;
	ady = -pem->oy_irr;
	pem->ox_irr += dx;
	pem->oy_irr += dy;

	if(pem->ox_irr > 0)
	{
		pem->ox_irr = 0;
	}else if((pem->maxw_irr + pem->ox_irr) < w)
	{
		pem->ox_irr = -(pem->maxw_irr - w);
		adx = -(adx + pem->ox_irr);
	}

	if(pem->oy_irr > 0)
	{
		pem->oy_irr = 0;
	}else if((pem->maxh_irr + pem->oy_irr) < h)
	{
		pem->oy_irr = -(pem->maxw_irr-h);
		ady = -(ady + pem->oy_irr);
	}

	if((0 == adx && 0 == ady) || NULL == pem->pFirstSbdt)
		return;

	pSbdt = pem->pFirstSbdt;
	do
	{
		pem_sbdt = (EM_VOBJECT*)GetEMofBN(pSbdt, MSN_VOBJECT);
		pem_sbdt->rsc.rcouter.left += adx;
		pem_sbdt->rsc.rcouter.right += adx;
		pem_sbdt->rsc.rcouter.top += ady;
		pem_sbdt->rsc.rcouter.bottom += ady;
		pSbdt = pem_sbdt->pNextCodt;
	}while(pSbdt != pem->pFirstSbdt);

	Refresh_DCLL_pFirstIIRSbdt(This);

	return;
}


/**
*
* 需求编号：	
* 需求功能：	生成当前位图 EM_VOBJECT.hBmpCurrent。
* 函    数：	static void MakeCurrentBitmap(OBJECT* This, const HBITMAP hBmpBackground)
* 描    述：	生成当前位图 EM_VOBJECT.hBmpCurrent。节点函数，VObject。
* 参    数：	This - [IN] 对象自己；
*               hBmpBackground - [IN] 背景位图，背景位图即没有绘制下级对象的干净位图。
* 返    回：	无
* 定 义 者：	赵平智
* 设 计 者：	赵平智
* 实 现 者：	赵平智
* 使 用 者：	
* 版    本：	V1.0
* 更新日期：	20110713
* 备    注：	
* 修改记录：	
* 测试要点：	
*/

static void MakeCurrentBitmap(OBJECT* This, const HBITMAP hBmpBackground)
{
	EM_VOBJECT*     pem = (EM_VOBJECT*)This->pEM;
	EM_VOBJECT*     pem_sbdt;
	OBJECT*         pSbdt;
	HDC             hdc, memdc1, memdc2, memdc3;
	HBITMAP         hBmpBkgd;
	HBITMAP         hBmpInnerRect;  /* the bitmap of inner rectangle */
	HBITMAP         hOrigBmp1, hOrigBmp2, hOrigBmp3;  /* original bitmap */
	HFONT           hOldFont;
	COLORREF        crOldColor;
	BITMAP          bm;
	int             w, h;

	hBmpBkgd = hBmpInnerRect = hOrigBmp1 = hOrigBmp2 = NULL;

	hdc = GetDC(*pem->pWndHandle);
	memdc1 = CreateCompatibleDC(hdc);
	memdc2 = CreateCompatibleDC(hdc);

	hOrigBmp1 = GetCurrentObject(memdc1, OBJ_BITMAP);
	hOrigBmp2 = GetCurrentObject(memdc2, OBJ_BITMAP);

	hBmpBkgd = (NULL == hBmpBackground) ? pem->ArrHBITMAP[pem->state] : hBmpBackground;

	if(pem->hBmpCurrent != NULL)
		DeleteObject(pem->hBmpCurrent);
	w = pem->rsc.rcouter.right - pem->rsc.rcouter.left;
	h = pem->rsc.rcouter.bottom - pem->rsc.rcouter.top;
	pem->hBmpCurrent = CreateCompatibleBitmap(hdc, w, h);
	SelectObject(memdc1, pem->hBmpCurrent);

	if(hBmpBkgd != NULL)
	{
		GetObject(hBmpBkgd, sizeof(bm), &bm);
		SelectObject(memdc2, hBmpBkgd);
		StretchBlt(memdc1, 0, 0, w, h, memdc2, 0, 0, bm.bmWidth, bm.bmHeight, SRCCOPY); 
	}

	SetBkMode(memdc1, TRANSPARENT);
	if(pem->ci.clen > 0)
	{
		if(pem->ci.font)
			hOldFont = SelectObject(memdc1, pem->ci.font);
		crOldColor = SetTextColor(memdc1, pem->ci.color);
		
		DrawText(memdc1, pem->ci.text, pem->ci.clen, &pem->ci.rect, pem->ci.format);
		
		if(pem->ci.font)
			SelectObject(memdc1, hOldFont);
		SetTextColor(memdc1, crOldColor);
	}

	if(pem->pFirstIIRSbdt != NULL)
	{
		if(NULL != GetBN(pem->pFirstIIRSbdt, MSN_COBJECT))
		{
			w = pem->rsc.rcinner.right - pem->rsc.rcinner.left;
			h = pem->rsc.rcinner.bottom - pem->rsc.rcinner.top;
			hBmpInnerRect = CreateCompatibleBitmap(hdc, w, h);
			SelectObject(memdc2, hBmpInnerRect);
			BitBlt(memdc2, 0, 0, w, h, memdc1, pem->rsc.rcinner.left, pem->rsc.rcinner.top, SRCCOPY);
			
			memdc3 = CreateCompatibleDC(hdc);
			hOrigBmp3 = GetCurrentObject(memdc3, OBJ_BITMAP);
			
			pSbdt = pem->pFirstIIRSbdt;
			do
			{
				pem_sbdt = (EM_VOBJECT*)GetEMofBN(pSbdt, MSN_VOBJECT);				
				GetObject(pem_sbdt->hBmpCurrent, sizeof(bm), &bm);
				SelectObject(memdc3, pem_sbdt->hBmpCurrent);
				w = pem_sbdt->rsc.rcouter.right - pem_sbdt->rsc.rcouter.left;
				h = pem_sbdt->rsc.rcouter.bottom - pem_sbdt->rsc.rcouter.top;
				StretchBlt(memdc2, pem_sbdt->rsc.rcouter.left, pem_sbdt->rsc.rcouter.top, w, h, memdc3, 0, 0, bm.bmWidth, bm.bmHeight, SRCCOPY); 
				
				pSbdt = pem_sbdt->pNextISIRCodt;
			}while(pSbdt != pem->pFirstIIRSbdt);
			
			w = pem->rsc.rcinner.right - pem->rsc.rcinner.left;
			h = pem->rsc.rcinner.bottom - pem->rsc.rcinner.top;
			BitBlt(memdc1, pem->rsc.rcinner.left, pem->rsc.rcinner.top, w, h, memdc2, 0, 0, SRCCOPY);
			
			SelectObject(memdc3, hOrigBmp3);
			DeleteDC(memdc3);
		}
	}
	
	ReleaseDC(*pem->pWndHandle, hdc);
	SelectObject(memdc1, hOrigBmp1);
	DeleteDC(memdc1);
	SelectObject(memdc2, hOrigBmp2);
	DeleteDC(memdc2);

	if(hBmpInnerRect != NULL)
		DeleteObject(hBmpInnerRect);


	return;
}

/**
*
* 需求编号：	
* 需求功能：	显示当前位图EM_VOBJECT.hBmpCurrent。
* 函    数：	static void  Paint(OBJECT* This)
* 描    述：	显示当前位图EM_VOBJECT.hBmpCurrent。节点函数，VObject。
* 参    数：	This - [IN] 对象自己。
* 返    回：	无
* 定 义 者：	赵平智
* 设 计 者：	赵平智
* 实 现 者：	赵平智
* 使 用 者：	
* 版    本：	V1.0.8
* 更新日期：	20110713
* 备    注：	
* 修改记录：	
* 测试要点：	
*/
static void  Paint(OBJECT* This)
{
	EM_VOBJECT*     pem = (EM_VOBJECT*)This->pEM;
	EM_VOBJECT*     pem_super; 
	HDC             hdc, memdc;
	HBITMAP         hOrigBmp;   /* original bitmap */
	RECT            rc1, rc2;
	int             w, h, x, y, dx, dy;

	hdc = GetDC(*pem->pWndHandle);
	memdc = CreateCompatibleDC(hdc);
	hOrigBmp = GetCurrentObject(memdc, OBJ_BITMAP);

	do
	{
		if(pem->pSuperior != NULL)
		{
			if(NULL != GetBN(pem->pSuperior, MSN_COBJECT)
				|| NULL != GetBN(pem->pSuperior, MSN_WPANEL))
				break;
		}

		SelectObject(memdc, pem->hBmpCurrent);
		w = pem->rsc.rcouter.right - pem->rsc.rcouter.left;
		h = pem->rsc.rcouter.bottom - pem->rsc.rcouter.top;
		BitBlt(hdc, 0, 0, w, h, memdc, 0, 0, SRCCOPY);
		ReleaseDC(*pem->pWndHandle, hdc);
		SelectObject(memdc, hOrigBmp);
		DeleteDC(memdc);
		return;
	}while(0);



	rc1 = pem->rsc.rcouter;
	dx = rc1.left; 
	dy = rc1.top;
	pem_super = (EM_VOBJECT*)GetEMofBN(pem->pSuperior, MSN_VOBJECT);

	/* 计算对象的显示区域，dx和dy保存外部矩形左上角到Panel对象的外部矩形左上角的距离。*/
	while(1)
	{		
		dx += pem_super->rsc.rcinner.left;
		dy += pem_super->rsc.rcinner.top;
		rc1.left += pem_super->rsc.rcinner.left;
		rc1.top += pem_super->rsc.rcinner.top;
		rc1.right += pem_super->rsc.rcinner.left;
		rc1.bottom += pem_super->rsc.rcinner.top;

		/* 在此永远不会出现不相交的情况，因为如果对象不在显示区就不会调用Paint函数。*/
		IsInter2Rects(&pem_super->rsc.rcinner, &rc1, &rc2);
		
		if(NULL == pem_super->pSuperior)
			break;

		if(NULL == GetBN(pem_super->pSuperior, MSN_COBJECT)
			&& NULL == GetBN(pem_super->pSuperior, MSN_WPANEL))
			break;
		
		dx += pem_super->rsc.rcouter.left;
		dy += pem_super->rsc.rcouter.top;
		rc1 = rc2;
		rc1.left += pem_super->rsc.rcouter.left;
		rc1.top += pem_super->rsc.rcouter.top;
		rc1.right += pem_super->rsc.rcouter.left;
		rc1.bottom += pem_super->rsc.rcouter.top;
		
		pem_super = (EM_VOBJECT*)GetEMofBN(pem_super->pSuperior, MSN_VOBJECT);
	}
	
	x = rc2.left - dx;
	y = rc2.top - dy;
	w = rc2.right - rc2.left;
	h = rc2.bottom - rc2.top;
	SelectObject(memdc, pem->hBmpCurrent);
	BitBlt(hdc, rc2.left, rc2.top, w, h, memdc, x, y, SRCCOPY);


	ReleaseDC(*pem->pWndHandle, hdc);
	SelectObject(memdc, hOrigBmp);
	DeleteDC(memdc);

	return;
}

/**
*
* 需求编号：	
* 需求功能：	重新绘制上级对象。
* 函    数：	static void  RepaintSuperior(OBJECT*  This)
* 描    述：	重新绘制上级对象。节点函数，VObject。
* 参    数：	This - [IN] 对象自己；
* 返    回：	无
* 定 义 者：	赵平智
* 设 计 者：	赵平智
* 实 现 者：	赵平智
* 使 用 者：	
* 版    本：	V1.0.8
* 更新日期：	20110713
* 备    注：	
* 修改记录：	
* 测试要点：	
*/
static void  RepaintSuperior(OBJECT*  This)
{
	EM_VOBJECT*     pem = (EM_VOBJECT*)This->pEM;
	OBJECT*         pVObject_super = GetBN(pem->pSuperior, MSN_VOBJECT);

	assert(pem->pSuperior != NULL);

	MakeCurrentBitmap(pVObject_super, NULL);
	Paint(pVObject_super);

	return;
}

/**
*
* 需求编号：	
* 需求功能：	激活对象
* 函    数：	static void Activate(OBJECT* This)
* 描    述：	激活对象，MSG_WGI_ACTIVATE行为调用。VObject节点函数。
* 参    数：	
* 返    回：	无
* 定 义 者：	赵平智
* 设 计 者：	赵平智
* 实 现 者：	赵平智
* 使 用 者：	
* 版    本：	V1.0.8
* 更新日期：	20110713
* 备    注：	
* 修改记录：	
* 测试要点：	
*/
static void Activate(OBJECT* This)
{
	EM_VOBJECT*     pem = (EM_VOBJECT*)This->pEM;
	OBJECT*         pvob1;
	OBJECT*         pvob2;
	EM_VOBJECT*     pem_vob1;
	EM_VOBJECT*     pem_vob2;
	EVOBSTATE       state;
	
	if(eVOBState_Active == pem->state)
		return;

	state = pem->state;
	pem->state = eVOBState_Active;
	if(pem->ArrHBITMAP[state] != pem->ArrHBITMAP[pem->state])
		MakeCurrentBitmap(This, NULL);
	
	pvob1 = This;
	pvob2 = NULL;
	pem_vob1 = (EM_VOBJECT*) pvob1->pEM;
	while(pem_vob1->pSuperior != NULL)
	{
		pvob2 = GetBN(pem_vob1->pSuperior, MSN_VOBJECT);
		pem_vob2 = (EM_VOBJECT*)pvob2->pEM;

		if(pem_vob2->pActiveSbdt != pvob1->po_AND)
		{
			if(pem_vob2->pActiveSbdt != NULL)
				Deactivate(GetBN(pem_vob2->pActiveSbdt, MSN_VOBJECT));
			pem_vob2->pActiveSbdt = pvob1->po_AND;
		}

		if(pem_vob2->state != eVOBState_Active)
		{		
			pem_vob2->state = eVOBState_Active;
			MakeCurrentBitmap(pvob2, NULL);	
			pvob1 = pvob2;
			pem_vob1 = pem_vob2;
		}else
		{
			MakeCurrentBitmap(pvob2, NULL);
			break;
        }
	}
	
	Paint((NULL == pvob2) ? pvob1 : pvob2);

	return;
}

/**
*
* 需求编号：	
* 需求功能：	使对象退出激活状态
* 函    数：	static void Deactivate(OBJECT* This)
* 描    述：	使对象退出激活状态，MSG_WGI_DEACTIVATE行为调用。VObject节点函数。
* 参    数：	
* 返    回：	无
* 定 义 者：	赵平智
* 设 计 者：	赵平智
* 实 现 者：	赵平智
* 使 用 者：	
* 版    本：	V1.0.8
* 更新日期：	20110713
* 备    注：	
* 修改记录：	
* 测试要点：	
*/
static void Deactivate(OBJECT* This)
{
	EM_VOBJECT*   pem = (EM_VOBJECT*)This->pEM;
	EM_VOBJECT*   pem_vob1;
	EM_VOBJECT*   pem_vob2;
	
	if(pem->state != eVOBState_Active)
		return;
	
	pem_vob1 = (EM_VOBJECT*)This->pEM;
	while(pem_vob1->pActiveSbdt != NULL)
	{
		pem_vob2 = GetEMofBN(pem_vob1->pActiveSbdt, MSN_VOBJECT);
		if(pem_vob2->style & VOBS_NOABSINACTIVE) //如果没有这个状态
		{
			if(pem_vob1->pCFOverSbdt == pem_vob1->pActiveSbdt)
				pem_vob2->state = eVOBState_FocusOver;
			else if(pem_vob1->pCFOnSbdt == pem_vob1->pActiveSbdt)
				pem_vob2->state = eVOBState_FocusOn;
			else
				pem_vob2->state = eVOBState_Normal;
		}else
		{
			pem_vob2->state = eVOBState_ABSInactive;
        }
        pem_vob1= pem_vob2;
	}
	
	while(pem_vob1 != (EM_VOBJECT*)This->pEM)
	{
		pem_vob2 = GetEMofBN(pem_vob1->pSuperior, MSN_VOBJECT);
		MakeCurrentBitmap(GetBN(pem_vob2->pActiveSbdt, MSN_VOBJECT), NULL);
		if(pem_vob1->state != eVOBState_ABSInactive) 
			pem_vob2->pActiveSbdt = NULL;
		pem_vob1 = pem_vob2;
	}
	
	if(pem_vob1->pSuperior != NULL)
	{
		pem_vob2 = GetEMofBN(pem_vob1->pSuperior , MSN_VOBJECT);
		
		if(pem_vob2->pCFOverSbdt == pem_vob2->pActiveSbdt->po_AND)
			pem_vob1->state = eVOBState_FocusOver;
		else if(pem_vob2->pCFOnSbdt == pem_vob2->pActiveSbdt->po_AND)
			pem_vob1->state = eVOBState_FocusOn;
		else
			pem_vob1->state = eVOBState_Normal;
		
		pem_vob2->pActiveSbdt = NULL;
	}else
	{
		pem_vob1->state = eVOBState_Normal;
	}

	MakeCurrentBitmap(This, NULL);
	Paint(This);
}

/*=======================================================*/

/**
*
* NAME: VObject_I_Open
*/
RESULT  VObject_I_Open(OBJECT* This, const VR* pCaller)
{
	EM_VOBJECT*      pem = (EM_VOBJECT*)This->pEM;
	
	if(1 == This->RefCnt)
	{
		pem->pOIOIC = GetBN(This, MSN_OIOIC); 

		return RP_RCONE;
	}
	
	return R_P;
}

/**
*
* NAME: VObject_I_Close
*/
RESULT  VObject_I_Close(OBJECT* This, const VR* pCaller)
{
	EM_VOBJECT*      pem = (EM_VOBJECT*)This->pEM;
	
	if(0 == This->RefCnt)
	{
		if(pem->hBmpCurrent != NULL)
		{
			DeleteObject(pem->hBmpCurrent);
			pem->hBmpCurrent = NULL;
		}

		return RP_RCZERO;
	}


	return R_P;
}

/**
*
* NAME: VObject__CMD_PREPARE
*/
RESULT VObject__CMD_PREPARE(OBJECT* This, const VR* pCaller)
{
	Refresh_DCLL_pFirstIIRSbdt(This);
	MakeCurrentBitmap(This, NULL);
	return R_P;
}

/**
*
* NAME: VObject__MAK_WGI_CURRENTBITMAP0
*/
RESULT  VObject__MAK_WGI_CURRENTBITMAP0(OBJECT* This, const VR* pCaller)
{
	MakeCurrentBitmap(This, NULL);
	return R_P;
}

/**
*
* NAME: VObject__CMD_WGI_REPAINTSUPERIOR
*/
RESULT  VObject__CMD_WGI_REPAINTSUPERIOR(OBJECT* This, const VR* pCaller)
{
	RepaintSuperior(This);
	return R_P;
}

/**
*
* NAME: VObject__CMD_WGI_PAINT
*/
RESULT  VObject__CMD_WGI_PAINT(OBJECT* This, const VR* pCaller)
{
	Paint(This);
	return R_P;
}

/**
*
* NAME: VObject__MSG_WGI_FOCUSOVERLEAVE
*/
RESULT  VObject__MSG_WGI_FOCUSOVERLEAVE(OBJECT* This, const VR* pCaller)
{
	EM_VOBJECT*      pem = (EM_VOBJECT*)This->pEM;
	EVOBSTATE        state;
	
	if(pem->state != eVOBState_Active &&
		pem->state != eVOBState_Selected &&
		pem->state != eVOBState_Disable)
	{
		state = pem->state;
		pem->state = eVOBState_Normal;
		if(pem->ArrHBITMAP[state] != pem->ArrHBITMAP[pem->state])
		{
			MakeCurrentBitmap(This, NULL);
			Paint(This);
		}
	}

	if(pem->pCFOverSbdt != NULL)
		VO_Interact0(pem->pCFOverSbdt, MSG_WGI_FOCUSOVERLEAVE, pCaller);

	return R_P;
}

/**
*
* NAME: VObject__MSG_WGI_FOCUSONLEAVE
* REMARK: 焦点ON-LEAVE与OVER-LEAVE的实现类似，修改时以OVER-LEAVE的实现为准。
*/
RESULT  VObject__MSG_WGI_FOCUSONLEAVE(OBJECT* This, const VR* pCaller)
{
	EM_VOBJECT*      pem = (EM_VOBJECT*)This->pEM;
	EVOBSTATE        state;
	
	if(pem->state != eVOBState_Active &&
		pem->state != eVOBState_Selected &&
		pem->state != eVOBState_Disable)
	{
		state = pem->state;
		pem->state = eVOBState_Normal;
		if(pem->ArrHBITMAP[state] != pem->ArrHBITMAP[pem->state])
		{
			MakeCurrentBitmap(This, NULL);
			Paint(This);
		}
	}

	if(pem->pCFOnSbdt != NULL)
		VO_Interact0(pem->pCFOnSbdt, MSG_WGI_FOCUSONLEAVE, pCaller);

	return R_P;
}

/**
*
* NAME: VObject__MSG_WGI_ACTIVATE
*/
RESULT  VObject__MSG_WGI_ACTIVATE(OBJECT* This, const VR* pCaller)
{
	Activate(This);
	return R_P;
}

/**
*
* NAME: VObject__MSG_WGI_DEACTIVATE
*/
RESULT  VObject__MSG_WGI_DEACTIVATE(OBJECT* This, const VR* pCaller)
{
	Deactivate(This);
	return R_P;
}

/**
*
* NAME: VObject__CMD_INITIALIZE
*/
RESULT  VObject__CMD_INITIALIZE(OBJECT* This, const INIT_VOBJECT* pivob, const VR* pCaller)
{
	EM_VOBJECT*      pem = (EM_VOBJECT*)This->pEM;
	
	pem->pSuperior = pivob->pSuperior;
//	pem->pFirstSbdt = pivob->pFirstSbdt;
	pem->pPrevCodt = pivob->pPrevCodt;
	pem->pNextCodt = pivob->pNextCodt; 
//	pem->pFirstIIRSbdt = pivob->pFirstIIRSbdt;
//	pem->pPrevISIRCodt = pivob->pPrevISIRCodt;
//	pem->pNextISIRCodt = pivob->pNextISIRCodt;
//	pem->ox_irr = pivob->ox_irr;
//	pem->oy_irr = pivob->oy_irr;
	pem->maxw_irr = pivob->maxw_irr;
	pem->maxh_irr = pivob->maxh_irr;
//	pem->hDC = pivob->hDC;
	memcpy(pem->ArrHBITMAP, pivob->ArrHBITMAP, sizeof(pem->ArrHBITMAP));
	pem->style = pivob->style;
	pem->state = pivob->state;
	pem->ci = pivob->ci;
	pem->rsc = pivob->rsc;
	pem->as = pivob->as;
	pem->rgn = pivob->rgn;
	
	return R_P;
}

/**
*
* NAME: VObject__MAK_WGI_CURRENTBITMAP2
*/
RESULT  VObject__MAK_WGI_CURRENTBITMAP2(OBJECT* This, const HBITMAP hBmpBkgd, const VR* pCaller)
{
	MakeCurrentBitmap(This, hBmpBkgd);
	return R_P;
}

/**
*
* NAME: VObject__MSG_WGI_FOCUSOVERMOVE
*/
RESULT  VObject__MSG_WGI_FOCUSOVERMOVE(OBJECT* This, const POINT pt, const VR* pCaller)
{
	EM_VOBJECT*     pem = (EM_VOBJECT*)This->pEM;
	EM_VOBJECT*     pem_sbdt;
	OBJECT*         pIIRSbdt;
	EVOBSTATE       state;
	RESULT          r;
	POINT           pt1;

	if(pem->pCFOverSbdt != NULL)
	{
		if(PtInRect(&pem->rsc.rcinner, pt))
		{
			pt1 = pt;
			pt1.x -= pem->rsc.rcinner.left;
			pt1.y -= pem->rsc.rcinner.top;	

			pem_sbdt = GetEMofBN(pem->pCFOverSbdt, MSN_VOBJECT);

			if(0 == pem_sbdt->as.zp.plg.npt)
				r = PtInRect(&pem_sbdt->rsc.rcouter, pt1) ? R_P : R_N;
			else
				r = IsPointInPolygon(pt1.x - pem_sbdt->rsc.rcouter.left, pt1.y - pem_sbdt->rsc.rcouter.top, &pem_sbdt->as.zp.plg) ? R_P : R_N;
			
			if(R_P == r)
			{
				pt1.x -= pem_sbdt->rsc.rcouter.left;
				pt1.y -= pem_sbdt->rsc.rcouter.top;	
				VO_Interact2(pem->pCFOverSbdt, MSG_WGI_FOCUSOVERMOVE, (BYTE*)&pt1, sizeof(POINT), pCaller);
				return R_P; 
			}
		}
		
		VO_Interact0(pem->pCFOverSbdt, MSG_WGI_FOCUSOVERLEAVE, pCaller);
		pem->pCFOverSbdt = NULL;
	}


    if(pem->state != eVOBState_Active &&
		pem->state != eVOBState_Selected &&
		pem->state != eVOBState_Disable &&
		pem->state != eVOBState_FocusOver)
	{
		state = pem->state;
		pem->state = eVOBState_FocusOver;
		if(pem->ArrHBITMAP[state] != pem->ArrHBITMAP[pem->state])
		{
			MakeCurrentBitmap(This, NULL);
			Paint(This);
		}
	}

	if(NULL == pem->pFirstIIRSbdt)
		return R_P; 

	pIIRSbdt = pem->pFirstIIRSbdt;
	while(1)
	{
		pt1 = pt;
		pt1.x -= pem->rsc.rcinner.left;
		pt1.y -= pem->rsc.rcinner.top;
		pem_sbdt = GetEMofBN(pIIRSbdt, MSN_VOBJECT);
		if(PtInRect(&pem->rsc.rcinner, pt) 
			&& PtInRect(&pem_sbdt->rsc.rcouter, pt1) 
			&& pem_sbdt->state != eVOBState_Hidden)
		{
			pem->pCFOverSbdt = pIIRSbdt;
			VO_Interact2(pem->pCFOverSbdt, MSG_WGI_FOCUSOVERMOVE, (BYTE*)&pt1, sizeof(POINT), pCaller);
			break;
		}else if(pem_sbdt->pPrevISIRCodt != pem->pFirstIIRSbdt)
		{
			pIIRSbdt = pem_sbdt->pPrevISIRCodt;
		}else
		{
			pem->pCFOverSbdt = NULL;
			break;
		}
	}

	return R_P;
}


/**
*
* NAME: VObject__MSG_WGI_FOCUSDOWN
*/
RESULT  VObject__MSG_WGI_FOCUSDOWN(OBJECT* This, const POINT pt, const VR* pCaller)
{
	EM_VOBJECT*     pem = (EM_VOBJECT*)This->pEM;
	EM_VOBJECT*     pem_sbdt;
	EVOBSTATE       state;
	POINT           pt1;

	pem->pCFDownSbdt = pem->pCFOnSbdt = pem->pCFOverSbdt;

	if(pem->state != eVOBState_Active &&
		pem->state != eVOBState_Selected &&
		pem->state != eVOBState_Disable)
	{
		state = pem->state;
		pem->state = eVOBState_FocusOn;
		if(pem->ArrHBITMAP[state] != pem->ArrHBITMAP[pem->state])
		{
			MakeCurrentBitmap(This, NULL);
			Paint(This);
		}
	}

	if(pem->pCFDownSbdt != NULL)
	{
		pem->pCFOverSbdt = NULL;

		pt1 = pt;
		pem_sbdt = GetEMofBN(pem->pCFDownSbdt, MSN_VOBJECT);
		pt1.x -= pem->rsc.rcinner.left + pem_sbdt->rsc.rcouter.left;
		pt1.y -= pem->rsc.rcinner.top + pem_sbdt->rsc.rcouter.top;
		VO_Interact2(pem->pCFDownSbdt, MSG_WGI_FOCUSDOWN, (BYTE*)&pt1, sizeof(POINT), pCaller);
	}

	return R_P;
}

/**
*
* NAME: VObject__MSG_WGI_FOCUSUP
* REMARK: 焦点UP与DOWN的实现类似，修改时以DOWN的实现为准。
*/
RESULT  VObject__MSG_WGI_FOCUSUP(OBJECT* This, const POINT pt, const VR* pCaller)
{
	EM_VOBJECT*     pem = (EM_VOBJECT*)This->pEM;
	EM_VOBJECT*     pem_sbdt;
	EVOBSTATE       state;
	POINT           pt1;

	pem->pCFUpSbdt = pem->pCFOverSbdt = pem->pCFOnSbdt;

	if(pem->state != eVOBState_Active &&
		pem->state != eVOBState_Selected &&
		pem->state != eVOBState_Disable)
	{
		state = pem->state;
		pem->state = eVOBState_FocusOver;
		if(pem->ArrHBITMAP[state] != pem->ArrHBITMAP[pem->state])
		{
			MakeCurrentBitmap(This, NULL);
			Paint(This);
		}
	}

	if(pem->pCFUpSbdt != NULL)
	{
		pem->pCFOnSbdt = NULL;

		pt1 = pt;
		pem_sbdt = GetEMofBN(pem->pCFUpSbdt, MSN_VOBJECT);
		pt1.x -= pem->rsc.rcinner.left + pem_sbdt->rsc.rcouter.left;
		pt1.y -= pem->rsc.rcinner.top + pem_sbdt->rsc.rcouter.top;
		VO_Interact2(pem->pCFUpSbdt, MSG_WGI_FOCUSUP, (BYTE*)&pt1, sizeof(POINT), pCaller);
	}

	return R_P;
}

/**
*
* NAME: VObject__MSG_WGI_FOCUSONMOVE
* REMARK: 焦点ON-MOVE与OVER-MOVE的实现类似，修改时以OVER-MOVE的实现为准。
*/
RESULT  VObject__MSG_WGI_FOCUSONMOVE(OBJECT* This, const POINT pt, const VR* pCaller)
{
	EM_VOBJECT*     pem = (EM_VOBJECT*)This->pEM;
	EM_VOBJECT*     pem_sbdt;
	OBJECT*         pIIRSbdt;
	EVOBSTATE       state;
	RESULT          r;
	POINT           pt1;

	if(pem->pCFOnSbdt != NULL)
	{
		if(PtInRect(&pem->rsc.rcinner, pt))
		{
			pt1 = pt;
			pt1.x -= pem->rsc.rcinner.left;
			pt1.y -= pem->rsc.rcinner.top;	

			pem_sbdt = GetEMofBN(pem->pCFOnSbdt, MSN_VOBJECT);

			if(0 == pem_sbdt->as.zp.plg.npt)
				r = PtInRect(&pem_sbdt->rsc.rcouter, pt1) ? R_P : R_N;
			else
				r = IsPointInPolygon(pt1.x - pem_sbdt->rsc.rcouter.left, pt1.y - pem_sbdt->rsc.rcouter.top, &pem_sbdt->as.zp.plg) ? R_P : R_N;
			
			if(R_P == r)
			{
				pt1.x -= pem_sbdt->rsc.rcouter.left;
				pt1.y -= pem_sbdt->rsc.rcouter.top;	
				VO_Interact2(pem->pCFOnSbdt, MSG_WGI_FOCUSONMOVE, (BYTE*)&pt1, sizeof(POINT), pCaller);
				return R_P; 
			}
		}
		
		VO_Interact0(pem->pCFOnSbdt, MSG_WGI_FOCUSONLEAVE, pCaller);
		pem->pCFOnSbdt = NULL;
	}


    if(pem->state != eVOBState_Active &&
		pem->state != eVOBState_Selected &&
		pem->state != eVOBState_Disable &&
		pem->state != eVOBState_FocusOn)
	{
		state = pem->state;
		pem->state = eVOBState_FocusOn;
		if(pem->ArrHBITMAP[state] != pem->ArrHBITMAP[pem->state])
		{
			MakeCurrentBitmap(This, NULL);
			Paint(This);
		}
	}

	if(NULL == pem->pFirstIIRSbdt)
		return R_P; 

	pIIRSbdt = pem->pFirstIIRSbdt;
	while(1)
	{
		pt1 = pt;
		pt1.x -= pem->rsc.rcinner.left;
		pt1.y -= pem->rsc.rcinner.top;
		pem_sbdt = GetEMofBN(pIIRSbdt, MSN_VOBJECT);
		if(PtInRect(&pem->rsc.rcinner, pt) 
			&& PtInRect(&pem_sbdt->rsc.rcouter, pt1) 
			&& pem_sbdt->state != eVOBState_Hidden)
		{
			pem->pCFOnSbdt = pIIRSbdt;
			VO_Interact2(pem->pCFOnSbdt, MSG_WGI_FOCUSONMOVE, (BYTE*)&pt1, sizeof(POINT), pCaller);
			break;
		}else if(pem_sbdt->pPrevISIRCodt != pem->pFirstIIRSbdt)
		{
			pIIRSbdt = pem_sbdt->pPrevISIRCodt;
		}else
		{
			pem->pCFOnSbdt = NULL;
			break;
		}
	}

	return R_P;
}
