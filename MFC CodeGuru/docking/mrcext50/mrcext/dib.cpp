// MRCEXT: Micro Focus Extension DLL for MFC 2.1+
// Copyright (C)1994-5	Micro Focus Inc, 2465 East Bayshore Rd, Palo Alto, CA 94303.
// 
//  This program is free software; you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation. In addition, you may also charge for any
//  application	using MRCEXT, and are under no obligation to supply source
//  code. You must accredit Micro Focus Inc in the "About Box", or banner
//  of your application. 
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should also have received a copy of the GNU General Public License with this
//  software, also indicating additional rights you have when using MRCEXT.  
//
//
// dib.cpp : implementation file
// $Revision:   1.2  $
// $Author:   SJR  $
// $Date:   Sep 22 1997 15:51:34  $
// This code implements a CMRCDib and CMRCDibPal class, suitable for loading/drawing
// 256-color bitmaps. Most of the code is borrowed from MSDN9, Win32 Animation 
// examples. It's probably a sledgehammer to crack a nut in terms of getting Sooty
// to have a 256-color bitmap, but there isn't that much code here, and anyway it'll
// probably come in useful elsewhere

#include "mrcstafx.h"
#include "mrcext.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMRCDib

IMPLEMENT_DYNAMIC(CMRCDib, CObject)

// Create a small DIB here so m_pBMI and m_pBits are always valid
CMRCDib::CMRCDib()
{
    m_pBMI = NULL;
    m_pBits = NULL;
	m_cLoadedFromResource = 0;
    Create(16, 16);
}


CMRCDib::~CMRCDib()
{
    // free the memory
	DeleteContents();
}

/////////////////////////////////////////////////////////////////////////////
// Private functions
//-------------------------------------------------------------------------
void CMRCDib::DeleteContents()
//-------------------------------------------------------------------------
{
// Separate the deallocation of memory, since resource-loaded Dib's don't need to
// free their memory.
    if (m_cLoadedFromResource == 0)
    {
		delete m_pBMI;
		delete m_pBits;
	}
   	m_pBMI = NULL;
	m_pBits = NULL;
	m_cLoadedFromResource = 0;
}



//-------------------------------------------------------------------------
static BOOL IsWinDIB(BITMAPINFOHEADER *pBIH)
//-------------------------------------------------------------------------
{
    ASSERT(pBIH != NULL);
    if (((BITMAPCOREHEADER *)pBIH)->bcSize == sizeof(BITMAPCOREHEADER)) 
        return FALSE;
    return TRUE;
}


//-------------------------------------------------------------------------
static int NumDIBColorEntries(BITMAPINFO *pBmpInfo) 
//-------------------------------------------------------------------------
{
    BITMAPINFOHEADER *pBIH;
    BITMAPCOREHEADER *pBCH;
    int iColors, iBitCount;

    ASSERT(pBmpInfo);

    pBIH = &(pBmpInfo->bmiHeader);
    pBCH = (BITMAPCOREHEADER *) pBIH;

    // start off by assuming the color table size from
    // the bit per pixel field
    if (IsWinDIB(pBIH))
        iBitCount = pBIH->biBitCount;
    else 
        iBitCount = pBCH->bcBitCount;

    switch (iBitCount)
    {
    case 1:
        iColors = 2;
        break;
    case 4:
        iColors = 16;
        break;
    case 8:
        iColors = 256;
        break;
    default:
        iColors = 0;
        break;
    }

    // If this is a Windows DIB, then the color table length
    // is determined by the biClrUsed field if it is non-zero
    if (IsWinDIB(pBIH) && (pBIH->biClrUsed != 0)) 
        iColors = pBIH->biClrUsed;
    return iColors;
}


/////////////////////////////////////////////////////////////////////////////
// CMRCDib commands

//-------------------------------------------------------------------------
BOOL CMRCDib::Create(int iWidth, int iHeight)
// creates a simple 256-color bitmap, initialized to all black.
//-------------------------------------------------------------------------
{
    // delete any existing stuff
    DeleteContents();

    // allocate memory for the header
    m_pBMI = (BITMAPINFO *) new BYTE[ sizeof(BITMAPINFOHEADER) + 256 * sizeof(RGBQUAD) ];
    if (!m_pBMI)
    {
        TRACE("CMRCDib:Out of memory for DIB header\n");
        return FALSE;
    }

    // allocate memory for the bits (DWORD aligned)
    int iBitsSize = ((iWidth + 3) & ~3) * iHeight;
    m_pBits = new BYTE[iBitsSize];
    if (!m_pBits)
    {
        TRACE("CMRCDib:Out of memory for DIB bits\n");
        delete m_pBMI;
        m_pBMI = NULL;
        return FALSE;
    }

    // fill in the header info
    BITMAPINFOHEADER *pBI = (BITMAPINFOHEADER *) m_pBMI;
    pBI->biSize = sizeof(BITMAPINFOHEADER);
    pBI->biWidth = iWidth;
    pBI->biHeight = iHeight;
    pBI->biPlanes = 1;
    pBI->biBitCount = 8;
    pBI->biCompression = BI_RGB;
    pBI->biSizeImage = 0;
    pBI->biXPelsPerMeter = 0;
    pBI->biYPelsPerMeter = 0;
    pBI->biClrUsed = 0;
    pBI->biClrImportant = 0;

    // create an arb color table (gray scale)
    RGBQUAD *prgb = GetClrTabAddress();
    for (int i = 0; i < 256; i++)
    {
        prgb->rgbBlue = prgb->rgbGreen = prgb->rgbRed = (BYTE) i;
        prgb->rgbReserved = 0;
        prgb++;
    }

    // set all the bits to a known state (black)
    memset(m_pBits, 0, iBitsSize);

    return TRUE;
}


//---------------------------------------------------------------------
BOOL CMRCDib::LoadFileName(LPCTSTR lpszFileName)
// Load DIB for a file name
//---------------------------------------------------------------------
{
	CFile file;
	if (!file.Open(lpszFileName, CFile::modeRead | CFile::shareDenyWrite))
		return FALSE;   
	return Load(&file);			// destructor will close the file
}	



//---------------------------------------------------------------------
BOOL CMRCDib::Load(CFile *fp)
// Load a DIB from an open file.
// code in here also handles PM format bitmaps 
//---------------------------------------------------------------------
{
#ifdef HANDLE_PM_BITMAPS
    BOOL bIsPM = FALSE;
#endif // HANDLE_PM_BITMAPS
    BITMAPINFO *pBmpInfo = NULL;
    BYTE *pBits = NULL;

    // get the current file position
    DWORD dwFileStart = fp->GetPosition();

    // read the file header to get the file size and to
    // find where the bits start in the file
    BITMAPFILEHEADER BmpFileHdr;
    int iBytes;
    iBytes = fp->Read(&BmpFileHdr, sizeof(BmpFileHdr));
    if (iBytes != sizeof(BmpFileHdr))
    {
        TRACE("CMRCDib::Load() - failed to read file header\n");
        goto $abort;
    }

    // check we have the magic 'BM' at the start
    if (BmpFileHdr.bfType != 0x4D42)
    {
        TRACE("CMRCDib::Load() - not a bitmap file\n");
        goto $abort;
    }

    // Assume file is a Windows DIB	and read the BITMAPINFOHEADER.  If it turns
    // out to be a PM DIB file, convert it later.
    BITMAPINFOHEADER BmpInfoHdr;
    iBytes = fp->Read(&BmpInfoHdr, sizeof(BmpInfoHdr)); 
    if (iBytes != sizeof(BmpInfoHdr))
    {
        TRACE("CMRCDib::Load() - failed to read BITMAPINFOHEADER\n");
        goto $abort;
    }

    // check we got a real Windows DIB file
    if (BmpInfoHdr.biSize != sizeof(BITMAPINFOHEADER))
    {
        if (BmpInfoHdr.biSize != sizeof(BITMAPCOREHEADER))
        {
        	TRACE("CMRCDib::Load() - file is not Windows or PM DIB format\n");
            goto $abort;
        }

#ifdef HANDLE_PM_BITMAPS
        // set a flag to convert PM file to Win format later
        bIsPM = TRUE;

        // back up the file pointer and read the BITMAPCOREHEADER
        // and create the BITMAPINFOHEADER from it
        fp->Seek(dwFileStart + sizeof(BITMAPFILEHEADER), CFile::begin);
        BITMAPCOREHEADER BmpCoreHdr;
        iBytes = fp->Read(&BmpCoreHdr, sizeof(BmpCoreHdr)); 
        if (iBytes != sizeof(BmpCoreHdr))
        {
            TRACE("CMRCDib::Load() - failed to read BITMAPCOREHEADER");
            goto $abort;
        }

        BmpInfoHdr.biSize = sizeof(BITMAPINFOHEADER);
        BmpInfoHdr.biWidth = (int) BmpCoreHdr.bcWidth;
        BmpInfoHdr.biHeight = (int) BmpCoreHdr.bcHeight;
        BmpInfoHdr.biPlanes = BmpCoreHdr.bcPlanes;
        BmpInfoHdr.biBitCount = BmpCoreHdr.bcBitCount;
        BmpInfoHdr.biCompression = BI_RGB;
        BmpInfoHdr.biSizeImage = 0;
        BmpInfoHdr.biXPelsPerMeter = 0;
        BmpInfoHdr.biYPelsPerMeter = 0;
        BmpInfoHdr.biClrUsed = 0;
        BmpInfoHdr.biClrImportant = 0;
#endif // HANDLE_PM_BITMAPS
    }

    // Work out how much memory we need for the BITMAPINFO
    // structure, color table and then for the bits.  
    // Allocate the memory blocks, copy the BmpInfoHdr we have so far 
    // and then read in the color table from the file.
    int iColors;
    int iColorTableSize;
    iColors = NumDIBColorEntries((LPBITMAPINFO) &BmpInfoHdr);
    iColorTableSize = iColors * sizeof(RGBQUAD);
    int iBitsSize;
    int iBISize;
    // always allocate enough room for 256 entries
    iBISize = sizeof(BITMAPINFOHEADER)    
           + 256 * sizeof(RGBQUAD);
    iBitsSize = BmpFileHdr.bfSize - 
                BmpFileHdr.bfOffBits;

    // allocate the memory for the header
    pBmpInfo = (LPBITMAPINFO) new BYTE[iBISize];
    if (!pBmpInfo)
    {
        TRACE("CMRCDib::Load() - Out of memory for DIB header");
        goto $abort;
    }

    // copy the header we already have
    memcpy(pBmpInfo, &BmpInfoHdr, sizeof(BITMAPINFOHEADER));

    // now read the color table in from the file
#ifdef HANDLE_PM_BITMAPS
    if (bIsPM)
    {
        // read each PM color table entry in turn and convert it
        // to Win DIB format as we go
        LPRGBQUAD lpRGB;
        lpRGB = (LPRGBQUAD) ((LPBYTE) pBmpInfo + sizeof(BITMAPINFOHEADER));
        int i;
        RGBTRIPLE rgbt;
        for (i=0; i<iColors; i++)
        {
            iBytes = fp->Read(&rgbt, sizeof(RGBTRIPLE));
            if (iBytes != sizeof(RGBTRIPLE))
            {
                TRACE("Failed to read RGBTRIPLE");
                goto $abort;
            }
            lpRGB->rgbBlue = rgbt.rgbtBlue;
            lpRGB->rgbGreen = rgbt.rgbtGreen;
            lpRGB->rgbRed = rgbt.rgbtRed;
            lpRGB->rgbReserved = 0;
            lpRGB++;
        }
    }
	else
    {
#endif // HANDLE_PM_BITMAPS
        // read the color table from the file
        iBytes = fp->Read(((LPBYTE) pBmpInfo) + sizeof(BITMAPINFOHEADER),
                             iColorTableSize);
        if (iBytes != iColorTableSize)
        {
            TRACE("CMRCDib::Load() - failed to read PM color table");
            goto $abort;
        }
#ifdef HANDLE_PM_BITMAPS
    }
#endif // HANDLE_PM_BITMAPS

    // allocate the memory for the bits
    pBits = new BYTE[iBitsSize];
    if (!pBits)
   	{
        TRACE("CMRCDib::Load() - out of memory for DIB bits");
        goto $abort;
    }

    // seek to the bits in the file
    fp->Seek(dwFileStart + BmpFileHdr.bfOffBits, CFile::begin);

    // read the bits
    iBytes = fp->Read(pBits, iBitsSize);
    if (iBytes != iBitsSize)
    {
        TRACE("CMRCDib::Load() - failed to read bits");
        goto $abort;
    }

    // Everything went OK
    DeleteContents();  // remove previous info, and delete this one
    m_pBMI = pBmpInfo; 
    m_pBits = pBits;
    return TRUE;
                
$abort: // something went wrong
    if (pBmpInfo)
     	delete pBmpInfo;
    if (pBits)
     	delete pBits;
    return FALSE;    
}



//--------------------------------------------------------------------------
BOOL CMRCDib::LoadFromResource(LPCTSTR lpszResource)
// load bitmap from a resource ID
//--------------------------------------------------------------------------
{
    BITMAPINFO *pBmpInfo = NULL;
    BYTE *pBits = NULL;

	HINSTANCE hResInst = AfxFindResourceHandle(lpszResource, RT_BITMAP);
	HRSRC hFindRes;
	HGLOBAL hLoadRes;
	LPBYTE lpRes, lpLockRes;

	hFindRes = ::FindResource(hResInst, lpszResource, RT_BITMAP);
	if (hFindRes == NULL)
		return FALSE;
	hLoadRes = LoadResource(hResInst, hFindRes);	
	if (hLoadRes == NULL)
		return FALSE;
	lpLockRes = (LPBYTE) ::LockResource(hLoadRes);
	if (lpLockRes == NULL)
		return FALSE;
	lpRes = lpLockRes;
					
    // check we got a real Windows DIB file
    if (((LPBITMAPINFOHEADER)lpLockRes)->biSize != sizeof(BITMAPINFOHEADER))
    	return FALSE;
	
    // Look at color table size, and work out where image bits start
    int iColors;
    int iColorTableSize;
    iColors = NumDIBColorEntries((LPBITMAPINFO)lpLockRes);
    iColorTableSize = iColors * sizeof(RGBQUAD);
    pBits = lpLockRes + sizeof(BITMAPINFOHEADER) + iColorTableSize;
	
	// Since the resource is now locked,we can just return pointers to the BITMAPINFO
	// structure and the bits.
 	
 	DeleteContents();		// remove previous DIB, if any
 	m_pBMI = (BITMAPINFO *) lpLockRes;
	m_pBits = pBits;
	m_cLoadedFromResource = 1;
    return TRUE;
}




//------------------------------------------------------------------
void CMRCDib::Draw(CDC *pDC, int x, int y)
// Draw the DIB to a given DC, at default size
//------------------------------------------------------------------
{
    ::StretchDIBits(pDC->GetSafeHdc(),
                  x,                        // dest x
                  y,                        // dest y
                  DibWidth(),                 // dest width
                  DibHeight(),                // dest height
                  0,                        // src x
                  0,                        // src y
                  DibWidth(),                 // src width
                  DibHeight(),                // src height
                  GetBitsAddress(),         // bits
                  GetBitmapInfoAddress(),   // BITMAPINFO
                  DIB_RGB_COLORS,           // options
                  SRCCOPY);                 // rop
}


//------------------------------------------------------------------
void CMRCDib::Draw(CDC *pDC, int x, int y, int cx, int cy)
// Draw the DIB to a given DC
//------------------------------------------------------------------
{
    ::StretchDIBits(pDC->GetSafeHdc(),
                  x,                        // dest x
                  y,                        // dest y
                  cx,                 		// dest width
                  cy,                		// dest height
                  0,                        // src x
                  0,                        // src y
                  DibWidth(),                 // src width
                  DibHeight(),                // src height
                  GetBitsAddress(),         // bits
                  GetBitmapInfoAddress(),   // BITMAPINFO
                  DIB_RGB_COLORS,           // options
                  SRCCOPY);                 // rop
}


//------------------------------------------------------------------
int CMRCDib::GetNumClrEntries()
// get the number of color table entries
//------------------------------------------------------------------
{
    return NumDIBColorEntries(m_pBMI);
}


//------------------------------------------------------------------
int CMRCDib::ColorTableSize()
// get the size of the color table entries
//------------------------------------------------------------------
{
    return NumDIBColorEntries(m_pBMI) * sizeof(RGBQUAD);
}




#define DIB_HEADER_MARKER   ((WORD) ('M' << 8) | 'B')
#define WIDTHBYTES(bits)    (((bits) + 31) / 32 * 4)


//------------------------------------------------------------------
int CMRCDib::SaveFile(LPCTSTR lpFileName)
//------------------------------------------------------------------
{	 
    BITMAPFILEHEADER    bmfHdr;     // Header for Bitmap file
    LPBITMAPINFOHEADER  lpBI;       // Pointer to DIB info structure
    HANDLE              fh;         // file handle for opened file
    DWORD               dwDIBSize;
    DWORD               dwWritten;

    //if (!hDib)
    //    return ERR_INVALIDHANDLE;

    fh = CreateFile(lpFileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS,
            FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN, NULL);

    if (fh == INVALID_HANDLE_VALUE)
        return 1; // ERR_OPEN;

    // Get a pointer to the DIB memory, the first of which contains
    // a BITMAPINFO structure

    lpBI = (LPBITMAPINFOHEADER)m_pBMI;
    if (!lpBI)
    {
        CloseHandle(fh);
        return 1; //ERR_LOCK;
    }

    // Check to see if we're dealing with an OS/2 DIB.  If so, don't
    // save it because our functions aren't written to deal with these
    // DIBs.

    if (lpBI->biSize != sizeof(BITMAPINFOHEADER))
    {
        //GlobalUnlock(hDib);
        CloseHandle(fh);
        return 1; //ERR_NOT_DIB;
    }

    // Fill in the fields of the file header

    // Fill in file type (first 2 bytes must be "BM" for a bitmap)

    bmfHdr.bfType = DIB_HEADER_MARKER;  // "BM"

    // Calculating the size of the DIB is a bit tricky (if we want to
    // do it right).  The easiest way to do this is to call GlobalSize()
    // on our global handle, but since the size of our global memory may have
    // been padded a few bytes, we may end up writing out a few too
    // many bytes to the file (which may cause problems with some apps,
    // like HC 3.0).
    //
    // So, instead let's calculate the size manually.
    //
    // To do this, find size of header plus size of color table.  Since the
    // first DWORD in both BITMAPINFOHEADER and BITMAPCOREHEADER conains
    // the size of the structure, let's use this.

    // Partial Calculation

    dwDIBSize = *(LPDWORD)lpBI + ColorTableSize(); 

    // Now calculate the size of the image

    // It's an RLE bitmap, we can't calculate size, so trust the biSizeImage
    // field

    if ((lpBI->biCompression == BI_RLE8) || (lpBI->biCompression == BI_RLE4))
        dwDIBSize += lpBI->biSizeImage;
    else
    {
        DWORD dwBmBitsSize;  // Size of Bitmap Bits only

        // It's not RLE, so size is Width (DWORD aligned) * Height

        dwBmBitsSize = WIDTHBYTES((lpBI->biWidth)*((DWORD)lpBI->biBitCount)) *
                lpBI->biHeight;

        dwDIBSize += dwBmBitsSize;

        // Now, since we have calculated the correct size, why don't we
        // fill in the biSizeImage field (this will fix any .BMP files which 
        // have this field incorrect).

        lpBI->biSizeImage = dwBmBitsSize;
    }


    // Calculate the file size by adding the DIB size to sizeof(BITMAPFILEHEADER)
                   
    bmfHdr.bfSize = dwDIBSize + sizeof(BITMAPFILEHEADER);
    bmfHdr.bfReserved1 = 0;
    bmfHdr.bfReserved2 = 0;

    // Now, calculate the offset the actual bitmap bits will be in
    // the file -- It's the Bitmap file header plus the DIB header,
    // plus the size of the color table.
    
    bmfHdr.bfOffBits = (DWORD)sizeof(BITMAPFILEHEADER) + lpBI->biSize +
            ColorTableSize();

    // Write the file header

    WriteFile(fh, (LPSTR)&bmfHdr, sizeof(BITMAPFILEHEADER), &dwWritten, NULL);

    // Write the DIB header and the bits -- use local version of
    // MyWrite, so we can write more than 32767 bytes of data
    
    WriteFile(fh, (LPSTR)lpBI, dwDIBSize, &dwWritten, NULL);

    //GlobalUnlock(hDib);
    CloseHandle(fh);

    if (dwWritten == 0)
        return 1; //ERR_OPEN; // oops, something happened in the write
    else
        return 0; // Success code
}

//--------------------------------------------------------------------------
HBITMAP CMRCDib::GetMappedBitmap(const BITMAPCOLORMAP * pColorMap, int nMaps)
// Returns bitmap from dib with requested colour mapping
//--------------------------------------------------------------------------
{
	// system color maps (same as MFC uses for toolbars, if user doesn't specify one)
	static const BITMAPCOLORMAP sysColorMap[] =
	{
		// mapping from color in DIB to system color
		{ RGB_TO_RGBQUAD(0x00, 0x00, 0x00),  COLOR_BTNTEXT },       // black
		{ RGB_TO_RGBQUAD(0x80, 0x80, 0x80),  COLOR_BTNSHADOW },     // dark grey
		{ RGB_TO_RGBQUAD(0xC0, 0xC0, 0xC0),  COLOR_BTNFACE },       // bright grey
		{ RGB_TO_RGBQUAD(0xFF, 0xFF, 0xFF),  COLOR_BTNHIGHLIGHT }   // white
	};
	
	LPBITMAPINFOHEADER lpBitmap = &(m_pBMI->bmiHeader);
	if (lpBitmap == NULL)
		return NULL;

	// make copy of BITMAPINFOHEADER so we can modify the color table
	int nColorTableSize = lpBitmap->biClrUsed;
	if (nColorTableSize == 0)
	{
		switch (lpBitmap->biBitCount)
		{
			case 4:
				nColorTableSize = 16;
				break;
			case 8:
				nColorTableSize = 256;
				break;
			default:
				return NULL;
		}
	}
	
	UINT nSize = lpBitmap->biSize + nColorTableSize * sizeof(RGBQUAD);
	LPBITMAPINFOHEADER lpBitmapInfo = (LPBITMAPINFOHEADER)::malloc(nSize);
	if (lpBitmapInfo == NULL)
		return NULL;
	memcpy(lpBitmapInfo, lpBitmap, nSize);

	// color table is in RGBQUAD DIB format
    DWORD* pColorTable = (DWORD*)(((BYTE*)lpBitmapInfo) + sizeof (BITMAPINFOHEADER));
    pColorTable = (DWORD*)(((LPBYTE)lpBitmapInfo) + (UINT)lpBitmapInfo->biSize);

	HDC hDCScreen = ::GetDC(HWND_DESKTOP);
	
	for (int iColor = 0; iColor < nColorTableSize; iColor++)
	{
		// look for matching RGBQUAD color in original
		for (int i = 0; i < nMaps; i++)
		{
			if (pColorTable[iColor] == pColorMap[i].rgbqFrom)
			{
				COLORREF clrNew = CLR_TO_RGBQUAD(::GetSysColor(pColorMap[i].iSysColorTo));
				// clrNew = ::GetNearestColor(hDCScreen, clrNew);		// map to solid colors only
				pColorTable[iColor] = clrNew;
				break;
			}
		}
	}

	int nWidth = DibWidth();
	int nHeight = DibHeight();
	HBITMAP hbm = ::CreateCompatibleBitmap(hDCScreen, nWidth, nHeight);
	::ReleaseDC(NULL, hDCScreen);
	if (hbm != NULL)
	{
		HDC hDCGlyphs = CreateCompatibleDC(NULL);
	
		HBITMAP hbmOld = (HBITMAP)::SelectObject(hDCGlyphs, hbm);

		LPBYTE lpBits = GetBitsAddress();

		StretchDIBits(hDCGlyphs, 0, 0, nWidth, nHeight, 0, 0, nWidth, nHeight,
			lpBits, (LPBITMAPINFO)lpBitmapInfo, DIB_RGB_COLORS, SRCCOPY);
		SelectObject(hDCGlyphs, hbmOld);
	   ::DeleteDC(hDCGlyphs);
	}
	
    // free copy of bitmap info struct
	::free(lpBitmapInfo);

	return hbm;
}

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// CMRCDibPal
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

CMRCDibPal::CMRCDibPal()
{
}

CMRCDibPal::~CMRCDibPal()
{
}

//-----------------------------------------------------------------------
BOOL CMRCDibPal::Create(CMRCDib *pDIB)
// Create a palette from the color table in a CMRCDib
//-----------------------------------------------------------------------
{
    DWORD dwColors = pDIB->GetNumClrEntries();
    // Check the DIB has a color table
    if (! dwColors)
    {
        TRACE("CMRCDibPal::Create() - no color table\n");   
        return FALSE;
    }

    // get a pointer to the RGB quads in the color table
    RGBQUAD * pRGB = pDIB->GetClrTabAddress();

    // allocate a log pal and fill it with the color table info
    LOGPALETTE *pPal = (LOGPALETTE *) new BYTE [ sizeof(LOGPALETTE) 
                     						+ dwColors * sizeof(PALETTEENTRY) ];
    if (!pPal)
    {
        TRACE("CMRCDibPal::Create() - out of memory for logpal");
        return FALSE;
    }
    pPal->palVersion = 0x300; // Windows 3.0
    pPal->palNumEntries = (WORD) dwColors; // table size
    for (DWORD dw=0; dw<dwColors; dw++)
    {
        pPal->palPalEntry[dw].peRed = pRGB[dw].rgbRed;
        pPal->palPalEntry[dw].peGreen = pRGB[dw].rgbGreen;
        pPal->palPalEntry[dw].peBlue = pRGB[dw].rgbBlue;
        pPal->palPalEntry[dw].peFlags = 0;
    }
    BOOL bResult = CreatePalette(pPal);
	delete pPal;
    return bResult;
}

/////////////////////////////////////////////////////////////////////////////
// CMRCDibPal commands

//-----------------------------------------------------------------------
int CMRCDibPal::GetNumColors()
//-----------------------------------------------------------------------
{
    int iColors = 0;
    if (!GetObject(sizeof(iColors), &iColors))
    {
        TRACE("CMRCDibPal::GetNumColors() - failed to get num pal colors");
        return 0;
    }
    return iColors;
}


