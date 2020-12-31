// HorizRuler.cpp : implementation file
//

#include "stdafx.h"
#include "printformeditor.h"
#include "HorizRuler.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHorizRuler

CHorizRuler::CHorizRuler()
{
	iFrom = 0;
	iTo = 2000;
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
	xMouse = -10;
}

CHorizRuler::~CHorizRuler()
{
}


BEGIN_MESSAGE_MAP(CHorizRuler, CButton)
	//{{AFX_MSG_MAP(CHorizRuler)
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHorizRuler message handlers

void CHorizRuler::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	int oxm = xMouse;

	CDC * pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
	CRect rc(lpDrawItemStruct->rcItem);
	pDC->FillSolidRect(rc, crBack);

	int t;
	int iMin = iFrom;// + iPos;
	int iMax = iTo; //iMin + rc.Width() / iDiv;
	if (iMax > iTo) iMax = iTo;
	int iRange = iMax - iMin;

	COLORREF crt = pDC->SetTextColor(crText);
	CFont * of   = pDC->SelectObject(&ft);
	UINT oa = pDC->SetTextAlign(TA_CENTER|TA_TOP);

	CString cs;

	CPen pn(PS_SOLID, 1, crLines);
	CPen * op = pDC->SelectObject(&pn);

	int r1 = rc.Height() / 3;
	int r2 = rc.Height() / 4;

	for (t = iMin; t <= iMax / iDiv; t += iGreatStep / iDiv)
	{
		if (rc.left + t - iPos > 0 && rc.top + t - iPos <= rc.right)
		{
			pDC->MoveTo(rc.left + t - iPos, rc.top + r2);
			pDC->LineTo(rc.left + t- iPos, rc.bottom - r2);
		}
		if (rc.top + t - iPos > rc.right) break;
	}

/*	for (t = iMin; t < iMax; t += iSmallStep / iDiv)
	{
		if (rc.left + t - iPos > 0 && rc.top + t - iPos < rc.right)
		{
			pDC->MoveTo(rc.left + t - iPos, rc.top + r1);
			pDC->LineTo(rc.left + t - iPos, rc.bottom - r1);
		}
		if (rc.top + t - iPos > rc.right) break;
	}
*/
	for (t = iMin; t <= iMax / iDiv; t += iTextStep / iDiv)
	{
		if (rc.left + t - iPos > 0 && rc.top + t - iPos <= rc.right)
		{
			cs.Format("%d", t *iDiv / iTextDiv);

			if (t <= iTo / iDiv)
				pDC->TextOut(rc.left + t - iPos, rc.top, cs);
		}
		if (rc.top + t - iPos > rc.right) break;
	}

	pDC->SetTextColor(crt);
	pDC->SelectObject(of);
	pDC->SetTextAlign(oa);
	pDC->SelectObject(op);

	xMouse = -1;
	DrawMouse(oxm);
}

void CHorizRuler::SetPos(const int pos)
{
	iPos = pos;
	if (iPos < iFrom) iPos = iFrom;

	if (GetSafeHwnd()) Invalidate();
}

void CHorizRuler::SetRange(const int r1, const int r2)
{
	iFrom = r1;
	iTo = r2;
	if (iPos < iFrom) iPos = iFrom;
	if (GetSafeHwnd()) Invalidate();
}

BOOL CHorizRuler::OnEraseBkgnd(CDC* pDC) 
{
	return true;	
//	return CButton::OnEraseBkgnd(pDC);
}

void CHorizRuler::DrawMouse(const int x)
{
	if (x == xMouse) return;

	CRect rc;
	GetClientRect(rc);
	CClientDC dc(this);
	int orop = dc.SetROP2(R2_NOT);
	CPen pn(PS_DASHDOT, 1, RGB(0,0,0));
	CPen * op = dc.SelectObject(&pn);

	if (xMouse >= 0)
	{
		dc.MoveTo(xMouse, rc.top);
		dc.LineTo(xMouse, rc.bottom);
	}
	xMouse = x;
	if (xMouse >= 0)
	{
		dc.MoveTo(xMouse, rc.top);
		dc.LineTo(xMouse, rc.bottom);
	}

	dc.SetROP2(orop);
	dc.SelectObject(op);
}
