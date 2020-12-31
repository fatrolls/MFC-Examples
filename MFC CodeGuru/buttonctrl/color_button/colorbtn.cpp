/////////////////////////////////////////////////////////////////////////////
// colorBtn.cpp : implementation file for the CColorButton class
//
// Written by Bob Ryan (ryan@cyberzone.net)
// Copyright (c) 1998.
//
// This code may be freely distributable in any application.  If
// you make any changes to the source, please let me know so that
// I might make a better version of the class.
//
// This file is provided "as is" with no expressed or implied warranty.
// The author accepts no liability for any damage/loss of business that
// this product may cause.
//
/////////////////////////////////////////////////////////////////////////////


#include "stdafx.h"
#include "colorbtn.h"
  
#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

// no automatic class substitution for this file!
#ifdef CColorButton
#undef CColorButton      CColorButton
#endif

// CColorButton
IMPLEMENT_DYNAMIC(CColorButton, CButton)

CColorButton::CColorButton() 
{  
#if (_MFC_VER < 0x0250)
  hwndOwner = NULL;  // initialize hwndOwner for GetOwner() and SetOwner() support in MFC < 2.5
#endif 
} 



CColorButton::~CColorButton()
{
} 



BOOL CColorButton::Attach(const UINT nID, CWnd* pParent, const COLORREF BGColor, const COLORREF FGColor, const COLORREF DisabledColor, const UINT nBevel)
{
	if (!SubclassDlgItem(nID, pParent))
		return FALSE;

	m_fg = FGColor;
	m_bg = BGColor; 
	m_disabled = DisabledColor;
	m_bevel = nBevel;

	return TRUE;
} 


void CColorButton::DrawItem(LPDRAWITEMSTRUCT lpDIS)
{
	CDC* pDC = CDC::FromHandle(lpDIS->hDC);

	UINT state = lpDIS->itemState; 
	CRect focusRect, btnRect;
	focusRect.CopyRect(&lpDIS->rcItem); 
	btnRect.CopyRect(&lpDIS->rcItem); 

	//
	// Set the focus rectangle to just past the border decoration
	//
	focusRect.left += 4;
    focusRect.right -= 4;
    focusRect.top += 4;
    focusRect.bottom -= 4;
      
	//
	// Retrieve the button's caption
	//
    const int bufSize = 512;
    TCHAR buffer[bufSize];
    GetWindowText(buffer, bufSize);
	

	//
	// Draw and label the button using draw methods 
	//
    DrawFilledRect(pDC, btnRect, GetBGColor()); 
    DrawFrame(pDC, btnRect, GetBevel());
  	DrawButtonText(pDC, btnRect, buffer, GetFGColor());


	//
	// Now, depending upon the state, redraw the button (down image) if it is selected,
	// place a focus rectangle on it, or redisplay the caption if it is disabled
	//
	if (state & ODS_FOCUS) {
		DrawFocusRect(lpDIS->hDC, (LPRECT)&focusRect);
		if (state & ODS_SELECTED){ 
    		DrawFilledRect(pDC, btnRect, GetBGColor()); 
    		DrawFrame(pDC, btnRect, -1);
  			DrawButtonText(pDC, btnRect, buffer, GetFGColor());
			DrawFocusRect(lpDIS->hDC, (LPRECT)&focusRect);
		}
	}
	else if (state & ODS_DISABLED) {
    	//COLORREF disabledColor = bg ^ 0xFFFFFF; // contrasting color
  		DrawButtonText(pDC, btnRect, buffer, GetDisabledColor());
    }
} 


void CColorButton::DrawFrame(CDC *DC, CRect R, int Inset)
{ 
	COLORREF dark, light, tlColor, brColor;
	int i, m, width;
	width = (Inset < 0)? -Inset : Inset;
	
	for (i = 0; i < width; i += 1) {
		m = 255 / (i + 2);
		dark = PALETTERGB(m, m, m);
		m = 192 + (63 / (i + 1));
		light = PALETTERGB(m, m, m);
		  
	  	if ( width == 1 ) {
			light = RGB(255, 255, 255);
			dark = RGB(128, 128, 128);
		}
		
		if ( Inset < 0 ) {
			tlColor = dark;
			brColor = light;
		}
		else {
			tlColor = light;
			brColor = dark;
		}
		
		DrawLine(DC, R.left, R.top, R.right, R.top, tlColor);							// Across top
		DrawLine(DC, R.left, R.top, R.left, R.bottom, tlColor);							// Down left
	  
		if ( (Inset < 0) && (i == width - 1) && (width > 1) ) {
			DrawLine(DC, R.left + 1, R.bottom - 1, R.right, R.bottom - 1, RGB(1, 1, 1));// Across bottom
			DrawLine(DC, R.right - 1, R.top + 1, R.right - 1, R.bottom, RGB(1, 1, 1));	// Down right
		}
	  	else {
			DrawLine(DC, R.left + 1, R.bottom - 1, R.right, R.bottom - 1, brColor);		// Across bottom
			DrawLine(DC, R.right - 1, R.top + 1, R.right - 1, R.bottom, brColor);		// Down right
		}
	  	InflateRect(R, -1, -1);
	}
}



void CColorButton::DrawFilledRect(CDC *DC, CRect R, COLORREF color)
{ 
	CBrush B;
	B.CreateSolidBrush(color);
	DC->FillRect(R, &B);
}
 

void CColorButton::DrawLine(CDC *DC, CRect EndPoints, COLORREF color)
{ 
	CPen newPen;
	newPen.CreatePen(PS_SOLID, 1, color);
	CPen *oldPen = DC->SelectObject(&newPen);
	DC->MoveTo(EndPoints.left, EndPoints.top);
	DC->LineTo(EndPoints.right, EndPoints.bottom);
	DC->SelectObject(oldPen);
    newPen.DeleteObject();
}

void CColorButton::DrawLine(CDC *DC, long left, long top, long right, long bottom, COLORREF color)
{ 
	CPen newPen;
	newPen.CreatePen(PS_SOLID, 1, color);
	CPen *oldPen = DC->SelectObject(&newPen);
	DC->MoveTo(left, top);
	DC->LineTo(right, bottom);
	DC->SelectObject(oldPen);
    newPen.DeleteObject();
}


void CColorButton::DrawButtonText(CDC *DC, CRect R, const char *Buf, COLORREF TextColor)
{
    COLORREF prevColor = DC->SetTextColor(TextColor);
    DC->SetBkMode(TRANSPARENT);
	DC->DrawText(Buf, strlen(Buf), R, DT_CENTER|DT_VCENTER|DT_SINGLELINE);
	DC->SetTextColor(prevColor);
}


		







