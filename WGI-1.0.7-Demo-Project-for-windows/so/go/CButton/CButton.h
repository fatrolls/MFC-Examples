/**
 *
 * 文 件 名：CButton.h
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

#ifndef __CBUTTON_H__
#define __CBUTTON_H__

#include "../go.h"


/*========================+ INIT +=======================*/

/*
*
* 名称：INIT_CBUTTON
*/
/*typedef struct TAG_INIT_CBUTTON
{
}INIT_CBUTTON;*/


/*==================+ Extended Member +==================*/

/*
*
* 名称：EM_CBUTTON
*/
typedef struct TAG_EM_CBUTTON
{
	OBJECT*     pOIOIC;
	OBJECT*     pVObject;
	OBJECT*     pCObject;
}EM_CBUTTON;


#endif		/* #ifndef __CBUTTON_H__ */
