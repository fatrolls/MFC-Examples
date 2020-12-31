// WidgetObj.cpp : implementation file
//

#include "stdafx.h"
#include "Widget.h"
#include "WidgetObj.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWidget

IMPLEMENT_SERIAL(CWidget, CObject, 1)

CWidget::CWidget()
{
	m_rect = CRect (0, 0, 90, 90);
	m_color = RGB (255, 0, 0);
}

CWidget::CWidget (int x, int y, COLORREF color)
{
	m_rect = CRect (x, y, x + 90, y + 90);
	m_color = color;
}

CWidget::~CWidget()
{
}

/////////////////////////////////////////////////////////////////////////////
// CWidget message handlers

CRect CWidget::GetRect()
{
	return m_rect;
}

COLORREF CWidget::GetColor()
{
	return m_color;
}

void CWidget::Serialize (CArchive& ar)
{
	CObject::Serialize (ar);

	if (ar.IsStoring ())
		ar << m_rect << m_color;
	else 
		ar >> m_rect >> m_color;
}

void CWidget::Draw(CDC *pDC)
{
	CBrush brush (m_color);
	CBrush* pOldBrush = pDC->SelectObject (&brush);

	CPoint points[3];
	points[0].x = m_rect.left;
	points[0].y = m_rect.bottom;
	points[1].x = m_rect.left + (m_rect.Width () / 2);
	points[1].y = m_rect.top;
	points[2].x = m_rect.right;
	points[2].y = m_rect.bottom;
	pDC->Polygon (points, 3);

	pDC->SelectObject (pOldBrush);
}

void CWidget::DrawSelected(CDC *pDC)
{
	CBrush brush (RGB (0, 255, 0));
	CBrush* pOldBrush = pDC->SelectObject (&brush);

	CPoint points[3];
	points[0].x = m_rect.left;
	points[0].y = m_rect.bottom;
	points[1].x = m_rect.left + (m_rect.Width () / 2);
	points[1].y = m_rect.top;
	points[2].x = m_rect.right;
	points[2].y = m_rect.bottom;
	pDC->Polygon (points, 3);

	pDC->SelectObject (pOldBrush);
}

void CWidget::DrawDragImage(CDC *pDC, POINT point)
{
    int nOldMode = pDC->SetROP2 (R2_NOT);
    CBrush* pOldBrush = (CBrush*) pDC->SelectStockObject (NULL_BRUSH);

    CPoint points[3];
    points[0].x = point.x;
    points[0].y = point.y + m_rect.Height ();
    points[1].x = point.x + (m_rect.Width () / 2);
    points[1].y = point.y;
    points[2].x = point.x + m_rect.Width ();
    points[2].y = point.y + m_rect.Height ();
    pDC->Polygon (points, 3);

    pDC->SelectObject (pOldBrush);
    pDC->SetROP2 (nOldMode);
}

BOOL CWidget::PtInWidget(POINT point)
{
    if (!m_rect.PtInRect (point))
        return FALSE;

    int cx = min (point.x - m_rect.left, m_rect.right - point.x);
    return ((m_rect.bottom - point.y) <= (2 * cx));
}
