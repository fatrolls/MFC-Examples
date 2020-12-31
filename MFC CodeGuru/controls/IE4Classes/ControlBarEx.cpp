#include "stdafx.h"
#include "ControlBarEx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CControlBarEx

BEGIN_MESSAGE_MAP(CControlBarEx, CControlBar)
	//{{AFX_MSG_MAP(CControlBarEx)
	ON_WM_PAINT()
	ON_WM_WINDOWPOSCHANGING()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CControlBarEx::SetBorders(int cxLeft, int cyTop, int cxRight, int cyBottom)
{
  ASSERT(cxLeft >= 0);
  ASSERT(cyTop >= 0);
  ASSERT(cxRight >= 0);
  ASSERT(cyBottom >= 0);

  m_cxLeftBorder = cxLeft;
  m_cyTopBorder = cyTop;
  m_cxRightBorder = cxRight;
  m_cyBottomBorder = cyBottom;
}

LRESULT CControlBarEx::WindowProc(UINT nMsg, WPARAM wParam, LPARAM lParam)
{
  ASSERT_VALID(this);

  LRESULT lResult;
  switch (nMsg)
  {
  case WM_NOTIFY:
  case WM_COMMAND:
  case WM_DRAWITEM:
  case WM_MEASUREITEM:
  case WM_DELETEITEM:
  case WM_COMPAREITEM:
  case WM_VKEYTOITEM:
  case WM_CHARTOITEM:
    // send these messages to the owner if not handled
    if (OnWndMsg(nMsg, wParam, lParam, &lResult))
      return lResult;
    else
    {
      // try owner next
      lResult = GetOwner()->SendMessage(nMsg, wParam, lParam);

      // special case for TTN_NEEDTEXTA and TTN_NEEDTEXTW
      if(nMsg == WM_NOTIFY)
      {
        NMHDR* pNMHDR = (NMHDR*)lParam;
        if (pNMHDR->code == TTN_NEEDTEXTA || pNMHDR->code == TTN_NEEDTEXTW)
        {
          TOOLTIPTEXTA* pTTTA = (TOOLTIPTEXTA*)pNMHDR;
          TOOLTIPTEXTW* pTTTW = (TOOLTIPTEXTW*)pNMHDR;
          if ((pNMHDR->code == TTN_NEEDTEXTA && (!pTTTA->lpszText || !*pTTTA->lpszText)) ||
            (pNMHDR->code == TTN_NEEDTEXTW && (!pTTTW->lpszText || !*pTTTW->lpszText)))
          {
            // not handled by owner, so let bar itself handle it
            lResult = CWnd::WindowProc(nMsg, wParam, lParam);
          }
        }
      }
      return lResult;
    }
  }

  // otherwise, just handle in default way
  lResult = CWnd::WindowProc(nMsg, wParam, lParam);
  return lResult;
}

void CControlBarEx::OnWindowPosChanging(LPWINDOWPOS lpWndPos)
{
  // WINBUG: We call DefWindowProc here instead of CWnd::OnWindowPosChanging
  //  (which calls CWnd::Default, which calls through the super wndproc)
  //  because certain control bars that are system implemented (such as
  //  CToolBar with TBSTYLE_FLAT) do not implement WM_WINDOWPOSCHANGING
  //  correctly, causing repaint problems.  This code bypasses that whole
  //  mess.
  ::DefWindowProc(m_hWnd, WM_WINDOWPOSCHANGING, 0, (LPARAM)lpWndPos);

  if (lpWndPos->flags & SWP_NOSIZE)
    return;

  // invalidate borders on the right
  CRect rect;
  GetWindowRect(&rect);
  CSize sizePrev = rect.Size();
  int cx = lpWndPos->cx;
  int cy = lpWndPos->cy;
  if (cx != sizePrev.cx && (m_dwStyle & CBRS_BORDER_RIGHT))
  {
    rect.SetRect(cx-afxData.cxBorder2, 0, cx, cy);
    InvalidateRect(&rect);
    rect.SetRect(sizePrev.cx-afxData.cxBorder2, 0, sizePrev.cx, cy);
    InvalidateRect(&rect);
  }

  // invalidate borders on the bottom
  if (cy != sizePrev.cy && (m_dwStyle & CBRS_BORDER_BOTTOM))
  {
    rect.SetRect(0, cy-afxData.cyBorder2, cx, cy);
    InvalidateRect(&rect);
    rect.SetRect(0, sizePrev.cy-afxData.cyBorder2, cx, sizePrev.cy);
    InvalidateRect(&rect);
  }
}

void CControlBarEx::OnPaint()
{
  // background is already filled in gray
  CPaintDC dc(this);

  // erase background now
  if (IsVisible())
    DoPaint(&dc);       // delegate to paint helper
}

void CControlBarEx::EraseNonClient()
{
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
  DrawBorders(&dc, rectWindow);

  // erase parts not drawn
  dc.IntersectClipRect(rectWindow);
  SendMessage(WM_ERASEBKGND, (WPARAM)dc.m_hDC);

  // draw gripper in non-client area
  DrawGripper(&dc, rectWindow);
}

void CControlBarEx::DoPaint(CDC* pDC)
{
  ASSERT_VALID(this);
  ASSERT_VALID(pDC);

  // paint inside client area
  CRect rect;
  GetClientRect(rect);
  DrawBorders(pDC, rect);
  DrawGripper(pDC, rect);
}

#define CX_GRIPPER  3
#define CY_GRIPPER  3
#define CX_BORDER_GRIPPER 2
#define CY_BORDER_GRIPPER 2

void CControlBarEx::DrawGripper(CDC* pDC, const CRect& rect)
{
  // only draw the gripper if not floating and gripper is specified
  if ((m_dwStyle & (CBRS_GRIPPER|CBRS_FLOATING)) == CBRS_GRIPPER)
  {
    // draw the gripper in the border
    if (m_dwStyle & CBRS_ORIENT_HORZ)
    {
      pDC->Draw3dRect(rect.left+CX_BORDER_GRIPPER,
        rect.top+m_cyTopBorder,
        CX_GRIPPER, rect.Height()-m_cyTopBorder-m_cyBottomBorder,
        afxData.clrBtnHilite, afxData.clrBtnShadow);
    }
    else
    {
      pDC->Draw3dRect(rect.left+m_cyTopBorder,
        rect.top+CY_BORDER_GRIPPER,
        rect.Width()-m_cyTopBorder-m_cyBottomBorder, CY_GRIPPER,
        afxData.clrBtnHilite, afxData.clrBtnShadow);
      GdiFlush();
    }
  }
}

// input CRect should be client rectangle size
void CControlBarEx::CalcInsideRect(CRect& rect, BOOL bHorz) const
{
  ASSERT_VALID(this);
  DWORD dwStyle = m_dwStyle;

  if (dwStyle & CBRS_BORDER_LEFT)
    rect.left += afxData.cxBorder2;
  if (dwStyle & CBRS_BORDER_TOP)
    rect.top += afxData.cyBorder2;
  if (dwStyle & CBRS_BORDER_RIGHT)
    rect.right -= afxData.cxBorder2;
  if (dwStyle & CBRS_BORDER_BOTTOM)
    rect.bottom -= afxData.cyBorder2;

  // inset the top and bottom.
  if (bHorz)
  {
    rect.left += m_cxLeftBorder;
    rect.top += m_cyTopBorder;
    rect.right -= m_cxRightBorder;
    rect.bottom -= m_cyBottomBorder;
    if ((m_dwStyle & (CBRS_GRIPPER|CBRS_FLOATING)) == CBRS_GRIPPER)
      rect.left += CX_BORDER_GRIPPER+CX_GRIPPER+CX_BORDER_GRIPPER;
  }
  else
  {
    rect.left += m_cyTopBorder;
    rect.top += m_cxLeftBorder;
    rect.right -= m_cyBottomBorder;
    rect.bottom -= m_cxRightBorder;
    if ((m_dwStyle & (CBRS_GRIPPER|CBRS_FLOATING)) == CBRS_GRIPPER)
      rect.top += CY_BORDER_GRIPPER+CY_GRIPPER+CY_BORDER_GRIPPER;
  }
}

/////////////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNAMIC(CControlBarEx, CControlBar)

/////////////////////////////////////////////////////////////////////////////
