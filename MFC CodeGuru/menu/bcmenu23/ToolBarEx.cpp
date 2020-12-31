/////////////////////////////////////////////////////////////////////////////
// Copyright (C) 1997,'98 by Joerg Koenig
// All rights reserved
//
// Distribute freely, except: don't remove my name from the source or
// documentation (don't take credit for my work), mark your changes (don't
// get me blamed for your possible bugs), don't alter or remove this
// notice.
// No warrantee of any kind, express or implied, is included with this
// software; use at your own risk, responsibility for damages (if any) to
// anyone resulting from the use of this software rests entirely with the
// user.
//
// Send bug reports, bug fixes, enhancements, requests, flames, etc., and
// I'll try to keep a version up to date.  I can be reached as follows:
//    J.Koenig@adg.de                 (company site)
//    Joerg.Koenig@rhein-neckar.de    (private site)
/////////////////////////////////////////////////////////////////////////////

// last revised: $Date: 10.05.98 17:45 $ $Revision: 2 $

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
//	if you want to reduce flickering, then you have to include
//	the header of Keith Rule's CMemDC class in your <stdafx.h>.
//	CToolBarEx will use it automagically then.
//	If you want a "real cool" 3D look, then you have to exchange the call
//	to "EnableDocking()" in your CMainFrame::OnCreate() method to
//	"FrameEnableDocking()". This will ensure, that the toolbar has the
//	same outfit as in Office or DevStudio.
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
//	o	Thanks to Patrick Liechty (patrickl@code3.code3.com) for
//		the reports of his experiences with VC++ 4.0/4.1
//	o	Thanks to Jeng-Yuan Sheu (m8501511@chu.edu.tw) for the
//		enhanced checked button.
//	o	Thanks to Todd C. Wilson (todd@mediatec.com) for his
//		bug report and code-enhancement for users of VC++ 4.2b
//	o	Matthias Drigalla <matthias.drigalla@bluewin.ch> has pointed
//		me out, that the timer is not released in all circumstances.
//	o	thanks to Jonathan Chin <jonathan.chin@scitec.com.au> for his
//		experiences with UNICODE and for his enhancement to conform to
//		the standard interface (the flat toolbar should not perform any
//		hit test (and hence displaying the raised button state) if the
//		parent window (application) does not have the focus or is disabled.)
//	o	thanks to Wang Ruopeng (ripple@thinker.ep.tsinghua.edu.cn) for
//		the enhanced outfit of checked buttons
//
//	o	Many thanks to Victor Vogelpoel, Jonathan Chin and Patrick Liechty
//		for their help to test and correct some bugs in the enhanced version.
//		Their work made this class much cleaner. Thanks.
//
//	o	Wolfgang Loch (W.Loch@intershop.de) sent in a fix for undockable bars
//	o	Thanks to John Armstrong (jarmstrong@runge.com.au) for his fix to
//		the adjustment of gripperspace in "classic" mode
//	o	Thanks to Anatoly Ivasyuk (aivasyuk@clark.net) for a much cooler method
//		to draw checked buttons that does not have the cursor on it.
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
//	o	some features of the toolbars seen in Office97/DevStudio
//		are not implemented (for instance text-only buttons or
//		the way how image+text buttons are displayed.
//
//	if you find others (and have a solution for them ?!), please let me know:
//		Joerg.Koenig@rhein-neckar.de		(private site) or
//		J.Koenig@adg.de						(company site)
//
// Changes:
//	05/10/98
//	o	buttons that are checked *and* disabled are now looking ok.
//	o	don't draw a gripper if the bar is not dockable
//	o	do not adjust space for gripper in "classic" mode
//
//	01/17/98
//	o	If you have Keith Rule's "MemDC.h" included via
//		"stdafx.h", then CToolBarEx uses it to reduce
//		flickering.
//	o	release the timer in all circumstances
//	o	made the class compile even if UNICODE is #define'ed
//	o	do not make any hit test (and display a raised button state)
//		if the application does not have the focus.
//	o	Changed the outfit of a checked button that does not have
//		the cursor on it.
//	Major enhancements:
//	o	added easy way to add controls to a toolbar
//		(both: replacing a button with a control and
//		inserting/appending new controls)
//	o	Added many functions especially for the often
//		requested need for additional controls
//	o	ALT-Drag feature implemented. You just can move buttons
//		(and controls!) from one CToolBarEx-object to another
//		in the style of the Developer Studio. There is no additional
//		requirement for having this feature in your application.
//		Just follow the online-help for how to enable customizable
//		toolbars. CToolBarEx uses the same technique.
//
//	11/25/97
//	o	Some minor modifications to compile with VC++ 4.0/4.1 and 4.2b
//	o	checked buttons now look hilighted (as in Office97/DevStudio)
//
//	11/07/97
//	(2 minor bugs have been occured as a result of the last update :)
//	o	The WRAP state of a separator will be ignored now, if
//		the bar is docked vertically
//	o	Draw an image transparently. This is needed only if one
//		uses 256 color images.
//
//	10/30/97
//	o	texts on buttons now work
//	o	gripper improved for a closer look like Office97
//	o	disabled images now look embossed
//	o	a separator is drawn only if it has no WRAP state set



#include "stdafx.h"
#include "ToolBarEx.h"

#ifndef __AFXPRIV_H__
	#include <afxpriv.h>	// one of the most interesting headers ;-)
							// if you plan to change CToolBarEx, then you
							// should better insert it in your "stdafx.h"
							// to speed up compilation
#endif


#ifdef _MEMDC_H_
	//#undef _MEMDC_H_		// this is for testing purposes
#endif



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
//	 button that will be drawn. However, we do, so watch out, whether the
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

	CCustomDrawInfo :: CCustomDrawInfo( CDC & dc, CToolBarEx * pParent ) {
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
// CToolBarEx  --  class static data

HCURSOR			CToolBarEx :: m_hOrigCursor		= 0;
HCURSOR			CToolBarEx :: m_hDragCursor		= 0;
HCURSOR			CToolBarEx :: m_hNoDragCursor	= 0;
BOOL			CToolBarEx :: m_bDragging		= FALSE;
BOOL			CToolBarEx :: m_bDragCursor		= FALSE;
int				CToolBarEx :: m_nDragButton		= -1;
CToolBarEx *	CToolBarEx :: m_pDropBar		= 0;
CPoint			CToolBarEx :: m_ptDrop(0,0);

/////////////////////////////////////////////////////////////////////////////
// CToolBarEx

CToolBarEx::CToolBarEx()
	: m_bFlatLook(TRUE)
	, m_clrBtnFace(::GetSysColor(COLOR_BTNFACE))
	, m_clrBtnHilight(::GetSysColor(COLOR_BTNHILIGHT))
	, m_clrBtnShadow(::GetSysColor(COLOR_BTNSHADOW))
	, m_clrBtnLight(::GetSysColor(COLOR_3DLIGHT))
	, m_nLastBtn(-1)
	, m_uTimerEvent(0)
	, m_pControls(0)
	, m_bReal3DBorder(FALSE)	// set to TRUE, if you're using FrameEnableDocking()
	, m_bDragChild(FALSE)
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
		_tcscpy(logfont.lfFaceName,_T("MS Sans Serif"));

	}
	logfont.lfHeight = 6 ;
	logfont.lfWidth = 0 ;	// let windows compute this.
	VERIFY( m_GuiFont.CreateFontIndirect( &logfont ) ) ;
}

CToolBarEx::~CToolBarEx()
{
	if( m_pControls ) {
		for( POSITION pos = m_pControls->GetHeadPosition() ; pos ; )
			delete m_pControls->GetNext(pos);
		delete m_pControls;
	}
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
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_WINDOWPOSCHANGING()
	ON_WM_CAPTURECHANGED()
	ON_WM_PARENTNOTIFY()
	ON_WM_KILLFOCUS()
	//}}AFX_MSG_MAP
	ON_MESSAGE(TB_SETBUTTONSIZE, OnSetButtonSize)
	ON_MESSAGE(TB_SETBITMAPSIZE, OnSetBitmapSize)
	ON_MESSAGE(TB_ADDBITMAP, OnAddBitmap)
	ON_MESSAGE(TB_DELETEBUTTON, OnDeleteButton)
#ifdef _MEMDC_H_
	ON_WM_ERASEBKGND()
#endif
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


void CToolBarEx :: SetFlatLook( BOOL bFlat ) {
	if( bFlat != m_bFlatLook ) {
		m_bFlatLook = bFlat;
		if( ::IsWindow(GetSafeHwnd()) ) {
            //flat tool bars have gripper space at the left, cause non-client to resize
            SetWindowPos(0, 0,0,0,0,SWP_FRAMECHANGED|SWP_NOMOVE|SWP_NOSIZE|SWP_NOZORDER);
			// force a repaint of all buttons
			Invalidate();
			// erase/draw the gripper
			OnNcPaint();
			// if the "FrameEnableDocking()" function is used, we have to adjust
			// the bars inside the parent.
			VERIFY(::IsWindow(m_hwndParent));
			((CFrameWnd*)(CWnd::FromHandle(m_hwndParent)))->RecalcLayout();
		}
	}
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

		if( HasButtonText() )
			CalculateOffset();		// strings may have been added

		// attach image-list for even more MFC feeling :)
		CImageList imglist;
		imglist.Attach(hImg);

		POINT cursor;
		::GetCursorPos(&cursor);
		ScreenToClient(&cursor);

		#ifdef _MEMDC_H_
			// if you have Keith Rule's CMemDC class inserted
			// in "stdafx.h", then we use it here ...
			CPaintDC dcp(this);
			CMemDC dc(&dcp);
			dc.FillSolidRect(rcUpdate, m_clrBtnFace);
		#else	// _MEMDC_H_
			CPaintDC dc(this); // device context for painting
		#endif	// _MEMDC_H_

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
				if( !(wState & TBSTATE_WRAP) || ! IsFloating() )
					DrawSeparator(dc, rc);
			} else {
				if( ! CRect().IntersectRect(rcUpdate, rc) )
					continue;	// this button needs no repaint

				BOOL bBtnDown = (wState & TBSTATE_CHECKED) || (wState & TBSTATE_PRESSED);
				BOOL bBtnEnabled = GetToolBarCtrl().IsButtonEnabled(int(uID));
				BOOL bHasCursor = rc.PtInRect(cursor);
				COLORREF clrRect = (bBtnDown && !bHasCursor) ? m_clrBtnLight : m_clrBtnFace;

				// maybe the button has text
				dc.SetTextColor(RGB(0,0,0));
				dc.SetBkColor(clrRect);

				if( HasButtonText() )
					// There is a bug in CToolBar: If there are texts assigned
					// to buttons, then the button-widths may change transparently
					// (without notified by CToolBar), so we recalculate the
					// horizontal offset here:
					m_sizeOffset.cx = (rc.Width() - m_sizeImage.cx) / 2;

				if( ! cdrw.NotifyItemPrePaint(i) )
					continue;	// parent has already drawn the button

				dc.FillSolidRect(rc, clrRect);

				// it seems, that CDC::Draw3dRect() changes the background color
				COLORREF clrBk = dc.GetBkColor();

				if( bBtnDown ) {
					// draw a pressed button
					dc.Draw3dRect(rc, m_clrBtnShadow, m_clrBtnHilight);
					if( ! bHasCursor ) {
						// if the button does not have the cursor on it,
						// then the pressed button is somewhat lighter
						// then the other buttons.
						CRect rcCheck = rc;
						rcCheck.DeflateRect(1,1);

						// draw an invisible frame around the hilighted area
						dc.Draw3dRect(rcCheck, m_clrBtnFace, m_clrBtnFace);

						rcCheck.DeflateRect(1,1);
						CBrush *pBrush = CDC::GetHalftoneBrush();
						dc.SetTextColor(m_clrBtnHilight);
						dc.SetBkColor(m_clrBtnFace);
						dc.FillRect(rcCheck, pBrush);
						dc.SetTextColor(RGB(0,0,0));
						dc.SetBkColor(clrRect);
					}
				} else if( bHasCursor && ! bBtnDown && bBtnEnabled )
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
				
				imglist.Draw(&dc, nBitmap, pt, ILD_TRANSPARENT);

				CString strText = GetButtonText(i);
				if( strText.GetLength() ) {
					CRect rectText(
						rc.left+3+bBtnDown,
						rc.top+m_sizeOffset.cy+m_sizeImage.cy+1+bBtnDown,
						rc.right-3+bBtnDown,
						rc.bottom-3+bBtnDown
					);
					int nBkMode = dc.SetBkMode(TRANSPARENT) ;
					dc.DrawText(strText, rectText, DT_CENTER|DT_VCENTER|DT_NOCLIP);
					dc.SetBkMode(nBkMode) ;
				}
				
				if( ! bBtnEnabled ) {
					// gray out that button
					rc.DeflateRect(bBtnDown,bBtnDown);
					DrawDisabledButton(dc, rc);
				}

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
    // Do not draw a gripper if the bar is floating or not
	// dockable.
	if( (m_dwStyle & CBRS_FLOATING) || m_dwDockStyle == 0 )
		return;

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

		//check whether styles have been changed
		for( nIdx = 0; nIdx < nBtn; ++nIdx ) {
			if( m_Styles[nIdx] != GetButtonStyle(nIdx) )
				// invalidate that button
				InvalidateButton(nIdx);
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
	m_clrBtnLight   = ::GetSysColor(COLOR_3DLIGHT);
}


void CToolBarEx::OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS FAR* lpncsp) 
{
	CToolBar::OnNcCalcSize(bCalcValidRects, lpncsp);
	if( m_bFlatLook ) {
		// adjust non-client area for gripper at left or top
		if( m_dwStyle & CBRS_ORIENT_HORZ ) {
			lpncsp->rgrc[0].left += 4;
			lpncsp->rgrc[0].right += 4;
		} else {
			lpncsp->rgrc[0].top += 6;
			lpncsp->rgrc[0].bottom += 6;
		}
	}
}


void CToolBarEx::OnMouseMove(UINT nFlags, CPoint point) 
{
	if( m_bDragging ) {
		DragMove();
		return;
	}

	if( m_bFlatLook && IsTopParentActive() && GetTopLevelParent()->IsWindowEnabled()) {
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
		// resolve this problem, we set a timer and check, whether
		// the mouse is outside the window ...
		KillTimer(m_uTimerEvent);
		m_uTimerEvent = SetTimer(1, 250, 0);
	}
	CToolBar::OnMouseMove(nFlags, point);
}


void CToolBarEx::OnNcPaint() 
{
	if( m_bFlatLook ) {
		// get window DC that is clipped to the non-client area
		CWindowDC dc(this);
		CRect rectClient;
		GetClientRect(rectClient);
		CRect rectWindow;
		GetWindowRect(rectWindow);
		ScreenToClient(rectWindow);
		rectClient.OffsetRect(-rectWindow.left, -rectWindow.top);
		dc.ExcludeClipRect(rectClient);

		// draw borders in non-client area
		rectWindow.OffsetRect(-rectWindow.left, -rectWindow.top);

		Draw3DBorders(&dc, rectWindow);

		dc.IntersectClipRect(rectWindow);

		#ifdef _MEMDC_H_
			// You're using Keith Rule's CMemDC. In this case
			// we have to make sure that WM_ERASEBKGND
			// will not be sent.
			dc.FillSolidRect(rectWindow, m_clrBtnFace);
		#else
			// erase parts not drawn
			SendMessage(WM_ERASEBKGND, (WPARAM)dc.m_hDC);
		#endif

		DrawGripper(dc);
	} else
		CToolBar::OnNcPaint();
}


void CToolBarEx :: Draw3DBorders(CDC * pDC, CRect & rect) {
	ASSERT_VALID(this);
	ASSERT_VALID(pDC);

	if( m_bReal3DBorder ) {
		DWORD dwStyle = m_dwStyle;
		if (!(dwStyle & CBRS_BORDER_ANY))
			return;

		COLORREF clr = (m_dwStyle & CBRS_BORDER_3D) ? m_clrBtnHilight : m_clrBtnShadow;
		if(m_dwStyle & CBRS_BORDER_LEFT)
			pDC->FillSolidRect(0, 0, 1, rect.Height() - 1, clr);
		if(m_dwStyle & CBRS_BORDER_TOP)
			pDC->FillSolidRect(0, 0, rect.Width()-1 , 1, clr);
		if(m_dwStyle & CBRS_BORDER_RIGHT)
			pDC->FillSolidRect(rect.right, 1, -1, rect.Height() - 1, m_clrBtnShadow);
		if(m_dwStyle & CBRS_BORDER_BOTTOM)
			pDC->FillSolidRect(0, rect.bottom, rect.Width()-1, -1, m_clrBtnShadow);

		// if undockable toolbar at top of frame, apply special formatting to mesh
		// properly with frame menu
		if(!m_pDockContext) {
			pDC->FillSolidRect(0,0,rect.Width(),1,m_clrBtnShadow);
			pDC->FillSolidRect(0,1,rect.Width(),1,m_clrBtnHilight);
		}

		if (dwStyle & CBRS_BORDER_LEFT)
			++rect.left;
		if (dwStyle & CBRS_BORDER_TOP)
			++rect.top;
		if (dwStyle & CBRS_BORDER_RIGHT)
			--rect.right;
		if (dwStyle & CBRS_BORDER_BOTTOM)
			--rect.bottom;
	} else
		DrawBorders(pDC, rect);
}

void CToolBarEx::OnTimer(UINT nIDEvent) 
{
	if( nIDEvent == m_uTimerEvent ) {
		if( m_nLastBtn >= 0 ) {
			POINT pt;
			::GetCursorPos(&pt);
			CRect rc;
			GetWindowRect(rc);
			if( ! rc.PtInRect(pt) ) {
				InvalidateButton(m_nLastBtn);
				m_nLastBtn = -1;
			}
		}
		if( m_nLastBtn < 0 )
			KillTimer(nIDEvent);
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

void CToolBarEx::OnWindowPosChanging(WINDOWPOS FAR* lpwndpos) 
{
	CToolBar::OnWindowPosChanging(lpwndpos);
	
	// If moved just force a redraw. This stops the partial redraw bug.
	if( !(lpwndpos->flags & SWP_NOMOVE) )
		Invalidate(FALSE);
	
}

#define PADWIDTH(x)	(((x)*8+31)&~31)/8


HIMAGELIST CToolBarEx :: GetImageList() {
	m_bDeleteImgList = FALSE;

	HIMAGELIST hImg = 0;

#ifdef TB_GETIMAGELIST
	// Some older versions of VC++ do not know of
	// the TB_GETIMAGELIST macro (defined in commctrl.h).

	hImg = HIMAGELIST(SendMessage(TB_GETIMAGELIST));

#ifdef _DEBUG
	if( hImg == 0 ) {
		TRACE0("CToolBarEx::GetImageList(): could not get image list\n");
	}
#endif
#endif // TB_GETIMAGELIST

	if( ! hImg ) {
		// comctl32.dll version prior to 4.70 doesn't know
		// anything of the TB_GETIMAGELIST message
		if( m_hbmImageWell != 0 ) {
			// Yep - we have a valid image.
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

void CToolBarEx::InvalidateButton(int nIndex) {
	if( nIndex < 0 || nIndex >= GetToolBarCtrl().GetButtonCount() )
		return;
	CRect rc;
	GetItemRect(nIndex, rc);
	InvalidateRect(rc, FALSE);
}

BOOL CToolBarEx :: IsSeparator(int nIndex) const {
	if( nIndex >= 0 && nIndex < GetToolBarCtrl().GetButtonCount() )
		if( GetButtonStyle(nIndex) == TBBS_SEPARATOR ) {
			// make sure this is a "real" separator
			CRect rc;
			GetItemRect(nIndex, rc);
			if( rc.Width() <= 8 )
				return TRUE;
		}

	return FALSE;
}

BOOL CToolBarEx :: IsControl(int nIndex) const {
	if( nIndex >= 0 && nIndex < GetToolBarCtrl().GetButtonCount() )
		if( GetButtonStyle(nIndex) == TBBS_SEPARATOR ) {
			// make sure this is a placeholder for a control
			CRect rc;
			GetItemRect(nIndex, rc);
			if( rc.Width() > 8 )
				return TRUE;
		}

	return FALSE;
}


CWnd * CToolBarEx :: GetControl(int idx, BOOL bIdxIsID) const {
	UINT uID = bIdxIsID ? UINT(idx) : GetItemID(idx);
	for( CWnd * pWnd = GetWindow(GW_CHILD); pWnd; pWnd = pWnd->GetNextWindow() )
		if( UINT(::GetWindowLong(pWnd->GetSafeHwnd(), GWL_ID)) == uID )
			return pWnd;
	return 0;
}


CWnd * CToolBarEx :: CtrlReplace(
						CRuntimeClass * pClass,
						CRect & rc,
						UINT ID,
						DWORD dwStyle ) {
	int nIndex = CommandToIndex(ID);
	if(nIndex < 0) {
		TRACE1("CToolBarEx::CtrlReplace(): 0x%x is not a valid ID for this toolbar.\n,", ID);
		return 0;
	}

	int nWidth = rc.Width();
	if( nWidth < 0 )
		nWidth = -nWidth;
	SetButtonInfo(nIndex, ID, TBBS_SEPARATOR, nWidth);


	CWnd * pCtrl = CreateControl(pClass, rc, ID, dwStyle);

	return pCtrl;
}

CWnd * CToolBarEx :: CtrlInsert(
						CRuntimeClass * pClass,
						CRect & rc,
						UINT ID,
						int nBefore,
						DWORD dwStyle) {
	BOOL bAppend = FALSE;
	CToolBarCtrl & wndToolBarCtrl = GetToolBarCtrl();
	if( nBefore < 0 || nBefore > wndToolBarCtrl.GetButtonCount() )
		bAppend = TRUE;

	int nWidth = rc.Width();
	if( nWidth < 0 )
		nWidth = -nWidth;

	TBBUTTON tbButton;
	tbButton.iBitmap = nWidth;
	tbButton.idCommand = ID;
	tbButton.fsState = TBSTATE_ENABLED;
	tbButton.fsStyle = TBSTYLE_SEP;
	tbButton.dwData = 0;
	tbButton.iString = 0;
	if( bAppend )
		wndToolBarCtrl.AddButtons(1, &tbButton);
	else
		wndToolBarCtrl.InsertButton(nBefore, &tbButton);

	CWnd * pCtrl = CreateControl(pClass, rc, ID, dwStyle);

	return pCtrl;
}

CWnd * CToolBarEx :: CreateControl(
						CRuntimeClass * pClass,
						CRect & rc,
						UINT ID,
						DWORD dwStyle) {
	if( ! pClass || ! pClass->IsDerivedFrom(RUNTIME_CLASS(CWnd)) ) {
		TRACE0("CToolBarEx::CreateControl(): given class is NULL or not derived from CWnd.\n");
		return 0;
	}

	CWnd * pCtrl = 0;

	BOOL bSelfDeleting = TRUE;

	CString strClass = pClass->m_lpszClassName;

	if( strClass == TEXT("CComboBox") ) {
		pCtrl = new CComboBox();
		bSelfDeleting = FALSE;
	} else if( strClass == TEXT("CEdit") ) {
		pCtrl = new CEdit();
		bSelfDeleting = FALSE;
	} else {
		pCtrl = (CWnd *)pClass->CreateObject();
		if( pCtrl == 0 ) {
			TRACE1("CToolBarEx::CreateControl(): dynamic create of control %hs failed.\n",
				pClass->m_lpszClassName);
			return 0;
		}
	}

	// create the control itself
	CRect rect = rc;
	BOOL bCreate = FALSE;

	if( pCtrl->IsKindOf(RUNTIME_CLASS(CComboBox)) )
		bCreate = ((CComboBox*)pCtrl)->Create(WS_CHILD|WS_VISIBLE|dwStyle, rect, this, ID);
	else if( pCtrl->IsKindOf(RUNTIME_CLASS(CEdit)) )
		bCreate = ((CEdit*)pCtrl)->Create(WS_CHILD|WS_VISIBLE|dwStyle, rect, this, ID);
	else
		bCreate = pCtrl->Create(0, 0, WS_CHILD|WS_VISIBLE|dwStyle, rect, this, ID);
	
	if( ! bCreate ) {
		TRACE1("CToolBarEx::CreateControl(): could not Create() control.\n,", ID);
		if( ! bSelfDeleting )
			delete pCtrl;
		return 0;
	}

	if( ! bSelfDeleting ) {
		// we have to remember this control, so we can delete it later
		if( ! m_pControls )
			m_pControls = new CObList();
		m_pControls->AddTail(pCtrl);
	}

	RepositionControls();

	return pCtrl;
}

void CToolBarEx :: RepositionControls() {
	// Walk all descendents.
	for( CWnd * pWnd = GetWindow(GW_CHILD); pWnd; pWnd = pWnd->GetNextWindow() ) {
		// If that window is a child of this
		// toolbar, then reposition this control.
		if( pWnd->GetParent() == this ) {
			DWORD dwID = ::GetWindowLong(pWnd->GetSafeHwnd(), GWL_ID);
			int idx = CommandToIndex(dwID);
			ASSERT(idx >= 0);
			CRect rc;
			GetItemRect(idx, rc);
			pWnd->SetWindowPos(0, rc.left, rc.top, 0, 0, SWP_NOZORDER|SWP_NOACTIVATE|SWP_NOSIZE|SWP_NOCOPYBITS);
			pWnd->ShowWindow(SW_SHOW);
		}
	}
}

void CToolBarEx :: RecalcLayout() {
	// Recalculate the size of the bar.
	BOOL bHorz = (m_dwStyle & CBRS_ORIENT_HORZ) != 0;
	if ((m_dwStyle & CBRS_FLOATING) && (m_dwStyle & CBRS_SIZE_DYNAMIC))
		CalcDynamicLayout(0, LM_HORZ | LM_MRUWIDTH | LM_COMMIT);
	else if (bHorz)
		CalcDynamicLayout(0, LM_HORZ | LM_HORZDOCK | LM_COMMIT);
	else
		CalcDynamicLayout(0, LM_VERTDOCK | LM_COMMIT);

	RepositionControls();

	// recalculate the parent frame
	if( m_dwStyle & CBRS_FLOATING ) {
		ASSERT(m_pDockBar != 0);
		((CMiniDockFrameWnd *)m_pDockBar->GetParent())->RecalcLayout();
	} else {
		((CFrameWnd*)GetParentFrame())->RecalcLayout();
	}
}

HBITMAP CToolBarEx :: GetBitmap(int nBtnID) {
	int nBitmap = SendMessage(TB_GETBITMAP, WPARAM(nBtnID));
	return GetBitmap(nBitmap, m_sizeImage);
}

HBITMAP CToolBarEx :: GetBitmap(int nIndex, const CSize & sizeBitmap) {
	HIMAGELIST hImgList = GetImageList();
	if( ! hImgList )
		return 0;

	CImageList imglist;
	imglist.Attach(hImgList);

	HICON hIcon = imglist.ExtractIcon(nIndex);
	CBitmap bmp;

	if( hIcon ) {
		CClientDC cdc(this) ;
		CDC dc;
		dc.CreateCompatibleDC(&cdc);
		VERIFY(bmp.CreateCompatibleBitmap(&cdc, sizeBitmap.cx, sizeBitmap.cy));
		CBitmap* pOldBmp = dc.SelectObject(&bmp);
		CBrush brush ;
		VERIFY(brush.CreateSolidBrush(m_clrBtnFace));
		::DrawIconEx(
			dc.GetSafeHdc(),
			0,
			0,
			hIcon,
			sizeBitmap.cx,
			sizeBitmap.cy,
			0,
			(HBRUSH)brush,
			DI_NORMAL
		);
		dc.SelectObject( pOldBmp );
		dc.DeleteDC();

		// the icon is not longer needed
		DestroyIcon(hIcon);
	} else
		TRACE1("CToolBarEx::GetBitmap(): unable to extract bitmap with index %d\n", nIndex);

	if( ! m_bDeleteImgList )
		imglist.Detach();

	return hIcon ? HBITMAP(bmp.Detach()) : 0;
}


LRESULT CToolBarEx::OnAddBitmap(WPARAM wParam, LPARAM lParam) {
	// work around a bug in CToolBar:
	// if one calls CToolBar::GetToolBarCtrl().AddBitmap(...),
	// then CToolBar does not realize this. This can lead to
	// confusing button images ...

	int nButtons = int(wParam);
	LPTBADDBITMAP pAddBmp = LPTBADDBITMAP(lParam);

	if( pAddBmp->hInst != HINST_COMMCTRL ) {
		// This workaround does not work, if one
		// specifies "HINST_COMMCTRL" to the "hInst"
		// member of pAddBmp, because we cannot access
		// the internals of commctl32.dll ...

		TRACE0("Adding a bitmap\n");

		HBITMAP hBitmap;
		if( pAddBmp->hInst != 0 )
			// Have to load the bitmap "pAddBmp->nID"
			// contains the resource-ID of the bitmap.
			hBitmap = ::LoadBitmap(pAddBmp->hInst, MAKEINTRESOURCE(pAddBmp->nID));
		else
			// "pAddBmp->nID" is the handle of the bitmap.
			hBitmap = HBITMAP(pAddBmp->nID);

		if(hBitmap == 0)
			return HRESULT(-1);

		// You really should use CToolBarEx as a replacement for
		// CToolBar. So make sure you have set up a toolbar
		// properly before you begin to customize it.
		ASSERT(m_hbmImageWell);

		// retrieve number of images currently stored in CToolBar
		BITMAP bitmap;
		VERIFY(::GetObject(m_hbmImageWell, sizeof(BITMAP), &bitmap));
		int nImageCount = bitmap.bmWidth / m_sizeImage.cx;

		CClientDC cdc(this);
		CDC dcOld, dcNew;
		dcOld.CreateCompatibleDC(&cdc);
		dcNew.CreateCompatibleDC(&cdc);

		HGDIOBJ hOldBmp = ::SelectObject(dcOld.GetSafeHdc(), m_hbmImageWell);

		// create the new bitmap and make it big enough to
		// hold all images (old+new)
		CBitmap bmpNew;
		bmpNew.CreateCompatibleBitmap(
			&cdc,
			bitmap.bmWidth + nButtons * m_sizeImage.cx,
			m_sizeImage.cy);
		CBitmap * pbmpNew = dcNew.SelectObject(&bmpNew);

		dcNew.BitBlt(0,0,bitmap.bmWidth,bitmap.bmHeight,&dcOld,0,0,SRCCOPY);

		::SelectObject(dcOld.GetSafeHdc(), hBitmap);
		dcNew.BitBlt(bitmap.bmWidth,0,m_sizeImage.cx*nButtons,bitmap.bmHeight,&dcOld,0,0,SRCCOPY);

		::SelectObject(dcOld.GetSafeHdc(), hOldBmp);
		dcNew.SelectObject(pbmpNew);
		dcOld.DeleteDC();
		dcNew.DeleteDC();

		VERIFY(bmpNew.GetObject(sizeof(BITMAP), &bitmap));

		HRESULT hRes = DefWindowProc(TB_ADDBITMAP, wParam, lParam);

		// syncronize toolbarcontrol's bitmap with our's
		AddReplaceBitmap(HBITMAP(bmpNew.Detach()));

		return HRESULT(nImageCount);
	}

	return DefWindowProc(TB_ADDBITMAP, wParam, lParam);
}


// intercept TB_DELETEBUTTON, so we can delete controls too.
LRESULT CToolBarEx::OnDeleteButton(WPARAM wParam, LPARAM lParam) {
	CWnd * pControl = GetControl(int(wParam));
	if( pControl ) {
		// this is the control associated with the button to delete
		BOOL bMustDelete = FALSE;
		if( m_pControls ) {
			// It is really a good idea to add a control via the
			// CToolBarEx own members. This will guarantee that
			// all resources are freed.
			POSITION pos = m_pControls->Find(pControl);
			if( pos ) {
				m_pControls->RemoveAt(pos);
				bMustDelete = TRUE;
			}
		}
		pControl->DestroyWindow();
		if( bMustDelete )
			delete pControl;
	}

	return DefWindowProc(TB_DELETEBUTTON, wParam, lParam);
}


#ifdef _MEMDC_H_
BOOL CToolBarEx::OnEraseBkgnd(CDC* pDC) 
{
	return IsFlatLook() ? FALSE : CToolBar::OnEraseBkgnd(pDC);
}
#endif

/////////////////////////////////////////////////////////////////////////////
// ALT-drag

// To keep the users of CToolBarEx from inserting cursor-resources, we
// create the cursors on the fly. This makes usage of CToolBarEx as easy as
// possible:

static const BYTE ANDmaskDrop[] = { 
    0xFF, 0xFF, 0xFF, 0xFF,   // line 1
    0xFF, 0xFF, 0xFF, 0xFF,   // line 2
    0xF3, 0xFF, 0xFF, 0xFF,   // line 3
    0xF1, 0xFF, 0xFF, 0xFF,   // line 4
 
    0xF0, 0xFF, 0xFF, 0xFF,   // line 5
    0xF0, 0x7F, 0xFF, 0xFF,   // line 6
    0xF0, 0x3F, 0xFF, 0xFF,   // line 7
    0xF0, 0x1F, 0xFF, 0xFF,   // line 8
 
    0xF0, 0x0F, 0xFF, 0xFF,   // line 9
    0xF0, 0x07, 0xFF, 0xFF,   // line 10
    0xF0, 0x03, 0xFF, 0xFF,   // line 11
    0xF0, 0x01, 0xFF, 0xFF,   // line 12
 
    0xF0, 0x00, 0xFF, 0xFF,   // line 13
    0xF0, 0x0F, 0xFF, 0xFF,   // line 14
    0xF0, 0x0F, 0xFF, 0xFF,   // line 15
    0xF1, 0x07, 0xFF, 0xFF,   // line 16
 
    0xF3, 0x07, 0xFF, 0xFF,   // line 17
    0xF6, 0x00, 0x00, 0x3F,   // line 18
    0xFE, 0x00, 0x00, 0x3F,   // line 19
    0xFE, 0x00, 0x00, 0x3F,   // line 20
 
    0xFE, 0x00, 0x00, 0x3F,   // line 21
    0xFE, 0x00, 0x00, 0x3F,   // line 22
    0xFE, 0x00, 0x00, 0x3F,   // line 23
    0xFE, 0x00, 0x00, 0x3F,   // line 24
 
    0xFE, 0x00, 0x00, 0x3F,   // line 25
    0xFE, 0x00, 0x00, 0x3F,   // line 26
    0xFF, 0xFF, 0xFF, 0xFF,   // line 27
    0xFF, 0xFF, 0xFF, 0xFF,   // line 28
 
    0xFF, 0xFF, 0xFF, 0xFF,   // line 29
    0xFF, 0xFF, 0xFF, 0xFF,   // line 30
    0xFF, 0xFF, 0xFF, 0xFF,   // line 31
    0xFF, 0xFF, 0xFF, 0xFF    // line 32
};
 
static const BYTE XORmaskDrop[] = { 
    0x00, 0x00, 0x00, 0x00,   // line 1
    0x00, 0x00, 0x00, 0x00,   // line 2
    0x00, 0x00, 0x00, 0x00,   // line 3
    0x04, 0x00, 0x00, 0x00,   // line 4
 
    0x06, 0x00, 0x00, 0x00,   // line 5
    0x07, 0x00, 0x00, 0x00,   // line 6
    0x07, 0x80, 0x00, 0x00,   // line 7
    0x07, 0xC0, 0x00, 0x00,   // line 8
 
    0x07, 0xE0, 0x00, 0x00,   // line 9
    0x07, 0xF0, 0x00, 0x00,   // line 10
    0x07, 0xF8, 0x00, 0x00,   // line 11
    0x07, 0xFC, 0x00, 0x00,   // line 12
 
    0x07, 0xE0, 0x00, 0x00,   // line 13
    0x07, 0x60, 0x00, 0x00,   // line 14
    0x06, 0x60, 0x00, 0x00,   // line 15
    0x04, 0x30, 0x00, 0x00,   // line 16
 
    0x00, 0x30, 0x00, 0x00,   // line 17
    0x00, 0x18, 0x00, 0x00,   // line 18
    0x00, 0xDD, 0xFF, 0x00,   // line 19
    0x00, 0xAC, 0xAA, 0x00,   // line 20
 
    0x00, 0xCD, 0x55, 0x00,   // line 21
    0x00, 0xA0, 0xAA, 0x00,   // line 22
    0x00, 0xD5, 0x55, 0x00,   // line 23
    0x00, 0xAA, 0xAA, 0x00,   // line 24
 
    0x00, 0x00, 0x00, 0x00,   // line 25
    0x00, 0x00, 0x00, 0x00,   // line 26
    0x00, 0x00, 0x00, 0x00,   // line 27
    0x00, 0x00, 0x00, 0x00,   // line 28
 
    0x00, 0x00, 0x00, 0x00,   // line 29
    0x00, 0x00, 0x00, 0x00,   // line 30
    0x00, 0x00, 0x00, 0x00,   // line 31
    0x00, 0x00, 0x00, 0x00    // line 32
};

static const BYTE ANDmaskNoDrop[] = { 
    0xFF, 0xFF, 0xFF, 0xFF,   // line 1
    0xFF, 0xFF, 0xFF, 0xFF,   // line 2
    0xF3, 0xFF, 0xFF, 0xFF,   // line 3
    0xF1, 0xFF, 0xFF, 0xFF,   // line 4
 
    0xF0, 0xFF, 0xFF, 0xFF,   // line 5
    0xF0, 0x7F, 0xFF, 0xFF,   // line 6
    0xF0, 0x3F, 0xFF, 0xFF,   // line 7
    0xF0, 0x1F, 0xFF, 0xFF,   // line 8
 
    0xF0, 0x0F, 0xFF, 0xFF,   // line 9
    0xF0, 0x07, 0xFF, 0xFF,   // line 10
    0xF0, 0x03, 0xFF, 0xFF,   // line 11
    0xF0, 0x01, 0xFF, 0xFF,   // line 12
 
    0xF0, 0x00, 0xFF, 0xFF,   // line 13
    0xF0, 0x0F, 0xFF, 0xFF,   // line 14
    0xF0, 0x0F, 0xFF, 0xFF,   // line 15
    0xF1, 0x07, 0xFF, 0xFF,   // line 16
 
    0xF3, 0x07, 0xFF, 0xFF,   // line 17
    0xF6, 0x00, 0x00, 0x3F,   // line 18
    0xFE, 0x00, 0x00, 0x3F,   // line 19
    0xFE, 0x00, 0x00, 0x3F,   // line 20
 
    0xFE, 0x00, 0x00, 0x3F,   // line 21
    0xFE, 0x00, 0x00, 0x0F,   // line 22
    0xFE, 0x00, 0x00, 0x0F,   // line 23
    0xFE, 0x00, 0x00, 0x0F,   // line 24
 
    0xFE, 0x00, 0x00, 0x0F,   // line 25
    0xFE, 0x00, 0x00, 0x0F,   // line 26
    0xFF, 0xFF, 0x80, 0x0F,   // line 27
    0xFF, 0xFF, 0x80, 0x0F,   // line 28
 
    0xFF, 0xFF, 0x80, 0x0F,   // line 29
    0xFF, 0xFF, 0x80, 0x0F,   // line 30
    0xFF, 0xFF, 0x80, 0x0F,   // line 31
    0xFF, 0xFF, 0x80, 0x0F    // line 32
};
 
static const BYTE XORmaskNoDrop[] = {
    0x00, 0x00, 0x00, 0x00,   // line 1
    0x00, 0x00, 0x00, 0x00,   // line 2
    0x00, 0x00, 0x00, 0x00,   // line 3
    0x04, 0x00, 0x00, 0x00,   // line 4
 
    0x06, 0x00, 0x00, 0x00,   // line 5
    0x07, 0x00, 0x00, 0x00,   // line 6
    0x07, 0x80, 0x00, 0x00,   // line 7
    0x07, 0xC0, 0x00, 0x00,   // line 8
 
    0x07, 0xE0, 0x00, 0x00,   // line 9
    0x07, 0xF0, 0x00, 0x00,   // line 10
    0x07, 0xF8, 0x00, 0x00,   // line 11
    0x07, 0xFC, 0x00, 0x00,   // line 12
 
    0x07, 0xE0, 0x00, 0x00,   // line 13
    0x07, 0x60, 0x00, 0x00,   // line 14
    0x06, 0x60, 0x00, 0x00,   // line 15
    0x04, 0x30, 0x00, 0x00,   // line 16
 
    0x00, 0x30, 0x00, 0x00,   // line 17
    0x00, 0x18, 0x00, 0x00,   // line 18
    0x00, 0xDD, 0xFF, 0x00,   // line 19
    0x00, 0xAC, 0xAA, 0x00,   // line 20
 
    0x00, 0xCD, 0x55, 0x00,   // line 21
    0x00, 0xA0, 0x80, 0x00,   // line 22
    0x00, 0xD5, 0x3F, 0xE0,   // line 23
    0x00, 0xAA, 0xA7, 0x20,   // line 24
 
    0x00, 0x00, 0x22, 0x20,   // line 25
    0x00, 0x00, 0x30, 0x60,   // line 26
    0x00, 0x00, 0x38, 0xE0,   // line 27
    0x00, 0x00, 0x30, 0x60,   // line 28
 
    0x00, 0x00, 0x22, 0x20,   // line 29
    0x00, 0x00, 0x27, 0x20,   // line 30
    0x00, 0x00, 0x3F, 0xE0,   // line 31
    0x00, 0x00, 0x00, 0x00    // line 32
};

void CToolBarEx::OnLButtonDown(UINT nFlags, CPoint point) 
{
	if( ::GetAsyncKeyState(VK_MENU) & (1<<15) )
		// one of the ALT keys is pressed too - begin drag operation
		if( BeginDrag() )
			return;
	
	if( ::GetAsyncKeyState(VK_SHIFT) & (1<<15) )
		// disable the old-style drag
		return;
	
	CToolBar::OnLButtonDown(nFlags, point);
}

void CToolBarEx::OnLButtonUp(UINT nFlags, CPoint point) 
{
	if( m_bDragging )
		EndDrag();
	else
		CToolBar::OnLButtonUp(nFlags, point);
}

BOOL CToolBarEx :: BeginDrag() {
	TRACE0("beginning drag operation\n");

	VERIFY(!m_hDragCursor);
	VERIFY(!m_hNoDragCursor);

	if( !(::GetWindowLong(GetToolBarCtrl().GetSafeHwnd(),GWL_STYLE) & CCS_ADJUSTABLE) )
		return FALSE;	// Bar is not adjustable

	register const int nBtn = GetToolBarCtrl().GetButtonCount();
	const int nLastBtn = m_nLastBtn;
	m_nLastBtn = -1;
	CPoint pt;
	::GetCursorPos(&pt);
	ScreenToClient(&pt);

	m_nDragButton = -1;

	// have a look for whether the button is valid and
	// - if so - draw a dragging border around it.
	for( register int i = 0 ; i < nBtn ; ++i ) {
		if( IsSeparator(i) )
			continue;	// real separators are not draggable

		CRect rc;
		GetItemRect(i, rc);

		const BOOL bHasCursor = rc.PtInRect(pt);

		if( bHasCursor ) {
			// OK we've found the button. Now ask for deletion:
			if( ! DoQueryDelete(i) )
				// the app does not allow the removal ...
				return FALSE;

			m_nDragButton = i;
			CClientDC cdc(this);
			cdc.DrawDragRect(rc, CSize(2,2),0,CSize(0,0));
			break;
		}
	}

	if( m_nDragButton < 0 )
		return FALSE;		// nothing to drag ...

	VERIFY(m_hDragCursor = ::CreateCursor(0, 4, 2, 32, 32, ANDmaskDrop, XORmaskDrop));
	VERIFY(m_hNoDragCursor = ::CreateCursor(0, 4, 2, 32, 32, ANDmaskNoDrop, XORmaskNoDrop));

	// capture the mouse during the drag operation
	SetCapture();

	// make sure we receive keyboard-input
	SetFocus();

	m_hOrigCursor = ::SetCursor(m_hDragCursor);
	m_bDragCursor = TRUE;

	m_bDragging = TRUE;

	::GetCursorPos(&pt);
	SetMarker(m_pDropBar=this, m_ptDrop=pt);

	return m_bDragging;
}



BOOL CToolBarEx :: IsValidDropTarget(const CWnd * pWnd) const {
	return	(pWnd &&
			pWnd->IsKindOf(RUNTIME_CLASS(CToolBarEx)) &&
			(::GetWindowLong(((CToolBarEx*)pWnd)->GetToolBarCtrl()
						.GetSafeHwnd(),GWL_STYLE) & CCS_ADJUSTABLE) &&
			((const CToolBarEx*)pWnd)->GetParentFrame() == GetParentFrame())
			? TRUE : FALSE;
}


void CToolBarEx :: DragMove() {
	//TRACE0("dragmove in progress\n");

	CPoint pt;
	::GetCursorPos(&pt);
	const CWnd * pWnd = WindowFromPoint(pt);

	// is the cursor moving over an adjustable toolbar ?
	BOOL bToolBar =	IsValidDropTarget(pWnd);
	
	// If the window under the cursor is not a toolbar, then
	// check whether this window is a child of a toolbar.
	while( ! bToolBar && (pWnd = pWnd->GetParent()) != 0 )
		bToolBar =	IsValidDropTarget(pWnd);

	// check whether we have to switch the cursor
	if( bToolBar && ! m_bDragCursor ) {
		::SetCursor(m_hDragCursor);
		m_bDragCursor = TRUE;
	} else if( ! bToolBar && m_bDragCursor ) {
		::SetCursor(m_hNoDragCursor);
		m_bDragCursor = FALSE;
	}

	SetMarker(m_pDropBar = (bToolBar ? (CToolBarEx*)pWnd : 0), m_ptDrop = pt);
}

void CToolBarEx :: EndDrag(BOOL bDoMove) {
	TRACE0("ending drag operation\n");

	// remove the marker
	SetMarker(0, CPoint(0,0));

	VERIFY(::SetCursor(m_hOrigCursor));
	::DestroyCursor(m_hDragCursor);
	::DestroyCursor(m_hNoDragCursor);
	m_hDragCursor = 0;
	m_hNoDragCursor = 0;

	if( m_nDragButton >= 0 ) {
		CToolBarCtrl & wndTBCtrl = GetToolBarCtrl();
		register const int nBtn = wndTBCtrl.GetButtonCount();

		if( m_bDragCursor && bDoMove ) {
			// move the button to a different location

			// make sure the last "DragMove()" has done its work correctly:
			ASSERT(m_pDropBar != 0);
			ASSERT_KINDOF(CToolBarEx, m_pDropBar);
			ASSERT(::GetWindowLong(m_pDropBar->GetToolBarCtrl()
									.GetSafeHwnd(),GWL_STYLE) & CCS_ADJUSTABLE);

			// have a look for where to drop the button
			int nDropBtn = m_pDropBar->FindDropButton(m_ptDrop);
			TBBUTTON tbButton;
			memset(&tbButton, 0, sizeof(TBBUTTON)); // not the safest, but the easiest way
													// to zero out all members ;-)

			if( m_pDropBar == this ) {
				// move the button around, but stay on *this* toolbar
				if( nDropBtn == m_nDragButton+1 || (nDropBtn < 0 && m_nDragButton == nBtn-1) ) {
					// simply insert a separator before the dragged button,
					// if there is still none
					if( m_nDragButton > 0 && !IsSeparator(m_nDragButton-1) ) {
						tbButton.iBitmap = 8;
						tbButton.fsState = TBSTATE_ENABLED;
						tbButton.fsStyle = TBSTYLE_SEP;
						if( DoQueryInsert(tbButton, m_nDragButton) )
							wndTBCtrl.InsertButton(m_nDragButton, &tbButton);
					}
				} else if( nDropBtn == m_nDragButton && m_nDragButton > 0 ) {
					// Remove the separator immediately before the dragged button.
					// if there is no such separator, then do nothing
					if( IsSeparator(nDropBtn-1) )
						if( DoQueryDelete(nDropBtn-1) )
							wndTBCtrl.DeleteButton(nDropBtn-1);
				} else {
					wndTBCtrl.GetButton(m_nDragButton, &tbButton);
					if( DoQueryInsert(tbButton, (nDropBtn>=0) ? nDropBtn : nBtn) ) {
						CWnd * pControl = 0;
						if( IsControl(m_nDragButton) ) {
							// Beware: The TB_DELETEBUTTON message causes the toolbar
							// to destroy the associated control.
							// To avoid this we temporary set the parent of the
							// control to NULL.
							pControl = GetControl(m_nDragButton);
							VERIFY(pControl != 0);
							pControl->SetParent(0);
						}

						if( nDropBtn >= 0 )
							// have to insert
							wndTBCtrl.InsertButton(nDropBtn, &tbButton);
						else
							// append the button
							wndTBCtrl.AddButtons(1, &tbButton);

						// delete the button at its original location
						// we do not need to ask the owner, because this
						// was already done in "BeginDrag()"
						wndTBCtrl.DeleteButton(
							(m_nDragButton < nDropBtn || nDropBtn < 0)
								? m_nDragButton
								: m_nDragButton+1
						);

						// Reconnect the control (if any)
						if( pControl )
							pControl->SetParent(this);

						if( m_nDragButton == wndTBCtrl.GetButtonCount()-1 )
							// remove trailing separators too
							RemoveTrailingSeparators();
					}
				}
			} else {
				// move the button to a different toolbar

				wndTBCtrl.GetButton(m_nDragButton, &tbButton);
				CToolBarCtrl & wndDropTBCtrl = m_pDropBar->GetToolBarCtrl();

				if( m_pDropBar->DoQueryInsert(tbButton, (nDropBtn>=0) ? nDropBtn : wndDropTBCtrl.GetButtonCount()) ) {
					// Get the bitmap of the dragged button and resize it to
					// the image-size of the destination-bar.
					int nDestBitmap = 0;
					if( IsControl(m_nDragButton) ) {
						CRect rc;
						GetItemRect(m_nDragButton, rc);
						nDestBitmap = rc.Width();
					} else {
						HBITMAP hBmp = GetBitmap(tbButton.iBitmap, m_pDropBar->m_sizeImage);
						CBitmap bmp;
						if( hBmp ) {
							bmp.Attach(hBmp);
							nDestBitmap = wndDropTBCtrl.AddBitmap(1, &bmp);
						}
					}
					tbButton.iBitmap = nDestBitmap;
					//tbButton.iString = nDestString;
					tbButton.iString = -1;
					BOOL bInsertOK;
					if( nDropBtn >= 0 )
						bInsertOK = wndDropTBCtrl.InsertButton(nDropBtn, &tbButton);
					else
						bInsertOK = wndDropTBCtrl.AddButtons(1, &tbButton);

					if( bInsertOK ) {
						// transfer the string too, if any (check target first)
						if( m_pDropBar->HasButtonText() && HasButtonText() )
						{
							// let the CToolBar class do all the leg work
							m_pDropBar->SetButtonText(
								m_pDropBar->CommandToIndex(tbButton.idCommand),
								GetButtonText(m_nDragButton)
							);
						}
						// check whether the dragged button was a control in real life and
						// - if so - move that control to its new parent.
						CheckMoveControl(m_pDropBar, tbButton);

						wndTBCtrl.DeleteButton(m_nDragButton);

						if( m_nDragButton == wndTBCtrl.GetButtonCount()-1 )
							// remove trailing separators too
							RemoveTrailingSeparators();

						m_pDropBar->RecalcLayout();
					}
				}
			}
		} else {
			// remove the button from the toolbar
			if( bDoMove ) {
				wndTBCtrl.DeleteButton(m_nDragButton);

				if( m_nDragButton == wndTBCtrl.GetButtonCount() )
					// remove trailing separators too
					RemoveTrailingSeparators();
			} else
				// User has aborted the drag-operation.
				// Remove the drag-border from the button
				InvalidateButton(m_nDragButton);
		}

		// Recalculate the size of the bar.and the parent
		RecalcLayout();
	}

	m_bDragging = FALSE;

	// mouse capture is not longer needed
	ReleaseCapture();
}


void CToolBarEx :: CheckMoveControl( CToolBarEx * pToolBar, const TBBUTTON & tbButton ) {
	ASSERT_VALID(pToolBar);
	CWnd * pControl = GetControl(tbButton.idCommand, TRUE);
	if( pControl ) {
		// now change the parent of the control, so that it jumps to the
		// other toolbar
		pControl->SetParent(pToolBar);

		// remove the control from our list (if it's present there) and
		// add it to the target's list
		if( m_pControls ) {
			POSITION pos = m_pControls->Find(pControl);
			if(pos) {
				m_pControls->RemoveAt(pos);
				if( ! pToolBar->m_pControls )
					pToolBar->m_pControls = new CObList();
				pToolBar->m_pControls->AddTail(pControl);
			}
		}
	}
}


void CToolBarEx :: RemoveTrailingSeparators() {
	CToolBarCtrl & wndTBCtrl = GetToolBarCtrl();
	register const int nBtn = wndTBCtrl.GetButtonCount();
	register int i = nBtn;
	while( i && IsSeparator(--i) )
		if( DoQueryDelete(i) )
			wndTBCtrl.DeleteButton(i);
}

int CToolBarEx :: FindDropButton( const CPoint & point ) {
	CPoint pt = point;
	ScreenToClient(&pt);

	CRect rc;
	// find the button which is closest to the cursor
	register const int nBtn = GetToolBarCtrl().GetButtonCount();
	for( register int i = 0 ; i < nBtn ; ++i ) {
		GetItemRect(i, rc);
		if( rc.PtInRect(pt) )
			// insert the button to drop before this button:
			return (pt.x - rc.left < rc.right - pt.x)
					? i
					: ((i==nBtn-1)
						? -1
						: i+1);
	}
	
	// have to append the button
	return -1;
}

void CToolBarEx :: GetMarkerRect( int nButton, CRect & rc ) {
	register const int nBtn = GetToolBarCtrl().GetButtonCount();
	if( nButton < 0 || nButton > nBtn ) {
		// set the marker behind the last button
		GetItemRect(nBtn-1, rc);
		rc.right += 3;
		rc.left = rc.right-6;
	} else {
		// set the marker before the given button
		GetItemRect(nButton, rc);
		rc.left -= 3;
		rc.right = rc.left+6;
	}
	rc.DeflateRect(0,1);
}

void CToolBarEx :: ShowMarker( const CRect & rcMarker, CBitmap & bmpArea ) {
	ASSERT( bmpArea.GetSafeHandle() == 0 );

	CClientDC  WinDC(this);
	CDC MemDC; MemDC.CreateCompatibleDC(&WinDC);

	bmpArea.CreateCompatibleBitmap(&WinDC, rcMarker.Width(), rcMarker.Height());
	CBitmap * pOldBmp = MemDC.SelectObject(&bmpArea);

	CPen pen(PS_SOLID, 1, RGB(0,0,0));
	CPen * pOldPen = WinDC.SelectObject(&pen);

	// save original area:
	MemDC.BitBlt(0,0,rcMarker.Width(),rcMarker.Height(),
				&WinDC, rcMarker.left, rcMarker.top, SRCCOPY);

	WinDC.MoveTo(rcMarker.TopLeft());
	WinDC.LineTo(rcMarker.right, rcMarker.top);
	WinDC.MoveTo(rcMarker.left+1, rcMarker.top+1);
	WinDC.LineTo(rcMarker.right-1, rcMarker.top+1);

	WinDC.MoveTo(rcMarker.left+2, rcMarker.top+2);
	WinDC.LineTo(rcMarker.left+2, rcMarker.bottom-2);
	WinDC.MoveTo(rcMarker.left+3, rcMarker.top+2);
	WinDC.LineTo(rcMarker.left+3, rcMarker.bottom-2);

	WinDC.MoveTo(rcMarker.left, rcMarker.bottom-1);
	WinDC.LineTo(rcMarker.right, rcMarker.bottom-1);
	WinDC.MoveTo(rcMarker.left+1, rcMarker.bottom-2);
	WinDC.LineTo(rcMarker.right-1, rcMarker.bottom-2);

	MemDC.SelectObject(pOldBmp);
	MemDC.DeleteDC();
	WinDC.SelectObject(pOldPen);
}

void CToolBarEx :: RestoreMarker( const CRect & rcArea, CBitmap & bmpArea ) {
	if( bmpArea.GetSafeHandle() == 0 )
		return;

	CClientDC  WinDC(this);
	CDC MemDC; MemDC.CreateCompatibleDC(&WinDC);

	CBitmap * pOldBmp = MemDC.SelectObject(&bmpArea);
	WinDC.BitBlt(rcArea.left, rcArea.top, rcArea.Width(), rcArea.Height(),
				&MemDC, 0, 0, SRCCOPY);

	MemDC.SelectObject(pOldBmp);
	MemDC.DeleteDC();
}

void CToolBarEx :: SetMarker( CToolBarEx * pBar, const CPoint & point ) {
	static CToolBarEx * pLastToolBar = 0;
	static CRect lastRect(0,0,0,0);
	static CBitmap bmpLastSavedArea;

	CRect rcMarker;

	// retrieve proposed rectangle for the marker
	if( pBar != 0 ) {
		int nDropBtn = pBar->FindDropButton(point);
		pBar->GetMarkerRect(nDropBtn, rcMarker);

		if(rcMarker == lastRect)
			return;		// don't need to erase/draw
	}

	// restore the previously marked area:
	if( pLastToolBar ) {
		pLastToolBar->RestoreMarker(lastRect, bmpLastSavedArea);
		bmpLastSavedArea.DeleteObject();
	}

	// draw the marker
	if( pBar != 0 ) {
		pBar->ShowMarker(rcMarker, bmpLastSavedArea);
		lastRect = rcMarker;
	}
	pLastToolBar = pBar;
}

BOOL CToolBarEx :: DoQueryDelete(int nButton) {
	ASSERT(nButton >= 0);

	TBBUTTON tbButton;
	if( ! GetToolBarCtrl().GetButton(nButton, &tbButton) ) {
		TRACE1("CToolBarEx::DoQueryDelete(): could not retrieve button %d\n", nButton);
		return FALSE;
	}

	return QueryDeleteInsert(tbButton, TRUE, nButton);
}

BOOL CToolBarEx :: QueryDeleteInsert(TBBUTTON & tbButton, BOOL bDelete, int nIndex) {
	TBNOTIFY tbn;
	memset(&tbn, 0, sizeof(TBNOTIFY));
	tbn.hdr.hwndFrom = GetSafeHwnd();
	tbn.hdr.idFrom = UINT(::GetWindowLong(tbn.hdr.hwndFrom, GWL_ID));
	tbn.hdr.code = bDelete ? TBN_QUERYDELETE : TBN_QUERYINSERT;
	tbn.iItem = nIndex;
	memcpy((void *)(&tbn.tbButton), (const void *)(&tbButton), sizeof(TBBUTTON));

	CString strText;
	if( bDelete ) {
		strText = GetButtonText(nIndex);
		tbn.cchText = strText.GetLength();
		tbn.pszText = strText.GetBuffer(tbn.cchText);
	}

	ASSERT(GetParentFrame() != 0);
	ASSERT(::IsWindow(GetParentFrame()->GetSafeHwnd()));

	BOOL bRet = GetParentFrame()->SendMessage(
					WM_NOTIFY,
					WPARAM(tbn.hdr.idFrom),
					LPARAM(&tbn)
				);
	
	if( bDelete )
		strText.ReleaseBuffer();

	return bRet;
}

void CToolBarEx::OnCaptureChanged(CWnd *pWnd) 
{
	if( m_bDragging )
		// without the mouse-capture we cannot complete the drag-operation
		EndDrag(FALSE);

	CToolBar::OnCaptureChanged(pWnd);
}


BOOL CToolBarEx :: PreTranslateMessage( MSG * pMsg ) {
	if( m_bDragging &&
		(pMsg->message == WM_KEYDOWN || pMsg->message == WM_KEYUP) && 
		int(pMsg->wParam) == VK_ESCAPE ) {

		// user pressed ESC to abort drag operation
		EndDrag(FALSE);
		return TRUE;
	}
	return CToolBar::PreTranslateMessage(pMsg);
}

void CToolBarEx::OnParentNotify(UINT message, LPARAM lParam) 
{
	if( LOWORD(message) == WM_LBUTTONDOWN && (::GetAsyncKeyState(VK_MENU) & (1<<15)) ) {
		// I see no chance to abort the child's message processing.
		// That's why we set a flag here. If we lose the focus (a click
		// in a child's area will activate that child window), then
		// we start the real drag-operation (that would return the
		// focus to the toolbar).
		// This solution is somewhat obfuscated, so if you know of
		// a better way -- let me know.
		m_bDragChild = TRUE;
		SetFocus();
	}

	CToolBar::OnParentNotify(message, lParam);
}

void CToolBarEx::OnKillFocus(CWnd* pNewWnd) 
{
	CToolBar::OnKillFocus(pNewWnd);
	
	if( m_bDragChild ) {
		// See OnParentNotify() above ...
		m_bDragChild = FALSE;
		if( GetCapture() != this )
			BeginDrag();
	}
}


/////////////////////////////////////////////////////////////////////////////
// helpers for docking 
/////////////////////////////////////////////////////////////////////////////


// We need our own version of a dock bar, because the original
// MFC implementation overlapps toolbars. CToolBarEx don't want
// such a overlapping, because this makes it impossible to draw
// a real 3d border ...
class CToolDockBar : public CDockBar {
	DECLARE_DYNAMIC(CToolDockBar)

	public:
		// this is the one and only method of interest
		virtual CSize	CalcFixedLayout(BOOL bStretch, BOOL bHorz);
};

IMPLEMENT_DYNAMIC(CToolDockBar, CDockBar);

CSize CToolDockBar::CalcFixedLayout(BOOL bStretch, BOOL bHorz)
{
	ASSERT_VALID(this);

	CSize sizeFixed = CControlBar::CalcFixedLayout(bStretch, bHorz);

	// get max size
	CSize sizeMax;
	if (!m_rectLayout.IsRectEmpty())
		sizeMax = m_rectLayout.Size();
	else
	{
		CRect rectFrame;
		CFrameWnd* pFrame = GetParentFrame();
		pFrame->GetClientRect(&rectFrame);
		sizeMax = rectFrame.Size();
	}

	// prepare for layout
	AFX_SIZEPARENTPARAMS layout;
	layout.hDWP = m_bLayoutQuery ?
		NULL : ::BeginDeferWindowPos(m_arrBars.GetSize());
	int cxBorder = 2, cyBorder = 2;
	CPoint pt(-cxBorder, -cyBorder);
	int nWidth = 0;

	BOOL bWrapped = FALSE;

	// layout all the control bars
	for (int nPos = 0; nPos < m_arrBars.GetSize(); nPos++)
	{
		CControlBar* pBar = GetDockedControlBar(nPos);
		void* pVoid = m_arrBars[nPos];

		if (pBar != NULL)
		{
			if(pBar->IsKindOf(RUNTIME_CLASS(CToolBarEx)) && ((CToolBarEx*)pBar)->IsFlatLook())
				((CToolBarEx*)pBar)->m_bReal3DBorder = TRUE,
				cxBorder = cyBorder = 0;
			else if(pBar->IsKindOf(RUNTIME_CLASS(CToolBarEx)) && !((CToolBarEx*)pBar)->IsFlatLook())
				((CToolBarEx*)pBar)->m_bReal3DBorder = FALSE,
				cxBorder = cyBorder = 2;
			else
				cxBorder = cyBorder = 2;

			if (pBar->IsVisible())
			{
				// get ideal rect for bar
				DWORD dwMode = 0;
				if ((pBar->m_dwStyle & CBRS_SIZE_DYNAMIC) &&
					(pBar->m_dwStyle & CBRS_FLOATING))
					dwMode |= LM_HORZ | LM_MRUWIDTH;
				else if (pBar->m_dwStyle & CBRS_ORIENT_HORZ)
					dwMode |= LM_HORZ | LM_HORZDOCK;
				else
					dwMode |=  LM_VERTDOCK;

				CSize sizeBar = pBar->CalcDynamicLayout(-1, dwMode);

				CRect rect(pt, sizeBar);

				// get current rect for bar
				CRect rectBar;
				pBar->GetWindowRect(&rectBar);
				ScreenToClient(&rectBar);

				if (bHorz)
				{
					// Offset Calculated Rect out to Actual
					if (rectBar.left > rect.left && !m_bFloating)
						rect.OffsetRect(rectBar.left - rect.left, 0);

					// If ControlBar goes off the right, then right justify
					if (rect.right > sizeMax.cx && !m_bFloating)
					{
						int x = rect.Width() - cxBorder;
						x = max(sizeMax.cx - x, pt.x);
						rect.OffsetRect(x - rect.left, 0);
					}

					// If ControlBar has been wrapped, then left justify
					if (bWrapped)
					{
						bWrapped = FALSE;
						rect.OffsetRect(-(rect.left + cxBorder), 0);
					}
					// If ControlBar is completely invisible, then wrap it
					else if ((rect.left >= (sizeMax.cx - cxBorder)) &&
						(nPos > 0) && (m_arrBars[nPos - 1] != NULL))
					{
						m_arrBars.InsertAt(nPos, (CObject*)NULL);
						pBar = NULL; pVoid = NULL;
						bWrapped = TRUE;
					}
					if (!bWrapped)
					{
						if (rect != rectBar)
						{
							if (!m_bLayoutQuery &&
								!(pBar->m_dwStyle & CBRS_FLOATING))
							{
								pBar->m_pDockContext->m_rectMRUDockPos = rect;
							}
							AfxRepositionWindow(&layout, pBar->m_hWnd, &rect);
						}
						pt.x = rect.left + sizeBar.cx - cxBorder;
						nWidth = max(nWidth, sizeBar.cy);
					}
				}
				else
				{
					// Offset Calculated Rect out to Actual
					if (rectBar.top > rect.top && !m_bFloating)
						rect.OffsetRect(0, rectBar.top - rect.top);

					// If ControlBar goes off the bottom, then bottom justify
					if (rect.bottom > sizeMax.cy && !m_bFloating)
					{
						int y = rect.Height() - cyBorder;
						y = max(sizeMax.cy - y, pt.y);
						rect.OffsetRect(0, y - rect.top);
					}

					// If ControlBar has been wrapped, then top justify
					if (bWrapped)
					{
						bWrapped = FALSE;
						rect.OffsetRect(0, -(rect.top + cyBorder));
					}
					// If ControlBar is completely invisible, then wrap it
					else if ((rect.top >= (sizeMax.cy - cyBorder)) &&
						(nPos > 0) && (m_arrBars[nPos - 1] != NULL))
					{
						m_arrBars.InsertAt(nPos, (CObject*)NULL);
						pBar = NULL; pVoid = NULL;
						bWrapped = TRUE;
					}
					if (!bWrapped)
					{
						if (rect != rectBar)
						{
							if (!m_bLayoutQuery &&
								!(pBar->m_dwStyle & CBRS_FLOATING))
							{
								pBar->m_pDockContext->m_rectMRUDockPos = rect;
							}
							AfxRepositionWindow(&layout, pBar->m_hWnd, &rect);
						}
						pt.y = rect.top + sizeBar.cy - cyBorder;
						nWidth = max(nWidth, sizeBar.cx);
					}
				}
			}
			if (!bWrapped)
			{
				// handle any delay/show hide for the bar
				pBar->RecalcDelayShow(&layout);
			}
		}
		if (pBar == NULL && pVoid == NULL && nWidth != 0)
		{
			// end of row because pBar == NULL
			if (bHorz)
			{
				pt.y += nWidth - cyBorder;
				sizeFixed.cx = max(sizeFixed.cx, pt.x);
				sizeFixed.cy = max(sizeFixed.cy, pt.y);
				pt.x = -cxBorder;
			}
			else
			{
				pt.x += nWidth - cxBorder;
				sizeFixed.cx = max(sizeFixed.cx, pt.x);
				sizeFixed.cy = max(sizeFixed.cy, pt.y);
				pt.y = -cyBorder;
			}
			nWidth = 0;
		}
	}
	if (!m_bLayoutQuery)
	{
		// move and resize all the windows at once!
		if (layout.hDWP == NULL || !::EndDeferWindowPos(layout.hDWP))
			TRACE0("Warning: DeferWindowPos failed - low system resources.\n");
	}

	// adjust size for borders on the dock bar itself
	CRect rect;
	rect.SetRectEmpty();
	CalcInsideRect(rect, bHorz);

	if ((!bStretch || !bHorz) && sizeFixed.cx != 0)
		sizeFixed.cx += -rect.right + rect.left;
	if ((!bStretch || bHorz) && sizeFixed.cy != 0)
		sizeFixed.cy += -rect.bottom + rect.top;

	return sizeFixed;
}


// dwDockBarMap
const DWORD dwDockBarMap[4][2] =
{
	{ AFX_IDW_DOCKBAR_TOP,      CBRS_TOP    },
	{ AFX_IDW_DOCKBAR_BOTTOM,   CBRS_BOTTOM },
	{ AFX_IDW_DOCKBAR_LEFT,     CBRS_LEFT   },
	{ AFX_IDW_DOCKBAR_RIGHT,    CBRS_RIGHT  },
};


// Unfortunataly a simple rewrite of CFrameWnd's EnableDocking() is not possible,
// because we have not enough permissions to access some data in this class.
// That's why we call CFrameWnd::EnableDocking() first and exchange all occurencies
// of CDockBar objects with our own version of a dock bar.
void FrameEnableDocking(CFrameWnd * pFrame, DWORD dwDockStyle) {
	ASSERT_VALID(pFrame);

	// must be CBRS_ALIGN_XXX or CBRS_FLOAT_MULTI only
	ASSERT((dwDockStyle & ~(CBRS_ALIGN_ANY|CBRS_FLOAT_MULTI)) == 0);

	pFrame->EnableDocking(dwDockStyle);

	for (int i = 0; i < 4; i++) {
		if (dwDockBarMap[i][1] & dwDockStyle & CBRS_ALIGN_ANY) {
			CDockBar* pDock = (CDockBar*)pFrame->GetControlBar(dwDockBarMap[i][0]);
			
			// make sure the dock bar is of correct type
			if( pDock == 0 || ! pDock->IsKindOf(RUNTIME_CLASS(CToolDockBar)) ) {
				BOOL bNeedDelete = ! pDock->m_bAutoDelete;
				pDock->m_pDockSite->RemoveControlBar(pDock);
				pDock->m_pDockSite = 0;	// avoid problems in destroying the dockbar
				pDock->DestroyWindow();
				if( bNeedDelete )
					delete pDock;
				pDock = 0;
			}

			if( pDock == 0 ) {
				pDock = new CToolDockBar;
				if (!pDock->Create(pFrame,
					WS_CLIPSIBLINGS|WS_CLIPCHILDREN|WS_CHILD|WS_VISIBLE |
						dwDockBarMap[i][1], dwDockBarMap[i][0])) {
					AfxThrowResourceException();
				}
			}
		}
	}
}
