/**************************************************************************
   THIS CODE AND INFORMATION IS PROVIDED 'AS IS' WITHOUT WARRANTY OF
   ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
   THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
   PARTICULAR PURPOSE.
   Author: Leon Finker  1/2001
**************************************************************************/
#ifndef __STATICDROPTARGET_H__
#define __STATICDROPTARGET_H__

#include "DragDropImpl.h"

//code taken from SEEDIB MSDN sample
static WORD DIBNumColors(void* pv) 
{     
	int bits;     
	LPBITMAPINFOHEADER  lpbi;     
	LPBITMAPCOREHEADER  lpbc;      
	lpbi = ((LPBITMAPINFOHEADER)pv);     
	lpbc = ((LPBITMAPCOREHEADER)pv);      
	/*  With the BITMAPINFO format headers, the size of the palette 
	 *  is in biClrUsed, whereas in the BITMAPCORE - style headers, it      
	 *  is dependent on the bits per pixel ( = 2 raised to the power of      
	 *  bits/pixel).
	 */     
	if (lpbi->biSize != sizeof(BITMAPCOREHEADER))
	{         
		if (lpbi->biClrUsed != 0)
			return (WORD)lpbi->biClrUsed;         
		bits = lpbi->biBitCount;     
	}     
	else         
		bits = lpbc->bcBitCount;
	switch (bits)
	{         
	case 1:                 
		return 2;         
	case 4:                 
		return 16;         
	case 8:       
		return 256;
	default:
		/* A 24 bitcount DIB has no color table */                 
		return 0;
	} 
} 
//code taken from SEEDIB MSDN sample
static WORD ColorTableSize(LPVOID lpv)
{
	LPBITMAPINFOHEADER lpbih = (LPBITMAPINFOHEADER)lpv;

	if (lpbih->biSize != sizeof(BITMAPCOREHEADER))
	{
	  if (((LPBITMAPINFOHEADER)(lpbih))->biCompression == BI_BITFIELDS)
		 /* Remember that 16/32bpp dibs can still have a color table */
		 return (sizeof(DWORD) * 3) + (DIBNumColors (lpbih) * sizeof (RGBQUAD));
	  else
		 return (WORD)(DIBNumColors (lpbih) * sizeof (RGBQUAD));
	}
	else
	  return (WORD)(DIBNumColors (lpbih) * sizeof (RGBTRIPLE));
}

class CStaticDropTarget : public CIDropTarget
{
public:
	CStaticDropTarget(HWND hTargetWnd):CIDropTarget(hTargetWnd){}	
	
	virtual bool OnDrop(FORMATETC* pFmtEtc, STGMEDIUM& medium, DWORD *pdwEffect)
	{
		if(pFmtEtc->cfFormat == CF_DIB && medium.tymed == TYMED_HGLOBAL)
		{
			if(medium.hGlobal != NULL)
			{
				LPBITMAPINFOHEADER  lpbi = (BITMAPINFOHEADER*)GlobalLock(medium.hGlobal);
				if(lpbi != NULL)
				{
					HBITMAP hbm;
					HDC hdc = GetDC(NULL);
					if(hdc != NULL)
					{
						int i = ((BITMAPFILEHEADER *)lpbi)->bfOffBits;
						hbm = CreateDIBitmap(hdc,(LPBITMAPINFOHEADER)lpbi,
											(LONG)CBM_INIT,
											(LPSTR)lpbi + lpbi->biSize + ColorTableSize(lpbi),
											(LPBITMAPINFO)lpbi,DIB_RGB_COLORS);

						::ReleaseDC(NULL,hdc);
					}
				GlobalUnlock(medium.hGlobal);
				if(hbm != NULL)
					hbm = (HBITMAP)SendMessage(m_hTargetWnd, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hbm);
				if(hbm != NULL)
					DeleteObject(hbm);
				return true; //release the medium
				}
			}
		}
		if(pFmtEtc->cfFormat == CF_BITMAP && medium.tymed == TYMED_GDI)
		{
			if(medium.hBitmap != NULL)
			{
				HBITMAP hBmp = (HBITMAP)SendMessage(m_hTargetWnd, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)medium.hBitmap);
				if(hBmp != NULL)
					DeleteObject(hBmp);
				return false; //don't free the bitmap
			}
		}
		if(pFmtEtc->cfFormat == CF_ENHMETAFILE && medium.tymed == TYMED_ENHMF)
		{
			ENHMETAHEADER emh;
			GetEnhMetaFileHeader(medium.hEnhMetaFile, sizeof(ENHMETAHEADER),&emh);
			RECT rc;//={0,0,EnhMetaHdr.rclBounds.right-EnhMetaHdr.rclBounds.left, EnhMetaHdr.rclBounds.bottom-EnhMetaHdr.rclBounds.top};
			HDC hDC= GetDC(m_hTargetWnd);
//start code: taken from ENHMETA.EXE MSDN Sample
//*ALSO NEED to GET the pallete (select and RealizePalette it, but i was too lazy*
			// Get the characteristics of the output device
			float PixelsX = (float)GetDeviceCaps( hDC, HORZRES );
			float PixelsY = (float)GetDeviceCaps( hDC, VERTRES );
			float MMX = (float)GetDeviceCaps( hDC, HORZSIZE );
			float MMY = (float)GetDeviceCaps( hDC, VERTSIZE );
			// Calculate the rect in which to draw the metafile based on the
			// intended size and the current output device resolution
			// Remember that the intended size is given in 0.01mm units, so
			// convert those to device units on the target device
			rc.top = (int)((float)(emh.rclFrame.top) * PixelsY / (MMY*100.0f));
			rc.left = (int)((float)(emh.rclFrame.left) * PixelsX / (MMX*100.0f));
			rc.right = (int)((float)(emh.rclFrame.right) * PixelsX / (MMX*100.0f));
			rc.bottom = (int)((float)(emh.rclFrame.bottom) * PixelsY / (MMY*100.0f));
//end code: taken from ENHMETA.EXE MSDN Sample

			HDC hdcMem = CreateCompatibleDC(hDC);
			HGDIOBJ hBmpMem = CreateCompatibleBitmap(hDC, emh.rclBounds.right, emh.rclBounds.bottom);
			HGDIOBJ hOldBmp = ::SelectObject(hdcMem, hBmpMem);
			PlayEnhMetaFile(hdcMem,medium.hEnhMetaFile,&rc);
			HBITMAP hBmp = (HBITMAP)::SelectObject(hdcMem, hOldBmp);
			DeleteDC(hdcMem);
			ReleaseDC(m_hTargetWnd,hDC);
			hBmp = (HBITMAP)SendMessage(m_hTargetWnd, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBmp);
				if(hBmp != NULL)
					DeleteObject(hBmp);
			return true;
		}
		if(pFmtEtc->cfFormat == CF_HDROP && medium.tymed == TYMED_HGLOBAL)
		{
			HDROP hDrop = (HDROP)GlobalLock(medium.hGlobal);
			if(hDrop != NULL)
			{
				TCHAR szFileName[MAX_PATH];
				UINT cFiles = DragQueryFile(hDrop, 0xFFFFFFFF, NULL, 0); 
				if(cFiles > 0)
				{
					DragQueryFile(hDrop, 0, szFileName, sizeof(szFileName)); 
					HBITMAP hBitmap = (HBITMAP)LoadImage(NULL, szFileName,IMAGE_BITMAP,0,0,LR_DEFAULTSIZE|LR_LOADFROMFILE);
					if(hBitmap)
					{
							HBITMAP hBmp = (HBITMAP)SendMessage(m_hTargetWnd, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBitmap);
							if(hBmp != NULL)
								DeleteObject(hBmp);
					}
				}
				//DragFinish(hDrop); // base class calls ReleaseStgMedium
			}
			GlobalUnlock(medium.hGlobal);
		}
		return true; //let base free the medium
	}

};

#endif //__STATICDROPTARGET_H__