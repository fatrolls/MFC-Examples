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
#include "TDLinePlotImpl.h"
#include "../TDPlot/AxisTDImpl.h"
#include "../../Basics/PlotUtility.h"

CTDLinePlotImpl::CTDLinePlotImpl(HWND hWnd) : CTDPlotImpl(hWnd)
{
}

CTDLinePlotImpl::~CTDLinePlotImpl()
{
}

void	CTDLinePlotImpl::GetPlotRange( double *xRange, double *yRange, double *zRange )
{
	GetDataRanges(xRange, yRange, zRange);
	
	double *pRange;
	double optRange[2];
	int	optNTicks, optMinorTicks;
	for(int i=0; i<3; i++)
	{
		if(i==0)pRange = xRange;
		else if(i==1)pRange = yRange;
		else pRange = zRange;
		
		if(pRange[0]==pRange[1])
		{
			if(pRange[0]==0.0)
			{
				pRange[0]-=0.5;
				pRange[1]+=0.5;
			}
			else
			{
				pRange[0]-=pow(10,floor(log10(fabs(pRange[0]))));;
				pRange[1]+=pow(10,floor(log10(fabs(pRange[0]))));;
			}
		}
		GetOptimalRange( pRange, optRange, &optNTicks, &optMinorTicks, false );
		memcpy(pRange, optRange, 2*sizeof(double));
		m_pAxes[i]->SetRange(pRange[0],pRange[1]);
		m_pAxes[i]->SetTickCount(optNTicks);
		m_pAxes[i]->SetMinorTickCount(optMinorTicks);
	}
}

void	CTDLinePlotImpl::OnDraw( HWND hWnd )
{
	HDC hDC = GetDC(hWnd);
	RECT destRect;
	GetClientRect(hWnd,&destRect);
	
	OnDraw( hDC, destRect );
	
	ReleaseDC(hWnd, hDC);
}

void	CTDLinePlotImpl::OnDraw(HDC hDC, RECT destRect)
{
	if(m_vXYZDataInfo.size() <= 0)
	{
		glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		return;
	}

	double xRange[2], yRange[2], zRange[2];
	GetPlotRange(xRange, yRange, zRange);

	glPushMatrix();
	wglMakeCurrent( hDC, m_hGLRC);
	CTDPlotImpl::OnDraw( hDC, destRect );
	SetPlotColors();
	DrawDataSets(xRange, yRange, zRange);
	glFlush();
	wglMakeCurrent(	hDC, NULL);
	SwapBuffers( hDC );
	glPopMatrix();
	m_rctLastClientRect = destRect;
}

void	CTDLinePlotImpl::DrawDataSets( double *xRange, double *yRange, double *zRange )
{
	for(int i=0; i<m_vXYZDataInfo.size(); i++)
	{
		DrawSingleDataSet(i, xRange, yRange, zRange);
	}
}

void		CTDLinePlotImpl::DrawSingleDataSet( int which, double *xRange, double *yRange, double *zRange )
{
	if(which<0 || which >= m_vXYZDataInfo.size() )return;
	CPlotData<DataPoint3D> *pDataSet = m_vXYZDataInfo[which].pDataSet;
	if(pDataSet->GetData().size()<=0)return;

	double xScale, yScale, zScale;
	double x, y, z;
	DataPoint3D dp;
	xScale = m_fLenX/(xRange[1] - xRange[0]);
	yScale = m_fLenY/(yRange[1] - yRange[0]);
	zScale = m_fLenY/(zRange[1] - zRange[0]);

	GLfloat *CtrlPoints;
	int NumOfCP;

	glColor3fv(m_vXYZDataInfo[which].fvPlotColor);
	
	int plottype = m_vXYZDataInfo[which].nPlotType;
	if(plottype == kTDPlotBezier && pDataSet->GetData().size()<4)
		plottype = kTDPlotConnected;

	int i,j;
	switch(plottype)
	{
	case kTDPlotScatter:
		glPointSize(m_vXYZDataInfo[which].nMarkerSize);
		glBegin(GL_POINTS);
		for(i=0; i<pDataSet->GetData().size(); i++)
		{
			dp = pDataSet->GetData()[i];
			x = xScale * ( dp.x - xRange[0] );
			y = yScale * ( dp.y - yRange[0] );
			z = zScale * ( dp.z - zRange[0] );
			
			glVertex3f(x, y, z);
		}
		glEnd();
		break;
	case kTDPlotConnected:
		glBegin(GL_LINE_STRIP);
		for(i=0; i<pDataSet->GetData().size(); i++)
		{
			dp = pDataSet->GetData()[i];
			x = xScale * ( dp.x - xRange[0] );
			y = yScale * ( dp.y - yRange[0] );
			z = zScale * ( dp.z - zRange[0] );
			
			glVertex3f(x, y, z);
		}
		glEnd();
		break;
	case kTDPlotBezier:
		if(pDataSet->GetData().size() <= 32)
			NumOfCP = pDataSet->GetData().size();
		else
			NumOfCP = 32;
		CtrlPoints = new GLfloat[3*NumOfCP];
		for(i=0; i<NumOfCP; i++)
		{
			if(pDataSet->GetData().size() <= 32)
			{
				j=i;
			}
			else
			{
				j=i*(pDataSet->GetData().size()-1.0f)/GLfloat(NumOfCP-1.0f);
			}
			dp = pDataSet->GetData()[j];
			x = xScale * ( dp.x - xRange[0] );
			y = yScale * ( dp.y - yRange[0] );
			z = zScale * ( dp.z - zRange[0] );
			
			CtrlPoints[3*i+0] = x;
			CtrlPoints[3*i+1] = y;
			CtrlPoints[3*i+2] = z;
		}

		glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, NumOfCP, CtrlPoints);
		glEnable(GL_MAP1_VERTEX_3);
		glShadeModel(GL_FLAT);
		
		glBegin(GL_LINE_STRIP);
		for(i=0; i<=m_nNurbsPoints; i++)
		{
			glEvalCoord1f((GLfloat)i/(GLfloat)m_nNurbsPoints);
			//glVertex3f(CtrlPoints[3*i+0], CtrlPoints[3*i+1], CtrlPoints[3*i+2]);
		}
		glEnd();

		glDisable(GL_MAP1_VERTEX_3);

		delete []CtrlPoints;
		
		break;
	default:
		break;
	}

	if(m_vXYZDataInfo[which].bMarkerShow)
		DrawMarkers(which, xRange, yRange, zRange);
}

void	CTDLinePlotImpl::DrawMarkers( int which, double *xRange, double *yRange, double *zRange )
{
	if(which<0 || which >= m_vXYZDataInfo.size() )return;
	CPlotData<DataPoint3D> *pDataSet = m_vXYZDataInfo[which].pDataSet;
	
	double xScale, yScale, zScale;
	double x, y, z;
	DataPoint3D dp;
	xScale = m_fLenX/(xRange[1] - xRange[0]);
	yScale = m_fLenY/(yRange[1] - yRange[0]);
	zScale = m_fLenY/(zRange[1] - zRange[0]);

	glColor3fv(m_vXYZDataInfo[which].fvPlotColor);

	glPointSize(m_vXYZDataInfo[which].nMarkerSize);
	glBegin(GL_POINTS);
	for(int i=0; i<pDataSet->GetData().size(); i++)
	{
		dp = pDataSet->GetData()[i];
		x = xScale * ( dp.x - xRange[0] );
		y = yScale * ( dp.y - yRange[0] );
		z = zScale * ( dp.z - zRange[0] );
		
		glVertex3f(x, y, z);
	}
	glEnd();
}

