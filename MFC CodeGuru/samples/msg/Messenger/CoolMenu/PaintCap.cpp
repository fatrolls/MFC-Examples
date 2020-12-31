////////////////////////////////////////////////////////////////
// 1997 Microsoft Systems Journal. 
// If this program works, it was written by Paul DiLascia.
// If not, I don't know who wrote it.
//
#include "StdAfx.h"
#include "PaintCap.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

////////////////
// Class used to get the caption rectangle of a window in window coords.
// This is the area of the title bar inside the window frame, including
// the icon and min/max/close buttons.
// 
class CCaptionRect : public CRect
{
public:
	CCaptionRect(const CWnd& wnd); // use reference to deny NULL ptr
};

IMPLEMENT_DYNAMIC(CCaptionPainter, CSubclassWnd);

CCaptionPainter::CCaptionPainter()
{
	Invalidate();
}

CCaptionPainter::~CCaptionPainter()
{
}

//////////////////
// Install caption handler. nPaintMsg is message I will send too frame
// when its caption needs painting.
//
BOOL CCaptionPainter::Install(CFrameWnd* pFrameWnd, UINT nPaintMsg)
{
	ASSERT_KINDOF(CFrameWnd, pFrameWnd);
	m_nPaintMsg = nPaintMsg;
	return HookWindow(pFrameWnd);
}

//////////////////
// Message handler handles caption-related messages
//
LRESULT CCaptionPainter::WindowProc(UINT msg, WPARAM wp, LPARAM lp)
{
	switch (msg)
	{
	case WM_NCPAINT:
		OnNcPaint(HRGN(wp));
		return 0;
	case WM_NCACTIVATE:
		return OnNcActivate(wp);
	case WM_SETTEXT:
		OnSetText((LPCTSTR)lp);
		return 0;
	case WM_SYSCOLORCHANGE:
	case WM_SETTINGCHANGE:
		Invalidate();
		if(m_nPaintMsg)
			m_pWndHooked->SendMessage(m_nPaintMsg, 0, 0L);
		else
			PaintCaption(false, NULL);
		return 0;
	}
	// I don't handle it: pass along
	return CSubclassWnd::WindowProc(msg, wp, lp);
}

/////////////////
// Handle WM_NCPAINT for main window
//
void CCaptionPainter::OnNcPaint(HRGN hRgn)
{
	ASSERT_VALID(m_pWndHooked);
	CWnd& wnd = *m_pWndHooked;

	CCaptionRect rc(wnd);			// caption rectangle in window coords
	CRect rcWin;					// window rect
	wnd.GetWindowRect(&rcWin);		// .. get window rect
	rc += rcWin.TopLeft();			// convert caption rect to screen coords

	// Don't bother painting if the caption doesn't lie within the region.
	//
	if ((WORD)hRgn > 1 && !::RectInRegion(hRgn, &rc)) {
		Default();					// just do default thing
		return;						// and quit
	}

	// Exclude caption from update region
	//
	HRGN hRgnCaption = ::CreateRectRgnIndirect(&rc);
	HRGN hRgnNew     = ::CreateRectRgnIndirect(&rc);
	if ((WORD)hRgn > 1) {
		// wParam is a valid region: subtract caption from it
		::CombineRgn(hRgnNew, hRgn, hRgnCaption, RGN_DIFF);
	} else {
		// wParam is not a valid region: create one that's the whole
		// window minus the caption bar
		HRGN hRgnAll = ::CreateRectRgnIndirect(&rcWin);
		CombineRgn(hRgnNew, hRgnAll, hRgnCaption, RGN_DIFF);
		DeleteObject(hRgnAll);
	}

	// Call Windows to do WM_NCPAINT with altered update region
	//
	MSG& msg = AfxGetThreadState()->m_lastSentMsg;
	WPARAM savewp = msg.wParam;			// save original wParam
	msg.wParam = (WPARAM)hRgnNew;		// set new region for DefWindowProc
	Default();
	DeleteObject(hRgnCaption);			// clean up
	DeleteObject(hRgnNew);				// ...
	msg.wParam = savewp;				// restore original wParam

	PaintCaption();						// Now paint my special caption
}

//////////////////
// Handle WM_NCACTIVATE for main window
//
BOOL CCaptionPainter::OnNcActivate(BOOL bActive)
{
	ASSERT_VALID(m_pWndHooked);
	CFrameWnd& frame = *((CFrameWnd*)m_pWndHooked);
	ASSERT_KINDOF(CFrameWnd, &frame);

	// Mimic MFC kludge to stay active if WF_STAYACTIVE bit is on
	if (frame.m_nFlags & WF_STAYACTIVE)
		bActive = TRUE;
	if (!frame.IsWindowEnabled())			// but not if disabled
		bActive = FALSE;
	if (bActive == m_bActive)
		return TRUE;					// nothing to do

	// In case this is a MDI app, manually activate/paint active MDI child
	// window, because Windows won't do it if parent frame is invisible.
	// Must do this BEFORE calling Default, or it will not work.
	//
	CFrameWnd* pActiveFrame = frame.GetActiveFrame();
	if (pActiveFrame!=&frame)
	{
		pActiveFrame->SendMessage(WM_NCACTIVATE,bActive);
		pActiveFrame->SendMessage(WM_NCPAINT);
	}

	// Turn WS_VISIBLE off before calling DefWindowProc,
	// so DefWindowProc won't paint and thereby cause flicker.
	//
	DWORD dwStyle = frame.GetStyle();
	if (dwStyle & WS_VISIBLE)
		::SetWindowLong(frame, GWL_STYLE, (dwStyle & ~ WS_VISIBLE));

	MSG& msg = AfxGetThreadState()->m_lastSentMsg;
	msg.wParam = bActive;
	Default();
	if (dwStyle & WS_VISIBLE)
		::SetWindowLong(frame, GWL_STYLE, dwStyle);

	// At this point, nothing has happened (since WS_VISIBLE was off).
	// Now it's time to paint.
	//
	m_bActive = bActive;					// update state
	frame.SendMessage(WM_NCPAINT);	// paint non-client area (frame too)
	return TRUE;							// done OK
}

//////////////////
// Handle WM_SETTEXT for main window
//
void CCaptionPainter::OnSetText(LPCTSTR lpText)
{
	lpText;

	ASSERT_VALID(m_pWndHooked);
	CWnd& wnd = *m_pWndHooked;

	// Turn WS_VISIBLE style off before calling Windows to
	// set the text, then turn it back on again after.
	//
	DWORD dwStyle = wnd.GetStyle();
	if (dwStyle & WS_VISIBLE)
		SetWindowLong(wnd.m_hWnd, GWL_STYLE, dwStyle & ~ WS_VISIBLE);
	Default();
	if (dwStyle & WS_VISIBLE)
		SetWindowLong(wnd.m_hWnd, GWL_STYLE, dwStyle);

	wnd.SendMessage(WM_NCPAINT);		// paint non-client (frame)
	Invalidate();							// force new bitmap
	PaintCaption();
}

//////////////////
// Paint custom caption. Flag tells whether active or not. Just blast the
// bitmap to the title bar, but not if minimized (iconic).
//
void CCaptionPainter::PaintCaption()
{
	ASSERT(m_pWndHooked);
	CWnd& wnd = *m_pWndHooked;

	//(Vytukas) Do not paint if main frame and iconic
	if (!wnd.GetParent() && wnd.IsIconic())
		return;

	// Get caption DC and rectangle
	CWindowDC dcWin(&wnd);						// window DC
	CDC dc;										// memory DC
	dc.CreateCompatibleDC(&dcWin);				// ...create it
	CCaptionRect rc(wnd);						// get caption rectangle
	if (rc.Size() != m_szCaption)				// if size changed:
	{											
		m_bmCaption[0].DeleteObject();			// invalidate bitmaps
		m_bmCaption[1].DeleteObject();			// ...
		m_szCaption = rc.Size();				// update new size
	}

	// Get active/inactive bitmap & determine if needs to be regenerated
	CBitmap& bm = m_bmCaption[m_bActive!=0];						// get bitmap
	BOOL bPaintIt = FALSE;											// paint anew?
	if (!(HBITMAP)bm) {												// no bitmap:
		bm.CreateCompatibleBitmap(&dcWin, rc.Width(), rc.Height()); // create one
		bPaintIt = TRUE;											// and paint it
	}
	CBitmap* pOldBitmap = dc.SelectObject(&bm);	// select bitmap into memory DC

	// If bitmap needs painting, call client to do it.
	if (bPaintIt) {
		PAINTCAP pc;
		pc.m_pDC = &dc;
		pc.m_szCaption = rc.Size();
		if(m_nPaintMsg)
			wnd.SendMessage(m_nPaintMsg, m_bActive, (LPARAM)&pc);
		else
			PaintCaption(m_bActive, &pc);
	}

	// blast bits to screen
	dcWin.BitBlt(rc.left,rc.top,rc.Width(),rc.Height(),&dc,0,0,SRCCOPY);
	dc.SelectObject(pOldBitmap); // restore DC
}

////////////////
// Draw caption icon. Returns width of icon.
//
int CCaptionPainter::DrawIcon(const PAINTCAP& pc)
{
	ASSERT(m_pWndHooked);
	CWnd& wnd = *m_pWndHooked;

	// Within the basic button rectangle, Windows 95 uses a 1 or 2 pixel border
	// Icon has 2 pixel border on left, 1 pixel on top/bottom, 0 right
	//
	int cxIcon = GetSystemMetrics(SM_CXSIZE);
	CRect rc(0, 0, cxIcon, GetSystemMetrics(SM_CYSIZE));
	rc.DeflateRect(0,1);
	rc.left += 2;
	DrawIconEx(pc.m_pDC->m_hDC, rc.left, rc.top,
		(HICON)GetClassLong(wnd.m_hWnd, GCL_HICONSM),
		rc.Width(), rc.Height(), 0, NULL, DI_NORMAL);
	return cxIcon;
}

////////////////
// Draw min, max/restore, close buttons.
// Returns total width of buttons drawn.
//
int CCaptionPainter::DrawButtons(const PAINTCAP& pc)
{
	ASSERT(m_pWndHooked);
	CWnd& wnd = *m_pWndHooked;
	DWORD dwStyle = wnd.GetStyle();
	if (!(dwStyle & WS_CAPTION))
		return 0;

	ASSERT(pc.m_pDC);
	CDC& dc = *pc.m_pDC;

	int cxIcon = GetSystemMetrics(SM_CXSIZE);
	int cyIcon = GetSystemMetrics(SM_CYSIZE);

	// Draw caption buttons. These are all drawn inside a rectangle
	// of dimensions SM_CXSIZE by SM_CYSIZE
	CRect rc(0, 0, cxIcon, cyIcon);
	rc += CPoint(pc.m_szCaption.cx-cxIcon, 0);	// move right

	// Close box has a 2 pixel border on all sides but left, which is zero
	rc.DeflateRect(0,2);
	rc.right -= 2;
	dc.DrawFrameControl(&rc, DFC_CAPTION, DFCS_CAPTIONCLOSE);

	// Max/restore button is like close box; just shift rectangle left
	// Also does help button, if any.
	BOOL bMaxBox = dwStyle & WS_MAXIMIZEBOX;
	if (bMaxBox || (wnd.GetExStyle() & WS_EX_CONTEXTHELP))
	{
		rc -= CPoint(cxIcon, 0);
		dc.DrawFrameControl(&rc, DFC_CAPTION,
			bMaxBox ? (wnd.IsZoomed() ? DFCS_CAPTIONRESTORE : DFCS_CAPTIONMAX) :
				DFCS_CAPTIONHELP);
	}

	// Minimize button has 2 pixel border on all sides but right.
	if (dwStyle & WS_MINIMIZEBOX)
	{
		rc -= CPoint(cxIcon-2,0);
		dc.DrawFrameControl(&rc, DFC_CAPTION, DFCS_CAPTIONMIN);
	}
	return pc.m_szCaption.cx - rc.left - 2;
}

//////////////////
// CCaptionRect Constructor computes caption rectangle in window coords.
//
CCaptionRect::CCaptionRect(const CWnd& wnd)
{
	// Get size of frame around window
	DWORD dwStyle = wnd.GetStyle();
	CSize szFrame = (dwStyle & WS_THICKFRAME) ?
		CSize(GetSystemMetrics(SM_CXSIZEFRAME),
			   GetSystemMetrics(SM_CYSIZEFRAME)) :
		CSize(GetSystemMetrics(SM_CXFIXEDFRAME),
				GetSystemMetrics(SM_CYFIXEDFRAME));

	int cxIcon = GetSystemMetrics(SM_CXSIZE); // width of caption icon/button

	// Compute rectangle
	wnd.GetWindowRect(this);		// window rect in screen coords
	*this -= CPoint(left, top);	// shift origin to (0,0)
	left  += szFrame.cx;				// frame
	right -= szFrame.cx;				// frame
	top   += szFrame.cy;				// top = end of frame
	bottom = top + GetSystemMetrics(SM_CYCAPTION)  // height of caption
		- GetSystemMetrics(SM_CYBORDER);				  // minus gray shadow border
}
