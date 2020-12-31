////////////////////////////////////////////////////////////////////////////////////////////
// This file was created by Ming(2012-11-03).
#ifndef _CUSTOMFONT_H_INCLUDE_
#define _CUSTOMFONT_H_INCLUDE_
#pragma once
#include <atlgdi.h>

class CCustomFont
{
public:
	CCustomFont(void)  : m_pFont(NULL)
	{

	};

	~CCustomFont(void)
	{
		DeleteFont();
	}

private:
	CFont* m_pFont;

public:
	// Delete the font.
	void DeleteFont()
	{
		if (m_pFont)
		{
			delete m_pFont;
			m_pFont = NULL;
		}
	};

	// Set the font via font name.
	CFont* SetFont(CString strFontName = _T("Arial"), int nHeight = -14, int nWeight = FW_BOLD)
	{
		// Delete old font first.
		if (m_pFont)
		{
			DeleteFont();
		}

		m_pFont = new CFont;
		m_pFont->CreateFont(nHeight,					// nHeight 
			0,							// nWidth 
			0,							// nEscapement 
			0,							// nOrientation 
			nWeight,					// nWeight 
			0,							// bItalic 
			FALSE,						// bUnderline 
			0,							// cStrikeOut 
			ANSI_CHARSET,				// nCharSet 
			OUT_DEFAULT_PRECIS,			// nOutPrecision 
			CLIP_DEFAULT_PRECIS,		// nClipPrecision 
			CLEARTYPE_QUALITY,			// nQuality 
			DEFAULT_PITCH | FF_SWISS,	// nPitchAndFamily 
			strFontName					// Font type.
			);
		return m_pFont;
	}

	// Set the font via HFONT.
	CFont* SetFont(HFONT hFont)
	{
		if (hFont == NULL)
		{
			ATLASSERT(FALSE);
			return NULL;
		}

		// Delete old font first.
		if (m_pFont)
		{
			DeleteFont();
		}

		m_pFont = new CFont;
		m_pFont->Attach(hFont);
		return m_pFont;
	}

	// Get Current font.
	CFont* GetCurFont()	
	{
		ATLASSERT(m_pFont->m_hFont != NULL);
		return m_pFont;	
	}
};
#endif // _CUSTOMFONT_H_INCLUDE_
