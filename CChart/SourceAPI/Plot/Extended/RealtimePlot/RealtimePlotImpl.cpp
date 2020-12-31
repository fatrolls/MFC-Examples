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
#include "RealtimePlotImpl.h"
#include "../../Basics/PlotUtility.h"
#include <sstream>

CRealtimePlotImpl::CRealtimePlotImpl(HWND hWnd)
{
	// Initialize chart
	CAxis *axis;
	axis = AddAxis(kLocationBottom);
	axis->SetTitle("Time Window");
	axis = AddAxis(kLocationLeft);
	axis->SetTitle("Values");
	if(m_bHoldXValue)
		SetXRange(0.0,m_fTimeSpan);
	else
		SetXAutoRange();
	
	SetUseMajorHGrids(false);
	SetUseMajorVGrids(false);

	this->SetSubtitleShow(true);

	////////////////////////////////
	m_hWnd = hWnd;

	///////////////////////////////
	//Virtual Window
	HDC hDC=GetDC(m_hWnd);
	HBITMAP hMembmp;
	m_maxX=GetSystemMetrics(SM_CXSCREEN);
	m_maxY=GetSystemMetrics(SM_CYSCREEN);
	hMembmp=CreateCompatibleBitmap(hDC,m_maxX,m_maxY);
	m_hMemDC=CreateCompatibleDC(hDC); 
	SelectObject(m_hMemDC,hMembmp); 
	RECT rect; 
	SetRect(&rect,0,0,m_maxX,m_maxY);
	HBRUSH hBrush;
	hBrush = CreateSolidBrush(RGB(255,255,255)); 
	SelectObject(m_hMemDC,hBrush); 
	FillRect(m_hMemDC,&rect,hBrush);
	DeleteObject(hBrush);
	DeleteObject(hMembmp);
	
	ReleaseDC(m_hWnd,hDC);
}

CRealtimePlotImpl::~CRealtimePlotImpl()
{
	//Virtual window
	DeleteDC(m_hMemDC);
}

void CRealtimePlotImpl::OnDraw(HWND hWnd)
{
	//Draw to virtual window
	RECT destRect;
	GetClientRect(m_hWnd, &destRect);
	if (IsEmpty())
	{
		EraseBkgnd(m_hMemDC, destRect);
		return;
	}
	SetLastClientRect(destRect);	
	CXYPlotImpl::OnDraw(m_hMemDC, destRect);

	//blt from virtual window to screen
	HDC hDC = GetDC(m_hWnd);
	StretchBlt(hDC, 0, 0, m_maxX, m_maxY, m_hMemDC, 0, 0, m_maxX, m_maxY, SRCCOPY);
	ReleaseDC(m_hWnd, hDC);
}

void CRealtimePlotImpl::SetNumOfDatas( int num )
{
	if(num<=0)return;
	
	int i,num0 = GetDataSetCount();
	if( num == num0 )return;
	else
	{
		m_vfMax.resize( num );
		m_vfMin.resize( num );
		m_vfValue.resize( num );
		m_vbArrival.resize( num );
		m_vnCounters.resize( num );
		
		if( num <  num0 )
		{
			for( int i=0; i < num0-num; i++ )
			{
				GetAbsoluteDataSet(i)->GetData().pop_back();
			}
		}
		else
		{
			MyVData2D vData;
			vData.resize(1);
			vData[0].x = 0.0;
			vData[0].y = 0.0;
			for( i=num0; i<num; i++)
			{
				AddCurve(vData);
				GetAbsoluteDataSet(i)->GetData().clear();
				
				m_vfMax[i] = 0.0;
				m_vfMin[i] = 0.0;
				m_vfValue[i] = 0.0;
				m_vbArrival[i] = false;
				m_vnCounters[i]=0;
			}
		}
		
	}
	m_nDatas = num;
}

void CRealtimePlotImpl::ResetPlot()
{
	for(int i=0; i<GetNumOfDatas(); i++)
	{
		GetValueMax()[i] = 0.0;
		GetValueMin()[i] = 0.0;
		GetAbsoluteDataSet(i)->GetData().clear();
		GetValue()[i] = 0.0;
		GetArrival()[i] = false;
		GetCounters()[i] = 0;
		
		GetXYDataInfo()[i].fXDataMin=0.0;
		GetXYDataInfo()[i].fXDataMax=0.0;
		GetXYDataInfo()[i].fYDataMin=0.0;
		GetXYDataInfo()[i].fYDataMax=0.0;
	}
}

void CRealtimePlotImpl::OnInsertData()
{
	int nP = (int)ceil(m_fTimeSpan*1000/m_nTimePeriod)+1;
	double fMin,fMax;

	int k;
	for(k=0; k<m_nDatas; k++)
	{
		if(!m_vbArrival[k])break;

		if(m_vfValue[k]>m_vfMax[k])GetXYDataInfo()[k].fYDataMax = m_vfMax[k] = m_vfValue[k];
		if(m_vfValue[k]<m_vfMin[k])GetXYDataInfo()[k].fYDataMin = m_vfMin[k] = m_vfValue[k];
		
		if(k==0)
		{
			fMin=m_vfMin[k];
			fMax=m_vfMax[k];
		}
		else
		{
			if(m_vfMin[k]<fMin)fMin=m_vfMin[k];
			if(m_vfMax[k]>fMax)fMax=m_vfMax[k];
		}
		
		DataPoint2D dp;
		dp.x = m_vnCounters[k]*m_nTimePeriod/1000.0;
		dp.y = m_vfValue[k];
		if( m_vnCounters[k] < nP )
		{
			GetAbsoluteDataSet(k)->GetData().push_back(dp);	
		}
		else
		{
			if( m_bHoldXValue )
			{
				for(int i = 0; i<GetAbsoluteDataSet(0)->GetDataSize()-1;i++)
				{
					GetAbsoluteDataSet(k)->GetData()[i].y = GetAbsoluteDataSet(k)->GetData()[i+1].y;
				}
				GetAbsoluteDataSet(k)->GetData()[GetAbsoluteDataSet(k)->GetData().size()-1].y = m_vfValue[k];
			}
			else
			{
				GetAbsoluteDataSet(k)->GetData().erase(GetAbsoluteDataSet(k)->GetData().begin());
				GetAbsoluteDataSet(k)->GetData().push_back(dp);	
			}
			
		}
		m_vbArrival[k] = false;
		m_vnCounters[k]++;
	}
	
	double t1,t2;
	t2=GetMaxCounter()*m_nTimePeriod/1000.0;
	t1=t2-m_fTimeSpan;
	if(t1<0.0)t1=0.0;

	ostringstream ostr;
	ostr<<t1<<" s ---- "<<t2<<" s";
	SetSubtitle(ostr.str());
	
	double inRange[2],outRange[2];
	inRange[0] = fMin;
	inRange[1] = fMax;
	int nTicks,nMinorTicks;
	GetOptimalRange(inRange, outRange, &nTicks, &nMinorTicks, false);
	SetYRange(outRange[0],outRange[1]);
	CAxis *axis = AddAxis(kLocationLeft);
	axis->SetTickCount(nTicks);
	axis->SetMinorTickCount(nMinorTicks);

	for(k=0; k<m_nDatas; k++)
	{
		GetXYDataInfo()[k].fXDataMax = t2;
		GetXYDataInfo()[k].fXDataMin = t1;
	}
	
	OnDraw(m_hWnd);
}
