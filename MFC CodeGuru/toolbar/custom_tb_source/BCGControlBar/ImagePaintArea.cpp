// ImagePaintArea.cpp : implementation file
//

#include "stdafx.h"
#include "ImagePaintArea.h"
#include "BCGToolBarImages.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CImagePaintArea

CImagePaintArea::CImagePaintArea()
{
	m_sizeImage.cx = 0;
	m_sizeImage.cy = 0;

	m_pBitmap = NULL;
	m_rgbColor = RGB (0, 0, 0);	// Black

	m_rectParentPreviewArea.SetRectEmpty ();

	m_memDC.CreateCompatibleDC (NULL);
}

CImagePaintArea::~CImagePaintArea()
{
}


BEGIN_MESSAGE_MAP(CImagePaintArea, CButton)
	//{{AFX_MSG_MAP(CImagePaintArea)
	ON_WM_ERASEBKGND()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_CANCELMODE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CImagePaintArea message handlers

void CImagePaintArea::DrawItem (LPDRAWITEMSTRUCT lpDIS)
{
	CDC* pDC = CDC::FromHandle (lpDIS->hDC);
	ASSERT_VALID (pDC);

	CRect rectClient = lpDIS->rcItem;
	rectClient.InflateRect (-1, -1);

	int dx = rectClient.Width () / m_sizeImage.cx;
	int dy = rectClient.Height () / m_sizeImage.cy;

	CRect rectDraw = rectClient;

	rectDraw.right = rectDraw.left + dx * m_sizeImage.cx;
	rectDraw.bottom = rectDraw.top + dy * m_sizeImage.cy;

	rectClient = rectDraw;
	rectClient.InflateRect (1, 1);

	pDC->Draw3dRect (rectDraw,
					::GetSysColor (COLOR_3DDKSHADOW),
					::GetSysColor (COLOR_3DHILIGHT));

	//-----------
	// Draw grid:
	//-----------
	CPen penGrid (PS_SOLID, 1, ::GetSysColor (COLOR_3DSHADOW));
	CPen* pOldPen = (CPen*) pDC->SelectObject (&penGrid);

	for (int x = rectDraw.left + dx; x <= rectDraw.right - dx; x += dx)
	{
		pDC->MoveTo (x, rectDraw.top + 1);
		pDC->LineTo (x, rectDraw.bottom - 1);
	}

	for (int y = rectDraw.top + dy; y <= rectDraw.bottom - dy; y += dy)
	{
		pDC->MoveTo (rectDraw.left + 1, y);
		pDC->LineTo (rectDraw.right - 1, y);
	}

	pDC->SelectObject (pOldPen);

	//-------------
	// Draw bitmap:
	//-------------
	if (m_pBitmap == NULL)
	{
		return;
	}

	CBitmap* pOldBitmap = m_memDC.SelectObject (m_pBitmap);

	for (x = 0; x < m_sizeImage.cx; x ++)
	{
		for (y = 0; y < m_sizeImage.cy; y ++)
		{
			COLORREF rgbPixel = 
				CBCGToolBarImages::MapFromSysColor (m_memDC.GetPixel (x, y), FALSE);
			if (rgbPixel != (COLORREF) -1)
			{
				CRect rect (
					CPoint (rectDraw.left + x * dx, rectDraw.top + y * dy),
					CSize (dx, dy));
				rect.InflateRect (-1, -1);

				pDC->FillSolidRect (rect, rgbPixel);
			}
		}
	}

	m_memDC.SelectObject (pOldBitmap);
}
//********************************************************************************
BOOL CImagePaintArea::OnEraseBkgnd(CDC* pDC) 
{
	CRect rectClient;	// Client area rectangle
	GetClientRect (&rectClient);

	pDC->FillSolidRect (&rectClient, ::GetSysColor (COLOR_3DFACE));
	return TRUE;
}
//********************************************************************************
void CImagePaintArea::OnMouseMove(UINT nFlags, CPoint point) 
{
	CRect rectClient;	// Client area rectangle
	GetClientRect (&rectClient);

	if (rectClient.PtInRect (point) && (nFlags & MK_LBUTTON))
	{
		DrawPixel (point);
	}
}
//********************************************************************************
void CImagePaintArea::OnLButtonDown(UINT nFlags, CPoint point) 
{
	SetCapture ();

	DrawPixel (point);
}
//********************************************************************************
void CImagePaintArea::OnLButtonUp(UINT nFlags, CPoint point) 
{
	if (GetCapture () == this)
	{
		ReleaseCapture ();
	}

	DrawPixel (point);
}
//********************************************************************************
void CImagePaintArea::OnCancelMode() 
{
	if (GetCapture () == this)
	{
		ReleaseCapture ();
	}
}
//********************************************************************************DrawPixel (point);
void CImagePaintArea::DrawPixel (POINT point)
{
	CRect rectClient;	// Client area rectangle
	GetClientRect (&rectClient);

	rectClient.InflateRect (-1, -1);

	int dx = rectClient.Width () / m_sizeImage.cx;
	int dy = rectClient.Height () / m_sizeImage.cy;

	int x = (point.x - 1) / dx;
	int y = (point.y - 1) / dy;

	x = max (min (x, m_sizeImage.cx - 1), 0);
	y = max (min (y, m_sizeImage.cy - 1), 0);

	CRect rect (
		CPoint (rectClient.left + x * dx, rectClient.top + y * dy),
		CSize (dx, dy));
	rect.InflateRect (-1, -1);

	CClientDC dc (this);
	dc.FillSolidRect (rect, m_rgbColor);

	//---------------
	// Update bitmap:
	//---------------
	CBitmap* pOldBitmap = m_memDC.SelectObject (m_pBitmap);
	m_memDC.SetPixel (x, y, CBCGToolBarImages::MapToSysColor (m_rgbColor));
	m_memDC.SelectObject (pOldBitmap);

	GetParent()->InvalidateRect (m_rectParentPreviewArea);
}
//********************************************************************************
void CImagePaintArea::SetBitmap (CBitmap* pBitmap)
{
	m_pBitmap = pBitmap;

	if (m_pBitmap == NULL)
	{
		m_sizeImage.cx = 0;
		m_sizeImage.cy = 0;
		return;
	}

	BITMAP bmp;
	m_pBitmap->GetBitmap (&bmp);

	m_sizeImage.cx = bmp.bmWidth;
	m_sizeImage.cy = bmp.bmHeight;
}
