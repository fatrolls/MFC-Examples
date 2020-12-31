/*============================================================================*/
/*                                                                            */
/*                            C O P Y R I G H T                               */
/*                                                                            */
/*                          (C) Copyright 2012 by                             */
/*                              Yang Guojun                                   */
/*                           All Rights Reserved                              */
/*                                                                            */
/*      The author assumes no responsibility for the use or reliability of    */
/*      his software.                                                         */
/*                                                                            */
/*============================================================================*/

/* ############################################################################################################################## */
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//

#ifndef __PLOTREDIFINITIONS_H_122333444455555__
#define __PLOTREDIFINITIONS_H_122333444455555__

typedef	CPlotImpl Chart;

typedef CXYPlotImpl XYChart;
typedef CXYPlotImplI XYChartI;
Declare_CDblBufferPlotImplI( XYChartID1, CXYPlotImpl, CXYHandler )
typedef	XYChartID1<CXYPlotImpl> XYChartID;

typedef CSplitPlotImpl<CXYPlotImpl> SplitChart;
typedef CSplitPlotImplI<CXYPlotImpl> SplitChartI;
Declare_CDblBufferPlotImplI( SplitChartID1, CSplitPlotImpl, CSplitHandler )
typedef SplitChartID1< CSplitPlotImpl<CXYPlotImpl> > SplitChartID;

typedef CLayeredPlotImpl LayeredChart;
typedef CLayeredPlotImplI LayeredChartI;
Declare_CDblBufferPlotImplI( LayeredChartID1, CLayeredPlotImpl, CLayeredHandler )
typedef LayeredChartID1<CLayeredPlotImpl> LayeredChartID;

typedef CImagePlotImpl	ImgChart;
typedef CImagePlotImplI ImgChartI;
Declare_CDblBufferPlotImplI( ImgChartID1, CImagePlotImpl, CImageHandler )
typedef ImgChartID1<CImagePlotImpl> ImgChartID;

typedef CContourLinePlotImpl	ContourLineChart;
typedef CContourLinePlotImplI	ContourLineChartI;
Declare_CDblBufferPlotImplI( ContourLineChartID1, CContourLinePlotImpl, CXYHandler )
typedef ContourLineChartID1<CContourLinePlotImpl> ContourLineChartID;

typedef	CSplinePlotImpl	SplineChart;
typedef	CSplinePlotImplI	SplineChartI;
Declare_CDblBufferPlotImplI( SplineChartID1, CSplinePlotImpl, CXYHandler )
typedef SplineChartID1<CSplinePlotImpl> SplineChartID;

typedef CBendingPlotImpl BendChart;
typedef CBendingPlotImplI BendChartI;
Declare_CDblBufferPlotImplI( BendChartID1, CBendingPlotImpl, CXYHandler )
typedef BendChartID1<CBendingPlotImpl> BendChartID;

typedef CObjectPlotImpl ObjChart;
typedef CObjectPlotImplI ObjChartI;
Declare_CDblBufferPlotImplI( ObjChartID1, CObjectPlotImpl, CObjectHandler )
typedef ObjChartID1<CObjectPlotImpl> ObjChartID;

typedef COscilloPlotImpl OscilloChart;
typedef COscilloPlotImplI OscilliChartI;
Declare_CDblBufferPlotImplI( OscilloChartID1, COscilloPlotImpl, CXYHandler )
typedef OscilloChartID1<COscilloPlotImpl> OscilloChartID;

typedef	CPiePlotImpl	PieChart;
typedef CPiePlotImplI	PieChartI;
Declare_CDblBufferPlotImplI( PieChartID1, CPiePlotImpl, CPieHandler )
typedef PieChartID1<CPiePlotImpl> PieChartID;

typedef CStemPlotImpl StemChart;
typedef CStemPlotImplI StemChartI;
Declare_CDblBufferPlotImplI( StemChartID1, CStemPlotImpl, CXYHandler )
typedef StemChartID1<CStemPlotImpl> StemChartID;

typedef CRealtimeDemoImpl RealtimeChart;
typedef CRealtimeDemoImplI RealtimeChartI;

#endif