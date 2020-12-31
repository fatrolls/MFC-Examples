
#include "stdafx.h"
#include "Resource.h"
#include "SkinStatic.h"
#include "SkinHelper.h"
#include "DrawHelpers.h"

IMPLEMENT_DYNAMIC(CSkinStatic, CStatic)

BEGIN_MESSAGE_MAP(CSkinStatic, CStatic)
	ON_WM_PAINT()
	ON_WM_CREATE()
    ON_WM_SETCURSOR()
	ON_WM_MOUSEMOVE()
	ON_MESSAGE(WM_MOUSELEAVE, OnMouseLeave)
	ON_MESSAGE(WM_SETTEXT, OnSetTextMesage)
	ON_WM_CTLCOLOR_REFLECT()
END_MESSAGE_MAP()

// 构造函数
CSkinStatic::CSkinStatic()
{
	m_bHovering = false;
	m_bUnderline = true;
	m_bSeperator = false;
	m_crBack = CLR_NONE;
	m_crHoverText=RGB(250, 0, 0);
	m_crNormalText=RGB(0, 0, 255);
	m_crSepFirst = RGB(76, 162, 225);
	m_crSepSecond = RGB(227, 243, 255);
}

// 析构函数
CSkinStatic::~CSkinStatic()
{
}

// 设置下划线
void CSkinStatic::SetUnderline(bool bUnderline)
{
	if (m_bUnderline != bUnderline)
	{
		m_bUnderline = bUnderline;
		if (GetSafeHwnd()) RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_ERASE | RDW_UPDATENOW | RDW_ERASENOW);
	}
	return;
}

// 设置分隔条
void CSkinStatic::SetSeperator(bool bSeperator)
{
	if (m_bSeperator != bSeperator)
	{
		m_bSeperator = bSeperator;
		if (GetSafeHwnd())
		{
			// 获取位置
			CRect ControlRect;
			GetWindowRect(&ControlRect);
			GetParent()->ScreenToClient(&ControlRect);
			ControlRect.top = ControlRect.top + ControlRect.Height() / 2;
			ControlRect.bottom = ControlRect.top + 1;
			MoveWindow(ControlRect, TRUE);
		}
	}
}

// 背景颜色
void CSkinStatic::SetBackColor(COLORREF crBackColor)
{
	// 设置变量
	m_crBack = crBackColor;

	// 重画窗口
	if (m_hWnd != NULL)
	{
		RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_ERASE | RDW_UPDATENOW | RDW_ERASENOW);
	}

	return;
}

// 字体颜色
void CSkinStatic::SetStaticTextColor(COLORREF crHoverText, COLORREF crNormalText)
{
	// 设置变量
	m_crHoverText = crHoverText;
	m_crNormalText = crNormalText;

	// 重画窗口
	if (m_hWnd != NULL)
	{
		RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_ERASE | RDW_UPDATENOW | RDW_ERASENOW);
	}

	return;
}

// 分隔条颜色
void CSkinStatic::SetSeperatorColor(COLORREF crFirst, COLORREF crSecond)
{
	m_crSepFirst = crFirst;
	m_crSepSecond = crSecond;

	// 重画窗口
	if (m_hWnd != NULL)
	{
		RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_ERASE | RDW_UPDATENOW | RDW_ERASENOW);
	}
}

// 控件子类化
void CSkinStatic::PreSubclassWindow()
{
	__super::PreSubclassWindow();

	return;
}

// 建立消息
int CSkinStatic::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (__super::OnCreate(lpCreateStruct) == -1) return -1;

	return 0;
}

HBRUSH CSkinStatic::CtlColor(CDC* pDC, UINT nCtlColor)
{
	pDC->SetBkMode(TRANSPARENT);
	return (HBRUSH)::GetStockObject(NULL_BRUSH);
}

// 绘画消息
void CSkinStatic::OnPaint()
{
	CPaintDC dc(this);

	// 获取位置
	CRect ClientRect;
	GetClientRect(&ClientRect);

	// 分隔条
	if (m_bSeperator)
	{
		DrawHelpers()->GradientFill(&dc, ClientRect, m_crSepFirst, m_crSepSecond, TRUE);
		return;
	}

	// 设置 DC
	dc.SetBkMode(TRANSPARENT);
	if (m_crBack != CLR_NONE) dc.FillSolidRect(&ClientRect, m_crBack);
	//// 创建字体
	//CFont font;
	//font.CreateFont(-12,0,0,0,0,0,(m_bUnderline&&m_bHovering)?1:0,0,0,3,2,ANTIALIASED_QUALITY,2,TEXT("宋体"));
	//CFont* pOldFont = dc.SelectObject(&font);
	CFont* pOldFont = dc.SelectObject(&CSkinHelper::GetDefaultFont());
	if (m_bHovering) dc.SetTextColor(m_crHoverText);
	else dc.SetTextColor(m_crNormalText);

	// 绘画字体
	CString strText;
	GetWindowText(strText);
	LONG dwStyte = GetWindowLong(m_hWnd, GWL_STYLE);
	UINT uFormat = DT_VCENTER | DT_SINGLELINE | DT_END_ELLIPSIS;
	if (dwStyte&SS_RIGHT) uFormat |= DT_RIGHT;
	else if (dwStyte&SS_CENTER) uFormat |= DT_CENTER;
	else uFormat |= DT_LEFT;
	dc.DrawText(strText, &ClientRect, uFormat);

	dc.SelectObject(pOldFont);

	return;
}

// 光标消息
BOOL CSkinStatic::OnSetCursor(CWnd * pWnd, UINT nHitTest, UINT message)
{
	LONG dwStyte = GetWindowLong(m_hWnd, GWL_STYLE);
	if ((dwStyte & SS_NOTIFY) == 0) return __super::OnSetCursor(pWnd, nHitTest, message);

	::SetCursor(CSkinHelper::GetSysHandCursor());

	return TRUE;
}

// 鼠标移动消息
void CSkinStatic::OnMouseMove(UINT nFlags, CPoint point)
{
	LONG dwStyte = GetWindowLong(m_hWnd, GWL_STYLE);
	if (m_bHovering == false && (dwStyte & SS_NOTIFY))
	{
		// 注册消息
		m_bHovering = true;

		TRACKMOUSEEVENT TrackMouseEvent;
		TrackMouseEvent.cbSize=sizeof(TrackMouseEvent);
		TrackMouseEvent.dwFlags=TME_LEAVE;
		TrackMouseEvent.hwndTrack=GetSafeHwnd();
		TrackMouseEvent.dwHoverTime=HOVER_DEFAULT;
		_TrackMouseEvent(&TrackMouseEvent);

		RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_ERASE | RDW_UPDATENOW | RDW_ERASENOW);
	}

	__super::OnMouseMove(nFlags, point);
}

// 鼠标离开消息
LRESULT CSkinStatic::OnMouseLeave(WPARAM wparam, LPARAM lparam)
{
	LONG dwStyte = GetWindowLong(m_hWnd, GWL_STYLE);
	if ((dwStyte & SS_NOTIFY) == 0) return 0;

	m_bHovering = false;
	RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_ERASE | RDW_UPDATENOW | RDW_ERASENOW);
	return 0;
}

// 标题消息
LRESULT	CSkinStatic::OnSetTextMesage(WPARAM wParam, LPARAM lParam)
{
	LRESULT lResult = Default();
	return lResult;
}

