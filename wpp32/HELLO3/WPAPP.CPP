//////////////////////////////////////////////////////////
// WINDOWS++ CLASS LIBRARY.  Copyright 1992,1996 Paul DiLascia.
// FILE: WPAPP.CPP
//
// Implementation for application object.

#include "wpmain.h"
#include "wpapp.h"
#include <stdarg.h>

//////////////////
// Get module's name.  Strip filename of path and extension.
// 
CSTR WPModule::getName()
{
	if (name[0] == 0 && hinst) {
		char buf[MAXFILENAMELEN];
		getFileName(buf, MAXFILENAMELEN);
		char *filename = NULL;
		for (char *next=strtok(buf,"\\"); next; next=strtok(NULL,"\\"))
			filename = next;
		strtok(filename,".");
		strcpy(name, filename);
	}
	return name;
}

//////////////////
// Initialize application object.  Called from WinMain.
// 
void WPApp::init(HANDLE h, HANDLE p, LPSTR cmd, int show)
{
	hinst = h;
	pinst = p;
	cmdLine=cmd;
	cmdShow=show;
	getName();
	loadAccel("AppAccel");		// default accelerator table
}

//////////////////
// Run the message loop.  Arg tells how to show main window.
// Returns value passed via App.quit();
// 
void WPApp::run()
{
	if (mainWin==NULL) {
		ErrBox("No application Window!");
		return;
	}
	mainWin->show(cmdShow);
	mainWin->update();
	
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {
		if (!(accel && TranslateAccelerator((*mainWin)(), accel, &msg))) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	exitCode = msg.wParam;
}

//////////////////
// This is a handy function for doing printf-style error boxes.
// 
int ErrBox(CSTR format, ...)
{
	char buf[128];

	va_list argptr;
	va_start(argptr, format);
	vsprintf(buf, format, argptr);
	va_end(argptr);
	return MessageBox(NULL, buf, NULL, MB_OK | MB_ICONEXCLAMATION);
}
