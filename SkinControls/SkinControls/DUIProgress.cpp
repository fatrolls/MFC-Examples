
#include "StdAfx.h"
#include "DUIProgress.h"

CDUIProgress::CDUIProgress()
{
	m_bHorizontal = true;
	m_nMax = 100;
	m_nMin = 0;
	m_nPos = 0;
	m_clrProgressTrans = CLR_NONE;
	m_clrBgTrans = CLR_NONE;
}

CDUIProgress::~CDUIProgress()
{
}

LPCTSTR CDUIProgress::GetClass() const
{
	return TEXT("DUIProgress");
}

void CDUIProgress::PaintStatusImage(CDC* pDC)
{
	if (!IsVisible()) return;

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
		m_ImageBg.DrawImage(pDC, rcReal.left, rcReal.top, rcReal.Width(), rcReal.Height(), m_clrBgTrans);
	if (m_ImageProgress.IsValid())
		m_ImageProgress.DrawImage(pDC, rcReal.left, rcReal.top, cxsrc, cysrc, m_clrProgressTrans);
}

void CDUIProgress::SetRange(int nLower, int nUpper)
{
	m_nMin = nLower;
	m_nMax = nUpper;
}

void CDUIProgress::GetRange(int& nLower, int& nUpper) const
{
	nLower = m_nMin;
	nUpper = m_nMax;
}

int CDUIProgress::GetValue() const
{
	return m_nPos;
}

void CDUIProgress::SetValue(int nPos, bool bRedraw)
{
	m_nPos = nPos;
	if (bRedraw) UpdateControl();
}

void CDUIProgress::SetBgImage(LPCTSTR lpszBg, BitmapFormat bf, COLORREF clrTrans)
{
	m_ImageBg.LoadFromFile(lpszBg, bf);
	m_clrBgTrans = clrTrans;
}

void CDUIProgress::SetProgressImage(LPCTSTR lpszProgress, BitmapFormat bf, COLORREF clrTrans)
{
	m_ImageProgress.LoadFromFile(lpszProgress, bf);
	m_clrProgressTrans = clrTrans;
}

bool CDUIProgress::IsHorizontal() const
{
	return m_bHorizontal;
}

void CDUIProgress::SetHorizontal(bool bHorizontal)
{
	if( m_bHorizontal == bHorizontal ) return;

	m_bHorizontal = bHorizontal;
}

void CDUIProgress::SetAttribute(LPCTSTR lpszName, LPCTSTR lpszValue)
{
	if (_tcscmp(lpszName, TEXT("imagebgtranscolor")) == 0)
	{
		BYTE r, g, b;
		LPTSTR lpstr = NULL;
		r = (BYTE)_tcstoul(lpszValue, &lpstr, 10); ASSERT(lpstr);
		g = (BYTE)_tcstoul(lpstr + 1, &lpstr, 10); ASSERT(lpstr);
		b = (BYTE)_tcstoul(lpstr + 1, &lpstr, 10); ASSERT(lpstr);
		m_clrBgTrans = RGB(r, g, b);
	}
	else if (_tcscmp(lpszName, TEXT("imageprotranscolor")) == 0)
	{
		BYTE r, g, b;
		LPTSTR lpstr = NULL;
		r = (BYTE)_tcstoul(lpszValue, &lpstr, 10); ASSERT(lpstr);
		g = (BYTE)_tcstoul(lpstr + 1, &lpstr, 10); ASSERT(lpstr);
		b = (BYTE)_tcstoul(lpstr + 1, &lpstr, 10); ASSERT(lpstr);
		m_clrProgressTrans = RGB(r, g, b);
	}
	else if (_tcscmp(lpszName, TEXT("horizontal")) == 0) SetHorizontal((_tcscmp(lpszValue, TEXT("true")) == 0));
	else if (_tcscmp(lpszName, TEXT("imagebg")) == 0) m_ImageBg.LoadFromFile(lpszValue);
	else if (_tcscmp(lpszName, TEXT("imageprogress")) == 0) m_ImageProgress.LoadFromFile(lpszValue);
	else if (_tcscmp(lpszName, TEXT("max")) == 0) m_nMax = _tcstol(lpszValue, NULL, 10);
	else if (_tcscmp(lpszName, TEXT("min")) == 0) m_nMin = _tcstol(lpszValue, NULL, 10);
	else if (_tcscmp(lpszName, TEXT("value")) == 0) m_nPos = _tcstol(lpszValue, NULL, 10);
	else CDUIControl::SetAttribute(lpszName, lpszValue);
}

void CDUIProgress::UpdateSkinInfo(LPCTSTR lpszName, LPCTSTR lpszValue)
{
	if (_tcscmp(lpszName, TEXT("imagebgtranscolor")) == 0)
	{
		BYTE r, g, b;
		LPTSTR lpstr = NULL;
		r = (BYTE)_tcstoul(lpszValue, &lpstr, 10); ASSERT(lpstr);
		g = (BYTE)_tcstoul(lpstr + 1, &lpstr, 10); ASSERT(lpstr);
		b = (BYTE)_tcstoul(lpstr + 1, &lpstr, 10); ASSERT(lpstr);
		m_clrBgTrans = RGB(r, g, b);
	}
	else if (_tcscmp(lpszName, TEXT("imageprotranscolor")) == 0)
	{
		BYTE r, g, b;
		LPTSTR lpstr = NULL;
		r = (BYTE)_tcstoul(lpszValue, &lpstr, 10); ASSERT(lpstr);
		g = (BYTE)_tcstoul(lpstr + 1, &lpstr, 10); ASSERT(lpstr);
		b = (BYTE)_tcstoul(lpstr + 1, &lpstr, 10); ASSERT(lpstr);
		m_clrProgressTrans = RGB(r, g, b);
	}
	else if (_tcscmp(lpszName, TEXT("imagebg")) == 0) m_ImageBg.LoadFromFile(lpszValue);
	else if (_tcscmp(lpszName, TEXT("imageprogress")) == 0) m_ImageProgress.LoadFromFile(lpszValue);
	else CDUIControl::SetAttribute(lpszName, lpszValue);
}

