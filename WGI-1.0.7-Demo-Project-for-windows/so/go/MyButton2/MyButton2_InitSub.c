/**
 *
 * 文 件 名：MyButton2_InitSub.c
 *
 * 描    述：初始化 MyButton2 的各级下级对象的 .c 文件。
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


#include "MyButton2_InitSub.h"
#include "../CObject/CObject.h"


extern  HBITMAP     g_ArrHBITMAP[eNum_BMP];


/**
*
* NAME: MyButton2_InitSub_Button
*/
void  MyButton2_InitSub_Button(OBJECT* This, ESMYBUTTON2  es, const VR* pCaller)
{
	EM_MYBUTTON2*       pem = (EM_MYBUTTON2*)This->pEM;
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
	case eButton_MyButton2:
		ivob.ArrHBITMAP[eVOBState_Normal] = g_ArrHBITMAP[eButton2_Normal_BMP];
		ivob.ArrHBITMAP[eVOBState_FocusOver] = g_ArrHBITMAP[eButton2_FocusOver_BMP];
		ivob.ArrHBITMAP[eVOBState_FocusOn] = g_ArrHBITMAP[eButton2_FocusOn_BMP];
		ivob.ArrHBITMAP[eVOBState_Active] = g_ArrHBITMAP[eButton2_Active_BMP];
		ivob.ArrHBITMAP[eVOBState_ABSInactive] = g_ArrHBITMAP[eButton2_ABSInactive_BMP];
		GetObject(ivob.ArrHBITMAP[eVOBState_Normal], sizeof(bm), &bm);
		ivob.rsc.rcouter.left = MYBUTTON2_BUTTON_L;
		ivob.rsc.rcouter.top = MYBUTTON2_BUTTON_T;
		ivob.rsc.rcouter.right = ivob.rsc.rcouter.left + bm.bmWidth;
		ivob.rsc.rcouter.bottom = ivob.rsc.rcouter.top + bm.bmHeight;
		ivob.rsc.rcinner.left = 4;
		ivob.rsc.rcinner.top = 4;
		ivob.rsc.rcinner.right = ivob.rsc.rcinner.left + bm.bmWidth - 8;
		ivob.rsc.rcinner.bottom = ivob.rsc.rcinner.top + bm.bmHeight - 8;
		ivob.pPrevCodt = pem->ArrSUB[eButton_MyButton2];
		ivob.pNextCodt = pem->ArrSUB[eButton_MyButton2];
		break;
	default:
		assert(0);
		break;
	}

	ivob.maxw_irr = ivob.rsc.rcinner.right - ivob.rsc.rcinner.left;
	ivob.maxh_irr = ivob.rsc.rcinner.bottom - ivob.rsc.rcinner.top;

	icob.pWndHandle = pem_vob->pWndHandle;

	VO_Open(pem->ArrSUB[es], pCaller);
	VO_Interact2(GetBN(pem->ArrSUB[es], MSN_VOBJECT), CMD_INITIALIZE, (BYTE*)&ivob, sizeof(INIT_VOBJECT), pCaller);
	VO_Interact2(GetBN(pem->ArrSUB[es], MSN_COBJECT), CMD_INITIALIZE, (BYTE*)&icob, sizeof(INIT_COBJECT), pCaller);

	return;
}