
#include "StdAfx.h"
#include "DUISlider.h"
#include "DUIManager.h"

CDUISlider::CDUISlider()
{
	m_byButtonState = 0;
	m_clrThumbTrans = CLR_NONE;
	m_szThumb.SetSize(0, 0);
	m_bMouseHover = false;
	m_bLButtonDown = false;
}

CDUISlider::~CDUISlider()
{
}

LPCTSTR CDUISlider::GetClass() const
{
	return TEXT("DUISlider");
}

void CDUISlider::PaintStatusImage(CDC* pDC)
{
	if (!IsVisible()) return;

	//CDUIProgress::PaintStatusImage(pDC);
	if( m_nMax <= m_nMin ) m_nMax = m_nMin + 1;
	if( m_nPos > m_nMax ) m_nPos = m_nMax;
	if( m_nPos < m_nMin ) m_nPos = m_nMin;

	int cxsrc = 0;
	int cysrc = 0;
	CRect rcReal = GetPos();
	if (m_bHorizontal)
	{
		cxsrc = (m_nPos - m_nMin) * (rcReal.right - rcReal.left) / (m_nMax - m_nMin);
		cysrc = rcReal.bottom - rcReal.top;
	}
	else
	{
		cxsrc = rcReal.right - rcReal.left;
		cysrc = (rcReal.bottom - rcReal.top) * (m_nMax - m_nPos) / (m_nMax - m_nMin);
	}

	if (m_ImageBg.IsValid())
	{
		if (m_bHorizontal)
			m_ImageBg.DrawImage(pDC, rcReal.left, rcReal.top + (rcReal.Height() - m_ImageBg.GetHeight()) / 2, rcReal.Width(), m_ImageBg.GetHeight(), m_clrBgTrans);
		else
			m_ImageBg.DrawImage(pDC, rcReal.left + (rcReal.Width() - m_ImageBg.GetWidth()) / 2, rcReal.top, m_ImageBg.GetWidth(), rcReal.Height(), m_clrBgTrans);
	}

	CRect rcThumb = GetThumbRect();

	if (m_ImageProgress.IsValid())
	{
		CRect rcTemp = rcThumb;
		rcTemp.left -= rcReal.left;
		rcTemp.top -= rcReal.top;
		rcTemp.right -= rcReal.left;
		rcTemp.bottom -= rcReal.top;
		if (m_bHorizontal)
		{
			m_ImageProgress.DrawImage(pDC, rcReal.left, rcReal.top + (rcReal.Height() - m_ImageProgress.GetHeight()) / 2, rcTemp.left,
				m_ImageProgress.GetHeight(), m_clrProgressTrans);
		}
		else
		{
			m_ImageProgress.DrawImage(pDC, rcReal.left + (rcReal.Width() - m_ImageProgress.GetWidth()) / 2, rcReal.top,
				m_ImageProgress.GetWidth(), rcTemp.top, m_clrProgressTrans);
		}
	}

	if (m_ImageThumb.IsValid())
	{
		m_ImageThumb.DrawImage(pDC, rcThumb.left, rcThumb.top, m_szThumb.cx, m_szThumb.cy, m_byButtonState * m_szThumb.cx, 0,
			m_szThumb.cx, m_szThumb.cy, m_clrThumbTrans);
	}
}

// ²Ù×÷Ïà¹Ø
bool CDUISlider::OnMouseMove(const CPoint& point)
{
	if (!IsVisible() || !IsEnabled()) return false;
	CRect rcReal = GetPos();
	bool bInRect = !rcReal.PtInRect(point) ? false : true;

	CRect rcThumb = GetThumbRect();
	bool bInThumb = rcThumb.PtInRect(point) == TRUE ? true : false;
	if (m_bLButtonDown)
	{
		if (m_bHorizontal)
		{
			if (point.x >= rcReal.right - m_szThumb.cx / 2 ) m_nPos = m_nMax;
			else if (point.x <= rcReal.left + m_szThumb.cx / 2 ) m_nPos = m_nMin;
			else m_nPos = m_nMin + (m_nMax - m_nMin) * (point.x - rcReal.left - m_szThumb.cx / 2) / (rcReal.right - rcReal.left - m_szThumb.cx);
		}
		else
		{
			if (point.y >= rcReal.bottom - m_szThumb.cy / 2 ) m_nPos = m_nMin;
			else if (point.y <= rcReal.top + m_szThumb.cy / 2  ) m_nPos = m_nMax;
			else m_nPos = m_nMin + (m_nMax - m_nMin) * (rcReal.bottom - point.y - m_szThumb.cy / 2) / (rcReal.bottom - rcReal.top - m_szThumb.cy);
		}
		UpdateControl();
		return true;
	}
	else if (bInRect && !m_bMouseHover && bInThumb)
	{
		m_byButtonState = 1;
		m_bMouseHover = true;
		UpdateControl();
		return true;
	}
	else if (!bInRect && m_bMouseHover)
	{
		m_byButtonState = 0;
		m_bMouseHover = false;
		UpdateControl();
		return false;
	}

	return bInRect;
}

bool CDUISlider::OnMouseLeave()
{
	if (!IsVisible() || !IsEnabled()) return false;

	m_bMouseHover = false;
	if (m_byButtonState != 0)
	{
		m_byButtonState = 0;
		UpdateControl();
	}
	m_bLButtonDown = false;
	return true;
}

bool CDUISlider::OnLButtonDown(const CPoint& point)
{
	if (!IsVisible() || !IsEnabled()) return false;
	CRect rcReal = GetPos();
	bool bInRect = !rcReal.PtInRect(point) ? false : true;

	CRect rcThumb = GetThumbRect();
	if (bInRect && rcThumb.PtInRect(point) == TRUE)
	{
		if (m_pDUIManager != NULL && m_pDUIManager->GetOwnerWnd() && m_pDUIManager->GetOwnerWnd()->GetSafeHwnd())
		{
			m_pDUIManager->GetOwnerWnd()->SetCapture();
			m_bLButtonDown = true;
		}
		m_byButtonState = 2;
		UpdateControl();
	}
	else if (bInRect)
	{
		if (m_bHorizontal)
		{
			if (point.x >= rcReal.right - m_szThumb.cx / 2 ) m_nPos = m_nMax;
			else if (point.x <= rcReal.left + m_szThumb.cx / 2 ) m_nPos = m_nMin;
			else m_nPos = m_nMin + (m_nMax - m_nMin) * (point.x - rcReal.left - m_szThumb.cx / 2) / (rcReal.right - rcReal.left - m_szThumb.cx);
		}
		else
		{
			if (point.y >= rcReal.bottom - m_szThumb.cy / 2 ) m_nPos = m_nMin;
			else if (point.y <= rcReal.top + m_szThumb.cy / 2  ) m_nPos = m_nMax;
			else m_nPos = m_nMin + (m_nMax - m_nMin) * (rcReal.bottom - point.y - m_szThumb.cy / 2) / (rcReal.bottom - rcReal.top - m_szThumb.cy);
		}
		UpdateControl();
		if (m_pDUIManager != NULL && m_pDUIManager->GetOwnerWnd() && m_pDUIManager->GetOwnerWnd()->GetSafeHwnd())
		{
			m_pDUIManager->GetOwnerWnd()->SendMessage(WM_DUI_MESSAGE, GetID(), (LPARAM)this);
		}
	}
	return bInRect;
}

bool CDUISlider::OnLButtonUp(const CPoint& point)
{
	if (!IsVisible() || !IsEnabled()) return false;
	CRect rcReal = GetPos();
	bool bInRect = !rcReal.PtInRect(point) ? false : true;

	ReleaseCapture();
	m_bLButtonDown = false;
	CRect rcThumb = GetThumbRect();
	if (m_byButtonState == 2)
	{
		bool bMouseHover = rcThumb.PtInRect(point) == TRUE ? true : false;
		m_byButtonState = bMouseHover ? 1 : 0;
		m_bMouseHover = bMouseHover;
		if (m_bHorizontal)
		{
			if (point.x >= rcReal.right - m_szThumb.cx / 2 ) m_nPos = m_nMax;
			else if (point.x <= rcReal.left + m_szThumb.cx / 2 ) m_nPos = m_nMin;
			else m_nPos = m_nMin + (m_nMax - m_nMin) * (point.x - rcReal.left - m_szThumb.cx / 2) / (rcReal.right - rcReal.left - m_szThumb.cx);
		}
		else
		{
			if (point.y >= rcReal.bottom - m_szThumb.cy / 2 ) m_nPos = m_nMin;
			else if (point.y <= rcReal.top + m_szThumb.cy / 2  ) m_nPos = m_nMax;
			else m_nPos = m_nMin + (m_nMax - m_nMin) * (rcReal.bottom - point.y - m_szThumb.cy / 2) / (rcReal.bottom - rcReal.top - m_szThumb.cy);
		}
		if (m_pDUIManager != NULL && m_pDUIManager->GetOwnerWnd() && m_pDUIManager->GetOwnerWnd()->GetSafeHwnd())
		{
			m_pDUIManager->GetOwnerWnd()->SendMessage(WM_DUI_MESSAGE, GetID(), (LPARAM)this);
		}
		UpdateControl();
	}
	return bInRect;
}

CRect CDUISlider::GetThumbRect()
{
	CRect rcReal = GetPos();
	if (m_bHorizontal)
	{
		int left = rcReal.left + (rcReal.Width() - m_szThumb.cx) * (m_nPos - m_nMin) / (m_nMax - m_nMin);
		int top = (rcReal.bottom + rcReal.top - m_szThumb.cy) / 2;
		return CRect(left, top, left + m_szThumb.cx, top + m_szThumb.cy); 
	}
	else
	{
		int left = (rcReal.right + rcReal.left - m_szThumb.cx) / 2;
		int top = rcReal.bottom - m_szThumb.cy - (rcReal.bottom - rcReal.top - m_szThumb.cy) * (m_nPos - m_nMin) / (m_nMax - m_nMin);
		return CRect(left, top, left + m_szThumb.cx, top + m_szThumb.cy); 
	}
}

void CDUISlider::SetThumbImage(LPCTSTR lpszThumb, BitmapFormat bf, COLORREF clrTrans)
{
	m_ImageThumb.LoadFromFile(lpszThumb, bf);
	m_clrThumbTrans = clrTrans;
	if (m_ImageThumb.IsValid())
	{
		m_szThumb.cx = m_ImageThumb.GetWidth() / 3;
		m_szThumb.cy = m_ImageThumb.GetHeight();
	}
}

void CDUISlider::SetAttribute(LPCTSTR lpszName, LPCTSTR lpszValue)
{
	if (_tcscmp(lpszName, TEXT("thumbtranscolor")) == 0)
	{
		BYTE r, g, b;
		LPTSTR lpstr = NULL;
		r = (BYTE)_tcstoul(lpszValue, &lpstr, 10); ASSERT(lpstr);
		g = (BYTE)_tcstoul(lpstr + 1, &lpstr, 10); ASSERT(lpstr);
		b = (BYTE)_tcstoul(lpstr + 1, &lpstr, 10); ASSERT(lpstr);
		m_clrThumbTrans = RGB(r, g, b);
	}
	else if (_tcscmp(lpszName, TEXT("imagethumb")) == 0) m_ImageThumb.LoadFromFile(lpszValue);
	else if (_tcscmp(lpszName, TEXT("thumbsize")) == 0)
	{
		LPTSTR lpstr = NULL;
		m_szThumb.cx = _tcstol(lpszValue, &lpstr, 10); ASSERT(lpstr);
		m_szThumb.cy = _tcstol(lpstr + 1, &lpstr, 10); ASSERT(lpstr);
	}
	else CDUIProgress::SetAttribute(lpszName, lpszValue);
}

void CDUISlider::UpdateSkinInfo(LPCTSTR lpszName, LPCTSTR lpszValue)
{
	if (_tcscmp(lpszName, TEXT("thumbtranscolor")) == 0)
	{
		BYTE r, g, b;
		LPTSTR lpstr = NULL;
		r = (BYTE)_tcstoul(lpszValue, &lpstr, 10); ASSERT(lpstr);
		g = (BYTE)_tcstoul(lpstr + 1, &lpstr, 10); ASSERT(lpstr);
		b = (BYTE)_tcstoul(lpstr + 1, &lpstr, 10); ASSERT(lpstr);
		m_clrThumbTrans = RGB(r, g, b);
	}
	else if (_tcscmp(lpszName, TEXT("imagethumb")) == 0) m_ImageThumb.LoadFromFile(lpszValue);
	else if (_tcscmp(lpszName, TEXT("thumbsize")) == 0)
	{
		LPTSTR lpstr = NULL;
		m_szThumb.cx = _tcstol(lpszValue, &lpstr, 10); ASSERT(lpstr);
		m_szThumb.cy = _tcstol(lpstr + 1, &lpstr, 10); ASSERT(lpstr);
	}
	else CDUIProgress::SetAttribute(lpszName, lpszValue);
}

