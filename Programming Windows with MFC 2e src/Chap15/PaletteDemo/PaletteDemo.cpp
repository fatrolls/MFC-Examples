#include <afxwin.h>
#include "PaletteDemo.h"

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
    ON_WM_CREATE ()
    ON_WM_ERASEBKGND ()
    ON_WM_PAINT ()
    ON_WM_QUERYNEWPALETTE ()
    ON_WM_PALETTECHANGED ()
END_MESSAGE_MAP ()

CMainWindow::CMainWindow ()
{
    Create (NULL, _T ("Palette Demo"));
}

int CMainWindow::OnCreate (LPCREATESTRUCT lpcs)
{
    if (CFrameWnd::OnCreate (lpcs) == -1)
        return -1;

	//
	// Create a logical palette if running on a palettized adapter.
	//
    CClientDC dc (this);
    if (dc.GetDeviceCaps (RASTERCAPS) & RC_PALETTE) {
        struct {
            LOGPALETTE lp;
            PALETTEENTRY ape[63];
        } pal;

        LOGPALETTE* pLP = (LOGPALETTE*) &pal;
        pLP->palVersion = 0x300;
        pLP->palNumEntries = 64;

        for (int i=0; i<64; i++) {
            pLP->palPalEntry[i].peRed = 0;
            pLP->palPalEntry[i].peGreen = 0;
            pLP->palPalEntry[i].peBlue = 255 - (i * 4);
            pLP->palPalEntry[i].peFlags = 0;
        }
        m_palette.CreatePalette (pLP);
    }
    return 0;
}

BOOL CMainWindow::OnEraseBkgnd (CDC* pDC)
{
    CRect rect;
    GetClientRect (&rect);

    CPalette* pOldPalette;
    if ((HPALETTE) m_palette != NULL) {
        pOldPalette = pDC->SelectPalette (&m_palette, FALSE);
        pDC->RealizePalette ();
    }

    DoGradientFill (pDC, &rect);

    if ((HPALETTE) m_palette != NULL)
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
    if ((HPALETTE) m_palette == NULL)   // Shouldn't happen, but
        return 0;                       // let's be sure.

    CClientDC dc (this);
    CPalette* pOldPalette = dc.SelectPalette (&m_palette, FALSE);

    UINT nCount;
    if (nCount = dc.RealizePalette ())
        Invalidate ();

    dc.SelectPalette (pOldPalette, FALSE);
    return nCount;
}

void CMainWindow::OnPaletteChanged (CWnd* pFocusWnd)
{
    if ((HPALETTE) m_palette == NULL)   // Shouldn't happen, but
        return;                         // let's be sure.

    if (pFocusWnd != this) {
        CClientDC dc (this);
        CPalette* pOldPalette = dc.SelectPalette (&m_palette, FALSE);
        if (dc.RealizePalette ())
            Invalidate ();
        dc.SelectPalette (pOldPalette, FALSE);
    }
}

void CMainWindow::DoGradientFill (CDC* pDC, LPRECT pRect)
{
    CBrush* pBrush[64];
    for (int i=0; i<64; i++)
        pBrush[i] = new CBrush (PALETTERGB (0, 0, 255 - (i * 4)));

    int nWidth = pRect->right - pRect->left;
    int nHeight = pRect->bottom - pRect->top;
    CRect rect;

    for (i=0; i<nHeight; i++) {
        rect.SetRect (0, i, nWidth, i + 1);
        pDC->FillRect (&rect, pBrush[(i * 63) / nHeight]);
    }

    for (i=0; i<64; i++)
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
