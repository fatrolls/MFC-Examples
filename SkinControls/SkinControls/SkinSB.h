
#ifndef SKIN_SB_H_
#define SKIN_SB_H_
#pragma once

#include "SkinControlsDefine.h"

#ifdef __cplusplus
extern "C"{
#endif

	//----------------------------------------------------------------
	// Name : SkinSB_Init()
	// Desc : Initialize and load the scrollbar skin
	//----------------------------------------------------------------
	SKIN_CONTROLS_EXPORT BOOL WINAPI SkinSB_InitH(HWND hwnd, HBITMAP hBmp);

	//----------------------------------------------------------------
	// Name : SkinSB_Init()
	// Desc : Initialize and load the scrollbar skin
	//----------------------------------------------------------------
	SKIN_CONTROLS_EXPORT BOOL WINAPI SkinSB_Init(HWND hwnd, LPCTSTR pszFileName);


	//----------------------------------------------------------------
	// Name : SkinSB_Uninit()
	// Desc : Remove the scrollbar skin
	//----------------------------------------------------------------
	SKIN_CONTROLS_EXPORT BOOL WINAPI SkinSB_Uninit(HWND hwnd);


	//----------------------------------------------------------------
	// Name : SkinSB_IsValid()
	// Desc : Whether initialied ?
	//----------------------------------------------------------------
	SKIN_CONTROLS_EXPORT BOOL WINAPI SkinSB_IsValid(HWND hwnd);


	//----------------------------------------------------------------
	// Name : SkinSB_GetScrollInfo()
	// Desc : Gets the information for a skin scroll bar
	//----------------------------------------------------------------
	SKIN_CONTROLS_EXPORT BOOL WINAPI SkinSB_GetScrollInfo(HWND hwnd, int fnBar, LPSCROLLINFO lpsi);


	//----------------------------------------------------------------
	// Name : SkinSB_SetScrollInfo()
	// Desc : Sets the information for a skin scroll bar
	//---------------------------------------------------------------- 
	SKIN_CONTROLS_EXPORT int  WINAPI SkinSB_SetScrollInfo(HWND hwnd, int fnBar, LPCSCROLLINFO psi, BOOL fRedraw);


	//----------------------------------------------------------------
	// Name : SkinSB_GetScrollPos()
	// Desc : Gets the thumb position in a skin scroll bar
	//----------------------------------------------------------------
	SKIN_CONTROLS_EXPORT int  WINAPI SkinSB_GetScrollPos(HWND hwnd, int fnBar);


	//----------------------------------------------------------------
	// Name : SkinSB_SetScrollPos()
	// Desc : Sets the current position of the thumb in a skin scroll bar
	//----------------------------------------------------------------
	SKIN_CONTROLS_EXPORT int  WINAPI SkinSB_SetScrollPos(HWND hwnd, int nBar, int nPos, BOOL fRedraw);


	//----------------------------------------------------------------
	// Name : SkinSB_GetScrollRange()
	// Desc : Gets the scroll range for a skin scroll bar
	//----------------------------------------------------------------
	SKIN_CONTROLS_EXPORT BOOL WINAPI SkinSB_GetScrollRange(HWND hwnd, int nBar, LPINT lpMinPos, LPINT lpMaxPos);


	//----------------------------------------------------------------
	// Name : SkinSB_SetScrollRange()
	// Desc : Sets the scroll range of a skin scroll bar
	//----------------------------------------------------------------
	SKIN_CONTROLS_EXPORT BOOL WINAPI SkinSB_SetScrollRange(HWND hwnd, int nBar, int nMinPos, int nMaxPos, BOOL fRedraw);


	//----------------------------------------------------------------
	// Name : SkinSB_ShowScrollBar()
	// Desc : Shows or hides a skin scroll bar
	//----------------------------------------------------------------
	SKIN_CONTROLS_EXPORT BOOL WINAPI SkinSB_ShowScrollBar(HWND hwnd, int wBar, BOOL fShow);


	//----------------------------------------------------------------
	// Name : SkinSB_EnableScrollBar()
	// Desc : Enables or disables one or both skin scroll bar direction buttons
	//----------------------------------------------------------------
	SKIN_CONTROLS_EXPORT BOOL WINAPI SkinSB_EnableScrollBar(HWND hwnd, UINT wSBflags, UINT wArrows);


#ifdef __cplusplus
}
#endif

#endif // SKIN_SB_H_
