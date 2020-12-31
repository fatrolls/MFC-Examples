//////////////////////////////////////////////////////////
// WINDOWS++ CLASS LIBRARY.  Copyright 1992 Paul DiLascia.
// FILE: WINMAIN.CPP
//
// WinMain function for Windows++ class library. Also contains other
// "global" stuff like the main window and dialog procs, global objects, 
// new, delete, etc.

#include "wpp.h"

//////////////////
// Below are all the global objects.
// 
WPMouse			Mouse;
WPKeyboard		Keyboard;
WPCursor			Cursor;
WPWinIni			WinIni;
WPCaret			Caret;
WPClipboard		Clipboard;

////////////////
// WINMAIN function.  This is linked as part of the 
// Windows++ library, so Windows++ programs should not
// supply WinMain.  Instead, they must supply WPApp::main.
// 
int PASCAL WinMain(HINSTANCE hinst, HINSTANCE pinst, LPSTR cmd, int show)
{
	if (theApp==NULL) {
		// If you get here, you forgot to instantiate a WPApp object in your app
		MsgBox("No application object!","WinMain",MB_OK|MB_ICONEXCLAMATION);
	}
	theApp->init(hinst, pinst, cmd, show);		// init application object
	theApp->main();									// call user's entry-point
	return theApp->exitCode;						// (result from PostQuitMessage)
}

