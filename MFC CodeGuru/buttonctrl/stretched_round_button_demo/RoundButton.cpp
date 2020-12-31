// RoundButton.cpp : implementation file
//
// Round Buttons!
//
// Written by Chris Maunder (Chris.Maunder@cbr.clw.csiro.au)
// Copyright (c) 1997,1998.
// 
// Modified: 2 Feb 1998 - Fix vis problem, CRgn resource leak,
//                        button reposition code redone. CJM.
//
// This code may be used in compiled form in any way you desire. This
// file may be redistributed unmodified by any means PROVIDING it is 
// not sold for profit without the authors written consent, and 
// providing that this notice and the authors name is included. If 
// the source code in this file is used in any commercial application 
// then a simple email would be nice.
//
// This file is provided "as is" with no expressed or implied warranty.
// The author accepts no liability if it causes any damage to your
// computer, causes your pet cat to fall ill, increases baldness or
// makes you car start emitting strange noises when you start it up.
//
// Expect bugs.
// 
// Please use and enjoy. Please let me know of any bugs/mods/improvements 
// that you have found/implemented and I will fix/incorporate them into this
// file. 
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "math.h"
#include "RoundButton.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// prototypes
COLORREF GetColour(double dAngle, COLORREF crBright, COLORREF crDark);
void DrawCircle(CDC* pDC, CPoint p, LONG lRadius, COLORREF crColour, BOOL bDashed = FALSE);
void DrawCircleLeft(CDC* pDC, CPoint p, LONG lRadius, COLORREF crBright, COLORREF crDark);
void DrawCircleRight(CDC* pDC, CPoint p, LONG lRadius, COLORREF crBright, COLORREF crDark);


// Calculate colour for a point at the given angle by performing a linear
// interpolation between the colours crBright and crDark based on the cosine
// of the angle between the light source and the point.
//
// Angles are measured from the +ve x-axis (i.e. (1,0) = 0 degrees, (0,1) = 90 degrees )
// But remember: +y points down!

COLORREF GetColour(double dAngle, COLORREF crBright, COLORREF crDark)
{
#define Rad2Deg	180.0/3.1415 

// For better light-continuity along the edge of a stretched button: 
//	LIGHT_SOURCE_ANGLE == -1.88
	
//#define LIGHT_SOURCE_ANGLE	-2.356		// -2.356 radians = -135 degrees, i.e. From top left
#define LIGHT_SOURCE_ANGLE	-1.88

	ASSERT(dAngle > -3.1416 && dAngle < 3.1416);
	double dAngleDifference = LIGHT_SOURCE_ANGLE - dAngle;

	if (dAngleDifference < -3.1415) dAngleDifference = 6.293 + dAngleDifference;
	else if (dAngleDifference > 3.1415) dAngleDifference = 6.293 - dAngleDifference;

	double Weight = 0.5*(cos(dAngleDifference)+1.0);

	BYTE Red   = (BYTE) (Weight*GetRValue(crBright) + (1.0-Weight)*GetRValue(crDark));
	BYTE Green = (BYTE) (Weight*GetGValue(crBright) + (1.0-Weight)*GetGValue(crDark));
	BYTE Blue  = (BYTE) (Weight*GetBValue(crBright) + (1.0-Weight)*GetBValue(crDark));

	//TRACE("LightAngle = %0.0f, Angle = %3.0f, Diff = %3.0f, Weight = %0.2f, RGB %3d,%3d,%3d\n", 
	//	  LIGHT_SOURCE_ANGLE*Rad2Deg, dAngle*Rad2Deg, dAngleDifference*Rad2Deg, Weight,Red,Green,Blue);

	return RGB(Red, Green, Blue);
}

void DrawCircle(CDC* pDC, CPoint p, LONG lRadius, COLORREF crColour, BOOL bDashed)
{
	const int nDashLength = 1;
	LONG lError, lXoffset, lYoffset;
	int  nDash = 0;
	BOOL bDashOn = TRUE;

	//Check to see that the coordinates are valid
	ASSERT( (p.x + lRadius <= LONG_MAX) && (p.y + lRadius <= LONG_MAX) );
	ASSERT( (p.x - lRadius >= LONG_MIN) && (p.y - lRadius >= LONG_MIN) );

	//Set starting values
	lXoffset = lRadius;
	lYoffset = 0;
	lError   = -lRadius;

	do {
		if (bDashOn) {
			pDC->SetPixelV(p.x + lXoffset, p.y + lYoffset, crColour);
			pDC->SetPixelV(p.x + lXoffset, p.y - lYoffset, crColour);
			pDC->SetPixelV(p.x + lYoffset, p.y + lXoffset, crColour);
			pDC->SetPixelV(p.x + lYoffset, p.y - lXoffset, crColour);
			pDC->SetPixelV(p.x - lYoffset, p.y + lXoffset, crColour);
			pDC->SetPixelV(p.x - lYoffset, p.y - lXoffset, crColour);
			pDC->SetPixelV(p.x - lXoffset, p.y + lYoffset, crColour);
			pDC->SetPixelV(p.x - lXoffset, p.y - lYoffset, crColour);
		}

		//Advance the error term and the constant X axis step
		lError += lYoffset++;

		//Check to see if error term has overflowed
		if ((lError += lYoffset) >= 0)
			lError -= --lXoffset * 2;

		if (bDashed && (++nDash == nDashLength)) {
			nDash = 0;
			bDashOn = !bDashOn;
		}

	} while (lYoffset <= lXoffset);	//Continue until halfway point
} 

// The original Drawcircle function is split up into DrawCircleRight and DrawCircleLeft
// to make stretched buttons
//
void DrawCircleRight(CDC* pDC, CPoint p, LONG lRadius, COLORREF crBright, COLORREF crDark)
{
	LONG lError, lXoffset, lYoffset;

	//Check to see that the coordinates are valid
	ASSERT( (p.x + lRadius <= LONG_MAX) && (p.y + lRadius <= LONG_MAX) );
	ASSERT( (p.x - lRadius >= LONG_MIN) && (p.y - lRadius >= LONG_MIN) );

	//Set starting values
	lXoffset = lRadius;
	lYoffset = 0;
	lError   = -lRadius;

	do {
		const double Pi = 3.141592654, 
					 Pi_on_2 = Pi * 0.5,
					 Three_Pi_on_2 = Pi * 1.5;
		COLORREF crColour;
		double   dAngle = atan2(lYoffset, lXoffset);

		//Draw the current pixel, reflected across all four arcs

		crColour = GetColour(dAngle, crBright, crDark);
		pDC->SetPixelV(p.x + lXoffset, p.y + lYoffset, crColour);

		crColour = GetColour(Pi_on_2 - dAngle, crBright, crDark);
		pDC->SetPixelV(p.x + lYoffset, p.y + lXoffset, crColour);

		crColour = GetColour(-Pi_on_2 + dAngle, crBright, crDark);
		pDC->SetPixelV(p.x + lYoffset, p.y - lXoffset, crColour);

		crColour = GetColour(-dAngle, crBright, crDark);
		pDC->SetPixelV(p.x + lXoffset, p.y - lYoffset, crColour);

		//Advance the error term and the constant X axis step
		lError += lYoffset++;

		//Check to see if error term has overflowed
		if ((lError += lYoffset) >= 0)
			lError -= --lXoffset * 2;

	} while (lYoffset <= lXoffset);	//Continue until halfway point
} 

// The original Drawcircle function is split up into DrawCircleRight and DrawCircleLeft
// to make stretched buttons
//
void DrawCircleLeft(CDC* pDC, CPoint p, LONG lRadius, COLORREF crBright, COLORREF crDark)
{
	LONG lError, lXoffset, lYoffset;

	//Check to see that the coordinates are valid
	ASSERT( (p.x + lRadius <= LONG_MAX) && (p.y + lRadius <= LONG_MAX) );
	ASSERT( (p.x - lRadius >= LONG_MIN) && (p.y - lRadius >= LONG_MIN) );

	//Set starting values
	lXoffset = lRadius;
	lYoffset = 0;
	lError   = -lRadius;

	do {
		const double Pi = 3.141592654, 
					 Pi_on_2 = Pi * 0.5,
					 Three_Pi_on_2 = Pi * 1.5;
		COLORREF crColour;
		double   dAngle = atan2(lYoffset, lXoffset);

		//Draw the current pixel, reflected across all eight arcs

		crColour = GetColour(Pi_on_2 + dAngle, crBright, crDark);
		pDC->SetPixelV(p.x - lYoffset, p.y + lXoffset, crColour);

		crColour = GetColour(Pi - dAngle, crBright, crDark);
		pDC->SetPixelV(p.x - lXoffset, p.y + lYoffset, crColour);

		crColour = GetColour(-Pi + dAngle, crBright, crDark);
		pDC->SetPixelV(p.x - lXoffset, p.y - lYoffset, crColour);

		crColour = GetColour(-Pi_on_2 - dAngle, crBright, crDark);
		pDC->SetPixelV(p.x - lYoffset, p.y - lXoffset, crColour);

		//Advance the error term and the constant X axis step
		lError += lYoffset++;

		//Check to see if error term has overflowed
		if ((lError += lYoffset) >= 0)
			lError -= --lXoffset * 2;

	} while (lYoffset <= lXoffset);	//Continue until halfway point
} 

/////////////////////////////////////////////////////////////////////////////
// CRoundButton

CRoundButton::CRoundButton()
{
	m_bDrawDashedFocusCircle = TRUE;
}

CRoundButton::~CRoundButton()
{
	m_rgn.DeleteObject();
}

BEGIN_MESSAGE_MAP(CRoundButton, CButton)
	//{{AFX_MSG_MAP(CRoundButton)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRoundButton message handlers

void CRoundButton::PreSubclassWindow() 
{
	CButton::PreSubclassWindow();

	ModifyStyle(0, BS_OWNERDRAW);

	CRect rect;
	GetClientRect(rect);

	// set m_bStretch if the button is not square and landscape 
	m_bStretch = rect.Width() > rect.Height() ? TRUE : FALSE;

	// Resize the window to make it square if it is not stretched
	if(!m_bStretch)	rect.bottom = rect.right = min(rect.bottom,rect.right);

	// Get the vital statistics of the window
	// m_ptLeft/m_ptRight are the centerpoints of the left/right arcs of stretched buttons
	m_ptCentre = m_ptLeft = m_ptRight = rect.CenterPoint();

	m_nRadius  = rect.bottom/2-1;

	m_ptLeft.x = m_nRadius;
	m_ptRight.x = rect.right - m_nRadius - 1;

	// Set the window region so mouse clicks only activate the round section 
	// of the button
	m_rgn.DeleteObject(); 
	SetWindowRgn(NULL, FALSE);
	m_rgn.CreateEllipticRgnIndirect(rect);
	SetWindowRgn(m_rgn, TRUE);

	// Convert client coords to the parents client coords
	ClientToScreen(rect);
	CWnd* pParent = GetParent();
	if (pParent) pParent->ScreenToClient(rect);

	// Resize the window if it is not stretched
	if(!m_bStretch)	MoveWindow(rect.left, rect.top, rect.Width(), rect.Height(), TRUE);
}

void CRoundButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	ASSERT(lpDrawItemStruct != NULL);
	
	CDC* pDC   = CDC::FromHandle(lpDrawItemStruct->hDC);
	CRect rect = lpDrawItemStruct->rcItem;
	UINT state = lpDrawItemStruct->itemState;
	UINT nStyle = GetStyle();
	int nRadius = m_nRadius;

	int nSavedDC = pDC->SaveDC();

	pDC->SelectStockObject(NULL_BRUSH);
	pDC->FillSolidRect(rect, ::GetSysColor(COLOR_BTNFACE));

	// Draw the focus circle around the button for non-stretched buttons
	if ((state & ODS_FOCUS) && m_bDrawDashedFocusCircle && !m_bStretch)
		DrawCircle(pDC, m_ptCentre, nRadius--, RGB(0,0,0));

	// Draw the raised/sunken edges of the button (unless flat)
	if (nStyle & BS_FLAT) {

		// for stretched buttons: draw left and right arcs and connect the with lines
		if(m_bStretch)
		{
			CPen* oldpen;
			
			CRect LeftBound(0,0,nRadius*2,nRadius*2);
			CRect RightBound(m_ptRight.x-nRadius,0,m_ptRight.x+nRadius,nRadius*2);

			oldpen = pDC->SelectObject(new CPen(PS_SOLID, 1, ::GetSysColor(COLOR_3DDKSHADOW)));
			pDC->Arc(LeftBound, CPoint(m_ptLeft.x,0), CPoint(m_ptLeft.x,nRadius*2));
			pDC->Arc(RightBound, CPoint(m_ptRight.x,nRadius*2), CPoint(m_ptRight.x,0));
			pDC->MoveTo(m_ptLeft.x,0); pDC->LineTo(m_ptRight.x,0);
			pDC->MoveTo(m_ptLeft.x,nRadius*2-1); pDC->LineTo(m_ptRight.x,nRadius*2-1);

			nRadius--;
			LeftBound.DeflateRect(1,1);
			RightBound.DeflateRect(1,1);

			delete pDC->SelectObject(new CPen(PS_SOLID, 1, ::GetSysColor(COLOR_3DHIGHLIGHT)));
			pDC->Arc(LeftBound, CPoint(m_ptLeft.x,1), CPoint(m_ptLeft.x,nRadius*2));
			pDC->Arc(RightBound, CPoint(m_ptRight.x,nRadius*2), CPoint(m_ptRight.x,0));
			pDC->MoveTo(m_ptLeft.x,1); pDC->LineTo(m_ptRight.x,1);
			pDC->MoveTo(m_ptLeft.x,nRadius*2); pDC->LineTo(m_ptRight.x,nRadius*2);

			delete pDC->SelectObject(oldpen);
		}

		// for non-stretched buttons: draw two circles
		else
		{
			DrawCircle(pDC, m_ptCentre, nRadius--, ::GetSysColor(COLOR_3DDKSHADOW));
			DrawCircle(pDC, m_ptCentre, nRadius--, ::GetSysColor(COLOR_3DHIGHLIGHT));
		}
	} else {
		if ((state & ODS_SELECTED))	{

			// draw the circular segments for stretched AND non-stretched buttons
			DrawCircleLeft(pDC, m_ptLeft, nRadius, 
					   ::GetSysColor(COLOR_3DDKSHADOW), ::GetSysColor(COLOR_3DHIGHLIGHT));
			DrawCircleRight(pDC, m_ptRight, nRadius, 
					   ::GetSysColor(COLOR_3DDKSHADOW), ::GetSysColor(COLOR_3DHIGHLIGHT));
			DrawCircleLeft(pDC, m_ptLeft, nRadius-1, 
					   ::GetSysColor(COLOR_3DSHADOW), ::GetSysColor(COLOR_3DLIGHT));
			DrawCircleRight(pDC, m_ptRight, nRadius-1, 
					   ::GetSysColor(COLOR_3DSHADOW), ::GetSysColor(COLOR_3DLIGHT));

			// draw connecting lines for stretched buttons only
			if (m_bStretch)
			{
				CPen* oldpen;
				CPen* mypen;

				oldpen = pDC->SelectObject(new CPen(PS_SOLID, 1, ::GetSysColor(COLOR_3DDKSHADOW)));
				pDC->MoveTo(m_ptLeft.x, 1); pDC->LineTo(m_ptRight.x, 1);

				delete pDC->SelectObject(new CPen(PS_SOLID, 1, ::GetSysColor(COLOR_3DSHADOW)));
				pDC->MoveTo(m_ptLeft.x, 2);	pDC->LineTo(m_ptRight.x, 2);

				delete pDC->SelectObject(new CPen(PS_SOLID, 1, ::GetSysColor(COLOR_3DLIGHT)));
				pDC->MoveTo(m_ptLeft.x, m_ptLeft.y + nRadius-1); pDC->LineTo(m_ptRight.x, m_ptLeft.y + nRadius-1);

				delete pDC->SelectObject(new CPen(PS_SOLID, 1, ::GetSysColor(COLOR_3DHIGHLIGHT)));
				pDC->MoveTo(m_ptLeft.x, m_ptLeft.y + nRadius); pDC->LineTo(m_ptRight.x, m_ptLeft.y + nRadius);

				delete pDC->SelectObject(oldpen);
			}
					   
		} else {

			// draw the circular segments for stretched AND non-stretched buttons
			DrawCircleLeft(pDC, m_ptLeft, nRadius, 
					   ::GetSysColor(COLOR_3DHIGHLIGHT), ::GetSysColor(COLOR_3DDKSHADOW));
			DrawCircleRight(pDC, m_ptRight, nRadius, 
					   ::GetSysColor(COLOR_3DHIGHLIGHT), ::GetSysColor(COLOR_3DDKSHADOW));
			DrawCircleLeft(pDC, m_ptLeft, nRadius - 1, 
					   ::GetSysColor(COLOR_3DLIGHT), ::GetSysColor(COLOR_3DSHADOW));
			DrawCircleRight(pDC, m_ptRight, nRadius - 1, 
					   ::GetSysColor(COLOR_3DLIGHT), ::GetSysColor(COLOR_3DSHADOW));

			// draw connecting lines for stretched buttons only
			if (m_bStretch)
			{
				CPen* oldpen;

				oldpen = pDC->SelectObject(new CPen(PS_SOLID, 1, pDC->GetPixel(m_ptLeft.x, 1)));
				pDC->MoveTo(m_ptLeft.x, 1); pDC->LineTo(m_ptRight.x, 1);

				delete pDC->SelectObject(new CPen(PS_SOLID, 1, pDC->GetPixel(m_ptLeft.x, 2)));
				pDC->MoveTo(m_ptLeft.x, 2); pDC->LineTo(m_ptRight.x, 2);

				delete pDC->SelectObject(new CPen(PS_SOLID, 1, pDC->GetPixel(m_ptLeft.x, m_ptLeft.y + nRadius)));
				pDC->MoveTo(m_ptLeft.x, m_ptLeft.y + nRadius); pDC->LineTo(m_ptRight.x, m_ptLeft.y + nRadius);

				delete pDC->SelectObject(new CPen(PS_SOLID, 1, pDC->GetPixel(m_ptLeft.x, m_ptLeft.y + nRadius - 1)));
				pDC->MoveTo(m_ptLeft.x, m_ptLeft.y + nRadius - 1); pDC->LineTo(m_ptRight.x, m_ptLeft.y + nRadius - 1);
				
				delete pDC->SelectObject(oldpen);
			}
		}
	}
	
	// draw the text if there is any
	CString strText;
	GetWindowText(strText);

	if (!strText.IsEmpty())
	{
		CRgn rgn;

		if (m_bStretch){
		rgn.CreateRectRgn(m_ptLeft.x-nRadius/2, m_ptCentre.y-nRadius, 
			m_ptRight.x+nRadius/2, m_ptCentre.y+nRadius);}

		else{
		rgn.CreateEllipticRgn(m_ptCentre.x-nRadius, m_ptCentre.y-nRadius, 
			m_ptCentre.x+nRadius, m_ptCentre.y+nRadius);}

		pDC->SelectClipRgn(&rgn);

		CSize Extent = pDC->GetTextExtent(strText);
		CPoint pt = CPoint( m_ptCentre.x - Extent.cx/2, m_ptCentre.y - Extent.cy/2 );

		if (state & ODS_SELECTED) pt.Offset(1,1);

		pDC->SetBkMode(TRANSPARENT);

		if (state & ODS_DISABLED)
			pDC->DrawState(pt, Extent, strText, DSS_DISABLED, TRUE, 0, (HBRUSH)NULL);
		else
		{
			// changed this code to give the text a 3d-look
			COLORREF oldcol = pDC->SetTextColor(::GetSysColor(COLOR_3DHIGHLIGHT));
			pDC->TextOut(pt.x, pt.y, strText);
			pDC->SetTextColor(::GetSysColor(COLOR_3DDKSHADOW));
			pDC->TextOut(pt.x-1, pt.y-1, strText);
			pDC->SetTextColor(oldcol);
		}

		pDC->SelectClipRgn(NULL);
		rgn.DeleteObject();
	}

	// Draw the focus circle on the inside of the button if it is non-stretched
	if ((state & ODS_FOCUS) && m_bDrawDashedFocusCircle && !m_bStretch)
		DrawCircle(pDC, m_ptCentre, nRadius-2, RGB(0,0,0), TRUE);

	pDC->RestoreDC(nSavedDC);
}
