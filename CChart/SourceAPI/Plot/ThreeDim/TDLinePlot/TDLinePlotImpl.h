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

#ifndef __TDLINEPLOTIMPL_H_122333444455555__
#define __TDLINEPLOTIMPL_H_122333444455555__

#include "../TDPlot/TDPlotImpl.h"
#include "TDLinePlot.h"

class CTDLinePlotImpl : public CTDLinePlot, public CTDPlotImpl
{
public:
	CTDLinePlotImpl(HWND hWnd);
	~CTDLinePlotImpl();

	void		OnDraw( HWND hWnd );
	void		OnDraw(HDC hDC, RECT destRect);

protected:
	void		GetPlotRange( double *xRange, double *yRange, double *zRange );

	void		DrawDataSets( double *xRange, double *yRange, double *zRange );
	void		DrawSingleDataSet( int which, double *xRange, double *yRange, double *zRange );
	void		DrawMarkers( int which, double *xRange, double *yRange, double *zRange );
};

#endif