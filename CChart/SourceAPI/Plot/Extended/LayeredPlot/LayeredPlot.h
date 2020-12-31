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

#ifndef __LAYEREDPLOT_H_122333444455555__
#define __LAYEREDPLOT_H_122333444455555__

class CPlotLayerImpl;
class CLayeredLegend;

class CLayeredPlot
{
public:
	CLayeredPlot();
	virtual ~CLayeredPlot();

	void		SetDefaults();
	void		CopySettings(const CLayeredPlot *plot);
	
	CPlotLayerImpl*		GetLayer(int nIndex);

protected:
	vector<CPlotLayerImpl*>	m_vpLayers;
};


#endif