
#ifndef SKIN_SPLITTER_H_
#define SKIN_SPLITTER_H_
#pragma once

#include "SkinControlsDefine.h"

// 拆分类型
enum SplitterType
{
	ST_HOR, // 横向拆分
	ST_VOR, // 竖向拆分
};

// 拆分事件
interface ISplitterEvent
{
	// 拆分事件
	virtual void OnSplitterEvent(UINT uControlID, int nXPos, int nYPos) = 0;
};

// 拆分条类
class SKIN_CONTROLS_EXPORT CSkinSplitter : public CWnd
{
public:
	// 构造函数
	CSkinSplitter();
	// 析构函数
	virtual ~CSkinSplitter();

	// 重载函数
protected:
	// 绑定函数
	virtual void PreSubclassWindow();
	// 命令消息
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);

	// 配置函数
public:
	// 设置类型
	void SetSplitterType(SplitterType st);
	// 设置范围
	void SetSplitterRange(int nMinDragPos, int nMaxDragPos);
	// 设置接口
	void SetSplitterEvent(ISplitterEvent* pISplitterEvent);

	// 设置颜色
public:
	// 背景颜色
	void SetSplitterColor(COLORREF crBackColor);

	// 查询函数
public:
	// 获取类型
	SplitterType GetSplitterType() { return m_SplitterType; }
	// 获取接口
	ISplitterEvent* GetSplitterEvent() { return m_pISplitterEvent; };
	// 设置范围
	void GetSplitterRange(int& nMinDragPos, int& nMaxDragPos) { nMinDragPos = m_nMinDragPos; nMaxDragPos = m_nMaxDragPos; }

	// 消息函数
protected:
	// 重画消息
	void OnPaint();
	// 绘画背景
	BOOL OnEraseBkgnd(CDC * pDC);
	// 失去焦点
	void OnKillFocus(CWnd * pNewWnd);
	// 鼠标消息
	void OnMouseMove(UINT nFlags, CPoint point);
	// 鼠标消息
	void OnLButtonUp(UINT nFlags, CPoint point);
	// 鼠标消息
	void OnLButtonDown(UINT nFlags, CPoint point);
	// 光标消息
	BOOL OnSetCursor(CWnd * pWnd, UINT nHitTest, UINT uMmessage);

	DECLARE_MESSAGE_MAP()

	// 状态变量
protected:
	bool m_bMouseDown; // 是否按下
	CRect m_rcDrawLine; // 线条位置

	// 属性变量
protected:
	int m_nMaxDragPos; // 最大位置
	int m_nMinDragPos; // 最小位置
	SplitterType m_SplitterType; // 拆分类型

	// 颜色变量
protected:
	COLORREF m_crBackColor; // 背景颜色

	// 组件变量
protected:
	ISplitterEvent* m_pISplitterEvent; // 拆分事件
};

#endif // SKIN_SPLITTER_H_