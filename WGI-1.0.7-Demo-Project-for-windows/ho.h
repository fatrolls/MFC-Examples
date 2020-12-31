/**
 *
 * 文 件 名：ho.h
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

#ifndef __HO_WGIDEMO_H__
#define __HO_WGIDEMO_H__

#include <stdlib.h>
#include <memory.h>
#include "resource.h"
#include "oioic/oioic.h"


/*========================+ OID +========================*/

/* 注意：在目前操作系统下，尽管大多情况不需要创建HO和AO，但它
*  们的OID是必需的！不需要创建的HO或AO就在这里为它们定义OID。*/

#define   OID_HO           (0x0000000000010000 | OID_OS)  /* HO的OID。*/
#define   OID_WGIDEMO      (OID_HO + 0) /* wgidemo的OID。HO */
#define   OID_MAIN         (OID_HO + 1) /* Main的OID。AO */
/* #define   OID_XXX3      (OID_HO + 2) /-* xxx3的OID。.. *-/ */
/* ...     ...     ...     ...     ...     ... */
#define   OID_             (OID_HO + 3) /* 其它OID的起点。*/


/*========================+ MSN +========================*/

#define   MSN_WGIDEMO      (MSN_ + 0)  /* wgidemo的MSN。HO */
#define   MSN_MAIN         (MSN_ + 1)  /* Main的MSN。AO */
#define   MSN_VOBJECT      (MSN_ + 2)  /* VObject的MSN。GO */
#define   MSN_WOBJECT      (MSN_ + 3)  /* WObject的MSN。GO */
#define   MSN_COBJECT      (MSN_ + 4)  /* CObject的MSN。GO */
#define   MSN_WPANEL       (MSN_ + 5)  /* WPanel的MSN。GO */
#define   MSN_CBUTTON      (MSN_ + 6)  /* CButton的MSN。GO */
#define   MSN_MYDIALOG     (MSN_ + 7)  /* MyDialog的MSN。GO */
#define   MSN_MYBUTTON     (MSN_ + 8)  /* MyButton的MSN。GO */
#define   MSN_MYBUTTON2    (MSN_ + 9)  /* MyButton2的MSN。GO */

/* ...     ...     ...     ...     ...     ... */


/*=======================+ Result +======================*/

/* ...     ...     ...     ...     ...     ... */
/* #define     RN_XXXXX              (RN_ - 1) */
/* #define     RN_XXXXX              (RN_ - 0) */
/** N 结果（上）：**/

/* ...     ...     ...     ...     ...     ... */
/* #define     RO_XXXXX             (RON_ - 1) */
/* #define     RO_XXXXX             (RON_ - 0) */
/**
** 负 O 结果（上）：
**
** 正 O 结果（下）：
**/
/* #define     RO_XXXXX             (ROP_ + 0) */
/* #define     RO_XXXXX             (ROP_ + 1) */
/* ...     ...     ...     ...     ...     ... */

/** P 结果（下）：**/
/* #define     RP_XXXXX              (RP_ + 0) */
/* #define     RP_XXXXX              (RP_ + 1) */
/* ...     ...     ...     ...     ...     ... */


/*=======================+ Action +======================*/

/** AC0 行为：**/
#define     CMD_WGI_PAINT             (AC0_ + 0)
#define     MSG_WGI_FOCUSOVERLEAVE    (AC0_ + 1)
#define     MSG_WGI_FOCUSONLEAVE      (AC0_ + 2)
#define     MSG_WGI_ACTIVATE          (AC0_ + 3)
#define     MSG_WGI_DEACTIVATE        (AC0_ + 4)
#define     MAK_WGI_CURRENTBITMAP0    (AC0_ + 5)
#define     CRT_WGI_WINDOW            (AC0_ + 6)
#define     DTR_WGI_WINDOW            (AC0_ + 7)
#define     CMD_WGI_REPAINTSUPERIOR   (AC0_ + 8)
/* ...     ...     ...     ...     ...     ... */

/** AC1 行为：**/
/* #define     XXX_YYYYY            (AC1_ + 0) */
/* #define     XXX_YYYYY            (AC1_ + 1) */
/* ...     ...     ...     ...     ...     ... */

/** AC2 行为：**/
#define     MSG_WGI_FOCUSOVERMOVE       (AC2_ + 0)
#define     MSG_WGI_FOCUSONMOVE         (AC2_ + 1)
#define     MSG_WGI_FOCUSDOWN           (AC2_ + 2)
#define     MSG_WGI_FOCUSUP             (AC2_ + 3)
#define     MAK_WGI_CURRENTBITMAP2      (AC2_ + 4)
#define     MAK_WGI_CURRENTBITMAP2      (AC2_ + 4)
#define     CMD_WGI_MOVE                (AC2_ + 5)
/* ...     ...     ...     ...     ...     ... */

/** AC3 行为：**/
/* #define     XXX_YYYYY            (AC3_ + 0) */
/* #define     XXX_YYYYY            (AC3_ + 1) */
/* ...     ...     ...     ...     ...     ... */


/*=======================================================*/


#endif		/* #ifndef __HO_WGIDEMO_H__ */
