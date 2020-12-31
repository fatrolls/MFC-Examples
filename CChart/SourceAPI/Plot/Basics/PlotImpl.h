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

#ifndef __PLOTIMPL_H_122333444455555__
#define __PLOTIMPL_H_122333444455555__

#include "Plot.h"
#include "AxisImpl.h"

// Plot regions
enum
{
	kXYRegionOut = 0,
	kXYRegionData = 1,
	kXYRegionTitle = 2,
	kXYRegionBottom = 3,
	kXYRegionLeft = 4,
	kXYRegionTop = 5,
	kXYRegionRight = 6,
		
	kRegionCount
};

// class CPlot is a basement class
class CPlotImpl : public CPlot
{
public:
	CPlotImpl();
	virtual ~CPlotImpl();
public:
	//Method of converting handles between HWND and HDC
	//HWND WindowFromDC(HDC);
	//HDC GetDC(HWND);ReleaseDC(HWND, HDC)
	virtual	void		OnDraw( HWND hWnd );
	virtual void		OnDraw(HDC hDC, RECT destRect);	

public:
	virtual	void		DataToLP( HDC hDC, double *data, LPPOINT point );
	virtual	void		LPToData( HDC hDC, LPPOINT point, double *data );

	virtual	int			RegionIdentify(HDC hDC,POINT point);

protected:
	void				DrawTextInRect(HDC hDC, RECT rect, string title, LOGFONT logFont, int backmode, COLORREF color);
	void				DrawTitle(HDC hDC, RECT titleRect);
	void				DrawSubtitle( HDC hDC, RECT subtitleRect );
	virtual void		EraseBkgnd( HDC hDC, RECT destRect );//Set to virtual to be replaced in gdiplus implement
	void				DrawFrame( HDC hDC, RECT plotRect );
	void				DrawGrids( HDC hDC, RECT plotRect );

	RECT				AdjustPlotSizeForAxes( HDC hDC, RECT plotRect );
	RECT				AdjustPlotSizeForTitle( HDC hDC, RECT plotRect );

public:
	RECT				GetPlotRect( HDC hDC, RECT clientRect );
	RECT				GetTitleRect( HDC hDC, RECT clientRect, RECT chartRect );
	RECT				GetSubtitleRect( HDC hDC, RECT chartRect);

	inline	CAxis		*NewAxis( ){CAxisImpl *axis = new CAxisImpl(this); return axis;}
	
};

#endif