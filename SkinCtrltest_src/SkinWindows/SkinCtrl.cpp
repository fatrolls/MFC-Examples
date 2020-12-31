// SkinCtrl.cpp: implementation of the CSkinCtrl class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "SkinCtrlmgr.h"
#include "SkinCtrl.h"
#include "SkinCtrls.h"
#include "skinglobals.h"
#include "..\shared\wclassdefines.h"
#include "..\shared\winclasses.h"
#include "..\shared\delayredraw.h"
#include "..\shared\SysColors.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

// globals -- no other way using windows hooks.
static CSkinCtrl*	g_pCtrl = NULL;
static HHOOK		g_hMsgHook = NULL;
static int			g_nScrollbar = -1;

const int CORNER = 4;
const int EDGE = 1;
const int SCROLLCX = ::GetSystemMetrics(SM_CXHSCROLL);

CFont CSkinCtrl::s_fontMarlett2;
ISkinCtrlRender* CSkinCtrl::s_pRenderer = NULL;
BOOL CSkinCtrl::s_bDrawingEnabled = TRUE;

//////////////////////////////////////////////////////////////////////

CSkinCtrl::CSkinCtrl() : 
	m_pGlobals(NULL), 
	m_dwBaseStyle(SKCS_NOEDGE), 
	m_dwCtrlStyle(0), 
	m_bPreMFCSubclass(FALSE),
	m_bDragging(FALSE)
{
}

CSkinCtrl::~CSkinCtrl()
{
}

void CSkinCtrl::SetGlobals(CSkinGlobals* pGlobals)
{
	m_pGlobals = pGlobals;

//	if (IsValid())
//		Refresh();
}

COLORREF CSkinCtrl::GetBkgndColor() // controls background color
{ 
	switch (EdgeStyle())
	{
		case SKCS_NOEDGE:
		case SKCS_CLIENTEDGE:
			return GetColor(COLOR_WINDOW);

		case SKCS_BTNEDGE:
			return GetColor(COLOR_3DFACE); 

		case SKCS_ETCHEDEDGE:
			return GetParentBkgndColor();

		default:
			ASSERT (0);
			return -1;
	}
} 

COLORREF CSkinCtrl::GetColor(int nColor)
{
	return m_pGlobals ? m_pGlobals->GetColor(nColor) : CSkinGlobals::GetColorSt(nColor);
}

BOOL CSkinCtrl::IsChild(CSkinCtrl* pSkin)
{
	if (!pSkin)
		return FALSE;

	return ::IsChild(m_hWndHooked, pSkin->m_hWndHooked);
}

BOOL CSkinCtrl::AttachWindow(CWnd* pWnd) 
{ 
	m_bPreMFCSubclass = (CWnd::FromHandlePermanent(pWnd->GetSafeHwnd()) == NULL);
	
	if (HookWindow(*pWnd))
	{
		m_bDialog = CWinClasses::IsClass(*pWnd, WC_DIALOGBOX);
		m_dwOrgStyle = pWnd->GetStyle(); // original window style

		// init
		OnSetIni();

		// this forces WM_NCCALCSIZE to be sent to the ctrl
		// so that it can define its new border
		pWnd->SetWindowPos(NULL, 0, 0, 0, 0, SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER); 

		return TRUE;
	}
	
	// else
	return FALSE;
}

// special treatment needed for popup windows
BOOL CSkinCtrl::IsPopup()
{
	// else
	return (::GetParent(GetHwnd()) == ::GetDesktopWindow());
}

void CSkinCtrl::Refresh(BOOL bUpdateWindow) 
{ 
	Invalidate(); 

	if (bUpdateWindow)
		UpdateWindow(GetHwnd());

	SendMessage(WM_NCPAINT);
}

BOOL CSkinCtrl::ModifyStyle(DWORD dwStylesToRemove, DWORD dwStylesToAdd)
{
	DWORD dwStyle = m_dwCtrlStyle;

	m_dwCtrlStyle |= dwStylesToAdd;
	m_dwCtrlStyle &= ~dwStylesToRemove;

	if (dwStyle != m_dwCtrlStyle)
	{
		Invalidate();
		SendMessage(WM_NCPAINT);
	}

	return TRUE;
}

BOOL CSkinCtrl::DetachWindow() 
{ 
	HWND hwnd = GetHwnd();

	if (!hwnd)
		return TRUE; // ?? done already

	CWnd* pWndPerm = CWnd::FromHandlePermanent(hwnd);
	CWnd* pCtrl = pWndPerm ? pWndPerm : CWnd::FromHandle(hwnd);
	ASSERT (pCtrl);

	DWORD dwStyle = pCtrl->GetStyle();
	
	// if we hooked this window PRIOR to MFC subclassing via DDX_Control,
	// then MFC will assert when it destructs the attached control because
	// the HWND does not get correctly detached presumably because the WndProc
	// has been so mucked about. so we unsubclass and then resubclass to keep 
	// MFC happy
	if (pWndPerm && m_bPreMFCSubclass)
		pWndPerm->UnsubclassWindow();
	
	// do children first
	if (pCtrl && pCtrl->GetSafeHwnd())
	{
		CWnd* pChild = pCtrl->GetWindow(GW_CHILD); 
		
		while (pChild)    
		{
			CSkinCtrlMgr::Instance().Unskin(*pChild);
			pChild = pChild->GetNextWindow();
		}
	}
	
	BOOL bRes = HookWindow((HWND)NULL); 
	
	if (pWndPerm && m_bPreMFCSubclass)
		pWndPerm->SubclassWindow(hwnd);
	
	// restore original window style
	if (::IsWindow(*pCtrl))
	{
		if (pCtrl && pCtrl->GetSafeHwnd())
			pCtrl->ModifyStyle(dwStyle, m_dwOrgStyle);
	}
	
	return bRes;
}

LRESULT CSkinCtrl::WindowProc(HWND hRealWnd, UINT msg, WPARAM wp, LPARAM lp)
{
	ASSERT(hRealWnd);

	if (s_bDrawingEnabled)
		return OnMsg(msg, wp, lp);
	else
		return CSubclassWnd::WindowProc(hRealWnd, msg, wp, lp);
}

LRESULT CSkinCtrl::OnMsg(UINT msg, WPARAM wp, LPARAM lp)
{
	UINT uRes = 0;
	LRESULT lr = 0;
	CWnd* pThis = GetCWnd();

	// this is an extra check because if we set the msg hook in response
	// to an edit box whose scrollbars we disabled then the standard way
	// does not seem to work :(
	if (g_hMsgHook && !(GetAsyncKeyState(MK_LBUTTON) & 0x8000))
	{
		// uninstall hook.
		::UnhookWindowsHookEx(g_hMsgHook);
		g_hMsgHook = NULL;
		g_pCtrl = NULL;
		g_nScrollbar = -1;
	}
	
	switch (msg) 
	{
	case WM_HSCROLL:
	case WM_VSCROLL:
		{
			UINT uSBCode = LOWORD(wp);
			int nPos = HIWORD(wp);

			// if lParam is NULL then its from one of 'this' control's scroll bars
			if (!lp)
				OnScroll(uSBCode, nPos, (msg == WM_HSCROLL));
			else
				CSkinCtrlMgr::Instance().DoScroll((HWND)lp, uSBCode, nPos, (msg == WM_HSCROLL)); 
		}
		// drop thru
	case WM_KEYDOWN:
	case WM_KEYUP:
	case WM_CHAR:
		{
			CWindowDC dc(GetCWnd());
			CRect rWindow;
			GetDrawRect(rWindow);
			DrawScrollbars(&dc, rWindow);
		}
		break;
		
	case WM_PAINT: 
		if (WantsDraw(SKCS_PAINT))
		{
			CPaintDC dc(GetCWnd());
			
			if (OnPaint(&dc))
				lr = 0;
			else
				lr = CSubclassWnd::WindowProc(GetHwnd(), msg, (WPARAM)dc.GetSafeHdc(), lp);

			return lr;
		}
		break;
		
	case WM_PRINT: 
		if (lp & PRF_NONCLIENT)
		{
			// base class first
			CSubclassWnd::WindowProc(GetHwnd(), msg, wp, lp);

			if (IsPopup())
			{
				CDC* pDC = CDC::FromHandle((HDC)wp);
				
				CRect rWindow;
				GetDrawRect(rWindow);
				COLORREF color = GetColor(COLOR_3DSHADOW);

				pDC->Draw3dRect(rWindow, color, color);
				DrawScrollbars(pDC, rWindow, SB_BOTH);

				return 0;
			}
			else if (WantsDraw(SKCS_NCPAINT))
			{
				CDC* pDC = CDC::FromHandle((HDC)wp);
				
				OnNcPaint(pDC);
				
				return 0;
			}
		}
		break;
		
	case WM_NCPAINT: 
		if (IsPopup())
		{
			// base class first
			CSubclassWnd::WindowProc(GetHwnd(), msg, wp, lp);

			CWindowDC dc(GetCWnd());
			
			CRect rWindow;
			GetDrawRect(rWindow);
			COLORREF color = GetColor(COLOR_3DSHADOW);

			dc.Draw3dRect(rWindow, color, color);
			DrawScrollbars(&dc, rWindow, SB_BOTH);

			return 0;
		}
		else if (WantsDraw(SKCS_NCPAINT))
		{
			CWindowDC dc(GetCWnd());
			
			if (!WantsDraw(SKCS_NOBASENCPAINT))
			{
				if (wp > 1) // ie a real rgn
				{
					// make sure the scrollbars are included in the draw
					HRGN hRgn = GetScrollTrackRgn();

					if (hRgn)
						::CombineRgn((HRGN)wp, (HRGN)wp, hRgn, RGN_OR);

					::DeleteObject(hRgn);
				}

				CSubclassWnd::WindowProc(GetHwnd(), msg, wp, lp);
			}

			// do our painting over the top
			OnNcPaint(&dc);
			
			return 0;
		}
		break;
		
	case WM_ERASEBKGND: 
		if (WantsDraw(SKCS_ERASEBKGND))
		{
			CDC* pDC = CDC::FromHandle((HDC)wp);
			
			if (OnEraseBkgnd(pDC))
				return TRUE;
		}
		break;

	case WM_DRAWITEM:
		{
			LPDRAWITEMSTRUCT pDIS = (LPDRAWITEMSTRUCT)lp;

			// this really gets a bit tricky
			if (pDIS->CtlType != ODT_MENU)
			{
				CSkinCtrl* pSkin = CSkinCtrlMgr::Instance().GetSkinCtrl(pDIS->hwndItem);

				if (pSkin)
				{
					if (pSkin->WantsDraw(SKCS_DRAWITEM))
					{
						if (CSkinCtrlMgr::Instance().DoDrawItem(pDIS->hwndItem, pDIS))
							return TRUE; 
					}
					else if (pSkin->WantsDraw(SKCS_POSTDRAWITEM))
					{
						BOOL bRes =	CSubclassWnd::WindowProc(GetHwnd(), msg, wp, lp);

						if (pSkin->OnDrawItem(pDIS))
							return TRUE; 
						else
							return bRes;
					}
				}
			}
		}
		break;

	case WM_NCLBUTTONDOWN:
		// when scrolling window controls do alot of 'under the covers' redrawing which
		// we need to overdraw with our scrollbars.
		// the only of doing this is a global message hook for the duration of the scrolling
		if (wp == HTVSCROLL || wp == HTHSCROLL)
		{
			g_pCtrl = this;
			
			if (g_hMsgHook != NULL)
				::UnhookWindowsHookEx(g_hMsgHook);

			g_nScrollbar = (wp == HTVSCROLL ? SB_VERT : SB_HORZ);
			g_hMsgHook = SetWindowsHookEx(WH_MSGFILTER,	MsgWndProc, NULL, ::GetCurrentThreadId());
		}
		break;
		
	case WM_NCLBUTTONUP:
		// remove the global message hook for scrolling
		if (g_hMsgHook)
		{
			::UnhookWindowsHookEx(g_hMsgHook);
			g_hMsgHook = NULL;
			g_pCtrl = NULL;
			g_nScrollbar = -1;
		}
		break;
		
	case WM_NCCALCSIZE:
		lr = Default();

		// popups have simple borders for now
		if (!IsPopup() && WantsDraw(SKCS_NCPAINT) && wp)
		{
			OnNcCalcSize(&((LPNCCALCSIZE_PARAMS)lp)->rgrc[0]);
		}
		return lr;
		
	case WM_NOTIFY:
		{
			NMHDR* pNMHDR = (NMHDR*)lp;
			
			if (pNMHDR->code == NM_CUSTOMDRAW)
			{
				lr = CSkinCtrlMgr::Instance().DoCustomDraw(pNMHDR->hwndFrom, pNMHDR);
				
				if (m_bDialog)
					SetWindowLong(GetHwnd(), DWL_MSGRESULT, lr);
			}
			else
			{
				lr = Default();

				CSkinCtrlMgr::Instance().DoNotifyReflect(pNMHDR->hwndFrom, pNMHDR, lr);
				CSkinCtrlMgr::Instance().DoNotify(*pThis, pNMHDR); // safe version
			}
			return lr;
		}
	
	case WM_COMMAND:
		{
			UINT uMsg = HIWORD(wp);

			if (uMsg > 1)
			{
				lr = Default();

				CSkinCtrlMgr::Instance().DoNotifyReflect((HWND)lp, uMsg, lr); 
				CSkinCtrlMgr::Instance().DoNotify(*pThis, uMsg, LOWORD(wp), CWnd::FromHandle((HWND)lp)); // safe version

				return lr;
			}
		}
		break;

	case WM_SIZE:
		if (OnSize(GET_X_LPARAM(lp), GET_Y_LPARAM(lp)))
			return 0;
		break;
		
	case WM_MOVE:
		if (OnMove(GET_X_LPARAM(lp), GET_Y_LPARAM(lp)))
			return 0;
		break;
		
	case WM_TIMER:
		OnTimer(wp);
		break;
		
	case WM_KILLFOCUS:
	case WM_SETFOCUS:
		SendMessage(WM_NCPAINT);
		OnSetFocus(msg == WM_SETFOCUS);
		break;

	case WM_STYLECHANGED:
		{
			LPSTYLESTRUCT pSS = (LPSTYLESTRUCT)lp;
			OnStyleChanged(wp == GWL_EXSTYLE, pSS->styleOld, pSS->styleNew);
		}
		break;
		
	case WM_CTLCOLORBTN:
	case WM_CTLCOLORDLG:
	case WM_CTLCOLOREDIT:
	case WM_CTLCOLORLISTBOX:
	case WM_CTLCOLORSCROLLBAR:
	case WM_CTLCOLORSTATIC:
		{
			return (LRESULT)CSkinCtrlMgr::Instance().DoCtlColor((HWND)lp, CDC::FromHandle((HDC)wp));
		}
		break;

	case WM_ENABLE:
		{
			SetRedraw(FALSE);
			lr = Default();
			SetRedraw(TRUE);

			Refresh(TRUE);
			return lr;
		}
		break;
	}
	
	// We don't handle it: pass along
	return Default();//CSubclassWnd::WindowProc(GetHwnd(), msg, wp, lp);
}

void CSkinCtrl::OnScroll(UINT nSBCode, UINT nPos, BOOL bHorz)
{
	switch (nSBCode)
	{
	case SB_THUMBTRACK:
		m_bDragging = TRUE;
		break;

	default:
		m_bDragging = FALSE;
		break;
	}
}

void CSkinCtrl::OnUpdateHotspots(LPPOINT pOldCursor, LPPOINT pNewCursor, UINT uOldHitTest, UINT uNewHitTest)
{
	// if the user is in the middle of scrolling
	if (g_hMsgHook)
		return;

	ASSERT (pOldCursor || pNewCursor);

	// if the application has set a render callback 
	// we also check the entire window area
	if (s_pRenderer)
	{
		if (uNewHitTest != uOldHitTest && (uNewHitTest == HTNOWHERE || uOldHitTest == HTNOWHERE))
		{
			CWindowDC dc(GetCWnd());
			OnNcPaint(&dc);
			return; // in which case we don't need to paint anything else
		}
	}

	// default just checks for mouse over scrollbuttons
	DWORD dwStyle = GetStyle();

	// only interested in windows with scrollbars
	if (dwStyle & WS_HSCROLL || dwStyle & WS_VSCROLL)
	{
		CWindowDC dc(GetCWnd());

		// is or was the mouse in the scrollbar areas ?
		if (uOldHitTest == HTVSCROLL || uOldHitTest == HTHSCROLL || uNewHitTest == HTVSCROLL || uNewHitTest == HTHSCROLL)
		{
			CRect rWindow;
			GetDrawRect(rWindow);

			if (pOldCursor && pNewCursor)
			{
				// has it moved on or off a scrollbutton
				CRect rHorz, rVert, rBack, rForward;
				BOOL bOn, bWasOn;

				GetScrollbarRects(rWindow, rHorz, rVert);
				GetScrollbarButtonRects(rHorz, SB_HORZ, rBack, rForward);

				bOn = rBack.PtInRect(*pNewCursor);
				bWasOn = rBack.PtInRect(*pOldCursor);

				if (bOn != bWasOn)
				{
					DrawScrollbars(&dc, rWindow, SB_BOTH);
					return;
				}

				// else try next
				bOn = rForward.PtInRect(*pNewCursor);
				bWasOn = rForward.PtInRect(*pOldCursor);

				if (bOn != bWasOn)
				{
					DrawScrollbars(&dc, rWindow, SB_BOTH);
					return;
				}

				// else try next
				GetScrollbarButtonRects(rVert, SB_VERT, rBack, rForward);

				bOn = rBack.PtInRect(*pNewCursor);
				bWasOn = rBack.PtInRect(*pOldCursor);

				if (bOn != bWasOn)
				{
					DrawScrollbars(&dc, rWindow, SB_BOTH);
					return;
				}

				// else try next
				bOn = rForward.PtInRect(*pNewCursor);
				bWasOn = rForward.PtInRect(*pOldCursor);

				if (bOn != bWasOn)
				{
					DrawScrollbars(&dc, rWindow, SB_BOTH);
					return;
				}
			}
			else
				DrawScrollbars(&dc, rWindow, SB_BOTH);
		}
		else if (uNewHitTest == HTNOWHERE) // mouse has left the window
		{
			CRect rWindow;
			GetDrawRect(rWindow);

			DrawScrollbars(&dc, rWindow, SB_BOTH);
		}
	}
}

BOOL CSkinCtrl::IsHot(LPRECT pRect, BOOL bScreenCoords)
{
	HWND hCapture = ::GetCapture();

	if (hCapture && hCapture != GetHwnd())
		return FALSE;

	CRect rect(pRect);

	if (!pRect)
		GetWindowRect(rect);

	else if (!bScreenCoords)
	{
		CRect rWindow;
		GetWindowRect(rWindow);
		rect.OffsetRect(rWindow.TopLeft());
	}

	return CSkinCtrlMgr::Instance().IsHot(rect);
}

void CSkinCtrl::OnNcCalcSize(LPRECT pClient)
{
	int nEdge = max(0, GetFrameThickness() - 2);

	::InflateRect(pClient, -nEdge, -nEdge);
}

BOOL CSkinCtrl::OnPaint(CDC* pDC)
{
	return FALSE;
}

void CSkinCtrl::OnNcPaint(CDC* pDC)
{
	CRect rWindow;
	GetDrawRect(rWindow);
	
	NcPaint(pDC, rWindow);
}

void CSkinCtrl::NcPaint(CDC* pDC, CRect rect)
{
	NcPaintBorder(pDC, rect, GetParentBkgndColor(), GetBkgndColor(), EdgeStyle());
			
	DrawScrollbars(pDC, rect);
}

void CSkinCtrl::NcPaintBorder(CDC* pDC, CRect rect, COLORREF crParentBack, COLORREF crBack, int nEdgeStyle, BOOL bIsNc)
{
	if (g_nScrollbar != -1)
		return;

	if (nEdgeStyle != SKCS_NOEDGE)
	{
		const int nEdge = EDGE * 2;
		
		// fill the gap between the nc and client areas
		if (bIsNc)
		{
			rect.DeflateRect(EDGE, EDGE);
			CRect rClient;
			GetDrawRect(NULL, rClient);
			
			// make sure on the right and bottom that we do not paint over the scroll bars
			DWORD dwStyle = GetStyle();
			
			if (dwStyle & WS_HSCROLL)
				rClient.bottom += SCROLLCX;
			
			if (dwStyle & WS_VSCROLL)
			{
				if (HasLeftScrollbar())
					rClient.left -= SCROLLCX;
				else
					rClient.right += SCROLLCX;
			}

			// simple filled rects
			pDC->FillSolidRect(rect.left, rect.top, rect.right, 
				max(nEdge, rClient.top - rect.top), crBack);
			
			pDC->FillSolidRect(rect.left, rect.top, 
				max(nEdge, rClient.left - rect.left), rect.bottom, crBack);
			
			pDC->FillSolidRect(min(rect.right - nEdge, rClient.right), rect.top, 
				max(nEdge, rect.right - rClient.right), rect.bottom, crBack);
			
			pDC->FillSolidRect(rect.left, min(rect.bottom - nEdge, rClient.bottom), 
				rect.right, max(nEdge, rect.bottom - rClient.bottom), crBack);
			
			rect.InflateRect(EDGE, EDGE);
		}

		if (!s_pRenderer)
			FillCorners(pDC, rect, crParentBack);

		int nCorner = min(CORNER, min(rect.Height() / 2, rect.Width() / 2)); 

		// special case: very small etched frames
		if (nEdgeStyle == SKCS_ETCHEDEDGE && (rect.Height() < 4 || rect.Width() < 4))
			nEdgeStyle = SKCS_CLIENTEDGE;
				
		Draw3dEdge(pDC, rect, nCorner, nEdgeStyle, GetState(rect));
	}
}

int CSkinCtrl::GetState(LPRECT pHotRect)
{
	int nState = IM_COLD;

	if (!IsWindowEnabled())
		nState = IM_DISABLED;

	else if (pHotRect && IsHot(pHotRect))
		nState = IM_HOT;

	return nState;
}

void CSkinCtrl::FillCorners(CDC* pDC, LPRECT pWindow, COLORREF crParentBack, int nCorners, int nEdgeStyle)
{
	if (!CORNER)
		return;

	// else
	const int nCorner = CORNER + 1;

	if (nEdgeStyle == -1)
		nEdgeStyle = EdgeStyle();

	int nExtra = (nEdgeStyle == SKCS_BTNEDGE) ? 1 : 0;
	
	// fill by rgn method
	CRgn rgnCorners, rgnRect;
	rgnCorners.CreateRoundRectRgn(pWindow->left, pWindow->top, pWindow->right, pWindow->bottom, nCorner, nCorner);
	rgnRect.CreateRectRgnIndirect(pWindow);

	rgnRect.CombineRgn(&rgnRect, &rgnCorners, RGN_DIFF);

	pDC->FillRgn(&rgnRect, GetColorBrush(crParentBack));
	
/*
	CBrush* pOld = pDC->SelectObject();
	
	pDC->SelectStockObject(NULL_PEN);

	CRect rWindow(pWindow);
	CPoint ptCorner[3];
	
	// top left
	ptCorner[0] = ptCorner[1] = ptCorner[2] = rWindow.TopLeft();
	ptCorner[1].y = ptCorner[0].y + nCorner;
	ptCorner[2].x = ptCorner[0].x + nCorner;

	if (nCorners & RC_TOPLEFT)
		pDC->Polygon(ptCorner, 3);
	
	// top right
	ptCorner[0].x = rWindow.right;
	ptCorner[1].x = ptCorner[0].x;
	ptCorner[2].x = ptCorner[0].x - nCorner;

	if (nCorners & RC_TOPRIGHT)
		pDC->Polygon(ptCorner, 3);
	
	// bottom right
	ptCorner[0] = rWindow.BottomRight();
	ptCorner[1].y = ptCorner[0].y - nCorner - 1;
	ptCorner[2].y = ptCorner[0].y;

	if (nCorners & RC_BOTTOMRIGHT)
		pDC->Polygon(ptCorner, 3);
	
	// bottom left
	ptCorner[0].x = rWindow.left;
	ptCorner[1].x = ptCorner[0].x;
	ptCorner[2].x = ptCorner[0].x + nCorner + 1;

	if (nCorners & RC_BOTTOMLEFT)
		pDC->Polygon(ptCorner, 3);
	
	pDC->SelectObject(pOld);
*/
}

BOOL CSkinCtrl::OnEraseBkgnd(CDC* pDC)
{
	CRect rClient;
	GetClientRect(rClient);
	EraseBkgnd(pDC, rClient);
	
	return TRUE;
}

void CSkinCtrl::EraseBkgnd(CDC* pDC, CRect rect)
{
	pDC->FillSolidRect(rect, GetBkgndColor());
}

HBRUSH CSkinCtrl::OnCtlColor(CDC* pDC)
{
	pDC->SetBkMode(TRANSPARENT);
	
	COLORREF crBkgnd = GetBkgndColor();
	pDC->SetBkColor(crBkgnd);
	pDC->SetTextColor(GetColor(COLOR_WINDOWTEXT));
	
	return (HBRUSH)GetColorBrush(crBkgnd)->GetSafeHandle();
}

void CSkinCtrl::GetDrawRect(LPRECT pWindow, LPRECT pClient, BOOL bExcludeScrollbars)
{
	CRect rWindow;
	GetWindowRect(rWindow);
	
	if (pClient)
	{
		GetClientRect(pClient);
		GetCtrl()->ClientToScreen(pClient);
		::OffsetRect(pClient, -rWindow.left, -rWindow.top);
		
		if (!bExcludeScrollbars)
		{
			DWORD dwStyle = GetStyle();
			
			if (dwStyle & WS_VSCROLL)
			{
				if (HasLeftScrollbar())
					pClient->left -= SCROLLCX;
				else
					pClient->right += SCROLLCX;
			}
			
			if (dwStyle & WS_HSCROLL)
				pClient->bottom += SCROLLCX;
		}
	}
	
	if (pWindow)
	{
		rWindow.OffsetRect(-rWindow.TopLeft());
		*pWindow = rWindow;
	}
}

int CSkinCtrl::GetFrameThickness() 
{ 
	if (IsPopup())
		return 2;

	else if (EdgeStyle() == SKCS_NOEDGE)
		return 0;

	else
		return EDGE + 2; 
}

BOOL CSkinCtrl::HasCtrlStyle(DWORD dwStyle, DWORD dwMask)
{
	if (dwMask == -1)
		dwMask = dwStyle;

	return ((m_dwCtrlStyle & dwMask) == dwStyle);
}

BOOL CSkinCtrl::HasLeftScrollbar()
{
	DWORD dwExStyle = GetCtrl()->GetExStyle();
	return (dwExStyle & WS_EX_LEFTSCROLLBAR);
}

BOOL CSkinCtrl::IsScrollbarEnabled(int nBar, BOOL bSpinButton)
{
	// Disabled scrollbar never have a thumb
	if (!IsWindowEnabled())
		return FALSE;      

	if (bSpinButton)
		return TRUE;
	
	// The minimal thumb size depends on the system version
	// For Windows 98 minimal thumb size is a half of scrollbar size 
	// and for Windows NT is always 8 pixels regardless of system metrics. 
	// I really don't know why.
	int nMinThumbSize;
	
	if (GetVersion() & 0x80000000) // Windows 98 code
		nMinThumbSize = SCROLLCX / 2;
	else                    
		nMinThumbSize = 8;

	CWnd* pWnd = GetCWnd();

	SCROLLINFO si;
	si.cbSize = sizeof(SCROLLINFO);
	si.fMask = SIF_ALL;     
	pWnd->GetScrollInfo(nBar, &si );

	CRect rWindow, rScrollbar;

	GetWindowRect(rWindow);
	GetScrollbarRects(rWindow, nBar == SB_HORZ ? rScrollbar : NULL, nBar == SB_VERT ? rScrollbar : NULL);
	
	// Calculate the size and position of the thumb 
	int nRange = si.nMax - si.nMin + 1; 
	
	if (nRange)
	{
		CRect rThumb(rScrollbar);
		int nScrollArea = (nBar == SB_HORZ ? rScrollbar.Width() : rScrollbar.Height()) - 2 * SCROLLCX;
		
		int nThumbSize; 

		if (!si.nPage) // If nPage is not set then thumb has default size
			nThumbSize = GetSystemMetrics(SM_CXHTHUMB);
		else
			nThumbSize = max(MulDiv(si.nPage ,nScrollArea, nRange), nMinThumbSize);
		
		if (nThumbSize >= nScrollArea && nScrollArea > 0)
			return FALSE;
	}
	else
		return FALSE;

	return TRUE;
}

void CSkinCtrl::DrawScrollbars(CDC* pDC, CRect rWindow, int nBar)
{
	if (CSkinBase::IsThemingEnabled())
		return;

	DWORD dwStyle = GetStyle();
	BOOL bHorz = (dwStyle & WS_HSCROLL);
	BOOL bVert = (dwStyle & WS_VSCROLL);
	BOOL bDrawHorz = (nBar == SB_HORZ || nBar == SB_BOTH);
	BOOL bDrawVert = (nBar == SB_VERT || nBar == SB_BOTH);

	CPoint ptCursor;
	GetCursorPos(&ptCursor);
	
	if (bHorz && bVert)
	{
		CRect rHorz, rVert, rDead;
		GetScrollbarRects(rWindow, rHorz, rVert, rDead);

		if (bDrawHorz)
			DrawScrollBar(pDC, rHorz, SB_HORZ, &ptCursor);
		
		if (bDrawVert)
			DrawScrollBar(pDC, rVert, SB_VERT, &ptCursor);
		
		// draw the dead space
		if (nBar == SB_BOTH)
			pDC->FillSolidRect(rDead, GetBkgndColor());
	}
	else if (bVert && bDrawVert)
	{
		CRect rVert;
		GetScrollbarRects(rWindow, NULL, rVert);
		DrawScrollBar(pDC, rVert, SB_VERT, &ptCursor);
	}
	else if (bHorz && bDrawHorz)
	{
		CRect rHorz;
		GetScrollbarRects(rWindow, rHorz, NULL);
		DrawScrollBar(pDC, rHorz, SB_HORZ, &ptCursor);
	}
}

HRGN CSkinCtrl::GetScrollTrackRgn()
{
	CRect rVert, rHorz, rWindow;

	GetDrawRect(rWindow);
	GetScrollbarRects(rWindow, rHorz, rVert, NULL);

	if (rHorz.IsRectEmpty() && rVert.IsRectEmpty())
		return NULL; // has no scrollbars

	// else
	CRgn rgn;

	if (!rHorz.IsRectEmpty() && !rVert.IsRectEmpty())
	{
		CRgn rgnTemp;

		rgn.CreateRectRgnIndirect(rHorz);
		rgnTemp.CreateRectRgnIndirect(rVert);

		rgn.CombineRgn(&rgn, &rgnTemp, RGN_OR);
		
		rgnTemp.DeleteObject();
	}
	else if (!rHorz.IsRectEmpty())
	{
		rgn.CreateRectRgnIndirect(rHorz);
	}
	else // if (!rVert.IsRectEmpty())
	{
		rgn.CreateRectRgnIndirect(rVert);
	}

	return (HRGN)rgn.Detach();
}

void CSkinCtrl::GetScrollbarRects(CRect rWindow, LPRECT pHorz, LPRECT pVert, LPRECT pDeadSpace)
{
	int nFrameSize = GetFrameThickness(); 
	
	DWORD dwStyle = GetStyle();
	BOOL bHorz = (dwStyle & WS_HSCROLL);
	BOOL bVert = (dwStyle & WS_VSCROLL);
	BOOL bLeftScrollbar = HasLeftScrollbar();

	// init
	if (pHorz)
		SetRectEmpty(pHorz);

	if (pVert)
		SetRectEmpty(pVert);

	if (pDeadSpace)
		SetRectEmpty(pDeadSpace);

	if (bHorz && bVert)
	{
		if (pHorz)
		{
			pHorz->left = rWindow.left + nFrameSize + (bLeftScrollbar ? SCROLLCX : 0); 
			pHorz->top = rWindow.bottom - nFrameSize - SCROLLCX;
			pHorz->right = rWindow.right - nFrameSize - (bLeftScrollbar ? 0 : SCROLLCX); 
			pHorz->bottom = rWindow.bottom - nFrameSize;
		}
		
		if (pVert)
		{
			pVert->left = bLeftScrollbar ? (rWindow.left + nFrameSize) : 
										(rWindow.right - nFrameSize - SCROLLCX); 
			pVert->top = rWindow.top + nFrameSize;
			pVert->right = pVert->left + SCROLLCX; 
			pVert->bottom = rWindow.bottom - nFrameSize - SCROLLCX;
		}

		if (pDeadSpace)
		{
			pDeadSpace->left = bLeftScrollbar ? (rWindow.left + nFrameSize) : 
										(rWindow.right - nFrameSize - SCROLLCX); 
			pDeadSpace->right = pDeadSpace->left + SCROLLCX; 
			pDeadSpace->top = rWindow.bottom - nFrameSize - SCROLLCX;
			pDeadSpace->bottom = pDeadSpace->top + SCROLLCX;
		}
	}
	else if (bVert && pVert)
	{
		pVert->left = bLeftScrollbar ? (rWindow.left + nFrameSize) : 
										(rWindow.right - nFrameSize - SCROLLCX); 
		pVert->top = rWindow.top + nFrameSize;
		pVert->right = pVert->left + SCROLLCX; 
		pVert->bottom = rWindow.bottom - nFrameSize;
	}
	else if (bHorz && pHorz)
	{
		pHorz->left = rWindow.left + nFrameSize; 
		pHorz->top = rWindow.bottom - nFrameSize - SCROLLCX;
		pHorz->right = rWindow.right - nFrameSize; 
		pHorz->bottom = rWindow.bottom - nFrameSize;
	}
}

void CSkinCtrl::DrawScrollbarThumb(CDC* pDC, CRect rScrollbar, int nBar)
{
	// The minimal thumb size depends on the system version
	// For Windows 98 minimal thumb size is a half of scrollbar size 
	// and for Windows NT is always 8 pixels regardless of system metrics. 
	// I really don't know why.
	int nMinThumbSize;
	
	if (GetVersion() & 0x80000000) // Windows 98 code
		nMinThumbSize = SCROLLCX / 2;
	else                    
		nMinThumbSize = 8;

	CWnd* pWnd = GetCWnd();

	// Disabled scrollbar never have a thumb
	if (!IsWindowEnabled())
		return;      
	
	SCROLLINFO si;
	si.cbSize = sizeof(SCROLLINFO);
	si.fMask = SIF_ALL;     
	pWnd->GetScrollInfo(nBar, &si );
	
	// Calculate the size and position of the thumb   
	int nRange = si.nMax - si.nMin + 1; 
	
	if (nRange)
	{
		CRect rThumb(rScrollbar);
		int nScrollArea = (nBar == SB_HORZ ? rScrollbar.Width() : rScrollbar.Height()) - 2 * SCROLLCX;
		
		int nThumbSize; 

		if (!si.nPage) // If nPage is not set then thumb has default size
			nThumbSize = GetSystemMetrics(SM_CXHTHUMB);
		else
			nThumbSize = max(MulDiv(si.nPage ,nScrollArea, nRange), nMinThumbSize);
		
		if (nThumbSize >= nScrollArea)
		{
			nThumbSize = nScrollArea;
			return;
		}
		
		int nThumbPos;
		if (UINT(nRange) == si.nPage)
		{
			nThumbPos = 0;
			nThumbSize--;
		}
		else
			nThumbPos = MulDiv(si.nPos - si.nMin, nScrollArea - nThumbSize, nRange - si.nPage);
		
		if (nBar == SB_VERT)
		{
			rThumb.top += SCROLLCX + nThumbPos;
			rThumb.bottom = rThumb.top + nThumbSize;
		}
		else // SB_HORZ
		{
			rThumb.left += SCROLLCX + nThumbPos;
			rThumb.right = rThumb.left + nThumbSize;
		}
		
		if (nThumbSize <= nScrollArea) // Don't draw the thumb when it's larger than the scroll area
		{
			pDC->FillSolidRect(rThumb, 0);
			pDC->Draw3dRect(rThumb, GetColor(COLOR_3DHILIGHT), GetColor(COLOR_3DSHADOW));
		}
	}   
}

void CSkinCtrl::DrawScrollBar(CDC* pDC, CRect rScrollbar, int nBar, LPPOINT pCursor)
{   
	BOOL bMouseDown = (!m_bDragging && pCursor) ? (GetAsyncKeyState(MK_LBUTTON) & 0x8000) : FALSE;
	
	// Calculate the arrow rectangles
	CRect rc1 = rScrollbar, rc2 = rScrollbar; 
	GetScrollbarButtonRects(rScrollbar, nBar, rc1, rc2);
		
	// Draw the scrollbar arrows
	DrawScrollbarButton(pDC, rc1, nBar, TRUE, (bMouseDown && rc1.PtInRect(*pCursor)), GetBkgndColor());
	DrawScrollbarButton(pDC, rc2, nBar, FALSE, (bMouseDown && rc2.PtInRect(*pCursor)), GetBkgndColor());
}

void CSkinCtrl::GetScrollbarButtonRects(CRect rScrollbar, int nBar, LPRECT pBack, LPRECT pForward)
{
	int nScrollSize = SCROLLCX;
	
	if (nBar == SB_HORZ)
	{
		if ((rScrollbar.Width()) < 2 * nScrollSize)
			nScrollSize = rScrollbar.Width() / 2;
		
		if (pBack)
		{
			*pBack = rScrollbar;
			pBack->right = pBack->left + nScrollSize;
		}
		
		if (pForward)
		{
			*pForward = rScrollbar;
			pForward->left = pForward->right - nScrollSize;
		}
	}
	else // SB_VERT
	{
		if ((rScrollbar.Height()) < 2 * nScrollSize)
			nScrollSize = rScrollbar.Height() / 2;
		
		if (pBack)
		{
			*pBack = rScrollbar;
			pBack->bottom = pBack->top + nScrollSize;      
		}
		
		if (pForward)
		{
			*pForward = rScrollbar;
			pForward->top = pForward->bottom - nScrollSize;
		}
	}   
}

void CSkinCtrl::DrawScrollbarButton(CDC* pDC, CRect rButton, int nBar, BOOL bBack, BOOL bDown, COLORREF crParentBackColor, BOOL bSpinButton)
{
	// determine state
	BOOL bEnabled = IsScrollbarEnabled(nBar, bSpinButton);

	int nState = IM_COLD;
	
	if (!bEnabled)
		nState = IM_DISABLED;

	else if (!m_bDragging)
	{
		if (bDown)
			nState = IM_DOWN;
		
		else if (IsHot(rButton))
			nState = IM_HOT;
	}

	BOOL bClipped = bSpinButton || (nBar == SB_HORZ && rButton.Width() < SCROLLCX) || 
									(nBar == SB_VERT && rButton.Height() < SCROLLCX);

	BOOL bTextured = (GetControlBitmap(bClipped ? SKCB_SPINUP : SKCB_SCROLLUP, 0, 0, 
										bClipped ? -1 : SKCB_SCROLLALL) != NULL);
	
	CDC dcMem;
	dcMem.CreateCompatibleDC(pDC);
	
	CRect rMem(rButton);
	rMem.OffsetRect(-rMem.TopLeft());
	
	CBitmap bmp;
	bmp.CreateCompatibleBitmap(pDC, rButton.Width(), rButton.Height());
	CBitmap* pOldBM = dcMem.SelectObject(&bmp);

	if (bTextured)
	{
		dcMem.FillSolidRect(rMem, crParentBackColor);

		int nCtl = SKCB_SCROLLALL;
		COLORREF crMask;

		if (bClipped)
		{
			if (nBar == SB_HORZ)
				nCtl = bBack ? SKCB_SPINLEFT : SKCB_SPINRIGHT;
			else
				nCtl = bBack ? SKCB_SPINUP : SKCB_SPINDOWN;
		}
		else
		{
			if (nBar == SB_HORZ)
				nCtl = bBack ? SKCB_SCROLLLEFT : SKCB_SCROLLRIGHT;
			else
				nCtl = bBack ? SKCB_SCROLLUP : SKCB_SCROLLDOWN;
		}

		CDC dcMem2;
		dcMem2.CreateCompatibleDC(pDC);

		CBitmap* pBM = GetControlBitmap(nCtl, nState, &crMask, SKCB_SCROLLALL);
		CBitmap* pOld = dcMem2.SelectObject(pBM);

		BITMAP bm;
		pBM->GetBitmap(&bm);

		if (bm.bmHeight != rMem.bottom || bm.bmWidth != rMem.right)
		{
			CSkinBase::StretchBlt(&dcMem, 0, 0, rMem.right, rMem.bottom, &dcMem2, 0, 0, bm.bmWidth, bm.bmHeight, SRCCOPY, crMask);
		}
		else
		{
			CSkinBase::BitBlt(&dcMem, 0, 0, rMem.right, rMem.bottom, &dcMem2, 0, 0, SRCCOPY, crMask);
		}

		if (nBar == SB_HORZ)
		{
//			if (bClipped)
//				rMem.left += (bBack ? -1 : 1);
//			else
//				rMem.left += (bBack ? -2 : 3);
		}

		dcMem2.SelectObject(pOld);
		dcMem2.DeleteDC();
	}
	else
	{
		// border
		if (!s_pRenderer || !s_pRenderer->Draw3dRect(&dcMem, rMem, SKCS_BTNEDGE, nState, GetColor(COLOR_3DFACE)))
		{
			int nStyle = (bDown ? SKCS_CLIENTEDGE : SKCS_BTNEDGE);

			int nCorner = !bSpinButton ? SCROLLCX / 2 : min(CORNER, min(rMem.right, rMem.bottom) / 2);
			COLORREF crBack = GetColor((nState == IM_DOWN || nState == IM_HOT) ? COLOR_3DHILIGHT : COLOR_3DFACE);

			dcMem.FillSolidRect(rMem, crParentBackColor);

			dcMem.SelectStockObject(NULL_PEN);
			CBrush* pOldBr = dcMem.SelectObject(GetColorBrush(crBack));

			if (!bSpinButton)
				dcMem.Ellipse(rMem.left, rMem.top, rMem.right + 1, rMem.bottom + 1);
			else
				dcMem.RoundRect(rMem.left, rMem.top, rMem.right + 1, rMem.bottom + 1, nCorner * 2, nCorner * 2);

			dcMem.SelectObject(pOldBr);

			if (!bClipped) // standard round buttons
			{
				Draw3dEdge(&dcMem, rMem, nCorner, nStyle, nState);
			}
			else
			{
				DWORD dwFlags = RC_EDGES | RC_THIN | (bDown ? RC_DOWN : RC_UP);
				DWORD dwCorners = 0;
				int nClipping = 0;

				if (nBar == SB_HORZ)
				{
					dcMem.FillSolidRect((bBack ? nCorner : 0), 0,
										rMem.right - (bBack ? 0 : nCorner),	rMem.bottom,
										crBack);

					nClipping = (bBack ? ISKCR_CLIPRIGHT : ISKCR_CLIPLEFT);
				}
				else
				{
					dcMem.FillSolidRect(0, (bBack ? nCorner : 0),
										rMem.right,	rMem.bottom - (bBack ? 0 : nCorner),
										crBack);

					nClipping = (bBack ? ISKCR_CLIPBOTTOM : ISKCR_CLIPTOP);
				}

				// border
				Draw3dEdge(&dcMem, rMem, nCorner, nStyle, nState, nClipping);

//				if (nBar == SB_HORZ)
//					rMem.left += (bBack ? -2 : 3);
			}
		}
	}

	if (!bTextured || !GetControlBitmap(SKCB_SCROLLUP))
	{
		if (nBar == SB_HORZ)
			rMem.left += (bBack ? -2 : 3);

		else if (bClipped && !bBack)
			rMem.top -= 2;

		char cArrow = (nBar == SB_HORZ) ? (bBack ? 0x77 : 0x38) : (bBack ? 0x74 : 0x75);

		COLORREF colorText = GetColor(bEnabled ? COLOR_WINDOWTEXT : COLOR_GRAYTEXT);
		dcMem.SetTextColor(colorText);

		if (bDown)
			rMem.OffsetRect(1, 1);
		
		dcMem.SetBkMode(TRANSPARENT);
		CFont* pOld = dcMem.SelectObject(GetFont(SBFONT_MARLETT));
		dcMem.DrawText(cArrow, rMem, DT_VCENTER | DT_CENTER | DT_SINGLELINE);
		dcMem.SelectObject(pOld);
	}
	
	pDC->BitBlt(rButton.left, rButton.top, rButton.Width(), rButton.Height(), &dcMem, 0, 0, SRCCOPY);
	
	dcMem.SelectObject(pOldBM);
	dcMem.DeleteDC();
	bmp.DeleteObject();
}

void CSkinCtrl::Draw3dEdge(CDC* pDC, LPRECT pRect, int nRadius, int nEdge, int nState, int nClipping)
{
	CRect rect(pRect);

	if (s_pRenderer)
	{
		if ((nClipping == ISKCR_CLIPNONE) && (nRadius == (pRect->right - pRect->left) / 2))
		{
			if (s_pRenderer->Draw3dRoundEdge(pDC, pRect, nEdge, nState))
				return;
		}
		else if (s_pRenderer->Draw3dEdge(pDC, pRect, nEdge, nState, nClipping))
			return;
	}

	DWORD dwEdges = RC_ALL & 
					((nClipping & ISKCR_CLIPLEFT) ? ~RC_LEFT : RC_ALL) &
					((nClipping & ISKCR_CLIPRIGHT) ? ~RC_RIGHT : RC_ALL) &
					((nClipping & ISKCR_CLIPTOP) ? ~RC_TOP : RC_ALL) &
					((nClipping & ISKCR_CLIPBOTTOM) ? ~RC_BOTTOM : RC_ALL);

	// else
	switch (nEdge)
	{
	case SKCS_BTNEDGE:
		CRoundCorner::Draw(pDC, rect, nRadius, dwEdges, RC_EDGES | RC_THIN | RC_UP);
		break;
		
	case SKCS_CLIENTEDGE:
		CRoundCorner::Draw(pDC, rect, nRadius, dwEdges, RC_EDGES | RC_THIN | RC_DOWN);
		break;
		
	case SKCS_ETCHEDEDGE:
		if (nRadius < 2)
		{
			BOOL bHorz = (rect.Height() <= nRadius);
			
			bHorz ? rect.bottom-- : rect.right--;
			pDC->FillSolidRect(rect, GetColor(COLOR_3DSHADOW));
			
			rect.OffsetRect(bHorz ? 0 : 1, bHorz ? 1 : 0);
			pDC->FillSolidRect(rect, GetColor(COLOR_3DHILIGHT));
		}
		else // box
		{
			rect.right--;
			rect.bottom--;
			
			pDC->SelectStockObject(NULL_BRUSH);
			rect.OffsetRect(1, 1);
			
			// highlight first then shadow, else 2 of the corners look wrong
			CPen* pOldPen = pDC->SelectObject(GetColorPen(COLOR_3DHIGHLIGHT));
			pDC->RoundRect(rect, CPoint(nRadius, nRadius));
			
			rect.OffsetRect(-1, -1);
			pOldPen = pDC->SelectObject(GetColorPen(COLOR_3DSHADOW));
			pDC->RoundRect(rect, CPoint(nRadius, nRadius));
			pDC->SelectObject(pOldPen);
		}
	}
}

void CSkinCtrl::DrawDropButton(CDC* pDC, CRect rButton, LPPOINT pCursor, COLORREF crParentBackColor)
{
	int nDC = pDC->SaveDC();

	rButton.bottom = rButton.top + SCROLLCX;
	
	// pressed?
	CPoint ptCursor;
	
	BOOL bMouseDown = (GetAsyncKeyState(MK_LBUTTON) & 0x8000);
	
	if (bMouseDown)
	{
		if (!pCursor)
			GetCursorPos(&ptCursor);
		else
			ptCursor = *pCursor;
	}
	
	// textured?
	if (GetControlBitmap(SKCB_SCROLLDROPDOWN))
	{
		int nState = (bMouseDown && rButton.PtInRect(ptCursor)) ? IM_DOWN : IsHot(rButton) ? IM_HOT : IM_COLD;
		
		CDC dcMem, dcMem2;
		dcMem.CreateCompatibleDC(pDC);
		dcMem2.CreateCompatibleDC(pDC);
		
		CRect rMem(rButton);
		rMem.OffsetRect(-rMem.TopLeft());
		
		CBitmap bmp;
		bmp.CreateCompatibleBitmap(pDC, rButton.Width(), rButton.Height());
		CBitmap* pOldBM = dcMem.SelectObject(&bmp);

		dcMem.FillSolidRect(rMem, crParentBackColor);

		COLORREF crMask;
		CBitmap* pBM = GetControlBitmap(SKCB_SCROLLDROPDOWN, nState, &crMask);
		CBitmap* pOldBM2 = dcMem2.SelectObject(pBM);

		BITMAP bm;
		pBM->GetBitmap(&bm);

		// if the mask is -1 then we assume that no transparency is required
		if (bm.bmHeight != rMem.bottom || bm.bmWidth != rMem.right)
		{
			CSkinBase::StretchBlt(&dcMem, 0, 0, rMem.right, rMem.bottom, &dcMem2, 0, 0, bm.bmWidth, bm.bmHeight, SRCCOPY, crMask);
		}
		else
		{
			CSkinBase::BitBlt(&dcMem, 0, 0, rMem.right, rMem.bottom, &dcMem2, 0, 0, SRCCOPY, crMask);
		}

		pDC->BitBlt(rButton.left, rButton.top, rButton.Width(), rButton.Height(), &dcMem, 0, 0, SRCCOPY);

		dcMem.SelectObject(pOldBM);
		dcMem.DeleteDC();
		dcMem2.SelectObject(pOldBM2);
		dcMem2.DeleteDC();
		bmp.DeleteObject();
	}
	else
		DrawScrollbarButton(pDC, rButton, SB_VERT, FALSE, bMouseDown && rButton.PtInRect(ptCursor), crParentBackColor);
	
	pDC->RestoreDC(nDC);
}

void CSkinCtrl::DrawSpinButton(CDC* pDC, CRect rButton, LPPOINT pCursor, BOOL bVert, COLORREF crParentBackColor)
{
	// pressed?
	CPoint ptCursor;
	
	BOOL bMouseDown = (GetAsyncKeyState(MK_LBUTTON) & 0x8000);
	
	if (bMouseDown)
	{
		if (!pCursor)
			GetCursorPos(&ptCursor);
		else
			ptCursor = *pCursor;
	}

	CDC dcMem;
	dcMem.CreateCompatibleDC(pDC);
	
	CRect rMem(rButton);
	ptCursor.Offset(-rMem.TopLeft());
	rMem.OffsetRect(-rMem.TopLeft());
	
	CBitmap bmp;
	bmp.CreateCompatibleBitmap(pDC, rButton.Width(), rButton.Height());
	CBitmap* pOldBM = dcMem.SelectObject(&bmp);

	// draw left/up arrow
	CRect rHalf = rMem;

	if (bVert)
		rHalf.bottom = (rHalf.top + rHalf.bottom) / 2;
	else
		rHalf.right = (rHalf.left + rHalf.right) / 2;

	BOOL bDown = bMouseDown && rHalf.PtInRect(ptCursor);
	DrawScrollbarButton(&dcMem, rHalf, bVert ? SB_VERT : SB_HORZ, TRUE, bDown, crParentBackColor, TRUE);

	// draw right/down arrow
	if (bVert)
	{
		rHalf.top = rHalf.bottom;
		rHalf.bottom = rMem.bottom;
	}
	else
	{
		rHalf.left = rHalf.right;
		rHalf.right = rMem.right;
	}

	bDown = bMouseDown && !bDown && rHalf.PtInRect(ptCursor);
	DrawScrollbarButton(&dcMem, rHalf, bVert ? SB_VERT : SB_HORZ, FALSE, bDown, crParentBackColor, TRUE);

	pDC->BitBlt(rButton.left, rButton.top, rButton.Width(), rButton.Height(), &dcMem, 0, 0, SRCCOPY);
	
	dcMem.SelectObject(pOldBM);
	dcMem.DeleteDC();
	bmp.DeleteObject();
}

void CSkinCtrl::DrawPushButton(CDC* pDCMem, CRect rButton, int nState, int nCorner, COLORREF crParentBackColor, BOOL bClipLeft, BOOL bClipRight)
{
	int nEdge = (nState == IM_DOWN) ? SKCS_CLIENTEDGE : SKCS_BTNEDGE;
	int nClipping = (bClipLeft ? ISKCR_CLIPLEFT : 0) | (bClipRight ? ISKCR_CLIPRIGHT : 0);

	if (!s_pRenderer || !s_pRenderer->Draw3dRect(pDCMem, rButton, nEdge, nState, GetBkgndColor(), nClipping))
	{
		COLORREF crBackColor = (nState == IM_HOT || nState == IM_DOWN) ? 
							CRoundCorner::Lighter(GetBkgndColor(), 0.05f) : GetBkgndColor();

		if (bClipLeft && bClipRight)
			pDCMem->FillSolidRect(rButton, crBackColor);
		else
		{
			if (crParentBackColor != -1)
				pDCMem->FillSolidRect(rButton, crParentBackColor);
			
			pDCMem->SelectStockObject(NULL_PEN);
			CBrush* pOldBr = pDCMem->SelectObject(GetColorBrush(crBackColor));
			
			pDCMem->RoundRect(rButton.left, rButton.top, rButton.right + 1, rButton.bottom + 1, 
				nCorner * 2, nCorner * 2);
			
			pDCMem->SelectObject(pOldBr);
			
			// clipping
			if (bClipLeft)
				pDCMem->FillSolidRect(rButton.left, rButton.top, nCorner, rButton.Height(), crBackColor);
			
			else if (bClipRight)
				pDCMem->FillSolidRect(rButton.right - nCorner, rButton.top, nCorner, rButton.Height(), crBackColor);
		}
		
		// Draw the raised/sunken edges of the button (unless flat)
		DWORD dwCorners = (bClipLeft ? 0 : RC_LEFT) | (bClipRight ? 0 : RC_RIGHT);
		DWORD dwStyle = RC_EDGES | RC_THIN | (nState == IM_DOWN ? RC_DOWN : RC_UP);

		Draw3dEdge(pDCMem, rButton, nCorner, nEdge, dwStyle, nClipping);
	}
}

void CSkinCtrl::DrawPushButton(CDC* pDCMem, CRect rButton, CBitmap* pBMLeft, CBitmap* pBMMid, CBitmap* pBMRight, COLORREF crParentBackColor, COLORREF crMask)
{
	ASSERT (pBMLeft && pBMLeft->GetSafeHandle() && 
			pBMMid && pBMMid->GetSafeHandle() && 
			pBMRight && pBMRight->GetSafeHandle());

	if (!(pBMLeft && pBMLeft->GetSafeHandle() && 
			pBMMid && pBMMid->GetSafeHandle() && 
			pBMRight && pBMRight->GetSafeHandle()))
	{
		return;
	}

	CRect rMid = rButton, rBitmap;
	
	if (crMask != -1 && crParentBackColor != -1)
		pDCMem->FillSolidRect(rButton, crParentBackColor);
	
	CBitmap* pOld = NULL;
	CDC dcMem2;
	dcMem2.CreateCompatibleDC(pDCMem); // to hold the bitmaps

	// left part of button
	BITMAP bm;
	pBMLeft->GetBitmap(&bm);

	rBitmap.SetRect(rButton.left, 
					rButton.top, 
					min(rButton.left + bm.bmWidth, rButton.left + rButton.Width() / 2), 
					rButton.bottom);

	rMid.left = rBitmap.right;

	pOld = dcMem2.SelectObject(pBMLeft);
	DrawPushButtonBitmap(pDCMem, &dcMem2, rBitmap, pBMLeft, FALSE, crMask);
	dcMem2.SelectObject(pOld);

	// right part of button
	pBMRight->GetBitmap(&bm);

	rBitmap.SetRect(max(rButton.right - bm.bmWidth, rButton.right - rButton.Width() / 2), 
					rButton.top, 
					rButton.right, 
					rButton.bottom);
	rMid.right = rBitmap.left;
	
	pOld = dcMem2.SelectObject(pBMRight);
	DrawPushButtonBitmap(pDCMem, &dcMem2, rBitmap, pBMRight, FALSE, crMask);
	dcMem2.SelectObject(pOld);
	
	// middle part of button
	pBMMid->GetBitmap(&bm);
	
	pOld = dcMem2.SelectObject(pBMMid);
	DrawPushButtonBitmap(pDCMem, &dcMem2, rMid, pBMMid, TRUE, crMask);
	dcMem2.SelectObject(pOld);
		
	dcMem2.DeleteDC();
}

void CSkinCtrl::DrawPushButtonBitmap(CDC* pDCMem, CDC* pDCMem2, CRect rBitmap, CBitmap* pBitmap, BOOL bMid, COLORREF crMask)
{
	BITMAP bm;
	pBitmap->GetBitmap(&bm);

	// normally buttons are stretched horizontally but not vertically which is
	// why we require left:mid:right bitmaps.

	// however, we need to be able to handle a vertically stretched button 
	// without distorting the bitmap (> bitmap height)

	CBitmap* pOld = pDCMem2->SelectObject(pBitmap);

	if (rBitmap.Height() == bm.bmHeight)
	{
		CSkinBase::BitBlt(pDCMem, rBitmap.left, rBitmap.top, rBitmap.Width(), rBitmap.Height(), 
								pDCMem2, 0, 0, SRCCOPY, crMask);
	}
	else if (rBitmap.Height() < bm.bmHeight)
	{
		CSkinBase::StretchBlt(pDCMem, rBitmap.left, rBitmap.top, rBitmap.Width(), rBitmap.Height(), 
								pDCMem2, 0, 0, bm.bmWidth, bm.bmHeight, SRCCOPY, crMask);
	}
	else // split the bitmap vertically and stretch the middle few pixels
	{
		int nMid = 2 + bm.bmHeight % 2;
		int nTop = bm.bmHeight / 2 - 1;
		int nBottom = bm.bmHeight - nTop - nMid;

		// top
		CSkinBase::StretchBlt(pDCMem, rBitmap.left, rBitmap.top, 
							bMid ? rBitmap.Width() : bm.bmWidth, nTop, 
							pDCMem2, 0, 0, bm.bmWidth, nTop, SRCCOPY, crMask);

		// mid
		CSkinBase::StretchBlt(pDCMem, rBitmap.left, rBitmap.top + nTop, 
							bMid ? rBitmap.Width() : bm.bmWidth, rBitmap.Height() - (nTop + nBottom), 
							pDCMem2, 0, nTop, bm.bmWidth, nMid, SRCCOPY, crMask);

		// bottom
		CSkinBase::StretchBlt(pDCMem, rBitmap.left, rBitmap.bottom - nBottom, 
							bMid ? rBitmap.Width() : bm.bmWidth, nBottom, 
							pDCMem2, 0, nTop + nMid, bm.bmWidth, nBottom, SRCCOPY, crMask);
	}
}

void CSkinCtrl::CalcTextRect(CDC* pDC, CString sText, CRect& rText, UINT nAlign)
{
	CRect rCalc(rText);

	UINT nVAlign = (nAlign & (DT_VCENTER | DT_TOP | DT_BOTTOM));
	nAlign &= ~(DT_VCENTER | DT_TOP | DT_BOTTOM);

	int nHeight = pDC->DrawText(sText, rCalc, nAlign | DT_CALCRECT);

	if (rText.Height() > nHeight)
	{
		if (nVAlign & DT_VCENTER)
			rText.DeflateRect(0, (rText.Height() - nHeight) / 2);

		else if (nVAlign & DT_BOTTOM)
			rText.top = rText.bottom - nHeight;

		else // top
			rText.bottom = rText.top + nHeight;
	}

	if (rText.Width() > rCalc.Width())
	{
		if (nAlign & DT_CENTER)
			rText.DeflateRect((rText.Width() - rCalc.Width()) / 2, 0);

		else if (nAlign & DT_RIGHT)
			rText.left = rText.right - rCalc.Width();

		else // left
			rText.right = rText.left + rCalc.Width();
	}
}

COLORREF CSkinCtrl::GetParentBkgndColor()
{
	HWND hParent = GetParent();

	if (!hParent)
		return GetColor(COLOR_3DFACE);

	CSkinCtrl* pSkin = CSkinCtrlMgr::Instance().GetSkinCtrl(hParent);
	
	// if the parent is not skinned then return 3dface
	if (!pSkin)
		return GetColor(COLOR_3DFACE);

	else // retur the parent skins backcolor
		return pSkin->GetBkgndColor();
}

CWnd* CSkinCtrl::GetChildWnd(LPCTSTR szClass)
{
	CWnd* pChild = GetCtrl()->GetWindow(GW_CHILD); 
	
	while (pChild)    
	{
		if (CWinClasses::IsClass(*pChild, szClass))
			return pChild;
		
		pChild = pChild->GetNextWindow();
	}
	
	return NULL;
}

void CSkinCtrl::ClipChildren(CDC* pDC)
{
	CWnd* pChild = GetCtrl()->GetWindow(GW_CHILD); 
	
	while (pChild)    
	{
		if (pChild->IsWindowVisible())
		{
			CString sClassName(CWinClasses::GetClass(*pChild));
			BOOL bChildOK = TRUE;
			
			// flat toolbars
			if (sClassName.CompareNoCase(WC_TOOLBAR) == 0)
			{
				UINT uStyle = pChild->GetStyle();
				
				if (uStyle & TBSTYLE_FLAT)
					bChildOK = FALSE;
			}
			
			// group buttons
			else if (sClassName.CompareNoCase(WC_BUTTON) == 0)
			{
				UINT uStyle = pChild->GetStyle();
				
				if ((uStyle & 0x0F) == BS_GROUPBOX)
					bChildOK = FALSE;
			}
			
			// static frames
			else if (sClassName.CompareNoCase(WC_STATIC) == 0)
			{
				UINT uStyle = pChild->GetStyle();
				
				if ((uStyle & SS_BLACKFRAME) || (uStyle & SS_GRAYFRAME) || (uStyle & SS_WHITEFRAME))
					bChildOK = FALSE;
			}
			
			// dialogs
			else if (sClassName.CompareNoCase(WC_DIALOGBOX) == 0)
			{
				bChildOK = FALSE;
			}
			
			// we've got a valid window so clip it
			if (bChildOK)
			{
				CRect rChild;
				pChild->GetWindowRect(&rChild);
				pChild->ScreenToClient(&rChild);
				pChild->MapWindowPoints(GetCWnd(), rChild);

				pDC->ExcludeClipRect(&rChild);
			}
		}
		
		pChild = pChild->GetNextWindow();
	}
}

LRESULT CALLBACK CSkinCtrl::MsgWndProc(int code, WPARAM wp, LPARAM lp)
{
	if (g_pCtrl)
	{
		MSG& msg = *((MSG*)lp);
		
		if (g_pCtrl->OnMsgWndProc(msg))
			return TRUE;
	}
	
	// else
	return CallNextHookEx(g_hMsgHook, code, wp, lp);
}

BOOL CSkinCtrl::OnMsgWndProc(MSG& msg)
{
	ASSERT_VALID(GetCWnd());
	
	int code = msg.message;
	
	if (!(GetAsyncKeyState(MK_LBUTTON) & 0x8000))
	{
		// uninstall hook.
		::UnhookWindowsHookEx(g_hMsgHook);
		g_hMsgHook = NULL;
		g_pCtrl = NULL;
		g_nScrollbar = -1;
	}
	
	SendMessage(WM_NCPAINT);
	CSkinCtrlMgr::Instance().UpdateCursorPos();
	
	return FALSE; // not handled
}

////////////////////////////////////////////////////////////////////////////////////////////////
// static helpers because friend status is not transferable

CSkinCtrl* CSkinCtrl::GetSkinCtrl(CWnd* pCtrl) 
{ 
	return GetSkinCtrl(*pCtrl); 
}

CSkinCtrl* CSkinCtrl::GetSkinCtrl(HWND hCtrl) 
{ 
	return CSkinCtrlMgr::Instance().GetSkinCtrl(hCtrl); 
}

BOOL CSkinCtrl::Skin(HWND hCtrl)
{ 
	return CSkinCtrlMgr::Instance().Skin(hCtrl); 
}

LRESULT CSkinCtrl::DoCustomDraw(HWND hCtrl, NMHDR* pNMHDR)
{
	return CSkinCtrlMgr::Instance().DoCustomDraw(hCtrl, pNMHDR); 
}

LRESULT CSkinCtrl::DoNotifyReflect(HWND hCtrl, NMHDR* pNMHDR, LRESULT lrParent)
{
	return CSkinCtrlMgr::Instance().DoNotifyReflect(hCtrl, pNMHDR, lrParent); 
}

void CSkinCtrl::DoNotifyReflect(HWND hCtrl, UINT uNotify, LRESULT lrParent)
{
	CSkinCtrlMgr::Instance().DoNotifyReflect(hCtrl, uNotify, lrParent); 
}

HBRUSH CSkinCtrl::DoCtlColor(HWND hCtrl, CDC* pDC)
{
	return CSkinCtrlMgr::Instance().DoCtlColor(hCtrl, pDC); 
}

void CSkinCtrl::DoScroll(HWND hCtrl, UINT nSBCode, UINT nPos, BOOL bHorz)
{
	 CSkinCtrlMgr::Instance().DoScroll(hCtrl, nSBCode, nPos, bHorz); 
}

////////////////////////////////////////////////////////////////////////////////////////////////

void CSkinCtrl::GetCursorPos(LPPOINT pCursor)
{
	ASSERT (pCursor);
	CRect rWindow;

	CSkinCtrlMgr::Instance().GetCursorPos(pCursor);
	GetWindowRect(rWindow);

	pCursor->x -= rWindow.left;
	pCursor->y -= rWindow.top;
}

BOOL CSkinCtrl::DelayRedraw(int nDelay)
{
	return CDelayRedraw::Start(GetHwnd(), nDelay);
}

CFont* CSkinCtrl::GetFont(int nFont)
{
	if (nFont == SBFONT_MARLETT)
	{
		if (!s_fontMarlett2.GetSafeHandle())
		{
			VERIFY(s_fontMarlett2.CreateFont(SCROLLCX - 3, 0, 0, 0,
					FW_THIN, 0, 0, 0, SYMBOL_CHARSET, 0, 0, 0, 0, _T("Marlett")));
		}

		return &s_fontMarlett2;
	}

	// else
	return m_pGlobals ? m_pGlobals->GetFont(nFont) : CSkinGlobals::GetFontSt(nFont);
}

CBrush* CSkinCtrl::GetColorBrush(COLORREF color)
{
	return m_pGlobals ? m_pGlobals->GetColorBrush(color) : CSkinGlobals::GetColorBrushSt(color);
}

CPen* CSkinCtrl::GetColorPen(COLORREF color, int nWidth)
{
	return m_pGlobals ? m_pGlobals->GetColorPen(color, nWidth) : CSkinGlobals::GetColorPenSt(color, nWidth);
}

CBrush* CSkinCtrl::GetColorBrush(int nColor)
{
	return m_pGlobals ? m_pGlobals->GetColorBrush(nColor) : CSkinGlobals::GetColorBrushSt(nColor);
}

CPen* CSkinCtrl::GetColorPen(int nColor, int nWidth)
{
	return m_pGlobals ? m_pGlobals->GetColorPen(nColor, nWidth) : CSkinGlobals::GetColorPenSt(nColor, nWidth);
}

CBitmap* CSkinCtrl::GetControlBitmap(int nItem, int nState, COLORREF* pMask, int nAltItem)
{
	return m_pGlobals ? m_pGlobals->GetControlBitmap(nItem, nState, pMask, nAltItem) : NULL;
}

void CSkinCtrl::AlignRect(CRect& rect, const CRect& rContainer, UINT nAlignment)
{
	CSize size = rect.Size();
	rect = rContainer;

	// vert align
	if (nAlignment & DT_VCENTER)
		rect.DeflateRect(0, (rect.Height() - size.cy) / 2);

	else if (nAlignment & DT_BOTTOM)
		rect.top = rect.bottom - size.cy;

	else // top
		rect.bottom = rect.top + size.cy;

	// horz align
	if (nAlignment & DT_CENTER)
		rect.DeflateRect((rect.Width() - size.cx) / 2, 0);

	else if (nAlignment & DT_RIGHT)
		rect.left = rect.right - size.cx;

	else // left
		rect.right = rect.left + size.cx;
}
