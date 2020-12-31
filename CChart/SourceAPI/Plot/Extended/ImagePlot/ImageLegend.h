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

#ifndef __IMAGELEGEND_H_122333444455555__
#define __IMAGELEGEND_H_122333444455555__

//#include "../../Basics/Origin.h"

class CImageLegend
{
public:
	CImageLegend();
	virtual ~CImageLegend();

	void		SetDefaults();
	void		CopySettings(const CImageLegend *legend);
protected:
	int			m_nLegends;
public:
	int			GetLegends(){return m_nLegends;}
	void		SetLegends(int num){if(num<2)return; m_nLegends = num;}
};

#endif