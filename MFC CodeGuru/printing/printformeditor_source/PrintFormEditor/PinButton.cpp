// PinButton.cpp : implementation file
//

#include "stdafx.h"
#include "printformeditor.h"
#include "PinButton.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPinButton

CPinButton::CPinButton()
{
	pBmp = pCheckBmp = pCheckBmpPressed = NULL;
	bCheckMode = false;
	bCheckStatus = false;
	bHighlight = bLBtnDown = false;
	bCloseLock = false;
}

CPinButton::~CPinButton()
{
	if (pBmp) delete pBmp;
	if (pCheckBmp) delete pCheckBmp;
	if (pCheckBmpPressed) delete pCheckBmpPressed;
}

BEGIN_MESSAGE_MAP(CPinButton, CButton)
	//{{AFX_MSG_MAP(CPinButton)
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_KILLFOCUS()
	ON_WM_SETFOCUS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPinButton message handlers

void CPinButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	CDC * pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
	CRect rect(lpDrawItemStruct->rcItem);


	int iObk = pDC->SetBkMode(TRANSPARENT);
	UINT state = lpDrawItemStruct->itemState;

	int iYOffset = 0, iXOffset = 0;

	rect.top  += iYOffset;
	rect.left += iXOffset;

	CRect bdrRect(rect);

	int ix1 = 0, iy1 = 0;

	if (bHighlight)
	{
		if (state & ODS_SELECTED)
		{
			ix1 = 1;
			iy1 = 1;
		}
	}
	CBitmap * pBitmap = pBmp;
	if (bCheckMode && bCheckStatus) 
	{
		if (bHighlight) pBitmap = pCheckBmpPressed;
		else pBitmap = pCheckBmp;
	}

	if (pBitmap)
	{
		CDC tempDC;
		tempDC.CreateCompatibleDC(pDC);
		tempDC.SelectObject(pBitmap);
		int y = rect.top + 1;
		y = (rect.Height() - rcImage.Height()) / 2 + rect.top;
		int x = (rect.Width() - rcImage.Width()) / 2 + rect.left;
		pDC->BitBlt(x + ix1, y + iy1, rcImage.Width(), rcImage.Height(), &tempDC, 0, 0, SRCCOPY );
		rect.top += (rcImage.Height() + 2);
	}

	if (bCheckMode && bCheckStatus)
		pDC->Draw3dRect(bdrRect,GetSysColor(COLOR_3DSHADOW), GetSysColor(COLOR_3DHILIGHT));
	else if (bHighlight)
	{
		if (state & ODS_SELECTED)
			pDC->Draw3dRect(bdrRect,GetSysColor(COLOR_3DSHADOW), GetSysColor(COLOR_3DHILIGHT));
		else
			pDC->Draw3dRect(bdrRect,GetSysColor(COLOR_3DHILIGHT),GetSysColor(COLOR_3DSHADOW));
	}
}

int CPinButton::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CButton::OnCreate(lpCreateStruct) == -1)
		return -1;

	return 0;
}

void CPinButton::OnTimer(UINT nIDEvent) 
{
	static bool pPainted = false;	
	POINT pt;	
	GetCursorPos(&pt);	
	CRect rect;
	GetWindowRect (rect);	
	if (bLBtnDown)	
	{		
		KillTimer (1);
		if (pPainted) InvalidateRect (NULL);		
		pPainted = FALSE;		
		return;	
	}

	if (!rect.PtInRect (pt))	
	{		
		bHighlight = false;
		KillTimer (1);

		if (pPainted)			
			InvalidateRect(NULL);

		pPainted = false;
		return;	
	}
	else
	{
		bHighlight = true;
		if (!pPainted)
		{
			pPainted = true;
			InvalidateRect(NULL);
		}
	}
	
	CButton::OnTimer(nIDEvent);
}

bool CPinButton::SetBitmap(int resId, COLORREF * rmp, const bool bIsCheck)
{
	BITMAP bm;
	if (bIsCheck)
	{
		if (!pCheckBmp) pCheckBmp = new CBitmap;
		ASSERT(pCheckBmp);
		if (rmp)
		{
			COLORMAP cmMap = { *rmp, GetSysColor(COLOR_3DFACE) };
			if (pCheckBmp->LoadMappedBitmap(resId, 0, &cmMap, 1))
			{
				pCheckBmp->GetBitmap(&bm);
				rcImage.SetRect(0,0,bm.bmWidth, bm.bmHeight);
				return true;
			}
		}
		else
		{
			if (pCheckBmp->LoadBitmap(resId))
			{
				pCheckBmp->GetBitmap(&bm);
				rcImage.SetRect(0,0,bm.bmWidth, bm.bmHeight);
				return true;
			}
		}
	}
	else
	{
		if (!pBmp) pBmp = new CBitmap;
		ASSERT(pBmp);
		if (rmp)
		{
			COLORMAP cmMap = { *rmp, GetSysColor(COLOR_3DFACE) };
			if (pBmp->LoadMappedBitmap(resId, 0, &cmMap, 1))
			{
				pBmp->GetBitmap(&bm);
				rcImage.SetRect(0,0,bm.bmWidth, bm.bmHeight);
				return true;
			}
		}
		else
		{
			if (pBmp->LoadBitmap(resId))
			{
				pBmp->GetBitmap(&bm);
				rcImage.SetRect(0,0,bm.bmWidth, bm.bmHeight);
				return true;
			}
		}
	}
	return false;
}

bool CPinButton::SetBitmapCheckPress(int resId, COLORREF * rmp)
{
	BITMAP bm;
	if (!pCheckBmpPressed) pCheckBmpPressed = new CBitmap;
	ASSERT(pCheckBmpPressed);
	if (rmp)
	{
		COLORMAP cmMap = { *rmp, GetSysColor(COLOR_3DFACE) };
		if (pCheckBmpPressed->LoadMappedBitmap(resId, 0, &cmMap, 1))
		{
			pCheckBmpPressed->GetBitmap(&bm);
			rcImage.SetRect(0,0,bm.bmWidth, bm.bmHeight);
			return true;
		}
	}
	else
	{
		if (pCheckBmpPressed->LoadBitmap(resId))
		{
			pCheckBmpPressed->GetBitmap(&bm);
			rcImage.SetRect(0,0,bm.bmWidth, bm.bmHeight);
			return true;
		}
	}
	return false;
}


void CPinButton::EnableCheckMode(const bool bCheck)
{
	bCheckMode = bCheck;
}

bool CPinButton::IsDlgButtonChecked()
{
	return bCheckStatus;
}

void CPinButton::OnMouseMove(UINT nFlags, CPoint point) 
{
	SetTimer(1,10,NULL);
	CButton::OnMouseMove(nFlags, point);
}

void CPinButton::OnLButtonDown(UINT nFlags, CPoint point) 
{
	bLBtnDown = true;
	CButton::OnLButtonDown(nFlags, point);
}

void CPinButton::OnLButtonUp(UINT nFlags, CPoint point) 
{
	bLBtnDown = false;
	bool bThis = false;
	CPoint rpt(point);
	ClientToScreen(&rpt);
	CWnd * pWnd = WindowFromPoint(rpt);
	if (pWnd && pWnd->GetSafeHwnd() == GetSafeHwnd()) bThis = true;

	if (bCheckMode && bThis) 
	{
		bCheckStatus = !bCheckStatus;
		InvalidateRect(NULL);
	}
	if (bHighlight)	
	{
		bHighlight = false;
		InvalidateRect(NULL);
	}
//	if (bCheckMode) CButton::OnLButtonUp(nFlags, point);
//	else 
		if (!bCheckMode && bThis)
	{
		if (!bCheckMode) bCloseLock = true;
		GetParent()->SendMessage(WM_COMMAND, MAKELONG(GetDlgCtrlID(), BN_CLICKED), (LPARAM) GetSafeHwnd());
		if (!bCheckMode) bCloseLock = false;
	}
	CButton::OnLButtonUp(nFlags, point);
}

void CPinButton::OnKillFocus(CWnd* pNewWnd) 
{
	CButton::OnKillFocus(pNewWnd);
	if (pNewWnd && pNewWnd != GetParent() && !(GetParent()->IsChild(pNewWnd)) && !bCloseLock)
		GetParent()->SendMessage(WM_KILLFOCUS, (WPARAM) pNewWnd);
}

void CPinButton::OnSetFocus(CWnd* pOldWnd) 
{
	CButton::OnSetFocus(pOldWnd);
	
//	if (pOldWnd && pOldWnd != GetParent()) 
//		GetParent()->SetFocus();
	
}
