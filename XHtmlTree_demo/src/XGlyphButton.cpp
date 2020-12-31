// XGlyphButton.cpp  Version 1.1
//
// Author: Hans Dietrich
//         hdietrich2@hotmail.com
//
// Description:
//     XGlyphButton.cpp implements CXGlyphButton, a class to display buttons
//     with a symbol (or glyph) from a specifiec font.  It is based on the
//     work by Geno Carman - "Create a Simple Image Button":
//         http://www.codeguru.com/Cpp/controls/controls/bitmapbuttons/article.php/c5203
//
// This software is released into the public domain.  You are free to use it
// in any way you like, except that you may not sell this source code.
//
// This software is provided "as is" with no expressed or implied warranty.
// I accept no liability for any damage or loss of business that this software
// may cause.
//
///////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "XGlyphButton.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#ifndef CLEARTYPE_QUALITY
// used by the lfQuality member of the LOGFONT struct
#define CLEARTYPE_QUALITY  5		
#endif

/////////////////////////////////////////////////////////////////////////
// CXGlyphButton

BEGIN_MESSAGE_MAP(CXGlyphButton, CButton)
	//{{AFX_MSG_MAP(CXGlyphButton)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

///////////////////////////////////////////////////////////////////////////////
// ctor
CXGlyphButton::CXGlyphButton()
{
	memset(&m_lf, 0, sizeof(LOGFONT));

	m_cGlyph       = 0xB4;		// ? in a diamond
	m_lf.lfCharSet = DEFAULT_CHARSET;
	m_lf.lfHeight  = -30;
	m_lf.lfWeight  = FW_NORMAL;
	m_lf.lfQuality = CLEARTYPE_QUALITY;
	lstrcpy(m_lf.lfFaceName, _T("WingDings"));
}

///////////////////////////////////////////////////////////////////////////////
// dtor
CXGlyphButton::~CXGlyphButton()
{
	if (m_font.GetSafeHandle())
		m_font.DeleteObject();
}

///////////////////////////////////////////////////////////////////////////////
// PreSubclassWindow
void CXGlyphButton::PreSubclassWindow() 
{
	CButton::PreSubclassWindow();

	ReconstructFont();
	TCHAR ch[3] = { 0 };
	ch[0] = (TCHAR) m_cGlyph;
	SetWindowText(ch);
}

///////////////////////////////////////////////////////////////////////////////
// ReconstructFont
void CXGlyphButton::ReconstructFont()
{
	if (m_font.GetSafeHandle())
		m_font.DeleteObject();
	m_lf.lfQuality = CLEARTYPE_QUALITY;
	VERIFY(m_font.CreateFontIndirect(&m_lf));
	CButton::SetFont(&m_font, TRUE);
}

///////////////////////////////////////////////////////////////////////////////
// SetFont
void CXGlyphButton::SetFont(LOGFONT* plf)
{
	memcpy(&m_lf, plf, sizeof(LOGFONT));
	ReconstructFont();
}

///////////////////////////////////////////////////////////////////////////////
// SetFont
void CXGlyphButton::SetFont(CFont* pFont)
{
	pFont->GetLogFont(&m_lf);
	ReconstructFont();
}

///////////////////////////////////////////////////////////////////////////////
// SetGlyph
void CXGlyphButton::SetGlyph(LOGFONT* plf, UINT cGlyph)
{
	SetFont(plf);
	SetGlyph(cGlyph);
}

///////////////////////////////////////////////////////////////////////////////
// SetGlyph
void CXGlyphButton::SetGlyph(CFont* pFont, UINT cGlyph)
{
	pFont->GetLogFont(&m_lf);
	ReconstructFont();
	SetGlyph(cGlyph);
}

///////////////////////////////////////////////////////////////////////////////
// SetGlyph
void CXGlyphButton::SetGlyph(LONG lHeight, 
							 LONG lPointSize, 
							 LONG lWeight, 
							 LPCTSTR lpszFaceName, 
							 UINT cGlyph)
{
	ASSERT(lpszFaceName && lpszFaceName[0] != _T('\0'));
	m_lf.lfFaceName[0] = _T('\0');
	if (lpszFaceName)
		lstrcpy(m_lf.lfFaceName, lpszFaceName);
	m_lf.lfHeight = lHeight;
	if (lPointSize)		// use point size if not 0
			m_lf.lfHeight = GetFontHeight(lPointSize);
	m_lf.lfWeight = lWeight;
	ReconstructFont();
	SetGlyph(cGlyph);
}

///////////////////////////////////////////////////////////////////////////////
// SetGlyph
void CXGlyphButton::SetGlyph(LONG lPointSize, 
							 LPCTSTR lpszFaceName, 
							 UINT cGlyph)
{
	ASSERT(lpszFaceName && lpszFaceName[0] != _T('\0'));
	m_lf.lfFaceName[0] = _T('\0');
	if (lpszFaceName)
		lstrcpy(m_lf.lfFaceName, lpszFaceName);
	m_lf.lfHeight = GetFontHeight(lPointSize);
	ReconstructFont();
	SetGlyph(cGlyph);
}

///////////////////////////////////////////////////////////////////////////////
// SetGlyph
void CXGlyphButton::SetGlyph(UINT cGlyph)
{
	m_cGlyph = cGlyph;
	TCHAR ch[3] = { 0 };
	ch[0] = (TCHAR) m_cGlyph;
	SetWindowText(ch);
}

///////////////////////////////////////////////////////////////////////////////
// SetHeight
void CXGlyphButton::SetHeight(LONG lHeight)
{
	m_lf.lfHeight = lHeight;
	ReconstructFont();
}

///////////////////////////////////////////////////////////////////////////////
// SetWeight
void CXGlyphButton::SetWeight(LONG lWeight)
{
	m_lf.lfWeight = lWeight;
	ReconstructFont();
}

///////////////////////////////////////////////////////////////////////////////
// SetCharSet
void CXGlyphButton::SetCharSet(BYTE bCharSet)
{
	m_lf.lfCharSet = bCharSet;
	ReconstructFont();
}

///////////////////////////////////////////////////////////////////////////////
// SetFaceName
void CXGlyphButton::SetFaceName(LPCTSTR lpszFaceName)
{
	ASSERT(lpszFaceName && lpszFaceName[0] != _T('\0'));
	m_lf.lfFaceName[0] = _T('\0');
	if (lpszFaceName)
		lstrcpy(m_lf.lfFaceName, lpszFaceName);
	ReconstructFont();
}

///////////////////////////////////////////////////////////////////////////////
// SetPointSize
void CXGlyphButton::SetPointSize(LONG lPointSize)
{
	m_lf.lfHeight = GetFontHeight(lPointSize);
	ReconstructFont();
}

///////////////////////////////////////////////////////////////////////////////
// SetWingDingButton
void CXGlyphButton::SetWingDingButton(UINT nButton)
{
	m_lf.lfCharSet = SYMBOL_CHARSET;
	m_lf.lfHeight  = GetFontHeight(14);
	m_lf.lfWeight  = FW_NORMAL;
	lstrcpy(m_lf.lfFaceName, _T("WingDings"));

	SetGlyph(nButton);

	ReconstructFont();
}

///////////////////////////////////////////////////////////////////////////////
// GetFontPointSize
LONG CXGlyphButton::GetFontPointSize(LONG nHeight)
{
	HDC hdc = ::CreateDC(_T("DISPLAY"), NULL, NULL, NULL);
	ASSERT(hdc);
	LONG cyPixelsPerInch = ::GetDeviceCaps(hdc, LOGPIXELSY);
	::DeleteDC(hdc);

	LONG nPointSize = MulDiv(nHeight, 72, cyPixelsPerInch);
	if (nPointSize < 0)
		nPointSize = -nPointSize;

	return nPointSize;
}

///////////////////////////////////////////////////////////////////////////////
// GetFontHeight
LONG CXGlyphButton::GetFontHeight(LONG nPointSize)
{
	HDC hdc = ::CreateDC(_T("DISPLAY"), NULL, NULL, NULL);
	ASSERT(hdc);
	LONG cyPixelsPerInch = ::GetDeviceCaps(hdc, LOGPIXELSY);
	::DeleteDC(hdc);

	LONG nHeight = -MulDiv(nPointSize, cyPixelsPerInch, 72);

	//TRACE(_T("nPointSize=%d  nHeight=%d\n"), nPointSize, nHeight);

	return nHeight;
}
