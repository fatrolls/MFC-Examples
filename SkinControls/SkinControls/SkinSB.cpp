
#include "stdafx.h"
#include "internal.h"
#include "SkinSB.h"
#include <assert.h>

static TCHAR g_szPropSB[] = TEXT("SkinScrollBar");

const int SBMETRICS::cxVArrow = 16;//GetSystemMetrics(SM_CXVSCROLL);
const int SBMETRICS::cyVArrow = 16;//GetSystemMetrics(SM_CYVSCROLL);
const int SBMETRICS::cxHArrow = 16;//GetSystemMetrics(SM_CXHSCROLL);
const int SBMETRICS::cyHArrow = 16;//GetSystemMetrics(SM_CYHSCROLL);
const int SBMETRICS::cxThumb  = 16;//GetSystemMetrics(SM_CXHTHUMB);
const int SBMETRICS::cyThumb  = 16;//GetSystemMetrics(SM_CYVTHUMB);


// Public interfaces

//----------------------------------------------------------
// Name : SkinSB_Init()
// Desc : Initialize the skin scrollbar library
//----------------------------------------------------------
BOOL WINAPI SkinSB_InitH(HWND hwnd, HBITMAP hBmp)
{
	LPSKINSB psb;
	DWORD    dwStyle;

	if( !IsWindow(hwnd) ) {
		SetLastError(ERROR_INVALID_HANDLE);
		return FALSE;
	}

	if( SkinSB_IsValid(hwnd) )
		return FALSE;

	// Allocates memory
	psb = (LPSKINSB)LocalAlloc(LPTR, sizeof(SKINSB));
	if( psb == NULL )
		return FALSE;

	ZeroMemory(psb, sizeof(SKINSB));

	dwStyle = GetWindowLong(hwnd, GWL_STYLE);

	psb->Horz.cbSize = psb->Vert.cbSize = sizeof(SCROLLINFO);
	psb->Horz.fMask  = psb->Vert.fMask  = SIF_ALL|SIF_DISABLENOSCROLL;

	if( dwStyle & WS_HSCROLL )
		GetScrollInfo(hwnd, SB_HORZ, &psb->Horz);

	if( dwStyle & WS_VSCROLL )
		GetScrollInfo(hwnd, SB_VERT, &psb->Vert);


	// Is left scrollbar style
	if( GetWindowLong(hwnd, GWL_EXSTYLE) & WS_EX_LEFTSCROLLBAR )
		psb->fLeftScrollBar = TRUE;

	if( !hBmp ) {
		SetLastError(ERROR_INVALID_HANDLE);
		return FALSE;
	}

	psb->hBmp = hBmp;

	// Replace the window procedure
	psb->hwnd = hwnd;
	psb->pfnOldProc = (WNDPROC)(LONG_PTR)SetWindowLong(hwnd, 
		GWL_WNDPROC, (LONG)(LONG_PTR)SkinSB_Proc);

	psb->fPreventStyleChange = FALSE;
	psb->fTracking = FALSE;

	// Whether richedit control
	TCHAR szClassName[255] = { 0 };
	GetClassName(hwnd, szClassName, sizeof(szClassName));
	if( lstrcmpi(szClassName, TEXT("RichEdit20A")) == 0 ||
		lstrcmpi(szClassName, TEXT("RichEdit20W")) == 0 ) {
			psb->fRichEdit = TRUE;
		}

		// Set the window property 
		if( !SetProp(hwnd, g_szPropSB, (HANDLE)psb) )
			return FALSE;

		// Redraw the window noclient
		RedrawFrame(hwnd);

		return TRUE;
}

//----------------------------------------------------------------
// Name : SkinSB_Init()
// Desc : Initialize and load the scrollbar skin
//----------------------------------------------------------------
BOOL WINAPI SkinSB_Init(HWND hwnd, LPCTSTR pszFileName)
{
	LPSKINSB psb;
	DWORD    dwStyle;

	if( !IsWindow(hwnd) ) {
		SetLastError(ERROR_INVALID_HANDLE);
		return FALSE;
	}

	if( SkinSB_IsValid(hwnd) )
		return FALSE;

	// Allocates memory
	psb = (LPSKINSB)LocalAlloc(LPTR, sizeof(SKINSB));
	if( psb == NULL )
		return FALSE;

	ZeroMemory(psb, sizeof(SKINSB));

	dwStyle = GetWindowLong(hwnd, GWL_STYLE);

	psb->Horz.cbSize = psb->Vert.cbSize = sizeof(SCROLLINFO);
	psb->Horz.fMask  = psb->Vert.fMask  = SIF_ALL|SIF_DISABLENOSCROLL;

	if( dwStyle & WS_HSCROLL )
		GetScrollInfo(hwnd, SB_HORZ, &psb->Horz);

	if( dwStyle & WS_VSCROLL )
		GetScrollInfo(hwnd, SB_VERT, &psb->Vert);


	// Is left scrollbar style
	if( GetWindowLong(hwnd, GWL_EXSTYLE) & WS_EX_LEFTSCROLLBAR )
		psb->fLeftScrollBar = TRUE;

	if (pszFileName == NULL) return FALSE;

	HBITMAP hBmp = (HBITMAP)::LoadImage(AfxGetInstanceHandle(), pszFileName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE|LR_CREATEDIBSECTION);
	psb->hBmp = hBmp;

	// Replace the window procedure
	psb->hwnd = hwnd;
	psb->pfnOldProc = (WNDPROC)(LONG_PTR)SetWindowLong(hwnd, 
		GWL_WNDPROC, (LONG)(LONG_PTR)SkinSB_Proc);

	psb->fPreventStyleChange = FALSE;
	psb->fTracking = FALSE;

	// Whether richedit control
	TCHAR szClassName[255] = { 0 };
	GetClassName(hwnd, szClassName, sizeof(szClassName));
	if( lstrcmpi(szClassName, TEXT("RichEdit20A")) == 0 ||
		lstrcmpi(szClassName, TEXT("RichEdit20W")) == 0 ) {
			psb->fRichEdit = TRUE;
		}

		// Set the window property 
		if( !SetProp(hwnd, g_szPropSB, (HANDLE)psb) )
			return FALSE;

		// Redraw the window noclient
		RedrawFrame(hwnd);

		return TRUE;
}

//---------------------------------------------------------
// Name : SkinSB_Uninit()
// Desc : Finalize the skin scrollbar library
//---------------------------------------------------------
BOOL WINAPI SkinSB_Uninit(HWND hwnd)
{
	LPSKINSB    psb;
	SCROLLINFO  vsi;
	SCROLLINFO  hsi;
	BOOL        vValid, hValid;
	UINT        vFlags, hFlags;

	if( (psb = SkinSB_GetSB(hwnd)) == NULL )
		return FALSE;

	vsi.cbSize = hsi.cbSize = sizeof(SCROLLINFO);
	vsi.fMask  = hsi.fMask = SIF_ALL | SIF_DISABLENOSCROLL;

	vValid = SkinSB_GetScrollInfo(hwnd, SB_VERT, &vsi);
	vFlags = SkinSB_GetDisableFlags(psb, TRUE);
	hValid = SkinSB_GetScrollInfo(hwnd, SB_HORZ, &hsi);
	hFlags = SkinSB_GetDisableFlags(psb, FALSE);

	// Remove the subclass procedure
	SetWindowLong(hwnd, GWL_WNDPROC, (LONG)(LONG_PTR)psb->pfnOldProc);
	RemoveProp(hwnd, g_szPropSB);
	LocalFree((HLOCAL)psb);


	// Restore system scroll parameters
	if( vValid ) {
		SetScrollInfo(hwnd, SB_VERT, &vsi, TRUE);
		EnableScrollBar(hwnd, SB_VERT, vFlags);
	}

	if( hValid ) {
		SetScrollInfo(hwnd, SB_HORZ, &hsi, TRUE);
		EnableScrollBar(hwnd, SB_HORZ, hFlags);
	}

	return TRUE;
}

//---------------------------------------------------------
// Name : SkinSB_IsValid()
// Desc : Is initialized ??
//---------------------------------------------------------
BOOL WINAPI SkinSB_IsValid(HWND hwnd)
{
	return (SkinSB_GetSB(hwnd) != NULL);
}


//---------------------------------------------------------
// Name : SkinSB_GetScrollInfo()
// Desc : Overload API GetScrollInfo()
//---------------------------------------------------------
BOOL WINAPI SkinSB_GetScrollInfo(HWND hwnd, int fnBar, LPSCROLLINFO lpsi)
{
	if( !lpsi || lpsi->cbSize != sizeof(SCROLLINFO) )
		return FALSE;

	LPSKINSB psb;
	LPSCROLLINFO psi = NULL;
	BOOL fCopied = FALSE;

	// Is initialized ?
	if( (psb = SkinSB_GetSB(hwnd)) == NULL )
		return FALSE;

	// If be scrollbar control then call failed
	if( fnBar == SB_HORZ )
		psi = &psb->Horz;
	else if( fnBar == SB_VERT )
		psi = &psb->Vert;
	else if( fnBar == SB_CTL ) 
		return FALSE;

	if( lpsi->fMask & SIF_PAGE ) {
		lpsi->nPage = psi->nPage;
		fCopied = TRUE;
	}

	if( lpsi->fMask & SIF_POS ) {
		lpsi->nPos  = psi->nPos;
		fCopied = TRUE;
	}

	if( lpsi->fMask & SIF_TRACKPOS ) {
		lpsi->nTrackPos = psi->nTrackPos;
		fCopied = TRUE;
	}

	if( lpsi->fMask & SIF_RANGE ) {
		lpsi->nMin = psi->nMin;
		lpsi->nMax = psi->nMax;
		fCopied = TRUE;
	}

	return fCopied;
}

//---------------------------------------------------------
// Name : SkinSB_SetScrollInfo()
// Desc : Overload API SetScrollInfo()
//---------------------------------------------------------
int WINAPI SkinSB_SetScrollInfo(HWND hwnd, int fnBar, LPCSCROLLINFO psi, BOOL fRedraw)
{
	LPSKINSB        psb;
	LPSCROLLINFO    mysi;
	int             nRet;
	DWORD           dwStyle;
	BOOL            fVert;
	UINT            wScroll;
	BOOL            fScroll;
	BOOL            fOldScroll;
	BOOL            bReturnOldPos;

	// if be scrollbar control the call failed
	if( fnBar == SB_CTL )
		return 0;

	if( (psb = SkinSB_GetSB(hwnd)) == NULL )
		return 0;

	if( fRedraw )
		fRedraw = IsWindowVisible(hwnd);

	fVert         = (fnBar == SB_VERT);
	bReturnOldPos = (psi->fMask & SIF_POS);
	dwStyle       = GetWindowLong(hwnd, GWL_STYLE);
	wScroll       = fVert ? WS_VSCROLL : WS_HSCROLL;

	fScroll = fOldScroll = (dwStyle & wScroll) ? TRUE : FALSE;

	// Don't do anything if we're setting position of a nonexistent scroll bar.
	if( !(psi->fMask & SIF_RANGE) && !fOldScroll )
		return 0;

	mysi = (fVert ? &psb->Vert : &psb->Horz);

	if( !SkinSB_SetSBParms(mysi, *psi, &fScroll, &nRet, bReturnOldPos) &&
		!(psi->fMask & SIF_DISABLENOSCROLL) ) {
			if( fOldScroll && fRedraw )
				goto redrawAfterSet;
			return nRet;
		}

		if( fScroll )
		{
			psb->style |= wScroll;
			dwStyle |= wScroll;
		}
		else
		{
			psb->style &= ~wScroll;
			dwStyle &= ~wScroll;
		}

		// Keep the owner window scroll style
		SetWindowLong(hwnd, GWL_STYLE, dwStyle);

		if( psi->fMask & SIF_DISABLENOSCROLL ) {
			if( fOldScroll ) {
				fScroll = ((int)mysi->nPage <= (mysi->nMax - mysi->nMin));
				psb->style |= wScroll;
				dwStyle |= wScroll;
				SetWindowLong(hwnd, GWL_STYLE, dwStyle);
				SkinSB_EnableArrows(psb, fnBar, fScroll ? ESB_ENABLE_BOTH : ESB_DISABLE_BOTH);
			}
		}
		else if( fOldScroll ^ fScroll ) {
			RedrawFrame(hwnd);
			return nRet;
		}

		if( fScroll && fRedraw ) {

redrawAfterSet:
			if(dwStyle & wScroll) {
				HDC hDC = GetWindowDC(hwnd);
				SkinSB_DrawThumb(psb, hDC, fVert, SkinSB_GetState(psb, fVert, HTSCROLL_THUMB));
				ReleaseDC(hwnd, hDC);
			}
			else {
				if( SkinSB_IsScrollInfoActive(psi) )
					RedrawFrame(hwnd);
			}
		}

		return mysi->nPos; //lres;
}


//---------------------------------------------------------
// Name : SkinSB_GetScrollPos()
// Desc : Overload API GetScrollPos()
//---------------------------------------------------------
int WINAPI SkinSB_GetScrollPos(HWND hwnd, int nBar)
{
	LPSKINSB psb;
	int nPos;
	if( !(psb = SkinSB_GetSB(hwnd)) )
		return FALSE;

	if( nBar == SB_HORZ )
		nPos = psb->Horz.nPos;
	else if( nBar == SB_VERT )
		nPos = psb->Vert.nPos;
	else
		nPos = 0;

	return nPos;
}


//---------------------------------------------------------
// Name : SkinSB_SetScrollPos()
// Desc : Overload API SetScrollPos()
//---------------------------------------------------------
int WINAPI SkinSB_SetScrollPos(HWND hwnd, int nBar, int nPos, BOOL fRedraw)
{
	LPSKINSB psb;
	LPSCROLLINFO psi;
	int nOldPos;

	if( (psb = SkinSB_GetSB(hwnd)) == NULL)
		return FALSE;

	if( nBar == SB_HORZ )
		psi = &psb->Horz;
	else if( nBar == SB_VERT )
		psi = &psb->Vert;
	else
		return FALSE;

	nOldPos = psi->nPos;
	psi->nPos = nPos;

	if( fRedraw ) {
		HDC hDC = GetWindowDC(hwnd);
		SkinSB_DrawScrollBar(psb, hDC, (nBar == SB_VERT) );
		ReleaseDC(hwnd, hDC);
	}

	return nOldPos;
}


//---------------------------------------------------------
// Name : SkinSB_GetScrollRange()
// Desc : Overload API GetScrollRange()
//---------------------------------------------------------
BOOL WINAPI SkinSB_GetScrollRange(HWND hwnd, int nBar, LPINT lpMinPos, LPINT lpMaxPos)
{
	LPSKINSB psb;
	LPSCROLLINFO psi;
	if( !lpMinPos || !lpMaxPos )
		return FALSE;

	if( nBar == SB_CTL )
		return FALSE;

	if( (psb = SkinSB_GetSB(hwnd)) == NULL )
		return FALSE;

	if( nBar == SB_HORZ )
		psi = &psb->Horz;
	else if( nBar == SB_VERT )
		psi = &psb->Vert;
	else
		return FALSE;

	*lpMinPos = psi->nMin;
	*lpMaxPos = psi->nMax;

	return TRUE;
}


//---------------------------------------------------------
// Name : SkinSB_SetScrollRange()
// Desc : Overload API SetScrollRange()
//---------------------------------------------------------
BOOL WINAPI SkinSB_SetScrollRange(HWND hwnd, int nBar, int nMinPos, int nMaxPos, BOOL fRedraw)
{
	LPSKINSB psb;
	LPSCROLLINFO psi;

	if( !(psb = SkinSB_GetSB(hwnd)) )
		return FALSE;

	if( nBar == SB_HORZ )
		psi = &psb->Horz;
	else if( nBar == SB_VERT )
		psi = &psb->Vert;
	else
		return FALSE;

	psi->nMin = nMinPos;
	psi->nMax = nMaxPos;

	if(nMinPos == 0 && nMaxPos == 0)
		SkinSB_ShowScrollBar(hwnd, nBar, FALSE);

	if( fRedraw ) {
		HDC hDC = GetWindowDC(hwnd);
		SkinSB_DrawScrollBar(psb, hDC, (nBar == SB_VERT) );
		ReleaseDC(hwnd, hDC);
	}

	return TRUE;
}


//---------------------------------------------------------
// Name : SkinSB_ShowScrollBar()
// Desc : Overload API ShowScrollBar()
//---------------------------------------------------------
BOOL WINAPI SkinSB_ShowScrollBar(HWND hwnd, int wBar, BOOL fShow)
{
	BOOL fChanged = FALSE;
	DWORD dwStyle, dwNew = 0;

	switch( wBar )
	{
	case SB_CTL:
		ShowWindow(hwnd, fShow ? SW_SHOW : SW_HIDE);
		break;
	case SB_HORZ:
		dwNew = WS_HSCROLL;
		break;
	case SB_VERT:
		dwNew = WS_VSCROLL;
		break;
	case SB_BOTH:
		dwNew = WS_HSCROLL | WS_VSCROLL;
		break;
	}

	dwStyle = GetWindowLong(hwnd, GWL_STYLE);
	if( !fShow ) {
		if( dwStyle & dwNew ) {
			fChanged = TRUE;
			dwStyle &= ~dwNew;
		}
	}
	else {
		if( (dwStyle & dwNew) != dwNew ) {
			fChanged = TRUE;
			dwStyle |= dwNew;
		}
	}

	if( fChanged ) {
		SetWindowLong(hwnd, GWL_STYLE, dwStyle);
		RedrawFrame(hwnd);
	}

	return TRUE;
}


//---------------------------------------------------------
// Name : SkinSB_EnableScrollBar()
// Desc : Overload API EnableScrollBar()
//---------------------------------------------------------
BOOL WINAPI SkinSB_EnableScrollBar(HWND hwnd, UINT wSBflags, UINT wArrows)
{
	LPSKINSB psb;
	if( !(psb = SkinSB_GetSB(hwnd)) )
		return FALSE;

	if( wSBflags == SB_CTL )
		return FALSE;

	return SkinSB_EnableArrows(psb, wSBflags, wArrows);
}

// Internal Function


//---------------------------------------------------------
// Name : SkinSB_SetSBParms()
// Desc : Set scroll parameters
//---------------------------------------------------------
BOOL SkinSB_SetSBParms(LPSCROLLINFO psi, SCROLLINFO si, BOOL* pfScroll, int* plres, BOOL bOldPos)
{
	BOOL fChanged = FALSE;
	if( bOldPos )
		*plres = psi->nPos;

	if( si.fMask & SIF_RANGE ) {
		if( si.nMax < si.nMin )
			si.nMax = si.nMin;

		if( si.nMax != psi->nMax || si.nMin != psi->nMin ) {
			psi->nMax = si.nMax;
			psi->nMin = si.nMin;

			if( !(si.fMask & SIF_PAGE) ) {
				si.fMask |= SIF_PAGE;
				si.nPage = psi->nPage;
			}

			if( !(si.fMask & SIF_POS) ) {
				si.fMask |= SIF_POS;
				si.nPos  = psi->nPos;
			}

			fChanged = TRUE;
		}
	}

	if( si.fMask & SIF_PAGE ) {
		UINT nMaxPage = abs( psi->nMax - psi->nMin ) + 1;
		if( si.nPage > nMaxPage )
			si.nPage = nMaxPage;

		if( psi->nPage != si.nPage ) {
			psi->nPage = si.nPage;

			if( !(si.fMask & SIF_POS) ) {
				si.fMask |= SIF_POS;
				si.nPos  = psi->nPos;
			}

			fChanged = TRUE;
		}
	}

	if( si.fMask & SIF_POS ) {
		int nMaxPos = psi->nMax - ((psi->nPage) ? psi->nPage - 1 : 0);
		if( si.nPos < psi->nMin )
			si.nPos = psi->nMin;
		else if( si.nPos > nMaxPos )
			si.nPos = nMaxPos;

		if( psi->nPos != si.nPos ) {
			psi->nPos = si.nPos;
			fChanged = TRUE;
		}
	}

	if( si.fMask & SIF_TRACKPOS ) {
		if( psi->nTrackPos != si.nTrackPos ) {
			psi->nTrackPos = si.nTrackPos;
			fChanged = TRUE;
		}
	}

	if( !bOldPos )
		*plres = psi->nPos; // Return the new pos

	if( si.fMask & SIF_RANGE ) {
		if( *pfScroll = (psi->nMin != psi->nMax) )
			goto CheckPage;
	}
	else if( si.fMask & SIF_PAGE ) {
CheckPage:
		*pfScroll = ( (int)psi->nPage <= (psi->nMax - psi->nMin) );
	}

	return fChanged;
}


//---------------------------------------------------------
// Name : SkinSB_EnableArrows()
// Desc : Enable or Disable scrollbar arrows
//---------------------------------------------------------
BOOL SkinSB_EnableArrows(LPSKINSB psb, int nBar, UINT wArrows)
{
	HDC hDC;
	UINT uOldFlags;
	BOOL bRetValue = FALSE;

	if( psb == NULL )
		return FALSE;

	uOldFlags = psb->flags;
	if( (hDC = GetWindowDC(psb->hwnd)) == NULL )
		return FALSE;

	// Enable or disable horizontal scrollbar
	if( nBar == SB_HORZ || nBar == SB_BOTH ) {
		if( wArrows == ESB_ENABLE_BOTH )
			psb->flags &= ~ESB_DISABLE_BOTH;
		else
			psb->flags |= wArrows;

		if( uOldFlags != psb->flags ) {
			bRetValue = TRUE;
			if( GetWindowLong(psb->hwnd, GWL_STYLE ) & WS_HSCROLL )
				SkinSB_DrawScrollBar(psb, hDC, FALSE);
		}
	}

	// Enable or disable vertical scrollbar
	if( nBar == SB_VERT || nBar == SB_BOTH ) {
		if( wArrows == ESB_ENABLE_BOTH )
			psb->flags &= ~(ESB_DISABLE_BOTH << 2);
		else
			psb->flags |= (wArrows << 2);

		if( uOldFlags != psb->flags ) {
			bRetValue = TRUE;
			if( GetWindowLong(psb->hwnd, GWL_STYLE ) & WS_VSCROLL )
				SkinSB_DrawScrollBar(psb, hDC, TRUE);
		}
	}

	ReleaseDC(psb->hwnd, hDC);

	return bRetValue;
}


//---------------------------------------------------------
// Name : SkinSB_GetDisableFlags()
// Desc : Get scrollbar disable flags
//---------------------------------------------------------
UINT SkinSB_GetDisableFlags(LPSKINSB psb, BOOL fVert)
{
	return (fVert ? (psb->flags & 0x000c) >> 2 : psb->flags & 0x0003); 
}

//---------------------------------------------------------
// Name : SkinSB_SetWindowBits()
// Desc :
//---------------------------------------------------------
void SkinSB_SetWindowBits(HWND hWnd, int iWhich, DWORD dwBits, DWORD dwValue)
{
	DWORD dwStyle;
	DWORD dwNewStyle;

	dwStyle = GetWindowLong(hWnd, iWhich);
	dwNewStyle = ( dwStyle & ~dwBits ) | (dwValue & dwBits);
	if (dwStyle != dwNewStyle) {
		SetWindowLong(hWnd, iWhich, dwNewStyle);
	}
}

//---------------------------------------------------------
// Name : SkinSB_GetSB()
// Desc : Get the skin scrollbar data structure
//---------------------------------------------------------
LPSKINSB SkinSB_GetSB(HWND hwnd)
{
	return (LPSKINSB)GetProp(hwnd, g_szPropSB);
}


//---------------------------------------------------------
// Name : SkinSB_IsScrollInfoActive()
// Desc : Check scroll information whether active
//---------------------------------------------------------
BOOL SkinSB_IsScrollInfoActive(LPCSCROLLINFO lpsi)
{
	if( (lpsi->nPage <= 0) || (lpsi->nMax <= lpsi->nMin) )
		return FALSE;
	else return TRUE;

	//TCHAR szText[255]={0};
	//sprintf_s(szText, sizeof(szText), "Page=%d Max=%d Min=%d Pos=%d\n", lpsi->nPage, lpsi->nMax, lpsi->nMin, lpsi->nPos);
	//OutputDebugString(szText);

	//return lpsi->nPage > 0 ? TRUE : FALSE;
}


//----------------------------------------------------------
// Name : SkinSB_GetSizeBoxRect()
// Desc : Get the size box rect
//----------------------------------------------------------
BOOL SkinSB_GetSizeBoxRect(LPSKINSB psb, LPRECT lprc)
{
	DWORD dwStyle;
	RECT  rect;

	SetRectEmpty(lprc);
	dwStyle = GetWindowLong(psb->hwnd, GWL_STYLE);
	if( (dwStyle & WS_HSCROLL) && (dwStyle & WS_VSCROLL) ) {
		GetClientRect(psb->hwnd, &rect);
		ClientToScreen(psb->hwnd, (LPPOINT)&rect);
		ClientToScreen(psb->hwnd, ((LPPOINT)&rect)+1);

		// calculate rect of  left scrollbar sizebox 
		if( psb->fLeftScrollBar ) {
			lprc->left = rect.left - SBMETRICS::cxVArrow;
			lprc->right = rect.left;
		}
		else {
			lprc->left = rect.right;
			lprc->right = rect.right + SBMETRICS::cxVArrow;
		}

		lprc->top   = rect.bottom;
		lprc->bottom = rect.bottom + SBMETRICS::cxHArrow;
		return TRUE;
	}

	return FALSE;
}


//----------------------------------------------------------
// Name : SkinSB_GetScrollBarRect()
// Desc : Get the scrollbar rect
//----------------------------------------------------------
BOOL SkinSB_GetScrollBarRect(LPSKINSB psb, BOOL fVert, LPRECT lprc)
{
	assert(psb && lprc);
	if( !psb || !lprc )
		return FALSE;

	RECT   rect;
	DWORD  dwStyle;

	SetRectEmpty(lprc);
	GetClientRect(psb->hwnd, &rect);
	ClientToScreen(psb->hwnd, (LPPOINT)&rect);
	ClientToScreen(psb->hwnd, ((LPPOINT)&rect)+1);

	dwStyle = GetWindowLong(psb->hwnd, GWL_STYLE);

	if( fVert ) {
		if( psb->fLeftScrollBar ) {
			lprc->right = lprc->left = rect.left;
			if( dwStyle & WS_VSCROLL )
				lprc->left -= SBMETRICS::cxThumb;
		}
		else {
			lprc->right = lprc->left = rect.right;
			if( dwStyle & WS_VSCROLL )
				lprc->right += SBMETRICS::cxThumb;
		}
		lprc->top = rect.top;
		lprc->bottom = rect.bottom;
	}
	else {
		lprc->top = lprc->bottom = rect.bottom;
		if( dwStyle & WS_HSCROLL )
			lprc->bottom += SBMETRICS::cyThumb;
		lprc->left = rect.left;
		lprc->right = rect.right;
	}

	return TRUE;
}


//----------------------------------------------------------
// Name : SkinSB_GetThumbRect()
// Desc :
//----------------------------------------------------------
BOOL SkinSB_GetThumbRect(LPSKINSB psb, LPRECT lprc, BOOL fVert)
{
	assert(psb && lprc);
	if( !psb || !lprc )
		return FALSE;
	SBCALC   sbc;
	RECT     rect;
	SkinSB_SBCalc(psb, &sbc, fVert);
	GetWindowRect(psb->hwnd, &rect);
	if( fVert )
		SetRect(lprc, sbc.pxLeft, sbc.pxThumbTop, sbc.pxRight, sbc.pxThumbBottom);
	else
		SetRect(lprc, sbc.pxThumbLeft, sbc.pxTop, sbc.pxThumbRight, sbc.pxBottom);

	OffsetRect(lprc, -rect.left, -rect.top);
	return TRUE;
}

//----------------------------------------------------------
// Name : SkinSB_GetGrooveRect()
// Desc :
//----------------------------------------------------------
BOOL SkinSB_GetGrooveRect(LPSKINSB psb, LPRECT lprc, BOOL fVert)
{
	assert(psb && lprc);
	if( !psb || !lprc )
		return FALSE;
	SBCALC   sbc;
	RECT     rect;
	SkinSB_SBCalc(psb, &sbc, fVert);
	GetWindowRect(psb->hwnd, &rect);
	if( fVert )
		SetRect(lprc, sbc.pxLeft, sbc.pxUpArrow, sbc.pxRight, sbc.pxDownArrow);
	else
		SetRect(lprc, sbc.pxUpArrow, sbc.pxTop, sbc.pxDownArrow, sbc.pxBottom);
	OffsetRect(lprc, -rect.left, -rect.top);
	return TRUE;
}


//----------------------------------------------------------
// Name : SkinSB_DrawSizeBox()
// Desc : Draw the size box
//----------------------------------------------------------

BOOL SkinSB_DrawSizeBox(LPSKINSB psb, HDC hdc)
{
	HDC     hMemDC;
	HBITMAP hOldBmp;

	RECT rect, rc;
	GetWindowRect(psb->hwnd, &rect);
	SkinSB_GetSizeBoxRect(psb, &rc);
	OffsetRect(&rc, -rect.left, -rect.top);

	hMemDC = CreateCompatibleDC(NULL);
	hOldBmp = (HBITMAP)SelectObject(hMemDC, psb->hBmp);
	BitBlt(hdc, rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top, hMemDC, (psb->fLeftScrollBar ? 16 : 0), 16 * 2, SRCCOPY);

	// Release GDI object
	SelectObject(hMemDC, hOldBmp);
	DeleteDC(hMemDC);

	return TRUE;
}


//----------------------------------------------------------
// Name : SkinSB_DrawGroove()
// Desc :
//----------------------------------------------------------
BOOL SkinSB_DrawGroove(LPSKINSB psb, HDC hdc, LPRECT lprc, BOOL fVert)
{
	if( !hdc || !lprc || IsRectEmpty(lprc) )
		return FALSE;

	HDC      hbmpDC;
	HBITMAP  hOldBmp;
	int      nMode;

	hbmpDC = CreateCompatibleDC(hdc);
	hOldBmp = (HBITMAP)SelectObject(hbmpDC, psb->hBmp);
	nMode = SetStretchBltMode(hdc, HALFTONE);

	StretchBlt(hdc, lprc->left, lprc->top, lprc->right - lprc->left, 
		lprc->bottom - lprc->top, hbmpDC, 16 * 14, (fVert ? 0 : 16), 16, 16, SRCCOPY);

	SetStretchBltMode(hdc, nMode);
	SelectObject(hbmpDC, hOldBmp);
	DeleteDC(hbmpDC);

	return TRUE;
}


//----------------------------------------------------------
// Name : SkinSB_DrawScrollBar()
// Desc : Draw the scrollbar
//----------------------------------------------------------
void SkinSB_DrawScrollBar(LPSKINSB psb, HDC hdc, BOOL fVert)
{
	RECT rcGroove;
	RECT rcThumb;
	int nSaveDC = 0;

	SkinSB_GetGrooveRect(psb, &rcGroove, fVert);
	SkinSB_GetThumbRect(psb, &rcThumb, fVert);

	if( (rcThumb.right > rcThumb.left) && (rcThumb.bottom > rcThumb.top) &&
		SkinSB_IsScrollInfoActive((fVert ? &psb->Vert : &psb->Horz))) {

			// Draw the thumb
			SkinSB_DrawThumb(psb, hdc, fVert, SkinSB_GetState(psb, fVert, HTSCROLL_THUMB));
			nSaveDC = SaveDC(hdc);
			ExcludeClipRect(hdc, rcThumb.left, rcThumb.top, rcThumb.right, rcThumb.bottom);
		}

		SkinSB_DrawGroove(psb, hdc, &rcGroove, fVert);
		if( nSaveDC != 0 )
			RestoreDC(hdc, nSaveDC);

		// Draw the arrow
		SkinSB_DrawArrow(psb, hdc, fVert, HTSCROLL_LINEUP, SkinSB_GetState(psb, fVert, HTSCROLL_LINEUP) );
		SkinSB_DrawArrow(psb, hdc, fVert, HTSCROLL_LINEDOWN, SkinSB_GetState(psb, fVert, HTSCROLL_LINEDOWN));
}


//----------------------------------------------------------
// Name : SkinSB_DrawArrow()
// Desc : Draw the scrollbar arrow button
//----------------------------------------------------------
BOOL SkinSB_DrawArrow(LPSKINSB psb, HDC hdc, BOOL fVert, int nArrow, UINT uState)
{
	RECT      	rect, rc;
	SBCALC    	sbc;
	HDC       	hMemDC;
	HBITMAP   	hOldBmp;
	int			xOffset = 0, yOffset = 0;

	GetWindowRect(psb->hwnd, &rect);
	SkinSB_SBCalc(psb, &sbc, fVert);

	if( uState == 0 )
		uState = SkinSB_GetState(psb, fVert, nArrow);

	hMemDC  = CreateCompatibleDC(hdc);
	hOldBmp = (HBITMAP)SelectObject(hMemDC, psb->hBmp);

	switch( nArrow )
	{
		// up or left arrow
	case HTSCROLL_LINEUP:
		if( fVert ) {
			xOffset = 16 * uState;
			yOffset = 0;
			SetRect(&rc, sbc.pxLeft, sbc.pxTop, sbc.pxRight, sbc.pxUpArrow);
		}
		else {
			xOffset = 16 * uState;
			yOffset = 16;
			SetRect(&rc, sbc.pxLeft, sbc.pxTop, sbc.pxUpArrow, sbc.pxBottom);
		}
		break;
		// right or down arrow
	case HTSCROLL_LINEDOWN:
		if( fVert ) {
			xOffset = 16 * (uState + 4);
			yOffset = 0;
			SetRect(&rc, sbc.pxLeft, sbc.pxDownArrow, sbc.pxRight, sbc.pxBottom);
		}
		else {
			xOffset = 16 * (uState + 4);
			yOffset = 16;
			SetRect(&rc, sbc.pxDownArrow, sbc.pxTop, sbc.pxRight, sbc.pxBottom);
		}
		break;
	default: assert(0);
	}

	OffsetRect(&rc, -rect.left, -rect.top);
	BitBlt(hdc, rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top, hMemDC, xOffset, yOffset, SRCCOPY);

	SelectObject(hMemDC, hOldBmp);
	DeleteDC(hMemDC);

	return TRUE;

}

//----------------------------------------------------------
// Name : SkinSB_DrawThumb()
// Desc : Draw the thumb
//----------------------------------------------------------
void SkinSB_DrawThumb(LPSKINSB psb, HDC hdc, BOOL fVert, UINT uState)
{
	SBCALC   	sbc;
	RECT     	rc, rect;
	HDC      	hSrcDC;
	HDC      	memDC;
	HBITMAP  	hOldBmp;
	HBITMAP  	hMemBitmap, hOldBitmap;
	int      	cx, cy;
	int			xOffset, yOffset;
	int			xOffset1, yOffset1;

	SkinSB_SBCalc(psb, &sbc, fVert);
	GetWindowRect(psb->hwnd, &rect);

	// Chack scrollbar of size whether valid
	if( (sbc.pxTop >= sbc.pxBottom) || (sbc.pxLeft >= sbc.pxRight) )
		return ;

	// Draw the groove only
	if( (sbc.pxDownArrow - sbc.pxUpArrow) < (sbc.pxThumbBottom - sbc.pxThumbTop) ||
		uState == SB_STATE_DISABLED ) {
			SkinSB_GetGrooveRect(psb, &rc, fVert);
			SkinSB_DrawGroove(psb, hdc, &rc, fVert);
			return ;
		}

		// Padding the groove part
		if( sbc.pxUpArrow < sbc.pxThumbTop ) {
			if( fVert )
				SetRect(&rc, sbc.pxLeft, sbc.pxUpArrow,  sbc.pxRight, sbc.pxThumbTop);
			else
				SetRect(&rc, sbc.pxUpArrow, sbc.pxTop, sbc.pxThumbTop, sbc.pxBottom);
			OffsetRect(&rc, -rect.left, -rect.top);
			SkinSB_DrawGroove(psb, hdc, &rc, fVert);
		}

		if( sbc.pxThumbBottom < sbc.pxDownArrow ) {
			if( fVert )
				SetRect(&rc, sbc.pxLeft, sbc.pxThumbBottom, sbc.pxRight, sbc.pxDownArrow);
			else
				SetRect(&rc, sbc.pxThumbBottom, sbc.pxTop, sbc.pxDownArrow, sbc.pxBottom);
			OffsetRect(&rc, -rect.left, -rect.top);
			SkinSB_DrawGroove(psb, hdc, &rc, fVert);
		}

		// Draw the thumb use memory dc

		// Select scrollbar bitmap resource to dc
		hSrcDC   = CreateCompatibleDC(hdc);
		hOldBmp  = (HBITMAP)SelectObject(hSrcDC, psb->hBmp);

		// get the thumb rectangle
		SkinSB_GetThumbRect(psb, &rc, fVert);
		cx = rc.right - rc.left;
		cy = rc.bottom - rc.top;
		RECT rcMemDC = {0, 0, rc.right-rc.left, rc.bottom-rc.top};

		// Create memory DC
		memDC = CreateCompatibleDC(hdc);
		hMemBitmap = CreateCompatibleBitmap(hdc, cx, cy);
		hOldBitmap = (HBITMAP)SelectObject(memDC, hMemBitmap);
		SetBkColor(memDC, RGB(255,255,255));
		ExtTextOut(memDC, 0, 0, ETO_OPAQUE, &rcMemDC, NULL, 0, NULL);

		// Select state bitmap part
		xOffset = 16 * (uState + 8);
		yOffset = (fVert ? 0 : 16);

		xOffset1 = 16 * (uState + 11);
		yOffset1 = (fVert ? 0 : 16);

		if ( fVert ) {
			for( int i = 4; i < cy - 4; i += 8 )
				BitBlt(memDC, 0,  i, cx, 8, hSrcDC, xOffset, yOffset + 4, SRCCOPY);

			BitBlt(memDC, 0, 0, cx, 4, hSrcDC, xOffset, yOffset, SRCCOPY);
			BitBlt(memDC, 0, cy - 4, cx, 4, hSrcDC, xOffset, (yOffset + 16) - 4, SRCCOPY);

			if( cy > 16 + 8 ) {
				int y = (cy - 16) / 2;
				BitBlt(memDC, 0, y, cx, 16, hSrcDC, xOffset1, yOffset1, SRCCOPY);
			}
		}
		else {
			for( int i = 4; i < cx - 4; i += 8 )
				BitBlt(memDC, i, 0, 8, cy, hSrcDC, xOffset + 4, yOffset, SRCCOPY);
			BitBlt(memDC, 0, 0, 4, cy, hSrcDC, xOffset, yOffset, SRCCOPY);
			BitBlt(memDC, cx - 4, 0, 4, cy, hSrcDC, (xOffset + 16) - 4, yOffset, SRCCOPY);


			if( cx > 16 + 8 ) {
				int x = (cx - 16) / 2;
				BitBlt(memDC, x, 0, 16, cy, hSrcDC, xOffset1, yOffset1, SRCCOPY);
			}
		}

		BitBlt(hdc, rc.left, rc.top, rc.right-rc.left, rc.bottom-rc.top, memDC, 0,0, SRCCOPY);

		// Release the memory DC
		SelectObject(memDC, hOldBitmap);
		DeleteDC(memDC);
		DeleteObject(hMemBitmap);

		SelectObject(hSrcDC, hOldBmp);
		DeleteDC(hSrcDC);
}

//----------------------------------------------------------
// Name : SkinSB_HitTest()
// Desc : HitTest scrollbar items
//----------------------------------------------------------
DWORD SkinSB_HitTest(LPSKINSB psb, BOOL fVert, POINT pt)
{
	SBCALC  sbc;
	UINT    disFlags;
	int     x;

	SkinSB_SBCalc(psb, &sbc, fVert);

	if( pt.x < sbc.pxLeft  || pt.y < sbc.pxTop || 
		pt.x > sbc.pxRight || pt.y > sbc.pxBottom )
		return HTSCROLL_NONE;

	disFlags = SkinSB_GetDisableFlags(psb, fVert);
	x = fVert ? pt.y : pt.x;

	if( x < sbc.pxUpArrow ) {
		if( (disFlags & ESB_DISABLE_BOTH) || (disFlags & ESB_DISABLE_LTUP) )
			return HTSCROLL_NONE;
		else
			return HTSCROLL_LINEUP;
	}
	else if( (x > sbc.pxUpArrow) && (x < sbc.pxThumbTop) ) {
		if( (disFlags & ESB_DISABLE_BOTH) || (disFlags & ESB_DISABLE_LTUP) )
			return HTSCROLL_NONE;
		else
			return HTSCROLL_PAGEUP;
	}
	else if( (x >= sbc.pxThumbTop && x <= sbc.pxThumbBottom) && 
		(sbc.pxThumbTop > 0 && sbc.pxThumbBottom > sbc.pxThumbTop) ) {
			return HTSCROLL_THUMB;
		}
	else if( (x > sbc.pxThumbBottom) && (x < sbc.pxDownArrow) ) {
		if( disFlags & ESB_DISABLE_BOTH || disFlags & ESB_DISABLE_RTDN )
			return HTSCROLL_NONE;
		else
			return HTSCROLL_PAGEDOWN;
	}
	else if( x >= sbc.pxDownArrow ) {
		if( (disFlags & ESB_DISABLE_BOTH) || (disFlags & ESB_DISABLE_RTDN) )
			return HTSCROLL_NONE;
		else
			return HTSCROLL_LINEDOWN;
	}

	return HTSCROLL_NONE;
}


//----------------------------------------------------------
// Name : SkinSB_SBCalc()
// Desc : Calc the scrollbar items position and size
//----------------------------------------------------------
void SkinSB_SBCalc(LPSKINSB psb, LPSBCALC lpcalc, BOOL fVert)
{
	assert(psb && lpcalc);
	if( psb == NULL || lpcalc == NULL )
		return;

	RECT        	rcBar;             // scrollbar rect
	int         	nRange;            // range of scrollbar
	int         	nWorkingsize;      // size of scrollbar working 
	int         	nArrowsize;        // size of the arrow button
	int         	nThumbsize;        // size of the thumb  
	int         	nStart;            // start position of the thumb  
	int         	nThumbpos;         // current position of the thumb 
	SCROLLINFO* 	psi;

	SkinSB_GetScrollBarRect(psb, fVert, &rcBar);

	lpcalc->pxLeft   = rcBar.left;
	lpcalc->pxTop    = rcBar.top;
	lpcalc->pxRight  = rcBar.right;
	lpcalc->pxBottom = rcBar.bottom;

	if( fVert ) {
		psi = &psb->Vert;
		nArrowsize   = SBMETRICS::cxVArrow;
		nWorkingsize = (rcBar.bottom - rcBar.top) - nArrowsize * 2;
		nStart = rcBar.top + nArrowsize;

		lpcalc->pxUpArrow = rcBar.top + nArrowsize;
		lpcalc->pxDownArrow = rcBar.bottom - nArrowsize;
	}
	else {
		psi = &psb->Horz;
		nArrowsize   = SBMETRICS::cxHArrow;
		nWorkingsize = (rcBar.right - rcBar.left) - nArrowsize * 2;
		nStart = rcBar.left + nArrowsize;

		lpcalc->pxUpArrow = rcBar.left + nArrowsize;
		lpcalc->pxDownArrow = rcBar.right - nArrowsize;
	}

	nRange = (psi->nMax - psi->nMin) + 1;
	// Calculate size of the thumb
	if( SkinSB_IsScrollInfoActive(psi) ) {
		nThumbsize = MulDiv(psi->nPage, nWorkingsize, nRange);
		if( nThumbsize < MIN_THUMB_SIZE )
			nThumbsize = MIN_THUMB_SIZE;
		int pagesize = max(1, psi->nPage);

		nThumbpos = MulDiv(psi->nPos - psi->nMin, nWorkingsize - nThumbsize, nRange - pagesize);

		if( nThumbpos < 0 )
			nThumbpos = 0;

		if( nThumbpos >= nWorkingsize - nThumbsize )
			nThumbpos =  nWorkingsize - nThumbsize;

		nThumbpos += nStart;
		lpcalc->pxThumbTop = nThumbpos;
		lpcalc->pxThumbBottom = nThumbpos + nThumbsize;
	}
	else {
		lpcalc->pxThumbTop = 0;
		lpcalc->pxThumbBottom = 0;
	}	
}

//---------------------------------------------------------
// Name : SkinSB_TrackThumb()
// Desc : Track the scroll thumb
//---------------------------------------------------------
BOOL SkinSB_TrackThumb(LPSKINSB psb, BOOL fVert, POINT pt)
{
	SBCALC        	sbclc;
	int           	nPos;
	int           	nThumbpos;
	int           	nRange;
	int           	nThumbsize;
	int           	nWorksize;
	LPSCROLLINFO  	psi;

	SkinSB_SBCalc(psb, &sbclc, fVert);

	if( fVert ) {
		psi = &psb->Vert;
		nThumbpos = pt.y -  psb->pxMouseOffset;
	}
	else {
		psi = &psb->Horz;
		nThumbpos = pt.x - psb->pxMouseOffset;
	}

	nPos       = 0;
	nThumbpos -= sbclc.pxUpArrow;
	nThumbsize = sbclc.pxThumbBottom - sbclc.pxThumbTop;
	nWorksize  = sbclc.pxDownArrow - sbclc.pxUpArrow;
	nRange     = (psi->nMax - psi->nMin) + 1;

	if( nThumbpos < 0 )
		nThumbpos = 0;
	if( nThumbpos > nWorksize - nThumbsize)
		nThumbpos = nWorksize - nThumbsize;

	if( nRange > 0 )
		nPos = MulDiv(nThumbpos, nRange - psi->nPage, nWorksize - nThumbsize);

	// Send the scroll message to window !!!
	if( psi->nPos != nPos ) {
		psi->nTrackPos = nPos;
		psb->nTrackPos = nPos;
		// NOTE: 2008-12-24
		// Not use the SB_THUMBTRACK flag that because of 
		// the RichEdit cannot receving the WM_MOUSEMOVE message
		if( psb->fRichEdit )
			DoScrollMsg(psb->hwnd, /*SB_THUMBTRACK*/SB_THUMBPOSITION, nPos, fVert);
		else
			DoScrollMsg(psb->hwnd, SB_THUMBTRACK, nPos, fVert);
	}

	return TRUE;
}



//---------------------------------------------------------
// Name : SkinSB_GetState()
// Desc : Get scrollbar item status
//---------------------------------------------------------
UINT SkinSB_GetState(LPSKINSB psb, BOOL fVert, UINT nHitItem)
{
	BOOL 	fHotTracked;
	BOOL 	fPressed;
	BOOL 	fDisabled;
	UINT 	disFlags;
	UINT 	uState;

	fHotTracked = fPressed = fDisabled = FALSE;

	disFlags = SkinSB_GetDisableFlags(psb, fVert);
	switch( nHitItem ) {
	case HTSCROLL_LINEUP:
		fDisabled = ((disFlags & ESB_DISABLE_BOTH) || (disFlags & ESB_DISABLE_UP));
		break;
	case HTSCROLL_LINEDOWN:
		fDisabled = ((disFlags & ESB_DISABLE_BOTH) || (disFlags & ESB_DISABLE_DOWN));
		break;
	case HTSCROLL_THUMB:
		fDisabled = (disFlags & ESB_DISABLE_BOTH);
		break;

	case HTSCROLL_PAGEUP:
	case HTSCROLL_PAGEDOWN:
	case HTSCROLL_SIZEBOX:
	case HTSCROLL_NONE:
		return 0;
	}

	if( (nHitItem == GET_HTITEM(psb->dwLastCode)) && fVert == (HTSCROLL_VERT == GET_HTVERT(psb->dwLastCode)) )
		fHotTracked = TRUE;

	if( !fDisabled && psb->fTracking && fHotTracked )
		fPressed = TRUE;

	if( fDisabled )
		uState = SB_STATE_DISABLED;
	else if( fPressed )
		uState = SB_STATE_SELECTED;
	else if( fHotTracked )
		uState = SB_STATE_HIGHLIGHT;
	else
		uState = SB_STATE_DEFAULT;

	return uState;
}

//----------------------------------------------------------
// Name : SkinSB_Track()
// Desc :
//----------------------------------------------------------
void SkinSB_Track(LPSKINSB psb, DWORD dwTrackCode, POINT pt)
{
	LPSCROLLINFO    psi;
	WORD            wSBCode;
	DWORD			dwTrackItem;
	BOOL			fTrackVert;

	dwTrackItem = GET_HTITEM(dwTrackCode);
	fTrackVert = GET_HTVERT(dwTrackCode);

	psi = (fTrackVert ? &psb->Vert : &psb->Horz);

	switch( dwTrackItem )
	{
	case HTSCROLL_THUMB:
		SBCALC sbclc;
		SkinSB_SBCalc(psb, &sbclc, fTrackVert);
		psi->nTrackPos    = psi->nPos;
		psb->pxMouseOffset = (fTrackVert ? pt.y : pt.x) - sbclc.pxThumbTop;
		break;

	case HTSCROLL_LINEUP:
		wSBCode = SB_LINEUP;
		goto DoScroll;

	case HTSCROLL_LINEDOWN:
		wSBCode = SB_LINEDOWN;
		goto DoScroll;

	case HTSCROLL_PAGEDOWN:
		wSBCode = SB_PAGEDOWN;
		goto DoScroll;

	case HTSCROLL_PAGEUP:
		wSBCode = SB_PAGEUP;
DoScroll:
		psb->nScrollTimerMsg = MAKELONG((fTrackVert ? WM_VSCROLL : WM_HSCROLL), wSBCode);
		DoScrollMsg(psb->hwnd, wSBCode, 0, fTrackVert);
		SetTimer(psb->hwnd, ID_TIMER_DELAY, TIME_SCROLL_DELAY, NULL);
		break;
	default: return;
	}

	psb->dwTrackCode = dwTrackCode;
	psb->fTracking   = TRUE;

	SkinSB_HotTrack(psb, psb->dwTrackCode, TRUE);
	SetCapture(psb->hwnd);

	//SkinSB_TrackLoop(psb);
}

/*
//----------------------------------------------------------
// Name : SkinSB_TrackLoop()
// Desc :
//----------------------------------------------------------
void SkinSB_TrackLoop(LPSKINSB psb)
{
HWND    hwnd;
MSG     msg;
int     cmd;
//POINT   pt;

if( !psb->fTracking )
return;
hwnd = psb->hwnd;
while( GetCapture() == hwnd )
{
if( !GetMessage(&msg, hwnd, 0, 0) )
break;

if( !CallMsgFilter(&msg, MSGF_SCROLLBAR) )
{
cmd = msg.message;

if( msg.hwnd == hwnd &&
((cmd >= WM_MOUSEFIRST && cmd <= WM_MOUSELAST) ||
(cmd >= WM_KEYFIRST && cmd <= WM_KEYLAST))
)
{
TRACE("message loop\n");
SkinSB_Proc(hwnd, cmd, msg.wParam, msg.lParam);
}
}
else
{
TranslateMessage(&msg);
DispatchMessage(&msg);
}
}
}*/

//----------------------------------------------------------
// Name : SkinSB_HotTrack()
// Desc : Hot scrollbar arrow and thumb items
//----------------------------------------------------------
BOOL SkinSB_HotTrack(LPSKINSB psb, DWORD dwTrackCode, BOOL fMouseDown)
{
	HDC  	hdc;
	DWORD 	dwOldCode;
	DWORD	dwHitItem;
	BOOL	fVert;

	// Save old hittest code
	dwOldCode = psb->dwLastCode;
	psb->dwLastCode = dwTrackCode;

	dwHitItem = GET_HTITEM(dwTrackCode);
	fVert = GET_HTVERT(dwTrackCode);

	hdc = GetWindowDC(psb->hwnd);
	if( dwTrackCode != dwOldCode || fMouseDown) {
		// Restore old scrollbar item state
		if( GET_HTITEM(dwOldCode) == HTSCROLL_LINEUP )
			SkinSB_DrawArrow(psb, hdc, GET_HTVERT(dwOldCode), HTSCROLL_LINEUP, SB_STATE_DEFAULT);
		else if( GET_HTITEM(dwOldCode) == HTSCROLL_LINEDOWN )
			SkinSB_DrawArrow(psb, hdc, GET_HTVERT(dwOldCode), HTSCROLL_LINEDOWN, SB_STATE_DEFAULT);
		else if( GET_HTITEM(dwOldCode) == HTSCROLL_THUMB )
			SkinSB_DrawThumb(psb, hdc, GET_HTVERT(dwOldCode), SB_STATE_DEFAULT);


		// Draw new scrollbar item state
		if( dwHitItem == HTSCROLL_LINEUP )
			SkinSB_DrawArrow(psb, hdc, fVert, HTSCROLL_LINEUP, fMouseDown ? SB_STATE_SELECTED : SB_STATE_HIGHLIGHT);
		else if( dwHitItem == HTSCROLL_LINEDOWN )
			SkinSB_DrawArrow(psb, hdc, fVert, HTSCROLL_LINEDOWN, fMouseDown ? SB_STATE_SELECTED : SB_STATE_HIGHLIGHT);
		else if( dwHitItem == HTSCROLL_THUMB)
			SkinSB_DrawThumb(psb, hdc, fVert, fMouseDown ? SB_STATE_SELECTED : SB_STATE_HIGHLIGHT);
	}

	ReleaseDC(psb->hwnd, hdc);

	return TRUE;
}

// Message handle

//----------------------------------------------------------
// Name : SkinSB_OnStyleChanged()
// Desc :
//----------------------------------------------------------
LRESULT SkinSB_OnStyleChanged(LPSKINSB psb, int nStyleType, LPSTYLESTRUCT lpStyleStruct)
{
	if( psb->fPreventStyleChange )
		return 0;

	if( nStyleType == GWL_EXSTYLE ) {
		BOOL fOld = psb->fLeftScrollBar;
		if( lpStyleStruct->styleNew & WS_EX_LEFTSCROLLBAR )
			psb->fLeftScrollBar = TRUE;
		else
			psb->fLeftScrollBar = FALSE;

		if( fOld != psb->fLeftScrollBar )
			RedrawFrame(psb->hwnd);
	}

	return CallWindowProc(psb->pfnOldProc, psb->hwnd, WM_STYLECHANGED, nStyleType, (LPARAM)lpStyleStruct);
}

//----------------------------------------------------------
// Name : SkinSB_OnNcCalcSize()
// Desc :
//----------------------------------------------------------
LRESULT SkinSB_OnNcCalcSize(LPSKINSB psb, BOOL bCalcValidRects, NCCALCSIZE_PARAMS* lpncsp)
{
	LRESULT   lr;
	DWORD     dwStyle;
	RECT*     lprc, rect;

	lprc = &lpncsp->rgrc[0];
	rect = *lprc;

	dwStyle = GetWindowLong(psb->hwnd, GWL_STYLE);

	if( dwStyle & (WS_VSCROLL | WS_HSCROLL) ) {
		psb->fPreventStyleChange = TRUE;
		SetWindowLong(psb->hwnd, GWL_STYLE, dwStyle & ~(WS_VSCROLL|WS_HSCROLL));
	}

	lr = CallWindowProc(psb->pfnOldProc, psb->hwnd, WM_NCCALCSIZE, (WPARAM)bCalcValidRects, (LPARAM)lpncsp);

	if( dwStyle & (WS_VSCROLL | WS_HSCROLL) ) {
		SetWindowLong(psb->hwnd, GWL_STYLE, dwStyle);
		psb->fPreventStyleChange = FALSE;
	}

	if( (dwStyle & WS_HSCROLL) && 
		(lprc->bottom - lprc->top) > SBMETRICS::cxHArrow ) {
			lprc->bottom -= SBMETRICS::cxHArrow;
		}

		if( (dwStyle & WS_VSCROLL) &&
			(lprc->right - lprc->left) > SBMETRICS::cxVArrow ) {
				if( psb->fLeftScrollBar )
					lprc->left += SBMETRICS::cxVArrow;
				else
					lprc->right -= SBMETRICS::cxVArrow;
			}
			return lr;
}

//----------------------------------------------------------
// Name : SkinSB_OnNcPaint()
// Desc :
//----------------------------------------------------------
LRESULT SkinSB_OnNcPaint(LPSKINSB psb, HRGN hRgn)
{
	LRESULT  lr;
	DWORD    dwStyle;
	HDC      hDC;

	if( !IsWindowVisible(psb->hwnd) )
		return 0;

	dwStyle = GetWindowLong(psb->hwnd, GWL_STYLE);
	if( dwStyle & (WS_VSCROLL | WS_HSCROLL) ) {
		psb->fPreventStyleChange = TRUE;
		SetWindowLong(psb->hwnd, GWL_STYLE, dwStyle & ~(WS_VSCROLL|WS_HSCROLL));
	}

	// draw frame border by system
	lr = CallWindowProc(psb->pfnOldProc, psb->hwnd, WM_NCPAINT, (WPARAM)hRgn, 0);

	if( dwStyle & (WS_VSCROLL | WS_HSCROLL) ) {
		SetWindowLong(psb->hwnd, GWL_STYLE, dwStyle);
		psb->fPreventStyleChange = FALSE;
	}

	//hDC = GetDCEx(psb->hwnd, hRgn, DCX_WINDOW|DCX_INTERSECTRGN|DCX_CACHE );
	hDC = GetWindowDC(psb->hwnd);

	// Draw scrollbar
	if( dwStyle & WS_VSCROLL )
		SkinSB_DrawScrollBar(psb, hDC, TRUE);

	if( dwStyle & WS_HSCROLL )
		SkinSB_DrawScrollBar(psb, hDC, FALSE);

	// draw the size box
	if( dwStyle & (WS_VSCROLL | WS_HSCROLL) )
		SkinSB_DrawSizeBox(psb, hDC);

	ReleaseDC(psb->hwnd, hDC);

	return lr;
}

//----------------------------------------------------------
// Name : SkinSB_OnNcHitTest()
// Desc :
//----------------------------------------------------------
LRESULT SkinSB_OnNcHitTest(LPSKINSB psb, WPARAM wParam, LPARAM lParam)
{

	RECT rcHorz, rcVert, rcSize;
	POINT pt = {LOWORD(lParam), HIWORD(lParam)};

	SkinSB_GetScrollBarRect(psb, TRUE, &rcVert);
	SkinSB_GetScrollBarRect(psb, FALSE, &rcHorz);
	SkinSB_GetSizeBoxRect(psb, &rcSize);

	if( PtInRect(&rcVert, pt) )
		return HTVSCROLL;
	else if( PtInRect(&rcHorz, pt) )
		return HTHSCROLL;
	else if( PtInRect(&rcSize, pt) )
		return HTSIZE;

	return CallWindowProc(psb->pfnOldProc, psb->hwnd, WM_NCHITTEST, wParam, lParam);
}


//----------------------------------------------------------
// Name : SkinSB_OnNcMouseMove()
// Desc :
//----------------------------------------------------------
LRESULT SkinSB_OnNcMouseMove(LPSKINSB psb, WPARAM wParam, LPARAM lParam)
{
	if( wParam == HTHSCROLL || wParam == HTVSCROLL ) {
		POINT pt;
		BOOL  fVert;
		DWORD dwHitCode;

		pt.x  = LOWORD(lParam); 
		pt.y  = HIWORD(lParam);
		fVert = ( wParam == HTVSCROLL );

		if( !SkinSB_IsScrollInfoActive((fVert ? &psb->Vert : &psb->Horz)) )
			return 0;

		dwHitCode  = SkinSB_HitTest(psb, fVert, pt);
		if( dwHitCode == HTSCROLL_NONE )
			return 0;

		if( fVert )
			dwHitCode |= HTSCROLL_VERT;

		SkinSB_HotTrack(psb, dwHitCode, FALSE);
	}
	else if( wParam == HTSIZE ) {
		SkinSB_HotTrack(psb, HTSCROLL_NONE, FALSE);
	}

	return CallWindowProc(psb->pfnOldProc, psb->hwnd, WM_NCMOUSEMOVE, wParam, lParam);
}

//---------------------------------------------------------
// Name : SkinSB_OnNcMouseLeave()
// Desc :
//---------------------------------------------------------
LRESULT SkinSB_OnNcMouseLeave(LPSKINSB psb, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(wParam);
	UNREFERENCED_PARAMETER(lParam);

	psb->fMouseTracking = FALSE;
	if( psb->fTracking )
		return 0;

	SkinSB_HotTrack(psb, HTSCROLL_NONE, FALSE);
	psb->dwLastCode = HTSCROLL_NONE;

	return 0;
}

//----------------------------------------------------------
// Name : SkinSB_OnNcLButtonDown()
// Desc :
//----------------------------------------------------------
LRESULT SkinSB_OnNcLButtonDown(LPSKINSB psb, WPARAM wParam, LPARAM lParam)
{
	if( wParam == HTHSCROLL || wParam == HTVSCROLL ) {
		POINT 			pt;
		BOOL  			fVert;
		DWORD   		dwHitCode;
		LPSCROLLINFO    psi;

		pt.x  = LOWORD(lParam);
		pt.y  = HIWORD(lParam);
		fVert = (wParam == HTVSCROLL);

		psi = (fVert ? &psb->Vert : &psb->Horz);

		if( !SkinSB_IsScrollInfoActive(psi) )
			return 0;

		dwHitCode = SkinSB_HitTest(psb, fVert, pt);
		if( dwHitCode == HTSCROLL_NONE )
			return 0;

		if( fVert )
			dwHitCode |= HTSCROLL_VERT;
		psb->nTrackPos = psi->nPos;
		psb->dwLastCode = dwHitCode;
		SkinSB_Track(psb, dwHitCode, pt);
		return 0;

	}
	return CallWindowProc(psb->pfnOldProc, psb->hwnd, WM_NCLBUTTONDOWN, wParam, lParam);
}

//----------------------------------------------------------
// Name : SkinSB_OnMouseMove()
// Desc :
//----------------------------------------------------------
LRESULT SkinSB_OnMouseMove(LPSKINSB psb, WPARAM wParam, LPARAM lParam)
{
	DWORD   	dwPos;
	POINT   	pt;
	dwPos = 	GetMessagePos();
	pt.x  = 	LOWORD(dwPos);
	pt.y  = 	HIWORD(dwPos);

	// Mouse left button down
	if( psb->fTracking && (wParam & MK_LBUTTON) ) {
		if( GET_HTITEM(psb->dwTrackCode) == HTSCROLL_THUMB ) {
			SkinSB_TrackThumb(psb, GET_HTVERT(psb->dwTrackCode), pt);
			return 0;
		}

		LRESULT lr = SkinSB_OnNcHitTest(psb, 0, dwPos);
		if( lr == HTHSCROLL || lr == HTVSCROLL ) {
			BOOL fVert = (lr == HTVSCROLL);
			DWORD dwHitCode = SkinSB_HitTest(psb, fVert, pt);
			if( fVert ) dwHitCode |= HTSCROLL_VERT; 

			if( dwHitCode != psb->dwTrackCode )
				// Unallowed hot-track other hittest item
				SkinSB_HotTrack(psb, HTSCROLL_NONE, FALSE);
			else
				SkinSB_HotTrack(psb, psb->dwTrackCode, TRUE);
		}
		else  {
			SkinSB_HotTrack(psb, HTSCROLL_NONE, FALSE);
		}
		return 0;
	}

	return CallWindowProc(psb->pfnOldProc, psb->hwnd, WM_MOUSEMOVE, wParam, lParam);
}

//----------------------------------------------------------
// Name : SkinSB_OnLButtonUp()
// Desc :
//----------------------------------------------------------
LRESULT SkinSB_OnLButtonUp(LPSKINSB psb, WPARAM wParam, LPARAM lParam)
{
	DWORD dwHitItem = GET_HTITEM(psb->dwTrackCode);
	BOOL fTrackVert = GET_HTVERT(psb->dwTrackCode);

	if( dwHitItem != HTSCROLL_NONE && psb->fTracking) {
		// Release mouse capture
		ReleaseCapture();

		// End scroll
		switch( dwHitItem )
		{
		case HTSCROLL_LINEUP:
		case HTSCROLL_LINEDOWN:
		case HTSCROLL_PAGEUP:
		case HTSCROLL_PAGEDOWN:
			KillTimer(psb->hwnd, ID_TIMER_SCROLL);
			DoScrollMsg(psb->hwnd, SB_ENDSCROLL, 0, fTrackVert);
			break;

		case HTSCROLL_THUMB:
			if( psb->fTracking ) {
				DWORD  dwPos;
				DWORD  dwCode;
				POINT  pt;
				dwPos = GetMessagePos();
				pt.x = LOWORD(dwPos);
				pt.y = HIWORD(dwPos);
				DoScrollMsg(psb->hwnd, SB_THUMBPOSITION, psb->nTrackPos, fTrackVert);
				DoScrollMsg(psb->hwnd, SB_ENDSCROLL, 0, fTrackVert);
				dwCode = SkinSB_HitTest(psb, fTrackVert, pt);
				if( fTrackVert ) dwCode |= HTSCROLL_VERT;
				psb->dwLastCode = dwCode;
			}
			break;
		}

		// Clean the track parameters
		psb->pxMouseOffset    = 0;
		psb->nScrollTimerMsg = MAKELONG(WM_NULL, 0);
		psb->dwTrackCode     = HTSCROLL_NONE;
		psb->fTracking       = FALSE;
		//psb->nTrackPos       = 0;

		HDC hdc = GetWindowDC(psb->hwnd);
		SkinSB_DrawScrollBar(psb, hdc, fTrackVert);
		ReleaseDC(psb->hwnd, hdc);

		return 0;
	}
	return CallWindowProc(psb->pfnOldProc, psb->hwnd, WM_LBUTTONUP, wParam, lParam);
}

//----------------------------------------------------------
// Name : SkinSB_OnTimer()
// Desc :
//----------------------------------------------------------
LRESULT SkinSB_OnTimer(LPSKINSB psb, WPARAM wParam, LPARAM lParam)
{
	DWORD dwHitItem = GET_HTITEM(psb->dwTrackCode);
	BOOL fTrackVert = GET_HTVERT(psb->dwTrackCode);


	if( wParam == ID_TIMER_SCROLL ) {
		// if mouse left button released then close scroll timer 
		if( dwHitItem == HTSCROLL_NONE ) {
			KillTimer(psb->hwnd, ID_TIMER_SCROLL);
			return 0;
		}

		// Timer send scroll message
		if( psb->dwTrackCode == psb->dwLastCode )
		{
			WORD wSBCode = HIWORD(psb->nScrollTimerMsg);
			if( wSBCode == SB_PAGEDOWN || wSBCode == SB_PAGEUP ) {
				SBCALC sbc;
				DWORD dwPos;
				POINT pt;
				int px;
				dwPos = GetMessagePos();
				pt.x = LOWORD(dwPos);
				pt.y = HIWORD(dwPos);

				SkinSB_SBCalc(psb, &sbc, fTrackVert);
				px = (fTrackVert ? pt.y : pt.x);

				if( wSBCode == SB_PAGEDOWN ) {
					if( sbc.pxThumbBottom >= px ) {
						KillTimer(psb->hwnd, ID_TIMER_SCROLL);
						return 0;
					}
				}
				else {
					if( sbc.pxThumbTop <= px ) {
						KillTimer(psb->hwnd, ID_TIMER_SCROLL);
						return 0;
					}
				}
			}

			DoScrollMsg(psb->hwnd, wSBCode, 0, fTrackVert);
		}
		return 0;
	}
	else if(wParam == ID_TIMER_DELAY) {
		KillTimer(psb->hwnd, ID_TIMER_DELAY);
		SetTimer(psb->hwnd, ID_TIMER_SCROLL, TIME_SCROLL_INTERVAL, 0);
		return 0;
	}
	return CallWindowProc(psb->pfnOldProc, psb->hwnd, WM_TIMER, wParam, lParam);
}


//----------------------------------------------------------
// Name : SkinSB_Proc()
// Desc :
//----------------------------------------------------------
LRESULT CALLBACK SkinSB_Proc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LPSKINSB psb = SkinSB_GetSB(hwnd);

	if( psb && uMsg == WM_NCMOUSEMOVE ) {
		if(!psb->fMouseTracking && !psb->fTracking) {
			TRACKMOUSEEVENT tme;
			tme.cbSize = sizeof(tme);
			tme.hwndTrack = psb->hwnd;
			tme.dwFlags = TME_LEAVE|TME_NONCLIENT;
			tme.dwHoverTime = 0;
			psb->fMouseTracking = _TrackMouseEvent(&tme);
		}
	}

	switch( uMsg )
	{
	case WM_NCPAINT:
		return SkinSB_OnNcPaint(psb, (HRGN)wParam);

	case WM_NCCALCSIZE:
		return SkinSB_OnNcCalcSize(psb, (BOOL)wParam, (NCCALCSIZE_PARAMS*)lParam);

	case WM_NCHITTEST:
		return SkinSB_OnNcHitTest(psb, wParam, lParam);

	case WM_STYLECHANGED:
		return SkinSB_OnStyleChanged(psb, (int)wParam, (LPSTYLESTRUCT)lParam);

	case WM_NCLBUTTONDOWN:
		return SkinSB_OnNcLButtonDown(psb, wParam, lParam);

	case WM_NCMOUSEMOVE:
		return SkinSB_OnNcMouseMove(psb, wParam, lParam);

	case WM_MOUSEMOVE:
		return SkinSB_OnMouseMove(psb, wParam, lParam);

	case WM_LBUTTONUP:
		return SkinSB_OnLButtonUp(psb, wParam, lParam);

	case WM_NCMOUSELEAVE:		
		return SkinSB_OnNcMouseLeave(psb, wParam, lParam);

	case WM_NCLBUTTONDBLCLK:
	case WM_NCRBUTTONDBLCLK:
		return 0;

	case WM_TIMER:
		return SkinSB_OnTimer(psb, wParam, lParam);

	case WM_NCDESTROY:
		{
			LRESULT lr = CallWindowProc(psb->pfnOldProc, hwnd, uMsg, wParam, lParam);
			SkinSB_Uninit(hwnd);
			return lr;
		}
	}
	return CallWindowProc(psb->pfnOldProc, hwnd, uMsg, wParam, lParam);
}