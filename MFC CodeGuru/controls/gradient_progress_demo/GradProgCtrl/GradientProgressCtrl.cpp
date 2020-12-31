// GradientProgressCtrl.cpp : implementation file
//
//
//
// Written by matt weagle (mweagle@redrose.net)
// Copyright (c) 1998.
//
// This code may be used in compiled form in any way you desire. This
// file may be redistributed unmodified by any means PROVIDING it is 
// not sold for profit without the authors written consent, and 
// providing that this notice and the authors name is included. If 
// the source code in  this file is used in any commercial application 
// then a simple email would be nice.
//
// This file is provided "as is" with no expressed or implied warranty.
// The author accepts no liability if it causes any damage whatsoever.
// Consider yourself lucky if it works, unlucky if it doesn't.
//
// Thanks to Chris Maunder (Chris.Maunder@cbr.clw.csiro.au) for the 
// foregoing disclaimer.
// 
// Please use and enjoy. Please let me know of any bugs/mods/improvements 
// that you have found/implemented and I will fix/incorporate them into this
// file. 

#include "stdafx.h"
#include "GradientProgressCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGradientProgressCtrl

CGradientProgressCtrl::CGradientProgressCtrl()
{
	// Defaults assigned by CProgressCtrl()
	m_nLower = 0;
	m_nUpper = 100;
	m_nCurrentPosition = 0;
	m_nStep = 10;	
	
	// Initial colors
	m_clrStart	= COLORREF(RGB(255, 0,0));
	m_clrEnd =	 COLORREF(RGB(0,0,255));
	m_clrBkGround = ::GetSysColor(COLOR_3DFACE);
	m_clrText = COLORREF(RGB(255, 255, 255));

	// Initial show percent
	m_bShowPercent = FALSE;
}

CGradientProgressCtrl::~CGradientProgressCtrl()
{
}


BEGIN_MESSAGE_MAP(CGradientProgressCtrl, CProgressCtrl)
	//{{AFX_MSG_MAP(CGradientProgressCtrl)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGradientProgressCtrl message handlers

/************************************************************************/
// The main drawing routine.  Consists of two parts
// (1) Call the DrawGradient routine to draw the visible part of the progress gradient
// (2) If needed, show the percentage text
/************************************************************************/
void CGradientProgressCtrl::OnPaint() 
{
	CPaintDC dc(this); // device context for painting

	// TODO: Add your message handler code here

	// If the current positionis  invalid then we should fade into the  background
	if (m_nCurrentPosition <= m_nLower || m_nCurrentPosition >= m_nUpper)
	{
		CRect rect;
		GetClientRect(rect);
		CBrush brush;
		brush.CreateSolidBrush(::GetSysColor(COLOR_3DFACE));
		dc.FillRect(&rect, &brush);
		VERIFY(brush.DeleteObject());
		return;
	}


	// Figure out what part should be visible so we can stop the gradient when needed
	CRect rectClient;
	GetClientRect(&rectClient);
	float maxWidth((float)m_nCurrentPosition/(float)m_nUpper * (float)rectClient.right);


	// Draw the gradient
	DrawGradient(&dc, rectClient, (int)maxWidth);

	// Show percent indicator if needed
	if (m_bShowPercent)
	{
		CString percent;
		percent.Format("%.0f%%", 100.0f*(float)m_nCurrentPosition/(float)m_nUpper);
		dc.SetTextColor(m_clrText);
		dc.SetBkMode(TRANSPARENT);
		dc.DrawText(percent, &rectClient, DT_VCENTER |  DT_CENTER | DT_SINGLELINE);
	}

	// Do not call CProgressCtrl::OnPaint() for painting messages
}


/*************************************************************************/
// Need to keep track of wher the indicator thinks it is.
/*************************************************************************/
void CGradientProgressCtrl:: SetRange(int nLower, int nUpper)
{
	m_nLower = nLower;
	m_nUpper = nUpper;
	m_nCurrentPosition = nLower;
	CProgressCtrl::SetRange(nLower, nUpper);
}

/*************************************************************************/
// Need to keep track of wher the indicator thinks it is.
/*************************************************************************/
int CGradientProgressCtrl:: SetPos(int nPos)
{
	m_nCurrentPosition = nPos;
	return (CProgressCtrl::SetPos(nPos));
}

/*************************************************************************/
// Need to keep track of wher the indicator thinks it is.
/*************************************************************************/
int CGradientProgressCtrl:: SetStep(int nStep)
{
	m_nStep = nStep;
	return (CProgressCtrl::SetStep(nStep));
}

/*************************************************************************/
// Need to keep track of wher the indicator thinks it is.
/*************************************************************************/
int CGradientProgressCtrl:: StepIt(void)
{
	m_nCurrentPosition += m_nStep;
	return (CProgressCtrl::StepIt());
}

/*************************************************************************/
// Where most of the actual work is done.  The general version would fill the entire rectangle with
// a gradient, but we want to truncate the drawing to reflect the actual progress control position.
/*************************************************************************/
void CGradientProgressCtrl::DrawGradient(CPaintDC *pDC, const RECT &rectClient, const int &nMaxWidth)
{
	RECT rectFill;			   // Rectangle for filling band
	float fStep;              // How wide is each band?
	CBrush brush;			// Brush to fill in the bar	

	
	CMemDC memDC(pDC);

	// First find out the largest color distance between the start and end colors.  This distance
	// will determine how many steps we use to carve up the client region and the size of each
	// gradient rect.
	int r, g, b;							// First distance, then starting value
	float rStep, gStep, bStep;		// Step size for each color

	// Get the color differences
	r = (GetRValue(m_clrEnd) - GetRValue(m_clrStart));
	g = (GetGValue(m_clrEnd) - GetGValue(m_clrStart));
	b =  (GetBValue(m_clrEnd) - GetBValue(m_clrStart));


	// Make the number of steps equal to the greatest distance
	int nSteps = max(abs(r), max(abs(g), abs(b)));

	// Determine how large each band should be in order to cover the
	// client with nSteps bands (one for every color intensity level)
	fStep = (float)rectClient.right / (float)nSteps;

	// Calculate the step size for each color
	rStep = r/(float)nSteps;
	gStep = g/(float)nSteps;
	bStep = b/(float)nSteps;

	// Reset the colors to the starting position
	r = GetRValue(m_clrStart);
	g = GetGValue(m_clrStart);
	b = GetBValue(m_clrStart);


	// Start filling bands
	for (int iOnBand = 0; iOnBand < nSteps; iOnBand++) 
	{
		
		::SetRect(&rectFill,
					(int)(iOnBand * fStep),       // Upper left X
					 0,									 // Upper left Y
					(int)((iOnBand+1) * fStep),          // Lower right X
					rectClient.bottom+1);			// Lower right Y
	
		// CDC::FillSolidRect is faster, but it does not handle 8-bit color depth
		VERIFY(brush.CreateSolidBrush(RGB(r+rStep*iOnBand, g + gStep*iOnBand, b + bStep *iOnBand)));
		memDC.FillRect(&rectFill,&brush);
		VERIFY(brush.DeleteObject());


		// If we are past the maximum for the current position we need to get out of the loop.
		// Before we leave, we repaint the remainder of the client area with the background color.
		if (rectFill.right > nMaxWidth)
		{
			::SetRect(&rectFill, rectFill.right, 0, rectClient.right, rectClient.bottom);
			VERIFY(brush.CreateSolidBrush(m_clrBkGround));
			memDC.FillRect(&rectFill, &brush);
			VERIFY(brush.DeleteObject());
			return;
		}
	}
}

/*************************************************************************/
// All drawing is done in the OnPaint function
/*************************************************************************/
BOOL CGradientProgressCtrl::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	return TRUE;
}
