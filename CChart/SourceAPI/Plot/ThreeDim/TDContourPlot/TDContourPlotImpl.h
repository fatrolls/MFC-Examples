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

#ifndef __TDCONTOURPLOTIMPL_H_122333444455555__
#define __TDCONTOURPLOTIMPL_H_122333444455555__

#include "../TDPlot/TDPlotImpl.h"
#include "TDContourPlot.h"

class CTDContourPlotImpl : public CTDContourPlot, public CTDPlotImpl
{
public:
	CTDContourPlotImpl(HWND hWnd);
	~CTDContourPlotImpl();

	void		OnDraw( HWND hWnd );
	void		OnDraw( HDC hDC, RECT destRect );

protected:
	void		GetPlotRange( double *xRange, double *yRange, double *zRange );
	void		DrawSurface( double *xRange, double *yRange, double *zRange );

	double		GetStepValue( int index, double v1, double v2, int nSegs, bool bExponential);

	void		InitLight();
	void		DeleteLight();
};

#endif