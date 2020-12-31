#pragma once
#ifdef USEXPTHEMES

/************************************************************
**
**	Simple Theme class for CHoverBitmapButton
**
**	You could use the WTL CTheme class instead.
**
**	by Rail Jon Rogut Feb 2003
**
**	Include this in stdafx.h
**
*************************************************************/

#include <Uxtheme.h>
#include <tmschema.h>

typedef HRESULT(__stdcall *PFNCLOSETHEMEDATA)(HTHEME hTheme);
typedef HRESULT(__stdcall *PFNDRAWTHEMEBACKGROUND)(HTHEME hTheme, HDC hdc, 
							int iPartId, int iStateId, const RECT *pRect,  const RECT *pClipRect);
typedef HTHEME(__stdcall *PFNOPENTHEMEDATA)(HWND hwnd, LPCWSTR pszClassList);
typedef HRESULT (__stdcall *PFNDRAWTHEMETEXT)(HTHEME hTheme, HDC hdc, int iPartId, 
							int iStateId, LPCWSTR pszText, int iCharCount, DWORD dwTextFlags, 
							DWORD dwTextFlags2, const RECT *pRect);
typedef HRESULT (__stdcall *PFNGETTHEMEBACKGROUNDCONTENTRECT)(HTHEME hTheme,  HDC hdc, 
							int iPartId, int iStateId,  const RECT *pBoundingRect, 
							RECT *pContentRect);

typedef HRESULT (__stdcall *PFNDRAWTHEMEEDGE)(HTHEME hTheme,  HDC hdc, 
							int iPartId, int iStateId,  const RECT *pDestRect, 
							UINT uEdge, UINT uFlags, RECT *pContentRect);

typedef HRESULT (__stdcall *PFNDRAWTHEMEICON)(HTHEME hTheme,  HDC hdc, 
							int iPartId, int iStateId,  const RECT *pRect, 
							HIMAGELIST himl, int iImageIndex);

//Changed by PEK
typedef BOOL (__stdcall *PFNISTHEMEACTIVE)(VOID);

#endif