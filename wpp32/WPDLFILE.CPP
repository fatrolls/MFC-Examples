//////////////////////////////////////////////////////////
// WINDOWS++ CLASS LIBRARY.  Copyright 1992 Paul DiLascia.
// FILE: WPDLFILE.CPP
//
// Implementation of file dialogs.

#include "wpp.h"

typedef UINT (CALLBACK *HOOKFN)(HWND, UINT, WPARAM, LPARAM);

const OFN_DEFAULT = OFN_ENABLEHOOK | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY;
const OFN_OPENDEFAULT = OFN_DEFAULT | OFN_FILEMUSTEXIST;
const OFN_SAVEDEFAULT = OFN_DEFAULT | OFN_OVERWRITEPROMPT;

const char DEFAULTFILT[] = "Any File (*.*)\0*.*\0";

//////////////////
// Create File Open dialog.
// 
WPDlgFileOpen::WPDlgFileOpen(WPWin *pwin, char* fname, LPCSTR title) 
	: WPDialogModal(NULL, pwin)
{
	filename = fname;
	tempbuf[0]=0;
	memset(&ofn, 0, sizeof(ofn));
	ofn.lStructSize=sizeof(ofn);
	ofn.hwndOwner = GetHwnd(pwin);
	ofn.lpstrFile=tempbuf;
	ofn.nMaxFile=sizeof(tempbuf);
	ofn.lpstrTitle= (LPSTR)title;
	ofn.Flags= OFN_OPENDEFAULT;
	ofn.lpfnHook = (HOOKFN)theApp->getDlgProc();
	ofn.nFilterIndex=1;
	setFilter(DEFAULTFILT);
}

//////////////////
// Create window: just call COMMDLG.
// 
BOOL WPDlgFileOpen::createWin()
{ 
	if ((result = GetOpenFileName(&ofn))!=0 && filename)
		strcpy(filename, tempbuf);
	return result != -1;
}

//////////////////
// File Save As dialog.
// 
WPDlgFileSaveAs::WPDlgFileSaveAs(WPWin *pwin, char* fname, LPCSTR title)
	: WPDlgFileOpen(pwin, fname, title)
{
	ofn.Flags= OFN_SAVEDEFAULT;
}

/////////////////
// Create window: just call COMMDLG.
// 
BOOL WPDlgFileSaveAs::createWin()
{
	if ((result = GetSaveFileName(&ofn))!=0 && filename)
		strcpy(filename, tempbuf);
	return result != -1;
}

