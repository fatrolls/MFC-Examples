
#ifndef SKIN_CHECKBUTTON_H_
#define SKIN_CHECKBUTTON_H_
#pragma once

#include "SkinControlsDefine.h"
#include "SkinCheckBox.h"

// 复选按钮 可以用来模拟按钮的一对状态 避免重新加载位图
class SKIN_CONTROLS_EXPORT CSkinCheckButton : public CSkinCheckBox
{
public:
	CSkinCheckButton();
	virtual ~CSkinCheckButton();

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

public:
	// 建立消息
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

	DECLARE_MESSAGE_MAP()
	DECLARE_DYNAMIC(CSkinCheckButton)

	// 内部函数
protected:
	void SizeToImage();
	bool CalcButtonRgn();
};

#endif // SKIN_CHECKBUTTON_H_