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
#include "XYPlotImpl.h"
#include "LegendImpl.h"
#include "PlotData.h"
#include "PlotUtility.h"

CLegendImpl::CLegendImpl(CPlot *pPlotImpl)
{
	m_pPlot = pPlotImpl;

	m_bCanShow = true;
	m_nRealLineLength = m_nLineLength;
	m_nRealFontHeight = m_lfFont.lfHeight;
}

CLegendImpl::~CLegendImpl()
{

}

RECT		CLegendImpl::GetInitialPlotRect(HDC hDC, RECT chartRect)
{
	CXYPlotImpl *pPlot = (CXYPlotImpl *)m_pPlot;
	
	RECT legendRect = {0,0,0,0};
	if(!pPlot)return legendRect;
	if(!pPlot->IsUseLegend())return legendRect;

	// init
	legendRect.bottom = (7*chartRect.top+chartRect.bottom)/8;
	legendRect.top = chartRect.top;
	legendRect.left = (chartRect.left+2*chartRect.right)/3;
	legendRect.right = chartRect.right;

	int nLegend = min(pPlot->GetDataSetCount(),m_nMaxNumOfLegend);
	
	HFONT		hOldFont, hFont;
	bool		keepGoing = true;
	SIZE		legendSize,tmSize;
	LOGFONT		logFont;
	int			i;
	string		strName;
	
	//adjust the font size
	logFont = m_lfFont;
	m_nRealLineLength = m_nLineLength;

	while( keepGoing == true )
	{
		hFont = CreateFontIndirect(&logFont);
		hOldFont = (HFONT)SelectObject(hDC,hFont);

		legendSize.cx = legendSize.cy = 0;
		for(i = 0;i<nLegend;i++)
		{
			strName = pPlot->GetAbsoluteDataTitle(i);
			if(strName.empty())strName = "Un";
			GetTextExtentPoint(hDC,strName.c_str(),strName.length(),&tmSize);
			if(tmSize.cx>legendSize.cx)legendSize.cx = tmSize.cx;
			legendSize.cy += tmSize.cy;
		}
		
		if( legendSize.cx+m_nRealLineLength+2*m_nMarginSize+m_nDragMarginSize > abs(legendRect.right-legendRect.left)
			|| legendSize.cy+2*m_nMarginSize> abs(legendRect.bottom-legendRect.top) )
		{
			if( legendSize.cx+m_nRealLineLength+2*m_nMarginSize+m_nDragMarginSize > abs(legendRect.right-legendRect.left) )
			{
				if( legendSize.cx+m_nRealLineLength+2*m_nMarginSize+m_nDragMarginSize > abs(chartRect.right-chartRect.left) )
				{
					if(logFont.lfHeight >=6 )
						logFont.lfHeight--;
					else
						m_nRealLineLength--;
				}
				else
				{
					keepGoing = false;
				}
			}
			if( legendSize.cy+2*m_nMarginSize> abs(legendRect.bottom-legendRect.top) )
			{
				if( legendSize.cy+2*m_nMarginSize> abs(chartRect.bottom-chartRect.top) )
				{
					if(logFont.lfHeight >=6 )
						logFont.lfHeight--;
					else
						m_nRealLineLength--;
				}
				else
				{
					keepGoing = false;
				}
			}
			
		}
		else
		{
			keepGoing = false;
		}
		
		if( logFont.lfHeight <= 4 || m_nRealLineLength <= 10 ) keepGoing = false;
		
		SelectObject(hDC,hOldFont);
		DeleteObject(hFont);
	}
	m_nRealFontHeight = logFont.lfHeight;

	// actual size
	legendRect.right = legendRect.left+legendSize.cx+m_nRealLineLength+2*m_nMarginSize+m_nDragMarginSize;
	legendRect.top = legendRect.bottom - legendSize.cy - 2*m_nMarginSize;

	m_bCanShow = true;
	// if it is too large
	if( abs(legendRect.right-legendRect.left)>abs(chartRect.right-chartRect.left) || abs(legendRect.bottom-legendRect.top)>abs(chartRect.bottom-chartRect.top) )
	{
		m_bCanShow = false;
		RECT nullRect = {0,0,0,0};
		return nullRect;
	}

	if(!m_bConfined)return legendRect;
	
	// if it is out of range
	if(legendRect.right > chartRect.right)//over the right border
	{
		legendRect.right = chartRect.right;
		legendRect.left = legendRect.right - legendSize.cx - m_nRealLineLength - 2*m_nMarginSize - m_nDragMarginSize;
	}
	if(legendRect.top < chartRect.top)
	{
		legendRect.top = chartRect.top;
		legendRect.bottom = legendRect.top + legendSize.cy + 2*m_nMarginSize;
	}
	return legendRect;
}

RECT		CLegendImpl::GetPlotRect(HDC hDC, RECT chartRect)
{
	CPlot *pPlot = (CPlot *)m_pPlot;

	RECT legendRect = {0,0,0,0};
	if(!pPlot)return legendRect;
	if(!pPlot->IsUseLegend())return legendRect;

	if(m_bDragMode)
	{
		SIZE offset = m_sizeOffsetOrigin;
		offset.cx+=(m_ptCurr.x-m_ptOrigin.x);
		offset.cy+=(m_ptCurr.y-m_ptOrigin.y);
		m_sizeOffset = offset;
	}

	legendRect = GetInitialPlotRect(hDC, chartRect);
	if(!m_bCanShow)
	{
		return legendRect;
	}

	// add the offset
	OffsetRect(&legendRect,m_sizeOffset.cx,m_sizeOffset.cy);
	if(!m_bConfined)return legendRect;
	
	// restrict in the rectangle
	int width = legendRect.right-legendRect.left;
	int height = legendRect.bottom - legendRect.top;
	if(legendRect.right > chartRect.right)
	{
		legendRect.right = chartRect.right;
		legendRect.left = legendRect.right - width;
	}
	if(legendRect.left < chartRect.left)
	{
		legendRect.left = chartRect.left;
		legendRect.right = legendRect.left + width;
	}
	if(legendRect.top < chartRect.top)
	{
		legendRect.top = chartRect.top;
		legendRect.bottom = legendRect.top + height;
	}
	if(legendRect.bottom > chartRect.bottom)
	{
		legendRect.bottom = chartRect.bottom;
		legendRect.top = legendRect.bottom - height;
	}
	return legendRect;
}

int			CLegendImpl::RegionIdentify(HDC hDC,POINT point)
{
	CXYPlotImpl *pPlot = (CXYPlotImpl *)m_pPlot;

	RECT plotRect,theRect;
	
	//data region
	plotRect = pPlot->GetPlotRect(hDC,pPlot->GetLastClientRect());

	// in legend rect
	theRect = GetPlotRect(hDC, plotRect);
	if(!PtInRect(&theRect,point) )
		return -1;
	theRect.left += m_nMarginSize + m_nDragMarginSize;
	theRect.right -= m_nMarginSize;
	theRect.top += m_nMarginSize;
	theRect.bottom -= m_nMarginSize;

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

void		CLegendImpl::OnDraw( HDC hDC, RECT plotRect)
{
	if(!m_pPlot)return;
	CXYPlotImpl *pPlot = (CXYPlotImpl *)m_pPlot;
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
	int i;

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
	for(i = 0;i<nLegend;i++)
	{
		if(!pPlot->IsDataShow(pPlot->GetDataID(i)))continue;
		
		hLinePen = CreatePen(pPlot->GetPlotLineStyle(pPlot->GetDataID(i)),pPlot->GetPlotLineSize(pPlot->GetDataID(i)),pPlot->GetPlotColor(pPlot->GetDataID(i)));
		SelectObject( hDC,hLinePen );

		crText = pPlot->GetPlotColor(pPlot->GetDataID(i));
		SetTextColor( hDC,crText );
		strName = pPlot->GetAbsoluteDataSet(i)->GetTitle();
		if(strName.empty())strName = "Un";
		GetTextExtentPoint(hDC,strName.c_str(),strName.length(),&tmSize);

		//Draw Marker
		POINT pt={legendRect.left+m_nMarginSize+m_nDragMarginSize+m_nRealLineLength/2, legendRect.top+long((i+0.5)*tmSize.cy)+m_nMarginSize};
		pPlot->DrawSolelyMarker(hDC,pt,i);

		//Draw Line
		if(!m_bColorRect)
		{
			if( pPlot->GetPlotType(pPlot->GetDataID(i)) != kXYPlotScatter )
			{
				MoveToEx(hDC,legendRect.left+m_nMarginSize+m_nDragMarginSize,legendRect.top+long((i+0.5)*tmSize.cy)+m_nMarginSize,NULL);
				LineTo(hDC,legendRect.left+m_nMarginSize+m_nDragMarginSize+m_nRealLineLength,legendRect.top+long((i+0.5)*tmSize.cy)+m_nMarginSize);
			}
		}
		else
		{
			HBRUSH hDataBrush = CreateSolidBrush(pPlot->GetXYDataInfo()[i].crPlotColor);
			HBRUSH hOldBrush = (HBRUSH)SelectObject( hDC,hDataBrush );
			RECT colorRect={legendRect.left+m_nMarginSize+m_nDragMarginSize, legendRect.top+i*tmSize.cy+m_nMarginSize, legendRect.left+m_nMarginSize+m_nDragMarginSize+m_nRealLineLength, legendRect.top+(i+1)*tmSize.cy+m_nMarginSize};
			Rectangle(hDC, colorRect.left, colorRect.top, colorRect.right, colorRect.bottom);
			SelectObject(hDC, hOldBrush);
			DeleteObject(hDataBrush);
		}

		//Draw Title
		TextOut(hDC,legendRect.left+m_nMarginSize+m_nDragMarginSize+m_nRealLineLength,legendRect.top+i*tmSize.cy+m_nMarginSize,strName.c_str(),strName.length());
		
		DeleteObject(hLinePen);

	}
	SelectObject( hDC,hOldFont );
	SelectObject( hDC,hOldPen );
	DeleteObject(hFont);
	DeleteObject(hBorderPen);
}