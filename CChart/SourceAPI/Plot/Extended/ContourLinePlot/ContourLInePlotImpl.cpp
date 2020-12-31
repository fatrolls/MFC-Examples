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

#include "ContourLInePlotImpl.h"
#include "../../Basics/PlotData.h"
#include "ListContour.h"
#include <sstream>

CContourLinePlotImpl::CContourLinePlotImpl()
{
	SetUseMajorHGrids(false);
	SetUseMajorVGrids(false);
	m_pListContour = new CListContour;
}

CContourLinePlotImpl::~CContourLinePlotImpl()
{
	if(m_pListContour)delete m_pListContour;
}

void CContourLinePlotImpl::SetDataInfoDraw(bool bDraw)
{
	for(int i=0;i<GetDataSetCount();i++)
	{
		GetDataSet(GetDataID(i))->SetInfoDraw(bDraw);
	}
}

int CContourLinePlotImpl::GetDataSetLevels()
{
	return m_pListContour->GetNPlanes();
}

bool CContourLinePlotImpl::CreateContour()
{
	m_pListContour->Generate();

	// draw line strips
	CLineStripList* pStripList;
	CLineStrip* pStrip;
	UINT i,index;
	CLineStripList::iterator pos;
	CLineStrip::iterator pos2;
	//double pLimits[4];
	double x,y;
	MyVData2D vData;
	DataPoint2D datapoint;
	int nPt,cPt;

	ostringstream ostr;

	int dataID;
	string info,name;
	int count=0;

	DeleteAllData();

	//m_pListContour->GetLimits(pLimits);
	AddAxis(kLocationBottom);
	AddAxis(kLocationLeft);
	for (i=0;i<m_pListContour->GetNPlanes();i++)
	{
		pStripList=m_pListContour->GetLines(i);
		//ASSERT(pStripList);
		info="";
		
		for (pos=pStripList->begin(); pos != pStripList->end() ; pos++)
		{
			pStrip=(*pos);
			//ASSERT(pStrip);
			if (pStrip->empty())
				continue;
			nPt=pStrip->size();
			vData.clear();

			cPt=0;
			for (pos2=pStrip->begin(); pos2 != pStrip->end() ; pos2++)
			{
				// retreiving index
				index=(*pos2);
				// drawing
				x=m_pListContour->GetXi(index);
				y=m_pListContour->GetYi(index);
				datapoint.x=x;
				datapoint.y=y;
				cPt++;
				vData.push_back(datapoint);
			}
			dataID=AddCurve(vData);
			if(info=="")
			{
				ostr.str("");
				ostr<<m_pListContour->GetValue(x,y);
				info = ostr.str();
				//info.Format("%g",m_pListContour->GetValue(x,y));
			}
			GetDataSet(dataID)->SetInfo(info);
			GetDataSet(dataID)->SetDataLevel(i);
			SetAutoColor(dataID,true);
			count++;
			ostr.str("");
			ostr<<"Contour line "<<count;
			name = ostr.str();
			SetDataTitle(dataID,name);
			SetPlotType(dataID,kXYPlotConnect);
		}
	}
	SetAutoDataColor(true);
	//SetMaskOfSetColor(RGB(0,0,0));
	SetModeOfSetColors(kSetColorFromTwoColor);
	SetLineColor1(RGB(0,0,0));
	SetLineColor2(RGB(255,0,0));
	double limits[4];
	m_pListContour->GetLimits(limits);
	SetXRange(limits[0],limits[1]);
	SetYRange(limits[2],limits[3]);

	return true;
}

bool CContourLinePlotImpl::CreateContour(int nPlanes)
{
	return CreateContour(nPlanes,false);
}

bool CContourLinePlotImpl::CreateContour(int nPlanes,bool bExponential)
{
	m_pListContour->SetPlanes(nPlanes,bExponential);
	return CreateContour();
}