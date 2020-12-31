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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Three Dimension plot use the OpenGL API to draw on the screen

#ifndef __TDCONTOURPLOT_H_122333444455555__
#define __TDCONTOURPLOT_H_122333444455555__

#include "gl/gl.h"

class CTDContourPlot
{
public:
	CTDContourPlot();
	~CTDContourPlot();

	void		SetDefaults();
	void		CopySettings(CTDContourPlot *plot);

public:
	//static	void f4min(int *n, double x[2], double *y);
	//static	void f4max(int *n, double x[2], double *y);
	static	void f4min(double x[2], double &y);
	static	void f4max(double x[2], double &y);

	void		SetFieldFcn(double (*_pFieldFcn) (double, double)){m_pFieldFcn = _pFieldFcn;}
	void		SetPlotRange(double pRange[4]);
	
protected:
	double		(*m_pFieldFcn)(double x, double y);
	double		m_fXRange[2], m_fYRange[2], m_fZRange[2];

	GLfloat		m_fvColor1[3];
	GLfloat		m_fvColor2[3];

	int			m_nXSteps, m_nYSteps;
	int			m_nXMapSteps, m_nYMapSteps;

	bool		m_bExponential;
	bool		m_bLighting;
protected:
	void		GetDataRanges(double xRange[2], double yRange[2], double zRange[2]);
	void		GetZRange();
};

#endif