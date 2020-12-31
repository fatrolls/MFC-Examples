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
#include "PiePlotImpl.h"
#include "../../Basics/MyConst.h"

CPiePlotImpl::CPiePlotImpl()
{
	Reset();
	m_pLegend->SetColorRect(true);
}

CPiePlotImpl::~CPiePlotImpl()
{

}

void	CPiePlotImpl::Reset()
{
	m_vXYDataInfo.clear();

	for(int i=0; i<kMaxAxes; i++)
	{
		CAxis *axis=0;
		axis=GetAxis(i);
		if(axis)axis->SetVisible(false);
	}
}

int		CPiePlotImpl::AddPie(double value)
{
	return AddPie(value, RGB(255,0,0), "Untitled", 1.0);
}

int		CPiePlotImpl::AddPie(double value, COLORREF color, string title, double scale)
{
	if(value <= 0.0) return -1;
	if(GetDataSetCount() < m_nMaxPies)
	{
		if(scale <= 0.0 || scale > 1.0 )
			scale = 1.0;
		
		MyVData2D vData;
		DataPoint2D dp;
		dp.x = 0.0;
		dp.y = value;
		vData.push_back( dp );
		AddCurve(vData);
	}
	return -1;
}

void	CPiePlotImpl::GetPlotRange( double *xRange, double *yRange )
{
	xRange[0]=0.0;
	xRange[1]=1.0;
	yRange[0]=0.0;
	yRange[1]=1.0;
	SetXRange(0.0,1.0);
	SetYRange(0.0,1.0);
}

void	CPiePlotImpl::OnDraw( HWND hWnd )
{
	HDC hDC = GetDC(hWnd);
	RECT destRect;
	GetClientRect(hWnd,&destRect);
	
	OnDraw( hDC, destRect );
	
	ReleaseDC(hWnd, hDC);
}

void	CPiePlotImpl::OnDraw(HDC hDC, RECT destRect)
{
	//if there is no data, doing nothing
	if(GetDataSetCount()<=0)
	{
		EraseBkgnd( hDC, destRect );
		return;
	}

	//////////////////////////////////////////////////////////////////

	RECT			plotRect;
//	double			xRange[] = {1e30, -1e30}, yRange[]={1e30,-1e30};

	// Make sure our ranges are set
	// Get ranges for plotting
//	GetPlotRange( xRange, yRange );
	// Get the size of our plotting rectangle
	plotRect = GetPlotRect( hDC, destRect );
	//
	EraseBkgnd(hDC, destRect);
	// Draw Pies
	DrawPies( hDC, plotRect);
	// Draw basics
	CPlotImpl::OnDraw(hDC,destRect);
}

void	CPiePlotImpl::DrawPies( HDC hDC, RECT plotRect )
{
	int i;
	double ctx, cty, a, b, ratio, total;

	if(!GetFreqPara(plotRect, ctx, cty, a, b, total))
		return;
	double a1,b1,s1;

	HPEN hPen,hOldPen;
	HBRUSH hBrush,hOldBrush;
	hPen = CreatePen(m_nLineStyle, m_nLineSize, m_crLineColor);
	hOldPen = (HPEN)SelectObject(hDC, hPen);

	if(!m_bShadowing)
	{
		hBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
		hOldBrush = (HBRUSH)SelectObject(hDC, hBrush);
		Ellipse(hDC, int(ctx-a), int(cty-b), int(ctx+a), int(cty+b));
		DeleteObject(hBrush);
		SelectObject(hDC, hOldBrush);
	}
	else
	{
		hBrush = CreateSolidBrush( m_crShadowColor );
		hOldBrush = (HBRUSH)SelectObject(hDC, hBrush);
		double ctx1,cty1,ctx2,cty2;
		ctx1 = ctx - 2 * m_nShadowHalfLength * cos( m_fShadowAngle * myPi /180.0);
		cty1 = cty + 2 * m_nShadowHalfLength * sin( m_fShadowAngle * myPi /180.0) * b / a;
		Ellipse(hDC, int(ctx1-a), int(cty1-b), int(ctx1+a), int(cty1+b));
		ctx2 = ctx;// + m_nShadowHalfLength * cos( m_fShadowAngle * myPi /180.0);
		cty2 = cty;// - m_nShadowHalfLength * sin( m_fShadowAngle * myPi /180.0) * b / a;
		Ellipse(hDC, int(ctx2-a), int(cty2-b), int(ctx2+a), int(cty2+b));
		
		BeginPath(hDC);
		double TAngle1,TAngle2;
		TAngle1 = (m_fShadowAngle + 90.0) * myPi /180.0;
		TAngle2 = (m_fShadowAngle + 270.0) * myPi /180.0;
		
		MoveToEx(hDC, int( ctx1 + a * cos( TAngle2 ) ), int( cty1 - b * sin( TAngle2 ) ), NULL );
		LineTo(hDC, int( ctx2 + a * cos( TAngle2 ) ), int( cty2 - b * sin( TAngle2 ) ) );
		ArcTo(hDC, int (ctx2-a ), int( cty2-b ), int( ctx2+a ), int( cty2+b ), int( ctx2 + a * cos( TAngle2 ) ), int(cty2 - b * sin( TAngle2 ) ), int( ctx2 + a * cos( TAngle1 ) ), int (cty2 - b * sin( TAngle1 ) ) );
		LineTo(hDC, int( ctx1 + a * cos( TAngle1 ) ), int( cty1 - b * sin( TAngle1 ) ) );
		ArcTo(hDC, int( ctx1-a ), int( cty1-b ), int( ctx1+a ), int( cty1+b ), int( ctx1 + a * cos( TAngle1 ) ), int( cty1 - b * sin( TAngle1 ) ), int( ctx1 + a * cos( TAngle2 ) ), int( cty1 - b * sin( TAngle2 ) ) );
		LineTo(hDC, int( ctx1 + a * cos( TAngle2 ) ), int( cty1 - b * sin( TAngle2 ) ) );
		
		EndPath(hDC);
		StrokeAndFillPath(hDC);
		
		DeleteObject(hBrush);
		SelectObject(hDC, hOldBrush);
	}

	double curr = m_fStartAngle/360.0;
	SetPlotColors();
	for(i=0; i<GetDataSetCount(); i++)
	{
		hBrush = CreateSolidBrush(m_vXYDataInfo[i].crPlotColor);
		hOldBrush = (HBRUSH)SelectObject(hDC, hBrush);

		s1 = m_vXYDataInfo[i].fScale;
		if(s1<=0.0 || s1>1.0)s1=1.0;
		a1 = a * s1;
		b1 = b * s1;

		ratio = m_vXYDataInfo[i].pDataSet->GetData()[0].y/total;
		if(m_bClockWise)ratio = -ratio;
		if(ratio > 0.0)
		{
			Pie(hDC, int(ctx-a1), int(cty-b1), int(ctx+a1), int(cty+b1),
				int(ctx+a1*cos(curr*2.0*myPi)), int(cty-b1*sin(curr*2.0*myPi)),
				int(ctx+a1*cos((curr+ratio)*2.0*myPi)), int(cty-b1*sin((curr+ratio)*2.0*myPi)));
		}
		else
		{
			Pie(hDC, int(ctx-a1), int(cty-b1), int(ctx+a1), int(cty+b1),
				int(ctx+a1*cos((curr+ratio)*2.0*myPi)), int(cty-b1*sin((curr+ratio)*2.0*myPi)),
				int(ctx+a1*cos(curr*2.0*myPi)), int(cty-b1*sin(curr*2.0*myPi)));
		}

		SelectObject(hDC, hOldBrush);
		DeleteObject(hBrush);

		curr += ratio;
	}

	if(m_bShowPieTitle)
	{
		curr = m_fStartAngle/360.0;

		int fontheight;
		for(i=0; i<GetDataSetCount(); i++)
		{
			s1 = m_vXYDataInfo[i].fScale;
			if(s1<=0.0 || s1>1.0)s1=1.0;
			a1 = a * s1;
			b1 = b * s1;
			
			ratio = m_vXYDataInfo[i].pDataSet->GetData()[0].y/total;
			if(m_bClockWise)ratio = -ratio;
			
			RECT rect = GetPieTitleRect( hDC, plotRect, i, ctx, cty, a1, b1, curr, ratio, fontheight );
			if( IsRectEmpty(&rect) )continue;
			//if Lighted or selected
			if(m_vXYDataInfo[i].bLighted || m_vXYDataInfo[i].bSelected)
			{
				DeleteObject(hPen);
				hPen = CreatePen(m_vXYDataInfo[i].nPlotLineStyle, m_vXYDataInfo[i].nPlotLineStyle, m_vXYDataInfo[i].crPlotColor);
				SelectObject(hDC, hPen);
				Rectangle(hDC, rect.left, rect.top, rect.right, rect.bottom);
			}
			//light or select ended

			// determine intersect
			LOGFONT logFont = m_lfPieTitleFont;
			logFont.lfHeight = fontheight;
			COLORREF fontColor = m_vXYDataInfo[i].crPlotColor;
			
			HRGN hRgnPie = GetPieRegion( i, hDC, plotRect, ctx, cty, a1, b1, curr, ratio );
			HRGN hRgnTitle = CreateRectRgn( rect.left, rect.top, rect.right, rect.bottom );
			HRGN hRgnIntersect = hRgnPie;
			int rgn_ret = CombineRgn(hRgnIntersect, hRgnPie, hRgnTitle, RGN_AND);
			DeleteObject(hRgnPie);
			DeleteObject(hRgnTitle);
			DeleteObject(hRgnIntersect);
			if( rgn_ret == COMPLEXREGION || rgn_ret == SIMPLEREGION )
			{
				fontColor = RGB( 255-GetRValue(fontColor), 255-GetGValue(fontColor), 255-GetBValue(fontColor) );
			}
			// determine intersect ended
			
			DrawTextInRect( hDC, rect, m_vXYDataInfo[i].pDataSet->GetTitle(), logFont, TRANSPARENT, fontColor );

			curr += ratio;
		}
	}

	SelectObject(hDC, hOldPen);
	DeleteObject(hPen);
}


bool	CPiePlotImpl::GetFreqPara( RECT plotRect, double &ctx, double &cty, double &a, double &b, double &total )
{
	int i;
	//double ratio,total = 0.0;
	total = 0.0;
	for(i=0; i<GetDataSetCount(); i++)
	{
		if(m_vXYDataInfo[i].pDataSet->GetData()[0].y <= 0)return false;
		total += m_vXYDataInfo[i].pDataSet->GetData()[0].y;
	}
	if(total <= 0.0)return false;
	
	double scale = m_fScale;
	if(scale<=0.0 || scale>1.0)scale=1.0;
	
	double curr = m_fStartAngle/360.0;

	a = scale*abs(plotRect.right - plotRect.left)/2.0;
	b = scale*abs(plotRect.bottom - plotRect.top)/2.0;
	if(m_bCircleMode)
		a = b = min(a,b);
	ctx = (plotRect.right + plotRect.left)/2.0;
	cty = (plotRect.bottom + plotRect.top)/2.0;
	
	if(m_bShadowing)
	{
		ctx += m_nShadowHalfLength * cos( m_fShadowAngle * myPi /180.0);
		cty -= m_nShadowHalfLength * sin( m_fShadowAngle * myPi /180.0) * b / a;
	}

	// add offset
	ctx += m_sizeOffset.cx;
	cty += m_sizeOffset.cy;
	if(ctx + a > plotRect.right)ctx = plotRect.right - a;
	if(ctx - a < plotRect.left)ctx = plotRect.left + a;
	if(cty + b > plotRect.bottom)cty = plotRect.bottom - b;
	if(cty - b < plotRect.top )cty = plotRect.top + b;
	if(m_bShadowing)
	{
		double ctx1, cty1;
		ctx1 = ctx - 2 * m_nShadowHalfLength * cos( m_fShadowAngle * myPi /180.0);
		cty1 = cty + 2 * m_nShadowHalfLength * sin( m_fShadowAngle * myPi /180.0) * b / a;
		if(ctx1 + a > plotRect.right)ctx -= ctx1 + a - plotRect.right;
		if(ctx1 - a < plotRect.left)ctx += plotRect.left -ctx1 + a;
		if(cty1 + b > plotRect.bottom)cty -= cty1 + b - plotRect.bottom;
		if(cty1 - b < plotRect.top )cty += plotRect.top -cty1 + b;
	}

	return true;
}

bool	CPiePlotImpl::GetFreqPara( RECT plotRect, int which, double &ctx, double &cty, double &a, double &b, double &a1, double &b1, double &curr, double &ratio, double &total )
{
	if(which < 0 || which >= GetDataSetCount())return false;
	if(!GetFreqPara(plotRect, ctx, cty, a, b, total))return false;
	
	curr = m_fStartAngle/360.0;
	for( int i=0; i<which; i++)
	{
		ratio = m_vXYDataInfo[i].pDataSet->GetData()[0].y/total;
		if(m_bClockWise)ratio = -ratio;
		curr += ratio;
	}

	ratio = m_vXYDataInfo[which].pDataSet->GetData()[0].y/total;
	if(m_bClockWise)ratio = -ratio;

	double s1 = m_vXYDataInfo[which].fScale;
	if(s1<=0.0 || s1>1.0)s1=1.0;
	a1 = a * s1;
	b1 = b * s1;

	return true;
}

RECT	CPiePlotImpl::GetPieTitleRect( HDC hDC, RECT plotRect, int which, double ctx, double cty, double a1, double b1, double curr, double ratio, int &fontheight )
{
	RECT rect={0,0,0,0};
	if( which < 0 || which >= GetDataSetCount() )
		return rect;

	POINT ptStart;
	double dx,dy;
	dx = a1*cos((curr+ratio/2.0)*2.0*myPi);;
	dy = b1*sin((curr+ratio/2.0)*2.0*myPi);
	ptStart.x = long(ctx + dx);
	ptStart.y = long(cty - dy);

	HFONT		hOldFont, hFont;
	LOGFONT		logFont = m_lfPieTitleFont;

	SIZE	tmSize = {0,0};
	bool	keepGoing = true;
	if( m_vXYDataInfo[which].pDataSet->GetTitle() != "" )
	{
		// if the rect is too large, change the font size
		while( keepGoing == true )
		{
			hFont = CreateFontIndirect(&logFont);
			hOldFont = (HFONT)SelectObject(hDC,hFont);
			GetTextExtentPoint( hDC, m_vXYDataInfo[which].pDataSet->GetTitle().c_str(),m_vXYDataInfo[which].pDataSet->GetTitle().length(), &tmSize );
			SelectObject(hDC, hOldFont );
			DeleteObject(hFont);
			if( (tmSize.cx > abs(plotRect.right - plotRect.left ) || tmSize.cy > abs(plotRect.bottom - plotRect.top)) && logFont.lfHeight > 4 )
			{
				logFont.lfHeight--;
			}
			else
			{
				keepGoing = false;
			}
		}

		// the initial position
		if( dx > 0.0 && dy > 0.0 )
		{
			rect.left = ptStart.x;
			rect.right = ptStart.x + tmSize.cx;
			rect.top = ptStart.y - tmSize.cy;
			rect.bottom = ptStart.y;
		}
		else if( dx <= 0.0 && dy > 0.0 )
		{
			rect.left = ptStart.x - tmSize.cx;
			rect.right = ptStart.x;
			rect.top = ptStart.y - tmSize.cy;
			rect.bottom = ptStart.y;
		}
		else if( dx <= 0.0 && dy <= 0.0 )
		{
			rect.left = ptStart.x - tmSize.cx;
			rect.right = ptStart.x;
			rect.top = ptStart.y;
			rect.bottom = ptStart.y + tmSize.cy;
		}
		else
		{
			rect.left = ptStart.x;
			rect.right = ptStart.x + tmSize.cx;
			rect.top = ptStart.y;
			rect.bottom = ptStart.y + tmSize.cy;
		}

		// Adding the offset
		OffsetRect(&rect, m_vXYDataInfo[which].sizeTitleOffset.cx, m_vXYDataInfo[which].sizeTitleOffset.cy);

		// Adjust the position
		if( rect.left < plotRect.left )
			OffsetRect(&rect, plotRect.left - rect.left, 0);
		if( rect.right > plotRect.right )
			OffsetRect(&rect, plotRect.right - rect.right, 0);
		if( rect.top < plotRect.top )
			OffsetRect(&rect, 0, plotRect.top - rect.top );
		if( rect.bottom > plotRect.bottom )
			OffsetRect(&rect, 0, plotRect.bottom - rect.bottom );
	}

	fontheight = logFont.lfHeight;

	return rect;
}

RECT	CPiePlotImpl::GetPieTitleRect( HDC hDC, RECT plotRect, int which )
{
	RECT rect={0,0,0,0};
	if( which < 0 || which >= GetDataSetCount() )
		return rect;

	double ctx, cty, a, b, a1, b1, curr, ratio, total;
	if(!GetFreqPara(plotRect, which, ctx, cty, a, b, a1, b1, curr, ratio, total))
		return rect;

	int fontheight;
	return GetPieTitleRect(hDC, plotRect,which, ctx, cty, a1, b1, curr, ratio, fontheight );
}

HRGN	CPiePlotImpl::GetPieRegion( int which, HDC hDC, RECT plotRect, double ctx, double cty, double a1, double b1, double curr, double ratio )
{
	// Pie region
	HBRUSH hBrush = (HBRUSH)GetStockObject(NULL_BRUSH),hOldBrush;
	hOldBrush = (HBRUSH)SelectObject(hDC, hBrush);
	HPEN hPen = (HPEN)GetStockObject(NULL_PEN), hOldPen;
	hOldPen = (HPEN)SelectObject(hDC, hPen);
		
	BeginPath(hDC);
	if(ratio > 0.0)
	{
		Pie( hDC, int(ctx-a1), int(cty-b1), int(ctx+a1), int(cty+b1),
			int(ctx+a1*cos(curr*2.0*myPi)), int(cty-b1*sin(curr*2.0*myPi)),
			int(ctx+a1*cos((curr+ratio)*2.0*myPi)),int( cty-b1*sin((curr+ratio)*2.0*myPi)));
	}
	else
	{
		Pie( hDC, int(ctx-a1), int(cty-b1), int(ctx+a1), int(cty+b1),
			int(ctx+a1*cos((curr+ratio)*2.0*myPi)), int(cty-b1*sin((curr+ratio)*2.0*myPi)),
			int(ctx+a1*cos(curr*2.0*myPi)), int(cty-b1*sin(curr*2.0*myPi) ));
	}
	EndPath(hDC);
	
	SelectObject(hDC, hOldBrush);
	DeleteObject(hBrush);
	SelectObject(hDC, hOldPen);
	DeleteObject(hPen);
	
	HRGN hRgn = PathToRegion(hDC);

	return hRgn;
}

bool	CPiePlotImpl::PtInPieArea( HDC hDC, POINT point, RECT plotRect )
{
	double scale = m_fScale;
	if(scale<=0.0 || scale>1.0)scale=1.0;

	double a,b,ctx,cty;
	a = scale*abs(plotRect.right - plotRect.left)/2.0;
	b = scale*abs(plotRect.bottom - plotRect.top)/2.0;
	if(m_bCircleMode)
		a = b = min(a,b);
	ctx = (plotRect.right + plotRect.left)/2.0;
	cty = (plotRect.bottom + plotRect.top)/2.0;

	if(m_bShadowing)
	{
		ctx += m_nShadowHalfLength * cos( m_fShadowAngle * myPi /180.0);
		cty -= m_nShadowHalfLength * sin( m_fShadowAngle * myPi /180.0) * b / a;
	}

	HRGN hRgn = CreateEllipticRgn(int(ctx-a), int(cty-b), int(ctx+a), int(cty+b));
	if( PtInRegion(hRgn, point.x, point.y) )
	{
		DeleteObject(hRgn);
		return true;
	}

	DeleteObject(hRgn);

	return false;
}

bool	CPiePlotImpl::PtInPieArea( int which, HDC hDC, POINT point, RECT plotRect, bool withTitle )
{
	double ctx, cty, a, b, a1, b1, curr, ratio, total;
	GetFreqPara(plotRect, which, ctx, cty, a, b, a1, b1, curr, ratio, total);

	if(PtInPieArea(which, hDC, point, plotRect, withTitle, ctx, cty, a1, b1, curr, ratio ))
		return true;
	return false;
}

bool	CPiePlotImpl::PtInPieArea( int which, HDC hDC, POINT point, RECT plotRect, bool withTitle, double ctx, double cty, double a1, double b1, double curr, double ratio )
{
	// Pie region
	HRGN hRgn = GetPieRegion( which, hDC, plotRect, ctx, cty, a1, b1, curr, ratio );
	
	if( PtInRegion(hRgn, point.x, point.y) )
	{
		DeleteObject(hRgn);
		return true;
	}

	DeleteObject(hRgn);

	// Title region
	int fontheight;
	RECT PieTitleRect = GetPieTitleRect( hDC, plotRect, which, ctx, cty, a1, b1, curr, ratio, fontheight );
	if( PtInRect( & PieTitleRect, point ) )
	{
		return true;
	}
	
	return false;
}

bool	CPiePlotImpl::PtInPieTitleArea(  int which, HDC hDC, POINT point, RECT plotRect )
{
	RECT PieTitleRect = GetPieTitleRect( hDC, plotRect, which );
	if( PtInRect(&PieTitleRect, point) )return true;
	return false;
}

int		CPiePlotImpl::GetNeareastDataSet( HDC hDC, POINT point )
{
	if(GetDataSetCount()<=0)return -1;

	RECT plotRect = GetPlotRect(hDC, GetLastClientRect());

	int			i, nIdx=-1;

	// prepare begin
	double ratio,total = 0.0;
	for(i=0; i<GetDataSetCount(); i++)
	{
		if(m_vXYDataInfo[i].pDataSet->GetData()[0].y <= 0)return false;
		total += m_vXYDataInfo[i].pDataSet->GetData()[0].y;
	}
	if(total <= 0.0)return false;
	
	double scale = m_fScale;
	if(scale<=0.0 || scale>1.0)scale=1.0;
	
	double curr = m_fStartAngle/360.0;
	double a,b,ctx,cty;
	a = scale*abs(plotRect.right - plotRect.left)/2.0;
	b = scale*abs(plotRect.bottom - plotRect.top)/2.0;
	if(m_bCircleMode)
		a = b = min(a,b);
	ctx = (plotRect.right + plotRect.left)/2.0;
	cty = (plotRect.bottom + plotRect.top)/2.0;
	
	if(m_bShadowing)
	{
		ctx += m_nShadowHalfLength * cos( m_fShadowAngle * myPi /180.0);
		cty -= m_nShadowHalfLength * sin( m_fShadowAngle * myPi /180.0) * b / a;
	}
	
	double a1,b1,s1;
	// prepare end

	// determine
	for(i=0; i<GetDataSetCount(); i++)
	{
		ratio = m_vXYDataInfo[i].pDataSet->GetData()[0].y/total;
		if(m_bClockWise)ratio = -ratio;

		// prepare begin
		s1 = m_vXYDataInfo[i].fScale;
		if(s1<=0.0 || s1>1.0)s1=1.0;
		a1 = a * s1;
		b1 = b * s1;
		// prepare end

		if( PtInPieArea( i, hDC, point, plotRect, true, ctx, cty, a1, b1, curr, ratio ) )
		{
			nIdx = i;
			break;
		}

		curr += ratio;
	}

	if(nIdx==-1)
		return -1;
	else
		return GetDataID(nIdx);
}

