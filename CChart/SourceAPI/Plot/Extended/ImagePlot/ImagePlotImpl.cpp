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

#include "StdAfx.h"
#include "ImagePlotImpl.h"
#include "ImageLegendImpl.h"
#include "../../Basics/PlotUtility.h"

CImagePlotImpl::CImagePlotImpl()
{
	if(m_pLegend)
	{
		DeleteLegend();
	}
	m_pLegend = new CImageLegendImpl(this);
	m_bUseLegend = true;
}

CImagePlotImpl::~CImagePlotImpl()
{

}

void	CImagePlotImpl::OnDraw( HWND hWnd )
{
	HDC hDC = GetDC(hWnd);
	RECT destRect;
	GetClientRect(hWnd,&destRect);
	
	OnDraw( hDC, destRect );
	
	ReleaseDC(hWnd, hDC);
}

void	CImagePlotImpl::OnDraw(HDC hDC, RECT destRect)
{
	// Get ranges for plotting
	double xRange[2], yRange[2];
	GetPlotRange( xRange, yRange );
	// Get the size of our plotting rectangle
	RECT plotRect = GetPlotRect( hDC, destRect );
	// Erase
	// Draw the legend
	EraseBkgnd(hDC, destRect);	

	// Draw the map
	StretchBlt(hDC, plotRect.left, plotRect.top, abs(plotRect.right-plotRect.left), abs(plotRect.bottom-plotRect.top), m_hMemImageDC, 0, 0, m_nWidth, m_nHeight, SRCCOPY);

	// Draw basics
	CPlotImpl::OnDraw(hDC,destRect);
}

string	CImagePlotImpl::GetAbsoluteDataTitle( int which )
{
	return ((CImageLegendImpl*)m_pLegend)->GetLegendTitle(which);
}

void	CImagePlotImpl::GetPlotRange( double *xRange, double *yRange )
{
	memcpy(xRange, m_fXRange, sizeof(double)*2);
	memcpy(yRange, m_fYRange, sizeof(double)*2);

	bool		haveXRange = false, haveYRange = false;
	bool		haveBottom = false, haveLeft = false;
	CAxis		*axis;
	int			i;
	double		optRange[2];
	int			optNTicks, optMinorTicks;

	// Now that we've autoranged, set up the autoranged axses
	haveLeft = haveBottom = false;
	for( i = 0; i < GetAxisCount(); i++ )
	{
		axis = GetAxis(i);
		{

			switch( axis->GetLocation() )
			{
			case kLocationTop:
			case kLocationCenterHB:
			case kLocationCenterHT:
				// fall through
			case kLocationBottom:
				axis->SetRange(xRange[0], xRange[1]);
				GetOptimalRangeExact( xRange, optRange, &optNTicks, &optMinorTicks );
				memcpy( xRange, optRange, 2*sizeof( double ) );
				if(axis->IsAutoMajorTick()) axis->SetTickCount( optNTicks );
				if(axis->IsAutoMinorTick()) axis->SetMinorTickCount( optMinorTicks );
				break;
			case kLocationRight:
			case kLocationCenterVL:
			case kLocationCenterVR:
				// fall through
			case kLocationLeft:
				axis->SetRange(yRange[0], yRange[1]);
				GetOptimalRangeExact( yRange, optRange, &optNTicks, &optMinorTicks );
				memcpy( yRange, optRange, 2*sizeof( double ) );
				if(axis->IsAutoMajorTick()) axis->SetTickCount( optNTicks );
				if(axis->IsAutoMinorTick()) axis->SetMinorTickCount( optMinorTicks );
				haveLeft = true;
				break;
			default: break;
			}
		}
	}
}
/*
bool	CImagePlotImplI::OnMouseDown( HWND hWnd, POINT point )
{
	if(GetDataSetCount()<=0) return false;
	
	HDC hDC = GetDC( hWnd );

	// Capture
	SetCapture(hWnd);
	RECT clientRect;
	GetClientRect(hWnd, &clientRect);
	ClientToScreen(hWnd,(LPPOINT)&clientRect);
	ClientToScreen(hWnd,(LPPOINT)&clientRect+1);
	ClipCursor(&clientRect);
	// end

	bool needUpdate = false;
	
	DPtoLP( hDC, &point,1);
	
	//Set Drag mode
	int which = ((CLegendImpl *)GetLegend())->RegionIdentify(hDC,point);
	if(which>=0)
	{
		GetLegend()->SetDragMode(true,point);

		ReleaseDC(hWnd, hDC);
		return true;
	}
	
	ReleaseDC(hWnd, hDC);
	return false;
}

bool	CImagePlotImplI::OnMouseUp( HWND hWnd, POINT point )
{
	if(GetLegend()->IsDragMode())GetLegend()->SetDragMode(false,point);
	if(GetCapture())ReleaseCapture();
	ClipCursor(NULL);

	return false;
}

bool	CImagePlotImplI::OnMouseDblClk( HWND hWnd, POINT point )
{
	return false;
}

bool	CImagePlotImplI::OnMouseMove( HWND hWnd, POINT point )
{
	if(GetDataSetCount()<=0) return false;

	HDC hDC = GetDC( hWnd );

	static int loc0=-1;
	static bool light_title0=false;
	static bool light_dataregion0=false;

	bool needUpdate = false;

	if(GetDataSetCount()<=0) goto mousemove_return;
	
	DPtoLP( hDC, &point,1);

	if(GetLegend()->IsDragMode())
	{
		GetLegend()->SetCurrentPoint(point);
		needUpdate = true;
		goto mousemove_return;
	}

	int which;

	CAxis *axis;
	int location;
	bool light_title,light_dataregion;
	int region;
	region=RegionIdentify(hDC,point);
	switch(region)
	{
	case kXYRegionData:
		if(AxisLighted())
		{
			UnlightAllAxis();
			if(loc0>=0)
			{
				needUpdate = true;
			}
			loc0=-1;
		}
		//如果处于legend区域
		which=((CLegendImpl *)GetLegend())->RegionIdentify(hDC,point);
		if(which>=0)
		{
			GetLegend()->SetCurrent(true);
		}
		else
		{
			GetLegend()->SetCurrent(false);
		}
		break;
	
	case kXYRegionBottom:
		location=kLocationBottom;
		goto LightAxis;
	case kXYRegionTop:
		location=kLocationTop;
		goto LightAxis;
	case kXYRegionLeft:
		location=kLocationLeft;
		goto LightAxis;
	case kXYRegionRight:
		location=kLocationRight;
LightAxis:
		axis=GetAxisByLocation(location);
		if(axis)
		{
			UnlightAllAxis();
			axis->SetCurrent(true);
			if(location!=loc0)
			{
				needUpdate = true;
			}
			loc0=location;
		}
		break;
	default:
		// unlignt axis
		if(AxisLighted())
		{
			UnlightAllAxis();
			if(loc0>=0)
			{
				needUpdate = true;
			}
			loc0=-1;
		}
		break;
	}

	if(region == kXYRegionTitle)
	{		
		light_title=true;
		if(light_title != light_title0)
		{
			SetLightTitle(true);
			needUpdate = true;
		}
		light_title0=light_title;
	}
	else
	{
		// unlight title
		if(IsLightTitle())
		{
			SetLightTitle(false);
			if(light_title0)
			{
				needUpdate = true;
			}
			light_title0=false;
		}
	}

	if(region == kXYRegionData)
	{		
		light_dataregion=true;
		if(light_dataregion != light_dataregion0)
		{
			SetLightDataRegion(true);
			needUpdate = true;
		}
		light_dataregion0=light_dataregion;
	}
	else
	{
		// unlight data region
		if(IsLightDataRegion())
		{
			SetLightDataRegion(false);
			if(light_dataregion0)
			{
				needUpdate = true;
			}
			light_dataregion0=false;
		}
	}

mousemove_return:
	ReleaseDC(hWnd,hDC);
	return needUpdate;
}

bool	CImagePlotImplI::OnContextMenu(HMENU hMenu, HWND hWnd, POINT point  )
{
	return false;
}
*/