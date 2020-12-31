
#include "stdafx.h"
#include "Resource.h"
#include "SkinDialog.h"

IMPLEMENT_DYNAMIC(CSkinDialog, CDialog)

BEGIN_MESSAGE_MAP(CSkinDialog, CDialog)
	ON_WM_NCCALCSIZE()
	ON_WM_NCHITTEST()
	ON_WM_NCPAINT()
	ON_MESSAGE(WM_SETTEXT, OnSetTextMesage)
	ON_WM_SIZE()
	ON_WM_NCMOUSEMOVE()
	ON_WM_NCMOUSELEAVE()
	ON_WM_NCLBUTTONDOWN()
	ON_WM_NCLBUTTONUP()
	ON_WM_NCRBUTTONUP()
	ON_WM_ACTIVATEAPP()
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()

// 构造函数
CSkinDialog::CSkinDialog(UINT nIDTemplate, CWnd* pParentWnd) 
	: CDialog(nIDTemplate, pParentWnd)
{
	m_pSkin = new CSkinWindow;

	m_crBackground = RGB(207, 229, 245);
	m_crBottomBar = RGB(192, 222, 244);
	m_BkBrush.CreateSolidBrush(m_crBackground);
	m_crBottomLine = RGB(76, 162, 225);
	m_nBottomBarHeight = 30;
}

// 析构函数
CSkinDialog::~CSkinDialog()
{
	if (m_BkBrush.GetSafeHandle())
	{
		m_BkBrush.DeleteObject();
	}

	if (m_pSkin != NULL)
	{
		delete m_pSkin;
		m_pSkin = NULL;
	}
}

// 初始化消息
BOOL CSkinDialog::OnInitDialog()
{
	__super::OnInitDialog();

	if (m_pSkin != NULL) m_pSkin->InitWindow(this);

	return TRUE;
}

// 非客户区大小
void CSkinDialog::OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS* lpncsp)
{
	if (m_pSkin != NULL)
	{
		m_pSkin->OnNcCalcSize(this, bCalcValidRects, lpncsp);
	}
	else
	{
		__super::OnNcCalcSize(bCalcValidRects, lpncsp);
	}
}

// 非客户区按键测试
LRESULT CSkinDialog::OnNcHitTest(CPoint point)
{
	if (m_pSkin != NULL)
	{
		return m_pSkin->OnNcHitTest(this, point, (GetStyle() & WS_THICKFRAME) ? TRUE : FALSE);
	}
	else
	{
		return __super::OnNcHitTest(point);
	}
}

// 非客户区绘制
void CSkinDialog::OnNcPaint()
{
	if (m_pSkin != NULL)
	{
		m_pSkin->OnNcPaint(this);
	}
	else
	{
		__super::OnNcPaint();
	}
}

// 标题消息
LRESULT CSkinDialog::OnSetTextMesage(WPARAM wParam, LPARAM lParam)
{
	if (m_pSkin != NULL)
	{
		BOOL bVisible = IsWindowVisible();
		if (bVisible) ModifyStyle(WS_VISIBLE, 0);
		LONG lResult = Default();
		if (bVisible) ModifyStyle(0, WS_VISIBLE);
		m_pSkin->OnSetText(this);
		return lResult;
	}
	else
	{
		return Default();
	}
}

// 位置消息
void CSkinDialog::OnSize(UINT nType, int cx, int cy)
{
	if (m_pSkin != NULL) m_pSkin->OnSize(this);

	__super::OnSize(nType, cx, cy);
}

// 非客户区鼠标移动
void CSkinDialog::OnNcMouseMove(UINT nHitTest, CPoint point)
{
	if (m_pSkin != NULL) m_pSkin->OnNcMouseMove(this, nHitTest, point);

	__super::OnNcMouseMove(nHitTest, point);
}

// 非客户区鼠标离开
void CSkinDialog::OnNcMouseLeave()
{
	if (m_pSkin != NULL) m_pSkin->OnNcMouseLeave(this);

	__super::OnNcMouseLeave();
}

// 左键按下
void CSkinDialog::OnNcLButtonDown(UINT nFlags, CPoint point)
{
	if (m_pSkin != NULL && m_pSkin->OnNcLButtonDown(this, nFlags, point)) return;

	__super::OnNcLButtonDown(nFlags, point);
}

// 左键松开
void CSkinDialog::OnNcLButtonUp(UINT nFlags, CPoint point)
{
	if ( m_pSkin != NULL && m_pSkin->OnNcLButtonUp(this, nFlags, point)) return;

	__super::OnNcLButtonUp(nFlags, point);
}

// 右键松开
void CSkinDialog::OnNcRButtonUp(UINT nFlags, CPoint point)
{
	if ( m_pSkin != NULL) m_pSkin->OnNcRButtonUp(this, nFlags, point);
	
	__super::OnNcRButtonUp(nFlags, point);
}

// 激活消息
void CSkinDialog::OnActivateApp(BOOL bActive, DWORD dwThreadID)
{
	if (m_pSkin != NULL) m_pSkin->OnActivateApp(this, bActive, dwThreadID);
	else __super::OnActivateApp(bActive, dwThreadID);
}

// 控件颜色
HBRUSH CSkinDialog::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	switch (nCtlColor)
	{
	case CTLCOLOR_BTN:
	case CTLCOLOR_STATIC:
		{
			pDC->SetBkMode(TRANSPARENT);
			return (HBRUSH)m_BkBrush;
		}
	}

	return __super::OnCtlColor(pDC, pWnd, nCtlColor);
}

// 背景
BOOL CSkinDialog::OnEraseBkgnd(CDC * pDC)
{
	CRect rcClient, rcDraw;
	GetClientRect(&rcClient);

	rcDraw = rcClient;
	rcDraw.bottom -= m_nBottomBarHeight;
	pDC->FillSolidRect(&rcDraw, m_crBackground);

	rcDraw.top = rcDraw.bottom;
	rcDraw.bottom = rcDraw.top + 1;
	pDC->FillSolidRect(&rcDraw, m_crBottomLine);
	rcDraw.top = rcDraw.bottom;
	rcDraw.bottom = rcDraw.top + 1;
	pDC->FillSolidRect(&rcDraw, RGB(255, 255, 255));

	rcDraw.top = rcDraw.bottom;
	rcDraw.bottom = rcClient.bottom;
	pDC->FillSolidRect(&rcDraw, m_crBottomBar);

	return TRUE;
}

// 设置SKIN图片
bool CSkinDialog::SetSkinImage(LPCTSTR pszFileName, BitmapFormat bf)
{
	if (m_pSkin != NULL) return m_pSkin->SetSkinImage(pszFileName, bf);

	return false;
}

bool CSkinDialog::SetSkinImage(BYTE* pBuffer, DWORD dwBufferSize, BitmapFormat bf)
{
	if (m_pSkin != NULL) return m_pSkin->SetSkinImage(pBuffer, dwBufferSize, bf);

	return false;
}

bool CSkinDialog::SetSkinImage(LPCTSTR lpszResource, HINSTANCE hInst, BitmapFormat bf)
{
	if (m_pSkin != NULL) return m_pSkin->SetSkinImage(lpszResource, hInst, bf);

	return false;
}

// 设置标题文字颜色 crInactiveText: 未激活文字的颜色
void CSkinDialog::SetCaptionTextColor(COLORREF crText, COLORREF crInactiveText)
{
	if (m_pSkin != NULL) m_pSkin->SetCaptionTextColor(crText, crInactiveText);
}