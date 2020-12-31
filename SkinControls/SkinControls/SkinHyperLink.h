
#ifndef SKIN_HYPERLINK_H_
#define SKIN_HYPERLINK_H_
#pragma once

#include "SkinControlsDefine.h"

// 超连接类
class SKIN_CONTROLS_EXPORT CSkinHyperLink : public CStatic
{
public:
	// 构造函数
	CSkinHyperLink();
	// 析构函数
	virtual ~CSkinHyperLink();

	// 查询函数
public:
	// 获取调整
	bool GetAutoAdjust() { return m_bAutoAdjust; }
	// 获取访问
	bool GetVisited() { return m_bVisited; }
	// 获取下划线
	bool GetUnderline() { return m_bUnderline; }
	// 获取 URL
	LPCTSTR GetHyperLinkUrl() { return m_strURL; }

	// 设置函数
public:
	// 设置访问
    void SetVisited(bool bVisited);
	// 设置下划线
    void SetUnderline(bool bUnderline);
	// 设置调整
    void SetAutoAdjust(bool bAutoAdjust);
	// 设置 URL
	void SetHyperLinkUrl(LPCTSTR pszUrl);
	// 设置背景色
	void SetBackColor(COLORREF cr);
	// 字体颜色
	void SetHyperLinkTextColor(COLORREF crHoverText, COLORREF crNormalText, COLORREF crVisitedText);

	// 重载函数
protected:
	// 控件子类化
	virtual void PreSubclassWindow();

	// 内部函数
protected:
	// 初始化
	void InitHyperLink();
	// 调整位置
	void AdjustHyperLink();

	// 消息函数
protected:
	// 建立消息
	int OnCreate(LPCREATESTRUCT lpCreateStruct);
	// 绘画消息
	void OnPaint();
	// 单击控件
	void OnStnClicked();
	// 鼠标移动
	void OnMouseMove(UINT nFlags, CPoint point);
	// 光标消息
    BOOL OnSetCursor(CWnd * pWnd, UINT nHitTest, UINT message);
	// 鼠标离开
	LRESULT OnMouseLeave(WPARAM wparam, LPARAM lparam);
	// 标题消息
	LRESULT	OnSetTextMesage(WPARAM wParam, LPARAM lParam);
	// 控件颜色
	HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);

	DECLARE_MESSAGE_MAP()
	DECLARE_DYNAMIC(CSkinHyperLink)

	// 变量定义
private:
	bool m_bHovering; // 盘旋标志
	bool m_bVisited; // 是否访问
	bool m_bUnderline; // 是否划线
	bool m_bAutoAdjust; // 自动调整
	CString	 m_strURL; // 连接地址
	COLORREF m_crBack; // 背景
	COLORREF m_crHoverText; // 字体颜色
	COLORREF m_crNormalText; // 字体颜色
	COLORREF m_crVisitedText; // 字体颜色
};

#endif // SKIN_HYPERLINK_H_