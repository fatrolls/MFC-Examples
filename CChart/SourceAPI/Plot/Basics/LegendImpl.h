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

#ifndef __LEGENDIMPL_H_122333444455555__
#define __LEGENDIMPL_H_122333444455555__

#include "Legend.h"

class CPlot;

class CLegendImpl : public CLegend
{
protected:
	CPlot				*m_pPlot;
	
	virtual RECT		GetInitialPlotRect(HDC hDC, RECT chartRect);

	bool				m_bCanShow;
	int					m_nRealLineLength;
	int					m_nRealFontHeight;

public:
	CLegendImpl(CPlot *pPlotImpl);
	virtual ~CLegendImpl();

	inline CPlot	*GetPlot(){return m_pPlot;}
	inline void		SetPlot(CPlot *plot){m_pPlot=plot;}

	RECT			GetPlotRect(HDC hDC, RECT chartRect);

	virtual	int		RegionIdentify(HDC hDC,POINT point);

	virtual	void	OnDraw( HDC hDC, RECT plotRect);
};

#endif