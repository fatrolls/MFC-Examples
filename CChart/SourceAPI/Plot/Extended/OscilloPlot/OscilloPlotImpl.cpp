/*============================================================================*/
/*                                                                            */
/*                            C O P Y R I G H T                               */
/*                                                                            */
/*                          (C) Copyright 2011 by                             */
/*                              Yang Guojun                                   */
/*                           All Rights Reserved                              */
/*                                                                            */
/*      The author assumes no responsibility for the use or reliability of    */
/*      his software.                                                         */
/*                                                                            */
/*============================================================================*/

/* ############################################################################################################################## */

#include "stdafx.h"
#include "OscilloPlotImpl.h"

/////////////////////////////////////////////////////////////////////////
// Class CPlot

COscilloPlotImpl::COscilloPlotImpl()
{
}

COscilloPlotImpl::~COscilloPlotImpl()
{
}

void	COscilloPlotImpl::OnDraw(HWND hWnd)
{
	HDC hDC = GetDC(hWnd);
	RECT destRect;
	GetClientRect(hWnd,&destRect);
	
	OnDraw( hDC, destRect );
	
	ReleaseDC(hWnd, hDC);
}

void	COscilloPlotImpl::OnDraw(HDC hDC, RECT destRect)
{
	//if there is no data, doing nothing
	if(m_vXYDataInfo.size()<=0)
	{
		CPlotImpl::EraseBkgnd( hDC, destRect );
		return;
	}
	SetLastClientRect(destRect);


	//////////////////////////////////////////////////////
	CPlotImpl::EraseBkgnd(hDC,destRect);
	// Get the size of our plotting rectangle
	RECT plotRect = GetPlotRect( hDC, destRect );
	// Draw Selelected zone
	DrawSelZone( hDC, plotRect );
	// Draw the cross
	DrawCursor(hDC, plotRect);
	// Draw basics
	bool erase = IsEraseBkgnd();
	SetEraseBkgnd(false);
	CXYPlotImpl::OnDraw(hDC,destRect);
	SetEraseBkgnd(erase);
}

void	COscilloPlotImpl::DrawCursor( HDC hDC, RECT plotRect )
{
	if(!m_bShowHCursor && !m_bShowVCursor)return;

	double xRange[2],yRange[2];
	GetPlotRange(xRange,yRange);

	if(m_fCursorX<xRange[0] || m_fCursorX>xRange[1] || m_fCursorY<yRange[0] || m_fCursorY>yRange[1])return;
	
	HPEN		hPen, hOldPen;
	hPen=CreatePen( m_nCursorStyle, m_nCursorSize, m_crCursorColor );
	hOldPen = (HPEN)SelectObject( hDC, hPen );

	double data[2];
	POINT point;
	data[0]=m_fCursorX;
	data[1]=m_fCursorY;

	DataToLP(hDC,data,&point);
	
	// Bound to a curve
	if(m_bHoldCursorToCurve && m_nIndexToHoldCursor>=0 
		&& m_nIndexToHoldCursor < GetDataSetCount() )
	{
		double dt[2];
		if(GetNeareastDataPoint(GetDataID(m_nIndexToHoldCursor), hDC, point, dt)>=0)
		{
			data[1]=dt[1];
			DataToLP(hDC,data,&point);
		}
	}	

	if(m_bShowHCursor)
	{
		MoveToEx(hDC,plotRect.left,point.y,NULL);
		LineTo(hDC,plotRect.right,point.y);
	}
	if(m_bShowVCursor)
	{
		MoveToEx(hDC, point.x,plotRect.bottom,NULL);
		LineTo(hDC, point.x,plotRect.top);
	}

	SelectObject( hDC, hOldPen );
	DeleteObject(hPen);
}

void	COscilloPlotImpl::DrawSelZone( HDC hDC, RECT plotRect )
{
	bool xDraw=true,yDraw=true;
	if( !m_bEnableXZoneSel )xDraw=false;
	if(m_fXZoneSelLower>m_fXZoneSelUpper)xDraw=false;
	if( !m_bEnableYZoneSel )yDraw=false;
	if(m_fYZoneSelLower>m_fYZoneSelUpper)yDraw=false;

	double xRange[2],yRange[2];
	GetPlotRange(xRange,yRange);
	if(m_fXZoneSelLower>xRange[1] || m_fXZoneSelUpper<xRange[0])xDraw=false;
	if(m_fXZoneSelLower<xRange[0] && m_fXZoneSelUpper>xRange[1])xDraw=false;
	if(m_fYZoneSelLower>yRange[1] || m_fYZoneSelUpper<yRange[0])yDraw=false;
	if(m_fYZoneSelLower<yRange[0] && m_fYZoneSelUpper>yRange[1])yDraw=false;

	if(!xDraw && !yDraw)return;

	HPEN		hPen0,hPen1, hOldPen;
	hPen0=CreatePen( PS_SOLID, 0, m_crZoneSelColor );
	hPen1=CreatePen( PS_SOLID, 1, m_crLightColor );
	hOldPen = (HPEN)SelectObject( hDC, hPen0 );
	
	HBRUSH		hBrush, hOldBrush;
	hBrush=CreateSolidBrush( m_crZoneSelColor );
	hOldBrush = (HBRUSH)SelectObject( hDC, hBrush );

	int xlow,xupp,ylow,yupp;
	double data[2];
	POINT point;
	if(xDraw)
	{
		data[1]=0.0;
		data[0]=m_fXZoneSelLower;	
		DataToLP(hDC,data,&point);
		xlow=point.x;
		data[0]=m_fXZoneSelUpper;
		DataToLP(hDC,data,&point);
		xupp=point.x;

		if(m_fXZoneSelLower>xRange[0] && m_fXZoneSelUpper<xRange[1])
		{
			RECT lightRect = plotRect;
			lightRect.left = xlow;
			lightRect.right = xupp;
			Rectangle(hDC,lightRect.left,lightRect.top,lightRect.right,lightRect.bottom);
		}
	}
	if(yDraw)
	{
		data[0]=0.0;
		data[1]=m_fYZoneSelLower;
		DataToLP(hDC,data,&point);
		ylow=point.y;
		data[1]=m_fYZoneSelUpper;
		DataToLP(hDC,data,&point);
		yupp=point.y;

		if(m_fYZoneSelLower>yRange[0] && m_fYZoneSelUpper<yRange[1])
		{
			RECT lightRect = plotRect;
			lightRect.top = yupp;
			lightRect.bottom = ylow;
			Rectangle(hDC,lightRect.left,lightRect.top,lightRect.right,lightRect.bottom);
		}
	}

	SelectObject( hDC, hPen1 );
	if(xDraw)
	{
		if(m_fXZoneSelLower>xRange[0] && m_fXZoneSelLower<xRange[1])
		{
			MoveToEx(hDC,xlow,plotRect.top,NULL);
			LineTo(hDC,xlow,plotRect.bottom);
		}
		if(m_fXZoneSelUpper>xRange[0] && m_fXZoneSelUpper<xRange[1])
		{
			MoveToEx(hDC,xupp,plotRect.top,NULL);
			LineTo(hDC,xupp,plotRect.bottom);
		}
	}
	if(yDraw)
	{
		if(m_fYZoneSelLower>yRange[0] && m_fYZoneSelLower<yRange[1])
		{			
			MoveToEx(hDC,plotRect.left,ylow,NULL);
			LineTo(hDC,plotRect.right,ylow);
		}
		if(m_fYZoneSelUpper>yRange[0] && m_fYZoneSelUpper<yRange[1])
		{
			MoveToEx(hDC,plotRect.left,yupp,NULL);
			LineTo(hDC,plotRect.right,yupp);
		}
	}

	SelectObject( hDC,hOldBrush );
	DeleteObject(hBrush);
	SelectObject( hDC,hOldPen );
	DeleteObject( hPen0 );
	DeleteObject( hPen1 );
}
