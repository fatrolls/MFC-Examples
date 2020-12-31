/**
 *
 * 文 件 名：MyButton_InitSub.c
 *
 * 描    述：初始化 MyButton 的各级下级对象的 .c 文件。
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


#include "MyButton_InitSub.h"
#include "../CObject/CObject.h"


/**
*
* NAME: MyButton_InitSub_Button
*/
void  MyButton_InitSub_Button(OBJECT* This, ESMYBUTTON  es, const VR* pCaller)
{
	EM_MYBUTTON*        pem = (EM_MYBUTTON*)This->pEM;
	EM_VOBJECT*         pem_vob = (EM_VOBJECT*)pem->pVObject->pEM;
	INIT_VOBJECT        ivob;
	INIT_COBJECT        icob;
	BITMAP              bm;


	memset(&ivob, 0, sizeof(INIT_VOBJECT));
	memset(&icob, 0, sizeof(INIT_COBJECT));

	ivob.pSuperior = This;
	ivob.rsc.rcinner.left = 0;
	ivob.rsc.rcinner.top = 0;
	ivob.style |= VOBS_NOABSINACTIVE;
	ivob.state = eVOBState_Normal;
	ivob.ArrHBITMAP[eVOBState_Normal] = pem->ArrHBITMAP[eButton_Normal_BMP_MyButton];
	ivob.ArrHBITMAP[eVOBState_FocusOver] = pem->ArrHBITMAP[eButton_FocusOver_BMP_MyButton];
	ivob.ArrHBITMAP[eVOBState_FocusOn] = pem->ArrHBITMAP[eButton_FocusOn_BMP_MyButton];
	ivob.ArrHBITMAP[eVOBState_Active] = pem->ArrHBITMAP[eButton_Active_BMP_MyButton];
	ivob.ArrHBITMAP[eVOBState_ABSInactive] = pem->ArrHBITMAP[eButton_ABSInactive_BMP_MyButton];

	switch(es)
	{
	case eButton1_MyButton:
		ivob.rsc.rcouter.left = MYBUTTON_BUTTON1_L;
		ivob.rsc.rcouter.top = MYBUTTON_BUTTON1_T;
		ivob.pPrevCodt = pem->ArrSUB[eButton3_MyButton];
		ivob.pNextCodt = pem->ArrSUB[eButton2_MyButton];
		break;
	case eButton2_MyButton:
		ivob.rsc.rcouter.left = MYBUTTON_MYBUTTON_L;
		ivob.rsc.rcouter.top = MYBUTTON_MYBUTTON_T;
		ivob.pPrevCodt = pem->ArrSUB[eButton1_MyButton];
		ivob.pNextCodt = pem->ArrSUB[eButton3_MyButton];
		break;
	case eButton3_MyButton:
		ivob.rsc.rcouter.left = MYBUTTON_BUTTON3_L;
		ivob.rsc.rcouter.top = MYBUTTON_BUTTON3_T;
		ivob.pPrevCodt = pem->ArrSUB[eButton2_MyButton];
		ivob.pNextCodt = pem->ArrSUB[eButton1_MyButton];
		break;
	default:
		assert(0);
		break;
	}

	GetObject(ivob.ArrHBITMAP[eVOBState_Normal], sizeof(bm), &bm);

	ivob.rsc.rcinner.right = ivob.rsc.rcinner.left + bm.bmWidth;
	ivob.rsc.rcinner.bottom = ivob.rsc.rcinner.top + bm.bmHeight;
	ivob.rsc.rcouter.right = ivob.rsc.rcouter.left + bm.bmWidth;
	ivob.rsc.rcouter.bottom = ivob.rsc.rcouter.top + bm.bmHeight;
	ivob.maxw_irr = ivob.rsc.rcinner.right - ivob.rsc.rcinner.left;
	ivob.maxh_irr = ivob.rsc.rcinner.bottom - ivob.rsc.rcinner.top;

	icob.pWndHandle = pem_vob->pWndHandle;

	VO_Open(pem->ArrSUB[es], pCaller);
	VO_Interact2(GetBN(pem->ArrSUB[es], MSN_VOBJECT), CMD_INITIALIZE, (BYTE*)&ivob, sizeof(INIT_VOBJECT), pCaller);
	VO_Interact2(GetBN(pem->ArrSUB[es], MSN_COBJECT), CMD_INITIALIZE, (BYTE*)&icob, sizeof(INIT_COBJECT), pCaller);

	return;
}