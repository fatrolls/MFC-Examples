#include <afxwin.h>
#include "MouseCap.h"

CMyApp myApp;

/////////////////////////////////////////////////////////////////////////
// CMyApp member functions

BOOL CMyApp::InitInstance ()
{
    m_pMainWnd = new CMainWindow;
    m_pMainWnd->ShowWindow (m_nCmdShow);
    m_pMainWnd->UpdateWindow ();
    return TRUE;
}

/////////////////////////////////////////////////////////////////////////
// CMainWindow message map and member functions

BEGIN_MESSAGE_MAP (CMainWindow, CFrameWnd)
    ON_WM_LBUTTONDOWN ()
    ON_WM_LBUTTONUP ()
    ON_WM_MOUSEMOVE ()
    ON_WM_NCLBUTTONDOWN ()
END_MESSAGE_MAP ()

CMainWindow::CMainWindow ()
{
    m_bTracking = FALSE;
    m_bCaptureEnabled = TRUE;

	//
	// Register a WNDCLASS.
	//
    CString strWndClass = AfxRegisterWndClass (
        0,
        AfxGetApp ()->LoadStandardCursor (IDC_CROSS),
        (HBRUSH) (COLOR_WINDOW + 1),
        AfxGetApp ()->LoadStandardIcon (IDI_WINLOGO)
    );

	//
	// Create a window.
	//
    Create (strWndClass, _T ("Mouse Capture Demo (Capture Enabled)"));
}

void CMainWindow::OnLButtonDown (UINT nFlags, CPoint point)
{
	//
	// Record the anchor point and set the tracking flag.
	//
    m_ptFrom = point;
    m_ptTo = point;
    m_bTracking = TRUE;

	//
	// If capture is enabled, capture the mouse.
	//
    if (m_bCaptureEnabled)
        SetCapture ();
}

void CMainWindow::OnMouseMove (UINT nFlags, CPoint point)
{
	//
	// If the mouse is moved while we're "tracking" (that is, while a
	// line is being rubber-banded), erase the old rubber-band line and
	// draw a new one.
	//
    if (m_bTracking) {
        CClientDC dc (this);
        InvertLine (&dc, m_ptFrom, m_ptTo);
        InvertLine (&dc, m_ptFrom, point);
        m_ptTo = point;
    }
}

void CMainWindow::OnLButtonUp (UINT nFlags, CPoint point)
{
	//
	// If the left mouse button is released while we're tracking, release
	// the mouse if it's currently captured, erase the last rubber-band
	// line, and draw a thick red line in its place.
	//
    if (m_bTracking) {
        m_bTracking = FALSE;
        if (GetCapture () == this)
            ::ReleaseCapture ();

        CClientDC dc (this);
        InvertLine (&dc, m_ptFrom, m_ptTo);

        CPen pen (PS_SOLID, 16, RGB (255, 0, 0));
        dc.SelectObject (&pen);

        dc.MoveTo (m_ptFrom);
        dc.LineTo (point);
    }
}

void CMainWindow::OnNcLButtonDown (UINT nHitTest, CPoint point)
{
	//
	// When the window's title bar is clicked with the left mouse button,
	// toggle the capture flag on or off and update the window title.
	//
    if (nHitTest == HTCAPTION) {
        m_bCaptureEnabled = m_bCaptureEnabled ? FALSE : TRUE;
        SetWindowText (m_bCaptureEnabled ?
            _T ("Mouse Capture Demo (Capture Enabled)") :
            _T ("Mouse Capture Demo (Capture Disabled)"));
    }
    CFrameWnd::OnNcLButtonDown (nHitTest, point);
}

void CMainWindow::InvertLine (CDC* pDC, CPoint ptFrom, CPoint ptTo)
{
	//
	// Invert a line of pixels by drawing a line in the R2_NOT drawing mode.
	//
    int nOldMode = pDC->SetROP2 (R2_NOT);

    pDC->MoveTo (ptFrom);
    pDC->LineTo (ptTo);

    pDC->SetROP2 (nOldMode);
}
