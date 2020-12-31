/**
 *
 * 文 件 名：WPanel.h
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

#ifndef __WPANEL_H__
#define __WPANEL_H__

#include "../go.h"
#include "../WObject/WObject.h"


#define GET_X_LPARAM(lp)   ((int)(short)LOWORD(lp))
#define GET_Y_LPARAM(lp)   ((int)(short)HIWORD(lp))


/*========================+ INIT +=======================*/

/*
*
* 名称：INIT_WPANEL
*/
/*typedef struct TAG_INIT_WPANEL
{
}INIT_WPANEL;*/


/*==================+ Extended Member +==================*/

/*
*
* 名称：EM_WPANEL
*/
typedef struct TAG_EM_WPANEL
{
	OBJECT*     pOIOIC;
	OBJECT*     pVObject;
	OBJECT*     pWObject;
}EM_WPANEL;


#endif		/* #ifndef __WPANEL_H__ */
