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

#include "StdAfx.h"
#include "TDLinePlot.h"
#include "../../Basics/XYPlot.h"
#include "../../Basics/PlotUtility.h"
#include "../TDPlot/TDPlot.h"

CTDLinePlot::CTDLinePlot()
{
	SetDefaults();
}

CTDLinePlot::~CTDLinePlot()
{
	DeleteAll();
}

void	CTDLinePlot::SetDefaults()
{
	m_nCurDataID = 0;

	m_bAutoDataColor = true;
	m_nModeOfSetColors = kSetColorFromTable;
	m_fvLineColor1[0] = 1.0f;
	m_fvLineColor1[1] = 0.0f;
	m_fvLineColor1[2] = 0.0f;
	m_fvLineColor2[0] = 0.0f;
	m_fvLineColor2[1] = 1.0f;
	m_fvLineColor2[2] = 1.0f;
}

void	CTDLinePlot::SetDefaults(int index)
{
	int			i = index;

	if( i < 0 || i >= m_vXYZDataInfo.size() ) return;

	m_vXYZDataInfo[i].bDataRangesSet = false;

	m_vXYZDataInfo[i].nPlotType = kTDPlotBezier;

	m_vXYZDataInfo[i].bMarkerShow = true;
	m_vXYZDataInfo[i].nMarkerSize = 2;

	m_vXYZDataInfo[i].fvDataColor[0] = 0.0f;
	m_vXYZDataInfo[i].fvDataColor[1] = 0.0f;
	m_vXYZDataInfo[i].fvDataColor[2] = 0.0f;
	m_vXYZDataInfo[i].fvPlotColor[0] = 0.0f;
	m_vXYZDataInfo[i].fvPlotColor[1] = 0.0f;
	m_vXYZDataInfo[i].fvPlotColor[2] = 0.0f;

	m_vXYZDataInfo[i].bAutoColor = true;
}

void	CTDLinePlot::CopySettings(CTDLinePlot *plot)
{

}

// Deletes a data set, and moves all the settings
// around in their arrays
bool	CTDLinePlot::DeleteData( int dataID )
{
	int count=m_vXYZDataInfo.size();
	for( int i = 0; i < count; i++ )
	{
		if( m_vXYZDataInfo[i].nDataID == dataID )
		{
			// Delete this data set
			m_vXYZDataInfo[i].pDataSet->DeleteData();
			// Free the object
			delete m_vXYZDataInfo[i].pDataSet;
			
			m_vXYZDataInfo.erase(m_vXYZDataInfo.begin()+i);
			return true;
		}
	}

	return false;
}

// Deletes every data set
void	CTDLinePlot::DeleteAllData( void )
{
	bool		keepGoing = true;

	while( keepGoing == true && m_vXYZDataInfo.size() > 0 )
	{
		keepGoing = DeleteData( GetDataID(0) );
	}
	//SetXAutoRange();
	//SetYAutoRange();
}

void	CTDLinePlot::DeleteAll( void )
{
	DeleteAllData();
}

int	CTDLinePlot::AddCurve( double *pX, double *pY, double *pZ, int nLen )
{
	if(!pX || !pY || !pZ || nLen<=0)return -1;
	MyVData3D vData;
	DataPoint3D dp;
	for(int i=0;i<nLen;i++)
	{
		dp.x = pX[i];
		dp.y = pY[i];
		dp.z = pZ[i];
		vData.push_back(dp);
	}
	return AddData(vData);
}

// Based on a dataID, get an index to the arrays
int		CTDLinePlot::GetIndex( int dataID ) const
{
	int			i;

	for( i = 0; i < m_vXYZDataInfo.size(); i++ )
	{
		if( m_vXYZDataInfo[i].nDataID == dataID )
		{
			return i;
		}
	}

	return -1;
}

// Returns the data set requested, or NULL if invalid
CPlotData<DataPoint3D>	*CTDLinePlot::GetAbsoluteDataSet( int which )
{
	CPlotData<DataPoint3D>		*plotData;

	if( which < 0 || which >= m_vXYZDataInfo.size() ) return NULL;

	plotData = m_vXYZDataInfo[which].pDataSet;

	return plotData;
}

// Sets up the data range variable for the
// specified data set
void	CTDLinePlot::GetDataRange( int dataID )
{
	int			i, j;
	double		minX, minY, minZ, maxX, maxY, maxZ;
	CPlotData<DataPoint3D>	*dataSet;

	i = GetIndex( dataID );
	if( i < 0 ) return;

	if( m_vXYZDataInfo[i].bDataRangesSet == false )
	{
		minX = 1e30; minY = 1e30; minZ = 1e30;
		maxX = -1e30; maxY = -1e30; maxZ = -1e30;
		m_vXYZDataInfo[i].bDataRangesSet = true;
		
		dataSet = GetAbsoluteDataSet( i );
		
		// Just find min and max of x
		for( j = 0; j < dataSet->GetData().size(); j++)
		{
			if( dataSet->GetData()[j].x < minX ) minX = dataSet->GetData()[j].x;
			if( dataSet->GetData()[j].x > maxX ) maxX = dataSet->GetData()[j].x;

			if( dataSet->GetData()[j].y < minY ) minY = dataSet->GetData()[j].y;
			if( dataSet->GetData()[j].y > maxY ) maxY = dataSet->GetData()[j].y;

			if( dataSet->GetData()[j].z < minZ ) minZ = dataSet->GetData()[j].z;
			if( dataSet->GetData()[j].z > maxZ ) maxZ = dataSet->GetData()[j].z;
		}
				
		m_vXYZDataInfo[i].fXDataMin = minX;
		m_vXYZDataInfo[i].fXDataMax = maxX;
		m_vXYZDataInfo[i].fYDataMin = minY;
		m_vXYZDataInfo[i].fYDataMax = maxY;
		m_vXYZDataInfo[i].fZDataMin = minZ;
		m_vXYZDataInfo[i].fZDataMax = maxZ;
	}
}

// Gets all data ranges, and sets up the data range
// variable for them
void	CTDLinePlot::GetDataRanges( void )
{
	for( int i = 0; i < m_vXYZDataInfo.size(); i++ )
	{
		GetDataRange( GetDataID(i) );
	}
}



void	CTDLinePlot::GetDataRanges(double xRange[2], double yRange[2], double zRange[2])
{
	GetDataRanges();

	xRange[0]=1e30;
	xRange[1]=-1e30;
	yRange[0]=1e30;
	yRange[1]=-1e30;
	zRange[0]=1e30;
	zRange[1]=-1e30;
	for( int i = 0; i < m_vXYZDataInfo.size(); i++ )
	{
		if(m_vXYZDataInfo[i].fXDataMin < xRange[0])xRange[0] = m_vXYZDataInfo[i].fXDataMin;
		if(m_vXYZDataInfo[i].fXDataMax > xRange[1])xRange[1] = m_vXYZDataInfo[i].fXDataMax;
		if(m_vXYZDataInfo[i].fYDataMin < yRange[0])yRange[0] = m_vXYZDataInfo[i].fYDataMin;
		if(m_vXYZDataInfo[i].fYDataMax > yRange[1])yRange[1] = m_vXYZDataInfo[i].fYDataMax;
		if(m_vXYZDataInfo[i].fZDataMin < zRange[0])zRange[0] = m_vXYZDataInfo[i].fZDataMin;
		if(m_vXYZDataInfo[i].fZDataMax > zRange[1])zRange[1] = m_vXYZDataInfo[i].fZDataMax;
	}
}

///Data management

int	CTDLinePlot::AddData( MyVData3D vData )
{
	CPlotData<DataPoint3D> *dataSet = new CPlotData<DataPoint3D>;
	
	int returnVal = dataSet->SetData( vData );
	if( returnVal == false ) return -1;

	// Now add this to our typed pointer array
	XYZDataInfo xyzdi;
	xyzdi.pDataSet = dataSet;
	xyzdi.nDataID	 = m_nCurDataID;
	m_vXYZDataInfo.push_back(xyzdi);
	SetDefaults( GetIndex( m_nCurDataID ) );
	GetDataRanges();
	m_nCurDataID++;

	return (m_nCurDataID -1);
}

void	CTDLinePlot::SetPlotColors()
{
	int nNum=m_vXYZDataInfo.size();
	for( int i = 0; i < nNum; i++ )
	{
		//Set color and line size
		if(m_bAutoDataColor && m_vXYZDataInfo[i].bAutoColor)
		{
			switch(m_nModeOfSetColors)
			{
			case kSetColorFromTwoColor:
				m_vXYZDataInfo[i].fvPlotColor[0] = ( m_fvLineColor1[0]*(nNum-i) + m_fvLineColor2[0] )/nNum;
				m_vXYZDataInfo[i].fvPlotColor[1] = ( m_fvLineColor1[1]*(nNum-i) + m_fvLineColor2[1] )/nNum;
				m_vXYZDataInfo[i].fvPlotColor[2] = ( m_fvLineColor1[2]*(nNum-i) + m_fvLineColor2[2] )/nNum;
				break;
			default:
				m_vXYZDataInfo[i].fvPlotColor[0] = GetRValue( colorTableForPlot[i%NUMOFCOLORS] )/255.0;
				m_vXYZDataInfo[i].fvPlotColor[1] = GetGValue( colorTableForPlot[i%NUMOFCOLORS] )/255.0;
				m_vXYZDataInfo[i].fvPlotColor[2] = GetBValue( colorTableForPlot[i%NUMOFCOLORS] )/255.0;
				break;
			}
		}
		else
		{
			memcpy(m_vXYZDataInfo[i].fvPlotColor, m_vXYZDataInfo[i].fvDataColor, 3*sizeof(GLfloat) );;
		}
	}
}