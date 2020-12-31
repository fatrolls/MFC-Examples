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
#include <math.h>
#include "AxisTDImpl.h"

CAxisTDImpl::CAxisTDImpl(CTDPlot *plot)
{

}

CAxisTDImpl::~CAxisTDImpl( )
{
	
}

// Returns the distance along the axis, in DATA UNITS
// where the requested tick mark lies
double		CAxisTDImpl::GetTickPosValue( int whichTick )
{
	double		range,pos,epsl=1.0e-12;
	
	// Assume user has checked the tick values first
	if( whichTick < 0 || (GetTickCount() > 0 && whichTick > GetTickCount()+1) )
		return 0.0;
	
	range = m_Range[1] - m_Range[0];
	
	if( GetTickCount() > 0 )
	{
		// User has specified number of ticks
		pos = m_Range[0] + range * (double)whichTick/((double)GetTickCount()+1.0);
		if(range!=0.0)
		{
			if(fabs(pos/range)<epsl)pos=0.0;
		}
	}
	else
	{
		// For now, just use four regions
		pos = m_Range[0] + range * (double)whichTick/((double)5.0);
		if(range!=0.0)
		{
			if(fabs(pos/range)<epsl)pos=0.0;
		}
	}
	
	return pos;
}