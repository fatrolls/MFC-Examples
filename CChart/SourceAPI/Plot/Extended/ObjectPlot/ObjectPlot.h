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

#ifndef __OBJECTPLOT_H_122333444455555__
#define __OBJECTPLOT_H_122333444455555__

#include <vector>
using namespace std;

typedef struct stMetaObject
{
	int			nCode;// 1: Line; 2: Rectangle; 3: Ellipse; 4: Circle
	double		fX1;
	double		fY1;
	bool		bData1;
	double		fX2;
	double		fY2;
	bool		bData2;

	double		fCtX;
	double		fCtY;
	bool		bDataCT;
	double		fRx;
	bool		bDataX;
	double		fRy;
	bool		bDataY;

	double		fRadius;
	bool		bDataR;
	bool		bDataRX;

	int			nLineStyle;
	int			nLineWidth;
	COLORREF	crLineColor;
	bool		bFill;
	COLORREF	crFillColor;
	bool		bLighted;
	bool		bSelected;
}MetaObject;

class CObjectPlot
{
public:
	CObjectPlot();
	virtual ~CObjectPlot();


	vector<MetaObject>		m_vMetaObjects;
	void	LightMetaObject(int index, bool bLight);
	void	UnlightAllMetaObjects();
	void	SelectMetaObject(int index, bool bSelect);
	void	UnselectAllMetaObjects();

public:
	void	ClearMetaObjects(){ m_vMetaObjects.clear(); }
	vector<MetaObject> &GetMetaObjects(){ return m_vMetaObjects; }

	void	AddLine(double x1, double y1, bool bData1, double x2, double y2, bool bData2, int linestyle, int linewidth, COLORREF color);
	void	AddRectangle(double x1, double y1, bool bData1, double x2, double y2, bool bData2, int linestyle, int linewidth, COLORREF linecolor, bool bFill, COLORREF fillcolor);
	void	AddEllipse(double ctx, double cty, bool bDataCT, double rx, bool bDataX, double ry, bool bDataY, int linestyle, int linewidth, COLORREF linecolor, bool bFill, COLORREF fillcolor);
	void	AddCircle(double ctx, double cty, bool bDataCT, double radius, bool bDataR, bool bDataRX, int linestyle, int linewidth, COLORREF linecolor, bool bFill, COLORREF fillcolor);
};

#endif