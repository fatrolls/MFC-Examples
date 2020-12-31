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
#include "TDPlotImpl.h"
#include "AxisTDimpl.h"
#include "GlFont.h"

CTDPlotImpl::CTDPlotImpl(HWND hWnd)
{
	AddAxes();
	InitializeOpenGL(hWnd);
}

CTDPlotImpl::~CTDPlotImpl()
{
	FinallizeOpenGL();
}

void	CTDPlotImpl::AddAxes()
{
	DeleteAxes();

	m_pAxes[0] = new CAxisTDImpl(this);
	m_pAxes[0]->SetDefaults();
	m_pAxes[0]->SetLocation(kLocationTDX);
	m_pAxes[1] = new CAxisTDImpl(this);
	m_pAxes[1]->SetDefaults();
	m_pAxes[1]->SetLocation(kLocationTDY);
	m_pAxes[2] = new CAxisTDImpl(this);
	m_pAxes[2]->SetDefaults();
	m_pAxes[2]->SetLocation(kLocationTDZ);
}

void	CTDPlotImpl::OnDraw( HWND hWnd )
{
	HDC hDC = GetDC(hWnd);
	RECT destRect;
	GetClientRect(hWnd,&destRect);
	
	OnDraw( hDC, destRect );
	
	ReleaseDC(hWnd, hDC);
}

void	CTDPlotImpl::OnDraw(HDC hDC, RECT destRect)
{

	double xRange[2], yRange[2], zRange[2];
	GetPlotRange(xRange, yRange, zRange);

	SetProjection( abs(destRect.right - destRect.left), abs(destRect.bottom - destRect.top) );
	EraseBkgnd();
	InitialTransform();
	DrawFrame();
	DrawGrids(xRange, yRange, zRange);
	DrawTitle();

	m_rctLastClientRect = destRect;
}

void	CTDPlotImpl::EraseBkgnd()
{
	glClearColor(m_fvBkgndColor[0], m_fvBkgndColor[1], m_fvBkgndColor[2], 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void	CTDPlotImpl::SetProjection(int cx, int cy)
{
	int	w = cx;
	int h = cy;
	
	GLfloat fRange = m_fProjectionRange;
	
	if(h == 0) h = 1;
	
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	
	glLoadIdentity();
	if( w <= h )
		glOrtho(-fRange, fRange, -fRange*h/w, fRange*h/w, -fRange, fRange);
	else
		glOrtho(-fRange*w/h, fRange*w/h, -fRange, fRange, -fRange, fRange);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void	CTDPlotImpl::InitialTransform()
{
	//glTranslatef(m_fLenX/3.0f, -m_fLenY/3.0f, m_fLenZ);
	//glTranslatef(-m_fLenX/2.0f, -m_fLenY/2.0f, m_fLenZ);
	glRotatef(m_fAngleX, 1.0f, 0.0f, 0.0f);
	glRotatef(m_fAngleY, 0.0f, 1.0f, 0.0f);
	glRotatef(m_fAngleZ, 0.0f, 0.0f, 1.0f);
	glTranslatef(-m_fLenX/2.0f, -m_fLenY/2.0f, 0.0f);
}

void	CTDPlotImpl::DrawFrame()
{
	// Draw the outer frame
	glColor3fv(m_fvAxisPlaneColor);
	if(m_bShowXYFrame)
	{
		glBegin(GL_POLYGON);
			glVertex3f(0.0f, 0.0f, 0.0f);
			glVertex3f(m_fLenX, 0.0f, 0.0f);
			glVertex3f(m_fLenX, m_fLenY, 0.0f);
			glVertex3f(0.0f, m_fLenY, 0.0f);
		glEnd();
	}
	if(m_bShowYZFrame)
	{	
		glBegin(GL_POLYGON);
			glVertex3f(0.0f, 0.0f, 0.0f);
			glVertex3f(0.0f, m_fLenY, 0.0f);
			glVertex3f(0.0f, m_fLenY, m_fLenZ);
			glVertex3f(0.0f, 0.0f, m_fLenZ);
		glEnd();
	}
	if(m_bShowZXFrame)
	{	
		glBegin(GL_POLYGON);
			glVertex3f(0.0f, 0.0f, 0.0f);
			glVertex3f(m_fLenX, 0.0f, 0.0f);
			glVertex3f(m_fLenX, 0.0f, m_fLenZ);
			glVertex3f(0.0f, 0.0f, m_fLenZ);
		glEnd();
	}

	// Draw the axis lines
	glBegin(GL_LINES);
		glColor3fv(m_fvFrameColor);
		// the three axis line
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(m_fLenX, 0.0f, 0.0f);
		
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, m_fLenY, 0.0f);
		
		glVertex3f(0.0f, 0.0f, 0.0f);
		glVertex3f(0.0f, 0.0f, m_fLenZ);
		
		// the contrary
/*		glVertex3f(m_fLenX, m_fLenY, m_fLenZ);
		glVertex3f(m_fLenX, m_fLenY, 0.0f);
		
		glVertex3f(m_fLenX, m_fLenY, m_fLenZ);
		glVertex3f(0.0f, m_fLenY, m_fLenZ);
		
		glVertex3f(m_fLenX, m_fLenY, m_fLenZ);
		glVertex3f(m_fLenX, 0.0f, m_fLenZ);*/

		// others
		glVertex3f(m_fLenX, 0.0f, 0.0f);
		glVertex3f(m_fLenX, m_fLenY, 0.0f);

		glVertex3f(m_fLenX, 0.0f, 0.0f);
		glVertex3f(m_fLenX, 0.0f, m_fLenZ);

		glVertex3f(0.0f, m_fLenY, 0.0f);
		glVertex3f(m_fLenX, m_fLenY, 0.0f);

		glVertex3f(0.0f, m_fLenY, 0.0f);
		glVertex3f(0.0f, m_fLenY, m_fLenZ);

		glVertex3f(0.0f, 0.0f, m_fLenZ);
		glVertex3f(m_fLenX, 0.0f, m_fLenZ);

		glVertex3f(0.0f, 0.0f, m_fLenZ);
		glVertex3f(0.0f, m_fLenY, m_fLenZ);
	glEnd();
}

void	CTDPlotImpl::DrawGrids( double *xRange, double *yRange, double *zRange )
{
	DrawMajorGrids(xRange, yRange, zRange);
	DrawMinorGrids(xRange, yRange, zRange);
}

void	CTDPlotImpl::DrawMajorGrids( double *xRange, double *yRange, double *zRange )
{
	if(!m_bShowMajorGrid)return;

	GLfloat x, y, z;
	int i;

	int nMajorTicks;

	nMajorTicks = m_pAxes[0]->GetTickCount();
	for(i=1; i<=nMajorTicks; i++)
	{
		x = i * m_fLenX/(nMajorTicks + 1);
		glBegin(GL_LINES);
			glVertex3f(x, 0.0f, 0.0f);
			glVertex3f(x, m_fLenY, 0.0f);

			glVertex3f(x, 0.0f, 0.0f);
			glVertex3f(x, 0.0f, m_fLenZ);
		glEnd();
	}
	nMajorTicks = m_pAxes[1]->GetTickCount();
	for(i=1; i<=nMajorTicks; i++)
	{
		y = i * m_fLenY/(nMajorTicks + 1);
		glBegin(GL_LINES);
		glVertex3f(0.0f, y, 0.0f);
		glVertex3f(m_fLenX, y, 0.0f);
		
		glVertex3f(0.0f, y, 0.0f);
		glVertex3f(0.0f, y, m_fLenZ);
		glEnd();
	}
	nMajorTicks = m_pAxes[2]->GetTickCount();
	for(i=1; i<=nMajorTicks; i++)
	{
		z = i * m_fLenZ/(nMajorTicks + 1);
		glBegin(GL_LINES);
		glVertex3f(0.0f, 0.0f, z);
		glVertex3f(m_fLenX, 0.0f, z);
		
		glVertex3f(0.0f, 0.0f, z);
		glVertex3f(0.0f, m_fLenY, z);
		glEnd();
	}
}

void	CTDPlotImpl::DrawMinorGrids( double *xRange, double *yRange, double *zRange )
{
	if(!m_bShowMinorGrid)return;

	GLfloat x, y, z;
	int i, j;
	
	int nMajorTicks, nMinorTicks;
	
	nMajorTicks = m_pAxes[0]->GetTickCount();
	nMinorTicks = m_pAxes[0]->GetMinorTickCount();
	for(i=0; i<=nMajorTicks; i++)
	{
		for(j=1; j<=nMinorTicks; j++)
		{
			x = i * m_fLenX/(nMajorTicks + 1) + j * m_fLenX/(nMajorTicks + 1)/(nMinorTicks + 1);
			glBegin(GL_LINES);
			glVertex3f(x, 0.0f, 0.0f);
			glVertex3f(x, m_fLenY, 0.0f);
			
			glVertex3f(x, 0.0f, 0.0f);
			glVertex3f(x, 0.0f, m_fLenZ);
			glEnd();
		}
		
	}
	nMajorTicks = m_pAxes[1]->GetTickCount();
	nMinorTicks = m_pAxes[1]->GetMinorTickCount();
	for(i=0; i<=nMajorTicks; i++)
	{
		for(j=1; j<=nMinorTicks; j++)
		{
			y = i * m_fLenY/(nMajorTicks + 1) + j * m_fLenY/(nMajorTicks + 1)/(nMinorTicks + 1);
			glBegin(GL_LINES);
			glVertex3f(0.0f, y, 0.0f);
			glVertex3f(m_fLenX, y, 0.0f);
			
			glVertex3f(0.0f, y, 0.0f);
			glVertex3f(0.0f, y, m_fLenZ);
			glEnd();
		}
		
	}
	nMajorTicks = m_pAxes[2]->GetTickCount();
	nMinorTicks = m_pAxes[2]->GetMinorTickCount();
	for(i=0; i<=nMajorTicks; i++)
	{
		for(j=1; j<=nMinorTicks; j++)
		{
			z = i * m_fLenZ/(nMajorTicks + 1) + j * m_fLenY/(nMajorTicks + 1)/(nMinorTicks + 1);
			glBegin(GL_LINES);
			glVertex3f(0.0f, 0.0f, z);
			glVertex3f(m_fLenX, 0.0f, z);
			
			glVertex3f(0.0f, 0.0f, z);
			glVertex3f(0.0f, m_fLenY, z);
			glEnd();
		}
		
	}
}

void CTDPlotImpl::DrawTitle()
{
	CGlFont glfont;
	double length = glfont.Get3DLength(m_strTitle.c_str());
	glPushMatrix();
	glTranslatef(m_fLenX/2,0-length,m_fLenZ*1.05);
	glRotatef(-90.0,1.0f,0.0f,0.0f);
	glRotatef(180.0,0.0f,0.0f,1.0f);
	glScalef(2.0f,2.0f,2.0f);
	glfont.Draw3DText(m_strTitle.c_str());
	glPopMatrix();
}