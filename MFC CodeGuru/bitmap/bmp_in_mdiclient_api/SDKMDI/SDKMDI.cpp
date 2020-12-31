#define STRICT
#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <tchar.h>

#include "resource.h"

LRESULT CALLBACK FrameWndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK SubClassProc(HWND hWnd, UINT nMsg, WPARAM wParam, LPARAM lParam);

WNDPROC		g_fnOldProc = NULL;
HINSTANCE	g_hInstance = NULL;
_TCHAR		szFrameClass[] = _T("VnMdiFrame");


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
				   PSTR szCommandList, int iCmdShow)
{
	HWND	hWndFrame;
	MSG		msg;

	WNDCLASSEX	wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	g_hInstance = hInstance;

	if (!hPrevInstance)
	{
		wc.cbSize	= sizeof(WNDCLASSEX);
		wc.style	= CS_HREDRAW | CS_VREDRAW;
		wc.lpfnWndProc = FrameWndProc;
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.hInstance = hInstance;
		wc.hIcon = NULL;
		wc.hCursor = NULL;
		wc.hbrBackground = (HBRUSH) (COLOR_APPWORKSPACE + 1);
		wc.lpszMenuName = NULL;
		wc.lpszClassName = szFrameClass;
		wc.hIconSm = NULL;

		RegisterClassEx(&wc);

		hWndFrame = CreateWindow(szFrameClass, _T("MDI Bitmap Background"),
			WS_VISIBLE | WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN,
			CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
			NULL, NULL, hInstance, NULL);

		UpdateWindow(hWndFrame);

		while(GetMessage(&msg, NULL, 0, 0))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		return msg.wParam;
	}

	return 0;
}


LRESULT CALLBACK FrameWndProc(HWND hWnd, UINT nMsg, WPARAM wParam, LPARAM lParam)
{
	static HWND hwndClient = NULL;

	CLIENTCREATESTRUCT ccs;

	switch(nMsg)
	{
	case WM_CREATE :
		ZeroMemory(&ccs, sizeof(CLIENTCREATESTRUCT));
		ccs.hWindowMenu = NULL;
		hwndClient = CreateWindow(_T("MDICLIENT"), NULL, WS_CHILD | WS_CLIPCHILDREN | WS_VISIBLE,
			0, 0, 0, 0, hWnd, (HMENU) NULL, g_hInstance, (LPSTR) &ccs);
		g_fnOldProc = (WNDPROC) SetWindowLong(hwndClient, GWL_WNDPROC, (LONG) SubClassProc);
		return 0;
		break;

	case WM_QUERYENDSESSION :
	case WM_CLOSE :
		if (NULL != GetWindow(hwndClient, GW_CHILD))
			return 0;
		break;

	case WM_DESTROY :
		PostQuitMessage(0);
		return 0;
		break;
	}

	return DefFrameProc(hWnd, hwndClient, nMsg, wParam, lParam);
}


LRESULT CALLBACK SubClassProc(HWND hWnd, UINT nMsg, WPARAM wParam, LPARAM lParam)
{
	static HBITMAP hBitmap = NULL;
	static BITMAP bm;

	switch (nMsg)
	{
	case WM_ERASEBKGND:
		if (!hBitmap)
		{
			hBitmap = LoadBitmap(g_hInstance, MAKEINTRESOURCE(IDB_MDIBKGND));
			ZeroMemory(&bm, sizeof(BITMAP));
			GetObject(hBitmap, sizeof(BITMAP), (LPVOID)&bm);
		}

		if (hBitmap != NULL)
		{
			HDC hDC = (HDC) wParam;

			RECT rect;
			GetClientRect(hWnd, &rect);

			HDC hMemDC = CreateCompatibleDC(NULL);
			HBITMAP hOldBitmap = NULL;

			UINT nWidth = rect.right - rect.left;
			UINT nHeight = rect.bottom - rect.top;

			hOldBitmap = (HBITMAP) SelectObject(hMemDC, hBitmap);

			UINT nX;
			UINT nY;

			for (nX = 0; nX < nWidth; nX += bm.bmWidth)
				for (nY = 0; nY < nHeight; nY += bm.bmHeight)
					BitBlt(hDC, nX, nY, bm.bmWidth, bm.bmHeight, hMemDC, 0, 0, SRCCOPY);

			SelectObject(hMemDC, hOldBitmap);

			return 1;
		}

		break;

	case WM_DESTROY:
		if (hBitmap)
		{
			DeleteObject(hBitmap);
			hBitmap = NULL;
			ZeroMemory(&bm, sizeof(BITMAP));
		}

		break;
	}

	return CallWindowProc(g_fnOldProc, hWnd, nMsg, wParam, lParam);
}
