/**
 *
 * 文 件 名：oioic.h
 *
 * 描    述：OIOIC 节点的 .h 文件。
 *
 * 创 建 者：赵平智   <bruce.zhao.zpz@gmail.com>
 *
 * 创建日期：20050310
 *
 * 版    本：1.0.18
 *
 * 版权(C)2005-2011 赵平智。保留所有权利。　　　
 *
 * 备    注：
 *
 *
 * * 维护历史 *
 *
 *   <日期>             <修改者>
 *   <修改内容...>
 *
 **/

#ifndef __OIOIC_H__
#define __OIOIC_H__
   
#include "o.h"


/*========================+ INIT +=======================*/

/*
*
* 名称：INIT_OIOIC
*/
/*typedef struct TAG_INIT_OIOIC
{
}INIT_OIOIC;*/


/*==================+ Extended Member +==================*/

/*
*
* 名称：EM_OIOIC
*/
typedef struct TAG_EM_OIOIC
{
	QUEUE	   IQ;	/* 输入队列。*/  
	QUEUE	   OQ;  /* 输出队列。*/  
	MODES      mds;	/* 模式集。*/
}EM_OIOIC;


#endif  /* #ifndef __OIOIC_H__ */
