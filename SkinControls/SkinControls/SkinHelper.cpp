
#include "stdafx.h"
#include "SkinHelper.h"

CFont CSkinHelper::m_DefaultFont; // 默认字体
CFont CSkinHelper::m_CaptionFont; //默认字体

CFont& CSkinHelper::GetDefaultFont()
{
	if (m_DefaultFont.GetSafeHandle() == NULL)
	{
		// 创建字体
		m_DefaultFont.CreateFont(-12,0,0,0,0,0,0,0,0,3,2,ANTIALIASED_QUALITY,2,TEXT("宋体"));
		ASSERT(m_DefaultFont.GetSafeHandle() != NULL);
		return m_DefaultFont;
	}
	return m_DefaultFont;
}

// 标题字体
CFont& CSkinHelper::GetCaptionFont()
{
	if (m_CaptionFont.GetSafeHandle() == NULL)
	{
		m_CaptionFont.CreateFont(
			-12, // nHeight 
			0,          // nWidth 
			0,          // nEscapement 
			0,          // nOrientation 
			FW_BOLD,    // nWeight 
			FALSE,      // bItalic 
			FALSE,      // bUnderline 
			0,          // cStrikeOut 
			ANSI_CHARSET, // nCharSet 
			OUT_DEFAULT_PRECIS, // nOutPrecision 
			CLIP_DEFAULT_PRECIS, // nClipPrecision 
			DEFAULT_QUALITY, // nQuality 
			DEFAULT_PITCH|FF_SWISS, // nPitchAndFamily 
			TEXT("宋体"));

		ASSERT(m_CaptionFont.GetSafeHandle() != NULL);
		return m_CaptionFont;
	}
	return m_CaptionFont;
}

// 手光标
HCURSOR CSkinHelper::GetSysHandCursor()
{
	TCHAR strWinDir[MAX_PATH] = {0};
	HCURSOR hHandCursor = NULL;
	hHandCursor = ::LoadCursor(NULL, MAKEINTRESOURCE(32649));

	// Still no cursor handle - load the WinHelp hand cursor
	if( hHandCursor == NULL )
	{
		GetWindowsDirectory(strWinDir, MAX_PATH);
		_tcscat(strWinDir, _T("\\winhlp32.exe"));

		// This retrieves cursor #106 from winhlp32.exe, which is a hand pointer
		HMODULE hModule = ::LoadLibrary(strWinDir);
		DWORD	dwErr = GetLastError();
		if( hModule != NULL )
		{
			HCURSOR	 hTempCur = ::LoadCursor(hModule, MAKEINTRESOURCE(106));
			hHandCursor = (hTempCur != NULL) ? CopyCursor(hTempCur) : NULL;
			FreeLibrary(hModule);
		}
	}
	return hHandCursor;
}