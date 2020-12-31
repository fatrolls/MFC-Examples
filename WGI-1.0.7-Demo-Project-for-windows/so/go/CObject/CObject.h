/**
 *
 * 文 件 名：CObject.h
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

#ifndef __COBJECT_H__
#define __COBJECT_H__

#include "../go.h"
#include "../VObject/VObject.h"


/*========================+ INIT +=======================*/

/*
*
* 名称：INIT_COBJECT
*/
typedef struct TAG_INIT_COBJECT
{
	const HWND*    pWndHandle;
}INIT_COBJECT;


/*==================+ Extended Member +==================*/

/*
*
* 名称：EM_COBJECT
*/
typedef struct TAG_EM_COBJECT
{
	OBJECT*     pOIOIC;
	OBJECT*     pVObject;
}EM_COBJECT;


#endif		/* #ifndef __COBJECT_H__ */
