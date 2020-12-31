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
#include "AxisImpl.h"
#include <sstream>

/////////////////////////////////////////////////////////////////////////
// Class CAxisImpl

CAxisImpl::CAxisImpl(CPlot	*plot)
{
	m_pPlot = plot;
	m_nRealTitleHeight = m_lfTitleFont.lfHeight;
	m_nRealTickLabelHeight = m_lfLabelFont.lfHeight;
}

CAxisImpl::~CAxisImpl()
{
}

/////////////////////////////////////////////////////////////////////////
// implement

RECT	CAxisImpl::GetPlotRect( HDC hDC, RECT clientRect, RECT chartRect )
{
	RECT plotRect;
	SIZE axisDims, paddingDims;
	plotRect=chartRect;
	axisDims = GetMinDisplaySize( hDC );
	paddingDims = GetPaddingSize( hDC );
	
	switch( GetLocation() )
	{
	case kLocationBottom:
		plotRect.top=chartRect.bottom;
		plotRect.bottom=plotRect.top+axisDims.cy;

		plotRect.left-=paddingDims.cx;
		plotRect.right+=paddingDims.cy;
		break;
	case kLocationTop:
		plotRect.bottom=chartRect.top;
		plotRect.top=plotRect.bottom-axisDims.cy;

		plotRect.left-=paddingDims.cx;
		plotRect.right+=paddingDims.cy;
		break;
	case kLocationLeft:
		plotRect.right=chartRect.left;
		plotRect.left=plotRect.right-axisDims.cx;

		plotRect.bottom+=paddingDims.cx;
		plotRect.top-=paddingDims.cy;
		break;
	case kLocationRight:
		plotRect.left=chartRect.right;
		plotRect.right=plotRect.left+axisDims.cx;

		plotRect.bottom+=paddingDims.cx;
		plotRect.top-=paddingDims.cy;
		break;
	case kLocationCenterVL:
		plotRect.right = (chartRect.left + chartRect.right)/2;
		plotRect.left = plotRect.right - axisDims.cy;

		plotRect.bottom+=paddingDims.cx;
		plotRect.top-=paddingDims.cy;
		break;
	case kLocationCenterVR:
		plotRect.left = (chartRect.left + chartRect.right)/2;
		plotRect.right = plotRect.left + axisDims.cy;
		
		plotRect.bottom+=paddingDims.cx;
		plotRect.top-=paddingDims.cy;
		break;
	case kLocationCenterHB:
		plotRect.top = (chartRect.top + chartRect.bottom)/2;
		plotRect.bottom = plotRect.top + axisDims.cy;

		plotRect.left-=paddingDims.cx;
		plotRect.right+=paddingDims.cy;
		break;
	case kLocationCenterHT:
		plotRect.bottom = (chartRect.top + chartRect.bottom)/2;
		plotRect.top = plotRect.bottom + axisDims.cy;
		
		plotRect.left-=paddingDims.cx;
		plotRect.right+=paddingDims.cy;
		break;
	default:
		break;
	}
	return plotRect;
}

int	CAxisImpl::GetMaxTickLength()
{
	int mtlen=0;
	// Addint the major tick
	switch(m_nTickPosition)
	{
	case kTickPositionInner:
		if(m_nTickLength>mtlen)mtlen=m_nTickLength;
		break;
	case kTickPositionBoth:
		if(m_nTickLength/2>mtlen)mtlen=m_nTickLength/2;
		break;
	default:
		break;
	}
	// Addin the minor tick
	switch(m_nMinorTickPosition)
	{
	case kTickPositionInner:
		if(m_nMinorTickLength>mtlen)mtlen=m_nMinorTickLength;
		break;
	case kTickPositionBoth:
		if(m_nMinorTickLength/2>mtlen)mtlen=m_nMinorTickLength/2;
		break;
	default:
		break;
	}
	return mtlen;
}

SIZE CAxisImpl::GetRealTickLabelDimension(HDC hDC, RECT chartRect)
{
	bool			keepGoing = true;
	HFONT			hFont,hOldFont;
	LOGFONT			logFont;

	int				nMaxLabelWidth;
	int				i;
	string			tickLabel;
	int				tickHeight=0;
	SIZE			labelExtent={0,0};

	logFont=m_lfLabelFont;

	// Set up font and make sure that the font size will fit
	// the width or height of our chart
	while( keepGoing == true )
	{
		//pOldFont = MySelectFont( pDC, &font, &logFont );
		hFont = CreateFontIndirect(&logFont);
		hOldFont = (HFONT)SelectObject(hDC,hFont);
		nMaxLabelWidth=0;
		for(i=0;i<GetTickCount();i++)
		{
			tickLabel=GetTickLabel(i);
			GetTextExtentPoint(hDC, tickLabel.c_str(),tickLabel.length(),&labelExtent );
			if(labelExtent.cx>nMaxLabelWidth)nMaxLabelWidth=labelExtent.cx;
		}
		switch( GetLocation() )
		{
		case kLocationBottom:
		case kLocationTop:
		case kLocationCenterHB:
		case kLocationCenterHT:
			if( nMaxLabelWidth > abs(chartRect.right - chartRect.left) / GetTickCount() && logFont.lfHeight > 4 )
				logFont.lfHeight--;
			else
				keepGoing = false;
			break;
		case kLocationLeft:
		case kLocationRight:
		case kLocationCenterVL:
		case kLocationCenterVR:
			if( labelExtent.cy > abs(chartRect.bottom - chartRect.top) / GetTickCount() && logFont.lfHeight > 4  )
				logFont.lfHeight--;
			else
				keepGoing = false;
			break;
		}
	
		//pDC->SelectObject( pOldFont );
		SelectObject(hDC, hOldFont);
		DeleteObject(hFont);
	}

	m_nRealTickLabelHeight = logFont.lfHeight;
	labelExtent.cx = nMaxLabelWidth;
	return labelExtent;
}

int	CAxisImpl::GetRealTitleHeight(HDC hDC, RECT clientRect, RECT chartRect)
{
	bool keepGoing;
	HFONT hFont,hOldFont;
	LOGFONT logFont;
	SIZE tmSize;

	keepGoing = true;
	logFont=m_lfTitleFont;
	if( m_nTitlePosition == kTitlePositionNormal )
	{
		while( keepGoing == true )
		{
			hFont = CreateFontIndirect(&logFont);
			hOldFont = (HFONT)SelectObject(hDC,hFont);
			GetTextExtentPoint(hDC,m_strTitle.c_str(),m_strTitle.length(),&tmSize);
			SelectObject(hDC, hOldFont );
			DeleteObject(hFont);

			switch( GetLocation() )
			{
			case kLocationLeft:
			case kLocationRight:
			case kLocationCenterVL:
			case kLocationCenterVR:
				if( tmSize.cx > abs(chartRect.bottom - chartRect.top) )
					logFont.lfHeight--;
				else
					keepGoing = false;
				break;
			case kLocationTop:
			case kLocationBottom:
			case kLocationCenterHB:
			case kLocationCenterHT:
				if( tmSize.cx > abs(chartRect.right - chartRect.left) )
					logFont.lfHeight--;
				else
					keepGoing = false;
				break;
			}

			if( logFont.lfHeight <= 4 ) keepGoing = false;
		}
	}
	m_nRealTitleHeight = logFont.lfHeight;
	return logFont.lfHeight;
}

RECT CAxisImpl::GetTitleRect(HDC hDC, RECT clientRect, RECT chartRect)
{
	RECT textRect=clientRect;

	bool			keepGoing;
	HFONT			hFont,hOldFont;
	LOGFONT			logFont;
	SIZE			tmSize;

	long			width,height;
	SIZE			paddingSize=GetPaddingSize(hDC);
	string			tickLabel;
	SIZE			MaxLabelExtent={0,0};

	keepGoing = true;

	//calc the size of tick labels
	if(m_bShowTickLabel)
	{
		MaxLabelExtent = GetRealTickLabelDimension(hDC, chartRect);
	}

	logFont=m_lfTitleFont;
	logFont.lfHeight = GetRealTitleHeight(hDC, clientRect, chartRect);

	hFont = CreateFontIndirect(&logFont);
	hOldFont = (HFONT)SelectObject(hDC,hFont);
	GetTextExtentPoint(hDC,m_strTitle.c_str(),m_strTitle.length(),&tmSize);
	SelectObject(hDC, hOldFont );
	DeleteObject(hFont);

	// Find the rectangle that encloses our axis title
	switch( GetLocation() )
	{
	case kLocationLeft:
	case kLocationCenterVL:
		if( m_nTitlePosition == kTitlePositionNormal )
		{
			// This is the good rect
			textRect = chartRect;
			if(GetLocation()==kLocationLeft)
				textRect.right = chartRect.left - 5 - MaxLabelExtent.cx - GetMaxTickLength();
			else 
				textRect.right = (chartRect.left + chartRect.right)/2;
			textRect.left = textRect.right - tmSize.cy;
			height = chartRect.bottom - chartRect.top;

			// Adjust position for font orientation and size
			textRect.top = chartRect.top + height/2 - tmSize.cx/2;
			textRect.bottom = textRect.top + tmSize.cx;
		}
		else
		{
			if( m_nTitlePosition == kTitlePositionLower )
			{
				textRect = GetPlotRect(hDC,clientRect,chartRect);
				textRect.top = chartRect.bottom+paddingSize.cx;
				textRect.bottom = textRect.top+tmSize.cy;
				textRect.left=chartRect.left-tmSize.cx/2;
				textRect.right=textRect.left+tmSize.cx;

			}
			else
			{
				textRect = GetPlotRect(hDC,clientRect,chartRect);
				textRect.bottom = chartRect.top-paddingSize.cy;
				textRect.top = textRect.bottom-tmSize.cy;
				textRect.left=chartRect.left-tmSize.cx/2;
				textRect.right=textRect.left+tmSize.cx;
			}
		}
		break;
	case kLocationRight:
	case kLocationCenterVR:
		if( m_nTitlePosition == kTitlePositionNormal )
		{
			height = chartRect.bottom-chartRect.top;

			if(GetLocation()==kLocationRight)
				textRect.left = chartRect.right + 5 + MaxLabelExtent.cx + GetMaxTickLength();
			else
				textRect.left = (chartRect.left + chartRect.right)/2;
			textRect.right = textRect.left + tmSize.cy;

			// position
			textRect.top = chartRect.top + height/2 - tmSize.cx;
			textRect.bottom = textRect.top + tmSize.cx;
		}
		else
		{
			if( m_nTitlePosition == kTitlePositionLower )
			{
				textRect = GetPlotRect(hDC,clientRect,chartRect);
				textRect.top = chartRect.bottom+paddingSize.cx;
				textRect.bottom = textRect.top+tmSize.cy;
				textRect.left=chartRect.right-tmSize.cx/2;
				textRect.right=textRect.left+tmSize.cx;

			}
			else
			{
				textRect = GetPlotRect(hDC,clientRect,chartRect);
				textRect.bottom = chartRect.top-paddingSize.cy;
				textRect.top = textRect.bottom-tmSize.cy;
				textRect.left=chartRect.right-tmSize.cx/2;
				textRect.right=textRect.left+tmSize.cx;
			}
		}
		break;
	case kLocationTop:
	case kLocationCenterHT:
		textRect = chartRect;
		if(GetLocation()==kLocationTop)
			textRect.bottom = chartRect.top - 5 - MaxLabelExtent.cy - GetMaxTickLength();
		else
			textRect.bottom = (chartRect.top + chartRect.bottom)/2;
		textRect.top = textRect.bottom - tmSize.cy;

		width = chartRect.right - chartRect.left; 
		textRect.left = chartRect.left + width/2 - tmSize.cx/2;
		textRect.right = textRect.left + tmSize.cx;

		logFont.lfEscapement = 0;
		logFont.lfOrientation = 0;

		break;
	case kLocationBottom:
	case kLocationCenterHB:
		textRect = chartRect;
		if(GetLocation()==kLocationBottom)
			textRect.top = chartRect.bottom + 5 + MaxLabelExtent.cy + GetMaxTickLength();
		else
			textRect.top = (chartRect.top + chartRect.bottom)/2;
		textRect.bottom = textRect.top + tmSize.cy;

		width = chartRect.right - chartRect.left; 
		textRect.left = chartRect.left + width/2 - tmSize.cx/2;
		textRect.right = textRect.left + tmSize.cx;

		logFont.lfEscapement = 0;
		logFont.lfOrientation = 0;

		break;
	}
	return textRect;
}

void CAxisImpl::OnDraw(HDC hDC, RECT clientRect, RECT chartRect)
{
	if(!m_bVisible) return;
	if(m_bCurrent)
	{
		DrawFrame(hDC,clientRect,chartRect,m_pPlot->GetLigntLineStyle(), m_pPlot->GetLightLineSize(), m_pPlot->GetLightColor());
	}
	DrawTitle(hDC, clientRect, chartRect );
	DrawAxisLine(hDC,clientRect,chartRect);
	DrawMajorTicks(hDC,clientRect,chartRect);
	DrawMinorTicks(hDC,clientRect,chartRect);
	DrawTickLabels(hDC,clientRect,chartRect);
}

void	CAxisImpl::DrawFrame(HDC hDC, RECT clientRect, RECT chartRect, int style, int size, COLORREF color)
{
	HPEN hPen,hOldPen;
	HBRUSH hBrush,hOldBrush;
	hPen=CreatePen(style, size, color );
	hOldPen = (HPEN)SelectObject(hDC, hPen );
	hBrush= (HBRUSH)GetStockObject(NULL_BRUSH);//CreateSolidBrush(color);
	hOldBrush = (HBRUSH)SelectObject(hDC,hBrush);
	RECT rect=GetPlotRect( hDC, clientRect, chartRect );
	Rectangle(hDC,rect.left,rect.top,rect.right,rect.bottom);
	SelectObject(hDC,hOldBrush);
	DeleteObject(hBrush);
	SelectObject(hDC,hOldPen);
	DeleteObject(hPen);
}

void CAxisImpl::DrawTitle(HDC hDC, RECT clientRect, RECT chartRect)
{
	if( m_strTitle == "" )return;

	//unsigned int	textMode;
	RECT	textRect;
	HFONT	hFont,hOldFont;
	LOGFONT logFont;
	COLORREF titlecolor;

	textRect = GetTitleRect(hDC, clientRect,chartRect);// also set height of title font and ticklabel font
	// Adding offset
	OffsetRect(&textRect, m_sizeTitleOffset.cx, m_sizeTitleOffset.cy);
	
	logFont=m_lfTitleFont;
	logFont.lfHeight = m_nRealTitleHeight;

	if(m_bSameColor)
		titlecolor = m_crAxisColor;
	else
		titlecolor = m_crTitleColor;
	
	SetBkMode( hDC,TRANSPARENT );
	SetTextColor( hDC,titlecolor );
	//Rectangle(hDC,textRect.left,textRect.top,textRect.right,textRect.bottom);

	// Find the rectangle that encloses our axis title
	int x0,y0;
	x0 = textRect.left;
	y0 = textRect.top;
	switch( GetLocation() )
	{
	case kLocationLeft:
	case kLocationCenterVL:
		if( m_nTitlePosition == kTitlePositionNormal )
		{
			logFont.lfEscapement = 900;
			logFont.lfOrientation = 900;
			x0 = textRect.left;
			y0 = textRect.bottom;
		}
		break;
	case kLocationRight:
	case kLocationCenterVR:
		if( m_nTitlePosition == kTitlePositionNormal )
		{
			logFont.lfEscapement = 2700;
			logFont.lfOrientation = 2700;
			x0 = textRect.right;
			y0 = textRect.top;
		}
		break;
	default:
		break;
	}
	hFont = CreateFontIndirect(&logFont);
	hOldFont = (HFONT)SelectObject(hDC,hFont);
	TextOut(hDC, x0, y0, m_strTitle.c_str(), m_strTitle.length());

	SelectObject(hDC, hOldFont );
	DeleteObject(hFont);
}

void CAxisImpl::DrawAxisLine(HDC hDC, RECT clientRect, RECT chartRect)
{
	//POINT tmpPoint;
	if( fabs( m_Range[1] - m_Range[0] )<= 1e-30 )return;

	HPEN		hPen,hOldPen;

	hPen = CreatePen( m_nLineStyle, m_nAxisSize, m_crAxisColor );
	hOldPen = (HPEN)SelectObject(hDC,hPen);
	//firstly, draw the axis line
	switch( GetLocation() )
	{
	case kLocationLeft:
		MoveToEx(hDC,chartRect.left,chartRect.bottom,NULL);
		LineTo(hDC,chartRect.left,chartRect.top);
		break;
	case kLocationRight:
		MoveToEx(hDC,chartRect.right,chartRect.bottom,NULL);
		LineTo(hDC,chartRect.right,chartRect.top);
		break;
	case kLocationBottom:
		MoveToEx(hDC,chartRect.left,chartRect.bottom,NULL);
		LineTo(hDC,chartRect.right,chartRect.bottom);
		break;
	case kLocationTop:
		MoveToEx(hDC,chartRect.left,chartRect.top,NULL);
		LineTo(hDC,chartRect.right,chartRect.top);
		break;
	case kLocationCenterVL:
	case kLocationCenterVR:
		MoveToEx(hDC,(chartRect.left+chartRect.right)/2,chartRect.bottom,NULL);
		LineTo(hDC,(chartRect.left+chartRect.right)/2,chartRect.top);
	case kLocationCenterHB:
	case kLocationCenterHT:
		MoveToEx(hDC,chartRect.left,(chartRect.top+chartRect.bottom)/2,NULL);
		LineTo(hDC,chartRect.right,(chartRect.top+chartRect.bottom)/2);
		break;
	}
	SelectObject(hDC,hOldPen);
	DeleteObject(hPen);
}

void CAxisImpl::DrawMajorTicks(HDC hDC, RECT clientRect, RECT chartRect)
{
	if(!m_bShowMajorTicks)return;

	double position, range;

	HPEN		hPen,hOldPen;
	double		scale, interval, tickScale;
	int			i;
	long		startPoint;
	int			tickMarkLength;
	POINT		tickPoint;

	COLORREF	tickcolor;
	if(m_bSameColor)
	{
		tickcolor = m_crAxisColor;
	}
	else
	{
		tickcolor = m_crTickColor;
	}

	hPen = CreatePen( PS_SOLID, m_nTickSize, tickcolor );
	hOldPen = (HPEN)SelectObject(hDC,hPen);

	range = m_Range[1] - m_Range[0];
	tickMarkLength = m_nTickLength;

	interval = GetTickPosValue(1) - GetTickPosValue(0);
	tickScale = interval / GetMinorTickCount();

	//then draw ticks and marks
	for( i = 0; i <= GetTickCount()+1; i++ )
	{
		position = GetTickPosValue( i );

		switch( GetLocation() )
		{
		case kLocationBottom:
		case kLocationTop:
		case kLocationCenterHB:
		case kLocationCenterHT:
			//startPoint = GetLocation() == kLocationBottom?chartRect.bottom:chartRect.top;
			if(GetLocation()==kLocationBottom)
				startPoint = chartRect.bottom;
			else if(GetLocation()==kLocationTop)
				startPoint = chartRect.top;
			else
				startPoint = (chartRect.bottom + chartRect.top)/2;
			scale = (double)abs(chartRect.right - chartRect.left) / range;
			// Major Tick marks
			switch(m_nTickPosition)
			{
			case kTickPositionNone:
				goto NoMajorTick1;
			case kTickPositionOuter:
				switch( GetLocation() )
				{
				case kLocationBottom:
				case kLocationCenterHB:
					tickPoint.y = startPoint - tickMarkLength;
					break;
				default:
					tickPoint.y = startPoint;
				}
				break;
			case kTickPositionInner:
				switch( GetLocation() )
				{
				case kLocationBottom:
				case kLocationCenterHB:
					tickPoint.y = startPoint;
					break;
				default:
					tickPoint.y = startPoint - tickMarkLength;
				}
				break;
			default:
				tickPoint.y = startPoint - tickMarkLength/2;
			}
			tickPoint.x = chartRect.left + (long)((position-m_Range[0]) * scale);
			MoveToEx(hDC, tickPoint.x, tickPoint.y, NULL );
			tickPoint.y += tickMarkLength;
			LineTo(hDC, tickPoint.x, tickPoint.y );
NoMajorTick1:				
			break;
		case kLocationLeft:
		case kLocationRight:
		case kLocationCenterVL:
		case kLocationCenterVR:
			// Major Tick marks
			//startPoint = (GetLocation()==kLocationLeft?chartRect.left:chartRect.right);
			if(GetLocation()==kLocationLeft)
				startPoint = chartRect.left;
			else if(GetLocation()==kLocationRight)
				startPoint = chartRect.right;
			else
				startPoint = (chartRect.left + chartRect.right)/2;
			
			scale = fabs(double(chartRect.bottom - chartRect.top)) / range;
			tickPoint.y = chartRect.bottom - (long)((position-m_Range[0]) * scale);
			switch( m_nTickPosition )
			{
			case kTickPositionNone:
				goto NoMajorTick2;
			case kTickPositionOuter:
				switch( GetLocation() )
				{
				case kLocationLeft:
				case kLocationCenterVL:
					tickPoint.x = startPoint;
					break;
				default:
					tickPoint.x = startPoint - tickMarkLength;
				}
				break;
			case kTickPositionInner:
				switch( GetLocation() )
				{
				case kLocationLeft:
				case kLocationCenterVL:
					tickPoint.x = startPoint - tickMarkLength;
					break;
				default:
					tickPoint.x = startPoint;
				}
				break;
			default:
				tickPoint.x = startPoint - tickMarkLength/2;
			}
			MoveToEx(hDC, tickPoint.x, tickPoint.y, NULL );
			tickPoint.x += tickMarkLength;
			LineTo( hDC, tickPoint.x, tickPoint.y );
NoMajorTick2:				

			break;
		default: break;
		}
	}
		
	SelectObject(hDC,hOldPen);
	DeleteObject(hPen);
}

void CAxisImpl::DrawMinorTicks(HDC hDC, RECT clientRect, RECT chartRect)
{
	if(!m_bShowMinorTicks)return;

	double position, range;
	
	HPEN		hPen,hOldPen;
	double		scale, interval,tickScale;
	int			i,j;
	long		startPoint;
	int			minorTickMarkLength;
	POINT		tickPoint;
	
	COLORREF	minortickcolor;
	if(m_bSameColor)
	{
		minortickcolor = m_crAxisColor;
	}
	else
	{
		minortickcolor = m_crTickColor;
	}
	
	hPen = CreatePen( PS_SOLID, m_nMinorTickSize, minortickcolor );
	hOldPen = (HPEN)SelectObject(hDC,hPen);
	
	range = m_Range[1] - m_Range[0];
	minorTickMarkLength = m_nMinorTickLength;

	interval = GetTickPosValue(1) - GetTickPosValue(0);
	tickScale = interval / GetMinorTickCount();
	//then draw ticks and marks
	for( i = 0; i <= GetTickCount()+1; i++ )
	{
		position = GetTickPosValue( i );

		switch( GetLocation() )
		{
		case kLocationBottom:
		case kLocationTop:
		case kLocationCenterHB:
		case kLocationCenterHT:
			if(GetLocation()==kLocationBottom)
				startPoint = chartRect.bottom;
			else if(GetLocation()==kLocationTop)
				startPoint = chartRect.top;
			else
				startPoint = (chartRect.bottom + chartRect.top)/2;
			//startPoint = GetLocation() == kLocationBottom?chartRect.bottom:chartRect.top;
			scale = (double)abs(chartRect.right - chartRect.left) / range;
			
			// Minor tick marks
			if( i <= GetTickCount() )
			{
				for( j = 1; j < GetMinorTickCount(); j++ )
				{
					tickPoint.x = chartRect.left + (long)((position-m_Range[0]+j*tickScale) * scale);
					switch( m_nMinorTickPosition )
					{
					case kTickPositionNone:
						goto NoMinorTick1;
					case kTickPositionOuter:
						switch( GetLocation() )
						{
						case kLocationBottom:
						case kLocationCenterHB:
							tickPoint.y = startPoint - minorTickMarkLength;
							break;
						default:
							tickPoint.y = startPoint;
						}
						break;
					case kTickPositionInner:
						switch( GetLocation() )
						{
						case kLocationBottom:
						case kLocationCenterHB:
							tickPoint.y = startPoint;
							break;
						default:
							tickPoint.y = startPoint - minorTickMarkLength;
						}
						break;
					default:
						tickPoint.y = startPoint - minorTickMarkLength/2;
					}
					MoveToEx(hDC, tickPoint.x, tickPoint.y, NULL );
					tickPoint.y += minorTickMarkLength;
					LineTo(hDC, tickPoint.x, tickPoint.y );

				}
			}
NoMinorTick1:			
			break;
		case kLocationLeft:
		case kLocationRight:
		case kLocationCenterVL:
		case kLocationCenterVR:
			// Major Tick marks
			//startPoint = (GetLocation()==kLocationLeft?chartRect.left:chartRect.right);
			if(GetLocation()==kLocationLeft)
				startPoint = chartRect.left;
			else if(GetLocation()==kLocationRight)
				startPoint = chartRect.right;
			else
				startPoint = (chartRect.left + chartRect.right)/2;
			
			scale = fabs(double(chartRect.bottom - chartRect.top)) / range;
			// Minor tick marks
			if( i <= GetTickCount() )
			{
				for( j = 1; j < GetMinorTickCount(); j++ )
				{
					tickPoint.y = chartRect.bottom - (long)((position-m_Range[0]+j*tickScale) * scale);
					switch( m_nMinorTickPosition )
					{
					case kTickPositionNone:
						goto NoMinorTick2;
					case kTickPositionOuter:
						switch( GetLocation() )
						{
						case kLocationLeft:
						case kLocationCenterVL:
							tickPoint.x = startPoint;
							break;
						default:
							tickPoint.x = startPoint - minorTickMarkLength;
						}
						break;
					case kTickPositionInner:
						switch( GetLocation() )
						{
						case kLocationLeft:
						case kLocationCenterVL:
							tickPoint.x = startPoint - minorTickMarkLength;
							break;
						default:
							tickPoint.x = startPoint;
						}
						break;
					default:
						tickPoint.x = startPoint - minorTickMarkLength/2;
					}
					MoveToEx(hDC, tickPoint.x, tickPoint.y, NULL );
					tickPoint.x += minorTickMarkLength;
					LineTo(hDC, tickPoint.x, tickPoint.y );
				}

			}
NoMinorTick2:

			break;
		default: break;
		}
	}
	SelectObject(hDC,hOldPen);
	DeleteObject(hPen);
}

void CAxisImpl::DrawTickLabels(HDC hDC, RECT clientRect, RECT chartRect)
{
	if(!m_bShowTickLabel)return;

	double position, range;
	
	HFONT		hFont,hOldFont;
	LOGFONT		logFont;
	RECT			textRect;
	SIZE			tmSize={0,0};
	unsigned int	textMode;
	int				tickHeight = 0;
	int				maxTickLength;
	double		scale, interval,tickScale;
	int			i,sign;
	long		startPoint;
	POINT		tickPoint;
	int			tickMarkLength;
	string		tickLabel;
	SIZE		labelExtent={0,0};
	
	COLORREF	ticklabelcolor;
	if(m_bSameColor)
	{
		ticklabelcolor = m_crAxisColor;
	}
	else
	{
		ticklabelcolor = m_crTickLabelColor;
	}

	// when no title, the following function do not execute, we cannot get a good ticklabelheight
	if(m_strTitle=="")
		GetRealTickLabelDimension(hDC, chartRect);
	
	// now ready
	logFont = m_lfLabelFont;
	logFont.lfHeight = m_nRealTickLabelHeight;

	hFont = CreateFontIndirect( &logFont );
	hOldFont = (HFONT)SelectObject(hDC,hFont);
	
	range = m_Range[1] - m_Range[0];
	tickMarkLength = m_nTickLength;
	
	// Setup of ranges, pens
	SetBkMode(hDC, TRANSPARENT );
	SetTextColor(hDC, ticklabelcolor );

	switch( GetLocation() )
	{
	case kLocationBottom:
	case kLocationTop:
	case kLocationCenterHB:
	case kLocationCenterHT:
		//textMode = DT_NOCLIP | DT_CENTER | DT_SINGLELINE | (GetLocation()==kLocationBottom?DT_TOP:DT_BOTTOM);
		textMode = DT_NOCLIP | DT_CENTER | DT_SINGLELINE;
		if(GetLocation() == kLocationBottom || GetLocation() == kLocationCenterHB)
			textMode |= DT_TOP;
		else
			textMode |= DT_BOTTOM;
		break;
	case kLocationLeft:
	case kLocationRight:
	case kLocationCenterVL:
	case kLocationCenterVR:
		//textMode = DT_NOCLIP | DT_VCENTER | DT_SINGLELINE | (GetLocation()==kLocationRight?DT_LEFT:DT_RIGHT);
		textMode = DT_NOCLIP | DT_VCENTER | DT_SINGLELINE;
		if(GetLocation() == kLocationRight || GetLocation() == kLocationCenterVR)
			textMode |= DT_LEFT;
		else
			textMode |= DT_RIGHT;
		// Don't calculate tickHeight here because it is calculated later
		break;
	default: break;
	}
	
	// For moving our labels and titles, we need to be away
	// from the longest tick mark
	maxTickLength = GetMaxTickLength();

	// Do we add or subtract distance to move labels?
	if( GetLocation() == kLocationBottom || GetLocation() == kLocationRight
		|| m_nLocation == kLocationCenterHB || m_nLocation == kLocationCenterVR)
		sign = -1; else sign = 1;
	
	interval = GetTickPosValue(1) - GetTickPosValue(0);
	tickScale = interval / GetMinorTickCount();
	interval = GetTickPosValue(1) - GetTickPosValue(0);
	tickScale = interval / GetMinorTickCount();
	//then draw ticks and marks
	for( i = 0; i <= GetTickCount()+1; i++ )
	{
		position = GetTickPosValue( i );

		switch( GetLocation() )
		{
		case kLocationBottom:
		case kLocationCenterHB:
		case kLocationTop:
		case kLocationCenterHT:
			//startPoint = (GetLocation() == kLocationBottom || GetLocation() == kLocationCenterHB)?chartRect.bottom:chartRect.top;
			if(GetLocation() == kLocationBottom)
				startPoint = chartRect.bottom;
			else if(GetLocation() == kLocationTop)
				startPoint = chartRect.top;
			else
				startPoint = (chartRect.bottom + chartRect.top)/2;

			scale = (double)abs(chartRect.right - chartRect.left) / range;
		
			// Tick labels
			tickPoint.x = chartRect.left + (long)((position-m_Range[0]) * scale);
			tickPoint.y = startPoint - sign*tickMarkLength/2;
			textRect.left = textRect.right = tickPoint.x;
			textRect.top = textRect.bottom = tickPoint.y;
			OffsetRect(&textRect, m_sizeLabelOffset.cx, m_sizeLabelOffset.cy);// Adding offset
			tickLabel = GetTickLabel( i );
			DrawText(hDC, tickLabel.c_str(),tickLabel.length(), (LPRECT)&textRect, textMode );
		
			break;
		case kLocationLeft:
		case kLocationCenterVL:
		case kLocationRight:
		case kLocationCenterVR:
			// Major Tick marks
			//startPoint = ((GetLocation()==kLocationLeft || GetLocation()==kLocationCenterVL)?chartRect.left:chartRect.right);
			if(GetLocation() == kLocationLeft)
				startPoint = chartRect.left;
			else if(GetLocation() == kLocationRight)
				startPoint = chartRect.right;
			else
				startPoint = (chartRect.left + chartRect.right)/2;
			
			scale = fabs(double(chartRect.bottom - chartRect.top)) / range;
			tickPoint.y = chartRect.bottom - (long)((position-m_Range[0]) * scale);
			
			// Tick labels
			tickPoint.y = chartRect.bottom - (long)((position-m_Range[0]) * scale);
			tickPoint.x = startPoint - sign*tickMarkLength/2;
			textRect.left = textRect.right = tickPoint.x;
			textRect.top = textRect.bottom = tickPoint.y;
			OffsetRect(&textRect, m_sizeLabelOffset.cx, m_sizeLabelOffset.cy);// Adding offset
			tickLabel = GetTickLabel( i );
			DrawText(hDC, tickLabel.c_str(), tickLabel.length(), (LPRECT)&textRect, textMode );
			GetTextExtentPoint(hDC, tickLabel.c_str(), tickLabel.length(), &labelExtent );
			if( labelExtent.cx > tickHeight ) tickHeight = labelExtent.cx;

			break;
		default: break;
		}
	}
	SelectObject( hDC, hOldFont);
	DeleteObject( hFont );
}

// Returns the rectangle, in the current coordinate space,
// that the axis will take up. Used to adjust the size
// of the main chart when an axis is near.
SIZE	CAxisImpl::GetMinDisplaySize( HDC hDC )
{
	SIZE		minSize={0,0};
	TEXTMETRIC	tm;
	HFONT		hFont, hOldFont;

	// We have to calculate the height (or width) of the tick marks,
	// the fonts (titles, if any) and the labels
	//if( m_strTitle != "" )
	if( m_strTitle != "" && m_nTitlePosition==kTitlePositionNormal)
	{
		hFont = CreateFontIndirect( &m_lfTitleFont );
		hOldFont = (HFONT)SelectObject(hDC,hFont);
		GetTextExtentPoint(hDC, m_strTitle.c_str(), m_strTitle.length(),&minSize);
		SelectObject(hDC,hOldFont);
		DeleteObject(hFont);
	}


	if( GetTickCount() > 0 )
	{
		SIZE		temp={0,0}, temp2={0,0};
		int			i;

		hFont = CreateFontIndirect( &m_lfLabelFont );
		hOldFont = (HFONT)SelectObject(hDC,hFont);

		GetTextMetrics(hDC, &tm);
		string strLabel;
		for( i = 0; i <= GetTickCount()+1; i++ )
		{
			strLabel = GetTickLabel(i);
			GetTextExtentPoint(hDC,strLabel.c_str(),strLabel.length(),&temp);
			if( temp.cx > temp2.cx ) temp2.cx = temp.cx;
			if( temp.cy > temp2.cy ) temp2.cy = temp.cy;
		}

		// Some approximate spacings
		if( m_nLocation == kLocationLeft || m_nLocation == kLocationRight
			|| m_nLocation == kLocationCenterVL || m_nLocation == kLocationCenterVR )
			{ minSize.cy += temp2.cx + m_nMarginVertical; minSize.cx += temp2.cy + m_nMarginVertical; }
		else
			{ minSize.cx += temp2.cx + m_nMarginHorizontal; minSize.cy += temp2.cy + m_nMarginHorizontal; }

		SelectObject(hDC,hOldFont);
		DeleteObject(hFont);
	}

	// Finally the tick marks
	//minSize.cy += max(m_nMinorTickLength, m_nTickLength)/2;//Infact, this line should be changed with the tick position
	minSize.cy += GetMaxTickLength();

	// If we're left or right, switch x and y
	if( m_nLocation == kLocationLeft || m_nLocation == kLocationRight
		|| m_nLocation == kLocationCenterVL || m_nLocation == kLocationCenterVR)
	{
		SIZE	temp={minSize.cy,minSize.cx};
		return temp;
	}
	else
	{
		return minSize;
	}
}

// These are always returned axis-specific
// so for bottom  = left, right,
// for right = bottom pad, top pad
// for top = left, right
// for left = bottom, top

// This function looks at the first and last tick mark of
// an axis to see how much it extends over the edge of the
// chart. It assumes that the first and last tick marks
// go on the end of the axis. This may change in the future.
SIZE	CAxisImpl::GetPaddingSize( HDC hDC )
{
	SIZE		temp1={0,0}, temp2={0,0};
	TEXTMETRIC	tm;

	if( GetTickCount() > 0 )
	{
		HFONT		hOldFont, hFont;
		int			i;

		hFont = CreateFontIndirect(&m_lfLabelFont);
		hOldFont = (HFONT)SelectObject(hDC,hFont);

		GetTextMetrics(hDC,&tm);
		string strLabel;
		// Get info for first and last tick marks
		for( i = 0; i <= GetTickCount()+1; i+= GetTickCount() )
		{
			strLabel = GetTickLabel(i);
			GetTextExtentPoint(hDC,strLabel.c_str(),strLabel.length(),&temp1);
			switch( GetLocation() )
			{
			case kLocationBottom:
			case kLocationTop:
			case kLocationCenterHB:
			case kLocationCenterHT:
				if( i == 0 ) temp2.cx = temp1.cx / 2; else temp2.cy = temp1.cx / 2;
				break;
			case kLocationLeft:
			case kLocationRight:
			case kLocationCenterVL:
			case kLocationCenterVR:
				if( i == 0 ) temp2.cx = temp1.cy / 2; else temp2.cy = temp1.cy / 2;
				break;
			}
		}
		SelectObject(hDC,hOldFont);
		DeleteObject(hFont);
	}
	return temp2;
}

SIZE	CAxisImpl::GetSize( HDC hDC )
{
	SIZE theSize;
	SIZE axisDims, paddingDims;
	axisDims = GetMinDisplaySize( hDC );
	paddingDims = GetPaddingSize( hDC );

	switch( GetLocation() )
	{
	case kLocationBottom:
	case kLocationTop:
	case kLocationCenterHB:
	case kLocationCenterHT:
		theSize.cx = axisDims.cx + paddingDims.cx + paddingDims.cy;
		theSize.cy = axisDims.cy;
		break;
	case kLocationLeft:
	case kLocationRight:
	case kLocationCenterVL:
	case kLocationCenterVR:
		theSize.cx = axisDims.cx;
		theSize.cy = axisDims.cy + paddingDims.cx + paddingDims.cy;
		break;
	
	default:
		break;
	}
	return theSize;
}

// Returns the distance along the axis, in DATA UNITS
// where the requested tick mark lies
double		CAxisImpl::GetTickPosValue( int whichTick )
{
	double		range,pos,epsl=1.0e-12;

	// Assume user has checked the tick values first
	if( whichTick < 0 || (GetTickCount() > 0 && whichTick > GetTickCount()+1) )
		return 0.0;

	range = m_Range[1] - m_Range[0];

	if( GetTickCount() > 0 )
	{
		// User has specified number of ticks
		pos = m_Range[0] + range * (double)whichTick/((double)GetTickCount()+1.0);
		if(range!=0.0)
		{
			if(fabs(pos/range)<epsl)pos=0.0;
		}
	}
	else
	{
		// For now, just use four regions
		pos = m_Range[0] + range * (double)whichTick/((double)5.0);
		if(range!=0.0)
		{
			if(fabs(pos/range)<epsl)pos=0.0;
		}
	}

	return pos;
}

// Gets the label string for the requested tick mark.
// Useful in future if want to add user-specified
// tick labels.
string		CAxisImpl::GetTickLabel( int whichTick )
{
	string			tickLabel;
	
	if(!m_bReplaceLabel)
	{
		double			value = GetTickPosValue( whichTick );
		ostringstream ostr;
		ostr<<value;
		tickLabel = ostr.str();
	}
	else
	{
		if( whichTick < (int)m_vstrAlternateLabels.size() )
			tickLabel = m_vstrAlternateLabels[whichTick];
		else
			tickLabel = "";
	}

	// add the label suffix
	if(tickLabel != "" && m_strLabelSuffix != "")
		tickLabel += m_strLabelSuffix;

	return tickLabel;
}

