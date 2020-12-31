
#ifndef SKIN_SCROLLBAR_H_
#define SKIN_SCROLLBAR_H_
#pragma once

#include "SkinControlsDefine.h"

// 滚动条类
class SKIN_CONTROLS_EXPORT CSkinScrollBar
{
	// 函数定义
public:
	// 构造函数
	CSkinScrollBar();
	// 析构函数
	virtual ~CSkinScrollBar();

	// 功能函数
public:
	// 配置滚动
	void InitScroolBar(CWnd* pWnd);

	// 资源变量
public:
	static CBitmap m_bmScrollBar;
};

#endif // SKIN_SCROLLBAR_H_