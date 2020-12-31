
#include "StdAfx.h"
#include "DUIButton.h"
#include "DUIManager.h"
#include "SkinHelper.h"

CDUIButton::CDUIButton()
{
	m_byStatus = 0;
	m_bMouseHover = false;
	m_clrTrans = CLR_NONE;
	m_uTextFormat = DT_CENTER|DT_VCENTER|DT_SINGLELINE;
}

CDUIButton::~CDUIButton()
{
}

LPCTSTR CDUIButton::GetClass() const
{
	return TEXT("DUIButton");
}

void CDUIButton::PaintText(CDC* pDC)
{
	if (!IsVisible()) return;

	if (!m_strText.IsEmpty())
	{
		pDC->SetBkMode(TRANSPARENT);
		COLORREF clrOld = pDC->SetTextColor(m_clrTextColor);
		CFont* pFont = &CSkinHelper::GetDefaultFont();
		if (m_pFont) pFont = m_pFont;
		CFont* pOldFont = pDC->SelectObject(pFont);
		pDC->DrawText(m_strText, GetPos(), m_uTextFormat);
		pDC->SetTextColor(clrOld);
		pDC->SelectObject(pOldFont);
	}
}

void CDUIButton::PaintStatusImage(CDC* pDC)
{
	if (!IsVisible()) return;

	CRect rcReal = GetPos();
	int nButtonWidth = m_ImageStatus.GetWidth() / 4;
	int nButtonHeight = m_ImageStatus.GetHeight();
	m_ImageStatus.DrawImage(pDC, rcReal.left, rcReal.top, nButtonWidth, nButtonHeight, m_byStatus * nButtonWidth, 0, nButtonWidth, nButtonHeight, m_clrTrans);
}

// ²Ù×÷Ïà¹Ø
bool CDUIButton::OnMouseMove(const CPoint& point)
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

bool CDUIButton::OnMouseLeave()
{
	if ((IsVisible() == false) || (IsEnabled() == false)) return false;

	m_bMouseHover = false;
	if (m_byStatus != 0)
	{
		m_byStatus = 0;
		UpdateControl();
	}
	return true;
}

bool CDUIButton::OnLButtonDown(const CPoint& point)
{
	if (!IsVisible() || !IsEnabled()) return false;
	CRect rcReal = GetPos();
	bool bInRect = !rcReal.PtInRect(point) ? false : true;

	if (bInRect)
	{
		m_byStatus = 2;
		UpdateControl();
	}
	return bInRect;
}

bool CDUIButton::OnLButtonUp(const CPoint& point)
{
	if (!IsVisible() || !IsEnabled()) return false;
	CRect rcReal = GetPos();
	bool bInRect = !rcReal.PtInRect(point) ? false : true;

	if (m_byStatus == 2)
	{
		m_byStatus = bInRect ? 1 : 0;
		m_bMouseHover = bInRect;
		UpdateControl();
	}
	return bInRect;
}

void CDUIButton::SetEnabled(bool bEnable, bool bReDraw)
{
	m_bEnabled = bEnable;
	m_byStatus = !bEnable ? 3 : 0;
	if (bReDraw) UpdateControl();
}

void CDUIButton::SetImage(LPCTSTR lpszFileName, BitmapFormat bf, COLORREF clrTrans)
{
	m_clrTrans = clrTrans;
	m_ImageStatus.LoadFromFile(lpszFileName, bf);
}

void CDUIButton::SetAttribute(LPCTSTR lpszName, LPCTSTR lpszValue)
{
	if (_tcscmp(lpszName, TEXT("image")) == 0) m_ImageStatus.LoadFromFile(lpszValue);
	else if (_tcscmp(lpszName, TEXT("imagetranscolor")) == 0)
	{
		BYTE r, g, b;
		LPTSTR lpstr = NULL;
		r = (BYTE)_tcstoul(lpszValue, &lpstr, 10); ASSERT(lpstr);
		g = (BYTE)_tcstoul(lpstr + 1, &lpstr, 10); ASSERT(lpstr);
		b = (BYTE)_tcstoul(lpstr + 1, &lpstr, 10); ASSERT(lpstr);
		m_clrTrans = RGB(r, g, b);
	}
	else CDUIControl::SetAttribute(lpszName, lpszValue);
}

void CDUIButton::UpdateSkinInfo(LPCTSTR lpszName, LPCTSTR lpszValue)
{
	if (_tcscmp(lpszName, TEXT("image")) == 0)
	{
		m_ImageStatus.LoadFromFile(lpszValue);
	}
	else if (_tcscmp(lpszName, TEXT("imagetranscolor")) == 0)
	{
		BYTE r, g, b;
		LPTSTR lpstr = NULL;
		r = (BYTE)_tcstoul(lpszValue, &lpstr, 10); ASSERT(lpstr);
		g = (BYTE)_tcstoul(lpstr + 1, &lpstr, 10); ASSERT(lpstr);
		b = (BYTE)_tcstoul(lpstr + 1, &lpstr, 10); ASSERT(lpstr);
		m_clrTrans = RGB(r, g, b);
	}
	else CDUIControl::UpdateSkinInfo(lpszName, lpszValue);
}

void CDUIButton::OnClick()
{
	if (m_pDUIManager == NULL) return;
	CWnd* pOwnerWnd = m_pDUIManager->GetOwnerWnd();
	if (pOwnerWnd == NULL || pOwnerWnd->GetSafeHwnd() == NULL) return;
	pOwnerWnd->SendMessage(WM_DUI_MESSAGE, GetID(), (LPARAM)this);
}
