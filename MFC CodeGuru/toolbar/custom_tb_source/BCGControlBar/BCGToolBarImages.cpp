// BCGToolBarImages.cpp: implementation of the CBCGToolBarImages class.
//
//////////////////////////////////////////////////////////////////////

#include "Stdafx.h"
#include "WinSpool.h"
#include <afxpriv.h>
#include "globals.h"
#include "BCGToolBarImages.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

static BOOL WriteDIB( LPCTSTR szFile, HANDLE hDIB);
static HANDLE DDBToDIB (HBITMAP bitmap, DWORD dwCompression);


// globals for fast drawing (shared globals)
static HDC hDCGlyphs = NULL;
static HDC hDCMono = NULL;
static HBRUSH hbrDither = NULL;

/*
	DIBs use RGBQUAD format:
		0xbb 0xgg 0xrr 0x00

	Reasonably efficient code to convert a COLORREF into an
	RGBQUAD is byte-order-dependent, so we need different
	code depending on the byte order we're targeting.
*/

#define RGB_TO_RGBQUAD(r,g,b)   (RGB(b,g,r))
#define CLR_TO_RGBQUAD(clr)     (RGB(GetBValue(clr), GetGValue(clr), GetRValue(clr)))
#define RGBQUAD_TO_CLR(clr)     (RGB(GetBValue(clr), GetGValue(clr), GetRValue(clr)))

// Raster Ops
#define ROP_DSPDxax  0x00E20746L
#define ROP_PSDPxax  0x00B8074AL

/////////////////////////////////////////////////////////////////////////////
// Init / Term

// a special struct that will cleanup automatically
struct _AFX_TOOLBAR_TERM
{
	~_AFX_TOOLBAR_TERM()
	{
		AfxDeleteObject((HGDIOBJ*)&hDCMono);
		AfxDeleteObject((HGDIOBJ*)&hDCGlyphs);
		AfxDeleteObject((HGDIOBJ*)&hbrDither);
	}
};

static const _AFX_TOOLBAR_TERM toolbarTerm;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CBCGToolBarImages::CBCGToolBarImages()
{
	m_bModified = FALSE;
	m_iCount = 0;

	m_hbmImageWell = NULL;
	m_hInstImageWell = NULL;

	m_uiResID = 0;
	m_bUserImagesList = FALSE;

	// initialize the toolbar drawing engine
	static BOOL bInitialized;
	if (!bInitialized)
	{
		hDCGlyphs = CreateCompatibleDC(NULL);

		// Mono DC and Bitmap for disabled image
		hDCMono = ::CreateCompatibleDC(NULL);

		HBITMAP hbmGray = CreateDitherBitmap();
		if (hbmGray != NULL)
		{
			ASSERT(hbrDither == NULL);
			hbrDither = ::CreatePatternBrush(hbmGray);
			AfxDeleteObject((HGDIOBJ*)&hbmGray);
		}

		if (hDCGlyphs == NULL || hDCMono == NULL || hbrDither == NULL)
			AfxThrowResourceException();

		bInitialized = TRUE;
	}

	// UISG standard sizes
	m_sizeButton.cx = 24;
	m_sizeButton.cy = 22;
	m_sizeImage.cx = 16;
	m_sizeImage.cy = 15;
}
//*******************************************************************************
CBCGToolBarImages::~CBCGToolBarImages()
{
	AfxDeleteObject((HGDIOBJ*)&m_hbmImageWell);
}
//*******************************************************************************
void CBCGToolBarImages::SetSizes (SIZE sizeButton, SIZE sizeImage)
{
	ASSERT(sizeButton.cx > 0 && sizeButton.cy > 0);
	ASSERT(sizeImage.cx > 0 && sizeImage.cy > 0);

	// button must be big enough to hold image + 3 pixels on each side
	ASSERT(sizeButton.cx >= sizeImage.cx + 6);
	ASSERT(sizeButton.cy >= sizeImage.cy + 6);

	m_sizeButton = sizeButton;
	m_sizeImage = sizeImage;
}
//*******************************************************************************
BOOL CBCGToolBarImages::Load (UINT uiResID, HINSTANCE hinstRes)
{
	m_uiResID = uiResID;

	LPCTSTR lpszResourceName = MAKEINTRESOURCE (uiResID);
	ASSERT(lpszResourceName != NULL);

	AfxDeleteObject((HGDIOBJ*)&m_hbmImageWell);     // get rid of old one

	m_hInstImageWell = (hinstRes == NULL) ? 
		AfxFindResourceHandle (lpszResourceName, RT_BITMAP) : 
		hinstRes;

	m_hbmImageWell = (HBITMAP) ::LoadImage (
		m_hInstImageWell,
		lpszResourceName,
		IMAGE_BITMAP,
		0, 0,
		LR_CREATEDIBSECTION | LR_LOADMAP3DCOLORS);

	UpdateCount ();
	return (m_hbmImageWell != NULL);
}
//*******************************************************************************
BOOL CBCGToolBarImages::Load (LPCSTR lpszBmpFileName)
{
	ASSERT (lpszBmpFileName != NULL);

	AfxDeleteObject((HGDIOBJ*)&m_hbmImageWell);     // get rid of old one

	m_hbmImageWell = (HBITMAP) ::LoadImage (
		AfxGetInstanceHandle (),
		lpszBmpFileName,
		IMAGE_BITMAP,
		0, 0,
		LR_LOADFROMFILE | LR_CREATEDIBSECTION | LR_LOADMAP3DCOLORS);

	if (m_hbmImageWell == NULL)
	{
		TRACE("Can't load bitmap: %s. GetLastError() = %x\r\n", 
			lpszBmpFileName,
			GetLastError ());
		return FALSE;
	}

	m_bUserImagesList = TRUE;
	m_strUDLPath = lpszBmpFileName;

	UpdateCount ();
	return TRUE;
}
//*******************************************************************************
BOOL CBCGToolBarImages::PrepareDrawImage (CBCGDrawState& ds)
{
	ASSERT(m_hbmImageWell != NULL);

	// We need to kick-start the bitmap selection process.
	ds.hbmOldGlyphs = (HBITMAP)SelectObject (hDCGlyphs, m_hbmImageWell);
	ds.hbmMono = CreateBitmap(m_sizeButton.cx-2, m_sizeButton.cy-2,
					1, 1, NULL);
	ds.hbmMonoOld = (HBITMAP)SelectObject(hDCMono, ds.hbmMono);
	if (ds.hbmOldGlyphs == NULL || ds.hbmMono == NULL || ds.hbmMonoOld == NULL)
	{
		TRACE0("Error: can't draw toolbar.\r\n");
		AfxDeleteObject((HGDIOBJ*)&ds.hbmMono);
		return FALSE;
	}

	return TRUE;
}
//*******************************************************************************
void CBCGToolBarImages::EndDrawImage (CBCGDrawState& ds)
{
	SelectObject(hDCMono, ds.hbmMonoOld);
	AfxDeleteObject((HGDIOBJ*)&ds.hbmMono);
	SelectObject(hDCGlyphs, ds.hbmOldGlyphs);
}
//*******************************************************************************
void CBCGToolBarImages::CreateMask(int iImage, CPoint ptOffset,
	 BOOL bHilite, BOOL bHiliteShadow)
{
	// initalize whole area with 0's
	PatBlt(hDCMono, 0, 0, m_sizeButton.cx-2, m_sizeButton.cy-2, WHITENESS);

	// create mask based on color bitmap
	// convert this to 1's
	SetBkColor(hDCGlyphs, globalData.clrBtnFace);
	BitBlt(hDCMono, ptOffset.x, ptOffset.y, m_sizeImage.cx, m_sizeImage.cy,
		hDCGlyphs, iImage * m_sizeImage.cx, 0, SRCCOPY);

	if (bHilite)
	{
		// convert this to 1's
		SetBkColor(hDCGlyphs, globalData.clrBtnHilite);

		// OR in the new 1's
		BitBlt(hDCMono, ptOffset.x, ptOffset.y, m_sizeImage.cx, m_sizeImage.cy,
			hDCGlyphs, iImage * m_sizeImage.cx, 0, SRCPAINT);

		if (bHiliteShadow)
			BitBlt(hDCMono, 1, 1, m_sizeButton.cx-3, m_sizeButton.cy-3,
				hDCMono, 0, 0, SRCAND);
	}
}
//********************************************************************************
BOOL CBCGToolBarImages::Draw (CDC* pDC, 
				int x, int y,
				POINT ptOffset,
				int iImage,
				BOOL bHilite,
				BOOL bDisabled,
				BOOL bIndeterminate)
{
	if (iImage < 0 || iImage >= m_iCount)
	{
		return FALSE;
	}

	ASSERT_VALID(pDC);

	int dx = m_sizeButton.cx;
	int dy = m_sizeButton.cy;

	if (!bHilite && !bDisabled)
	{
		// normal image version
		::BitBlt(pDC->m_hDC, x + ptOffset.x, y + ptOffset.y,
			m_sizeImage.cx, m_sizeImage.cy,
			hDCGlyphs, iImage * m_sizeImage.cx, 0, SRCCOPY);
		return TRUE;        // nothing more to do (rest of style is ignored)
	}

	if (bDisabled || bIndeterminate)
	{
		// disabled or indeterminate version
		CreateMask(iImage, ptOffset, TRUE, FALSE);

		pDC->SetTextColor(0L);                  // 0's in mono -> 0 (for ROP)
		pDC->SetBkColor((COLORREF)0x00FFFFFFL); // 1's in mono -> 1

		if (bDisabled)
		{
			// disabled - draw the hilighted shadow
			HGDIOBJ hbrOld = pDC->SelectObject (globalData.hbrBtnHilite);
			if (hbrOld != NULL)
			{
				// draw hilight color where we have 0's in the mask
				BitBlt(pDC->m_hDC, x + 1, y + 1,
					m_sizeButton.cx - 2, m_sizeButton.cy - 2,
					hDCMono, 0, 0, ROP_PSDPxax);
				pDC->SelectObject(hbrOld);
			}
		}

		//BLOCK: always draw the shadow
		{
			HGDIOBJ hbrOld = pDC->SelectObject(globalData.hbrBtnShadow);
			if (hbrOld != NULL)
			{
				// draw the shadow color where we have 0's in the mask
				BitBlt(pDC->m_hDC, x, y,
					m_sizeButton.cx - 2, m_sizeButton.cy - 2,
					hDCMono, 0, 0, ROP_PSDPxax);
				pDC->SelectObject(hbrOld);
			}
		}
	}

	// if it is checked do the dither brush avoiding the glyph
	if (bHilite || bIndeterminate)
	{
		HGDIOBJ hbrOld = pDC->SelectObject(hbrDither);
		if (hbrOld != NULL)
		{
			ptOffset.x -= globalData.cxBorder2;
			ptOffset.y -= globalData.cyBorder2;
			CreateMask(iImage, ptOffset, !bIndeterminate,
					bDisabled);

			pDC->SetTextColor(0L);              // 0 -> 0
			pDC->SetBkColor((COLORREF)0x00FFFFFFL); // 1 -> 1

			ASSERT(globalData.cxBorder2 == globalData.cyBorder2);
			int delta = bIndeterminate ?
						globalData.cxBorder2*2 : globalData.cxBorder2*2;

			// only draw the dither brush where the mask is 1's
			BitBlt(pDC->m_hDC,
				x + globalData.cxBorder2, y + globalData.cyBorder2, dx-delta, dy-delta,
				hDCMono, 0, 0, ROP_DSPDxax);
			pDC->SelectObject(hbrOld);
		}
	}

	return TRUE;
}
//********************************************************************************
void CBCGToolBarImages::FillDitheredRect (CDC* pDC, const CRect& rect)
{
	ASSERT_VALID(pDC);

	pDC->SetTextColor(0L);              // 0 -> 0
	pDC->SetBkColor((COLORREF)0x00FFFFFFL); // 1 -> 1

	::FillRect (pDC->GetSafeHdc (), &rect, hbrDither);
}
//********************************************************************************
HBITMAP CBCGToolBarImages::CreateDitherBitmap ()
{
	struct  // BITMAPINFO with 16 colors
	{
		BITMAPINFOHEADER bmiHeader;
		RGBQUAD      bmiColors[16];
	} bmi;
	memset(&bmi, 0, sizeof(bmi));

	bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmi.bmiHeader.biWidth = 8;
	bmi.bmiHeader.biHeight = 8;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biBitCount = 1;
	bmi.bmiHeader.biCompression = BI_RGB;

	COLORREF clr = ::GetSysColor(COLOR_BTNFACE);

	bmi.bmiColors[0].rgbBlue = GetBValue(clr);
	bmi.bmiColors[0].rgbGreen = GetGValue(clr);
	bmi.bmiColors[0].rgbRed = GetRValue(clr);

	clr = ::GetSysColor(COLOR_BTNHIGHLIGHT);
	bmi.bmiColors[1].rgbBlue = GetBValue(clr);
	bmi.bmiColors[1].rgbGreen = GetGValue(clr);
	bmi.bmiColors[1].rgbRed = GetRValue(clr);

	// initialize the brushes
	long patGray[8];
	for (int i = 0; i < 8; i++)
	   patGray[i] = (i & 1) ? 0xAAAA5555L : 0x5555AAAAL;

	HDC hDC = GetDC(NULL);
	HBITMAP hbm = CreateDIBitmap(hDC, &bmi.bmiHeader, CBM_INIT,
		(LPBYTE)patGray, (LPBITMAPINFO)&bmi, DIB_RGB_COLORS);
	ReleaseDC(NULL, hDC);

	return hbm;
}
//********************************************************************************
void CBCGToolBarImages::OnSysColorChange()
{
	// re-initialize global dither brush
	HBITMAP hbmGray = CreateDitherBitmap();
	if (hbmGray != NULL)
	{
		HBRUSH hbrNew = ::CreatePatternBrush(hbmGray);
		if (hbrNew != NULL)
		{
			AfxDeleteObject((HGDIOBJ*)&hbrDither);      // free old one
			hbrDither = hbrNew;
		}
		::DeleteObject(hbmGray);
	}

	// re-color bitmap for toolbar
	if (m_hbmImageWell != NULL)
	{
		if (m_bUserImagesList)
		{
			Load (m_strUDLPath);
		}
		else
		{
			Load (m_uiResID, m_hInstImageWell);
		}
	}

	UpdateCount ();
}
//********************************************************************************
void CBCGToolBarImages::UpdateCount ()
{
	if (m_hbmImageWell == NULL)
	{
		m_iCount = 0;
		return;
	}

	BITMAP bmp;
	if (::GetObject (m_hbmImageWell, sizeof (BITMAP), &bmp) == 0)
	{
		m_iCount = 0;
		return;
	}

	int iWidth = bmp.bmWidth;
	m_iCount = iWidth / m_sizeImage.cx;
}

//////////////////////////////////////////
// Image editing methods:
//////////////////////////////////////////

int CBCGToolBarImages::AddImage (HBITMAP hbmp)
{
	if (!m_bUserImagesList)	// Only user images can be edited!
	{
		return -1;
	}

	//-------------------------------
	// Get original bitmap attrbutes:
	//-------------------------------
	BITMAP bmp;
	if (::GetObject (m_hbmImageWell, sizeof (BITMAP), &bmp) == 0)
	{
		return -1;
	}

	//-------------------------------------------------------
	// Create memory source DC and select an original bitmap:
	//-------------------------------------------------------
	CDC memDCSrc;
	memDCSrc.CreateCompatibleDC (NULL);

	HBITMAP hOldBitmapSrc = (HBITMAP) memDCSrc.SelectObject (m_hbmImageWell);
	if (hOldBitmapSrc == NULL)
	{
		return -1;
	}

	//----------------------------------------------------------
	// Create a new bitmap compatibel with the source memory DC
	// (original bitmap SHOULD BE ALREADY SELECTED!):
	//----------------------------------------------------------
	HBITMAP hNewBitmap = (HBITMAP) ::CreateCompatibleBitmap (memDCSrc,
									bmp.bmWidth + m_sizeImage.cx,
									bmp.bmHeight);
	if (hNewBitmap == NULL)
	{
		memDCSrc.SelectObject (hOldBitmapSrc);
		return -1;
	}

	//------------------------------------------------------
	// Create memory destination DC and select a new bitmap:
	//------------------------------------------------------
	CDC memDCDst;
	memDCDst.CreateCompatibleDC (&memDCSrc);
	
	HBITMAP hOldBitmapDst = (HBITMAP) memDCDst.SelectObject (hNewBitmap);
	if (hOldBitmapDst == NULL)
	{
		memDCSrc.SelectObject (hOldBitmapSrc);
		::DeleteObject (hNewBitmap);
		return -1;
	}

	//-----------------------------
	// Copy original bitmap to new:
	//-----------------------------
	memDCDst.BitBlt (0, 0, bmp.bmWidth, bmp.bmHeight,
				&memDCSrc, 0, 0, SRCCOPY);
	
	//---------------------------------------
	// Select a new button image and copy it:
	//---------------------------------------
	if (memDCSrc.SelectObject (hbmp) == NULL)
	{
		memDCDst.SelectObject (hOldBitmapDst);
		memDCSrc.SelectObject (hOldBitmapSrc);

		::DeleteObject (hNewBitmap);
		return -1;
	}

	memDCDst.BitBlt (bmp.bmWidth, 0, m_sizeImage.cx, bmp.bmHeight,
				&memDCSrc, 0, 0, SRCCOPY);

	memDCDst.SelectObject (hOldBitmapDst);
	memDCSrc.SelectObject (hOldBitmapSrc);

	::DeleteObject (m_hbmImageWell);

	m_hbmImageWell = hNewBitmap;
	m_bModified = TRUE;

	UpdateCount ();
	return m_iCount - 1;
}
//*******************************************************************************
BOOL CBCGToolBarImages::UpdateImage (int iImage, HBITMAP hbmp)
{
	if (!m_bUserImagesList)	// Only user images can be edited!
	{
		return FALSE;
	}

	CWindowDC	dc (NULL);
	CBitmap 	bitmap;
	CDC 		memDCSrc;
	CDC 		memDCDst;

	memDCSrc.CreateCompatibleDC (&dc);
	memDCDst.CreateCompatibleDC (&dc);
	
	HBITMAP hOldBitmapDst = (HBITMAP) memDCDst.SelectObject (m_hbmImageWell);
	HBITMAP hOldBitmapSrc = (HBITMAP) memDCSrc.SelectObject (hbmp);

	memDCDst.BitBlt (m_sizeImage.cx * iImage, 0, m_sizeImage.cx, m_sizeImage.cy,
				&memDCSrc, 0, 0, SRCCOPY);

	memDCDst.SelectObject (hOldBitmapDst);
	memDCSrc.SelectObject (hOldBitmapSrc);

	m_bModified = TRUE;
	return TRUE;
}
//*******************************************************************************
BOOL CBCGToolBarImages::DeleteImage (int iImage)
{
	if (!m_bUserImagesList)	// Only user images can be edited!
	{
		return FALSE;
	}

	if (iImage < 0 || iImage >= GetCount ())	// Wrong index
	{
		return FALSE;
	}

	//-------------------------------
	// Get original bitmap attrbutes:
	//-------------------------------
	BITMAP bmp;
	if (::GetObject (m_hbmImageWell, sizeof (BITMAP), &bmp) == 0)
	{
		return -1;
	}

	//-------------------------------------------------------
	// Create memory source DC and select an original bitmap:
	//-------------------------------------------------------
	CDC memDCSrc;
	memDCSrc.CreateCompatibleDC (NULL);

	HBITMAP hOldBitmapSrc = (HBITMAP) memDCSrc.SelectObject (m_hbmImageWell);
	if (hOldBitmapSrc == NULL)
	{
		return -1;
	}

	//----------------------------------------------------------
	// Create a new bitmap compatibel with the source memory DC
	// (original bitmap SHOULD BE ALREADY SELECTED!):
	//----------------------------------------------------------
	HBITMAP hNewBitmap = (HBITMAP) ::CreateCompatibleBitmap (memDCSrc,
									bmp.bmWidth - m_sizeImage.cx,
									bmp.bmHeight);
	if (hNewBitmap == NULL)
	{
		memDCSrc.SelectObject (hOldBitmapSrc);
		return -1;
	}

	//------------------------------------------------------
	// Create memory destination DC and select a new bitmap:
	//------------------------------------------------------
	CDC memDCDst;
	memDCDst.CreateCompatibleDC (&memDCSrc);
	
	HBITMAP hOldBitmapDst = (HBITMAP) memDCDst.SelectObject (hNewBitmap);
	if (hOldBitmapDst == NULL)
	{
		memDCSrc.SelectObject (hOldBitmapSrc);
		::DeleteObject (hNewBitmap);
		return -1;
	}

	//-----------------------------
	// Copy original bitmap to new:
	//-----------------------------

	if (iImage != 0)
	{
		memDCDst.BitBlt (0, 0, 
					m_sizeImage.cx * iImage, bmp.bmHeight,
					&memDCSrc, 0, 0, SRCCOPY);
	}
	
	if (iImage != m_iCount - 1)
	{
		memDCDst.BitBlt (m_sizeImage.cx * iImage, 0, 
					bmp.bmWidth - (m_iCount - iImage - 1) * m_sizeImage.cx, bmp.bmHeight,
					&memDCSrc, 
					m_sizeImage.cx * (iImage + 1), 0, SRCCOPY);
	}

	memDCDst.SelectObject (hOldBitmapDst);
	memDCSrc.SelectObject (hOldBitmapSrc);

	::DeleteObject (m_hbmImageWell);

	m_hbmImageWell = hNewBitmap;
	m_bModified = TRUE;

	UpdateCount ();
	return FALSE;
}
//*******************************************************************************
COLORREF CBCGToolBarImages::MapToSysColor (COLORREF color, BOOL bUseRGBQUAD)
{
	struct COLORMAP
	{
		// use DWORD instead of RGBQUAD so we can compare two RGBQUADs easily
		DWORD rgbqFrom;
		int iSysColorTo;
	};
	static const COLORMAP sysColorMap[] =
	{
		// mapping from color in DIB to system color
		{ RGB_TO_RGBQUAD(0x00, 0x00, 0x00),  COLOR_BTNTEXT },       // black
		{ RGB_TO_RGBQUAD(0x80, 0x80, 0x80),  COLOR_BTNSHADOW },     // dark grey
		{ RGB_TO_RGBQUAD(0xC0, 0xC0, 0xC0),  COLOR_BTNFACE },       // bright grey
		{ RGB_TO_RGBQUAD(0xFF, 0xFF, 0xFF),  COLOR_BTNHIGHLIGHT }   // white
	};
	const int nMaps = 4;

	// look for matching RGBQUAD color in original
	for (int i = 0; i < nMaps; i++)
	{
		if (color == sysColorMap[i].rgbqFrom)
		{
			return bUseRGBQUAD ? 
				CLR_TO_RGBQUAD(::GetSysColor(sysColorMap[i].iSysColorTo)) :
				::GetSysColor(sysColorMap[i].iSysColorTo);
		}
	}

	return color;
}
//********************************************************************************
COLORREF CBCGToolBarImages::MapFromSysColor (COLORREF color, BOOL bUseRGBQUAD)
{
	struct COLORMAP
	{
		// use DWORD instead of RGBQUAD so we can compare two RGBQUADs easily
		DWORD rgbTo;
		int iSysColorFrom;
	};
	static const COLORMAP sysColorMap[] =
	{
		// mapping from color in DIB to system color
		{ RGB(0x00, 0x00, 0x00),  COLOR_BTNTEXT },       // black
		{ RGB(0x80, 0x80, 0x80),  COLOR_BTNSHADOW },     // dark grey
		{ RGB(0xC0, 0xC0, 0xC0),  COLOR_BTNFACE },       // bright grey
		{ RGB(0xFF, 0xFF, 0xFF),  COLOR_BTNHIGHLIGHT }   // white
	};
	const int nMaps = 4;

	// look for matching RGBQUAD color in original
	for (int i = 0; i < nMaps; i++)
	{
		COLORREF clrSystem = ::GetSysColor (sysColorMap[i].iSysColorFrom);

		if (bUseRGBQUAD)
		{
			if (color == CLR_TO_RGBQUAD (clrSystem))
			{
				return CLR_TO_RGBQUAD (sysColorMap[i].rgbTo);
			}
		}
		else
		{
			if (/*RGBQUAD_TO_CLR*/ (color) == clrSystem)
			{
				return sysColorMap[i].rgbTo;
			}
		}
	}

	return color;
}
//************************************************************************************
BOOL CBCGToolBarImages::Save (LPCSTR lpszBmpFileName)
{
	CString strFile = (lpszBmpFileName == NULL) ?
						m_strUDLPath : lpszBmpFileName;

	if (!m_bModified && strFile == m_strUDLPath)
	{
		return TRUE;
	}

	if (!m_bUserImagesList ||	// Only user-defined bitmaps can be saved!
		m_hbmImageWell == NULL)	// Not loaded yet!
	{
		return FALSE;
	}

	if (!WriteDIB (strFile, DDBToDIB (m_hbmImageWell, 0)))
	{
		return FALSE;
	}

	m_bModified = FALSE;
	return TRUE;
}
//************************************************************************************
static BOOL WriteDIB( LPCTSTR szFile, HANDLE hDIB)
{
	BITMAPFILEHEADER	hdr;
	LPBITMAPINFOHEADER	lpbi;

	if (!hDIB)
		return FALSE;

	CFile file;
	if( !file.Open( szFile, CFile::modeWrite|CFile::modeCreate) )
		return FALSE;

	lpbi = (LPBITMAPINFOHEADER)hDIB;

	int nColors = 1 << lpbi->biBitCount;

	// Fill in the fields of the file header 
	hdr.bfType		= ((WORD) ('M' << 8) | 'B');	// is always "BM"
	hdr.bfSize		= GlobalSize (hDIB) + sizeof( hdr );
	hdr.bfReserved1 	= 0;
	hdr.bfReserved2 	= 0;
	hdr.bfOffBits		= (DWORD) (sizeof( hdr ) + lpbi->biSize +
						nColors * sizeof(RGBQUAD));

	// Write the file header 
	file.Write( &hdr, sizeof(hdr) );

	// Write the DIB header and the bits 
	file.Write( lpbi, GlobalSize(hDIB) );

	return TRUE;
}
//********************************************************************************
static HANDLE DDBToDIB (HBITMAP bitmap, DWORD dwCompression) 
{
	BITMAP			bm;
	BITMAPINFOHEADER	bi;
	LPBITMAPINFOHEADER 	lpbi;
	DWORD			dwLen;
	HANDLE			hDIB;
	HANDLE			handle;
	HDC 			hDC;
	HPALETTE		hPal;

	// The function has no arg for bitfields
	if( dwCompression == BI_BITFIELDS )
		return NULL;

	hPal = (HPALETTE) GetStockObject(DEFAULT_PALETTE);

	// Get bitmap information
	::GetObject(bitmap, sizeof(bm),(LPSTR)&bm);

	// Initialize the bitmapinfoheader
	bi.biSize		= sizeof(BITMAPINFOHEADER);
	bi.biWidth		= bm.bmWidth;
	bi.biHeight 		= bm.bmHeight;
	bi.biPlanes 		= 1;
	bi.biBitCount		= bm.bmPlanes * bm.bmBitsPixel;
	bi.biCompression	= dwCompression;
	bi.biSizeImage		= 0;
	bi.biXPelsPerMeter	= 0;
	bi.biYPelsPerMeter	= 0;
	bi.biClrUsed		= 0;
	bi.biClrImportant	= 0;

	// Compute the size of the  infoheader and the color table
	int nColors = (1 << bi.biBitCount);
	if( nColors > 256 ) 
		nColors = 0;
	dwLen  = bi.biSize + nColors * sizeof(RGBQUAD);

	// We need a device context to get the DIB from
	hDC = ::CreateCompatibleDC (NULL);
	if (hDC == NULL)
	{
		return FALSE;
	}

	HBITMAP bmp = ::CreateBitmap (1, 1, 1, nColors, NULL);
	if (bmp == NULL)
	{
		::DeleteDC(hDC);
		return NULL;
	}

	HBITMAP hOldBitmap = (HBITMAP)::SelectObject (hDC, bmp);

	hPal = SelectPalette(hDC,hPal,FALSE);
	RealizePalette(hDC);

	// Allocate enough memory to hold bitmapinfoheader and color table
	hDIB = GlobalAlloc(GMEM_FIXED,dwLen);

	if (!hDIB){
		::SelectPalette(hDC,hPal,FALSE);
		::SelectObject (hDC, hOldBitmap);
		::DeleteObject (bmp);
		::DeleteDC(hDC);
		return NULL;
	}

	lpbi = (LPBITMAPINFOHEADER)hDIB;

	*lpbi = bi;

	// Call GetDIBits with a NULL lpBits param, so the device driver 
	// will calculate the biSizeImage field 
	GetDIBits(hDC, bitmap, 0L, (DWORD)bi.biHeight,
			(LPBYTE)NULL, (LPBITMAPINFO)lpbi, (DWORD)DIB_RGB_COLORS);

	bi = *lpbi;

	// If the driver did not fill in the biSizeImage field, then compute it
	// Each scan line of the image is aligned on a DWORD (32bit) boundary
	if (bi.biSizeImage == 0){
		bi.biSizeImage = ((((bi.biWidth * bi.biBitCount) + 31) & ~31) / 8) 
						* bi.biHeight;

		// If a compression scheme is used the result may infact be larger
		// Increase the size to account for this.
		if (dwCompression != BI_RGB)
			bi.biSizeImage = (bi.biSizeImage * 3) / 2;
	}

	// Realloc the buffer so that it can hold all the bits
	dwLen += bi.biSizeImage;
	if (handle = GlobalReAlloc(hDIB, dwLen, GMEM_MOVEABLE))
		hDIB = handle;
	else{
		GlobalFree(hDIB);

		// Reselect the original palette
		SelectPalette(hDC,hPal,FALSE);
		::SelectObject (hDC, hOldBitmap);
		::DeleteObject (bmp);
		::DeleteDC(hDC);
		return NULL;
	}

	// Get the bitmap bits
	lpbi = (LPBITMAPINFOHEADER)hDIB;

	// FINALLY get the DIB
	BOOL bGotBits = GetDIBits( hDC, bitmap,
				0L,				// Start scan line
				(DWORD)bi.biHeight,		// # of scan lines
				(LPBYTE)lpbi 			// address for bitmap bits
				+ (bi.biSize + nColors * sizeof(RGBQUAD)),
				(LPBITMAPINFO)lpbi,		// address of bitmapinfo
				(DWORD)DIB_RGB_COLORS);		// Use RGB for color table

	if( !bGotBits )
	{
		GlobalFree(hDIB);
		
		SelectPalette(hDC,hPal,FALSE);
		::SelectObject (hDC, hOldBitmap);
		::DeleteObject (bmp);
		::DeleteDC(hDC);
		return NULL;
	}

	// Convert color table to the standard 3-d colors:
	DWORD* pColorTable = (DWORD*)(((LPBYTE)lpbi) + (UINT) lpbi->biSize);
	for (int iColor = 0; iColor < nColors; iColor ++)
	{
		pColorTable[iColor] = CBCGToolBarImages::MapFromSysColor (pColorTable[iColor]);
	}

	SelectPalette(hDC,hPal,FALSE);
	::SelectObject (hDC, hOldBitmap);
	::DeleteObject (bmp);
	::DeleteDC(hDC);

	return hDIB;
}


/////////////////////////////////////////////////////////////////////////////
// CBCGToolBarImages diagnostics

#ifdef _DEBUG
void CBCGToolBarImages::AssertValid() const
{
	CObject::AssertValid();

	ASSERT(m_hbmImageWell != NULL);
}

void CBCGToolBarImages::Dump(CDumpContext& dc) const
{
	CObject::Dump(dc);

	dc << "\nm_uiResID = " << m_uiResID;
	dc << "\nm_bUserImagesList = " << m_bUserImagesList;
	dc << "\nm_sizeButton = " << m_sizeButton;
	dc << "\nm_sizeImage = " << m_sizeImage;

	if (m_bUserImagesList)
	{
		dc << "\nm_strUDLPath = " << m_strUDLPath;
	}

	if (dc.GetDepth() > 0)
	{
	}

	dc << "\n";
}

#endif
