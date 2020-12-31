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

#ifndef __IMAGEPLOT_H_122333444455555__
#define __IMAGEPLOT_H_122333444455555__

#include "ImageLegend.h"

class CImagePlot
{
public:
	CImagePlot();
	virtual ~CImagePlot();
	void	SetDefaults();
	void	CopySettings(CImagePlot *plot);
protected:
	HDC		m_hMemImageDC;

	double	(*m_pFieldFcn)(double x, double y);
	int		m_nWidth,m_nHeight;
	double	m_fXRange[2],m_fYRange[2];

	COLORREF	m_crColor1,m_crColor2;
	bool		m_bExponential;

	double		m_fMaxValue, m_fMinValue;

public:
	inline	int		GetWidth(){return m_nWidth;}
	inline	void	SetWidth(int width){m_nWidth = width;}
	inline	int		GetHeight(){return m_nHeight;}
	inline	void	SetHeight(int height){m_nHeight = height;}

	inline	COLORREF	GetColor1(){return m_crColor1;}
	inline	void		SetColor1(COLORREF color){m_crColor1=color;}
	inline	COLORREF	GetColor2(){return m_crColor2;}
	inline	void		SetColor2(COLORREF color){m_crColor2=color;}

	inline	bool	IsExponential(){return m_bExponential;}
	inline	void	SetExponential(bool exp){m_bExponential = exp;}

	inline	double	GetMaxValue(){return m_fMaxValue;}
	inline	double	GetMinValue(){return m_fMinValue;}

	inline	void	SetFieldFcn(double (*_pFieldFcn) (double, double)){m_pFieldFcn = _pFieldFcn;}

	inline	void	SetRanges(double xRange[2], double yRange[2]){memcpy(m_fXRange, xRange, sizeof(double)*2);memcpy(m_fYRange, yRange, sizeof(double)*2);}
	inline	void	GetRanges(double xRange[2], double yRange[2]){memcpy(xRange, m_fXRange, sizeof(double)*2);memcpy(yRange, m_fYRange, sizeof(double)*2);}

public:
	void	CreateMemDC(HWND hWnd);
	bool	CreateImage();
};

#endif