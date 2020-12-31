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
#include "../XYPlotImpl.h"
#include "../XYHandler.h"
#include "DefHandlers.h"
#include <sstream>

/////////////////////////////////////////////////////////////////////////
// Context Menu

// Some constants for the popup menus
const int		tickSizes[] = {2, 3, 4, 5, 6, 7, 8, 9, 10};
const int		nTickSizes				=	9;

const int		nLineSizes				=	10;

// These constants are for the popup menu support. They
// facilitate making and interpretation of the menus

const int		kMenuPlotSettings		=	32768;

// for title
const int		kMenuTitle				=	10;
const int		kMenuSubTitle			=	kMenuTitle+nFontSizes+2;

// for axes
const int		kMenuAxisRange			=	100;
const int		kMenuAxisMinimum		=	(1*kMenuAxisRange);
const int		kMenuDataRange			=	100;
const int		kMenuDataMinimum		=	(1*kMenuDataRange+1000);

const int		kMenuAxisTitleSize		=	1;
const int		kMenuAxisLabelSize		=	(kMenuAxisTitleSize+nFontSizes);
const int		kMenuAxisMajorTickCount	=	(kMenuAxisLabelSize+nFontSizes);
// The +1 below is because there is one additional tick size (which is the "Auto" item)
const int		kMenuAxisMinorTickCount	=	(kMenuAxisMajorTickCount+nTickSizes+1);

// for background
const int		kHutchTypeCount			=	6;
const int		nGridsSizes				=	4;
const int		nGradientSizes			=	4;
const int		nBkgndSizes				=	1+kBrushTypeCount+kHutchTypeCount;
const int		nDataRegionSizes		=	2+kBrushTypeCount+kHutchTypeCount;
const int		nBorderSizes			=	1+nLineSizes;
const int		kMenuBackground			=	(kMenuAxisRange*kMaxAxes)+kMenuAxisMinimum;
const int		kMenuGrids				=	kMenuBackground;
const int		kMenuGradient			=	kMenuGrids + nGridsSizes;
const int		kMenuBkgnd				=	kMenuGradient + nGradientSizes;
const int		kMenuBkgndBrushType		=	kMenuBkgnd + 1;
const int		kMenuBkgndHutchType		=	kMenuBkgndBrushType+kBrushTypeCount;
const int		kMenuDataRegion			=	kMenuBkgnd + nBkgndSizes;
const int		kMenuDataRegionBrushType	=	kMenuDataRegion + 2;
const int		kMenuDataRegionHutchType	=	kMenuDataRegionBrushType+kBrushTypeCount;
const int		kMenuBorder				=	kMenuDataRegion + nDataRegionSizes;

const int		kMenuBackgroundRange	=	100;

// for legend
const int		kMenuLegend				=	kMenuBackground+kMenuBackgroundRange;
const int		kMenuLegendRange		=	30;

// for data set
const int		kMenuChartType			=	0;
const int		kMenuLineSize			=	(1+kPlotTypeCount);
const int		kMenuLineStyle			=	(1+kMenuLineSize+nLineSizes);
const int		kMenuMarker				=	(1+kMenuLineStyle+5);
const int		kMenuMarkerFill			=	(kMarkerTypeCount);
const int		kMenuMarkerSize			=	(kMenuMarkerFill+1);
const int		nMarkerSizes			=	20;
const int		kMenuMarkerFrequency	=	(kMenuMarkerSize+nMarkerSizes);
const int		nMaxDataSetsMenus		=	64;

/////////////////////////////////////////////////////////////////////////

HMENU	CreateContextMenu(CXYPlotImpl *plot);

void	AddFontSizePopup( HMENU addMenu, LPCSTR titleString, long compare, int startVal );
void	AddTitlePopup(CXYPlotImpl *plot, HMENU addMenu, LPCSTR titleString, int startVal);
void	AddSubtitlePopup(CXYPlotImpl *plot, HMENU addMenu, LPCSTR titleString, int startVal);
void	AddLineSizePopup(HMENU addMenu, LPCSTR titleString, long compare, int startVal);
void	AddGridPopup(CXYPlotImpl *plot, HMENU addMenu, LPCSTR titleString, int startVal);
void	AddPlotTypePopup( HMENU addMenu, LPCSTR titleString, long compare, int startVal );
void	AddDataLineSizePopup(CXYPlotImpl *plot, HMENU addMenu, LPCSTR titleString, int dataID, int startVal );
void	AddDataLineStylePopup( CXYPlotImpl *plot, HMENU addMenu, LPCSTR titleString, int dataID, int startVal );
void	AddMarkerPopup( CXYPlotImpl *plot, HMENU addMenu, LPCSTR titleString, int dataID, int startVal );
void	AddDataPopup( CXYPlotImpl *plot, int whichDataSet, HMENU menu, int startVal );
void	AddGradientPopup( CXYPlotImpl *plot, HMENU addMenu, LPCSTR titleString, int startVal);
void	AddAxisPopup( CXYPlotImpl *plot, HMENU menu, int which, int startVal );
void	AddNumberOfTicksPopup( HMENU addMenu, LPCSTR titleString, long compare, int startVal, BOOL bAuto );
void	AddBrushTypePopup( HMENU addMenu, LPCSTR titleString, long compare, int startVal );
void	AddHutchTypePopup( HMENU addMenu, LPCSTR titleString, long compare, int startVal );

int		InterpretPopupItem( CXYPlotImpl *plot, HWND hWnd, int result );
int		InterpretDataSetPopupItem( CXYPlotImpl *plot,HWND hWnd, int whichDataSet, int result );
int		InterpretAxisPopupItem( CXYPlotImpl *plot, int which, int whichResult );

/////////////////////////////////////////////////////////////////////////

int DefContextMenu( CXYPlotImpl *plot, HMENU hMenu, HWND hWnd, POINT point )
{
	HMENU			menu;
	int				result;

	if(!IsWindow(hWnd))return kPopupError;
	if( plot->GetDataSetCount()<=0 )return kPopupError;

	if( IsMenu(hMenu) )
	{
		result = TrackPopupMenu(hMenu, TPM_LEFTALIGN | TPM_RIGHTBUTTON | TPM_RETURNCMD, point.x, point.y, 0, hWnd, NULL);
		SendMessage( hWnd, WM_COMMAND, (WPARAM)result, 0);
		return kPopupNoAction;
	}

	menu = CreateContextMenu(plot);
	result = TrackPopupMenu(menu, TPM_LEFTALIGN | TPM_RIGHTBUTTON | TPM_RETURNCMD, point.x, point.y, 0, hWnd, NULL);
	DestroyMenu(menu);

	return InterpretPopupItem( plot, hWnd, result );
}

HMENU	CreateContextMenu(CXYPlotImpl *plot)
{
	HMENU			menu, subMenu;
	int				i;
	UINT			flag;

	menu = CreatePopupMenu();

	// Check for a title, and put in title menu if needed
	if( plot->GetTitle() != "" || ( plot->GetSubtitle() != "" && plot->IsSubtitleShow()) )
	{
		subMenu = CreatePopupMenu();
		AddTitlePopup(plot, subMenu, "&Main Title", kMenuTitle);
		AddSubtitlePopup(plot, subMenu, "&Sub Title", kMenuSubTitle);
		AppendMenu(menu, MF_POPUP | MF_STRING, (UINT) subMenu, "&Titles" );
	}

	if( plot->GetAxisCount() > 0 )
	{
		subMenu = CreatePopupMenu();
		for( i = 0; i < plot->GetAxisCount(); i++ )
		{
			AddAxisPopup(plot, subMenu, i, (kMenuAxisRange*i)+kMenuAxisMinimum );
		}
		
		if( plot->GetAxisCount() > 1)
			AppendMenu(menu, MF_POPUP | MF_STRING, (UINT) subMenu, "&Axes" );
		else
			AppendMenu(menu, MF_POPUP | MF_STRING, (UINT) subMenu, "&Axis" );
	}
	

	// Back ground
	subMenu = CreatePopupMenu();

	AddGridPopup(plot, subMenu, "&Grids", kMenuGrids);
	AddGradientPopup(plot, subMenu, "Gra&dient", kMenuGradient);
	AppendMenu(subMenu, MF_SEPARATOR, 0, (LPCSTR)0 );
	AppendMenu(subMenu, MF_STRING, kMenuBkgnd, "&Background Color..." );
	AddBrushTypePopup(subMenu, "Background B&rush", plot->GetBkgndBrushType(), kMenuBkgndBrushType);
	AddHutchTypePopup(subMenu, "Background &Hutch", plot->GetBkgndHatchStyle(), kMenuBkgndHutchType);
	AppendMenu(subMenu, MF_SEPARATOR, 0, (LPCSTR)0 );
	if( plot->IsUseDataRegionBrush() )
		AppendMenu(subMenu, MF_STRING, kMenuDataRegion, "D&isable Data Area Brush" );
	else
		AppendMenu(subMenu, MF_STRING, kMenuDataRegion, "&Enable Data Area Brush" );
	AppendMenu(subMenu, MF_STRING, kMenuDataRegion+1, "&Data Area Color..." );
	AddBrushTypePopup(subMenu, "Data Area B&rush", plot->GetDataRegionBrushType(), kMenuDataRegionBrushType);
	AddHutchTypePopup(subMenu, "Data Area &Hutch", plot->GetDataRegionHatchStyle(), kMenuDataRegionHutchType);
	AppendMenu(subMenu, MF_SEPARATOR, 0, (LPCSTR)0 );
	AppendMenu(subMenu, MF_STRING, kMenuBorder, "Border &Color..." );
	AddLineSizePopup(subMenu, "Border &Sizes", plot->GetBorderSize(), kMenuBorder+1);

	AppendMenu(menu, MF_POPUP | MF_STRING, (UINT) subMenu, "B&ackground" );

	// Legend
	subMenu = CreatePopupMenu();
	if( plot->IsUseLegend() )
		AppendMenu(subMenu, MF_STRING, kMenuLegend, "&Hide Legend" );
	else
		AppendMenu(subMenu, MF_STRING, kMenuLegend, "&Show Legend" );
	flag = GetPopupCheckedFlag( plot->GetLegend()->IsTransparent() );
	AppendMenu(subMenu, MF_STRING | flag, kMenuLegend+1, "&Transparent" );
	flag = GetPopupCheckedFlag( plot->GetLegend()->IsConfined() );
	AppendMenu(subMenu, MF_STRING | flag, kMenuLegend+2, "&Confined" );
	AppendMenu(subMenu, MF_STRING, kMenuLegend+3, "Legend &Font..." );
	AppendMenu(subMenu, MF_STRING, kMenuLegend+4, "&Bkgnd Color..." );
	AppendMenu(subMenu, MF_SEPARATOR, 0, (LPCSTR)0 );
	AppendMenu(subMenu, MF_STRING, kMenuLegend+5, "Border &Color..." );
	AddLineSizePopup(subMenu, "Border &Size", plot->GetLegend()->GetBorderLineSize(),kMenuLegend+6);

	AppendMenu(menu, MF_POPUP | MF_STRING, (UINT) subMenu, "L&egend" );
	
	// Data sets
	subMenu = CreatePopupMenu();
	
	AppendMenu(subMenu, MF_STRING, kMenuPlotSettings-2, "&Load data...");
	AppendMenu(subMenu, MF_STRING, kMenuPlotSettings-1, "&Save data...");
	AppendMenu(subMenu, MF_SEPARATOR, 0, (LPCSTR)0 );
	for( i = 0; i < min( plot->GetDataSetCount(),nMaxDataSetsMenus ); i++ )
	{
		AddDataPopup(plot, i, subMenu, (kMenuDataRange*i) + kMenuDataMinimum );
	}
	
	ostringstream ostr;
	string str;
	ostr<<"&Data Sets(Total "<<plot->GetDataSetCount()<<")";
	str=ostr.str();
	AppendMenu(menu, MF_POPUP | MF_STRING, (UINT) subMenu, str.c_str() );
	

	// Settings...
	AppendMenu(menu, MF_SEPARATOR, 0, (LPCSTR)0 );
	AppendMenu(menu, MF_STRING, kMenuPlotSettings, "&Plot Settings..." );

	return menu;
}

// Take the result of the popup menu selection, figure out
// what the user wanted, and take the appropriate action
int		InterpretPopupItem( CXYPlotImpl *plot, HWND hWnd, int result )
{
	int			whichAxis, returnVal;
	string		filename;

	COLORREF	color=0;
	LOGFONT		logfont;

	//if( result >= kMinimumPopupValue ) return result;

	// Grids
	if( result <= 0 ) return kPopupError;

	// Title
	if(result >= kMenuTitle && result < kMenuTitle + nFontSizes + 2)
	{
		if( result >= kMenuTitle && result < kMenuTitle + nFontSizes )
		{
			plot->GetTitleFont().lfHeight = fontSizes[result-kMenuTitle];
			return kPopupUpdate;
		}
		else if( result == kMenuTitle + nFontSizes )
		{
			color = plot->GetTitleColor();
			if(ShowColorDialog(hWnd, color))
			{
				plot->SetTitleColor(color);
				return kPopupUpdate;
			}
		}
		else if( result == kMenuTitle + nFontSizes +1 )
		{
			logfont = plot->GetTitleFont();
			if(ShowFontDialog(hWnd, logfont, color))
			{
				plot->SetTitleFont(logfont);
				return kPopupUpdate;
			}
		}
	}
	if(result >= kMenuSubTitle && result < kMenuSubTitle + nFontSizes + 3)
	{
		if( result == kMenuSubTitle )
		{
			plot->SetSubtitleShow( !plot->IsSubtitleShow() );
			return kPopupUpdate;
		}
		if( result >= kMenuSubTitle + 1 && result < kMenuSubTitle + 1 + nFontSizes )
		{
			plot->GetSubtitleFont().lfHeight = fontSizes[result - kMenuSubTitle - 1];
			return kPopupUpdate;
		}
		else if( result == kMenuSubTitle + nFontSizes + 1 )
		{
			color = plot->GetSubtitleColor();
			if(ShowColorDialog(hWnd, color))
			{
				plot->SetSubtitleColor(color);
				return kPopupUpdate;
			}
		}
		else if( result == kMenuSubTitle + nFontSizes + 2 )
		{
			logfont = plot->GetSubtitleFont();
			if(ShowFontDialog(hWnd, logfont, color))
			{
				plot->SetSubtitleFont(logfont);
				return kPopupUpdate;
			}
		}
	}
	

	// Axes
	if( result >= kMenuAxisMinimum && result < kMenuAxisMinimum + (kMaxAxes*kMenuAxisRange) )
	{
		// These must be axis sets
		whichAxis = (result-kMenuAxisMinimum) / kMenuAxisRange;

		if( whichAxis < 0 || whichAxis > plot->GetAxisCount() ) return kPopupError;

		if( result % kMenuAxisRange == kMenuAxisRange-1 ) // have to do this one manually
			if( DefAxisSettings(plot, hWnd, plot->GetAxis(whichAxis)->GetLocation()) ) return kPopupUpdate; else return kPopupNoAction;

		//if( (returnVal = plot->GetAxis(whichAxis)->InterpretAxisPopupItem( (result-kMenuAxisMinimum) % kMenuAxisRange ) ) == kPopupError )
		if( (returnVal = InterpretAxisPopupItem(plot, whichAxis, (result-kMenuAxisMinimum) % kMenuAxisRange ) ) == kPopupError )
			return result;
		else
			return returnVal;
	}

	// Background
	if( result >= kMenuBackground && result < kMenuBackground + kMenuBackgroundRange )//gradient back ground
	{
		if( result < kMenuGrids + nGridsSizes )
		{
			switch( result - kMenuGrids )
			{
			case 0: plot->SetUseMajorHGrids( !plot->IsUseMajorHGrids() ); break;
			case 1: plot->SetUseMajorVGrids( !plot->IsUseMajorVGrids() ); break;
			case 2: plot->SetUseMinorHGrids( !plot->IsUseMinorHGrids() ); break;
			case 3: plot->SetUseMinorVGrids( !plot->IsUseMinorVGrids() ); break;
			default: break;
			}
			return kPopupUpdate;
		}
		if( result >= kMenuGradient && result < kMenuGradient + nGradientSizes)
		{
			switch(result - kMenuGradient)
			{
			case 0: plot->SetGradientBkgnd(!plot->IsGradientBkgnd());return kPopupUpdate;
			case 1: plot->SetGradientHorizontal( !plot->IsGradientHorizontal() );return kPopupUpdate;
			case 2:
				color = plot->GetGradientColor1();
				if(ShowColorDialog(hWnd, color))
				{
					plot->SetGradientColor1(color);
					return kPopupUpdate;
				}
				return kPopupNoAction;
			case 3:
				color = plot->GetGradientColor2();
				if(ShowColorDialog(hWnd, color))
				{
					plot->SetGradientColor2(color);
					return kPopupUpdate;
				}
				return kPopupNoAction;
			}
		}
		if( result >= kMenuBkgnd && result < kMenuBkgnd + nBkgndSizes )
		{
			if( result - kMenuBkgnd ==0 )
			{
				color = plot->GetBkgndColor();
				if(ShowColorDialog(hWnd, color))
				{
					plot->SetBkgndColor(color);
					return kPopupUpdate;
				}
				return kPopupNoAction;
			}
			if( result - kMenuBkgndBrushType >= 0 && result - kMenuBkgndBrushType < kBrushTypeCount )
			{
				plot->SetBkgndBrushType(result - kMenuBkgndBrushType );
				return kPopupUpdate;
			}
			if( result - kMenuBkgndHutchType >= 0 && result - kMenuBkgndHutchType < kHutchTypeCount )
			{
				plot->SetBkgndHatchStyle(result - kMenuBkgndHutchType );
				return kPopupUpdate;
			}
			
		}
		if( result >= kMenuDataRegion && result < kMenuDataRegion + nDataRegionSizes )
		{
			if( result - kMenuDataRegion == 0 )
			{
				plot->SetUseDataRegionBrush( !plot->IsUseDataRegionBrush() );
				return kPopupUpdate;
			}
			if( result - kMenuDataRegion == 1 )
			{
				color = plot->GetDataRegionColor();
				if(ShowColorDialog(hWnd, color))
				{
					plot->SetDataRegionColor(color);
					return kPopupUpdate;
				}
				return kPopupNoAction;
			}
			if( result - kMenuDataRegionBrushType >= 0 && result - kMenuDataRegionBrushType < kBrushTypeCount )
			{
				plot->SetDataRegionBrushType(result - kMenuDataRegionBrushType );
				return kPopupUpdate;
			}
			if( result - kMenuDataRegionHutchType >= 0 && result - kMenuDataRegionHutchType < kHutchTypeCount )
			{
				plot->SetDataRegionHatchStyle(result - kMenuDataRegionHutchType );
				return kPopupUpdate;
			}
		}
		if( result >= kMenuBorder && result < kMenuBorder + nBorderSizes )
		{
			if( result - kMenuBorder == 0 )
			{
				color = plot->GetBorderColor();
				if(ShowColorDialog(hWnd, color))
				{
					plot->SetBorderColor(color);
					return kPopupUpdate;
				}
				return kPopupNoAction;
			}
			if( result - kMenuBorder > 0 && result - kMenuBorder <= nLineSizes )
			{
				plot->SetBorderSize( result - kMenuBorder );
				return kPopupUpdate;
			}
		}
	}

	// Legend
	if( result >= kMenuLegend && result < kMenuLegend + kMenuLegendRange )//use legend
	{
		if( result == kMenuLegend )
		{
			plot->SetUseLegend(!plot->IsUseLegend());
			return kPopupUpdate;
		}
		if( result == kMenuLegend + 1 )
		{
			plot->GetLegend()->SetTransparent( !plot->GetLegend()->IsTransparent() );
			return kPopupUpdate;
		}
		if( result == kMenuLegend + 2 )
		{
			plot->GetLegend()->SetConfined( !plot->GetLegend()->IsConfined() );
			return kPopupUpdate;
		}
		if( result == kMenuLegend + 3 )
		{
			logfont = plot->GetLegend()->GetFont();
			if(ShowFontDialog(hWnd, logfont, color))
			{
				plot->GetLegend()->SetFont(logfont);
				return kPopupUpdate;
			}
			return kPopupNoAction;
		}
		if( result == kMenuLegend + 4 )
		{
			color = plot->GetLegend()->GetBkgndColor();
			if(ShowColorDialog(hWnd, color))
			{
				plot->GetLegend()->SetBkgndColor(color);
				return kPopupUpdate;
			}
			return kPopupNoAction;
		}
		if( result == kMenuLegend + 5 )
		{
			color = plot->GetLegend()->GetBorderColor();
			if(ShowColorDialog(hWnd, color))
			{
				plot->GetLegend()->SetBorderColor(color);
				return kPopupUpdate;
			}
			return kPopupNoAction;
		}
		if( result >= kMenuLegend + 6 && result < kMenuLegend + 6 + nLineSizes )
		{
			plot->GetLegend()->SetBorderLizeSize( result - kMenuLegend - 5 );
			return kPopupUpdate;
		}
	}

	// Dataset
	if( result >= kMenuDataMinimum && result < kMenuDataMinimum + min( plot->GetDataSetCount(), nMaxDataSetsMenus )*kMenuDataRange )
	{
		int			whichDataSet;

		whichDataSet = (result-kMenuDataMinimum) / kMenuDataRange;

		if( whichDataSet < 0 || whichDataSet > plot->GetDataSetCount()-1 ) return kPopupError;

		if( (result-kMenuDataMinimum) % kMenuDataRange == kMenuDataRange-1 ) // have to do this one manually
		{
			if( DefDataSettings(plot, hWnd, whichDataSet) ) return kPopupUpdate; else return kPopupNoAction;
		}

		return InterpretDataSetPopupItem( plot, hWnd, whichDataSet, (result-kMenuDataMinimum) % kMenuDataRange );
	}

	if( result == kMenuPlotSettings - 2 )
	{
		if( !ShowFileDialog(hWnd, true, filename) )	return kPopupNoAction;
		if( plot->ReadFromFile(filename) )
		{
			MessageBox(hWnd, "Load data OK", "Infomation", MB_OK);
			return kPopupUpdate;
		}
		else
		{
			return kPopupNoAction;
		}
	}

	if( result == kMenuPlotSettings - 1 )
	{
		if( !ShowFileDialog(hWnd, false, filename) ) return kPopupNoAction;
		if( plot->WriteToFile(filename) )
		{
			MessageBox(hWnd, "Save data OK", "Infomation", MB_OK);
		}
		return kPopupNoAction;
	}

	// The last menu, ^_^
	if( result == kMenuPlotSettings )
	{
		if( DefPlotSettings(plot, hWnd) ) return kPopupUpdate; else return kPopupNoAction;
	}

	return kPopupError;
}

// Adds a popup menu for font sizes.
void	AddFontSizePopup( HMENU addMenu, LPCSTR titleString, long compare, int startVal )
{
	HMENU			subMenu = CreatePopupMenu();
	UINT			flag;
	
	for( int i = 0; i < nFontSizes; i++ )
	{
		flag = GetPopupCheckedFlag( compare == fontSizes[i] );
		ostringstream ostr;
		string str;
		ostr<<fontSizes[i];
		str=ostr.str();
		AppendMenu(subMenu, MF_STRING | flag, startVal+i, str.c_str() );
	}
	
	AppendMenu(addMenu, MF_POPUP, (UINT)subMenu, titleString );
}

void	AddLineSizePopup(HMENU addMenu, LPCSTR titleString, long compare, int startVal)
{
	HMENU			subMenu = CreatePopupMenu();
	UINT			flag;

	for(int i=0; i<nLineSizes; i++)
	{
		flag = GetPopupCheckedFlag( compare == i+1 );
		ostringstream ostr;
		string str;
		ostr<<i+1;
		str=ostr.str();
		AppendMenu( subMenu, MF_STRING | flag, startVal+i, str.c_str() );
	}
	AppendMenu(addMenu, MF_POPUP | MF_STRING, (UINT) subMenu, titleString );
}

//
void	AddTitlePopup(CXYPlotImpl *plot, HMENU addMenu, LPCSTR titleString, int startVal)
{
	HMENU			subMenu;

	subMenu = CreatePopupMenu();
	AddFontSizePopup( subMenu, "S&ize", plot->GetTitleFont().lfHeight, startVal );
	AppendMenu(subMenu, MF_STRING, startVal+nFontSizes, "&Color..." );
	AppendMenu(subMenu, MF_STRING, startVal+nFontSizes+1, "&Font..." );

	AppendMenu(addMenu, MF_POPUP | MF_STRING, (UINT) subMenu, titleString );
}

//
void	AddSubtitlePopup(CXYPlotImpl *plot, HMENU addMenu, LPCSTR titleString, int startVal)
{
	HMENU			subMenu;
	
	subMenu = CreatePopupMenu();
	if( plot->IsSubtitleShow() )
		AppendMenu(subMenu, MF_STRING, startVal, "&Hide It" );
	else
		AppendMenu(subMenu, MF_STRING, startVal, "&Show It" );
	AppendMenu(subMenu, MF_SEPARATOR, 0, (LPCSTR)0 );
	AddFontSizePopup( subMenu, "S&ize", plot->GetTitleFont().lfHeight, startVal+1 );
	AppendMenu(subMenu, MF_STRING, startVal+1+nFontSizes, "&Color..." );
	AppendMenu(subMenu, MF_STRING, startVal+1+nFontSizes+1, "&Font..." );
	
	AppendMenu(addMenu, MF_POPUP | MF_STRING, (UINT) subMenu, titleString );
}

//
void	AddGridPopup(CXYPlotImpl *plot, HMENU addMenu, LPCSTR titleString, int startVal)
{
	HMENU			subMenu;
	UINT			flag;

	subMenu = CreatePopupMenu();
	flag = GetPopupCheckedFlag( plot->IsUseMajorHGrids() );
	AppendMenu(subMenu, MF_STRING | flag, startVal, "&Major Horizontal Grids" );
	flag = GetPopupCheckedFlag(plot->IsUseMajorVGrids() );
	AppendMenu(subMenu, MF_STRING | flag, startVal+1, "M&ajor Vertical Grids" );
	flag = GetPopupCheckedFlag(plot->IsUseMinorHGrids() );
	AppendMenu(subMenu, MF_STRING | flag, startVal+2, "M&inor Horizontal Grids" );
	flag = GetPopupCheckedFlag(plot->IsUseMinorVGrids() );
	AppendMenu(subMenu, MF_STRING | flag, startVal+3, "Mi&nor Vertical Grids" );
	AppendMenu(addMenu, MF_POPUP | MF_STRING, (UINT) subMenu, "&Grids" );
}

// Add a popup menu for the different chart types
void	AddPlotTypePopup( HMENU addMenu, LPCSTR titleString, long compare, int startVal )
{
	HMENU			subMenu;
	UINT			flag;
	
	subMenu = CreatePopupMenu();

	flag = GetPopupCheckedFlag( compare == kXYPlotScatter  );
	AppendMenu(subMenu, MF_STRING | flag, startVal+kXYPlotScatter , "XY &Scatter" );
	flag = GetPopupCheckedFlag( compare == kXYPlotConnect );
	AppendMenu(subMenu, MF_STRING | flag, startVal+kXYPlotConnect, "XY &Line" );
	flag = GetPopupCheckedFlag( compare == kXYPlotStepHV );
	AppendMenu(subMenu, MF_STRING | flag, startVal+kXYPlotStepHV, "Step &H-V" );
	flag = GetPopupCheckedFlag( compare == kXYPlotStepVH );
	AppendMenu(subMenu, MF_STRING | flag, startVal+kXYPlotStepVH, "Step &V-H" );
	flag = GetPopupCheckedFlag( compare == kXYPlotStepHVH );
	AppendMenu(subMenu, MF_STRING | flag, startVal+kXYPlotStepHVH, "S&tep H-V-H" );
	flag = GetPopupCheckedFlag( compare == kXYPlotStepVHV );
	AppendMenu(subMenu, MF_STRING | flag, startVal+kXYPlotStepVHV, "St&ep &V-H-V" );
	flag = GetPopupCheckedFlag( compare == kXYPlotBezier );
	AppendMenu(subMenu, MF_STRING | flag, startVal+kXYPlotBezier, "&Bezier Line" );
	
	AppendMenu(addMenu, MF_POPUP, (UINT) subMenu, titleString);
}

// Add a popup menu for brush type
void	AddBrushTypePopup( HMENU addMenu, LPCSTR titleString, long compare, int startVal )
{
	HMENU			subMenu;
	UINT			flag;
	
	subMenu = CreatePopupMenu();
	
	flag = GetPopupCheckedFlag( compare == kBrushNull  );
	AppendMenu(subMenu, MF_STRING | flag, startVal+kBrushNull , "&Null Brush" );
	flag = GetPopupCheckedFlag( compare == kBrushSolid );
	AppendMenu(subMenu, MF_STRING | flag, startVal+kBrushSolid, "&Solid Brush" );
	flag = GetPopupCheckedFlag( compare == kBrushHatch );
	AppendMenu(subMenu, MF_STRING | flag, startVal+kBrushHatch, "&Hatch Brush" );
	flag = GetPopupCheckedFlag( compare == kBrushPattern );
	AppendMenu(subMenu, MF_STRING | flag, startVal+kBrushPattern, "&Pattern Brush" );
	
	AppendMenu(addMenu, MF_POPUP, (UINT) subMenu, titleString);
}

// Add a popup menu for hutch type
void	AddHutchTypePopup( HMENU addMenu, LPCSTR titleString, long compare, int startVal )
{
	HMENU			subMenu;
	UINT			flag;
	
	subMenu = CreatePopupMenu();

	flag = GetPopupCheckedFlag( compare == 0  );
	AppendMenu(subMenu, MF_STRING | flag, startVal+0 , "&Horizontal Hutch" );/* ----- */
	flag = GetPopupCheckedFlag( compare == 1 );
	AppendMenu(subMenu, MF_STRING | flag, startVal+1, "&Vertical Hutch" );/* ||||| */
	flag = GetPopupCheckedFlag( compare == 2 );
	AppendMenu(subMenu, MF_STRING | flag, startVal+2, "&FDiagonal Hutch" );/* \\\\\ */
	flag = GetPopupCheckedFlag( compare == 3 );
	AppendMenu(subMenu, MF_STRING | flag, startVal+3, "&BDiagonal Hutch" );/* ///// */
	flag = GetPopupCheckedFlag( compare == 4 );
	AppendMenu(subMenu, MF_STRING | flag, startVal+4, "&Cross Hutch" );/* +++++ */
	flag = GetPopupCheckedFlag( compare == 5 );
	AppendMenu(subMenu, MF_STRING | flag, startVal+5, "&Diagcross Hutch" );/* xxxxx */
	
	AppendMenu(addMenu, MF_POPUP, (UINT) subMenu, titleString);
}

// Add a popup for the line size of a data set
void	AddDataLineSizePopup(CXYPlotImpl *plot, HMENU addMenu, LPCSTR titleString, int dataID, int startVal )
{
	HMENU		subMenu = CreatePopupMenu();
	UINT		flag;
		
	// Line size
	for( int i = 0; i < nLineSizes; i++ )
	{
		flag = GetPopupCheckedFlag( plot->GetDataLineSize( dataID ) == i+1 );
		ostringstream ostr;
		string str;
		ostr<<i+1;
		str=ostr.str();
		AppendMenu(subMenu, MF_STRING | flag, startVal+i, str.c_str() );
	}
	AppendMenu(addMenu, MF_POPUP, (UINT) subMenu, titleString );
}

// Add a popup for the line size of a data set
void	AddDataLineStylePopup( CXYPlotImpl *plot, HMENU addMenu, LPCSTR titleString, int dataID, int startVal )
{
	HMENU		subMenu;
	UINT		flag;
	
	subMenu = CreatePopupMenu();
	
	// We'll just hard code these for now
	flag = GetPopupCheckedFlag( plot->GetDataLineStyle( dataID ) == 0 );
	AppendMenu(subMenu, MF_STRING | flag, startVal,   "Solid ____________" );
	flag = GetPopupCheckedFlag( plot->GetDataLineStyle( dataID ) == 1 );
	AppendMenu(subMenu, MF_STRING | flag, startVal+1, "Dashed _ _ _ _ _ _" );
	flag = GetPopupCheckedFlag( plot->GetDataLineStyle( dataID ) == 2 );
	AppendMenu(subMenu, MF_STRING | flag, startVal+2, "Dotted . . . . . ." );
	flag = GetPopupCheckedFlag( plot->GetDataLineStyle( dataID ) == 3 );
	AppendMenu(subMenu, MF_STRING | flag, startVal+3, "Dash-Dot _ . _ . _" );
	flag = GetPopupCheckedFlag( plot->GetDataLineStyle( dataID ) == 4 );
	AppendMenu(subMenu, MF_STRING | flag, startVal+4, "Dash-Dot-Dot _ . ." );
	
	AppendMenu(addMenu, MF_POPUP, (UINT) subMenu, titleString );
}

// Add a popup menu for the different marker types and frequencies
void	AddMarkerPopup( CXYPlotImpl *plot, HMENU addMenu, LPCSTR titleString, int dataID, int startVal )
{
	HMENU			shapeMenu,sizeMenu,freqMenu;
	int				i, markerShape, freq;
	UINT			flag;

	ostringstream ostr;
	string str;
	
	// Marker shape
	shapeMenu = CreatePopupMenu();
	markerShape = plot->GetMarkerType( dataID );
	flag = GetPopupCheckedFlag( markerShape == kXYMarkerNone );
	AppendMenu(shapeMenu, MF_STRING | flag, startVal+kXYMarkerNone, "&No marker" );
	flag = GetPopupCheckedFlag( markerShape == kXYMarkerCircle );
	AppendMenu(shapeMenu, MF_STRING | flag, startVal+kXYMarkerCircle, "&Circle marker" );
	flag = GetPopupCheckedFlag( markerShape == kXYMarkerSquareUpright );
	AppendMenu(shapeMenu, MF_STRING | flag, startVal+kXYMarkerSquareUpright, "&Upright square marker" );
	flag = GetPopupCheckedFlag( markerShape == kXYMarkerSquareOblique );
	AppendMenu(shapeMenu, MF_STRING | flag, startVal+kXYMarkerSquareOblique, "&Oblique square marker" );
	flag = GetPopupCheckedFlag( markerShape == kXYMarkerTriangleLeft );
	AppendMenu(shapeMenu, MF_STRING | flag, startVal+kXYMarkerTriangleLeft, "&Left riangle marker" );
	flag = GetPopupCheckedFlag( markerShape == kXYMarkerTriangleRight );
	AppendMenu(shapeMenu, MF_STRING | flag, startVal+kXYMarkerTriangleRight, "&Right triangle marker" );
	flag = GetPopupCheckedFlag( markerShape == kXYMarkerTriangleUp );
	AppendMenu(shapeMenu, MF_STRING | flag, startVal+kXYMarkerTriangleUp, "&Up triangle marker" );
	flag = GetPopupCheckedFlag( markerShape == kXYMarkerTriangleDown );
	AppendMenu(shapeMenu, MF_STRING | flag, startVal+kXYMarkerTriangleDown, "&Down triangle marker" );
	flag = GetPopupCheckedFlag( markerShape == kXYMarkerX );
	AppendMenu(shapeMenu, MF_STRING | flag, startVal+kXYMarkerX, "&X marker" );
	flag = GetPopupCheckedFlag( markerShape == kXYMarkerDot );
	AppendMenu(shapeMenu, MF_STRING | flag, startVal+kXYMarkerDot,"&Dot marker" );
	
	AppendMenu(addMenu, MF_POPUP, (UINT) shapeMenu, "&Marker shape" );
	
	// Marker Fill
	flag = GetPopupCheckedFlag( plot->GetMarkerFillState( dataID ) );
	AppendMenu(addMenu, MF_STRING | flag, startVal+kMenuMarkerFill, "M&arker fill" );
	
	// Marker size
	sizeMenu = CreatePopupMenu();
	for( i = 0; i < nMarkerSizes; i++ )
	{
		flag = GetPopupCheckedFlag( plot->GetMarkerSize( dataID ) == (i+1) );
		ostr.str("");
		ostr<<i+1;
		str=ostr.str();
		AppendMenu(sizeMenu, MF_STRING | flag, startVal+i+kMenuMarkerSize, str.c_str() );
	}
	AppendMenu(addMenu, MF_POPUP, (UINT) sizeMenu, "Ma&rker size" );
	
	// Marker frequency
	freqMenu= CreatePopupMenu();
	freq = abs(plot->GetMarkerFrequency( dataID ));
	if( freq == 1 || freq ==0 ) freq = 10;
	flag = GetPopupCheckedFlag( plot->GetMarkerFrequency( dataID ) == 1 );
	AppendMenu(freqMenu, MF_STRING | flag, startVal+kMenuMarkerFrequency, "&Mark every point" );
	flag = GetPopupCheckedFlag( (plot->GetMarkerFrequency( dataID )) > 1 );
	ostr.str("");
	ostr<<"M&ark every "<<freq<<" points";
	str=ostr.str();
	AppendMenu(freqMenu, MF_STRING | flag, startVal+kMenuMarkerFrequency+1, str.c_str() );
	flag = GetPopupCheckedFlag( (plot->GetMarkerFrequency( dataID )) < 0 );
	ostr.str("");
	ostr<<"Ma&rk "<<freq<<" points";
	str=ostr.str();
	AppendMenu(freqMenu, MF_STRING | flag, startVal+kMenuMarkerFrequency+2, str.c_str() );
	flag = GetPopupCheckedFlag( (plot->GetMarkerFrequency( dataID )) == 0 );
	str="Mar&k none";
	AppendMenu(freqMenu, MF_STRING | flag, startVal+kMenuMarkerFrequency+3, str.c_str() );
	
	AppendMenu(addMenu, MF_POPUP, (UINT) freqMenu, "Mar&ker frequency" );
}

// Add the popup menu for a specific data set
void	AddDataPopup( CXYPlotImpl *plot, int whichDataSet, HMENU menu, int startVal )
{
	string			str,name;
	HMENU			dataMenu;
	HMENU			subMenu;
	int				dataID;
	
	if( whichDataSet < 0 || whichDataSet >= plot->GetDataSetCount() ) return;
	
	dataID = plot->GetDataID(whichDataSet);
	
	dataMenu = CreatePopupMenu();
	
	AddPlotTypePopup( dataMenu, "&Plot type", plot->GetPlotType( dataID ), startVal+kMenuChartType );
	
	AppendMenu(dataMenu, MF_SEPARATOR, 0, (LPCSTR)0 );
	
	AddDataLineSizePopup( plot, dataMenu, "&Line size", dataID, startVal + kMenuLineSize );
	
	AddDataLineStylePopup( plot, dataMenu, "L&ine style", dataID, startVal + kMenuLineStyle );
	
	AppendMenu(dataMenu, MF_SEPARATOR, 0, (LPCSTR)0 );
	
	AddMarkerPopup( plot, dataMenu, "Marker", dataID, startVal + kMenuMarker );
	
	AppendMenu(dataMenu, MF_SEPARATOR, 0, (LPCSTR)0 );
	subMenu = CreatePopupMenu();
	AppendMenu(subMenu, MF_SEPARATOR, 0, (LPCSTR)0 );
	AppendMenu(subMenu, MF_STRING, startVal+kMenuDataRange-5, "&Load data...");
	AppendMenu(subMenu, MF_STRING, startVal+kMenuDataRange-4, "S&ave data...");
	AppendMenu(subMenu, MF_SEPARATOR, 0, (LPCSTR)0 );
	AppendMenu(subMenu, MF_STRING, startVal+kMenuDataRange-3, "&Erase data" );
	if(plot->IsDataShow(plot->GetDataID(whichDataSet)))
		AppendMenu(subMenu, MF_STRING, startVal+kMenuDataRange-2, "&Hide  data" );
	else
		AppendMenu(subMenu, MF_STRING, startVal+kMenuDataRange-2, "&Show  data" );
	AppendMenu(dataMenu, MF_POPUP, (UINT) subMenu, "&Data management");
	// Add it to main menu
	AppendMenu(dataMenu, MF_SEPARATOR, 0, (LPCSTR)0 );
	AppendMenu(dataMenu, MF_STRING, startVal+kMenuDataRange-1, "&Data Settings..." );
	
	
	str = plot->GetDataTitle( dataID );
	if( str == "" )str="Untitled";
	ostringstream ostr;
	ostr<<str.c_str()<<"\t("<<whichDataSet+1<<"/"<<plot->GetDataSetCount()<<")";
	name = ostr.str();
	if( name.length() > 24 )
	{
		name = str.substr(0, 24);
		name = str + "...";
	}
	
	AppendMenu(menu, MF_POPUP, (UINT) dataMenu, name.c_str() );
}

void	AddGradientPopup( CXYPlotImpl *plot, HMENU addMenu, LPCSTR titleString, int startVal)
{
	HMENU		subMenu;
	int			flag;

	subMenu = CreatePopupMenu();

	flag = GetPopupCheckedFlag( plot->IsGradientBkgnd() );
	AppendMenu(subMenu, MF_STRING | flag, startVal, "&Gradient Enabled" );
	if(plot->IsGradientHorizontal())
		AppendMenu(subMenu, MF_STRING, startVal+1, "Gradient &Vertical" );
	else
		AppendMenu(subMenu, MF_STRING, startVal+1, "Gradient &Horizontal" );
	AppendMenu( subMenu, MF_STRING, startVal+2, "&Start Color");
	AppendMenu( subMenu, MF_STRING, startVal+3, "Stop &Color");

	AppendMenu(addMenu, MF_POPUP | MF_STRING, (UINT) subMenu, "&Gradient" );
}

// Result here is rounded down to zero for the data set items
int		InterpretDataSetPopupItem( CXYPlotImpl *plot, HWND hWnd, int whichDataSet, int result )
{

	string		filename;
	int			dataID = plot->GetDataID(whichDataSet);

	// result is chart type
	if( result >= kMenuChartType && result < kMenuLineSize )
	{
		// These correlate perfectly
		plot->SetPlotType( dataID, result - kMenuChartType );

		return kPopupUpdate;
	}

	// result is line size
	if( result - kMenuLineSize >= 0 && result < kMenuLineSize + nLineSizes )
	{
		plot->SetDataLineSize( dataID, result - kMenuLineSize + 1 );

		return kPopupUpdate;
	}

	// result is line style
	if( result - kMenuLineStyle >= 0 && result < kMenuLineStyle + 5 )
	{
		plot->SetDataLineStyle( dataID, result - kMenuLineStyle );

		return kPopupUpdate;
	}

	// result is marker type
	if( result - kMenuMarker >= 0 && result - kMenuMarker < kMarkerTypeCount )
	{
		plot->SetMarkerType( dataID, result - kMenuMarker );
		return kPopupUpdate;
	}

	// marker fill item
	if( result - kMenuMarker == kMenuMarkerFill )
	{
		plot->SetMarkerFillState( dataID, !plot->GetMarkerFillState(dataID) );
		return kPopupUpdate;
	}

	// marker size popup
	if( result - kMenuMarker >= kMenuMarkerSize && result - kMenuMarker < kMenuMarkerSize+nMarkerSizes )
	{
		plot->SetMarkerSize( dataID, (result - (kMenuMarkerFill + kMenuMarker) ) );
		return kPopupUpdate;
	}

	// marker frequency
	if( result - kMenuMarker >= kMenuMarkerFrequency && result - kMenuMarker < kMenuMarkerFrequency + 4 )
	{
		int			tempResult = result - kMenuMarkerFrequency - kMenuMarker;
		int			freq = abs(plot->GetMarkerFrequency(dataID));
		
		if( freq == 1 || freq==0 ) freq = 10;
		
		switch( tempResult )
		{
		case 0: plot->SetMarkerFrequency( dataID, 1 ); break;
		case 1: plot->SetMarkerFrequency( dataID, freq ); break;
		case 2: plot->SetMarkerFrequency( dataID, -freq ); break;
		case 3: plot->SetMarkerFrequency( dataID, 0 ); break;
		default: break;
		}
		
		return kPopupUpdate;
	}

	// Load data
	if( result == kMenuDataRange - 5)
	{
		if( !ShowFileDialog(hWnd, true, filename) )
			return kPopupNoAction;
		if(plot->GetDataSet(plot->GetDataID(whichDataSet))->ReadFromFile(filename.c_str()))
		{
			plot->SetDataModified(plot->GetDataID(whichDataSet));
			//plot->GetXYDataInfo()[whichDataSet].bDataRangesSet = false;
			//plot->GetDataRanges();
			MessageBox(hWnd, "Load data OK", "Infomation", MB_OK);
			return kPopupUpdate;
		}
		else
		{
			return kPopupNoAction;
		}
	}

	// Save data
	if( result == kMenuDataRange - 4)
	{
		if( !ShowFileDialog(hWnd, false, filename) )
			return kPopupNoAction;
		if(plot->GetDataSet(plot->GetDataID(whichDataSet))->WriteToFile(filename.c_str()))
		{
			MessageBox(hWnd, "Save data OK", "Infomation", MB_OK);
		}

		return kPopupNoAction;
	}

	// delete this curve
	if( result == kMenuDataRange - 3)
	{
		plot->DeleteData(plot->GetDataID(whichDataSet));
		return kPopupUpdate;
	}
	// hide this curve
	if( result == kMenuDataRange - 2)
	{
		plot->SetDataShow(plot->GetDataID(whichDataSet), !plot->IsDataShow(plot->GetDataID(whichDataSet)));
		return kPopupUpdate;		
	}
	return kPopupNoAction;
}

// Adds the menus that pertain to the axis, including auto ranging,
// title size, label size, tick marks, etc. This is only called
// by the popup menu constructors for the chart types.
void	AddAxisPopup( CXYPlotImpl *plot, HMENU menu, int which, int startVal )
{
	UINT			flag;
	string			str;
	HMENU			axisMenu;
	
	axisMenu = CreatePopupMenu();
	
	flag = GetPopupCheckedFlag( plot->GetAxis(which)->IsRangeSet() == false );
	AppendMenu(axisMenu, MF_STRING | flag, startVal, "&Auto range" );
	
	// Font sizes
	AddFontSizePopup( axisMenu, "&Title size", plot->GetAxis(which)->GetTitleFont().lfHeight, startVal+kMenuAxisTitleSize );
	AddFontSizePopup( axisMenu, "&Label size", plot->GetAxis(which)->GetLabelFont().lfHeight, startVal+kMenuAxisLabelSize );
	
	AppendMenu(axisMenu, MF_SEPARATOR, 0, (LPCSTR)0 );
	
	// Number of major and minor ticks
	//AddNumberOfTicksPopup( &axisMenu, "Major ticks", m_nTickCount+1, startVal + kMenuAxisMajorTickCount );
	//AddNumberOfTicksPopup( &axisMenu, "Minor ticks", m_nMinorTickCount, startVal + kMenuAxisMinorTickCount );
	AddNumberOfTicksPopup( axisMenu, "&Major ticks", plot->GetAxis(which)->GetTickCount()+1, startVal + kMenuAxisMajorTickCount, plot->GetAxis(which)->IsAutoMajorTick() );
	AddNumberOfTicksPopup( axisMenu, "M&inor ticks", plot->GetAxis(which)->GetMinorTickCount(), startVal + kMenuAxisMinorTickCount, plot->GetAxis(which)->IsAutoMinorTick() );
	
	// Add it to main menu
	switch( plot->GetAxis(which)->GetLocation() )
	{
	case kLocationLeft: str = "&Left Axis"; break;
	case kLocationRight: str = "&Right Axis"; break;
	case kLocationTop: str = "&Top Axis"; break;
	case kLocationBottom: str = "&Bottom Axis"; break;
	default: str = "Error"; break;
	}
	
	AppendMenu(axisMenu, MF_SEPARATOR, 0, (LPCSTR)0 );
	
	// A settings item is always useful
	AppendMenu(axisMenu, MF_STRING, startVal+kMenuAxisRange-1, "&Axis Settings..." );
	
	AppendMenu(menu, MF_POPUP, (UINT) axisMenu, str.c_str() );
}


// Adds a popup menu for the number of ticks
//void	CAxis::AddNumberOfTicksPopup( CMenu *addMenu, LPCSTR titleString, long compare, int startVal )
void	AddNumberOfTicksPopup( HMENU addMenu, LPCSTR titleString, long compare, int startVal, BOOL bAuto )
{
	HMENU			subMenu = CreatePopupMenu();
	UINT			flag;

	//flag = GetPopupCheckedFlag( compare <= 0 );
	flag = GetPopupCheckedFlag( bAuto );
	AppendMenu(subMenu, MF_STRING | flag, startVal, "Auto" );

	for( int i = 0; i < nTickSizes; i++ )
	{
		//flag = GetPopupCheckedFlag( compare == tickSizes[i] );
		flag = GetPopupCheckedFlag( compare == tickSizes[i] && !bAuto );
		ostringstream ostr;
		string str;
		ostr<<tickSizes[i];
		str=ostr.str();
		AppendMenu(subMenu, MF_STRING | flag, startVal+i+1, str.c_str() );
	}

	AppendMenu(addMenu, MF_POPUP, (UINT) subMenu, titleString );
}


// Takes a return value from the popup menu and figures
// out what menu function it was. The value of "which"
// should be 0 for the first axis menu item.
int		InterpretAxisPopupItem( CXYPlotImpl *plot, int which, int whichResult )
{
	if( whichResult < 0 ) return kPopupError;

	// Did user say "auto range"?
	//if( whichResult == 0 ) { m_bRangeSet = !m_bRangeSet; return kPopupUpdate; }
	if( whichResult == 0 ) { plot->GetAxis(which)->SetRangeSet(!plot->GetAxis(which)->IsRangeSet()); return kPopupUpdate; }

	// font sizes
	if( whichResult < kMenuAxisLabelSize + nFontSizes )
	{
		if( whichResult < kMenuAxisTitleSize + nFontSizes ) // title font
		{
			//m_lfTitleFont.lfHeight = fontSizes[whichResult - kMenuAxisTitleSize];
			plot->GetAxis(which)->GetTitleFont().lfHeight=fontSizes[whichResult - kMenuAxisTitleSize];
		}
		else // label font
		{
			plot->GetAxis(which)->GetLabelFont().lfHeight = fontSizes[whichResult - kMenuAxisLabelSize];
		}


		return kPopupUpdate;
	}

	// Number of ticks
	if( whichResult >= kMenuAxisMajorTickCount && whichResult < kMenuAxisMajorTickCount + nTickSizes + 1 ) // major ticks
	{
		//if( whichResult - kMenuAxisMajorTickCount == 0 ) m_nTickCount = -abs(m_nTickCount);
		if( whichResult - kMenuAxisMajorTickCount == 0 )
		{
			//m_bAutoMajorTick	 = true;
			//m_nTickCount = abs(m_nTickCount);
			plot->GetAxis(which)->SetAutoMajorTick(true);
			plot->GetAxis(which)->SetTickCount(-abs(plot->GetAxis(which)->GetTickCount()));
		}
		else
		{
			//m_bAutoMajorTick  = FALSE;
			//m_nTickCount = tickSizes[whichResult-kMenuAxisMajorTickCount-1] - 1;
			plot->GetAxis(which)->SetAutoMajorTick(false);
			plot->GetAxis(which)->SetTickCount(tickSizes[whichResult-kMenuAxisMajorTickCount-1] - 1);
		}
		return kPopupUpdate;
	}
	else if( whichResult >= kMenuAxisMinorTickCount && whichResult < kMenuAxisMinorTickCount + nTickSizes + 1 ) // minor ticks
	{
		//if( (whichResult-kMenuAxisMinorTickCount) == 0 ) m_nMinorTickCount = -abs(m_nTickCount);
		if( (whichResult-kMenuAxisMinorTickCount) == 0 )
		{
			//m_bAutoMinorTick  = true;
			//m_nMinorTickCount = abs(m_nTickCount);
			plot->GetAxis(which)->SetAutoMinorTick(true);
			plot->GetAxis(which)->SetMinorTickCount(abs(plot->GetAxis(which)->GetMinorTickCount()));
		}
		else
		{
			//m_bAutoMinorTick  = false;
			//m_nMinorTickCount = tickSizes[(whichResult-kMenuAxisMinorTickCount-1)];
			plot->GetAxis(which)->SetAutoMinorTick(false);
			plot->GetAxis(which)->SetMinorTickCount(tickSizes[(whichResult-kMenuAxisMinorTickCount-1)]);
		}
		return kPopupUpdate;
	}

	// Settings (unfortunately, have to do this one in parent)

	return kPopupError;
}
