
#include "StdAfx.h"
#include "SkinWindow.h"
#include "Resource.h"

#define BORDER_WIDTH GetSystemMetrics(SM_CXSIZEFRAME)
#define SIZEBOX_WIDTH GetSystemMetrics(SM_CXSIZE)

CSkinImage CSkinWindow::m_ImageDefSkin;

CSkinWindow::CSkinWindow()
{
	m_rcPart[SKINPART_TOP_LEFT].SetRect(0, 0, 3, 27);
	m_rcPart[SKINPART_TOP].SetRect(3, 0, 4, 27);
	m_rcPart[SKINPART_TOP_RIGHT].SetRect(4, 0, 7, 27);
	m_rcPart[SKINPART_IA_TOP_LEFT].SetRect(7, 0, 10, 27);
	m_rcPart[SKINPART_IA_TOP].SetRect(10, 0, 11, 27);
	m_rcPart[SKINPART_IA_TOP_RIGHT].SetRect(11, 0, 14, 27);

	m_rcPart[SKINPART_LEFT_TOP].SetRect(0, 27, 3, 28);
	m_rcPart[SKINPART_LEFT].SetRect(0, 28, 3, 29);
	m_rcPart[SKINPART_LEFT_BOTTOM].SetRect(0, 29, 3, 30);
	m_rcPart[SKINPART_IA_LEFT_TOP].SetRect(7, 27, 10, 28);
	m_rcPart[SKINPART_IA_LEFT].SetRect(7, 28, 10, 29);
	m_rcPart[SKINPART_IA_LEFT_BOTTOM].SetRect(7, 29, 10, 30);

	m_rcPart[SKINPART_RIGHT_TOP].SetRect(4, 27, 7, 28);
	m_rcPart[SKINPART_RIGHT].SetRect(4, 28, 7, 29);
	m_rcPart[SKINPART_RIGHT_BOTTOM].SetRect(4, 29, 7, 30);
	m_rcPart[SKINPART_IA_RIGHT_TOP].SetRect(11, 27, 14, 28);
	m_rcPart[SKINPART_IA_RIGHT].SetRect(11, 28, 14, 29);
	m_rcPart[SKINPART_IA_RIGHT_BOTTOM].SetRect(11, 29, 14, 30);

	m_rcPart[SKINPART_BOTTOM_LEFT].SetRect(0, 30, 3, 33);
	m_rcPart[SKINPART_BOTTOM].SetRect(3, 30, 4, 33);
	m_rcPart[SKINPART_BOTTOM_RIGHT].SetRect(4, 30, 7, 33);
	m_rcPart[SKINPART_IA_BOTTOM_LEFT].SetRect(7, 30, 10, 33);
	m_rcPart[SKINPART_IA_BOTTOM].SetRect(10, 30, 11, 33);
	m_rcPart[SKINPART_IA_BOTTOM_RIGHT].SetRect(11, 30, 14, 33);

	m_rcPart[SKINPART_IA_MINIMIZE].SetRect(14, 0, 42, 21);
	m_rcPart[SKINPART_MINIMIZE].SetRect(42, 0, 70, 21);
	m_rcPart[SKINPART_MINIMIZE_HOT].SetRect(70, 0, 98, 21);
	m_rcPart[SKINPART_MINIMIZE_DOWN].SetRect(98, 0, 126, 21);

	m_rcPart[SKINPART_IA_MAXIMIZE].SetRect(14, 21, 40, 42);
	m_rcPart[SKINPART_MAXIMIZE].SetRect(42, 21, 68, 42);
	m_rcPart[SKINPART_MAXIMIZE_HOT].SetRect(70, 21, 96, 42);
	m_rcPart[SKINPART_MAXIMIZE_DOWN].SetRect(98, 21, 124, 42);

	m_rcPart[SKINPART_IA_RESTORE].SetRect(14, 42, 40, 63);
	m_rcPart[SKINPART_RESTORE].SetRect(42, 42, 68, 63);
	m_rcPart[SKINPART_RESTORE_HOT].SetRect(70, 42, 96, 63);
	m_rcPart[SKINPART_RESTORE_DOWN].SetRect(98, 42, 124, 63);

	m_rcPart[SKINPART_IA_CLOSE].SetRect(14, 63, 42, 84);
	m_rcPart[SKINPART_CLOSE].SetRect(42, 63, 70, 84);
	m_rcPart[SKINPART_CLOSE_HOT].SetRect(70, 63, 98, 84);
	m_rcPart[SKINPART_CLOSE_DOWN].SetRect(98, 63, 126, 84);

	m_rcAnchor[SKINANCHOR_SYSICON].SetRect(6, 4, 24, 22);
	m_rcAnchor[SKINANCHOR_MINIMIZE].SetRect(-86, 1, -58, 22);
	m_rcAnchor[SKINANCHOR_MAXIMIZE].SetRect(-58, 1, -32, 22);
	m_rcAnchor[SKINANCHOR_CLOSE].SetRect(-32, 1, -4, 22);

	m_rcCaption.SetRect(26, 4, 526, 24);

	m_rcResize.left = BORDER_WIDTH;
	m_rcResize.top = BORDER_WIDTH;
	m_rcResize.right = BORDER_WIDTH;
	m_rcResize.bottom = BORDER_WIDTH;

	m_crCaptionText = RGB(51, 51, 51);
	m_crCaptionInactive	= RGB(128, 128, 128);

	m_nHoverAnchor = 0;
	m_nDownAnchor = 0;

	m_bTracking = FALSE;
	m_bIsMaximizeEnable = FALSE;
	m_bIsMinimzseEnable = FALSE;

	if (!m_ImageDefSkin.IsValid())
	{
		HMODULE hModule = GetModuleHandle(SKIN_CONTROLS_DLL_NAME);
		m_ImageDefSkin.LoadFromResource(hModule, MAKEINTRESOURCE(IDB_DIALOG));
	}
}

CSkinWindow::~CSkinWindow()
{
}

// 初始配置
void CSkinWindow::InitWindow(CWnd* pWnd)
{
	pWnd->ModifyStyle(WS_CAPTION, 0);

	m_fnCaption.CreateFont(
		-12, // nHeight 
		0,          // nWidth 
		0,          // nEscapement 
		0,          // nOrientation 
		FW_BOLD,    // nWeight 
		FALSE,      // bItalic 
		FALSE,      // bUnderline 
		0,          // cStrikeOut 
		ANSI_CHARSET, // nCharSet 
		OUT_DEFAULT_PRECIS, // nOutPrecision 
		CLIP_DEFAULT_PRECIS, // nClipPrecision 
		DEFAULT_QUALITY, // nQuality 
		DEFAULT_PITCH|FF_SWISS, // nPitchAndFamily 
		TEXT("宋体"));

	m_bIsMaximizeEnable = !!(pWnd->GetStyle()&WS_MAXIMIZEBOX);
	m_bIsMinimzseEnable = !!(pWnd->GetStyle()&WS_MINIMIZEBOX);

	if (m_bIsMinimzseEnable && !m_bIsMaximizeEnable) m_rcAnchor[SKINANCHOR_MINIMIZE].SetRect(-60, 1, -32, 22);
}

void CSkinWindow::OnNcCalcSize(CWnd* pWnd, BOOL bCalcValidRects, NCCALCSIZE_PARAMS FAR* lpncsp)
{
	CRect rcAdjust(0, 0, 0, 0);
	RECT& rect = lpncsp->rgrc[0];

	rcAdjust.top = max(rcAdjust.top, m_rcPart[SKINPART_TOP_LEFT].Height());
	rcAdjust.top = max(rcAdjust.top, m_rcPart[SKINPART_TOP].Height());
	rcAdjust.top = max(rcAdjust.top, m_rcPart[SKINPART_TOP_RIGHT].Height());

	rcAdjust.left = max(rcAdjust.left, m_rcPart[SKINPART_LEFT].Width());

	rcAdjust.right = max(rcAdjust.right, m_rcPart[SKINPART_RIGHT].Width());

	rcAdjust.bottom = max(rcAdjust.bottom, m_rcPart[SKINPART_BOTTOM_LEFT].Height());
	rcAdjust.bottom = max(rcAdjust.bottom, m_rcPart[SKINPART_BOTTOM].Height());
	rcAdjust.bottom = max(rcAdjust.bottom, m_rcPart[SKINPART_BOTTOM_RIGHT].Height());

	rect.left += rcAdjust.left;
	rect.top += rcAdjust.top;
	rect.right -= rcAdjust.right;
	rect.bottom	-= rcAdjust.bottom;
}

LRESULT CSkinWindow::OnNcHitTest(CWnd* pWnd, CPoint point, BOOL bResizable)
{
	CRect rcWnd;
	CRect rcAnchor;
	int nPointX = 0;

	pWnd->GetWindowRect(&rcWnd);
	CSkinImage* pImage = NULL;
	if (m_ImageSkin.IsValid()) pImage = &m_ImageSkin;
	else pImage = &m_ImageDefSkin;

	ResolveAnchor(rcWnd, rcAnchor, SKINANCHOR_SYSICON);
	if(::PtInRect(&rcAnchor, point))
	{
		return HTSYSMENU;
	}

	if(m_bIsMinimzseEnable)
	{
		ResolveAnchor(rcWnd, rcAnchor, SKINANCHOR_MINIMIZE);
		if(::PtInRect(&rcAnchor, point))
		{
			return HTREDUCE;
		}
	}

	if(m_bIsMaximizeEnable)
	{
		ResolveAnchor(rcWnd, rcAnchor, SKINANCHOR_MAXIMIZE);
		if(::PtInRect(&rcAnchor, point))
		{
			return HTZOOM;
		}
	}

	ResolveAnchor(rcWnd, rcAnchor, SKINANCHOR_CLOSE);
	if(::PtInRect(&rcAnchor, point))
	{
		return HTCLOSE;
	}

	if(bResizable && !pWnd->IsZoomed())
	{
		if(point.x>=rcWnd.right-SIZEBOX_WIDTH && point.y>=rcWnd.bottom-SIZEBOX_WIDTH)
		{
			return HTBOTTOMRIGHT;
		}

		if(point.x < rcWnd.left+m_rcResize.left)
		{
			if(point.y < rcWnd.top+m_rcResize.top)
			{
				return HTTOPLEFT;
			}
			else if(point.y >= rcWnd.bottom-m_rcResize.bottom)
			{
				return HTBOTTOMLEFT;
			}
			else
			{
				return HTLEFT;
			}
		}
		else if(point.x >= rcWnd.right-m_rcResize.right)
		{
			if(point.y < rcWnd.top+m_rcResize.top)
			{
				return HTTOPRIGHT;
			}
			else if(point.y >= rcWnd.bottom-m_rcResize.bottom)
			{
				return HTBOTTOMRIGHT;
			}
			else
			{
				return HTRIGHT;
			}
		}
		else if(point.y < rcWnd.top+m_rcResize.top)
		{
			if(point.x < rcWnd.left+m_rcResize.left)
			{
				return HTTOPLEFT;
			}
			else if(point.x >= rcWnd.right-m_rcResize.right)
			{
				return HTTOPRIGHT;
			}
			return HTTOP;
		}
		else if(point.y >= rcWnd.bottom-m_rcResize.bottom)
		{
			if(point.x < rcWnd.left+m_rcResize.left)
			{
				return HTBOTTOMLEFT;
			}
			else if(point.x >= rcWnd.right-m_rcResize.right)
			{
				return HTBOTTOMRIGHT;
			}
			return HTBOTTOM;
		}
	}

	if(point.y < rcWnd.top+m_rcPart[SKINPART_TOP].Height())
	{
		return HTCAPTION;
	}

	return rcWnd.PtInRect(point) ? HTCLIENT : HTBORDER;
}

void CSkinWindow::OnNcPaint(CWnd* pWnd)
{
	CDC* pWndDC = pWnd->GetWindowDC();
	Paint(pWnd, pWndDC);
	pWnd->ReleaseDC(pWndDC);
}

void CSkinWindow::OnSetText(CWnd* pWnd)
{
	CDC* pWndDC = pWnd->GetWindowDC();
	Paint(pWnd, pWndDC);
	pWnd->ReleaseDC(pWndDC);
}

void CSkinWindow::OnSize(CWnd* pWnd)
{
	if(pWnd->IsIconic())
	{
		return;
	}

	pWnd->SetWindowRgn(NULL, FALSE);

	CRect rcWnd;
	pWnd->GetWindowRect(&rcWnd);
	HRGN hRgn = CreateRoundRectRgn(0, 0, rcWnd.Width()+1, rcWnd.Height()+1, 6, 6);
	pWnd->SetWindowRgn(hRgn, TRUE);
	::DeleteObject(hRgn);
}

BOOL CSkinWindow::OnEraseBkgnd(CWnd* pWnd, CDC* pDC)
{
	return TRUE;
}

void CSkinWindow::OnNcMouseMove(CWnd* pWnd, UINT nHitTest, CPoint point)
{
	int	nAnchor	= 0;
	if(nHitTest == HTREDUCE)
	{
		nAnchor = SKINANCHOR_MINIMIZE;
	}
	else if(nHitTest == HTZOOM)
	{
		nAnchor = SKINANCHOR_MAXIMIZE;
	}
	else if(nHitTest == HTCLOSE)
	{
		nAnchor = SKINANCHOR_CLOSE;
	}

	if(m_nDownAnchor && m_nDownAnchor!=nAnchor)
	{
		if((GetAsyncKeyState(VK_LBUTTON)&0x8000) == 0)
		{
			m_nDownAnchor = 0;
		}
		nAnchor = 0;
	}

	if(nAnchor != m_nHoverAnchor)
	{
		m_nHoverAnchor = nAnchor;
		CDC* pWndDC = pWnd->GetWindowDC();
		Paint(pWnd, pWndDC);
		pWnd->ReleaseDC(pWndDC);
	}

	if(!m_bTracking)
	{
		TRACKMOUSEEVENT tme;
		tme.cbSize = sizeof(tme);
		tme.hwndTrack = pWnd->m_hWnd;
		tme.dwFlags = TME_LEAVE|TME_HOVER|TME_NONCLIENT;
		tme.dwHoverTime = 1;
		m_bTracking = _TrackMouseEvent(&tme);
	}
}

void CSkinWindow::OnNcMouseLeave(CWnd* pWnd)
{
	POINT pt = { -1, -1 };
	OnNcMouseMove(pWnd, OnNcHitTest(pWnd, pt, TRUE), pt);

	m_bTracking = FALSE;
}

BOOL CSkinWindow::OnNcLButtonDown(CWnd* pWnd, UINT nHitTest, CPoint point)
{
	int nAnchor = 0;
	if (nHitTest == HTREDUCE) nAnchor = SKINANCHOR_MINIMIZE;
	else if (nHitTest == HTZOOM) nAnchor = SKINANCHOR_MAXIMIZE;
	else if (nHitTest == HTCLOSE) nAnchor = SKINANCHOR_CLOSE;
	else return FALSE;

	m_nHoverAnchor = m_nDownAnchor = nAnchor;

	CDC* pWndDC = pWnd->GetWindowDC();
	Paint(pWnd, pWndDC);
	pWnd->ReleaseDC(pWndDC);

	return TRUE;
}

BOOL CSkinWindow::OnNcLButtonUp(CWnd* pWnd, UINT nHitTest, CPoint point)
{
	if(!m_nDownAnchor)
	{
		return FALSE;
	}

	if(m_nDownAnchor == m_nHoverAnchor)
	{
		switch(m_nDownAnchor)
		{
		case SKINANCHOR_MINIMIZE:
			pWnd->PostMessage(WM_SYSCOMMAND, SC_MINIMIZE, 0);
			break;
		case SKINANCHOR_MAXIMIZE:
			pWnd->PostMessage(WM_SYSCOMMAND, pWnd->IsZoomed() ? SC_RESTORE : SC_MAXIMIZE, 0);
			break;
		case SKINANCHOR_CLOSE:
			pWnd->PostMessage(WM_SYSCOMMAND, SC_CLOSE, 0);
			break;
		}
	}

	m_nHoverAnchor = 0;
	m_nDownAnchor = 0;

	OnNcMouseMove(pWnd, OnNcHitTest(pWnd, point, TRUE), point);

	return FALSE;
}

// 右键松开
BOOL CSkinWindow::OnNcRButtonUp(CWnd* pWnd, UINT nFlags, CPoint point)
{
	if(nFlags == HTCAPTION || nFlags == HTSYSMENU)
	{
		// #define   WM_SYSMENU     0x0313  //   ;Internal
		pWnd->SendMessage(0x0313, 0, MAKELPARAM(point.x, point.y));
	}

	return TRUE;
}

// 激活消息
BOOL CSkinWindow::OnActivateApp(CWnd* pWnd, BOOL bActive, DWORD dwThreadID)
{
	CDC* pWndDC = pWnd->GetWindowDC();
	Paint(pWnd, pWndDC);
	pWnd->ReleaseDC(pWndDC);

	return TRUE;
}

void CSkinWindow::Paint(CWnd* pWnd, CDC* pDC)
{
	CSkinImage* pImage = NULL;
	if (m_ImageSkin.IsValid()) pImage = &m_ImageSkin;
	else pImage = &m_ImageDefSkin;

	CRect rcWnd;
	pWnd->GetWindowRect(&rcWnd);
	OffsetRect(&rcWnd, -rcWnd.left, -rcWnd.top);

	BOOL bActive = ::GetActiveWindow()==pWnd->m_hWnd ? TRUE : FALSE;
	int nPart;
	CRect rcTop, rcLeft, rcRight, rcBottom, rcMiddle;

	// 顶部双缓冲
	rcTop = rcWnd;
	if (bActive==FALSE)
		rcTop.bottom = rcTop.top + m_rcPart[SKINPART_IA_TOP].Height();
	else
		rcTop.bottom = rcTop.top + m_rcPart[SKINPART_TOP].Height();
	rcMiddle = rcTop;
	rcMiddle.OffsetRect(-rcTop.left, -rcTop.top);
	CDC TopBufferDC;
	CBitmap TopBufferBitmap, *pOldTopBitmap = NULL;
	TopBufferDC.CreateCompatibleDC(pDC);
	TopBufferBitmap.CreateCompatibleBitmap(pDC, rcTop.Width(), rcTop.Height());
	pOldTopBitmap = TopBufferDC.SelectObject(&TopBufferBitmap);

	// 上左
	if(bActive==FALSE)
	{
		nPart = SKINPART_IA_TOP_LEFT;
		rcMiddle.left += m_rcPart[nPart].Width();
	}
	else
	{
		nPart = SKINPART_TOP_LEFT;
		rcMiddle.left += m_rcPart[nPart].Width();
	}
	pImage->DrawImage(&TopBufferDC, 0, 0, m_rcPart[nPart].Width(), m_rcPart[nPart].Height(), 
		m_rcPart[nPart].left, m_rcPart[nPart].top, m_rcPart[nPart].Width(), m_rcPart[nPart].Height());

	// 上右
	if(bActive==FALSE)
	{
		nPart = SKINPART_IA_TOP_RIGHT;
		rcMiddle.right -= m_rcPart[nPart].Width();
	}
	else
	{
		nPart = SKINPART_TOP_RIGHT;
		rcMiddle.right -= m_rcPart[nPart].Width();
	}
	pImage->DrawImage(&TopBufferDC, rcTop.right - m_rcPart[nPart].Width(), 0, m_rcPart[nPart].Width(), m_rcPart[nPart].Height(), 
		m_rcPart[nPart].left, m_rcPart[nPart].top, m_rcPart[nPart].Width(), m_rcPart[nPart].Height());

	// 上中
	if(bActive==FALSE)
	{
		nPart = SKINPART_IA_TOP;
	}
	else
	{
		nPart = SKINPART_TOP;
	}
	pImage->DrawImage(&TopBufferDC, rcMiddle.left, 0, rcMiddle.Width(), m_rcPart[nPart].Height(), 
		m_rcPart[nPart].left, m_rcPart[nPart].top, m_rcPart[nPart].Width(), m_rcPart[nPart].Height());

	// 绘制标题栏上的按钮
	BOOL bZoomed = pWnd->IsZoomed();
	CRect rcItem;
	for(int nAnchor=SKINANCHOR_CLOSE; nAnchor>=SKINANCHOR_MINIMIZE; --nAnchor)
	{
		if (nAnchor == SKINANCHOR_MINIMIZE && !m_bIsMinimzseEnable) continue;
		if (nAnchor == SKINANCHOR_MAXIMIZE && !m_bIsMaximizeEnable) continue;
		int nPart = (nAnchor-SKINANCHOR_MINIMIZE)*4 + SKINPART_MINIMIZE;
		if(bZoomed && nAnchor==SKINANCHOR_MAXIMIZE)
		{
			nPart = SKINPART_RESTORE;
		}

		if(bActive==FALSE)
		{
			nPart += 3;
		}
		else
		{
			if(m_nHoverAnchor == nAnchor)
			{
				nPart += (m_nDownAnchor==nAnchor?2:1);
			}
			else
			{
				nPart += (m_nDownAnchor==nAnchor?0:0);
			}
		}

		CRect rcPart = m_rcPart[nPart];
		if (!m_bIsMinimzseEnable && nAnchor == SKINANCHOR_CLOSE)
		{
			rcPart.top += m_rcPart[nPart].Height();
			rcPart.bottom += m_rcPart[nPart].Height();
		}

		ResolveAnchor(rcWnd, rcItem, nAnchor);
		pImage->DrawImage(&TopBufferDC, rcItem.left, rcItem.top, rcPart.Width(), rcPart.Height(),
			rcPart.left, rcPart.top, rcPart.Width(), rcPart.Height());
	}

	// 绘制SysIcon
	HICON hIcon	= NULL;
	hIcon = (HICON)pWnd->SendMessage(WM_GETICON, ICON_SMALL, 0);
	CRect rcIcon;
	ResolveAnchor(rcWnd, rcIcon, SKINANCHOR_SYSICON);
	DrawIconEx(TopBufferDC.m_hDC, rcIcon.left, rcIcon.top, hIcon,
		m_rcAnchor[SKINANCHOR_SYSICON].Width(),
		m_rcAnchor[SKINANCHOR_SYSICON].Height(),
		0, NULL, DI_NORMAL);

	// 绘制标题栏
	// 不能超过260个字符
	TCHAR szCaption[MAX_PATH] = { 0 };
	pWnd->GetWindowText(szCaption, MAX_PATH);
	HFONT hOldFont = (HFONT)::SelectObject(TopBufferDC.m_hDC, m_fnCaption);
	RECT rcCaption = m_rcCaption;
	rcCaption.right = min(m_rcCaption.right, rcItem.left);
	if(rcCaption.left > rcCaption.right)
	{
		rcCaption.left = rcCaption.right;
	}
	int nOldMode = SetBkMode(TopBufferDC.m_hDC, TRANSPARENT);
	COLORREF clrOld;
	if(bActive == FALSE)
	{
		clrOld = SetTextColor(TopBufferDC.m_hDC, m_crCaptionInactive);
	}
	else
	{
		clrOld = SetTextColor(TopBufferDC.m_hDC, m_crCaptionText);
	}
	DrawText(TopBufferDC.m_hDC, szCaption, lstrlen(szCaption), &rcCaption, DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS);
	SetTextColor(TopBufferDC.m_hDC, clrOld);
	SetBkMode(TopBufferDC.m_hDC, nOldMode);
	::SelectObject(TopBufferDC.m_hDC, hOldFont);

	// 顶部绘图
	pDC->BitBlt(rcTop.left, rcTop.top, rcTop.Width(), rcTop.Height(), &TopBufferDC, 0, 0, SRCCOPY);
	TopBufferDC.SelectObject(pOldTopBitmap);
	TopBufferDC.DeleteDC();
	TopBufferBitmap.DeleteObject();

	// 左边双缓冲
	rcLeft = rcWnd;
	if (bActive==FALSE)
	{
		rcLeft.right = rcLeft.left + m_rcPart[SKINPART_IA_LEFT].Width();
		rcLeft.top += m_rcPart[SKINPART_IA_TOP].Height();
		rcLeft.bottom -= m_rcPart[SKINPART_IA_BOTTOM].Height();
	}
	else
	{
		rcLeft.right = rcLeft.left + m_rcPart[SKINPART_LEFT].Width();
		rcLeft.top += m_rcPart[SKINPART_TOP].Height();
		rcLeft.bottom -= m_rcPart[SKINPART_BOTTOM].Height();
	}
	rcMiddle = rcLeft;
	rcMiddle.OffsetRect(-rcLeft.left, -rcLeft.top);
	CDC LeftBufferDC;
	CBitmap LeftBufferBitmap, *pOldLeftBitmap = NULL;
	LeftBufferDC.CreateCompatibleDC(pDC);
	LeftBufferBitmap.CreateCompatibleBitmap(pDC, rcLeft.Width(), rcLeft.Height());
	pOldLeftBitmap = LeftBufferDC.SelectObject(&LeftBufferBitmap);

	// 左上
	if(bActive==FALSE)
	{
		nPart = SKINPART_IA_LEFT_TOP;
		rcMiddle.top += m_rcPart[nPart].Height();
	}
	else
	{
		nPart = SKINPART_LEFT_TOP;
		rcMiddle.top += m_rcPart[nPart].Height();
	}
	pImage->DrawImage(&LeftBufferDC, 0, 0, m_rcPart[nPart].Width(), m_rcPart[nPart].Height(), 
		m_rcPart[nPart].left, m_rcPart[nPart].top, m_rcPart[nPart].Width(), m_rcPart[nPart].Height());

	// 左下
	if(bActive==FALSE)
	{
		nPart = SKINPART_IA_LEFT_BOTTOM;
		rcMiddle.bottom -= m_rcPart[nPart].Height();
	}
	else
	{
		nPart = SKINPART_LEFT_BOTTOM;
		rcMiddle.bottom -= m_rcPart[nPart].Height();
	}
	pImage->DrawImage(&LeftBufferDC, 0, rcMiddle.bottom, m_rcPart[nPart].Width(), m_rcPart[nPart].Height(), 
		m_rcPart[nPart].left, m_rcPart[nPart].top, m_rcPart[nPart].Width(), m_rcPart[nPart].Height());

	// 左中
	if(bActive==FALSE)
	{
		nPart = SKINPART_IA_LEFT;
	}
	else
	{
		nPart = SKINPART_LEFT;
	}
	pImage->DrawImage(&LeftBufferDC, 0, rcMiddle.top, m_rcPart[nPart].Width(), rcMiddle.Height(), 
		m_rcPart[nPart].left, m_rcPart[nPart].top, m_rcPart[nPart].Width(), m_rcPart[nPart].Height());

	// 左边绘图
	pDC->BitBlt(rcLeft.left, rcLeft.top, rcLeft.Width(), rcLeft.Height(), &LeftBufferDC, 0, 0, SRCCOPY);
	LeftBufferDC.SelectObject(pOldLeftBitmap);
	LeftBufferDC.DeleteDC();
	LeftBufferBitmap.DeleteObject();

	// 右边双缓冲
	rcRight = rcWnd;
	if (bActive==FALSE)
	{
		rcRight.left = rcRight.right - m_rcPart[SKINPART_IA_RIGHT].Width();
		rcRight.top += m_rcPart[SKINPART_IA_TOP].Height();
		rcRight.bottom -= m_rcPart[SKINPART_IA_BOTTOM].Height();
	}
	else
	{
		rcRight.left = rcRight.right - m_rcPart[SKINPART_RIGHT].Width();
		rcRight.top += m_rcPart[SKINPART_TOP].Height();
		rcRight.bottom -= m_rcPart[SKINPART_BOTTOM].Height();
	}
	rcMiddle = rcRight;
	rcMiddle.OffsetRect(-rcRight.left, -rcRight.top);
	CDC RightBufferDC;
	CBitmap RightBufferBitmap, *pOldRightBitmap = NULL;
	RightBufferDC.CreateCompatibleDC(pDC);
	RightBufferBitmap.CreateCompatibleBitmap(pDC, rcRight.Width(), rcRight.Height());
	pOldRightBitmap = RightBufferDC.SelectObject(&RightBufferBitmap);

	// 右上
	if(bActive==FALSE)
	{
		nPart = SKINPART_IA_RIGHT_TOP;

		rcMiddle.top += m_rcPart[nPart].Height();
	}
	else
	{
		nPart = SKINPART_RIGHT_TOP;

		rcMiddle.top += m_rcPart[nPart].Height();
	}
	pImage->DrawImage(&RightBufferDC, 0, 0, m_rcPart[nPart].Width(), m_rcPart[nPart].Height(), 
		m_rcPart[nPart].left, m_rcPart[nPart].top, m_rcPart[nPart].Width(), m_rcPart[nPart].Height());

	// 右下
	if(bActive==FALSE)
	{
		nPart = SKINPART_IA_RIGHT_BOTTOM;

		rcMiddle.bottom -= m_rcPart[nPart].Height();
	}
	else
	{
		nPart = SKINPART_RIGHT_BOTTOM;

		rcMiddle.bottom -= m_rcPart[nPart].Height();
	}

	pImage->DrawImage(&RightBufferDC, 0, rcMiddle.bottom, m_rcPart[nPart].Width(), m_rcPart[nPart].Height(), 
		m_rcPart[nPart].left, m_rcPart[nPart].top, m_rcPart[nPart].Width(), m_rcPart[nPart].Height());

	// 右中
	if(bActive==FALSE)
	{
		nPart = SKINPART_IA_RIGHT;
	}
	else
	{
		nPart = SKINPART_RIGHT;
	}    
	pImage->DrawImage(&RightBufferDC, 0, rcMiddle.top, m_rcPart[nPart].Width(), rcMiddle.Height(), 
		m_rcPart[nPart].left, m_rcPart[nPart].top, m_rcPart[nPart].Width(), m_rcPart[nPart].Height());

	// 右边绘图
	pDC->BitBlt(rcRight.left, rcRight.top, rcRight.Width(), rcRight.Height(), &RightBufferDC, 0, 0, SRCCOPY);
	RightBufferDC.SelectObject(pOldRightBitmap);
	RightBufferDC.DeleteDC();
	RightBufferBitmap.DeleteObject();

	// 底部双缓冲
	rcBottom = rcWnd;
	if (bActive==FALSE)
	{
		rcBottom.top = rcBottom.bottom -  m_rcPart[SKINPART_IA_BOTTOM].Height();
	}
	else
	{
		rcBottom.top = rcBottom.bottom -  m_rcPart[SKINPART_IA_BOTTOM].Height();
	}
	rcMiddle = rcBottom;
	rcMiddle.OffsetRect(-rcBottom.left, -rcBottom.top);
	CDC BottomBufferDC;
	CBitmap BottomBufferBitmap, *pOldBottomBitmap = NULL;
	BottomBufferDC.CreateCompatibleDC(pDC);
	BottomBufferBitmap.CreateCompatibleBitmap(pDC, rcBottom.Width(), rcBottom.Height());
	pOldBottomBitmap = BottomBufferDC.SelectObject(&BottomBufferBitmap);

	// 下左
	if(bActive==FALSE)
	{
		nPart = SKINPART_IA_BOTTOM_LEFT;

		rcMiddle.left += m_rcPart[nPart].Width();
	}
	else
	{
		nPart = SKINPART_BOTTOM_LEFT;

		rcMiddle.left += m_rcPart[nPart].Width();
	}
	pImage->DrawImage(&BottomBufferDC, 0, 0, m_rcPart[nPart].Width(), m_rcPart[nPart].Height(), 
		m_rcPart[nPart].left, m_rcPart[nPart].top, m_rcPart[nPart].Width(), m_rcPart[nPart].Height());

	// 下右
	if(bActive==FALSE)
	{
		nPart = SKINPART_IA_BOTTOM_RIGHT;

		rcMiddle.right -= m_rcPart[nPart].Width();
	}
	else
	{
		nPart = SKINPART_BOTTOM_RIGHT;

		rcMiddle.right -= m_rcPart[nPart].Width();
	}
	pImage->DrawImage(&BottomBufferDC, rcMiddle.right, 0, m_rcPart[nPart].Width(), m_rcPart[nPart].Height(), 
		m_rcPart[nPart].left, m_rcPart[nPart].top, m_rcPart[nPart].Width(), m_rcPart[nPart].Height());

	// 下中
	if(bActive==FALSE)
	{
		nPart = SKINPART_IA_BOTTOM;
	}
	else
	{
		nPart = SKINPART_BOTTOM;
	}
	pImage->DrawImage(&BottomBufferDC, rcMiddle.left, 0, rcMiddle.Width(), m_rcPart[nPart].Height(), 
		m_rcPart[nPart].left, m_rcPart[nPart].top, m_rcPart[nPart].Width(), m_rcPart[nPart].Height());

	// 底部绘图
	pDC->BitBlt(rcBottom.left, rcBottom.top, rcBottom.Width(), rcBottom.Height(), &BottomBufferDC, 0, 0, SRCCOPY);
	BottomBufferDC.SelectObject(pOldBottomBitmap);
	BottomBufferDC.DeleteDC();
	BottomBufferBitmap.DeleteObject();
}

void CSkinWindow::ResolveAnchor(const CRect& rcClient, CRect& rcAnchor, int nAnchor)
{
	rcAnchor = m_rcAnchor[nAnchor];
	OffsetRect(&rcAnchor, rcAnchor.left<0?rcClient.right:rcClient.left, 0);
	OffsetRect(&rcAnchor, 0, rcAnchor.top<0?rcClient.bottom:rcClient.top);
}

// 设置SKIN图片
bool CSkinWindow::SetSkinImage(LPCTSTR pszFileName, BitmapFormat bf)
{
	// 效验参数
	ASSERT(pszFileName);
	if (pszFileName == NULL) return false;

	// 加载图
	m_ImageSkin.DestroyImage();
	m_ImageSkin.LoadFromFile(pszFileName, bf);
	ASSERT(m_ImageSkin.IsValid());

	return true;
}

bool CSkinWindow::SetSkinImage(BYTE* pBuffer, DWORD dwBufferSize, BitmapFormat bf)
{
	// 效验参数
	ASSERT(pBuffer && dwBufferSize);
	if (pBuffer==NULL || dwBufferSize == 0) return false;

	// 加载图
	m_ImageSkin.DestroyImage();
	m_ImageSkin.LoadFromMemory(pBuffer, dwBufferSize, bf);
	ASSERT(m_ImageSkin.IsValid());

	return true;
}

bool CSkinWindow::SetSkinImage(LPCTSTR lpszResource, HINSTANCE hInst, BitmapFormat bf)
{
	m_ImageSkin.DestroyImage();
	m_ImageSkin.LoadFromResource(hInst, lpszResource, bf);
	ASSERT(m_ImageSkin.IsValid());

	return true;
}

// 设置标题文字颜色 crInactiveText: 未激活文字的颜色
void CSkinWindow::SetCaptionTextColor(COLORREF crText, COLORREF crInactiveText)
{
	m_crCaptionText = crText;
	m_crCaptionInactive = crInactiveText;
}
