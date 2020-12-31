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

#ifndef __STEMPLOTIMPL_H_122333444455555__
#define __STEMPLOTIMPL_H_122333444455555__

#include "../../Basics/XYPlotImpl.h"
#include "../../Basics/XYHandler.h"
#include "StemPlot.h"

class	CStemPlotImpl : public CStemPlot, public CXYPlotImpl
{
public:
	CStemPlotImpl();
	virtual ~CStemPlotImpl();
private:
	int		m_nMaxSize;

public:
	void	OnDraw( HWND hWnd );
	void	OnDraw( HDC hDC, RECT destRect );

	int		AddData(vector<double> vData);
	int		AddData(double *pData, int nLen);

	void	SetXLabel(string label, int which);
protected:
	void	DrawDataSets( HDC hDC, RECT plotRect, double *xRange, double *yRange );
	void	DrawSingleDataSet( int which, HDC hDC, RECT plotRect, double *xRange, double *yRange );

	void	GetPlotRange( double *xRange, double *yRange );
public:
	int		GetNeareastDataSet( HDC hDC, POINT point );
public:
	bool	PtInDataArea( int which, HDC hDC, POINT point, RECT plotRect, double *xRange, double *yRange );
	void	SetMaxDataSetLen(int len);
};

class CStemPlotImplI : public CStemPlotImpl, public CXYHandler<CStemPlotImplI>
{
	
};

#endif




















