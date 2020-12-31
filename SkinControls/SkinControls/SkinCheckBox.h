
#ifndef SKIN_CHECKBOX_H_
#define SKIN_CHECKBOX_H_
#pragma once

#include "SkinControlsDefine.h"
#include "SkinButton.h"

// 复选框
class SKIN_CONTROLS_EXPORT CSkinCheckBox : public CSkinButton
{
public:
	CSkinCheckBox();
	virtual ~CSkinCheckBox();

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
	void SetCheckBoxTextColor(COLORREF clrTextColor);
	// 设置背景色
	void SetBackColor(COLORREF clrBack) { m_clrBack = clrBack; }
	// 从资源加载图片设置背景图片
	void SetBackImage(LPCTSTR lpszResource, HINSTANCE hInst, BitmapFormat bf = BF_UNKNOWN);
	// 从文件加载图片设置背景图片
	void SetBackImage(LPCTSTR lpszFileName, BitmapFormat bf = BF_UNKNOWN);
	// 从内存加载图片设置背景图片
	void SetBackImage(BYTE* pBuffer, DWORD dwBufferSize, BitmapFormat bf = BF_UNKNOWN);

public:
	// 建立消息
	int OnCreate(LPCREATESTRUCT lpCreateStruct);
	// 大小消息
	void OnSize(UINT nType, int cx, int cy);
	// 左键按下
	void OnLButtonDown(UINT nFlags, CPoint point);
	// 左键松开
	void OnLButtonUp(UINT nFlags, CPoint point);
	// 失去焦点
	void OnKillFocus(CWnd* pNewWnd);
	LRESULT OnGetCheck(WPARAM, LPARAM);
	LRESULT OnSetCheck(WPARAM, LPARAM);
	// 控件颜色
	HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);

	DECLARE_MESSAGE_MAP()
	DECLARE_DYNAMIC(CSkinCheckBox)

protected:
	BOOL m_bChecked;
	CSkinImage m_ImageBackground;
	COLORREF m_clrBack;
	COLORREF m_clrTextColor;

private:
	static CSkinImage m_ImageDefButton; // 默认按钮
};

#endif // SKIN_CHECKBOX_H_