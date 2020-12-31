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

#ifndef __SPLINEPlOT_32167_H__
#define __SPLINEPlOT_32167_H__

class CSplinePlot
{
public:
	CSplinePlot();
	virtual ~CSplinePlot();

	void	SetDefaults();
	void	CopySettings(CSplinePlot *plot);

};

#endif