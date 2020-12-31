// ChildView.cpp : implementation of the CChildView class
//

#include "stdafx.h"
#include "BitmapDemo.h"
#include "MaskedBitmap.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChildView

CChildView::CChildView()
{
    m_bDrawOpaque = TRUE;
}

CChildView::~CChildView()
{
}

BEGIN_MESSAGE_MAP(CChildView,CWnd )
	//{{AFX_MSG_MAP(CChildView)
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_WM_ERASEBKGND()
	ON_COMMAND(ID_OPTIONS_DRAW_OPAQUE, OnOptionsDrawOpaque)
	ON_COMMAND(ID_OPTIONS_DRAW_TRANSPARENT, OnOptionsDrawTransparent)
	ON_UPDATE_COMMAND_UI(ID_OPTIONS_DRAW_OPAQUE, OnUpdateOptionsDrawOpaque)
	ON_UPDATE_COMMAND_UI(ID_OPTIONS_DRAW_TRANSPARENT, OnUpdateOptionsDrawTransparent)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChildView message handlers

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW), HBRUSH(COLOR_WINDOW+1), NULL);

	return TRUE;
}

void CChildView::OnPaint() 
{
    CRect rect;
    GetClientRect (&rect);
    CPaintDC dc (this);

    BITMAP bm;
    m_bitmap.GetBitmap (&bm);
    int cx = (rect.Width () / (bm.bmWidth + 8)) + 1;
    int cy = (rect.Height () / (bm.bmHeight + 8)) + 1;

    int i, j, x, y;
    for (i=0; i<cx; i++) {
        for (j=0; j<cy; j++) {
            x = 8 + (i * (bm.bmWidth + 8));
            y = 8 + (j * (bm.bmHeight + 8));
            if (m_bDrawOpaque)
                m_bitmap.Draw (&dc, x, y);
            else
                m_bitmap.DrawTransparent (&dc, x, y, RGB (255, 0, 0));
        }
    }
}

int CChildView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd ::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	//
	// Load the bitmap.
	//
    m_bitmap.LoadBitmap (IDB_BITMAP);

	//
	// Create a palette for a gradient fill if this is a palettized device.
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

BOOL CChildView::OnEraseBkgnd(CDC* pDC) 
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

void CChildView::DoGradientFill(CDC *pDC, LPRECT pRect)
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

void CChildView::OnOptionsDrawOpaque() 
{
    m_bDrawOpaque = TRUE;
    Invalidate ();
}

void CChildView::OnOptionsDrawTransparent() 
{
    m_bDrawOpaque = FALSE;
    Invalidate ();
}

void CChildView::OnUpdateOptionsDrawOpaque(CCmdUI* pCmdUI) 
{
    pCmdUI->SetCheck (m_bDrawOpaque ? 1 : 0);
}

void CChildView::OnUpdateOptionsDrawTransparent(CCmdUI* pCmdUI) 
{
    pCmdUI->SetCheck (m_bDrawOpaque ? 0 : 1);
}
