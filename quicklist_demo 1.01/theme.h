#pragma once
#ifdef USEXPTHEMES
#include "themelib.h"

/************************************************************
**
**	Simple Theme class for CHoverBitmapButton
**
**	You could use the WTL CTheme class instead.
**
**	by Rail Jon Rogut Feb 2003
**
*************************************************************/

class CTheme
	{
	public:
		CTheme();
		~CTheme();

	public:
		void	Init(void);
		void	Init(HWND hWnd);
		void	ReInit(void);
		void	ThemeChanged(HWND hWnd);
		void	OpenTheme(HWND hWnd);

		// Setup defaults for CHoverBitmapButton:

		void	DrawThemeBackground(HDC dc, RECT *pRect, 
											int iPartID = BP_PUSHBUTTON, 
											int iStateID = PBS_HOT, 
											RECT *pClipRect = NULL); 

		void	DrawThemeEdge(HDC dc, RECT *pRect, 
											UINT uEdge = EDGE_BUMP, 
											UINT uFlags = BF_RECT, 
											int iPartID = BP_PUSHBUTTON, 
											int iStateID = PBS_HOT, 
											RECT *pClipRect = NULL);

		void	GetThemeBackgroundContentRect(	HDC dc,
										int iPartID,
										int iStateID,					  
										const RECT* pBoundingRect,					  
										RECT* pContentRect );

		void	DrawThemeText(	HDC dc,
								int iPartId,
								int iStateId,
								LPCWSTR pszText,
								int iCharCount,
								DWORD dwTextFlags,
								DWORD dwTextFlags2,
								const RECT *pRect
								);

		void	DrawThemeText(	HDC dc,
								int iPartId,
								int iStateId,
								LPCSTR pszText,
								int iCharCount,
								DWORD dwTextFlags,
								DWORD dwTextFlags2,
								const RECT *pRect
								);


		BOOL	GetAppearance(void);

	public:
		BOOL	m_bXPTheme;
		BOOL	m_bThemeExists;
		BOOL	m_bLibLoaded;
		HMODULE	m_hModThemes;
		HTHEME	m_hTheme;

		HWND	m_hWnd;

		PFNOPENTHEMEDATA					zOpenThemeData;
		PFNDRAWTHEMEBACKGROUND				zDrawThemeBackground;
		PFNCLOSETHEMEDATA					zCloseThemeData;
		PFNDRAWTHEMEEDGE					zDrawThemeEdge;
		PFNDRAWTHEMEICON					zDrawThemeIcon;
		PFNDRAWTHEMETEXT					zDrawThemeText;
		PFNGETTHEMEBACKGROUNDCONTENTRECT	zGetThemeBackgroundContentRect;

		//Changed by PEK
		PFNISTHEMEACTIVE					zIsAppThemed;
};

#endif