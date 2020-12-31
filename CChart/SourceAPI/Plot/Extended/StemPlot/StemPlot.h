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

#ifndef __STEMPLOT_H_122333444455555__
#define __STEMPLOT_H_122333444455555__

class	CStemPlot
{
public:
	CStemPlot();
	virtual ~CStemPlot();

	void	SetDefaults();
	void	CopySettings(CStemPlot *plot);
protected:
	int		m_nMaxDataSets;
	int		m_nMaxDataSetLen;
	double	m_fRatioOccupy;
public:
	inline	int		GetMaxDataSets() { return m_nMaxDataSets; }
	inline	void	SetMaxDataSets(int num) { if( num>0 )m_nMaxDataSets = num; }
	inline	int		GetMaxDataSetLen() { return m_nMaxDataSetLen; }
	inline	virtual	void	SetMaxDataSetLen(int len) { if( len>0 )m_nMaxDataSetLen = len; }
	inline	double	GetRatioOccupy() { return m_fRatioOccupy; }
	inline	void	SetRatioOccupy( double ratio ) { if(ratio<=0 || ratio>1)return; m_fRatioOccupy = ratio;}
};

#endif