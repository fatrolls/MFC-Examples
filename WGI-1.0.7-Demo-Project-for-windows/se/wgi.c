/**
 *
 * 文 件 名：wgi.c
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

#include <olectl.h>
#include "se.h"


/**
*
* 需求编号：	
* 需求功能：	加载图片文件。
* 函    数：	HBITMAP  LoadPictureFile(const TCHAR* adrame)
* 描    述：	加载图片文件，SE函数。
* 参    数：	adrame - [IN] address and name，图片地址和名称。
* 返    回：	非NULL - 加载成功；NULL - 加载失败。
* 定 义 者：	赵平智
* 设 计 者：	赵平智
* 实 现 者：	赵平智
* 使 用 者：	
* 版    本：	V1.0
* 更新日期：	20110713
* 备    注：	
* 修改记录：	
* 测试要点：		
*/
HBITMAP  LoadPictureFile(const TCHAR* adrame)
{ 
	HANDLE hFile; 
	HBITMAP hBmp; 
	DWORD dwSize; 
	DWORD dwRead; 
	HGLOBAL hMemJpeg; 
	LPSTREAM lpStream; 
	OLE_HANDLE hJpegBmp; 
	HRESULT hr; 
	LPPICTURE lpPicture = NULL; 
	void *pMemJpeg; 
	
	/* Open the file and get the size. */ 
	if((hFile = CreateFile(adrame, GENERIC_READ, FILE_SHARE_READ, 
		NULL, OPEN_EXISTING, 0, NULL)) == INVALID_HANDLE_VALUE) 
		return NULL; 
	if((dwSize = GetFileSize(hFile, NULL)) == 0xFFFFFFFF) 
	{ 
		CloseHandle(hFile); 
		return NULL; 
	} 
	
	/* Allocate space for file, read it in, and then close the file again. */ 
	if((hMemJpeg = GlobalAlloc(GMEM_MOVEABLE, dwSize)) == NULL) 
	{ 
		CloseHandle(hFile); 
		return NULL; 
	} 
	if((pMemJpeg = GlobalLock(hMemJpeg)) == NULL) 
	{ 
		CloseHandle(hFile); 
		GlobalFree(hMemJpeg); 
		return NULL; 
	} 
	if(!ReadFile(hFile, pMemJpeg, dwSize, &dwRead, NULL)) 
	{ 
		CloseHandle(hFile); 
		GlobalFree(hMemJpeg); 
		return NULL; 
	} 
	CloseHandle(hFile); 
	GlobalUnlock(hMemJpeg); 
	
	/* Create the stream and load the picture. */ 
	if((hr = CreateStreamOnHGlobal(hMemJpeg, TRUE, &lpStream)) != S_OK) 
	{ 
		GlobalFree(hMemJpeg); 
		return NULL; 
	} 
	if(OleLoadPicture(lpStream, dwSize, FALSE, &IID_IPicture, &lpPicture) != S_OK) 
	{ 
		GlobalFree(hMemJpeg); 
		lpStream->lpVtbl->Release(lpStream); 
		return NULL; 
	} 
	
	/* Get the handle to the image, and then copy it. */ 
	if((lpPicture->lpVtbl->get_Handle(lpPicture, &hJpegBmp)) != S_OK) 
	{ 
		GlobalFree(hMemJpeg); 
		lpStream->lpVtbl->Release(lpStream); 
		lpPicture->lpVtbl->Release(lpPicture); 
		return NULL; 
	} 
	if((hBmp = CopyImage((HANDLE *) hJpegBmp, IMAGE_BITMAP, 0, 0, LR_COPYRETURNORG)) == NULL) 
	{ 
		GlobalFree(hMemJpeg); 
		lpStream->lpVtbl->Release(lpStream); 
		lpPicture->lpVtbl->Release(lpPicture); 
		return NULL; 
	} 
	
	/* Free the original image and memory. */ 
	GlobalFree(hMemJpeg); 
	lpStream->lpVtbl->Release(lpStream); 
	lpPicture->lpVtbl->Release(lpPicture); 

	return hBmp; 

} /* End of LoadPictureFile(). */  


/**
*
* 需求编号：	
* 需求功能：	判断一点是否在一个多边形内。
* 函    数：	BOOL  IsPointInPolygon(int x, int y, const POLYGON*  pplg)
* 描    述：	判断一点是否在一个多边形内，SE函数。
* 参    数：	x - [IN] 点的X轴坐标； 
*               y - [IN] 点的Y轴坐标；
*               pplg - [IN] 指向多边形。
* 返    回：	TRUE - 点在多边形内，FALSE - 点不在多边形内。
* 定 义 者：	赵平智
* 设 计 者：	赵平智
* 实 现 者：	赵平智
* 使 用 者：	
* 版    本：	V1.0.8
* 更新日期：	20110713
* 备    注：	
* 修改记录：	
* 测试要点：	
*/
BOOL  IsPointInPolygon(int x, int y, const POLYGON*  pplg)
{
	return TRUE;
}

/**
*
* 需求编号：	
* 需求功能：	判断两个在同一平面的矩形是否相交。
* 函    数：	BOOL  IsInter2Rects(const RECT* pSrcRect1, const RECT* pSrcRect2, RECT*  pDstRect)
* 描    述：	判断两个在同一平面的矩形是否相交（包括内含），SE函数。
* 参    数：	pSrcRect1 - [IN] 第一个平面多边形。
*               pSrcRect2 - [IN] 第二个平面多边形。
*               pDstRect - [OUT] 这个参数可以为NULL，如果不为NULL,输出两个矩形相交的部分（也是矩形）,如果两个矩形不相交,就把这个结构体置空。
* 返    回：	TRUE - 两平面矩形相交，FALSE - 两平面矩形不相交。
* 定 义 者：	赵平智
* 设 计 者：	赵平智
* 实 现 者：	赵平智
* 使 用 者：	
* 版    本：	V1.0.8
* 更新日期：	20110713
* 备    注：	
* 修改记录：	
* 测试要点：	
*/
BOOL  IsInter2Rects(const RECT* pSrcRect1, const RECT* pSrcRect2, RECT*  pDstRect)
{
	if(NULL == pDstRect)
	{
		RECT  rc;
		return IntersectRect(&rc, pSrcRect1, pSrcRect2);
	}else
	{
		return IntersectRect(pDstRect, pSrcRect1, pSrcRect2);
	}
}
