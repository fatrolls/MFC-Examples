/**
 *
 * 文 件 名：MyDialog.c
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

#include <wchar.h>
#include "MyDialog.h"
#include "MyDialog_InitSub.h"


extern   const  TCHAR    g_szMyDialogClass[]; 
extern   const  TCHAR    g_szMyDialogName[]; 


VOID  TOG_MyDialog(OBJECT* pObj);

static ATOM  MyRegisterClass(OBJECT* This);
static LRESULT CALLBACK MyDialogProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
static void  LoadBitmaps(OBJECT*  This);
static void  UnloadBitmaps(OBJECT*  This);


/*=====================+ OICC label +====================*/

/*<oicc>*/
/*<ibn> WPanel </ibn>*/
/*<crt>*/
RESULT  CRT_MyDialog(OBJID* pOID, BYTKTY IQCty, BYTKTY OQCty, SI32 NumCR, OBJECT** ppObj, BYTE* pExotic)
{
	extern  VOID  InitAIBofND(OBJECT* pND, MLDSN* pMsn, NUMIB nib);
	extern  VOID  InitABNofND(OBJECT* pND, MLDSN* pMsn, NUMBN nbn);
	extern  VOID  TOG_WPanel(OBJECT* pObj);
	extern  VOID  TOG_WObject(OBJECT* pObj);
	extern  VOID  TOG_VObject(OBJECT* pObj);
	extern  VOID  TOG_OIOIC(OBJECT* pObj);


	UI32   ux_ND = 5; 	/* ND数量。*/
	UI32   ux_BN = 10; 	/* 各ND的BN数量之和。*/
	UI32   ux_IB = 4; 	/* 各ND的IBN数量之和。*/
	UI32   ux_CS = NumCR * 15; 	/* 各ND的最少CS数量之和。*/
	UI32   ux_EM = sizeof(EM_MYDIALOG) + sizeof(EM_WPANEL) + sizeof(EM_WOBJECT)
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

		/** MyDialog **/
		pND = (OBJECT*)pIC;
		TOG_MyDialog(pND);
		pND->MSN = MSN_MYDIALOG;
		pND->OID = (*pOID)++;
		pND->po_AND = (OBJECT*)pIC;
		pND->NND = ux_ND;

		/** WPanel **/
		TOG_WPanel(++pND);
		pND->MSN = MSN_WPANEL;
		pND->OID = (*pOID)++;
		pND->po_AND = (OBJECT*)pIC;
		pND->NND = ux_ND;

		/** WObject **/
		TOG_WObject(++pND);
		pND->MSN = MSN_WOBJECT;
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

		/** MyDialog **/
		pND = (OBJECT*)pIC;

		/* - AIB - */
		pND->ppo_AIB = (OBJECT**)p;
		ArrMsn[0] = MSN_WPANEL;
		InitAIBofND(pND, ArrMsn, 1);
		p += sizeof(OBJECT*) * 1;

		/* - ABN - */
		pND->ppo_ABN = (OBJECT**)p;
		ArrMsn[0] = MSN_WPANEL;
		ArrMsn[1] = MSN_WOBJECT;
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
		p += sizeof(EM_MYDIALOG);

		/** WPanel **/
		++pND;

		/* - AIB - */
		pND->ppo_AIB = (OBJECT**)p;
		ArrMsn[0] = MSN_WOBJECT;
		InitAIBofND(pND, ArrMsn, 1);
		p += sizeof(OBJECT*) * 1;

		/* - ABN - */
		pND->ppo_ABN = (OBJECT**)p;
		ArrMsn[0] = MSN_WOBJECT;
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
		p += sizeof(EM_WPANEL);

		/** WObject **/
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
		p += sizeof(EM_WOBJECT);

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
* 名称：MyDialog_Open
*/
static  RESULT  MyDialog_Open(OBJECT* This, const VR* pCaller)
{
	VR	             caller;
	EM_MYDIALOG*      pem;


	OBS_OBJECT_OPEN_;


	/* 在下面完成接口自己的任务。*/

	caller.cr = pCaller->cr;
	caller.mr = This->OID;

	if(1 == This->RefCnt)
	{
		pem = (EM_MYDIALOG*)This->pEM;
		pem->pOIOIC = GetBN(This, MSN_OIOIC); 
		pem->pVObject = GetBN(This, MSN_VOBJECT); 
		pem->pWObject = GetBN(This, MSN_WOBJECT); 
		pem->pWPanel = GetBN(This, MSN_WPANEL);

		CreateObject(MSN_CBUTTON, 0, 0, 1, &pem->ArrSUB[eTRCClose_MyDialog]);
		CreateObject(MSN_CBUTTON, 0, 0, 1, &pem->ArrSUB[eButton1_MyDialog]);
		CreateObject(MSN_MYBUTTON, 0, 0, 1, &pem->ArrSUB[eButton2_MyDialog]);
		CreateObject(MSN_MYBUTTON2, 0, 0, 1, &pem->ArrSUB[eButton3_MyDialog]);
		CreateObject(MSN_CBUTTON, 0, 0, 1, &pem->ArrSUB[eDownloadWGI_MyDialog]);
		CreateObject(MSN_CBUTTON, 0, 0, 1, &pem->ArrSUB[eDownloadOIOIC_MyDialog]);


		LoadBitmaps(This);

		return RP_RCONE;
	}


	return R_P;
}

/**
*
* 名称：MyDialog_Input
*/
static  RESULT  MyDialog_Input(OBJECT* This, BYTE* IStrm, BYTKTY Qty, const VR* pCaller)
{

	/* ... */


	/* 在上面完成接口自己的任务。*/

	SBO_OBJECT_INPUT;
}

/**
*
* 名称：MyDialog_Output
*/
static  RESULT  MyDialog_Output(OBJECT* This, BYTE* OStrm, BYTKTY Cty, BYTKTY* pQty, const VR* pCaller)
{

	/* ... */


	/* 在上面完成接口自己的任务。*/

	SBO_OBJECT_OUTPUT;
}

/**
*
* 名称：MyDialog_IOput
*/
static  RESULT  MyDialog_IOput(OBJECT* This, BYTE* IStrm, BYTKTY Qty, BYTE* OStrm, BYTKTY Cty, BYTKTY* pQty, const VR* pCaller)
{

	/* ... */


	/* 在上面完成接口自己的任务。*/

	SBO_OBJECT_IOPUT;
}

/**
*
* 名称：MyDialog_Interact0
*/
static  RESULT  MyDialog_Interact0(OBJECT* This, ACTION Act, const VR* pCaller)
{
	VR                  caller;
	EM_MYDIALOG*          pem = (EM_MYDIALOG*)This->pEM;
	EM_VOBJECT*         pem_vob = (EM_VOBJECT*)pem->pVObject->pEM;
    EM_WOBJECT*         pem_wob = (EM_WOBJECT*)pem->pWObject->pEM;
	RESULT              r;
	int                 i;
	
    caller.cr = pCaller->cr;
	caller.mr = This->OID;

	switch(Act)
	{
	case CMD_PREPARE:
		if(0 == MyRegisterClass(This))
			return R_N;
		r = VO_Interact0(pem->pWObject, CRT_WGI_WINDOW, &caller);
		assert(RP(r));

		for(i = 0; i<eNumSub_MyDialog; i++)
			MyDialog_InitSub_Button(This, i, &caller);

		for(i = 0; i<eNumSub_MyDialog; i++)
			VO_Interact0(pem->ArrSUB[i], CMD_PREPARE, &caller);

		pem_vob->pFirstSbdt = pem->ArrSUB[eTRCClose_MyDialog];
		VO_Interact0(pem->pVObject, CMD_PREPARE, &caller);
		return R_P;
	case CMD_RUN:
		//SendMessage(pem_wob->hWnd, WM_INITDIALOG, 0, 0);
		ShowWindow(pem_wob->hWnd, SW_SHOW);
		return R_P;
	default:
		break;
	}


	/* 在上面完成接口自己的任务。*/

	SBO_OBJECT_INTERACT0;
}

/**
*
* 名称：MyDialog_Interact1
*/
static  RESULT  MyDialog_Interact1(OBJECT* This, ACTION Act, BYTE* OStrm, BYTKTY Cty, BYTKTY* pQty, const VR* pCaller)
{

	/* ... */


	/* 在上面完成接口自己的任务。*/

	SBO_OBJECT_INTERACT1;
}

/**
*
* 名称：MyDialog_Interact2
*/
static  RESULT  MyDialog_Interact2(OBJECT* This, ACTION  Act, BYTE* IStrm, BYTKTY Qty, const VR* pCaller)
{

	/* ... */


	/* 在上面完成接口自己的任务。*/

	SBO_OBJECT_INTERACT2;
}

/**
*
* 名称：MyDialog_Interact3
*/
static  RESULT  MyDialog_Interact3(OBJECT* This, ACTION Act, BYTE* IStrm, BYTKTY Qty, BYTE* OStrm, BYTKTY Cty, BYTKTY* pQty, const VR* pCaller)
{

	/* ... */


	/* 在上面完成接口自己的任务。*/

	SBO_OBJECT_INTERACT3;
}

/**
*
* 名称：MyDialog_Close
*/
static  RESULT  MyDialog_Close(OBJECT* This, const VR* pCaller)
{
	VR                  caller;
	EM_MYDIALOG*          pem = (EM_MYDIALOG*)This->pEM;
	int                 i;

	OBS_OBJECT_CLOSE_;

	/* 在下面完成接口自己的任务。*/

    caller.cr = pCaller->cr;
	caller.mr = This->OID;

	if(0 == This->RefCnt)
	{
		UnloadBitmaps(This);
		
		for(i = 0; i<eNumSub_MyDialog; i++)
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
* 名称：TOG_MyDialog
*/
VOID  TOG_MyDialog(OBJECT* pObj)
{
	pObj->Open = MyDialog_Open;
	pObj->Input = MyDialog_Input;
	pObj->Output = MyDialog_Output;
	pObj->IOput = MyDialog_IOput;
	pObj->Interact0 = MyDialog_Interact0;
	pObj->Interact1 = MyDialog_Interact1;
	pObj->Interact2 = MyDialog_Interact2;
	pObj->Interact3 = MyDialog_Interact3;
	pObj->Close = MyDialog_Close;
}

/*====================+ Function(s) +====================*/

/**
*
* 名称：MyRegisterClass
* 描述：
*/
static ATOM  MyRegisterClass(OBJECT* This)
{
	EM_MYDIALOG*          pem = (EM_MYDIALOG*)This->pEM;
	EM_WOBJECT*         pem_wob = (EM_WOBJECT*)pem->pWObject->pEM;
	WNDCLASS wc;

	wc.style			= CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc	    = (WNDPROC)MyDialogProc;
	wc.cbClsExtra		= 0;
	wc.cbWndExtra		= 0;
	wc.hInstance		= pem_wob->hInstance;
	wc.hIcon			= LoadIcon(pem_wob->hInstance, MAKEINTRESOURCE(IDI_WGIDEMO));
	wc.hCursor		    = NULL;//LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wc.lpszMenuName	    = NULL;
	wc.lpszClassName	= pem_wob->pClassName;

	return RegisterClass(&wc);
}

/**
*
* 名称：MyDialogProc
* 描述：Mesage handler for dialog.
*/
static LRESULT CALLBACK MyDialogProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static  POINT     s_pt = {0,0};

	VR                caller;
	OBJECT*           This;
	EM_MYDIALOG*      pem;
	EM_VOBJECT*       pem_vob;
	EM_VOBJECT*       pem_vob_sbdt;
	PAINTSTRUCT       ps;
	POINT             pt;
	MOVE              mv;


	caller.cr = OID_MAIN;

	switch (message)
	{
	case WM_INITDIALOG:
		//This = (OBJECT*)GetWindowLong(hWnd, GWL_USERDATA);
		break;
	case WM_PAINT:	
		if(NULL == (This = (OBJECT*)GetWindowLong(hWnd, GWL_USERDATA))) 
			break;
		pem = (EM_MYDIALOG*)This->pEM;
		caller.mr = This->OID;
		BeginPaint(hWnd, &ps);
		VO_Interact0(pem->pWPanel, CMD_WGI_PAINT, &caller);
		EndPaint(hWnd, &ps);
		break;
	case WM_ACTIVATE:
		if(NULL == (This = (OBJECT*)GetWindowLong(hWnd, GWL_USERDATA))) 
			break; 
		pem = (EM_MYDIALOG*)This->pEM;
		caller.mr = This->OID;

		if(WA_CLICKACTIVE == LOWORD(wParam) || WA_ACTIVE == LOWORD(wParam))
			VO_Interact0(pem->pWPanel, MSG_WGI_ACTIVATE, &caller);
		else
			VO_Interact0(pem->pWPanel, MSG_WGI_DEACTIVATE, &caller);

		break;
	case WM_MOUSEMOVE:
		This = (OBJECT*)GetWindowLong(hWnd, GWL_USERDATA);   
		pem = (EM_MYDIALOG*)This->pEM;
		caller.mr = This->OID;
		pem_vob = (EM_VOBJECT*)GetEMofBN(This, MSN_VOBJECT);
		pt.x = GET_X_LPARAM(lParam);
		pt.y = GET_Y_LPARAM(lParam);
		if(wParam != MK_LBUTTON)
		{
			VO_Interact2(pem->pWPanel, MSG_WGI_FOCUSOVERMOVE, (BYTE*)&pt, sizeof(POINT), &caller);
		}else
		{
			VO_Interact2(pem->pWPanel, MSG_WGI_FOCUSONMOVE, (BYTE*)&pt, sizeof(POINT), &caller);
			if(NULL == pem_vob->pCFDownSbdt)
			{
				PostMessage(hWnd, WM_NCLBUTTONDOWN, HTCAPTION, 0);
			}else
			{
				pem_vob_sbdt = (EM_VOBJECT*)GetEMofBN(pem_vob->pCFDownSbdt, MSN_VOBJECT);
				if(NULL == pem_vob_sbdt->pCFDownSbdt)
				{
					if(pem_vob->pCFDownSbdt != pem->ArrSUB[eDownloadWGI_MyDialog]
						&& pem_vob->pCFDownSbdt != pem->ArrSUB[eDownloadOIOIC_MyDialog])
					{
						memset(&mv, 0, sizeof(MOVE));
						mv.dxLR = mv.dxUL = GET_X_LPARAM(lParam) - s_pt.x;
						mv.dyLR = mv.dyUL = GET_Y_LPARAM(lParam) - s_pt.y;
						VO_Interact2(pem_vob->pCFDownSbdt, CMD_WGI_MOVE, (BYTE*)&mv, sizeof(MOVE), &caller);
						
						s_pt.x = GET_X_LPARAM(lParam);
						s_pt.y = GET_Y_LPARAM(lParam);
					}
				}
			}
		}
		break;
	case WM_LBUTTONDOWN:
		This = (OBJECT*)GetWindowLong(hWnd, GWL_USERDATA);   
		pem = (EM_MYDIALOG*)This->pEM;
		caller.mr = This->OID;
		pem_vob = (EM_VOBJECT*)GetEMofBN(This, MSN_VOBJECT);
		pt.x = GET_X_LPARAM(lParam);
		pt.y = GET_Y_LPARAM(lParam);
		VO_Interact2(pem->pWPanel, MSG_WGI_FOCUSDOWN, (BYTE*)&pt, sizeof(POINT), &caller);
		
		if(pem_vob->pCFDownSbdt != NULL)
		{
			if(pem_vob->pCFDownSbdt == pem->ArrSUB[eTRCClose_MyDialog])
			{
				PostMessage(hWnd, WM_CLOSE, 0, 0);
				break;
			}

			s_pt.x = GET_X_LPARAM(lParam);
			s_pt.y = GET_Y_LPARAM(lParam);

			if(pem_vob->pCFDownSbdt == pem->ArrSUB[eDownloadWGI_MyDialog])
				ShellExecute(hWnd, TEXT("open"), TEXT("http://code.google.com/p/oic-wgi/downloads/list"), NULL, NULL, SW_SHOWMAXIMIZED);
			else if(pem_vob->pCFDownSbdt == pem->ArrSUB[eDownloadOIOIC_MyDialog])
				ShellExecute(hWnd, TEXT("open"), TEXT("http://code.google.com/p/oioic/downloads/list"), NULL, NULL, SW_SHOWMAXIMIZED);
			else
				VO_Interact0(pem_vob->pCFDownSbdt, MSG_WGI_ACTIVATE, &caller);
		}

		break;
	case WM_LBUTTONUP:
		This = (OBJECT*)GetWindowLong(hWnd, GWL_USERDATA);   
		pem = (EM_MYDIALOG*)This->pEM;
		caller.mr = This->OID;
		pem_vob = (EM_VOBJECT*)GetEMofBN(This, MSN_VOBJECT);
		pt.x = GET_X_LPARAM(lParam);
		pt.y = GET_Y_LPARAM(lParam);
		VO_Interact2(pem->pWPanel, MSG_WGI_FOCUSUP, (BYTE*)&pt, sizeof(POINT), &caller);
		break;
	case WM_KEYDOWN:
		//This = (OBJECT*)GetWindowLong(hWnd, GWL_USERDATA);
		break;
	case WM_CHAR:
		//This = (OBJECT*)GetWindowLong(hWnd, GWL_USERDATA);
		break;
	case WM_ERASEBKGND:
		return TRUE; // 消除移动窗口闪烁。
	case WM_CLOSE:
		This = (OBJECT*)GetWindowLong(hWnd, GWL_USERDATA);   
		pem = (EM_MYDIALOG*)This->pEM;
		caller.mr = This->OID;
		VO_Interact0(pem->pWObject, DTR_WGI_WINDOW, &caller);
		break;
	case WM_DESTROY:
		PostQuitMessage (0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return TRUE; 
}

/**
*
* NAME: LoadBitmaps
*/
static void  LoadBitmaps(OBJECT*  This)
{
	EM_MYDIALOG*    pem = (EM_MYDIALOG*)This->pEM;
	TCHAR          szFilePath[MAX_PATH+1];
	TCHAR*         p;

	GetModuleFileName(NULL, szFilePath, MAX_PATH);
	p = wcsrchr(szFilePath, L'\\') + 1;
	p += swprintf(p, TEXT("%s"), TEXT("skins\\"));

	/*- Button1 -*/
	swprintf(p, TEXT("%s"), TEXT("Button1_Normal.jpg"));
	pem->ArrHBITMAP[eButton1_Normal_BMP_MyDialog] = LoadPictureFile(szFilePath);

	swprintf(p, TEXT("%s"), TEXT("Button1_FocusOver.jpg"));
	pem->ArrHBITMAP[eButton1_FocusOver_BMP_MyDialog] = LoadPictureFile(szFilePath);

	swprintf(p, TEXT("%s"), TEXT("Button1_FocusOn.jpg"));
	pem->ArrHBITMAP[eButton1_FocusOn_BMP_MyDialog] = LoadPictureFile(szFilePath);

	swprintf(p, TEXT("%s"), TEXT("Button1_Active.jpg"));
	pem->ArrHBITMAP[eButton1_Active_BMP_MyDialog] = LoadPictureFile(szFilePath);

	swprintf(p, TEXT("%s"), TEXT("Button1_ABSInactive.jpg"));
	pem->ArrHBITMAP[eButton1_ABSInactive_BMP_MyDialog] = LoadPictureFile(szFilePath);

	/*- Button3 -*/
	swprintf(p, TEXT("%s"), TEXT("Button3_Normal.jpg"));
	pem->ArrHBITMAP[eButton3_Normal_BMP_MyDialog] = LoadPictureFile(szFilePath);

	swprintf(p, TEXT("%s"), TEXT("Button3_FocusOver.jpg"));
	pem->ArrHBITMAP[eButton3_FocusOver_BMP_MyDialog] = LoadPictureFile(szFilePath);

	swprintf(p, TEXT("%s"), TEXT("Button3_FocusOn.jpg"));
	pem->ArrHBITMAP[eButton3_FocusOn_BMP_MyDialog] = LoadPictureFile(szFilePath);

	swprintf(p, TEXT("%s"), TEXT("Button3_Active.jpg"));
	pem->ArrHBITMAP[eButton3_Active_BMP_MyDialog] = LoadPictureFile(szFilePath);

	swprintf(p, TEXT("%s"), TEXT("Button3_ABSInactive.jpg"));
	pem->ArrHBITMAP[eButton3_ABSInactive_BMP_MyDialog] = LoadPictureFile(szFilePath);

	/*- DownloadWGI -*/
	swprintf(p, TEXT("%s"), TEXT("DownloadWGI_Normal.jpg"));
	pem->ArrHBITMAP[eDownloadWGI_Normal_BMP_MyDialog] = LoadPictureFile(szFilePath);

	swprintf(p, TEXT("%s"), TEXT("DownloadWGI_FocusOver.jpg"));
	pem->ArrHBITMAP[eDownloadWGI_FocusOver_BMP_MyDialog] = LoadPictureFile(szFilePath);

	swprintf(p, TEXT("%s"), TEXT("DownloadWGI_FocusOn.jpg"));
	pem->ArrHBITMAP[eDownloadWGI_FocusOn_BMP_MyDialog] = LoadPictureFile(szFilePath);

	/*- DownloadOIOIC -*/
	swprintf(p, TEXT("%s"), TEXT("DownloadOIOIC_Normal.jpg"));
	pem->ArrHBITMAP[eDownloadOIOIC_Normal_BMP_MyDialog] = LoadPictureFile(szFilePath);

	swprintf(p, TEXT("%s"), TEXT("DownloadOIOIC_FocusOver.jpg"));
	pem->ArrHBITMAP[eDownloadOIOIC_FocusOver_BMP_MyDialog] = LoadPictureFile(szFilePath);

	swprintf(p, TEXT("%s"), TEXT("DownloadOIOIC_FocusOn.jpg"));
	pem->ArrHBITMAP[eDownloadOIOIC_FocusOn_BMP_MyDialog] = LoadPictureFile(szFilePath);

	return;
}

/**
*
* NAME: UnloadBitmaps
*/
static void  UnloadBitmaps(OBJECT*  This)
{
	EM_MYDIALOG*    pem = (EM_MYDIALOG*)This->pEM;
	int            i;

	for(i = 0; i < eNum_BMP_MyDialog; i++)
	{
		if(pem->ArrHBITMAP[i])
			DeleteObject(pem->ArrHBITMAP[i]);
	}

	return;
}
