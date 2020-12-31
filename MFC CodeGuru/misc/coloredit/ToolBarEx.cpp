// ToolBarEx.cpp : implementation file
//
// Description:
//	CToolBarEx provides additional features to the standard toolbar
//	"CToolBar". The main addition is the flat mode (last seen in
//	Developer Studio 5.0).
//	There are no special requirements for having the flat mode in your
//	application (no special comctl32.dll or what ever)!
//	If you need custom draw abilities, then you have to use VC++ >= 4.2
//	However, the flat mode should work with older versions of VC++ too (let
//	me know of your experiences!)
//
// Usage:
//	The only task you have to perform, is to
//		#include "ToolBarEx.h"
//	in either StdAfx.h or MainFrm.h and to change the type of
//	CMainFrame::m_wndToolBar from CToolBar to CToolBarEx.
//	Don't forget to recompile :-)
//
// Acknowledgements:
//	o	The main idea of how to draw a separator and the gripper is stolen
//		from Roger Onslow's MSIE flat toolbar.
//		Thanks for saving my time, Roger ;-)
//	o	The embossed drawing of a disabled image came from
//		Victor M. Vogelpoel (victorv@telic.nl)
//	o	Some hints for buttons with text came from
//		David Bates (bates@econ.ubc.ca)
//		(I'm still thinking, text on toolbar-buttons is broken.
//		That has to be tooltip's work. However, texts on buttons
//		now work)
//
//
// (known) bugs and limitations:
//	o	the CDRF_NEWFONT notification is still untested ...
//	o	Assigning texts to buttons may cause the buttons to
//		resize horizontally without notified by CToolBar. This
//		leads to a wrong calculation inside CalcDynamicLayout()
//		and CalcFixedLayout(). One could override both these
//		functions in derived classes to avoid that problem,
//		but that would be a greater pain ...
//
//	if you find others (and have a solution for them ?!), please let me know:
//		Joerg.Koenig@rhein-neckar.de		(private site) or
//		J.Koenig@adg.de						(company site)
//
// Changes:
//	30.10.97
//	o	texts on buttons now work
//	o	gripper improved for a closer look like Office97
//	o	disabled images now look embossed
//	o	a separator is drawn only if it has no WRAP state set



#include "stdafx.h"
#include "ToolBarEx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// local helper class CCustomDrawInfo
//
// The helper class CCustomDrawInfo handles the messaging to the docking
// frame of the toolbar in flat mode only. If flat-mode is disabled, then
// MFC's own messanger will be used.
//
// A few words about custom draw on toolbars:
// o custom draw is possible for MFC >= 4.2 only (older versions don't know
//   anything about certain structures ...)
// o MFC does not set the "rc" member of NMCUSTOMDRAW to the rectangle of the
//	 button that will be drawn. However, we do, so watch out, wether the
//	 toolbar is flat or not (or ignore the "rc" member in both cases).
//	 If the current mode is not "flat", then MFC's art of message arrives ...
// o MFC does not send a message for separators, so we too don't do it.
// o It seems that MFC toolbars never send *ERASE notifications; instead they
//   send TBN_QUERYDELETE for instance.
// o The CDRF_NEWFONT notification result is ignored (in flat mode. Never
//   tried with original MFC, because it is broken on toolbars).
/////////////////////////////////////////////////////////////////////////////

class CCustomDrawInfo {

#if _MFC_VER >= 0x0420
	NMCUSTOMDRAW	m_CDRW;				// custom draw information holder
	LRESULT			m_PrePaint;			// result from prepaint notification
	LRESULT			m_ItemPrePaint;		// dito for specific item
	CToolBarEx *	m_pToolBar;			// the real sender of the notification
	CWnd *			m_pReceiver;		// the receiver of the notification

	LRESULT			NotifyParent();
#endif // _MFC_VER

	public:		// construction
		CCustomDrawInfo( CDC & dc, CToolBarEx * pToolBar );

	public:
		// NotifyItemPrePaint() returns TRUE,
		// if the user wants to do the default
		// (CDRF_DODEFAULT) or FALSE, if the
		// user wants to skip (CDRF_SKIPDEFAULT)
		// Note that CDRF_SKIPDEFAULT is not
		// allowed for CDDS_PREPAINT, CDDS_POSTPAINT !
		// and CDDS_ITEMPOSTPAINT
		void	NotifyPrePaint();
		BOOL	NotifyItemPrePaint(int item);
		void	NotifyItemPostPaint(int item);
		void	NotifyPostPaint();
};


#if _MFC_VER >= 0x420

	LRESULT CCustomDrawInfo :: NotifyParent() {
		LRESULT lRes = CDRF_DODEFAULT;

		if( m_pReceiver )
			lRes = m_pReceiver->SendMessage(WM_NOTIFY,
											WPARAM(m_CDRW.hdr.idFrom),
											LPARAM(&m_CDRW));
		return lRes;
	}


	CCustomDrawInfo :: CCustomDrawInfo( CDC & dc, CToolBarEx * pBar )
		: m_PrePaint(0)
		, m_ItemPrePaint(0)
	{
		VERIFY((m_pToolBar = pBar) != 0);
		VERIFY((m_CDRW.hdc = dc.GetSafeHdc()) != 0);

		HWND hwnd = pBar->GetSafeHwnd();
		VERIFY(::IsWindow(hwnd));

		// initialise the NMHDR member of the customdraw structure
		m_CDRW.hdr.hwndFrom = hwnd;
		m_CDRW.hdr.idFrom = UINT(::GetWindowLong(hwnd, GWL_ID));
		m_CDRW.hdr.code = NM_CUSTOMDRAW;

		// Do not use CControlBar::GetDockingFrame() to receive
		// the parent. CWnd::GetParent() is inacceptable too.
		// Both these functions don't work, if the toolbar is
		// floating in the air!
		m_pReceiver = pBar->GetParentFrame();
		if( m_pReceiver )
			VERIFY(::IsWindow(m_pReceiver->GetSafeHwnd()));
	}

	void CCustomDrawInfo :: NotifyPrePaint() {
		// fill the customdraw structure with values for CDDS_PREPAINT
		m_CDRW.dwDrawStage = CDDS_PREPAINT;
		// the rest of the structure stays undefined in this stage
		// of drawing.
		m_PrePaint = NotifyParent();
	}

	BOOL CCustomDrawInfo :: NotifyItemPrePaint( int nItem ) {
		BOOL bRet = TRUE;	// we assume to do the default
		if( m_PrePaint & CDRF_NOTIFYITEMDRAW ) {
			m_CDRW.dwDrawStage = CDDS_ITEMPREPAINT;
			m_pToolBar->GetItemRect(nItem, &m_CDRW.rc);
			m_CDRW.dwItemSpec = DWORD(m_pToolBar->GetItemID(nItem));
			UINT uStyle = m_pToolBar->GetButtonStyle(nItem);
			BOOL bEnable = m_pToolBar->GetToolBarCtrl()
							.IsButtonEnabled(m_CDRW.dwItemSpec);
			m_CDRW.uItemState = (bEnable ? 0 : CDIS_DISABLED) |
								(((uStyle & TBBS_PRESSED) || (uStyle & TBBS_CHECKED)) ?
									CDIS_CHECKED : 0);
			m_CDRW.lItemlParam = 0;
			m_ItemPrePaint = NotifyParent();
			if( m_ItemPrePaint & CDRF_SKIPDEFAULT )
				bRet = FALSE;
		}
		return bRet;
	}

	void CCustomDrawInfo :: NotifyItemPostPaint( int nItem ) {
		if( m_ItemPrePaint & CDRF_NOTIFYPOSTPAINT ) {
			m_CDRW.dwDrawStage = CDDS_ITEMPOSTPAINT;
			// the rest of the data has not been changed since ITEMPREPAINT
			// make sure it is so:
			ASSERT(m_pToolBar->GetItemID(nItem) == m_CDRW.dwItemSpec);
			NotifyParent();
		}
	}

	void CCustomDrawInfo :: NotifyPostPaint() {
		if( m_PrePaint & CDRF_NOTIFYPOSTPAINT ) {
			m_CDRW.dwDrawStage = CDDS_POSTPAINT;
			NotifyParent();
		}
	}
			
#else	// _MFC_VER < 4.2

	CCustomDrawInfo :: CCustomDrawInfo( CDC & dc, CWnd * pParent ) {
	}

	void CCustomDrawInfo :: NotifyPrePaint() {
	}

	void CCustomDrawInfo :: NotifyPostPaint() {
	}
	
	BOOL CCustomDrawInfo :: NotifyItemPrePaint( int ) {
		return TRUE;	// we always make the drawing by ourself
	}

	void CCustomDrawInfo :: NotifyItemPostPaint( int ) {
	}

#endif	// _MFC_VER



/////////////////////////////////////////////////////////////////////////////
// CToolBarEx

CToolBarEx::CToolBarEx()
	: m_bFlatLook(TRUE)
	, m_clrBtnFace(::GetSysColor(COLOR_BTNFACE))
	, m_clrBtnHilight(::GetSysColor(COLOR_BTNHILIGHT))
	, m_clrBtnShadow(::GetSysColor(COLOR_BTNSHADOW))
	, m_nLastBtn(-1)
	, m_uTimerEvent(0)
{
	CalculateOffset();

	// create the default font, used for buttons with text
	CFont Font;
	BOOL bOldSys = FALSE;
	if( ! Font.CreateStockObject( DEFAULT_GUI_FONT ) ) {
		// older versions of Windows* (NT 3.51 for instance)
		// fail with DEFAULT_GUI_FONT
		VERIFY( Font.CreateStockObject( SYSTEM_FONT ) );
		bOldSys = TRUE;
	}
	LOGFONT logfont ;
	Font.GetLogFont( &logfont ) ;
	if( bOldSys ) {
		logfont.lfWeight = 400;
		strcpy(logfont.lfFaceName,"MS Sans Serif");
	}
	logfont.lfHeight = 6 ;
	logfont.lfWidth = 0 ;	// let windows compute this.
	VERIFY( m_GuiFont.CreateFontIndirect( &logfont ) ) ;
}

CToolBarEx::~CToolBarEx()
{
}


IMPLEMENT_DYNAMIC(CToolBarEx, CToolBar)


BEGIN_MESSAGE_MAP(CToolBarEx, CToolBar)
	//{{AFX_MSG_MAP(CToolBarEx)
	ON_WM_PAINT()
	ON_WM_SYSCOLORCHANGE()
	ON_WM_NCCALCSIZE()
	ON_WM_MOUSEMOVE()
	ON_WM_NCPAINT()
	ON_WM_TIMER()
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
	ON_MESSAGE(TB_SETBUTTONSIZE, OnSetButtonSize)
	ON_MESSAGE(TB_SETBITMAPSIZE, OnSetBitmapSize)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CToolBarEx message handlers

LRESULT CToolBarEx :: OnSetButtonSize(WPARAM wParam, LPARAM lParam) {
	LRESULT lResult = CToolBar::OnSetButtonSize(wParam, lParam);
	if( lResult )
		CalculateOffset();
	return lResult;
}

LRESULT CToolBarEx :: OnSetBitmapSize(WPARAM wParam, LPARAM lParam) {
	LRESULT lResult = CToolBar::OnSetBitmapSize(wParam, lParam);
	if( lResult )
		CalculateOffset();
	return lResult;
}


void CToolBarEx::OnPaint() 
{
	HIMAGELIST hImg = GetImageList();

#ifdef _DEBUG
	if( hImg == 0 ) {
		TRACE0("CToolBarEx::OnPaint(): could not get image list\n");
	}
#endif

	if( m_bFlatLook && hImg ) {
		CRect rcUpdate;
		if( ! GetUpdateRect(rcUpdate) )
			return;

		if( m_pStringMap && !m_pStringMap->IsEmpty() )
			CalculateOffset();		// strings may have been added

		// attach image-list for even more MFC feeling :)
		CImageList imglist;
		imglist.Attach(hImg);

		POINT cursor;
		::GetCursorPos(&cursor);
		ScreenToClient(&cursor);

		CPaintDC dc(this); // device context for painting
		CFont * pOldFont = dc.SelectObject(&m_GuiFont);

		// Now it's time for the first custom-draw-notification...
		CCustomDrawInfo cdrw(dc, this);
		cdrw.NotifyPrePaint();

		register const int nBtn = GetToolBarCtrl().GetButtonCount();

		for( register int i = 0; i < nBtn; ++i ) {
			CRect rc;
			GetItemRect(i, rc);

			int nBitmap; UINT uID, uStyleState;
			GetButtonInfo(i, uID, uStyleState, nBitmap);
			WORD wStyle = LOWORD(uStyleState);
			WORD wState = HIWORD(uStyleState);

			if( wState & TBSTATE_HIDDEN )
				continue;

			if( wStyle == TBSTYLE_SEP ) {
				if( !(wState & TBSTATE_WRAP) )
					DrawSeparator(dc, rc);
			} else {
				if( ! CRect().IntersectRect(rcUpdate, rc) )
					continue;	// this button needs no repaint

				// maybe the button has text
				dc.SetTextColor(RGB(0,0,0));
				dc.SetBkColor(m_clrBtnFace);

				// There is a bug in CToolBar: If there are texts assigned
				// to buttons, then the button-widths may change transparently
				// (without notified by CToolBar), so we recalculate the
				// horizontal offset here:
				m_sizeOffset.cx = (rc.Width() - m_sizeImage.cx) / 2;

				if( ! cdrw.NotifyItemPrePaint(i) )
					continue;	// parent has already drawn the button

				BOOL bBtnDown = (wState & TBSTATE_CHECKED) || (wState & TBSTATE_PRESSED);
				BOOL bBtnEnabled = GetToolBarCtrl().IsButtonEnabled(int(uID));

				dc.FillSolidRect(rc,m_clrBtnFace);

				// it seems, that CDC::Draw3dRect() changes the background color
				COLORREF clrBk = dc.GetBkColor();

				if( bBtnDown )
					// draw a pressed button
					dc.Draw3dRect(rc, m_clrBtnShadow, m_clrBtnHilight);
				else if( rc.PtInRect(cursor) && ! bBtnDown && bBtnEnabled )
					// draw a normal button
					dc.Draw3dRect(rc, m_clrBtnHilight, m_clrBtnShadow);
				else if( ! bBtnDown && bBtnEnabled )
					// Draw an invisible rect around the button.
					// This prevents us from erasing the background
					// if the button was formed before
					// (that would cause the button to flicker ...)
					dc.Draw3dRect(rc, m_clrBtnFace, m_clrBtnFace);
				
				dc.SetBkColor(clrBk);

				// the point where to start with the image
				CPoint pt(rc.left + m_sizeOffset.cx + bBtnDown,
						  rc.top + m_sizeOffset.cy + bBtnDown);
				
				imglist.Draw(&dc, nBitmap, pt, ILD_NORMAL);
				CString strText = GetButtonText(i);
				if( strText.GetLength() ) {
					CRect rectText(
						rc.left+3+bBtnDown,
						rc.top+m_sizeOffset.cy+m_sizeImage.cy+1+bBtnDown,
						rc.right-3+bBtnDown,
						rc.bottom-3+bBtnDown
					);
					dc.DrawText(strText, rectText, DT_CENTER|DT_VCENTER|DT_NOCLIP);
				}
				
				if( ! bBtnEnabled )
					// gray out that button
					DrawDisabledButton(dc, rc);

				cdrw.NotifyItemPostPaint(i);
			}
		}

		dc.SelectObject(pOldFont);

		if( ! m_bDeleteImgList )
			imglist.Detach();

		// last but not least: inform the parent for end of painting
		cdrw.NotifyPostPaint();
	} else
		// classic mode (or couldn't receive imagelist)
		CToolBar::OnPaint();
}


void CToolBarEx :: DrawDisabledButton( CDC & dc, const CRect & rc ) const {
	// create a monochrome memory DC
	CDC ddc;
	ddc.CreateCompatibleDC(0);
	CBitmap bmp;
	bmp.CreateCompatibleBitmap(&ddc, rc.Width(), rc.Height());
	CBitmap * pOldBmp = ddc.SelectObject(&bmp);
	
	// build a mask
	ddc.PatBlt(0, 0, rc.Width(), rc.Height(), WHITENESS);
	dc.SetBkColor(m_clrBtnFace);
	ddc.BitBlt(0, 0, rc.Width(), rc.Height(), &dc, rc.left, rc.top, SRCCOPY);
	dc.SetBkColor(m_clrBtnHilight);
	ddc.BitBlt(0, 0, rc.Width(), rc.Height(), &dc, rc.left, rc.top, SRCPAINT);

	// Copy the image from the toolbar into the memory DC
	// and draw it (grayed) back into the toolbar.
	dc.FillSolidRect(rc.left, rc.top, rc.Width(), rc.Height(), m_clrBtnFace);
	dc.SetBkColor(RGB(0, 0, 0));
	dc.SetTextColor(RGB(255, 255, 255));
	CBrush brShadow, brHilight;
	brHilight.CreateSolidBrush(m_clrBtnHilight);
	brShadow.CreateSolidBrush(m_clrBtnShadow);
	CBrush * pOldBrush = dc.SelectObject(&brHilight);
	dc.BitBlt(rc.left+1, rc.top+1, rc.Width(), rc.Height(), &ddc, 0, 0, 0x00E20746L);
	dc.SelectObject(&brShadow);
	dc.BitBlt(rc.left, rc.top, rc.Width(), rc.Height(), &ddc, 0, 0, 0x00E20746L);
	
	// reset DCs
	dc.SelectObject(pOldBrush);
	ddc.SelectObject(pOldBmp);
	ddc.DeleteDC();

	bmp.DeleteObject();
}


void CToolBarEx :: DrawSeparator( CDC & dc, CRect & rc ) const {
    BOOL bHorz = ((m_dwStyle & CBRS_ORIENT_HORZ) != 0) ? TRUE : FALSE;
	// make sure, this separator is not a placeholder for
	// another control.
	if( rc.Width() <= 8 ) {
		if( bHorz ) {
			// draw the separator bar in the middle
			int x = (rc.left + rc.right) / 2;
			rc.left = x-1; rc.right = x+1;
			dc.Draw3dRect(
				rc,
				m_clrBtnShadow,
				m_clrBtnHilight
			);
		} else {
			// draw the separator bar in the middle
			rc.left = rc.left - m_sizeButton.cx;
			rc.right = rc.left + m_sizeButton.cx;
			rc.top = rc.bottom+1;
			rc.bottom = rc.top+3;
			int y = (rc.top+rc.bottom)/2;
			rc.top = y-1; rc.bottom = y+1;
			dc.Draw3dRect(
				rc,
				m_clrBtnShadow,
				m_clrBtnHilight
			);
		}
	}
}


void CToolBarEx :: DrawGripper( CDC & dc ) const { 
    if( m_dwStyle & CBRS_FLOATING )
		return;		// no gripper if floating

	CRect gripper;
	GetWindowRect(gripper);
	ScreenToClient(gripper);
	gripper.OffsetRect(-gripper.left, -gripper.top);

	if( m_dwStyle & CBRS_ORIENT_HORZ ) {
		// gripper at left
		gripper.DeflateRect(4, 4);
		gripper.right = gripper.left+3;
        dc.Draw3dRect(
			gripper,
			m_clrBtnHilight,
            m_clrBtnShadow
		);
		gripper.OffsetRect(3, 0);
        dc.Draw3dRect(
			gripper,
			m_clrBtnHilight,
            m_clrBtnShadow
		);
	} else {
		// gripper at top
		gripper.DeflateRect(4, 4);
		gripper.bottom = gripper.top+3;
		dc.Draw3dRect(
			gripper,
			m_clrBtnHilight,
            m_clrBtnShadow
		);
		gripper.OffsetRect(0, 3);
        dc.Draw3dRect(
			gripper,
			m_clrBtnHilight,
            m_clrBtnShadow
		);
	}
}

void CToolBarEx :: OnUpdateCmdUI( CFrameWnd* pTarget, BOOL bDisableIfNoHndler ) {
	if( m_bFlatLook ) {
		// save current styles
		register const int nBtn = GetToolBarCtrl().GetButtonCount();
		register int nIdx;
		for( nIdx = 0; nIdx < nBtn; ++nIdx )
			m_Styles.SetAtGrow(nIdx, GetButtonStyle(nIdx));

		// do base class processing
		CToolBar::OnUpdateCmdUI(pTarget,bDisableIfNoHndler);

		//check wether styles have been changed
		for( nIdx = 0; nIdx < nBtn; ++nIdx ) {
			if( m_Styles[nIdx] != GetButtonStyle(nIdx) ) {
				// invalidate that button
				CRect rc;
				GetItemRect(nIdx, rc);
				InvalidateRect(rc);
			}
		}
	} else
		// simply delegate
		CToolBar::OnUpdateCmdUI(pTarget,bDisableIfNoHndler);
}

void CToolBarEx::OnSysColorChange() 
{
	CToolBar::OnSysColorChange();

	m_clrBtnFace    = ::GetSysColor(COLOR_BTNFACE);
	m_clrBtnHilight = ::GetSysColor(COLOR_BTNHILIGHT);
	m_clrBtnShadow  = ::GetSysColor(COLOR_BTNSHADOW);
}


void CToolBarEx::OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS FAR* lpncsp) 
{
	CToolBar::OnNcCalcSize(bCalcValidRects, lpncsp);
	// adjust non-client area for gripper at left or top
	if( m_dwStyle & CBRS_ORIENT_HORZ ) {
		lpncsp->rgrc[0].left += 4;
		lpncsp->rgrc[0].right += 4;
	} else {
		lpncsp->rgrc[0].top += 6;
		lpncsp->rgrc[0].bottom += 6;
	}
}


void CToolBarEx::OnMouseMove(UINT nFlags, CPoint point) 
{
	if( m_bFlatLook ) {
		register const int nBtn = GetToolBarCtrl().GetButtonCount();
		const int nLastBtn = m_nLastBtn;
		m_nLastBtn = -1;

		for( register int i = 0 ; i < nBtn ; ++i ) {
			CRect rc;
			GetItemRect(i, rc);

			const BOOL bBtnEnabled = GetToolBarCtrl().IsButtonEnabled(int(GetItemID(i)));
			const BOOL bSep = GetButtonStyle(i) & TBBS_SEPARATOR;

			if( bSep || ! bBtnEnabled )
				continue;

			const BOOL bHasCursor = rc.PtInRect(point);

			if( bHasCursor && bBtnEnabled ) {
				if( nLastBtn != i ) {
					// force a repaint of the button with the cursor on it
					InvalidateRect(rc, FALSE);
				}
				m_nLastBtn = i;
			} else if( !bHasCursor && i == nLastBtn ) {
				// force a repaint of the last formed button
				InvalidateRect(rc, FALSE);
			}
		}
		// One problem occures with WM_MOUSEMOVE: we cannot detect
		// that the mouse leaves the window. If the mouse moves quick
		// enough, then the last formed button stays visible. To
		// resolve this problem, we set a timer and check, wether
		// the mouse is outside the window ...
		KillTimer(m_uTimerEvent);
		m_uTimerEvent = SetTimer(1, 250, 0);
	}
	CToolBar::OnMouseMove(nFlags, point);
}


void CToolBarEx::OnNcPaint() 
{
	if( m_bFlatLook ) {
		CToolBar::EraseNonClient();
		CWindowDC dc(this);
		DrawGripper(dc);
	} else
		CToolBar::OnNcPaint();
}

void CToolBarEx::OnTimer(UINT nIDEvent) 
{
	if( nIDEvent == m_uTimerEvent && m_nLastBtn >= 0 ) {
		POINT pt;
		::GetCursorPos(&pt);
		CRect rc;
		GetWindowRect(rc);
		if( ! rc.PtInRect(pt) ) {
			GetItemRect(m_nLastBtn, rc);
			InvalidateRect(rc, FALSE);
			m_nLastBtn = -1;
			KillTimer(nIDEvent);
		}
	} else
		CToolBar::OnTimer(nIDEvent);
}

int CToolBarEx::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CToolBar::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// Save the parent at creation time. It may change, if
	// the toolbar is floating; but we want to know of the
	// "real" parent (for notification messages)!
	m_hwndParent = lpCreateStruct->hwndParent;
	
	return 0;
}

#define PADWIDTH(x)	(((x)*8+31)&~31)/8


HIMAGELIST CToolBarEx :: GetImageList() {
	m_bDeleteImgList = FALSE;

	HIMAGELIST hImg = HIMAGELIST(SendMessage(TB_GETIMAGELIST));

#ifdef _DEBUG
	if( hImg == 0 ) {
		TRACE0("CToolBarEx::OnPaint(): could not get image list\n");
	}
#endif

	if( ! hImg ) {
		// comctl32.dll version prior to 4.70 doesn't know
		// anything of the TB_GETIMAGELIST message
		if( m_hbmImageWell != 0 ) {
			// Yup - we have a valid image.
			// But beware: Do not use this bitmap directly.
			// We make the copy by ourself. CopyImage() (for
			// instace) produces inacceptable copies under
			// some circumstances ...
			CImageList imglist;
			CBitmap bmp;
			
			// retrieve the size of the bitmap
			BITMAP bmHdr;
			::GetObject(m_hbmImageWell, sizeof(BITMAP), &bmHdr);
			
			DWORD dwWidth, dwHeight = bmHdr.bmHeight;
			
			if (bmHdr.bmBitsPixel > 8)
				dwWidth = PADWIDTH(bmHdr.bmWidth * 3);
			else
				dwWidth = PADWIDTH(bmHdr.bmWidth);
			
			// copy the bitmap
			CClientDC cdc(this);
			CDC dc1, dc2;
			dc1.CreateCompatibleDC(&cdc);
			dc2.CreateCompatibleDC(&cdc);
			bmp.CreateCompatibleBitmap(&cdc, dwWidth, dwHeight);
			CBitmap * pOBmp = dc1.SelectObject(&bmp);
			HGDIOBJ hOObj = ::SelectObject(dc2.GetSafeHdc(), m_hbmImageWell);
			dc1.BitBlt(0,0,dwWidth,dwHeight,&dc2,0,0,SRCCOPY);
			::SelectObject(dc2.GetSafeHdc(), hOObj);
			dc1.SelectObject(pOBmp);
			dc1.DeleteDC();
			dc2.DeleteDC();

			imglist.Create(m_sizeImage.cx, m_sizeImage.cy,TRUE,dwWidth/m_sizeImage.cx,1);
			imglist.SetBkColor(m_clrBtnFace);
			imglist.Add(&bmp,m_clrBtnFace);
			hImg = imglist.Detach();
			bmp.DeleteObject();
			m_bDeleteImgList = TRUE;
		}
	}

	return hImg;
}
