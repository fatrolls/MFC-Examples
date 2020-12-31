#include <afxwin.h>
#include <math.h>
#include "RegionDemo.h"

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
    ON_WM_PAINT ()
END_MESSAGE_MAP ()

CMainWindow::CMainWindow ()
{
    Create (NULL, _T ("Region Demo"));
}

void CMainWindow::OnPaint ()
{
    CPaintDC dc (this);

	//
    // Create a 72-point Times New Roman font.
	//
    CFont font;
    font.CreatePointFont (720, _T ("Times New Roman"));

	//
    // Create a clipping region from the text string "Hello, MFC."
	//
    CRect rect;
    GetClientRect (&rect);
    CString string ("Hello, MFC");

    CFont* pOldFont = dc.SelectObject (&font);
    CSize size = dc.GetTextExtent (string);
    int x = (rect.Width () - size.cx) / 2;

	TEXTMETRIC tm;
	dc.GetTextMetrics (&tm);
    int y = (rect.Height () - tm.tmHeight) / 2;

    dc.BeginPath ();
    dc.TextOut (x, y, string);
    dc.EndPath ();
    dc.SelectObject (pOldFont);

    CRect rcText;
    CRgn rgn1, rgn2;
    rgn1.CreateFromPath (&dc);
    rgn1.GetRgnBox (&rcText);
    rgn2.CreateRectRgnIndirect (&rcText);
    rgn1.CombineRgn (&rgn2, &rgn1, RGN_DIFF);

    dc.SelectClipRgn (&rgn1);

	//
    // Draw a radial array of lines.
	//
    dc.SetViewportOrg (rect.Width () / 2, rect.Height () / 2);
    double fRadius = hypot (rect.Width () / 2, rect.Height () / 2);

    for (double fAngle = 0.0; fAngle < 6.283; fAngle += 0.01745) {
        dc.MoveTo (0, 0);
        dc.LineTo ((int) ((fRadius * cos (fAngle)) + 0.5),
            (int) ((fRadius * sin (fAngle)) + 0.5));
    }
}
