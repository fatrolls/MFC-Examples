// CDIBSectionLite.cpp : implementation file
//
// General purpose DIBsection wrapper class for Win9x, NT 4.0
//
// Author      : Chris Maunder (cmaunder@dundas.com)
// Date        : 17 May 1999
//
// Copyright © Dundas Software Ltd. 1999, All Rights Reserved                      
//
// This code may be used in compiled form in any way you desire. This
// file may be redistributed unmodified by any means PROVIDING it is 
// not sold for profit without the authors written consent, and 
// providing that this notice and the authors name is included. If 
// the source code in this file is used in any commercial application 
// then a simple email would be nice.
//
// This file is provided "as is" with no expressed or implied warranty.
// The author accepts no liability for any damage, in any form, caused
// by this code. Use it at your own risk and as with all code expect bugs!
// It's been tested but I'm not perfect.
// 
// Please use and enjoy. Please let me know of any bugs/mods/improvements 
// that you have found/implemented and I will fix/incorporate them into this
// file.
//
// History :  25 May 1999 - First release
//             4 Jun 1999 - Fixed SetBitmap bug


#include "DIBSectionLite.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// Standard colours
PALETTEENTRY CDIBSectionLite::ms_StdColours[] = {
    { 0x00, 0x00, 0x00, 0 },    // First 2 will be palette for monochrome bitmaps
    { 0xFF, 0xFF, 0xFF, 0 },

    { 0x00, 0x00, 0xFF, 0 },    // First 16 will be palette for 16 colour bitmaps
    { 0x00, 0xFF, 0x00, 0 },
    { 0x00, 0xFF, 0xFF, 0 },
    { 0xFF, 0x00, 0x00, 0 },
    { 0xFF, 0x00, 0xFF, 0 },
    { 0xFF, 0xFF, 0x00, 0 },

    { 0x00, 0x00, 0x80, 0 },
    { 0x00, 0x80, 0x00, 0 },
    { 0x00, 0x80, 0x80, 0 },
    { 0x80, 0x00, 0x00, 0 },
    { 0x80, 0x00, 0x80, 0 },
    { 0x80, 0x80, 0x00, 0 },
    { 0x80, 0x80, 0x80, 0 },

    { 0xC0, 0xC0, 0xC0, 0 },
};

/////////////////////////////////////////////////////////////////////////////
// CDIBSectionLite static functions

// --- In  : nBitsPerPixel - bits per pixel
// --- Out : 
// --- Returns :The number of colours for this colour depth
// --- Effect : Returns the number of color table entries given the number
//              of bits per pixel of a bitmap
/*static*/ int CDIBSectionLite::NumColorEntries(int nBitsPerPixel) 
{
    int nColors = 0;

    switch (nBitsPerPixel) 
    {
	    case 1:  nColors = 2;   break;
        case 4:  nColors = 16;  break;
        case 8:  nColors = 256; break;
        case 16:
        case 24:
        case 32: nColors = 0;   break; // 16,24 or 32 bpp have no color table

        default:
           ASSERT(FALSE);
    }

    return nColors;
}

// --- In  : nWidth - image width in pixels
//           nBitsPerPixel - bits per pixel
// --- Out :
// --- Returns : Returns the number of storage bytes needed for each scanline 
//               in the bitmap
// --- Effect : 
/*static*/ int CDIBSectionLite::BytesPerLine(int nWidth, int nBitsPerPixel)
{
    int nBytesPerLine = nWidth * nBitsPerPixel;
    nBytesPerLine = ( (nBytesPerLine + 31) & (~31) ) / 8;

    return nBytesPerLine;
}

// --- In  : palette - reference to a palette object which will be filled
//           nNumColours - number of colour entries to fill
// --- Out :
// --- Returns : TRUE on success, false otherwise
// --- Effect : Creates a halftone color palette independant of screen color depth.
//              palette will be filled with the colors, and nNumColours is the No.
//              of colors to file. If nNumColoursis 0 or > 256, then 256 colors are used.
/*static*/ BOOL CDIBSectionLite::CreateHalftonePalette(CPalette& palette, int nNumColours)
{
    palette.DeleteObject();

    int nNumStandardColours = sizeof(ms_StdColours) / sizeof(ms_StdColours[0]);
    int nIndex = 0;
    int nNumEntries = nNumColours;
    if (nNumEntries <= 0 || nNumEntries > 256)
        nNumEntries = 256;

    PALETTEINFO PalInfo;                   
    PalInfo.palNumEntries = (WORD) nNumEntries;

    // The standard colours (16)
    for (int i = 0; i < nNumStandardColours; i++)
    {
        if (nIndex >= nNumEntries) break;
        memcpy( &(PalInfo.palPalEntry[nIndex]), &(ms_StdColours[i]), sizeof(PALETTEENTRY) );
        nIndex++;
    }

    // A colour cube (6 divisions = 216)
    for (int blue = 0; blue <= 5; blue++)
        for (int green = 0; green <= 5; green++)
            for (int red = 0; red <= 5; red++)
            {
                if (nIndex >= nNumEntries)
                    break;

                PalInfo.palPalEntry[nIndex].peRed   = (BYTE) ((red*255)/5);
                PalInfo.palPalEntry[nIndex].peGreen = (BYTE) ((green*255)/5);
                PalInfo.palPalEntry[nIndex].peBlue  = (BYTE) ((blue*255)/5);
                PalInfo.palPalEntry[nIndex].peFlags = 0;
                nIndex++;
            }

    // A grey scale (24 divisions)
    for (int grey = 0; grey <= 23; grey++)
    {
        if (nIndex >= nNumEntries) 
            break;

        PalInfo.palPalEntry[nIndex].peRed   = (BYTE) (grey*255/23);
        PalInfo.palPalEntry[nIndex].peGreen = (BYTE) (grey*255/23);
        PalInfo.palPalEntry[nIndex].peBlue  = (BYTE) (grey*255/23);
        PalInfo.palPalEntry[nIndex].peFlags = 0;
        nIndex++;
    }

    return palette.CreatePalette((LPLOGPALETTE) PalInfo);
}


/////////////////////////////////////////////////////////////////////////////
// CDIBSectionLite

CDIBSectionLite::CDIBSectionLite()
{
    m_hBitmap = NULL;
    m_bDither = FALSE;
    m_hDrawDib = NULL;

    DeleteObject(); // This will initialise to a known state - ie. empty
}

CDIBSectionLite::~CDIBSectionLite()
{
    DeleteObject();
}

// --- In  :
// --- Out :
// --- Returns :
// --- Effect : Resets the object to an empty state, and frees all memory used.
void CDIBSectionLite::DeleteObject()
{
    if (m_hBitmap)
        ::DeleteObject(m_hBitmap);
    m_hBitmap = NULL;
    m_ppvBits = NULL;

    memset(&m_DIBinfo, 0, sizeof(m_DIBinfo));

    if (m_hDrawDib)
        DrawDibClose(m_hDrawDib);
    m_hDrawDib = NULL;

    m_iColorDataType = DIB_RGB_COLORS;
    m_iColorTableSize = 0;
}

/////////////////////////////////////////////////////////////////////////////
// CDIBSectionLite diagnostics

#ifdef _DEBUG
void CDIBSectionLite::AssertValid() const
{
    ASSERT(m_hBitmap);

    DIBSECTION ds;
    DWORD dwSize = GetObject( m_hBitmap, sizeof(DIBSECTION), &ds );
    ASSERT(dwSize == sizeof(DIBSECTION));

    ASSERT(0 <= m_iColorTableSize && m_iColorTableSize <= 256);

	CObject::AssertValid();
}

void CDIBSectionLite::Dump(CDumpContext& dc) const
{
	CObject::Dump(dc);
}

#endif //_DEBUG

// --- In  : bDither - whether or not dithering should be enabled
// --- Out :
// --- Returns : TRUE on success
// --- Effect : Turns dithering on by using the DrawDib functions instead of 
//              the GDI functions
BOOL CDIBSectionLite::SetDither(BOOL bDither)
{
    BOOL bResult = TRUE;

    // Check for a no-change op.
    if ( (m_bDither == bDither) &&
         ((m_hDrawDib && bDither) || (!m_hDrawDib && !bDither)) )
        return bResult;

    if (m_hDrawDib != NULL)
    {
        DrawDibClose(m_hDrawDib);
        m_hDrawDib = NULL;
    }

    if (bDither)
    {
        if ( (m_hDrawDib = DrawDibOpen()) == NULL )
            bResult = FALSE;
    }

    m_bDither = (m_hDrawDib != NULL);

    return bResult;
}

// --- In  : 
// --- Out :
// --- Returns : TRUE if dithering is used
// --- Effect : Returns whether or not the DrawDib functions (and hence dithering)
//              is being used.
BOOL CDIBSectionLite::GetDither()
{
    return (m_bDither && (m_hDrawDib != NULL));
}

/////////////////////////////////////////////////////////////////////////////
// CDIBSectionLite operations

// --- In  : pDC - Pointer to a device context
//           ptDest - point at which the topleft corner of the image is drawn
//           bForceBackground - Specifies whether the palette is forced to be 
//                              a background palette
// --- Out :
// --- Returns : TRUE on success
// --- Effect : Draws the image 1:1 on the device context
BOOL CDIBSectionLite::Draw(CDC* pDC, CPoint ptDest, BOOL bForceBackground /*=FALSE*/ ) 
{ 
    if (!m_hBitmap)
        return FALSE;

    CSize size = GetSize();
    CPoint SrcOrigin = CPoint(0,0);

    BOOL bResult = FALSE;

    if (GetDither() && GetBitCount() >= 8)
    {
        DrawDibSetPalette( m_hDrawDib, (HPALETTE)m_Palette);
        DrawDibRealize( m_hDrawDib,  pDC->GetSafeHdc(),  bForceBackground);
        
        bResult = DrawDibDraw(m_hDrawDib, pDC->GetSafeHdc(), 
                              ptDest.x, ptDest.y, size.cx, size.cy, 
                              GetBitmapInfoHeader(), GetDIBits(), 
                              SrcOrigin.x, SrcOrigin.y, size.cx, size.cy, 
                              0/*DDF_HALFTONE*/);
    }
    else
    {
        CPalette* pOldPalette = NULL;
        if (m_Palette.m_hObject && UsesPalette(pDC))
        {
            pOldPalette = pDC->SelectPalette(&m_Palette, bForceBackground);
            pDC->RealizePalette();
        }

        bResult = SetDIBitsToDevice(pDC->GetSafeHdc(), 
                                    ptDest.x, ptDest.y, 
                                    size.cx, size.cy,
                                    SrcOrigin.x, SrcOrigin.y,
                                    SrcOrigin.y, size.cy - SrcOrigin.y, 
                                    GetDIBits(), GetBitmapInfo(), 
                                    m_iColorDataType); 

        if (pOldPalette)
            pDC->SelectPalette(pOldPalette, FALSE);
    }
    
    return bResult;
}

// --- In  : pDC - Pointer to a device context
//           ptDest - point at which the topleft corner of the image is drawn
//           size - size to stretch the image
//           bForceBackground - Specifies whether the palette is forced to be 
//                              a background palette
// --- Out :
// --- Returns : TRUE on success
// --- Effect : Stretch draws the image to the desired size on the device context
BOOL CDIBSectionLite::Stretch(CDC* pDC, CPoint ptDest, CSize size, 
                              BOOL bForceBackground /*=FALSE*/) 
{ 
    if (!m_hBitmap)
        return FALSE;

    CSize imagesize = GetSize();
    CPoint SrcOrigin = CPoint(0,0);

    BOOL bResult = FALSE;

    if (GetDither() && GetBitCount() >= 8)
    {
        DrawDibSetPalette( m_hDrawDib, (HPALETTE)m_Palette);
        DrawDibRealize( m_hDrawDib,  pDC->GetSafeHdc(),  bForceBackground);
        
        bResult = DrawDibDraw(m_hDrawDib, pDC->GetSafeHdc(), 
                              ptDest.x, ptDest.y, size.cx, size.cy, 
                              GetBitmapInfoHeader(), GetDIBits(), 
                              SrcOrigin.x, SrcOrigin.y, imagesize.cx, imagesize.cy, 
                              0/*DDF_HALFTONE*/);
    }
    else
    {
        CPalette* pOldPalette = NULL;
        if (m_Palette.m_hObject && UsesPalette(pDC))
        {
            pOldPalette = pDC->SelectPalette(&m_Palette, bForceBackground);
            pDC->RealizePalette();
        }

        pDC->SetStretchBltMode(COLORONCOLOR);

        bResult = StretchDIBits(pDC->GetSafeHdc(), 
                                ptDest.x, ptDest.y, 
                                size.cx, size.cy,
                                SrcOrigin.x, SrcOrigin.y,
                                imagesize.cx, imagesize.cy, 
                                GetDIBits(), GetBitmapInfo(), 
                                m_iColorDataType, SRCCOPY); 

        if (pOldPalette)
            pDC->SelectPalette(pOldPalette, FALSE);
    }

    return bResult;
}


//////////////////////////////////////////////////////////////////////////////
// Setting the bitmap...


// --- In  : nIDResource - resource ID
// --- Out :
// --- Returns : Returns TRUE on success, FALSE otherwise
// --- Effect : Initialises the bitmap from a resource. If failure, then object is
//              initialised back to an empty bitmap.
BOOL CDIBSectionLite::SetBitmap(UINT nIDResource)
{   
    return SetBitmap(MAKEINTRESOURCE(nIDResource));
}

// --- In  : lpszResourceName - resource name
// --- Out :
// --- Returns : Returns TRUE on success, FALSE otherwise
// --- Effect : Initialises the bitmap from a resource. If failure, then object is
//              initialised back to an empty bitmap.
BOOL CDIBSectionLite::SetBitmap(LPCTSTR lpszResourceName)
{
    HBITMAP hBmp = (HBITMAP)::LoadImage(AfxGetResourceHandle(), 
                                        lpszResourceName,
                                        IMAGE_BITMAP, 
                                        0,0, 
                                        LR_CREATEDIBSECTION);

    if (!hBmp) return FALSE;

    BOOL bResult = SetBitmap(hBmp);
    ::DeleteObject(hBmp);
    return bResult;
}

// --- In  : lpBitmapInfo - pointer to a BITMAPINFO structure
//           lpBits - pointer to image bits
// --- Out :
// --- Returns : Returns TRUE on success, FALSE otherwise
// --- Effect : Initialises the bitmap using the information in lpBitmapInfo to determine
//              the dimensions and colours, and the then sets the bits from the bits in
//              lpBits. If failure, then object is initialised back to an empty bitmap.
BOOL CDIBSectionLite::SetBitmap(LPBITMAPINFO lpBitmapInfo, LPVOID lpBits)
{
    DeleteObject();

    if (!lpBitmapInfo || !lpBits)
        return FALSE;

    HDC hDC = NULL;
    try {
        BITMAPINFOHEADER& bmih = lpBitmapInfo->bmiHeader;

        // Compute the number of colours in the colour table
        m_iColorTableSize = NumColorEntries(bmih.biBitCount);

        DWORD dwBitmapInfoSize = sizeof(BITMAPINFO) + m_iColorTableSize*sizeof(RGBQUAD);

        // Copy over BITMAPINFO contents
        memcpy(&m_DIBinfo, lpBitmapInfo, dwBitmapInfoSize);

        // Should now have all the info we need to create the sucker.
        //TRACE(_T("Width %d, Height %d, Bits/pixel %d, Image Size %d\n"),
        //      bmih.biWidth, bmih.biHeight, bmih.biBitCount, bmih.biSizeImage);

        // Create a DC which will be used to get DIB, then create DIBsection
        hDC = ::GetDC(NULL);
        if (!hDC) 
        {
            TRACE0("Unable to get DC\n");
            AfxThrowResourceException();
        }

        m_hBitmap = CreateDIBSection(hDC, (const BITMAPINFO*) m_DIBinfo,
                                     m_iColorDataType, &m_ppvBits, NULL, 0);
        ::ReleaseDC(NULL, hDC);
        if (!m_hBitmap)
        {
            TRACE0("CreateDIBSection failed\n");
            AfxThrowResourceException();
        }

        DWORD dwImageSize = m_DIBinfo.bmiHeader.biSizeImage;
        if (dwImageSize == 0)
        {
            int nBytesPerLine = BytesPerLine(lpBitmapInfo->bmiHeader.biWidth, 
                                             lpBitmapInfo->bmiHeader.biBitCount);
            dwImageSize = nBytesPerLine * lpBitmapInfo->bmiHeader.biHeight;
        }

        // Flush the GDI batch queue 
        GdiFlush();

        memcpy(m_ppvBits, lpBits, dwImageSize);

        if (!CreatePalette())
        {
            TRACE0("Unable to create palette\n");
            AfxThrowResourceException();
        }
    }
    catch (CException *e)
    {
        e->Delete();
        _ShowLastError();
        if (hDC) 
            ::ReleaseDC(NULL, hDC);
        DeleteObject();
        return FALSE;
    }

    return TRUE;
}

// --- In  : hBitmap - handle to image
//           pPalette - optional palette to use when setting image
// --- Out :
// --- Returns : Returns TRUE on success, FALSE otherwise
// --- Effect : Initialises the bitmap from the HBITMAP supplied. If failure, then
//              object is initialised back to an empty bitmap.
BOOL CDIBSectionLite::SetBitmap(HBITMAP hBitmap, CPalette* pPalette /*= NULL*/)
{
    DeleteObject();

    if (!hBitmap)
        return FALSE;

    // Get dimensions of bitmap
    BITMAP bm;
    if (!::GetObject(hBitmap, sizeof(bm),(LPVOID)&bm))
        return FALSE;
    bm.bmHeight = abs(bm.bmHeight);
   
    CWindowDC dc(NULL);
    CPalette* pOldPalette = NULL;

    try {
        m_iColorTableSize = NumColorEntries(bm.bmBitsPixel);

        // Initialize the BITMAPINFOHEADER in m_DIBinfo
        BITMAPINFOHEADER& bih = m_DIBinfo.bmiHeader;
        bih.biSize          = sizeof(BITMAPINFOHEADER);
        bih.biWidth         = bm.bmWidth;
        bih.biHeight        = bm.bmHeight;
        bih.biPlanes        = 1;                // Must always be 1 according to docs
        bih.biBitCount      = bm.bmBitsPixel;
        bih.biCompression   = BI_RGB;
        bih.biSizeImage     = BytesPerLine(bm.bmWidth, bm.bmBitsPixel) * bm.bmHeight;
        bih.biXPelsPerMeter = 0;
        bih.biYPelsPerMeter = 0;
        bih.biClrUsed       = 0;
        bih.biClrImportant  = 0;

        // calls GetDIBits with NULL bits pointer to fill in the BITMAPINFOHEADER data
        if (!::GetDIBits(dc.m_hDC, hBitmap, 0, bm.bmHeight, NULL, m_DIBinfo, m_iColorDataType))
        {
            TRACE0("Unable to GetDIBits\n");
            AfxThrowResourceException();
        }

        // If the driver did not fill in the biSizeImage field, then compute it
        // Each scan line of the image is aligned on a DWORD (32bit) boundary
        if (bih.biSizeImage == 0)
            bih.biSizeImage = BytesPerLine(bih.biWidth, bih.biBitCount) * bih.biHeight;

        if (pPalette)
            SetPalette(pPalette);
        else
            CreateHalftonePalette(m_Palette, m_iColorTableSize);

        if (m_Palette.GetSafeHandle())
        {
            pOldPalette = dc.SelectPalette(&m_Palette, FALSE);
            dc.RealizePalette();
        }

        // Create it!
        m_hBitmap = CreateDIBSection(dc.m_hDC, 
                                     (const BITMAPINFO*) m_DIBinfo,
                                     m_iColorDataType,
                                     &m_ppvBits, 
                                     NULL, 0);
        if (pOldPalette)
            dc.SelectPalette(pOldPalette, FALSE);
        pOldPalette = NULL; 

        if (!m_hBitmap)
        {
            TRACE0("Unable to CreateDIBSection\n");
            AfxThrowResourceException();
        }
    
        // Need to copy the supplied bitmap onto the newly created DIBsection
        CDC memDC, CopyDC;
        if (!CopyDC.CreateCompatibleDC(&dc) || !memDC.CreateCompatibleDC(&dc)) 
        {
            TRACE0("Unable to create compatible DC's\n");
            AfxThrowResourceException();
        }

        if (m_Palette.GetSafeHandle())
        {
            memDC.SelectPalette(&m_Palette, FALSE);  memDC.RealizePalette();
            CopyDC.SelectPalette(&m_Palette, FALSE); CopyDC.RealizePalette();
        }

        GdiFlush();

        HBITMAP hOldMemBitmap  = (HBITMAP) SelectObject(memDC.m_hDC,  hBitmap);
        HBITMAP hOldCopyBitmap = (HBITMAP) SelectObject(CopyDC.m_hDC, m_hBitmap);

        CopyDC.BitBlt(0,0, bm.bmWidth, bm.bmHeight, &memDC, 0,0, SRCCOPY);

        SelectObject(memDC.m_hDC, hOldMemBitmap);
        SelectObject(CopyDC.m_hDC, hOldCopyBitmap);

        if (m_Palette.GetSafeHandle())
        {
            memDC.SelectStockObject(DEFAULT_PALETTE);
            CopyDC.SelectStockObject(DEFAULT_PALETTE);
        }
    }
    catch (CException *e)
    {
        e->Delete();
        _ShowLastError();
        if (pOldPalette)
            dc.SelectPalette(pOldPalette, FALSE);
        DeleteObject();
        return FALSE;
    }

    return TRUE;
}


//////////////////////////////////////////////////////////////////////////////
// Persistance...


// --- In  : lpszFileName - image filename
// --- Out :
// --- Returns : Returns TRUE on success, FALSE otherwise
// --- Effect : Loads the bitmap from a bitmap file with the name lpszFileName. 
//              If failure, then object is initialised back to an empty bitmap.
BOOL CDIBSectionLite::Load(LPCTSTR lpszFileName)
{
    CFile file;
    if (!file.Open(lpszFileName, CFile::modeRead))
        return FALSE;

    // Get the current file position.  
    DWORD dwFileStart = file.GetPosition();

    // The first part of the file contains the file header.
	// This will tell us if it is a bitmap, how big the header is, and how big 
    // the file is. The header size in the file header includes the color table.
	BITMAPFILEHEADER BmpFileHdr;
    int nBytes;
    nBytes = file.Read(&BmpFileHdr, sizeof(BmpFileHdr));
    if (nBytes != sizeof(BmpFileHdr)) 
    {
        TRACE0("Failed to read file header\n");
        return FALSE;
    }

    // Check that we have the magic 'BM' at the start.
    if (BmpFileHdr.bfType != DS_BITMAP_FILEMARKER)
    {
        TRACE0("Not a bitmap file\n");
        return FALSE;
    }

    // Read the header (assuming it's a DIB). 
	DIBINFO	BmpInfo;
    nBytes = file.Read(&BmpInfo, sizeof(BITMAPINFOHEADER)); 
    if (nBytes != sizeof(BITMAPINFOHEADER)) 
    {
        TRACE0("Failed to read BITMAPINFOHEADER\n");
        return FALSE;
    }

    // Check that we have a real Windows DIB file.
    if (BmpInfo.bmiHeader.biSize != sizeof(BITMAPINFOHEADER))
    {
        TRACE0(" File is not a Windows DIB\n");
        return FALSE;
    }

    // See how big the color table is in the file (if there is one).  
    int nColors = NumColorEntries(BmpInfo.bmiHeader.biBitCount);
	if (nColors > 0) 
    {
        // Read the color table from the file.
        int nColorTableSize = nColors * sizeof(RGBQUAD);
		nBytes = file.Read(BmpInfo.ColorTable(), nColorTableSize);
		if (nBytes != nColorTableSize) 
        {
			TRACE0("Failed to read color table\n");
			return FALSE;
        }
	}

	// So how big the bitmap surface is.
    int nBitsSize = BmpFileHdr.bfSize - BmpFileHdr.bfOffBits;

    // Allocate the memory for the bits and read the bits from the file.
    BYTE* pBits = (BYTE*) malloc(nBitsSize);
    if (!pBits) 
    {
        TRACE0("Out of memory for DIB bits\n");
        return FALSE;
    }

    // Seek to the bits in the file.
    file.Seek(dwFileStart + BmpFileHdr.bfOffBits, CFile::begin);

    // read the bits
    nBytes = file.Read(pBits, nBitsSize);
    if (nBytes != nBitsSize) 
    {
        TRACE0("Failed to read bits\n");
        free(pBits);
		return FALSE;
    }

	// Everything went OK.
	BmpInfo.bmiHeader.biSizeImage = nBitsSize;

    if (!SetBitmap((LPBITMAPINFO) BmpInfo, pBits))
    {
        TRACE0("Failed to set bitmap info\n");
        free(pBits);
		return FALSE;
    }

    free(pBits);

    return TRUE;
}

// --- In  : lpszFileName - image filename
// --- Out :
// --- Returns : Returns TRUE on success, FALSE otherwise
// --- Effect : Saves the image to file.
BOOL CDIBSectionLite::Save(LPCTSTR lpszFileName)
{
    BITMAPFILEHEADER   hdr;
    LPBITMAPINFOHEADER lpbi = GetBitmapInfoHeader();

    if (!lpbi || !lpszFileName)
        return FALSE;

    CFile file;
    if (!file.Open(lpszFileName, CFile::modeWrite|CFile::modeCreate))
        return FALSE;

    DWORD dwBitmapInfoSize = sizeof(BITMAPINFO) + m_iColorTableSize*sizeof(RGBQUAD);
    DWORD dwFileHeaderSize = dwBitmapInfoSize + sizeof(hdr);

    // Fill in the fields of the file header 
    hdr.bfType       = DS_BITMAP_FILEMARKER;
    hdr.bfSize       = dwFileHeaderSize + lpbi->biSizeImage;
    hdr.bfReserved1  = 0;
    hdr.bfReserved2  = 0;
    hdr.bfOffBits    = dwFileHeaderSize;

    // Write the file header 
    file.Write(&hdr, sizeof(hdr));

    // Write the DIB header
    file.Write(lpbi, dwBitmapInfoSize);
    
    // Write DIB bits
    file.Write(GetDIBits(), lpbi->biSizeImage);

    return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CDIBSectionLite palette stuff


// --- In  :
// --- Out :
// --- Returns : TRUE on success
// --- Effect : Creates the palette from the DIBSection's color table. Assumes 
//              m_iColorTableSize has been set and the DIBsection m_hBitmap created
BOOL CDIBSectionLite::CreatePalette()
{
    m_Palette.DeleteObject();

    if (!m_hBitmap)
        return FALSE;

    // Create a 256 color halftone palette if there is no color table in the DIBSection
    if (m_iColorTableSize == 0)
        return CreateHalftonePalette(m_Palette, 256);


    HDC hDC = ::GetDC(NULL);
    if (!hDC)
        return FALSE;

    // Get space for the colour entries
    RGBQUAD *pRGB = new RGBQUAD[m_iColorTableSize];
    if (!pRGB)
    {
        ReleaseDC(NULL, hDC);
        return CreateHalftonePalette(m_Palette, m_iColorTableSize);
    }

    // Create a memory DC compatible with the current DC
    CDC MemDC;
    MemDC.CreateCompatibleDC(CDC::FromHandle(hDC));
    if (!MemDC.GetSafeHdc())
    {
        delete [] pRGB;
        ::ReleaseDC(NULL, hDC);
        return CreateHalftonePalette(m_Palette, m_iColorTableSize);
    }
    ::ReleaseDC(NULL, hDC);
    
    HBITMAP hOldBitmap = (HBITMAP) ::SelectObject(MemDC.GetSafeHdc(), m_hBitmap);
    if (!hOldBitmap)
    {
        delete [] pRGB;
        return CreateHalftonePalette(m_Palette, m_iColorTableSize);
    }

    // Get the colours used. 
    int nColours = ::GetDIBColorTable(MemDC.GetSafeHdc(), 0, m_iColorTableSize, pRGB);

    // Clean up
    ::SelectObject(MemDC.GetSafeHdc(), hOldBitmap);

    if (!nColours)   // No colours retrieved => the bitmap in the DC is not a DIB section
    {
        delete [] pRGB;
        return CreateHalftonePalette(m_Palette, m_iColorTableSize);
    }   
    
    // Create and fill a LOGPALETTE structure with the colours used.
    PALETTEINFO PaletteInfo;
    PaletteInfo.palNumEntries = (WORD) m_iColorTableSize;
                        
    for (int i = 0; i < nColours; i++)
    {
        PaletteInfo.palPalEntry[i].peRed   = pRGB[i].rgbRed;
        PaletteInfo.palPalEntry[i].peGreen = pRGB[i].rgbGreen;
        PaletteInfo.palPalEntry[i].peBlue  = pRGB[i].rgbBlue;
        PaletteInfo.palPalEntry[i].peFlags = 0;
    }
    for (; i < (int) m_iColorTableSize; i++)
    {
        PaletteInfo.palPalEntry[i].peRed   = 0;
        PaletteInfo.palPalEntry[i].peGreen = 0;
        PaletteInfo.palPalEntry[i].peBlue  = 0;
        PaletteInfo.palPalEntry[i].peFlags = 0;
    }

    delete [] pRGB;

    // Create Palette!
    return m_Palette.CreatePalette(&PaletteInfo);
}

// --- In  : pPalette - new palette to use
// --- Out :
// --- Returns : TRUE on success
// --- Effect : Sets the current palette used by the image from the supplied CPalette,
//              and sets the color table in the DIBSection
BOOL CDIBSectionLite::SetPalette(CPalette* pPalette)
{
    m_Palette.DeleteObject();

    if (!pPalette)
        return FALSE;

    UINT nColours = pPalette->GetEntryCount();
    if (nColours <= 0 || nColours > 256)
        return FALSE;

    // Get palette entries
    PALETTEINFO pi;
    pi.palNumEntries = (WORD) pPalette->GetPaletteEntries(0, nColours, (LPPALETTEENTRY) pi);
                          
    // TODO: If pi.palNumEntries < m_iColorTableSize, then fill in blanks with 0's

    return SetLogPalette(&pi);
}

// --- In  : pLogPalette - new palette to use
// --- Out :
// --- Returns : TRUE on success
// --- Effect : Sets the current palette used by the image from the supplied LOGPALETTE
BOOL CDIBSectionLite::SetLogPalette(LOGPALETTE* pLogPalette)
{
    ASSERT(pLogPalette->palVersion == (WORD) 0x300);
    UINT nColours = pLogPalette->palNumEntries;
    if (nColours <= 0 || nColours > 256)
    {
        CreatePalette();
        return FALSE;
    }

    // Create new palette
    m_Palette.DeleteObject();
    if (!m_Palette.CreatePalette(pLogPalette))
    {
        CreatePalette();
        return FALSE;
    }

    if (m_iColorTableSize == 0)
        return TRUE;

    // Set the DIB colours
    RGBQUAD RGBquads[256]; 
    for (UINT i = 0; i < nColours; i++)
    {
        RGBquads[i].rgbRed   = pLogPalette->palPalEntry[i].peRed;
        RGBquads[i].rgbGreen = pLogPalette->palPalEntry[i].peGreen;
        RGBquads[i].rgbBlue  = pLogPalette->palPalEntry[i].peBlue;
        RGBquads[i].rgbReserved = 0;
    }
    
    return FillDIBColorTable(nColours, RGBquads);
}

void CDIBSectionLite::CreateGradientBmp	(COLORREF clrBack,
								 COLORREF clrStart,
								 COLORREF clrEnd,
								 int iWidth,
								 int iHeight,
								 int iDirection)
{
	RECT rectFill;			   // Rectangle for filling band
	float fStep;              // How wide is each band?
	CBrush brush;			// Brush to fill in the bar	

	CBitmap ourNewBitmap;
	CWindowDC dc(NULL);
	CDC tempDC;
	CDC tempDC1;

	tempDC.CreateCompatibleDC(&dc);
	tempDC1.CreateCompatibleDC(&dc);

	ourNewBitmap.CreateDiscardableBitmap(&dc,iWidth,iHeight);
	//ourNewBitmap.CreateBitmap(iWidth,iHeight,3,32,NULL);

	CBitmap* pOldBitmap = tempDC.SelectObject(&ourNewBitmap);
	// First find out the largest color distance between the start and end colors.  This distance
	// will determine how many steps we use to carve up the client region and the size of each
	// gradient rect.
	int r, g, b;							// First distance, then starting value
	float rStep, gStep, bStep;		// Step size for each color

	// Get the color differences
	r = (GetRValue(clrEnd) - GetRValue(clrStart));
	g = (GetGValue(clrEnd) - GetGValue(clrStart));
	b =  (GetBValue(clrEnd) - GetBValue(clrStart));

	// Make the number of steps equal to the greatest distance
	int nSteps = max(abs(r), max(abs(g), abs(b)));

	// Determine how large each band should be in order to cover the
	// client with nSteps bands (one for every color intensity level)
	if(iDirection == BMGRADIENT_DIRECTION_HORZ)
		fStep = (float)iWidth / (float)nSteps;
	else if(iDirection == BMGRADIENT_DIRECTION_VERT)
		fStep = (float)iHeight / (float)nSteps;

	// Calculate the step size for each color
	rStep = r/(float)nSteps;
	gStep = g/(float)nSteps;
	bStep = b/(float)nSteps;

	// Reset the colors to the starting position
	r = GetRValue(clrStart);
	g = GetGValue(clrStart);
	b = GetBValue(clrStart);

	// Start filling bands

	for (int iOnBand = 0; iOnBand < nSteps; iOnBand++) 
	{
		// Set the rect we will fill with the gradient
		if(iDirection == BMGRADIENT_DIRECTION_HORZ)
		{
			::SetRect(&rectFill,
						(int)(iOnBand * fStep),       // Upper left X
						 0,									 // Upper left Y
						(int)((iOnBand+1) * fStep),          // Lower right X
						iHeight+1);			// Lower right Y
		}
		else if(iDirection == BMGRADIENT_DIRECTION_VERT)
		{
			::SetRect(&rectFill,
						0,       // Upper left X
						 (iOnBand * fStep),					 // Upper left Y
						iWidth,          // Lower right X
						(int)((iOnBand+1) * fStep));			// Lower right Y
		}
	
		// CDC::FillSolidRect is faster, but it does not handle 8-bit color depth
		VERIFY(brush.CreateSolidBrush(RGB(r+rStep*iOnBand, g + gStep*iOnBand, b + bStep *iOnBand)));
		tempDC.FillRect(&rectFill,&brush);
		VERIFY(brush.DeleteObject());


		// If we are past the maximum for the current position we need to get out of the loop.
		// Before we leave, we repaint the remainder of the client area with the background color.
		if(iDirection == BMGRADIENT_DIRECTION_HORZ)
		{
			if (rectFill.right > iWidth)
			{
				::SetRect(&rectFill, rectFill.right, 0, iWidth, iHeight);
				VERIFY(brush.CreateSolidBrush(clrBack));
				tempDC.FillRect(&rectFill, &brush);
				VERIFY(brush.DeleteObject());
				return;
			}
		}
		else if(iDirection == BMGRADIENT_DIRECTION_VERT)
		{
			if (rectFill.right > iHeight)
			{
				::SetRect(&rectFill, rectFill.right, 0, iWidth, iHeight);
				VERIFY(brush.CreateSolidBrush(clrBack));
				tempDC.FillRect(&rectFill, &brush);
				VERIFY(brush.DeleteObject());
				return;
			}
		}
		
	}


	// Create a 32 bit bitmap
	m_ppvBits = new DWORD[iWidth*iHeight];
	BITMAPINFO bih;

    // create DIB Section
    bih.bmiHeader.biSize          = sizeof(BITMAPINFOHEADER);
    bih.bmiHeader.biWidth         = iWidth; 
    bih.bmiHeader.biHeight        = iHeight; 
    bih.bmiHeader.biPlanes        = 1; 
    bih.bmiHeader.biBitCount      = 32; 
    bih.bmiHeader.biCompression   = BI_RGB; 
    bih.bmiHeader.biSizeImage     = 0; 
    bih.bmiHeader.biXPelsPerMeter = 0; 
    bih.bmiHeader.biYPelsPerMeter = 0; 
    bih.bmiHeader.biClrUsed       = 0; 
    bih.bmiHeader.biClrImportant  = 0; 
	
	
	SetBitmap(&bih,m_ppvBits);

	DWORD* pLine = (DWORD*)GetDIBits();


	// Copy the bits into our 32 bit dib..
	for(int i=0;i<iHeight;i++)
	{	
		for(int j=0;j<iWidth;j++)
		{
			pLine[(i*iWidth)+j] = FixColorRef(tempDC.GetPixel(j,i));
		}
	}

	// Set the dc back to normal
	tempDC.SelectObject(pOldBitmap);


	
}
void CDIBSectionLite::Create32BitFromPicture (CPictureHolder* pPicture,
											 int iWidth,
											 int iHeight)
{
	CBitmap ourNewSizedBMP;
	CWindowDC dc(NULL);
	CDC tempDC;
	CRect rcRender;

	tempDC.CreateCompatibleDC(&dc);

	ourNewSizedBMP.CreateDiscardableBitmap(&dc,iWidth,iHeight);

	// Now we need to select it into our temp DC so we can render the picture onto it
	CBitmap* pOldBitmap = tempDC.SelectObject(&ourNewSizedBMP);

	// Render the picture onto our bmp
	rcRender.SetRect(0,0,iWidth,iHeight);
	pPicture->Render(&tempDC,rcRender,rcRender);

	// Create a 32 bit bitmap
	m_ppvBits = new DWORD[iWidth*iHeight];
	BITMAPINFO bih;

    // create DIB Section
    bih.bmiHeader.biSize          = sizeof(BITMAPINFOHEADER);
    bih.bmiHeader.biWidth         = iWidth; 
    bih.bmiHeader.biHeight        = iHeight; 
    bih.bmiHeader.biPlanes        = 1; 
    bih.bmiHeader.biBitCount      = 32; 
    bih.bmiHeader.biCompression   = BI_RGB; 
    bih.bmiHeader.biSizeImage     = 0; 
    bih.bmiHeader.biXPelsPerMeter = 0; 
    bih.bmiHeader.biYPelsPerMeter = 0; 
    bih.bmiHeader.biClrUsed       = 0; 
    bih.bmiHeader.biClrImportant  = 0; 
	
	
	SetBitmap(&bih,m_ppvBits);

	DWORD* pLine = (DWORD*)GetDIBits();


	// Copy the bits into our 32 bit dib..
	for(int i=0;i<iHeight;i++)
	{	
		for(int j=0;j<iWidth;j++)
		{
			pLine[(i*iWidth)+j] = FixColorRef(tempDC.GetPixel(j,i));
		}
	}

	// Set the dc back to normal
	tempDC.SelectObject(pOldBitmap);

}
inline COLORREF CDIBSectionLite::FixColorRef(COLORREF clr)
{
	int r = GetRValue(clr);
	int g = GetGValue(clr);
	int b =  GetBValue(clr);

	return RGB(b,g,r);
}

// --- In  : nNumColours - number of colours to set
//           pRGB - colours to fill
// --- Out :
// --- Returns : Returns TRUE on success
// --- Effect : Sets the colours used by the image. Only works if # colours <= 256
BOOL CDIBSectionLite::FillDIBColorTable(UINT nNumColours, RGBQUAD *pRGB)
{
    if (!m_hBitmap || !pRGB || !nNumColours || !m_iColorTableSize
        || nNumColours > 256)
        return FALSE;

    // Create a memory DC compatible with the screen
    HDC hDC = ::GetDC(NULL);
    if (!hDC) return FALSE;

    CDC MemDC;
    MemDC.CreateCompatibleDC(CDC::FromHandle(hDC));
    ::ReleaseDC(NULL, hDC);
    if (!MemDC.GetSafeHdc())
        return FALSE;

    HBITMAP hOldBitmap = (HBITMAP) ::SelectObject(MemDC.GetSafeHdc(), m_hBitmap);

    // Set the bitmap colours.
    int nColours = ::SetDIBColorTable(MemDC.GetSafeHdc(), 0, nNumColours, pRGB);

    // Clean up
    if (hOldBitmap)
        ::SelectObject(MemDC.GetSafeHdc(), hOldBitmap);
    MemDC.DeleteDC();

    return (nColours > 0);
}

#ifdef _DEBUG
// Makes trace windows a little bit more informative...
void CDIBSectionLite::_ShowLastError()
{
    LPVOID lpMsgBuf;
    FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,    
                  NULL, GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), 
                  (LPTSTR) &lpMsgBuf, 0, NULL);
    TRACE1("Last error: %s\n", lpMsgBuf);
    LocalFree(lpMsgBuf);
}
#else
void CDIBSectionLite::_ShowLastError() {}
#endif
