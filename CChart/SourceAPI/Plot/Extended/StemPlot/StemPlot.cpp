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
#include "StemPlot.h"

CStemPlot::CStemPlot()
{
	SetDefaults();
}

CStemPlot::~CStemPlot()
{

}

void	CStemPlot::SetDefaults()
{
	m_nMaxDataSets = 4;
	m_nMaxDataSetLen = 10;
	m_fRatioOccupy = 0.6;
}

void	CStemPlot::CopySettings(CStemPlot *plot)
{
	m_nMaxDataSets = plot->m_nMaxDataSets;
	m_nMaxDataSetLen = plot->m_nMaxDataSetLen;
	m_fRatioOccupy = plot->m_fRatioOccupy;
}