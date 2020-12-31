// SpecialStatusBar.cpp: implementation of the CSpecialStatusBar class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ImageEdit.h"
#include "SpecialStatusBar.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

BEGIN_MESSAGE_MAP(CSpecialStatusBar, CStatusBar)
	ON_WM_CREATE ()
	ON_WM_SIZE ()
END_MESSAGE_MAP()

CSpecialStatusBar::CSpecialStatusBar()
{
}

CSpecialStatusBar::~CSpecialStatusBar()
{
}

int CSpecialStatusBar::OnCreate (LPCREATESTRUCT lpcs)
{
	static UINT nIndicators[] =
	{
		ID_SEPARATOR,
		ID_SEPARATOR,
		ID_SEPARATOR
	};

	if (CStatusBar::OnCreate (lpcs) == -1)
		return -1;

	//
	// Add panes to the status bar.
	//
	SetIndicators (nIndicators, sizeof (nIndicators) / sizeof (UINT));

	//
	// Size the status bar panes.
	//
    TEXTMETRIC tm;
    CClientDC dc (this);
    CFont* pFont = GetFont ();
    CFont* pOldFont = dc.SelectObject (pFont);
    dc.GetTextMetrics (&tm);
    dc.SelectObject (pOldFont);

    int cxWidth;
    UINT nID, nStyle;
    GetPaneInfo (1, nID, nStyle, cxWidth);
    SetPaneInfo (1, nID, nStyle, tm.tmAveCharWidth * 24);
    GetPaneInfo (2, nID, nStyle, cxWidth);
    SetPaneInfo (2, nID, SBPS_NOBORDERS, tm.tmAveCharWidth * 24);

	//
	// Place a progress control in the rightmost pane.
	//
	CRect rect;
	GetItemRect (2, &rect);
	m_wndProgress.Create (WS_CHILD | WS_VISIBLE | PBS_SMOOTH, rect, this, -1);
	m_wndProgress.SetRange (0, 100);
	m_wndProgress.SetPos (0);
	return 0;
}

void CSpecialStatusBar::OnSize (UINT nType, int cx, int cy)
{
	CStatusBar::OnSize (nType, cx, cy);

	//
	// Resize the rightmost pane to fit the resized status bar.
	//
	CRect rect;
	GetItemRect (2, &rect);
	m_wndProgress.SetWindowPos (NULL, rect.left, rect.top,
		rect.Width (), rect.Height (), SWP_NOZORDER);
}

void CSpecialStatusBar::SetImageStats(LPCTSTR pszStats)
{
	SetPaneText (1, pszStats, TRUE);
}

void CSpecialStatusBar::SetProgress(int nPercent)
{
	ASSERT (nPercent >= 0 && nPercent <= 100);
	m_wndProgress.SetPos (nPercent);
}
