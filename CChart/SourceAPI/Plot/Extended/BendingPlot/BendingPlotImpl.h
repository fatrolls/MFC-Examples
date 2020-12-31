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

#ifndef __BENDINGPLOTIMPL_H_122333444455555__
#define __BENDINGPLOTIMPL_H_122333444455555__

#include "BendingPlot.h"
#include "../../Basics/XYPlotImpl.h"
#include "../../Basics/XYHandler.h"

class CBendingPlotImpl : public CBendingPlot, public CXYPlotImpl
{
public:
	CBendingPlotImpl();
	virtual	~CBendingPlotImpl();

public:
	void	InitBendingAxis();
	
public:
	int		AddCurve( double *pX, double *pY, int nLen );
};

class CBendingPlotImplI : public CBendingPlotImpl, public CXYHandler<CBendingPlotImplI>
{

};

#endif