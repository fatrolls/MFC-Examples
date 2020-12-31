#include "stdafx.h"
#ifdef USEXPTHEMES

#include "theme.h"

/************************************************************
**
**	Simple Theme class for CHoverBitmapButton
**
**	You could use the WTL CTheme class instead.
**
**	by Rail Jon Rogut Feb 2003
**
*************************************************************/

CTheme::CTheme()
{
	m_bXPTheme = FALSE;
	m_bLibLoaded = FALSE;

	m_bThemeExists = FALSE;

	m_hModThemes = NULL;
	m_hTheme = NULL;

	m_hWnd = NULL;

	zOpenThemeData = NULL;
	zDrawThemeBackground = NULL;
	zCloseThemeData = NULL;
	zDrawThemeText = NULL;
	zGetThemeBackgroundContentRect = NULL;
	zDrawThemeEdge = NULL;
	zDrawThemeIcon = NULL;

	//Changed by PEK
	zIsAppThemed = NULL;
}

CTheme::~CTheme()
{
	if (m_hModThemes)
		::FreeLibrary(m_hModThemes);
}

void CTheme::Init(HWND hWnd)
{
	Init();
	OpenTheme(hWnd);
}

//Changed by PEK
void CTheme::Init()
{
	m_hModThemes = LoadLibrary(_T("UXTHEME.DLL"));

	if(m_hModThemes)
	{
		zOpenThemeData = (PFNOPENTHEMEDATA)GetProcAddress(m_hModThemes, _T("OpenThemeData"));
		zDrawThemeBackground = (PFNDRAWTHEMEBACKGROUND)GetProcAddress(m_hModThemes, _T("DrawThemeBackground"));
		zCloseThemeData = (PFNCLOSETHEMEDATA)GetProcAddress(m_hModThemes, _T("CloseThemeData"));
		zDrawThemeText = (PFNDRAWTHEMETEXT)GetProcAddress(m_hModThemes, _T("DrawThemeText"));
		zGetThemeBackgroundContentRect = (PFNGETTHEMEBACKGROUNDCONTENTRECT)GetProcAddress(m_hModThemes, _T("GetThemeBackgroundContentRect"));
		zDrawThemeEdge = (PFNDRAWTHEMEEDGE)GetProcAddress(m_hModThemes, _T("DrawThemeEdge"));
		zDrawThemeIcon = (PFNDRAWTHEMEICON)GetProcAddress(m_hModThemes, _T("DrawThemeIcon"));

		//Changed by PEK
		zIsAppThemed = (PFNISTHEMEACTIVE)GetProcAddress(m_hModThemes, _T("IsAppThemed"));
		
		if(zOpenThemeData && zDrawThemeBackground && zCloseThemeData 
									&& zDrawThemeText && zGetThemeBackgroundContentRect 
									&& zDrawThemeEdge && zDrawThemeIcon && zIsAppThemed)
			{
			m_bLibLoaded = TRUE;			
			}
		else
			{
			::FreeLibrary(m_hModThemes);
			m_hModThemes = NULL;
			}
	}

	m_bXPTheme = GetAppearance();
	
}

void	CTheme::ReInit(void)
{
	if (m_hModThemes)
		::FreeLibrary(m_hModThemes);

	m_hModThemes = NULL;
	m_bLibLoaded = FALSE;
	m_bXPTheme = FALSE;
	m_bThemeExists = FALSE;
}

void	CTheme::ThemeChanged(HWND hWnd)
{
	if (m_bLibLoaded)
	{
		if (m_hTheme)
		{
			zCloseThemeData(m_hTheme);
			ReInit();
		}
	}

	Init();

	OpenTheme(hWnd);
}

void	CTheme::OpenTheme(HWND hWnd)
{
	if (m_bLibLoaded)
		{
		ASSERT(hWnd);

		m_hWnd = hWnd;

		m_hTheme = zOpenThemeData(m_hWnd, L"Button");

		if (m_hTheme)
			m_bThemeExists = TRUE;
		}
}

void	CTheme::GetThemeBackgroundContentRect(	HDC dc,
												int iPartID,					  
												int iStateID,
												const RECT* pBoundingRect,
												RECT* pContentRect )
{	
	if(m_hTheme && zGetThemeBackgroundContentRect)	
	{		
		zGetThemeBackgroundContentRect(	m_hTheme,			
										dc,			
										iPartID,			
										iStateID,			
										pBoundingRect,			
										pContentRect		  
										);	
	}
}


void	CTheme::DrawThemeText(	HDC dc,
					  int iPartId,
					  int iStateId,
					  LPCSTR pszText,
					  int iCharCount,
					  DWORD dwTextFlags,
					  DWORD dwTextFlags2,
					  const RECT *pRect
					  )
{
	if(m_hTheme && zDrawThemeText)
	{
		//Convert string to unicode
		int length = iCharCount;

		if(iCharCount == -1)
		{
			length = _mbstrlen(pszText);
		}

		//Use api convert routine
		wchar_t* wbuffer = new wchar_t[length+1];
		
		MultiByteToWideChar(	CP_THREAD_ACP,
								0,
								pszText,
								length,
								wbuffer,
								length+1);
		
		wbuffer[length] = '\0';
		
		DrawThemeText(	dc,
						iPartId,
						iStateId,
						wbuffer,
						iCharCount,
						dwTextFlags,
						dwTextFlags2,
						pRect );
		
		delete [] wbuffer;

	}
}

void	CTheme::DrawThemeText(	HDC dc,
						int iPartId,
						int iStateId,
						LPCWSTR pszText,
						int iCharCount,
						DWORD dwTextFlags,
						DWORD dwTextFlags2,
						const RECT *pRect
					  )
{
	if(m_hTheme && zDrawThemeText)
	{
		zDrawThemeText(	m_hTheme,
						dc,
						iPartId,
						iStateId,
						pszText,
						iCharCount,
						dwTextFlags,
						dwTextFlags2,
						pRect );
	}
}


void	CTheme::DrawThemeBackground(HDC dc, RECT *pRect, int iPartID, int iStateID, RECT *pClipRect)
{
	CRect r = *pRect;

	r.InflateRect(1, 1);

	if (m_hTheme)
		{
		zDrawThemeBackground(m_hTheme, dc, iPartID, iStateID, &r, pClipRect);
		}
}

void	CTheme::DrawThemeEdge(HDC dc, RECT *pRect, UINT uEdge, UINT uFlags, int iPartID, int iStateID, RECT *pClipRect)
{
	if (m_hTheme)
		{
		zDrawThemeEdge(m_hTheme, dc, iPartID, iStateID, pRect, uEdge, uFlags, pClipRect);
		}
}

//Changed by PEK
BOOL	CTheme::GetAppearance(void)
{
	//No library loaded, no themes possible
	if(!m_hModThemes)
		return FALSE;
	
	if(zIsAppThemed != NULL)
		//Ask DLL is theme is used
		return zIsAppThemed();
	
	return FALSE;

	//NOTE! No need to use registry here!
}

#endif