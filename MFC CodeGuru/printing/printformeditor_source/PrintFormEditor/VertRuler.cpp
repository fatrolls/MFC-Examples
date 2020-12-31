// VertRuler.cpp : implementation file
//

#include "stdafx.h"
#include "printformeditor.h"
#include "VertRuler.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVertRuler

CVertRuler::CVertRuler()
{
	iFrom = 0;
	iTo = 2700;
	iDiv = 2;
	iPos = 0;

	iTextStep = 100;
	iGreatStep = 50;
	iSmallStep = 25;
	iTextDiv = 100;

	ft.CreatePointFont(90, "Arial");

	crBack = RGB(255,255,255);
	crText = RGB(0,0,0);
	crLines = RGB(0,0,0);
	yMouse = -10;
}

CVertRuler::~CVertRuler()
{
}


BEGIN_MESSAGE_MAP(CVertRuler, CButton)
	//{{AFX_MSG_MAP(CVertRuler)
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVertRuler message handlers

void CVertRuler::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	int oym = yMouse;

	CDC * pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
	CRect rc(lpDrawItemStruct->rcItem);
	pDC->FillSolidRect(rc, crBack);

	int t;
	int iMin = iFrom;// + iPos;
	int iMax = iTo;//iMin + rc.Height() / iDiv;
//	if (iMax > iTo) iMax = iTo;
	int iRange = iMax - iMin;

	COLORREF crt = pDC->SetTextColor(crText);
	CFont * of   = pDC->SelectObject(&ft);
	UINT oa = pDC->SetTextAlign(TA_CENTER|TA_TOP);

	CString cs;

	CPen pn(PS_SOLID, 1, crLines);
	CPen * op = pDC->SelectObject(&pn);

	int r1 = rc.Width() / 3;
	int r2 = rc.Width() / 4;
	int r3 = rc.Width() / 2;

	CSize sz = pDC->GetTextExtent("X");
	int y1 = sz.cy / 2;

	for (t = iMin; t <= iMax / iDiv; t += iGreatStep / iDiv)
	{
		if (rc.top + t - iPos > 0 && rc.top + t - iPos <= rc.bottom)
		{
			pDC->MoveTo(rc.left + r2, rc.top + t - iPos);
			pDC->LineTo(rc.right -r2, rc.top + t - iPos);
		}
		if (rc.top + t - iPos > rc.bottom) break;
	}

/*	for (t = iMin; t < iMax; t += iSmallStep)
	{
		if (rc.top + t - iPos > 0 && rc.top + t - iPos < rc.bottom)
		{
			pDC->MoveTo(rc.left + r1, rc.top + t - iPos);
			pDC->LineTo(rc.right -r1, rc.top + t - iPos);
		}
		if (rc.top + t - iPos > rc.bottom) break;
	}
*/
	for (t = iMin; t <= iMax / iDiv; t += iTextStep / iDiv)
	{
		if (rc.top + t - iPos > 0 && rc.top + t - iPos <= rc.bottom)
		{
			cs.Format("%d", (iMin + t) *iDiv / iTextDiv);
			if (t <= iTo / iDiv)
				pDC->TextOut(rc.left + r3, rc.top + t - y1 - iPos, cs);
//			cs.Format("%d", t / iTextDiv);
//			pDC->TextOut(rc.left + t - iPos, rc.top, cs);
		}
		if (rc.top + t - iPos > rc.bottom) break;
	}


	pDC->SetTextColor(crt);
	pDC->SelectObject(of);
	pDC->SetTextAlign(oa);
	pDC->SelectObject(op);
	
	yMouse = -1;
	DrawMouse(oym);
}

void CVertRuler::SetPos(const int pos)
{
	iPos = pos;
	if (iPos < iFrom) iPos = iFrom;
	if (GetSafeHwnd()) Invalidate();
}

void CVertRuler::SetRange(const int r1, const int r2)
{
	iFrom = r1;
	iTo = r2;
	if (iPos < iFrom) iPos = iFrom;
	if (GetSafeHwnd()) Invalidate();
}


BOOL CVertRuler::OnEraseBkgnd(CDC* pDC) 
{
	return true;	
//	return CButton::OnEraseBkgnd(pDC);
}

void CVertRuler::DrawMouse(const int y)
{
	if (y == yMouse) return;

	CRect rc;
	GetClientRect(rc);
	CClientDC dc(this);
	int orop = dc.SetROP2(R2_NOT);
	CPen pn(PS_DASHDOT, 1, RGB(0,0,0));
	CPen * op = dc.SelectObject(&pn);

	if (yMouse >= 0)
	{
		dc.MoveTo(rc.left, yMouse);
		dc.LineTo(rc.right, yMouse);
	}
	yMouse = y;
	if (yMouse >= 0)
	{
		dc.MoveTo(rc.left, yMouse);
		dc.LineTo(rc.right, yMouse);
	}

	dc.SetROP2(orop);
	dc.SelectObject(op);
}
