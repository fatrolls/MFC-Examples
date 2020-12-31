#include <afxwin.h>
#include "LivePalette.h"

CMyApp myApp;

/////////////////////////////////////////////////////////////////////////
// CMyApp member functions

BOOL CMyApp::InitInstance ()
{
	//
	// Verify that the host system is running in a palettized video mode.
	//
    CClientDC dc (NULL);
    if ((dc.GetDeviceCaps (RASTERCAPS) & RC_PALETTE) == 0) {
        AfxMessageBox (_T ("Palette animation is not supported on this " \
		    "device. Set the color depth to 256 colors and try again."),
            MB_ICONSTOP | MB_OK);
        return FALSE;
    }

	//
	// Initialize the application as normal.
	//
    m_pMainWnd = new CMainWindow;
	m_pMainWnd->ShowWindow (m_nCmdShow);
	m_pMainWnd->UpdateWindow ();
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////
// CMainWindow message map and member functions

BEGIN_MESSAGE_MAP (CMainWindow, CFrameWnd)
    ON_WM_CREATE ()
    ON_WM_ERASEBKGND ()
    ON_WM_PAINT ()
    ON_WM_TIMER ()
    ON_WM_QUERYNEWPALETTE ()
    ON_WM_PALETTECHANGED ()
    ON_WM_DESTROY ()
END_MESSAGE_MAP ()

CMainWindow::CMainWindow ()
{
    Create (NULL, _T ("Palette Animation Demo"));
}

int CMainWindow::OnCreate (LPCREATESTRUCT lpcs)
{
    static BYTE bColorVals[8][3] = {
        128, 128, 128,  // Dark Gray
        0,     0, 255,  // Blue
        0,   255,   0,  // Green
        0,   255, 255,  // Cyan
        255,   0,   0,  // Red
        255,   0, 255,  // Magenta
        255, 255,   0,  // Yellow
        192, 192, 192   // Light gray
    };

    if (CFrameWnd::OnCreate (lpcs) == -1)
        return -1;

	//
	// Create a palette to support palette animation.
	//
    struct {
        LOGPALETTE lp;
        PALETTEENTRY ape[7];
    } pal;

    LOGPALETTE* pLP = (LOGPALETTE*) &pal;
    pLP->palVersion = 0x300;
    pLP->palNumEntries = 8;

    for (int i=0; i<8; i++) {
        pLP->palPalEntry[i].peRed = bColorVals[i][0];
        pLP->palPalEntry[i].peGreen = bColorVals[i][1];
        pLP->palPalEntry[i].peBlue = bColorVals[i][2];
        pLP->palPalEntry[i].peFlags = PC_RESERVED;
    }

    m_palette.CreatePalette (pLP);

	//
	// Program a timer to fire every half-second.
	//
    SetTimer (1, 500, NULL);
    return 0;
}

void CMainWindow::OnTimer (UINT nTimerID)
{
    PALETTEENTRY pe[8];
    m_palette.GetPaletteEntries (7, 1, pe);
    m_palette.GetPaletteEntries (0, 7, &pe[1]);
    m_palette.AnimatePalette (0, 8, pe);
}

BOOL CMainWindow::OnEraseBkgnd (CDC* pDC)
{
    CRect rect;
    GetClientRect (&rect);

    CPalette* pOldPalette;
    pOldPalette = pDC->SelectPalette (&m_palette, FALSE);
    pDC->RealizePalette ();

    DoBkgndFill (pDC, &rect);

    pDC->SelectPalette (pOldPalette, FALSE);
    return TRUE;
}

void CMainWindow::OnPaint ()
{
    CRect rect;
    GetClientRect (&rect);
    CPaintDC dc (this);
    DoDrawText (&dc, &rect);
}

BOOL CMainWindow::OnQueryNewPalette ()
{
    CClientDC dc (this);
    dc.SelectPalette (&m_palette, FALSE);

    UINT nCount;
    if (nCount = dc.RealizePalette ())
        Invalidate ();

    return nCount;
}

void CMainWindow::OnPaletteChanged (CWnd* pFocusWnd)
{
    if (pFocusWnd != this) {
        CClientDC dc (this);
        dc.SelectPalette (&m_palette, FALSE);
        if (dc.RealizePalette ())
            Invalidate ();
    }
}

void CMainWindow::OnDestroy ()
{
    KillTimer (1);
}

void CMainWindow::DoBkgndFill (CDC* pDC, LPRECT pRect)
{
    CBrush* pBrush[8];
    for (int i=0; i<8; i++)
        pBrush[i] = new CBrush (PALETTEINDEX (i));

    int nWidth = pRect->right - pRect->left;
    int nHeight = (pRect->bottom - pRect->top) / 8;

    CRect rect;
    int y1, y2;

    for (i=0; i<8; i++) {
        y1 = i * nHeight;
        y2 = (i == 7) ? pRect->bottom - pRect->top : y1 + nHeight;
        rect.SetRect (0, y1, nWidth, y2);
        pDC->FillRect (&rect, pBrush[i]);
    }

    for (i=0; i<8; i++)
        delete pBrush[i];
}

void CMainWindow::DoDrawText (CDC* pDC, LPRECT pRect)
{
    CFont font;
    font.CreatePointFont (720, _T ("Comic Sans MS"));

    pDC->SetBkMode (TRANSPARENT);
    pDC->SetTextColor (RGB (255, 255, 255));

    CFont* pOldFont = pDC->SelectObject (&font);
    pDC->DrawText (_T ("Hello, MFC"), -1, pRect, DT_SINGLELINE | 
        DT_CENTER | DT_VCENTER);
    pDC->SelectObject (pOldFont);
}
