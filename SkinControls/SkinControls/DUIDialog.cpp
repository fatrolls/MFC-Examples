
#include "stdafx.h"
#include "DUIDialog.h"
#include "DUIDlgBuilder.h"

BEGIN_MESSAGE_MAP(CDUIDialog, CWnd)
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

CDUIDialog::CDUIDialog(UINT nIDTemplate, CWnd* pParentWnd) : CDialog(nIDTemplate, pParentWnd)
{
	m_pDuiManager = new CDUIManager;
	m_bMouseHover = false;
}

CDUIDialog::~CDUIDialog()
{
	SafeDelete(m_pDuiManager);
}

// 加载配置
bool CDUIDialog::LoadSkinXml(LPCTSTR lpszXml, LPCTSTR lpszWindow)
{
	ASSERT(m_pDuiManager);
	if (m_pDuiManager == NULL) return false;

	CDUIDialogBuilder dlgbuilder;
	return dlgbuilder.Create(lpszXml, lpszWindow, m_pDuiManager);
}

// 更新皮肤
bool CDUIDialog::UpdateSkinInfo(LPCTSTR lpszXml, LPCTSTR lpszWindow)
{
	ASSERT(m_pDuiManager);
	if (m_pDuiManager == NULL) return false;

	return m_pDuiManager->UpdateSkinInfo(lpszXml, lpszWindow);
}

// 绘画DUI控件
void CDUIDialog::DrawDuiControls(CDC* pDC)
{
	if (m_pDuiManager)
	{
		m_pDuiManager->PaintControls(pDC);
	}
}

// 初始化消息
BOOL CDUIDialog::OnInitDialog()
{
	__super::OnInitDialog();

	if (m_pDuiManager) m_pDuiManager->SetOwnerWnd(this);

	return TRUE;
}

void CDUIDialog::OnSize(UINT nType, int cx, int cy)
{
	__super::OnSize(nType, cx, cy);

	if (cx == 0 || cy == 0) return;

	if (m_pDuiManager) m_pDuiManager->SetWndSize(cx, cy);
}

void CDUIDialog::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (m_pDuiManager) m_pDuiManager->OnLButtonDown(point);

	__super::OnLButtonDown(nFlags, point);
}

void CDUIDialog::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (m_pDuiManager) m_pDuiManager->OnLButtonUp(point);

	__super::OnLButtonUp(nFlags, point);
}

void CDUIDialog::OnRButtonDown(UINT nFlags, CPoint point)
{
	if (m_pDuiManager) m_pDuiManager->OnRButtonDown(point);

	__super::OnRButtonDown(nFlags, point);
}

void CDUIDialog::OnRButtonUp(UINT nFlags, CPoint point)
{
	if (m_pDuiManager) m_pDuiManager->OnRButtonUp(point);

	__super::OnRButtonUp(nFlags, point);
}

void CDUIDialog::OnMouseMove(UINT nFlags, CPoint point)
{
	if (!m_bMouseHover)
	{
		// 注册消息
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

LRESULT CDUIDialog::OnMouseLeave(WPARAM wParam, LPARAM lParam)
{
	if (m_bMouseHover) m_pDuiManager->OnMouseLeave();
	m_bMouseHover = false;
	return 0;
}

BOOL CDUIDialog::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
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

LRESULT CDUIDialog::OnDuiMessage(WPARAM wParam, LPARAM lParam)
{
	DuiMessageHandler((UINT)wParam, (CDUIControl*)lParam);

	return 0;
}
