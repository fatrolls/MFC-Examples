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
#include "ImageLegend.h"

CImageLegend::CImageLegend()
{
	SetDefaults();
}

CImageLegend::~CImageLegend()
{
}

void CImageLegend::SetDefaults()
{
	m_nLegends = 5;
}

void CImageLegend::CopySettings(const CImageLegend* legend)
{
	m_nLegends = legend->m_nLegends;
}
