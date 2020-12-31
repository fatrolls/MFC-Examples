
#ifndef SKIN_PROGRESSCTRL_H_
#define SKIN_PROGRESSCTRL_H_
#pragma once

#include "SkinControlsDefine.h"
#include "SkinImage.h"

// 进度条
class SKIN_CONTROLS_EXPORT CSkinProgressCtrl : public CProgressCtrl
{
public:
	CSkinProgressCtrl();
	virtual ~CSkinProgressCtrl();

	// 功能函数
public:
	// 设置背景图
	void SetProgressBackImage(LPCTSTR pszFileName, BitmapFormat bf = BF_UNKNOWN);
	// 设置背景图
	void SetProgressBackImage(LPCTSTR lpszResource, HINSTANCE hInst, BitmapFormat bf = BF_UNKNOWN);
	// 设置背景图
	void SetProgressBackImage(BYTE* pBuffer, DWORD dwBufferSize, BitmapFormat bf = BF_UNKNOWN);
	// 设置进度图
	void SetProgressImage(LPCTSTR pszFileName, BitmapFormat bf = BF_UNKNOWN);
	// 设置进度图
	void SetProgressImage(LPCTSTR lpszResource, HINSTANCE hInst, BitmapFormat bf = BF_UNKNOWN);
	// 设置进度图
	void SetProgressImage(BYTE* pBuffer, DWORD dwBufferSize, BitmapFormat bf = BF_UNKNOWN);

	// 重载函数
protected:
	// 控件子类化
	virtual void PreSubclassWindow();

protected:
	// 建立消息
	int OnCreate(LPCREATESTRUCT lpCreateStruct);
	// 绘画
	void OnPaint();
	// 背景
	BOOL OnEraseBkgnd(CDC* pDC);
	void OnSize(UINT nType, int cx, int cy);

	DECLARE_MESSAGE_MAP()
	DECLARE_DYNAMIC(CSkinProgressCtrl)

protected:
	CSkinImage m_ImageProgress; // 进度条
	CSkinImage m_ImageBack; //背景图
};

#endif // SKIN_PROGRESSCTRL_H_