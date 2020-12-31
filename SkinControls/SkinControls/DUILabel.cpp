
#include "StdAfx.h"
#include "DUILabel.h"
#include "DUIManager.h"
#include "SkinHelper.h"

CDUILabel::CDUILabel()
{
	m_bHyperLink = false;
	m_byStatus = 0;
	m_bMouseHover = false;
	m_clrHover = RGB(250, 0, 0);
	m_bUnderline = true;
}

CDUILabel::~CDUILabel()
{
}

LPCTSTR CDUILabel::GetClass() const
{
	return TEXT("DUILabel");
}

void CDUILabel::PaintText(CDC* pDC)
{
	if (!IsVisible()) return;

	if (!m_strText.IsEmpty())
	{
		pDC->SetBkMode(TRANSPARENT);
		CFont* pFont = &CSkinHelper::GetDefaultFont();
		if (m_pFont) pFont = m_pFont;
		if (m_bHyperLink)
		{
			COLORREF clrOld;
			if (m_byStatus == 1) clrOld = pDC->SetTextColor(m_clrHover);
			else clrOld = pDC->SetTextColor(m_clrTextColor);
			CFont font;
			LOGFONT lf;
			pFont->GetLogFont(&lf);
			lf.lfUnderline = (m_bUnderline && m_byStatus != 0) ? 1 : 0;
			font.CreateFontIndirect(&lf);
			CFont* pOldFont = pDC->SelectObject(&font);
			pDC->DrawText(m_strText, GetPos(), DT_VCENTER | DT_CENTER | DT_SINGLELINE | DT_END_ELLIPSIS);
			pDC->SetTextColor(clrOld);
			pDC->SelectObject(pOldFont);
		}
		else
		{
			CFont* pOldFont = pDC->SelectObject(pFont);
			COLORREF clrOld = pDC->SetTextColor(m_clrTextColor);
			pDC->DrawText(m_strText, GetPos(), m_uTextFormat);
			pDC->SetTextColor(clrOld);
			pDC->SelectObject(pOldFont);
		}
	}
}

void CDUILabel::SetHyperLink(bool bHyperLink, COLORREF clrTextNormal, COLORREF clrTextHover, bool bUnderline)
{
	m_bHyperLink = bHyperLink;
	m_clrTextColor = clrTextNormal;
	m_clrHover = clrTextHover;
	m_bUnderline = bUnderline;
}

void CDUILabel::SetAttribute(LPCTSTR lpszName, LPCTSTR lpszValue)
{
	if (_tcscmp(lpszName, TEXT("hovercolor")) == 0)
	{
		BYTE r, g, b;
		LPTSTR lpstr = NULL;
		r = (BYTE)_tcstoul(lpszValue, &lpstr, 10); ASSERT(lpstr);
		g = (BYTE)_tcstoul(lpstr + 1, &lpstr, 10); ASSERT(lpstr);
		b = (BYTE)_tcstoul(lpstr + 1, &lpstr, 10); ASSERT(lpstr);
		m_clrHover = RGB(r, g, b);
	}
	else if (_tcscmp(lpszName, TEXT("hyperlink")) == 0) m_bHyperLink = (_tcscmp(lpszValue, TEXT("true")) == 0);
	else if (_tcscmp(lpszName, TEXT("underline")) == 0) m_bUnderline = (_tcscmp(lpszValue, TEXT("true")) == 0);
	else CDUIControl::SetAttribute(lpszName, lpszValue);
}

void CDUILabel::UpdateSkinInfo(LPCTSTR lpszName, LPCTSTR lpszValue)
{
	if (_tcscmp(lpszName, TEXT("hovercolor")) == 0)
	{
		BYTE r, g, b;
		LPTSTR lpstr = NULL;
		r = (BYTE)_tcstoul(lpszValue, &lpstr, 10); ASSERT(lpstr);
		g = (BYTE)_tcstoul(lpstr + 1, &lpstr, 10); ASSERT(lpstr);
		b = (BYTE)_tcstoul(lpstr + 1, &lpstr, 10); ASSERT(lpstr);
		m_clrHover = RGB(r, g, b);
	}
	else CDUIControl::SetAttribute(lpszName, lpszValue);
}

// ²Ù×÷Ïà¹Ø
bool CDUILabel::OnMouseMove(const CPoint& point)
{
	if (!IsVisible() || !IsEnabled()) return false;
	CRect rcReal = GetPos();
	bool bInRect = !rcReal.PtInRect(point) ? false : true;

	if (bInRect && !m_bMouseHover)
	{
		m_byStatus = 1;
		m_bMouseHover = true;
		UpdateControl();
		return true;
	}
	else if (!bInRect && m_bMouseHover)
	{
		m_byStatus = 0;
		m_bMouseHover = false;
		UpdateControl();
		return false;
	}

	return bInRect;
}

bool CDUILabel::OnMouseLeave()
{
	if (!IsVisible() || !IsEnabled()) return false;

	if (m_byStatus != 0)
	{
		m_byStatus = 0;
		UpdateControl();
	}
	return true;
}

bool CDUILabel::OnLButtonDown(const CPoint& point)
{
	if (!IsVisible() || !IsEnabled()) return false;
	CRect rcReal = GetPos();
	bool bInRect = !rcReal.PtInRect(point) ? false : true;

	if (bInRect)
	{
		m_byStatus = 1;
		UpdateControl();
	}
	return bInRect;
}

bool CDUILabel::OnLButtonUp(const CPoint& point)
{
	if (!IsVisible() || !IsEnabled()) return false;
	CRect rcReal = GetPos();
	bool bInRect = !rcReal.PtInRect(point) ? false : true;

	if (m_byStatus == 1)
	{
		m_byStatus = bInRect ? 1 : 0;
		m_bMouseHover = bInRect;
		UpdateControl();
	}
	return bInRect;
}

bool CDUILabel::OnMouseCursor(const CPoint& point)
{
	if (!IsVisible() || !IsEnabled()) return false;
	CRect rcReal = GetPos();
	bool bInRect = !rcReal.PtInRect(point) ? false : true;
	if (bInRect && m_bHyperLink)
	{
		::SetCursor(CSkinHelper::GetSysHandCursor());
	}
	return bInRect;
}

void CDUILabel::OnClick()
{
	if (!m_bHyperLink) return;
	if (m_pDUIManager == NULL) return;
	CWnd* pOwnerWnd = m_pDUIManager->GetOwnerWnd();
	if (pOwnerWnd == NULL || pOwnerWnd->GetSafeHwnd() == NULL) return;
	pOwnerWnd->SendMessage(WM_DUI_MESSAGE, GetID(), (LPARAM)this);
}
