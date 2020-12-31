/**
 *
 * 文 件 名：se.c
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

#include <wchar.h>
#include "se.h"


HBITMAP     g_ArrHBITMAP[eNum_BMP];


/**
*
* NAME: LoadBitmaps
* DESC: load resource of bitmaps
*/
void  LoadBitmaps()
{
	TCHAR                szFilePath[MAX_PATH+1];
	TCHAR*               p;

	GetModuleFileName(NULL, szFilePath, MAX_PATH);
	p = wcsrchr(szFilePath, L'\\') + 1;
	p += swprintf(p, TEXT("%s"), TEXT("skins\\"));

	/*- TRCClose -*/
	swprintf(p, TEXT("%s"), TEXT("TRCClose_Normal.jpg"));
	g_ArrHBITMAP[eTRCClose_Normal_BMP] = LoadPictureFile(szFilePath);

	swprintf(p, TEXT("%s"), TEXT("TRCClose_FocusOver.jpg"));
	g_ArrHBITMAP[eTRCClose_FocusOver_BMP] = LoadPictureFile(szFilePath);

	swprintf(p, TEXT("%s"), TEXT("TRCClose_FocusOn.jpg"));
	g_ArrHBITMAP[eTRCClose_FocusOn_BMP] = LoadPictureFile(szFilePath);

    /*- Button2 -*/
	swprintf(p, TEXT("%s"), TEXT("Button2_Normal.jpg"));
	g_ArrHBITMAP[eButton2_Normal_BMP] = LoadPictureFile(szFilePath);

	swprintf(p, TEXT("%s"), TEXT("Button2_FocusOver.jpg"));
	g_ArrHBITMAP[eButton2_FocusOver_BMP] = LoadPictureFile(szFilePath);

	swprintf(p, TEXT("%s"), TEXT("Button2_FocusOn.jpg"));
	g_ArrHBITMAP[eButton2_FocusOn_BMP] = LoadPictureFile(szFilePath);

	swprintf(p, TEXT("%s"), TEXT("Button2_Active.jpg"));
	g_ArrHBITMAP[eButton2_Active_BMP] = LoadPictureFile(szFilePath);

	swprintf(p, TEXT("%s"), TEXT("Button2_ABSInactive.jpg"));
	g_ArrHBITMAP[eButton2_ABSInactive_BMP] = LoadPictureFile(szFilePath);

	return;
}

/**
*
* NAME: UnloadBitmaps
* DESC: unload resource of bitmap
*/
void  UnloadBitmaps()
{
	int i;

	for(i = 0; i < eNum_BMP; i++)
	{
		if(g_ArrHBITMAP[i])
			DeleteObject(g_ArrHBITMAP[i]);
	}

	return;
}