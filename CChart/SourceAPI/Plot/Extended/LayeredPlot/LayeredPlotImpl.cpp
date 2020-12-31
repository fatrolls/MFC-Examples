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
#include "LayeredPlotImpl.h"
#include "LayeredLegendImpl.h"
#include "PlotLayerImpl.h"
#include "../../Basics/PlotUtility.h"

///////////////////////////////////////////////////////////////////////////////////////////////////
//

CLayeredPlotImpl::CLayeredPlotImpl()
{
	if(m_pLegend)
	{
		DeleteLegend();
	}
	m_pLegend = new CLayeredLegendImpl(this);
	CPlot::AddAxis(kLocationBottom);
	CPlot::AddAxis(kLocationLeft);
}

CLayeredPlotImpl::~CLayeredPlotImpl()
{
	ClearLayers();
}

bool	CLayeredPlotImpl::IsEmpty()
{
	if(m_vpLayers.size()<=0)return true;
	for(int i=0;i<(int)m_vpLayers.size();i++)
	{
		if(!((CPlotLayerImpl*)m_vpLayers[i])->IsEmpty())return false;
	}
	return true;
}

bool	CLayeredPlotImpl::NeedDrawing()
{
	if(IsEmpty())return false;
	for(int i=0;i<(int)m_vpLayers.size();i++)
	{
		if(((CPlotLayerImpl*)m_vpLayers[i])->NeedDrawing())return true;
	}
	return false;
}

CAxis*	CLayeredPlotImpl::AddAxis( int nLayerIdx, int location )
{
	if( nLayerIdx<0 || nLayerIdx>=this->GetNumOfLayers() )return NULL;
	return ((CPlotLayerImpl *)m_vpLayers[nLayerIdx])->AddAxis( location );
}

CAxis*	CLayeredPlotImpl::GetAxis( int nLayerIdx, int location )
{
	if( nLayerIdx<0 || nLayerIdx>=this->GetNumOfLayers() )return NULL;
	return ((CPlotLayerImpl *)m_vpLayers[nLayerIdx])->GetAxis( location );
}

int		CLayeredPlotImpl::GetLocalIdx(int which, int &idxOfLayer, int &idxInLayer)
{
	if(which<0 || which>=GetDataSetCount())
	{
		idxOfLayer=-1;
		idxInLayer=-1;
		return -1;
	}
	int count=0,cntOfLayer,dataID;
	for(int i=0;i<GetNumOfLayers();i++)
	{
		cntOfLayer=((CPlotLayerImpl *)m_vpLayers[i])->GetDataSetCount();
		if(count<=which && count+cntOfLayer>which)
		{
			idxOfLayer=i;
			idxInLayer=which-count;
			dataID=((CPlotLayerImpl *)m_vpLayers[idxOfLayer])->GetDataID(idxInLayer);
			return dataID;
		}
		count+=cntOfLayer;
	}
	return -1;
}

int		CLayeredPlotImpl::GetDataSetCount( void )
{
	int count = 0;
	for(int i=0; i<(int)m_vpLayers.size(); i++)
	{
		count+=((CPlotLayerImpl *)m_vpLayers[i])->GetDataSetCount();
	}
	return count;
}

CPlotData<DataPoint2D>	*CLayeredPlotImpl::GetAbsoluteDataSet( int which )
{
	if(which<0 || which>GetDataSetCount())return NULL;
	int count = 0, cnt0=0;
	for(int i=0; i<(int)m_vpLayers.size(); i++)
	{
		count+=((CPlotLayerImpl *)m_vpLayers[i])->GetDataSetCount();
		if(which>=cnt0 && which<count)
		{
			return ((CPlotLayerImpl *)m_vpLayers[i])->GetAbsoluteDataSet(which-cnt0);
		}
		cnt0+=((CPlotLayerImpl *)m_vpLayers[i])->GetDataSetCount();
	}
	return NULL;
}

int		CLayeredPlotImpl::SetNumOfLayers( int num )
{
	ClearLayers();
	if(num > 0)
	{
		m_vpLayers.resize(num);
		for(int i=0; i<(int)m_vpLayers.size(); i++)
		{
			m_vpLayers[i] = new CPlotLayerImpl;
		}
	}
	return m_vpLayers.size();
}

void	CLayeredPlotImpl::GetPlotRange( double xRange[2], double yRange[2] )
{
	xRange[0]=-1.0e30;
	xRange[1]=1.0e30;
	yRange[0]=-1.0e30;
	yRange[1]=1.0e30;
	
	double xrng[2],yrng[2];
	
	int i;
	bool set=false;
	for(i=0;i<(int)m_vpLayers.size();i++)
	{
		if(!((CPlotLayerImpl*)m_vpLayers[i])->NeedDrawing())continue;
		if(!set)
		{
			((CPlotLayerImpl*)m_vpLayers[i])->GetPlotRange( xRange, yRange );
			((CPlotLayerImpl*)m_vpLayers[i])->GetDataRanges( xRange, yRange );
			set=true;
			continue;
		}
		
		((CPlotLayerImpl*)m_vpLayers[i])->GetPlotRange( xrng, yrng );
		((CPlotLayerImpl*)m_vpLayers[i])->GetDataRanges( xrng, yrng );
		if(xrng[0]<xRange[0])xRange[0]=xrng[0];
		if(xrng[1]>xRange[1])xRange[1]=xrng[1];
		if(yrng[0]<yRange[0])yRange[0]=yrng[0];
		if(yrng[1]>yRange[1])yRange[1]=yrng[1];
	}

	int nTicks,nMinorTicks;
	GetOptimalRange(xRange, xrng, &nTicks, &nMinorTicks, true);
	memcpy(xRange, xrng, 2*sizeof(double));
	
	CPlot::SetXRange( xRange[0],xRange[1] );
	SetYRange(yrng[0], yrng[1]);
	CAxis *axis;
	for(i=0;i<(int)m_vpLayers.size();i++)
	{
		if(!((CPlotLayerImpl*)m_vpLayers[i])->NeedDrawing())continue;
		axis=((CPlotLayerImpl *)m_vpLayers[i])->AddAxis(kLocationBottom);
		((CPlotLayerImpl *)m_vpLayers[i])->SetXRange(xRange[0],xRange[1]);
		((CPlotLayerImpl *)m_vpLayers[i])->SetYAutoRange();
		((CPlotLayerImpl *)m_vpLayers[i])->GetPlotRange(xrng,yrng);
	}
}


int		CLayeredPlotImpl::AddCurve(double *pX, double *pY, int nLen, int nLayerIdx)
{
	if(nLayerIdx < 0 || nLayerIdx >= GetNumOfLayers() )return -1;
	int dataID = ((CPlotLayerImpl*)m_vpLayers[nLayerIdx])->AddCurve(pX,pY,nLen);

	double xRange[2],yRange[2];
	GetPlotRange(xRange,yRange);

	return dataID;
}
/*
int		CLayeredPlotImpl::AddLayer(CPlotLayerImpl *layer)
{
	CPlotLayerImpl *tmp = new CPlotLayerImpl;
	*tmp = *layer;
	m_vpLayers.push_back(tmp);

	
	double xRange[2],yRange[2];
	GetPlotRange(xRange,yRange);

	return m_vpLayers.size();
}
*/
int		CLayeredPlotImpl::AddLayer()
{
	CPlotLayerImpl *tmp = new CPlotLayerImpl;
	m_vpLayers.push_back(tmp);	
	return m_vpLayers.size();
}

void	CLayeredPlotImpl::ClearLayers(int nIndex)
{
	if(nIndex < 0 || nIndex >= GetNumOfLayers() )return;
	if(m_vpLayers[nIndex])delete m_vpLayers[nIndex];
	m_vpLayers.erase(m_vpLayers.begin()+nIndex);
}

void	CLayeredPlotImpl::ClearLayers()
{
	for(int i=m_vpLayers.size()-1; i>=0; i--)
	{
		if(m_vpLayers[i])delete m_vpLayers[i];
		m_vpLayers.pop_back();
	}
}

void	CLayeredPlotImpl::DeleteAllData( void )
{
	ClearLayers();
}

SIZE	CLayeredPlotImpl::GetAxisSize( HDC hDC, int location )
{
	SIZE axisSize={0,0};
	SIZE dispSize,paddingSize,maxPaddingSize;
	int i;
	CAxis *axis;
	switch(location)
	{
	case kLocationBottom:
	case kLocationTop:
		axis=GetAxisByLocation(location);
		if(axis)
		{
			dispSize = ((CAxisImpl *)axis)->GetMinDisplaySize( hDC );
			paddingSize = ((CAxisImpl *)axis)->GetPaddingSize( hDC );
			axisSize = dispSize;
			axisSize.cx += (paddingSize.cx+paddingSize.cy);
		}
		break;
	case kLocationLeft:
	case kLocationRight:
		for(i=0;i<GetNumOfLayers();i++)
		{
			if(!m_vpLayers[i]->NeedDrawing())continue;
			SIZE tmp={0,0};
			maxPaddingSize=tmp;
			axis=m_vpLayers[i]->GetAxisByLocation(location);
			if(axis)
			{
				dispSize = ((CAxisImpl *)axis)->GetMinDisplaySize( hDC );
				paddingSize = ((CAxisImpl *)axis)->GetPaddingSize( hDC );
				axisSize.cx += dispSize.cx;
				if( dispSize.cy > axisSize.cy ) axisSize.cy = dispSize.cy;
				if( paddingSize.cx > maxPaddingSize.cx ) maxPaddingSize.cx = paddingSize.cx;
				if( paddingSize.cy > maxPaddingSize.cy ) maxPaddingSize.cy = paddingSize.cy;
			}
		}
		axisSize.cy+=(maxPaddingSize.cx+maxPaddingSize.cy);
		break;
	default:
		break;
	}
	return axisSize;
}

SIZE	CLayeredPlotImpl::GetAxisPaddingSize( HDC hDC, int location )
{
	SIZE paddingSize,maxPaddingSize={0,0};
	int i;
	CAxis *axis;
	switch(location)
	{
	case kLocationBottom:
	case kLocationTop:
		axis=GetAxisByLocation(location);
		if(axis)
		{
			maxPaddingSize = ((CAxisImpl *)axis)->GetPaddingSize( hDC );
		}
		break;
	case kLocationLeft:
	case kLocationRight:
		for(i=0;i<GetNumOfLayers();i++)
		{
			if(!m_vpLayers[i]->NeedDrawing())continue;
			axis=m_vpLayers[i]->GetAxisByLocation(location);
			if(axis)
			{
				paddingSize = ((CAxisImpl *)axis)->GetPaddingSize( hDC );

				if( paddingSize.cx > maxPaddingSize.cx ) maxPaddingSize.cx = paddingSize.cx;
				if( paddingSize.cy > maxPaddingSize.cy ) maxPaddingSize.cy = paddingSize.cy;
			}
		}
		break;
	default:
		break;
	}
	return maxPaddingSize;
}

SIZE	CLayeredPlotImpl::GetTitleSize( HDC hDC )
{
	SIZE size={0,0};
	
	string strTitle=GetTitle();
	if( strTitle != "" )
	{
		HFONT		hOldFont, hFont;
		hFont = CreateFontIndirect(&GetTitleFont());
		hOldFont = (HFONT)SelectObject(hDC, hFont);
		//size = pDC->GetTextExtent( strTitle );
		GetTextExtentPoint( hDC, strTitle.c_str(), strTitle.length(), &size);
		SelectObject( hDC, hOldFont );
		DeleteObject(hFont);
	}
	
	return size;
}

RECT	CLayeredPlotImpl::GetPlotRect( HDC hDC, RECT clientRect)
{
	//////////////////////////////////////////////////////////////
	// Get Plot Rect
	int i;
	
	RECT plotRect=clientRect;
	SIZE sizeRect={0,0},sizeTmp={0,0};
	
	// First title
	sizeRect=GetTitleSize(hDC);
	plotRect.top+=sizeRect.cy;
	
	// then top axis
	sizeRect = GetAxisSize( hDC, kLocationTop);
	plotRect.top+=sizeRect.cy;
	
	// then bottom axis
	sizeRect = GetAxisSize( hDC, kLocationBottom);
	plotRect.bottom-=sizeRect.cy;
	
	// then left axis
	sizeRect.cx = sizeRect.cy = 0;
	for(i=0;i<(int)m_vpLayers.size();i++)
	{
		if(!((CPlotLayerImpl *)m_vpLayers[i])->NeedDrawing())continue;
		sizeTmp=((CPlotLayerImpl *)m_vpLayers[i])->GetAxisSize( hDC, kLocationLeft );
		sizeRect.cx+=sizeTmp.cx;
	}
	plotRect.left+=sizeRect.cx;
	
	// then right axis
	sizeRect.cx = sizeRect.cy = 0;
	for(i=0;i<(int)m_vpLayers.size();i++)
	{
		if(!((CPlotLayerImpl *)m_vpLayers[i])->NeedDrawing())continue;
		sizeTmp=((CPlotLayerImpl *)m_vpLayers[i])->GetAxisSize( hDC, kLocationRight );
		sizeRect.cx+=sizeTmp.cx;
	}
	plotRect.right-=sizeRect.cx;
	
	// Add spacing
	InflateRect( &plotRect, -10, -10 );
	
	return plotRect;
}

RECT	CLayeredPlotImpl::GetTitleRect( HDC hDC, RECT clientRect, RECT chartRect )
{
	RECT	titleRect=clientRect;
	SIZE	tmSize={0,0},axSize={0,0};
	if( GetTitle() != "" )
	{
		HFONT		hOldFont, hFont;
		
		hFont = CreateFontIndirect(&GetTitleFont());
		hOldFont = (HFONT)SelectObject(hDC, hFont);
		GetTextExtentPoint(hDC, GetTitle().c_str(),GetTitle().length(),&tmSize);
		SelectObject( hDC, hOldFont );
		DeleteObject(hFont);
	}
	
	axSize = GetAxisSize( hDC, kLocationTop );
	
	titleRect.bottom=chartRect.top-axSize.cy;
	titleRect.top=titleRect.bottom-tmSize.cy;
	titleRect.left=chartRect.left;
	titleRect.right=chartRect.right;
	
	return titleRect;
}

void	CLayeredPlotImpl::OnDraw( HWND hWnd )
{
	HDC hDC = GetDC(hWnd);
	RECT destRect;
	GetClientRect(hWnd,&destRect);
	
	OnDraw( hDC, destRect );
	
	ReleaseDC(hWnd, hDC);
}

void	CLayeredPlotImpl::OnDraw( HDC hDC, RECT destRect)
{
	//if there is no data, doing nothing
	if(!NeedDrawing())
	{
		EraseBkgnd( hDC, destRect );
		return;
	}

	int i;

	// Get number of left axis and right axis
	CAxis *axis=NULL;

	int numLeft=0,numRight=0;
	for(i=0;i<(int)m_vpLayers.size();i++)
	{
		if(!((CPlotLayerImpl *)m_vpLayers[i])->NeedDrawing())continue;

		axis=((CPlotLayerImpl *)m_vpLayers[i])->GetAxisByLocation(kLocationLeft);
		if(axis)numLeft++;
		axis=((CPlotLayerImpl *)m_vpLayers[i])->GetAxisByLocation(kLocationRight);
		if(axis)numRight++;
	}

	double xRange[2], yRange[2];
	GetPlotRange(xRange,yRange);

	// get plot rect
	RECT plotRect=GetPlotRect(hDC,destRect);

	// Erase the background using parent function
	EraseBkgnd( hDC, destRect );

	// First Draw Frame
	DrawFrame(hDC, plotRect);

	// Draw the grids using the parent function
	DrawGrids( hDC, plotRect );

	// The draw title
	RECT titleRect = GetTitleRect( hDC, destRect, plotRect);
	DrawTitle(hDC, titleRect);

	// then bottom and top axis;
	axis=GetAxisByLocation(kLocationBottom);
	if(axis)
	{
		((CAxisImpl *)axis)->OnDraw(hDC,destRect,plotRect);
	}
	axis=GetAxisByLocation(kLocationTop);
	if(axis)
	{
		((CAxisImpl *)axis)->OnDraw(hDC,destRect,plotRect);
	}
	// then left and right axis;
	SIZE axisSize;
	RECT newRect=plotRect;
	
	for(i=0;i<(int)m_vpLayers.size();i++)
	{
		if(!((CPlotLayerImpl *)m_vpLayers[i])->NeedDrawing())continue;

		axis=((CPlotLayerImpl *)m_vpLayers[i])->GetAxisByLocation(kLocationLeft);
		{
			if(axis)
			{
				((CAxisImpl *)axis)->OnDraw(hDC,destRect,newRect);
				
				axisSize=((CPlotLayerImpl *)m_vpLayers[i])->GetAxisSize( hDC, kLocationLeft );
				newRect.left-=axisSize.cx;
			}
		}
		
		axis=((CPlotLayerImpl *)m_vpLayers[i])->GetAxisByLocation(kLocationRight);
		{
			if(axis)
			{
				((CAxisImpl *)axis)->OnDraw(hDC,destRect,newRect);

				axisSize=((CPlotLayerImpl *)m_vpLayers[i])->GetAxisSize( hDC, kLocationRight );
				newRect.right+=axisSize.cx;
			}
		}
	}

	// Draw Legend
	if(IsUseLegend())m_pLegend->OnDraw(hDC, plotRect);

	// Draw each layer,only draw curve
	for(i=0;i<(int)m_vpLayers.size();i++)
	{
		if(!((CPlotLayerImpl *)m_vpLayers[i])->NeedDrawing())continue;
		((CPlotLayerImpl *)m_vpLayers[i])->OnDraw( hDC, plotRect );
	}

	SetLastClientRect(destRect);
 
}

bool	CLayeredPlotImpl::AxisLighted()
{
	if(CPlot::AxisLighted())return true;
	
	for(int i=0;i<GetNumOfLayers();i++)
	{
		if(((CPlotLayerImpl *)m_vpLayers[i])->AxisLighted())return true;
	}
	
	return false;
}

void	CLayeredPlotImpl::UnlightAllAxis()
{
	CPlot::UnlightAllAxis();
	
	for(int i=0;i<GetNumOfLayers();i++)
	{
		((CPlotLayerImpl *)m_vpLayers[i])->UnlightAllAxis();
	}
	
}

int		CLayeredPlotImpl::RegionIdentify(HDC hDC,POINT point)
{
	//CAxis *pAxis=0;
	RECT theRect;
	
	//data region
	theRect=GetPlotRect(hDC,GetLastClientRect() );
	if( PtInRect(&theRect, point) )
		return kXYRegionData;
	//title region
	theRect=GetTitleRect(hDC,GetLastClientRect() ,GetPlotRect(hDC,GetLastClientRect() ));
	if( PtInRect(&theRect, point) )
		return kXYRegionTitle;
	//top and bottom axis region
	CAxisImpl *axis;
	for(int i=0;i<GetAxisCount();i++)
	{
		axis=(CAxisImpl *)CPlot::GetAxis(i);
		theRect=axis->GetPlotRect(hDC,GetLastClientRect() ,GetPlotRect(hDC,GetLastClientRect() ));
		if( PtInRect(&theRect, point) )
		{
			if(axis->GetLocation()==kLocationBottom)return kXYRegionBottom;
			if(axis->GetLocation()==kLocationTop)return kXYRegionTop;
		}
	}
	
	//left and right axis region
	theRect=GetPlotRect(hDC,GetLastClientRect() );
	SIZE axisSize,padddingSize;
	RECT axisRect;
	
	axisSize = GetAxisSize(hDC,kLocationLeft);
	padddingSize = GetAxisPaddingSize(hDC, kLocationLeft);
	axisRect.right = theRect.left;
	axisRect.left = axisRect.right - axisSize.cx;
	axisRect.top = theRect.top - padddingSize.cx;
	axisRect.bottom = theRect.bottom + padddingSize.cy;
	if( PtInRect(&axisRect, point) )
		return kXYRegionLeft;
	
	axisSize = GetAxisSize(hDC,kLocationRight);
	padddingSize = GetAxisPaddingSize(hDC, kLocationRight);
	axisRect.left = theRect.right;
	axisRect.right = axisRect.left + axisSize.cx;
	axisRect.top = theRect.top - padddingSize.cx;
	axisRect.bottom = theRect.bottom + padddingSize.cy;
	if( PtInRect(&axisRect, point) )
		return kXYRegionRight;
	
	return kXYRegionOut;
}

int		CLayeredPlotImpl::LightByPoint( HDC hDC, POINT point, int &idxOfLayer, int &idxInLayer )
{
	if( RegionIdentify(hDC,point) != kXYRegionData )
	{
		idxOfLayer=-1;
		idxInLayer=-1;
		return -1;
	}
	
	int n=((CLayeredLegendImpl *)GetLegend())->RegionIdentify(hDC,point);
	int dataID;
	if(n>=0)
	{
		dataID=GetLocalIdx(n,idxOfLayer,idxInLayer);
		if(dataID<0)
		{
			return -1;
		}
		goto LightCurveByPoint;
	}
	
	dataID= GetNeareastDataSet( hDC, point, idxOfLayer, idxInLayer );
LightCurveByPoint:
	if(dataID>=0)
	{
		((CPlotLayerImpl *)m_vpLayers[idxOfLayer])->SetLighted(dataID,true);
		return dataID;
	}
	else
	{
		idxOfLayer=-1;
		idxInLayer=-1;
		UnlightAllDataSets();
		return -1;
	}
}

int		CLayeredPlotImpl::SelectByPoint( HDC hDC, POINT point, int &idxOfLayer, int &idxInLayer )
{
	if( RegionIdentify(hDC,point) != kXYRegionData )
	{
		idxOfLayer=-1;
		idxInLayer=-1;
		return -1;
	}
	
	int n=((CLayeredLegendImpl *)GetLegend())->RegionIdentify(hDC,point);
	int dataID;
	if(n>=0)
	{
		dataID=GetLocalIdx(n,idxOfLayer,idxInLayer);
		if(dataID<0)
		{
			return -1;
		}
		goto SelectCurveByPoint;
	}
	
	dataID = GetNeareastDataSet( hDC, point, idxOfLayer, idxInLayer );
	
SelectCurveByPoint:
	if(dataID>=0)
	{
		((CPlotLayerImpl *)m_vpLayers[idxOfLayer])->SetSelected(dataID,!((CPlotLayerImpl *)m_vpLayers[idxOfLayer])->IsSelected(dataID));
		return dataID;
	}
	else
	{
		idxOfLayer=-1;
		idxInLayer=-1;
		SelectAllDataSets(false);
		return -1;
	}
}

int		CLayeredPlotImpl::GetNeareastDataSet( HDC hDC, POINT point, int &idxOfLayer, int &idxInLayer )
{
	int dataID;
	for(int i=0;i<GetNumOfLayers();i++)
	{
		dataID=((CPlotLayerImpl *)m_vpLayers[i])->GetNeareastDataSet(hDC,point);
		if(dataID>=0)
		{
			idxOfLayer=i;
			idxInLayer=((CPlotLayerImpl *)m_vpLayers[idxOfLayer])->GetIndex(dataID);
			if(idxInLayer>=0)return dataID;
		}
	}
	idxOfLayer=-1;
	idxInLayer=-1;
	return -1;
}

RECT	CLayeredPlotImpl::GetLayerAxisRect( int idxOfLayer, int location, HDC hDC, RECT plotRect )
{
	CAxis *axis;
	SIZE axisSize,paddingSize;
	RECT axisRect={0,0,0,0};
	RECT newRect=plotRect;
	
	if(!((CPlotLayerImpl *)m_vpLayers[idxOfLayer])->NeedDrawing())return axisRect;
	if(location==kLocationBottom || location==kLocationTop)return axisRect;
	
	for(int i=0;i<idxOfLayer;i++)
	{
		if(!((CPlotLayerImpl *)m_vpLayers[i])->NeedDrawing())continue;
		
		axis=((CPlotLayerImpl *)m_vpLayers[i])->GetAxisByLocation(kLocationLeft);
		{
			if(axis)
			{
				axisSize=((CPlotLayerImpl *)m_vpLayers[i])->GetAxisSize( hDC, kLocationLeft );
				newRect.left-=axisSize.cx;
			}
		}
		axis=((CPlotLayerImpl *)m_vpLayers[i])->GetAxisByLocation(kLocationRight);
		{
			if(axis)
			{
				axisSize=((CPlotLayerImpl *)m_vpLayers[i])->GetAxisSize( hDC, kLocationRight );
				newRect.right+=axisSize.cx;
			}
		}
	}
	
	axis=((CPlotLayerImpl *)m_vpLayers[idxOfLayer])->GetAxisByLocation(location);
	{
		if(axis)
		{
			axisSize = ((CAxisImpl *)axis)->GetMinDisplaySize( hDC );
			paddingSize = ((CAxisImpl *)axis)->GetPaddingSize( hDC );
			
			axisRect=newRect;
			if(location==kLocationLeft)
			{
				axisRect.right=newRect.left;
				axisRect.left=axisRect.right-axisSize.cx;
			}
			else
			{
				axisRect.left=newRect.right;
				axisRect.right=axisRect.left+axisSize.cx;
			}
			axisRect.bottom+=paddingSize.cy;
			axisRect.top-=paddingSize.cx;
		}
	}
	return axisRect;
}

int		CLayeredPlotImpl::GetIdxOfLayerByPointInAxisRegion(HDC hDC, RECT plotRect, POINT point)
{
	int i,region=RegionIdentify(hDC,point);
	RECT axisRect;
	if( region==kXYRegionLeft )
	{
		for(i=0;i<GetNumOfLayers();i++)
		{
			axisRect=GetLayerAxisRect(i,kLocationLeft,hDC,plotRect);
			if(IsRectEmpty(&axisRect))continue;
			if( PtInRect(&axisRect, point) )
			{
				return i;
			}
		}
	}
	else if( region==kXYRegionRight )
	{
		for(i=0;i<GetNumOfLayers();i++)
		{
			axisRect=GetLayerAxisRect(i,kLocationRight,hDC,plotRect);
			if(IsRectEmpty(&axisRect))continue;
			if( PtInRect(&axisRect, point) )
			{
				return i;
			}
		}
	}
	return -1;
}
