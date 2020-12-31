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

#include "stdafx.h"
#include "XYPlot.h"
#include "Legend.h"
#include "PlotData.h"
#include "PlotUtility.h"

CLegend::CLegend()
{
	SetDefaults();
}

CLegend::~CLegend()
{

}

void		CLegend::SetDefaults()
{
	m_nMaxNumOfLegend = 8;
	m_sizeOffset.cx = m_sizeOffset.cy = 0;
#ifndef	DEFAULT_WHITE_BACKGROUND
	// Default is black background
	m_crBorderColor = RGB(255,255,255);
	m_crBkgndColor = RGB(0,0,0);
#else
	m_crBorderColor = RGB(0,0,0);
	m_crBkgndColor = RGB(255,255,255);
#endif
	m_nBorderLineSize = 2;
	m_nBorderLineStyle  = PS_SOLID;
	m_nLineLength = 60;
	m_bTransparent = false;
	m_nMarginSize = 2;
	m_nDragMarginSize = 10;

	m_bConfined = true;

	m_bColorRect = false;

	m_bCurrent = false;

	HFONT		hFont;
	hFont = CreateFont(16, 0, 0, 0, FW_BOLD, TRUE, FALSE, 0,
		ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH | FF_ROMAN,"Arial");
	GetObject(hFont,sizeof(LOGFONT),&m_lfFont);
	DeleteObject(hFont);

	m_bDragMode = false;
}

void		CLegend::CopySettings(const CLegend *legend)
{
	m_nMaxNumOfLegend = legend->m_nMaxNumOfLegend;
	m_sizeOffset = legend->m_sizeOffset;
	m_crBorderColor = legend->m_crBorderColor;
	m_crBkgndColor = legend->m_crBkgndColor;
	m_nBorderLineSize = legend->m_nBorderLineSize;
	m_nBorderLineStyle = legend->m_nBorderLineStyle;
	m_nLineLength = legend->m_nLineLength;
	m_bTransparent = legend->m_bTransparent;
	m_nMarginSize = legend->m_nMarginSize;
	m_nDragMarginSize = legend->m_nDragMarginSize;
	m_lfFont = legend->m_lfFont;
	m_bCurrent = legend->m_bCurrent;
	m_bConfined = legend->m_bConfined;
	m_bColorRect = legend->m_bColorRect;
}
