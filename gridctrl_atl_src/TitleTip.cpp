////////////////////////////////////////////////////////////////////////////
// TitleTip.cpp : implementation file
//
// Code taken from www.codeguru.com. - thanks Zafir!
//
// Written by Mario Zucca 
//        mailto:mario@GenoaValley.org
//        http://www.GenoaValley.org
//
// Copyright (c) 2000.
//
// The code contained in this file is based on the original
// Grid control written by Chris Maunder,
//        mailto:chris@codeproject.com
//        http://www.codeproject.com

#include "stdafx.h"
#include "TitleTip.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTitleTip::CTitleTip()
{
	m_rectTitle.left =0;
	m_rectTitle.right =0;
	m_rectTitle.top =0;
	m_rectTitle.bottom =0;
}

CTitleTip::~CTitleTip()
{
	DestroyWindow();
}

BOOL CTitleTip::Create(HWND hwnd)
{
	ATLASSERT(hwnd);

	DWORD dwStyle = WS_BORDER | WS_POPUP; 
	DWORD dwExStyle = WS_EX_TOOLWINDOW | WS_EX_TOPMOST;
	m_pParentWnd.Attach(hwnd);

	RECT rc = {0,0,0,0};

	HWND wnd = CWindowImpl<CTitleTip>::Create(hwnd,rc,NULL,dwStyle,dwExStyle);

	return (m_hWnd != NULL);

}

void CTitleTip::Show(RECT rectTitle, LPCTSTR lpszTitleText,
					 int xoffset/*=0*/,
					 LPRECT lpHoverRect /*=NULL*/,
					 LPLOGFONT lpLogFont /*=NULL*/)
{
	ATLASSERT( m_hWnd );

    if (
		(rectTitle.right-rectTitle.left <=0) ||
		(rectTitle.bottom-rectTitle.top <=0))
        return;

    m_rectHover = (lpHoverRect != NULL)? *lpHoverRect : rectTitle;

	m_pParentWnd.ClientToScreen( &m_rectHover );
    m_pParentWnd.ScreenToClient( &m_rectHover );

	// If titletip is already displayed, don't do anything.
	if( IsWindowVisible() ) 
		return;

	// Do not display the titletip is app does not have focus
	if( GetFocus() == NULL )
		return;

	// Define the rectangle outside which the titletip will be hidden.
	// We add a buffer of one pixel around the rectangle
	m_rectTitle.top    = -1;
	m_rectTitle.left   = -xoffset-1;
	m_rectTitle.right  = (m_rectTitle.right-m_rectTitle.left)-xoffset;
	m_rectTitle.bottom = (m_rectTitle.bottom-m_rectTitle.top)+1;

	// Determine the width of the text
	m_pParentWnd.ClientToScreen( &rectTitle );

	HDC dc = GetDC();
	
	_bstr_t strTitle = _T("");
    strTitle += _T(" ");
    strTitle += lpszTitleText; 
    strTitle += _T(" ");

	HFONT font, pOldFont = NULL;
    if (lpLogFont)
    {
        font = CreateFontIndirect(lpLogFont);
	    pOldFont = (HFONT) SelectObject(dc, font );
    }
    else
    {
        // use same font as ctrl
	    pOldFont = (HFONT)SelectObject(dc, m_pParentWnd.GetFont() );
    }

	SIZE size;
	GetTextExtentPoint32(dc, strTitle,strTitle.length(), &size);

    TEXTMETRIC tm;
    GetTextMetrics(dc,&tm);
    size.cx += tm.tmOverhang;

	RECT rectDisplay = rectTitle;
	rectDisplay.left += xoffset;
	rectDisplay.right = rectDisplay.left + size.cx + xoffset;
    
    // Do not display if the text fits within available space
    if( rectDisplay.right > rectTitle.right-xoffset )
    {
        // Show the titletip
        SetWindowPos( HWND_TOP, &rectDisplay, 
            SWP_SHOWWINDOW|SWP_NOACTIVATE );
        
        SetBkMode(dc, TRANSPARENT );
        TextOut(dc, 0, 0, strTitle,strTitle.length() );
		TRACKMOUSEEVENT tme;
		tme.cbSize = sizeof(tme);
		tme.dwFlags = TME_LEAVE;
		tme.hwndTrack = m_hWnd;
		tme.dwHoverTime = HOVER_DEFAULT;

 //       BOOL err = _TrackMouseEvent(&tme);
		SetCapture();
    }
    
    SelectObject(dc, pOldFont );
	DeleteObject(font);
	ReleaseDC(dc);

}

void CTitleTip::Hide()
{
  	if (!::IsWindow(m_hWnd))
        return;

    if (GetCapture() == m_hWnd)
        ReleaseCapture();

	ShowWindow( SW_HIDE );

}
