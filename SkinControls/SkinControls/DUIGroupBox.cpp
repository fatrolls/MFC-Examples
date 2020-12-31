
#include "StdAfx.h"
#include "DUIGroupBox.h"
#include "SkinHelper.h"

CDUIGroupBox::CDUIGroupBox()
{
	m_clrBorder = RGB(0, 87, 233);
}

CDUIGroupBox::~CDUIGroupBox()
{
}

LPCTSTR CDUIGroupBox::GetClass() const
{
	return TEXT("DUIGroupBox");
}

void CDUIGroupBox::PaintText(CDC* pDC)
{
	if (!IsVisible()) return;

	pDC->SetBkMode(TRANSPARENT);
	COLORREF clrOld = pDC->SetTextColor(m_clrTextColor);
	CFont* pFont = &CSkinHelper::GetDefaultFont();
	if (m_pFont) pFont = m_pFont;
	CFont* pOldFont = pDC->SelectObject(pFont);

	CPen pen;
	pen.CreatePen(PS_SOLID, 1, m_clrBorder);
	CPen* pOldPen = pDC->SelectObject(&pen);
	pDC->SelectObject(::GetStockObject(NULL_BRUSH));
	CRect rcBorder = GetPos();
	CSize sizeText(0, 0);
	if (!m_strText.IsEmpty())
	{
		sizeText = pDC->GetTextExtent(m_strText);
	}
	rcBorder.top += sizeText.cy / 2;
	int nOldMode = pDC->SetROP2(R2_NOTXORPEN);
	pDC->RoundRect(rcBorder, CPoint(8, 8));
	pDC->SetROP2(nOldMode);

	if (!m_strText.IsEmpty())
	{
		CRect rcText = GetPos();
		rcText.left += 10;
		rcText.right = rcText.left + sizeText.cx + 10;
		rcText.bottom = rcText.top + sizeText.cy;

		nOldMode = pDC->SetROP2(R2_NOTXORPEN);
		pDC->MoveTo(rcText.left, rcBorder.top);
		pDC->LineTo(rcText.right, rcBorder.top);
		pDC->DrawText(m_strText, &rcText, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		pDC->SetROP2(nOldMode);
	}

	pDC->SetTextColor(clrOld);
	pDC->SelectObject(pOldPen);
	pDC->SelectObject(pOldFont);
}

void CDUIGroupBox::SetAttribute(LPCTSTR lpszName, LPCTSTR lpszValue)
{
	if (_tcscmp(lpszName, TEXT("bordercolor")) == 0)
	{
		BYTE r, g, b;
		LPTSTR lpstr = NULL;
		r = (BYTE)_tcstoul(lpszValue, &lpstr, 10); ASSERT(lpstr);
		g = (BYTE)_tcstoul(lpstr + 1, &lpstr, 10); ASSERT(lpstr);
		b = (BYTE)_tcstoul(lpstr + 1, &lpstr, 10); ASSERT(lpstr);
		SetBorderColor(RGB(r, g, b));
	}
	else CDUIControl::SetAttribute(lpszName, lpszValue);
}

void CDUIGroupBox::UpdateSkinInfo(LPCTSTR lpszName, LPCTSTR lpszValue)
{
	if (_tcscmp(lpszName, TEXT("bordercolor")) == 0)
	{
		BYTE r, g, b;
		LPTSTR lpstr = NULL;
		r = (BYTE)_tcstoul(lpszValue, &lpstr, 10); ASSERT(lpstr);
		g = (BYTE)_tcstoul(lpstr + 1, &lpstr, 10); ASSERT(lpstr);
		b = (BYTE)_tcstoul(lpstr + 1, &lpstr, 10); ASSERT(lpstr);
		SetBorderColor(RGB(r, g, b));
	}
	else CDUIControl::SetAttribute(lpszName, lpszValue);
}

void CDUIGroupBox::SetBorderColor(COLORREF clrBorder)
{
	m_clrBorder = clrBorder;
}

// ²Ù×÷Ïà¹Ø
bool CDUIGroupBox::OnMouseMove(const CPoint& point)
{
	return false;
}

bool CDUIGroupBox::OnMouseLeave()
{
	return false;
}

bool CDUIGroupBox::OnLButtonDown(const CPoint& point)
{
	return false;
}

bool CDUIGroupBox::OnLButtonUp(const CPoint& point)
{
	return false;
}

bool CDUIGroupBox::OnRButtonDown(const CPoint& point)
{
	return false;
}

bool CDUIGroupBox::OnRButtonUp(const CPoint& point)
{
	return false;
}

bool CDUIGroupBox::OnMouseCursor(const CPoint& point)
{
	return false;
}
