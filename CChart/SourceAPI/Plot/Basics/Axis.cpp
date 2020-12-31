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
#include "Axis.h"
#include "PlotUtility.h"

/////////////////////////////////////////////////////////////////////////
// Class CAxis

CAxis::CAxis()
{
	SetDefaults();
}

CAxis::~CAxis()
{
}

/////////////////////////////////////////////////////////////////////////
// implement

void CAxis::SetDefaults()
{
	m_nTickCount = 4;
	m_nMinorTickCount = 5;
	m_Range[0] = m_Range[1] = 0.0;
	m_bVisible = true;
	m_strTitle = "";
	m_nLocation = kLocationBottom;

#ifdef DEFAULT_WHITE_BACKGROUND
	m_crAxisColor = RGB(0, 100, 0);
	m_crTitleColor = RGB(0, 0, 0);
#else
	m_crAxisColor = RGB(0, 255, 0);
	m_crTitleColor = RGB(255, 255, 255);
#endif

	m_nTickLength = 10;
	m_nMinorTickLength = 5;
	m_nTickPosition = kTickPositionOuter;
	m_nMinorTickPosition = kTickPositionOuter;
	m_nTickSize = 1;
	m_nMinorTickSize = 1;
	m_crTickColor = m_crAxisColor;
	m_crMinorTickColor = m_crAxisColor;
	m_bRangeSet = false;

	m_bAutoMajorTick = true;
	m_bAutoMinorTick = true;

	m_bShowMajorTicks = true;
	m_bShowMinorTicks = true;

	m_crTickLabelColor = m_crAxisColor;
	m_bShowTickLabel = true;

	m_nAxisSize = 2;
	m_nLineStyle = PS_SOLID;

	m_nMarginHorizontal = 10;
	m_nMarginVertical = 15;


	m_bCurrent = false;

	m_nTitlePosition = kTitlePositionNormal;
	SIZE offset = {0, 0};
	m_sizeTitleOffset = offset;
	m_sizeLabelOffset = offset;
	m_strLabelSuffix = "";

	m_bSameColor = true;

	m_bReplaceLabel = false;
	m_vstrAlternateLabels.clear();

	HFONT hFont;

	hFont = CreateFont(30, 0, 0, 0, FW_BOLD, FALSE, FALSE, 0, ANSI_CHARSET,
				OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
				DEFAULT_PITCH | FF_ROMAN, "Arial");
	GetObject(hFont, sizeof(LOGFONT), &m_lfTitleFont);
	DeleteObject(hFont);
	hFont = CreateFont(24, 0, 0, 0, FW_BOLD, FALSE, FALSE, 0, ANSI_CHARSET,
				OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
				DEFAULT_PITCH | FF_ROMAN, "Arial");
	GetObject(hFont, sizeof(LOGFONT), &m_lfLabelFont);
	DeleteObject(hFont);
}

void CAxis::CopySettings(CAxis* axis)
{
	m_nTickCount = axis->m_nTickCount;
	m_nMinorTickCount = axis->m_nMinorTickCount;
	m_nTickLength = axis->m_nTickLength;
	m_nMinorTickLength = axis->m_nMinorTickLength;
	m_nTickPosition = axis->m_nTickPosition;
	m_nMinorTickPosition = axis->m_nMinorTickPosition;
	m_nTickSize = axis->m_nTickSize;
	m_nMinorTickSize = axis->m_nMinorTickSize;
	m_crTickColor = axis->m_crTickColor;
	m_crMinorTickColor = axis->m_crMinorTickColor;
	m_nAxisSize = axis->m_nAxisSize;
	m_nLineStyle = axis->m_nLineStyle;
	m_Range[0] = axis->m_Range[0];
	m_Range[1] = axis->m_Range[1];
	m_bVisible = axis->m_bVisible;
	m_strTitle = axis->m_strTitle;
	m_nLocation = axis->m_nLocation;
	m_lfTitleFont = axis->m_lfTitleFont;
	m_lfLabelFont = axis->m_lfLabelFont;
	m_crAxisColor = axis->m_crAxisColor;
	m_crTitleColor = axis->m_crTitleColor;
	m_bRangeSet = axis->m_bRangeSet;
	m_bAutoMajorTick = axis->m_bAutoMajorTick;
	m_bAutoMinorTick = axis->m_bAutoMinorTick;
	m_bShowMajorTicks = axis->m_bShowMajorTicks;
	m_bShowMinorTicks = axis->m_bShowMinorTicks;

	m_crTickLabelColor = axis->m_crTickLabelColor;
	m_bShowTickLabel = axis->m_bShowTickLabel;

	m_nMarginHorizontal = axis->m_nMarginHorizontal;
	m_nMarginVertical = axis->m_nMarginVertical;

	m_nTitlePosition = axis->m_nTitlePosition;
	m_sizeTitleOffset = axis->m_sizeTitleOffset;
	m_sizeLabelOffset = axis->m_sizeLabelOffset;
	m_strLabelSuffix = axis->m_strLabelSuffix;

	m_bSameColor = axis->m_bSameColor;
}

