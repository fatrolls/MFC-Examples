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

#include "StdAfx.h"
#include "TDPlot.h"
#include "../../Basics/XYPlot.h"
#include "../../Basics/PlotUtility.h"

CTDPlot::CTDPlot()
{
	SetDefaults();
	SetRectEmpty( &m_rctLastClientRect );
	m_pAxes[0] = m_pAxes[1] = m_pAxes[2] = NULL;
}

CTDPlot::~CTDPlot()
{
	DeleteAxes();
}

void	CTDPlot::SetDefaults()
{
	m_fvBkgndColor[0] = 0.5f;
	m_fvBkgndColor[1] = 0.5f;
	m_fvBkgndColor[2] = 0.5f;
	m_fvFrameColor[0] = 1.0f;
	m_fvFrameColor[1] = 1.0f;
	m_fvFrameColor[2] = 0.5f;
	m_fvAxisPlaneColor[0] = 0.0f;
	m_fvAxisPlaneColor[1] = 1.0f;
	m_fvAxisPlaneColor[2] = 1.0f;

	m_bShowXYFrame = true;
	m_bShowYZFrame = true;
	m_bShowZXFrame = true;

	m_bShowMajorGrid = true;
	m_bShowMinorGrid = false;
	m_fvMajorGridColor[0] = 0.6f;
	m_fvMajorGridColor[1] = 0.0f;
	m_fvMajorGridColor[2] = 0.0f;
	m_fvMinorGridColor[0] = 0.0f;
	m_fvMinorGridColor[1] = 0.8f;
	m_fvMinorGridColor[2] = 0.0f;

	m_fLenX = 10.0f;
	m_fLenY = 10.0f;
	m_fLenZ = 10.0f;
	m_fAngleX = 100.0f;
	m_fAngleY = 170.0f;
	m_fAngleZ = 30.0f;

	m_fProjectionRange = 20.0f;

	m_strTitle = "3D Plot";

	m_nNurbsPoints = 40;
}

void	CTDPlot::CopySettings(CTDPlot *plot)
{

}

void	CTDPlot::InitializeOpenGL(HWND hWnd)
{
	PIXELFORMATDESCRIPTOR	pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER, 
		PFD_TYPE_RGBA,
		24,
		0, 0, 0, 0, 0, 0,
		0,
		0,
		0,
		0, 0, 0, 0, 
		32,
		0,
		0,
		PFD_MAIN_PLANE,
		0,
		0, 0, 0
	};
	HDC hDC = GetDC(hWnd);
	int aaa= GetLastError();
	int pf = ChoosePixelFormat(hDC, &pfd);
	BOOL rt = SetPixelFormat(hDC, pf, &pfd);
	m_hGLRC = wglCreateContext(hDC);
	ReleaseDC(hWnd, hDC);
}

void	CTDPlot::FinallizeOpenGL()
{
	wglDeleteContext(m_hGLRC);
}

void	CTDPlot::GetRange( double *xRange, double *yRange, double *zRange)
{
	double *pRange;
	for(int i=0; i<3; i++)
	{
		if(i==0)pRange = xRange;
		else if(i==1)pRange = yRange;
		else pRange = zRange;
		
		m_pAxes[i]->GetRange(pRange);
	}
}

// Shortcut to get xRange of plot
void	CTDPlot::GetXRange( double *range )
{
	double			yRange[2], zRange[2];
	GetRange( range, yRange, zRange );
}

// Shortcut to get yRange of plot
void	CTDPlot::GetYRange( double *range )
{
	double			xRange[2], zRange[2];
	GetRange( xRange, range, zRange );
}

// Shortcut to get zRange of plot
void	CTDPlot::GetZRange( double *range )
{
	double			xRange[2], yRange[2];
	GetRange( xRange, yRange, range );
}
