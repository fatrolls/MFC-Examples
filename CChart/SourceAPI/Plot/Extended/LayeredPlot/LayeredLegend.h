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

#ifndef __LAYEREDLEGEND_H_122333444455555__
#define __LAYEREDLEGEND_H_122333444455555__

class CLayeredLegend
{
public:
	CLayeredLegend();
	virtual ~CLayeredLegend();

	void		SetDefaults();
	void		CopySettings(const CLayeredLegend *legend);
};

#endif