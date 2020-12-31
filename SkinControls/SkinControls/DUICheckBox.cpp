
#include "StdAfx.h"
#include "DUICheckBox.h"
#include "DUIManager.h"
#include "SkinHelper.h"

CDUICheckBox::CDUICheckBox()
{
	m_bCheck = false;
	m_uTextFormat = DT_LEFT|DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS;
}

CDUICheckBox::~CDUICheckBox()
{
}

LPCTSTR CDUICheckBox::GetClass() const
{
	return TEXT("DUICheckBox");
}

void CDUICheckBox::PaintText(CDC* pDC)
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
		rcText.left += m_ImageStatus.GetWidth() / 8 + 4;
		pDC->DrawText(m_strText, &rcText, m_uTextFormat);
		pDC->SetTextColor(clrOld);
		pDC->SelectObject(pOldFont);
	}
}

void CDUICheckBox::PaintStatusImage(CDC* pDC)
{
	if (!IsVisible()) return;

	CRect rcReal = GetPos();
	int nButtonWidth = m_ImageStatus.GetWidth() / 8;
	int nButtonHeight = m_ImageStatus.GetHeight();
	m_ImageStatus.DrawImage(pDC, rcReal.left, rcReal.top, nButtonWidth, nButtonHeight, 
		(m_bCheck ? (m_byStatus + 4): (m_byStatus)) * nButtonWidth, 0, nButtonWidth, nButtonHeight, m_clrTrans);
}

void CDUICheckBox::SetAttribute(LPCTSTR lpszName, LPCTSTR lpszValue)
{
	if (_tcscmp(lpszName, TEXT("checked")) == 0) SetCheck((_tcscmp(lpszValue, TEXT("true")) == 0));
	else CDUIButton::SetAttribute(lpszName, lpszValue);
}

void CDUICheckBox::SetCheck(bool bCheck, bool bRedraw)
{
	m_bCheck = bCheck;
	if (bRedraw) UpdateControl();
}

void CDUICheckBox::OnClick()
{
	if (m_pDUIManager == NULL) return;
	CWnd* pOwnerWnd = m_pDUIManager->GetOwnerWnd();
	if (pOwnerWnd == NULL || pOwnerWnd->GetSafeHwnd() == NULL) return;
	pOwnerWnd->SendMessage(WM_DUI_MESSAGE, GetID(), (LPARAM)this);
	SetCheck(!m_bCheck, true);
}

