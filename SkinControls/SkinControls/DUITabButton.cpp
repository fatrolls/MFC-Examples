
#include "StdAfx.h"
#include "DUITabButton.h"
#include "DUIManager.h"
#include "SkinHelper.h"

CDUITabButton::CDUITabButton()
{
	m_uTextFormat = DT_CENTER|DT_VCENTER|DT_SINGLELINE;
	m_clrCheckTextColor = m_clrTextColor;
}

CDUITabButton::~CDUITabButton()
{
}

LPCTSTR CDUITabButton::GetClass() const
{
	return TEXT("DUITabButton");
}

void CDUITabButton::PaintText(CDC* pDC)
{
	if (!IsVisible()) return;

	if (!m_strText.IsEmpty())
	{
		pDC->SetBkMode(TRANSPARENT);
		COLORREF clrOld = pDC->SetTextColor(m_clrTextColor);
		if (m_bCheck) clrOld = pDC->SetTextColor(m_clrCheckTextColor);
		CFont* pFont = &CSkinHelper::GetDefaultFont();
		if (m_pFont) pFont = m_pFont;
		CFont* pOldFont = pDC->SelectObject(pFont);
		CRect rcText = GetPos();
		pDC->DrawText(m_strText, &rcText, m_uTextFormat);
		pDC->SetTextColor(clrOld);
		pDC->SelectObject(pOldFont);
	}
}

void CDUITabButton::PaintStatusImage(CDC* pDC)
{
	if (!IsVisible()) return;

	CRect rcReal = GetPos();
	int nButtonWidth = m_ImageStatus.GetWidth() / 3;
	int nButtonHeight = m_ImageStatus.GetHeight();
	int nImagePos = 0;
	if (m_bCheck) nImagePos = 2 * nButtonWidth;
	else if (m_bMouseHover) nImagePos = nButtonWidth;
	m_ImageStatus.DrawImage(pDC, rcReal.left, rcReal.top, nButtonWidth, nButtonHeight, 
		nImagePos, 0, nButtonWidth, nButtonHeight, m_clrTrans);

	if (m_ImageStatus2.IsValid())
	{
		nButtonWidth = m_ImageStatus2.GetWidth() / 3;
		nButtonHeight = m_ImageStatus2.GetHeight();
		nImagePos = 0;
		if (m_bCheck) nImagePos = 2 * nButtonWidth;
		else if (m_bMouseHover) nImagePos = nButtonWidth;
		m_ImageStatus2.DrawImage(pDC, rcReal.left, rcReal.top, nButtonWidth, nButtonHeight, 
			nImagePos, 0, nButtonWidth, nButtonHeight);
	}
}

void CDUITabButton::SetAttribute(LPCTSTR lpszName, LPCTSTR lpszValue)
{
	if (_tcscmp(lpszName, TEXT("image2")) == 0) m_ImageStatus2.LoadFromFile(lpszValue);
	else if (_tcscmp(lpszName, TEXT("checktextcolor")) == 0)
	{
		BYTE r, g, b;
		LPTSTR lpstr = NULL;
		r = (BYTE)_tcstoul(lpszValue, &lpstr, 10); ASSERT(lpstr);
		g = (BYTE)_tcstoul(lpstr + 1, &lpstr, 10); ASSERT(lpstr);
		b = (BYTE)_tcstoul(lpstr + 1, &lpstr, 10); ASSERT(lpstr);
		m_clrCheckTextColor = RGB(r, g, b);
	}
	else CDUIRadioBox::SetAttribute(lpszName, lpszValue);
}

void CDUITabButton::UpdateSkinInfo(LPCTSTR lpszName, LPCTSTR lpszValue)
{
	if (_tcscmp(lpszName, TEXT("image2")) == 0) m_ImageStatus2.LoadFromFile(lpszValue);
	else if (_tcscmp(lpszName, TEXT("checktextcolor")) == 0)
	{
		BYTE r, g, b;
		LPTSTR lpstr = NULL;
		r = (BYTE)_tcstoul(lpszValue, &lpstr, 10); ASSERT(lpstr);
		g = (BYTE)_tcstoul(lpstr + 1, &lpstr, 10); ASSERT(lpstr);
		b = (BYTE)_tcstoul(lpstr + 1, &lpstr, 10); ASSERT(lpstr);
		m_clrCheckTextColor = RGB(r, g, b);
	}
	else CDUIRadioBox::SetAttribute(lpszName, lpszValue);
}

void CDUITabButton::SetCheckTextColor(COLORREF clrCheckText, bool bRedraw)
{
	m_clrCheckTextColor = clrCheckText;
	if (bRedraw) UpdateControl();
}

void CDUITabButton::SetImage2(LPCTSTR lpszFileName, BitmapFormat bf)
{
	m_ImageStatus2.LoadFromFile(lpszFileName, bf);
}

