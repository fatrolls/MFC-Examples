#include "stdafx.h"
#include "PPHtmlStatic.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define TIMER_ANIMATION		0x104

/////////////////////////////////////////////////////////////////////////////
// CPPHtmlStatic

CPPHtmlStatic::CPPHtmlStatic()
{
	m_hBitmapBk = NULL;

	m_hRgn = NULL;
	m_bRectRgn = FALSE;
	m_nRoundX = m_nRoundY = 0;

	m_bIsRunning = FALSE;
	m_dwFrameRate = 0;

	m_bIsImage = FALSE;
	SetText(_T(""));

	m_rcArea.SetRectEmpty();
	SetMargins();
	
	SetAlign(PPHTMLSTATIC_ALIGN_DEFAULT);
	SetHyperlinkStyle(RGB(0, 0, 255), FALSE, RGB(0, 0, 255), TRUE);
	SetImageZoom(100, 100);
//	SetFitOutput();

	SetBorder((HBRUSH)NULL);
	
	SetTextColor(::GetSysColor(COLOR_WINDOWTEXT));

	//Customizes a static's background
	SetBkColor(::GetSysColor(COLOR_3DFACE));
	SetBkMode(OPAQUE);
	SetBkEffect(CPPDrawManager::EFFECT_SOLID);
} //End of CPPHtmlStatic

CPPHtmlStatic::~CPPHtmlStatic()
{
	if (NULL != m_hbrBorder)
	{
		::DeleteObject(m_hbrBorder);
		m_hbrBorder = NULL;
	} //if
	
	FreeResources();
} //End of ~CPPHtmlStatic

BEGIN_MESSAGE_MAP(CPPHtmlStatic, CStatic)
	//{{AFX_MSG_MAP(CPPHtmlStatic)
	ON_WM_PAINT()
	ON_WM_SETCURSOR()
	ON_WM_LBUTTONDOWN()
	ON_WM_ERASEBKGND()
	ON_WM_MOUSEMOVE()
	ON_WM_TIMER()
	ON_WM_ENABLE()
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_SETTEXT, OnSetText)
	ON_MESSAGE(WM_GETTEXT, OnGetText)
	ON_MESSAGE(WM_SETFONT, OnSetFont)
	ON_MESSAGE(WM_GETFONT, OnGetFont)
	ON_MESSAGE(WM_MOUSELEAVE, OnMouseLeave)
	ON_MESSAGE(UDM_TOOLTIP_REPAINT, OnRepaintWindow)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPPHtmlStatic message handlers
void CPPHtmlStatic::PreSubclassWindow() 
{
	//Enable the Static to send the Window Messages To its parent
	ModifyStyle(WS_HSCROLL|WS_VSCROLL, SS_NOTIFY);
	ModifyStyleEx(0, WS_EX_RIGHTSCROLLBAR);

	DWORD dwStyle = GetStyle();
//	SetWindowLong(GetSafeHwnd(), GWL_STYLE, dwStyle | SS_NOTIFY);

//	DWORD dwExStyles = GetExStyle();
//	dwExStyles |= WS_EX_RIGHTSCROLLBAR;
//	SetWindowLong(GetSafeHwnd(), GWL_EXSTYLE, dwExStyles);

	m_bIsEnabled = (WS_DISABLED & dwStyle) ? FALSE : TRUE;
	m_drawer.EnableOutput(m_bIsEnabled);
	
	m_drawer.SetCallbackRepaint(GetSafeHwnd(), UDM_TOOLTIP_REPAINT);

	CFont* pFont = GetFont();
	HFONT hFont = NULL;
	//ENG: Gets a default system font
	//RUS: Получаем системный шрифт по-умолчанию
	if (NULL == hFont)
	{
		hFont = (HFONT)::GetStockObject(DEFAULT_GUI_FONT);
		if (NULL == hFont)
			hFont = (HFONT)::GetStockObject(ANSI_VAR_FONT);
	}
	else hFont = (HFONT)pFont->GetSafeHandle();

	SetDefaultFont(hFont);

	//ENG: Sets a control's initializing text
	CString str;
	GetWindowText(str);
	SetText(str);
	
	CStatic::PreSubclassWindow();
} //End of PreSubclassWindow

void CPPHtmlStatic::FreeResources()
{
	if (NULL != m_hBitmapBk)
	{
		::DeleteObject(m_hBitmapBk);
		m_hBitmapBk = NULL;
	}
} //End of FreeResources

afx_msg BOOL CPPHtmlStatic::OnEraseBkgnd(CDC* pDC) 
{
	return TRUE;
} //End of OnEraseBkgnd

BOOL CPPHtmlStatic::DestroyWindow() 
{
	ClearFrameRate();
	SetRgn(); //Delete a region
	return CStatic::DestroyWindow();
}

afx_msg void CPPHtmlStatic::OnTimer(UINT nIDEvent) 
{
	if ((TIMER_ANIMATION == nIDEvent) && m_bIsEnabled)
	{
		m_drawer.OnTimer();
		RepaintWindow();
	}
	
	CStatic::OnTimer(nIDEvent);
} //End of OnTimer

afx_msg void CPPHtmlStatic::OnEnable(BOOL bEnable) 
{
	CStatic::OnEnable(bEnable);
	
	m_bIsEnabled = bEnable;
	m_drawer.EnableOutput(bEnable);
//	EnableScrollBarCtrl(SB_HORZ, bEnable);
//	EnableScrollBarCtrl(SB_VERT, bEnable);
//	Invalidate();
//	UpdateWindow();
	UpdateSurface();
} //End of OnEnable

afx_msg LRESULT CPPHtmlStatic::OnSetText(WPARAM wParam, LPARAM lParam)
{
	m_bIsImage = FALSE;
	SetText((LPCTSTR)lParam);
	return 0;
} //End of OnSetFont

afx_msg LRESULT CPPHtmlStatic::OnGetText(WPARAM wParam, LPARAM lParam)
{
	return (LRESULT)(LPCTSTR)m_sText;
} //End of OnSetFont

afx_msg LRESULT CPPHtmlStatic::OnSetFont (WPARAM wParam, LPARAM lParam)
{
	SetDefaultFont((HFONT)wParam);
	return 0;
} //End of OnSetFont

afx_msg LRESULT CPPHtmlStatic::OnGetFont (WPARAM, LPARAM)
{
	return (LRESULT)m_hFont;
} //End of OnSetFont

afx_msg void CPPHtmlStatic::OnMouseMove(UINT nFlags, CPoint point) 
{
	// Create TRACKMOUSEEVENT structure
	TRACKMOUSEEVENT tmeMouseEvent;		
	
	// Initialize members of structure
	tmeMouseEvent.cbSize = sizeof(TRACKMOUSEEVENT);
	tmeMouseEvent.dwFlags = TME_LEAVE;
	tmeMouseEvent.hwndTrack = m_hWnd;
	
	// Track mouse leave event
	_TrackMouseEvent(&tmeMouseEvent);
	
	CStatic::OnMouseMove(nFlags, point);
} //End of OnMouseMove

// Handler for WM_MOUSELEAVE
afx_msg LRESULT CPPHtmlStatic::OnMouseLeave(WPARAM wParam, LPARAM lParam)
{
	POINT point;
	::GetCursorPos(&point);
	ScreenToClient(&point);
	m_drawer.OnSetCursor(&point);
//	RepaintWindow();

	return 0;
} // End of OnMouseLeave

void CPPHtmlStatic::UpdateSurface()
{
	if (::IsWindow(GetSafeHwnd()))
	{
		if (NULL == m_hRgn)
		{
			Invalidate();
			UpdateWindow();
		}
		else
		{
			CRect (rc);
			GetWindowRect(rc);
			RedrawWindow();
			GetParent()->ScreenToClient(rc);
			GetParent()->InvalidateRect(rc,TRUE);
			GetParent()->UpdateWindow();
		} //if 
	} //if
} //End of UpdateSurface

void CPPHtmlStatic::OnSize(UINT nType, int cx, int cy) 
{
	CStatic::OnSize(nType, cx, cy);

	//Stretch a region
	if (m_bRectRgn) 
	{
		SetRgn(CreateRegion());
		m_bRectRgn = TRUE;
	}
	else
	{
		SetRgn();
	} //if
	
	if (TRANSPARENT != m_nBkMode)
		FreeResources();
	UpdateSurface();
} //End of OnSize

void CPPHtmlStatic::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	HDC hMemDC = ::CreateCompatibleDC(dc.GetSafeHdc());
//	HDC hMemDC = NULL;
	
	CRect rcClient;
	GetClientRect(&rcClient);

	if (NULL == m_pHScroll.GetSafeHwnd())
	{
		//CRect rc = rcClient;
		//rc.top = rc.bottom - GetSystemMetrics(SM_CYHSCROLL);
//		m_pHScroll.Create(WS_VISIBLE|WS_CHILD|SBS_HORZ|SBS_BOTTOMALIGN, rcClient, this, 2000);
		//rc = rcClient;
		//rc.left = rc.right - GetSystemMetrics(SM_CXVSCROLL);
//		m_pVScroll.Create(WS_VISIBLE|WS_CHILD|SBS_VERT|SBS_RIGHTALIGN, rcClient, this, 2001);
//		SetScrollPos(SB_HORZ, 0);
//		GetScrollBarCtrl(SBS_HORZ)->SetParent(this);
	} //if
//	return;

	//Copies a background of a static control to a bitmap
/*
	if (NULL != m_hBitmapBk)
		::DeleteObject(m_hBitmapBk);
	m_hBitmapBk = ::CreateCompatibleBitmap(dc.GetSafeHdc(), rcClient.Width(), rcClient.Height());
	HBITMAP hOldBmp = (HBITMAP)::SelectObject(hMemDC, m_hBitmapBk);
	if (TRANSPARENT == m_nBkMode)
	{
		::BitBlt(hMemDC, 0, 0, rcClient.Width(), rcClient.Height(), dc.GetSafeHdc(), rcClient.left, rcClient.top, SRCCOPY);
	}
	else
	{
//		::BitBlt(hMemDC, 0, 0, rcClient.Width(), rcClient.Height(), NULL, 0, 0, WHITENESS);
		HBRUSH brush = ::CreateSolidBrush(m_clrBk);
		::FillRect(hMemDC, rcClient, brush);
		::DeleteObject(brush);
	} //if
	::SelectObject(hMemDC, hOldBmp);
	::DeleteDC(hMemDC);
*/
	if (NULL == m_hBitmapBk)
	{
		m_hBitmapBk = ::CreateCompatibleBitmap(dc.GetSafeHdc(), rcClient.Width(), rcClient.Height());
		HBITMAP hOldBmp = (HBITMAP)::SelectObject(hMemDC, m_hBitmapBk);
		if (TRANSPARENT == m_nBkMode)
		{
			::BitBlt(hMemDC, 0, 0, rcClient.Width(), rcClient.Height(), dc.GetSafeHdc(), rcClient.left, rcClient.top, SRCCOPY);
		}
		else
		{
			//		::BitBlt(hMemDC, 0, 0, rcClient.Width(), rcClient.Height(), NULL, 0, 0, WHITENESS);
			m_drawer.GetDrawManager()->FillEffect(hMemDC, m_dwBkEffect, rcClient, m_clrBkBegin, m_clrBkMid, m_clrBkEnd, m_nGranularity, 5);
		} //if
		::SelectObject(hMemDC, hOldBmp);
	} //if
	::DeleteDC(hMemDC);

	CString str = m_sText;
	if (!m_bIsImage && (m_clrText != -1))
	{
		//If text mode was setted a color was specified
		CString sColor;
		sColor.Format(_T("<font color=0x%06X>"), m_clrText);
		str = sColor + str + _T("</font>");
	} //if

	DWORD dwStyle = GetStyle();
	int nControlWidth = rcClient.Width() - m_szTextMargin.cx * 2 - 1;
	if (dwStyle & SS_LEFTNOWORDWRAP)
		m_drawer.SetMaxWidth();
	else
		m_drawer.SetMaxWidth(nControlWidth);

//	m_drawer.EnableTextWrap((dwStyle & SS_LEFTNOWORDWRAP) ? FALSE : TRUE);
	m_drawer.PrepareOutput(dc.GetSafeHdc(), str, &m_szOutput);
	if (!m_bIsImage && (dwStyle & SS_LEFTNOWORDWRAP))
		m_szOutput.cx = max(nControlWidth, m_szOutput.cx);

/*

	EnableScrollBarCtrl(SB_HORZ);
	SetScrollRange(SB_HORZ, 0, 100);
	ShowScrollBar(SB_HORZ);
	EnableScrollBarCtrl(SB_VERT);
	SetScrollRange(SB_VERT, 0, 100);
	ShowScrollBar(SB_VERT);
*/
/*
	if (m_szOutput.cx > rcClient.Width())
	{
		SetScrollRange(SB_HORZ, 0, rcClient.Width() - m_szOutput.cx);
		ShowScrollBar(SB_HORZ, TRUE);
	}
	else ShowScrollBar(SB_HORZ, FALSE);
	
	if (m_szOutput.cy > rcClient.Height())
	{
		SetScrollRange(SB_VERT, 0, rcClient.Height() - m_szOutput.cy);
		ShowScrollBar(SB_VERT, TRUE);
	}
	else ShowScrollBar(SB_VERT, FALSE);
*/

	SIZE size;
	size.cx = min(m_szOutput.cx, rcClient.Width());
	size.cy = min(m_szOutput.cy, rcClient.Height());

	DWORD dwAlign = m_dwAlign;
	//Horizontal align
	if (PPHTMLSTATIC_ALIGN_DEFAULT == (dwAlign & 0x03))
	{
		switch (dwStyle & 0x03)
		{
		case SS_LEFT:
			dwAlign |= PPHTMLSTATIC_ALIGN_LEFT;
			break;
		case SS_RIGHT:
			dwAlign |= PPHTMLSTATIC_ALIGN_RIGHT;
			break;
		case SS_CENTER:
			dwAlign |= PPHTMLSTATIC_ALIGN_CENTER;
			break;
		} //switch
	} //if
	//Vertical align
	if (PPHTMLSTATIC_ALIGN_DEFAULT == (dwAlign & 0x0C))
	{
		if (SS_CENTERIMAGE & dwStyle)
			dwAlign |= PPHTMLSTATIC_ALIGN_VCENTER;
		else
			dwAlign |= PPHTMLSTATIC_ALIGN_TOP;
	} //if
	
	CPoint pt = rcClient.TopLeft();
	switch (dwAlign & 0x03)
	{
	case PPHTMLSTATIC_ALIGN_RIGHT:
		pt.x += rcClient.Width() - size.cx - m_szTextMargin.cx;
		break;
	case PPHTMLSTATIC_ALIGN_CENTER:
		pt.x += (rcClient.Width() - size.cx) / 2;
		break;
	default:
		pt.x += m_szTextMargin.cx;
		break;
	} //switch
	
	switch (dwAlign & 0x0C)
	{
	case PPHTMLSTATIC_ALIGN_BOTTOM:
		pt.y += rcClient.Height() - size.cy - m_szTextMargin.cy;
		break;
	case PPHTMLSTATIC_ALIGN_VCENTER:
		pt.y += (rcClient.Height() - size.cy) / 2;
		break;
	default:
		pt.y += m_szTextMargin.cy;
		break;
	} //switch

	//ENG: A placement of the output area
	//RUS: Положение области вывода по отношению к клиентским координатам
	m_rcArea.SetRect(pt.x, pt.y, pt.x + size.cx, pt.y + size.cy);

	RepaintWindow(dc.GetSafeHdc());
} //End of OnPaint

BOOL CPPHtmlStatic::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	if (m_bIsEnabled)
	{
		POINT point;
		::GetCursorPos(&point);
		ScreenToClient(&point);
//		ptClient.x -= m_rcArea.left;
//		ptClient.y -= m_rcArea.top;
		if (m_drawer.OnSetCursor(&point))
			return TRUE; //The cursor over the hyperlink
	} //if
	
	return CStatic::OnSetCursor(pWnd, nHitTest, message);
} //End of OnSetCursor

HRGN CPPHtmlStatic::CreateRegion()
{
	RECT rect;
	GetClientRect(&rect);
	return ::CreateRoundRectRgn(rect.left, rect.top, rect.right, rect.bottom, m_nRoundX, m_nRoundY);
}

afx_msg void CPPHtmlStatic::OnLButtonDown(UINT nFlags, CPoint point) 
{
	if (m_rcArea.PtInRect(point) && m_bIsEnabled)
	{
		CPoint ptClient = point;
//		ptClient.x -= m_rcArea.left;
//		ptClient.y -= m_rcArea.top;
		m_drawer.OnLButtonDown(&ptClient);
	} //if

	CStatic::OnLButtonDown(nFlags, point);
} //End of OnLButtonDown

void CPPHtmlStatic::SetText(LPCTSTR lpszText)
{
	m_sText = (CString)lpszText;
	UpdateSurface();
} //End of SetText

afx_msg LRESULT CPPHtmlStatic::OnRepaintWindow(WPARAM wParam, LPARAM lParam)
{
	TRACE("CPPHtmlStatic::OnRepaintWindow()\n");
	RepaintWindow();
    return TRUE;
} //End of the UDM_TOOLTIP_REPAINT handler

void CPPHtmlStatic::RepaintWindow(HDC hDC /* = NULL */)
{
	TRACE("CPPHtmlStatic::RepaintWindow()\n");
	//ENG: If device context not passed
	//RUS: Если контекст устройства не передавался, то получаем его и устанавливаем признак автоматического удаления
	BOOL bAutoReleaseDC = FALSE;
	if (NULL == hDC)
	{
		hDC = ::GetDC(this->GetSafeHwnd());
		bAutoReleaseDC = TRUE;
	} //if

	CRect rcClient;
	GetClientRect(&rcClient);

	//ENG: Creates memory context
	//RUS: Создаем контекст устройства в памяти
	HDC hMemDC = ::CreateCompatibleDC(hDC);
	HDC hBkDC = ::CreateCompatibleDC(hDC);
	HBITMAP hOldBkBitmap = (HBITMAP)::SelectObject(hBkDC, m_hBitmapBk);
	HBITMAP hBitmap = ::CreateCompatibleBitmap(hDC, rcClient.Width(), rcClient.Height());
	HBITMAP hOldBitmap = (HBITMAP)::SelectObject(hMemDC, hBitmap);

	//ENG: Copy background to the temporary bitmap
	//RUS: Копируем фон под тултипом в память
	::BitBlt(hMemDC, 0, 0, rcClient.Width(), rcClient.Height(), hBkDC, 0, 0, SRCCOPY);

	CRect rcOutput = m_rcArea;
	if (!m_bIsEnabled)
	{
		rcOutput.OffsetRect(1, 1);
		m_drawer.SetDisabledColor(::GetSysColor(COLOR_BTNHILIGHT));
		m_drawer.DrawPreparedOutput(hMemDC, &rcOutput);
		rcOutput.OffsetRect(-1, -1);
		m_drawer.SetDisabledColor(::GetSysColor(COLOR_BTNSHADOW));
	}
	//ENG: Draw HTML string
	//RUS: Отображаем HTML строку
	m_drawer.DrawPreparedOutput(hMemDC, &rcOutput);

	if (NULL != m_hRgn)
		::SelectClipRgn(hDC, m_hRgn);
	
	//ENG: Output a tooltip to the screen
	//RUS: Выводим тултип на экран
	::BitBlt(hDC, 0, 0, rcClient.Width(), rcClient.Height(), hMemDC, 0, 0, SRCCOPY);

	if (NULL != m_hRgn)
	{
		if (NULL != m_hbrBorder)
			::FrameRgn(hDC, m_hRgn, m_hbrBorder, m_szBorder.cx, m_szBorder.cy);
		::SelectClipRgn(hDC, NULL);
	}
	else if (NULL != m_hbrBorder)
		::FrameRect(hDC, rcClient, m_hbrBorder);
	
	//ENG: Free resources
	//RUS: Освобождаем задействованные ресурсы
	::SelectObject(hBkDC, hOldBkBitmap);
	::SelectObject(hMemDC, hOldBitmap);
	::DeleteObject(hBitmap);
	::DeleteDC(hBkDC);
	::DeleteDC(hMemDC);

	//ENG: Releases device context if needed
	//RUS: Освобождаем контекст устройства если это необходимо
	if (bAutoReleaseDC)
		::ReleaseDC(this->GetSafeHwnd(), hDC);
}

///////////////////////////////////////////////////////////////////////////////
// public methods

void CPPHtmlStatic::SetDefaultFont(HFONT hFont)
{
	m_hFont = hFont;

	if (NULL != hFont)
	{
		LOGFONT lf;
		CFont::FromHandle(hFont)->GetLogFont(&lf);
		CString str;
		str.Format(_T("font-size:%dpt; color:0x%06X; font-family:%s; font-weight:%d"), lf.lfHeight, ::GetSysColor(COLOR_WINDOWTEXT), lf.lfFaceName, lf.lfWeight);
		if (lf.lfItalic)
			str += _T("; font-style:italic");
		m_drawer.SetTextStyle(_T("body"), str);
		UpdateSurface();
	} //if
} //End of SetDefaultFont

void CPPHtmlStatic::SetImageZoom(int nPercent /* = 100 */)
{
	SetImageZoom(nPercent, nPercent);
}  //End of SetImageZoom

void CPPHtmlStatic::SetImageZoom(int nWidthPercent /* = 100 */, int nHeightPercent /* = 100 */)
{
	m_nHeightPercent = nHeightPercent;
	m_nWidthPercent = nWidthPercent;
	if (m_bIsImage)
	{
		CRect rect;
		GetClientRect(&rect);
		CString str = m_sTemplate.Left(m_sTemplate.GetLength() - 1);
		CString str1, str2;
		
		if (0 == nWidthPercent)
			str1.Format(_T(" width=%d"), rect.Width() - m_szTextMargin.cx * 2 - 1);
		else
		{
			if (m_szImage.cx < 0)
				str1.Format(_T(" width=%d%%"), nWidthPercent);
			else
				str1.Format(_T(" width=%d"), ::MulDiv(m_szImage.cx, nWidthPercent, 100));
		} //if
		
		if (0 == nHeightPercent)
			str2.Format(_T(" height=%d"), rect.Height() - m_szTextMargin.cy * 2);
		else
		{
			if (m_szImage.cx < 0)
				str2.Format(_T(" height=%d%%"), nHeightPercent);
			else
				str2.Format(_T(" height=%d"), ::MulDiv(m_szImage.cy, nHeightPercent, 100));
		} //if

		str += str1 + str2 + _T(">");
		SetText(str);
	} //if
} //End of SetImageZoom

void CPPHtmlStatic::SetAlign(DWORD dwAlign /* = PPHTMLSTATIC_ALIGN_DEFAULT */)
{
	TRACE(_T("CPPHtmlStatic::SetTextAlign()\n"));
	m_dwAlign = dwAlign;
	UpdateSurface();
} //End of SetAlign


DWORD CPPHtmlStatic::GetAlign()
{
	TRACE(_T("CPPHtmlStatic::GetTextAlign()\n"));
	return m_dwAlign;
} //End of GetAlign

void CPPHtmlStatic::SetHyperlink(LPCTSTR lpszText, LPCTSTR lpszUrl, BOOL bParentNotify /* = FALSE */)
{
	ASSERT(lpszText);
	ASSERT(lpszUrl);
	
	ClearFrameRate();
	CString str;
	if (bParentNotify)
		str.Format(_T("<a msg=\"%s\">%s</a>"), lpszUrl, lpszText);
	else
		str.Format(_T("<a href=\"%s\">%s</a>"), lpszUrl, lpszText);
	SetText(str);
} //End of SetHyperlink

void CPPHtmlStatic::SetIcon(DWORD dwIdIcon, LPSIZE lpSize /* = NULL */)
{
	ASSERT(dwIdIcon);
	ClearFrameRate();
	if (NULL != lpSize)
	{
		m_szImage = *lpSize;
		m_sTemplate.Format(_T("<icon idres=%d>"), dwIdIcon);
	}
	else
	{
		m_szImage = CSize(-1, -1);
		m_sTemplate.Format(_T("<icon idres=%d>"), dwIdIcon);
	}
	m_bIsImage = TRUE;
	SetImageZoom(m_nWidthPercent, m_nHeightPercent);
} //End of SetIcon

void CPPHtmlStatic::SetIcon(HICON hIcon)
{
	ASSERT(hIcon);
	ClearFrameRate();
	m_sTemplate.Format(_T("<icon handle=0x%X>"), hIcon);
	m_bIsImage = TRUE;
	m_szImage = CSize(-1, -1);
	SetImageZoom(m_nWidthPercent, m_nHeightPercent);
} //End of SetIcon

void CPPHtmlStatic::SetBitmap(DWORD dwIdBitmap, COLORREF clrMask /* = RGB(255, 0, 255) */)
{
	ASSERT(dwIdBitmap);
	ClearFrameRate();
	if (-1 == clrMask)
		m_sTemplate.Format(_T("<bmp idres=%d>"), dwIdBitmap);
	else
		m_sTemplate.Format(_T("<bmp idres=%d mask=0x%06X>"), dwIdBitmap, clrMask);
	m_bIsImage = TRUE;
	m_szImage = CSize(-1, -1);
	SetImageZoom(m_nWidthPercent, m_nHeightPercent);
} //End of SetBitmap

void CPPHtmlStatic::SetBitmap(HBITMAP hBitmap, COLORREF clrMask /* = RGB(255, 0, 255) */)
{
	ASSERT(hBitmap);
	ClearFrameRate();
	if (-1 == clrMask)
		m_sTemplate.Format(_T("<bmp handle=0x%X>"), hBitmap);
	else
		m_sTemplate.Format(_T("<bmp handle=0x%X mask=0x%06X>"), hBitmap, clrMask);
	m_bIsImage = TRUE;
	m_szImage = CSize(-1, -1);
	SetImageZoom(m_nWidthPercent, m_nHeightPercent);
} //End of SetBitmap

void CPPHtmlStatic::SetAnimation(DWORD dwIdBitmap, LPSIZE lpSizeItem /* = NULL */, COLORREF clrMask /* = RGB(255, 0, 255) */)
{
	ASSERT(dwIdBitmap);
	SetFrameRate(m_dwFrameRate);
	if (NULL == lpSizeItem) 
	{
		if (-1 == clrMask)
			m_sTemplate.Format(_T("<ilst index=0 idres=%d speed=1>"), dwIdBitmap);
		else
			m_sTemplate.Format(_T("<ilst index=0 idres=%d mask=0x%06X speed=1>"), dwIdBitmap, clrMask);
	}
	else
	{
		if (-1 == clrMask)
			m_sTemplate.Format(_T("<ilst index=0 idres=%d cx=%d, cy=%d speed=1>"), dwIdBitmap, lpSizeItem->cx, lpSizeItem->cy);
		else
			m_sTemplate.Format(_T("<ilst index=0 idres=%d mask=0x%06X cx=%d, cy=%d speed=1>"), dwIdBitmap, clrMask, lpSizeItem->cx, lpSizeItem->cy);
	} //if
	m_bIsImage = TRUE;
	m_szImage = CSize(-1, -1);
	SetImageZoom(m_nWidthPercent, m_nHeightPercent);
}

void CPPHtmlStatic::SetAnimation(HBITMAP hBitmap, LPSIZE lpSizeItem /* = NULL */, COLORREF clrMask /* = RGB(255, 0, 255) */)
{
	ASSERT(hBitmap);
	SetFrameRate(m_dwFrameRate);
	if (NULL == lpSizeItem) 
	{
		if (-1 == clrMask)
			m_sTemplate.Format(_T("<ilst index=0 handle=0x%X speed=1>"), hBitmap);
		else
			m_sTemplate.Format(_T("<ilst index=0 handle=0x%X mask=0x%06X speed=1>"), hBitmap, clrMask);
	}
	else
	{
		if (-1 == clrMask)
			m_sTemplate.Format(_T("<ilst index=0 handle=0x%X cx=%d, cy=%d speed=1>"), hBitmap, lpSizeItem->cx, lpSizeItem->cy);
		else
			m_sTemplate.Format(_T("<ilst index=0 handle=0x%X mask=0x%06X cx=%d, cy=%d speed=1>"), hBitmap, clrMask, lpSizeItem->cx, lpSizeItem->cy);
	} //if
	m_bIsImage = TRUE;
	m_szImage = CSize(-1, -1);
	SetImageZoom(m_nWidthPercent, m_nHeightPercent);
}

void CPPHtmlStatic::SetImageList(DWORD dwIdBitmap, DWORD dwIndex, LPSIZE lpSizeItem /* = NULL */, COLORREF clrMask /* = RGB(255, 0, 255) */)
{
	ClearFrameRate();
	if (NULL == lpSizeItem) 
	{
		if (-1 == clrMask)
			m_sTemplate.Format(_T("<ilst index=%d idres=%d>"), dwIndex, dwIdBitmap);
		else
			m_sTemplate.Format(_T("<ilst index=%d idres=%d mask=0x%06X>"), dwIndex, dwIdBitmap, clrMask);
	}
	else
	{
		if (-1 == clrMask)
			m_sTemplate.Format(_T("<ilst index=%d idres=%d cx=%d, cy=%d>"), dwIndex, dwIdBitmap, lpSizeItem->cx, lpSizeItem->cy);
		else
			m_sTemplate.Format(_T("<ilst index=%d idres=%d mask=0x%06X cx=%d, cy=%d>"), dwIndex, dwIdBitmap, clrMask, lpSizeItem->cx, lpSizeItem->cy);
	} //if
	m_bIsImage = TRUE;
	m_szImage = CSize(-1, -1);
	SetImageZoom(m_nWidthPercent, m_nHeightPercent);
}

void CPPHtmlStatic::SetImageList(HBITMAP hBitmap, DWORD dwIndex, LPSIZE lpSizeItem /* = NULL */, COLORREF clrMask /* = RGB(255, 0, 255) */)
{
	ClearFrameRate();
	if (NULL == lpSizeItem) 
	{
		if (-1 == clrMask)
			m_sTemplate.Format(_T("<ilst index=%d handle=0x%X>"), dwIndex, hBitmap);
		else
			m_sTemplate.Format(_T("<ilst index=%d handle=0x%X mask=0x%06X>"), dwIndex, hBitmap, clrMask);
	}
	else
	{
		if (-1 == clrMask)
			m_sTemplate.Format(_T("<ilst index=%d handle=0x%X cx=%d, cy=%d>"), dwIndex, hBitmap, lpSizeItem->cx, lpSizeItem->cy);
		else
			m_sTemplate.Format(_T("<ilst index=%d handle=0x%X mask=0x%06X cx=%d, cy=%d>"), dwIndex, hBitmap, clrMask, lpSizeItem->cx, lpSizeItem->cy);
	} //if
	m_bIsImage = TRUE;
	m_szImage = CSize(-1, -1);
	SetImageZoom(m_nWidthPercent, m_nHeightPercent);
}

//Method was added by Steve Mayfield
void CPPHtmlStatic::ClearFrameRate()
{
  if(m_bIsRunning)
  {
    KillTimer(TIMER_ANIMATION);
    m_bIsRunning = FALSE;
  }
} //End of ClearFrameRate

//--------------------------------------------------------------------------
// CPPHtmlStatic::SetFrameRate()
//		Sets the new frame rate for the animation
//--------------------------------------------------------------------------
// Parameters:
//		dwFrameRate		 - Specified a time-out value between current and next 
//						   displayed bitmap
//--------------------------------------------------------------------------
// Sets the new frame rate for the animation. For the CPPHtmlStatic class the 
// frame rate means a time-out period in milliseconds between current and next 
// bitmap instead of number of frames per second. 
// The default value is 500 milliseconds.
//--------------------------------------------------------------------------
void CPPHtmlStatic::SetFrameRate(DWORD dwFrameRate /* = 500 */)
{
	if ((m_dwFrameRate == dwFrameRate) && m_bIsRunning)
		return;

	ClearFrameRate();
	m_dwFrameRate = dwFrameRate;
	if (dwFrameRate)
		m_bIsRunning = SetTimer(TIMER_ANIMATION, dwFrameRate, NULL);
} //End of SetAnimationSpeed

/////////////////////////////////////////////////////////////////////
// CPPHtmlStatic::SetCallbackHyperlink
// This function sets or removes the notification messages from the control before display.
//
// Parameters:
///////////////////////////////////////////////////////////////////////
void CPPHtmlStatic::SetCallbackHyperlink(UINT nMessage, LPARAM lParam /* = 0 */)
{
	TRACE(_T("CPPHtmlDrawer::SetCallbackHyperlink()\n"));
	m_drawer.SetCallbackHyperlink(GetParent()->GetSafeHwnd(), nMessage, lParam);
} //End SetCallbackHyperlink

//--------------------------------------------------------------------------
// CPPHtmlStatic::SetHyperlinkStyle
//--------------------------------------------------------------------------
void CPPHtmlStatic::SetHyperlinkStyle(COLORREF clrOrg, BOOL bOrgUnderline, COLORREF clrHover, BOOL bHoverUnderline)
{
	CString str;
	str.Format(_T("color:0x%06X; text-decoration:"), clrOrg);
	if (bOrgUnderline) str += _T("underline");
	else str += _T("none");
	m_drawer.SetTextStyle(_T("a:link"), str);
	str.Format(_T("color:0x%06X; text-decoration:"), clrHover);
	if (bHoverUnderline) str += _T("underline");
	else str += _T("none");
	m_drawer.SetTextStyle(_T("a:hover"), str);
} //End of SetHyperlinkStyle

void CPPHtmlStatic::SetBkColor(COLORREF clrBk)
{
	SetBkColor(clrBk, clrBk, clrBk);
} //End of SetBkColor

void CPPHtmlStatic::SetBkColor(COLORREF clrBegin, COLORREF clrEnd)
{
	SetBkColor(clrBegin, clrBegin, clrEnd);
} //End of SetBkColor

void CPPHtmlStatic::SetBkColor(COLORREF clrBegin, COLORREF clrMid, COLORREF clrEnd)
{
	if (TRANSPARENT != m_nBkMode)
		FreeResources();
	m_clrBkBegin = clrBegin;
	m_clrBkMid = clrMid;
	m_clrBkEnd = clrEnd;
	UpdateSurface();
} //End of SetBkColor

void CPPHtmlStatic::SetBkMode(int nBkMode /*= TRANSPARENT*/)
{
	if (m_nBkMode != nBkMode)
		FreeResources();
	m_nBkMode = nBkMode;
	UpdateSurface();
} //End of SetBkMode

void CPPHtmlStatic::SetBkEffect(DWORD dwEffect, BYTE nGranularity /*= 5*/)
{
	if (TRANSPARENT != m_nBkMode)
		FreeResources();
	m_dwBkEffect = dwEffect;
	m_nGranularity = nGranularity;
	UpdateSurface();
} //End of SetBkEffect

void CPPHtmlStatic::SetTextColor(COLORREF clrText /*= -1*/)
{
	m_clrText = clrText;
	UpdateSurface();
} //End of SetTextColor

void CPPHtmlStatic::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	MessageBox("OnHScroll");
	
	CStatic::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CPPHtmlStatic::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	MessageBox("OnVScroll");
	
	CStatic::OnVScroll(nSBCode, nPos, pScrollBar);
}

//--------------------------------------------------------------------------
// CPPHtmlStatic::SetRgn()
//		Sets a region to static control
//--------------------------------------------------------------------------
// Parameters:
//	nRgn		- Handle of the region. 
//--------------------------------------------------------------------------
void CPPHtmlStatic::SetRgn(HRGN hRgn /*= NULL*/)
{
	m_bRectRgn = FALSE;
	if (NULL != m_hRgn)
	{
		::DeleteObject(m_hRgn);
		m_hRgn = NULL;
	} //if
	m_hRgn = hRgn;
	UpdateSurface();
} //End of SetRgn

//--------------------------------------------------------------------------
// CPPHtmlStatic::SetRectRgn()
//		Create a rectangle region
//--------------------------------------------------------------------------
void CPPHtmlStatic::SetRectRgn()
{
	m_nRoundX = m_nRoundY = 0;
	SetRgn(CreateRegion());
	m_bRectRgn = TRUE;
} //End of SetRectRgn

//--------------------------------------------------------------------------
// CPPHtmlStatic::SetRoundRectRgn()
//		Create a region as rounded rectangle
//--------------------------------------------------------------------------
// Parameters:
//	nWidth		- Specifies the width of the ellipse used to draw the rounded corners. 
//	nHeight		- Specifies the height of the ellipse used to draw the rounded corners. 
//--------------------------------------------------------------------------
void CPPHtmlStatic::SetRoundRectRgn(int nWidth, int nHeight)
{
	m_nRoundX = nWidth;
	m_nRoundY = nHeight;
	SetRgn(CreateRegion());
	m_bRectRgn = TRUE;
} //End of SetRoundRectRgn

void CPPHtmlStatic::SetMargins(int nXMargin /*= 0*/, int nYMargin /*= 0*/)
{
	m_szTextMargin.cx = nXMargin;
	m_szTextMargin.cy = nYMargin;
	UpdateSurface();
} //End of SetMargins

////////////////////////////////////////////////////////////////////
// CPPToolTip::SetBorder()
//	Sets a border of the static.
//------------------------------------------------------------------
// Parameters:
//		color			- Color of the static's border
//		hbr				- Brush for drawing static's border
//      nWidth			- A width of the brush
//		nHeight			- A height of the brush
////////////////////////////////////////////////////////////////////
void CPPHtmlStatic::SetBorder(COLORREF color, int nWidth /* = 1 */, int nHeight /* = 1 */)
{
	HBRUSH hbr = ::CreateSolidBrush(color);
	SetBorder(hbr, nWidth, nHeight);
} //End of SetBorder

void CPPHtmlStatic::SetBorder(HBRUSH hbr, int nWidth /* = 1 */, int nHeight /* = 1 */)
{
	if (NULL != m_hbrBorder)
	{
		::DeleteObject(m_hbrBorder);
		m_hbrBorder = NULL;
	} //if

	if (nWidth && nHeight && (NULL != hbr))
	{
		m_hbrBorder = hbr;
		m_szBorder.cx = nWidth;
		m_szBorder.cy = nHeight;
	} //if
	UpdateSurface();
} //End of SetBorder

void CPPHtmlStatic::SetWrapText(BOOL bWrapText)
{
	DWORD dwStyle = GetStyle();
	if (bWrapText) 
		ModifyStyle(SS_LEFTNOWORDWRAP, 0);
	else 
		ModifyStyle(0, SS_LEFTNOWORDWRAP);
	UpdateSurface();
}
