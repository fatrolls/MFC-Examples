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
#include "PlotImpl.h"
#include "AxisImpl.h"
#include "LegendImpl.h"

// For function GradientFill
#pragma comment(lib, "msimg32")

/////////////////////////////////////////////////////////////////////////
// Class CPlotImpl

CPlotImpl::CPlotImpl()
{
	SetDefaults();

	AddAxis(kLocationBottom);
	AddAxis(kLocationLeft);
}

CPlotImpl::~CPlotImpl()
{
	// Delete data sets and axes, perhaps
	for( int i = 0; i < kMaxAxes; i++ )
	{
		if(m_pAxes[i])
		{
			delete m_pAxes[i];
			m_pAxes[i] = NULL;
		}
	}
}

void CPlotImpl::OnDraw( HWND hWnd )
{
	HDC hDC = GetDC(hWnd);
	RECT destRect;
	GetClientRect(hWnd,&destRect);

	OnDraw( hDC, destRect );

	ReleaseDC(hWnd, hDC);
}

void CPlotImpl::OnDraw(HDC hDC, RECT destRect)
{
	SetLastClientRect(destRect);

	////////////////////////////////////////////////////////////////
	RECT plotRect, titleRect, subtitleRect;

	plotRect = GetPlotRect( hDC, destRect );
	//EraseBkgnd( hDC, destRect );
	DrawGrids( hDC, plotRect );
	DrawFrame( hDC, plotRect );

	titleRect = GetTitleRect(hDC, destRect, plotRect);
	subtitleRect = GetSubtitleRect(hDC, plotRect);
	DrawTitle( hDC, titleRect );
	DrawSubtitle(hDC, subtitleRect );

	CAxis *axis;
	// Draw the axes
	for( int i = 0; i < GetAxisCount(); i++ )
	{
		axis = GetAxis(i);
		((CAxisImpl*)axis)->OnDraw( hDC, destRect, plotRect );
	}
	// Draw Legend
	if(m_bUseLegend)m_pLegend->OnDraw(hDC,plotRect);
	
}

void CPlotImpl::DrawTextInRect(HDC hDC, RECT rect, string title, LOGFONT logFont, int backmode, COLORREF color)
{
	if( title =="" )return;

	HFONT		hOldFont, hFont;
	bool		keepGoing = true;
	SIZE		tmSize;

	// Auto size font. Changes the title font size
	// to smaller if there is not enough space on
	// the plot. Perhaps add a user flag for this?
	while( keepGoing == true )
	{
		hFont = CreateFontIndirect(&logFont);
		hOldFont = (HFONT)SelectObject(hDC, hFont);
		GetTextExtentPoint(hDC, title.c_str(), title.length(), &tmSize);
		if( tmSize.cx > abs(rect.right - rect.left) || 
			tmSize.cy > abs(rect.bottom - rect.top) )
			logFont.lfHeight--;
		else
			keepGoing = false;

		if( logFont.lfHeight <= 4 ) keepGoing = false;

		SelectObject( hDC,hOldFont );
		DeleteObject(hFont);
	}

	// Draw the text. There should be a background transparent mode
	SetBkMode( hDC, backmode );
	SetTextColor( hDC, color );
	hFont = CreateFontIndirect(&logFont);
	hOldFont = (HFONT)SelectObject(hDC, hFont);
	DrawText(hDC, title.c_str(), title.length(), &rect, DT_CENTER | DT_BOTTOM | DT_SINGLELINE );

	SelectObject( hDC, hOldFont );
	DeleteObject( hFont );
}

void CPlotImpl::DrawTitle(HDC hDC, RECT titleRect)
{
	if(m_strTitle == "")return;
	if(m_bLightTitle)
	{
		HPEN hPen = CreatePen( PS_SOLID, m_nLightLineSize, m_crLightColor );
		HBRUSH hBrush,hOldBrush;
		HPEN hOldPen = (HPEN)SelectObject( hDC,hPen );
		hBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
		hOldBrush = (HBRUSH)SelectObject(hDC,hBrush);
		Rectangle(hDC,titleRect.left,titleRect.top,titleRect.right,titleRect.bottom);
		SelectObject(hDC,hBrush);
		SelectObject(hDC,hOldPen);
		DeleteObject(hPen);
		DeleteObject(hBrush);
	}
	DrawTextInRect(hDC, titleRect,m_strTitle, m_lfTitleFont, TRANSPARENT, m_crTitleColor);
}

void	CPlotImpl::DrawSubtitle( HDC hDC, RECT subtitleRect )
{
	if( m_strSubtitle =="" || !m_bSubtitleShow )return;
	DrawTextInRect(hDC, subtitleRect, m_strSubtitle, m_lfSubtitleFont, TRANSPARENT, m_crSubtitleColor);
}

void CPlotImpl::EraseBkgnd( HDC hDC, RECT destRect )
{
	// Erase the Bkgnd
	if( !m_bEraseBkgnd ) return;

	// Gradient Bkgnd
	if(m_bGradientBkgnd)
	{
		TRIVERTEX        vert[2];
		GRADIENT_RECT    gRect;
		UINT r,g,b;
		r=GetRValue(m_crGradientColor1);
		g=GetGValue(m_crGradientColor1);
		b=GetBValue(m_crGradientColor1);

		vert [0] .x      = destRect.left;
		vert [0] .y      = destRect.top;
		vert [0] .Red    = r*256;
		vert [0] .Green  = g*256;
		vert [0] .Blue   = b*256;
		vert [0] .Alpha  = 0x0000;
		
		r=GetRValue(m_crGradientColor2);
		g=GetGValue(m_crGradientColor2);
		b=GetBValue(m_crGradientColor2);

		vert [1] .x      = destRect.right;
		vert [1] .y      = destRect.bottom;
		vert [1] .Red    = r*256;
		vert [1] .Green  = g*256;
		vert [1] .Blue   = b*256;
		vert [1] .Alpha  = 0x0000;

		gRect.UpperLeft  = 0;
		gRect.LowerRight = 1;

		DWORD dwMode;
		if(m_bGradientHorizontal)
		{
			dwMode=GRADIENT_FILL_RECT_H;
		}
		else
		{
			dwMode=GRADIENT_FILL_RECT_V;
		}
		GradientFill(hDC, vert, 4, &gRect, 1, dwMode);
		return;
	}

	RECT plotRect = GetPlotRect( hDC, destRect );
	
	// Erase backgound
	HBRUSH			hBrush;
	switch(m_nBkgndBrushType)
	{
	case kBrushSolid:
		hBrush = CreateSolidBrush( m_crBkgndColor );
		break;
	case kBrushHatch:
		hBrush = CreateHatchBrush( m_nBkgndHatchStyle, m_crBkgndColor);
		break;
	case kBrushPattern:
		hBrush = CreatePatternBrush( m_hBkgndPattern );
		break;
	default:
		hBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
		break;
	}

	FillRect(hDC, &destRect, hBrush);
	DeleteObject(hBrush);
	

	// Set data region color
	if(  m_bUseDataRegionBrush )
	{
		switch(m_nDataRegionBrushType)
		{
		case kBrushSolid:
			hBrush = CreateSolidBrush( m_crDataRegionColor );
			break;
		case kBrushHatch:
			hBrush = CreateHatchBrush( m_nDataRegionHatchStyle, m_crDataRegionColor);
			break;
		case kBrushPattern:
			hBrush = CreatePatternBrush( m_hDataRegionPattern );
			break;
		default:
			hBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
			break;
		}
		FillRect( hDC, &plotRect, hBrush );
		DeleteObject(hBrush);
	}
}

void	CPlotImpl::DrawGrids( HDC hDC, RECT plotRect )
{
	// Draw the major and minor grids

	// Get the grid information from the axes
	double		scale, range, theRange[2];
	CAxis		*axis;
	POINT		point, tickPoint;
	int			i, j, k;
	double		position, interval, tickScale;
	HPEN		hPen;
	HPEN		hOldPen, hMinorPen;
	bool		vDraw = false, hDraw = false;

	hPen = CreatePen( m_nMajorGridLineStyle, m_nMajorGridLineSize, m_crMajorGridColor );
	hMinorPen = CreatePen( m_nMinorGridLineStyle, m_nMinorGridLineSize, m_crMinorGridColor );

	hOldPen = (HPEN)SelectObject( hDC, hPen );

	SetBkColor(hDC, m_crBkgndColor );

	SetBkMode(hDC, TRANSPARENT );

	// We base our grids on the left or bottom axis, if they exist.
	for( i = 0; i < m_nAxisCount; i++ )
	{
		axis = m_pAxes[i];

		axis->GetRange( theRange );
		range = theRange[1] - theRange[0];

		if( ( axis->GetLocation() == kLocationLeft || axis->GetLocation() == kLocationRight
			|| axis->GetLocation() == kLocationCenterVL || axis->GetLocation() == kLocationCenterVR)
			&& (m_bUseMajorHGrids == true || m_bUseMinorHGrids == true )
			&& !hDraw )
		{
			scale = fabs(double(plotRect.bottom - plotRect.top)) / range;
			for( j = 0; j <= axis->GetTickCount(); j++ )
			{
				
				position = ((CAxisImpl*)axis)->GetTickPosValue( j );
				if( m_bUseMajorHGrids == true && j > 0 )
				{
					SelectObject( hDC, hPen );
					
					point.y = (long)(plotRect.bottom - scale * (position - theRange[0]));
					point.x = plotRect.left;
					MoveToEx(hDC, point.x,point.y, NULL );
					point.x = plotRect.right;
					LineTo( hDC,point.x,point.y );
				}

				if( m_bUseMinorHGrids == true )
				{
					interval = ((CAxisImpl*)axis)->GetTickPosValue(1) - ((CAxisImpl*)axis)->GetTickPosValue(0);
					tickScale = interval / ((CAxisImpl*)axis)->GetMinorTickCount();
					tickPoint = point;

					SelectObject(hDC, hMinorPen );
					for( k = 1; k < axis->GetMinorTickCount(); k++ )
					{
						tickPoint.y = plotRect.bottom - (long)((position-theRange[0]+(k*tickScale)) * scale);
						tickPoint.x = plotRect.left;
						MoveToEx( hDC,tickPoint.x,tickPoint.y,NULL );
						tickPoint.x = plotRect.right;
						LineTo( hDC,tickPoint.x,tickPoint.y );
					}
				}
			}
			hDraw = true;
		}

		if( ( axis->GetLocation() == kLocationBottom || axis->GetLocation() == kLocationTop
			|| axis->GetLocation() == kLocationCenterHB || axis->GetLocation() == kLocationCenterHT)
			&&	(m_bUseMajorVGrids == true || m_bUseMinorVGrids == true )
			&& !vDraw )
		{
			scale = (double)(plotRect.right - plotRect.left) / range;
			for( j = 0; j <= axis->GetTickCount(); j++ )
			{
				position = ((CAxisImpl*)axis)->GetTickPosValue( j );
				if( m_bUseMajorVGrids == true && j > 0 )
				{
					SelectObject( hDC, hPen );

					point.x = (long)(scale * (position - theRange[0]) + plotRect.left);
					point.y = plotRect.bottom;
					MoveToEx(hDC, point.x, point.y, NULL );
					point.y = plotRect.top;
					LineTo( hDC, point.x, point.y );
				}
				 
				if( m_bUseMinorVGrids == true )
				{
					interval = ((CAxisImpl*)axis)->GetTickPosValue(1) - ((CAxisImpl*)axis)->GetTickPosValue(0);
					tickScale = interval / ((CAxisImpl*)axis)->GetMinorTickCount();
					tickPoint = point;

					SelectObject( hDC,hMinorPen );
					for( k = 1; k < axis->GetMinorTickCount(); k++ )
					{
						tickPoint.x = plotRect.left + (long)((position-theRange[0]+(k*tickScale)) * scale);
						tickPoint.y = plotRect.bottom;
						MoveToEx( hDC, tickPoint.x,tickPoint.y, NULL );
						tickPoint.y = plotRect.top;
						LineTo( hDC,tickPoint.x,tickPoint.y );
					}
				}
			}
			vDraw = true;
		}	
	}
	SelectObject( hDC, hOldPen );
	DeleteObject( hPen );
	DeleteObject( hMinorPen );
}

void	CPlotImpl::DrawFrame( HDC hDC, RECT plotRect )
{
	if( m_nBorderSize <= 0 )return;

	COLORREF bordercolor = m_bLightDataRegion?m_crLightColor:m_crBorderColor;
	int bordersize = m_bLightDataRegion?m_nLightLineSize:m_nBorderSize;

	HPEN	hPen,hOldPen;
	HBRUSH hBrush,hOldBrush;
	hPen = CreatePen( m_nBorderStyle, bordersize, bordercolor );
	hBrush=(HBRUSH)GetStockObject(NULL_BRUSH);

	hOldPen = (HPEN)SelectObject(hDC, hPen);
	hOldBrush = (HBRUSH)SelectObject(hDC,hBrush);

	Rectangle(hDC,plotRect.left,plotRect.top,plotRect.right,plotRect.bottom);

	SelectObject(hDC, hOldBrush);
	DeleteObject(hBrush);
	SelectObject(hDC, hOldPen );
	DeleteObject(hPen);
}

RECT	CPlotImpl::GetPlotRect( HDC hDC, RECT clientRect )
{
	RECT plotRect = clientRect;
	// Ask the axes what size they want
	plotRect = AdjustPlotSizeForAxes( hDC, plotRect );

	// What size do we need for the title
	plotRect = AdjustPlotSizeForTitle( hDC, plotRect );

	// Add spacing
	//plotRect.InflateRect( -20, 20 );
	plotRect.left += m_nMarginLeft;
	plotRect.right -= m_nMarginRight;
	plotRect.top += m_nMarginTop;
	plotRect.bottom -= m_nMarginBottom;

	// Equal XY Axis
	if( m_bEqualXYAxis )
	{
		if( abs( plotRect.right - plotRect.left ) > abs( plotRect.bottom - plotRect.top ) )
		{
			plotRect.right = plotRect.left + abs( plotRect.bottom - plotRect.top );
		}
		else
		{
			plotRect.bottom = plotRect.top + abs( plotRect.right - plotRect.left );
		}
	}

	return plotRect;
}

RECT	CPlotImpl::GetTitleRect( HDC hDC, RECT clientRect, RECT chartRect )
{
	RECT	titleRect=clientRect;
	SIZE	tmSize={0,0},axSize={0,0};
	if( GetTitle() != "" )
	{
		HFONT		hOldFont, hFont;

		//pOldFont = MySelectFont( pDC, &font, &GetTitleFont() );
		hFont = CreateFontIndirect(&m_lfTitleFont);
		hOldFont = (HFONT)SelectObject(hDC,hFont);
		GetTextExtentPoint( hDC, m_strTitle.c_str(),m_strTitle.length(), &tmSize );
		SelectObject(hDC, hOldFont );
		DeleteObject(hFont);
	}
	
	CAxis *axis;
	for(int i=0;i<GetAxisCount();i++)
	{
		axis=GetAxis(i);
		if( ((CAxisImpl*)axis)->GetLocation()==kLocationTop)
		{
			axSize=((CAxisImpl*)axis)->GetMinDisplaySize(hDC);
			break;
		}
	}

	titleRect.bottom=chartRect.top-axSize.cy;
	titleRect.top=titleRect.bottom-tmSize.cy;
	titleRect.left=chartRect.left;
	titleRect.right=chartRect.right;

	return titleRect;
}

RECT	CPlotImpl::GetSubtitleRect( HDC hDC, RECT chartRect)
{
	RECT subtitleRect;

	subtitleRect = chartRect;
	subtitleRect.top = chartRect.top;
	subtitleRect.bottom = chartRect.top*7/8+chartRect.bottom/8;

	// Make sure there is a minimal separation
	if( subtitleRect.bottom == chartRect.bottom ) subtitleRect.bottom += 10;

	// Add offset
	//subtitleRect.OffsetRect(m_sizeSubtitleOffset);
	OffsetRect(&subtitleRect, m_sizeSubtitleOffset.cx, m_sizeSubtitleOffset.cy);

	return subtitleRect;
}

RECT	CPlotImpl::AdjustPlotSizeForAxes( HDC hDC, RECT plotRect )
{
	int			i;
	CAxis		*axis;
	SIZE		axisDims, paddingDims;

	for( i = 0; i < m_nAxisCount; i++ )
	{
		axis = m_pAxes[i];
		axisDims = ((CAxisImpl*)axis)->GetMinDisplaySize( hDC );
		paddingDims = ((CAxisImpl*)axis)->GetPaddingSize( hDC );
		switch( ((CAxisImpl*)axis)->GetLocation() )
		{
		case kLocationBottom:
			plotRect.bottom -= axisDims.cy;
			plotRect.left += paddingDims.cx;
			plotRect.right -= paddingDims.cy;
			break;
		case kLocationTop:
			plotRect.top += axisDims.cy;
			plotRect.left += paddingDims.cx;
			plotRect.right -= paddingDims.cy;
			break;
		case kLocationLeft:
			plotRect.left += axisDims.cx;
			plotRect.bottom -= paddingDims.cx;
			plotRect.top += paddingDims.cy;
			break;
		case kLocationRight:
			plotRect.right -= axisDims.cx;
			plotRect.bottom -= paddingDims.cx;
			plotRect.top += paddingDims.cy;
			break;
		case kLocationCenterHB:
		case kLocationCenterHT:
			plotRect.left += paddingDims.cx;
			plotRect.right -= paddingDims.cy;
			break;
		case kLocationCenterVL:
		case kLocationCenterVR:
			plotRect.bottom -= paddingDims.cx;
			plotRect.top += paddingDims.cy;
			break;
		default: break;
		}
	}

	return plotRect;
}

// If there is a title, shrink the plot size appropriately.
RECT	CPlotImpl::AdjustPlotSizeForTitle( HDC hDC, RECT plotRect )
{
	if( m_strTitle != "" )
	{
		SIZE		tmSize={0,0};
		HFONT		hOldFont,hFont;
		hFont = CreateFontIndirect(&m_lfTitleFont);
		hOldFont = (HFONT)SelectObject(hDC, hFont);
		GetTextExtentPoint(hDC,m_strTitle.c_str(),m_strTitle.length(),&tmSize);
		plotRect.top += tmSize.cy;
		SelectObject(hDC,hOldFont);
		DeleteObject(hFont);
	}

	return plotRect;
}


// The default functions do nothing to the passed things
void	CPlotImpl::DataToLP( HDC hDC, double *data, LPPOINT point )
{
	RECT		plotRect;
	double		xRange[2], yRange[2];
	double		scaleX, scaleY;

	if( point == NULL ) return;

	plotRect = GetPlotRect( hDC, GetLastClientRect()  );

	GetRange( xRange, yRange );

	scaleX = (xRange[1] - xRange[0] ) / abs(plotRect.right - plotRect.left);
	scaleY = (yRange[1] - yRange[0] ) / abs(plotRect.bottom - plotRect.top);

	if( scaleX == 0. || scaleY == 0. ) return;

	point->x = (long)((data[0]-xRange[0]) / scaleX) + plotRect.left;
	point->y = -(long)((data[1]-yRange[0]) / scaleY) + plotRect.bottom;
}

void	CPlotImpl::LPToData( HDC hDC, LPPOINT point, double *data )
{
	RECT		plotRect;
	double		xRange[2], yRange[2];
	double		scaleX, scaleY;
	
	if( point == NULL ) return;

	plotRect = GetPlotRect( hDC, GetLastClientRect()  );

	GetRange( xRange, yRange );

	scaleX = (xRange[1] - xRange[0] ) / abs(plotRect.right - plotRect.left);
	scaleY = (yRange[1] - yRange[0] ) / abs(plotRect.bottom - plotRect.top);

	if( scaleX == 0. || scaleY == 0. ) return;

	data[0] = (point->x-plotRect.left) * scaleX + xRange[0];
	data[1] = (plotRect.bottom-point->y) * scaleY + yRange[0];
}

int		CPlotImpl::RegionIdentify( HDC hDC, POINT point )
{
	CAxis *pAxis=0;
	RECT theRect;
	
	//data region
	theRect=GetPlotRect(hDC,GetLastClientRect() );
	//if( (theRect.right-point.x)*(point.x-theRect.left)>=0 && (theRect.top-point.y)*(point.y-theRect.bottom)>=0 )
	if( PtInRect(&theRect,point) )
		return kXYRegionData;
	//title region
	theRect=GetTitleRect(hDC,GetLastClientRect() ,GetPlotRect(hDC, GetLastClientRect() ));
	//if( (theRect.right-point.x)*(point.x-theRect.left)>=0 && (theRect.top-point.y)*(point.y-theRect.bottom)>=0 )
	if( PtInRect(&theRect,point) )
		return kXYRegionTitle;
	//axis region
	CAxis *axis;
	for(int i=0;i<GetAxisCount();i++)
	{
		axis=GetAxis(i);
		theRect=((CAxisImpl*)axis)->GetPlotRect(hDC, GetLastClientRect(), GetPlotRect(hDC,GetLastClientRect() ));
		//if( (theRect.right-point.x)*(point.x-theRect.left)>=0 && (theRect.top-point.y)*(point.y-theRect.bottom)>=0 )
		if( PtInRect(&theRect,point) )
		{
			if(axis->GetLocation()==kLocationLeft)return kXYRegionLeft;
			if(axis->GetLocation()==kLocationRight)return kXYRegionRight;
			if(axis->GetLocation()==kLocationBottom)return kXYRegionBottom;
			if(axis->GetLocation()==kLocationTop)return kXYRegionTop;
		}
	}
	return kXYRegionOut;
}
