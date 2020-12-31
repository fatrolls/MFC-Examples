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
#include "SplinePlotImpl.h"
#include <sstream>

CSplinePlotImpl::CSplinePlotImpl()
{
}

CSplinePlotImpl::~CSplinePlotImpl()
{
}

int CSplinePlotImpl::AddSplineByNum(MyVData2D vData, int nSplineMode,
	COLORREF color, int nSegments, int nOrder, int nEdgeMode)
{
	if (nOrder <= 1 || nSegments <= 1)
		return -1;

	CSpline spline;
	MyVData2D vSplData;
	DataPoint2D datapoint;
	ostringstream ostr;
	string name;

	int i, j;
	double max, min;

	ClearAdjoinCoincide(vData);

	int dataID;

	spline.SetSegments(nSegments);
	spline.SetEdgeMode(nEdgeMode);
	switch (nSplineMode)
	{
	case kSplModeParabolic:
		for (i = 0; i < (int)vData.size() - 1; i++)
		{
			for (int j = 0; j < spline.GetSegments(); j++)
			{
				if (!spline.GetParSplineValue(datapoint, vData, i, j))
					continue;
				vSplData.push_back(datapoint);
			}
			if (i == vData.size() - 2)
			{
				if (!spline.GetParSplineValue(datapoint, vData, i,
								spline.GetSegments()))
					continue;
				vSplData.push_back(datapoint);
			}
		}
		dataID = AddCurve(vSplData);
		name = "parabolic spline";
		SetDataTitle(dataID, name);
		SetDataColor(dataID, color);
		return dataID;
	case kSplModeCubic:
		for (i = 0; i <= (int)vData.size() - 2; i++)
		{
			for (j = 0; j < spline.GetSegments(); j++)
			{
				if (!spline.GetCubicSplineValue(datapoint, vData, i, j))
					continue;
				vSplData.push_back(datapoint);
			}
			if (i == vData.size() - 2)
			{
				if (!spline.GetCubicSplineValue(datapoint, vData, i,
								spline.GetSegments()))
					continue;
				vSplData.push_back(datapoint);
			}
		}
		dataID = AddCurve(vSplData);
		name = "cubic spline";
		SetDataTitle(dataID, name);
		SetDataColor(dataID, color);

		return dataID;
	case kSplModeBezier:
		for (i = 0; i <= spline.GetSegments(); i++)
		{
			if (!spline.GetBezierSplineValue(datapoint, vData, i))
				continue;
			vSplData.push_back(datapoint);
		}
		dataID = AddCurve(vSplData);
		name = "bezier spline";
		SetDataTitle(dataID, name);
		SetDataColor(dataID, color);
		return dataID;
	case kSplModeB:
		for (i = 0; i <= (int)vData.size() - nOrder; i++)
		{
			for (j = 0; j < spline.GetSegments(); j++)
			{
				if (!spline.GetBSplineValue(datapoint, vData, i, nOrder, j))
					continue;
				vSplData.push_back(datapoint);
			}
			if (i == vData.size() - nOrder)
			{
				if (!spline.GetBSplineValue(datapoint, vData, i, nOrder,
								spline.GetSegments()))
					continue;
				vSplData.push_back(datapoint);
			}
		}
		dataID = AddCurve(vSplData);
		ostr<<nOrder<<" order B-Spline";
		name=ostr.str();
		SetDataTitle(dataID, name);
		SetDataColor(dataID, color);
		return dataID;
	case kSplModeLeastSquare:
		min = vData[0].x;
		max = vData[0].x;
		for (i = 1; i < (int)vData.size(); i++)
		{
			if (vData[i].x < min)
				min = vData[i].x;
			if (vData[i].x > max)
				max = vData[i].x;
		}
		for (i = 0; i <= spline.GetSegments(); i++)
		{
			datapoint.x = min + i * (max - min) / (spline.GetSegments() - 1);
			spline.GetLeastSqualValue(datapoint, vData, nOrder);
			vSplData.push_back(datapoint);
		}
		dataID = AddCurve(vSplData);
		ostr<<nOrder<<" order least square";
		name=ostr.str();
		SetDataTitle(dataID, name);
		SetDataColor(dataID, color);
		return dataID;

	default:
		return -1;
	}
}

int CSplinePlotImpl::AddSplineByStep(MyVData2D vData, int nSplineMode,
	COLORREF color, double fMaxStep, int nOrder, int nEdgeMode)
{
	if (nOrder <= 1 || fMaxStep < 0.0)
		return -1;

	CSpline spline;
	MyVData2D vSplData;
	DataPoint2D datapoint, datapoint1;
	
	ostringstream ostr;
	string name;

	int i, j;
	double max, min;
	double xlength;

	ClearAdjoinCoincide(vData);

	int dataID;

	int nSeg;

	//spline.SetSegments(nSegments);
	spline.SetEdgeMode(nEdgeMode);
	switch (nSplineMode)
	{
	case kSplModeParabolic:
		for (i = 0; i < (int)vData.size() - 1; i++)
		{
			nSeg = (int) ceil(fabs((vData[i + 1].x - vData[i].x) / fMaxStep));
			if (nSeg <= 0)
				nSeg = 1;
			spline.SetSegments(nSeg);

			for (int j = 0; j < spline.GetSegments(); j++)
			{
				if (!spline.GetParSplineValue(datapoint, vData, i, j))
					continue;
				vSplData.push_back(datapoint);
			}
			if (i == vData.size() - 2)
			{
				if (!spline.GetParSplineValue(datapoint, vData, i,
								spline.GetSegments()))
					continue;
				vSplData.push_back(datapoint);
			}
		}
		dataID = AddCurve(vSplData);
		name = "parabolic spline";
		SetDataTitle(dataID, name);
		SetDataColor(dataID, color);
		return dataID;
	case kSplModeCubic:
		for (i = 0; i <= (int)vData.size() - 2; i++)
		{
			nSeg = (int) ceil(fabs((vData[i + 1].x - vData[i].x) / fMaxStep));
			if (nSeg <= 0)
				nSeg = 1;
			spline.SetSegments(nSeg);
			for (j = 0; j < spline.GetSegments(); j++)
			{
				if (!spline.GetCubicSplineValue(datapoint, vData, i, j))
					continue;
				vSplData.push_back(datapoint);
			}
			if (i == vData.size() - 2)
			{
				if (!spline.GetCubicSplineValue(datapoint, vData, i,
								spline.GetSegments()))
					continue;
				vSplData.push_back(datapoint);
			}
		}
		dataID = AddCurve(vSplData);
		name = "cubic spline";
		SetDataTitle(dataID, name);
		SetDataColor(dataID, color);

		return dataID;
	case kSplModeBezier:
		xlength = spline.GetXLength(vData);
		nSeg = (int) ceil(xlength / fMaxStep);
		if (nSeg <= 0)
			nSeg = 1;
		spline.SetSegments(nSeg);

		for (i = 0; i <= spline.GetSegments(); i++)
		{
			if (!spline.GetBezierSplineValue(datapoint, vData, i))
				continue;
			vSplData.push_back(datapoint);
		}
		dataID = AddCurve(vSplData);
		name = "bezier spline";
		SetDataTitle(dataID, name);
		SetDataColor(dataID, color);
		return dataID;
	case kSplModeB:
		for (i = 0; i <= (int)vData.size() - nOrder; i++)
		{
			//xlength=spline.GetCentroid(vData,i+1,nOrder).x-spline.GetCentroid(vData,i,nOrder).x;
			datapoint = spline.GetBSplCtrlPoint(vData, i, nOrder, true);
			datapoint1 = spline.GetBSplCtrlPoint(vData, i, nOrder, false);
			xlength = datapoint1.x - datapoint.x;

			nSeg = (int) ceil(fabs(xlength / fMaxStep));
			if (nSeg <= 0)
				nSeg = 1;
			spline.SetSegments(nSeg);

			for (j = 0; j < spline.GetSegments(); j++)
			{
				if (!spline.GetBSplineValue(datapoint, vData, i, nOrder, j))
					continue;
				vSplData.push_back(datapoint);
			}
			if (i == vData.size() - nOrder)
			{
				if (!spline.GetBSplineValue(datapoint, vData, i, nOrder,
								spline.GetSegments()))
					continue;
				vSplData.push_back(datapoint);
			}
		}
		dataID = AddCurve(vSplData);
		ostr<<nOrder<<" order B-Spline";
		name=ostr.str();
		SetDataTitle(dataID, name);
		SetDataColor(dataID, color);
		return dataID;
	case kSplModeLeastSquare:
		min = vData[0].x;
		max = vData[0].x;
		for (i = 1; i < (int)vData.size(); i++)
		{
			if (vData[i].x < min)
				min = vData[i].x;
			if (vData[i].x > max)
				max = vData[i].x;
		}
		nSeg = (int) ceil(fabs((max - min) / fMaxStep));
		if (nSeg <= 0)
			nSeg = 1;
		spline.SetSegments(nSeg);

		for (i = 0; i <= spline.GetSegments(); i++)
		{
			datapoint.x = min + i * (max - min) / (spline.GetSegments() - 1);
			spline.GetLeastSqualValue(datapoint, vData, nOrder);
			vSplData.push_back(datapoint);
		}
		dataID = AddCurve(vSplData);
		ostr<<nOrder<<"order least square";
		name=ostr.str();
		SetDataTitle(dataID, name);
		SetDataColor(dataID, color);
		return dataID;

	default:
		return -1;
	}
}