//////////////////////////////////////////////////////////
// WINDOWS++ CLASS LIBRARY.  Copyright 1992,1996 Paul DiLascia.
// FILE: WPWIN.CPP
//
// Base WPWin class for all window objects--Version 3 for HELLO3.
// New since version 2:
// . mechanism to link window objects to their windows
//	  via the property list
// . a single central window procdure, WPWndProc
// . default msgProc calls old window procedure
//
// All windows are now formally subclassed by replacing their
// window procedures with our own.

#include "wpwin.h"
#include "wpapp.h"

#ifdef __ZTC__
#define CASTWNDPROC (void*)
#else
#define CASTWNDPROC
#endif

#define WP_WINPTR "w+"	// this property stores the window object pointer

WINCREATEARGS WPWin::createArgs;
WPWin *WPWin::NewWin = NULL;

////////////////////////////////////////////////////////////////
// This is THE Window Proc used for all Windows++ windows!
// The only message it actually handles is WM_DESTROY, to which it
// responds by destroying the linked Windows++ object.  Windows++
// programs should now NEVER DELETE WINDOWS OBJECTS, and window 
// object must always be create with "new", not on the stack.
// 
LRESULT CALLBACK WPWndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
	WPWin* win = WPWin::GetWin(hwnd);
	assert(win);

	if (msg==WM_DESTROY) {	// got WM_DESTROY:
		delete win;				// call virtual destructor
		return 0;
	}
	WPEvent event(msg, wp, lp);	// create an event object on the stack
	return win->msgProc(event);	// call virtual message proc
}

//////////////////
// Default WPWin message proc just calls Windows' default
//
LONG WPWin::msgProc(WPEvent &e)
{
	return CallWindowProc(oldProc, hwnd, e.msg, e.wp, e.lp); 
}

////////////////
// Overloaded new operator stores ptr in NewWin so 
// constructor can mark object as deletable.
// 
void* WPWin::operator new(size_t size)
{ 	
	return NewWin = (WPWin*)new char [size];
} 

void WPWin::operator delete(void* ptr)
{ 
	assert(((WPWin*)ptr)->deletable);	// safety
	delete ptr;
}

//////////////////
// Initialize WPWin instance.
// 
WPWin::WPWin(CSTR classnm)
{
	deletable = this==NewWin;
	NewWin=NULL;
	oldProc = NULL;
	hwnd = NULL;

	// set default registration args
	createArgs.wndcls.lpszClassName = (LPSTR)classnm;
	createArgs.wndcls.style = CS_HREDRAW | CS_VREDRAW;
	createArgs.wndcls.lpfnWndProc = CASTWNDPROC DefWindowProc;
	createArgs.wndcls.cbClsExtra = 0;
	createArgs.wndcls.cbWndExtra = 0;
	createArgs.wndcls.hInstance = App();
	createArgs.wndcls.hIcon = NULL;
	createArgs.wndcls.hCursor = LoadCursor(NULL, IDC_ARROW);
	createArgs.wndcls.hbrBackground = GetStockObject(WHITE_BRUSH);
	createArgs.wndcls.lpszMenuName = NULL;

	// set default creation args
	createArgs.title = NULL;
	createArgs.style = createArgs.exstyle = 0;
	createArgs.pos.origin(CW_USEDEFAULT, CW_USEDEFAULT);
	createArgs.pos.extent(CW_USEDEFAULT, CW_USEDEFAULT);
	createArgs.hmenu = NULL;
	createArgs.parent = NULL;
}

//////////////////
// Link object to a real (Windows) window.
// 
void WPWin::linkHwnd(HWND newhwnd)
{
	assert(hwnd==NULL);						// better not be already linked!
	assert(IsWindow(newhwnd));				// better have a real HWND!
	hwnd = newhwnd;							// store Window handle
	setProp(WP_WINPTR, (HANDLE)this);	// store ourself in window

	//////
	// Now "hook" the window's window proc--i.e., subclass it, saving
	// the original window procedure.
	// 
	oldProc = (FARPROC)GetWindowLong(hwnd, GWL_WNDPROC);
	SetWindowLong(hwnd, GWL_WNDPROC, (LONG)WPWndProc);
}

//////////////////
// Get window object from window handle (HWND)
// 
WPWin* WPWin::GetWin(HWND hwnd)
{ 
	if (hwnd==NULL)
		return NULL;
	assert(IsWindow(hwnd));
	return (WPWin*)GetProp(hwnd, WP_WINPTR);
}

////////////////
// Destroy window: unlink it.
// 
WPWin::~WPWin()
{
	unLinkHwnd();
}

//////////////////
// Unlink a window.
// 
void WPWin::unLinkHwnd()
{
	if (hwnd) {									 // if linked:
		if (oldProc) {
			// restore old window proc
			SetWindowLong(hwnd, GWL_WNDPROC, (LONG)oldProc);
			oldProc = NULL;					 // just to be safe!
		}
		assert(GetWin(hwnd)==this);	// double-check for safety
		removeProp(WP_WINPTR);			// free up window property
		hwnd = NULL;						// goodbye window handle!
	}
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
	linkHwnd(newhwnd);
	return hwnd!=NULL;
}
