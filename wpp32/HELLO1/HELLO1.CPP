//////////////////////////////////////////////////////////
// WINDOWS++ CLASS LIBRARY.  Copyright 1992,1996 Paul DiLascia.
// FILE: HELLO1.CPP
//

#include "wpp.h"

#ifdef __ZTC__
#define CASTWNDPROC (void*)
#else
#define CASTWNDPROC
#endif

LRESULT FAR PASCAL WndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);

//////////////////
// This class represents the main hello window.  
// It's derived from the base window class, WPWin.
// 
class HelloWin : public WPWin {
public:
	HelloWin(HANDLE hinst);		// constructor takes module handle
};

//////////////////
// Initialize an instance of HelloWin: 
// initialize createArgs, then create the window.
// 
HelloWin::HelloWin(HANDLE hinst) : WPWin("HELLOWIN")
{
	createArgs.wndcls.lpfnWndProc = WndProc;
	createArgs.wndcls.hInstance = hinst;
	createArgs.wndcls.lpszMenuName = "HelloMenu";
	createArgs.wndcls.hIcon = LoadIcon(hinst, "HelloIcon");
	createArgs.style = WS_OVERLAPPEDWINDOW;
	createWin("HELLO1--1st C++ version");
}

/////////////////
// Program entry point
// 
int PASCAL WinMain(HANDLE hinst, HANDLE pinst, LPSTR cmdline, int show)
{
	HelloWin *win = new HelloWin(hinst); // create a HelloWin object instance

	win->show(show);	// show it (=ShowWindow)
	win->update();		// update it (=UpdateWindow)

	// This a normal Windows message loop
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	delete win;			// destroy the window object
	return msg.wParam;
}

////////////////
// Here's the window procedure.  It's unchanged from HELLO.C.
// 
LRESULT FAR PASCAL WndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
	PAINTSTRUCT ps;
	HDC hdc;
	RECT rect;

	switch(msg) {
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		GetClientRect(hwnd, &rect);
		DrawText(hdc, "Goodbye, C.  Hello C++.", -1, &rect,
			DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		EndPaint(hwnd, &ps);
		return 0;
		
	case WM_COMMAND:
		switch (wp) {
		case IDCANCEL:
			SendMessage(hwnd, WM_CLOSE, 0, 0);
			break;
		}
		return 0;
		
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, msg, wp, lp);
}

