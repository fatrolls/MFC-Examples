#include "StdAfx.h"
#include "CellSpinCtrl.h"

DWORD CCellSpinCtrl::m_dwSpinCtrlStyle = CLCS_ACTIVE_FRM_NORMAL | CLCS_INACTIVE_FRM_NORMAL;

CCellSpinCtrl::CCellSpinCtrl() : m_TopPressed(FALSE), m_BottomPressed(FALSE), 
					m_TopPressedNotReleased(FALSE), m_BottomPressedNotReleased(FALSE),
					m_bIsBottomHot(FALSE), m_bIsTopHot(FALSE),
					m_TimerID(0), m_TimerStep(0)
{
	::ZeroMemory(&m_rcUpClick, sizeof(RECT));
	::ZeroMemory(&m_rcDownClick, sizeof(RECT));
	::ZeroMemory(&m_rcTxtArea, sizeof(RECT));
}

CCellSpinCtrl::~CCellSpinCtrl()
{
}

void CCellSpinCtrl::InstantiateTimer()
{
// Really helpful article on how to get the repeat up/down buttons to work:
// http://www.codeproject.com/KB/system/mouserepeat.aspx	
	CWnd *p = GetWindowFromHandle();
	if (p && (m_TopPressed || m_BottomPressed))
	{
		p->SetCapture();
        int setting = 0;
        ::SystemParametersInfo(SPI_GETKEYBOARDDELAY, 0, &setting, 0);
        int interval = (setting + 1) * 250;
        m_TimerID = p->SetTimer(99, interval, NULL);
        m_TimerStep = 1;
	}
}

BOOL CCellSpinCtrl::OnLButtonDown(UINT nFlags, CPoint point)
{
	CCellCtrl::OnLButtonDown(nFlags, point);
	BOOL retVal = TRUE;

	if (PtInRect(&m_rcUpClick, point))
	{
		m_TopPressed = TRUE;
		m_BottomPressed = FALSE;
		m_TopPressedNotReleased = TRUE;
		m_BottomPressedNotReleased = FALSE;
		OnIncrement();
		retVal = FALSE;
	}
	else if (PtInRect(&m_rcDownClick, point))
	{
		m_TopPressed = FALSE;
		m_BottomPressed = TRUE;
		m_TopPressedNotReleased = FALSE;
		m_BottomPressedNotReleased = TRUE;
		OnDecrement();
		retVal = FALSE;
	}
	else
	{
		m_TopPressed = FALSE;
		m_BottomPressed = FALSE;
		m_TopPressedNotReleased = FALSE;
		m_BottomPressedNotReleased = FALSE;
	}
	InstantiateTimer();
	return retVal;
}

void CCellSpinCtrl::UnPressButtons()
{
	BOOL OldTopPressed = m_TopPressed, OldBottomPressed = m_BottomPressed;
	m_TopPressed = FALSE;
	m_BottomPressed = FALSE;

	CWnd *p = GetWindowFromHandle();

	if (p && OldTopPressed)
		p->InvalidateRect(&m_rcUpClick, FALSE);
	else if (p && OldBottomPressed)
		p->InvalidateRect(&m_rcDownClick, FALSE);

	if (p)
	{
		p->KillTimer(m_TimerID);
        ::ReleaseCapture();
        m_TimerStep = 0;
	}
}

BOOL CCellSpinCtrl::OnLButtonUp(UINT nFlags, CPoint point)
{ 
	UnPressButtons();
	m_TopPressedNotReleased = FALSE;
	m_BottomPressedNotReleased = FALSE;
	return TRUE; 
}

const RECT &CCellSpinCtrl::GetTextRect() const
{
	return m_rcTxtArea;
}

BOOL CCellSpinCtrl::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	BOOL bRetVal = TRUE;

	if (nChar == VK_UP)
	{
		OnIncrement();
		bRetVal = FALSE;
	}
	else if (nChar == VK_DOWN)
	{
		OnDecrement();
		bRetVal = FALSE;
	}
	return bRetVal;
}

void CCellSpinCtrl::DrawCtrl(CDC *pDC, const LPRECT prcCell, UINT uiItemState /*= 0*/)
{
	CString			strText;
	CBrush			Brush;
	int				iSavedDC;
	DWORD			dwStyle = GetStyle();
	BOOL			bHighlighted = FALSE;

	iSavedDC = pDC->SaveDC();

	HTHEME hTheme = OpenThemeData(m_hParentWnd, _T("EDIT"));
	HTHEME hSpinTheme = OpenThemeData(m_hParentWnd, _T("SPIN"));

	Brush.CreateSolidBrush(GetSysColor(IsDisabled()? COLOR_BTNFACE : COLOR_WINDOW));

	pDC->FillRect(prcCell, &Brush);

	// Calculate button rectangles:
	int BorderMargin = (hTheme && hSpinTheme)? 1 : 2;
	int SepMargin = (hTheme && hSpinTheme)? 1 : 0;

	CopyRect(&m_rcUpClick, prcCell);
	m_rcUpClick.left = prcCell->right - DEFAULT_BUTTON_WIDTH;
	m_rcUpClick.right = prcCell->right - BorderMargin;
	m_rcUpClick.top = prcCell->top + BorderMargin;
	m_rcUpClick.bottom = prcCell->top + (prcCell->bottom - prcCell->top)/2 + SepMargin;
	CopyRect(&m_rcDownClick, &m_rcUpClick);
	m_rcDownClick.top = prcCell->top + (prcCell->bottom - prcCell->top)/2 + SepMargin;
	m_rcDownClick.bottom = prcCell->bottom - BorderMargin;

	if (hTheme && hSpinTheme)
	{
		int				StateId;
		HRESULT			hRes = 0;
		RECT			rc;
		
		// Draw themed frame:
		StateId = GetThemeStateId(EPSN_NORMAL, EPSN_HOT, EPSN_FOCUSED, EPSN_DISABLED);
		hRes = DrawThemeBackground(hTheme, pDC->m_hDC, EP_EDITBORDER_NOSCROLL, StateId, prcCell, NULL);
		StateId = GetThemeStateId(ETS_NORMAL, ETS_HOT, ETS_FOCUSED, ETS_DISABLED);
		hRes = GetThemeBackgroundContentRect(hTheme, pDC->m_hDC, EP_EDITTEXT, StateId, prcCell, &rc);

		pDC->FillRect(&rc, &Brush);
		// Draw buttons:
		if (prcCell->right - prcCell->left >= DEFAULT_BUTTON_WIDTH)
		{
			StateId = GetThemeUpDownButtonStateId(TRUE, UPS_NORMAL, UPS_HOT, UPS_PRESSED, UPS_DISABLED);
			hRes = DrawThemeBackground(hSpinTheme, pDC->m_hDC, SPNP_UP, StateId, &m_rcUpClick, NULL);
			StateId = GetThemeUpDownButtonStateId(FALSE, DNS_NORMAL, DNS_HOT, DNS_PRESSED, DNS_DISABLED);
			hRes = DrawThemeBackground(hSpinTheme, pDC->m_hDC, SPNP_DOWN, StateId, &m_rcDownClick, NULL);
		}
	}
	if (uiItemState & (ODS_FOCUS | ODS_SELECTED) && !m_bActive && !IsDisabled())
	{
		CBrush	HighlightBrush;
		CRect	rcHighlight;	
		HighlightBrush.CreateSolidBrush(GetSysColor(IsDisabled()? COLOR_BTNFACE : COLOR_HIGHLIGHT));

		CopyRect(&rcHighlight, prcCell);
		InflateRect(&rcHighlight, -::GetSystemMetrics(SM_CXFIXEDFRAME), -::GetSystemMetrics(SM_CYFIXEDFRAME)); 
	
		rcHighlight.right -= (DEFAULT_BUTTON_WIDTH -::GetSystemMetrics(SM_CXFIXEDFRAME));

		if (rcHighlight.right > rcHighlight.left)
			pDC->FillRect(&rcHighlight, &HighlightBrush);

		HighlightBrush.DeleteObject();

		bHighlighted = TRUE;
	}

	CopyRect(&m_rcTxtArea, prcCell);
	InflateRect(&m_rcTxtArea, -::GetSystemMetrics(SM_CXFIXEDFRAME), -::GetSystemMetrics(SM_CYFIXEDFRAME));
	m_rcTxtArea.right -= DEFAULT_BUTTON_WIDTH;

	DrawTextArea(pDC, prcCell, bHighlighted);

	if (!hTheme || !hSpinTheme)
	{
		DrawFrameCtrl(pDC, prcCell);

		pDC->DrawFrameControl(&m_rcUpClick, DFC_SCROLL, DFCS_SCROLLUP | 
			(IsDisabled()? DFCS_INACTIVE : (m_TopPressed && m_bActive)? DFCS_FLAT : 0));

		pDC->DrawFrameControl(&m_rcDownClick, DFC_SCROLL, DFCS_SCROLLDOWN | 
			(IsDisabled()? DFCS_INACTIVE : (m_BottomPressed && m_bActive)? DFCS_FLAT : 0));
	}
	else
	{
		if (hTheme)
			CloseThemeData(hTheme);

		if (hSpinTheme)
			CloseThemeData(hSpinTheme);
	}
	Brush.DeleteObject();
	pDC->RestoreDC(iSavedDC);
}

void CCellSpinCtrl::OnHotMouseMove(UINT nFlags, CPoint point)
{
	CCellCtrl::OnHotMouseMove(nFlags, point);

	BOOL bWasButtonHot = m_bIsTopHot;
	m_bIsTopHot = PtInRect(&m_rcUpClick, point);
	if (bWasButtonHot != m_bIsTopHot)
		GetWindowFromHandle()->InvalidateRect(&m_rcUpClick, FALSE);

	bWasButtonHot = m_bIsBottomHot;
	m_bIsBottomHot = PtInRect(&m_rcDownClick, point);
	if (bWasButtonHot != m_bIsBottomHot)
		GetWindowFromHandle()->InvalidateRect(&m_rcDownClick, FALSE);
} 

void CCellSpinCtrl::OnKillHot()
{
	CCellCtrl::OnKillHot();
	m_bIsTopHot = FALSE;
	m_bIsBottomHot = FALSE;
}

BOOL CCellSpinCtrl::OnMouseMove(UINT nFlags, CPoint point)
{
	BOOL bUpActive = PtInRect(&m_rcUpClick, point),
		bDownActive = PtInRect(&m_rcDownClick, point);

	if (!bUpActive && !bDownActive)
		UnPressButtons();
	else if (bUpActive && m_TopPressedNotReleased && !m_TopPressed)
	{
		m_TopPressed = TRUE;
		OnIncrement();
		InstantiateTimer();
		GetWindowFromHandle()->InvalidateRect(&m_rcUpClick, FALSE);
	}
	else if (bDownActive && m_BottomPressedNotReleased && !m_BottomPressed)
	{
		m_BottomPressed = TRUE;
		OnDecrement();
		InstantiateTimer();
		GetWindowFromHandle()->InvalidateRect(&m_rcDownClick, FALSE);
	}
	return TRUE;
}

BOOL CCellSpinCtrl::OnTimer(UINT_PTR nIDEvent)
{
	CWnd *p = GetWindowFromHandle();

    if(p && m_TimerStep == 1)
    {
        p->KillTimer(m_TimerID);
        DWORD setting = 0;
        ::SystemParametersInfo(SPI_GETKEYBOARDSPEED, 0, &setting, 0);
        int interval = 400 - (setting * 12);
        m_TimerID = p->SetTimer(100, interval, NULL);
        m_TimerStep = 2;
    }

    if(m_TimerStep)
	{
		if (m_TopPressed)
			OnIncrement();
		else if (m_BottomPressed)
			OnDecrement();
	}
	return FALSE;
}

void CCellSpinCtrl::AddToCtrlTypeStyle(DWORD dwFlags)
{
	m_dwSpinCtrlStyle |= dwFlags;
}

void CCellSpinCtrl::RemoveFromCtrlTypeStyle(DWORD dwFlags)
{
	m_dwSpinCtrlStyle &= ~dwFlags;
}

LONG CCellSpinCtrl::GetStyle()
{
	return m_dwSpinCtrlStyle | m_dwStyle;
}


