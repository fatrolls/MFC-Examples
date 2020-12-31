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
#include "ImagePlot.h"
#include <math.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// A test function for plot
/*double test(double x, double y)
{
	//return 1.0/( sqrt((x-2.0)*(x-2.0)+y*y) + sqrt((x+2.0)*(x+2.0)+y*y) );
	return 0.5 * (cos(x + 3.14 / 4) + sin(y + 3.14 / 4));
}*/
extern double TestFunction(double x, double y);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Implementation


CImagePlot::CImagePlot()
{
	m_hMemImageDC = NULL;

	SetFieldFcn(TestFunction);

	SetDefaults();
}

CImagePlot::~CImagePlot()
{
	//if(m_pLegend) delete m_pLegend;
	if(m_hMemImageDC)DeleteDC(m_hMemImageDC);
}

void	CImagePlot::SetDefaults()
{
	m_nWidth = 640;
	m_nHeight = 480;

	m_fXRange[0] = m_fYRange[0] = -5.0;
	m_fXRange[1] = m_fYRange[1] = 5.0;

	m_crColor1 = RGB(0, 128, 255);
	m_crColor2 = RGB(255, 0, 0);

	m_fMaxValue = m_fMinValue = 0.0;

	m_bExponential = false;
}

void	CImagePlot::CopySettings(CImagePlot *plot)
{
	m_nWidth = plot->m_nWidth;
	m_nHeight = plot->m_nHeight;
	memcpy(m_fXRange, plot->m_fXRange, sizeof(double)*2);
	memcpy(m_fYRange, plot->m_fYRange, sizeof(double)*2);

	m_crColor1 = plot->m_crColor1;
	m_crColor2 = plot->m_crColor2;

	m_bExponential = plot->m_bExponential;

	m_fMaxValue = plot->m_fMaxValue;
	m_fMinValue = plot->m_fMinValue;
}

void	CImagePlot::CreateMemDC(HWND hWnd)
{
	HDC hDC=GetDC(hWnd);
	HBITMAP hMembmp;
	int	maxX=GetSystemMetrics(SM_CXSCREEN);
	int	maxY=GetSystemMetrics(SM_CYSCREEN);
	hMembmp=CreateCompatibleBitmap(hDC,maxX,maxY);
	if(m_hMemImageDC)DeleteDC(m_hMemImageDC);
	m_hMemImageDC=CreateCompatibleDC(hDC); 
	SelectObject(m_hMemImageDC,hMembmp); 
	RECT rect; 
	SetRect(&rect,0,0,maxX,maxY);
	HBRUSH hBrush;
	hBrush = CreateSolidBrush(RGB(255,255,255)); 
	SelectObject(m_hMemImageDC,hBrush); 
	FillRect(m_hMemImageDC,&rect,hBrush);
	DeleteObject(hBrush);
	DeleteObject(hMembmp);
	
	ReleaseDC(hWnd,hDC);
}

bool	CImagePlot::CreateImage()
{
	double *pData = NULL;
	pData = new double[m_nWidth*m_nHeight];
	if(!pData)return false;

	double dx,dy,x0,y0;
	x0 = m_fXRange[0];
	y0 = m_fYRange[0];
	dx = (m_fXRange[1] - m_fXRange[0])/m_nWidth;
	dy = (m_fYRange[1] - m_fYRange[0])/m_nHeight;

	// Firstly, calculate the value on the array
	double maxval,minval;
	double x, y;
	int i, j;
	for(i=0; i<m_nHeight; i++)
	{
		for(j=0; j<m_nWidth; j++)
		{
			x = x0 + (j+0.5)*dx;
			y = y0 + (i+0.5)*dy;
			pData[j + i*m_nWidth ] = m_pFieldFcn(x, y); 
			if(i == 0 && j == 0)
			{
				maxval = minval =pData[0];
			}
			else
			{
				if(pData[j + i*m_nWidth ] > maxval)maxval = pData[j + i*m_nWidth ];
				if(pData[j + i*m_nWidth ] < minval)minval = pData[j + i*m_nWidth ];
			}
		}
	}

	m_fMaxValue = maxval;
	m_fMinValue = minval;

	bool bExp = m_bExponential;
	if(minval <= 0.0)bExp = false;

	if(bExp)
	{
		for(i=0; i<m_nWidth*m_nHeight; i++)
		{
			pData[i] = log10(pData[i]);
		}
		maxval = log10(maxval);
		minval = log10(minval);
	}

	// Then set the color at every point
	short r,g,b;
	short c1,c2;
	double val;
	if(maxval == minval)
	{
		r = ( GetRValue(m_crColor1) + GetRValue(m_crColor2) )/2;
		g = ( GetGValue(m_crColor1) + GetGValue(m_crColor2) )/2;
		b = ( GetBValue(m_crColor1) + GetBValue(m_crColor2) )/2;
		for(i=0; i<m_nHeight; i++)
		{
			for(j=0; j<m_nWidth; j++)
			{
				SetPixel(m_hMemImageDC, j, m_nHeight-1-i, RGB(r,g,b));
			}
		}
		delete []pData;
		return true;
	}

	for(i=0; i<m_nHeight; i++)
	{
		for(j=0; j<m_nWidth; j++)
		{
			val = pData[j + i*m_nWidth ];
			c1 = GetRValue(m_crColor1); c2 = GetRValue(m_crColor2);
			r = short( c1 + (c2 - c1)/(maxval - minval)*(val - minval) );
			c1 = GetGValue(m_crColor1); c2 = GetGValue(m_crColor2);
			g = short( c1 + (c2 - c1)/(maxval - minval)*(val - minval) );
			c1 = GetBValue(m_crColor1); c2 = GetBValue(m_crColor2);
			b = short ( c1 + (c2 - c1)/(maxval - minval)*(val - minval) );
			SetPixel(m_hMemImageDC, j, m_nHeight-1-i, RGB(r,g,b));
		}
	}

	delete []pData;
	return true;
}