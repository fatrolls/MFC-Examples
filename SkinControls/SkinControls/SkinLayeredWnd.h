
#ifndef SKIN_LAYERED_WND_H_
#define SKIN_LAYERED_WND_H_
#pragma once

#include "SkinControlsDefine.h"
#include "SkinImage.h"

/*
用法(以对话框为例):
定义一个 CSkinLayeredWnd m_SkinLayeredWnd;
处理ON_WM_SHOWWINDOW 和 ON_WM_WINDOWPOSCHANGED() 这2个消息
BOOL OnInitDialog()
{
// 分层窗口
m_SkinLayeredWnd.CreateLayered(...);
m_SkinLayeredWnd.InitLayeredArea(...);
}
VOID OnShowWindow(BOOL bShow, UINT nStatus)
{
__super::OnShowWindow(bShow, nStatus);

// 显示分层
if (m_SkinLayeredWnd.m_hWnd != NULL)
{
m_SkinLayeredWnd.ShowWindow((bShow == FALSE) ? SW_HIDE : SW_SHOW);
}

return;
}
VOID CDlgStatus::OnWindowPosChanged(WINDOWPOS * lpWndPos)
{
__super::OnWindowPosChanging(lpWndPos);

// 移动分层
if ((m_SkinLayeredWnd.m_hWnd != NULL) && (lpWndPos->cx >= 0) && (lpWndPos->cy > 0))
{
m_SkinLayeredWnd.SetWindowPos(NULL, lpWndPos->x, lpWndPos->y, lpWndPos->cx, lpWndPos->cy, SWP_NOZORDER);
}

return;
}
*/

// 分层窗口
class SKIN_CONTROLS_EXPORT CSkinLayeredWnd : public CWnd
{
public:
	// 构造函数
	CSkinLayeredWnd();
	// 析构函数
	virtual ~CSkinLayeredWnd();

	// 功能函数
public:
	// 创建窗口
	VOID CreateLayered(CWnd* pWndControl, CRect& rcWindow);
	// 设置区域
	VOID InitLayeredArea(CDC* pDCImage, BYTE cbAlpha, CRect& rcUnLayered, CPoint& PointRound, bool bUnLayeredChild);
	// 设置区域
	VOID InitLayeredArea(CSkinImage& Image, BYTE cbAlpha, CRect& rcUnLayered, CPoint& PointRound, bool bUnLayeredChild);

	// 消息映射
protected:
	// 关闭消息
	VOID OnClose();
	// 焦点消息
	VOID OnSetFocus(CWnd* pOldWnd);

	// 静态函数
protected:
	// 枚举函数
	static BOOL CALLBACK EnumChildProc(HWND hWndChild, LPARAM lParam);

	DECLARE_MESSAGE_MAP()

private:
	CWnd* m_pWndControl; // 控件窗口
};

#endif // SKIN_LAYERED_WND_H_