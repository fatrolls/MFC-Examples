//////////////////////////////////////////////////////////
// WINDOWS++ CLASS LIBRARY.  Copyright 1996 Paul DiLascia.
// FILE: WPAPP.H
//
// Definitions for WPApp.

#ifndef WPAPP_H
#define WPAPP_H

#include "wppdefs.h"

//////////////////
// Class used to represent a Windows module.  
// Essentially, it's just a module instance handle.
// 
class WPModule {
protected:
	char name[16];		// module name
	LPCSTR cmdLine;	// windows command line
	HANDLE hinst;		// module handle

public:
	WPModule(HANDLE h=NULL)	{ hinst = h; name[0]=0; }
	WPModule(CSTR nm)
		{ strcpy(name, nm); hinst = GetModuleHandle(name); }

	HANDLE operator()()				{ return hinst; }
	void getCmdLine(char *buf)		{ lstrcpy(buf, (LPSTR)cmdLine); }
	CSTR getName();
	int getFileName(char *buf, int buflen)
		{ return GetModuleFileName(hinst, (LPSTR)buf, buflen); }

	HANDLE loadIcon(LPCSTR name)		
		{ return LoadIcon(HIWORD(name) ? hinst : NULL, (LPSTR)name); }
	HANDLE loadIcon(int id)		
		{ return LoadIcon(hinst, MAKEINTRESOURCE(id)); }
};

//////////////////
// Application object. There is exactly one application for each
// Windows++ program.  It stores the module instance handle.
// Each app must provide a "main" function.
// 
class WPApp : public WPModule {
	friend int PASCAL WinMain(HANDLE, HANDLE, LPSTR, int);

	HANDLE pinst;					// previous instance handle
	int cmdShow;					// how to show window
	int exitCode;					// returned from WinMain
	WPMainWin *mainWin;			// main application window
	HANDLE accel;					// accelerator table, if any

	void init(HANDLE h, HANDLE p, LPSTR cmd, int show);
	void main();
	void run();

public:
	HANDLE getPrevInst()			{ return pinst; }
	BOOL first()					{ return pinst==NULL; }

	void quit(int ret=0)			{ PostQuitMessage(ret); }

	HANDLE loadAccel(CSTR acname)
		{ return accel = LoadAccelerators(hinst, (LPSTR)acname); }
};

extern WPApp App;		// THE application

#endif
