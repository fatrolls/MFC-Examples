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
#include "RealtimePlot.h"

CRealtimePlot::CRealtimePlot()
{
	m_fTimeSpan = 10;
	m_nTimePeriod = 50;

	m_bHoldXValue = true;
		
	m_nDatas = 0;
}

CRealtimePlot::~CRealtimePlot()
{

}
