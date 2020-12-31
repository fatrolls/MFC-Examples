//////////////////////////////////////////////////////////
// WINDOWS++ CLASS LIBRARY.  Copyright 1992,1996 Paul DiLascia.
// FILE: WPWIN.H
//
// Definitions for WPWin class.

#ifndef WPWIN_H
#define WPWIN_H

#include "wprect.h"

//////////////////
// This structure is used to specify the Windows registration
// and creation arguments before creating an actual window.
// 
struct WINCREATEARGS {
	WNDCLASS wndcls;		// Windows registration structure
	CSTR title;				// window's title
	DWORD style;			// style (WS_OVERLAPPED, etc.)
	DWORD exstyle;			// extended style (Windows 3.0)
	WPRect pos;				// window position (x,y,w,h)
	WPWin* parent;			// parent window
	HMENU hmenu;			// menu handle
	LPSTR lparam;			// create parm
};

//////////////////
// This is THE base window class, from which all window classes
// are derived.  It provided methods corresponding to most Windows
// functions that take a window handle (HWND).
// 
class WPWin {
private:
	HWND hwnd;								// window handle
public:
	WPWin(CSTR classnm);					// constructor

	static WINCREATEARGS createArgs;	// creation/regsitration args

	HWND getHwnd()							{ return hwnd; }
	HWND operator()()						{ return hwnd; }
	static HWND GetHwnd(WPWin* win)	{ return win ? win->hwnd : NULL; }

	void update()							{ UpdateWindow(hwnd); }
	BOOL show(int how=SW_SHOW)			{ return ShowWindow(hwnd, how); }
	BOOL createWin();
	BOOL createWin(CSTR title)
		{ createArgs.title=title; return createWin(); }
};

#endif
