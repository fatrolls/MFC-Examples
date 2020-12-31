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

#ifndef __XYPLOTIMPL_H_122333444455555__
#define __XYPLOTIMPL_H_122333444455555__

#include "XYPlot.h"
#include "PlotImpl.h"
#include "LegendImpl.h"
#include "XYHandler.h"

// class CPlot is a basement class
class CXYPlotImpl : public CXYPlot , public CPlotImpl
{
public:
	CXYPlotImpl();
	virtual ~CXYPlotImpl();

public:
	virtual	void		OnDraw( HWND hWnd );
	virtual	void		OnDraw(HDC hDC, RECT destRect);

public:
	int					LightByPoint( HDC hDC, POINT point );
	int					SelectByPoint( HDC hDC, POINT point );
	
	virtual	int			GetNeareastDataSet( HDC hDC, POINT point );
	int					GetNeareastDataPoint( int dataID, HDC hDC, POINT point, double data[2]);
	// Utilize current point to light a data set
	void				DrawSolelyMarker( HDC hDC, POINT point, int whichDataSet ){ DrawSingleMarker( hDC, point, whichDataSet, 0 );}

	virtual	void		GetPlotRange( double *xRange, double *yRange );

	virtual	bool		IsEmpty(){return m_vXYDataInfo.size()<=0;}

protected:

	virtual	void		DrawDataSets( HDC hDC, RECT plotRect, double *xRange, double *yRange );
	void				DrawSingleDataSet( int which, HDC hDC, RECT plotRect, double *xRange, double *yRange );
	void				DrawMarkers(int whichDataSet, HDC hDC, RECT plotRect, double *xRange, double *yRange);
	void				DrawSingleMarker( HDC hDC, POINT point, int whichDataSet, int dataPointNumber );
	void				DrawDataSetInfo( int which, HDC hDC, RECT plotRect, double *xRange, double *yRange );

	void				ApproachNearestIdx(int curIdx,int &nIdx,double *data,int lo,int up,double dlM,double &dl0);

	CLegend				*NewLegend(){CLegendImpl *pLegend = new CLegendImpl(this); return pLegend;}
};

class CXYPlotImplI : public CXYPlotImpl, public CXYHandler<CXYPlotImplI>
{
};

#endif