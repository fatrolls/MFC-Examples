//////////////////////////////////////////////////////////
// WINDOWS++ CLASS LIBRARY.  Copyright 1992,1996 Paul DiLascia.
// FILE: WPWIN.H
//
// Definitions for WPWin class.

#ifndef WPWIN_H
#define WPWIN_H

#include "wprect.h"

//////////////////
// Event object, used to pass msg, wParam, and lParam
// 
struct WPEvent {
	UINT   msg;	// the message
	WPARAM wp;		// word parameter
	LPARAM lp;		// long parameter
	friend class WPUserWin;

	WPEvent(UINT m, WPARAM w=0, LPARAM l=0) { msg=m; wp=w; lp=l; }
	~WPEvent() { }

	WORD cmd()			{ return LOWORD(wp); }
	HMENU menu()		{ return (HMENU)wp; }
	int childHwnd()	{ return LOWORD(lp); }
	int childMsg()		{ return HIWORD(wp); }
	int x()				{ return LOWORD(lp); }
	int y()				{ return HIWORD(lp); }
	int width()			{ return LOWORD(lp); }
	int height()		{ return HIWORD(lp); }
	LPSTR text()		{ return (LPSTR)lp; }
	WPPoint point()	{ return *((WPPoint *)&lp); }
	HWND focusHwnd()	{ return (HWND)wp; }

	int key()			{ return wp; }
	int keyRepeat()	{ return LOWORD(lp); }
	int keyScan()		{ return LOBYTE(HIWORD(lp)); }
	int keyFlags()		{ return HIBYTE(HIWORD(lp)); }

	WPPoint screenPos()	{ return (WPPoint)GetMessagePos(); }
	DWORD time()			{ return GetMessageTime(); }
};

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
	static WPWin* NewWin;	// window being created
	FARPROC oldProc;			// original window proc
	HWND hwnd;					// handle to window
	BOOL deletable;			// FALSE if stack object

	void linkHwnd(HWND newhwnd);
	void unLinkHwnd();

	friend LRESULT CALLBACK WPWndProc(HWND, UINT, WPARAM, LPARAM);

protected:
	virtual LONG msgProc(WPEvent &e);

public:
	WPWin(CSTR classnm);					// constructor
	virtual ~WPWin();

	static WINCREATEARGS createArgs;	// creation/regsitration args

	void *operator new(size_t size);
	void operator delete(void *ptr);

	HWND getHwnd()							{ return hwnd; }
	HWND operator()()						{ return hwnd; }
	static HWND GetHwnd(WPWin* win)	{ return win ? win->hwnd : NULL; }
	static WPWin* GetWin(HWND hwnd);

	void update()							{ UpdateWindow(hwnd); }
	BOOL show(int how=SW_SHOW)			{ return ShowWindow(hwnd, how); }
	BOOL createWin();
	BOOL createWin(CSTR title)
		{ createArgs.title=title; return createWin(); }

	// properties
	HANDLE getProp(CSTR kwd)				{ return GetProp(hwnd, (LPSTR)kwd); }
	void setProp(CSTR kwd, HANDLE val)	{ SetProp(hwnd, (LPSTR)kwd, val); }
	void removeProp(CSTR kwd)				{ RemoveProp(hwnd, (LPSTR)kwd); }

	void close() { SendMessage(hwnd, WM_CLOSE, 0, 0); }
};

#endif
