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
#include "../../Resources/PlotResources.h"
#include "../XYPlotImpl.h"
#include "../XYHandler.h"
#include "ColorControl.h"
#include <Commdlg.h>
#include <commctrl.h>
#include "DefHandlers.h"
#include <sstream>

/////////////////////////////////////////////////////////////////////////
// Axis Settings

typedef struct
{
	CXYPlotImpl *plot;
	int location;
}AxisSettingParam;

BOOL CALLBACK DefAxisSettingsFunc(HWND hWnd, UINT message, WPARAM wparam, LPARAM lparam);
BOOL CALLBACK DefAxisSettingsFNew(HWND hWnd, UINT message, WPARAM wparam, LPARAM lparam);

BOOL CALLBACK AxisTitleDlgFunc(HWND hWnd, UINT message, WPARAM wparam, LPARAM lparam);
BOOL CALLBACK AxisTickLabelDlgFunc(HWND hWnd, UINT message, WPARAM wparam, LPARAM lparam);
BOOL CALLBACK AxisRangeDlgFunc(HWND hWnd, UINT message, WPARAM wparam, LPARAM lparam);
BOOL CALLBACK AxisColorsDlgFunc(HWND hWnd, UINT message, WPARAM wparam, LPARAM lparam);
BOOL CALLBACK AxisMajorTicksDlgFunc(HWND hWnd, UINT message, WPARAM wparam, LPARAM lparam);
BOOL CALLBACK AxisMinorTicksDlgFunc(HWND hWnd, UINT message, WPARAM wparam, LPARAM lparam);

bool SetupDataFromAxis(HWND hWnd, CXYPlotImpl *plot, int location, LOGFONT &lfTitleFont, LOGFONT &lfLabelFont);
bool SaveDataToAxis(HWND hWnd, CXYPlotImpl *plot, int location, LOGFONT lfTitleFont, LOGFONT lfLabelFont);

void SetupDataForTitle(HWND hWnd, CXYPlotImpl *plot, int location, LOGFONT &lfTitleFont);
void SaveDataForTitle(HWND hWnd, CXYPlotImpl *plot, int location, LOGFONT lfTitleFont);
void SetupDataForTickLabel(HWND hWnd, CXYPlotImpl *plot, int location, LOGFONT &lfLabelFont);
void SaveDataForTickLabel(HWND hWnd, CXYPlotImpl *plot, int location, LOGFONT lfLabelFont);
void SetupDataForRange(HWND hWnd, CXYPlotImpl *plot, int location);
void SaveDataForRange(HWND hWnd, CXYPlotImpl *plot, int location);
void SetupDataForColors(HWND hWnd, CXYPlotImpl *plot, int location);
void SaveDataForColors(HWND hWnd, CXYPlotImpl *plot, int location);
void SetupDataForMajorTicks(HWND hWnd, CXYPlotImpl *plot, int location);
void SaveDataForMajorTicks(HWND hWnd, CXYPlotImpl *plot, int location);
void SetupDataForMinorTicks(HWND hWnd, CXYPlotImpl *plot, int location);
void SaveDataForMinorTicks(HWND hWnd, CXYPlotImpl *plot, int location);

string	GetMainLabel( CXYPlotImpl *plot, int index );
void InitAllTabs(HWND *hPages, AxisSettingParam *para);

/////////////////////////////////////////////////////////////////////////

bool DefAxisSettings( CXYPlotImpl *plot, HWND hWnd, int location )
{
	AxisSettingParam para;
	para.plot = plot;
	para.location = location;

	if(!CPlot::m_bNewInteractive)
	{
		if(DialogBoxParam(GetModuleHandle(NULL),MAKEINTRESOURCE(IDD_AXIS_SETTINGS), hWnd, (DLGPROC)DefAxisSettingsFunc, (LPARAM)&para))
			return true;
		else
			return false;
	}
	else
	{
		if(DialogBoxParam(GetModuleHandle(NULL),MAKEINTRESOURCE(IDD_AXISSETTINGS), hWnd, (DLGPROC)DefAxisSettingsFNew, (LPARAM)&para))
			return true;
		else
			return false;
	}
	
}

BOOL CALLBACK DefAxisSettingsFunc(HWND hWnd, UINT message, WPARAM wparam, LPARAM lparam)
{
	static CXYPlotImpl *plot;
	static int location;
	static AxisSettingParam *para;

	static LOGFONT	lfTitleFont,lfLabelFont;
	// local varibles
	string	str;
	int		num;

	int		oldHeight;
	
	HDC		hdc;
	LOGFONT	*pLogFont;
	COLORREF color=0;

	switch(message)
	{
	case WM_INITDIALOG:
		para = (AxisSettingParam *)lparam;
		plot = para->plot;
		location = para->location;

		SetupDataFromAxis(hWnd, plot, location, lfTitleFont, lfLabelFont);

		return TRUE;
	case WM_COMMAND:
		if(HIWORD (wparam) == EN_CHANGE)
		{
			switch(LOWORD(wparam))
			{
			case IDC_AS_XRANGE_LOW:
			case IDC_AS_XRANGE_HIGH:
				SendDlgItemMessage(hWnd, IDC_AS_AUTO_XRANGE, BM_SETCHECK, FALSE, 0);
				return TRUE;
			case IDC_AS_NUMBER_MAJOR_TICKS:
				SendDlgItemMessage(hWnd, IDC_AS_AUTO_MAJOR_TICKS, BM_SETCHECK, FALSE, 0);
				return TRUE;
			case IDC_AS_NUMBER_MINOR_TICKS:
				SendDlgItemMessage(hWnd, IDC_AS_AUTO_MINOR_TICKS, BM_SETCHECK, FALSE, 0);
				return TRUE;
			}
		}
		if(HIWORD (wparam) == BN_CLICKED)
		{
			if(LOWORD(wparam) == IDC_AXIS_PREVIOUS || LOWORD(wparam) == IDC_AXIS_NEXT)
			{
				SaveDataToAxis(hWnd, plot, location, lfTitleFont, lfLabelFont);
				if(LOWORD(wparam)==IDC_AXIS_PREVIOUS)
				{
					num = plot->GetAxisIndex(location)-1;
					if(num<0)num=plot->GetAxisCount()-1;
				}
				if(LOWORD(wparam)==IDC_AXIS_NEXT)
				{
					num = plot->GetAxisIndex(location)+1;
					if(num>=plot->GetAxisCount())num=0;
				}
				para->location = plot->GetAxis(num)->GetLocation();
				SendMessage(hWnd, WM_INITDIALOG, 0, (LPARAM)para);
			}

			if(LOWORD(wparam) == IDC_AS_CHOOSE_TITLE_FONT || LOWORD(wparam) == IDC_AS_CHOOSE_LABEL_FONT)
			{
				hdc = GetDC(hWnd);

				if(LOWORD(wparam) == IDC_AS_CHOOSE_TITLE_FONT)
				{
					pLogFont = &lfTitleFont;
					SendDlgItemMessage(hWnd, IDC_AS_COLOR_TITLE_FONT, WM_GETCOLOR, 0, (LPARAM)&color); 
				}
				else if(LOWORD(wparam) == IDC_AS_CHOOSE_LABEL_FONT)
				{
					pLogFont = &lfLabelFont;
					SendDlgItemMessage(hWnd, IDC_AS_COLOR_LABEL_FONT, WM_GETCOLOR, 0, (LPARAM)&color); 
				}
				oldHeight = pLogFont->lfHeight;
				pLogFont->lfHeight = -MulDiv(oldHeight, GetDeviceCaps(hdc, LOGPIXELSY), 72);

				// Font Dialog
				if( ShowFontDialog(hWnd, *pLogFont, color))
				{
					pLogFont->lfHeight = -MulDiv(pLogFont->lfHeight, 72, GetDeviceCaps(hdc, LOGPIXELSY));
					
					if(LOWORD(wparam) == IDC_AS_CHOOSE_TITLE_FONT)
					{
						SendDlgItemMessage(hWnd, IDC_AS_TITLE_FONT, WM_SETTEXT, 0, (LPARAM)GetFontDescription( &lfTitleFont ).c_str());
					}
					else if(LOWORD(wparam) == IDC_AS_CHOOSE_LABEL_FONT)
					{
						SendDlgItemMessage(hWnd, IDC_AS_LABEL_FONT, WM_SETTEXT, 0, (LPARAM)GetFontDescription( &lfLabelFont ).c_str());
					}
				}

				ReleaseDC(hWnd, hdc);
			}
		}
		switch(LOWORD(wparam))
		{
		case IDOK:
			SaveDataToAxis(hWnd, plot, location, lfTitleFont, lfLabelFont);

			EndDialog(hWnd, 1);
		case IDCANCEL:
			EndDialog(hWnd, 0);
			return TRUE;
		}
		break;
	}
	return FALSE;
}

const int nPages = 6;
BOOL CALLBACK DefAxisSettingsFNew(HWND hWnd, UINT message, WPARAM wparam, LPARAM lparam)
{
	static CXYPlotImpl *plot;
	static int location;
	static AxisSettingParam *para;

	static HWND hPage[nPages];
	static int curpage = 0;
	TCITEM tcitem;
	RECT rt;

	LPNMHDR pnmh;

	int i,num;
	string label;
	switch(message)
	{
	case WM_INITDIALOG:
		para = (AxisSettingParam *)lparam;
		plot = para->plot;
		location = para->location;

		SendDlgItemMessage(hWnd, IDC_AXIS_SETTINGS_TAB, TCM_DELETEALLITEMS, 0, 0);
		// add pages
		ZeroMemory(&tcitem, sizeof(TCITEM));
		tcitem.mask = TCIF_PARAM | TCIF_TEXT;
		tcitem.iImage = -1;
		tcitem.pszText = _T("Title");
		SendDlgItemMessage(hWnd, IDC_AXIS_SETTINGS_TAB, TCM_INSERTITEM, 0, (LPARAM)&tcitem);
		tcitem.pszText = _T("Tick label");
		SendDlgItemMessage(hWnd, IDC_AXIS_SETTINGS_TAB, TCM_INSERTITEM, 1, (LPARAM)&tcitem);
		tcitem.pszText = _T("Range");
		SendDlgItemMessage(hWnd, IDC_AXIS_SETTINGS_TAB, TCM_INSERTITEM, 2, (LPARAM)&tcitem);
		tcitem.pszText = _T("Axis color");
		SendDlgItemMessage(hWnd, IDC_AXIS_SETTINGS_TAB, TCM_INSERTITEM, 3, (LPARAM)&tcitem);
		tcitem.pszText = _T("Major ticks");
		SendDlgItemMessage(hWnd, IDC_AXIS_SETTINGS_TAB, TCM_INSERTITEM, 4, (LPARAM)&tcitem);
		tcitem.pszText = _T("Minor ticks");
		SendDlgItemMessage(hWnd, IDC_AXIS_SETTINGS_TAB, TCM_INSERTITEM, 5, (LPARAM)&tcitem);

		hPage[0] = CreateDialogParam(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_AXISSETTINGS_TITLE), GetDlgItem(hWnd, IDC_AXIS_SETTINGS_TAB), AxisTitleDlgFunc, (LPARAM)para);
		hPage[1] = CreateDialogParam(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_AXISSETTINGS_TICKLABEL), GetDlgItem(hWnd, IDC_AXIS_SETTINGS_TAB), AxisTickLabelDlgFunc, (LPARAM)para);
		hPage[2] = CreateDialogParam(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_AXISSETTINGS_RANGE), GetDlgItem(hWnd, IDC_AXIS_SETTINGS_TAB), AxisRangeDlgFunc, (LPARAM)para);
		hPage[3] = CreateDialogParam(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_AXISSETTINGS_AXISCOLOR), GetDlgItem(hWnd, IDC_AXIS_SETTINGS_TAB), AxisColorsDlgFunc, (LPARAM)para);
		hPage[4] = CreateDialogParam(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_AXISSETTINGS_MAJORTICKS), GetDlgItem(hWnd, IDC_AXIS_SETTINGS_TAB), AxisMajorTicksDlgFunc, (LPARAM)para);
		hPage[5] = CreateDialogParam(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_AXISSETTINGS_MINORTICKS), GetDlgItem(hWnd, IDC_AXIS_SETTINGS_TAB), AxisMinorTicksDlgFunc, (LPARAM)para);

		GetClientRect(GetDlgItem(hWnd, IDC_AXIS_SETTINGS_TAB), &rt);
		rt.top += 20;
		rt.bottom -= 8;
		rt.left += 8;
		rt.right -= 8;

		for(i=0; i<nPages; i++)
		{
			MoveWindow(hPage[i], rt.left, rt.top, rt.right-rt.left, rt.bottom-rt.top, TRUE);
			if(i==curpage)
			{
				ShowWindow(hPage[i], SW_SHOW);
			}
			else
			{
				ShowWindow(hPage[i], SW_HIDE);
			}
		}
		

		//create the combo box
		//i = plot->GetAxisIndex(location);
		SendDlgItemMessage(hWnd, IDC_AS_LISTAXES, CB_RESETCONTENT, 0, 0);
		for(i=plot->GetAxisCount()-1; i>=0; i--)
		{
			label = GetMainLabel(plot, i);
			SendDlgItemMessage(hWnd, IDC_AS_LISTAXES, CB_INSERTSTRING, 0, (LPARAM)label.c_str());
		}
		SendDlgItemMessage(hWnd, IDC_AS_LISTAXES, CB_SETCURSEL, (WPARAM)plot->GetAxisIndex(location), 0);

		// check the save when switch box
		SendDlgItemMessage(hWnd, IDC_AS_SAVE_WHEN_SWITCHING, BM_SETCHECK, FALSE, 0);

		return TRUE;
	case WM_DESTROY:
		for(i=0; i<nPages; i++)
		{
			if(IsWindow(hPage[i]))
				DestroyWindow(hPage[i]);
		}
		return TRUE;;
	case WM_COMMAND:
		if(HIWORD (wparam) == CBN_SELCHANGE && LOWORD(wparam) == IDC_AS_LISTAXES )
		{
			num = SendDlgItemMessage(hWnd, IDC_AS_LISTAXES, CB_GETCURSEL, 0, 0);
			if( SendDlgItemMessage(hWnd, IDC_AS_SAVE_WHEN_SWITCHING, BM_GETCHECK, 0, 0)==BST_CHECKED )
			{
				for(i=0; i<nPages; i++)
				{
					SendMessage(hPage[i],	WM_COMMAND, IDOK, 0);
				}
			}
			location = plot->GetAxis(num)->GetLocation();
			para->location = location;
			InitAllTabs(hPage, para);
			return TRUE;
		}
		if(HIWORD (wparam) == BN_CLICKED)
		{
			if(LOWORD(wparam)==IDC_AXIS_PREVIOUS || LOWORD(wparam)==IDC_AXIS_NEXT)
			{
				num = SendDlgItemMessage(hWnd, IDC_AS_LISTAXES, CB_GETCURSEL, 0, 0);
				if( SendDlgItemMessage(hWnd, IDC_AS_SAVE_WHEN_SWITCHING, BM_GETCHECK, 0, 0)==BST_CHECKED )
				{
					for(i=0; i<nPages; i++)
					{
						SendMessage(hPage[i],	WM_COMMAND, IDOK, 0);
					}
				}
				if(LOWORD(wparam)==IDC_DATA_PREVIOUS)
				{
					num--;
					if (num<0 ) num = plot->GetAxisCount()-1;
				}
				else
				{
					num++;
					if( num>= plot->GetAxisCount() )num=0;
				}
				SendDlgItemMessage(hWnd, IDC_AS_LISTAXES, CB_SETCURSEL, (WPARAM)num, 0);
				location = plot->GetAxis(num)->GetLocation();
				para->location = location;
				InitAllTabs(hPage, para);
				return TRUE;
			}
		}
		switch(LOWORD(wparam))
		{
		case IDOK:
			for(i=0; i<nPages; i++)
			{
				SendMessage(hPage[i], WM_COMMAND, IDOK, 0);
			}
			
			EndDialog(hWnd, 1);
		case IDCANCEL:
			EndDialog(hWnd, 0);
			return TRUE;
		}
		break;
	case WM_NOTIFY:
		pnmh = (LPNMHDR) lparam;
		switch(pnmh->code)
		{
			case TCN_SELCHANGE:
			// Apply Changes
			curpage = TabCtrl_GetCurSel(GetDlgItem(hWnd, IDC_AXIS_SETTINGS_TAB));
			for(i=0; i<nPages; i++)
			{
				if(i!=curpage)
					ShowWindow(hPage[i], SW_HIDE);
				else
					ShowWindow(hPage[i], SW_SHOW);
			}
			return TRUE;
		}
		break;
	}
	return FALSE;
}

bool SetupDataFromAxis(HWND hWnd, CXYPlotImpl *plot, int location, LOGFONT &lfTitleFont, LOGFONT &lfLabelFont)
{
	ostringstream ostr;
	string str;
	ostr<<"Axis "<<plot->GetAxisIndex(location)+1<<" of "<<plot->GetAxisCount();
	str=ostr.str();
	SendDlgItemMessage(hWnd, IDC_AS_LABEL, WM_SETTEXT, 0, (LPARAM)str.c_str());
	
	SetupDataForTitle(hWnd, plot, location, lfTitleFont);
	SetupDataForTickLabel(hWnd, plot, location, lfLabelFont);
	SetupDataForRange(hWnd, plot, location);
	SetupDataForColors(hWnd, plot, location);
	SetupDataForMajorTicks(hWnd, plot, location);
	SetupDataForMinorTicks(hWnd, plot, location);
	
	return true;
}

bool SaveDataToAxis(HWND hWnd, CXYPlotImpl *plot, int location, LOGFONT lfTitleFont, LOGFONT lfLabelFont)
{
	SaveDataForTitle(hWnd, plot, location, lfTitleFont);
	SaveDataForTickLabel(hWnd, plot, location, lfLabelFont);
	SaveDataForRange(hWnd, plot, location);
	SaveDataForColors(hWnd, plot, location);
	SaveDataForMajorTicks(hWnd, plot, location);
	SaveDataForMinorTicks(hWnd, plot, location);

	return true;
}

void SetupDataForTitle(HWND hWnd, CXYPlotImpl *plot, int location, LOGFONT &lfTitleFont)
{
	CAxis *axis = plot->GetAxisByLocation(location);
	
	// Deal with the title
	SendDlgItemMessage(hWnd, IDC_AS_PLOT_TITLE, WM_SETTEXT, 0, (LPARAM)axis->GetTitle().c_str());
	SendDlgItemMessage(hWnd, IDC_AS_COLOR_TITLE_FONT, WM_SETCOLOR, 0, (LPARAM)axis->GetTitleColor());
	lfTitleFont = axis->GetTitleFont();
	SendDlgItemMessage(hWnd, IDC_AS_TITLE_FONT, WM_SETTEXT, 0, (LPARAM)GetFontDescription( &axis->GetTitleFont() ).c_str());
}
void SaveDataForTitle(HWND hWnd, CXYPlotImpl *plot, int location, LOGFONT lfTitleFont)
{
	// local varibles
	char	strtmp[1024];
	CAxis	*axis = plot->GetAxisByLocation(location);
	COLORREF color;
	
	// Deal with the title
	GetWindowText(GetDlgItem(hWnd, IDC_AS_PLOT_TITLE), strtmp, 1024);
	axis->SetTitle(strtmp);
	SendDlgItemMessage(hWnd, IDC_AS_COLOR_TITLE_FONT, WM_GETCOLOR, 0, (LPARAM)&color); 
	axis->SetTitleColor(color);
	axis->SetTitleFont(lfTitleFont);
}

void SetupDataForTickLabel(HWND hWnd, CXYPlotImpl *plot, int location, LOGFONT &lfLabelFont)
{
	CAxis *axis = plot->GetAxisByLocation(location);
	
	// Deal with the tick label
	SendDlgItemMessage(hWnd, IDC_AS_COLOR_LABEL_FONT, WM_SETCOLOR, 0, (LPARAM)axis->GetTickLabelColor());
	lfLabelFont = axis->GetLabelFont();
	SendDlgItemMessage(hWnd, IDC_AS_LABEL_FONT, WM_SETTEXT, 0, (LPARAM)GetFontDescription( &axis->GetLabelFont() ).c_str()); 
}
void SaveDataForTickLabel(HWND hWnd, CXYPlotImpl *plot, int location, LOGFONT lfLabelFont)
{
	// local varibles
	CAxis	*axis = plot->GetAxisByLocation(location);
	COLORREF color;
	
	// Deal with the tick label
	SendDlgItemMessage(hWnd, IDC_AS_COLOR_LABEL_FONT, WM_GETCOLOR, 0, (LPARAM)&color); 
	axis->SetTickLabelColor(color);
	axis->SetLabelFont(lfLabelFont);
}

void SetupDataForRange(HWND hWnd, CXYPlotImpl *plot, int location)
{
	CAxis *axis = plot->GetAxisByLocation(location);
	
	ostringstream ostr;
	string str;
	
	// Deal with the range
	ostr<<axis->GetLowerRange();
	str=ostr.str();
	SendDlgItemMessage(hWnd, IDC_AS_XRANGE_LOW, WM_SETTEXT, 0, (LPARAM)str.c_str());
	ostr.str("");
	ostr<<axis->GetUpperRange();
	str=ostr.str();
	SendDlgItemMessage(hWnd, IDC_AS_XRANGE_HIGH, WM_SETTEXT, 0, (LPARAM)str.c_str());
	SendDlgItemMessage(hWnd, IDC_AS_AUTO_XRANGE, BM_SETCHECK, !axis->IsRangeSet(), 0);
}
void SaveDataForRange(HWND hWnd, CXYPlotImpl *plot, int location)
{
	// local varibles
	char	strtmp[1024];
	CAxis	*axis = plot->GetAxisByLocation(location);
	
	double	xRange[2];
	
	int		check;
	
	// Deal with the range
	GetWindowText(GetDlgItem(hWnd, IDC_AS_XRANGE_LOW), strtmp, 1024);
	xRange[0]=atof(strtmp);
	GetWindowText(GetDlgItem(hWnd, IDC_AS_XRANGE_HIGH), strtmp, 1024);
	xRange[1]=atof(strtmp);
	check = SendDlgItemMessage(hWnd, IDC_AS_AUTO_XRANGE, BM_GETCHECK, 0, 0);
	if(check==BST_CHECKED)
	{
		axis->SetRangeSet( false );
	}
	else if(check==BST_UNCHECKED)
	{
		axis->SetRange( true, xRange[0], xRange[1] );
	}
}

void SetupDataForColors(HWND hWnd, CXYPlotImpl *plot, int location)
{
	CAxis *axis = plot->GetAxisByLocation(location);
	// Deal with the colors
	SendDlgItemMessage(hWnd, IDC_AS_COLOR_SAMECHECK, BM_SETCHECK, axis->IsSameColor(), 0);
	SendDlgItemMessage(hWnd, IDC_AS_COLOR_AXIS, WM_SETCOLOR, 0, (LPARAM)axis->GetAxisColor());

	ostringstream ostr;
	string str;
	ostr<<plot->GetAxisByLocation(location)->GetAxisSize();
	str=ostr.str();
	SendDlgItemMessage(hWnd, IDC_AS_AXIS_SIZE, WM_SETTEXT, 0, (LPARAM)str.c_str());
	SendDlgItemMessage(hWnd, IDC_AS_AXIS_STYLE, CB_RESETCONTENT, 0, 0);
	SendMessage(GetDlgItem(hWnd,IDC_AS_AXIS_STYLE), CB_ADDSTRING, 0, (LPARAM)"Solid _______________________");
	SendMessage(GetDlgItem(hWnd,IDC_AS_AXIS_STYLE), CB_ADDSTRING, 0, (LPARAM)"Dashed _ _ _ _ _ _ _ _ _ _ _ _ _ _");
	SendMessage(GetDlgItem(hWnd,IDC_AS_AXIS_STYLE), CB_ADDSTRING, 0, (LPARAM)"Dotted . . . . . . . . . . . . . . . . . . . . . .");
	SendMessage(GetDlgItem(hWnd,IDC_AS_AXIS_STYLE), CB_ADDSTRING, 0, (LPARAM)"Dash-Dot _ . _ . _ . _ . _ . _ . _ . _ .");
	SendMessage(GetDlgItem(hWnd,IDC_AS_AXIS_STYLE), CB_ADDSTRING, 0, (LPARAM)"Dash-Dot-Dot _ . . _ . . _ . . _ . . _ .");
	SendMessage(GetDlgItem(hWnd,IDC_AS_AXIS_STYLE), CB_SETCURSEL, (WPARAM)plot->GetAxisByLocation(location)->GetLineStyle(), 0);
}
void SaveDataForColors(HWND hWnd, CXYPlotImpl *plot, int location)
{
	// local varibles
	CAxis	*axis = plot->GetAxisByLocation(location);
	
	char strtmp[1024];
	
	COLORREF color;
	int		check;
	int		num;

	
	// Deal with the colors
	check = SendDlgItemMessage(hWnd, IDC_AS_COLOR_SAMECHECK, BM_GETCHECK, 0, 0);
	if(check==BST_CHECKED)
	{
		axis->SetSameColor(true);
	}
	else if(check==BST_UNCHECKED)
	{
		axis->SetSameColor(false);
	}
	SendDlgItemMessage(hWnd, IDC_AS_COLOR_AXIS, WM_GETCOLOR, 0, (LPARAM)&color); 
	axis->SetAxisColor(color);

	GetWindowText(GetDlgItem(hWnd, IDC_AS_AXIS_SIZE), strtmp, 1024);
	plot->GetAxisByLocation(location)->SetAxisSize(atoi(strtmp));
	num = SendDlgItemMessage(hWnd, IDC_AS_AXIS_STYLE, CB_GETCURSEL, 0, 0);
	plot->GetAxisByLocation(location)->SetLineStyle(num);
}

void SetupDataForMajorTicks(HWND hWnd, CXYPlotImpl *plot, int location)
{
	CAxis *axis = plot->GetAxisByLocation(location);
	
	ostringstream ostr;
	string str;
	
	// Deal with the major tick marks
	ostr<<axis->GetTickCount()+1;
	str=ostr.str();
	SendDlgItemMessage(hWnd, IDC_AS_NUMBER_MAJOR_TICKS, WM_SETTEXT, 0, (LPARAM)str.c_str());
	SendDlgItemMessage(hWnd, IDC_AS_AUTO_MAJOR_TICKS, BM_SETCHECK, axis->IsAutoMajorTick(), 0);
	ostr.str("");
	ostr<<axis->GetTickLength()/10.0;
	str=ostr.str();
	SendDlgItemMessage(hWnd, IDC_AS_MAJOR_TICK_LENGTH, WM_SETTEXT, 0, (LPARAM)str.c_str());
	ostr.str("");
	ostr<<axis->GetTickSize();
	str=ostr.str();
	SendDlgItemMessage(hWnd, IDC_AS_MAJOR_TICK_SIZE, WM_SETTEXT, 0, (LPARAM)str.c_str());
	SendDlgItemMessage(hWnd, IDC_AS_COLOR_MAJORTICK, WM_SETCOLOR, 0, (LPARAM)axis->GetTickColor());
	SendDlgItemMessage(hWnd, IDC_AS_MAJORTICK_POSITION, CB_RESETCONTENT, 0, 0);
	SendDlgItemMessage(hWnd, IDC_AS_MAJORTICK_POSITION, CB_ADDSTRING, 0, (LPARAM)"None");
	SendDlgItemMessage(hWnd, IDC_AS_MAJORTICK_POSITION, CB_ADDSTRING, 0, (LPARAM)"Inner");
	SendDlgItemMessage(hWnd, IDC_AS_MAJORTICK_POSITION, CB_ADDSTRING, 0, (LPARAM)"Outer");
	SendDlgItemMessage(hWnd, IDC_AS_MAJORTICK_POSITION, CB_ADDSTRING, 0, (LPARAM)"Both");
	SendDlgItemMessage(hWnd, IDC_AS_MAJORTICK_POSITION, CB_SETCURSEL, (WPARAM)axis->GetTickPosition(), 0);
}
void SaveDataForMajorTicks(HWND hWnd, CXYPlotImpl *plot, int location)
{
	// local varibles
	char	strtmp[1024];
	int		num;
	CAxis	*axis = plot->GetAxisByLocation(location);
	
	
	COLORREF color;
	int		check;
	
	// Deal with the major tick marks
	GetWindowText(GetDlgItem(hWnd, IDC_AS_NUMBER_MAJOR_TICKS), strtmp, 1024);
	axis->SetTickCount(abs(atoi(strtmp))-1);
	check = SendDlgItemMessage(hWnd, IDC_AS_AUTO_MAJOR_TICKS, BM_GETCHECK, 0, 0);
	if(check==BST_CHECKED)
	{
		axis->SetAutoMajorTick(true);
	}
	else if(check==BST_UNCHECKED)
	{
		axis->SetAutoMajorTick(false);
	}
	GetWindowText(GetDlgItem(hWnd, IDC_AS_MAJOR_TICK_LENGTH), strtmp, 1024);
	axis->SetTickLength((int)fabs(atof(strtmp))*10);
	GetWindowText(GetDlgItem(hWnd, IDC_AS_MAJOR_TICK_SIZE), strtmp, 1024);
	axis->SetTickSize((int)fabs(atof(strtmp)));
	SendDlgItemMessage(hWnd, IDC_AS_COLOR_MAJORTICK, WM_GETCOLOR, 0, (LPARAM)&color); 
	axis->SetTickColor(color);
	num = SendDlgItemMessage(hWnd, IDC_AS_MAJORTICK_POSITION, CB_GETCURSEL, 0, 0);
	axis->SetTickPosition(num);
}

void SetupDataForMinorTicks(HWND hWnd, CXYPlotImpl *plot, int location)
{
	CAxis *axis = plot->GetAxisByLocation(location);
	
	ostringstream ostr;
	string str;
	
	// Deal with the minor tick marks
	ostr<<axis->GetMinorTickCount();
	str=ostr.str();
	SendDlgItemMessage(hWnd, IDC_AS_NUMBER_MINOR_TICKS, WM_SETTEXT, 0, (LPARAM)str.c_str());
	SendDlgItemMessage(hWnd, IDC_AS_AUTO_MINOR_TICKS, BM_SETCHECK, axis->IsAutoMinorTick(), 0);
	ostr.str("");
	ostr<<axis->GetMinorTickLength()/10.0;
	str=ostr.str();
	SendDlgItemMessage(hWnd, IDC_AS_MINOR_TICK_LENGTH, WM_SETTEXT, 0, (LPARAM)str.c_str());
	ostr.str("");
	ostr<<axis->GetMinorTickSize();
	str=ostr.str();
	SendDlgItemMessage(hWnd, IDC_AS_MINOR_TICK_SIZE, WM_SETTEXT, 0, (LPARAM)str.c_str());
	SendDlgItemMessage(hWnd, IDC_AS_COLOR_MINORTICK, WM_SETCOLOR, 0, (LPARAM)axis->GetMinorTickColor());
	SendDlgItemMessage(hWnd, IDC_AS_MINORTICK_POSITION, CB_RESETCONTENT, 0, 0);
	SendDlgItemMessage(hWnd, IDC_AS_MINORTICK_POSITION, CB_ADDSTRING, 0, (LPARAM)"None");
	SendDlgItemMessage(hWnd, IDC_AS_MINORTICK_POSITION, CB_ADDSTRING, 0, (LPARAM)"Inner");
	SendDlgItemMessage(hWnd, IDC_AS_MINORTICK_POSITION, CB_ADDSTRING, 0, (LPARAM)"Outer");
	SendDlgItemMessage(hWnd, IDC_AS_MINORTICK_POSITION, CB_ADDSTRING, 0, (LPARAM)"Both");
	SendDlgItemMessage(hWnd, IDC_AS_MINORTICK_POSITION, CB_SETCURSEL, (WPARAM)axis->GetMinorTickPosition(), 0);
}
void SaveDataForMinorTicks(HWND hWnd, CXYPlotImpl *plot, int location)
{
	// local varibles
	char	strtmp[1024];
	int		num;
	CAxis	*axis = plot->GetAxisByLocation(location);
	
	
	COLORREF color;
	int		check;
	
	// Deal with the minor tick marks
	GetWindowText(GetDlgItem(hWnd, IDC_AS_NUMBER_MINOR_TICKS), strtmp, 1024);
	axis->SetMinorTickCount(abs(atoi(strtmp)));
	check = SendDlgItemMessage(hWnd, IDC_AS_AUTO_MINOR_TICKS, BM_GETCHECK, 0, 0);
	if(check==BST_CHECKED)
	{
		axis->SetAutoMinorTick(true);
	}
	else if(check==BST_UNCHECKED)
	{
		axis->SetAutoMinorTick(false);
	}
	GetWindowText(GetDlgItem(hWnd, IDC_AS_MINOR_TICK_LENGTH), strtmp, 1024);
	axis->SetMinorTickLength((int)fabs(atof(strtmp))*10);
	GetWindowText(GetDlgItem(hWnd, IDC_AS_MINOR_TICK_SIZE), strtmp, 1024);
	axis->SetMinorTickSize((int)fabs(atof(strtmp)));
	SendDlgItemMessage(hWnd, IDC_AS_COLOR_MINORTICK, WM_GETCOLOR, 0, (LPARAM)&color); 
	axis->SetMinorTickColor(color);
	num = SendDlgItemMessage(hWnd, IDC_AS_MINORTICK_POSITION, CB_GETCURSEL, 0, 0);
	axis->SetMinorTickPosition(num);
}

string	GetMainLabel( CXYPlotImpl *plot, int index )
{
	if(index<0 || index >= plot->GetAxisCount())return "";
	
	string		 location;
	CAxis		*axis = plot->GetAxis(index);//&m_pAxes[index];
	
	if( axis != NULL )
	{
		switch( axis->GetLocation() )
		{
		case kLocationBottom: location = "bottom"; break;
		case kLocationLeft: location = "left"; break;
		case kLocationRight: location = "right"; break;
		case kLocationTop: location = "top"; break;
		default: break;
		}
	}
	else location = "";
	
	ostringstream ostr;
	ostr<<"Axis "<<index+1<<" of "<<plot->GetAxisCount()<<", ("<<location.c_str()<<")";
		
	return ostr.str();
}

void InitAllTabs(HWND *hPages, AxisSettingParam *para)
{
	for(int i=0; i<nPages; i++)
	{
		SendMessage(hPages[i], WM_INITDIALOG, 0, (LPARAM)para);
	}
}

BOOL CALLBACK AxisTitleDlgFunc(HWND hWnd, UINT message, WPARAM wparam, LPARAM lparam)
{
	static AxisSettingParam *para;
	static CXYPlotImpl	*plot;
	static int location;
	static LOGFONT	lfTitleFont;
	
	// local varibles
	HDC		hdc;
	LOGFONT	*pLogFont;
	COLORREF color;

	int oldHeight;
	
	switch(message)
	{
	case WM_INITDIALOG:
		para = (AxisSettingParam *)lparam;
		plot = para->plot;
		location = para->location;

		// Deal with the title
		SetupDataForTitle(hWnd, plot, location, lfTitleFont);
		return TRUE;
	case WM_COMMAND:
		
		// font buttons are clicked
		if(HIWORD (wparam) == BN_CLICKED)
		{
			if(LOWORD(wparam)==IDC_AS_CHOOSE_TITLE_FONT)
			{
				hdc = GetDC(hWnd);
				
				pLogFont = &lfTitleFont;
				SendDlgItemMessage(hWnd, IDC_PS_COLOR_TITLE_FONT, WM_GETCOLOR, 0, (LPARAM)&color); 
				
				oldHeight = pLogFont->lfHeight;
				pLogFont->lfHeight = -MulDiv(oldHeight, GetDeviceCaps(hdc, LOGPIXELSY), 72);
				
				// Font Dialog				
				if( ShowFontDialog(hWnd, *pLogFont, color))
				{
					pLogFont->lfHeight = -MulDiv(pLogFont->lfHeight, 72, GetDeviceCaps(hdc, LOGPIXELSY));
					
					SendDlgItemMessage(hWnd, IDC_AS_TITLE_FONT, WM_SETTEXT, 0, (LPARAM)GetFontDescription( &lfTitleFont ).c_str());
					
				}
				
				ReleaseDC(hWnd, hdc);
			}
		}
		switch(LOWORD(wparam))
		{
		case IDOK:
			SaveDataForTitle(hWnd, plot, location, lfTitleFont);
			return TRUE;
		}
		break;
	}

	return FALSE;
}


BOOL CALLBACK AxisTickLabelDlgFunc(HWND hWnd, UINT message, WPARAM wparam, LPARAM lparam)
{
	static AxisSettingParam *para;
	static CXYPlotImpl	*plot;
	static int location;
	static LOGFONT	lfLabelFont;
	
	// local varibles
	HDC		hdc;
	LOGFONT	*pLogFont;
	COLORREF color;
	
	int oldHeight;
	
	switch(message)
	{
	case WM_INITDIALOG:
		para = (AxisSettingParam *)lparam;
		plot = para->plot;
		location = para->location;
		
		// Deal with the title
		SetupDataForTickLabel(hWnd, plot, location, lfLabelFont);
		return TRUE;
	case WM_COMMAND:
		
		// font buttons are clicked
		if(HIWORD (wparam) == BN_CLICKED)
		{
			if(LOWORD(wparam)==IDC_AS_CHOOSE_LABEL_FONT)
			{
				hdc = GetDC(hWnd);
				
				pLogFont = &lfLabelFont;
				SendDlgItemMessage(hWnd, IDC_PS_COLOR_TITLE_FONT, WM_GETCOLOR, 0, (LPARAM)&color); 
				
				oldHeight = pLogFont->lfHeight;
				pLogFont->lfHeight = -MulDiv(oldHeight, GetDeviceCaps(hdc, LOGPIXELSY), 72);
				
				// Font Dialog				
				if( ShowFontDialog(hWnd, *pLogFont, color))
				{
					pLogFont->lfHeight = -MulDiv(pLogFont->lfHeight, 72, GetDeviceCaps(hdc, LOGPIXELSY));
					
					SendDlgItemMessage(hWnd, IDC_AS_LABEL_FONT, WM_SETTEXT, 0, (LPARAM)GetFontDescription( &lfLabelFont ).c_str());
					
				}
				
				ReleaseDC(hWnd, hdc);
			}
		}
		switch(LOWORD(wparam))
		{
		case IDOK:
			SaveDataForTickLabel(hWnd, plot, location, lfLabelFont);
			return TRUE;
		}
		break;
	}
	
	return FALSE;
}

BOOL CALLBACK AxisRangeDlgFunc(HWND hWnd, UINT message, WPARAM wparam, LPARAM lparam)
{
	static AxisSettingParam *para;
	static CXYPlotImpl	*plot;
	static int location;
	

	switch(message)
	{
	case WM_INITDIALOG:
		para = (AxisSettingParam *)lparam;
		plot = para->plot;
		location = para->location;
		
		// Deal with the title
		SetupDataForRange(hWnd, plot, location);
		return TRUE;
	case WM_COMMAND:
		
		// font buttons are clicked
		if(HIWORD (wparam) == EN_CHANGE)
			{
				switch(LOWORD(wparam))
				{
				case IDC_AS_XRANGE_LOW:
				case IDC_AS_XRANGE_HIGH:
					//bAutoXRange = false;
					SendDlgItemMessage(hWnd, IDC_AS_AUTO_XRANGE, BM_SETCHECK, FALSE, 0);
					return TRUE;
				}
		}
		switch(LOWORD(wparam))
		{
		case IDOK:
			SaveDataForRange(hWnd, plot, location);
			return TRUE;
		}
		break;
	}
	
	return FALSE;
}

BOOL CALLBACK AxisColorsDlgFunc(HWND hWnd, UINT message, WPARAM wparam, LPARAM lparam)
{
	static AxisSettingParam *para;
	static CXYPlotImpl	*plot;
	static int location;
	
	switch(message)
	{
	case WM_INITDIALOG:
		para = (AxisSettingParam *)lparam;
		plot = para->plot;
		location = para->location;
		
		// Deal with the title
		SetupDataForColors(hWnd, plot, location);
		return TRUE;
	case WM_COMMAND:
		switch(LOWORD(wparam))
		{
		case IDOK:
			SaveDataForColors(hWnd, plot, location);
			return TRUE;
		}
		break;
	}
	
	return FALSE;
}

BOOL CALLBACK AxisMajorTicksDlgFunc(HWND hWnd, UINT message, WPARAM wparam, LPARAM lparam)
{
	static AxisSettingParam *para;
	static CXYPlotImpl	*plot;
	static int location;
	
	switch(message)
	{
	case WM_INITDIALOG:
		para = (AxisSettingParam *)lparam;
		plot = para->plot;
		location = para->location;
		
		// Deal with the title
		SetupDataForMajorTicks(hWnd, plot, location);
		return TRUE;
	case WM_COMMAND:
		if(HIWORD (wparam) == EN_CHANGE)
		{
			switch(LOWORD(wparam))
			{
			case IDC_AS_NUMBER_MAJOR_TICKS:
				SendDlgItemMessage(hWnd, IDC_AS_AUTO_MAJOR_TICKS, BM_SETCHECK, FALSE, 0);
				return TRUE;
			}
		}
		switch(LOWORD(wparam))
		{
		case IDOK:
			SaveDataForMajorTicks(hWnd, plot, location);
			return TRUE;
		}
		break;
	}
	
	return FALSE;
}

BOOL CALLBACK AxisMinorTicksDlgFunc(HWND hWnd, UINT message, WPARAM wparam, LPARAM lparam)
{
	static AxisSettingParam *para;
	static CXYPlotImpl	*plot;
	static int location;
	
	switch(message)
	{
	case WM_INITDIALOG:
		para = (AxisSettingParam *)lparam;
		plot = para->plot;
		location = para->location;
		
		// Deal with the title
		SetupDataForMinorTicks(hWnd, plot, location);
		return TRUE;
	case WM_COMMAND:
		if(HIWORD (wparam) == EN_CHANGE)
		{
			switch(LOWORD(wparam))
			{
			case IDC_AS_NUMBER_MINOR_TICKS:
				SendDlgItemMessage(hWnd, IDC_AS_AUTO_MINOR_TICKS, BM_SETCHECK, FALSE, 0);
				return TRUE;
			}
		}
		switch(LOWORD(wparam))
		{
		case IDOK:
			SaveDataForMinorTicks(hWnd, plot, location);
			return TRUE;
		}
		break;
	}
	
	return FALSE;
}