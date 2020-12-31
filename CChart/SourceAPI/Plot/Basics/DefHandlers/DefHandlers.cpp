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
#include "DefHandlers.h"
#include "../XYPlotImpl.h"
#include <commdlg.h>
#include <sstream>

// Returns a string containing the name and font size of
// the passed font
string	GetFontDescription( LOGFONT *font )
{
	if( font == NULL ) return "";

	ostringstream ostr;
	ostr<<font->lfHeight<<" point "<<font->lfFaceName;
	return ostr.str();
}

UINT	GetPopupCheckedFlag( BOOL how )
{
	if( how ) return MF_CHECKED;
	else return MF_UNCHECKED;
}

bool	ShowFileDialog(HWND hWnd, bool open, string &filename, LPCSTR filter)
{
	OPENFILENAME ofn;       // common dialog box structure
	char szFile[260];       // buffer for file name
	
	ZeroMemory(&ofn, sizeof(OPENFILENAME));
	szFile[0] = '\0'; 
	ofn.lStructSize = sizeof(OPENFILENAME); 
	ofn.hwndOwner = hWnd; 
	ofn.lpstrFilter = filter; 
	ofn.lpstrCustomFilter = (LPSTR)NULL; 
	ofn.nMaxCustFilter = 0L; 
	ofn.nFilterIndex = 1L; 
	ofn.lpstrFile= szFile; 
	ofn.nMaxFile = sizeof(szFile); 
	//ofn.lpstrFileTitle = szFileTitle; 
	//ofn.nMaxFileTitle = sizeof(szFileTitle); 
	ofn.lpstrInitialDir = (LPSTR) NULL; 
	ofn.lpstrTitle = (LPSTR)NULL; 
	ofn.lpstrInitialDir = (LPSTR)NULL; 
	ofn.Flags = OFN_SHOWHELP | OFN_OVERWRITEPROMPT; 
	ofn.nFileOffset = 0; 
	ofn.nFileExtension = 0; 
	//ofn.lpstrTitle = szTitle; 
	//ofn.lpstrDefExt = szDefExt; 
	
	if(open)
	{
		if( GetOpenFileName(&ofn) == TRUE)
		{
			filename = ofn.lpstrFile;
			return true;
		}
	}
	else
	{
		if( GetSaveFileName(&ofn) == TRUE)
		{
			filename = ofn.lpstrFile;
			return true;
		}
	}
	return false;
}

bool	ShowFontDialog(HWND hWnd, LOGFONT &logfont, COLORREF &color)
{
	CHOOSEFONT cf;

	ZeroMemory(&cf, sizeof(CHOOSEFONT));
	cf.lStructSize = sizeof (CHOOSEFONT);
	cf.hwndOwner = hWnd;
	cf.hDC = (HDC)NULL; 
	cf.lpLogFont = &logfont;
	cf.iPointSize = 0; 
	cf.Flags = CF_SCREENFONTS | CF_INITTOLOGFONTSTRUCT;
	cf.rgbColors = color;
	cf.lCustData = 0L;
	cf.lpfnHook = (LPCFHOOKPROC)NULL; 
	cf.lpTemplateName = (LPSTR)NULL; 
	cf.hInstance = (HINSTANCE) NULL; 
	cf.lpszStyle = (LPSTR)NULL; 
	cf.nFontType = SCREEN_FONTTYPE; 
	cf.nSizeMin = 0; 
	cf.nSizeMax = 0; 
	
	if (ChooseFont(&cf)==TRUE)
	{
		color = cf.rgbColors;
		return true;
	}
	else
	{
		return false;
	}
}

bool	ShowColorDialog(HWND hWnd, COLORREF &cr)
{
	CHOOSECOLOR cc;
	COLORREF crCustColors[16];
	cc.lStructSize=sizeof(CHOOSECOLOR);
	cc.hwndOwner=hWnd;
	cc.hInstance=NULL;
	cc.rgbResult=cr;
	cc.lpCustColors =crCustColors;
	cc.Flags=CC_RGBINIT|CC_FULLOPEN|CC_ANYCOLOR;
	cc.lCustData=0;
	cc.lpfnHook=NULL;
	cc.lpTemplateName=NULL;
	BOOL ret=ChooseColor(&cc);
	if(ret)cr=cc.rgbResult;
	return ret==TRUE;
}