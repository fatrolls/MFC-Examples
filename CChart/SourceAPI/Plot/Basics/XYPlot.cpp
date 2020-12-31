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

#include "Stdafx.h"
#include "XYPlot.h"

#include <fstream>

/////////////////////////////////////////////////////////////////////////
// Class CPlot

CXYPlot::CXYPlot()
{
	SetDefaults();
}

CXYPlot::~CXYPlot()
{
	DeleteAll();
}

void	CXYPlot::SetDefaults()
{
	m_nCurDataID = 0;

	m_bMultiSelect = false;
	m_nShowDataSetInfoMode = kShowDataSetInfoEveryN;
	m_nShowDataSetInfoNum = 1;
	m_nShowDataSetInfoDataPointStep = 32;
	
	m_bKeepFormer = true;

	m_bAutoLineStyle = true;
	
	m_bAutoDataColor = true;
	m_nModeOfSetColors = kSetColorFromTable;
	m_crLineColor1		= RGB(255,0,0);
	m_crLineColor2		= RGB(255,255,0);

	for( int i = 0; i< GetDataSetCount(); i++ )
	{
		SetDefaults( i );
	}
}

// Set the defaults for all the variables in an XY Plot
void	CXYPlot::SetDefaults( int index )
{
	int			i = index;

	if( i < 0 || i >= GetDataSetCount() ) return;

#ifdef DEFAULT_WHITE_BACKGROUND
	m_vXYDataInfo[i].crDataColor = RGB(0,0,0);
	m_vXYDataInfo[i].crPlotColor = RGB(0,0,0);
#else
	m_vXYDataInfo[i].crDataColor = RGB(255,255,255);
	m_vXYDataInfo[i].crPlotColor = RGB(255,255,255);
#endif
	m_vXYDataInfo[i].bAutoColor = true;
	m_vXYDataInfo[i].bDataRangesSet = false;

	m_vXYDataInfo[i].nMarkerType = kXYMarkerNone;
	m_vXYDataInfo[i].nMarkerSize = 4;
	m_vXYDataInfo[i].bMarkerFill = false;
	m_vXYDataInfo[i].nMarkerFrequency = -10;
	m_vXYDataInfo[i].nPlotType = kXYPlotConnect;

	m_vXYDataInfo[i].nDataLineSize = 1;
	m_vXYDataInfo[i].nPlotLineSize = 1;

	m_vXYDataInfo[i].nDataLineStyle = PS_SOLID;
	m_vXYDataInfo[i].nPlotLineStyle = PS_SOLID;
	m_vXYDataInfo[i].bAutoLineStyle = false;

	m_vXYDataInfo[i].nDataFillMode = kDataFillClosed;
	m_vXYDataInfo[i].bDataFill = false;
	m_vXYDataInfo[i].nDataFillBrushType = kBrushSolid;
	m_vXYDataInfo[i].crDataFillColor = RGB(240,240,168);
	m_vXYDataInfo[i].nDataFillHatchStyle = HS_CROSS;
	m_vXYDataInfo[i].hDataFillPattern = NULL;

	m_vXYDataInfo[i].bDataShow = true;
	m_vXYDataInfo[i].bSelected = false;
	m_vXYDataInfo[i].bLighted = false;

	SIZE size = {0,0};
	m_vXYDataInfo[i].sizeTitleOffset = size;

	m_vXYDataInfo[i].fScale = 1.0;
	m_vXYDataInfo[i].bDragMode = false;

	m_vXYDataInfo[i].bSpecialFlag = false;
}

// Copy the settings from one chart to another
void	CXYPlot::CopySettings( const CXYPlot *plot )
{
	// First copy the cplot
	//CPlot::CopySettings((const CPlot *)plot);

	// Then cxyplot
	m_nCurDataID = plot->m_nCurDataID;

	m_bMultiSelect					= plot->m_bMultiSelect;
	m_nShowDataSetInfoMode			= plot->m_nShowDataSetInfoMode;
	m_nShowDataSetInfoNum			= plot->m_nShowDataSetInfoNum;
	m_nShowDataSetInfoDataPointStep	= plot->m_nShowDataSetInfoDataPointStep;
	
	m_bKeepFormer					= plot->m_bKeepFormer;

	m_bAutoLineStyle				= plot->m_bAutoLineStyle;
	
	m_bAutoDataColor				= plot->m_bAutoDataColor;
	m_nModeOfSetColors				= plot->m_nModeOfSetColors;
	m_crLineColor1					= plot->m_crLineColor1;
	m_crLineColor2					= plot->m_crLineColor2;

	//if(plot->m_pLegend)m_pLegend->CopySettings(plot->m_pLegend);
}

void	CXYPlot::CopyAll( const CXYPlot *plot )
{
	int	i;

	DeleteAllData();
	for( i=0; i<plot->GetDataSetCount(); i++ )
	{
		AddData(plot->GetAbsoluteData(i));
		m_vXYDataInfo[i].pDataSet->CopySettings(plot->m_vXYDataInfo[i].pDataSet);
	}

	for( i = 0; i < GetDataSetCount(); i++ )
	{
		m_vXYDataInfo[i].nDataID = plot->m_vXYDataInfo[i].nDataID;
		m_vXYDataInfo[i].crDataColor = plot->m_vXYDataInfo[i].crDataColor;
		m_vXYDataInfo[i].crPlotColor = plot->m_vXYDataInfo[i].crPlotColor;
		m_vXYDataInfo[i].bAutoColor = plot->m_vXYDataInfo[i].bAutoColor;
		m_vXYDataInfo[i].bDataRangesSet = plot->m_vXYDataInfo[i].bDataRangesSet;

		m_vXYDataInfo[i].nMarkerType = plot->m_vXYDataInfo[i].nMarkerType;
		m_vXYDataInfo[i].nMarkerSize = plot->m_vXYDataInfo[i].nMarkerSize;
		m_vXYDataInfo[i].bMarkerFill = plot->m_vXYDataInfo[i].bMarkerFill;
		m_vXYDataInfo[i].nMarkerFrequency = plot->m_vXYDataInfo[i].nMarkerFrequency;
		m_vXYDataInfo[i].nPlotType = plot->m_vXYDataInfo[i].nPlotType;

		m_vXYDataInfo[i].nDataLineSize = plot->m_vXYDataInfo[i].nDataLineSize;
		m_vXYDataInfo[i].nDataLineStyle = plot->m_vXYDataInfo[i].nDataLineStyle;
		m_vXYDataInfo[i].nPlotLineStyle = plot->m_vXYDataInfo[i].nPlotLineStyle;
		m_vXYDataInfo[i].bAutoLineStyle = plot->m_vXYDataInfo[i].bAutoLineStyle;

		m_vXYDataInfo[i].bDataShow = plot->m_vXYDataInfo[i].bDataShow;
		m_vXYDataInfo[i].bSelected = plot->m_vXYDataInfo[i].bSelected;
		m_vXYDataInfo[i].bLighted = plot->m_vXYDataInfo[i].bLighted;

		m_vXYDataInfo[i].nDataFillMode = plot->m_vXYDataInfo[i].nDataFillMode;
		m_vXYDataInfo[i].bDataFill = plot->m_vXYDataInfo[i].bDataFill;
		m_vXYDataInfo[i].nDataFillBrushType = plot->m_vXYDataInfo[i].nDataFillBrushType;
		m_vXYDataInfo[i].crDataFillColor = plot->m_vXYDataInfo[i].crDataFillColor;
		m_vXYDataInfo[i].nDataFillHatchStyle = plot->m_vXYDataInfo[i].nDataFillHatchStyle;
		if(m_vXYDataInfo[i].hDataFillPattern)DeleteObject(m_vXYDataInfo[i].hDataFillPattern);
		m_vXYDataInfo[i].hDataFillPattern = plot->m_vXYDataInfo[i].hDataFillPattern;

		m_vXYDataInfo[i].bSpecialFlag = plot->m_vXYDataInfo[i].bSpecialFlag;

		m_vXYDataInfo[i].sizeTitleOffset = plot->m_vXYDataInfo[i].sizeTitleOffset;
		m_vXYDataInfo[i].fScale = plot->m_vXYDataInfo[i].fScale;

		m_vXYDataInfo[i].bDragMode = plot->m_vXYDataInfo[i].bDragMode;

	}
	
	CopySettings(plot);
}

// Deletes a data set, and moves all the settings
// around in their arrays
bool	CXYPlot::DeleteData( int dataID )
{
	int count=GetDataSetCount();
	for( int i = 0; i < count; i++ )
	{
		if( m_vXYDataInfo[i].nDataID == dataID )
		{
			// Delete this data set
			m_vXYDataInfo[i].pDataSet->DeleteData();
			// Free the object
			delete m_vXYDataInfo[i].pDataSet;
			// Free the handle of bitmap for brush pattern
			if(m_vXYDataInfo[i].hDataFillPattern)DeleteObject(m_vXYDataInfo[i].hDataFillPattern);

			m_vXYDataInfo.erase(m_vXYDataInfo.begin()+i);
			return true;
		}
	}

	return false;
}

// Deletes every data set
void	CXYPlot::DeleteAllData( void )
{
	bool		keepGoing = true;

	while( keepGoing == true && GetDataSetCount() > 0 )
	{
		keepGoing = DeleteData( GetDataID(0) );
	}
	SetSpecialFlag(false);
	//SetXAutoRange();
	//SetYAutoRange();
}

void	CXYPlot::DeleteAll( void )
{
	DeleteAllData();
}

int	CXYPlot::AddCurve( double *pX, double *pY, int nLen )
{
	if(!pX || !pY || nLen<=0)return -1;
	MyVData2D vData;
	DataPoint2D dp;
	for(int i=0;i<nLen;i++)
	{
		dp.x=pX[i];
		dp.y=pY[i];
		vData.push_back(dp);
	}
	return AddCurve(vData);
}

int CXYPlot::AddDataSet(MyVData2D vData,int charttype,COLORREF color,int markertype,int markerfreq)
{
	if(vData.size()<=0)return -1;

	if(!m_bKeepFormer)DeleteAllData();

	int		dataID = AddData( vData );
	if(dataID<0)return -1;

	SetPlotType(dataID,charttype);
	SetMarkerType(dataID,markertype);
	SetMarkerFrequency( dataID, markerfreq );
	SetDataColor(dataID,color);	

	return dataID;
}

string		CXYPlot::GetDataTitle( int dataID )
{
	int i = GetIndex(dataID);
	if( i < 0 ) return "";
	else return m_vXYDataInfo[i].pDataSet->GetTitle();
}

void		CXYPlot::SetDataTitle( int dataID, string title )
{
	int index = GetIndex( dataID );
	if( index < 0 || index >= GetDataSetCount() ) return;
	m_vXYDataInfo[index].pDataSet->SetTitle( title );
}

// Based on a dataID, get an index to the arrays
int		CXYPlot::GetIndex( int dataID ) const
{
	int			i;

	for( i = 0; i < GetDataSetCount(); i++ )
	{
		if( m_vXYDataInfo[i].nDataID == dataID )
		{
			return i;
		}
	}

	return -1;
}

const MyVData2D &CXYPlot::GetData( int dataID ) const
{
	int index=GetIndex(dataID);
	if(index<0)index=0;
	return m_vXYDataInfo[index].pDataSet->GetDataConst();
}

const MyVData2D &CXYPlot::GetAbsoluteData( int which ) const
{
	if(which<0 || which>GetDataSetCount())which=0;
	return m_vXYDataInfo[which].pDataSet->GetDataConst();
}

// Returns the data set requested, or NULL if invalid
CPlotData<DataPoint2D>	*CXYPlot::GetAbsoluteDataSet( int which )
{
	CPlotData<DataPoint2D>		*plotData;

	if( which < 0 || which >= GetDataSetCount() ) return NULL;

	plotData = m_vXYDataInfo[which].pDataSet;

	return plotData;
}

string		CXYPlot::GetAbsoluteDataTitle( int which )
{
	CPlotData<DataPoint2D>		*plotData = GetAbsoluteDataSet( which );
	
	if(!plotData)
		return "";
	else
		return plotData->GetTitle();
}

CPlotData<DataPoint2D>	*CXYPlot::GetDataSet( int dataID )
{
	int		i = GetIndex( dataID );

	if( i >= 0 ) return GetAbsoluteDataSet( i ); else return NULL;
}

// Sets up the data range variable for the
// specified data set
void	CXYPlot::GetDataRange( int dataID )
{
	int			i, j;
	double		minX, minY, maxX, maxY;
	CPlotData<DataPoint2D>	*dataSet;

	i = GetIndex( dataID );
	if( i < 0 ) return;

	if( m_vXYDataInfo[i].bDataRangesSet == false )
	{
		minX = 1e30; minY = 1e30;
		maxX = -1e30; maxY = -1e30;
		m_vXYDataInfo[i].bDataRangesSet = true;
		
		dataSet = GetAbsoluteDataSet( i );
		
		// Just find min and max of x
		for( j = 0; j < dataSet->GetDataSize(); j++)
		{
			if( dataSet->GetData()[j].x < minX ) minX = dataSet->GetData()[j].x;
			if( dataSet->GetData()[j].x > maxX ) maxX = dataSet->GetData()[j].x;

			if( dataSet->GetData()[j].y < minY ) minY = dataSet->GetData()[j].y;
			if( dataSet->GetData()[j].y > maxY ) maxY = dataSet->GetData()[j].y;
		}
				
		m_vXYDataInfo[i].fXDataMin = minX;
		m_vXYDataInfo[i].fXDataMax = maxX;
		m_vXYDataInfo[i].fYDataMin = minY;
		m_vXYDataInfo[i].fYDataMax = maxY;
	}
}

// Gets all data ranges, and sets up the data range
// variable for them
void	CXYPlot::GetDataRanges( void )
{
	for( int i = 0; i < GetDataSetCount(); i++ )
	{
		GetDataRange( GetDataID(i) );
	}
}

void	CXYPlot::GetDataRanges(double xRange[2], double yRange[2])
{
	GetDataRanges();

	xRange[0]=1e30;
	xRange[1]=-1e30;
	yRange[0]=1e30;
	yRange[1]=-1e30;
	for( int i = 0; i < GetDataSetCount(); i++ )
	{
		if(m_vXYDataInfo[i].fXDataMin < xRange[0])xRange[0] = m_vXYDataInfo[i].fXDataMin;
		if(m_vXYDataInfo[i].fXDataMax > xRange[1])xRange[1] = m_vXYDataInfo[i].fXDataMax;
		if(m_vXYDataInfo[i].fYDataMin < yRange[0])yRange[0] = m_vXYDataInfo[i].fYDataMin;
		if(m_vXYDataInfo[i].fYDataMax > yRange[1])yRange[1] = m_vXYDataInfo[i].fYDataMax;
	}
}

///Data management

int	CXYPlot::AddData( MyVData2D vData )
{
	CPlotData<DataPoint2D> *dataSet = new CPlotData<DataPoint2D>;
	
	int returnVal = dataSet->SetData( vData );
	if( returnVal == false ) return -1;

	// Now add this to our typed pointer array
	XYDataInfo xydi;
	xydi.pDataSet = dataSet;
	xydi.nDataID	 = m_nCurDataID;
	m_vXYDataInfo.push_back(xydi);
	SetDefaults( GetIndex( m_nCurDataID ) );
	GetDataRanges();
	m_nCurDataID++;

	return (m_nCurDataID -1);

}

int	CXYPlot::SetData( int dataID, MyVData2D vData )
{
	int index = GetIndex( dataID );
	if( index >= GetDataSetCount() || index < 0 ) return -1;

	if( m_vXYDataInfo[index].pDataSet->SetData( vData ) )
	{
		m_vXYDataInfo[index].bDataRangesSet = false;
		GetDataRange(dataID);
		return dataID;
	}
	else
		return -1;
}

bool	CXYPlot::SetDataModified( int dataID )
{
	if( dataID < 0 )
	{
		GetDataRanges();
		// all have been modified
	}
	else
	{
		m_vXYDataInfo[GetIndex(dataID)].bDataRangesSet=false;
		GetDataRange( dataID );
		// one has been modified
	}

	return true;
}

bool	CXYPlot::WriteToFile( string pathName )
{
	//FILE*				fp;
	ofstream			ofs;
	int					whichDataSet;
	CPlotData<DataPoint2D>		*dataSet;
	
	if( GetDataSetCount() <= 0 ) return false;

	
	ofs.open(pathName.c_str(),ios::app);
	if(!ofs.is_open())return false;

	for( whichDataSet = 0; whichDataSet < GetDataSetCount(); whichDataSet++ )
	{
		dataSet = GetAbsoluteDataSet(whichDataSet);
		
		if( dataSet == NULL ) continue;
		if(!dataSet->WriteToFile(ofs))
		{
			ofs.close();
			return false;
		}
		if( whichDataSet != GetDataSetCount() - 1 )
		{
			//fwrite("\r\n",strlen("\r\n"),1,fp);
			ofs.write("\r\n",strlen("\r\n"));
		}
	}
	ofs.close();
/*
	fp = fopen( pathName.c_str(), "a+" );
	if(!fp)	return false;
	
	for( whichDataSet = 0; whichDataSet < GetDataSetCount(); whichDataSet++ )
	{
		dataSet = GetAbsoluteDataSet(whichDataSet);
		
		if( dataSet == NULL ) continue;
		if(!dataSet->WriteToFile(fp))
		{
			fclose(fp);
			return false;
		}
		if( whichDataSet != GetDataSetCount() - 1 )
		{
			fwrite("\r\n",strlen("\r\n"),1,fp);
		}
	}
	
	fclose(fp);*/
	return true;
}

bool	CXYPlot::WriteToFile( int which, string pathName )
{
	if( which < 0 || which >= GetDataSetCount() ) return false;
	
	CPlotData<DataPoint2D>		*dataSet = GetAbsoluteDataSet(which);
	
	if( dataSet == NULL ) return false;
	
	if(!dataSet->WriteToFile(pathName))return false;
	
	return true;
}

bool	CXYPlot::ReadFromFile( string pathName )
{
	CPlotData<DataPoint2D> dataSet;
	if( !dataSet.ReadFromFile( pathName ) )return false;
	
	int dataID = AddData(dataSet.GetData());
	SetDataTitle( dataID, dataSet.GetTitle() );
	
	return true;
}

bool	CXYPlot::ReadFromFile( int which, string pathName )
{
	if( which < 0 || which >= GetDataSetCount() ) return false;
	
	CPlotData<DataPoint2D>	*dataSet = GetAbsoluteDataSet(which);
	if( dataSet == NULL ) return false;
	
	if( !dataSet->ReadFromFile( pathName ) )return false;
	SetDataModified( GetDataID( which ) );
	
	return true;
}

int		CXYPlot::GetLineWidth(int linewidth, bool bLighted, bool bSelected)
{
	if(linewidth <= 0)
		linewidth =1;
	if(bSelected)
		return linewidth + 2;
	else if(bLighted)
		return linewidth + 1;
	else
		return linewidth;
}

COLORREF	CXYPlot::GetLineColor(COLORREF linecolor, bool bLighted, bool bSelected)
{
	if(bSelected)
		return RGB((GetRValue(linecolor)+255)/2,GetGValue(linecolor),(GetBValue(linecolor)+255)/2);
	else if(bLighted)
		return RGB((GetRValue(linecolor)+255)/2,(GetGValue(linecolor)+255)/2,GetBValue(linecolor));
	else
		return linecolor;
}

void	CXYPlot::SetPlotColors()
{
	int nNum=GetDataSetCount();
	short r,g,b;
	for( int i = 0; i < nNum; i++ )
	{
		//Set color and line size
		if(m_bAutoDataColor && m_vXYDataInfo[i].bAutoColor)
		{
			switch(m_nModeOfSetColors)
			{
			case kSetColorFromTwoColor:
				r= ( GetRValue(m_crLineColor1)*(nNum-i) + GetRValue(m_crLineColor2) )/nNum;
				g= ( GetGValue(m_crLineColor1)*(nNum-i) + GetGValue(m_crLineColor2) )/nNum;
				b= ( GetBValue(m_crLineColor1)*(nNum-i) + GetBValue(m_crLineColor2) )/nNum;
				m_vXYDataInfo[i].crPlotColor=RGB(r,g,b);
				break;
			default:
				m_vXYDataInfo[i].crPlotColor=colorTableForPlot[i%NUMOFCOLORS];
				break;
			}
		}
		else
		{
			m_vXYDataInfo[i].crPlotColor=m_vXYDataInfo[i].crDataColor;
		}
		m_vXYDataInfo[i].crPlotColor = GetLineColor(m_vXYDataInfo[i].crPlotColor, m_vXYDataInfo[i].bLighted, m_vXYDataInfo[i].bSelected);
	}
}

void	CXYPlot::SetPlotLineStyles()
{
	for( int i = 0; i < GetDataSetCount(); i++ )
	{
		if(m_bAutoLineStyle && m_vXYDataInfo[i].bAutoLineStyle)
			m_vXYDataInfo[i].nPlotLineStyle=i%5;
		else
			m_vXYDataInfo[i].nPlotLineStyle=m_vXYDataInfo[i].nDataLineStyle;
	}
}

void	CXYPlot::SetPlotLineSizes()
{
	for( int i = 0; i < GetDataSetCount(); i++ )
	{
		m_vXYDataInfo[i].nPlotLineSize = GetLineWidth(m_vXYDataInfo[i].nDataLineSize, m_vXYDataInfo[i].bLighted, m_vXYDataInfo[i].bSelected);
	}
}