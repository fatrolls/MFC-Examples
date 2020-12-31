
#ifndef SKIN_RADIOBUTTON_H_
#define SKIN_RADIOBUTTON_H_
#pragma once

#include "SkinControlsDefine.h"
#include "SkinRadioBox.h"

// 单选按钮 可以用来模拟TabCtrl ListBox
class SKIN_CONTROLS_EXPORT CSkinRadioButton : public CSkinRadioBox
{
public:
	CSkinRadioButton();
	virtual ~CSkinRadioButton();

	// 重载函数
public:
	// 控件子类化
	virtual void PreSubclassWindow();
	// 界面绘画函数
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);

	// 设置函数
public:
	// 加载位图
	bool SetButtonImage(LPCTSTR lpszFileName, BitmapFormat bf = BF_UNKNOWN, bool bAutoClipTrans = false);
	// 加载位图
	bool SetButtonImage(BYTE* pBuffer, DWORD dwBufferSize, BitmapFormat bf = BF_UNKNOWN, bool bAutoClipTrans = false);
	// 加载位图
	bool SetButtonImage(LPCTSTR lpszResource, HINSTANCE hInst, BitmapFormat bf = BF_UNKNOWN, bool bAutoClipTrans = false);

	// 消息函数
protected:
	// 建立消息
	int OnCreate(LPCREATESTRUCT lpCreateStruct);

	// 内部函数
protected:
	void SizeToImage();
	bool CalcButtonRgn();

	DECLARE_MESSAGE_MAP()
	DECLARE_DYNAMIC(CSkinRadioButton)
};

#endif // SKIN_RADIOBUTTON_H_