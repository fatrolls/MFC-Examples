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
#include "PiePlot.h"

CPiePlot::CPiePlot()
{
	SetDefaults();
}

CPiePlot::~CPiePlot()
{

}

void	CPiePlot::SetDefaults()
{
	m_nMaxPies = 10;
	m_fScale = 0.8;
	m_nLineSize = 1;
	m_nLineStyle = PS_SOLID;
	m_crLineColor = RGB(128,168,128);
	m_bCircleMode = false;

	m_bShowPieTitle = true;
	m_fStartAngle = 90.0;
	m_bClockWise = true;

	m_bShadowing = false;
	m_nShadowHalfLength = 5;
	m_fShadowAngle = 90.0;
	m_crShadowColor = RGB(128,128,128);

	SIZE offset={0,0};
	m_sizeOffset = offset;
	m_bDragMode = false;

	HFONT	hFont=CreateFont(24, 0, 0, 0, FW_BOLD, FALSE, FALSE, 0,
		ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH | FF_ROMAN,"Arial");
	GetObject(hFont,sizeof(LOGFONT),&m_lfPieTitleFont);
	DeleteObject(hFont);
}

void	CPiePlot::CopySettings(CPiePlot *plot)
{
	m_nMaxPies = plot->m_nMaxPies;
	m_fScale = plot->m_fScale;
	m_nLineSize = plot->m_nLineSize;
	m_nLineStyle = plot->m_nLineStyle;
	m_crLineColor = plot->m_crLineColor;
	m_bCircleMode = plot->m_bCircleMode;

	m_lfPieTitleFont = plot->m_lfPieTitleFont;
	m_bShowPieTitle = plot->m_bShowPieTitle;
	m_fStartAngle = plot->m_fStartAngle;
	m_bClockWise = plot->m_bClockWise;

	m_bShadowing = plot->m_bShadowing;
	m_nShadowHalfLength = plot->m_nShadowHalfLength;
	m_fShadowAngle = plot->m_fShadowAngle;
	m_crShadowColor = plot->m_crShadowColor;

	m_sizeOffset = plot->m_sizeOffset;
	m_bDragMode = plot->m_bDragMode;
}
