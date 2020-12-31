
#ifndef SKIN_RADIOBOX_H_
#define SKIN_RADIOBOX_H_
#pragma once

#include "SkinControlsDefine.h"
#include "SkinButton.h"

// 单选框
class SKIN_CONTROLS_EXPORT CSkinRadioBox : public CSkinButton
{
public:
	CSkinRadioBox();
	virtual ~CSkinRadioBox();

	// 重载函数
public:
	// 控件子类化
	virtual void PreSubclassWindow();
	// 界面绘画函数
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);

	// 设置函数
public:
	// 加载位图
	bool SetButtonImage(LPCTSTR lpszFileName, BitmapFormat bf = BF_UNKNOWN);
	// 加载位图
	bool SetButtonImage(BYTE* pBuffer, DWORD dwBufferSize, BitmapFormat bf = BF_UNKNOWN);
	// 加载位图
	bool SetButtonImage(LPCTSTR lpszResource, HINSTANCE hInst, BitmapFormat bf = BF_UNKNOWN);
	// 设置文字颜色
	void SetRadioBoxTextColor(COLORREF clrTextColor);
	// 设置背景色
	void SetBackColor(COLORREF clrBack) { m_clrBack = clrBack; }

public:
	// 建立消息
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	// 大小消息
	void OnSize(UINT nType, int cx, int cy);
	// 左键按下
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	// 左键松开
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	// 擦除背景
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	// 失去焦点
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg LRESULT OnGetCheck(WPARAM, LPARAM);
	afx_msg LRESULT OnSetCheck(WPARAM, LPARAM);
	// 控件颜色
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);

	DECLARE_MESSAGE_MAP()
	DECLARE_DYNAMIC(CSkinRadioBox)

	// 内部函数
protected:
	void UncheckRadioButtonsInGroup();

protected:
	BOOL m_bChecked;
	COLORREF m_clrBack;
	COLORREF m_clrTextColor;

private:
	static CSkinImage m_ImageDefButton; // 默认按钮
};

#endif // SKIN_RADIOBOX_H_