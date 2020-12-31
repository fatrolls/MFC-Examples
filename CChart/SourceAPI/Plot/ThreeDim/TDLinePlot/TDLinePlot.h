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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Three Dimension plot use the OpenGL API to draw on the screen

#ifndef __TDLINEPLOT_H_122333444455555__
#define __TDLINEPLOT_H_122333444455555__

#include "../../Basics/PlotData.h"
#include "gl/gl.h"

enum
{
	kTDPlotScatter,
	kTDPlotConnected,
	kTDPlotBezier,

	kTDPlotCount
};

typedef struct stXYZDataInfo
{
	CPlotData<DataPoint3D>	*pDataSet;
	int			nDataID;

	int			nPlotType;

	GLfloat		fvDataColor[3];
	GLfloat		fvPlotColor[3]; // An RGB value
	bool		bAutoColor; // Let the program choose color

	bool		bMarkerShow;
	int			nMarkerSize;

	double		fXDataMin;
	double		fXDataMax;
	double		fYDataMin;
	double		fYDataMax;
	double		fZDataMin;
	double		fZDataMax;
	bool		bDataRangesSet;
}XYZDataInfo;
typedef vector<XYZDataInfo> vXYZDataInfo;

class CTDLinePlot
{
public:
	CTDLinePlot();
	~CTDLinePlot();

	void		SetDefaults();
	void		SetDefaults(int index);
	void		CopySettings(CTDLinePlot *plot);

	bool		DeleteData( int dataID );
	void		DeleteAllData( void );
	void		DeleteAll( void );

	bool		SetDataModified( int dataID );
public:
	int			AddCurve( double *pX, double *pY, double *pZ, int nLen );
protected:
	vXYZDataInfo	m_vXYZDataInfo;
	int				m_nCurDataID;

	bool		m_bAutoDataColor;
	int			m_nModeOfSetColors;
	GLfloat		m_fvLineColor1[3];
	GLfloat		m_fvLineColor2[3];

public:
	int			GetDataID( int index) const{if(index<0 || index>=m_vXYZDataInfo.size())return -1;else return m_vXYZDataInfo[index].nDataID;};
	int			GetIndex( int dataID ) const;

	void		GetDataRange( int dataID );
	void		GetDataRanges();
	void		GetDataRanges(double xRange[2], double yRange[2], double zRange[2]);

	virtual CPlotData<DataPoint3D>	*GetAbsoluteDataSet( int which );
public:
	//void		GetPlotRange( double *xRange, double *yRange, double *zRange );
	

protected:

	void	SetPlotColors();
private:
	int		AddData( MyVData3D vData );
	
};

#endif