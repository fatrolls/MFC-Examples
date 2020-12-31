
#include "stdafx.h"
#include "Resource.h"
#include "SkinHyperLink.h"
#include "SkinHelper.h"

#define DEF_HOVERTEXT_COLOR			RGB(255,0,255)
#define DEF_VISITEDTEXT_COLOR		RGB(0,0,100)
#define DEF_NORMALTEXT_COLOR		RGB(0,0,230)

//////////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNAMIC(CSkinHyperLink, CStatic)

BEGIN_MESSAGE_MAP(CSkinHyperLink, CStatic)
	ON_WM_PAINT()
	ON_WM_CREATE()
    ON_WM_SETCURSOR()
	ON_WM_MOUSEMOVE()
	ON_MESSAGE(WM_MOUSELEAVE,OnMouseLeave)
	ON_MESSAGE(WM_SETTEXT,OnSetTextMesage)
	ON_CONTROL_REFLECT(STN_CLICKED, OnStnClicked)
	ON_WM_CTLCOLOR_REFLECT()
END_MESSAGE_MAP()

// 构造函数
CSkinHyperLink::CSkinHyperLink()
{
	m_bVisited=false;
	m_bHovering=false;
	m_bUnderline=true;
	m_bAutoAdjust=true;
	m_crBack = CLR_NONE;
	m_crHoverText=RGB(250,0,0);
	m_crNormalText=RGB(0,0,255);
	m_crVisitedText=RGB(0,0,100);
}

// 析构函数
CSkinHyperLink::~CSkinHyperLink()
{
}


// 控件子类化
void CSkinHyperLink::PreSubclassWindow()
{
	__super::PreSubclassWindow();

	// 初始化
	InitHyperLink();

	return;
}

// 建立消息
int CSkinHyperLink::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (__super::OnCreate(lpCreateStruct)==-1) return -1;

	// 初始化
	InitHyperLink();

	return 0;
}

HBRUSH CSkinHyperLink::CtlColor(CDC* pDC, UINT nCtlColor)
{
	pDC->SetBkMode(TRANSPARENT);
	return (HBRUSH)::GetStockObject(NULL_BRUSH);
}

// 绘画消息
void CSkinHyperLink::OnPaint()
{
	CPaintDC dc(this);

	// 获取位置
	CRect ClientRect;
	GetClientRect(&ClientRect);

	// 设置 DC
	dc.SetBkMode(TRANSPARENT);
	if (m_crBack != CLR_NONE) dc.FillSolidRect(&ClientRect, m_crBack);
	CFont* pOldFont = dc.SelectObject(&CSkinHelper::GetDefaultFont());
	if (m_bHovering) dc.SetTextColor(m_crHoverText);
	else if (m_bVisited) dc.SetTextColor(m_crVisitedText);
	else dc.SetTextColor(m_crNormalText);

	// 绘画字体
	CString strText;
	GetWindowText(strText);
	LONG dwStyte=GetWindowLong(m_hWnd,GWL_STYLE);
	UINT uFormat=DT_VCENTER|DT_SINGLELINE|DT_END_ELLIPSIS;
	if (dwStyte&SS_RIGHT) uFormat|=DT_RIGHT;
	else if (dwStyte&SS_CENTER) uFormat|=DT_CENTER;
	else uFormat|=DT_LEFT;
	dc.DrawText(strText,&ClientRect,uFormat);

	dc.SelectObject(pOldFont);

	return;
}

// 光标消息
BOOL CSkinHyperLink::OnSetCursor(CWnd * pWnd, UINT nHitTest, UINT message)
{
	::SetCursor(CSkinHelper::GetSysHandCursor());

	return TRUE;
}

// 单击控件
void CSkinHyperLink::OnStnClicked()
{
	// 判断状态
	if ((m_strURL.IsEmpty())) return;

	// 打开网页
	ShellExecute(NULL,TEXT("open"), m_strURL,NULL,NULL,SW_SHOW);

	// 重画控件
	if (m_bVisited == false)
	{
		m_bVisited=true;
		Invalidate();
	}

	return;
}

// 鼠标移动消息
void CSkinHyperLink::OnMouseMove(UINT nFlags, CPoint point)
{
	if (m_bHovering==false)
	{
		// 注册消息
		m_bHovering=true;

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
LRESULT CSkinHyperLink::OnMouseLeave(WPARAM wparam, LPARAM lparam)
{
	m_bHovering=false;
	RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_ERASE | RDW_UPDATENOW | RDW_ERASENOW);
	return 0;
}

// 标题消息
LRESULT	CSkinHyperLink::OnSetTextMesage(WPARAM wParam, LPARAM lParam)
{
	LRESULT lResult=Default();
	if (m_bAutoAdjust) AdjustHyperLink();
	return lResult;
}

// 设置访问
void CSkinHyperLink::SetVisited(bool bVisited)
{
	if (m_bVisited!=bVisited)
	{
		m_bVisited=bVisited;
		if (GetSafeHwnd()) RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_ERASE | RDW_UPDATENOW | RDW_ERASENOW);
	}
	return;
}

// 设置下划线
void CSkinHyperLink::SetUnderline(bool bUnderline)
{
	if (m_bUnderline!=bUnderline)
	{
		m_bUnderline=bUnderline;
		if (GetSafeHwnd()) RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_ERASE | RDW_UPDATENOW | RDW_ERASENOW);
	}
	return;
}

// 设置 URL
void CSkinHyperLink::SetHyperLinkUrl(LPCTSTR pszUrl)
{
	// 设置变量
	m_strURL=pszUrl;

	return;
}

// 设置调整
void CSkinHyperLink::SetAutoAdjust(bool bAutoAdjust)
{
	if (m_bAutoAdjust!=bAutoAdjust)
	{
		m_bAutoAdjust=bAutoAdjust;
		if (m_bAutoAdjust) AdjustHyperLink();
	}
	return;
}

// 背景颜色
void CSkinHyperLink::SetBackColor(COLORREF crBackColor)
{
	// 设置变量
	m_crBack = crBackColor;

	// 重画窗口
	if (m_hWnd!=NULL)
	{
		RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_ERASE | RDW_UPDATENOW | RDW_ERASENOW);
	}

	return;
}

// 字体颜色
void CSkinHyperLink::SetHyperLinkTextColor(COLORREF crHoverText, COLORREF crNormalText, COLORREF crVisitedText)
{
	// 设置变量
	m_crHoverText = crHoverText;
	m_crNormalText = crNormalText;
	m_crVisitedText = crVisitedText;

	// 重画窗口
	if (m_hWnd!=NULL)
	{
		RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_ERASE | RDW_UPDATENOW | RDW_ERASENOW);
	}

	return;
}

// 初始化
void CSkinHyperLink::InitHyperLink()
{
	SetWindowLong(m_hWnd,GWL_STYLE,GetStyle()|SS_NOTIFY);
	if (m_bAutoAdjust) AdjustHyperLink();

	return;
}

// 调整位置
void CSkinHyperLink::AdjustHyperLink()
{
	// 获取标题
	CString strText;
	GetWindowText(strText);

	// 获取位置
	CRect ControlRect;
	GetWindowRect(&ControlRect);
	GetParent()->ScreenToClient(&ControlRect);

	// 计算长度
	CDC* pDC=GetDC();
	CSize Size=pDC->GetTextExtent(strText);
	ReleaseDC(pDC);

	// 移动位置
	MoveWindow(ControlRect.left,ControlRect.top,Size.cx,Size.cy);

	return;
}

