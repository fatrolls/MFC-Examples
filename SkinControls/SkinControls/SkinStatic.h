
#ifndef SKIN_STATIC_H_
#define SKIN_STATIC_H_
#pragma once

#include "SkinControlsDefine.h"

// 文字或分隔条
class SKIN_CONTROLS_EXPORT CSkinStatic : public CStatic
{
public:
	// 构造函数
	CSkinStatic();
	// 析构函数
	virtual ~CSkinStatic();

	// 设置函数
public:
	// 设置下划线
    void SetUnderline(bool bUnderline);
	// 设置分隔条
	void SetSeperator(bool bSeperator);
	// 设置背景色
	void SetBackColor(COLORREF cr);
	// 字体颜色
	void SetStaticTextColor(COLORREF crHoverText, COLORREF crNormalText);
	// 分隔条颜色
	void SetSeperatorColor(COLORREF crFirst, COLORREF crSecond);

	// 重载函数
protected:
	// 控件子类化
	virtual void PreSubclassWindow();

	// 消息函数
protected:
	// 建立消息
	int OnCreate(LPCREATESTRUCT lpCreateStruct);
	// 绘画消息
	void OnPaint();
	// 鼠标移动
	void OnMouseMove(UINT nFlags, CPoint point);
	// 光标消息
    BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	// 鼠标离开
	LRESULT OnMouseLeave(WPARAM wparam, LPARAM lparam);
	// 标题消息
	LRESULT	OnSetTextMesage(WPARAM wParam, LPARAM lParam);
	// 控件颜色
	HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);

	DECLARE_MESSAGE_MAP()
	DECLARE_DYNAMIC(CSkinStatic)

	// 变量定义
protected:
	bool m_bHovering; // 盘旋标志
	bool m_bUnderline; // 是否划线
	bool m_bSeperator; // 分隔条
	COLORREF m_crBack; // 背景
	COLORREF m_crHoverText; // 字体颜色
	COLORREF m_crNormalText; // 字体颜色
	COLORREF m_crSepFirst; // 分隔条颜色
	COLORREF m_crSepSecond; // 分隔条颜色
};

#endif // SKIN_STATIC_H_