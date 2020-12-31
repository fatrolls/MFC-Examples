// VtxButton.cpp: implementation file
//
// CVtxButton
//
// Copyright © 1998 Hilton Campbell. All rights reserved.
//
// Code fragments by Chris Maunder (Chris.Maunder@cbr.clw.csiro.au)
// Copyright © 1997,1998 Chris Maunder.
// 
// Revisions: 
// 30 June 1998		Initial release		Hilton Campbell (hiltonc@softhome.net)
//
// This code may be used in compiled form in any way you desire. This file may be 
// redistributed unmodified by any means PROVIDING it is not sold for profit without the 
// author's written consent, and providing that this notice and the authors name is 
// included. If the source code in this file is used in any distributed application, please
// let me know by e-mail so that I can feel special. 
//
// No warrantee of any kind, express or implied, is included with this software; use at 
// your own risk, responsibility for damages (if any) to anyone resulting from the use of 
// this software rests entirely with the user.
//
///////////////////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Vtx.h"
#include "VtxButton.h"
#include <math.h>

// Windows system colors:
#define RGB_BUTTON_BLACK	(GetSysColor(COLOR_3DDKSHADOW))
#define RGB_BUTTON_WHITE	(GetSysColor(COLOR_3DHILIGHT))
#define RGB_BUTTON_GRAY		(GetSysColor(COLOR_3DFACE))
#define RGB_BUTTON_LIGHT	(GetSysColor(COLOR_3DLIGHT))
#define RGB_BUTTON_DARK		(GetSysColor(COLOR_3DSHADOW))

// The angle (in radians) from which the light is from:
#define LIGHT_SOURCE_ANGLE	3 * PI / 4

// There is no excuse for inaccuracy in this area =)
#define PI			3.1415926535897932384626433832795028841971693993751058209
// A very convenient way to properly convert double's to int's:
#define round(x)	(int)(x + 0.5)

///////////////////////////////////////////////////////////////////////////////////////////
// Misc functions

// Compute the angle of a line segment given it's rise and run:
double GetAngle(const double& dRise, const double& dRun)
{
	double dAngle = atan2(dRise, dRun);
	
	if (dAngle < 0.0)
		dAngle = 2 * PI + dAngle;

	return dAngle;
}

// Compute an intermediate color:
COLORREF InterpolateColors(const COLORREF& crA, const COLORREF& crB, const double& dWeight)
{
	BYTE Red   = (BYTE)(dWeight * GetRValue(crA) + (1.0 - dWeight) * GetRValue(crB));
	BYTE Green = (BYTE)(dWeight * GetGValue(crA) + (1.0 - dWeight) * GetGValue(crB));
	BYTE Blue  = (BYTE)(dWeight * GetBValue(crA) + (1.0 - dWeight) * GetBValue(crB));

	return RGB(Red, Green, Blue);
}

// Compute the color of a line segment defined by ptA and ptB:
COLORREF GetColor(const CPoint& ptA, const CPoint& ptZ, const COLORREF& crDark, 
				  const COLORREF& crBright)
{

	double dRise = (double)(ptZ.y - ptA.y);
	double dRun = (double)(ptA.x - ptZ.x);
	double dAngle = 2 * PI - GetAngle(dRun, dRise);

	double dAngleDifference = fabs(LIGHT_SOURCE_ANGLE - dAngle);

	// I blatantly took this code fragment, "0.5 * (cos(dAngleDifference) + 1.0)," from  
	// Chris Maunder because it works. I am at a loss as to why.
	return InterpolateColors(crBright, crDark, 0.5 * (cos(dAngleDifference) + 1.0));
}

///////////////////////////////////////////////////////////////////////////////////////////
// CVtxButton button

CVtxButton::CVtxButton()
{
	m_pBtn = new CBitmap;
	m_pBtnFocus = new CBitmap;
	m_pBtnSelected = new CBitmap;
	m_pBitmapDC = new CDC;

	m_bNeedToRegenerateBitmaps = TRUE;
}

CVtxButton::~CVtxButton()
{
	delete m_pBitmapDC;
	delete m_pBtn;
	delete m_pBtnFocus;
	delete m_pBtnSelected;
}

/////////////////////////////////////////////////////////////////////////////
// CVtxButton message handlers

void CVtxButton::PreSubclassWindow() 
{
	CButton::PreSubclassWindow();

	ModifyStyle(0, BS_OWNERDRAW);
}

// Paint the button with the correct bitmap:
void CVtxButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	ASSERT(lpDrawItemStruct != NULL);
	CDC *pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
	CRect rect = lpDrawItemStruct->rcItem;
	UINT state = lpDrawItemStruct->itemState;

	if (!m_vtxBtnPolygons.ValidPolygons())
		SetVtx(VTX_RECT);
	if (m_bNeedToRegenerateBitmaps || m_dwStyle != GetStyle())
		GenerateBitmaps(lpDrawItemStruct);

	if (state & ODS_SELECTED)
		m_pBitmapDC->SelectObject(m_pBtnSelected);
	else
	{
		if (state & ODS_FOCUS)
			m_pBitmapDC->SelectObject(m_pBtnFocus);
		else
			m_pBitmapDC->SelectObject(m_pBtn);
	}

	pDC->BitBlt(0, 0, rect.Width(), rect.Height(), m_pBitmapDC, 0, 0, SRCCOPY);
}

///////////////////////////////////////////////////////////////////////////////////////////
// CVtxButton operations

void CVtxButton::SetVtxPolygons(CVtxPolygons *vtxBtnPolygons)
{
	m_vtxBtnPolygons.Copy(*vtxBtnPolygons);

	CRgn rgn;
	m_vtxBtnPolygons.CreatePolygonRgn(&rgn, 0);
	
	HRGN hRgn;
	hRgn = (HRGN)rgn.Detach();
	SetWindowRgn(hRgn, TRUE);

	m_bNeedToRegenerateBitmaps = TRUE;
}

void CVtxButton::SetVtx(const int& nType)
{
	CRect rect;
	GetClientRect(rect);

	m_vtxBtnPolygons.Create(&rect, nType);
	CRgn rgn;
	m_vtxBtnPolygons.CreatePolygonRgn(&rgn, 0);

	HRGN hRgn;
	hRgn = (HRGN)rgn.Detach();
	SetWindowRgn(hRgn, TRUE);

	m_bNeedToRegenerateBitmaps = TRUE;
}

///////////////////////////////////////////////////////////////////////////////////////////
// CVtxButton state bitmap generation:

void CVtxButton::GenerateBitmaps(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	ASSERT(lpDrawItemStruct != NULL);
	CDC *pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
	CRect rect = lpDrawItemStruct->rcItem;
	UINT state = lpDrawItemStruct->itemState;

	m_dwStyle = GetStyle();

	CRgn rgn;
	m_vtxBtnPolygons.CreatePolygonRgn(&rgn, 3);

	delete m_pBitmapDC;	
	m_pBitmapDC = new CDC;
	m_pBitmapDC->CreateCompatibleDC(pDC);
	CFont *oldFont = m_pBitmapDC->SelectObject(pDC->GetCurrentFont());

	CString	strText;
	GetWindowText(strText);
	CSize	extent = m_pBitmapDC->GetTextExtent(strText);
	CPoint	ptCenter = rect.CenterPoint(); 
	CPoint	pt = CPoint(ptCenter.x - extent.cx / 2 - 1, ptCenter.y - extent.cy / 2 - 1);
	CRect	textRect(pt.x, pt.y, pt.x + extent.cx, pt.y + extent.cy);

	delete m_pBtn;
	m_pBtn = new CBitmap;
	m_pBtn->CreateCompatibleBitmap(pDC, rect.right, rect.bottom);
	m_pBitmapDC->SelectObject(m_pBtn);
	m_pBitmapDC->SelectStockObject(NULL_BRUSH);
	m_pBitmapDC->FillSolidRect(rect, RGB_BUTTON_GRAY);

	// Generate m_pBtn bitmap: unfocused button
	if (m_dwStyle & BS_FLAT)
	{
		COLORREF crBlend = InterpolateColors(RGB_BUTTON_WHITE, RGB_BUTTON_BLACK, 0.5);

		CPen *oldpen = m_pBitmapDC->SelectObject(new CPen(PS_SOLID, 1, RGB_BUTTON_GRAY));
		CBrush *oldBrush = m_pBitmapDC->SelectObject(new CBrush(crBlend));
		CPoint pts[4];
		
		for (int i = 0; i < m_vtxBtnPolygons.GetSize(0) - 1; i++)
		{
			pts[2] = CPoint(*m_vtxBtnPolygons.GetAt(0, i + 1));
			pts[3] = CPoint(*m_vtxBtnPolygons.GetAt(0, i));

			delete m_pBitmapDC->SelectObject(new CBrush(crBlend));
			delete m_pBitmapDC->SelectObject(new CPen(PS_SOLID, 1, crBlend));
			pts[0] = CPoint(*m_vtxBtnPolygons.GetAt(1, i));
			pts[1] = CPoint(*m_vtxBtnPolygons.GetAt(1, i + 1));
			m_pBitmapDC->Polygon(pts, 4);
			delete m_pBitmapDC->SelectObject(new CPen(PS_SOLID, 1, RGB_BUTTON_WHITE));
			m_pBitmapDC->MoveTo(*m_vtxBtnPolygons.GetAt(1, i + 1));
			m_pBitmapDC->LineTo(*m_vtxBtnPolygons.GetAt(1, i));
			m_pBitmapDC->SetPixelV(*m_vtxBtnPolygons.GetAt(1, i), RGB_BUTTON_WHITE);

			delete m_pBitmapDC->SelectObject(new CPen(PS_SOLID, 1, RGB_BUTTON_BLACK));
			m_pBitmapDC->MoveTo(*m_vtxBtnPolygons.GetAt(0, i + 1));
			m_pBitmapDC->LineTo(*m_vtxBtnPolygons.GetAt(0, i));
			m_pBitmapDC->SetPixelV(*m_vtxBtnPolygons.GetAt(0, i), RGB_BUTTON_BLACK);
		}

		delete m_pBitmapDC->SelectObject(oldpen);
		delete m_pBitmapDC->SelectObject(oldBrush);
	}
	else
	{
		CPen *oldpen = m_pBitmapDC->SelectObject(new CPen(PS_SOLID, 1, RGB_BUTTON_GRAY));
		CBrush *oldBrush = m_pBitmapDC->SelectObject(new CBrush(RGB_BUTTON_GRAY));
		CPoint pts[4];

		COLORREF crLighter = RGB_BUTTON_LIGHT;
		COLORREF crDarker = RGB_BUTTON_DARK;
		COLORREF crBlend = RGB_BUTTON_GRAY;
		
		for (int i = 0; i < m_vtxBtnPolygons.GetSize(0) - 1; i++)
		{
			pts[2] = CPoint(*m_vtxBtnPolygons.GetAt(0, i + 1));
			pts[3] = CPoint(*m_vtxBtnPolygons.GetAt(0, i));

			crLighter = GetColor(*m_vtxBtnPolygons.GetAt(1, i), 
				*m_vtxBtnPolygons.GetAt(1, i + 1), RGB_BUTTON_DARK, 
				RGB_BUTTON_LIGHT);
			crDarker = GetColor(*m_vtxBtnPolygons.GetAt(0, i), 
				*m_vtxBtnPolygons.GetAt(0, i + 1), RGB_BUTTON_BLACK, 
				RGB_BUTTON_WHITE);
			crBlend = InterpolateColors(crLighter, crDarker, 0.5);

			delete m_pBitmapDC->SelectObject(new CBrush(crBlend));
			delete m_pBitmapDC->SelectObject(new CPen(PS_SOLID, 1, crBlend));
			pts[0] = CPoint(*m_vtxBtnPolygons.GetAt(1, i));
			pts[1] = CPoint(*m_vtxBtnPolygons.GetAt(1, i + 1));
			m_pBitmapDC->Polygon(pts, 4);
			delete m_pBitmapDC->SelectObject(new CPen(PS_SOLID, 1, crLighter));
			m_pBitmapDC->MoveTo(*m_vtxBtnPolygons.GetAt(1, i + 1));
			m_pBitmapDC->LineTo(*m_vtxBtnPolygons.GetAt(1, i));
			m_pBitmapDC->SetPixelV(*m_vtxBtnPolygons.GetAt(1, i), crLighter);

			delete m_pBitmapDC->SelectObject(new CPen(PS_SOLID, 1, crDarker));
			pts[0] = CPoint(*m_vtxBtnPolygons.GetAt(0, i));
			pts[1] = CPoint(*m_vtxBtnPolygons.GetAt(0, i + 1));
			m_pBitmapDC->Polygon(pts, 4);
		}

		delete m_pBitmapDC->SelectObject(oldpen);
		delete m_pBitmapDC->SelectObject(oldBrush);
	}
	if (!strText.IsEmpty())
	{		
		m_pBitmapDC->SelectClipRgn(&rgn);

		m_pBitmapDC->SetBkMode(TRANSPARENT);
		if (state & ODS_DISABLED)
			m_pBitmapDC->DrawState(pt, extent, strText, DSS_DISABLED, TRUE, 0, (HBRUSH)NULL);
		else
		{
			m_pBitmapDC->DrawText(strText, -1, textRect, DT_SINGLELINE | DT_CENTER | 
				DT_VCENTER);
		}

		m_pBitmapDC->SelectClipRgn(NULL);
	}

	delete m_pBtnFocus;
	m_pBtnFocus = new CBitmap;
	m_pBtnFocus->CreateCompatibleBitmap(pDC, rect.right, rect.bottom);
	m_pBitmapDC->SelectObject(m_pBtnFocus);
	m_pBitmapDC->SelectStockObject(NULL_BRUSH);
	m_pBitmapDC->FillSolidRect(rect, RGB_BUTTON_GRAY);

	// Generate m_pBtnFocus bitmap: focused button
	if (m_dwStyle & BS_FLAT)
	{
		CPen *oldpen = m_pBitmapDC->SelectObject(new CPen(PS_SOLID, 1, RGB_BUTTON_GRAY));
		CBrush *oldBrush = m_pBitmapDC->SelectObject(new CBrush(RGB_BUTTON_GRAY));
		CPoint pts[4];

		COLORREF crBlend = InterpolateColors(RGB_BUTTON_WHITE, RGB_BUTTON_BLACK, 0.5);
		
		for (int i = 0; i < m_vtxBtnPolygons.GetSize(0) - 1; i++)
		{
			pts[2] = CPoint(*m_vtxBtnPolygons.GetAt(0, i + 1));
			pts[3] = CPoint(*m_vtxBtnPolygons.GetAt(0, i));

			delete m_pBitmapDC->SelectObject(new CBrush(crBlend));
			delete m_pBitmapDC->SelectObject(new CPen(PS_SOLID, 1, crBlend));
			pts[0] = CPoint(*m_vtxBtnPolygons.GetAt(2, i));
			pts[1] = CPoint(*m_vtxBtnPolygons.GetAt(2, i + 1));
			m_pBitmapDC->Polygon(pts, 4);
			delete m_pBitmapDC->SelectObject(new CPen(PS_SOLID, 1, RGB_BUTTON_WHITE));
			m_pBitmapDC->MoveTo(*m_vtxBtnPolygons.GetAt(2, i + 1));
			m_pBitmapDC->LineTo(*m_vtxBtnPolygons.GetAt(2, i));
			m_pBitmapDC->SetPixelV(*m_vtxBtnPolygons.GetAt(2, i), RGB_BUTTON_WHITE);

			delete m_pBitmapDC->SelectObject(new CBrush(RGB_BUTTON_BLACK));
			delete m_pBitmapDC->SelectObject(new CPen(PS_SOLID, 1, RGB_BUTTON_BLACK));
			pts[0] = CPoint(*m_vtxBtnPolygons.GetAt(1, i));
			pts[1] = CPoint(*m_vtxBtnPolygons.GetAt(1, i + 1));
			m_pBitmapDC->Polygon(pts, 4);
		}
		
		delete m_pBitmapDC->SelectObject(oldBrush);
		delete m_pBitmapDC->SelectObject(new CPen(PS_SOLID, 1, RGB_BUTTON_BLACK));

		for (i = 0; i < m_vtxBtnPolygons.GetSize(0) - 1; i++)
		{
			m_pBitmapDC->MoveTo(*m_vtxBtnPolygons.GetAt(0, i + 1));
			m_pBitmapDC->LineTo(*m_vtxBtnPolygons.GetAt(0, i));
			m_pBitmapDC->SetPixelV(*m_vtxBtnPolygons.GetAt(0, i), RGB_BUTTON_BLACK);
		}

		COLORREF crColor = InterpolateColors(RGB_BUTTON_GRAY, RGB_BUTTON_DARK, 0.5);
		delete m_pBitmapDC->SelectObject(new CPen(PS_SOLID, 1, crColor));

		for (i = 0; i < m_vtxBtnPolygons.GetSize(0) - 1; i++)
		{
			m_pBitmapDC->MoveTo(*m_vtxBtnPolygons.GetAt(3, i + 1));
			m_pBitmapDC->LineTo(*m_vtxBtnPolygons.GetAt(3, i));
			m_pBitmapDC->SetPixelV(*m_vtxBtnPolygons.GetAt(3, i), crColor);
		}

		delete m_pBitmapDC->SelectObject(oldpen);	
	}
	else
	{
		CPen *oldpen = m_pBitmapDC->SelectObject(new CPen(PS_SOLID, 1, RGB_BUTTON_GRAY));
		CBrush *oldBrush = m_pBitmapDC->SelectObject(new CBrush(RGB_BUTTON_GRAY));
		CPoint pts[4];

		COLORREF crLighter = RGB_BUTTON_LIGHT;
		COLORREF crDarker = RGB_BUTTON_DARK;
		COLORREF crBlend = RGB_BUTTON_GRAY;
		
		for (int i = 0; i < m_vtxBtnPolygons.GetSize(0) - 1; i++)
		{
			pts[2] = CPoint(*m_vtxBtnPolygons.GetAt(0, i + 1));
			pts[3] = CPoint(*m_vtxBtnPolygons.GetAt(0, i));

			crLighter = GetColor(*m_vtxBtnPolygons.GetAt(2, i), 
				*m_vtxBtnPolygons.GetAt(2, i + 1), RGB_BUTTON_DARK, 
				RGB_BUTTON_LIGHT);
			crDarker = GetColor(*m_vtxBtnPolygons.GetAt(1, i), 
				*m_vtxBtnPolygons.GetAt(1, i + 1), RGB_BUTTON_BLACK, 
				RGB_BUTTON_WHITE);
			crBlend = InterpolateColors(crLighter, crDarker, 0.5);

			delete m_pBitmapDC->SelectObject(new CBrush(crBlend));
			delete m_pBitmapDC->SelectObject(new CPen(PS_SOLID, 1, crBlend));	
			pts[0] = CPoint(*m_vtxBtnPolygons.GetAt(2, i));
			pts[1] = CPoint(*m_vtxBtnPolygons.GetAt(2, i + 1));
			m_pBitmapDC->Polygon(pts, 4);
			delete m_pBitmapDC->SelectObject(new CPen(PS_SOLID, 1, crLighter));
			m_pBitmapDC->MoveTo(*m_vtxBtnPolygons.GetAt(2, i + 1));
			m_pBitmapDC->LineTo(*m_vtxBtnPolygons.GetAt(2, i));
			m_pBitmapDC->SetPixelV(*m_vtxBtnPolygons.GetAt(2, i), crLighter);

			delete m_pBitmapDC->SelectObject(new CBrush(crDarker));
			delete m_pBitmapDC->SelectObject(new CPen(PS_SOLID, 1, crDarker));
			pts[0] = CPoint(*m_vtxBtnPolygons.GetAt(1, i));
			pts[1] = CPoint(*m_vtxBtnPolygons.GetAt(1, i + 1));
			m_pBitmapDC->Polygon(pts, 4);
		}
		
		delete m_pBitmapDC->SelectObject(oldBrush);
		delete m_pBitmapDC->SelectObject(new CPen(PS_SOLID, 1, RGB_BUTTON_BLACK));

		for (i = 0; i < m_vtxBtnPolygons.GetSize(0) - 1; i++)
		{
			m_pBitmapDC->MoveTo(*m_vtxBtnPolygons.GetAt(0, i + 1));
			m_pBitmapDC->LineTo(*m_vtxBtnPolygons.GetAt(0, i));
			m_pBitmapDC->SetPixelV(*m_vtxBtnPolygons.GetAt(0, i), RGB_BUTTON_BLACK);
		}

		COLORREF crColor = InterpolateColors(RGB_BUTTON_GRAY, RGB_BUTTON_DARK, 0.5);
		delete m_pBitmapDC->SelectObject(new CPen(PS_SOLID, 1, crColor));

		for (i = 0; i < m_vtxBtnPolygons.GetSize(0) - 1; i++)
		{
			m_pBitmapDC->MoveTo(*m_vtxBtnPolygons.GetAt(3, i + 1));
			m_pBitmapDC->LineTo(*m_vtxBtnPolygons.GetAt(3, i));
			m_pBitmapDC->SetPixelV(*m_vtxBtnPolygons.GetAt(3, i), crColor);
		}

		delete m_pBitmapDC->SelectObject(oldpen);	
	}
	if (!strText.IsEmpty())
	{		
		m_pBitmapDC->SelectClipRgn(&rgn);

		m_pBitmapDC->SetBkMode(TRANSPARENT);
		if (state & ODS_DISABLED)
			m_pBitmapDC->DrawState(pt, extent, strText, DSS_DISABLED, TRUE, 0, 
			(HBRUSH)NULL);
		else
		{
			m_pBitmapDC->DrawText(strText, -1, textRect, DT_SINGLELINE | DT_CENTER | 
				DT_VCENTER);
		}

		m_pBitmapDC->SelectClipRgn(NULL);
	}

	delete m_pBtnSelected;
	m_pBtnSelected = new CBitmap;
	m_pBtnSelected->CreateCompatibleBitmap(pDC, rect.right, rect.bottom);
	m_pBitmapDC->SelectObject(m_pBtnSelected);
	m_pBitmapDC->SelectStockObject(NULL_BRUSH);
	m_pBitmapDC->FillSolidRect(rect, RGB_BUTTON_GRAY);

	// Generate m_pBtnSelected bitmap: selected button
	if (m_dwStyle & BS_FLAT)
	{
		COLORREF crBlend = InterpolateColors(RGB_BUTTON_DARK, RGB_BUTTON_BLACK, 0.5);

		CPen *oldpen = m_pBitmapDC->SelectObject(new CPen(PS_SOLID, 1, RGB_BUTTON_GRAY));
		CBrush *oldBrush = m_pBitmapDC->SelectObject(new CBrush(RGB_BUTTON_GRAY));
		CPoint pts[4];
		
		for (int i = 0; i < m_vtxBtnPolygons.GetSize(0) - 1; i++)
		{
			pts[2] = CPoint(*m_vtxBtnPolygons.GetAt(0, i + 1));
			pts[3] = CPoint(*m_vtxBtnPolygons.GetAt(0, i));

			delete m_pBitmapDC->SelectObject(new CBrush(crBlend));
			delete m_pBitmapDC->SelectObject(new CPen(PS_SOLID, 1, crBlend));
			pts[0] = CPoint(*m_vtxBtnPolygons.GetAt(2, i));
			pts[1] = CPoint(*m_vtxBtnPolygons.GetAt(2, i + 1));
			m_pBitmapDC->Polygon(pts, 4);
			delete m_pBitmapDC->SelectObject(new CPen(PS_SOLID, 1, RGB_BUTTON_WHITE));
			m_pBitmapDC->MoveTo(*m_vtxBtnPolygons.GetAt(2, i + 1));
			m_pBitmapDC->LineTo(*m_vtxBtnPolygons.GetAt(2, i));
			m_pBitmapDC->SetPixelV(*m_vtxBtnPolygons.GetAt(2, i), RGB_BUTTON_WHITE);

			delete m_pBitmapDC->SelectObject(new CBrush(RGB_BUTTON_BLACK));
			delete m_pBitmapDC->SelectObject(new CPen(PS_SOLID, 1, RGB_BUTTON_BLACK));
			pts[0] = CPoint(*m_vtxBtnPolygons.GetAt(1, i));
			pts[1] = CPoint(*m_vtxBtnPolygons.GetAt(1, i + 1));
			m_pBitmapDC->Polygon(pts, 4);
		}
		
		delete m_pBitmapDC->SelectObject(oldBrush);
		delete m_pBitmapDC->SelectObject(new CPen(PS_SOLID, 1, RGB_BUTTON_BLACK));

		for (i = 0; i < m_vtxBtnPolygons.GetSize(0) - 1; i++)
		{
			m_pBitmapDC->MoveTo(*m_vtxBtnPolygons.GetAt(0, i + 1));
			m_pBitmapDC->LineTo(*m_vtxBtnPolygons.GetAt(0, i));
			m_pBitmapDC->SetPixelV(*m_vtxBtnPolygons.GetAt(0, i), RGB_BUTTON_BLACK);
		}

		COLORREF crColor = InterpolateColors(RGB_BUTTON_GRAY, RGB_BUTTON_DARK, 0.5);
		delete m_pBitmapDC->SelectObject(new CPen(PS_SOLID, 1, crColor));

		for (i = 0; i < m_vtxBtnPolygons.GetSize(0) - 1; i++)
		{
			m_pBitmapDC->MoveTo(*m_vtxBtnPolygons.GetAt(3, i + 1));
			m_pBitmapDC->LineTo(*m_vtxBtnPolygons.GetAt(3, i));
			m_pBitmapDC->SetPixelV(*m_vtxBtnPolygons.GetAt(3, i), crColor);
		}

		delete m_pBitmapDC->SelectObject(oldpen);
	}
	else
	{
		COLORREF crBlend = InterpolateColors(RGB_BUTTON_DARK, RGB_BUTTON_BLACK, 0.5);

		CPen *oldpen = m_pBitmapDC->SelectObject(new CPen(PS_SOLID, 1, RGB_BUTTON_DARK));
		CBrush *oldBrush = m_pBitmapDC->SelectObject(new CBrush(crBlend));
		CPoint pts[4];

		for (int i = 0; i < m_vtxBtnPolygons.GetSize(0) - 1; i++)
		{
			delete m_pBitmapDC->SelectObject(new CPen(PS_SOLID, 1, crBlend));
			pts[0] = CPoint(*m_vtxBtnPolygons.GetAt(1, i));
			pts[1] = CPoint(*m_vtxBtnPolygons.GetAt(1, i + 1));
			pts[2] = CPoint(*m_vtxBtnPolygons.GetAt(0, i + 1));
			pts[3] = CPoint(*m_vtxBtnPolygons.GetAt(0, i));
			m_pBitmapDC->Polygon(pts, 4);
			delete m_pBitmapDC->SelectObject(new CPen(PS_SOLID, 1, RGB_BUTTON_DARK));
			m_pBitmapDC->MoveTo(*m_vtxBtnPolygons.GetAt(1, i + 1));
			m_pBitmapDC->LineTo(*m_vtxBtnPolygons.GetAt(1, i));
			m_pBitmapDC->SetPixelV(*m_vtxBtnPolygons.GetAt(1, i), RGB_BUTTON_DARK);
		}

		delete m_pBitmapDC->SelectObject(oldBrush);
		delete m_pBitmapDC->SelectObject(new CPen(PS_SOLID, 1, RGB_BUTTON_BLACK));

		for (i = 0; i < m_vtxBtnPolygons.GetSize(0) - 1; i++)
		{
			m_pBitmapDC->MoveTo(*m_vtxBtnPolygons.GetAt(0, i + 1));
			m_pBitmapDC->LineTo(*m_vtxBtnPolygons.GetAt(0, i));
			m_pBitmapDC->SetPixelV(*m_vtxBtnPolygons.GetAt(0, i), RGB_BUTTON_BLACK);
		}

		COLORREF crColor = InterpolateColors(RGB_BUTTON_GRAY, RGB_BUTTON_DARK, 0.5);
		delete m_pBitmapDC->SelectObject(new CPen(PS_SOLID, 1, crColor));

		for (i = 0; i < m_vtxBtnPolygons.GetSize(0) - 1; i++)
		{
			m_pBitmapDC->MoveTo(*m_vtxBtnPolygons.GetAt(3, i + 1));
			m_pBitmapDC->LineTo(*m_vtxBtnPolygons.GetAt(3, i));
			m_pBitmapDC->SetPixelV(*m_vtxBtnPolygons.GetAt(3, i), crColor);
		}

		delete m_pBitmapDC->SelectObject(oldpen);
	}
	if (!strText.IsEmpty())
	{		
		m_pBitmapDC->SelectClipRgn(&rgn);

		pt.Offset(1, 1);
		textRect.OffsetRect(1, 1);

		m_pBitmapDC->SetBkMode(TRANSPARENT);
		if (state & ODS_DISABLED)
			m_pBitmapDC->DrawState(pt, extent, strText, DSS_DISABLED, TRUE, 0, 
			(HBRUSH)NULL);
		else
		{
			m_pBitmapDC->DrawText(strText, -1, textRect, DT_SINGLELINE | DT_CENTER | 
				DT_VCENTER);
		}

		m_pBitmapDC->SelectClipRgn(NULL);
	}

	m_pBitmapDC->SelectObject(oldFont);

	m_bNeedToRegenerateBitmaps = FALSE;
}

///////////////////////////////////////////////////////////////////////////////////////////