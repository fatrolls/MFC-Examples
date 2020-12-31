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

#ifndef __AXISTDIMPL_H_122333444455555__
#define __AXISTDIMPL_H_122333444455555__

#include "../../Basics/Axis.h"
#include "TDPlot.h"

class CAxisTDImpl : public CAxis
{
public:
	CAxisTDImpl(CTDPlot	*plot);
	virtual ~CAxisTDImpl();

public:
	double		GetTickPosValue( int whichTick );
};

#endif