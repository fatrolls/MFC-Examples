#include "stdafx.h"
#include "CustomHyperbar.h"

void CCustomHyperbar::RenderBackground(CDC * pDC, RECT * pRect)
{
	pDC->FillSolidRect(pRect, RGB(235,234,214));

	CBrush brush(RGB(60, 83, 174));

	CBrush * pOldBrush = pDC->SelectObject(&brush);

	POINT pt;
	pt.x = pt.y = 15;
	pDC->RoundRect(pRect, pt);

	pDC->SelectObject(pOldBrush);

	CPen pen1(PS_SOLID, 1, RGB(56, 73, 141));

	CPen * pOldPen = pDC->SelectObject(&pen1);
	
	for(int y = pRect->top + 2; y < pRect->bottom - 2; y += 3)
	{
		pDC->MoveTo(pRect->left, y);
		pDC->LineTo(pRect->right, y);
	}

	pDC->SelectObject(pOldPen);
}
