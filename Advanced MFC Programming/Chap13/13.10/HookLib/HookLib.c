#include "HookLib.h"
#include <stdio.h>

#pragma data_seg("SHARDATA")
static HWND g_hWnd=NULL;
static HHOOK g_hHookKeyboard=NULL;
#pragma data_seg()

BOOL CALLBACK LibMain(HANDLE hModule, DWORD dwReason, LPVOID lpReserved)
{
	return TRUE;
}

int CALLBACK WEP (int bSystemExit)
{
    return TRUE;
}

STDENTRY_(BOOL) SetKeyboardHook(HWND hWnd, HINSTANCE hInstance)
{
	g_hHookKeyboard=SetWindowsHookEx
	(
		WH_KEYBOARD,
		KeyboardProc,
		hInstance,
		0
	);
	if(g_hHookKeyboard == FALSE)
	{
		return FALSE;
	}
	g_hWnd=hWnd;

	return TRUE;
}

BOOL UnsetKeyboardHook()
{
	return UnhookWindowsHookEx(g_hHookKeyboard); 
}

LRESULT CALLBACK KeyboardProc(int code, WPARAM wParam, LPARAM lParam)
{
	if(code < 0 || code != HC_ACTION)
	{
		return CallNextHookEx(g_hHookKeyboard, code, wParam, lParam);
	}
	if(code == HC_ACTION)
	{
		int nKeyState;

		nKeyState=GetKeyState(VK_CONTROL);
		if(lParam & 0x80000000 || lParam & 0x40000000)
		{
			return CallNextHookEx(g_hHookKeyboard, code, wParam, lParam);
		}
		switch(wParam)
		{
			case VK_F3:
			{
				if(IsWindow(g_hWnd) && HIBYTE(nKeyState))
				{
					if(IsWindowVisible(g_hWnd) == FALSE)
					{
						ShowWindow(g_hWnd, SW_SHOW);
						UnsetKeyboardHook();
					}
				}
				break;
			}
		}
	}

	return CallNextHookEx(g_hHookKeyboard, code, wParam, lParam);
}