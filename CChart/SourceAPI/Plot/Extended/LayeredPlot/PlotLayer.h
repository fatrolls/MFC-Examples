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

#ifndef __PLOTLAYER_H_122333444455555__
#define __PLOTLAYER_H_122333444455555__

class CPlotLayer
{
protected:
	RECT m_LastPlotRect;
public:
	CPlotLayer();
	virtual ~CPlotLayer();
	virtual CPlotLayer& operator=(const CPlotLayer& rhs);

	void		SetDefaults();
	void		CopySettings(const CPlotLayer *plot);
};


#endif