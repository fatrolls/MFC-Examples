/**
 *
 * 文 件 名：WObject.h
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

#ifndef __WOBJECT_H__
#define __WOBJECT_H__

#include "../go.h"
#include "../VObject/VObject.h"


/*========================+ INIT +=======================*/

/*
*
* 名称：INIT_WOBJECT
*/
typedef struct TAG_INIT_WOBJECT
{
	HINSTANCE        hInstance;
	const TCHAR*     pClassName;
	const TCHAR*     pWindowName;
}INIT_WOBJECT;


/*==================+ Extended Member +==================*/

/*
*
* 名称：EM_WOBJECT
*/
typedef struct TAG_EM_WOBJECT
{
	OBJECT*          pOIOIC;
	OBJECT*          pVObject;
	HINSTANCE        hInstance;
	HWND             hWnd;
	const  TCHAR*    pClassName;
	const  TCHAR*    pWindowName;
}EM_WOBJECT;


#endif		/* #ifndef __WOBJECT_H__ */
