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
#include "OscilloPlot.h"

/////////////////////////////////////////////////////////////////////////
// Class CPlot

COscilloPlot::COscilloPlot()
{
	SetDefaults();
}

COscilloPlot::~COscilloPlot()
{
}

void	COscilloPlot::SetDefaults()
{
	m_bShowHCursor = false;
	m_bShowVCursor = false;
	m_fCursorX = 1.0e90;
	m_fCursorY = 1.0e90;
	m_bHoldCursorToCurve = false;
	m_nIndexToHoldCursor = 0;
	m_nCursorSize	= 1;
	m_nCursorStyle	= PS_SOLID;
	m_crCursorColor = RGB(128,0,0);

	m_bEnableXZoneSel=false;
	m_bEnableYZoneSel=false;
	m_fXZoneSelLower = -1.0e90;
	m_fXZoneSelUpper = 1.0e90;
	m_fYZoneSelLower = -1.0e90;
	m_fYZoneSelUpper = 1.0e90;
	m_crZoneSelColor = RGB(224,224,255);
}

// Copy the settings from one chart to another
void	COscilloPlot::CopySettings( const COscilloPlot *plot )
{
	// Then COscilloPlot
	m_bShowHCursor	 = plot->m_bShowHCursor;
	m_bShowVCursor	 = plot->m_bShowVCursor;
	m_fCursorX		 = plot->m_fCursorX;
	m_fCursorY		 = plot->m_fCursorY;
	m_bHoldCursorToCurve = plot->m_bHoldCursorToCurve;
	m_nIndexToHoldCursor = plot->m_nIndexToHoldCursor;
	m_nCursorSize	= plot->m_nCursorSize;
	m_nCursorStyle	= plot->m_nCursorStyle;
	m_crCursorColor	 = plot->m_crCursorColor;
	m_bEnableXZoneSel= plot->m_bEnableXZoneSel;
	m_bEnableYZoneSel= plot->m_bEnableYZoneSel;
	m_fXZoneSelLower = plot->m_fXZoneSelLower;
	m_fXZoneSelUpper = plot->m_fXZoneSelUpper;
	m_fYZoneSelLower = plot->m_fYZoneSelLower;
	m_fYZoneSelUpper = plot->m_fYZoneSelUpper;
	m_crZoneSelColor = plot->m_crZoneSelColor;

}

