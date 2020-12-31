//////////////////////////////////////////////////////////
// WINDOWS++ CLASS LIBRARY.  Copyright 1992,1996 Paul DiLascia.
// FILE: HELLO.C
//
/******************************************************/
/* This is the basic C version of the hello program.  */
/******************************************************/

#include <windows.h>

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);

int PASCAL WinMain(HINSTANCE hinst, HINSTANCE pinst, LPSTR cmdline, int show)
{
	HWND hwnd;
	MSG msg;

	if (pinst==NULL) {
		WNDCLASS wndcls;

		wndcls.style = CS_HREDRAW | CS_VREDRAW;
		wndcls.lpfnWndProc = WndProc;
		wndcls.cbClsExtra = 0;
		wndcls.cbWndExtra = 0;
		wndcls.hInstance = hinst;
		wndcls.hIcon = LoadIcon(hinst, "HELLOICON");
		wndcls.hCursor = LoadCursor(NULL, IDC_ARROW);
		wndcls.hbrBackground = GetStockObject(WHITE_BRUSH);
		wndcls.lpszMenuName = "HELLOMENU";
		wndcls.lpszClassName = "HELLOWIN";

		RegisterClass(&wndcls);
	}

	hwnd = CreateWindow("HELLOWIN",		 /* class name */
		"HELLO--The C version",				 /* title */
		WS_OVERLAPPEDWINDOW,					 /* window style */
		CW_USEDEFAULT,							 /* x position */
		CW_USEDEFAULT,							 /* y position */
		CW_USEDEFAULT,							 /* width */
		CW_USEDEFAULT,							 /* height */
		NULL,										 /* parent */
		NULL,										 /* menu */
		hinst,									 /* module instance */
		NULL);									 /* create param */

	ShowWindow(hwnd, show);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
	PAINTSTRUCT ps;
	HDC hdc;
	RECT rect;

	switch(msg) {
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		GetClientRect(hwnd, &rect);
		DrawText(hdc, "Hello, world.", -1, &rect,
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
