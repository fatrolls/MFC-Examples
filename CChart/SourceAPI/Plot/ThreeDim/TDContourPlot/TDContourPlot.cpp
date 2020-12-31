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
#include "TDContourPlot.h"
#include "../../Basics/XYPlot.h"
#include "../../Basics/PlotUtility.h"
#include "../TDPlot/TDPlot.h"
#include "../../Accessary/Numerical/Optimize/Optimize.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
extern double TestFunction(double x, double y);

CTDContourPlot *pThis;
/*
void CTDContourPlot::f4min(int *n, double x[2], double *y)
{
	*y = pThis->m_pFieldFcn(x[0], x[1]);
}

void CTDContourPlot::f4max(int *n, double x[2], double *y)
{
	*y = -pThis->m_pFieldFcn(x[0], x[1]);
}
*/

void CTDContourPlot::f4min(double x[2], double &y)
{
	y = pThis->m_pFieldFcn(x[0], x[1]);
}

void CTDContourPlot::f4max(double x[2], double &y)
{
	y = -pThis->m_pFieldFcn(x[0], x[1]);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
CTDContourPlot::CTDContourPlot()
{
	pThis = this;
	SetDefaults();
}

CTDContourPlot::~CTDContourPlot()
{
}

void	CTDContourPlot::SetDefaults()
{
	m_fvColor1[0] = 1.0f;
	m_fvColor1[1] = 0.0f;
	m_fvColor1[2] = 0.0f;
	m_fvColor2[0] = 0.0f;
	m_fvColor2[1] = 1.0f;
	m_fvColor2[2] = 1.0f;

	m_pFieldFcn = TestFunction;

	m_fXRange[0] = m_fYRange[0] = m_fZRange[0] = -5.0;
	m_fXRange[1] = m_fYRange[1] = m_fZRange[1] = 5.0;
	GetZRange();

	m_nXSteps = m_nYSteps = 32;
	m_nXMapSteps = m_nYMapSteps = 20;

	m_bExponential = false;
	m_bLighting = true;
}


void	CTDContourPlot::CopySettings(CTDContourPlot *plot)
{

}

void	CTDContourPlot::GetDataRanges(double xRange[2], double yRange[2], double zRange[2])
{
	memcpy(xRange, m_fXRange, 2*sizeof(double));
	memcpy(yRange, m_fYRange, 2*sizeof(double));
	GetZRange();
	memcpy(zRange, m_fZRange, 2*sizeof(double));
}

void	CTDContourPlot::SetPlotRange(double pRange[4])
{
	m_fXRange[0] = pRange[0];
	m_fXRange[1] = pRange[1];
	m_fYRange[0] = pRange[2];
	m_fYRange[1] = pRange[3];
	GetZRange();
}

void	CTDContourPlot::GetZRange()
{
	//int iflag;
	double x[2],xlb[2],xub[2];
	xlb[0] = m_fXRange[0];
	xlb[1] = m_fYRange[0];
	xub[0] = m_fXRange[1];
	xub[1] = m_fYRange[1];
	//BoundedPowell(f4min,2,x,xlb,xub,1.0,1e-4,10000,iflag);
	//m_fZRange[0] = m_pFieldFcn(x[0],x[1]);
	FindMin2D(f4min,xlb,xub,x,m_fZRange[0]);
	//BoundedPowell(f4max,2,x,xlb,xub,1.0,1e-4,10000,iflag);
	//m_fZRange[1] = m_pFieldFcn(x[0],x[1]);
	FindMin2D(f4max,xlb,xub,x,m_fZRange[1]);
}
