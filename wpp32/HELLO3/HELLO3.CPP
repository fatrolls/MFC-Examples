//////////////////////////////////////////////////
// HELLO3--The third C++ version of HELLO.
// Copyright 1992,1996 Paul DiLascia.
// 

#include "wpp.h"

//////////////////
// Hello window class.  The only new thing is msgProc.
// 
class HelloWin : public WPMainWin {
public:
	HelloWin()		{ createWin("HELLO3--3rd C++ version"); }
	LONG msgProc(WPEvent &event);
};

//////////////////
// Main program entry point, called from internal WinMain
// 
void WPApp::main()
{
	mainWin = new HelloWin;		// notice we never delete it!
	run();
}

//////////////////
// This is the Windows++ virtual message procedure, called 
// from the internal window procedure, WPWndProc.
// 
LONG HelloWin::msgProc(WPEvent &event)
{
	switch(event.msg) {
	case WM_PAINT:
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(getHwnd(), &ps);
		RECT rect;
		GetClientRect(getHwnd(), &rect);
		DrawText(hdc, "Almost there.", -1, &rect,
			DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		EndPaint(getHwnd(), &ps);
		return 0;
	}
	return WPMainWin::msgProc(event);
}
