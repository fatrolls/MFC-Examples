#include "stdafx.h"
#include "..\Utilities.h"
#include "CellCtrl.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCellCtrl::CCellCtrl() : m_strText(_T("")), m_hParentWnd(NULL), m_bActive(FALSE), m_dwStyle(0), m_bHot(FALSE), m_pParentEnabled(NULL)
{

}

CCellCtrl::~CCellCtrl()
{

}

void CCellCtrl::AddToStyle(DWORD dwFlags)
{
	m_dwStyle |= dwFlags;
}

void CCellCtrl::RemoveFromStyle(DWORD dwFlags)
{
	m_dwStyle &= ~dwFlags;
}

void CCellCtrl::DrawFrameCtrl(CDC *pDC, const LPRECT prcCell)
{
	DWORD dwStyle = GetStyle();

	if ((m_bActive && (dwStyle & CLCS_ACTIVE_FRM_NORMAL)) || (!m_bActive && (dwStyle & CLCS_INACTIVE_FRM_NORMAL)))
	{
		pDC->DrawEdge(prcCell, EDGE_SUNKEN, BF_RECT);
	}
	else if ((m_bActive && (dwStyle & CLCS_ACTIVE_FRM_PLAIN)) || (!m_bActive && (dwStyle & CLCS_INACTIVE_FRM_PLAIN)))
	{
		int				iSavedDC;
		LOGBRUSH		LogBrush;
		CBrush			Brush;
		
		iSavedDC = pDC->SaveDC();
		::ZeroMemory(&LogBrush, sizeof(LogBrush));
		LogBrush.lbStyle = BS_NULL;
		Brush.CreateBrushIndirect(&LogBrush);
		pDC->SelectObject(Brush);
		pDC->Rectangle(prcCell);
		Brush.DeleteObject();
		pDC->RestoreDC(iSavedDC);
	}
}

int CCellCtrl::GetAlignDrawFlag() const
{
	if (m_dwStyle & CLCS_ALIGN_CENTER)
		return DT_CENTER;

	if (m_dwStyle & CLCS_ALIGN_RIGHT)
		return DT_RIGHT;

	return DT_LEFT;
}