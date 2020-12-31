//////////////////////////////////////////////////////////
// WINDOWS++ CLASS LIBRARY.  Copyright 1992,1996 Paul DiLascia.
// FILE: WINMAIN.CPP
//
// WinMain fucntion fo Windows++ class library.

#include "wpapp.h"

WPApp App;		// THE application object

////////////////
// WINMAIN function.  This is linked as part of the 
// Windows++ library, so Windows++ programs should not
// supply WinMain.  Instead, they must supply WPApp::main.
// 
int PASCAL WinMain(HANDLE hinst, HANDLE pinst, LPSTR cmd, int show)
{
	App.init(hinst, pinst, cmd, show);	// init application object
	App.main();									// call user's entry-point
	return App.exitCode;						// (result from PostQuitMessage)
}
