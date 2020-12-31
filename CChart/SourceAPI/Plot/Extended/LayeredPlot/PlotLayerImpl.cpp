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
#include "PlotLayerImpl.h"

CPlotLayerImpl::CPlotLayerImpl()
{
}

CPlotLayerImpl::~CPlotLayerImpl()
{
	
}

CPlotLayerImpl& CPlotLayerImpl::operator=(const CPlotLayerImpl& rhs)
{
	CPlot::CopySettings(&rhs);
	CXYPlot::CopyAll(&rhs);
	return *this;
}

SIZE	CPlotLayerImpl::GetAxisSize( HDC hDC, int location )
{
	SIZE size={0,0};
	CAxis		*axis=GetAxisByLocation(location);
	if(axis==NULL)return size;
	
	SIZE		axisDims, paddingDims;
	axisDims = ((CAxisImpl *)axis)->GetMinDisplaySize( hDC );
	paddingDims = ((CAxisImpl *)axis)->GetPaddingSize( hDC );
	size=axisDims;
	
	switch(location)
	{
	case kLocationBottom:		
	case kLocationTop:
		size.cx+=(paddingDims.cx+paddingDims.cy);
		size.cy=axisDims.cy;
		break;
	case kLocationLeft:
	case kLocationRight:
		size.cy+=(paddingDims.cx+paddingDims.cy);
		size.cx=axisDims.cx;
		break;
	default: break;
	}
	
	return size;
}

void	CPlotLayerImpl::OnDraw( HWND hWnd )
{
	HDC hDC = GetDC(hWnd);
	RECT destRect;
	GetClientRect(hWnd,&destRect);
	
	OnDraw( hDC, destRect );
	
	ReleaseDC(hWnd, hDC);
}

void	CPlotLayerImpl::OnDraw( HDC hDC, RECT destRect )
{
	if(m_vXYDataInfo.size()<=0)
	{
		EraseBkgnd( hDC, destRect );
		return;
	}
	
	double	xRange[] = {1e30, -1e30}, yRange[]={1e30,-1e30};
	GetPlotRange( xRange, yRange );
	
	DrawDataSets( hDC, destRect, xRange, yRange );
	
	SetLastClientRect(destRect);
	m_LastPlotRect = destRect;
}

void	CPlotLayerImpl::DataToLP( HDC hDC, double *data, LPPOINT point )
{
	RECT		plotRect, tempRect;
	double		xRange[2], yRange[2];
	double		scaleX, scaleY;
	
	if( point == NULL || hDC == NULL ) return;
	
	tempRect = GetLastClientRect() ;
	//NormalizeRect(tempRect);
	if( IsRectEmpty(&tempRect) ) return;
	
	//plotRect = GetPlotRect( pDC, m_rctLastClientRect  );
	plotRect = m_LastPlotRect;
	
	GetRange( xRange, yRange );
	
	scaleX = (xRange[1] - xRange[0] ) / abs(plotRect.right - plotRect.left);
	scaleY = (yRange[1] - yRange[0] ) / abs(plotRect.bottom - plotRect.top);
	
	if( scaleX == 0. || scaleY == 0. ) return;
	
	point->x = (long)((data[0]-xRange[0]) / scaleX) + plotRect.left;
	point->y = -(long)((data[1]-yRange[0]) / scaleY) + plotRect.bottom;
}

void	CPlotLayerImpl::LPToData( HDC hDC, LPPOINT point, double *data )
{
	RECT		plotRect, tempRect;
	double		xRange[2], yRange[2];
	double		scaleX, scaleY;
	
	if( point == NULL || hDC == NULL ) return;
	
	tempRect = GetLastClientRect() ;
	//tempRect.NormalizeRect();
	if( IsRectEmpty( &tempRect) ) return;
	
	//plotRect = GetPlotRect( pDC, m_rctLastClientRect  );
	plotRect = m_LastPlotRect;
	
	GetRange( xRange, yRange );
	
	scaleX = (xRange[1] - xRange[0] ) / abs(plotRect.right - plotRect.left);
	scaleY = (yRange[1] - yRange[0] ) / abs(plotRect.bottom - plotRect.top);
	
	if( scaleX == 0. || scaleY == 0. ) return;
	
	data[0] = (point->x-plotRect.left) * scaleX + xRange[0];
	data[1] = -(point->y-plotRect.bottom) * scaleY + yRange[0];
}
