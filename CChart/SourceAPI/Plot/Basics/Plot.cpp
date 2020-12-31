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

#include "stdafx.h"
#include "Plot.h"
#include "Axis.h"
#include "Legend.h"

/////////////////////////////////////////////////////////////////////////
// Class CPlot static members

bool CPlot::m_bNewInteractive=true;

/////////////////////////////////////////////////////////////////////////
// Class CPlot

CPlot::CPlot()
{
	for( int i = 0; i < kMaxAxes; i++ ) 
	{
		m_pAxes[i] = NULL;
	}
	m_pLegend = NULL;
	m_hBkgndPattern = NULL;
	m_hDataRegionPattern = NULL;

	SetDefaults();
}

CPlot::~CPlot()
{
	DeleteAll();
}

void	CPlot::SetDefaults()
{
	m_bUseMajorHGrids = false;
	m_bUseMajorVGrids = false;
	m_bUseMinorHGrids = false;
	m_bUseMinorVGrids = false;

	m_strTitle = "";

	m_strSubtitle="Subtitle";
	m_bSubtitleShow=false;
	m_sizeSubtitleOffset.cx=m_sizeSubtitleOffset.cy=0;

#ifndef	DEFAULT_WHITE_BACKGROUND
	// Default is black background
	m_crBkgndColor = RGB( 0, 0, 0 );
	m_crBorderColor = RGB( 255, 255, 255 );
	m_crTitleColor = RGB( 255, 255, 255 );
	m_crSubtitleColor = RGB( 128, 0, 255 );
#else
	m_crBkgndColor = RGB( 255, 255, 255 );
	m_crBorderColor = RGB( 0, 0, 0 );
	m_crTitleColor = RGB( 0, 0, 0 );
	m_crSubtitleColor = RGB( 255, 0, 128 );
#endif

	m_crMajorGridColor = RGB( 128, 128, 128 );
	m_crMinorGridColor = m_crMajorGridColor;

	m_nMajorGridLineSize = 1;
	m_nMinorGridLineSize = 1;

	m_nMajorGridLineStyle = PS_SOLID;
	m_nMinorGridLineStyle = PS_DOT;

	m_nBorderSize = 1;
	m_nBorderStyle = PS_SOLID;
	m_crBorderColor = RGB(128,0,0);

	m_nMarginLeft = 0;
	m_nMarginRight = 0;
	m_nMarginTop = 0;
	m_nMarginBottom = 0;

	m_nAxisCount = 0;
	m_bEqualXYRange = false;
	m_bEqualXYAxis = false;

	m_bEraseBkgnd = true;
	m_nBkgndBrushType = kBrushSolid;
	m_nBkgndHatchStyle = HS_CROSS;
	if(m_hBkgndPattern)
	{
		DeleteObject(m_hBkgndPattern);
		m_hBkgndPattern = NULL;
	}

	m_nDataRegionBrushType = kBrushSolid;
	m_nDataRegionHatchStyle = HS_CROSS;
	if(m_hDataRegionPattern)
	{
		DeleteObject(m_hDataRegionPattern);
		m_hDataRegionPattern = NULL;
	}
	m_bUseDataRegionBrush = true;
	m_crDataRegionColor = m_crBkgndColor;//RGB( 244, 244, 244 );

	m_bGradientBkgnd = false;
	m_bGradientHorizontal = false;
	m_crGradientColor1 = RGB(225,225,225);
	m_crGradientColor2 = RGB(255,255,255);

	m_bLightTitle = false;
	m_bLightDataRegion = false;
	m_crLightColor = RGB(128,64,192);
	m_nLightLineSize = 2;
	m_nLightLineStyle = PS_SOLID;

	m_bUseLegend= false;
	if(m_pLegend)DeleteLegend();;

	DeleteAllAxes();

	HFONT	hFont=CreateFont(36, 0, 0, 0, FW_BOLD, FALSE, FALSE, 0,
		ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH | FF_ROMAN,"Arial");
	GetObject(hFont,sizeof(LOGFONT),&m_lfTitleFont);
	GetObject(hFont,sizeof(LOGFONT),&m_lfSubtitleFont);
	DeleteObject(hFont);

	SetRectEmpty(&m_rctLastClientRect);
}

void	CPlot::CopySettings(const CPlot *plot)
{
	m_bUseMajorHGrids				= plot->m_bUseMajorHGrids;
	m_bUseMajorVGrids				= plot->m_bUseMajorVGrids;
	m_bUseMinorHGrids				= plot->m_bUseMinorHGrids;
	m_bUseMinorVGrids				= plot->m_bUseMinorVGrids;
	m_crMajorGridColor				= plot->m_crMajorGridColor;
	m_crMinorGridColor				= plot->m_crMinorGridColor;
	m_nMajorGridLineSize			= plot->m_nMajorGridLineSize;
	m_nMinorGridLineSize			= plot->m_nMinorGridLineSize;
	m_nMajorGridLineStyle			= plot->m_nMajorGridLineStyle;
	m_nMinorGridLineStyle			= plot->m_nMinorGridLineStyle;

	m_nAxisCount					= plot->m_nAxisCount;
	DeleteAllAxes();
	for(int i=0;i<m_nAxisCount;i++)
	{
		m_pAxes[i]=NewAxis();
		m_pAxes[i]->CopySettings(plot->m_pAxes[i]);
	}

	if(plot->m_pLegend)
	{
		if(!m_pLegend)m_pLegend=NewLegend();
		m_pLegend->CopySettings(plot->m_pLegend);
	}

	m_strTitle						= plot->m_strTitle;
	m_lfTitleFont					= plot->m_lfTitleFont;
	m_crTitleColor					= plot->m_crTitleColor;

	m_strSubtitle					= plot->m_strSubtitle;
	m_lfSubtitleFont				= plot->m_lfSubtitleFont;
	m_crSubtitleColor				= plot->m_crSubtitleColor;
	m_bSubtitleShow					= plot->m_bSubtitleShow;
	m_sizeSubtitleOffset			= plot->m_sizeSubtitleOffset;

	
	m_crBkgndColor					= plot->m_crBkgndColor;
	m_crBorderColor					= plot->m_crBorderColor;
	m_nBorderSize					= plot->m_nBorderSize;
	m_nBorderStyle					= plot->m_nBorderStyle;

	m_bUseDataRegionBrush			= plot->m_bUseDataRegionBrush;
	m_crDataRegionColor				= plot->m_crDataRegionColor;

	m_bGradientBkgnd				= plot->m_bGradientBkgnd;
	m_bGradientHorizontal			= plot->m_bGradientHorizontal;
	m_crGradientColor1				= plot->m_crGradientColor1;
	m_crGradientColor2				= plot->m_crGradientColor2;

	m_bLightTitle					= plot->m_bLightTitle;
	m_bLightDataRegion				= plot->m_bLightDataRegion;
	m_crLightColor					= plot->m_crLightColor;
	m_nLightLineSize				= plot->m_nLightLineSize;
	m_nLightLineStyle				= plot->m_nLightLineStyle;

	m_nMarginLeft					= plot->m_nMarginLeft;
	m_nMarginRight					= plot->m_nMarginRight;
	m_nMarginTop					= plot->m_nMarginTop;
	m_nMarginBottom					= plot->m_nMarginBottom;

	m_bEraseBkgnd					= plot->m_bEraseBkgnd;
	m_nBkgndBrushType				= plot->m_nBkgndBrushType;
	m_nBkgndHatchStyle				= plot->m_nBkgndHatchStyle;
	if(m_hBkgndPattern)DeleteObject(m_hBkgndPattern);
	m_hBkgndPattern					= plot->m_hBkgndPattern;

	m_nDataRegionBrushType			= plot->m_nDataRegionBrushType;
	m_nDataRegionHatchStyle			= plot->m_nDataRegionHatchStyle;
	if(m_hDataRegionPattern)DeleteObject(m_hDataRegionPattern);
	m_hDataRegionPattern			= plot->m_hDataRegionPattern;

	m_bEqualXYRange					= plot->m_bEqualXYRange;
	m_bEqualXYAxis					= plot->m_bEqualXYAxis;

	m_bUseLegend					= plot->m_bUseLegend;

	//m_pFcnDS						= plot->m_pFcnDS;
	//m_pFcnAS						= plot->m_pFcnAS;
	//m_pFcnPS						= plot->m_pFcnPS;
}

void	CPlot::DeleteAll()
{
	DeleteAllAxes();
	DeleteLegend();
	DeleteUsedHandles();
}

void	CPlot::DeleteUsedHandles()
{
	if(m_hBkgndPattern)
	{
		DeleteObject(m_hBkgndPattern);
		m_hBkgndPattern = NULL;
	}
	if(m_hDataRegionPattern)
	{
		DeleteObject(m_hDataRegionPattern);
		m_hDataRegionPattern =NULL;
	}
}

// Adds an axis to the plot. Returns a pointer to
// this axis which need not be stored by the user
// but is useful for initial setup of the axis
CAxis	*CPlot::AddAxis( int location )
{
	CAxis		*axis;
	
	if( m_nAxisCount >= kMaxAxes ) return NULL;
	
	if( (axis = GetAxisByLocation( location )) == NULL )
	{
		axis = NewAxis();//new CAxisImpl(this);
		axis->SetDefaults();
		axis->SetLocation( location );
		
		// Add to our axis data sets
		m_pAxes[m_nAxisCount] = axis;
		m_nAxisCount++;
	}
	
	return axis;
}

// Returns the axis at a specified location (left, top, etc)
// or NULL if no such axis exists
CAxis	*CPlot::GetAxisByLocation( int location )
{
	int			i;
	CAxis		*axis;

	for( i = 0; i < GetAxisCount(); i++ )
	{
		axis = GetAxis(i);
		if( axis != NULL && axis->GetLocation() == location )
			return axis;
	}

	return NULL;
}

int		CPlot::GetAxisIndex( int location )
{
	int			i;
	CAxis		*axis;

	for( i = 0; i < GetAxisCount(); i++ )
	{
		axis = GetAxis(i);
		if( axis != NULL && axis->GetLocation() == location )
			return i;
	}

	return -1;
}

void	CPlot::RejectAxisByLocation(int location)
{
	int		i,which=-1;
	CAxis	*axis,*ax1;
	for( i = 0; i < GetAxisCount(); i++)
	{
		axis = GetAxis(i);
		if( axis != NULL && axis->GetLocation() == location )
		{
			which=i;
			break;
		}
	}
	if(which==-1)return;

	for( i = which; i < m_nAxisCount-1; i++)
	{		
		axis = GetAxis(i);
		ax1=GetAxis(i+1);
		if(axis && ax1)axis->CopySettings(ax1);
	}
	m_nAxisCount--;
}

void	CPlot::RejectAxis(int which)
{
	if( which<0 || which> GetAxisCount() )return;

	CAxis	*axis,*ax1;
	for( int i = which; i < m_nAxisCount-1; i++)
	{		
		axis = GetAxis(i);
		ax1=GetAxis(i+1);
		if(axis && ax1)axis->CopySettings(ax1);
	}
	m_nAxisCount--;
}

void	CPlot::RejectAllAxes()
{
	while( GetAxisCount() >0 )
	{
		RejectAxis(0);
	}
}

void	CPlot::DeleteAllAxes()
{
	for( int i = 0; i < kMaxAxes; i++ )
	{
		if(m_pAxes[i])
		{
			delete m_pAxes[i];
			m_pAxes[i] = NULL;
		}
	}
}

bool	CPlot::AxisLighted()
{
	for(int i=0;i<GetAxisCount();i++)
		if(m_pAxes[i]->IsCurrent())return true;
		return false;
}

void	CPlot::UnlightAllAxis()
{
	for(int i=0;i<GetAxisCount();i++)
		m_pAxes[i]->SetCurrent(false);
}

CLegend *	CPlot::GetLegend()
{
	return m_pLegend;
}

void		CPlot::DeleteLegend()
{
	if(m_pLegend)
	{
		delete m_pLegend;
		m_pLegend=NULL;
	}
}

// Shortcut function to set the x range (setX = true) or
// yRange (setX = false) of a chart. Sets the left or
// bottom axis by default, but will use top or right
// if default axes do not exist.
void	CPlot::SetRange( bool setX, double low, double high )
{
	int				i;
	CAxis			*axis;
	int				bottom = -1, left = -1;

	for( i = 0; i < m_nAxisCount; i++ )
	{
		axis = GetAxis( i );
		if( axis == NULL ) continue;

		switch( axis->GetLocation() )
		{
		case kLocationTop:
		case kLocationCenterHB:
		case kLocationCenterHT:
			if( bottom < 0 ) bottom = i;
			break;
		case kLocationBottom: bottom = i; break;
		
		case kLocationRight:
		case kLocationCenterVL:
		case kLocationCenterVR:
			if( left < 0 ) left = i;
			break;
		case kLocationLeft: left = i; break;
		default:
			break;
		}
	}

	// Now check these axes
	if( setX )
	{
		if( bottom >= 0 )
		{
			axis = GetAxis( bottom );
			axis->SetRange( true, low, high );
		}
	}
	else
	{
		if( left >= 0 )
		{
			axis = GetAxis( left );
			axis->SetRange( true, low, high );
		}
	}
}

// Shortcut to set xRange of plot
void	CPlot::SetXRange( double low, double high )
{
	SetRange( true, low, high );
}

// Shortcut to set yRange of plot
void	CPlot::SetYRange( double low, double high )
{
	SetRange( false, low, high );
}

void	CPlot::GetRange( double *xRange, double *yRange )
{
	int				i;
	CAxis			*axis;
	int				bottom = -1, left = -1;

	for( i = 0; i < m_nAxisCount; i++ )
	{
		axis = GetAxis( i );
		if( axis == NULL ) continue;

		switch( axis->GetLocation() )
		{
		case kLocationTop:
		case kLocationCenterHB:
		case kLocationCenterHT:
			if( bottom < 0 ) bottom = i;
			break;
		case kLocationBottom: bottom = i; break;
		
		case kLocationRight:
		case kLocationCenterVL:
		case kLocationCenterVR:
			if( left < 0 ) left = i;
			break;
		case kLocationLeft: left = i; break;
		
		default:
			break;
		}
	}

	// Now check these axes
	if( bottom >= 0 )
	{
		axis = GetAxis( bottom );
		axis->GetRange( xRange );
	}
	else
	{
		// no axis
		xRange[0] = 0; xRange[1] = 10;
	}

	if( left >= 0 )
	{
		axis = GetAxis( left );
		axis->GetRange( yRange );
	}
	else
	{
		// no axis
		yRange[0] = 0; yRange[1] = 10;
	}
}

// Shortcut to get xRange of plot
void	CPlot::GetXRange( double *range )
{
	double			yRange[2];
	GetRange( range, yRange );
}

// Shortcut to get yRange of plot
void	CPlot::GetYRange( double *range )
{
	double			xRange[2];
	GetRange( xRange, range );
}

// haveXRange and haveYRange are set to whether the
// x and y axes have auto-ranging. This goes based
// on the left and bottom axes by default, but
// will use top/right if defaults do not exist.
void	CPlot::IsAutoRange( bool &haveXRange, bool &haveYRange )
{
	int			i;
	CAxis		*axis;
	bool		haveBottom = false, haveLeft = false;

	haveXRange = true, haveYRange = true;

	for( i = 0; i < m_nAxisCount; i++ )
	{
		axis = GetAxis(i);
		if( axis == NULL ) continue;

		switch( axis->GetLocation() )
		{
		case kLocationTop:
		case kLocationCenterHB:
		case kLocationCenterHT:
			if( haveBottom == true || axis->IsRangeSet() == false )
				break;
			// fall through
		case kLocationBottom:
			if( axis->IsRangeSet() )
			{
				haveXRange = false;
			}
			haveBottom = true;
			break;
		case kLocationRight:
		case kLocationCenterVL:
		case kLocationCenterVR:
			if( haveLeft == true || axis->IsRangeSet() == false )
				break;
			// fall through
		case kLocationLeft:
			if( axis->IsRangeSet() )
			{
				haveYRange = false;
			}
			haveLeft = true;
			break;
		default: break;
		}
	}
}

// Returns whether the x axis is auto ranged
bool	CPlot::IsXAutoRange( void )
{
	bool		xAuto, yAuto;

	IsAutoRange( xAuto, yAuto );

	return xAuto;
}

// Returns whethre the y axis is auto ranged 
bool	CPlot::IsYAutoRange( void )
{
	bool		xAuto, yAuto;

	IsAutoRange( xAuto, yAuto );

	return yAuto;
}

// Sets an axis to be auto ranging. X Axis if
// setX is true, y Axis otherwise. Sets the
// left/bottom axis by default but will use
// right/top if the defaults do not exist.
void	CPlot::SetAutoRange( bool setX )
{
	int				i;
	CAxis			*axis;
	int				bottom = -1, left = -1;

	for( i = 0; i < m_nAxisCount; i++ )
	{
		axis = GetAxis( i );
		if( axis == NULL ) continue;

		switch( axis->GetLocation() )
		{
		case kLocationTop:
		case kLocationCenterHB:
		case kLocationCenterHT:
			if( bottom < 0 ) bottom = i;
			break;
		case kLocationBottom: bottom = i; break;
		
		case kLocationRight:
		case kLocationCenterVL:
		case kLocationCenterVR:
			if( left < 0 ) left = i;
			break;
		case kLocationLeft: left = i; break;

		default:
			break;
		}
	}

	// Now check these axes
	if( setX )
	{
		if( bottom >= 0 )
		{
			axis = GetAxis( bottom );
			axis->SetRangeSet( false );
		}
	}
	else
	{
		if( left >= 0 )
		{
			axis = GetAxis( left );
			axis->SetRangeSet( false );
		}
	}

}

// Shortcut to set the x axis to auto range
void	CPlot::SetXAutoRange( void )
{
	SetAutoRange( true );
}

// Shortcut to set the y axis to auto range
void	CPlot::SetYAutoRange( void )
{
	SetAutoRange( false );
}

