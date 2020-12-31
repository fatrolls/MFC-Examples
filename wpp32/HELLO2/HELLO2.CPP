//////////////////////////////////////////////////////////
// WINDOWS++ CLASS LIBRARY.  Copyright 1992,1996 Paul DiLascia.
// FILE: HELLO2.CPP
//

#include "wpp.h"

#ifdef __ZTC__
#define CASTWNDPROC (void*)
#else
#define CASTWNDPROC
#endif

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);

//////////////////
// This class represents the main hello window.  
// Note that it's now derived from WPMainWin.
// 
class HelloWin : public WPMainWin {
public:
	HelloWin();		// constructor takes no args now
};

//////////////////
// Initialize an instance of HelloWin: 
// it's much smaller now: only need to init window proc!
// 
HelloWin::HelloWin()
{
	createArgs.wndcls.lpfnWndProc = WndProc;
	createWin("HELLO2--2nd C++ version");
}

//////////////////
// Program entry point, called from internal WinMain.
// 
void WPApp::main()
{
	mainWin = new HelloWin;			// create instance of HelloWin
	run();								// run message loop
	delete mainWin;					// delete window
}

////////////////
// Here's the window procedure.  The only difference from 
// HELLO1 is that we now call App.quit instead of PostQuitMessage.
// 
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
	PAINTSTRUCT ps;
	HDC hdc;
	RECT rect;

	switch(msg) {
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		GetClientRect(hwnd, &rect);
		DrawText(hdc, "Two down, two to go.", -1, &rect,
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
		App.quit(0);
		return 0;
	}
	return DefWindowProc(hwnd, msg, wp, lp);
}
