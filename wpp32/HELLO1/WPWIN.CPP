//////////////////////////////////////////////////////////
// WINDOWS++ CLASS LIBRARY.  Copyright 1992,1996 Paul DiLascia.
// FILE: WPWIN.CPP
//
// Base WPWin class for all window objects--Version 1 for HELLO1.

#include "wpwin.h"

WINCREATEARGS WPWin::createArgs;			 // instantiate createArgs

//////////////////
// Initialize WPWin instance.
// 
WPWin::WPWin(CSTR classnm)
{
	hwnd = NULL;

	// set default registration args
	createArgs.wndcls.lpszClassName = (LPSTR)classnm;
	createArgs.wndcls.style = CS_HREDRAW | CS_VREDRAW;
	createArgs.wndcls.lpfnWndProc = DefWindowProc;
	createArgs.wndcls.cbClsExtra = 0;
	createArgs.wndcls.cbWndExtra = 0;
	createArgs.wndcls.hInstance = NULL;
	createArgs.wndcls.hIcon = NULL;
	createArgs.wndcls.hCursor = LoadCursor(NULL, IDC_ARROW);
	createArgs.wndcls.hbrBackground = GetStockObject(WHITE_BRUSH);
	createArgs.wndcls.lpszMenuName = NULL;

	// set default creation args
	createArgs.title = NULL;
	createArgs.style = 0;
	createArgs.exstyle = 0;
	createArgs.pos.origin(CW_USEDEFAULT, CW_USEDEFAULT);
	createArgs.pos.extent(CW_USEDEFAULT, CW_USEDEFAULT);
	createArgs.hmenu = NULL;
	createArgs.parent = NULL;
}

//////////////////
// Create window using current values in createArgs.
//
BOOL WPWin::createWin()
{
	LPCSTR classnm = createArgs.wndcls.lpszClassName;
	assert(classnm);
	HANDLE hinst = createArgs.wndcls.hInstance;
	assert(hinst);
	WNDCLASS temp;

	// Register window class if it ain't already registered!
	if (!GetClassInfo(hinst, classnm, &temp) &&	// try module..
		!GetClassInfo(NULL, classnm, &temp)) {		// ..and built-in

		BOOL ret = RegisterClass(&createArgs.wndcls);
		assert(ret);
	}

	// Create window. 
	// Since we're in Windows 3.0 or better, use CreateWindowEx.
	HWND newhwnd = CreateWindowEx(createArgs.exstyle,
		classnm,
		(LPSTR)createArgs.title,
		createArgs.style, 
		createArgs.pos.left,
		createArgs.pos.top,
		createArgs.pos.width(),
		createArgs.pos.height(),
		WPWin::GetHwnd(createArgs.parent),
		createArgs.hmenu, 
		hinst,
		createArgs.lparam);

	assert(newhwnd);
	hwnd = newhwnd;
	return hwnd!=NULL;
}
