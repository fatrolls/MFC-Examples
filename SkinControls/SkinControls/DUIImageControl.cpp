
#include "StdAfx.h"
#include "DUIImageControl.h"
#include "DUIManager.h"
#include "SkinHelper.h"

CDUIImageControl::CDUIImageControl()
{
	m_clrTransColor = CLR_NONE;
	m_uTextFormat = DT_CENTER|DT_VCENTER|DT_SINGLELINE;
}

CDUIImageControl::~CDUIImageControl()
{
}

LPCTSTR CDUIImageControl::GetClass() const
{
	return TEXT("DUIImageControl");
}

void CDUIImageControl::PaintBkImage(CDC* pDC)
{
	if (!IsVisible()) return;

	if (m_Image.IsValid() && m_pDUIManager!= NULL)
	{
		CRect rcReal = GetPos();
		m_Image.DrawImage(pDC, rcReal.left, rcReal.top, rcReal.Width(), rcReal.Height(), m_clrTransColor);
	}
}

void CDUIImageControl::PaintText(CDC* pDC)
{
	if (!IsVisible()) return;

	if (!m_strText.IsEmpty())
	{
		pDC->SetBkMode(TRANSPARENT);
		COLORREF clrOld = pDC->SetTextColor(m_clrTextColor);
		CFont* pFont = &CSkinHelper::GetDefaultFont();
		if (m_pFont) pFont = m_pFont;
		CFont* pOldFont = pDC->SelectObject(pFont);
		CRect rcText = GetPos();
		pDC->DrawText(m_strText, &rcText, m_uTextFormat);
		pDC->SetTextColor(clrOld);
		pDC->SelectObject(pOldFont);
	}
}

void CDUIImageControl::SetAttribute(LPCTSTR lpszName, LPCTSTR lpszValue)
{
	if (_tcscmp(lpszName, TEXT("image")) == 0) m_Image.LoadFromFile(lpszValue);
	else if (_tcscmp(lpszName, TEXT("transcolor")) == 0)
	{
		BYTE r, g, b;
		LPTSTR lpstr = NULL;
		r = (BYTE)_tcstoul(lpszValue, &lpstr, 10); ASSERT(lpstr);
		g = (BYTE)_tcstoul(lpstr + 1, &lpstr, 10); ASSERT(lpstr);
		b = (BYTE)_tcstoul(lpstr + 1, &lpstr, 10); ASSERT(lpstr);
		m_clrTransColor = RGB(r, g, b);
	}
	else CDUIControl::SetAttribute(lpszName, lpszValue);
}

void CDUIImageControl::UpdateSkinInfo(LPCTSTR lpszName, LPCTSTR lpszValue)
{
	if (_tcscmp(lpszName, TEXT("image")) == 0)
	{
		m_Image.LoadFromFile(lpszValue);
	}
	else if (_tcscmp(lpszName, TEXT("transcolor")) == 0)
	{
		BYTE r, g, b;
		LPTSTR lpstr = NULL;
		r = (BYTE)_tcstoul(lpszValue, &lpstr, 10); ASSERT(lpstr);
		g = (BYTE)_tcstoul(lpstr + 1, &lpstr, 10); ASSERT(lpstr);
		b = (BYTE)_tcstoul(lpstr + 1, &lpstr, 10); ASSERT(lpstr);
		m_clrTransColor = RGB(r, g, b);
	}
	else CDUIControl::SetAttribute(lpszName, lpszValue);
}
