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

#ifndef __TDPLOTIMPL_H_122333444455555__
#define __TDPLOTIMPL_H_122333444455555__

#include "TDPlot.h"

class CTDPlotImpl : public CTDPlot
{
public:
	CTDPlotImpl(HWND hWnd);
	~CTDPlotImpl();

	void		OnDraw( HWND hWnd );
	void		OnDraw(HDC hDC, RECT destRect);

protected:
	void		SetProjection(int cx, int cy);
	void		EraseBkgnd();
	void		InitialTransform();

	void		AddAxes();

protected:
	void		DrawFrame();
	void		DrawGrids( double *xRange, double *yRange, double *zRange );
	void		DrawMajorGrids( double *xRange, double *yRange, double *zRange );
	void		DrawMinorGrids( double *xRange, double *yRange, double *zRange );
	void		DrawTitle();
};

#endif