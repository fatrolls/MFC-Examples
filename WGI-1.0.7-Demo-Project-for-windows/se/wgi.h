/**
 *
 * 文 件 名：wgi.h
 *
 * 描    述：
 *
 * 创 建 者：
 *
 * 创建日期：
 *
 * 版    本：1.0.8
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

#ifndef __WGI_H__
#define __WGI_H__

#include "se.h"


/*
*
* 名称：POLYGON
* 描述：多边形结构体
*/
typedef struct TAG_POLYGON
{
	POINT*    pAPT;
	int       npt;
}POLYGON;


/*
*
* 名称：ZPOLYGON
* 描述：Z轴多边形结构体。
*/
typedef struct TAG_ZPOLYGON
{
	POLYGON     plg;
	int         z;
}ZPOLYGON;


/*=======================================================*/

extern  HBITMAP  LoadPictureFile(const TCHAR* adrame);
extern  BOOL  IsPointInPolygon(int x, int y, const POLYGON*  pplg);
extern  BOOL  IsInter2Rects(const RECT* pSrcRect1, const RECT* pSrcRect2, RECT*  pDstRect);


#endif		/* #ifndef __WGI_H__ */