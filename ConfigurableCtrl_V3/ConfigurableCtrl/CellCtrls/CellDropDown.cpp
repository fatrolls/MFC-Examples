#include "stdafx.h"
#include "CellDropDown.h"
#include "..\utilities.h"
#include "listctrlcellwnd.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCellDropDown::CCellDropDown() : CCellButton(),
								m_pPopUpWnd(NULL),
								m_bPopUpBlocked(FALSE),
								m_bPopUpOpen(FALSE),
								m_eDropDownType(WDDT_ButtonClickOnly),
								m_bPumpActionButtonEffect(FALSE),
								m_lButtonOffset(DEFAULT_BUTTON_WIDTH)
{
	::ZeroMemory(&m_rcBounding, sizeof(RECT));
}

CCellDropDown::~CCellDropDown()
{
}

void CCellDropDown::DrawCtrl(CDC *pDC, const LPRECT prcCell, UINT uiItemState /*= 0*/)
{
	RECT			rcButton;
	int				iSavedDC = pDC->SaveDC();
	BOOL			PushedCond = FALSE;

	DrawFrameCtrl(pDC, prcCell);
	
	if (prcCell->right - prcCell->left > m_lButtonOffset)
	{
		rcButton.right = prcCell->right - ::GetSystemMetrics(SM_CXEDGE);
		rcButton.top = prcCell->top + ::GetSystemMetrics(SM_CYEDGE);
		rcButton.bottom = prcCell->bottom - ::GetSystemMetrics(SM_CYEDGE);
		rcButton.left = rcButton.right - ::GetSystemMetrics(SM_CXVSCROLL);

		PushedCond = (m_bPumpActionButtonEffect)? g_CritSect.IsButtonPushed() : m_bPopUpOpen;

		pDC->DrawFrameControl(&rcButton, DFC_SCROLL, DFCS_SCROLLCOMBOBOX | 
			(IsDisabled()? DFCS_INACTIVE : (PushedCond && m_bActive)? DFCS_FLAT : 0));// Used DFCS_FLAT and not DFCS_PUSHED, as this gives correct draw.

		m_bPopUpBlocked = FALSE;
	}
	else
		m_bPopUpBlocked = TRUE;

	pDC->RestoreDC(iSavedDC);
}

void CCellDropDown::CalculateTextAreaRect()
{
	CopyRect(&m_rcTextArea, &m_rcBounding);
	m_rcTextArea.left += ::GetSystemMetrics(SM_CXEDGE);
	m_rcTextArea.top += ::GetSystemMetrics(SM_CYEDGE);
	m_rcTextArea.right -= m_lButtonOffset;
	m_rcTextArea.bottom -= ::GetSystemMetrics(SM_CYEDGE);
}

int CCellDropDown::GetMinWidth()
{
	return m_lButtonOffset;
}

const RECT &CCellDropDown::GetTextRect() const
{
	return m_rcTextArea;
}

void CCellDropDown::OnInactiveResizeColumn(const CRect &Rect)
{
	CopyRect(&m_rcBounding, Rect);	
	m_bPopUpBlocked = (m_rcBounding.right - m_rcBounding.left > GetMinLegalWidth())? FALSE : TRUE;
	CalculateTextAreaRect();
}

void CCellDropDown::OnResizeColumn()
{
	Inactivate();
}

void CCellDropDown::ActivatePushButton(const CPoint &point)
{
	BOOL bWasButtonPushed = g_CritSect.IsButtonPushed();
	g_CritSect.SetPushButtonStatus((IsKeyDown(VK_LBUTTON) && PtInRect(&m_rcButton, point))? TRUE : FALSE); 

	if (bWasButtonPushed != g_CritSect.IsButtonPushed())
		GetWindowFromHandle()->InvalidateRect(&m_rcButton, FALSE);
}

struct ComboThreadInfo
{
	CPoint			*m_pPoint;
	CRect			*m_prcButton;
	HWND			m_hParentWnd;

	ComboThreadInfo() : m_pPoint(new CPoint), m_prcButton(new CRect){}
	~ComboThreadInfo(){delete m_pPoint;delete m_prcButton;}
};

UINT ButtonReaction(LPVOID pParam)
{
	Sleep(200);
	ComboThreadInfo *pClassDetails;

	pClassDetails = (ComboThreadInfo *)(pParam);

	BOOL bWasButtonPushed = g_CritSect.IsButtonPushed();
	BOOL bIsButtonPushed = (IsKeyDown(VK_LBUTTON) && PtInRect(pClassDetails->m_prcButton, *pClassDetails->m_pPoint))? TRUE : FALSE; 

	if (bWasButtonPushed != bIsButtonPushed)
	{
		g_CritSect.SetPushButtonStatus(bIsButtonPushed);
		CWnd *pWnd;
		pWnd = pWnd->FromHandle(pClassDetails->m_hParentWnd);
		pWnd->InvalidateRect(pClassDetails->m_prcButton, FALSE);
	}
	delete pClassDetails;
	return 0; 
}

BOOL CCellDropDown::OnPressButton(UINT nFlags, CPoint point)
{
	if (!m_bPopUpBlocked && !m_bPopUpOpen)
	{
		RECT rc;
		GetDropDownBoundingRect(rc);

		RECT ScreenCoordRect = rc, 
			ScreenRect = {0, 0, GetSystemMetrics(SM_CXFULLSCREEN), GetSystemMetrics(SM_CYFULLSCREEN)};
		
		GetWindowFromHandle()->GetParent()->ClientToScreen(&ScreenCoordRect);

	    if (!IsRectInRect(&ScreenCoordRect, &ScreenRect))
		{
			GetDropDownBoundingRect(rc, FALSE);
		}
		
		GetWindowFromHandle()->MapWindowPoints(NULL, &rc);
		VERIFY(m_pPopUpWnd->SetWindowPos(GetWindowFromHandle()->GetParent(), rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top, SWP_SHOWWINDOW));

		OnOpenDropDown();
		m_pPopUpWnd->SetFocus();
		m_bPopUpOpen = TRUE;

		g_CritSect.SetPushButtonStatus(TRUE);
		GetWindowFromHandle()->InvalidateRect(&m_rcButton, FALSE);

		if (m_bPumpActionButtonEffect)
		{
			ComboThreadInfo *pClassDetails = new ComboThreadInfo;

			pClassDetails->m_hParentWnd = m_hParentWnd;
			pClassDetails->m_pPoint->x = point.x;
			pClassDetails->m_pPoint->y = point.y;
			CopyRect(pClassDetails->m_prcButton, &m_rcButton);

			AfxBeginThread(ButtonReaction, pClassDetails);
		}
	}
	else if (!m_bPopUpBlocked)
	{
		if (m_pPopUpWnd)
		{
			m_pPopUpWnd->ShowWindow(SW_HIDE);
			m_bPopUpOpen = FALSE;
		}
	}
	return TRUE;
}

void CCellDropDown::CloseDropDown()
{
	m_bPopUpOpen = FALSE;
	m_pPopUpWnd->ShowWindow(SW_HIDE);
	GetWindowFromHandle()->InvalidateRect(&m_rcTextArea, FALSE);
	GetWindowFromHandle()->InvalidateRect(&m_rcButton, FALSE);
	GetWindowFromHandle()->SetFocus();
}

void CCellDropDown::OnCellCtrlMsg(WPARAM wParam, LPARAM lParam)
{
	if (wParam == ID_POPUP_SELCLOSE)
	{
		OnSelCloseDropDown(lParam);
		CloseDropDown();
	}
	else if (wParam == ID_POPUP_SELCHANGE)
	{
		OnSelChangeDropDown(lParam);
		GetWindowFromHandle()->InvalidateRect(&m_rcTextArea, FALSE);
	}
	else if (wParam == ID_POPUP_CLOSE)
		CloseDropDown();
}

void CCellDropDown::Inactivate()
{
	if (m_pPopUpWnd && CWnd::FromHandle(m_pPopUpWnd->m_hWnd))
		m_pPopUpWnd->ShowWindow(SW_HIDE);

	m_bPopUpOpen = FALSE;
}

void CCellDropDown::OnKillActive()
{
	CCellButton::OnKillActive();
	Inactivate();
}

void CCellDropDown::OnKillFocus(CWnd* pNewWnd)
{
	if (pNewWnd != m_pPopUpWnd && m_pPopUpWnd->IsWindowVisible())
	{
		Inactivate();
		GetWindowFromHandle()->InvalidateRect(&m_rcButton, FALSE);
	}
}

void CCellDropDown::OnParentMove(int x, int y)
{
	if (m_bPopUpOpen)
	{
		RECT rc;
		GetDropDownBoundingRect(rc);
		GetWindowFromHandle()->MapWindowPoints(NULL, &rc);
		VERIFY(m_pPopUpWnd->SetWindowPos(GetWindowFromHandle()->GetParent(), rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top, SWP_SHOWWINDOW));
	}
}

void CCellDropDown::SetWindowRect(LPRECT lpRect)
{
	CopyRect(&m_rcBounding, lpRect);

	CalculateTextAreaRect();

	if (m_eDropDownType == WDDT_ClickAnyWhere)
	{
		CopyRect(&m_rcClickRect, lpRect);
		CopyRect(&m_rcButton, lpRect);
		m_rcButton.left = m_rcButton.right - m_lButtonOffset;
	}
	else if (m_eDropDownType == WDDT_ButtonClickOnly)
	{
		CopyRect(&m_rcButton, lpRect);
		m_rcButton.left = m_rcButton.right - m_lButtonOffset;
		CopyRect(&m_rcClickRect, &m_rcButton);
	}
}

BOOL CCellDropDown::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	m_pPopUpWnd->ShowWindow(SW_HIDE);
	return CCellButton::OnVScroll(nSBCode, nPos, pScrollBar);
} 

BOOL CCellDropDown::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	m_pPopUpWnd->ShowWindow(SW_HIDE);
	return CCellButton::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CCellDropDown::OnEnter()
{
	if (m_bPopUpOpen)
	{
		m_bPopUpOpen = FALSE;
		CListCtrlCellWnd *p = (CListCtrlCellWnd *)m_pPopUpWnd;
		p->OnEnter();
		GetWindowFromHandle()->InvalidateRect(&m_rcTextArea, FALSE);
		GetWindowFromHandle()->InvalidateRect(&m_rcButton, FALSE);
	}
}

void CCellDropDown::OnEscape()
{
	if (m_bPopUpOpen)
	{
		ReleaseCapture();
		CloseDropDown();
	}
}

BOOL CCellDropDown::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	BOOL bRetVal = TRUE;

	if (nChar == VK_F4 )
	{
		OnPressButton(nFlags, CPoint(0,0));
	}
	return bRetVal;
}

BOOL CCellDropDown::DrawThemeCombobox(HDC hDc, const LPRECT prcCell)
{
	BOOL	Drawn = FALSE;
	HTHEME hTheme = OpenThemeData(m_hParentWnd, _T("ComboBox"));
		
	if (hTheme)
	{
		Drawn =			TRUE;
		int				StateId;
		HRESULT			hRes = S_OK;
		RECT			rcButton;

		StateId = GetThemeStateId(CBB_NORMAL, CBB_HOT, CBB_FOCUSED, CBB_DISABLED);

		VERIFY(!(hRes = DrawThemeBackground(hTheme, hDc, CP_BORDER, StateId, prcCell, NULL)));

		VERIFY(!(hRes = GetThemeBackgroundContentRect(hTheme, hDc, CP_BORDER, StateId, prcCell, &rcButton)));

		// GetThemePartSize and GetThemeMetric don't seem to work very well, so have to use GetSystemMetrics.
		// ie the standard default button offset.
		rcButton.left = prcCell->right - m_lButtonOffset;

		if (m_eDropDownType == WDDT_ClickAnyWhere)
			CopyRect(&m_rcClickRect, prcCell);
		else if (m_eDropDownType == WDDT_ButtonClickOnly)
			CopyRect(&m_rcClickRect, &rcButton);
		
		if (prcCell->right - prcCell->left > m_lButtonOffset)
		{
			if (IsThemePartDefined(hTheme, CP_DROPDOWNBUTTONRIGHT, 0))
			{
				StateId = GetThemeButtonStateId(m_bPopUpOpen, CBXSR_NORMAL, CBXSR_HOT, CBXSR_PRESSED, CBXSR_DISABLED);
				VERIFY(!(hRes = DrawThemeBackground(hTheme, hDc, CP_DROPDOWNBUTTONRIGHT, StateId, &rcButton, NULL)));
			}
			else
			{
				StateId = GetThemeButtonStateId(m_bPopUpOpen, CBXS_NORMAL, CBXS_HOT, CBXS_PRESSED, CBXS_DISABLED);
				VERIFY(!(hRes = DrawThemeBackground(hTheme, hDc, CP_DROPDOWNBUTTON, StateId, &rcButton, NULL)));
			}
		}

		CloseThemeData(hTheme);
	}
	return Drawn;
}
