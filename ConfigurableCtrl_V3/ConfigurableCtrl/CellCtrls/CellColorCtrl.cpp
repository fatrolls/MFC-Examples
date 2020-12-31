#include "stdafx.h"
#include "CellColorCtrl.h"
#include "PopUpColorBar.h"

DWORD CCellColorCtrl::m_dwDateCtrlStyle = 0;

CCellColorCtrl::CCellColorCtrl() //: m_Color(0x00ABCDEF)
{
	m_pPopUpWnd = new CPopupColorBar;
}

CCellColorCtrl::~CCellColorCtrl()
{
	delete m_pPopUpWnd;
}

void CCellColorCtrl::DrawCtrl(CDC *pDC, const LPRECT prcCell, UINT uiItemState /*= 0*/)
{
	CBrush			Brush;
	int				iSavedDC;
	RECT			rcColorArea;

	Brush.CreateSolidBrush(GetSysColor(IsDisabled()? COLOR_BTNFACE : COLOR_WINDOW));
	pDC->FillRect(prcCell, &Brush);
	Brush.DeleteObject();

	iSavedDC = pDC->SaveDC();
	BOOL bThemeDrawn = DrawThemeCombobox(pDC->m_hDC, prcCell);

	COLORREF SelColor = GetSelectedColor();

	Brush.CreateSolidBrush(SelColor);

	CopyRect(&rcColorArea, prcCell); 
	
	InflateRect(&rcColorArea, -::GetSystemMetrics(SM_CXFIXEDFRAME), -::GetSystemMetrics(SM_CYFIXEDFRAME));
	rcColorArea.right -= ::GetSystemMetrics(SM_CXVSCROLL);
	
	if (rcColorArea.right > rcColorArea.left)
		pDC->FillRect(&rcColorArea, &Brush);

	Brush.DeleteObject();

	if (!bThemeDrawn)
	{
		pDC->DrawEdge(prcCell, EDGE_SUNKEN, BF_RECT);
		CCellDropDown::DrawCtrl(pDC, prcCell, uiItemState);
	}
	pDC->RestoreDC(iSavedDC);
}

void CCellColorCtrl::Initialize(HWND hParentWnd, BOOL *pParentEnabled, LPCTSTR strText)
{
	CCellDropDown::Initialize(hParentWnd, pParentEnabled, strText);

	CPopupColorBar *p = dynamic_cast<CPopupColorBar *>(m_pPopUpWnd);

	if (p)
	{
		p->Create(m_hParentWnd, this);		
	}
}

int CCellColorCtrl::GetMinWidth()
{
	return CCellDropDown::GetMinWidth();
}

void CCellColorCtrl::AddToCtrlTypeStyle(DWORD dwFlags)
{
}

void CCellColorCtrl::RemoveFromCtrlTypeStyle(DWORD dwFlags)
{
}

LONG CCellColorCtrl::GetStyle()
{
	return m_dwDateCtrlStyle | m_dwStyle;
}

void CCellColorCtrl::OnOpenDropDown()
{
	CPopupColorBar *pPopUpColorBar = dynamic_cast<CPopupColorBar *>(m_pPopUpWnd);

	if (pPopUpColorBar)
		pPopUpColorBar->OpenDropDown(GetSelectedColor());
}

void CCellColorCtrl::GetDropDownBoundingRect(RECT &rc, BOOL downwards /*= TRUE*/)
{
	CPopupColorBar *p = dynamic_cast<CPopupColorBar *>(m_pPopUpWnd);

	if (p)
	{
		p->GetBoundingRect(m_rcBounding, rc, downwards);
	}
}

void CCellColorCtrl::OnSelCloseDropDown(LPARAM lParam)
{
	m_strText.Format(_T("%#010X"), lParam); 
}