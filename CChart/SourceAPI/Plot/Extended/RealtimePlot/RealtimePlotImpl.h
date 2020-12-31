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

#ifndef __REALTIMEPLOTIMPL_H_122333444455555__
#define __REALTIMEPLOTIMPL_H_122333444455555__

#include "../../Basics/XYPlotImpl.h"
#include "../../Basics/XYHandler.h"
#include "RealtimePlot.h"


class CRealtimePlotImpl : public CRealtimePlot, public CXYPlotImpl
{
public:
	CRealtimePlotImpl(HWND hWnd);
	virtual ~CRealtimePlotImpl();
	
public:
	void		SetNumOfDatas( int num );
	void		ResetPlot();
	void		OnInsertData();
	void		OnDraw( HWND hWnd );
protected:
	HWND		m_hWnd;

	//virtual window parameters
	HDC			m_hMemDC;
	int			m_maxX,m_maxY;
};


#endif