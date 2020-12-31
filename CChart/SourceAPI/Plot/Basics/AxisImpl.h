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

#ifndef __AXISIMPL_H_122333444455555__
#define __AXISIMPL_H_122333444455555__

#include "Axis.h"


class CAxisImpl : public CAxis
{
public:
	CAxisImpl(CPlot	*plot);
	virtual ~CAxisImpl();

private:
	CPlot		*m_pPlot;

	int			m_nRealTitleHeight, m_nRealTickLabelHeight;

public:

	void		OnDraw( HDC hDC, RECT clientRect, RECT chartRect );

	void		*GetPlot(){return m_pPlot;}
	void		SetPlot(CPlot *plot){m_pPlot=plot;}

	double		GetTickPosValue( int whichTick );
	string		GetTickLabel( int whichTick );

	RECT		GetPlotRect( HDC hDC, RECT clientRect, RECT chartRect );

	SIZE		GetMinDisplaySize( HDC hDC );
	SIZE		GetPaddingSize( HDC hDC );
	SIZE		GetSize( HDC hDC);

private:
	int			GetMaxTickLength();
	SIZE		GetRealTickLabelDimension(HDC hDC, RECT chartRect);
	int			GetRealTitleHeight(HDC hDC, RECT clientRect, RECT chartRect);
	RECT		GetTitleRect(HDC hDC, RECT clientRect, RECT chartRect);
	void		DrawFrame(HDC hDC, RECT clientRect, RECT chartRect, int style, int size, COLORREF color);
	void		DrawTitle(HDC hDC, RECT clientRect, RECT chartRect);
	void		DrawAxisLine(HDC hDC, RECT clientRect, RECT chartRect);
	void		DrawMajorTicks(HDC hDC, RECT clientRect, RECT chartRect);
	void		DrawMinorTicks(HDC hDC, RECT clientRect, RECT chartRect);
	void		DrawTickLabels(HDC hDC, RECT clientRect, RECT chartRect);
};

#endif