/*****************************************************************************************
模 块 名：Ripper
说    明：水波特效的主程序
创 建 人：魔佳
版    本：V1.0.0
*****************************************************************************************/

#include <tchar.h>
#include "wave.h"
#include "resource.h"

HINSTANCE hInstExe = NULL;
HWND hWnd = NULL;
WAVEOBJECT stWaveObj;

TCHAR szClass[] = TEXT ("Ripper");
TCHAR szTitle[] = TEXT ("水波特效");
//TCHAR szTip[] = TEXT ("水波特效演示by罗云彬\n使用Win32汇编语言编写，源代码可见http://asm.yeah.net\n\n鼠标左键：在点击处激发水波\n鼠标右键：循环切换（下雨、快艇、波浪等）");
//TCHAR szError[] = TEXT ("初始化水波对象错误");

void Quit (void)
{
	WaveFree (&stWaveObj);
	DestroyWindow (hWnd);
	PostQuitMessage (0);
}

LRESULT CALLBACK WndProc (HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT stPs;
	HDC hDc;
	HBITMAP hBmp;
	UINT cx, cy;
	int count = 0;

	switch (message) {
	case WM_CREATE:
		hBmp = LoadBitmap (hInstExe, MAKEINTRESOURCE (IDB_BITMAP1));
		WaveInit (&stWaveObj, hWnd, hBmp, 30, 0);
		SetWindowPos (hWnd, HWND_TOPMOST, 0, 0, stWaveObj.dwBmpWidth+5, stWaveObj.dwBmpHeight+25, SWP_NOMOVE);
		WaveEffect (&stWaveObj, 1, 3, 5, 120);
		return 0;
	case WM_CLOSE:
		Quit ();
		return 0;
	case WM_PAINT:
		hDc  = BeginPaint (hWnd, &stPs);
		WaveUpdateFrame (&stWaveObj, hDc, TRUE);
		EndPaint (hWnd, &stPs);
		return 0;
	case WM_MOUSEMOVE:
		cx = LOWORD (lParam);
		cy = HIWORD (lParam);
		//WaveDropStone (&stWaveObj, cx, cy, 2, 256);
		return 0;
	case WM_LBUTTONDOWN:
		cx = LOWORD (lParam);
		cy = HIWORD (lParam);
		WaveDropStone (&stWaveObj, cx, cy, 2, 5000);
		return 0;
	case WM_RBUTTONDOWN:
		switch (stWaveObj.dwEffectType) {
		case 0:
			WaveEffect (&stWaveObj, 1, 5, 4, 250);
			break;
		case 1:
			WaveEffect (&stWaveObj, 3, 200, 2, 8);
			break;
		case 3:
			WaveEffect (&stWaveObj, 2, 4, 2, 180);
			break;
		default:
			WaveEffect (&stWaveObj, 0, 0, 0, 0);
		}
		return 0;
	case WM_KEYDOWN:
		switch (wParam) {
		case 0x46:
			WaveDropStone (&stWaveObj, stWaveObj.dwBmpWidth*7/16, stWaveObj.dwBmpHeight/2, 2, 5000);
			WaveDropStone (&stWaveObj, stWaveObj.dwBmpWidth*9/16, stWaveObj.dwBmpHeight/2, 2, 5000);
			WaveDropStone (&stWaveObj, stWaveObj.dwBmpWidth/2, stWaveObj.dwBmpHeight/4, 2, 5000);
			WaveDropStone (&stWaveObj, stWaveObj.dwBmpWidth/2, stWaveObj.dwBmpHeight*3/4, 2, 5000);
			WaveDropStone (&stWaveObj, stWaveObj.dwBmpWidth*5/16, stWaveObj.dwBmpHeight/2, 2, 5000);
			WaveDropStone (&stWaveObj, stWaveObj.dwBmpWidth*3/16, stWaveObj.dwBmpHeight/2, 2, 5000);
			WaveDropStone (&stWaveObj, stWaveObj.dwBmpWidth*11/16, stWaveObj.dwBmpHeight/2, 2, 5000);
			WaveDropStone (&stWaveObj, stWaveObj.dwBmpWidth*13/16, stWaveObj.dwBmpHeight/2, 2, 5000);
			break;
		}
		return 0;
	}

	return DefWindowProc (hWnd, message, wParam, lParam);
}

int APIENTRY _tWinMain (HINSTANCE hInstance, HINSTANCE, LPTSTR pszCmdLine, int nCmdShow)
{	
	MSG msg;

	//注册窗口类
	hInstExe = hInstance;
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof (WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = (WNDPROC) WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstExe;
	wcex.hIcon = LoadIcon (NULL, IDI_APPLICATION);
	wcex.hCursor = LoadCursor (NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH) GetStockObject (WHITE_BRUSH);	//(HBRUSH) (COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = szClass;
	wcex.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
	RegisterClassEx (&wcex);

	//创建窗口并显示
	hWnd = CreateWindowEx (NULL, szClass, szTitle, WS_OVERLAPPED | WS_SYSMENU, 
		300, 200, 800, 500, NULL, NULL, hInstExe, NULL);

	ShowWindow (hWnd, nCmdShow);
	UpdateWindow (hWnd);

	//窗口消息循环
	while (GetMessage (&msg, NULL, 0, 0)) {
		TranslateMessage (&msg);
		DispatchMessage (&msg);
	}

	return 0;
}