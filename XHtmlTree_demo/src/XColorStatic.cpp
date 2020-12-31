// XColorStatic.cpp  Version 1.0
//
// Author:  Hans Dietrich
//          hdietrich2@hotmail.com
//
// This software is released into the public domain.
// You are free to use it in any way you like.
//
// This software is provided "as is" with no expressed
// or implied warranty.  I accept no liability for any
// damage or loss of business that this software may cause.
//
///////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "XColorStatic.h"
#include "FontSize.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#pragma warning(disable : 4996)	// disable bogus deprecation warning

///////////////////////////////////////////////////////////////////////////////
// CXColorStatic

BEGIN_MESSAGE_MAP(CXColorStatic, CStatic)
	//{{AFX_MSG_MAP(CXColorStatic)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

///////////////////////////////////////////////////////////////////////////////
// ctor
CXColorStatic::CXColorStatic()
{
	m_rgbText       = GetSysColor(COLOR_BTNTEXT);
	m_rgbBackground = GetSysColor(COLOR_BTNFACE);
	m_pBrush        = new CBrush(m_rgbBackground);
	m_bBold         = FALSE;
	m_hIcon         = NULL;
	m_nXMargin = m_nYMargin = 0;
}

///////////////////////////////////////////////////////////////////////////////
// dtor
CXColorStatic::~CXColorStatic()
{
	if (m_font.GetSafeHandle())
		m_font.DeleteObject();

	if (m_pBrush)
	{
		m_pBrush->DeleteObject();
		delete m_pBrush;
	}
	m_pBrush = NULL;
}

///////////////////////////////////////////////////////////////////////////////
// PreSubclassWindow
void CXColorStatic::PreSubclassWindow() 
{
	// get current font
	CFont* pFont = GetFont();
	if (!pFont)
	{
		HFONT hFont = (HFONT)GetStockObject(DEFAULT_GUI_FONT);
		if (hFont == NULL)
			hFont = (HFONT) GetStockObject(ANSI_VAR_FONT);
		if (hFont)
			pFont = CFont::FromHandle(hFont);
	}
	ASSERT(pFont);
	ASSERT(pFont->GetSafeHandle());

	// create the font for this control
	LOGFONT lf;
	pFont->GetLogFont(&lf);
	m_font.CreateFontIndirect(&lf);
}

///////////////////////////////////////////////////////////////////////////////
// OnPaint
void CXColorStatic::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	dc.SaveDC();

	dc.SetTextColor(m_rgbText);
	dc.SetBkColor(m_rgbBackground);
	dc.SetBkMode(OPAQUE);
	dc.SelectObject(m_pBrush);

	CRect rect;
	GetClientRect(rect); 

	// cannot have both an icon and text

	if (m_hIcon)
	{
		int nIconX = ::GetSystemMetrics(SM_CXICON);
		int nIconY = ::GetSystemMetrics(SM_CYICON);

		rect.left = rect.left + (rect.Width() - nIconX) / 2;
		rect.top = rect.top + (rect.Height() - nIconY) / 2;

		dc.DrawIcon(rect.left, rect.top, m_hIcon);
	}
	else
	{
		dc.SelectObject(&m_font);

		// get static's text
		CString strText = _T("");
		GetWindowText(strText);

		UINT nFormat = 0;
		DWORD dwStyle = GetStyle();

		// set DrawText format from static style settings
		if (dwStyle & SS_CENTER)
			nFormat |= DT_CENTER;
		else if (dwStyle & SS_LEFT)
			nFormat |= DT_LEFT;
		else if (dwStyle & SS_RIGHT)
			nFormat |= DT_RIGHT;

		if (dwStyle & SS_CENTERIMAGE)	// vertical centering ==> single line only
			nFormat |= DT_VCENTER | DT_SINGLELINE;
		else
			nFormat |= DT_WORDBREAK;

		rect.left += m_nXMargin;
		rect.top  += m_nYMargin;
		dc.DrawText(strText, rect, nFormat);
	}
	
	dc.RestoreDC(-1);
}

///////////////////////////////////////////////////////////////////////////////
// OnEraseBkgnd
BOOL CXColorStatic::OnEraseBkgnd(CDC* pDC) 
{
	CRect cr;
	GetClientRect(cr); 
	pDC->FillRect(&cr, m_pBrush);

	return TRUE; //CStatic::OnEraseBkgnd(pDC);
}

///////////////////////////////////////////////////////////////////////////////
// SetFont
void CXColorStatic::SetFont(LOGFONT *pLogFont, BOOL bRedraw /*= TRUE*/)
{
	ASSERT(pLogFont);
	if (!pLogFont)
		return;

	if (m_font.GetSafeHandle())
		m_font.DeleteObject();

	LOGFONT lf = *pLogFont;

	lf.lfWeight = m_bBold ? FW_BOLD : FW_NORMAL;

	m_font.CreateFontIndirect(&lf);

	if (bRedraw)
		RedrawWindow();
}

///////////////////////////////////////////////////////////////////////////////
// SetFont
void CXColorStatic::SetFont(LPCTSTR lpszFaceName, 
							int nPointSize, 
							BOOL bRedraw /*= TRUE*/)
{
	// null face name is ok - we will use current font

	LOGFONT lf;
	memset(&lf, 0, sizeof(lf));

	if (lpszFaceName == NULL)
	{
		CFont *pFont = GetFont();
		ASSERT(pFont);
		pFont->GetLogFont(&lf);
	}
	else
	{
		_tcsncpy(lf.lfFaceName, lpszFaceName, sizeof(lf.lfFaceName)/sizeof(TCHAR)-1);
	}

	lf.lfHeight = GetFontHeight(nPointSize);

	SetFont(&lf, bRedraw);
}

///////////////////////////////////////////////////////////////////////////////
// SetFont
void CXColorStatic::SetFont(CFont *pFont, BOOL bRedraw /*= TRUE*/)
{
	ASSERT(pFont);
	if (!pFont)
		return;

	LOGFONT lf;
	memset(&lf, 0, sizeof(lf));

	pFont->GetLogFont(&lf);

	SetFont(&lf, bRedraw);
}

///////////////////////////////////////////////////////////////////////////////
// SetTextColor
void CXColorStatic::SetTextColor(COLORREF rgb, BOOL bRedraw /*= TRUE*/) 
{ 
	m_rgbText = rgb; 
	if (bRedraw)
		RedrawWindow();
}

///////////////////////////////////////////////////////////////////////////////
// SetBold
void CXColorStatic::SetBold(BOOL bFlag, BOOL bRedraw /*= TRUE*/)
{ 
	m_bBold = bFlag;

	LOGFONT lf;
	memset(&lf, 0, sizeof(lf));

	CFont *pFont = GetFont();
	ASSERT(pFont);
	pFont->GetLogFont(&lf);

	lf.lfWeight = m_bBold ? FW_BOLD : FW_NORMAL;

	SetFont(&lf, bRedraw);
}

///////////////////////////////////////////////////////////////////////////////
// SetBackgroundColor
void CXColorStatic::SetBackgroundColor(COLORREF rgb, BOOL bRedraw /*= TRUE*/) 
{ 
	m_rgbBackground = rgb; 
	if (m_pBrush)
	{
		m_pBrush->DeleteObject();
		delete m_pBrush;
	}
	m_pBrush = new CBrush(m_rgbBackground);
	if (bRedraw)
		RedrawWindow();
}

///////////////////////////////////////////////////////////////////////////////
// SetIcon
void CXColorStatic::SetIcon(HICON hIcon, BOOL bRedraw /*= TRUE*/)
{
	ASSERT(hIcon);

	m_hIcon = hIcon;
	if (bRedraw)
		RedrawWindow();
}
