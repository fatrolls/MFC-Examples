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
#include "LayeredLegendImpl.h"
#include "LayeredPlotImpl.h"
#include "PlotLayerImpl.h"

CLayeredLegendImpl::CLayeredLegendImpl(CPlot *pPlotImpl) : CLegendImpl(pPlotImpl)
{

}

CLayeredLegendImpl::~CLayeredLegendImpl()
{

}

int		CLayeredLegendImpl::RegionIdentify(HDC hDC,POINT point)
{
	CLayeredPlotImpl *pPlot = (CLayeredPlotImpl *)m_pPlot;
	
	RECT plotRect,theRect;
	
	//data region
	plotRect = pPlot->GetPlotRect(hDC,pPlot->GetLastClientRect());
	
	// in legend rect
	theRect = GetPlotRect(hDC, plotRect);
	//if( (theRect.right-point.x)*(point.x-theRect.left)<0 || (theRect.top-point.y)*(point.y-theRect.bottom)<0 )
	if(!PtInRect(&theRect,point) )
		return -1;
	theRect.left += m_nMarginSize + m_nDragMarginSize;
	theRect.right -= m_nMarginSize;
	theRect.top += m_nMarginSize;
	theRect.bottom -= m_nMarginSize;
	
	//if( (theRect.right-m_nMarginSize-point.x)*(point.x-theRect.left-m_nMarginSize-m_nDragMarginSize)>0 && (theRect.bottom-m_nMarginSize-point.y)*(point.y-theRect.top-m_nMarginSize)>0 )
	if(PtInRect(&theRect,point))
	{
		HFONT		hOldFont, hFont;
		LOGFONT		logFont;
		string		strName;
		
		logFont = m_lfFont;
		hFont = CreateFontIndirect(&logFont);
		hOldFont = (HFONT)SelectObject(hDC,hFont);
		strName = "Un";
		SIZE tmSize;
		GetTextExtentPoint(hDC, strName.c_str(),strName.length(), &tmSize );
		SelectObject( hDC, hOldFont );
		DeleteObject(hFont);
		
		int nLegend = min(pPlot->GetDataSetCount(),m_nMaxNumOfLegend);
		
		int idx = (point.y-theRect.top-m_nMarginSize)/tmSize.cy;
		if(idx<0)idx = 0;
		else if(idx >= nLegend)idx = nLegend-1;
		
		return idx;
	}
	else
	{
		return pPlot->GetDataSetCount();
	}
}

void	CLayeredLegendImpl::OnDraw( HDC hDC, RECT plotRect)
{
	if(!m_pPlot)return;
	CLayeredPlotImpl *pPlot = (CLayeredPlotImpl *)m_pPlot;
	if(pPlot->GetDataSetCount()<=0)return;
	
	RECT legendRect = GetPlotRect(hDC,plotRect);
	if(!m_bCanShow)
	{
		m_bCanShow = true;
		return;
	}
	
	COLORREF bordercolor;
	if(m_bCurrent)
	{
		bordercolor = pPlot->GetLightColor();
	}
	else
	{
		bordercolor = m_crBorderColor;
	}
	HPEN		hBorderPen, hOldPen;
	hBorderPen = CreatePen( m_nBorderLineStyle, m_nBorderLineSize, bordercolor );
	
	hOldPen = (HPEN)SelectObject( hDC,hBorderPen );
	if(m_bTransparent)
	{
		HBRUSH hBrush = (HBRUSH) GetStockObject(NULL_BRUSH),hOldBrush;
		hOldBrush = (HBRUSH)SelectObject(hDC,hBrush);
		Rectangle(hDC,legendRect.left,legendRect.top,legendRect.right,legendRect.bottom);
		SelectObject(hDC,hOldBrush);
		DeleteObject(hBrush);
	}
	else
	{
		HBRUSH hBrush, hOldBrush;
		hBrush = CreateSolidBrush(m_crBkgndColor);
		hOldBrush = (HBRUSH)SelectObject(hDC,hBrush);
		Rectangle(hDC,legendRect.left,legendRect.top,legendRect.right,legendRect.bottom);
		SelectObject(hDC,hOldBrush);
		DeleteObject(hBrush);
	}
	
	int nLegend = min(pPlot->GetDataSetCount(),m_nMaxNumOfLegend);
	int i,j;
	
	HFONT	hOldFont, hFont;
	LOGFONT logFont;
	HPEN hLinePen;
	COLORREF crText;
	SIZE	tmSize;
	string	strName;
	
	SetBkMode( hDC,TRANSPARENT );
	logFont = m_lfFont;
	logFont.lfHeight = m_nRealFontHeight;
	hFont = CreateFontIndirect(&logFont);
	hOldFont = (HFONT)SelectObject(hDC,hFont);

	int count=0;
	for(i=0;i<pPlot->GetNumOfLayers();i++)
	{
		CPlotLayerImpl *pLayer=((CPlotLayerImpl *)pPlot->GetLayer(i));
		for(j=0;j<pLayer->GetDataSetCount();j++)
		{
			
			if(!pLayer->IsDataShow(pLayer->GetDataID(j)))continue;
			hLinePen = CreatePen(pLayer->GetPlotLineStyle(pLayer->GetDataID(j)),pLayer->GetPlotLineSize(pLayer->GetDataID(j)),pLayer->GetPlotColor(pLayer->GetDataID(j)));
			SelectObject( hDC, hLinePen );
			
			crText=pLayer->GetPlotColor(pLayer->GetDataID(j));
			SetTextColor( hDC, crText );
			strName=pLayer->GetAbsoluteDataSet(j)->GetTitle();
			if(strName.empty())strName="Un";
			//tmSize=pDC->GetTextExtent(strName);
			GetTextExtentPoint(hDC, strName.c_str(), strName.length(), &tmSize);
			
			//Draw Marker
			POINT pt={legendRect.left+m_nMarginSize+m_nDragMarginSize+m_nRealLineLength/2,legendRect.top+long((i+0.5)*tmSize.cy)+m_nMarginSize};
			pLayer->DrawSolelyMarker(hDC,pt,j);
			
			//Draw Line
			if(pLayer->GetPlotType(pLayer->GetDataID(j))!=kXYPlotScatter )
			{
				MoveToEx(hDC, legendRect.left+m_nMarginSize+m_nDragMarginSize,legendRect.top+long((count+0.5)*tmSize.cy)+m_nMarginSize, NULL);
				LineTo(hDC, legendRect.left+m_nMarginSize+m_nDragMarginSize+m_nRealLineLength,legendRect.top+long((count+0.5)*tmSize.cy)+m_nMarginSize);
			}
			
			//Draw Title
			TextOut(hDC, legendRect.left+m_nMarginSize+m_nDragMarginSize+m_nRealLineLength,legendRect.top+count*tmSize.cy+m_nMarginSize,strName.c_str(), strName.length());
			count++;

			DeleteObject(hLinePen);

			if(count>=nLegend)break;
		}
		if(count>=nLegend)break;
	}
	SelectObject( hDC,hOldFont );
	SelectObject( hDC,hOldPen );
	DeleteObject(hFont);
	DeleteObject(hBorderPen);
}
