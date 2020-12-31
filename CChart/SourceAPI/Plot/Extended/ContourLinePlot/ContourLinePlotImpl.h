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

#ifndef __COUNTOURLINEPLOTIMPL_H_122333444455555__
#define __COUNTOURLINEPLOTIMPL_H_122333444455555__

#include "../../Basics/XYPlotImpl.h"
#include "../../Basics/XYHandler.h"
#include "ContourLinePlot.h"

class CContourLinePlotImpl : public CContourLinePlot, public CXYPlotImpl
{
public:
	CContourLinePlotImpl();
	virtual ~CContourLinePlotImpl();
public:
	void SetDataInfoDraw(bool bDraw);
	bool CreateContour();
	bool CreateContour(int nPlanes);
	bool CreateContour(int nPlanes,bool bExponential);

	int GetDataSetLevels();//{return m_listContour.GetNPlanes();}
};

class CContourLinePlotImplI : public CContourLinePlotImpl, public CXYHandler<CContourLinePlotImplI>
{

};

#endif