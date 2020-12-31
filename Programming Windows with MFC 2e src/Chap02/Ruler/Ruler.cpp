#include <afxwin.h>
#include "Ruler.h"

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
    Create (NULL, _T ("Ruler"));
}

void CMainWindow::OnPaint ()
{
    CPaintDC dc (this);
    
    //
    // Initialize the device context.
    //
    dc.SetMapMode (MM_LOENGLISH);
    dc.SetTextAlign (TA_CENTER | TA_BOTTOM);
    dc.SetBkMode (TRANSPARENT);

    //
    // Draw the body of the ruler.
    //
    CBrush brush (RGB (255, 255, 0));
    CBrush* pOldBrush = dc.SelectObject (&brush);
    dc.Rectangle (100, -100, 1300, -200);
    dc.SelectObject (pOldBrush);

    //
    // Draw the tick marks and labels.
    //
    for (int i=125; i<1300; i+=25) {
        dc.MoveTo (i, -192);
        dc.LineTo (i, -200);
    }

    for (i=150; i<1300; i+=50) {
        dc.MoveTo (i, -184);
        dc.LineTo (i, -200);
    }

    for (i=200; i<1300; i+=100) {
        dc.MoveTo (i, -175);
        dc.LineTo (i, -200);

        CString string;
        string.Format (_T ("%d"), (i / 100) - 1);
        dc.TextOut (i, -175, string);
    }
}
