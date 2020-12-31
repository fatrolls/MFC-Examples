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

#ifndef __TDPLOT_H_122333444455555__
#define __TDPLOT_H_122333444455555__

#include <gl/gl.h>
#include <gl/glu.h>
#include <gl/glaux.h>
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
#pragma comment(lib, "glaux.lib")

//#include "../../Basics/Origin.h"
#include "../../Basics/PlotData.h"
#include "../../Basics/Axis.h"

class CTDPlot
{
public:
	CTDPlot();
	~CTDPlot();

	void		SetDefaults();
	void		CopySettings(CTDPlot *plot);
protected:
	CAxis		*m_pAxes[3];

	GLfloat		m_fvBkgndColor[3];
	GLfloat		m_fvFrameColor[3];
	GLfloat		m_fvAxisPlaneColor[3];

	GLfloat		m_fLenX;
	GLfloat		m_fLenY;
	GLfloat		m_fLenZ;
	GLfloat		m_fAngleX;
	GLfloat		m_fAngleY;
	GLfloat		m_fAngleZ;

	bool		m_bShowXYFrame;
	bool		m_bShowYZFrame;
	bool		m_bShowZXFrame;

	bool		m_bShowMajorGrid;
	bool		m_bShowMinorGrid;
	GLfloat		m_fvMajorGridColor[3];
	GLfloat		m_fvMinorGridColor[3];

	int			m_nNurbsPoints;

	GLfloat		m_fProjectionRange;

	string		m_strTitle;

public:
	virtual	void		GetPlotRange( double *xRange, double *yRange, double *zRange )=0;
	void		GetRange( double *xRange, double *yRange, double *zRange );
	void		GetXRange( double *range );
	void		GetYRange( double *range );
	void		GetZRange( double *range );

protected:
	HGLRC	m_hGLRC;
	RECT	m_rctLastClientRect;

	void	InitializeOpenGL(HWND hWnd);
	void	FinallizeOpenGL();
	
	virtual	void	AddAxes()=0;
	void	DeleteAxes() { for(int i=0; i<3; i++)if(m_pAxes[i])delete m_pAxes[i]; }	
};

#endif