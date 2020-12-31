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
// mrcbmpbtn.cpp : implementation file
// $Date:   04 Feb 1997 10:40:52  $
// $Revision:   1.0  $
// $Author:   MRC  $

#include "mrcstafx.h"
#include "mrcpriv.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

extern MRC_AUX_DATA afxData;

static HDC hDCGlyphs = NULL;        
static HDC hDCMono = NULL;
static HBRUSH hbrDither = NULL;

/////////////////////////////////////////////////////////////////////////////
// CMRCBitmapButton
IMPLEMENT_DYNAMIC(CMRCBitmapButton, CButton)

BEGIN_MESSAGE_MAP(CMRCBitmapButton, CButton)
	//{{AFX_MSG_MAP(CMRCBitmapButton)
	ON_WM_SYSCOLORCHANGE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// Raster Ops
#define ROP_DSPDxax  0x00E20746L
#define ROP_PSDPxax  0x00B8074AL



/////////////////////////////////////////////////////////////////////////////
// CMRCBitmapButton message handlers

//------------------------------------------------------------------------------------
CMRCBitmapButton::CMRCBitmapButton()
//------------------------------------------------------------------------------------
{
	m_hBitmap = NULL;
}


CMRCBitmapButton::~CMRCBitmapButton()
{
}


//----------------------------------------------------------------------------------------
BOOL CMRCBitmapButton::Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID)
//----------------------------------------------------------------------------------------
{
	dwStyle |= BS_OWNERDRAW;
	return CButton::Create(NULL, dwStyle, rect, pParentWnd, nID);
}


//----------------------------------------------------------------------------------------
BOOL CMRCBitmapButton::LoadBitmap(LPCTSTR lpszResource)
// Load the specified bitmap. Note this function is virtual, so you can override it,
// either to turn off the coloring, or change the way the bitmap is loaded.
//----------------------------------------------------------------------------------------
{
	if (m_hBitmap != NULL)
		::DeleteObject(m_hBitmap);

	m_hInst = AfxFindResourceHandle(lpszResource, RT_BITMAP);
	m_hRsrc = ::FindResource(m_hInst, lpszResource, RT_BITMAP);
	if (m_hRsrc == NULL)
	{
		TRACE("CMRCBitapButton failed to load bitmap\n");
		return FALSE;
	}

	m_hBitmap = LoadRecolorBitmap(m_hInst, m_hRsrc);

	BITMAP bm;
	::GetObject(m_hBitmap, sizeof(bm), &bm);	
 	m_sizeImage.cx = bm.bmWidth;
 	m_sizeImage.cy = bm.bmHeight;
	return TRUE;
}



//----------------------------------------------------------------------------------------
BOOL CMRCBitmapButton::AutoLoad(UINT nID, CWnd * pParent, BOOL bSetSize)
//----------------------------------------------------------------------------------------
{
	// first attach to the dialog control
	if (!SubclassDlgItem(nID, pParent))
		return FALSE;

	CString buttonName;
	GetWindowText(buttonName);
	ASSERT(!buttonName.IsEmpty());      // must provide a title

	if (!LoadBitmap(buttonName))
	{								  		
		return FALSE;
	}
	
	if (bSetSize == TRUE)
	{
		AutoSize();
	}
	return TRUE;
}


//----------------------------------------------------------------------------------------
BOOL CMRCBitmapButton::AutoSize()
// sets the size of the button to match the loaded bitmap
//----------------------------------------------------------------------------------------
{
	if (m_hBitmap == NULL) 
		return FALSE;
	SetWindowPos(NULL, 0, 0, m_sizeImage.cx + 6, m_sizeImage.cy + 6,
						SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOZORDER);		
	return TRUE;
}


//----------------------------------------------------------------------------------------
void DrawDisabled(CDC* pDC, CPoint pt, CSize sizeImage, HBITMAP hBitmap)
// draw a disabled bitmap 
// borrowed from old toolbar code in MFC
//----------------------------------------------------------------------------------------
{
	CDC monoDC;
	CBitmap bmp;

    // create a mono bitmap and select it into a DC compatible with that passed in
    // This DC is used to create the mask
    if(!monoDC.CreateCompatibleDC(pDC) ||
	   !bmp.CreateBitmap(sizeImage.cx, sizeImage.cy, 1, 1, NULL))
		return;

	CDC glyphDC;
    VERIFY(glyphDC.CreateCompatibleDC(NULL));
    HBITMAP hOldBitmap = (HBITMAP)::SelectObject(glyphDC.m_hDC, hBitmap);
    
    // Initialise to 0.
	CBitmap* pOldBmp = monoDC.SelectObject(&bmp);
	monoDC.PatBlt(0, 0, sizeImage.cx, sizeImage.cy, WHITENESS);
	
	// Create mask based on the button bitmap.
	glyphDC.SetBkColor(afxData.clrBtnFace);
	monoDC.BitBlt(0, 0, sizeImage.cx, sizeImage.cy, &glyphDC, 1, 1, SRCCOPY);

	glyphDC.SetBkColor(afxData.clrBtnHilite);
	monoDC.BitBlt(0, 0, sizeImage.cx, sizeImage.cy, &glyphDC, 1, 1, SRCPAINT);

    ::SelectObject(glyphDC.m_hDC, hOldBitmap);

    pDC->SetBkColor(RGB(255,255,255));      
	pDC->SetTextColor(0L);
    
    // Draw button highlight where there are zeros in the mask, but shifted
    // 1 pixel right and down
    HBRUSH OldBrush = (HBRUSH)::SelectObject(pDC->m_hDC, afxData.hbrBtnHilite);
	pDC->BitBlt(pt.x + 1, pt.y + 1, sizeImage.cx - 1, sizeImage.cy - 1, &monoDC, 0, 0, ROP_PSDPxax);

	// Draw button shadow where there are zero's in the mask, but at the specified position.
    // it's the difference between the two bitblt's that gives the idented effect 
    ::SelectObject(pDC->m_hDC, afxData.hbrBtnShadow);
	pDC->BitBlt(pt.x, pt.y, sizeImage.cx, sizeImage.cy, &monoDC, 0, 0, ROP_PSDPxax);

    ::SelectObject(pDC->m_hDC, OldBrush);
	monoDC.SelectObject(pOldBmp);
}


/*
//----------------------------------------------------------------------------------------
void DrawDisabled(CDC * pDC, CPoint pt, CSize sizeImage, HBITMAP hbmp)
//-----------------------------------------------------------------------------------------
{
    // stolen from old toolbar code....
    HDC hDCGlyphs = CreateCompatibleDC(NULL);
    HBITMAP hOldBitmap = (HBITMAP)::SelectObject(hDCGlyphs, hbmp);   // select bitmap into a DC

	BOOL bHilite = TRUE;
    BOOL bHiliteShadow = FALSE;
	// initalize whole area with 0's
	PatBlt(hDCMono, 0, 0, sizeImage.cx, sizeImage.cy, WHITENESS);

	// create mask based on color bitmap
	// convert this to 1's
	SetBkColor(hDCGlyphs, afxData.clrBtnFace);
	BitBlt(hDCMono, pt.x, pt.y, sizeImage.cx, sizeImage.cy, hDCGlyphs, 0 , 0, SRCCOPY);


	if (bHilite)        // TRUE
	{
		// convert this to 1's
		SetBkColor(hDCGlyphs, afxData.clrBtnHilite);

		// OR in the new 1's
		BitBlt(hDCMono, pt.x, pt.y, sizeImage.cx, sizeImage.cy, hDCGlyphs, 0, 0, SRCPAINT);

		//if (bHiliteShadow)      // FALSE...
		//	BitBlt(hDCMono, 1, 1, m_sizeButton.cx-3, m_sizeButton.cy-3,
		//		hDCMono, 0, 0, SRCAND);
	}

    ::BitBlt(pDC->m_hDC, pt.x, pt.y, sizeImage.cx, sizeImage.cy, hDCMono, 0, 0, SRCCOPY);

    ::DeleteDC(hDCGlyphs);
    return;

	pDC->SetTextColor(0L);                  // 0's in mono -> 0 (for ROP)
	pDC->SetBkColor((COLORREF)0x00FFFFFFL); // 1's in mono -> 1

	//if (nStyle & TBBS_DISABLED) // TRUE 
	//{
		// disabled - draw the hilighted shadow
		HGDIOBJ hbrOld = pDC->SelectObject(afxData.hbrBtnHilite);
		if (hbrOld != NULL)
		{
			// draw hilight color where we have 0's in the mask
			// BitBlt(pDC->m_hDC, x + 1, y + 1, m_sizeButton.cx - 2, m_sizeButton.cy - 2, hDCMono, 0, 0, ROP_PSDPxax);
			BitBlt(pDC->m_hDC, pt.x + 1, pt.y + 1, sizeImage.cx -2, sizeImage.cy - 2, hDCMono, 0, 0, ROP_PSDPxax);
			pDC->SelectObject(hbrOld);
		}
	//}

	//BLOCK: always draw the shadow
	{
		HGDIOBJ hbrOld = pDC->SelectObject(afxData.hbrBtnShadow);
		if (hbrOld != NULL)
		{
			// draw the shadow color where we have 0's in the mask
			//BitBlt(pDC->m_hDC, x, y, m_sizeButton.cx - 2, m_sizeButton.cy - 2, hDCMono, 0, 0, ROP_PSDPxax);
			BitBlt(pDC->m_hDC, pt.x, pt.y, sizeImage.cx -2, sizeImage.cy - 2, hDCMono, 0, 0, ROP_PSDPxax);
			pDC->SelectObject(hbrOld);
		}
	}

}
*/
    


//----------------------------------------------------------------------------------------
void CMRCBitmapButton::DrawItem(LPDRAWITEMSTRUCT lpDIS) 
//----------------------------------------------------------------------------------------
{
//	itemAction:
//		ODA_DRAWENTIRE
//		ODA_FOCUS
//		ODA_SELECT:	
//	itemState: ODS_DISABLED, ODS_FOCUS ODS_SELECTED (=down) 

	CRect rcClient;
	GetClientRect(&rcClient);
	m_sizeButton = rcClient.Size();
	int dx = m_sizeButton.cx;
	int dy = m_sizeButton.cy;

	CDC dc;
	dc.Attach(lpDIS->hDC);

	// interior grey
	dc.FillSolidRect(&rcClient, afxData.clrBtnFace);
	
	// determine offset of bitmap (centered within button)
	CPoint ptOffset;
	ptOffset.x = (dx - m_sizeImage.cx - 1) / 2;
	ptOffset.y = (dy - m_sizeImage.cy) / 2;

	if (lpDIS->itemState & ODS_SELECTED)
	{
		// pressed in or checked
		dc.Draw3dRect(0, 0, dx, dy,
			afxData.bWin4 ? afxData.clrWindowFrame : afxData.clrBtnShadow,
			afxData.bWin4 ? afxData.clrBtnHilite : afxData.clrBtnFace);

		if (afxData.bWin4)
		{
			dc.Draw3dRect(1, 1, dx - 2, dy - 2,
				afxData.clrBtnShadow, afxData.clrBtnFace);
		}

		// for any depressed button, add one to the offsets.
		ptOffset.x += 1;
		ptOffset.y += 1;
	}
	else
	{
        // regular button look
		dc.Draw3dRect(0, 0, dx, dy, afxData.clrBtnHilite,
			afxData.bWin4 ? afxData.clrWindowFrame : afxData.clrBtnShadow);
		dc.Draw3dRect(1, 1, dx - 2, dy - 2,
			afxData.clrBtnFace, afxData.clrBtnShadow);
	}

	// create bitmap for item
    if (lpDIS->itemState & ODS_DISABLED)
    {
        //dc.SelectObject(CBitmap::FromHandle(m_hBitmap));
        DrawDisabled(&dc, ptOffset, m_sizeImage, m_hBitmap);
        //DrawDisabled(&dc, ptOffset, m_sizeImage, m_hBitmap);
        //dc.DrawState(ptOffset, m_sizeImage, CBitmap::FromHandle(m_hBitmap), DSS_UNION);       
    }
    else
    {
        CDC SrcDC;
		SrcDC.CreateCompatibleDC(&dc);
		SrcDC.SelectObject(CBitmap::FromHandle(m_hBitmap));

		// normal image version
		dc.BitBlt(ptOffset.x, ptOffset.y,
				m_sizeImage.cx, m_sizeImage.cy,
				&SrcDC,
				0 ,0, SRCCOPY);
	}

	// indicate focus by drawing a rectangle inside the button - done after the bitmap so it's
	// visible
	if (lpDIS->itemState & ODS_FOCUS)
	{
     	dc.SetBkColor(afxData.clrBtnFace);
   		CRect rect = rcClient;
		rect.InflateRect(-3,-3);
		dc.DrawFocusRect(&rect);
	}

	dc.Detach();

}


void CMRCBitmapButton::OnSysColorChange() 
{
	CButton::OnSysColorChange();
	
	if (m_hBitmap != NULL)
	{
		::DeleteObject(m_hBitmap);
		m_hBitmap = LoadRecolorBitmap(m_hInst, m_hRsrc);
	}
}



// routine to handle recoloring of bitmaps to fit standard colors. This really just the
// code from MFC, with the addition that you can specify your own color table mapping, and 
// it'll handle 256-color as well as 16-color bitmaps 
// Hey, why write your own routines from scratch, when Microsoft have provided a ready-working
// one for you ?

#ifndef _MAC
#define RGB_TO_RGBQUAD(r,g,b)   (RGB(b,g,r))
#define CLR_TO_RGBQUAD(clr)     (RGB(GetBValue(clr), GetGValue(clr), GetRValue(clr)))
#else
#define RGB_TO_RGBQUAD(r,g,b)   (RGB(r,g,b) << 8)
#define CLR_TO_RGBQUAD(clr)     (clr << 8)
#endif

//-----------------------------------------------------------------------------
HBITMAP LoadRecolorBitmap(LPCTSTR lpszResourceName, const BITMAPCOLORMAP * pColorMap, int nMaps)
//-----------------------------------------------------------------------------
{
	HINSTANCE hInst = AfxFindResourceHandle(lpszResourceName, RT_BITMAP);
	HRSRC hRsrc = ::FindResource(hInst, lpszResourceName, RT_BITMAP);
	if (hRsrc == NULL)
		return NULL;
	return LoadRecolorBitmap(hInst, hRsrc, pColorMap, nMaps);

}	


//-----------------------------------------------------------------------------
HBITMAP LoadRecolorBitmap(UINT nID, const BITMAPCOLORMAP * pColorMap, int nMaps)
//-----------------------------------------------------------------------------
{ 
	return LoadRecolorBitmap(MAKEINTRESOURCE(nID), pColorMap, nMaps);
}


//-----------------------------------------------------------------------------
HBITMAP LoadRecolorBitmap(HINSTANCE hInst, HRSRC hRsrc, const BITMAPCOLORMAP * pColorMap, int nMaps)
// Create a bitmap with a modified color table. This routine only handles 16-color bitmaps
//-----------------------------------------------------------------------------
{
	ASSERT(hRsrc != NULL);

	// system color maps (same as MFC uses for toolbars, if user doesn't specify one)
	static const BITMAPCOLORMAP sysColorMap[] =
	{
		// mapping from color in DIB to system color
		{ RGB_TO_RGBQUAD(0x00, 0x00, 0x00),  COLOR_BTNTEXT },       // black
		{ RGB_TO_RGBQUAD(0x80, 0x80, 0x80),  COLOR_BTNSHADOW },     // dark grey
		{ RGB_TO_RGBQUAD(0xC0, 0xC0, 0xC0),  COLOR_BTNFACE },       // bright grey
		{ RGB_TO_RGBQUAD(0xFF, 0xFF, 0xFF),  COLOR_BTNHIGHLIGHT }   // white
	};
	
	if (pColorMap == NULL)
	{
		pColorMap = sysColorMap;
		nMaps = 4;
	}

	HGLOBAL hglb;
	if ((hglb = ::LoadResource(hInst, hRsrc)) == NULL)
		return NULL;

	LPBITMAPINFOHEADER lpBitmap = (LPBITMAPINFOHEADER)LockResource(hglb);
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
	DWORD* pColorTable =
		(DWORD*)(((LPBYTE)lpBitmapInfo) + (UINT)lpBitmapInfo->biSize);

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

	int nWidth = (int)lpBitmapInfo->biWidth;
	int nHeight = (int)lpBitmapInfo->biHeight;
	HBITMAP hbm = ::CreateCompatibleBitmap(hDCScreen, nWidth, nHeight);
	::ReleaseDC(NULL, hDCScreen);
	if (hbm != NULL)
	{
		HDC hDCGlyphs = CreateCompatibleDC(NULL);
	
		HBITMAP hbmOld = (HBITMAP)::SelectObject(hDCGlyphs, hbm);

		LPBYTE lpBits;
		lpBits = (LPBYTE)(lpBitmap + 1);
		lpBits += (1 << (lpBitmapInfo->biBitCount)) * sizeof(RGBQUAD);

		StretchDIBits(hDCGlyphs, 0, 0, nWidth, nHeight, 0, 0, nWidth, nHeight,
			lpBits, (LPBITMAPINFO)lpBitmapInfo, DIB_RGB_COLORS, SRCCOPY);
		SelectObject(hDCGlyphs, hbmOld);
	   ::DeleteDC(hDCGlyphs);
	}
	
	// free copy of bitmap info struct and resource itself
	::free(lpBitmapInfo);
	::FreeResource(hglb);

	return hbm;
}

