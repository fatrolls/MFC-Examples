//
//	Simple Win32 sample of the Cool Scrollbar Library
//	Written by J Brown.
//	Freeware
//
#include <windows.h>
#include <commctrl.h>
#include <shlobj.h>
#include "..\coolsb\coolscroll.h"

#include "resource.h"

char szAppName[]    = "CoolScroll Demo";
char szChildClass[] = "TestCustCtrl";

HINSTANCE hInstance;
HWND hwndMain;
HWND hwndCtrl;

LRESULT CommandHandler(HWND hwnd, WPARAM wParam, LPARAM lParam);
void	InitTest(void);
LRESULT HandleCustomDraw(UINT, NMCSBCUSTOMDRAW *);

int nVScrollMax, nVScrollPos, nVScrollPage;
int nHScrollMax, nHScrollPos, nHScrollPage;

int nVMaxLines = 20;
int nHMaxLines = 80;

int xChar = 10;
int yChar = 10;

void SetupScrollbars(HWND hwnd)
{
	SCROLLINFO si;
	RECT rect;

	GetClientRect(hwnd, &rect);

	// VERT
	nVScrollPage = min(nVMaxLines + 1, (rect.bottom - rect.top) / yChar);
	nVScrollMax  = max(0, nVMaxLines);
    nVScrollPos  = min(nVScrollPos, nVScrollMax - nVScrollPage + 1);
	
	si.cbSize	= sizeof(si);
	si.fMask	= SIF_PAGE | SIF_POS | SIF_RANGE | SIF_DISABLENOSCROLL;
	si.nMin		= 0;
	si.nMax		= nVScrollMax;
	si.nPos		= nVScrollPos;
	si.nPage	= min(nVScrollPage, nVScrollMax + 1);
	
	CoolSB_SetScrollInfo (hwnd, SB_VERT, &si, TRUE);

	// HORZ
	nHScrollPage = min(nHMaxLines + 1, (rect.right - rect.left) / xChar);
	nHScrollMax  = max(0, nHMaxLines);
    nHScrollPos  = min(nHScrollPos, nHScrollMax - nHScrollPage + 1);
	
	si.cbSize	= sizeof(si);
	si.fMask	= SIF_PAGE | SIF_POS | SIF_RANGE | SIF_DISABLENOSCROLL;
	si.nMin		= 0;
	si.nMax		= nHScrollMax;
	si.nPos		= nHScrollPos;
	si.nPage	= min(nHScrollPage, nHScrollMax + 1);
	
	CoolSB_SetScrollInfo (hwnd, SB_HORZ, &si, TRUE);
}

//
//	Child window procedure
//
LRESULT CALLBACK ChildWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static int count;
	char ach[80];

	switch(msg)
	{
	case WM_VSCROLL:

		switch(LOWORD(wParam))
		{
		case SB_LINEUP:		nVScrollPos --;					break;
		case SB_LINEDOWN:	nVScrollPos ++;					break;
		case SB_PAGEUP:		nVScrollPos -= nVScrollPage;	break;
		case SB_PAGEDOWN:	nVScrollPos += nVScrollPage;	break;
		case SB_TOP:		nVScrollPos = 0;				break;
		case SB_BOTTOM:		nVScrollPos = nVScrollMax -1;	break;
		case SB_THUMBTRACK: nVScrollPos = HIWORD(wParam);	break;
		}

		wsprintf(ach, "WM_VSCROLL %d\n", count++);
		OutputDebugString(ach);

		if(nVScrollPos < 0) 
			nVScrollPos = 0;

		if(nVScrollPos > nVScrollMax - nVScrollPage + 1) 
			nVScrollPos = nVScrollMax - nVScrollPage + 1;

		CoolSB_SetScrollPos(hwnd, SB_VERT, nVScrollPos, TRUE);

		return 0;

	case WM_HSCROLL:

		wsprintf(ach, "WM_HSCROLL %d\n", count++);
		OutputDebugString(ach);

		switch(LOWORD(wParam))
		{
		case SB_LINEUP:		nHScrollPos --;					break;
		case SB_LINEDOWN:	nHScrollPos ++;					break;
		case SB_PAGEUP:		nHScrollPos -= nHScrollPage;	break;
		case SB_PAGEDOWN:	nHScrollPos += nHScrollPage;	break;
		case SB_TOP:		nHScrollPos = 0;				break;
		case SB_BOTTOM:		nHScrollPos = nHScrollMax -1;	break;
		case SB_THUMBTRACK: nHScrollPos = HIWORD(wParam);	break;
		}

		if(nHScrollPos < 0) 
			nHScrollPos = 0;

		if(nHScrollPos > nHScrollMax - nHScrollPage + 1) 
			nHScrollPos = nHScrollMax - nHScrollPage + 1;

		CoolSB_SetScrollPos(hwnd, SB_HORZ, nHScrollPos, TRUE);

		return 0;

	case WM_SIZE:
		SetupScrollbars(hwnd);
		return 0;
	}

	return DefWindowProc(hwnd, msg, wParam, lParam);
}

//
//	Main window procedure
//
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	int width, height;
	NMHDR *hdr = (NMHDR *)lParam;
	SCROLLINFO si;

	switch(msg)
	{
	case WM_CREATE:

		hwndCtrl   = CreateWindowEx(WS_EX_CLIENTEDGE,
			szChildClass, "Test", 
			WS_VISIBLE | WS_CHILD | WS_VSCROLL | WS_HSCROLL,
			0,0,0,0, hwnd, 0, GetModuleHandle(0), 0);

		InitializeCoolSB(hwndCtrl);
		CoolSB_SetStyle(hwndCtrl, SB_BOTH, CSBS_NORMAL);

		si.cbSize = sizeof(si);
		si.fMask  = SIF_ALL;
		si.nMin   = 0;
		si.nMax   = 100;
		si.nPos   = 0;
		si.nPage  = 10;

		SetScrollInfo(hwndCtrl, SB_VERT, &si, TRUE);

		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	case WM_CLOSE:
		DestroyWindow(hwnd);
		return 0;

	case WM_SIZE:
		width  = (short)LOWORD(lParam);
		height = (short)HIWORD(lParam);

		MoveWindow(hwndCtrl, 0, 0, width, height, TRUE);
		return 0;

	case WM_COMMAND:
		return CommandHandler(hwnd, wParam, lParam);

	case WM_NOTIFY:
		if(hdr->code == NM_COOLSB_CUSTOMDRAW)
		{
			return HandleCustomDraw(wParam, (NMCSBCUSTOMDRAW *)lParam);
		}
		break;

	}
	return DefWindowProc(hwnd, msg, wParam, lParam);
}


int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrev, LPSTR lpCmdLine, int iShowCmd)
{
	HWND		hwnd;
	MSG			msg;
	WNDCLASSEX	wndclass;

	hInstance = hInst;

	InitTest();

	//Window class for the main application parent window
	wndclass.cbSize			= sizeof(wndclass);
	wndclass.style			= 0;
	wndclass.lpfnWndProc	= WndProc;
	wndclass.cbClsExtra		= 0;
	wndclass.cbWndExtra		= 0;
	wndclass.hInstance		= hInstance;
	wndclass.hIcon			= LoadIcon(0, MAKEINTRESOURCE(IDI_APPLICATION));
	wndclass.hCursor		= LoadCursor (NULL, IDC_ARROW);
	wndclass.hbrBackground	= (HBRUSH)0;
	wndclass.lpszMenuName	= MAKEINTRESOURCE(IDR_MENU1);
	wndclass.lpszClassName	= szAppName;
	wndclass.hIconSm		= LoadIcon (NULL, IDI_APPLICATION);

	RegisterClassEx(&wndclass);

	//Window class for the child window 
	wndclass.cbSize			= sizeof(wndclass);
	wndclass.style			= 0;
	wndclass.lpfnWndProc	= ChildWndProc;
	wndclass.cbClsExtra		= 0;
	wndclass.cbWndExtra		= 0;
	wndclass.hInstance		= hInst;
	wndclass.hIcon			= 0;
	wndclass.hCursor		= LoadCursor (NULL, IDC_ARROW);
	wndclass.hbrBackground	= (HBRUSH)(COLOR_WINDOW + 1);
	wndclass.lpszMenuName	= 0;
	wndclass.lpszClassName	= szChildClass;
	wndclass.hIconSm		= 0;

	RegisterClassEx(&wndclass);

	hwnd = CreateWindowEx(0,
				szAppName,				// window class name
				szAppName,				// window caption
				WS_OVERLAPPEDWINDOW|WS_CLIPCHILDREN,
				CW_USEDEFAULT,			// initial x position
				CW_USEDEFAULT,			// initial y position
				350,					// initial x size
				200,					// initial y size
				NULL,					// parent window handle
				NULL,					// use window class menu
				hInstance,				// program instance handle
				NULL);					// creation parameters

	hwndMain = hwnd;

	ShowWindow(hwnd, iShowCmd);

	while(GetMessage(&msg, NULL,0,0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}