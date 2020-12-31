#include "stdafx.h"
#include "CellButton.h"
#include "..\utilities.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCellButton::CCellButton() : CCellCtrl(), m_bIsButtonHot(FALSE)
{
	::ZeroMemory(&m_rcClickRect, sizeof(RECT));
}

CCellButton::~CCellButton()
{
}

BOOL CCellButton::OnLButtonDown(UINT nFlags, CPoint point)
{
	CCellCtrl::OnLButtonDown(nFlags, point);
	
	if (PtInRect(&m_rcClickRect, point))
	{
		// Need to check that m_rcClickRect is entirely inside the main list ctrl, otherwise can scroll
		// out of position, so that 
		CWnd *p = GetWindowFromHandle();
		
		if (p)
		{
			CRect Rect;
			p->GetClientRect(&Rect);
			Rect.InflateRect(1,1);

			if (IsRectInRect(&m_rcClickRect, &Rect))
				OnPressButton(nFlags, point);
		}
	}
	return TRUE;
}

void CCellButton::OnHotMouseMove(UINT nFlags, CPoint point)
{
	BOOL bWasButtonHot = m_bIsButtonHot;
	m_bIsButtonHot = PtInRect(&m_rcClickRect, point);
	if (bWasButtonHot != m_bIsButtonHot)
		GetWindowFromHandle()->InvalidateRect(&m_rcClickRect, FALSE);
} 

void CCellButton::OnKillHot()
{
	CCellCtrl::OnKillHot();
	m_bIsButtonHot = FALSE;
}