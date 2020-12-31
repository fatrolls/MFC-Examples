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

#include "Stdafx.h"
#include "RealtimeDemo.h"

CRealtimeDemo::CRealtimeDemo()
{
	m_bRun = false;

	m_nTimeResolution = 1 ;
}

CRealtimeDemo::~CRealtimeDemo()
{

}

void	CRealtimeDemo::SetDefaults()
{
}

void	CRealtimeDemo::CopySettings(CRealtimeDemo *demo)
{
}