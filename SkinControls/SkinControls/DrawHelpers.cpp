
#include "StdAfx.h"
#include "DrawHelpers.h"
#include "SystemHelpers.h"

//===========================================================================
// CWindowRect class
//===========================================================================

CWindowRect::CWindowRect(HWND hWnd)
{
	if (::IsWindow(hWnd))
		::GetWindowRect(hWnd, this);
	else
		SetRectEmpty();
}

CWindowRect::CWindowRect(const CWnd* pWnd)
{
	if (::IsWindow(pWnd->GetSafeHwnd()))
		::GetWindowRect(pWnd->GetSafeHwnd(), this);
	else
		SetRectEmpty();
}

//===========================================================================
// CClientRect class
//===========================================================================

CClientRect::CClientRect(HWND hWnd)
{
	if (::IsWindow(hWnd))
		::GetClientRect(hWnd, this);
	else
		SetRectEmpty();
}

CClientRect::CClientRect(const CWnd* pWnd)
{
	if (::IsWindow(pWnd->GetSafeHwnd()))
		::GetClientRect(pWnd->GetSafeHwnd(), this);
	else
		SetRectEmpty();
}

//===========================================================================
// CBufferDC class
//===========================================================================

CBufferDC::CBufferDC(HDC hDestDC, const CRect& rcPaint)
: m_hDestDC (hDestDC)
{
	m_rect = rcPaint;
	Attach (::CreateCompatibleDC (m_hDestDC));
	if (!m_hDC)
		return;

	m_bitmap.Attach (::CreateCompatibleBitmap(
		m_hDestDC, m_rect.right, m_rect.bottom));
	m_hOldBitmap = ::SelectObject (m_hDC, m_bitmap);
}

CBufferDC::CBufferDC(HDC hDestDC, const CRect& rcPaint, const BOOL bHorz /*=FALSE*/)
: m_hDestDC (hDestDC)
{
	m_rect = rcPaint;
	Attach (::CreateCompatibleDC (m_hDestDC));
	if (!m_hDC)
		return;

	m_bitmap.Attach (::CreateCompatibleBitmap(
		m_hDestDC, m_rect.right, m_rect.bottom));
	m_hOldBitmap = ::SelectObject (m_hDC, m_bitmap);
}

CBufferDC::CBufferDC(CPaintDC& paintDC)
{
	m_hDestDC = paintDC.GetSafeHdc();
	m_rect = paintDC.m_ps.rcPaint;

	Attach (::CreateCompatibleDC (m_hDestDC));
	if (!m_hDC)
		return;

	m_bitmap.Attach (::CreateCompatibleBitmap(
		m_hDestDC, max(1, m_rect.right), max(1, m_rect.bottom)));
	m_hOldBitmap = ::SelectObject (m_hDC, m_bitmap);

	CRgn rgn;
	rgn.CreateRectRgnIndirect(&m_rect);

	SelectClipRgn(&rgn);
}

CBufferDC::~CBufferDC()
{
	if (!m_hDC)
		return;

	if (m_hDestDC)
	{
		::BitBlt (m_hDestDC, m_rect.left, m_rect.top, m_rect.Width(),
			m_rect.Height(), m_hDC, m_rect.left, m_rect.top, SRCCOPY);
	}
	::SelectObject (m_hDC, m_hOldBitmap);
}
void CBufferDC::Discard()
{
	m_hDestDC = 0;
}

CDC* CBufferDC::GetDestDC()
{
	return CDC::FromHandle(m_hDestDC);
}

void CBufferDC::TakeSnapshot()
{
	::BitBlt (m_hDC, m_rect.left, m_rect.top, m_rect.Width(),
		m_rect.Height(), m_hDestDC, m_rect.left, m_rect.top, SRCCOPY);
}

//===========================================================================
// CBufferDC class
//===========================================================================

CBufferDCEx::CBufferDCEx(HDC hDestDC, const CRect rcPaint) : m_hDestDC (hDestDC)
{
	m_rect = rcPaint;
	Attach (::CreateCompatibleDC (m_hDestDC));
	m_bitmap = ::CreateCompatibleBitmap(
		m_hDestDC, m_rect.Width(), m_rect.Height());

	m_hOldBitmap = ::SelectObject (m_hDC, m_bitmap);

	SetViewportOrg(-rcPaint.left, -rcPaint.top);
}

CBufferDCEx::~CBufferDCEx()
{
	SetViewportOrg(0, 0);

	::BitBlt (m_hDestDC, m_rect.left, m_rect.top, m_rect.Width(),
		m_rect.Height(), m_hDC, 0, 0, SRCCOPY);
	::SelectObject (m_hDC, m_hOldBitmap);
	::DeleteObject(m_bitmap);
}

//===========================================================================
// CBitmapDC class
//===========================================================================

CBitmapDC::CBitmapDC(CDC* pDC, CBitmap* pBitmap)
: m_hDC(pDC->GetSafeHdc())
{
	m_hOldBitmap = SelectObject(m_hDC, pBitmap->GetSafeHandle());
}


CBitmapDC::CBitmapDC(CDC* pDC, HBITMAP hBitmap)
: m_hDC(pDC->GetSafeHdc())
{
	m_hOldBitmap = SelectObject(m_hDC, hBitmap);
}

CBitmapDC::~CBitmapDC()
{
	::SelectObject(m_hDC, m_hOldBitmap);
}

void CBitmapDC::SetBitmap(CBitmap* pBitmap)
{
	::SelectObject(m_hDC, m_hOldBitmap);
	m_hOldBitmap = SelectObject(m_hDC, pBitmap->GetSafeHandle());
}

//===========================================================================
// CFontDC class
//===========================================================================

CFontDC::CFontDC(CDC* pDC, CFont* pFont)
{
	ASSERT(pDC);

	m_pDC = pDC;
	m_pOldFont = NULL;
	m_clrOldTextColor = CLR_NONE;

	if (pFont)
	{
		SetFont(pFont);
	}
}

CFontDC::CFontDC(CDC* pDC, CFont* pFont, COLORREF clrTextColor)
{
	ASSERT(pDC);
	ASSERT(clrTextColor != CLR_NONE);

	m_pDC = pDC;
	m_pOldFont = NULL;
	m_clrOldTextColor = CLR_NONE;


	if (pFont)
	{
		SetFont(pFont);
	}

	SetColor(clrTextColor);
}

CFontDC::~CFontDC()
{
	ReleaseFont();
	ReleaseColor();
}

void CFontDC::SetFont(CFont* pFont)
{
	if (m_pDC && pFont)
	{
		CFont* pFontPrev = m_pDC->SelectObject(pFont);

		if (!m_pOldFont && pFontPrev)
		{
			m_pOldFont = pFontPrev;
		}
	}
}

void CFontDC::SetColor(COLORREF clrTextColor)
{
	ASSERT(clrTextColor != CLR_NONE);
	ASSERT(m_pDC);

	if (m_pDC && clrTextColor != CLR_NONE)
	{
		COLORREF clrTextColorPrev= m_pDC->SetTextColor(clrTextColor);

		if (m_clrOldTextColor == CLR_NONE)
		{
			m_clrOldTextColor = clrTextColorPrev;
		}
	}
}

void CFontDC::SetFontColor(CFont* pFont, COLORREF clrTextColor)
{
	SetFont(pFont);
	SetColor(clrTextColor);
}

void CFontDC::ReleaseFont()
{
	ASSERT(m_pDC);
	if (m_pDC && m_pOldFont)
	{
		m_pDC->SelectObject(m_pOldFont);
		m_pOldFont = NULL;
	}
}

void CFontDC::ReleaseColor()
{
	ASSERT(m_pDC);
	if (m_pDC && m_clrOldTextColor != CLR_NONE)
	{
		m_pDC->SetTextColor(m_clrOldTextColor);
		m_clrOldTextColor = CLR_NONE;
	}
}

//===========================================================================
// CPenDC class
//===========================================================================

CPenDC::CPenDC(CDC* pDC, CPen* pPen)
: m_hDC(pDC->GetSafeHdc())
{
	m_hOldPen = (HPEN)::SelectObject(m_hDC, pPen->GetSafeHandle());
}

CPenDC::CPenDC(HDC hDC, COLORREF crColor)
: m_hDC (hDC)
{
	VERIFY(m_pen.CreatePen (PS_SOLID, 1, crColor));
	m_hOldPen = (HPEN)::SelectObject (m_hDC, m_pen);
}

CPenDC::~CPenDC ()
{
	::SelectObject (m_hDC, m_hOldPen);
}

void CPenDC::Color(COLORREF crColor)
{
	::SelectObject (m_hDC, m_hOldPen);
	VERIFY(m_pen.DeleteObject());
	VERIFY(m_pen.CreatePen (PS_SOLID, 1, crColor));
	m_hOldPen = (HPEN)::SelectObject (m_hDC, m_pen);
}

COLORREF CPenDC::Color()
{
	LOGPEN logPen;
	m_pen.GetLogPen(&logPen);
	return logPen.lopnColor;
}

//===========================================================================
// CBrushDC class
//===========================================================================

CBrushDC::CBrushDC(HDC hDC, COLORREF crColor)
: m_hDC (hDC)
{
	VERIFY(m_brush.CreateSolidBrush (crColor));
	m_hOldBrush = (HBRUSH)::SelectObject (m_hDC, m_brush);
}

CBrushDC::~CBrushDC()
{
	::SelectObject(m_hDC, m_hOldBrush);
}

void CBrushDC::Color(COLORREF crColor)
{
	::SelectObject(m_hDC, m_hOldBrush);
	VERIFY(m_brush.DeleteObject());
	VERIFY(m_brush.CreateSolidBrush(crColor));
	m_hOldBrush = (HBRUSH)::SelectObject (m_hDC, m_brush);
}

//===========================================================================
// CCompatibleDC class
//===========================================================================

CCompatibleDC::CCompatibleDC(CDC* pDC, CBitmap* pBitmap)
{
	CreateCompatibleDC(pDC);
	m_hOldBitmap = (HBITMAP)::SelectObject(GetSafeHdc(), pBitmap->GetSafeHandle());
}

CCompatibleDC::CCompatibleDC(CDC* pDC, HBITMAP hBitmap)
{
	CreateCompatibleDC(pDC);
	m_hOldBitmap = (HBITMAP)::SelectObject(GetSafeHdc(), hBitmap);
}

CCompatibleDC::~CCompatibleDC()
{
	::SelectObject(GetSafeHdc(), m_hOldBitmap);
	DeleteDC();
}

//===========================================================================
// CDrawHelpers class
//===========================================================================

CDrawHelpers::CDrawHelpers()
{
	m_pfnFastGradientFill = 0;
	m_pfnAlphaBlend = 0;
	m_pfnTransparentBlt = 0;

	// Don't use CModuleHandle to reduce dependence between common source
	m_hMsImgDll = ::LoadLibrary(_T("msimg32.dll"));

	if (m_hMsImgDll)
	{
		m_pfnFastGradientFill = (PFNGRADIENTFILL)GetProcAddress(m_hMsImgDll, "GradientFill");
		m_pfnAlphaBlend = (PFNALPHABLEND)::GetProcAddress(m_hMsImgDll, "AlphaBlend");
		m_pfnTransparentBlt = (PFNTRANSPARENTBLT)::GetProcAddress(m_hMsImgDll, "TransparentBlt");
	}
}

CDrawHelpers* DrawHelpers()
{
	static CDrawHelpers s_instance; // singleton
	return &s_instance;
}

CDrawHelpers::~CDrawHelpers()
{
	if (m_hMsImgDll != NULL)
	{
		//::FreeLibrary(m_hMsImgDll); Dangerous to call FreeLibrary in destructor of static object.
	}
}

BOOL CDrawHelpers::GradientFill(HDC hdc, PTRIVERTEX pVertex, ULONG dwNumVertex, PVOID pMesh, ULONG dwNumMesh, ULONG dwMode)
{
	if (m_pfnFastGradientFill)
	{
		return (*m_pfnFastGradientFill)(hdc, pVertex, dwNumVertex, pMesh, dwNumMesh, dwMode);
	}

	return FALSE;
}

void CDrawHelpers::DrawAlphaRect(CDC* pDC, const CRect& rc, CColor& clr)
{
	// 只支持WIN2000以后的 如果想支持以前的 调用CSkinImage::AlphaBlend2
	if (m_pfnAlphaBlend && SystemVersion()->IsWin2KOrGreater())
	{
		CRect rcSrc = rc;
		rcSrc.OffsetRect(-rc.left, -rc.top);
		CBitmap BufferBitmap;
		BufferBitmap.CreateCompatibleBitmap(pDC, rcSrc.Width(), rcSrc.Height());
		CCompatibleDC memdc(pDC, &BufferBitmap);
		memdc.FillSolidRect(rcSrc, clr.ToCOLORREF());

		BLENDFUNCTION bf;
		ZeroMemory(&bf, sizeof(BLENDFUNCTION));

		bf.AlphaFormat  = 0;
		bf.SourceConstantAlpha = clr.GetAlpha();
		bf.BlendOp = AC_SRC_OVER;

		m_pfnAlphaBlend(pDC->GetSafeHdc(), rc.left, rc.top, rc.Width(), rc.Height(),
			memdc, rcSrc.left, rcSrc.top, rcSrc.Width(), rcSrc.Height(), bf);
	}
}

void CDrawHelpers::GradientFillSlow(CDC* pDC, LPCRECT lpRect, COLORREF crFrom, COLORREF crTo, BOOL bHorz)
{
	int cx = max(1, lpRect->right - lpRect->left);
	int cy = max(1, lpRect->bottom - lpRect->top);

	CRect rc;
	pDC->GetClipBox(&rc);

	if (rc.IsRectEmpty())
		rc = *lpRect;
	else
		rc.IntersectRect(rc, lpRect);

	if (bHorz)
	{
		for (int nX = rc.left; nX < rc.right; nX++)
		{
			pDC->FillSolidRect(nX, rc.top, 1, rc.Height(), BlendColors(
				crFrom, crTo, (double)(1.0 - ((nX - lpRect->left) / (double)cx))));
		}
	}
	else
	{
		for (int nY = rc.top; nY < rc.bottom; nY++)
		{
			pDC->FillSolidRect(rc.left, nY, rc.Width(), 1, BlendColors(
				crFrom, crTo, (double)(1.0 - ((nY - lpRect->top)) / (double)cy)));
		}
	}
}

void CDrawHelpers::GradientFillFast(CDC* pDC, LPCRECT lpRect, COLORREF crFrom, COLORREF crTo, BOOL bHorz)
{
	TRIVERTEX vert[2];
	vert[0].x = lpRect->left;
	vert[0].y = lpRect->top;
	vert[0].Red = (COLOR16)(GetRValue(crFrom) << 8);
	vert[0].Green = (COLOR16)(GetGValue(crFrom) << 8);
	vert[0].Blue = (COLOR16)(GetBValue(crFrom) << 8);
	vert[0].Alpha = 0x0000;

	vert[1].x = lpRect->right;
	vert[1].y = lpRect->bottom;
	vert[1].Red = (COLOR16)(GetRValue(crTo) << 8);
	vert[1].Green = (COLOR16)(GetGValue(crTo) << 8);
	vert[1].Blue = (COLOR16)(GetBValue(crTo) << 8);
	vert[1].Alpha = 0x0000;

	GRADIENT_RECT gRect = { 0, 1 };

	GradientFill(*pDC, vert, 2, &gRect, 1, bHorz ? GRADIENT_FILL_RECT_H : GRADIENT_FILL_RECT_V);
}

void CDrawHelpers::GradientFill(CDC* pDC, LPCRECT lpRect, COLORREF crFrom, COLORREF crTo, BOOL bHorz)
{
	if (!lpRect)
		return;

	if (::IsRectEmpty(lpRect))
		return;

	if (IsLowResolution(pDC->GetSafeHdc()))
	{
		pDC->FillSolidRect(lpRect, crFrom);
	}
	else if (crFrom == crTo)
	{
		pDC->FillSolidRect(lpRect, crFrom);
	}
	else if ((m_pfnFastGradientFill == NULL) || (IsContextRTL(pDC) && SystemVersion()->IsWin9x()))
	{
		GradientFillSlow(pDC, lpRect, crFrom, crTo, bHorz);
	}
	else
	{
		GradientFillFast(pDC, lpRect, crFrom, crTo, bHorz);
	}
}

void CDrawHelpers::GradientFill(CDC* pDC, LPCRECT lpRect, COLORREF crFrom, COLORREF crTo, BOOL bHorz, LPCRECT lpRectClip)
{
	CRect rc(lpRect);

	if (lpRectClip == NULL)
	{
		GradientFill(pDC, lpRect, crFrom, crTo, bHorz);
		return;
	}

	COLORREF crFrom1 = crFrom;

	if (bHorz)
	{
		if (rc.top < lpRectClip->top)
		{
			rc.top = lpRectClip->top;
		}

		if (rc.bottom > lpRectClip->bottom)
		{
			rc.bottom = lpRectClip->bottom;
		}

		if ((rc.left > lpRectClip->right) || (rc.right < lpRectClip->left))
			return;

		if (rc.left < lpRectClip->left)
		{
			rc.left = lpRectClip->left;

			crFrom = BlendColors(crFrom, crTo,
				(float)(lpRect->right - lpRectClip->left) / (float)(lpRect->right - lpRect->left));
		}

		if (rc.right > lpRectClip->right)
		{
			rc.right = lpRectClip->right;

			crTo = BlendColors(crFrom1, crTo,
				(float)(lpRect->right - lpRectClip->right) / (float)(lpRect->right - lpRect->left));

		}

		GradientFill(pDC, rc, crFrom, crTo, bHorz);

	}
	else
	{
		if (rc.left < lpRectClip->left)
		{
			rc.left = lpRectClip->left;
		}

		if (rc.right > lpRectClip->right)
		{
			rc.right = lpRectClip->right;
		}

		if ((rc.top > lpRectClip->bottom) || (rc.bottom < lpRectClip->top))
			return;

		if (rc.top < lpRectClip->top)
		{
			rc.top = lpRectClip->top;

			crFrom = BlendColors(crFrom, crTo,
				(float)(lpRect->bottom - lpRectClip->top) / (float)(lpRect->bottom - lpRect->top));
		}

		if (rc.bottom > lpRectClip->bottom)
		{
			rc.bottom = lpRectClip->bottom;

			crTo = BlendColors(crFrom1, crTo,
				(float)(lpRect->bottom - lpRectClip->bottom) / (float)(lpRect->bottom - lpRect->top));

		}

		GradientFill(pDC, rc, crFrom, crTo, bHorz);
	}
}

void CDrawHelpers::ExcludeCorners(CDC* pDC, CRect rc)
{
	pDC->ExcludeClipRect(rc.left, rc.top, rc.left + 1, rc.top + 1);
	pDC->ExcludeClipRect(rc.right - 1, rc.top, rc.right, rc.top + 1);
	pDC->ExcludeClipRect(rc.left, rc.bottom - 1, rc.left + 1, rc.bottom);
	pDC->ExcludeClipRect(rc.right - 1, rc.bottom - 1, rc.right, rc.bottom);
}

void CDrawHelpers::StripMnemonics(CString& strClear)
{
	for (int i = 0; i < strClear.GetLength(); i++)
	{
		if (strClear[i] == _T('&')) // Converts "&&" to "&" and "&&&&" to "&&"
		{
			strClear.Delete(i);
		}
	}
}

void CDrawHelpers::StripMnemonics(LPTSTR lpszClear)
{
	if (lpszClear == NULL || lpszClear == LPSTR_TEXTCALLBACK)
		return;

	LPTSTR lpszResult = lpszClear;

	while (*lpszClear)
	{
		if (*lpszClear == _T('&') && *(lpszClear + 1) != _T('&'))
		{
			lpszClear++;
			continue;
		}

		*lpszResult++ = *lpszClear++;
	}

	*lpszResult = 0;
}

void CDrawHelpers::BlurPoints(CDC* pDC, LPPOINT pts, int nCount)
{
	for (int i = 0; i < nCount; i += 2)
	{
		CPoint ptBlur = pts[i];
		CPoint ptDirection(pts[i].x + pts[i + 1].x, pts[i].y + pts[i + 1].y);

		COLORREF clrBlur = pDC->GetPixel(ptDirection);
		COLORREF clrDirection = pDC->GetPixel(ptBlur);

		pDC->SetPixel(ptBlur, RGB(
			(GetRValue(clrBlur) + GetRValue(clrDirection)) / 2,
			(GetGValue(clrBlur) + GetGValue(clrDirection)) / 2,
			(GetBValue(clrBlur) + GetBValue(clrDirection)) / 2));
	}
}

COLORREF CDrawHelpers::BlendColors(COLORREF crA, COLORREF crB, double fAmountA)
{
	double fAmountB = (1.0 - fAmountA);
	int btR = (int)(GetRValue(crA) * fAmountA + GetRValue(crB) * fAmountB);
	int btG = (int)(GetGValue(crA) * fAmountA + GetGValue(crB) * fAmountB);
	int btB = (int)(GetBValue(crA) * fAmountA + GetBValue(crB) * fAmountB);

	return RGB(min(255, btR), (BYTE)min(255, btG), (BYTE)min(255, btB));
}

COLORREF CDrawHelpers::DarkenColor(long lScale, COLORREF lColor)
{
	long red   = MulDiv(GetRValue(lColor), (255 - lScale), 255);
	long green = MulDiv(GetGValue(lColor), (255 - lScale), 255);
	long blue  = MulDiv(GetBValue(lColor), (255 - lScale), 255);

	return RGB(red, green, blue);
}

COLORREF CDrawHelpers::LightenColor(long lScale, COLORREF lColor)
{
	long R = MulDiv(255 - GetRValue(lColor), lScale, 255) + GetRValue(lColor);
	long G = MulDiv(255 - GetGValue(lColor), lScale, 255) + GetGValue(lColor);
	long B = MulDiv(255 - GetBValue(lColor), lScale, 255) + GetBValue(lColor);

	return RGB(R, G, B);
}

CPoint CDrawHelpers::Dlu2Pix(int dluX, int dluY)
{
	CPoint baseXY(::GetDialogBaseUnits());
	CPoint pixXY(0,0);
	pixXY.x = ::MulDiv(dluX, baseXY.x, 4);
	pixXY.y = ::MulDiv(dluY, baseXY.y, 8);
	return pixXY;
}

COLORREF CDrawHelpers::RGBtoHSL(COLORREF rgb)
{
	int delta, sum;
	int nH, nS, nL;
	int r = GetRValue(rgb);
	int g = GetGValue(rgb);
	int b = GetBValue(rgb);
	int cmax = ((r) >= (g) ? ((r) >= (b) ? (r) : (b)) : (g) >= (b) ? (g) : (b));
	int cmin = ((r) <= (g) ? ((r) <= (b) ? (r) : (b)) : (g) <= (b) ? (g) : (b));

	nL = (cmax + cmin + 1) / 2;
	if (cmax == cmin)
	{
		nH = 255; // H is really undefined
		nS = 0;
	}
	else
	{
		delta = cmax - cmin;
		sum = cmax + cmin;
		if (nL < 127)
			nS = ((delta + 1) * 256) / sum;
		else
			nS = (delta * 256) / ((2 * 256) - sum);
		if (r == cmax)
			nH = ((g - b) * 256) / delta;
		else if (g == cmax)
			nH = (2 * 256) + ((b - r) * 256) / delta;
		else
			nH = (4 * 256) + ((r - g) * 256) / delta;
		nH /= 6;
		if (nH < 0)
			nH += 256;
	}
	nH = nH * 239 / 255;
	nS = nS * 240 / 255;
	nL = nL * 240 / 255;

	return RGB((BYTE)min(nH, 239), (BYTE)min(nS, 240), (BYTE)min(nL, 240));
}

void CDrawHelpers::RGBtoHSL(COLORREF clr, double& h, double& s, double& l)
{
	double r = (double)GetRValue(clr)/255.0;
	double g = (double)GetGValue(clr)/255.0;
	double b = (double)GetBValue(clr)/255.0;

	double maxcolor = __max(r, __max(g, b));
	double mincolor = __min(r, __min(g, b));

	l = (maxcolor + mincolor)/2;

	if (maxcolor == mincolor)
	{
		h = 0;
		s = 0;
	}
	else
	{
		if (l < 0.5)
			s = (maxcolor-mincolor)/(maxcolor + mincolor);
		else
			s = (maxcolor-mincolor)/(2.0-maxcolor-mincolor);

		if (r == maxcolor)
			h = (g-b)/(maxcolor-mincolor);
		else if (g == maxcolor)
			h = 2.0+(b-r)/(maxcolor-mincolor);
		else
			h = 4.0+(r-g)/(maxcolor-mincolor);

		h /= 6.0;
		if (h < 0.0) h += 1;
	}
}

double CDrawHelpers::HueToRGB(double temp1, double temp2, double temp3)
{
	if (temp3 < 0)
		temp3 = temp3 + 1.0;
	if (temp3 > 1)
		temp3 = temp3-1.0;

	if (6.0*temp3 < 1)
		return (temp1+(temp2-temp1)*temp3 * 6.0);

	else if (2.0*temp3 < 1)
		return temp2;

	else if (3.0*temp3 < 2.0)
		return (temp1+(temp2-temp1)*((2.0/3.0)-temp3)*6.0);

	return temp1;
}

int CDrawHelpers::HueToRGB(int m1, int m2, int h)
{
	if (h < 0)
		h += 255;

	if (h > 255)
		h -= 255;

	if ((6 * h) < 255)
		return ((m1 + ((m2 - m1) / 255 * h * 6)) / 255);

	if ((2 * h) < 255)
		return m2 / 255;

	if ((3 * h) < (2 * 255))
		return ((m1 + (m2 - m1) / 255 * ((255 * 2 / 3) - h) * 6) / 255);

	return (m1 / 255);
}

COLORREF CDrawHelpers::HSLtoRGB(COLORREF hsl)
{
	int r, g, b;
	int m1, m2;
	int nH = GetRValue(hsl) * 255 / 239;
	int nS = GetGValue(hsl) * 255 / 240;
	int nL = GetBValue(hsl) * 255 / 240;

	if (nS == 0)
		r = g = b = nL;
	else
	{
		if (nL <= 127)
			m2 = nL * (255 + nS);
		else
			m2 = (nL + nS - ((nL * nS) / 255)) * 255;
		m1 = (2 * 255 * nL) - m2;
		r = HueToRGB(m1, m2, nH + (255 / 3));
		g = HueToRGB(m1, m2, nH);
		b = HueToRGB(m1, m2, nH - (255 / 3));
	}
	return RGB((BYTE)min(r, 255), (BYTE)min(g, 255), (BYTE)min(b, 255));
}

COLORREF CDrawHelpers::HSLtoRGB(double h, double s, double l)
{
	double r, g, b;
	double temp1, temp2;

	if (s == 0)
	{
		r = g = b = l;
	}
	else
	{
		if (l < 0.5)
			temp2 = l*(1.0 + s);
		else
			temp2 = l + s-l*s;

		temp1 = 2.0 * l-temp2;

		r = HueToRGB(temp1, temp2, h + 1.0/3.0);
		g = HueToRGB(temp1, temp2, h);
		b = HueToRGB(temp1, temp2, h - 1.0/3.0);
	}

	return RGB((BYTE)(r * 255), (BYTE)(g * 255), (BYTE)(b * 255));
}

static int CALLBACK EnumFontFamExProc(ENUMLOGFONTEX* pelf, NEWTEXTMETRICEX* /*lpntm*/, int /*FontType*/, LPVOID pThis)
{
	LPCTSTR strFontName = (LPCTSTR)pThis;
	CString strFaceName = pelf->elfLogFont.lfFaceName;

	if (strFaceName.CompareNoCase(strFontName) == 0)
		return 0;

	return 1;
}

BOOL CDrawHelpers::FontExists(LPCTSTR strFaceName)
{
	// Enumerate all styles and charsets of all fonts:
	LOGFONT lfEnum;
	::ZeroMemory(&lfEnum, sizeof(LOGFONT));

	lfEnum.lfFaceName[ 0 ] = 0;
	lfEnum.lfCharSet = DEFAULT_CHARSET;

	CWindowDC dc(NULL);

	return  ::EnumFontFamiliesEx(dc.m_hDC, &lfEnum, (FONTENUMPROC)
		EnumFontFamExProc, (LPARAM)strFaceName, 0) == 0;
}

CString CDrawHelpers::GetDefaultFontName()
{
	LOGFONT lfFont;
	ZeroMemory(&lfFont, sizeof(LOGFONT));
	::GetObject(::GetStockObject(DEFAULT_GUI_FONT), sizeof(LOGFONT), &lfFont);

	return CString(lfFont.lfFaceName);
}

CString CDrawHelpers::GetVerticalFontName(BOOL bUseOfficeFont)
{
	LOGFONT lfFont;
	ZeroMemory(&lfFont, sizeof(LOGFONT));
	::GetObject(::GetStockObject(DEFAULT_GUI_FONT), sizeof(LOGFONT), &lfFont);
	bool bUseSystemFont = lfFont.lfCharSet > SYMBOL_CHARSET;

	if (bUseSystemFont && !SystemVersion()->IsWin2KOrGreater())
		bUseSystemFont = FALSE;

	if (bUseSystemFont && (_tcsicmp(lfFont.lfFaceName, _T("MS Shell Dlg")) == 0))
		bUseSystemFont = FALSE; // Can draw it vertically in Windows 2000.

	CString strVerticalFaceName = _T("Arial");
	LPCTSTR strOfficeFont = _T("Tahoma");

	if (bUseSystemFont || !FontExists(strVerticalFaceName))
	{
		strVerticalFaceName = lfFont.lfFaceName;
	}
	else if (bUseOfficeFont && !bUseSystemFont && FontExists(strOfficeFont))
	{
		strVerticalFaceName = strOfficeFont;
	}

	return strVerticalFaceName;
}

BOOL CDrawHelpers::IsContextRTL(CDC* pDC)
{
	return pDC && IsContextRTL(pDC->GetSafeHdc());
}

BOOL CDrawHelpers::IsContextRTL(HDC hDC)
{
	typedef DWORD (CALLBACK* PFNGDIGETLAYOUTPROC)(HDC);
	static PFNGDIGETLAYOUTPROC s_pfn = (PFNGDIGETLAYOUTPROC)-1;

	if (s_pfn == (PFNGDIGETLAYOUTPROC)-1)
	{
		HINSTANCE hInst = ::GetModuleHandleA("GDI32.DLL");

		s_pfn = hInst ? (PFNGDIGETLAYOUTPROC)GetProcAddress(hInst, "GetLayout") : NULL;
	}

	return s_pfn ? (*s_pfn)(hDC) : FALSE;
}

void CDrawHelpers::SetContextRTL(CDC* pDC, BOOL bLayoutRTL)
{
	if (pDC) SetContextRTL(pDC->GetSafeHdc(), bLayoutRTL);
}

void CDrawHelpers::SetContextRTL(HDC hDC, BOOL bLayoutRTL)
{
	typedef DWORD (CALLBACK* PFNGDISETLAYOUTPROC)(HDC, DWORD);
	static PFNGDISETLAYOUTPROC s_pfn = (PFNGDISETLAYOUTPROC)-1;

	if (s_pfn == (PFNGDISETLAYOUTPROC)-1)
	{
		HINSTANCE hInst = ::GetModuleHandleA("GDI32.DLL");

		s_pfn = hInst ? (PFNGDISETLAYOUTPROC)GetProcAddress(hInst, "SetLayout") : NULL;
	}

	if (s_pfn != NULL)
	{
		(*s_pfn)(hDC, bLayoutRTL);
	}
}


void CDrawHelpers::KeyToLayout(CWnd* pWnd, UINT& nChar)
{
	ASSERT(pWnd);
	if (!pWnd || !pWnd->GetSafeHwnd())
		return;

	if (nChar == VK_LEFT && pWnd->GetExStyle() & WS_EX_LAYOUTRTL)
		nChar = VK_RIGHT;
	else if (nChar == VK_RIGHT && pWnd->GetExStyle() & WS_EX_LAYOUTRTL)
		nChar = VK_LEFT;

}

BOOL CDrawHelpers::DrawLine(CDC* pDC, int x, int y, int nLength, int nHeight, COLORREF crLine)
{
	if (pDC->GetSafeHdc())
	{
		CPenDC penDC(*pDC, crLine);
		pDC->MoveTo(x, y);
		pDC->LineTo(x + nLength, y + nHeight);
		return TRUE;
	}
	return FALSE;
}

BOOL CDrawHelpers::IsLowResolution(HDC hDC/* = 0*/)
{
	return FALSE;
}

BOOL CDrawHelpers::TakeSnapShot(CWnd* pWnd, CBitmap& bmpSnapshot)
{
	if (!::IsWindow(pWnd->GetSafeHwnd()))
		return FALSE;

	CWnd *pWndParent = pWnd->GetParent();
	if (::IsWindow(pWndParent->GetSafeHwnd()))
	{
		if (bmpSnapshot.GetSafeHandle() != NULL)
			bmpSnapshot.DeleteObject();

		//convert our coordinates to our parent coordinates.
		CWindowRect rc(pWnd);
		pWndParent->ScreenToClient(&rc);

		//copy what's on the parents background at this point
		CDC *pDC = pWndParent->GetDC();

		CDC memDC;
		memDC.CreateCompatibleDC(pDC);
		bmpSnapshot.CreateCompatibleBitmap(pDC, rc.Width(), rc.Height());

		CBitmapDC bitmapDC(&memDC, &bmpSnapshot);
		memDC.BitBlt(0, 0, rc.Width(), rc.Height(), pDC, rc.left, rc.top, SRCCOPY);

		pWndParent->ReleaseDC(pDC);

		return TRUE;
	}

	return FALSE;
}

BOOL CDrawHelpers::DrawTransparentBack(CDC* pDC, CWnd* pWnd, CBitmap& bmpSnapshot)
{
	if (!::IsWindow(pWnd->GetSafeHwnd()))
		return FALSE;

	if (::GetWindowLong(pWnd->GetSafeHwnd(), GWL_EXSTYLE) & WS_EX_TRANSPARENT)
	{
		// Get background.
		if (!TakeSnapShot(pWnd, bmpSnapshot))
			return FALSE;

		CClientRect rc(pWnd);

		CDC memDC;
		memDC.CreateCompatibleDC(pDC);

		CBitmapDC bitmapDC(&memDC, &bmpSnapshot);
		pDC->BitBlt(0, 0, rc.Width(), rc.Height(), &memDC, 0, 0, SRCCOPY);

		return TRUE;
	}

	return FALSE;
}

void CDrawHelpers::ScreenToWindow(CWnd* pWnd, LPPOINT lpPoint)
{
	RECT rc;
	::GetWindowRect(pWnd->GetSafeHwnd(), &rc);

	lpPoint->y -= rc.top;

	if (GetWindowLong(pWnd->GetSafeHwnd(), GWL_EXSTYLE) & WS_EX_LAYOUTRTL )
	{
		lpPoint->x = rc.right - lpPoint->x;
	}
	else
	{
		lpPoint->x -= rc.left;
	}
}

BOOL CDrawHelpers::RegisterWndClass(HINSTANCE hInstance, LPCTSTR lpszClassName, UINT style, HICON hIcon, HBRUSH hbrBackground)
{
	WNDCLASS wndcls;
	ZeroMemory(&wndcls, sizeof(wndcls));

	wndcls.style = style;
	wndcls.lpfnWndProc = ::DefWindowProc;
	wndcls.hInstance = hInstance ? hInstance : AfxGetInstanceHandle();
	wndcls.hCursor = AfxGetApp()->LoadStandardCursor(IDC_ARROW);
	wndcls.lpszClassName = lpszClassName;
	wndcls.hIcon = hIcon;
	wndcls.hbrBackground = hbrBackground;

	return AfxRegisterClass(&wndcls);
}

void CDrawHelpers::GetWindowCaption(HWND hWnd, CString& strWindowText)
{
#ifdef _UNICODE
	int nLen = (int)::DefWindowProc(hWnd, WM_GETTEXTLENGTH, 0, 0);
	::DefWindowProc(hWnd, WM_GETTEXT, nLen + 1, (WPARAM)(LPCTSTR)strWindowText.GetBuffer(nLen));
	strWindowText.ReleaseBuffer();
#else
	int nLen = ::GetWindowTextLength(hWnd);
	::GetWindowText(hWnd, strWindowText.GetBufferSetLength(nLen), nLen + 1);
	strWindowText.ReleaseBuffer();
#endif
}

