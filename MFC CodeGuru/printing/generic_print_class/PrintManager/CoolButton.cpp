// CoolButton.cpp : implementation file
//

#include "stdafx.h"
#include "PrintManager.h"
#include "CoolButton.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCoolButton

CCoolButton::CCoolButton()
{
	bHighlight = bLBtnDown = false;
	hHand = AfxGetApp()->LoadCursor(IDC_HANDCUR);
}

CCoolButton::~CCoolButton()
{
	if (fUnderline.GetSafeHandle()) fUnderline.DeleteObject();
}


BEGIN_MESSAGE_MAP(CCoolButton, CButton)
	//{{AFX_MSG_MAP(CCoolButton)
	ON_WM_MOUSEMOVE()
	ON_WM_SETCURSOR()
	ON_WM_TIMER()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_CREATE()
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCoolButton message handlers

void CCoolButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);

	CRect rect(lpDrawItemStruct->rcItem);

	COLORREF oc = pDC->GetTextColor();
	int iObk = pDC->SetBkMode(TRANSPARENT);

	UINT state = lpDrawItemStruct->itemState;

	CFont * pOldFont = NULL;

	int iYOffset = 0, iXOffset = 0;

	CString strText;
	GetWindowText(strText);

	rect.top  += iYOffset;
	rect.left += iXOffset;


	if (state & ODS_DISABLED)
	{		
		CBrush grayBrush;
		grayBrush.CreateSolidBrush (GetSysColor (COLOR_GRAYTEXT));
		CSize sz = pDC->GetTextExtent(strText);
		int x = rect.left + (rect.Width() - sz.cx)/2;
		int y = rect.top + (rect.Height() - sz.cy)/2;
		
		rect.top  += 2;
		rect.left += 2;
		pDC->SetTextColor(GetSysColor(COLOR_3DHIGHLIGHT));
		pDC->DrawText(strText, rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		rect.top  -= 2;
		rect.left -= 2;
		pDC->SetTextColor(GetSysColor(COLOR_GRAYTEXT));
		pDC->DrawText(strText, rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}
	else
	{
		if (bHighlight)
		{
			if (state & ODS_SELECTED)
			{
				pDC->Draw3dRect(rect,GetSysColor(COLOR_3DSHADOW), GetSysColor(COLOR_3DHILIGHT));
			}
			else
			{
				pDC->Draw3dRect(rect,GetSysColor(COLOR_3DHILIGHT),GetSysColor(COLOR_3DSHADOW));
			}
			pDC->SetTextColor(RGB(0,0,255));

			if (fUnderline.GetSafeHandle() == NULL)
			{
				CFont * pFont = GetFont();
				ASSERT(pFont);
				LOGFONT lf;
				pFont->GetLogFont(&lf);
				lf.lfUnderline = TRUE;
				fUnderline.CreateFontIndirect(&lf);		
			}

			pOldFont = pDC->SelectObject(&fUnderline);
		}
		else pDC->SetTextColor(GetSysColor(COLOR_BTNTEXT));

		pDC->DrawText(strText, rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		if (pOldFont) pDC->SelectObject(pOldFont);
	}
}

void CCoolButton::OnMouseMove(UINT nFlags, CPoint point) 
{
	SetTimer(1,10,NULL);
	
	CButton::OnMouseMove(nFlags, point);
}

BOOL CCoolButton::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	if (bHighlight) 
	{
		::SetCursor(hHand);
		return true;
	}

	return CButton::OnSetCursor(pWnd, nHitTest, message);
}

void CCoolButton::OnTimer(UINT nIDEvent) 
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

void CCoolButton::OnLButtonUp(UINT nFlags, CPoint point) 
{
	bLBtnDown = false;
	if (bHighlight)	
	{
		bHighlight = false;
		InvalidateRect(NULL);
	}
	CButton::OnLButtonUp(nFlags, point);
}

void CCoolButton::OnLButtonDown(UINT nFlags, CPoint point) 
{
	bLBtnDown = true;
	CButton::OnLButtonDown(nFlags, point);
}

int CCoolButton::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CButton::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	CFont * pFont = GetFont();
	ASSERT(pFont);

	LOGFONT lf;
	pFont->GetLogFont(&lf);
	lf.lfUnderline = TRUE;

	fUnderline.CreateFontIndirect(&lf);

	return 0;
}

BOOL CCoolButton::PreCreateWindow(CREATESTRUCT& cs) 
{
	cs.style |= BS_OWNERDRAW;
	return CButton::PreCreateWindow(cs);
}

BOOL CCoolButton::OnEraseBkgnd(CDC* pDC) 
{
	COLORREF cr = GetSysColor(COLOR_3DFACE);
	int r = GetRValue(cr);
	int g = GetGValue(cr);
	int b = GetBValue(cr);
	if (r > 1) r -= 2;
	if (g > 1) g -= 2;
	if (r < 3 && g < 3 && b < 253) b += 2;
	COLORREF cr1 = RGB(r,g,b);
	CRect rc;
	GetClientRect(rc);
	pDC->FillSolidRect(rc, cr1);
	return true;
}
