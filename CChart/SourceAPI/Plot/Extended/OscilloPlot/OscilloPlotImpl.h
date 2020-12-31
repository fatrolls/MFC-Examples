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

#ifndef __OSCILLOPLOTIMPL_H_122333444455555__
#define __OSCILLOPLOTIMPL_H_122333444455555__

#include "OscilloPlot.h"
#include "../../Basics/XYPlotImpl.h"
#include "../../Basics/XYHandler.h"

// class CPlot is a basement class
class COscilloPlotImpl : public COscilloPlot, public CXYPlotImpl
{
public:
	COscilloPlotImpl();
	virtual ~COscilloPlotImpl();

	void				DrawCursor( HDC hDC, RECT plotRect );
	void				DrawSelZone( HDC hDC, RECT plotRect );

public:
	void				OnDraw(HDC hDC, RECT destRect);
	void				OnDraw(HWND	hWnd);
};

class COscilloPlotImplI : public COscilloPlotImpl, public CXYHandler<COscilloPlotImplI>
{

};

#endif