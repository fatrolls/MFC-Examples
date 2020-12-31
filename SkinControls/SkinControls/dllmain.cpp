// dllmain.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include <afxwin.h>
#include <afxdllx.h>
#include "Detours.h"
#include "SkinControls.h"
#include "SkinSB.h"

static AFX_EXTENSION_MODULE SkinControlsDLL = { NULL, NULL };

// 声明钩子
DETOUR_TRAMPOLINE(int   WINAPI GetScrollPosT(HWND, int), GetScrollPos)
DETOUR_TRAMPOLINE(int   WINAPI SetScrollPosT(HWND, int, int, BOOL), SetScrollPos)
DETOUR_TRAMPOLINE(BOOL  WINAPI GetScrollInfoT(HWND, int, LPSCROLLINFO), GetScrollInfo)
DETOUR_TRAMPOLINE(int   WINAPI SetScrollInfoT(HWND, int, LPCSCROLLINFO, BOOL), SetScrollInfo)
DETOUR_TRAMPOLINE(BOOL  WINAPI GetScrollRangeT(HWND, int, LPINT, LPINT), GetScrollRange)
DETOUR_TRAMPOLINE(BOOL  WINAPI SetScrollRangeT(HWND, int, int, int, BOOL), SetScrollRange)
DETOUR_TRAMPOLINE(BOOL  WINAPI ShowScrollBarT(HWND, int, BOOL), ShowScrollBar)
DETOUR_TRAMPOLINE(BOOL  WINAPI EnableScrollBarT(HWND, UINT, UINT), EnableScrollBar)

//设置滚动
int WINAPI SetScrollInfoD(HWND hWnd, int fnBar, LPCSCROLLINFO lpScrollInfo, BOOL bRedraw)
{
	if (SkinSB_IsValid(hWnd))
	{
		return SkinSB_SetScrollInfo(hWnd,fnBar,lpScrollInfo,bRedraw);
	}
	else
	{
		return SetScrollInfoT(hWnd,fnBar,lpScrollInfo,bRedraw);
	}
}

//获取滚动
BOOL WINAPI GetScrollInfoD(HWND hWnd, int fnBar, LPSCROLLINFO lpScrollInfo)
{
	if (SkinSB_IsValid(hWnd))
	{
		return SkinSB_GetScrollInfo(hWnd, fnBar, lpScrollInfo);
	}
	else
	{
		return GetScrollInfoT(hWnd, fnBar, lpScrollInfo);
	}
}

//设置滚动
int WINAPI SetScrollPosD(HWND hWnd, int nBar, int nPos, BOOL bRedraw)
{
	if (SkinSB_IsValid(hWnd))
	{
		return SkinSB_SetScrollPos(hWnd,nBar, nPos,bRedraw);
	}
	else
	{
		return SetScrollPosT(hWnd,nBar, nPos,bRedraw);
	}
}

//获取滚动
int WINAPI GetScrollPosD(HWND hWnd, int nBar)
{
	if (SkinSB_IsValid(hWnd))
	{
		return SkinSB_GetScrollPos(hWnd,nBar);
	}
	else
	{
		return GetScrollPosT(hWnd,nBar);
	}
}

//设置滚动
BOOL WINAPI SetScrollRangeD(HWND hWnd, int nBar, int nMinPos, int nMaxPos, BOOL bRedraw)
{
	if (SkinSB_IsValid(hWnd))
	{
		return SkinSB_SetScrollRange(hWnd,nBar,nMinPos,nMaxPos,bRedraw);
	}
	else
	{
		return SetScrollRangeT(hWnd,nBar,nMinPos,nMaxPos,bRedraw);
	}
}

//获取滚动
BOOL WINAPI GetScrollRangeD(HWND hWnd, int nBar, LPINT lpMinPos, LPINT lpMaxPos)
{
	if (SkinSB_IsValid(hWnd))
	{
		return SkinSB_GetScrollRange(hWnd,nBar,lpMinPos,lpMaxPos);
	}
	else
	{
		return GetScrollRangeT(hWnd,nBar,lpMinPos,lpMaxPos);
	}
}

//显示滚动
BOOL WINAPI ShowScrollBarD(HWND hWnd, int nBar, BOOL bShow)
{
	if (SkinSB_IsValid(hWnd))
	{
		return SkinSB_ShowScrollBar(hWnd,nBar,bShow);
	}
	else
	{
		return ShowScrollBarT(hWnd,nBar,bShow);
	}
}

//启用滚动
BOOL WINAPI EnableScrollBarD(HWND hWnd, UINT wSBflags, UINT wArrows)
{
	if (SkinSB_IsValid(hWnd))
	{
		return SkinSB_EnableScrollBar(hWnd,wSBflags,wArrows);
	}
	else
	{
		return EnableScrollBarT(hWnd,wSBflags,wArrows);
	}
}

extern "C" int APIENTRY
DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	// Remove this if you use lpReserved
	UNREFERENCED_PARAMETER(lpReserved);

	if (dwReason == DLL_PROCESS_ATTACH)
	{
		// Extension DLL one-time initialization
		if (!AfxInitExtensionModule(SkinControlsDLL, hInstance))
			return 0;

		// Insert this DLL into the resource chain
		// NOTE: If this Extension DLL is being implicitly linked to by
		//  an MFC Regular DLL (such as an ActiveX Control)
		//  instead of an MFC application, then you will want to
		//  remove this line from DllMain and put it in a separate
		//  function exported from this Extension DLL.  The Regular DLL
		//  that uses this Extension DLL should then explicitly call that
		//  function to initialize this Extension DLL.  Otherwise,
		//  the CDynLinkLibrary object will not be attached to the
		//  Regular DLL's resource chain, and serious problems will
		//  result.

		new CDynLinkLibrary(SkinControlsDLL);

		//加载钩子
		DetourFunctionWithTrampoline((PBYTE)SetScrollPosT,(PBYTE)SetScrollPosD);
		DetourFunctionWithTrampoline((PBYTE)GetScrollPosT,(PBYTE)GetScrollPosD);
		DetourFunctionWithTrampoline((PBYTE)SetScrollInfoT,(PBYTE)SetScrollInfoD);
		DetourFunctionWithTrampoline((PBYTE)GetScrollInfoT,(PBYTE)GetScrollInfoD);
		DetourFunctionWithTrampoline((PBYTE)ShowScrollBarT,(PBYTE)ShowScrollBarD);
		DetourFunctionWithTrampoline((PBYTE)SetScrollRangeT,(PBYTE)SetScrollRangeD);
		DetourFunctionWithTrampoline((PBYTE)GetScrollRangeT,(PBYTE)GetScrollRangeD);
		DetourFunctionWithTrampoline((PBYTE)EnableScrollBarT,(PBYTE)EnableScrollBarD);

	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{
		// Terminate the library before destructors are called
		AfxTermExtensionModule(SkinControlsDLL);

		//卸载钩子
		DetourRemove((PBYTE)SetScrollPosT,(PBYTE)SetScrollPosD);
		DetourRemove((PBYTE)GetScrollPosT,(PBYTE)GetScrollPosD);
		DetourRemove((PBYTE)SetScrollInfoT,(PBYTE)SetScrollInfoD);
		DetourRemove((PBYTE)GetScrollInfoT,(PBYTE)GetScrollInfoD);
		DetourRemove((PBYTE)ShowScrollBarT,(PBYTE)ShowScrollBarD);
		DetourRemove((PBYTE)SetScrollRangeT,(PBYTE)SetScrollRangeD);
		DetourRemove((PBYTE)GetScrollRangeT,(PBYTE)GetScrollRangeD);
		DetourRemove((PBYTE)EnableScrollBarT,(PBYTE)EnableScrollBarD);
	}
	return 1;   // ok
}
