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

#include "Stdafx.h"
#include "XYPlotImpl.h"
#include "LegendImpl.h"
#include "AxisImpl.h"
#include "PlotUtility.h"
#include "DefHandlers/DefHandlers.h"
#include "DefHandlers/ColorControl.h"

/////////////////////////////////////////////////////////////////////////
// Class CPlot

CXYPlotImpl::CXYPlotImpl()
{
	if(!m_pLegend)m_pLegend = new CLegendImpl(this);
/*
	m_pFcnDS = DefDataSettings;
	m_pFcnAS = DefAxisSettings;
	m_pFcnPS = DefPlotSettings;
	m_pFcnPM = DefContextMenu;
*/
	m_bNewInteractive = true;

	RegisterColorControl();
}

CXYPlotImpl::~CXYPlotImpl()
{
	
}

// Gets the range of the plot from the axes, taking
// into account auto ranging if used
void	CXYPlotImpl::GetPlotRange( double *xRange, double *yRange )
{
	bool		haveXRange = false, haveYRange = false;
	bool		haveBottom = false, haveLeft = false;
	CAxis		*axis;
	int			i;
	double		optRange[2];
	int			optNTicks, optMinorTicks;
	CPlotData<DataPoint2D>	*dataSet;

	xRange[0] = 1e30;
	xRange[1] = -1e30;
	yRange[0] = 1e30;
	yRange[1] = -1e30;

	for( i = 0; i < GetAxisCount(); i++ )
	{
		axis = GetAxis(i);
		switch( axis->GetLocation() )
		{
		case kLocationTop:
		case kLocationCenterHB:
		case kLocationCenterHT:
			if( haveBottom == true || axis->IsRangeSet() == false )
				break;
			// fall through
		case kLocationBottom:
			if( axis->IsRangeSet() )
			{
				axis->GetRange( xRange );
				haveXRange = true;
			}
			haveBottom = true;
			break;
		case kLocationRight:
		case kLocationCenterVL:
		case kLocationCenterVR:
			if( haveLeft == true || axis->IsRangeSet() == false )
				break;
			// fall through
		case kLocationLeft:
			if( axis->IsRangeSet() )
			{
				axis->GetRange( yRange );
				haveYRange = true;
			}
			haveLeft = true;
			break;
		default: break;
		}
	}
		// Autoranging assumes the data is sorted
	if( haveXRange == false || haveYRange == false )
	{
		// Get the x range from the data
		for( i = 0; i < GetDataSetCount(); i++ )
		{
			dataSet = GetAbsoluteDataSet( i );
			if( haveXRange == false )
			{
				xRange[0] = min( xRange[0], m_vXYDataInfo[i].fXDataMin );
				xRange[1] = max( xRange[1], m_vXYDataInfo[i].fXDataMax );
				if(xRange[0]==xRange[1])
				{
					if(xRange[0]==0.0)
					{
						xRange[0]-=0.5;
						xRange[1]+=0.5;
					}
					else
					{
						xRange[0]-=pow(10,floor(log10(fabs(xRange[0]))));;
						xRange[1]+=pow(10,floor(log10(fabs(xRange[0]))));;
					}
				}
			}
			if( haveYRange == false )
			{
				yRange[0] = min( yRange[0], m_vXYDataInfo[i].fYDataMin );
				yRange[1] = max( yRange[1], m_vXYDataInfo[i].fYDataMax );
				if(yRange[0]==yRange[1])
				{
					if(yRange[0]==0.0)
					{
						yRange[0]-=0.5;
						yRange[1]+=0.5;
					}
					else
					{
						yRange[0]-=pow(10,floor(log10(fabs(yRange[0]))));;
						yRange[1]+=pow(10,floor(log10(fabs(yRange[0]))));;
					}
				}
			}
		}
	}

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
				if( haveBottom == true ) break;
				// fall through
			case kLocationBottom:
				if( haveXRange )
					GetOptimalRangeExact( xRange, optRange, &optNTicks, &optMinorTicks );
				else
				{
					GetOptimalRange( xRange, optRange, &optNTicks, &optMinorTicks, true );
					axis->SetRange( false, optRange[0], optRange[1] );
				}

				memcpy( xRange, optRange, 2*sizeof( double ) );
				//axis->SetTickCount( -optNTicks );
				if(axis->IsAutoMajorTick()) axis->SetTickCount( optNTicks );
				//axis->SetMinorTickCount( -optMinorTicks );
				if(axis->IsAutoMinorTick()) axis->SetMinorTickCount( optMinorTicks );
				haveBottom = true;
				break;
			case kLocationRight:
			case kLocationCenterVL:
			case kLocationCenterVR:
				if( haveLeft == true ) break;
				// fall through
			case kLocationLeft:
				if( haveYRange )
					GetOptimalRangeExact( yRange, optRange, &optNTicks, &optMinorTicks );
				else
				{
					GetOptimalRange( yRange, optRange, &optNTicks, &optMinorTicks, false );
					axis->SetRange( false, optRange[0], optRange[1] );
				}
				memcpy( yRange, optRange, 2*sizeof( double ) );
				//axis->SetTickCount( -optNTicks );
				if(axis->IsAutoMajorTick()) axis->SetTickCount( optNTicks );
				//axis->SetMinorTickCount( -optMinorTicks );
				if(axis->IsAutoMinorTick()) axis->SetMinorTickCount( optMinorTicks );
				haveLeft = true;
				break;
			default: break;
			}
		}
	}

	// Set equally range
	if( m_bEqualXYRange )
	{
		double range[2];
		range[0] = min( xRange[0], yRange[0] );
		range[1] = max( xRange[1], yRange[1] );
		xRange[0] = yRange[0] = range[0];
		xRange[1] = yRange[1] = range[1];

		// need to set the axis range and tickcount
		GetOptimalRangeExact( range, optRange, &optNTicks, &optMinorTicks );
		for( i = 0; i < GetAxisCount(); i++ )
		{
			axis = GetAxis(i);
			axis->SetRange( range[0], range[1] );
			axis->SetTickCount( optNTicks );
			axis->SetMinorTickCount( optMinorTicks );
		}
	}
}

void	CXYPlotImpl::OnDraw( HWND hWnd )
{
	HDC hDC = GetDC(hWnd);
	RECT destRect;
	GetClientRect(hWnd,&destRect);
	
	OnDraw( hDC, destRect );
	
	ReleaseDC(hWnd, hDC);
}

void	CXYPlotImpl::OnDraw(HDC hDC, RECT destRect)
{
	//if there is no data, doing nothing
	if(m_vXYDataInfo.size()<=0)
	{
		EraseBkgnd( hDC, destRect );
		return;
	}

	//////////////////////////////////////////////////////////////////

	RECT			plotRect;
	double			xRange[] = {1e30, -1e30}, yRange[]={1e30,-1e30};

	// Make sure our ranges are set
	// Get ranges for plotting
	GetPlotRange( xRange, yRange );
	// Get the size of our plotting rectangle
	plotRect = GetPlotRect( hDC, destRect );
	// Erase background
	EraseBkgnd(hDC, destRect);
	// Draw each data set
	DrawDataSets( hDC, plotRect, xRange, yRange );
	// Draw basics
	CPlotImpl::OnDraw(hDC,destRect);
}


// Draws the actual data set, including markers
void	CXYPlotImpl::DrawDataSets( HDC hDC, RECT plotRect, double *xRange, double *yRange )
{
	int			i;
	HRGN		hRgn;
	int			saveDC;
	RECT		dPlotRect = plotRect;

	// Create a region for clipping
	saveDC = SaveDC(hDC);
	
	//PlotRect.InflateRect( 1, -1, -1, 1 );
	InflateRect(&plotRect,2,2);
	LPtoDP( hDC,(LPPOINT) &dPlotRect, 2); 

	hRgn=CreateRectRgn( dPlotRect.left, dPlotRect.top, dPlotRect.right, dPlotRect.bottom );
	SelectObject(hDC,hRgn);

	// Set line colors,line styles, line sizes
	SetPlotColors();
	SetPlotLineStyles();
	SetPlotLineSizes();

	// Begin draw
	for( i = 0; i < GetDataSetCount(); i++ )
	{
		DrawSingleDataSet(i,hDC,plotRect,xRange,yRange);
	}

	RestoreDC(hDC, saveDC );
	
	DeleteObject(hRgn);
}

void	CXYPlotImpl::DrawSingleDataSet( int which, HDC hDC, RECT plotRect, double *xRange, double *yRange )
{
	if(!m_vXYDataInfo[which].bDataShow)return;

	int			j, nPts, nPts4Fill, nDatas;
	POINT		point, *myPoints = NULL;
	double		x1,x2, y1, y2;
	double		xScale, yScale;

	HPEN		hPen, hOldPen;
	HBRUSH		hBrush, hOldBrush;

	CPlotData<DataPoint2D>	*dataSet = GetAbsoluteDataSet( which );
	if( dataSet->GetData().size()<=0 ) return;

	hPen = CreatePen( m_vXYDataInfo[which].nPlotLineStyle, m_vXYDataInfo[which].nPlotLineSize, m_vXYDataInfo[which].crPlotColor );
	hOldPen = (HPEN)SelectObject(hDC, hPen );

	// We now have a rect and an xRange and a yRange, just some
	// simple transformations should get us our plot
	xScale = ((double)(plotRect.right-plotRect.left))/(xRange[1] - xRange[0]);
	yScale = ((double)(plotRect.bottom-plotRect.top))/(yRange[1] - yRange[0]);

	// Draw the dataset
	int plottype = m_vXYDataInfo[which].nPlotType;
	if(plottype == kXYPlotBezier && dataSet->GetData().size() < 4)plottype = kXYPlotConnect;
	nPts = nDatas = dataSet->GetData().size();
	switch( plottype )
	{
	case kXYPlotBezier:
		if(nDatas % 3 == 0)nPts += 1;
		else if( nDatas % 3 == 2 )	nPts += 2;
		break;
	case kXYPlotStepHV:
	case kXYPlotStepVH:
		nPts = 2 * nDatas - 1;
		break;
	case kXYPlotStepHVH:
	case kXYPlotStepVHV:
		nPts = 3 * nDatas - 2;
	}
	
	nPts4Fill = nPts;
	int fillmode = m_vXYDataInfo[which].nDataFillMode;
	if( fillmode == kDataFillFromBottomAxis || fillmode == kDataFillFromTopAxis
		|| fillmode == kDataFillFromLeftAxis || fillmode == kDataFillFromRightAxis)
	{
		nPts4Fill += 2;
	}
	myPoints = new POINT[nPts4Fill];

	switch( plottype )
	{
	case kXYPlotScatter:
		//Only need draw markers, have already done
		SelectObject(hDC,(HBRUSH)GetStockObject(NULL_BRUSH));
		//break;
	case kXYPlotConnect:
	case kXYPlotBezier:
		for( j = 0; j < nDatas; j++ )
		{
			point.x = (long)(xScale * (dataSet->GetData()[j].x-xRange[0]) + plotRect.left);
			point.y = (long)(plotRect.bottom - yScale * (dataSet->GetData()[j].y-yRange[0]));
			myPoints[j] = point;
		}
		if( plottype == kXYPlotBezier )
		{
			for( j = nDatas; j < nPts; j++ )
			{
				myPoints[j] = point;
			}
		}
		if( plottype == kXYPlotConnect )
			Polyline(hDC, myPoints, nPts);
		else if( plottype == kXYPlotBezier )
			PolyBezier(hDC, myPoints, nPts);
		break;
	case kXYPlotStepHV:
	case kXYPlotStepVH:
		for( j = 0; j < nDatas-1; j++ )
		{
			point.x = (long)(xScale * (dataSet->GetData()[j].x-xRange[0]) + plotRect.left);
			point.y = (long)(plotRect.bottom - yScale * (dataSet->GetData()[j].y-yRange[0]));
			myPoints[2*j] = point;
			if( plottype == kXYPlotStepHV )
			{
				point.x = (long)(xScale * (dataSet->GetData()[j+1].x-xRange[0]) + plotRect.left);
			}
			else if( plottype == kXYPlotStepVH )
			{
				point.y = (long)(plotRect.bottom - yScale * (dataSet->GetData()[j+1].y-yRange[0]));
			}
			myPoints[2*j+1] = point;
		}
		point.x = (long)(xScale * (dataSet->GetData()[nDatas-1].x-xRange[0]) + plotRect.left);
		point.y = (long)(plotRect.bottom - yScale * (dataSet->GetData()[nDatas-1].y-yRange[0]));
		myPoints[2*nDatas-2] = point;
		Polyline(hDC, myPoints, nPts);
		break;
	case kXYPlotStepHVH:
	case kXYPlotStepVHV:
		for( j = 0; j < nDatas-1; j++ )
		{
			point.x = (long)(xScale * (dataSet->GetData()[j].x-xRange[0]) + plotRect.left);
			point.y = (long)(plotRect.bottom - yScale * (dataSet->GetData()[j].y-yRange[0]));
			myPoints[3*j] = point;
			if( plottype == kXYPlotStepHVH )
			{
				x1 = point.x;
				x2 = (long)(xScale * (dataSet->GetData()[j+1].x-xRange[0]) + plotRect.left);
				point.x = long( (x1 + x2) / 2 );
				myPoints[3*j+1] = point;
				y2 = (long)(plotRect.bottom - yScale * (dataSet->GetData()[j+1].y-yRange[0]));
				point.y = long( y2 );
				myPoints[3*j+2] = point;
			}
			else if( plottype == kXYPlotStepVHV )
			{
				y1 = point.y;
				y2 = (long)(plotRect.bottom - yScale * (dataSet->GetData()[j+1].y-yRange[0]));
				point.y = long( (y1 + y2) / 2 );
				myPoints[3*j+1] = point;
				x2 = (long)(xScale * (dataSet->GetData()[j+1].x-xRange[0]) + plotRect.left);
				point.x = long( x2 );
				myPoints[3*j+2] = point;
			}
		}
		point.x = (long)(xScale * (dataSet->GetData()[nDatas-1].x-xRange[0]) + plotRect.left);
		point.y = (long)(plotRect.bottom - yScale * (dataSet->GetData()[nDatas-1].y-yRange[0]));
		myPoints[3*nDatas-3] = point;
		Polyline(hDC, myPoints, nPts);
		break;
	default:
		break;
	}

	// Fill data
	if(m_vXYDataInfo[which].bDataFill)
	{
		switch(m_vXYDataInfo[which].nDataFillBrushType)
		{
		case kBrushSolid:
			hBrush = CreateSolidBrush( m_vXYDataInfo[which].crDataFillColor );
			break;
		case kBrushHatch:
			hBrush = CreateHatchBrush(m_vXYDataInfo[which].nDataFillHatchStyle,m_vXYDataInfo[which].crDataFillColor);
			break;
		case kBrushPattern:
			hBrush = CreatePatternBrush(m_vXYDataInfo[which].hDataFillPattern);
			break;
		default:
			hBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
			break;
		}
		hOldBrush = (HBRUSH)SelectObject( hDC,hBrush );

		switch(m_vXYDataInfo[which].nDataFillMode)
		{
		case kDataFillClosed:
			break;
		case kDataFillFromBottomAxis:
		case kDataFillFromTopAxis:
			point.x = (long)(xScale * (dataSet->GetData()[nDatas-1].x-xRange[0]) + plotRect.left);
			if(m_vXYDataInfo[which].nDataFillMode == kDataFillFromBottomAxis)
				point.y = plotRect.bottom;
			else
				point.y = plotRect.top;
			myPoints[nPts4Fill - 2] = point;
			point.x = (long)(xScale * (dataSet->GetData()[0].x-xRange[0]) + plotRect.left);
			myPoints[nPts4Fill - 1] = point;
			break;
		case kDataFillFromLeftAxis:
		case kDataFillFromRightAxis:
			point.y = (long)(plotRect.bottom - yScale * (dataSet->GetData()[nDatas-1].y-yRange[0]));
			if(m_vXYDataInfo[which].nDataFillMode == kDataFillFromLeftAxis)
				point.x = plotRect.left;
			else
				point.x = plotRect.right;
			myPoints[nPts4Fill - 2] = point;
			point.y = (long)(plotRect.bottom - yScale * (dataSet->GetData()[0].y-yRange[0]));
			myPoints[nPts4Fill - 1] = point;
			break;
		default:
			break;
		}
		BeginPath(hDC);
		switch(plottype)
		{
		case kXYPlotConnect:
		case kXYPlotStepHV:
		case kXYPlotStepVH:
		case kXYPlotStepHVH:
		case kXYPlotStepVHV:
			Polyline(hDC, myPoints, nPts4Fill);
			break;
		case kXYPlotBezier:
			PolyBezier(hDC, myPoints, nPts4Fill );
			break;
		}			
		EndPath( hDC );
		StrokeAndFillPath(hDC);

		SelectObject(hDC,hOldBrush);
		DeleteObject(hBrush);
	}

	if(myPoints)delete []myPoints;

	//Draw the info of every data set, mainly used in the contour chart
	DrawDataSetInfo(which,hDC,plotRect,xRange,yRange);
	
	//Draw Markers
	DrawMarkers(which,hDC,plotRect,xRange,yRange);
	
	SelectObject( hDC,hOldPen );
	DeleteObject(hPen);
}

void	CXYPlotImpl::DrawDataSetInfo( int which, HDC hDC, RECT plotRect, double *xRange, double *yRange )
{
	CPlotData<DataPoint2D>	*dataSet = GetAbsoluteDataSet( which );

	if(!dataSet || !dataSet->IsInfoDraw())return;

	HFONT		hOldFont, hFont;
	LOGFONT		logFont;
	SIZE		tmSize;
	
	POINT		ptInfo;
	int			idxPtInfo=0;//this curve draw the info at this point
	int			theIdx;//data set index, some times get from data level(when draw contour)

	double		xScale = ((double)(plotRect.right-plotRect.left))/(xRange[1] - xRange[0]);
	double		yScale = ((double)(plotRect.bottom-plotRect.top))/(yRange[1] - yRange[0]);

	//MyVData vData = dataSet->GetData();
	bool		bDrawThis=false;
	if(dataSet->GetInfo()!="")
	{
		theIdx=dataSet->GetDataLevel()>=0?dataSet->GetDataLevel():which;
		switch(m_nShowDataSetInfoMode)
		{
		case kShowDataSetInfoNot:
			bDrawThis=false;
			break;
		case kShowDataSetInfoEveryN:
			if( theIdx%m_nShowDataSetInfoNum==0 )bDrawThis=true;
			break;
		case kShowDataSetInfoTotalN:
			if( theIdx%(int)ceil(GetDataSetLevels()/(double)m_nShowDataSetInfoNum)==0 )bDrawThis=true;
			break;
		default:
			break;
		}
	}
	if(!bDrawThis)return;

	logFont=GetTitleFont();
	logFont.lfHeight=dataSet->GetInfoFontsize();
	hFont = CreateFontIndirect(&logFont);
	hOldFont = (HFONT)SelectObject( hDC, hFont );

	GetTextExtentPoint(hDC,dataSet->GetInfo().c_str(),dataSet->GetInfo().length(),&tmSize);

	if(idxPtInfo>=dataSet->GetDataSize())idxPtInfo%=dataSet->GetData().size();
	ptInfo.x=(long)(xScale * (dataSet->GetData()[idxPtInfo].x-xRange[0]) + plotRect.left);
	ptInfo.y = (long)(plotRect.bottom - yScale * (dataSet->GetData()[idxPtInfo].y-yRange[0]))+tmSize.cy/2;
	if(ptInfo.x+tmSize.cx>plotRect.right)ptInfo.x=plotRect.right-tmSize.cx;
	if(ptInfo.y+tmSize.cy>plotRect.bottom)ptInfo.y=plotRect.bottom-tmSize.cy;

	if( dataSet->GetInfo()!="")
	{
		SetBkMode(hDC,TRANSPARENT);
		SetTextColor(hDC,m_vXYDataInfo[which].crPlotColor);
		TextOut(hDC,ptInfo.x,ptInfo.y,dataSet->GetInfo().c_str(),dataSet->GetInfo().length());
	}
	idxPtInfo+=m_nShowDataSetInfoDataPointStep;

	SelectObject(hDC, hOldFont );
	DeleteObject(hFont);
}

void	CXYPlotImpl::DrawMarkers(int whichDataSet, HDC hDC, RECT plotRect, double *xRange, double *yRange)
{
	int j;
	CPlotData<DataPoint2D>	*dataSet = GetAbsoluteDataSet( whichDataSet );

	double xScale,yScale;
	POINT point;

	xScale = ((double)(plotRect.right-plotRect.left))/(xRange[1] - xRange[0]);
	yScale = ((double)(plotRect.bottom-plotRect.top))/(yRange[1] - yRange[0]);

	for( j = 0; j < dataSet->GetDataSize(); j++ )
	{
		point.x = (long)(xScale * (dataSet->GetData()[j].x-xRange[0]) + plotRect.left);
		point.y = (long)(plotRect.bottom - yScale * (dataSet->GetData()[j].y-yRange[0]));
		DrawSingleMarker( hDC, point, whichDataSet, j );
	}
}

// Draws a marker at the current point, if a marker should be drawn there
void	CXYPlotImpl::DrawSingleMarker( HDC hDC, POINT point, int whichDataSet, int dataPointNumber )
{
	HBRUSH		hBrush, hOldBrush;
	RECT		rect;
	HPEN		hPen, hOldPen;
	POINT		startPoint, startLocation;

	if( m_vXYDataInfo[whichDataSet].nMarkerType == kXYMarkerNone ) return;

	// Check to see if we want to draw this marker
	if( m_vXYDataInfo[whichDataSet].nMarkerFrequency > 0 )
	{
		// positive means every nth data point
		if( dataPointNumber % m_vXYDataInfo[whichDataSet].nMarkerFrequency != 0 ) return;
	}
	else if( m_vXYDataInfo[whichDataSet].nMarkerFrequency < 0 )
	{
		// negative means n number of times
		int			n_elements = GetDataSet(GetDataID(whichDataSet))->GetData().size();
		int			n_markers = abs(m_vXYDataInfo[whichDataSet].nMarkerFrequency);
		if(n_markers==1)
		{
			if(dataPointNumber!=0)
				return;
		}
		else
		{
			// it is not easy to find an expression, so i use a loop
			for(int i=0;i<n_markers;i++)
			{
				if(dataPointNumber==i*(n_elements-1)/(n_markers-1))
					goto NeedDrawMarker;
			}
			return;
		}
	}
	else
		return; // == 0 means no marker

NeedDrawMarker:

	GetCurrentPositionEx(hDC,&startLocation);
	
	hPen=CreatePen( PS_SOLID, 1, m_vXYDataInfo[whichDataSet].crPlotColor );

	hOldPen = (HPEN)SelectObject( hDC,hPen );

	SetRect( &rect, point.x - m_vXYDataInfo[whichDataSet].nMarkerSize, point.y - m_vXYDataInfo[whichDataSet].nMarkerSize,
		point.x + m_vXYDataInfo[whichDataSet].nMarkerSize, point.y + m_vXYDataInfo[whichDataSet].nMarkerSize );

	hBrush=CreateSolidBrush( m_vXYDataInfo[whichDataSet].crPlotColor );

	hOldBrush = (HBRUSH)SelectObject( hDC,hBrush );

	BeginPath(hDC);

	double s2=sqrt(2.0);
	double offset;
	switch( m_vXYDataInfo[whichDataSet].nMarkerType )
	{
	case kXYMarkerNone:
		return; break;
	case kXYMarkerCircle:
		// the size is the radius
		Arc( hDC, rect.left,rect.top,rect.right,rect.bottom, point.x, point.y, point.x, point.y );
		break;
	case kXYMarkerSquareUpright:
		//MyFrameRect( pDC, rect );
		MoveToEx(hDC,rect.left,rect.top,NULL);
		LineTo(hDC,rect.right,rect.top);
		LineTo(hDC,rect.right,rect.bottom);
		LineTo(hDC,rect.left,rect.bottom);
		LineTo(hDC,rect.left,rect.top);
		break;
	case kXYMarkerSquareOblique:
		offset=ceil(m_vXYDataInfo[whichDataSet].nMarkerSize*s2);
		startPoint.x = point.x - (long)offset;
		startPoint.y = point.y;
		MoveToEx( hDC, startPoint.x, startPoint.y, NULL );
		startPoint.x += (long)offset;
		startPoint.y += (long)offset;
		LineTo( hDC, startPoint.x, startPoint.y );
		startPoint.x += (long)offset;
		startPoint.y -= (long)offset;
		LineTo( hDC, startPoint.x, startPoint.y );
		startPoint.x -= (long)offset;
		startPoint.y -= (long)offset;
		LineTo( hDC, startPoint.x, startPoint.y );
		startPoint.x -= (long)offset;
		startPoint.y += (long)offset;
		LineTo( hDC, startPoint.x, startPoint.y );
		MoveToEx( hDC, point.x, point.y, NULL );
		break;
	case kXYMarkerTriangleLeft:
		// Need to update this to actually center correctly using
		// the triangle's geometry
		offset=m_vXYDataInfo[whichDataSet].nMarkerSize;
		startPoint.x = point.x - (long)offset;
		startPoint.y = point.y ;
		MoveToEx( hDC, startPoint.x, startPoint.y, NULL );
		//startPoint.Offset( 2 *offset,  offset );
		startPoint.x += 2*(long)offset;
		startPoint.y -= (long)offset;
		LineTo( hDC, startPoint.x, startPoint.y );
		//startPoint.Offset( 0, -2*offset );
		startPoint.y += 2*(long)offset;
		LineTo( hDC, startPoint.x, startPoint.y );
		//startPoint.Offset( -2 *offset,  offset );
		startPoint.x -= 2*(long)offset;
		startPoint.y -= (long)offset;
		LineTo( hDC, startPoint.x, startPoint.y );
		MoveToEx( hDC, point.x, point.y, NULL );
		break;
	case kXYMarkerTriangleRight:
		// Need to update this to actually center correctly using
		// the triangle's geometry
		offset=m_vXYDataInfo[whichDataSet].nMarkerSize;
		startPoint.x = point.x + (long)offset;
		startPoint.y = point.y ;
		MoveToEx( hDC, startPoint.x, startPoint.y, NULL );
		//startPoint.Offset( -2 *offset,  offset );
		startPoint.x -= 2*(long)offset;
		startPoint.y -= (long)offset;
		LineTo( hDC, startPoint.x, startPoint.y );
		//startPoint.Offset( 0, -2*offset );
		startPoint.y += 2*(long)offset;
		LineTo( hDC, startPoint.x, startPoint.y );
		//startPoint.Offset( 2 *offset,  offset );
		startPoint.x += 2*(long)offset;
		startPoint.y -= (long)offset;
		LineTo( hDC, startPoint.x, startPoint.y );
		MoveToEx( hDC, point.x, point.y, NULL );
		break;
	case kXYMarkerTriangleUp:
		// Need to update this to actually center correctly using
		// the triangle's geometry
		offset=m_vXYDataInfo[whichDataSet].nMarkerSize;
		startPoint.x = point.x;
		startPoint.y = point.y - (long)offset;
		MoveToEx( hDC, startPoint.x, startPoint.y, NULL );
		//startPoint.Offset( offset, -2 * offset );
		startPoint.x += (long)offset;
		startPoint.y += 2*(long)offset;
		LineTo( hDC, startPoint.x, startPoint.y );
		//startPoint.Offset( -2*offset, 0 );
		startPoint.x -= 2*(long)offset;
		LineTo( hDC, startPoint.x, startPoint.y );
		//startPoint.Offset( offset, 2 * offset );
		startPoint.x += (long)offset;
		startPoint.y -= 2*(long)offset;
		LineTo( hDC, startPoint.x, startPoint.y );
		MoveToEx( hDC, point.x, point.y, NULL );
		break;
	case kXYMarkerTriangleDown:
		// Need to update this to actually center correctly using
		// the triangle's geometry
		offset=m_vXYDataInfo[whichDataSet].nMarkerSize;
		startPoint.x = point.x;
		startPoint.y = point.y + (long)offset;
		MoveToEx( hDC, startPoint.x, startPoint.y, NULL );
		//startPoint.Offset( offset, 2 * offset );
		startPoint.x += (long)offset;
		startPoint.y -= 2*(long)offset;
		LineTo( hDC, startPoint.x, startPoint.y );
		//startPoint.Offset( -2*offset, 0 );
		startPoint.x -= 2*(long)offset;
		LineTo( hDC, startPoint.x, startPoint.y );
		//startPoint.Offset( offset, -2 * offset );
		startPoint.x += (long)offset;
		startPoint.y += 2*(long)offset;
		LineTo( hDC, startPoint.x, startPoint.y );
		MoveToEx( hDC, point.x, point.y, NULL );
		break;
	case kXYMarkerX:
		offset=m_vXYDataInfo[whichDataSet].nMarkerSize;
		startPoint.x = point.x - (long)offset;
		startPoint.y = point.y + (long)offset;
		MoveToEx( hDC, startPoint.x, startPoint.y, NULL );
		//startPoint.Offset( 2*offset, 2*offset );
		startPoint.x += 2*(long)offset;
		startPoint.y -= 2*(long)offset;
		LineTo( hDC, startPoint.x, startPoint.y );
		//startPoint.Offset( -2*offset, 0 );
		startPoint.x -= 2*(long)offset;
		MoveToEx( hDC, startPoint.x, startPoint.y, NULL );
		//startPoint.Offset( 2*offset, -2*offset );
		startPoint.x += 2*(long)offset;
		startPoint.y += 2*(long)offset;
		LineTo( hDC, startPoint.x, startPoint.y );
		// Move back to beginning
		MoveToEx( hDC, point.x, point.y, NULL );
		break;
	case kXYMarkerDot:
		offset=m_vXYDataInfo[whichDataSet].nMarkerSize/5;
		startPoint.x = point.x - (long)offset;
		startPoint.y = point.y;
		MoveToEx( hDC, startPoint.x, startPoint.y, NULL );
		//startPoint.Offset(offset,offset);
		startPoint.x += (long)offset;
		startPoint.y -= (long)offset;
		LineTo( hDC, startPoint.x, startPoint.y );
		//startPoint.Offset(offset,-offset);
		startPoint.x += (long)offset;
		startPoint.y += (long)offset;
		LineTo( hDC, startPoint.x, startPoint.y );
		//startPoint.Offset(-offset,-offset);
		startPoint.x -= (long)offset;
		startPoint.y += (long)offset;
		LineTo( hDC, startPoint.x, startPoint.y );
		//startPoint.Offset(-offset,+offset);
		startPoint.x -= (long)offset;
		startPoint.y -= (long)offset;
		LineTo( hDC, startPoint.x, startPoint.y );
		// Move back to beginning
		MoveToEx( hDC, point.x, point.y, NULL );
		break;
	}

	EndPath(hDC);

	if( m_vXYDataInfo[whichDataSet].bMarkerFill )
		StrokeAndFillPath(hDC);
	else
		StrokePath(hDC);

	MoveToEx( hDC, startLocation.x, startLocation.y, NULL );
	SelectObject( hDC,hOldPen );
	DeleteObject(hPen);
	SelectObject( hDC,hOldBrush );
	DeleteObject(hBrush);
}

void	CXYPlotImpl::ApproachNearestIdx(int curIdx,int &nIdx,double *data,int lo,int up,double dlM,double &dl0)
{
	double dlt;
	double x0=data[0],y0;
	double xlo,xup,ylo,yup;
	xlo = GetAbsoluteData( curIdx )[lo].x;
	xup = GetAbsoluteData( curIdx )[up].x;
	ylo = GetAbsoluteData( curIdx )[lo].y;
	yup = GetAbsoluteData( curIdx )[up].y;
	if( xup - xlo != 0.0 )
	{
		int plottype = m_vXYDataInfo[curIdx].nPlotType;
		switch(plottype)
		{
		case kXYPlotConnect:
			y0 = ylo + ( yup - ylo )/(xup - xlo ) * (x0 - xlo);
			break;
		case kXYPlotStepHV:
			y0 = ylo;
			break;
		case kXYPlotStepVH:
			y0 = yup;
			break;
		case kXYPlotStepHVH:
			if(data[0] < (xlo + xup)/2)
				y0 = ylo;
			else
				y0 = yup;
			break;
		case kXYPlotStepVHV:
			y0 = (ylo + yup)/2;
			break;
		default:
			y0 = ylo + ( yup - ylo )/(xup - xlo ) * (x0 - xlo);
		}
		// determine y hit
		dlt = fabs(y0-data[1]);
		if(dlt<dlM)
		{
			goto HitTheCurve;
		}
		// determine x hit
		switch(plottype)
		{
		case kXYPlotStepHV:
			dlt = fabs(xup - data[0]);
			if(dlt<dlM && (data[1]-ylo)*(yup-data[1]>=0))
				goto HitTheCurve;
			break;
		case kXYPlotStepVH:
			dlt = fabs(xlo - data[0]);
			if(dlt<dlM && (data[1]-ylo)*(yup-data[1]>=0))
				goto HitTheCurve;
			break;
		case kXYPlotStepHVH:
			dlt = fabs( (xlo + xup)/2 - data[0]);
			if(dlt<dlM && (data[1]-ylo)*(yup-data[1]>=0))
				goto HitTheCurve;
			break;
		case kXYPlotStepVHV:
			if( data[0] < (xlo+xup)/2 )
			{
				dlt = fabs(xlo - data[0]);
				if(dlt<dlM && (data[1]-ylo)*((ylo+yup)/2-data[1]>=0))
				goto HitTheCurve;
			}
			else
			{
				dlt = fabs(xup - data[0]);
				if(dlt<dlM && (data[1]-(ylo+yup)/2 )*(yup-data[1]>=0))
				goto HitTheCurve;
			}
			break;
		default:
			break;
		}
		
	}
	else
	{
		dlt = fabs(data[0]-xlo);
		if(dlt<dlM && (yup-data[1])*(data[1]-ylo)>=0.0)
		{
			goto HitTheCurve;
		}
	}
	return;

HitTheCurve:
	if(nIdx==-1)
	{
		nIdx=curIdx;
		dl0=dlt;
	}
	else
	{
		if(dlt<dl0)
		{
			nIdx=curIdx;
			dl0=dlt;
		}
	}
}

int		CXYPlotImpl::GetNeareastDataSet( HDC hDC, POINT point )
{
	if(m_vXYDataInfo.size()<=0)return -1;

	CPlotData<DataPoint2D>			*dataSet;

	int					i, j, lo, up;
	double				data[2],range[2];
	
	int					nIdx;
	double				dlM,dl0;

	GetYRange(range);
	dlM=(range[1]-range[0])/128.0;

	LPToData( hDC, &point, data );

	nIdx=-1;
	for(i=0;i<GetDataSetCount();i++)
	{
		dataSet = GetDataSet( GetDataID( i ) );

		if( dataSet->GetData().size()<=1 ) continue;
		lo=-1;
		up=-1;
		
		GetDataRange( GetDataID(i) );

		if(data[0]<m_vXYDataInfo[i].fXDataMin || data[0]>m_vXYDataInfo[i].fXDataMax)
		{
			continue;
		}
		else
		{
			for(j=1;j<dataSet->GetDataSize();j++)
			{
				if( (data[0]-dataSet->GetData()[j-1].x)*(dataSet->GetData()[j].x-data[0])>=0.0 )
				{
					lo=j-1;
					up=j;
					ApproachNearestIdx(i,nIdx,data,lo,up,dlM,dl0);
					if(nIdx>=0)break;
				}
			}
		}
	}
	if(nIdx==-1)
		return -1;
	else
		return GetDataID(nIdx);
}

int		CXYPlotImpl::GetNeareastDataPoint( int dataID, HDC hDC, POINT point, double data[2])
{
	CPlotData<DataPoint2D> *pDataSet=GetDataSet(dataID);
	if(!pDataSet)return -1;
	if(pDataSet->GetData().size()<=0)return -1;

	int idx = GetIndex(dataID);

	LPToData( hDC, &point, data );
	if(data[0]<m_vXYDataInfo[idx].fXDataMin || data[0]>m_vXYDataInfo[idx].fXDataMax)return -1;

	int lo = -1, up = -1;
	bool set = false;
	double x0=data[0],y0=data[1];
	double y1, dist = 1.0e90;
	double xlo, xup, ylo, yup;

	for(int i=1; i<pDataSet->GetDataSize(); i++)
	{
		if( (data[0]-pDataSet->GetData()[i-1].x)*(pDataSet->GetData()[i].x-data[0])>=0.0 )
		{
			lo=i-1;
			up=i;
			set=true;
			
			xlo = pDataSet->GetData()[lo].x;
			xup = pDataSet->GetData()[up].x;
			ylo = pDataSet->GetData()[lo].y;
			yup = pDataSet->GetData()[up].y;

			if( xup - xlo != 0.0 )
				y1=ylo + ( yup - ylo )/(xup - xlo ) * (x0 - xlo);
			else
				y1=y0;
			
			if( fabs(y1-y0)<dist )
			{
				dist=fabs(y1-y0);
				data[1]=y1;
			}
		}
	}

	if(set)return lo;
	else return -1;
}
/*
int		CXYPlotImpl::RegionIdentify( HDC hDC, POINT point )
{
	CAxis *pAxis=0;
	RECT theRect;
	
	//data region
	theRect=GetPlotRect(hDC,m_rctLastClientRect );
	//if( (theRect.right-point.x)*(point.x-theRect.left)>=0 && (theRect.top-point.y)*(point.y-theRect.bottom)>=0 )
	if( PtInRect(&theRect,point) )
		return kXYRegionData;
	//title region
	theRect=GetTitleRect(hDC,m_rctLastClientRect ,GetPlotRect(hDC, m_rctLastClientRect ));
	//if( (theRect.right-point.x)*(point.x-theRect.left)>=0 && (theRect.top-point.y)*(point.y-theRect.bottom)>=0 )
	if( PtInRect(&theRect,point) )
		return kXYRegionTitle;
	//axis region
	CAxis *axis;
	for(int i=0;i<GetAxisCount();i++)
	{
		axis=GetAxis(i);
		theRect=((CAxisImpl*)axis)->GetPlotRect(hDC,m_rctLastClientRect , GetPlotRect(hDC,m_rctLastClientRect ));
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
*/


int		CXYPlotImpl::LightByPoint( HDC hDC, POINT point )
{
	if( RegionIdentify(hDC,point) != kXYRegionData )return -1;
	int dataID;
	
	if(m_bUseLegend)
	{
		int n=((CLegendImpl *)GetLegend())->RegionIdentify(hDC,point);
		if(n>=0 && n<GetDataSetCount())
		{
			dataID=GetDataID(n);
			goto LightCurveByPoint;
		}
	}	
	dataID=GetNeareastDataSet(hDC,point);
LightCurveByPoint:
	if(dataID>=0)
	{
		SetLighted(dataID,true);
		return dataID;
	}
	else
	{
		UnlightAllDataSets();
		return -1;
	}
}

int		CXYPlotImpl::SelectByPoint( HDC hDC, POINT point )
{
	if( RegionIdentify(hDC,point) != kXYRegionData )return -1;
	int dataID;
	
	if(m_bUseLegend)
	{
		int n=((CLegendImpl *)GetLegend())->RegionIdentify(hDC,point);
		if(n>=0 && n<GetDataSetCount())
		{
			dataID=GetDataID(n);
			goto SelectCurveByPoint;
		}
	}
	dataID=GetNeareastDataSet(hDC,point);
SelectCurveByPoint:
	if(dataID>=0)
	{
		SetSelected(dataID,!IsSelected(dataID));
		return dataID;
	}
	else
	{
		SelectAllDataSets(false);
		return -1;
	}
}
/*
bool	CXYPlotImpl::OnMouseDown( HWND hWnd, POINT point )
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

	static int curve_id0=-1;
	bool needUpdate = false;
	
	DPtoLP( hDC, &point,1);
	
	//Set Drag mode
	int curve_id, which = ((CLegendImpl *)GetLegend())->RegionIdentify(hDC,point);
	if(which>=0)
	{
		GetLegend()->SetDragMode(true,point);
		if(which == GetDataSetCount())goto UnselectCurve;//in drag region
		SetSelected(GetDataID(which),!IsSelected(GetDataID(which)));
		curve_id=GetDataID(which);
		goto SelectCurve;
	}
	
	int region;
	region=RegionIdentify(hDC,point);
	switch(region)
	{
	case kXYRegionData:
		curve_id=SelectByPoint(hDC,point);
SelectCurve:
		if(curve_id>=0 && curve_id != curve_id0)
		{
			curve_id0 = curve_id0;
			needUpdate = true;
		}
		else
		{
			goto UnselectCurve;
		}
		break;
	default:
UnselectCurve:
		SelectAllDataSets(false);
		needUpdate = true;
	}
	
//lbuttondown_return:
	ReleaseDC(hWnd,hDC);

	return needUpdate;
}

bool	CXYPlotImpl::OnMouseUp( HWND hWnd, POINT point )
{
	if(GetLegend()->IsDragMode())GetLegend()->SetDragMode(false,point);
	if(GetCapture())ReleaseCapture();
	ClipCursor(NULL);
	//SendMessage(hWnd,WM_PAINT,0,0);

	return false;
}

bool	CXYPlotImpl::OnMouseDblClk( HWND hWnd, POINT point )
{
	if(GetDataSetCount()<=0) return false;
	if( m_pFcnAS==NULL || m_pFcnDS==NULL || m_pFcnPS==NULL ) return false;

	HDC hDC = GetDC( hWnd );

	bool needUpdate = false;

	if(GetDataSetCount()<=0) goto lbuttondblclk_return;

	DPtoLP( hDC, &point,1);

	int which;
	which=((CLegendImpl *)GetLegend())->RegionIdentify(hDC,point);
	if(which>=0)
	{
		if(which == GetDataSetCount())goto lbuttondblclk_return;
		goto CurveProperty;
	}

	int location,region;
	region=RegionIdentify(hDC,point);
	switch(region)
	{
	case kXYRegionData:
		which=GetIndex(GetNeareastDataSet(hDC,point));

CurveProperty:
		if(which>=0)
		{
			if((*m_pFcnDS)(this,hWnd,which))
			{
				needUpdate = true;
			}
		}
		else
		{
			goto PlotProperty;
		}
		break;
	case kXYRegionBottom:
		location=kLocationBottom;
		goto SetAxis;
	case kXYRegionTop:
		location=kLocationTop;
		goto SetAxis;
	case kXYRegionLeft:
		location=kLocationLeft;
		goto SetAxis;
	case kXYRegionRight:
		location=kLocationRight;
SetAxis:
		if((*m_pFcnAS)(this,hWnd,location))
		{
			needUpdate = true;
		}
		break;
	default:

PlotProperty:
		if((*m_pFcnPS)(this,hWnd))
		{
			needUpdate = true;
		}
		break;
	}

	LPtoDP( hDC, &point,1);

lbuttondblclk_return:

	ReleaseDC(hWnd,hDC);

	return needUpdate;
}

bool	CXYPlotImpl::OnMouseMove( HWND hWnd, POINT point )
{
	if(GetDataSetCount()<=0) return false;

	HDC hDC = GetDC( hWnd );

	static int curve_id0=-1;
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

	int which,curve_id;

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
			if(which<GetDataSetCount())
			{
				curve_id=GetDataID(which);
			}
			else//处于Drag区域
			{
				curve_id=-1;
				needUpdate=true;
			}
			GetLegend()->SetCurrent(true);
		}
		else
		{
			curve_id=GetNeareastDataSet(hDC,point);
			if(GetLegend()->IsCurrent())needUpdate=true;//考虑Drag区域
			GetLegend()->SetCurrent(false);
		}

		if(curve_id>=0)
		{
			if(curve_id!=curve_id0)
			{
				SetLighted(curve_id,true);
				needUpdate = true;
			}
		}
		else
		{
			goto SameAsOutRegion;
		}
		curve_id0=curve_id;
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
SameAsOutRegion:
		if(IsLighted())
		{
			UnlightAllDataSets();
			if(curve_id0>=0)
			{
				needUpdate = true;
			}
		}
		curve_id0=-1;
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

bool	CXYPlotImpl::OnContextMenu(HMENU hMenu, HWND hWnd, POINT point  )
{
	if( m_pFcnPM == NULL ) return false;

	//ClientToScreen( hWnd, &point );
	if( (*m_pFcnPM)( this, hMenu, hWnd, point )==kPopupUpdate )
		return true ;
	else
		return false;
}

void CXYPlotImpl::Interactive(HWND hWnd, UINT message, POINT point)
{
	switch(message)
	{
	case WM_LBUTTONDOWN:
		if(OnMouseDown(hWnd,point))OnDraw(hWnd);
		break;
	case WM_LBUTTONUP:
		if(OnMouseUp(hWnd,point))OnDraw(hWnd);
		break;
	case WM_LBUTTONDBLCLK:
		if(OnMouseDblClk(hWnd,point))OnDraw(hWnd);
		break;
	case WM_MOUSEMOVE:
		if(OnMouseMove(hWnd,point))OnDraw(hWnd);
		break;
	case WM_CONTEXTMENU:
		if(OnContextMenu(NULL, hWnd, point))OnDraw(hWnd);
		break;
	case WM_SIZE:
		OnDraw(hWnd);
	case WM_ERASEBKGND:
		return;
	default:
		return;
	}
}

void	CXYPlotImpl::Interactive(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	POINT	point;
	point.x = LOWORD(lParam);
	point.y = HIWORD(lParam);
	Interactive(hWnd, message, point);
}
*/
