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

#include "ContourLinePlot.h"
#include "ListContour.h"

CContourLinePlot::CContourLinePlot()
{
}

CContourLinePlot::~CContourLinePlot()
{
}

void CContourLinePlot::SetPlotRange(double pRange[4])
{
	m_pListContour->SetPlotRange(pRange);
}

void CContourLinePlot::SetFieldFcn(double (*_pFieldFcn)(double, double))
{
	m_pListContour->SetFieldFcn(_pFieldFcn);
}

