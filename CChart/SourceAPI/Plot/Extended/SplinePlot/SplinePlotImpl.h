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

#ifndef __SPLINEPLOTIMPL_32167_H__
#define __SPLINEPLOTIMPL_32167_H__

#include "../../Basics/XYPlotImpl.h"
#include "../../Basics/XYHandler.h"
#include "SplinePlot.h"
#include "Spline.h"

class CSplinePlotImpl : public CSplinePlot, public CXYPlotImpl
{
public:
	CSplinePlotImpl();
	virtual ~CSplinePlotImpl();

	int AddSplineByNum(MyVData2D vData, int nSplineMode = kSplModeParabolic,
		COLORREF color = RGB(255, 0, 0), int nSegments = 20, int nOrder = 2,
		int nEdgeMode = kSplEdgeModeFree); 
	int AddSplineByStep(MyVData2D vData, int nSplineMode = kSplModeParabolic,
		COLORREF color = RGB(255, 0, 0), double fMaxStep = 1.0,
		int nOrder = 2, int nEdgeMode = kSplEdgeModeFree); 

	int AddSpline(MyVData2D vData)
	{
		return AddSplineByNum(vData);
	}
};

class CSplinePlotImplI : public CSplinePlotImpl, public CXYHandler<CSplinePlotImplI>
{

};

#endif