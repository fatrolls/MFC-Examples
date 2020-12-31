/**
 *
 * 文 件 名：MyDialog.h
 *
 * 描    述：
 *
 * 创 建 者：赵平智
 *
 * 创建日期：2011.08
 *
 * 版    本：1.0.7
 *
 * 版权(C)2005-2011 赵平智。保留所有权利。　
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

#ifndef __MYDIALOG_H__
#define __MYDIALOG_H__

#include "../go.h"
#include "../WPanel/WPanel.h"


/*
*
*  subordinates' coordinates.
*  L - left, T - top. 
*/

#define   MYDIALOG_TRCCLOSE_L                    965   
#define   MYDIALOG_TRCCLOSE_T                    10  

#define   MYDIALOG_BUTTON1_L                     120   
#define   MYDIALOG_BUTTON1_T                     100  

#define   MYDIALOG_BUTTON2_L                     50   
#define   MYDIALOG_BUTTON2_T                     220 

#define   MYDIALOG_BUTTON3_L                     480   
#define   MYDIALOG_BUTTON3_T                     130 

#define   MYDIALOG_DOWNLOADWGI_L                 200   
#define   MYDIALOG_DOWNLOADWGI_T                 670 

#define   MYDIALOG_DOWNLOADOIOIC_L               200   
#define   MYDIALOG_DOWNLOADOIOIC_T               712 



/*
*
* NAME: ESMYDIALOG
* DESC: enumerate subordinates of MyDialog
*/
typedef  enum  TAG_ESMYDIALOG
{
    eTRCClose_MyDialog,  // Close button at top right corner 

	/*- other cobs -*/
    eButton1_MyDialog,
	eButton2_MyDialog,
	eButton3_MyDialog,
	eDownloadWGI_MyDialog,
	eDownloadOIOIC_MyDialog,

	/*- number of enum - */
    eNumSub_MyDialog
}ESMYDIALOG;

/*
*
* NAME: EBITMAP_MYDIALOG
*/
typedef  enum  TAG_EBITMAP_MYDIALOG
{
	/*- Button1 -*/
	eButton1_Normal_BMP_MyDialog,
	eButton1_FocusOver_BMP_MyDialog,
	eButton1_FocusOn_BMP_MyDialog,
	eButton1_Active_BMP_MyDialog,
	eButton1_ABSInactive_BMP_MyDialog,

	/*- Button3 -*/
	eButton3_Normal_BMP_MyDialog,
	eButton3_FocusOver_BMP_MyDialog,
	eButton3_FocusOn_BMP_MyDialog,
	eButton3_Active_BMP_MyDialog,
	eButton3_ABSInactive_BMP_MyDialog,

	/*- DownloadWGI -*/
	eDownloadWGI_Normal_BMP_MyDialog,
	eDownloadWGI_FocusOver_BMP_MyDialog,
	eDownloadWGI_FocusOn_BMP_MyDialog,

	/*- DownloadOIOIC -*/
	eDownloadOIOIC_Normal_BMP_MyDialog,
	eDownloadOIOIC_FocusOver_BMP_MyDialog,
	eDownloadOIOIC_FocusOn_BMP_MyDialog,

	/*- number of enum -*/
    eNum_BMP_MyDialog
}EBITMAP_MYDIALOG;



/*========================+ INIT +=======================*/

/*
*
* 名称：INIT_MYDIALOG
*/
/*typedef struct TAG_INIT_MYDIALOG
{
}INIT_MYDIALOG;*/


/*==================+ Extended Member +==================*/

/*
*
* 名称：EM_MYDIALOG
*/
typedef struct TAG_EM_MYDIALOG
{
	OBJECT*     pOIOIC;
	OBJECT*     pVObject;
	OBJECT*     pWObject;
	OBJECT*     pWPanel;
	HBITMAP     ArrHBITMAP[eNum_BMP_MyDialog];
	OBJECT*     ArrSUB[eNumSub_MyDialog];
}EM_MYDIALOG;


#endif		/* #ifndef __MYDIALOG_H__ */
