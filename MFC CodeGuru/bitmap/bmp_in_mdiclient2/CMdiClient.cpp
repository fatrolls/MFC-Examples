#include "stdafx.h"
#include "CMdiClient.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CMdiClient::CMdiClient()
{
	m_nBackColor = CLR_INVALID;
	m_hPal = 0;
	m_hBitmap = 0;
	m_bTile = FALSE;
}

CMdiClient::~CMdiClient()
{
	::DeleteObject(m_hBitmap);
	::DeleteObject(m_hPal);
}

IMPLEMENT_DYNCREATE(CMdiClient, CWnd)

BEGIN_MESSAGE_MAP(CMdiClient, CWnd)
	//{{AFX_MSG_MAP(CMdiClient)
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

///////////////////////////////////////////////////////////////////////////////
//
// Function name	: CMdiClient::OnEraseBkgnd
// Description	    : 
// Return type		: BOOL 
//
///////////////////////////////////////////////////////////////////////////////
// Argument         : CDC* pDC
///////////////////////////////////////////////////////////////////////////////
BOOL CMdiClient::OnEraseBkgnd(CDC* pDC) 
{
	CRect rect;
	GetClientRect(&rect);

	BOOL result = TRUE;

	if (m_nBackColor != CLR_INVALID)
		pDC->FillSolidRect(&rect, m_nBackColor);
	else
		result = CWnd::OnEraseBkgnd(pDC);

	if (m_hBitmap)
	{
		HDC dcMem;
		dcMem = ::CreateCompatibleDC(0);
		HBITMAP oldBitmap = (HBITMAP)::SelectObject(dcMem, m_hBitmap);

		HPALETTE hOldPal = ::SelectPalette(pDC->m_hDC, m_hPal, FALSE);
		::RealizePalette(pDC->m_hDC);
		
		if (m_bTile)
			for (int nX = 0; nX < rect.Width(); nX += m_width)
				for (int nY = 0; nY < rect.Height(); nY += m_height)
					::BitBlt(pDC->m_hDC, nX, nY, m_width, m_height, dcMem, 0, 0, SRCCOPY);
		else // put it in the centre
			::BitBlt(pDC->m_hDC, (rect.right - m_width)/2, 
					(rect.bottom - m_height)/2, 
					m_width, m_height, dcMem, 0, 0, SRCCOPY);

		::SelectPalette(pDC->m_hDC, hOldPal, FALSE);
		::SelectObject(dcMem, oldBitmap);
	}

	return result;
}

///////////////////////////////////////////////////////////////////////////////
//
// Function name	: CMdiClient::SetBackColor
// Description	    : 
// Return type		: COLORREF 
//
///////////////////////////////////////////////////////////////////////////////
// Argument         : COLORREF nBackColor
///////////////////////////////////////////////////////////////////////////////
COLORREF CMdiClient::SetBackColor(COLORREF nBackColor)
{
	LockWindowUpdate();

	COLORREF cr = m_nBackColor;
	m_nBackColor = nBackColor;

	UnlockWindowUpdate();

	return cr;
}

///////////////////////////////////////////////////////////////////////////////
//
// Function name	: CMdiClient::SetBitmap
// Description	    : 
// Return type		: BOOL 
//
///////////////////////////////////////////////////////////////////////////////
// Argument         : UINT nID
///////////////////////////////////////////////////////////////////////////////
BOOL CMdiClient::SetBitmap(UINT nID)
{
	LockWindowUpdate();

	if (m_hBitmap)
	{
		::DeleteObject(m_hBitmap);
		m_hBitmap = 0;
	}
	if (m_hPal)
	{
		::DeleteObject(m_hPal);
		m_hPal = 0;
	}

	HRSRC hRes = ::FindResource(AfxGetInstanceHandle(),MAKEINTRESOURCE(nID),RT_BITMAP);

	if (!hRes)
	{
		UnlockWindowUpdate();
		return FALSE;
	}

	HGLOBAL hGbl = ::LoadResource(AfxGetInstanceHandle(), hRes);
	LPBITMAPINFOHEADER lpBMIH = (LPBITMAPINFOHEADER)::LockResource(hGbl);

	int numColors = (WORD)lpBMIH->biClrUsed;
	if (numColors == 0)
		numColors = 256;

	NPLOGPALETTE npPal = (NPLOGPALETTE)LocalAlloc(LMEM_FIXED, sizeof(LOGPALETTE) + 
				numColors * sizeof(PALETTEENTRY));

	npPal->palVersion = 0x300;
    npPal->palNumEntries = numColors;

	RGBQUAD FAR *lpRGB = (RGBQUAD FAR *)((LPSTR)lpBMIH + lpBMIH->biSize);

    for (WORD i = 0; i < numColors; i++, lpRGB++)
	{
	    npPal->palPalEntry[i].peRed = lpRGB->rgbRed;
	    npPal->palPalEntry[i].peGreen = lpRGB->rgbGreen;
	    npPal->palPalEntry[i].peBlue = lpRGB->rgbBlue;
	    npPal->palPalEntry[i].peFlags = 0;
	}

	m_hPal = ::CreatePalette((LPLOGPALETTE)npPal);
	LocalFree((HLOCAL)npPal);

    HDC hDC = ::GetDC(NULL);
    HPALETTE hOldPal = SelectPalette(hDC, m_hPal, FALSE);
    RealizePalette(hDC);

	LPSTR lpDIBBits = ((char*)lpBMIH + sizeof(BITMAPINFOHEADER) +  numColors * sizeof(RGBQUAD));

	m_hBitmap = ::CreateDIBitmap(hDC, (LPBITMAPINFOHEADER)lpBMIH, CBM_INIT,
            lpDIBBits, (LPBITMAPINFO)lpBMIH, DIB_RGB_COLORS);

	m_width = lpBMIH->biWidth;
	m_height = lpBMIH->biHeight;

    SelectPalette(hDC, hOldPal, FALSE);
    ::ReleaseDC(NULL, hDC);

	UnlockWindowUpdate();

	return TRUE;
}

///////////////////////////////////////////////////////////////////////////////
//
// Function name	: CMdiClient::OnSize
// Description	    : 
// Return type		: void 
//
///////////////////////////////////////////////////////////////////////////////
// Argument         : UINT nType
// Argument         :  int cx
// Argument         :  int cy
///////////////////////////////////////////////////////////////////////////////
void CMdiClient::OnSize(UINT nType, int cx, int cy) 
{
	CWnd::OnSize(nType, cx, cy);
	
	if (m_hBitmap)
		Invalidate();
}

BOOL CMdiClient::SetBitmap(LPCSTR szFilename)
{
    HANDLE      hDIB;
    HANDLE      hFile;

	LockWindowUpdate();

	if (m_hBitmap)
	{
		::DeleteObject(m_hBitmap);
		m_hBitmap = 0;
	}
	if (m_hPal)
	{
		::DeleteObject(m_hPal);
		m_hPal = 0;
	}

    if ((hFile = CreateFile(szFilename, GENERIC_READ, FILE_SHARE_READ, NULL,
            OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN,
            NULL)) != INVALID_HANDLE_VALUE)
    {
        hDIB = ReadDIBFile(hFile);
        CloseHandle(hFile);
    }

	LPBITMAPINFOHEADER lpBMIH = (LPBITMAPINFOHEADER)GlobalLock(hDIB);

	int numColors = (WORD)lpBMIH->biClrUsed;
	if (numColors == 0)
		numColors = 256;

	NPLOGPALETTE npPal = (NPLOGPALETTE)LocalAlloc(LMEM_FIXED, sizeof(LOGPALETTE) + 
				numColors * sizeof(PALETTEENTRY));

	npPal->palVersion = 0x300;
    npPal->palNumEntries = numColors;

	RGBQUAD FAR *lpRGB = (RGBQUAD FAR *)((LPSTR)lpBMIH + lpBMIH->biSize);

    for (WORD i = 0; i < numColors; i++, lpRGB++)
	{
	    npPal->palPalEntry[i].peRed = lpRGB->rgbRed;
	    npPal->palPalEntry[i].peGreen = lpRGB->rgbGreen;
	    npPal->palPalEntry[i].peBlue = lpRGB->rgbBlue;
	    npPal->palPalEntry[i].peFlags = 0;
	}

	m_hPal = ::CreatePalette((LPLOGPALETTE)npPal);
	LocalFree((HLOCAL)npPal);

    HDC hDC = ::GetDC(NULL);
    HPALETTE hOldPal = SelectPalette(hDC, m_hPal, FALSE);
    RealizePalette(hDC);

	LPSTR lpDIBBits = ((char*)lpBMIH + sizeof(BITMAPINFOHEADER) +  numColors * sizeof(RGBQUAD));

	m_hBitmap = ::CreateDIBitmap(hDC, (LPBITMAPINFOHEADER)lpBMIH, CBM_INIT,
            lpDIBBits, (LPBITMAPINFO)lpBMIH, DIB_RGB_COLORS);

	m_width = lpBMIH->biWidth;
	m_height = lpBMIH->biHeight;

    SelectPalette(hDC, hOldPal, FALSE);
    ::ReleaseDC(NULL, hDC);

	UnlockWindowUpdate();

	return TRUE;

}
/*************************************************************************
 *
 * Function:  ReadDIBFile (int)
 *
 *  Purpose:  Reads in the specified DIB file into a global chunk of
 *            memory.
 *
 *  Returns:  A handle to a dib (hDIB) if successful.
 *            NULL if an error occurs.
 *
 * Comments:  BITMAPFILEHEADER is stripped off of the DIB.  Everything
 *            from the end of the BITMAPFILEHEADER structure on is
 *            returned in the global memory handle.
 *
 *
 * NOTE: The DIB API were not written to handle OS/2 DIBs, so this
 * function will reject any file that is not a Windows DIB.
 *
 * History:   Date      Author       Reason
 *            9/15/91   Mark Bader   Based on DIBVIEW
 *            6/25/92   Mark Bader   Added check for OS/2 DIB
 *            7/21/92   Mark Bader   Added code to deal with bfOffBits
 *                                     field in BITMAPFILEHEADER      
 *            9/11/92   Mark Bader   Fixed Realloc Code to free original mem
 *            1/25/94   Hung Nguyen  Changed file APIs to Win32 APIs
 *
 *************************************************************************/

HANDLE CMdiClient::ReadDIBFile(HANDLE hFile)
{
    BITMAPFILEHEADER    bmfHeader;
    DWORD               dwBitsSize;
    UINT                nNumColors;   // Number of colors in table
    HANDLE              hDIB;        
    HANDLE              hDIBtmp;      // Used for GlobalRealloc() //MPB
    LPBITMAPINFOHEADER  lpbi;
    DWORD               offBits;
    DWORD               dwRead;

    // get length of DIB in bytes for use when reading

    dwBitsSize = GetFileSize(hFile, NULL);

    // Allocate memory for header & color table. We'll enlarge this
    // memory as needed.

    hDIB = GlobalAlloc(GMEM_MOVEABLE, (DWORD)(sizeof(BITMAPINFOHEADER) +
            256 * sizeof(RGBQUAD)));

    if (!hDIB)
        return NULL;

    lpbi = (LPBITMAPINFOHEADER)GlobalLock(hDIB);

    if (!lpbi) 
    {
        GlobalFree(hDIB);
        return NULL;
    }

    // read the BITMAPFILEHEADER from our file

    if (!ReadFile(hFile, (LPSTR)&bmfHeader, sizeof (BITMAPFILEHEADER),
            &dwRead, NULL))
        goto ErrExit;

    if (sizeof (BITMAPFILEHEADER) != dwRead)
        goto ErrExit;

    if (bmfHeader.bfType != 0x4d42)  // 'BM'
        goto ErrExit;

    // read the BITMAPINFOHEADER

    if (!ReadFile(hFile, (LPSTR)lpbi, sizeof(BITMAPINFOHEADER), &dwRead,
            NULL))
        goto ErrExit;

    if (sizeof(BITMAPINFOHEADER) != dwRead)
        goto ErrExit;

    // Check to see that it's a Windows DIB -- an OS/2 DIB would cause
    // strange problems with the rest of the DIB API since the fields
    // in the header are different and the color table entries are
    // smaller.
    //
    // If it's not a Windows DIB (e.g. if biSize is wrong), return NULL.

    if (lpbi->biSize == sizeof(BITMAPCOREHEADER))
        goto ErrExit;

    // Now determine the size of the color table and read it.  Since the
    // bitmap bits are offset in the file by bfOffBits, we need to do some
    // special processing here to make sure the bits directly follow
    // the color table (because that's the format we are susposed to pass
    // back)

    if (!(nNumColors = (UINT)lpbi->biClrUsed))
    {
        // no color table for 24-bit, default size otherwise

        if (lpbi->biBitCount != 24)
            nNumColors = 1 << lpbi->biBitCount; // standard size table
    }

    // fill in some default values if they are zero

    if (lpbi->biClrUsed == 0)
        lpbi->biClrUsed = nNumColors;

    if (lpbi->biSizeImage == 0)
    {
        lpbi->biSizeImage = ((((lpbi->biWidth * (DWORD)lpbi->biBitCount) +
                31) & ~31) >> 3) * lpbi->biHeight;
    }

    // get a proper-sized buffer for header, color table and bits

    GlobalUnlock(hDIB);
    hDIBtmp = GlobalReAlloc(hDIB, lpbi->biSize + nNumColors *
            sizeof(RGBQUAD) + lpbi->biSizeImage, 0);

    if (!hDIBtmp) // can't resize buffer for loading
        goto ErrExitNoUnlock; //MPB
    else
        hDIB = hDIBtmp;

    lpbi = (LPBITMAPINFOHEADER)GlobalLock(hDIB);

    // read the color table

    ReadFile (hFile, (LPSTR)(lpbi) + lpbi->biSize,
            nNumColors * sizeof(RGBQUAD), &dwRead, NULL);

    // offset to the bits from start of DIB header

    offBits = lpbi->biSize + nNumColors * sizeof(RGBQUAD);

    // If the bfOffBits field is non-zero, then the bits might *not* be
    // directly following the color table in the file.  Use the value in
    // bfOffBits to seek the bits.

    if (bmfHeader.bfOffBits != 0L)
        SetFilePointer(hFile, bmfHeader.bfOffBits, NULL, FILE_BEGIN);

    if (ReadFile(hFile, (LPSTR)lpbi + offBits, lpbi->biSizeImage, &dwRead,
            NULL))
        goto OKExit;


ErrExit:
    GlobalUnlock(hDIB);    

ErrExitNoUnlock:    
    GlobalFree(hDIB);
    return NULL;

OKExit:
    GlobalUnlock(hDIB);
    return hDIB;
}
