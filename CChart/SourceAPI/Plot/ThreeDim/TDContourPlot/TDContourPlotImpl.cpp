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
#include "TDContourPlotImpl.h"
#include "../TDPlot/AxisTDImpl.h"
#include "../../Basics/PlotUtility.h"
#include "../../Accessary/Numerical/NlFit/NlFit.h"

CTDContourPlotImpl::CTDContourPlotImpl(HWND hWnd) : CTDPlotImpl(hWnd)
{
}

CTDContourPlotImpl::~CTDContourPlotImpl()
{
}

void	CTDContourPlotImpl::GetPlotRange( double *xRange, double *yRange, double *zRange )
{
	GetDataRanges(xRange, yRange, zRange);
	
	double *pRange;
	double optRange[2];
	int	optNTicks, optMinorTicks;
	for(int i=0; i<3; i++)
	{
		if(i==0)pRange = xRange;
		else if(i==1)pRange = yRange;
		else pRange = zRange;

		if(pRange[0]==pRange[1])
		{
			if(pRange[0]==0.0)
			{
				pRange[0]-=0.5;
				pRange[1]+=0.5;
			}
			else
			{
				pRange[0]-=pow(10,floor(log10(fabs(pRange[0]))));;
				pRange[1]+=pow(10,floor(log10(fabs(pRange[0]))));;
			}
		}
		//if( m_pAxes[i]->IsRangeSet() )
			GetOptimalRangeExact( pRange, optRange, &optNTicks, &optMinorTicks );
		//else
			//GetOptimalRange( pRange, optRange, &optNTicks, &optMinorTicks, false );
		memcpy(pRange, optRange, 2*sizeof(double));
		m_pAxes[i]->SetRange(pRange[0],pRange[1]);
		m_pAxes[i]->SetTickCount(optNTicks);
		m_pAxes[i]->SetMinorTickCount(optMinorTicks);
	}
}

void	CTDContourPlotImpl::OnDraw( HWND hWnd )
{
	HDC hDC = GetDC(hWnd);
	RECT destRect;
	GetClientRect(hWnd,&destRect);
	
	OnDraw( hDC, destRect );
	
	ReleaseDC(hWnd, hDC);
}

void	CTDContourPlotImpl::OnDraw(HDC hDC, RECT destRect)
{
	double xRange[2], yRange[2], zRange[2];
	GetPlotRange(xRange, yRange, zRange);

	glPushMatrix();
	wglMakeCurrent( hDC, m_hGLRC );

	CTDPlotImpl::OnDraw( hDC, destRect );
	// Draw the Datasets
	InitLight();
	DrawSurface(xRange, yRange, zRange);
	DeleteLight();
	glFlush();
	wglMakeCurrent(	hDC, NULL);
	glPopMatrix();

	SwapBuffers( hDC );
	m_rctLastClientRect = destRect;
}

void	CTDContourPlotImpl::DrawSurface( double *xRange, double *yRange, double *zRange )
{
	double xScale, yScale, zScale;
	double x, y, z;
	xScale = m_fLenX/(xRange[1] - xRange[0]);
	yScale = m_fLenY/(yRange[1] - yRange[0]);
	zScale = m_fLenY/(zRange[1] - zRange[0]);

	GLfloat *CtrlPoints = new GLfloat[m_nXSteps*m_nYSteps*3];
	int i,j;
	for(i=0; i<m_nYSteps; i++)
	{
		for(j=0; j<m_nXSteps; j++)
		{
			x = xRange[0] + j*(xRange[1] - xRange[0])/m_nXSteps;
			y = yRange[0] + i*(yRange[1] - yRange[0])/m_nYSteps;
			z = m_pFieldFcn(x,y);

			CtrlPoints[3*(m_nXSteps*i+j)+0] = j*m_fLenX/m_nXSteps;
			CtrlPoints[3*(m_nXSteps*i+j)+1] = i*m_fLenY/m_nYSteps;
			CtrlPoints[3*(m_nXSteps*i+j)+2] = zScale*(z - zRange[0]);
		}
	}

	glMap2f(GL_MAP2_VERTEX_3, 0.0f, 1.0f, 3*m_nYSteps, m_nXSteps, 0.0f, 1.0f, 3, m_nYSteps, CtrlPoints);
	glEnable(GL_MAP2_VERTEX_3);
	glShadeModel(GL_FLAT);

	// surface
	glMapGrid2f(m_nXMapSteps,0.0f,1.0f,m_nYMapSteps,0.0f,1.0f);
	glEvalMesh2(GL_FILL,0,m_nXMapSteps,0,m_nYMapSteps);
	//glEvalMesh2(GL_LINE,0,m_nXMapSteps,0,m_nYMapSteps);

	glDisable(GL_MAP2_VERTEX_3);

	delete []CtrlPoints;
}

double		CTDContourPlotImpl::GetStepValue(int index, double v1, double v2, int nSegs, bool bExponential)
{
	if(v1 == v2)return v1;

	if(!m_bExponential)
	{
		return v1+index*(v2-v1)/nSegs;
	}
	else
	{
		if(v1!=0.0)
			return v1*pow(pow(fabs(v2/v1), 1.0/nSegs)*sign(v2/v1),index);
		else
			return sign(v2)*exp(log(fabs(v2))/nSegs*index);
	}
}

void	CTDContourPlotImpl::InitLight()
{
	GLfloat ambient[] = {0.6f, 0.0f, 0.2f, 1.0f};
	GLfloat position[4];
	GLfloat mat_diffuse[] = {0.6f, 0.9f, 0.8f, 1.0f};
	GLfloat mat_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
	GLfloat mat_shininess[] = {50.0f};

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);

	position[0] = m_fLenX;
	position[1] = m_fLenY;
	position[2] = m_fLenZ;
	position[3] = 1.0f;
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	position[0] = 0.0f;
	position[1] = 0.0f;
	position[2] = 0.0f;
	position[3] = 1.0f;
	glLightfv(GL_LIGHT1, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT1, GL_POSITION, position);

	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glMaterialfv(GL_BACK, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_BACK, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_BACK, GL_SHININESS, mat_shininess);
	
	glPointSize(5.0f);
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_POINTS);
		glVertex3fv(position);
	glEnd();

	//glEnable(GL_DEPTH_TEST);
	//glEnable(GL_AUTO_NORMAL);
	//glEnable(GL_NORMALIZE);
}

void	CTDContourPlotImpl::DeleteLight()
{
	glDisable(GL_LIGHT0);
	glDisable(GL_LIGHTING);
	//glDisable(GL_DEPTH_TEST);
	//glDisable(GL_AUTO_NORMAL);
	//glDisable(GL_NORMALIZE);
}