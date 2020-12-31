
#ifndef SKIN_EDIT_H_
#define SKIN_EDIT_H_
#pragma once

#include "SkinControlsDefine.h"

// 编辑框
class SKIN_CONTROLS_EXPORT CSkinEdit : public CEdit
{
	// 函数定义
public:
	// 构造函数
	CSkinEdit();
	// 析构函数
	virtual ~CSkinEdit();

	// 功能函数
public:
	// 设置颜色
	void SetEnableColor(COLORREF crEnableText, COLORREF crEnableBK, COLORREF crEnableBorder);
	// 设置颜色
	void SetDisableColor(COLORREF crDisableText, COLORREF crDisableBK, COLORREF crDisableBorder);

	// 消息函数 
protected:
	// 重画消息
    void OnNcPaint();
	// 绘画控件
	HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);

	DECLARE_MESSAGE_MAP()

	// 画刷对象
public:
	CBrush m_brEnable; // 画刷资源
	CBrush m_brDisable; // 画刷资源

	// 背景颜色
public:
	COLORREF m_crEnableBK; // 背景颜色
	COLORREF m_crDisableBK; // 背景颜色

	// 字体颜色
public:
	COLORREF m_crEnableText; // 字体颜色
	COLORREF m_crDisableText; // 字体颜色

	// 边框颜色
public:
	COLORREF m_crEnableBorder; // 边框颜色
	COLORREF m_crDisableBorder; // 边框颜色
};

#endif // SKIN_EDIT_H_