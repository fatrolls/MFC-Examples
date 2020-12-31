/**
 *
 * 文 件 名：MyButton.h
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

#ifndef __MYBUTTON_H__
#define __MYBUTTON_H__

#include "../go.h"


/*
*
*  subordinates' coordinates.
*  L - left, T - top. 
*/

#define   MYBUTTON_BUTTON1_L                 130   
#define   MYBUTTON_BUTTON1_T                 20 

#define   MYBUTTON_MYBUTTON_L                 130   
#define   MYBUTTON_MYBUTTON_T                 100   

#define   MYBUTTON_BUTTON3_L                 130   
#define   MYBUTTON_BUTTON3_T                 260 


/*
*
* NAME: ESMYBUTTON
* DESC: enumerate subordinates of MyButton
*/
typedef  enum  TAG_ESMYBUTTON
{
    eButton1_MyButton,
	eButton2_MyButton,
	eButton3_MyButton,

	/*- number of enum - */
    eNumSub_MyButton
}ESMYBUTTON;

/*
*
* NAME: EBITMAP_MYBUTTON
*/
typedef  enum  TAG_EBITMAP_MYBUTTON
{
	/*- Button -*/
	eButton_Normal_BMP_MyButton,
	eButton_FocusOver_BMP_MyButton,
	eButton_FocusOn_BMP_MyButton,
	eButton_Active_BMP_MyButton,
	eButton_ABSInactive_BMP_MyButton,

	/*- number of enum -*/
    eNum_BMP_MyButton
}EBITMAP_MYBUTTON;

/*========================+ INIT +=======================*/

/*
*
* 名称：INIT_MYBUTTON
*/
/*typedef struct TAG_INIT_MYBUTTON
{
}INIT_MYBUTTON;*/


/*==================+ Extended Member +==================*/

/*
*
* 名称：EM_MYBUTTON
*/
typedef struct TAG_EM_MYBUTTON
{
	OBJECT*     pOIOIC;
	OBJECT*     pVObject;
	OBJECT*     pCObject;
	OBJECT*     pCButton;
	HBITMAP     ArrHBITMAP[eNum_BMP_MyButton];
	OBJECT*     ArrSUB[eNumSub_MyButton];
	POINT       lastpt;
}EM_MYBUTTON;


#endif		/* #ifndef __MYBUTTON_H__ */
