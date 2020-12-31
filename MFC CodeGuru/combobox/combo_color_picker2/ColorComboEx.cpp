// ColorComboEx.cpp : implementation file
//
// Eric Zimmerman coolez@one.net

#include "stdafx.h"
#include "ComobTest.h"
#include "ColorComboEx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CColorComboEx

CColorComboEx::CColorComboEx()
{
	// Add the colors to the array
	
	colors.Add(RGB(0, 0, 0));			// Black
	colors.Add(RGB(128, 0, 0));			// Dark Red
	colors.Add(RGB(0, 128, 0));			// Dark Green
	colors.Add(RGB(128, 128, 0));		// Dark Yellow
	colors.Add(RGB(0, 0, 128));			// Dark Blue
	colors.Add(RGB(128, 0, 128));		// Dark Magenta
	colors.Add(RGB(0, 128, 128));		// Dark Cyan	
	colors.Add(RGB(192, 192, 192));		// Light Grey
	colors.Add(RGB(128, 128, 128));		// Medium Grey
	colors.Add(RGB(255, 0, 0));			// Red
	colors.Add(RGB(0, 255, 0));			// Green
	colors.Add(RGB(255, 255, 0));		// Yellow
	colors.Add(RGB(0, 0, 255));			// Blue
	colors.Add(RGB(255, 0, 255));		// Magenta
	colors.Add(RGB(0, 255, 255));		// Cyan
	colors.Add(RGB(255, 255, 255));		// White
	colors.Add(::GetSysColor(COLOR_WINDOWTEXT));	// Automatic
}

CColorComboEx::~CColorComboEx()
{
}


BEGIN_MESSAGE_MAP(CColorComboEx, CComboBox)
	//{{AFX_MSG_MAP(CColorComboEx)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CColorComboEx message handlers

void CColorComboEx::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	// This function of course does all the work.
		
	CDC dc;
	dc.Attach(lpDrawItemStruct->hDC);
	CRect rect(&(lpDrawItemStruct->rcItem));
	
	// This switch statement draws the item in the combo box based on the itemID.
	// The itemID corresponds to the index in the COLORREF array.
	switch(lpDrawItemStruct->itemID)
	{
	// The automatic case
	case 16:
		{
			// Create the brush
			CBrush brush(colors.GetSize());
			CRect rect(&(lpDrawItemStruct->rcItem));
			rect.InflateRect(-2, -2);
			// Color the area
			dc.FillRect(rect, &brush);
			// Draw teh focus rect if the mosue is either over the item, or if the item
			// is selected
			if (lpDrawItemStruct->itemState & ODS_SELECTED)
				dc.DrawFocusRect(rect);
			
			// Draw the text
			CString strColor = "Automatic";
			CSize textSize = dc.GetOutputTextExtent(strColor);
			dc.SetBkMode(TRANSPARENT);
			dc.SetTextColor(RGB(255, 255, 255));
			dc.DrawText(strColor, rect, DT_SINGLELINE | DT_CENTER);
			
		}
		break;
	default:
		// Drawing code for items accept the automatic color
		
		// Create the brush
		CBrush brush(colors[lpDrawItemStruct->itemID]);
		CRect rect(&(lpDrawItemStruct->rcItem));
		rect.InflateRect(-2, -2);
		// Color the area
		dc.FillRect(rect, &brush);
		// Draw the focus rect if the mouse is either over the item, or if the item
		// is selected
		if (lpDrawItemStruct->itemState & ODS_SELECTED)
			dc.DrawFocusRect(rect);
		
    }
	
	// This draws the black frame around each of the colors so that they
	// do not look like they are kind of blended together
	CBrush frameBrush(RGB(0, 0, 0));
	dc.FrameRect(rect, &frameBrush);
	rect.InflateRect(-1, -1);
	
	dc.Detach();
	
}

void CColorComboEx::PreSubclassWindow() 
{
	for (int nColors = 0; nColors < colors.GetSize(); nColors++)
		// Add a dummy string for every array item so that WM_DRAWITEM message is sent.
		AddString("");
	
	// Select the first color when the control is created.
	SetCurSel(0);
	
	CComboBox::PreSubclassWindow();
}

