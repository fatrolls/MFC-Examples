/**
 *
 * 文 件 名：MyDialog_InitSub.c
 *
 * 描    述：初始化 MyDialog 的各级下级对象的 .c 文件。
 *
 * 创 建 者：赵平智   <bruce.zhao.zpz@gmail.com>
 *
 * 创建日期：
 *
 * 备    注：InitSub - initialize subordinate
 *
 *
 * * 维护历史 *
 *
 *   <日期>                <修改者>
 *   <修改内容...>
 *
 **/


#include "MyDialog_InitSub.h"
#include "../CObject/CObject.h"


extern  HBITMAP     g_ArrHBITMAP[eNum_BMP];


/**
*
* NAME: MyDialog_InitSub_Button
*/
void  MyDialog_InitSub_Button(OBJECT* This, ESMYDIALOG  es, const VR* pCaller)
{
	EM_MYDIALOG*         pem = (EM_MYDIALOG*)This->pEM;
	EM_WOBJECT*         pem_wob = (EM_WOBJECT*)pem->pWObject->pEM;
	EM_VOBJECT*         pem_vob = (EM_VOBJECT*)pem->pVObject->pEM;
	INIT_VOBJECT        ivob;
	INIT_COBJECT        icob;
	BITMAP              bm;


	memset(&ivob, 0, sizeof(INIT_VOBJECT));
	memset(&icob, 0, sizeof(INIT_COBJECT));

	ivob.pSuperior = This;
	ivob.style |= VOBS_NOABSINACTIVE;
	ivob.state = eVOBState_Normal;

	switch(es)
	{
	case eTRCClose_MyDialog:
		ivob.ArrHBITMAP[eVOBState_Normal] = g_ArrHBITMAP[eTRCClose_Normal_BMP];
		ivob.ArrHBITMAP[eVOBState_FocusOver] = g_ArrHBITMAP[eTRCClose_FocusOver_BMP];
		ivob.ArrHBITMAP[eVOBState_FocusOn] = g_ArrHBITMAP[eTRCClose_FocusOn_BMP];
		ivob.ArrHBITMAP[eVOBState_Active] = g_ArrHBITMAP[eTRCClose_Normal_BMP];
		GetObject(ivob.ArrHBITMAP[eVOBState_Normal], sizeof(bm), &bm);
		ivob.rsc.rcouter.left = MYDIALOG_TRCCLOSE_L;
		ivob.rsc.rcouter.top = MYDIALOG_TRCCLOSE_T;
		ivob.rsc.rcouter.right = ivob.rsc.rcouter.left + bm.bmWidth;
		ivob.rsc.rcouter.bottom = ivob.rsc.rcouter.top + bm.bmHeight;
		ivob.rsc.rcinner.left = 0;
		ivob.rsc.rcinner.top = 0;
		ivob.rsc.rcinner.right = ivob.rsc.rcinner.left + bm.bmWidth;
		ivob.rsc.rcinner.bottom = ivob.rsc.rcinner.top + bm.bmHeight;
		ivob.pPrevCodt = pem->ArrSUB[eButton3_MyDialog];
		ivob.pNextCodt = pem->ArrSUB[eButton1_MyDialog];
		break;
	case eButton1_MyDialog:
		ivob.ArrHBITMAP[eVOBState_Normal] = pem->ArrHBITMAP[eButton1_Normal_BMP_MyDialog];
		ivob.ArrHBITMAP[eVOBState_FocusOver] = pem->ArrHBITMAP[eButton1_FocusOver_BMP_MyDialog];
		ivob.ArrHBITMAP[eVOBState_FocusOn] = pem->ArrHBITMAP[eButton1_Active_BMP_MyDialog];//pem->ArrHBITMAP[eButton1_FocusOn_BMP_MyDialog];
		ivob.ArrHBITMAP[eVOBState_Active] = pem->ArrHBITMAP[eButton1_Active_BMP_MyDialog];
		ivob.ArrHBITMAP[eVOBState_ABSInactive] = pem->ArrHBITMAP[eButton1_ABSInactive_BMP_MyDialog];
		GetObject(ivob.ArrHBITMAP[eVOBState_Normal], sizeof(bm), &bm);
		ivob.rsc.rcouter.left = MYDIALOG_BUTTON1_L;
		ivob.rsc.rcouter.top = MYDIALOG_BUTTON1_T;
		ivob.rsc.rcouter.right = ivob.rsc.rcouter.left + bm.bmWidth;
		ivob.rsc.rcouter.bottom = ivob.rsc.rcouter.top + bm.bmHeight;
		ivob.rsc.rcinner.left = 0;
		ivob.rsc.rcinner.top = 0;
		ivob.rsc.rcinner.right = ivob.rsc.rcinner.left + bm.bmWidth;
		ivob.rsc.rcinner.bottom = ivob.rsc.rcinner.top + bm.bmHeight;
		ivob.pPrevCodt = pem->ArrSUB[eTRCClose_MyDialog];
		ivob.pNextCodt = pem->ArrSUB[eButton2_MyDialog];
		break;
	case eButton2_MyDialog:
		ivob.ArrHBITMAP[eVOBState_Normal] = g_ArrHBITMAP[eButton2_Normal_BMP];
		ivob.ArrHBITMAP[eVOBState_FocusOver] = g_ArrHBITMAP[eButton2_FocusOver_BMP];
		ivob.ArrHBITMAP[eVOBState_FocusOn] = g_ArrHBITMAP[eButton2_Active_BMP];//g_ArrHBITMAP[eButton2_FocusOn_BMP];
		ivob.ArrHBITMAP[eVOBState_Active] = g_ArrHBITMAP[eButton2_Active_BMP];
		ivob.ArrHBITMAP[eVOBState_ABSInactive] = g_ArrHBITMAP[eButton2_ABSInactive_BMP];
		GetObject(ivob.ArrHBITMAP[eVOBState_Normal], sizeof(bm), &bm);
		ivob.rsc.rcouter.left = MYDIALOG_BUTTON2_L;
		ivob.rsc.rcouter.top = MYDIALOG_BUTTON2_T;
		ivob.rsc.rcouter.right = ivob.rsc.rcouter.left + bm.bmWidth;
		ivob.rsc.rcouter.bottom = ivob.rsc.rcouter.top + bm.bmHeight;
		ivob.rsc.rcinner.left = 4;
		ivob.rsc.rcinner.top = 4;
		ivob.rsc.rcinner.right = ivob.rsc.rcinner.left + bm.bmWidth - 8;
		ivob.rsc.rcinner.bottom = ivob.rsc.rcinner.top + bm.bmHeight - 8;
		ivob.pPrevCodt = pem->ArrSUB[eButton1_MyDialog];
		ivob.pNextCodt = pem->ArrSUB[eButton3_MyDialog];
		break;
	case eButton3_MyDialog:
		ivob.ArrHBITMAP[eVOBState_Normal] = pem->ArrHBITMAP[eButton3_Normal_BMP_MyDialog];
		ivob.ArrHBITMAP[eVOBState_FocusOver] = pem->ArrHBITMAP[eButton3_FocusOver_BMP_MyDialog];
		ivob.ArrHBITMAP[eVOBState_FocusOn] = pem->ArrHBITMAP[eButton3_Active_BMP_MyDialog];//pem->ArrHBITMAP[eButton3_FocusOn_BMP_MyDialog];
		ivob.ArrHBITMAP[eVOBState_Active] = pem->ArrHBITMAP[eButton3_Active_BMP_MyDialog];
		ivob.ArrHBITMAP[eVOBState_ABSInactive] = pem->ArrHBITMAP[eButton3_ABSInactive_BMP_MyDialog];
		GetObject(ivob.ArrHBITMAP[eVOBState_Normal], sizeof(bm), &bm);
		ivob.rsc.rcouter.left = MYDIALOG_BUTTON3_L;
		ivob.rsc.rcouter.top = MYDIALOG_BUTTON3_T;
		ivob.rsc.rcouter.right = ivob.rsc.rcouter.left + bm.bmWidth;
		ivob.rsc.rcouter.bottom = ivob.rsc.rcouter.top + bm.bmHeight;
		ivob.rsc.rcinner.left = 6;
		ivob.rsc.rcinner.top = 6;
		ivob.rsc.rcinner.right = ivob.rsc.rcinner.left + bm.bmWidth - 12;
		ivob.rsc.rcinner.bottom = ivob.rsc.rcinner.top + bm.bmHeight - 12;
		ivob.pPrevCodt = pem->ArrSUB[eButton2_MyDialog];
		ivob.pNextCodt = pem->ArrSUB[eDownloadWGI_MyDialog];
		break;
	case eDownloadWGI_MyDialog:
		ivob.ArrHBITMAP[eVOBState_Normal] = pem->ArrHBITMAP[eDownloadWGI_Normal_BMP_MyDialog];
		ivob.ArrHBITMAP[eVOBState_FocusOver] = pem->ArrHBITMAP[eDownloadWGI_FocusOver_BMP_MyDialog];
		ivob.ArrHBITMAP[eVOBState_FocusOn] = pem->ArrHBITMAP[eDownloadWGI_FocusOn_BMP_MyDialog];
		GetObject(ivob.ArrHBITMAP[eVOBState_Normal], sizeof(bm), &bm);
		ivob.rsc.rcouter.left = MYDIALOG_DOWNLOADWGI_L;
		ivob.rsc.rcouter.top = MYDIALOG_DOWNLOADWGI_T;
		ivob.rsc.rcouter.right = ivob.rsc.rcouter.left + bm.bmWidth;
		ivob.rsc.rcouter.bottom = ivob.rsc.rcouter.top + bm.bmHeight;
		ivob.rsc.rcinner.left = 0;
		ivob.rsc.rcinner.top = 0;
		ivob.rsc.rcinner.right = ivob.rsc.rcinner.left + bm.bmWidth;
		ivob.rsc.rcinner.bottom = ivob.rsc.rcinner.top + bm.bmHeight;
		ivob.pPrevCodt = pem->ArrSUB[eButton3_MyDialog];
		ivob.pNextCodt = pem->ArrSUB[eDownloadOIOIC_MyDialog];
		break;
	case eDownloadOIOIC_MyDialog:
		ivob.ArrHBITMAP[eVOBState_Normal] = pem->ArrHBITMAP[eDownloadOIOIC_Normal_BMP_MyDialog];
		ivob.ArrHBITMAP[eVOBState_FocusOver] = pem->ArrHBITMAP[eDownloadOIOIC_FocusOver_BMP_MyDialog];
		ivob.ArrHBITMAP[eVOBState_FocusOn] = pem->ArrHBITMAP[eDownloadOIOIC_FocusOn_BMP_MyDialog];
		GetObject(ivob.ArrHBITMAP[eVOBState_Normal], sizeof(bm), &bm);
		ivob.rsc.rcouter.left = MYDIALOG_DOWNLOADOIOIC_L;
		ivob.rsc.rcouter.top = MYDIALOG_DOWNLOADOIOIC_T;
		ivob.rsc.rcouter.right = ivob.rsc.rcouter.left + bm.bmWidth;
		ivob.rsc.rcouter.bottom = ivob.rsc.rcouter.top + bm.bmHeight;
		ivob.rsc.rcinner.left = 0;
		ivob.rsc.rcinner.top = 0;
		ivob.rsc.rcinner.right = ivob.rsc.rcinner.left + bm.bmWidth;
		ivob.rsc.rcinner.bottom = ivob.rsc.rcinner.top + bm.bmHeight;
		ivob.pPrevCodt = pem->ArrSUB[eDownloadWGI_MyDialog];
		ivob.pNextCodt = pem->ArrSUB[eTRCClose_MyDialog];
		break;
	default:
		assert(0);
		break;
	}

	ivob.maxw_irr = ivob.rsc.rcinner.right - ivob.rsc.rcinner.left;
	ivob.maxh_irr = ivob.rsc.rcinner.bottom - ivob.rsc.rcinner.top;

	icob.pWndHandle = &pem_wob->hWnd;

	VO_Open(pem->ArrSUB[es], pCaller);
	VO_Interact2(GetBN(pem->ArrSUB[es], MSN_VOBJECT), CMD_INITIALIZE, (BYTE*)&ivob, sizeof(INIT_VOBJECT), pCaller);
	VO_Interact2(GetBN(pem->ArrSUB[es], MSN_COBJECT), CMD_INITIALIZE, (BYTE*)&icob, sizeof(INIT_COBJECT), pCaller);

	return;
}