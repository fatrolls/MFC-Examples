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

#ifndef __COUNTOURLINEPLOT_H_122333444455555__
#define __COUNTOURLINEPLOT_H_122333444455555__
//
class CListContour;

class CContourLinePlot
{
public:
	CContourLinePlot();
	virtual ~CContourLinePlot();
protected:
	CListContour* m_pListContour;
public:
	CListContour* GetContour()
	{
		return m_pListContour;
	}
	void SetFieldFcn(double (*_pFieldFcn) (double, double));//{m_listContour.SetFieldFcn(_pFieldFcn);}
	void SetPlotRange(double pRange[4]);
};

#endif