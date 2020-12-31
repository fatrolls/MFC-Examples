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

#ifndef __DEFHANDLERS_H_122333444455555__
#define __DEFHANDLERS_H_122333444455555__

#include <string>
using namespace std;

#pragma comment(lib,"comctl32.lib")

class CXYPlotImpl;

const int		fontSizes[] = {8, 10, 12, 16, 20, 24, 30, 36, 42, 48, 54, 60, 72, 84, 96, 108 };
const int		nFontSizes = 16;

bool	DefDataSettings( CXYPlotImpl *plot, HWND hWnd, int whichDataSet );
bool	DefAxisSettings( CXYPlotImpl *plot, HWND hWnd, int location );
bool	DefPlotSettings( CXYPlotImpl *plot, HWND hWnd );

int		DefContextMenu( CXYPlotImpl *plot, HMENU hMenu, HWND hWnd, POINT point );

string	GetFontDescription( LOGFONT *font );

UINT	GetPopupCheckedFlag( BOOL how );
bool	ShowFileDialog(HWND hWnd, bool open, string &filename, LPCSTR filter="All Files(*.*)\0*.*\0Text Files(*.txt)\0*.TXT\0");
bool	ShowFontDialog(HWND hWnd, LOGFONT &logfont, COLORREF &color);
bool	ShowColorDialog(HWND hWnd, COLORREF &cr);

#endif
