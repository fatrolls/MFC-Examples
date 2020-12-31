// trans.c

//#include <windows.h>
#include <stdafx.h>

// DrawTransparentBitmap - Chris Becke / Raja Segar / Troels K.
static BOOL DrawTransparentHelper(HDC hdcDst, HBITMAP bmpMask,
                                  int xDst , int yDst ,
                                  int cxDst, int cyDst,
                                  HDC hdcImage,
                                  int xSrc , int ySrc ,
                                  int cxSrc, int cySrc
                                  )
{
   // We are going to paint the two DDB's in sequence to the destination.
   // 1st the monochrome bitmap will be blitted using an AND operation to
   // cut a hole in the destination. The color image will then be ORed
   // with the destination, filling it into the hole, but leaving the
   // surrounding area untouched.
   HDC dcMem   = CreateCompatibleDC(NULL);
   HGDIOBJ old = SelectObject(dcMem, bmpMask);
   BOOL bOK    = SetStretchBltMode(hdcDst,COLORONCOLOR);
   bOK = bOK && StretchBlt(hdcDst, xDst, yDst, cxDst, cyDst, dcMem , xSrc, ySrc, cxSrc, cySrc, SRCAND  );
   // Now, clean up.
   SelectObject(dcMem, old);
   DeleteDC(dcMem); dcMem = NULL;
   // Also note the use of SRCPAINT rather than SRCCOPY. 
   // Might fail with 'huge' cxDst/cyDst (Out of storage), if printing.
   bOK = bOK && StretchBlt(hdcDst, xDst, yDst, cxDst, cyDst, hdcImage, xSrc, ySrc, cxSrc, cySrc, SRCPAINT);
   return bOK;
}

EXTERN_C BOOL WINAPI DrawTransparentBitmap(HDC hdcDst, HDC hdcImage, COLORREF crTransparent, int xDst, int yDst, int cxDst, int cyDst, int cxSrc, int cySrc)
{
   BOOL bOK;
   // PREPARE MASK BEGIN
   HDC     hdcMask = CreateCompatibleDC(NULL);
   HBITMAP bmpMask = CreateBitmap(cxSrc, cySrc, 1, 1, NULL);

   // Load the bitmaps into memory DC
   HGDIOBJ oldMask = SelectObject(hdcMask, bmpMask);

   // Change the background to trans color
   COLORREF clrSaveBk = SetBkColor(hdcImage, crTransparent);

   // This call sets up the bmpMask bitmap.
   BOOL bGDI = BitBlt(hdcMask, 0, 0, cxSrc, cySrc, hdcImage,0,0,SRCCOPY);

   // Now, we need to paint onto the original image, making
   // sure that the "transparent" area is set to black. What
   // we do is AND the monochrome image onto the color Image
   // first. When blitting from mono to color, the monochrome
   // pixel is first transformed as follows:
   // if  1 (black) it is mapped to the color set by SetTextColor().
   // if  0 (white) is is mapped to the color set by SetBkColor().
   // Only then is the raster operation performed.

   COLORREF clrSaveText = SetTextColor(hdcImage, RGB(255,255,255));
   SetBkColor(hdcImage, RGB(0,0,0));

   bGDI = bGDI && BitBlt(hdcImage, 0, 0, cxSrc, cySrc, hdcMask, 0, 0, SRCAND);

   // Clean up by deselecting any objects, and delete the DC's.

   SelectObject(hdcMask, oldMask);  // clean up
   DeleteDC(hdcMask); hdcMask = NULL;
   SetBkColor  (hdcImage, clrSaveBk); // restore
   SetTextColor(hdcImage, clrSaveText);
   // PREPARE MASK END

   bOK = DrawTransparentHelper( hdcDst, bmpMask,          // The destination DC.
                         xDst,         // Where to draw
                         yDst,
                         cxDst,     // Width & Height
                         cyDst,
                         hdcImage,        // the DC holding the bmp
                         0,
                         0,
                         cxSrc,
                         cySrc);
   bGDI = bGDI && DeleteObject(bmpMask);
   return bOK;
}

/*
Does somebody know how to implement this better using TRANSPARENTROP?
#define TRANSPARENTROP 0xb8074a

EXTERN_C BOOL WINAPI DrawTransparentBitmap(HDC hdc, HDC dcSrc, COLORREF crTransparent, int xDst, int yDst, int cxDst, int cyDst, int cxSrc, int cySrc)
{
   // Now draw the checkmark transparently
   HBRUSH hbrush = CreateSolidBrush(crTransparent);
   HGDIOBJ old = SelectObject(hdc, hbrush);
   COLORREF cBG = SetBkColor(hdc, RGB(255,255,255));
   BOOL bOK = StretchBlt(hdc, xDst, yDst, cxDst, cyDst, dcSrc, 0, 0, cxSrc, cySrc, TRANSPARENTROP);
   SetBkColor(hdc, cBG);
   SelectObject(hdc, old);
   DeleteObject(hbrush);
   return bOK;
}
*/
