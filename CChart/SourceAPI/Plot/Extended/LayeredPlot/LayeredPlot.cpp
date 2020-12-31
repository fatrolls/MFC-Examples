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
#include "PlotLayerImpl.h"
#include "LayeredPlot.h"

CLayeredPlot::CLayeredPlot()
{
	SetDefaults();
}

CLayeredPlot::~CLayeredPlot()
{

}

void	CLayeredPlot::SetDefaults()
{

}

void	CLayeredPlot::CopySettings(const CLayeredPlot *plot)
{

}

CPlotLayerImpl*		CLayeredPlot::GetLayer(int nIndex)
{
	if(nIndex<0 || nIndex>=(int)m_vpLayers.size())return NULL;
	return m_vpLayers[nIndex];
}