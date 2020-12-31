
#include "stdafx.h"
#include "DuiWnd.h"
#include "DUIDlgBuilder.h"

BEGIN_MESSAGE_MAP(CDUIWnd, CWnd)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_MESSAGE(WM_MOUSELEAVE, OnMouseLeave)
	ON_MESSAGE(WM_DUI_MESSAGE, OnDuiMessage)
	ON_WM_SETCURSOR()
END_MESSAGE_MAP()

CDUIWnd::CDUIWnd()
{
	m_pDuiManager = new CDUIManager;
	m_bMouseHover = false;
}

CDUIWnd::~CDUIWnd()
{
	SafeDelete(m_pDuiManager);
}

// ¼ÓÔØÅäÖÃ
bool CDUIWnd::LoadSkinXml(LPCTSTR lpszXml, LPCTSTR lpszWindow)
{
	ASSERT(m_pDuiManager);
	if (m_pDuiManager == NULL) return false;

	CDUIDialogBuilder dlgbuilder;
	return dlgbuilder.Create(lpszXml, lpszWindow, m_pDuiManager);
}

// ¸üÐÂÆ¤·ô
bool CDUIWnd::UpdateSkinInfo(LPCTSTR lpszXml, LPCTSTR lpszWindow)
{
	ASSERT(m_pDuiManager);
	if (m_pDuiManager == NULL) return false;

	return m_pDuiManager->UpdateSkinInfo(lpszXml, lpszWindow);
}

// »æ»­DUI¿Ø¼þ
void CDUIWnd::DrawDuiControls(CDC* pDC)
{
	if (m_pDuiManager)
	{
		m_pDuiManager->PaintControls(pDC);
	}
}

int CDUIWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (__super::OnCreate(lpCreateStruct) == -1) return -1;

	if (m_pDuiManager) m_pDuiManager->SetOwnerWnd(this);

	return 0;
}

void CDUIWnd::OnSize(UINT nType, int cx, int cy)
{
	__super::OnSize(nType, cx, cy);

	if (cx == 0 || cy == 0) return;

	if (m_pDuiManager) m_pDuiManager->SetWndSize(cx, cy);
}

void CDUIWnd::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (m_pDuiManager) m_pDuiManager->OnLButtonDown(point);

	__super::OnLButtonDown(nFlags, point);
}

void CDUIWnd::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (m_pDuiManager) m_pDuiManager->OnLButtonUp(point);

	__super::OnLButtonUp(nFlags, point);
}

void CDUIWnd::OnRButtonDown(UINT nFlags, CPoint point)
{
	if (m_pDuiManager) m_pDuiManager->OnRButtonDown(point);

	__super::OnRButtonDown(nFlags, point);
}

void CDUIWnd::OnRButtonUp(UINT nFlags, CPoint point)
{
	if (m_pDuiManager) m_pDuiManager->OnRButtonUp(point);

	__super::OnRButtonUp(nFlags, point);
}

void CDUIWnd::OnMouseMove(UINT nFlags, CPoint point)
{
	if (!m_bMouseHover)
	{
		// ×¢²áÏûÏ¢
		m_bMouseHover = true;
		TRACKMOUSEEVENT TrackMouseEvent;
		TrackMouseEvent.cbSize = sizeof(TrackMouseEvent);
		TrackMouseEvent.dwFlags = TME_LEAVE;
		TrackMouseEvent.hwndTrack = GetSafeHwnd();
		TrackMouseEvent.dwHoverTime = HOVER_DEFAULT;
		_TrackMouseEvent(&TrackMouseEvent);
	}
	if (m_pDuiManager) m_pDuiManager->OnMouseMove(point);

	__super::OnMouseMove(nFlags, point);
}

LRESULT CDUIWnd::OnMouseLeave(WPARAM wParam, LPARAM lParam)
{
	if (m_bMouseHover) m_pDuiManager->OnMouseLeave();
	m_bMouseHover = false;
	return 0;
}

BOOL CDUIWnd::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	CPoint point;
	GetCursorPos(&point);
	ScreenToClient(&point);
	if (m_pDuiManager && m_pDuiManager->OnMouseCursor(point))
	{
		return TRUE;
	}

	return __super::OnSetCursor(pWnd, nHitTest, message);
}

LRESULT CDUIWnd::OnDuiMessage(WPARAM wParam, LPARAM lParam)
{
	DuiMessageHandler((UINT)wParam, (CDUIControl*)lParam);

	return 0;
}
