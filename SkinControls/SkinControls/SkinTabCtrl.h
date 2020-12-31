
#ifndef SKIN_TABCTRL_H_
#define SKIN_TABCTRL_H_
#pragma once

#include "SkinControlsDefine.h"
#include "SkinImage.h"

// 选择控件
class SKIN_CONTROLS_EXPORT CSkinTabCtrl : public CTabCtrl
{
public:
	// 构造函数
	CSkinTabCtrl();
	// 析构函数
	virtual ~CSkinTabCtrl();

	// 功能函数
public:
	// 设置按钮间隔
	void SetItemPadding(int nPadding = 1);
	// 设置颜色
	void SetTabCtrlColor(COLORREF crBackGround, COLORREF crBorder);
	// 加载TAB图
	bool SetTabImage(LPCTSTR lpszFileName, BitmapFormat bf = BF_UNKNOWN);
	// 加载TAB图
	bool SetTabImage(BYTE* pBuffer, DWORD dwBufferSize, BitmapFormat bf = BF_UNKNOWN);
	// 加载TAB图
	bool SetTabImage(LPCTSTR lpszResource, HINSTANCE hInst, BitmapFormat bf = BF_UNKNOWN);
	// 加载TAB背景图
	bool SetTabBgImage(LPCTSTR lpszFileName, BitmapFormat bf = BF_UNKNOWN);
	// 加载TAB背景图
	bool SetTabBgImage(BYTE* pBuffer, DWORD dwBufferSize, BitmapFormat bf = BF_UNKNOWN);
	// 加载TAB背景图
	bool SetTabBgImage(LPCTSTR lpszResource, HINSTANCE hInst, BitmapFormat bf = BF_UNKNOWN);

	// 重载函数
protected:
	// 控件子类化
	virtual void PreSubclassWindow();

	// 消息函数
protected:
	// 建立消息
	int OnCreate(LPCREATESTRUCT lpCreateStruct);
	// 重画函数	
	void OnPaint();
	// 绘画背景
	BOOL OnEraseBkgnd(CDC* pDC);
	// 大小消息
	void OnSize(UINT nType, int cx, int cy);
	// 左键按下
	void OnLButtonDown(UINT nFlags, CPoint point);

	DECLARE_MESSAGE_MAP()

	// 变量定义
protected:
	COLORREF m_crBackGround; // 背景颜色
	COLORREF m_crBorder; // 边框颜色
	CSkinImage m_ImageTab; // TAB图片
	CSkinImage m_ImageTabBg; // TAB 背景
	int m_nItempadding; // 按钮中间的距离

private:
	static CSkinImage m_ImageDefTab; // 默认图片
};

#endif // SKIN_TABCTRL_H_