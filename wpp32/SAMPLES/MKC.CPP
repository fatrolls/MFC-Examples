//////////////////////////////////////////////////////////
// WINDOWS++ CLASS LIBRARY.  Copyright 1992 Paul DiLascia.
// FILE: MKC.CPP
//
// Sample program to demonstrate use of keyboard, mouse and cursor.
// Shows status of [NUM CAP SCROLL] LOCK, mouse buttons and cursor pos.
// Also moves the cursor using arrow keys.

#include "prefix.h"

MyApp myApp; // instantiate one and only app

int TABS[] = { 12, 25 };			// tab-stops (in text coords)
const int NTABS = sizeof(TABS)/sizeof(TABS[0]);
const VK_SCROLLLOCK = 0x91;		// code for scroll lock

class MKCWin : public WPMainWin {
	TEXTMETRIC tm;				// text metrics
	int button[3];				// button states
	int repeat;					// keyboard repeat count
public:
	MKCWin();
	void paint(WPPaintDC &pdc);
	BOOL kbd(WPEvent& event);
	BOOL mouse(int msg, WPPoint p, WORD flags);
	BOOL activated(WORD state, BOOL minimized);
};

void MyApp::main()
{
	mainWin = new MKCWin;
	run();
}

//////////////////
// Create main window.  Use cursor from resource file.
// 
MKCWin::MKCWin()
{
	createArgs.wndcls.hCursor = theApp->loadCursor("XCURSOR");
	createArgs.pos.extent(200, 200);
	createWin("Mouse, Keyboard, Cursor");

	// Convert tab stops from text to pixel coordinates
	WPWinDC dc = this;
	dc.textMetrics(tm);
	TABS[0] *= tm.tmAveCharWidth;
	TABS[1] *= tm.tmAveCharWidth;
}

//////////////////
// Paint status of CAPSLOCK, etc. Uses Windows 3.0 tabbed text.
// 
void MKCWin::paint(WPPaintDC &dc)
{
	dc.setTabs(TABS, NTABS);

	WPPoint pt(tm.tmAveCharWidth, tm.tmHeight);

	dc.printF(pt, "MOUSE:\t%sPRESENT\t", 
		Mouse.present() ? (LPCSTR)"" : (LPCSTR)"NOT ");
	pt.y += tm.tmHeight;

	char LMR[4]="LMR";
	for (int i=0; i<3; i++) {
		dc.printF(pt, "%cBUTTON:\t%s\t", LMR[i], button[i] ? 
			(LPCSTR)"DOWN" : (LPCSTR)"UP");
		pt.y += tm.tmHeight;
	}

	dc.printF(pt,"NUMLOCK:\t%s\t", Keyboard.state(VK_NUMLOCK) ? 
		(LPCSTR)"ON" : (LPCSTR)"OFF");
	pt.y += tm.tmHeight;

	dc.printF(pt,"CAPLOCK:\t%s\t", Keyboard.state(VK_CAPITAL) ?
		(LPCSTR)"ON" : (LPCSTR)"OFF");
	pt.y += tm.tmHeight;

	dc.printF(pt,"SCROLL:\t%s\t", Keyboard.state(VK_SCROLLLOCK) ?
		(LPCSTR)"ON" : (LPCSTR)"OFF");
	pt.y += tm.tmHeight;

	WPPoint crs= Cursor();
	screenToClient(&crs);
	dc.printF(pt, "CURSOR:\t(%d,%d)\t", crs.x, crs.y);
}

//////////////////
// Handle mouse message.  
// Record button state and always invalidate the client area.
// 
BOOL MKCWin::mouse(int msg, WPPoint p, WORD flags)
{
	switch(msg) {
	case WM_LBUTTONDOWN:
	case WM_LBUTTONUP:
		button[0] = (msg==WM_LBUTTONDOWN);
		break;
	case WM_MBUTTONDOWN:
	case WM_MBUTTONUP:
		button[1] = (msg==WM_MBUTTONDOWN);
		break;
	case WM_RBUTTONDOWN:
	case WM_RBUTTONUP:
		button[2] = (msg==WM_RBUTTONDOWN);
	}
	invalidate();
	return TRUE;
}

BOOL MKCWin::activated(WORD state, BOOL minimized)
{
	if (!Mouse.present() && !minimized)
		Cursor.show(state);
	setFocus();
	return TRUE;
}

/////////////////
// Handle keyboard message
// 
BOOL MKCWin::kbd(WPEvent& event)
{
	int key = event.wp;
	switch (key) {
	case VK_NUMLOCK:							 // for any of these...
	case VK_CAPITAL:
	case VK_SCROLLLOCK:
		invalidate();							 // repaint window
		return TRUE;
	}

	switch (event.msg) {
	case WM_KEYDOWN:
		if (Keyboard.isArrowKey(key)) {
			// Got arrow key: move cursor
			WPPoint pt = Cursor();
			screenToClient(&pt);
			repeat += LOWORD(event.lp); // repeat

			switch (key) {
			case VK_LEFT:	pt.x -= repeat;	break;
			case VK_RIGHT:	pt.x += repeat;	break;
			case VK_UP:		pt.y -= repeat;	break;
			case VK_DOWN:	pt.y += repeat;	break;
			}

			// Don't move outside our window's client area
			WPRect rect = this;
			rect.capture(pt);
			clientToScreen(&pt);
			Cursor = pt;
			return TRUE;
		}
		break;

	case WM_KEYUP:
		repeat = 1;								 // Clear repeat count
		return TRUE;
	}
	return WPMainWin::kbd(event);
}
