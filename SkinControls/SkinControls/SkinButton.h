
#ifndef SKIN_BUTTON_H_
#define SKIN_BUTTON_H_
#pragma once

#include "SkinControlsDefine.h"
#include "SkinImage.h"

// 按钮类
// 如果图片是PNG 且 有alpha的话 可以继承CSkinButton然后重新处理OnEraseBkgnd让其返回默认处理方式(CButton::OnEraseBkgnd),
// 这样处理就不会导致4个状态图有重合的现象,会有一个系统默认背景,看起来好一点.
class SKIN_CONTROLS_EXPORT CSkinButton : public CButton
{
public:
	CSkinButton();
	virtual ~CSkinButton();

	// 重载函数
protected:
	// 控件子类化
	virtual void PreSubclassWindow();
	// 界面绘画函数
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);

	// 设置函数
public:
	// 加载位图
	bool SetButtonImage(LPCTSTR pszFileName, BitmapFormat bf = BF_UNKNOWN, bool bAutoClipTrans = false);
	// 加载位图
	bool SetButtonImage(BYTE* pBuffer, DWORD dwBufferSize, BitmapFormat bf = BF_UNKNOWN, bool bAutoClipTrans = false);
	// 加载位图
	bool SetButtonImage(LPCTSTR lpszResource, HINSTANCE hInst, BitmapFormat bf = BF_UNKNOWN, bool bAutoClipTrans = false);
	// 设置透明色
	void SetMaskColor(COLORREF clrMask) { m_clrMask = clrMask; }

	// 消息函数
protected:
	// 建立消息
	int OnCreate(LPCREATESTRUCT lpCreateStruct);
	// 鼠标移动
	void OnMouseMove(UINT nFlags, CPoint point);
	// 鼠标离开
	LRESULT OnMouseLeave(WPARAM wparam, LPARAM lparam);
	// 背景消息
	BOOL OnEraseBkgnd(CDC * pDC);
	// 大小消息
	void OnSize(UINT nType, int cx, int cy);

	DECLARE_MESSAGE_MAP()
	DECLARE_DYNAMIC(CSkinButton)

	// 内部函数
protected:
	void SizeToImage();
	bool CalcButtonRgn();

protected:
	CSkinImage m_ImageButton; // 按钮图片
	bool m_bAutoClipTrans; // 是否自动裁剪透明区域
	COLORREF m_clrMask; // MASK颜色
	bool m_bMouseOver; // 盘旋标志

private:
	static CSkinImage m_ImageDefButton; // 默认按钮
};

#endif // SKIN_BUTTON_H_