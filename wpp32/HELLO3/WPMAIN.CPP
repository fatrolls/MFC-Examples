//////////////////////////////////////////////////////////
// WINDOWS++ CLASS LIBRARY.  Copyright 1992,1996 Paul DiLascia.
// FILE: WPMAIN.CPP
//
// Implementation for WPMainWin.

#include "wpmain.h"
#include "wpapp.h"
#include "wpid.h"

//////////////////
// Init Main Window object: set up default createArgs.
// 
WPMainWin::WPMainWin() : WPWin("MAINWIN")
{
	createArgs.style = WS_OVERLAPPEDWINDOW;

	// Use "AppIcon" and "AppMenu" if any.
	createArgs.wndcls.lpszMenuName = "AppMenu";
	createArgs.wndcls.hIcon = App.loadIcon("AppIcon");
	if (createArgs.wndcls.hIcon==NULL)
		createArgs.wndcls.hIcon = App.loadIcon(IDI_APPLICATION);
}

////////////////
// Destructor: post quit message to Windows.
// This happens automatically when the main window is destroyed!
// 
WPMainWin::~WPMainWin()
{
	App.quit(0);
}

//////////////////
// Handle low-level commands for main app window, such as 
// Exit, About and so on.
// 
LONG WPMainWin::msgProc(WPEvent& event)
{
	switch (event.msg) {
	case WM_COMMAND:
		switch (event.cmd()) {
		case WPIDM_EXIT:
			close();
		}
		return 0;
	}
	return WPWin::msgProc(event);
}

