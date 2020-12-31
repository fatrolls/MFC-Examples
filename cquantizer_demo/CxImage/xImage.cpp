// CxImage.cpp : implementation file
/* 07/08/2001 v1.00 - ing.davide.pizzolato@libero.it
 * version 1.20 15/Oct/2001
 */

#include "xImage.h"

#if CXIMAGE_SUPPORT_JPG
#include "ximajpg.h"
#endif

#if CXIMAGE_SUPPORT_GIF
#include "ximagif.h"
#endif

#if CXIMAGE_SUPPORT_PNG
#include "ximapng.h"
#endif

#if CXIMAGE_SUPPORT_MNG
#include "ximamng.h"
#endif

#if CXIMAGE_SUPPORT_BMP
#include "ximabmp.h"
#endif

#if CXIMAGE_SUPPORT_ICO
#include "ximaico.h"
#endif

#if CXIMAGE_SUPPORT_TIF
#include "ximatif.h"
#endif

/**************************************/
// CxImage 
/**************************************/
// Initialize the internal structures
void CxImage::Startup(DWORD imagetype)
{
	hDib=NULL;
	memset(&head,0,sizeof(BITMAPINFOHEADER));
    head.biSize = sizeof(BITMAPINFOHEADER);
	memset(&info,0,sizeof(CXIMAGEINFO));
    info.dwType = imagetype;
	info.nQuality=75;
	info.nBkgndIndex=-1;
}
/**************************************/
// Empty image constructor
// > imagetype: (optional) set the image format (for future use)
CxImage::CxImage(DWORD imagetype)
{
	Startup(imagetype);
}
/**************************************/
// Sized image constructor
// > dwWidth: width
// > dwHeight: height
// > wBpp: bit per pixel
// > imagetype: (optional) set the image format (for future use)
CxImage::CxImage(DWORD dwWidth, DWORD dwHeight, WORD wBpp, DWORD imagetype)
{
	Startup(imagetype);
	Create(dwWidth,dwHeight,wBpp);
}
/**************************************/
// Source image constructor
// § The source image bits are not copied in the new image.
// > isrc: source image.
CxImage::CxImage(const CxImage *isrc)
{
	if (isrc){
		Startup(isrc->GetType());
		memcpy(&info,&isrc->info,sizeof(CXIMAGEINFO));
		Create(isrc->GetWidth(),isrc->GetHeight(),isrc->GetBpp(),isrc->GetType());
		SetPalette(isrc->GetPalette());
	}
}
/**************************************/
// Global object (clipboard paste) constructor
// § the clipboard format must be CF_DIB.
// > source bitmap object
CxImage::CxImage(HANDLE hMem)
{
	Startup();
	BYTE *lpVoid;						//pointer to the bitmap
	lpVoid = (BYTE *)GlobalLock(hMem);
	BITMAPINFOHEADER *pHead;			//pointer to the bitmap header
	pHead = (BITMAPINFOHEADER *)lpVoid;
	if (lpVoid){
		//copy the bitmap header
		memcpy(&head,pHead,sizeof(BITMAPINFOHEADER));
		//create the image
		if(!Create(head.biWidth,head.biHeight,head.biBitCount)){
			GlobalUnlock(lpVoid);
			return;
		}
		//copy the bits
		if(pHead->biCompression != BI_RGB){
			// BITFIELD case
			// set the internal header in the dib
			memcpy(hDib,&head,sizeof(head));
			// get the bitfield masks
			DWORD bf[3];
			memcpy(bf,lpVoid+pHead->biSize,12);
			// transform into RGB
			Bitfield2RGB(lpVoid+pHead->biSize+12,(WORD)bf[0],(WORD)bf[1],(WORD)bf[2],(BYTE)pHead->biBitCount);
		} else { //normal bitmap
			memcpy(hDib,lpVoid,GetSize());
		}
		GlobalUnlock(lpVoid);
		return;
	}
}
/**************************************/
// turns a 16 or 32 bit bitfield image into a RGB image
void CxImage::Bitfield2RGB(BYTE *src, WORD redmask, WORD greenmask, WORD bluemask, BYTE bpp)
{
	switch (bpp){
	case 16:
	{
		DWORD ns[3]={0,0,0};
		// compute the number of shift for each mask
		for (int i=0;i<16;i++){
			if ((redmask>>i)&0x01) ns[0]++;
			if ((greenmask>>i)&0x01) ns[1]++;
			if ((bluemask>>i)&0x01) ns[2]++;
		}
		ns[1]+=ns[0]; ns[2]+=ns[1];	ns[0]=8-ns[0]; ns[1]-=8; ns[2]-=8;
		// dword aligned width for 16 bit image
		long effwidth2=(((head.biWidth + 1) / 2) * 4);
		WORD w;
		long y2,y3,x2,x3;
		BYTE *p=info.pImage;
		// scan the buffer in reverse direction to avoid reallocations
		for (long y=head.biHeight-1; y>=0; y--){
			y2=effwidth2*y;
			y3=info.dwEffWidth*y;
			for (long x=head.biWidth-1; x>=0; x--){
				x2 = 2*x+y2;
				x3 = 3*x+y3;
				w = src[x2]+256*src[1+x2];
				p[  x3]=(BYTE)((w & bluemask)<<ns[0]);
				p[1+x3]=(BYTE)((w & greenmask)>>ns[1]);
				p[2+x3]=(BYTE)((w & redmask)>>ns[2]);
			}
		}
		break;
	}
	case 32:
	{
		// dword aligned width for 32 bit image
		long effwidth4 = head.biWidth * 4;
		long y4,y3,x4,x3;
		BYTE *p=info.pImage;
		// scan the buffer in reverse direction to avoid reallocations
		for (long y=head.biHeight-1; y>=0; y--){
			y4=effwidth4*y;
			y3=info.dwEffWidth*y;
			for (long x=head.biWidth-1; x>=0; x--){
				x4 = 4*x+y4;
				x3 = 3*x+y3;
				p[  x3]=src[  x4];
				p[1+x3]=src[1+x4];
				p[2+x3]=src[2+x4];
			}
		}
	}

	}
	return;
}
/**************************************/
// Bitmap resource constructor
// > hbmp: bitmap resource handle
CxImage::CxImage(HBITMAP hbmp)
{
	Startup();
	if (hbmp) { 
        BITMAP bm;
		// get informations about the bitmap
        GetObject(hbmp, sizeof(BITMAP), (LPSTR) &bm);
		// create the image
        Create(bm.bmWidth, bm.bmHeight, bm.bmBitsPixel);
		// create a device context for the bitmap
        HDC dc = ::GetDC(NULL);
		// copy the bits
        if (GetDIBits(dc, hbmp, 0, head.biHeight, info.pImage,
			(LPBITMAPINFO)&head, DIB_RGB_COLORS) == 0){
            strcpy(info.szLastError,"GetDIBits failed");
			::ReleaseDC(NULL, dc);
			return;
        }
		// if needed copy the palette colors
		SetPalette(((LPBITMAPINFO)&head)->bmiColors);
        ::ReleaseDC(NULL, dc);
    }
}
/**************************************/
// File name constructor
// > filename: file name
// > imagetype: specify the image format (CXIMAGE_FORMAT_BMP,...)
CxImage::CxImage(const char * filename, DWORD imagetype)
{
	Startup(imagetype);
	ReadFile(filename,imagetype);
}
/**************************************/
// Stream constructor
// § the file is always closed by the constructor.
// > stream: file with "rb" access
// > imagetype: specify the image format (CXIMAGE_FORMAT_BMP,...)
CxImage::CxImage(FILE * stream, DWORD imagetype)
{
	Startup(imagetype);
	Decode(stream,imagetype);
}
/**************************************/
CxImage::~CxImage()
{
	//free this only if it's valid and it's not a ghost
	if ((hDib)&&(info.pGhost==NULL)) free(hDib);
}
/**************************************/
void CxImage::CopyInfo(const CxImage &src)
{
	if (hDib==NULL) memcpy(&info,&src.info,sizeof(CXIMAGEINFO));
}
/**************************************/
CxImage& CxImage::operator = (CxImage isrc)
{
	Copy(&isrc);
	return *this;
}
/**************************************/
// returns the palette dimension in byte
DWORD CxImage::GetPaletteSize()
{
	return (head.biClrUsed * sizeof(RGBQUAD));
}
/**************************************/
// returns the pointer to the image bits
BYTE* CxImage::GetBits()
{ 
	if (hDib)	return ((BYTE*)hDib + *(LPDWORD)hDib + GetPaletteSize()); 
	return NULL;
}
/**************************************/
// Initializes or rebuilds the image.
// Returns the pointer to the internal hDib object
// > dwWidth: width
// > dwHeight: height
// > wBpp: bit per pixel
// > imagetype: (optional) set the image format (for future use)
void* CxImage::Create(DWORD dwWidth, DWORD dwHeight, WORD wBpp, DWORD imagetype)
{
	// destroy the existing image (if any)
	if (hDib) free(hDib);
	hDib=NULL;

    // Make sure bits per pixel is valid
    if		(wBpp <= 1)	wBpp = 1;
    else if (wBpp <= 4)	wBpp = 4;
    else if (wBpp <= 8)	wBpp = 8;
    else				wBpp = 24;

	// set the correct bpp value
    switch (wBpp){
        case 1:
            head.biClrUsed = 2;	break;
        case 4:
            head.biClrUsed = 16; break;
        case 8:
            head.biClrUsed = 256; break;
        default:
            head.biClrUsed = 0;
    }

	//set the common image informations
	info.bColorType = (wBpp>8) ? COLORTYPE_COLOR : COLORTYPE_PALETTE;
    info.dwEffWidth = ((((wBpp * dwWidth) + 31) / 32) * 4);

    // initialize BITMAPINFOHEADER
    head.biWidth = dwWidth;		// fill in width from parameter
    head.biHeight = dwHeight;	// fill in height from parameter
    head.biPlanes = 1;			// must be 1
    head.biBitCount = wBpp;		// from parameter
    head.biCompression = BI_RGB;    
    head.biSizeImage = info.dwEffWidth * dwHeight;
    head.biXPelsPerMeter = 0;
    head.biYPelsPerMeter = 0;
    head.biClrImportant = 0;

	hDib = malloc(GetSize()); // alloc memory block to store our bitmap
    if (!hDib) return NULL;

    // use our bitmap info structure to fill in first part of
    // our DIB with the BITMAPINFOHEADER
    LPBITMAPINFOHEADER  lpbi;
	lpbi = (LPBITMAPINFOHEADER)(hDib);
    *lpbi = head;

	info.pImage=GetBits();

    return hDib; //return handle to the DIB
}
/**************************************/
bool CxImage::DrawTransparentBitmap(HDC pDC, HBITMAP bmpMask,
									int xDst,  int yDst,
									int cxDst,  int cyDst,
									HDC pTmpDC, int cxSrc, int cySrc)
{
   // We are going to paint the two DDB's in sequence to the destination.
   // 1st the monochrome bitmap will be blitted using an AND operation to
   // cut a hole in the destination. The color image will then be ORed
   // with the destination, filling it into the hole, but leaving the
   // surrounding area untouched.
   HDC hdcMem = CreateCompatibleDC(NULL);
   HGDIOBJ old = SelectObject(hdcMem, bmpMask);
   bool bOK   = (SetStretchBltMode(pDC,COLORONCOLOR)!=0);
   bOK = bOK && StretchBlt(pDC, xDst, yDst, cxDst, cyDst, hdcMem, 0, 0, cxSrc, cySrc, SRCAND  );
   // Now, clean up.
   SelectObject(hdcMem, old);
   DeleteDC(hdcMem); hdcMem = NULL;
   // Also note the use of SRCPAINT rather than SRCCOPY.
   bOK = bOK && StretchBlt(pDC, xDst, yDst, cxDst, cyDst, pTmpDC, 0, 0, cxSrc, cySrc, SRCPAINT);
   return bOK;
}
/**************************************/
// Draws (stretch) the image with transparency support
// > pDC: destination device context
// > x,y: offset
// > cx,cy: (optional) size.
long CxImage::Draw(HDC pDC, long x, long y, long cx, long cy)
{
	if((hDib)&&(pDC))  {
		if (cx < 0) cx = head.biWidth;
		if (cy < 0) cy = head.biHeight;
		bool bTransparent = (info.nBkgndIndex != -1);

		if (!bTransparent){
			SetStretchBltMode(pDC,COLORONCOLOR);	
			StretchDIBits(pDC, x, y, cx, cy, 0, 0, head.biWidth, head.biHeight,
							info.pImage,(BITMAPINFO*)hDib, DIB_RGB_COLORS,SRCCOPY);
		} else {
			// draw image with transparent background
			const int safe = 0; // or else GDI fails in the following - sometimes 
			RECT rcDst = {x+safe, y+safe, x+cx, y+cy};
			if (RectVisible(pDC, &rcDst)){
				HDC dcMem = CreateCompatibleDC(pDC);
				HBITMAP bm = CreateCompatibleBitmap(pDC, head.biWidth, head.biHeight);
				HGDIOBJ oldbm = SelectObject(dcMem, bm);
				SetStretchBltMode(dcMem,COLORONCOLOR);
				StretchDIBits(dcMem, 0, 0, head.biWidth, head.biHeight, 0, 0, head.biWidth, head.biHeight,
								info.pImage,(BITMAPINFO*)hDib,DIB_RGB_COLORS,SRCCOPY);

				RGBQUAD rgbBG = GetPaletteColor((BYTE)info.nBkgndIndex);
				COLORREF crBG = RGB(rgbBG.rgbRed, rgbBG.rgbGreen, rgbBG.rgbBlue);

				// PREPARE MASK BEGIN
				HDC hdcDst = CreateCompatibleDC(pDC);
				HBITMAP mask = CreateBitmap(head.biWidth, head.biHeight, 1, 1, NULL);
				// Load the bitmaps into memory DC
				HGDIOBJ hbmDstT = SelectObject(hdcDst, mask);
				// Change the background to trans color
				COLORREF clrSaveBk = SetBkColor(dcMem, crBG);
				// This call sets up the mask bitmap.
				BitBlt(hdcDst,0,0,head.biWidth,head.biHeight,dcMem,0,0,SRCCOPY);
				// Now, we need to paint onto the original image, making
				// sure that the "transparent" area is set to black. What
				// we do is AND the monochrome image onto the color Image
				// first. When blitting from mono to color, the monochrome
				// pixel is first transformed as follows:
				// if  1 (black) it is mapped to the color set by SetTextColor().
				// if  0 (white) is is mapped to the color set by SetBkColor().
				// Only then is the raster operation performed.
				COLORREF clrSaveDstText = SetTextColor(dcMem, RGB(255,255,255));
				SetBkColor(dcMem, RGB(0,0,0));
				BitBlt(dcMem,0,0,head.biWidth,head.biHeight,hdcDst,0,0,SRCAND);
				// Clean up by deselecting any objects, and delete the DC's.
				SetTextColor(hdcDst, clrSaveDstText);
				SetBkColor(dcMem, clrSaveBk);
				SelectObject(hdcDst, hbmDstT);
				DeleteDC(hdcDst); hdcDst = NULL;
				// PREPARE MASK END
				DrawTransparentBitmap(pDC, mask,	// The destination DC.
									   x, y,		// Where to draw
									   cx,cy,		// Width & Height
									   dcMem,		// the DC holding the bmp
									   head.biWidth,
									   head.biHeight);
				SelectObject(dcMem, oldbm); 
				DeleteDC(dcMem);
				DeleteObject(mask);
				DeleteObject(bm);
			}
		}
		return 1;
	} 
	return 0;
}
/**************************************/
// Stretch the image. Obsolete: use Draw()
long CxImage::Stretch(HDC pDC, long xoffset, long yoffset, long xsize, long ysize)
{
	if((hDib)&&(pDC)) {
		//palette must be correctly filled
		SetStretchBltMode(pDC,COLORONCOLOR);	
		StretchDIBits(pDC, xoffset, yoffset,
					xsize, ysize, 0, 0, head.biWidth, head.biHeight,
					info.pImage,(BITMAPINFO*)hDib,DIB_RGB_COLORS,SRCCOPY);
		return 1;
	}
	return 0;
}
/**************************************/
// Tiles the device context in the specified rectangle with the image.
long CxImage::Tile(HDC pDC, RECT *rc)
{
	if((hDib)&&(pDC)&&(rc)) {
		int w = rc->right - rc->left;
		int	h = rc->bottom - rc->top;
		int x,y,z;
		int	bx=head.biWidth;
		int	by=head.biHeight;
		for (y = rc->top ; y < h ; y += by){
			if ((y+by)>h) by=h-y;
			z=bx;
			for (x = rc->left ; x < w ; x += z){
				if ((x+z)>w) z=w-x;
				Draw(pDC,x, y);
			}
		}
		return 1;
	}
	return 0;
}
/**************************************/
void CxImage::SetPaletteIndex(BYTE idx, BYTE r, BYTE g, BYTE b)
{
	if ((hDib)&&(head.biClrUsed)){
		BYTE* iDst = (BYTE*)(hDib) + sizeof(BITMAPINFOHEADER);
		if ((idx>=0)&&(idx<head.biClrUsed)){	
			long ldx=idx*sizeof(RGBQUAD);
			iDst[ldx++] = (BYTE) b;
			iDst[ldx++] = (BYTE) g;
			iDst[ldx++] = (BYTE) r;
			iDst[ldx] = (BYTE) 0;
		}
	}
}
/**************************************/
void CxImage::SetPaletteIndex(BYTE idx, RGBQUAD c)
{
	if ((hDib)&&(head.biClrUsed)){
		BYTE* iDst = (BYTE*)(hDib) + sizeof(BITMAPINFOHEADER);
		if ((idx>=0)&&(idx<head.biClrUsed)){	
			long ldx=idx*sizeof(RGBQUAD);
			iDst[ldx++] = (BYTE) c.rgbBlue;
			iDst[ldx++] = (BYTE) c.rgbGreen;
			iDst[ldx++] = (BYTE) c.rgbRed;
			iDst[ldx] = (BYTE) 0;
		}
	}
}
/**************************************/
void CxImage::SetPaletteIndex(BYTE idx, COLORREF cr)
{
	if ((hDib)&&(head.biClrUsed)){
		BYTE* iDst = (BYTE*)(hDib) + sizeof(BITMAPINFOHEADER);
		if ((idx>=0)&&(idx<head.biClrUsed)){	
			long ldx=idx*sizeof(RGBQUAD);
			iDst[ldx++] = (BYTE) GetBValue(cr);
			iDst[ldx++] = (BYTE) GetGValue(cr);
			iDst[ldx++] = (BYTE) GetRValue(cr);
			iDst[ldx] = (BYTE) 0;
		}
	}
}
/**************************************/
// returns the pointer to the first palette index 
RGBQUAD* CxImage::GetPalette() const
{
	if ((hDib)&&(head.biClrUsed))
		return (RGBQUAD*)((BYTE*)hDib + sizeof(BITMAPINFOHEADER));
	return NULL;
}
/**************************************/
RGBQUAD CxImage::GetPaletteColor(BYTE idx)
{
	RGBQUAD rgb = {0,0,0,0};
	if ((hDib)&&(head.biClrUsed)){
		BYTE* iDst = (BYTE*)(hDib) + sizeof(BITMAPINFOHEADER);
		if ((idx>=0)&&(idx<head.biClrUsed)){	
			long ldx=idx*sizeof(RGBQUAD);
			rgb.rgbBlue = iDst[ldx++];
			rgb.rgbGreen=iDst[ldx++];
			rgb.rgbRed =iDst[ldx];
			rgb.rgbReserved = 0;
		}
	}
	return rgb;
}
/**************************************/
BYTE CxImage::GetPixelIndex(long x,long y)
{
	if ((hDib==NULL)||(head.biClrUsed==0)) return 0;

	if ((x<0)||(y<0)||(x>=head.biWidth)||(y>=head.biHeight)) {
		if (info.nBkgndIndex != -1)	return (BYTE)info.nBkgndIndex;
		else return 0;
	}
	if (head.biBitCount==8){
		return info.pImage[y*info.dwEffWidth + x];
	} else {
		BYTE pos;
		BYTE iDst= info.pImage[y*info.dwEffWidth + (x*head.biBitCount >> 3)];
		if (head.biBitCount==4){
			pos = 4*(1-x%2);
			iDst &= (0x0F<<pos);
			return iDst >> pos;
		} else if (head.biBitCount==1){
			pos = 7-x%8;
			iDst &= (0x01<<pos);
			return iDst >> pos;
		}
	}
	return 0;
}
/**************************************/
RGBQUAD CxImage::GetPixelColor(long x,long y)
{
	RGBQUAD rgb={0,0,0,0};
	if ((hDib==NULL)||(x<0)||(y<0)||
		(x>=head.biWidth)||(y>=head.biHeight)){
		if (info.nBkgndIndex != -1) rgb = GetPaletteColor((BYTE)info.nBkgndIndex);
		return rgb;
	}

	if (head.biClrUsed) return GetPaletteColor(GetPixelIndex(x,y));
	else {
		BYTE* iDst = info.pImage + y*info.dwEffWidth + x*3;
		rgb.rgbBlue = *iDst++;
		rgb.rgbGreen= *iDst++;
		rgb.rgbRed =*iDst;
		return rgb;
	}
}
/**************************************/
void CxImage::SetPixelIndex(long x,long y,BYTE i)
{
	if ((hDib==NULL)||(head.biClrUsed==0)||
		(x<0)||(y<0)||(x>=head.biWidth)||(y>=head.biHeight)) return ;

	if (head.biBitCount==8){
		info.pImage[y*info.dwEffWidth + x]=i;
		return;
	} else {
		BYTE pos;
		BYTE* iDst= info.pImage + y*info.dwEffWidth + (x*head.biBitCount >> 3);
		if (head.biBitCount==4){
			pos = 4*(1-x%2);
			*iDst &= ~(0x0F<<pos);
			*iDst |= ((i & 0x0F)<<pos);
			return;
		} else if (head.biBitCount==1){
			pos = 7-x%8;
			*iDst &= ~(0x01<<pos);
			*iDst |= ((i & 0x01)<<pos);
			return;
		}
	}
}
/**************************************/
void CxImage::SetPixelColor(long x,long y,COLORREF cr)
{
	SetPixelColor(x,y,RGB2RGBQUAD(cr));
}
/**************************************/
void CxImage::SetPixelColor(long x,long y,RGBQUAD c)
{
	if ((hDib==NULL)||(x<0)||(y<0)||
		(x>=head.biWidth)||(y>=head.biHeight)) return;
	if (head.biClrUsed)
		SetPixelIndex(x,y,GetNearestIndex(c));
	else {
		BYTE* iDst = info.pImage + y*info.dwEffWidth + x*3;
		*iDst++ = c.rgbBlue;
		*iDst++ = c.rgbGreen;
		*iDst   = c.rgbRed;
	}
}
/**************************************/
BYTE CxImage::GetNearestIndex(RGBQUAD c)
{
	if ((hDib==NULL)||(head.biClrUsed==0)) return 0;
	BYTE* iDst = (BYTE*)(hDib) + sizeof(BITMAPINFOHEADER);
	long distance=200000;
	int i,j,m;
	long k,l;
	m = (int)(head.biClrImportant==0 ? head.biClrUsed : head.biClrImportant);
	for(i=0,l=0;i<m;i++,l+=sizeof(RGBQUAD)){
		k = (iDst[l]-c.rgbBlue)*(iDst[l]-c.rgbBlue)+
			(iDst[l+1]-c.rgbGreen)*(iDst[l+1]-c.rgbGreen)+
			(iDst[l+2]-c.rgbRed)*(iDst[l+2]-c.rgbRed);
		if (k==0){
			j=i;
			break;
		}
		if (k<distance){
			distance=k;
			j=i;
		}
	}
	return j;
}
/**************************************/
// swaps the blue and red components (for RGB images)
// > buffer: pointer to the bits
// > lenght: number of bytes to swap. lenght may not exceed the scan line.
void CxImage::RGB2BGR(BYTE *buffer, int length)
{
	if (buffer && (head.biClrUsed==0)){
		BYTE temp;
		length = min(length,(int)info.dwEffWidth);
		for (int i=0;i<length;i+=3){
			temp = buffer[i]; buffer[i] = buffer[i+2]; buffer[i+2] = temp;
		}
	}
}
/**************************************/
#define  HSLMAX   240	/* H,L, and S vary over 0-HSLMAX */
#define  RGBMAX   255   /* R,G, and B vary over 0-RGBMAX */
                        /* HSLMAX BEST IF DIVISIBLE BY 6 */
                        /* RGBMAX, HSLMAX must each fit in a BYTE. */
/* Hue is undefined if Saturation is 0 (grey-scale) */
/* This value determines where the Hue scrollbar is */
/* initially set for achromatic colors */
#define UNDEFINED (HSLMAX*2/3)
/**************************************/
RGBQUAD CxImage::RGBtoHSL(RGBQUAD lRGBColor)
{
	BYTE R,G,B;					/* input RGB values */
	BYTE H,L,S;					/* output HSL values */
	BYTE cMax,cMin;				/* max and min RGB values */
	WORD Rdelta,Gdelta,Bdelta;	/* intermediate value: % of spread from max*/

	R = lRGBColor.rgbRed;	/* get R, G, and B out of DWORD */
	G = lRGBColor.rgbGreen;
	B = lRGBColor.rgbBlue;

	cMax = max( max(R,G), B);	/* calculate lightness */
	cMin = min( min(R,G), B);
	L = (((cMax+cMin)*HSLMAX)+RGBMAX)/(2*RGBMAX);

	if (cMax==cMin){			/* r=g=b --> achromatic case */
		S = 0;					/* saturation */
		H = UNDEFINED;			/* hue */
	} else {					/* chromatic case */
		if (L <= (HSLMAX/2))	/* saturation */
			S = (((cMax-cMin)*HSLMAX)+((cMax+cMin)/2))/(cMax+cMin);
		else
			S = (((cMax-cMin)*HSLMAX)+((2*RGBMAX-cMax-cMin)/2))/(2*RGBMAX-cMax-cMin);
		/* hue */
		Rdelta = ( ((cMax-R)*(HSLMAX/6)) + ((cMax-cMin)/2) ) / (cMax-cMin);
		Gdelta = ( ((cMax-G)*(HSLMAX/6)) + ((cMax-cMin)/2) ) / (cMax-cMin);
		Bdelta = ( ((cMax-B)*(HSLMAX/6)) + ((cMax-cMin)/2) ) / (cMax-cMin);

		if (R == cMax)
			H = Bdelta - Gdelta;
		else if (G == cMax)
			H = (HSLMAX/3) + Rdelta - Bdelta;
		else /* B == cMax */
			H = ((2*HSLMAX)/3) + Gdelta - Rdelta;

		if (H < 0) H += HSLMAX;
		if (H > HSLMAX) H -= HSLMAX;
	}
	RGBQUAD hsl={L,S,H,0};
	return hsl;
}
/**************************************/
WORD CxImage::HueToRGB(WORD n1,WORD n2,WORD hue)
{ 
	/* range check: note values passed add/subtract thirds of range */
	if (hue < 0) hue += HSLMAX;
	if (hue > HSLMAX) hue -= HSLMAX;

	/* return r,g, or b value from this tridrant */
	if (hue < (HSLMAX/6))
		return ( n1 + (((n2-n1)*hue+(HSLMAX/12))/(HSLMAX/6)) );
	if (hue < (HSLMAX/2))
		return ( n2 );
	if (hue < ((HSLMAX*2)/3))
		return ( n1 + (((n2-n1)*(((HSLMAX*2)/3)-hue)+(HSLMAX/12))/(HSLMAX/6))); 
	else
		return ( n1 );
} 
/**************************************/
RGBQUAD CxImage::HSLtoRGB(COLORREF cHSLColor)
{
	return HSLtoRGB(RGB2RGBQUAD(cHSLColor));
}
/**************************************/
RGBQUAD CxImage::HSLtoRGB(RGBQUAD lHSLColor)
{ 
	WORD hue,lum,sat;
	BYTE R,G,B;					/* RGB component values */
	WORD Magic1,Magic2;			/* calculated magic numbers (really!) */

	hue = lHSLColor.rgbRed;	/* get H, S, and L out of DWORD */
	sat = lHSLColor.rgbGreen;
	lum = lHSLColor.rgbBlue;

	if (sat == 0) {            /* achromatic case */
		R=G=B=(lum*RGBMAX)/HSLMAX;
	} else {                   /* chromatic case */
		/* set up magic numbers */
		if (lum <= (HSLMAX/2))
			Magic2 = (lum*(HSLMAX + sat) + (HSLMAX/2))/HSLMAX;
		else
			Magic2 = lum + sat - ((lum*sat) + (HSLMAX/2))/HSLMAX;
		Magic1 = 2*lum-Magic2;

		/* get RGB, change units from HSLMAX to RGBMAX */
		R = (HueToRGB(Magic1,Magic2,(WORD)(hue+(HSLMAX/3)))*RGBMAX+(HSLMAX/2))/HSLMAX; 
		G = (HueToRGB(Magic1,Magic2,hue)*RGBMAX + (HSLMAX/2)) / HSLMAX;
		B = (HueToRGB(Magic1,Magic2,(WORD)(hue-(HSLMAX/3)))*RGBMAX+(HSLMAX/2))/HSLMAX; 
	}
	RGBQUAD rgb={B,G,R,0};
	return rgb;
}
/**************************************/
RGBQUAD CxImage::RGB2RGBQUAD(COLORREF cr)
{
	RGBQUAD c;
	c.rgbRed = GetRValue(cr);	/* get R, G, and B out of DWORD */
	c.rgbGreen = GetGValue(cr);
	c.rgbBlue = GetBValue(cr);
	c.rgbReserved=0;
	return c;
}
/**************************************/
COLORREF CxImage::RGBQUAD2RGB (RGBQUAD c)
{
	return RGB(c.rgbRed,c.rgbGreen,c.rgbBlue);
}
/**************************************/
bool CxImage::GetRGB(int i, BYTE* r, BYTE* g, BYTE* b)
{
	RGBQUAD* ppal=GetPalette();
	if (ppal) {
		*r = ppal[i].rgbRed;
		*g = ppal[i].rgbGreen;
		*b = ppal[i].rgbBlue; 
		return true;
	}
	return false;
}
/**************************************/
void CxImage::SetPalette(DWORD n, BYTE *r, BYTE *g, BYTE *b)
{
	if ((!r)||(hDib==NULL)||(head.biClrUsed==0)) return;
	if (!g) g = r;
	if (!b) b = g;
	RGBQUAD* ppal=GetPalette();
	DWORD m=min(n,head.biClrUsed);
	for (DWORD i=0; i<m;i++){
		ppal[i].rgbRed=r[i];
		ppal[i].rgbGreen=g[i];
		ppal[i].rgbBlue=b[i];
	}

}
/**************************************/
void CxImage::SetPalette(rgb_color_struct *rgb,DWORD nColors)
{
	if ((!rgb)||(hDib==NULL)||(head.biClrUsed==0)) return;
	RGBQUAD* ppal=GetPalette();
	DWORD m=min(nColors,head.biClrUsed);
	for (DWORD i=0; i<m;i++){
		ppal[i].rgbRed=rgb[i].r;
		ppal[i].rgbGreen=rgb[i].g;
		ppal[i].rgbBlue=rgb[i].b;
	}
}
/**************************************/
void CxImage::SetPalette(RGBQUAD* pPal,DWORD nColors)
{
	if ((pPal==NULL)||(hDib==NULL)||(head.biClrUsed==0)) return;
	memcpy(GetPalette(),pPal,min(GetPaletteSize(),nColors*sizeof(RGBQUAD)));
}
/**************************************/
void CxImage::SetGrayPalette()
{
	if ((hDib==NULL)||(head.biClrUsed==0)) return;
	RGBQUAD* pal=GetPalette();
	for (ULONG ni=0;ni<head.biClrUsed;ni++)
		pal[ni].rgbBlue=pal[ni].rgbGreen = pal[ni].rgbRed = (BYTE)(ni*(255/(head.biClrUsed-1)));
}
/**************************************/
void CxImage::BlendPalette(COLORREF cr,long perc)
{
	if ((hDib==NULL)||(head.biClrUsed==0)) return;
	BYTE* iDst = (BYTE*)(hDib) + sizeof(BITMAPINFOHEADER);
	DWORD i,r,g,b;
	RGBQUAD* pPal=(RGBQUAD*)iDst;
	r = GetRValue(cr);
	g = GetGValue(cr);
	b = GetBValue(cr);
	if (perc>100) perc=100;
	for(i=0;i<head.biClrUsed;i++){
		pPal[i].rgbBlue=(BYTE)((pPal[i].rgbBlue*(100-perc)+b*perc)/100);
		pPal[i].rgbGreen =(BYTE)((pPal[i].rgbGreen*(100-perc)+g*perc)/100);
		pPal[i].rgbRed =(BYTE)((pPal[i].rgbRed*(100-perc)+r*perc)/100);
	}
}
/**************************************/
// returns the whole hDib dimension
long CxImage::GetSize()
{
	return head.biSize + head.biSizeImage + GetPaletteSize();
}
/**************************************/
bool CxImage::IsValid()
{
	return (hDib!=NULL);
}
/**************************************/
bool CxImage::IsInside(long x, long y)
{
  return (0<=y && y<head.biHeight && 0<=x && x<head.biWidth);
}
/**************************************/
void CxImage::Copy(CxImage *src)
{
	if (src){
		memcpy(&info,&src->info,sizeof(CXIMAGEINFO));
	 	Create(src->GetWidth(),src->GetHeight(),src->GetBpp(),src->GetType());
	 	if (hDib && src->hDib) memcpy(hDib,src->hDib,GetSize());
	}
}
/**************************************/
// Transfer the image in a global bitmap handle (clipboard copy)
HANDLE CxImage::CopyToHandle()
{
	HANDLE hMem=NULL;
	if (hDib){
		hMem= GlobalAlloc(GHND, GetSize());
		BYTE* pDst=(BYTE*)GlobalLock(hMem);
		memcpy(pDst,hDib,GetSize());
		GlobalUnlock(hMem);
	}
	return hMem;
}
/**************************************/
// Transfer the image in a  bitmap handle
HBITMAP CxImage::MakeBitmap(HDC hdc)
{
	if ((!hdc) || (!hDib))  return NULL;
	// this single line seems to work very well
	HBITMAP bmp = CreateDIBitmap(hdc, (LPBITMAPINFOHEADER)hDib, CBM_INIT,
		GetBits(), (LPBITMAPINFO)hDib, DIB_RGB_COLORS);
	return bmp;
}
/**************************************/
void CxImage::Clear(BYTE bval)
{
	if (hDib) memset(info.pImage,bval,head.biSizeImage);
}
/**************************************/
// moves everything from (*from) to (this), (*from) become empty
void CxImage::Transfer(CxImage *from)
{
	if (from){
		if (hDib) free(hDib);

		memcpy(&head,&from->head,sizeof(BITMAPINFOHEADER));
		memcpy(&info,&from->info,sizeof(CXIMAGEINFO));
		hDib = from->hDib;

		memset(&from->head,0,sizeof(BITMAPINFOHEADER));
		memset(&from->info,0,sizeof(CXIMAGEINFO));
		from->hDib=NULL;
	}
}
/**************************************/
// (this) points to the same hDib owned by (*from), the image remains in (*from)
// but (this) has the access to the bits. Use carefully !!!
void CxImage::Ghost(CxImage *from)
{
	if (from){
		memcpy(&head,&from->head,sizeof(BITMAPINFOHEADER));
		memcpy(&info,&from->info,sizeof(CXIMAGEINFO));
		hDib = from->hDib;
		info.pGhost=from;
	}
}
bool CxImage::SaveFile(LPCWSTR filename, DWORD imagetype)
{
	FILE* hFile;	//file handle to write the image
	if ((hFile=_wfopen(filename,L"wb"))==NULL)  return false;
	bool bOK = Encode(hFile,imagetype);
	fclose(hFile);
	return bOK;
}
/**************************************/
bool CxImage::SaveFile(const char * filename, DWORD imagetype)
{
	FILE* hFile;	//file handle to write the image
	if ((hFile=fopen(filename,"wb"))==NULL)  return false;
	bool bOK = Encode(hFile,imagetype);
	fclose(hFile);
	return bOK;
}
/**************************************/
bool CxImage::Encode(FILE *hFile, DWORD imagetype)
{

#if CXIMAGE_SUPPORT_BMP
	if (imagetype==CXIMAGE_FORMAT_BMP){
		CxImageBMP newima;
		newima.Ghost(this);
		if (newima.Encode(hFile)){
			return true;
		} else {
			strcpy(info.szLastError,newima.GetLastError());
			return false;
		}
	}
#endif
#if CXIMAGE_SUPPORT_ICO
	if (imagetype==CXIMAGE_FORMAT_ICO){
		CxImageICO newima;
		newima.Ghost(this);
		if (newima.Encode(hFile)){
			return true;
		} else {
			strcpy(info.szLastError,newima.GetLastError());
			return false;
		}
	}
#endif
#if CXIMAGE_SUPPORT_TIF
	if (imagetype==CXIMAGE_FORMAT_TIF){
		CxImageTIF newima;
		newima.Ghost(this);
		if (newima.Encode(hFile)){
			return true;
		} else {
			strcpy(info.szLastError,newima.GetLastError());
			return false;
		}
	}
#endif
#if CXIMAGE_SUPPORT_JPG
	if (imagetype==CXIMAGE_FORMAT_JPG){
		CxImageJPG newima;
		newima.Ghost(this);
		if (newima.Encode(hFile)){
			return true;
		} else {
			strcpy(info.szLastError,newima.GetLastError());
			return false;
		}
	}
#endif
#if CXIMAGE_SUPPORT_GIF
	if (imagetype==CXIMAGE_FORMAT_GIF){
		CxImageGIF newima;
		newima.Ghost(this);
		if (newima.Encode(hFile)){
			return true;
		} else {
			strcpy(info.szLastError,newima.GetLastError());
			return false;
		}
	}
#endif
#if CXIMAGE_SUPPORT_PNG
	if (imagetype==CXIMAGE_FORMAT_PNG){
		CxImagePNG newima;
		newima.Ghost(this);
		if (newima.Encode(hFile)){
			return true;
		} else {
			strcpy(info.szLastError,newima.GetLastError());
			return false;
		}
	}
#endif
#if CXIMAGE_SUPPORT_MNG
	if (imagetype==CXIMAGE_FORMAT_MNG){
		CxImageMNG newima;
		newima.Ghost(this);
		if (newima.Encode(hFile)){
			return true;
		} else {
			strcpy(info.szLastError,newima.GetLastError());
			return false;
		}
	}
#endif
	strcpy(info.szLastError,"Unsupported operation for this format");
	return false;
}
/**************************************/
bool CxImage::ReadFile(const char * filename, DWORD imagetype)
{
	FILE* hFile;	//file handle to read the image
	if ((hFile=fopen(filename,"rb"))==NULL)  return false;
	bool bOK = Decode(hFile,imagetype);
	fclose(hFile);
	return bOK;
}
/**************************************/
bool CxImage::ReadFile(LPCWSTR filename, DWORD imagetype)
{
	FILE* hFile;	//file handle to read the image
	if ((hFile=_wfopen(filename, L"rb"))==NULL)  return false;
	bool bOK = Decode(hFile,imagetype);
	fclose(hFile);
	return bOK;
}
/**************************************/
bool CxImage::LoadResource(HRSRC hRes, DWORD imagetype)
{
	DWORD rsize=SizeofResource(NULL,hRes);
	HGLOBAL hMem=::LoadResource(NULL,hRes);
	if (hMem){
		char* lpVoid=(char*)LockResource(hMem);
		if (lpVoid){
			FILE* fTmp=tmpfile();
			if (fTmp){
				fwrite(lpVoid,rsize,1,fTmp);
				fseek(fTmp,0,SEEK_SET);
				bool bOK = Decode(fTmp,imagetype);
				fclose(fTmp);
				info.dwType = imagetype;
				return bOK;
			}
		}
	} else strcpy(info.szLastError,"Unable to load resource!");
	return false;
}
/**************************************/
bool CxImage::Decode(FILE *hFile, DWORD imagetype)
{

#if CXIMAGE_SUPPORT_BMP
	if (imagetype==CXIMAGE_FORMAT_BMP){
		CxImageBMP newima;
		newima.Transfer(this);
		if (newima.Decode(hFile)){
			Transfer(&newima);
			return true;
		} else {
			strcpy(info.szLastError,newima.GetLastError());
			return false;
		}
	}
#endif
#if CXIMAGE_SUPPORT_JPG
	if (imagetype==CXIMAGE_FORMAT_JPG){
		CxImageJPG newima;
		newima.Transfer(this);
		if (newima.Decode(hFile)){
			Transfer(&newima);
			return true;
		} else {
			strcpy(info.szLastError,newima.GetLastError());
			return false;
		}
	}
#endif
#if CXIMAGE_SUPPORT_ICO
	if (imagetype==CXIMAGE_FORMAT_ICO){
		CxImageICO newima;
		newima.Transfer(this);
		if (newima.Decode(hFile)){
			Transfer(&newima);
			return true;
		} else {
			strcpy(info.szLastError,newima.GetLastError());
			return false;
		}
	}
#endif
#if CXIMAGE_SUPPORT_GIF
	if (imagetype==CXIMAGE_FORMAT_GIF){
		CxImageGIF newima;
		newima.Transfer(this);
		if (newima.Decode(hFile)){
			Transfer(&newima);
			return true;
		} else {
			strcpy(info.szLastError,newima.GetLastError());
			return false;
		}
	}
#endif
#if CXIMAGE_SUPPORT_PNG
	if (imagetype==CXIMAGE_FORMAT_PNG){
		CxImagePNG newima;
		newima.Transfer(this);
		if (newima.Decode(hFile)){
			Transfer(&newima);
			return true;
		} else {
			strcpy(info.szLastError,newima.GetLastError());
			return false;
		}
	}
#endif
#if CXIMAGE_SUPPORT_TIF
	if (imagetype==CXIMAGE_FORMAT_TIF){
		CxImageTIF newima;
		newima.Transfer(this);
		if (newima.Decode(hFile)){
			Transfer(&newima);
			return true;
		} else {
			strcpy(info.szLastError,newima.GetLastError());
			return false;
		}
	}
#endif
#if CXIMAGE_SUPPORT_MNG
	if (imagetype==CXIMAGE_FORMAT_MNG){
		CxImageMNG newima;
		newima.Transfer(this);
		if (newima.Decode(hFile)){
			Transfer(&newima);
			return true;
		} else {
			strcpy(info.szLastError,newima.GetLastError());
			return false;
		}
	}
#endif
	strcpy(info.szLastError,"Unsupported operation for this format");
	return false;
}
/**************************************/
bool CxImage::Flip()
{
	if (!hDib) return false;
	CxImage* imatmp = new CxImage(this);
	if (!imatmp) return false;
	BYTE *iSrc,*iDst;
	iSrc=info.pImage + (head.biHeight-1)*info.dwEffWidth;
	iDst=imatmp->info.pImage;
    for(long y=0; y < head.biHeight; y++){
		memcpy(iDst,iSrc,info.dwEffWidth);
		iSrc-=info.dwEffWidth;
		iDst+=info.dwEffWidth;
	}
	Transfer(imatmp);
	delete imatmp;
	return true;
}
/**************************************/
bool CxImage::Mirror()
{
	if (!hDib) return false;

	CxImage* imatmp = new CxImage(this);
	if (!imatmp) return false;
	BYTE *iSrc,*iDst;
	long wdt=(head.biWidth-1) * (head.biBitCount==24 ? 3:1);
	iSrc=info.pImage + wdt;
	iDst=imatmp->info.pImage;
	long x,y;
	switch (head.biBitCount){
	case 24:
		for(y=0; y < head.biHeight; y++){
			for(x=0; x <= wdt; x+=3){
				*(iDst+x)=*(iSrc-x);
				*(iDst+x+1)=*(iSrc-x+1);
				*(iDst+x+2)=*(iSrc-x+2);
			}
			iSrc+=info.dwEffWidth;
			iDst+=info.dwEffWidth;
		}
		break;
	case 8:
		for(y=0; y < head.biHeight; y++){
			for(x=0; x <= wdt; x++)
				*(iDst+x)=*(iSrc-x);
			iSrc+=info.dwEffWidth;
			iDst+=info.dwEffWidth;
		}
		break;
	default:
		for(y=0; y < head.biHeight; y++){
			for(x=0; x <= wdt; x++)
				imatmp->SetPixelIndex(x,y,GetPixelIndex(wdt-x,y));
		}
	}
	Transfer(imatmp);
	delete imatmp;
	return true;
}
/**************************************/
bool CxImage::Negative()
{
	if (!hDib) return false;

	if (head.biBitCount<=8){
		RGBQUAD* ppal=GetPalette();
		for(DWORD i=0;i<head.biClrUsed;i++){
			ppal[i].rgbBlue =255-ppal[i].rgbBlue;
			ppal[i].rgbGreen =255-ppal[i].rgbGreen;
			ppal[i].rgbRed =255-ppal[i].rgbRed;
		}
	} else {
		BYTE *iSrc=info.pImage;
		long n=head.biHeight*info.dwEffWidth;
		for(long i=0; i < n; i++){
			*iSrc=~(*(iSrc));
			iSrc++;
		}
	}
	return true;
}
/**************************************/
bool CxImage::GrayScale()
{
	if (!hDib) return false;
	if (head.biBitCount<=8){
		RGBQUAD* ppal=GetPalette();
		int gray;
		//converts the colors to gray
		for(DWORD i=0;i<head.biClrUsed;i++){
			gray=RGB2GRAY(ppal[i].rgbRed,ppal[i].rgbGreen,ppal[i].rgbBlue);
			ppal[i].rgbBlue = ppal[i].rgbGreen = ppal[i].rgbRed = gray;
		}
		// preserve transparency
		if (info.nBkgndIndex != -1) info.nBkgndIndex = ppal[info.nBkgndIndex].rgbBlue;
		//create a "real" 8 bit gray scale image
		if (head.biBitCount==8){
			BYTE *img=info.pImage;
			for(DWORD i=0;i<head.biSizeImage;i++) img[i]=ppal[img[i]].rgbBlue;
			SetGrayPalette();
		}
		//transform to 8 bit gray scale
		if (head.biBitCount==4 || head.biBitCount==1){
			CxImage ima(head.biWidth,head.biHeight,8);
			ima.SetGrayPalette();
			BYTE *img=ima.GetBits();
			long l=ima.GetEffWidth();
			for (long y=0;y<head.biHeight;y++){
				for (long x=0;x<head.biWidth; x++){
					img[x+y*l]=ppal[GetPixelIndex(x,y)].rgbBlue;
				}
			}
			Transfer(&ima);
		}
	} else { //from RGB to 8 bit gray scale
		BYTE *iSrc=info.pImage;
		CxImage ima(head.biWidth,head.biHeight,8);
		ima.SetGrayPalette();
		BYTE *img=ima.GetBits();
		long l8=ima.GetEffWidth();
		long l=head.biWidth * 3;
		for(long y=0; y < head.biHeight; y++) {
			for(long x=0,x8=0; x < l; x+=3,x8++) {
				img[x8+y*l8]=RGB2GRAY(*(iSrc+x+2),*(iSrc+x+1),*(iSrc+x+0));
			}
			iSrc+=info.dwEffWidth;
		}
		Transfer(&ima);
	}
	return true;
}
/**************************************/
bool CxImage::Rotate(float angle)
{
	if (!hDib) return false;

//  $Id: FilterRotate.cpp,v 1.10 2000/12/18 22:42:53 uzadow Exp $
//  Copyright (c) 1996-1998 Ulrich von Zadow

	// Negative the angle, because the y-axis is negative.
	double ang = -angle*acos(0)/90;
	int newWidth, newHeight;
	int nWidth = GetWidth();
	int nHeight= GetHeight();
	double cos_angle = cos(ang);
	double sin_angle = sin(ang);

	// Calculate the size of the new bitmap
	POINT p1={0,0};
	POINT p2={nWidth,0};
	POINT p3={0,nHeight};
	POINT p4={nWidth-1,nHeight};
	POINT newP1,newP2,newP3,newP4, leftTop, rightTop, leftBottom, rightBottom;

	newP1.x = p1.x;
	newP1.y = p1.y;
	newP2.x = (long)(p2.x*cos_angle - p2.y*sin_angle);
	newP2.y = (long)(p2.x*sin_angle + p2.y*cos_angle);
	newP3.x = (long)(p3.x*cos_angle - p3.y*sin_angle);
	newP3.y = (long)(p3.x*sin_angle + p3.y*cos_angle);
	newP4.x = (long)(p4.x*cos_angle - p4.y*sin_angle);
	newP4.y = (long)(p4.x*sin_angle + p4.y*cos_angle);

	leftTop.x = min(min(newP1.x,newP2.x),min(newP3.x,newP4.x));
	leftTop.y = min(min(newP1.y,newP2.y),min(newP3.y,newP4.y));
	rightBottom.x = max(max(newP1.x,newP2.x),max(newP3.x,newP4.x));
	rightBottom.y = max(max(newP1.y,newP2.y),max(newP3.y,newP4.y));
	leftBottom.x = leftTop.x;
	leftBottom.y = rightBottom.y;
	rightTop.x = rightBottom.x;
	rightTop.y = leftTop.y;

	newWidth = rightTop.x - leftTop.x;
	newHeight= leftBottom.y - leftTop.y;
	CxImage imgDest(newWidth,newHeight,GetBpp());
	imgDest.SetPalette(GetPalette());
	imgDest.info.nBkgndIndex = info.nBkgndIndex;// TRK

	int x,y,newX,newY,oldX,oldY;

	if (head.biClrUsed==0){ //RGB
		for (y = leftTop.y, newY = 0; y<=leftBottom.y; y++,newY++){
			info.nProgress = (long)(100*newY/newHeight);
			if (info.nEscape) break;
			for (x = leftTop.x, newX = 0; x<=rightTop.x; x++,newX++){
				oldX = (long)(x*cos_angle + y*sin_angle - 0.5);
				oldY = (long)(y*cos_angle - x*sin_angle - 0.5);
				imgDest.SetPixelColor(newX,newY,GetPixelColor(oldX,oldY));
			}
		}
	} else { //PALETTE
		for (y = leftTop.y, newY = 0; y<=leftBottom.y; y++,newY++){
			info.nProgress = (long)(100*newY/newHeight);
			if (info.nEscape) break;
			for (x = leftTop.x, newX = 0; x<=rightTop.x; x++,newX++){
				oldX = (long)(x*cos_angle + y*sin_angle - 0.5);
				oldY = (long)(y*cos_angle - x*sin_angle - 0.5);
				imgDest.SetPixelIndex(newX,newY,GetPixelIndex(oldX,oldY));
			}
		}
	}

	Transfer(&imgDest);
	return true;
}
/**************************************/
bool CxImage::IsGrayScale()
{
	RGBQUAD* ppal=GetPalette();
	if(!(hDib && ppal && head.biClrUsed)) return false;
	for(DWORD i=0;i<head.biClrUsed;i++){
		if (ppal[i].rgbBlue!=i || ppal[i].rgbGreen!=i || ppal[i].rgbRed!=i) return false;
	}
	return true;
}
/**************************************/
// swap two indexes in the image and their colors in the palette
void CxImage::SwapIndex(BYTE idx1, BYTE idx2)
{
	RGBQUAD* ppal=GetPalette();
	if(!(hDib && ppal)) return;
	//swap the colors
	RGBQUAD tempRGB=GetPaletteColor(idx1);
	SetPaletteIndex(idx1,GetPaletteColor(idx2));
	SetPaletteIndex(idx2,tempRGB);
	//swap the pixels
	BYTE idx;
	for(long y=0; y < head.biHeight; y++){
		for(long x=0; x <= head.biWidth; x++){
			idx=GetPixelIndex(x,y);
			if (idx==idx1) SetPixelIndex(x,y,idx2);
			if (idx==idx2) SetPixelIndex(x,y,idx1);
		}
	}
}
/**************************************/
bool CxImage::Resample(long newx, long newy, int fast)
{
	if (newx==0 || newy==0) return false;

	float xScale, yScale, fX, fY;
	xScale = (float)head.biWidth  / (float)newx;
	yScale = (float)head.biHeight / (float)newy;

	CxImage newImage(newx,newy,head.biBitCount);
	newImage.SetPalette(GetPalette());
	newImage.info.nBkgndIndex = info.nBkgndIndex;

	if (fast) {
		for(long y=0; y<newy; y++){
			info.nProgress = (long)(100*y/newy);
			if (info.nEscape) break;
			fY = y * yScale;
			for(long x=0; x<newx; x++){
				fX = x * xScale;
				newImage.SetPixelColor(x,y,GetPixelColor((long)fX,(long)fY));
			}
		}
	} else {
		//© 1999 Steve McMahon (steve@dogma.demon.co.uk)
		long ifX, ifY, ifX1, ifY1, xmax, ymax;
		float ir1, ir2, ig1, ig2, ib1, ib2, dx, dy;
		BYTE r,g,b;
		RGBQUAD rgb1, rgb2, rgb3, rgb4;
		xmax = head.biWidth-1;
		ymax = head.biHeight-1;
		for(long y=0; y<newy; y++){
			info.nProgress = (long)(100*y/newy);
			if (info.nEscape) break;
			fY = y * yScale;
			ifY = (int)fY;
			ifY1 = min(ymax, ifY+1);
			dy = fY - ifY;
			for(long x=0; x<newx; x++){
				fX = x * xScale;
				ifX = (int)fX;
				ifX1 = min(xmax, ifX+1);
				dx = fX - ifX;
				// Interpolate using the four nearest pixels in the source
				if (head.biClrUsed){
					rgb1=GetPaletteColor(GetPixelIndex(ifX,ifY));
					rgb2=GetPaletteColor(GetPixelIndex(ifX1,ifY));
					rgb3=GetPaletteColor(GetPixelIndex(ifX,ifY1));
					rgb4=GetPaletteColor(GetPixelIndex(ifX1,ifY1));
				}
				else {
					BYTE* iDst;
					iDst = info.pImage + ifY*info.dwEffWidth + ifX*3;
					rgb1.rgbBlue = *iDst++;	rgb1.rgbGreen= *iDst++;	rgb1.rgbRed =*iDst;
					iDst = info.pImage + ifY*info.dwEffWidth + ifX1*3;
					rgb2.rgbBlue = *iDst++;	rgb2.rgbGreen= *iDst++;	rgb2.rgbRed =*iDst;
					iDst = info.pImage + ifY1*info.dwEffWidth + ifX*3;
					rgb3.rgbBlue = *iDst++;	rgb3.rgbGreen= *iDst++;	rgb3.rgbRed =*iDst;
					iDst = info.pImage + ifY1*info.dwEffWidth + ifX1*3;
					rgb4.rgbBlue = *iDst++;	rgb4.rgbGreen= *iDst++;	rgb4.rgbRed =*iDst;
				}
				// Interplate in x direction:
				ir1 = rgb1.rgbRed   * (1 - dy) + rgb3.rgbRed   * dy;
				ig1 = rgb1.rgbGreen * (1 - dy) + rgb3.rgbGreen * dy;
				ib1 = rgb1.rgbBlue  * (1 - dy) + rgb3.rgbBlue  * dy;
				ir2 = rgb2.rgbRed   * (1 - dy) + rgb4.rgbRed   * dy;
				ig2 = rgb2.rgbGreen * (1 - dy) + rgb4.rgbGreen * dy;
				ib2 = rgb2.rgbBlue  * (1 - dy) + rgb4.rgbBlue  * dy;
				// Interpolate in y:
				r = (BYTE)(ir1 * (1 - dx) + ir2 * dx);
				g = (BYTE)(ig1 * (1 - dx) + ig2 * dx);
				b = (BYTE)(ib1 * (1 - dx) + ib2 * dx);
				// Set output
				newImage.SetPixelColor(x,y,RGB(r,g,b));
			}
		}
	}

	Transfer(&newImage);
	return true;
}
/**************************************/
bool CxImage::DecreaseBpp(DWORD nbit, bool errordiffusion, RGBQUAD* ppal, DWORD clrimportant)
{
	if (!hDib) return false;
	if (head.biBitCount <  nbit) return false;
	if (head.biBitCount == nbit){
		if (clrimportant==0) return true;
		if (head.biClrImportant && (head.biClrImportant<clrimportant)) return true;
	}

	long er,eg,eb;
	RGBQUAD c,ce;

	CxImage tmp;
	tmp.CopyInfo(*this);
	tmp.Create(head.biWidth,head.biHeight,(WORD)nbit,info.dwType);
	if (clrimportant) tmp.SetClrImportant(clrimportant);

	switch (tmp.head.biBitCount){
	case 1:
		if (ppal) tmp.SetPalette(ppal,16);
		else {
			tmp.SetPaletteIndex(0,0,0,0);
			tmp.SetPaletteIndex(1,255,255,255);
		}
		break;
	case 4:
		if (ppal) tmp.SetPalette(ppal,16);
		else tmp.SetStdPalette();
		break;
	case 8:
		if (ppal) tmp.SetPalette(ppal);
		else tmp.SetStdPalette();
		break;
	default:
		return false;
	}

	for (long y=0;y<head.biHeight;y++){
		if (info.nEscape) break;
		info.nProgress = (long)(100*y/head.biHeight);
		for (long x=0;x<head.biWidth;x++){
			if (!errordiffusion){
				tmp.SetPixelColor(x,y,GetPixelColor(x,y));
			} else {
				c=GetPixelColor(x,y);
				tmp.SetPixelColor(x,y,c);

				ce=tmp.GetPixelColor(x,y);
				er=(long)c.rgbRed - (long)ce.rgbRed;
				eg=(long)c.rgbGreen - (long)ce.rgbGreen;
				eb=(long)c.rgbBlue - (long)ce.rgbBlue;

				c = GetPixelColor(x+1,y);
				c.rgbRed = (BYTE)min(255L,max(0L,(long)c.rgbRed + ((er*7)/16)));
				c.rgbGreen = (BYTE)min(255L,max(0L,(long)c.rgbGreen + ((eg*7)/16)));
				c.rgbBlue = (BYTE)min(255L,max(0L,(long)c.rgbBlue + ((eb*7)/16)));
				SetPixelColor(x+1,y,c);
				int coeff;
				for(int i=-1; i<2; i++){
					switch(i){
					case -1:
						coeff=2; break;
					case 0:
						coeff=4; break;
					case 1:
						coeff=1; break;
					}
					c = GetPixelColor(x+i,y+1);
					c.rgbRed = (BYTE)min(255L,max(0L,(long)c.rgbRed + ((er * coeff)/16)));
					c.rgbGreen = (BYTE)min(255L,max(0L,(long)c.rgbGreen + ((eg * coeff)/16)));
					c.rgbBlue = (BYTE)min(255L,max(0L,(long)c.rgbBlue + ((eb * coeff)/16)));
					SetPixelColor(x+i,y+1,c);
				}
			}
		}
	}

	if (head.biBitCount==1){
		tmp.SetPaletteIndex(0,0,0,0);
		tmp.SetPaletteIndex(1,255,255,255);
	}

	Transfer(&tmp);
	return true;
}
/**************************************/
void CxImage::SetStdPalette()
{
	if (!hDib) return;
	switch (head.biBitCount){
	case 8:
		{
			const BYTE pal256[1024] = {0,0,0,0,0,0,128,0,0,128,0,0,0,128,128,0,128,0,0,0,128,0,128,0,128,128,0,0,192,192,192,0,
			192,220,192,0,240,202,166,0,212,240,255,0,177,226,255,0,142,212,255,0,107,198,255,0,
			72,184,255,0,37,170,255,0,0,170,255,0,0,146,220,0,0,122,185,0,0,98,150,0,0,74,115,0,0,
			50,80,0,212,227,255,0,177,199,255,0,142,171,255,0,107,143,255,0,72,115,255,0,37,87,255,0,0,
			85,255,0,0,73,220,0,0,61,185,0,0,49,150,0,0,37,115,0,0,25,80,0,212,212,255,0,177,177,255,0,
			142,142,255,0,107,107,255,0,72,72,255,0,37,37,255,0,0,0,254,0,0,0,220,0,0,0,185,0,0,0,150,0,
			0,0,115,0,0,0,80,0,227,212,255,0,199,177,255,0,171,142,255,0,143,107,255,0,115,72,255,0,
			87,37,255,0,85,0,255,0,73,0,220,0,61,0,185,0,49,0,150,0,37,0,115,0,25,0,80,0,240,212,255,0,
			226,177,255,0,212,142,255,0,198,107,255,0,184,72,255,0,170,37,255,0,170,0,255,0,146,0,220,0,
			122,0,185,0,98,0,150,0,74,0,115,0,50,0,80,0,255,212,255,0,255,177,255,0,255,142,255,0,255,107,255,0,
			255,72,255,0,255,37,255,0,254,0,254,0,220,0,220,0,185,0,185,0,150,0,150,0,115,0,115,0,80,0,80,0,
			255,212,240,0,255,177,226,0,255,142,212,0,255,107,198,0,255,72,184,0,255,37,170,0,255,0,170,0,
			220,0,146,0,185,0,122,0,150,0,98,0,115,0,74,0,80,0,50,0,255,212,227,0,255,177,199,0,255,142,171,0,
			255,107,143,0,255,72,115,0,255,37,87,0,255,0,85,0,220,0,73,0,185,0,61,0,150,0,49,0,115,0,37,0,
			80,0,25,0,255,212,212,0,255,177,177,0,255,142,142,0,255,107,107,0,255,72,72,0,255,37,37,0,254,0,
			0,0,220,0,0,0,185,0,0,0,150,0,0,0,115,0,0,0,80,0,0,0,255,227,212,0,255,199,177,0,255,171,142,0,
			255,143,107,0,255,115,72,0,255,87,37,0,255,85,0,0,220,73,0,0,185,61,0,0,150,49,0,0,115,37,0,
			0,80,25,0,0,255,240,212,0,255,226,177,0,255,212,142,0,255,198,107,0,255,184,72,0,255,170,37,0,
			255,170,0,0,220,146,0,0,185,122,0,0,150,98,0,0,115,74,0,0,80,50,0,0,255,255,212,0,255,255,177,0,
			255,255,142,0,255,255,107,0,255,255,72,0,255,255,37,0,254,254,0,0,220,220,0,0,185,185,0,0,150,150,0,
			0,115,115,0,0,80,80,0,0,240,255,212,0,226,255,177,0,212,255,142,0,198,255,107,0,184,255,72,0,
			170,255,37,0,170,255,0,0,146,220,0,0,122,185,0,0,98,150,0,0,74,115,0,0,50,80,0,0,227,255,212,0,
			199,255,177,0,171,255,142,0,143,255,107,0,115,255,72,0,87,255,37,0,85,255,0,0,73,220,0,0,61,185,0,
			0,49,150,0,0,37,115,0,0,25,80,0,0,212,255,212,0,177,255,177,0,142,255,142,0,107,255,107,0,72,255,72,0,
			37,255,37,0,0,254,0,0,0,220,0,0,0,185,0,0,0,150,0,0,0,115,0,0,0,80,0,0,212,255,227,0,177,255,199,0,
			142,255,171,0,107,255,143,0,72,255,115,0,37,255,87,0,0,255,85,0,0,220,73,0,0,185,61,0,0,150,49,0,0,
			115,37,0,0,80,25,0,212,255,240,0,177,255,226,0,142,255,212,0,107,255,198,0,72,255,184,0,37,255,170,0,
			0,255,170,0,0,220,146,0,0,185,122,0,0,150,98,0,0,115,74,0,0,80,50,0,212,255,255,0,177,255,255,0,
			142,255,255,0,107,255,255,0,72,255,255,0,37,255,255,0,0,254,254,0,0,220,220,0,0,185,185,0,0,
			150,150,0,0,115,115,0,0,80,80,0,242,242,242,0,230,230,230,0,218,218,218,0,206,206,206,0,194,194,194,0,
			182,182,182,0,170,170,170,0,158,158,158,0,146,146,146,0,134,134,134,0,122,122,122,0,110,110,110,0,
			98,98,98,0,86,86,86,0,74,74,74,0,62,62,62,0,50,50,50,0,38,38,38,0,26,26,26,0,14,14,14,0,240,251,255,0,
			164,160,160,0,128,128,128,0,0,0,255,0,0,255,0,0,0,255,255,0,255,0,0,0,255,0,255,0,255,255,0,0,255,255,255,0};
			memcpy(GetPalette(),pal256,1024);
			break;
		}
	case 4:
		{
			const BYTE pal16[64]={0,0,0,0,0,0,128,0,0,128,0,0,0,128,128,0,128,0,0,0,128,0,128,0,128,128,0,0,192,192,192,0,
								128,128,128,0,0,0,255,0,0,255,0,0,0,255,255,0,255,0,0,0,255,0,255,0,255,255,0,0,255,255,255,0};
			memcpy(GetPalette(),pal16,64);
			break;
		}
	}
	return;
}
/**************************************/
bool CxImage::IncreaseBpp(DWORD nbit)
{
	if (!hDib) return false;
	switch (nbit){
	case 4:
		{
			if (head.biBitCount==4) return true;
			if (head.biBitCount>4) return false;

			CxImage tmp(head.biWidth,head.biHeight,4);
			tmp.SetPalette(GetPalette(),GetNumColors());
			for (long y=0;y<head.biHeight;y++){
				for (long x=0;x<head.biWidth;x++){
					tmp.SetPixelColor(x,y,GetPixelColor(x,y));
				}
			}
			Transfer(&tmp);
			return true;
		}
	case 8:
		{
			if (head.biBitCount==8) return true;
			if (head.biBitCount>8) return false;

			CxImage tmp(head.biWidth,head.biHeight,8);
			tmp.SetPalette(GetPalette(),GetNumColors());
			for (long y=0;y<head.biHeight;y++){
				for (long x=0;x<head.biWidth;x++){
					tmp.SetPixelColor(x,y,GetPixelColor(x,y));
				}
			}
			Transfer(&tmp);
			return true;
		}
	case 24:
		{
			if (head.biBitCount==24) return true;
			if (head.biBitCount>24) return false;

			CxImage tmp(head.biWidth,head.biHeight,24);
			for (long y=0;y<head.biHeight;y++){
				for (long x=0;x<head.biWidth;x++){
					tmp.SetPixelColor(x,y,GetPixelColor(x,y));
				}
			}
			Transfer(&tmp);
			return true;
		}
	}
	return false;
}
/**************************************/
bool CxImage::Colorize(BYTE hue, BYTE sat)
{
	if (!hDib) return false;

	RGBQUAD color;
	if (head.biClrUsed==0){

		long xmin,xmax,ymin,ymax;
		xmin = ymin = 0;
		xmax = head.biWidth; ymax=head.biHeight;

		for(long y=ymin; y<ymax; y++){
			for(long x=xmin; x<xmax; x++){
				{
					color = RGBtoHSL(GetPixelColor(x,y));
					color.rgbRed=hue;
					color.rgbGreen=sat;
					SetPixelColor(x,y,HSLtoRGB(color));
				}
			}
		}
	} else {
		for(DWORD j=0; j<head.biClrUsed; j++){
			color = RGBtoHSL(GetPaletteColor((BYTE)j));
			color.rgbRed=hue;
			color.rgbGreen=sat;
			SetPaletteIndex((BYTE)j,HSLtoRGB(color));
		}
	}

	return true;
}
/**************************************/
void CxImage::SetClrImportant(DWORD ncolors)
{
	if (ncolors==0 || ncolors>256) {
		head.biClrImportant = 0;
		return;
	}

	switch(head.biBitCount){
	case 1:
		head.biClrImportant = min(ncolors,2);
		break;
	case 4:
		head.biClrImportant = min(ncolors,16);
		break;
	case 8:
		head.biClrImportant = ncolors;
		break;
	}
	return;
}
/**************************************/
//EOF
