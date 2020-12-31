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

#ifndef __IMAGELEGENDIMPL_H_122333444455555__
#define __IMAGELEGENDIMPL_H_122333444455555__

#include "../../Basics/LegendImpl.h"
#include "ImageLegend.h"
#include <string>
using namespace std;

class CImageLegendImpl: public CImageLegend, public CLegendImpl
{
public:
	CImageLegendImpl(CPlot *pPlotImpl);
	virtual ~CImageLegendImpl();

	void		OnDraw( HDC hDC, RECT plotRect);
	int			RegionIdentify(HDC hDC,POINT point);

	string		GetLegendTitle(int index);

	RECT		GetInitialPlotRect(HDC hDC, RECT chartRect);
};

#endif