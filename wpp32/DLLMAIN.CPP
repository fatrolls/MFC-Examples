//////////////////////////////////////////////////////////
// WINDOWS++ CLASS LIBRARY.  Copyright 1992 Paul DiLascia.
// FILE: LIBMAIN.CPP
//
// Entry point for Windows++ DLL.
// Also contains "global" stuff that's in WINMAIN.CPP, such as
// new and delete, global objects and so on (but not WPWndProc and 
// WPDlgProc, which are duplicated in each app in order to use smart
// callbacks instead of MakeProcInstance).

#include "wpp.h"

WPMouse			Mouse;			// instantiate global objects
WPKeyboard		Keyboard;
WPCursor			Cursor;
WPWinIni			WinIni;
WPCaret			Caret;
WPClipboard		Clipboard;

//////////////////
// In Win32, DllMain replaces LibMain/WEP
//
extern "C"
BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID /*lpReserved*/)
{
	if (dwReason == DLL_PROCESS_ATTACH) {

	} else if (dwReason == DLL_PROCESS_DETACH) {

	}
	return TRUE;
}
