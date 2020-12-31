//////////////////////////////////////////////////////////
// WINDOWS++ CLASS LIBRARY.  Copyright 1992,1996 Paul DiLascia.
// FILE: WPMAIN.CPP
//
// Implementation for WPMainWin.

#include "wpmain.h"
#include "wpapp.h"

//////////////////
// Init Main Window object: set up default createArgs.
// 
WPMainWin::WPMainWin(CSTR classnm) : WPWin(classnm)
{
	createArgs.style = WS_OVERLAPPEDWINDOW;

	// Use "AppIcon" and "AppMenu" if any.
	createArgs.wndcls.lpszMenuName = "AppMenu";
	createArgs.wndcls.hIcon = App.loadIcon("AppIcon");
	if (createArgs.wndcls.hIcon==NULL)
		createArgs.wndcls.hIcon = App.loadIcon(IDI_APPLICATION);
}
