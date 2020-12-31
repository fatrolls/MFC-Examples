/**
 *
 * 文 件 名：Main.c
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
#include "Main.h"
#include "../../go/VObject/VObject.h"
#include "../../go/WObject/WObject.h"

#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>


extern  OBJECT*   g_poMainWnd;
extern  void  LoadBitmaps();
extern  void  UnloadBitmaps();

// Global Variables:
const  TCHAR   g_szDialogClass[] = TEXT("Dialog"); // main window class name.
const  TCHAR   g_szDialogName[] = TEXT("Dialog"); // main window name.
TCHAR   g_szCaption[] = TEXT("WGI 1.0.7 DEMO"); 


/*=====================+ OICC label +====================*/

/*<oicc>*/
/*<ibn> OIOIC </ibn>*/
/*<crt>*/
/*</crt>*/
/*</oicc>*/

/*=====================+ Interface +=====================*/

/**
*
* 名称：Main_Open
*/
static  RESULT  Main_Open(OBJECT* This, const VR* pCaller)
{
	OBS_OBJECT_OPEN_;

	/* 在下面完成接口自己的任务。*/


	if(1 == This->RefCnt)
		return RP_RCONE;


	return R_P;
}

/**
*
* 名称：Main_Input
*/
static  RESULT  Main_Input(OBJECT* This, BYTE* IStrm, BYTKTY Qty, const VR* pCaller)
{

	/* ... */


	/* 在上面完成接口自己的任务。*/

	SBO_OBJECT_INPUT;
}

/**
*
* 名称：Main_Output
*/
static  RESULT  Main_Output(OBJECT* This, BYTE* OStrm, BYTKTY Cty, BYTKTY* pQty, const VR* pCaller)
{

	/* ... */


	/* 在上面完成接口自己的任务。*/

	SBO_OBJECT_OUTPUT;
}

/**
*
* 名称：Main_IOput
*/
static  RESULT  Main_IOput(OBJECT* This, BYTE* IStrm, BYTKTY Qty, BYTE* OStrm, BYTKTY Cty, BYTKTY* pQty, const VR* pCaller)
{

	/* ... */


	/* 在上面完成接口自己的任务。*/

	SBO_OBJECT_IOPUT;
}

/**
*
* 名称：Main_Interact0
*/
static  RESULT  Main_Interact0(OBJECT* This, ACTION Act, const VR* pCaller)
{

	/* ... */


	/* 在上面完成接口自己的任务。*/

	SBO_OBJECT_INTERACT0;
}

/**
*
* 名称：Main_Interact1
*/
static  RESULT  Main_Interact1(OBJECT* This, ACTION Act, BYTE* OStrm, BYTKTY Cty, BYTKTY* pQty, const VR* pCaller)
{

	/* ... */


	/* 在上面完成接口自己的任务。*/

	SBO_OBJECT_INTERACT1;
}

/**
*
* 名称：Main_Interact2
*/
static  RESULT  Main_Interact2(OBJECT* This, ACTION  Act, BYTE* IStrm, BYTKTY Qty, const VR* pCaller)
{

	/* ... */


	/* 在上面完成接口自己的任务。*/

	SBO_OBJECT_INTERACT2;
}

/**
*
* 名称：Main_Interact3
*/
static  RESULT  Main_Interact3(OBJECT* This, ACTION Act, BYTE* IStrm, BYTKTY Qty, BYTE* OStrm, BYTKTY Cty, BYTKTY* pQty, const VR* pCaller)
{

	/* ... */


	/* 在上面完成接口自己的任务。*/

	SBO_OBJECT_INTERACT3;
}

/**
*
* 名称：Main_Close
*/
static  RESULT  Main_Close(OBJECT* This, const VR* pCaller)
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
* 名称：TOG_Main
*/
VOID  TOG_Main(OBJECT* pObj)
{
	pObj->Open = Main_Open;
	pObj->Input = Main_Input;
	pObj->Output = Main_Output;
	pObj->IOput = Main_IOput;
	pObj->Interact0 = Main_Interact0;
	pObj->Interact1 = Main_Interact1;
	pObj->Interact2 = Main_Interact2;
	pObj->Interact3 = Main_Interact3;
	pObj->Close = Main_Close;
}


/*=======================+ Main +========================*/


/**
*
* 名称：WinMain
* 描述：主体函数。
*/
int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
	VR		             caller = {OID_MAIN, OID_WGIDEMO};
	HWND                 hWnd;
	MSG                  msg;
	OBJECT*              pObject;
	INIT_VOBJECT         ivob;
	INIT_WOBJECT         iwob;
	HCURSOR              hCursor;
	RESULT               r;
	BITMAP               bm;
	HBITMAP              hBmpNormal, hBmpFocusOver, hBmpFocusOn, hBmpActive;  // Dialog's bitmaps
	TCHAR                szFilePath[MAX_PATH+1];
	TCHAR*               p;


	if(hWnd = FindWindow(g_szDialogClass, g_szDialogName))
	{
		SetForegroundWindow(hWnd);
		return  0;
	}
				
	hCursor = LoadCursor(NULL, IDC_ARROW);
	SetCursor(hCursor);

	GetModuleFileName(NULL, szFilePath, MAX_PATH);
	p = wcsrchr(szFilePath, L'\\') + 1;
	p += swprintf(p, TEXT("%s"), TEXT("skins\\"));
	
	swprintf(p, TEXT("%s"), TEXT("Dialog_Normal.jpg"));
	hBmpNormal = LoadPictureFile(szFilePath);
	assert(hBmpNormal);

	swprintf(p, TEXT("%s"), TEXT("Dialog_FocusOver.jpg"));
	hBmpFocusOver = LoadPictureFile(szFilePath);
	assert(hBmpFocusOver);

	swprintf(p, TEXT("%s"), TEXT("Dialog_FocusOn.jpg"));
	hBmpFocusOn = LoadPictureFile(szFilePath);
	assert(hBmpFocusOn);

	swprintf(p, TEXT("%s"), TEXT("Dialog_Active.jpg"));
	hBmpActive = LoadPictureFile(szFilePath);
	assert(hBmpActive);

	LoadBitmaps();

    // create and open object
	r = CreateObject(MSN_MYDIALOG, 0, 0, 1, &g_poMainWnd);
	if(RN(r))
		return  -1;
    r = VO_Open(g_poMainWnd, &caller);
	assert(RP(r));

	memset(&ivob, 0, sizeof(INIT_VOBJECT));
	memset(&iwob, 0, sizeof(INIT_WOBJECT));

	GetObject(hBmpNormal, sizeof(bm), &bm);

	ivob.ArrHBITMAP[eVOBState_Normal] = hBmpNormal;
	ivob.ArrHBITMAP[eVOBState_FocusOver] = hBmpFocusOver;
	ivob.ArrHBITMAP[eVOBState_FocusOn] = hBmpFocusOn;
	ivob.ArrHBITMAP[eVOBState_Active] = hBmpActive;
	ivob.rsc.rcouter.left = 50;
	ivob.rsc.rcouter.top = 50;
	ivob.rsc.rcouter.right = ivob.rsc.rcouter.left + bm.bmWidth;
	ivob.rsc.rcouter.bottom = ivob.rsc.rcouter.top + bm.bmHeight;
	ivob.rsc.rcinner.left = 5;
	ivob.rsc.rcinner.top = 5;
	ivob.rsc.rcinner.right = ivob.rsc.rcinner.left + bm.bmWidth - 10;
	ivob.rsc.rcinner.bottom = ivob.rsc.rcinner.top + bm.bmHeight - 10;
	ivob.maxw_irr = ivob.rsc.rcinner.right - ivob.rsc.rcinner.left;
	ivob.maxh_irr = ivob.rsc.rcinner.bottom - ivob.rsc.rcinner.top;
	ivob.state = eVOBState_Active;
	ivob.ci.text = g_szCaption;
	ivob.ci.clen = wcslen(g_szCaption);
	ivob.ci.cpty = sizeof(g_szCaption) / sizeof(TCHAR);
	ivob.ci.format = TF_CENTER;
	ivob.ci.color = RGB(255,255,255);
	ivob.ci.rect.left = 430;
	ivob.ci.rect.top = 50;
	ivob.ci.rect.right = 600;
	ivob.ci.rect.bottom = 100;

	iwob.hInstance = hInstance;
	iwob.pClassName = g_szDialogClass;
	iwob.pWindowName = g_szDialogName;

	pObject = GetBN(g_poMainWnd, MSN_VOBJECT);
	VO_Interact2(pObject, CMD_INITIALIZE, (BYTE*)&ivob, sizeof(INIT_VOBJECT), &caller);
	pObject = GetBN(g_poMainWnd, MSN_WOBJECT);
	VO_Interact2(pObject, CMD_INITIALIZE, (BYTE*)&iwob, sizeof(INIT_WOBJECT), &caller);
	VO_Interact0(g_poMainWnd, CMD_PREPARE, &caller);
	VO_Interact0(g_poMainWnd, CMD_RUN, &caller);

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	// close and destroy object
	r = VO_Close(g_poMainWnd, &caller);
	assert(RP_RCZERO == r);
	DestroyObject(g_poMainWnd); 

	DeleteObject(hBmpNormal);
	DeleteObject(hBmpFocusOver);
	DeleteObject(hBmpFocusOn);
	DeleteObject(hBmpActive);
	UnloadBitmaps();
	DestroyCursor(hCursor);

	_CrtDumpMemoryLeaks();

	return msg.wParam;
}

/*====================+ Function(s) +====================*/
/* ... */

