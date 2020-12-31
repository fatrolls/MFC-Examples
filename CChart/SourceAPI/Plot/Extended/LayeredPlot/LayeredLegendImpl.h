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

#ifndef __LAYEREDLEGENDIMPL_H_122333444455555__
#define __LAYEREDLEGENDIMPL_H_122333444455555__

#include "../../Basics/LegendImpl.h"
#include "LayeredLegend.h"

class CLayeredLegendImpl: public CLayeredLegend, public CLegendImpl
{
public:
	CLayeredLegendImpl(CPlot *pPlotImpl);
	virtual ~CLayeredLegendImpl();

	void		OnDraw( HDC hDC, RECT plotRect);
	int			RegionIdentify(HDC hDC,POINT point);
};

#endif