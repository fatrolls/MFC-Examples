
#ifndef SKIN_DIALOG_H_
#define SKIN_DIALOG_H_
#pragma once

#include "SkinControlsDefine.h"
#include "SkinWindow.h"

// 对话框类
class SKIN_CONTROLS_EXPORT CSkinDialog : public CDialog
{
public:
	// 构造函数
	CSkinDialog(UINT nIDTemplate, CWnd* pParentWnd = NULL);
	// 析构函数
	virtual ~CSkinDialog();

	// 功能函数
public:
	// 设置SKIN图片
	bool SetSkinImage(LPCTSTR pszFileName, BitmapFormat bf = BF_UNKNOWN);
	bool SetSkinImage(BYTE* pBuffer, DWORD dwBufferSize, BitmapFormat bf = BF_UNKNOWN);
	bool SetSkinImage(LPCTSTR lpszResource, HINSTANCE hInst, BitmapFormat bf = BF_UNKNOWN);
	// 设置标题文字颜色 crInactiveText: 未激活文字的颜色
	void SetCaptionTextColor(COLORREF crText, COLORREF crInactiveText);

	// 重载函数
protected:
	// 初始化消息
	virtual BOOL OnInitDialog();

	// 消息映射
protected:
	// 非客户区大小
	void OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS* lpncsp);
	// 非客户区按键测试
	LRESULT OnNcHitTest(CPoint point);
	// 非客户区绘制
	void OnNcPaint();
	// 标题消息
	LRESULT	OnSetTextMesage(WPARAM wParam, LPARAM lParam);
	// 位置消息
	void OnSize(UINT nType, int cx, int cy);
	// 非客户区鼠标移动
	void OnNcMouseMove(UINT nHitTest, CPoint point);
	// 非客户区鼠标离开
	void OnNcMouseLeave();
	// 左键按下
	void OnNcLButtonDown(UINT nFlags, CPoint point);
	// 左键松开
	void OnNcLButtonUp(UINT nFlags, CPoint point);
	// 右键松开
	void OnNcRButtonUp(UINT nFlags, CPoint point);
	// 激活消息
	void OnActivateApp(BOOL bActive, DWORD dwThreadID);
	// 背景
	afx_msg BOOL OnEraseBkgnd(CDC * pDC);
	// 控件颜色
	HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

	DECLARE_MESSAGE_MAP()
	DECLARE_DYNAMIC(CSkinDialog)

protected:
	CSkinWindow* m_pSkin;

protected:
	COLORREF m_crBackground;
	COLORREF m_crBottomBar;
	COLORREF m_crBottomLine;
	int m_nBottomBarHeight;
	CBrush m_BkBrush;
};

#endif // SKIN_DIALOG_H_