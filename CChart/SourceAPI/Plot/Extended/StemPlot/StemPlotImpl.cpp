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
#include "StemPlotImpl.h"
#include "../../Basics/PlotUtility.h"

CStemPlotImpl::CStemPlotImpl()
{
	CAxis *axis;
	axis = AddAxis(kLocationLeft);
	axis = AddAxis(kLocationBottom);
	//axis->SetShowTickLabel(false);
	axis->SetShowMajorTicks(false);
	axis->SetShowMinorTicks(false);
	axis->SetReplaceLabel(true);
	axis->GetAlternateLabels().resize(m_nMaxDataSetLen);
	axis->SetLabelSuffix("ÎåÈÕ");

	m_bUseLegend = true;
	m_pLegend->SetColorRect(true);
	
}

CStemPlotImpl::~CStemPlotImpl()
{

}

int	CStemPlotImpl::AddData(vector<double> vData)
{
	if((int)vData.size() <= 0)
		return -1;
	if(GetDataSetCount() >= m_nMaxDataSets)
		return -1;

	if((int)vData.size() > m_nMaxDataSetLen)
		vData.resize(m_nMaxDataSetLen);

	MyVData2D data;
	DataPoint2D dp;
	for(int i=0; i<(int)vData.size(); i++)
	{
		dp.x = i+1;
		dp.y = vData[i];
		data.push_back(dp);
	}
	return CXYPlot::AddCurve(data);
}

int		CStemPlotImpl::AddData(double *pData, int nLen)
{
	if(nLen<0 || !pData)
		return -1;
	if(GetDataSetCount() >= m_nMaxDataSets)
		return -1;

	vector<double> vData;
	for(int i=0; i<min(nLen, m_nMaxDataSetLen); i++)
	{
		vData.push_back(pData[i]);
	}

	return AddData(vData);
}

void	CStemPlotImpl::SetXLabel(string label, int which)
{
	CAxis *axis = AddAxis(kLocationBottom);
	if(which < 0 || which >= (int)axis->GetAlternateLabels().size() )
		return;
	axis->GetAlternateLabels()[which] = label;
}

void	CStemPlotImpl::GetPlotRange( double *xRange, double *yRange )
{
	CAxis *axis;
	CPlotData<DataPoint2D> *dataSet;
	int i;

	// Set X axis
	m_nMaxSize = 0;
	for(i=0; i<GetDataSetCount(); i++)
	{
		if(GetXYDataInfo()[i].pDataSet->GetDataSize() > m_nMaxSize )
			m_nMaxSize = m_vXYDataInfo[i].pDataSet->GetDataSize();
	}
	xRange[0] = 1.0;
	xRange[1] = m_nMaxSize+1;
	SetXRange(xRange[0], xRange[1]);

	axis = AddAxis(kLocationBottom);
	axis->SetTickCount(m_nMaxSize-1);
	axis->SetMinorTickCount(2);
	axis->GetAlternateLabels().resize(m_nMaxSize);

	//Set Y Axis
	axis = AddAxis(kLocationLeft);
	yRange[0] = 1e30;
	yRange[1] = -1e30;
	for( i = 0; i < GetDataSetCount(); i++ )
	{
		dataSet = GetAbsoluteDataSet( i );
		
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
	double optRange[2];
	int optNTicks, optMinorTicks;
	GetOptimalRange( yRange, optRange, &optNTicks, &optMinorTicks, false );
	axis->SetRange( false, optRange[0], optRange[1] );
	memcpy( yRange, optRange, 2*sizeof( double ) );
	if(axis->IsAutoMajorTick()) axis->SetTickCount( optNTicks );
	if(axis->IsAutoMinorTick()) axis->SetMinorTickCount( optMinorTicks );
}

void	CStemPlotImpl::SetMaxDataSetLen(int len)
{
	if( len>0 )
	{
		m_nMaxDataSetLen = len;
		CAxis *axis = AddAxis(kLocationBottom);
		axis->GetAlternateLabels().resize(m_nMaxDataSetLen);
	}
}

void	CStemPlotImpl::OnDraw( HWND hWnd )
{
	HDC hDC = GetDC(hWnd);
	RECT destRect;
	GetClientRect(hWnd,&destRect);
	
	OnDraw( hDC, destRect );
	
	ReleaseDC(hWnd, hDC);
}

void	CStemPlotImpl::OnDraw(HDC hDC, RECT destRect)
{
	double xRange[2],yRange[2];
	GetPlotRange(xRange,yRange);

	RECT	plotRect = GetPlotRect(hDC, destRect);
	CAxis *axis = AddAxis(kLocationBottom);
	SIZE offset = { long((plotRect.right - plotRect.left)/m_nMaxSize*m_fRatioOccupy/2.0), 0};
	axis->SetLabelOffset(offset);
	
	CXYPlotImpl::OnDraw( hDC, destRect );
}

void	CStemPlotImpl::DrawDataSets( HDC hDC, RECT plotRect, double *xRange, double *yRange )
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

void	CStemPlotImpl::DrawSingleDataSet( int which, HDC hDC, RECT plotRect, double *xRange, double *yRange )
{
	if(!m_vXYDataInfo[which].bDataShow)return;

	int			y;
	double		yScale;
	
	HPEN		hPen, hOldPen;
	HBRUSH		hBrush, hOldBrush;
	
	CPlotData<DataPoint2D>	*dataSet = GetAbsoluteDataSet( which );
	if( dataSet->GetData().size()<=0 ) return;

	COLORREF linecolor = m_vXYDataInfo[which].crPlotColor;
	if( m_vXYDataInfo[which].bLighted || m_vXYDataInfo[which].bSelected )
	{
		linecolor = RGB(255 - GetRValue(linecolor), 255 - GetGValue(linecolor), 255 - GetBValue(linecolor));
	}
	
	hPen = CreatePen( m_vXYDataInfo[which].nPlotLineStyle, m_vXYDataInfo[which].nPlotLineSize, linecolor );
	hOldPen = (HPEN)SelectObject(hDC, hPen );
	hBrush	= CreateSolidBrush( m_vXYDataInfo[which].crPlotColor );
	hOldBrush = (HBRUSH)SelectObject(hDC, hBrush);
	
	// We now have a rect and an xRange and a yRange, just some
	// simple transformations should get us our plot
	yScale = ((double)(plotRect.bottom-plotRect.top))/(yRange[1] - yRange[0]);
	
	double width = plotRect.right - plotRect.left;
	double SegLen = width / m_nMaxSize;
	double step = SegLen*m_fRatioOccupy/GetDataSetCount();
	int	y0 = plotRect.bottom;
	
	BeginPath(hDC);
	MoveToEx(hDC, plotRect.left, plotRect.bottom, NULL);
	for(int i=0; i<GetXYDataInfo()[which].pDataSet->GetDataSize(); i++)
	{
		y = (long)(plotRect.bottom - yScale * (dataSet->GetData()[i].y-yRange[0]));
		LineTo(hDC, int( plotRect.left+SegLen*i+which*step ), y0);
		LineTo(hDC, int( plotRect.left+SegLen*i+which*step ), y);
		LineTo(hDC, int( plotRect.left+SegLen*i+(which+1)*step ), y);
		LineTo(hDC, int( plotRect.left+SegLen*i+(which+1)*step ), y0);
	}
	EndPath(hDC);
	StrokeAndFillPath(hDC);

	SelectObject(hDC, hOldPen);
	SelectObject(hDC, hOldBrush);
	DeleteObject(hPen);
	DeleteObject(hBrush);
}

int		CStemPlotImpl::GetNeareastDataSet( HDC hDC, POINT point )
{
	if(GetDataSetCount()<=0)return -1;

	int			i, nIdx;

	double		xRange[] = {1e30, -1e30}, yRange[]={1e30,-1e30};
	GetPlotRange( xRange, yRange );
	RECT plotRect = GetPlotRect(hDC, GetLastClientRect());

	nIdx = -1;
	for(i=0;i<GetDataSetCount();i++)
	{
		if( PtInDataArea( i, hDC, point, plotRect, xRange, yRange) )
		{
			nIdx = i;
			break;
		}
	}
	if(nIdx==-1)
		return -1;
	else
		return GetDataID(nIdx);
}

bool	CStemPlotImpl::PtInDataArea( int which, HDC hDC, POINT point, RECT plotRect, double *xRange, double *yRange )
{
	if(!m_vXYDataInfo[which].bDataShow)return false;

	int			y;
	double		yScale;

	CPlotData<DataPoint2D>	*dataSet = GetAbsoluteDataSet( which );
	if( dataSet->GetData().size()<=0 ) return false;

	yScale = ((double)(plotRect.bottom-plotRect.top))/(yRange[1] - yRange[0]);

	double width = plotRect.right - plotRect.left;
	double SegLen = width / m_nMaxSize;
	double step = SegLen*m_fRatioOccupy/GetDataSetCount();
	int	y0 = plotRect.bottom;

	for(int i=0; i<GetXYDataInfo()[which].pDataSet->GetDataSize(); i++)
	{
		y = (long)(plotRect.bottom - yScale * (dataSet->GetData()[i].y-yRange[0]));
		RECT rt = { long(plotRect.left+SegLen*i+which*step), y, long(plotRect.left+SegLen*i+(which+1)*step), y0 };
		if( PtInRect(&rt, point) )return true;
	}

	return false;
}