// ScreenSaverWnd.cpp : implementation file
//
//////////
//
// Copyright (C) 1991-98 Ed Halley.
//   http://www.explorati.com/people/ed/
//   ed@explorati.com
//
// This published source code represents original intellectual
// property, owned and copyrighted by Ed Halley.
//
// The owner has authorized this source code for general public
// use without royalty, under two conditions:
//    * The source code maintains this copyright notice in full.
//    * The source code is only distributed for free or
//      reasonable duplication cost, not for distribution profit.
//
// Unauthorized use, copying or distribution is a violation of
// U.S. and international laws and is strictly prohibited.
//
//////////
//

#include "StdAfx.h"

#include "ScreenSaverWnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNAMIC(CScreenSaverWnd, CWnd)

BEGIN_MESSAGE_MAP(CScreenSaverWnd, CWnd)
	//{{AFX_MSG_MAP(CScreenSaverWnd)
	ON_WM_CREATE()
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
	ON_WM_PALETTECHANGED()
	ON_WM_QUERYNEWPALETTE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/* static */ CScreenSaverWnd* CScreenSaverWnd::sm_pTheScreenSaver = NULL;

CScreenSaverWnd::CScreenSaverWnd()
{
	sm_pTheScreenSaver = this;
	m_bAutoBlack = TRUE;
	m_pPalette = NULL;
}

CScreenSaverWnd::~CScreenSaverWnd()
{
	sm_pTheScreenSaver = NULL;
}

/////////////////////////////////////////////////////////////////////////////

//
// Setting up the new screen saver window.
//

int CScreenSaverWnd::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

#ifdef _DEBUG
	// Screen savers should be TOPMOST to block out any other windows,
	// such as other topmost windows created previously.  However, if you
	// are trying to debug a screen saver, it can get in the way.
	// We remove the topmost status from this window only if we're _DEBUG.
	// 
	SetWindowPos(&CWnd::wndNoTopMost,
		0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
#endif

	RestoreOptions();
	OnInitialUpdate();

	return 0;
}

void CScreenSaverWnd::OnInitialUpdate()
{
	// Base version does nothing.
	// A derived class can set up basic data structures.
}

void CScreenSaverWnd::SaveOptions()
{
	// Base version does nothing.
	// A derived class can store options in the registry or ini files.
}

void CScreenSaverWnd::RestoreOptions()
{
	// Base version does nothing.
	// A derived class can retrieve options from the registry or ini files.
}

/////////////////////////////////////////////////////////////////////////////

//
// The screen saver is made to paint.  We support OnDraw(), just like CView
// does, as a matter of convenience.
//
// Also for convenience, by the time an override of OnDraw() is called, the
// background has been blacked (if m_bAutoBlack), and the palette in
// m_pPalette has been realized properly.  These are optional.
//

BOOL CScreenSaverWnd::OnEraseBkgnd(CDC* pDC) 
{
	if (m_bAutoBlack)
	{
		CRect rcClient;
		GetClientRect(&rcClient);
		pDC->FillSolidRect(&rcClient, RGB(0, 0, 0));
	}
	return TRUE;
}

void CScreenSaverWnd::OnPaint() 
{
	CPaintDC dc(this);
	if (m_pPalette)
	{
		dc.SelectPalette(m_pPalette, FALSE);
		dc.RealizePalette();
	}

	OnDraw(&dc);
}

void CScreenSaverWnd::OnDraw(CDC* pDC)
{
	// Base version does nothing.
	// A derived class can use the DC to paint in any manner on the screen.
}

/////////////////////////////////////////////////////////////////////////////

//
// There is nothing about CScreenSaverWnd which requires using a CPalette.
// As a convenience, it can hold onto a CPalette and realize it at the proper
// times according to WM_QUERYNEWPALETTE and WM_PALETTECHANGED notifications.
//
// Separately, a derived class can turn on and off the automatic black
// background behavior which is handled in OnEraseBkgnd(). When it is off,
// all of the user's windows will still be visible when the screen saver
// starts its OnDraw().
//

CPalette* CScreenSaverWnd::GetPalette() const
{
	return m_pPalette;
}

CPalette* CScreenSaverWnd::SetPalette(CPalette* pPalette)
{
	// At no time does the CScreenSaverWnd take 'ownership' of a palette
	// object; i.e., it will never delete or create them.  It's just holding.
	//
	CPalette* pOldPalette = m_pPalette;
	m_pPalette = pPalette;
	OnQueryNewPalette();
	return pOldPalette;
}

BOOL CScreenSaverWnd::OnQueryNewPalette() 
{
	if (!m_pPalette)
		return FALSE;

	CClientDC dc(this);
	dc.SelectPalette(m_pPalette, FALSE);
	UINT uChanged = dc.RealizePalette();

	return TRUE;
}

void CScreenSaverWnd::OnPaletteChanged(CWnd* pFocusWnd) 
{
	if (pFocusWnd == this)
		return;

	OnQueryNewPalette();
}

BOOL CScreenSaverWnd::IsAutoBlack() const
{
	return m_bAutoBlack;
}

void CScreenSaverWnd::SetAutoBlack(BOOL bAutoBlack /* = TRUE */)
{
	m_bAutoBlack = bAutoBlack;
}

/////////////////////////////////////////////////////////////////////////////

//
// The message routing for screen saver windows is nonstandard.  Calling the
// regular default window proc is not appropriate.  These overrides will
// route the messages properly.
//
// For example, when the user hits a key or moves the mouse, if it's not
// handled by the screen saver in some way, it should go to the default
// ::DefScreenSaverProc() which will end the screen saver cleanly.
//

LRESULT CScreenSaverWnd::WindowProc(UINT uMsg,
                                    WPARAM wParam,
                                    LPARAM lParam)
{
	return CWnd::WindowProc(uMsg, wParam, lParam);
}

LRESULT CScreenSaverWnd::DefWindowProc(UINT uMsg,
                                       WPARAM wParam,
                                       LPARAM lParam)
{
	return ::DefScreenSaverProc(m_hWnd, uMsg, wParam, lParam);
}

/////////////////////////////////////////////////////////////////////////////

// ::ScreenSaverProc():
// This API must be exported to be recognized as a screen saver.  This serves
// as the window message proc called by Windows to display the screen saver
// window.  Not all messages that go to the window actually get sent to our
// proc.
//
LRESULT WINAPI ScreenSaverProc(HWND hWnd, UINT uMsg,
                               WPARAM wParam, LPARAM lParam)
{
	// There should be one global instance of a CScreenSaverWnd derivative.
	ASSERT(CScreenSaverWnd::sm_pTheScreenSaver);
	if (!CScreenSaverWnd::sm_pTheScreenSaver)
		return 0L;

	// Since we don't have a CWinApp object, we need to initialize the MFC
	// internals ourselves, and terminate them when the window is destroyed.

	if (!CScreenSaverWnd::sm_pTheScreenSaver->m_hWnd)
	{
		AfxWinInit((HINSTANCE)::GetWindowLong(hWnd, GWL_HINSTANCE),
		           NULL, "", SW_SHOWNORMAL);
		CScreenSaverWnd::sm_pTheScreenSaver->Attach(hWnd);
	}

	LRESULT lResult =
		::AfxCallWndProc(
			CScreenSaverWnd::sm_pTheScreenSaver,
			CScreenSaverWnd::sm_pTheScreenSaver->m_hWnd,
			uMsg, wParam, lParam);

	if (uMsg == WM_NCDESTROY)
	{
		ASSERT(!CScreenSaverWnd::sm_pTheScreenSaver ||
		       !CScreenSaverWnd::sm_pTheScreenSaver->m_hWnd);
		AfxWinTerm();
	}

	return lResult;
}

/////////////////////////////////////////////////////////////////////////////
