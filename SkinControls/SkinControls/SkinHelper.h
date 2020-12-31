
#ifndef SKIN_HELPER_H_
#define SKIN_HELPER_H_
#pragma once

#include "SkinControlsDefine.h"

// 辅助类
class SKIN_CONTROLS_EXPORT CSkinHelper
{
public:
	// 默认字体
	static CFont& GetDefaultFont();
	// 标题字体
	static CFont& GetCaptionFont();

	// 手形光标
	static HCURSOR GetSysHandCursor();

private:
	static CFont m_DefaultFont; // 默认字体
	static CFont m_CaptionFont; // 标题字体

private:
	CSkinHelper() {}
	~CSkinHelper() {}
};

#endif // SKIN_HELPER_H_