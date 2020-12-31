/*
 * File:	ximage.h
 * Purpose:	General Purpose Image Class 
 */
/* === C R E D I T S  &  D I S C L A I M E R S ==============
 * Permission is given by the author to freely redistribute and include
 * this code in any program as long as this credit is given where due.
 *
 * CxImage (c)  07/Aug/2001 <ing.davide.pizzolato@libero.it>
 * version 1.21 15/Oct/2001
 * See the file history.htm for the complete bugfix and news report.
 *
 * Special thanks to Troels Knakkergaard for new features, enhancements and bugfixes
 *
 * original CImage and CImageIterator implementation are:
 * Copyright:	(c) 1995, Alejandro Aguilar Sierra <asierra@servidor.unam.mx>
 *
 * COVERED CODE IS PROVIDED UNDER THIS LICENSE ON AN "AS IS" BASIS, WITHOUT WARRANTY
 * OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING, WITHOUT LIMITATION, WARRANTIES
 * THAT THE COVERED CODE IS FREE OF DEFECTS, MERCHANTABLE, FIT FOR A PARTICULAR PURPOSE
 * OR NON-INFRINGING. THE ENTIRE RISK AS TO THE QUALITY AND PERFORMANCE OF THE COVERED
 * CODE IS WITH YOU. SHOULD ANY COVERED CODE PROVE DEFECTIVE IN ANY RESPECT, YOU (NOT
 * THE INITIAL DEVELOPER OR ANY OTHER CONTRIBUTOR) ASSUME THE COST OF ANY NECESSARY
 * SERVICING, REPAIR OR CORRECTION. THIS DISCLAIMER OF WARRANTY CONSTITUTES AN ESSENTIAL
 * PART OF THIS LICENSE. NO USE OF ANY COVERED CODE IS AUTHORIZED HEREUNDER EXCEPT UNDER
 * THIS DISCLAIMER.
 *
 * Use at your own risk!
 * ==========================================================
 */
#if !defined(AFX_MYFXIMAGE_H)
#define AFX_MYFXIMAGE_H

#if _MSC_VER > 1000
#pragma once
#endif 

//#include <afxwin.h>		// needed by the specific platform
#include <windows.h>
//#include <tchar.h>
#include <stdio.h>
#include <math.h>

/////////////////////////////////////////////////////////////////////////////
// CxImage supported formats
#define CXIMAGE_SUPPORT_BMP 1
#define CXIMAGE_SUPPORT_GIF 0
#define CXIMAGE_SUPPORT_JPG 0
#define CXIMAGE_SUPPORT_PNG 0
#define CXIMAGE_SUPPORT_MNG 0
#define CXIMAGE_SUPPORT_ICO 0
#define CXIMAGE_SUPPORT_TIF 0

/////////////////////////////////////////////////////////////////////////////
// CxImage formats enumerator
enum {
#if CXIMAGE_SUPPORT_BMP
CXIMAGE_FORMAT_BMP,
#endif
#if CXIMAGE_SUPPORT_GIF
CXIMAGE_FORMAT_GIF,
#endif
#if CXIMAGE_SUPPORT_JPG
CXIMAGE_FORMAT_JPG,
#endif
#if CXIMAGE_SUPPORT_PNG
CXIMAGE_FORMAT_PNG,
#endif
#if CXIMAGE_SUPPORT_MNG
CXIMAGE_FORMAT_MNG,
#endif
#if CXIMAGE_SUPPORT_ICO
CXIMAGE_FORMAT_ICO,
#endif
#if CXIMAGE_SUPPORT_TIF
CXIMAGE_FORMAT_TIF,
#endif
CMAX_IMAGE_FORMATS
};

// needed for png & gif
struct rgb_color_struct { BYTE r,g,b; };
// needed for png & mng
#define COLORTYPE_PALETTE	1
#define COLORTYPE_COLOR		2
#define COLORTYPE_ALPHA		4

#define RGB2GRAY(r,g,b) ((b*11 + g*59 + r*30)/100) //color to grey mapping

/////////////////////////////////////////////////////////////////////////////
// CxImage class
/////////////////////////////////////////////////////////////////////////////
class CxImage
{
//extensible information collector
typedef struct tagCxImageInfo {
	DWORD	dwEffWidth;			//DWORD aligned scan line width
	BYTE*	pImage;				//THE IMAGE BITS
	void*	pGhost;				//if this is a ghost, pGhost point to the body
	DWORD	dwType;				//original image format
	BYTE	bColorType;			//used for PNG, MNG
	char	szLastError[256];	//debugging
	long	nProgress;			//monitor
	long	nEscape;			//escape
	long	nBkgndIndex;		//used for GIF, PNG, MNG
	BYTE	nQuality;			//used for JPEG
	long	nFrame;				//used for TIF, GIF, MNG : actual frame
	long	nNumFrames;			//used for TIF, GIF, MNG : total number of frames
	DWORD	dwFrameDelay;		//used for GIF, MNG
} CXIMAGEINFO;

public:
	//constructors
	CxImage(DWORD imagetype = 0);
	CxImage(DWORD dwWidth, DWORD dwHeight, WORD wBpp, DWORD imagetype = 0);
	CxImage(const CxImage *isrc);
	CxImage(HBITMAP hbmp);		//Windows resource
	CxImage(HANDLE hMem);		//Windows objects (clipboard)
	CxImage(const char * filename, DWORD imagetype = 0);
	CxImage(FILE * stream, DWORD imagetype = 0);
	virtual ~CxImage();
	CxImage& operator = (CxImage);

	//initializzation
	void*	Create(DWORD dwWidth, DWORD dwHeight, WORD wBpp, DWORD imagetype = 0);
	void	Clear(BYTE bval=0);
	void	Copy(CxImage *src);
	HANDLE	CopyToHandle();
	void	Transfer(CxImage *from);
	HBITMAP MakeBitmap(HDC hdc);

	//Attributes
	long	GetSize();
	BYTE*	GetBits();
	HANDLE	GetDIB()		const {return hDib;}
	DWORD	GetHeight()		const {return head.biHeight;}
	DWORD	GetWidth()		const {return head.biWidth;}
	DWORD	GetEffWidth()	const {return info.dwEffWidth;}
	DWORD	GetNumColors()	const {return head.biClrUsed;}
	DWORD	GetClrImportant() const {return head.biClrImportant;}
	BYTE	GetColorType()	const {return info.bColorType;}
	WORD	GetBpp()		const {return head.biBitCount;}
	DWORD	GetType()		const {return info.dwType;}
	long	GetTransIndex()	const {return info.nBkgndIndex;}
	LPSTR	GetLastError()	{return info.szLastError;}
	void	SetClrImportant(DWORD ncolors = 0);

	long	GetProgress()	const {return info.nProgress;}
	long	GetEscape()     const {return info.nEscape;}
	void	SetProgress(long p) {info.nProgress = p;}
	void	SetEscape(long i)   {info.nEscape = i;}

	//palette operations
	bool	IsGrayScale();
	DWORD	GetPaletteSize();
	RGBQUAD* GetPalette() const;
	RGBQUAD GetPaletteColor(BYTE idx);
	bool	GetRGB(int i, BYTE* r, BYTE* g, BYTE* b);
	BYTE	GetNearestIndex(RGBQUAD c);
	void	BlendPalette(COLORREF cr,long perc);
	void	SetGrayPalette();
	void	SetPalette(DWORD n, BYTE *r, BYTE *g, BYTE *b);
	void	SetPalette(RGBQUAD* pPal,DWORD nColors=256);
	void	SetPalette(rgb_color_struct *rgb,DWORD nColors=256);
	void	SetPaletteIndex(BYTE idx, BYTE r, BYTE g, BYTE b);
	void	SetPaletteIndex(BYTE idx, RGBQUAD c);
	void	SetPaletteIndex(BYTE idx, COLORREF cr);
	void	SetTransIndex(long idx) {info.nBkgndIndex = idx;}
	void	SwapIndex(BYTE idx1, BYTE idx2);
	void	SetStdPalette();

	//pixel operations
	bool	IsInside(long x, long y);
	BYTE	GetPixelIndex(long x,long y);
	RGBQUAD GetPixelColor(long x,long y);
	void	SetPixelColor(long x,long y,RGBQUAD c);
	void	SetPixelIndex(long x,long y,BYTE i);
	void	SetPixelColor(long x,long y,COLORREF cr);

	//painting operations
	long	Draw(HDC pDC, long x=0, long y=0, long cx = -1, long cy = -1);
	long	Draw(HDC hdc, const RECT& rect) { return Draw(hdc, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top); }
	long	Stretch(HDC pDC, long xoffset, long yoffset, long xsize, long ysize);
	long	Stretch(HDC hdc, const RECT& rect) { return Stretch(hdc, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top); }
	long	Tile(HDC pDC, RECT *rc);

	//color conversion utilities
	RGBQUAD HSLtoRGB(COLORREF cHSLColor);
	RGBQUAD RGB2RGBQUAD(COLORREF cr);
	COLORREF RGBQUAD2RGB (RGBQUAD c);
	RGBQUAD RGBtoHSL(RGBQUAD lRGBColor);
	RGBQUAD HSLtoRGB(RGBQUAD lHSLColor);
	void	RGB2BGR(BYTE *buffer, int length);

	// file operations
	bool SaveFile(const char * filename, DWORD imagetype=0);
	bool ReadFile(const char * filename, DWORD imagetype=0);
	bool SaveFile(LPCWSTR filename, DWORD imagetype=0);
	bool ReadFile(LPCWSTR filename, DWORD imagetype=0);
	bool LoadResource(HRSRC hRes, DWORD imagetype);
	bool Decode(FILE * hFile, DWORD imagetype);
	bool Encode(FILE * hFile, DWORD imagetype);

	// image operations
	bool IsValid();
	bool Flip();
	bool Mirror();
	bool Negative();
	bool GrayScale();
	bool Rotate(float angle);
	bool Resample(long newx, long newy, int fast = 1);
	bool DecreaseBpp(DWORD nbit, bool errordiffusion, RGBQUAD* ppal = 0, DWORD clrimportant = 0);
	bool IncreaseBpp(DWORD nbit);
	bool Colorize(BYTE hue, BYTE sat);

	// frame operations
	long GetNumFrames() const {return info.nNumFrames;}
	long GetFrame() const {return info.nFrame;}
	void SetFrame(long nFrame) {info.nFrame=nFrame;} 

protected:
	void Startup(DWORD imagetype = 0);
	void CopyInfo(const CxImage &src);
	void Ghost(CxImage *src);
	WORD HueToRGB(WORD n1,WORD n2,WORD hue);
	void Bitfield2RGB(BYTE *src, WORD redmask, WORD greenmask, WORD bluemask, BYTE bpp);
	bool DrawTransparentBitmap(HDC pDC, HBITMAP bmpMask, int xDst, int yDst,
						int cxDst,int cyDst,HDC pTmpDC,int cxSrc,int cySrc);

	void*				hDib; //contains the header, the palette, the bits
    BITMAPINFOHEADER    head; //stadnard header
	CXIMAGEINFO			info; //extended information
};
////////////////////////////////////////////////////////////////////////////
#endif // !defined(AFX_MYFXIMAGE_H)
